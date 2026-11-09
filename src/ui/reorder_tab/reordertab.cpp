#include "reordertab.h"

#include "assembler/assembler.h"
#include "common/globals.h"
#include "custom_pseudo_manager/custom_pseudo_manager.h"
#include "processor/processor_manager.h"
#include "reorder/reorder.h"
#include "ui/editor_tab/editortab.h"

#include <QClipboard>
#include <QComboBox>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSplitter>
#include <QVBoxLayout>
#include <QtConcurrent/QtConcurrent>

#include <fstream>
#include <iomanip>
#include <sstream>

namespace Kites
{
namespace
{
struct ProcessorChoice
{
    const char *label;
    ProcessorType type;
};
const ProcessorChoice kProcessors[] = {
    {"Single cycle (RVSS)", ProcessorType::RVSS},
    {"5-stage: no hazard detection, no forwarding", ProcessorType::RV5Stage_NH_NF},
    {"5-stage: hazard detection, no forwarding", ProcessorType::RV5Stage_H_NF},
    {"5-stage: no hazard detection, forwarding", ProcessorType::RV5Stage_NH_F},
    {"5-stage: hazard detection, forwarding", ProcessorType::RV5Stage_H_F},
};
} // namespace

ReorderTab::ReorderTab(QWidget *parent, EditorTab *editor, ProcessorManager *vmManager)
    : KitesTab(parent), m_editor(editor), m_vmManager(vmManager)
{
    m_processorBox = new QComboBox(this);
    for (const auto &p : kProcessors)
    {
        m_processorBox->addItem(p.label, static_cast<int>(p.type));
    }

    m_heuristicBox = new QComboBox(this);
    for (const std::string &name : reorder::heuristicNames())
    {
        m_heuristicBox->addItem(QString::fromStdString(name));
    }

    m_runButton = new QPushButton("Reorder", this);
    m_status = new QLabel(this);

    auto *controls = new QHBoxLayout;
    controls->addWidget(new QLabel("Processor:", this));
    controls->addWidget(m_processorBox);
    controls->addWidget(new QLabel("Heuristic:", this));
    controls->addWidget(m_heuristicBox);
    controls->addWidget(m_runButton);
    controls->addWidget(m_status, 1);

    m_summary = new QLabel(this);
    QFont summaryFont = m_summary->font();
    summaryFont.setBold(true);
    m_summary->setFont(summaryFont);

    const QFont mono = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    auto makeView = [&]()
    {
        auto *view = new QPlainTextEdit(this);
        view->setReadOnly(true); // still selectable / copyable with Ctrl+C
        view->setLineWrapMode(QPlainTextEdit::NoWrap);
        view->setFont(mono);
        return view;
    };
    m_originalView = makeView();
    m_reorderedView = makeView();
    m_originalStats = new QLabel(this);
    m_reorderedStats = new QLabel(this);

    m_copyAsmButton = new QPushButton("Copy assembly", this);
    m_copyHexButton = new QPushButton("Copy hex", this);
    m_copyAsmButton->setEnabled(false);
    m_copyHexButton->setEnabled(false);
    m_verifyLabel = new QLabel(this);
    m_verifyLabel->setWordWrap(true);

    auto makePane = [&](const QString &title, QLabel *stats, QPlainTextEdit *view,
                        QLayout *footer)
    {
        auto *pane = new QWidget(this);
        auto *layout = new QVBoxLayout(pane);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(new QLabel(title, pane));
        layout->addWidget(stats);
        layout->addWidget(view, 1);
        if (footer)
        {
            layout->addLayout(footer);
        }
        return pane;
    };

    auto *copyRow = new QHBoxLayout;
    copyRow->addWidget(m_copyAsmButton);
    copyRow->addWidget(m_copyHexButton);
    copyRow->addWidget(m_verifyLabel, 1);

    auto *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(makePane("Original code", m_originalStats, m_originalView, nullptr));
    splitter->addWidget(makePane("Reordered code", m_reorderedStats, m_reorderedView, copyRow));
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);

    auto *root = new QVBoxLayout(this);
    root->addLayout(controls);
    root->addWidget(m_summary);
    root->addWidget(splitter, 1);

    connect(m_runButton, &QPushButton::clicked, this, &ReorderTab::onReorderClicked);
    connect(m_copyAsmButton, &QPushButton::clicked, this, &ReorderTab::onCopyAssembly);
    connect(m_copyHexButton, &QPushButton::clicked, this, &ReorderTab::onCopyHex);
    connect(&m_simWatcher, &QFutureWatcher<SimPair>::finished, this,
            &ReorderTab::onSimulationFinished);
    syncProcessorFromManager();
}

ReorderTab::~ReorderTab()
{
    m_simWatcher.waitForFinished(); // the worker only uses copies, but don't outlive the tab
}

void ReorderTab::syncProcessorFromManager()
{
    if (!m_vmManager)
    {
        return;
    }
    const int idx = m_processorBox->findData(static_cast<int>(m_vmManager->getProcessorType()));
    if (idx >= 0)
    {
        m_processorBox->setCurrentIndex(idx);
    }
}

bool ReorderTab::assembleEditorText(AssembledProgram &program, QString &error)
{
    try
    {
        // Same steps MainWindow::tryParseAndLoadProgram() uses, minus loading into the VM.
        std::string text = m_editor->getRawText();
        text = customPseudoManager::expandPseudoInstruction(text);

        // Own scratch file: don't reuse temporary_assembly_file_path, the VM run path owns it.
        const std::filesystem::path scratch = globals::vm_state_directory / "reorder_input.s";
        {
            std::ofstream out(scratch);
            out << text;
        }
        program = assemble(scratch.string());
        return true;
    }
    catch (const std::exception &e)
    {
        error = QString::fromStdString(e.what());
        return false;
    }
}

QString ReorderTab::formatListing(const std::vector<uint32_t> &words,
                                  const std::vector<std::string> &lines)
{
    std::ostringstream out;
    for (size_t i = 0; i < words.size(); ++i)
    {
        out << std::hex << std::setfill('0') << std::setw(8) << (i * 4) << ": " << std::setw(8)
            << words[i] << std::dec << std::setfill(' ') << "   "
            << (i < lines.size() && !lines[i].empty() ? lines[i] : "(no text available)")
            << "\n";
    }
    return QString::fromStdString(out.str());
}

QString ReorderTab::statsText(const reorder_tab::SimResult &r)
{
    if (!r.error.empty())
    {
        return "Run error: " + QString::fromStdString(r.error);
    }
    const double cpi = r.retired ? static_cast<double>(r.cycles) / r.retired : 0.0;
    QString text = QString("Cycles: %1    Instructions retired: %2    CPI: %3")
                       .arg(r.cycles)
                       .arg(r.retired)
                       .arg(cpi, 0, 'f', 2);
    if (!r.note.empty())
    {
        text += "    (" + QString::fromStdString(r.note) + ")";
    }
    return text;
}

void ReorderTab::onReorderClicked()
{
    AssembledProgram program;
    QString error;
    if (!assembleEditorText(program, error))
    {
        m_status->setText("Assembly failed: " + error);
        return;
    }

    const std::vector<uint32_t> &original = program.text_buffer;
    m_originalView->setPlainText(
        formatListing(original, reorder_tab::buildListing(program, original).lines));
    m_reorderedView->clear();
    m_originalStats->clear();
    m_reorderedStats->clear();
    m_summary->clear();
    m_verifyLabel->clear();
    m_copyAsmButton->setEnabled(false);
    m_copyHexButton->setEnabled(false);

    const auto processor = static_cast<ProcessorType>(m_processorBox->currentData().toInt());
    std::vector<uint32_t> result;
    try
    {
        // Run the algorithm on the UI thread. Move it to a worker if it gets slow.
        result = reorder::reorderProgram(original, processor,
                                         static_cast<std::size_t>(m_heuristicBox->currentIndex()));
    }
    catch (const std::exception &e)
    {
        m_status->setText(QString("Reorder failed: ") + e.what());
        return;
    }
    if (result.size() != original.size())
    {
        m_status->setText("Reorder returned a different number of instructions.");
        return;
    }

    // Listing + copyable assembly (verified by assembling it again).
    m_lastWords = result;
    m_lastListing = reorder_tab::buildListing(program, result);
    m_reorderedView->setPlainText(formatListing(result, m_lastListing.lines));
    m_copyHexButton->setEnabled(true);

    std::string why;
    if (reorder_tab::verifyAssembly(m_lastListing.lines, result, why))
    {
        m_verifyLabel->setText("Done can copy assembly");
        m_copyAsmButton->setEnabled(true);
    }
    else
    {
        m_verifyLabel->setText(QString("Use Hex Assembly not verified")
                                   .arg(QString::fromStdString(why)));
        m_copyAsmButton->setEnabled(m_lastListing.complete); // still copyable, but unchecked
    }

    size_t moved = 0;
    for (size_t i = 0; i < original.size(); ++i)
    {
        moved += original[i] != result[i];
    }
    m_status->setText(
        QString("%1 instructions, %2 changed position").arg(original.size()).arg(moved));

    // Simulate both versions on private VMs in a worker thread (copies only).
    m_runButton->setEnabled(false);
    m_summary->setText("Simulating both programs...");
    AssembledProgram reordered = program;
    reordered.text_buffer = result;
    m_simWatcher.setFuture(QtConcurrent::run(
        [program, reordered, processor]() -> SimPair
        {
            return {reorder_tab::simulateProgram(program, processor),
                    reorder_tab::simulateProgram(reordered, processor)};
        }));
}

void ReorderTab::onSimulationFinished()
{
    const SimPair result = m_simWatcher.result();
    m_runButton->setEnabled(true);
    m_originalStats->setText(statsText(result.first));
    m_reorderedStats->setText(statsText(result.second));

    const auto &a = result.first;
    const auto &b = result.second;
    if (!a.error.empty() || !b.error.empty())
    {
        m_summary->setText("Could not compare cycles: a program raised a run error.");
        return;
    }
    if (!a.finished || !b.finished)
    {
        m_summary->setText("Cycle comparison may be incomplete: a program did not finish.");
        return;
    }
    const long long saved = static_cast<long long>(a.cycles) - static_cast<long long>(b.cycles);
    if (saved == 0)
    {
        m_summary->setText(QString("Same cycle count: %1").arg(a.cycles));
    }
    else
    {
        const double percent = a.cycles ? 100.0 * std::abs(saved) / a.cycles : 0.0;
        m_summary->setText(QString("Reordered program is %1 cycles %2 (%3%)")
                               .arg(std::abs(saved))
                               .arg(saved > 0 ? "faster" : "slower")
                               .arg(percent, 0, 'f', 1));
    }
}

void ReorderTab::onCopyAssembly()
{
    QGuiApplication::clipboard()->setText(
        QString::fromStdString(reorder_tab::joinLines(m_lastListing.lines)));
    m_status->setText(QString("Copied %1 lines of assembly").arg(m_lastListing.lines.size()));
}

void ReorderTab::onCopyHex()
{
    QGuiApplication::clipboard()->setText(
        QString::fromStdString(reorder_tab::joinHex(m_lastWords)));
    m_status->setText(QString("Copied %1 hex words").arg(m_lastWords.size()));
}
} // namespace Kites
