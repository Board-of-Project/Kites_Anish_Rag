/**
 * @file reorder_visual.h
 * @brief Side-by-side visualisation of a reordering.
 *
 * Every instruction of the original program gets a colour from a monochromatic gradient (light
 * for the first instruction, dark for the last). The reordered program keeps each instruction's
 * colour, so the shuffled gradient shows at a glance how much and where instructions moved.
 * Hovering an instruction in either list highlights it and its counterpart in the other list.
 */
#pragma once

#include <QColor>
#include <QWidget>

#include <cstddef>
#include <string>
#include <vector>

class QComboBox;
class QFrame;
class QLabel;
class QListWidget;
class QSlider;

namespace Kites
{
/// User-adjustable look of the gradient (the lightness range itself depends on light/dark mode).
struct ReorderGradient
{
    double hue = 215.0;        ///< 0..359
    double saturation = 0.75;  ///< 0..1 (saturation of the dark end; the light end is paler)
    double contrast = 1.0;     ///< 0.3..1: how much of the lightness range is used (1 = steepest)
};

class ReorderVisualView : public QWidget
{
  public:
    explicit ReorderVisualView(QWidget *parent = nullptr);

    /**
     * @param originalLines   one text line per original instruction
     * @param reorderedLines  one text line per reordered instruction
     * @param originalIndex   originalIndex[k] = position in the original program of the
     *                        instruction now at position k (see reorder::reorderProgram)
     */
    void setData(const std::vector<std::string> &originalLines,
                 const std::vector<std::string> &reorderedLines,
                 const std::vector<std::size_t> &originalIndex);
    void clear();

  protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    /// Re-colours the legend when the application switches between light and dark themes.
    void changeEvent(QEvent *event) override;

  private:
    static constexpr int kNone = -1;

    void paintRow(QListWidget *list, int row, int originalIdx, bool highlighted);
    void refreshLegend();
    void onColorChoice(int comboIndex);
    void applyGradientChange();
    void setHover(int originalIdx);
    void updateInfo(int originalIdx);

    QListWidget *m_originalList = nullptr;
    QListWidget *m_reorderedList = nullptr;
    QLabel *m_info = nullptr;
    QFrame *m_legendBar = nullptr;
    QComboBox *m_colorBox = nullptr;
    QSlider *m_contrastSlider = nullptr;
    ReorderGradient m_gradient;
    int m_lastColorIndex = 0; ///< combo entry to fall back to if "Custom..." is cancelled

    std::vector<int> m_order;    ///< m_order[k]  = original index of reordered row k
    std::vector<int> m_position; ///< m_position[i] = reordered row of original instruction i
    int m_hovered = kNone;       ///< original index currently highlighted
};
} // namespace Kites
