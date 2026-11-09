#pragma once

#include "common/assembled_program.h"
#include "processor/processor_types.h"
#include "reorder_listing.h"
#include "reorder_sim.h"
#include "ui/common/kitestab.h"

#include <QFutureWatcher>
#include <QString>

#include <utility>
#include <vector>

class QComboBox;
class QLabel;
class QPlainTextEdit;
class QPushButton;

namespace Kites
{
class EditorTab;
class ProcessorManager;

/**
 * @brief Tab with the original program on the left and the reordered program on the right.
 *
 * Flow on "Reorder": editor text -> expand pseudo instructions -> assemble() -> reorder the
 * machine words -> list both versions -> simulate both on private VMs and show their cycles.
 * Nothing here touches the main VM, so the main program state is never disturbed.
 */
class ReorderTab : public KitesTab
{
    Q_OBJECT

  public:
    explicit ReorderTab(QWidget *parent, EditorTab *editor, ProcessorManager *vmManager);
    ~ReorderTab() override;

  public slots:
    /// Connect to MainWindow::processorChangedSignal so the dropdown follows the app's VM.
    void syncProcessorFromManager();

  private slots:
    void onReorderClicked();
    void onSimulationFinished();
    void onCopyAssembly();
    void onCopyHex();

  private:
    using SimPair = std::pair<reorder_tab::SimResult, reorder_tab::SimResult>;

    bool assembleEditorText(AssembledProgram &program, QString &error);
    static QString formatListing(const std::vector<uint32_t> &words,
                                 const std::vector<std::string> &lines);
    static QString statsText(const reorder_tab::SimResult &r);

    EditorTab *m_editor = nullptr;
    ProcessorManager *m_vmManager = nullptr;
    QComboBox *m_processorBox = nullptr;
    QComboBox *m_heuristicBox = nullptr;
    QPushButton *m_runButton = nullptr;
    QPushButton *m_copyAsmButton = nullptr;
    QPushButton *m_copyHexButton = nullptr;
    QLabel *m_status = nullptr;
    QLabel *m_summary = nullptr;
    QLabel *m_originalStats = nullptr;
    QLabel *m_reorderedStats = nullptr;
    QLabel *m_verifyLabel = nullptr;
    QPlainTextEdit *m_originalView = nullptr;
    QPlainTextEdit *m_reorderedView = nullptr;

    QFutureWatcher<SimPair> m_simWatcher;

    // result of the last successful reorder, used by the copy buttons
    std::vector<uint32_t> m_lastWords;
    reorder_tab::Listing m_lastListing;
};
} // namespace Kites
