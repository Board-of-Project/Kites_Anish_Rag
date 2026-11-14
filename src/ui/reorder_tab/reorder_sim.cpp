#include "reorder_sim.h"

#include "processor/processor_base.h"
#include "processor/processor_factory.h"
#include "processor/processor_manager.h"

#include <exception>
#include <memory>

namespace Kites::reorder_tab
{
namespace
{
constexpr uint32_t kEcall = 0x00000073;
constexpr uint64_t kSyscallRead = 63;
} // namespace

SimResult simulateProgram(const AssembledProgram &program, ProcessorType type, unsigned maxCycles)
{
    SimResult result;
    if (program.text_buffer.empty())
    {
        result.finished = true;
        return result;
    }

    // Constructing a ProcessorManager registers every VM type with the factory (idempotent).
    ProcessorManager registry(nullptr, type);
    std::unique_ptr<ProcessorBase> processor = ProcessorFactory::createVM(type);
    processor->LoadProgram(program);
    processor->SetBreakpoints({}); // drop the automatic end-of-program breakpoint

    const bool singleCycle = type == ProcessorType::RVSS;
    bool moreWork = true;
    unsigned steps = 0;

    try
    {
        while (moreWork && steps < maxCycles)
        {
            if (singleCycle)
            {
                // A read ecall would wait for input that never comes: stop right before it.
                const uint64_t pc = processor->program_counter_;
                if (pc / 4 < program.text_buffer.size() && program.text_buffer[pc / 4] == kEcall &&
                    processor->registers_.ReadGpr(17) == kSyscallRead)
                {
                    result.note = "stopped at input ecall";
                    moreWork = false;
                    break;
                }
            }
            moreWork = processor->StepAndNotify();
            ++steps;
            if (processor->IsStopRequested()) // e.g. the exit syscall
            {
                moreWork = false;
            }
        }
    }
    catch (const std::exception &e)
    {
        result.error = e.what();
    }

    result.finished = !moreWork && result.error.empty();
    result.cycles = processor->cycle_s_;
    result.retired = processor->instructions_retired_;
    if (!result.finished && result.error.empty())
    {
        result.note = "did not finish within " + std::to_string(maxCycles) + " cycles";
    }
    return result;
}
} // namespace Kites::reorder_tab
