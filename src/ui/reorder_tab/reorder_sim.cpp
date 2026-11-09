#include "reorder_sim.h"

#include "processor/processor_manager.h"
#include "processor/registers.h"

#include <QObject>
#include <QString>

namespace Kites::reorder_tab
{
namespace
{
constexpr uint32_t kEcall = 0x00000073;
constexpr uint64_t kSyscallExit = 10;
constexpr uint64_t kSyscallRead = 63;
constexpr int kDrainCycles = 8; // idle cycles after the last fetch that mean "pipeline empty"
} // namespace

SimResult simulateProgram(const AssembledProgram &program, ProcessorType type, unsigned maxCycles)
{
    SimResult result;
    if (program.text_buffer.empty())
    {
        result.finished = true;
        return result;
    }

    ProcessorManager manager(nullptr, type);
    manager.setStepDelay(0);
    QObject::connect(&manager, &ProcessorManager::runErrorSignal, &manager,
                     [&](const QString &message, int)
                     {
                         if (result.error.empty())
                         {
                             result.error = message.toStdString();
                         }
                     });
    manager.loadProgram(program);

    const uint64_t endPc = static_cast<uint64_t>(program.text_buffer.size()) * 4;
    const bool singleCycle = type == ProcessorType::RVSS;

    unsigned lastRetired = 0;
    unsigned lastRetireCycle = 0;
    int idle = 0;

    for (unsigned i = 0; i < maxCycles; ++i)
    {
        const uint64_t pc = manager.getProgramCounter();

        if (singleCycle)
        {
            if (pc >= endPc)
            {
                result.finished = true;
                break;
            }
            // The RVSS exit ecall would call exit(0) on the whole application, and a read
            // ecall would wait for input forever, so stop right before either of them.
            if (program.text_buffer[pc / 4] == kEcall)
            {
                const uint64_t a7 = manager.getRegisterFile()->ReadGpr(17);
                if (a7 == kSyscallExit || a7 == kSyscallRead)
                {
                    result.finished = true;
                    result.note = a7 == kSyscallExit ? "stopped at exit ecall"
                                                      : "stopped at input ecall";
                    break;
                }
            }
        }

        manager.step();
        if (!result.error.empty())
        {
            break;
        }

        if (!singleCycle)
        {
            const unsigned retired = manager.getInstructionsRetired();
            if (retired != lastRetired)
            {
                lastRetired = retired;
                lastRetireCycle = manager.getCycles();
                idle = 0;
            }
            else if (manager.getProgramCounter() >= endPc && ++idle >= kDrainCycles)
            {
                result.finished = true;
                break;
            }
        }
    }

    result.retired = manager.getInstructionsRetired();
    result.stalls = manager.getStallCycles();
    result.cycles = singleCycle ? manager.getCycles() : lastRetireCycle;
    if (!result.finished && result.error.empty())
    {
        result.note = "did not finish within " + std::to_string(maxCycles) + " cycles";
    }
    return result;
}
} // namespace Kites::reorder_tab
