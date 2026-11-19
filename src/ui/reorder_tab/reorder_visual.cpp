#include "reorder_visual.h"

#include <QEvent>
#include <QFont>
#include <QFontDatabase>
#include <QColorDialog>
#include <QComboBox>
#include <QFrame>
#include <QSlider>
#include <QVariantList>
#include <QGuiApplication>
#include <QPainter>
#include <QPalette>
#include <QStyledItemDelegate>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QSplitter>
#include <QVBoxLayout>

#include <algorithm>
#include <cstdlib>

namespace Kites
{
namespace
{
// ---- colour scheme -------------------------------------------------------------------------
// The hue/saturation/contrast come from the user (ReorderGradient). What depends on the theme
// is the lightness range: dark mode keeps even the darkest shade clearly lighter than a dark
// background, light mode keeps even the lightest shade clearly darker than a light background.
// Ranges are wide on purpose: small programs have few rows, so neighbouring rows must differ.
struct LightnessRange
{
    double first; // lightness of the first instruction
    double last;  // lightness of the last instruction
};
constexpr LightnessRange kLightModeRange{0.93, 0.20};
constexpr LightnessRange kDarkModeRange{0.90, 0.30};

bool isDarkMode()
{
    return QGuiApplication::palette().color(QPalette::Window).lightness() < 128;
}

QColor gradientColor(const ReorderGradient &g, double t)
{
    const LightnessRange &r = isDarkMode() ? kDarkModeRange : kLightModeRange;
    const double mid = (r.first + r.last) / 2.0;
    const double half = (r.first - r.last) / 2.0 * g.contrast;
    const double lightness = (mid + half) - 2.0 * half * t; // first -> last: light -> dark
    // paler at the light end, fuller colour at the dark end: more separation between rows
    const double saturation = g.saturation * (0.55 + 0.45 * t);
    return QColor::fromHslF(g.hue / 360.0, saturation, lightness);
}

QColor textColorFor(const QColor &background)
{
    return background.lightnessF() > 0.55 ? QColor(20, 20, 20) : QColor(Qt::white);
}

const QColor kHighlightBg(255, 179, 0); // amber: stands out against every shade, both modes
const QColor kHighlightFg(Qt::black);
const QColor kUnknownBg(128, 128, 128);

// Item data used by RowDelegate
constexpr int kOriginalIndexRole = Qt::UserRole;     // int: original position (-1 = unknown)
constexpr int kHighlightedRole = Qt::UserRole + 1;   // bool
constexpr int kCountRole = Qt::UserRole + 2;         // int: number of instructions

/**
 * Paints rows itself instead of using item brushes: the application stylesheet
 * (QListWidget::item { padding; margin }, ::item:hover { background }) otherwise overrides
 * the item colours, which is what made the gradient invisible.
 */
class RowDelegate : public QStyledItemDelegate
{
  public:
    RowDelegate(const ReorderGradient *gradient, QObject *parent)
        : QStyledItemDelegate(parent), m_gradient(gradient)
    {
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override
    {
        const bool highlighted = index.data(kHighlightedRole).toBool();
        const int original = index.data(kOriginalIndexRole).toInt();
        const int count = index.data(kCountRole).toInt();

        QColor bg = kUnknownBg;
        if (highlighted)
        {
            bg = kHighlightBg;
        }
        else if (original >= 0)
        {
            bg = gradientColor(*m_gradient,
                               count > 1 ? static_cast<double>(original) / (count - 1) : 0.0);
        }
        const QColor fg = highlighted ? kHighlightFg : textColorFor(bg);

        painter->save();
        const QRect rowRect = option.rect.adjusted(0, 1, 0, -1); // 1px gap between rows
        painter->fillRect(rowRect, bg);
        QFont font = option.font;
        font.setBold(highlighted);
        painter->setFont(font);
        painter->setPen(fg);
        painter->drawText(rowRect.adjusted(8, 0, -8, 0), Qt::AlignVCenter | Qt::AlignLeft,
                          index.data(Qt::DisplayRole).toString());
        painter->restore();
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        const QFontMetrics fm(option.font);
        return QSize(fm.horizontalAdvance(index.data(Qt::DisplayRole).toString()) + 16,
                     fm.height() + 8);
    }

  private:
    const ReorderGradient *m_gradient;
};
} // namespace

ReorderVisualView::ReorderVisualView(QWidget *parent) : QWidget(parent)
{
    const QFont mono = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    auto makeList = [&]()
    {
        auto *list = new QListWidget(this);
        list->setFont(mono);
        list->setSelectionMode(QAbstractItemView::NoSelection);
        list->setItemDelegate(new RowDelegate(&m_gradient, list));
        list->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        list->setMouseTracking(true);
        list->viewport()->setMouseTracking(true);
        list->viewport()->installEventFilter(this);
        return list;
    };
    m_originalList = makeList();
    m_reorderedList = makeList();

    // legend: gradient bar from the first to the last original instruction
    auto *legend = new QHBoxLayout;
    m_legendBar = new QFrame(this);
    m_legendBar->setFixedHeight(14);
    m_legendBar->setMinimumWidth(160);
    m_legendBar->setFrameShape(QFrame::Box);
    refreshLegend();
    legend->addWidget(new QLabel("Original order:  first", this));
    legend->addWidget(m_legendBar, 1);
    legend->addWidget(new QLabel("last", this));

    // colour choice + contrast
    struct Preset { const char *name; double hue; double saturation; };
    static const Preset presets[] = {
        {"Blue", 215, 0.75}, {"Teal", 175, 0.70}, {"Green", 140, 0.60}, {"Orange", 28, 0.85},
        {"Red", 355, 0.75},  {"Purple", 275, 0.60}, {"Pink", 325, 0.70}, {"Grey", 0, 0.0},
    };
    m_colorBox = new QComboBox(this);
    for (const Preset &p : presets)
    {
        m_colorBox->addItem(p.name, QVariantList{p.hue, p.saturation});
    }
    m_colorBox->addItem("Custom...");
    m_contrastSlider = new QSlider(Qt::Horizontal, this);
    m_contrastSlider->setRange(30, 100); // percent of the lightness range that is used
    m_contrastSlider->setValue(100);
    m_contrastSlider->setFixedWidth(120);
    m_contrastSlider->setToolTip("Steepness of the gradient: higher = bigger difference "
                                 "between neighbouring instructions");
    legend->addSpacing(12);
    legend->addWidget(new QLabel("Colour:", this));
    legend->addWidget(m_colorBox);
    legend->addWidget(new QLabel("Contrast:", this));
    legend->addWidget(m_contrastSlider);
    connect(m_colorBox, &QComboBox::activated, this, [this](int i) { onColorChoice(i); });
    connect(m_contrastSlider, &QSlider::valueChanged, this,
            [this](int v)
            {
                m_gradient.contrast = v / 100.0;
                applyGradientChange();
            });

    m_info = new QLabel(this);
    m_info->setMinimumHeight(m_info->fontMetrics().height() + 4);

    auto makePane = [&](const QString &title, QListWidget *list)
    {
        auto *pane = new QWidget(this);
        auto *layout = new QVBoxLayout(pane);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(new QLabel(title, pane));
        layout->addWidget(list, 1);
        return pane;
    };
    auto *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(makePane("Original code", m_originalList));
    splitter->addWidget(makePane("Reordered code (number = original position)", m_reorderedList));
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);

    auto *root = new QVBoxLayout(this);
    root->addLayout(legend);
    root->addWidget(splitter, 1);
    root->addWidget(m_info);
    updateInfo(kNone);
}

void ReorderVisualView::refreshLegend()
{
    m_legendBar->setStyleSheet(QString("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
                                       "stop:0 %1, stop:1 %2);")
                                   .arg(gradientColor(m_gradient, 0.0).name(), gradientColor(m_gradient, 1.0).name()));
}

void ReorderVisualView::applyGradientChange()
{
    refreshLegend();
    m_originalList->viewport()->update(); // rows read the gradient when they are painted
    m_reorderedList->viewport()->update();
}

void ReorderVisualView::onColorChoice(int comboIndex)
{
    if (comboIndex == m_colorBox->count() - 1) // "Custom..."
    {
        const QColor chosen = QColorDialog::getColor(
            QColor::fromHslF(m_gradient.hue / 360.0, m_gradient.saturation, 0.5), this,
            "Gradient colour");
        if (!chosen.isValid())
        {
            m_colorBox->setCurrentIndex(m_lastColorIndex); // cancelled: keep the old colour
            return;
        }
        // only hue and saturation matter: lightness is what the gradient itself varies
        m_gradient.hue = chosen.hslHue() < 0 ? 0.0 : chosen.hslHue(); // -1 for greys
        m_gradient.saturation = chosen.hslSaturationF();
    }
    else
    {
        const QVariantList v = m_colorBox->itemData(comboIndex).toList();
        m_gradient.hue = v.value(0).toDouble();
        m_gradient.saturation = v.value(1).toDouble();
    }
    m_lastColorIndex = comboIndex;
    applyGradientChange();
}

void ReorderVisualView::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::PaletteChange || event->type() == QEvent::ApplicationPaletteChange)
    {
        applyGradientChange();
    }
    QWidget::changeEvent(event);
}

void ReorderVisualView::paintRow(QListWidget *list, int row, int originalIdx, bool highlighted)
{
    if (QListWidgetItem *item = list->item(row))
    {
        item->setData(kOriginalIndexRole, originalIdx);
        item->setData(kHighlightedRole, highlighted);
        item->setData(kCountRole, static_cast<int>(m_position.size()));
    }
}

void ReorderVisualView::clear()
{
    m_originalList->clear();
    m_reorderedList->clear();
    m_order.clear();
    m_position.clear();
    m_hovered = kNone;
    updateInfo(kNone);
}

void ReorderVisualView::setData(const std::vector<std::string> &originalLines,
                                const std::vector<std::string> &reorderedLines,
                                const std::vector<std::size_t> &originalIndex)
{
    clear();
    const int n = static_cast<int>(originalLines.size());
    const int m = static_cast<int>(reorderedLines.size());

    // mapping in both directions; anything out of range simply has no counterpart
    m_position.assign(n, kNone);
    m_order.assign(m, kNone);
    for (int k = 0; k < m && k < static_cast<int>(originalIndex.size()); ++k)
    {
        const int i = static_cast<int>(originalIndex[k]);
        if (i >= 0 && i < n)
        {
            m_order[k] = i;
            m_position[i] = k;
        }
    }

    const int width = static_cast<int>(QString::number(std::max(n, 1) - 1).size());
    auto text = [&](int idx, const std::string &line)
    {
        const QString label = idx >= 0 ? QString::number(idx).rightJustified(width, ' ')
                                       : QString(width, '?');
        return label + "  " + (line.empty() ? QString("(no text available)")
                                             : QString::fromStdString(line));
    };

    for (int i = 0; i < n; ++i)
    {
        m_originalList->addItem(new QListWidgetItem(text(i, originalLines[i])));
        paintRow(m_originalList, i, i, false);
    }
    for (int k = 0; k < m; ++k)
    {
        m_reorderedList->addItem(new QListWidgetItem(text(m_order[k], reorderedLines[k])));
        paintRow(m_reorderedList, k, m_order[k], false);
    }
}

void ReorderVisualView::updateInfo(int originalIdx)
{
    if (originalIdx < 0 || originalIdx >= static_cast<int>(m_position.size()) ||
        m_position[originalIdx] < 0)
    {
        m_info->setText("Hover an instruction to see where it moved.");
        return;
    }
    const int to = m_position[originalIdx];
    const int delta = to - originalIdx;
    m_info->setText(QString("Instruction %1: original position %1  ->  reordered position %2 (%3)")
                        .arg(originalIdx)
                        .arg(to)
                        .arg(delta == 0 ? QString("did not move")
                                        : QString("moved %1 %2")
                                              .arg(std::abs(delta))
                                              .arg(delta < 0 ? "up" : "down")));
}

void ReorderVisualView::setHover(int originalIdx)
{
    if (originalIdx == m_hovered)
    {
        return;
    }
    // restore the previous pair
    if (m_hovered != kNone && m_hovered < static_cast<int>(m_position.size()))
    {
        paintRow(m_originalList, m_hovered, m_hovered, false);
        if (m_position[m_hovered] >= 0)
        {
            paintRow(m_reorderedList, m_position[m_hovered], m_hovered, false);
        }
    }
    m_hovered = originalIdx;
    if (m_hovered != kNone)
    {
        paintRow(m_originalList, m_hovered, m_hovered, true);
        const int row = m_position[m_hovered];
        if (row >= 0)
        {
            paintRow(m_reorderedList, row, m_hovered, true);
            // the counterpart may be off screen in the other list: bring it into view
            m_originalList->scrollToItem(m_originalList->item(m_hovered),
                                         QAbstractItemView::EnsureVisible);
            m_reorderedList->scrollToItem(m_reorderedList->item(row),
                                          QAbstractItemView::EnsureVisible);
        }
    }
    updateInfo(m_hovered);
}

bool ReorderVisualView::eventFilter(QObject *watched, QEvent *event)
{
    QListWidget *list = nullptr;
    if (watched == m_originalList->viewport())
    {
        list = m_originalList;
    }
    else if (watched == m_reorderedList->viewport())
    {
        list = m_reorderedList;
    }
    if (!list)
    {
        return QWidget::eventFilter(watched, event);
    }

    if (event->type() == QEvent::MouseMove)
    {
        const auto *me = static_cast<QMouseEvent *>(event);
        const QListWidgetItem *item = list->itemAt(me->position().toPoint());
        int originalIdx = kNone;
        if (item)
        {
            const int row = list->row(item);
            originalIdx = (list == m_originalList)
                              ? row
                              : (row < static_cast<int>(m_order.size()) ? m_order[row] : kNone);
        }
        setHover(originalIdx);
    }
    else if (event->type() == QEvent::Leave)
    {
        setHover(kNone);
    }
    return QWidget::eventFilter(watched, event);
}
} // namespace Kites
