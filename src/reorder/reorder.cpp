#include "reorder.h"

#include "reordering.h" 
#include "utils.h"
#include "processor/processor_types.h"
#include <stdexcept>
#include <string>

namespace Kites
{

    Reorder::Proc toProc(ProcessorType processor)
{
    switch (processor)
    {
    case ProcessorType::RV5Stage_NH_NF:
        return Reorder::Proc::NoHazardNoFwd;
    case ProcessorType::RV5Stage_H_NF:
        return Reorder::Proc::HazardNoFwd;
    case ProcessorType::RV5Stage_NH_F:
        return Reorder::Proc::NoHazardFwd;
    case ProcessorType::RV5Stage_H_F:
        return Reorder::Proc::HazardFwd;
    case ProcessorType::RVSS:
    default:
        return Reorder::Proc::SingleCycle;
    }
}

const std::vector<std::string> & reorder::heuristicNames()
{
    // Built from the table in reordering.cpp, so the dropdown can never get out of sync.
    static const std::vector<std::string> names = []
    {
        std::vector<std::string> v;
        for (size_t i = 0; i < Reorder::heuristicCount(); ++i)
        {
            v.emplace_back(Reorder::heuristicName(i));
        }
        return v;
    }();
    return names;
}

std::vector<uint32_t> reorder::reorderProgram(const std::vector<uint32_t> &words, ProcessorType processor,
                                     std::size_t heuristicIndex)
{
    if (heuristicIndex >Reorder::heuristicCount())
    {
        throw std::invalid_argument("unknown heuristic index");
    }
    return Reorder::reorderer(words, toProc(processor), heuristicIndex);
}
} // namespace Kites::reorder