/**
 * @file repl.cpp
 * @brief Interactive REPL loop for kites-cli.
 */
#include "repl.h"

#include "common/globals.h"
#include "processor/registers.h"
#include "utils/utils.h"

#include <QObject>
#include <QString>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace Kites
{
namespace
{
void printRegisters(std::ostream &os, RegisterFile &registers)
{
    std::vector<uint64_t> gpr = registers.GetGprValues();
    os << "General-purpose registers:\n";
    for (size_t i = 0; i < gpr.size(); ++i)
    {
        os << "  x" << std::left << std::setw(3) << i << " = 0x" << std::hex << std::setw(16)
           << std::setfill('0') << gpr[i] << std::dec << std::setfill(' ') << "\n";
    }

    std::vector<uint64_t> fpr = registers.GetFprValues();
    os << "Floating-point registers:\n";
    for (size_t i = 0; i < fpr.size(); ++i)
    {
        os << "  f" << std::left << std::setw(3) << i << " = 0x" << std::hex << std::setw(16)
           << std::setfill('0') << fpr[i] << std::dec << std::setfill(' ') << "\n";
    }

    os << "Control and status registers:\n";
    for (const auto &[name, address] : csr_to_address)
    {
        os << "  " << std::left << std::setw(7) << name << " = 0x" << std::hex << std::setw(16)
           << std::setfill('0') << registers.ReadCsr(address) << std::dec << std::setfill(' ')
           << "\n";
    }
}

void printInfo(std::ostream &os, ProcessorManager &manager)
{
    os << "PC:                    0x" << std::hex << manager.getProgramCounter() << std::dec
       << "\n"
       << "Cycles:                " << manager.getCycles() << "\n"
       << "Instructions retired:  " << manager.getInstructionsRetired() << "\n"
       << "CPI:                   " << manager.getCPI() << "\n"
       << "IPC:                   " << manager.getIPC() << "\n"
       << "Stall cycles:          " << manager.getStallCycles() << "\n"
       << "Branch mispredictions: " << manager.getBranchMispredictions() << "\n";
}

void printBreakpoints(std::ostream &os, const command_handler::ReplState &state)
{
    if (state.breakpoints.empty())
    {
        os << "(no breakpoints set)\n";
        return;
    }
    os << "Breakpoints (source line numbers):\n";
    for (uint64_t line : state.breakpoints)
    {
        os << "  " << line << "\n";
    }
}

void printDisassembly(std::ostream &os, AssembledProgram &program)
{
    DumpDisasssembly(globals::disassembly_file_path, program);
    std::ifstream in(globals::disassembly_file_path);
    os << in.rdbuf();
}

void printHelp(std::ostream &os)
{
    os << "Commands:\n"
    << "  load <file> [--vm <name>]     assemble and load a program\n"
    << "                                 vm: rvss (default) | rv5-nh-nf | rv5-h-nf | "
    "rv5-nh-f | rv5-h-f\n"
    << "  run                           run to completion\n"
    << "  run_debug | rd                run until the next breakpoint\n"
    << "  step [n] | s [n]              execute n instructions (default 1)\n"
    << "  stop                          request the running program to stop\n"
    << "  undo | u                      step backward through executed instructions\n"
    << "  redo | r                      step forward through undone instructions\n"
    << "  reset                         reset the VM to its initial state\n"
    << "  add_breakpoint <line>         break at a source line number\n"
    << "  remove_breakpoint <line>      remove a breakpoint\n"
    << "  breakpoints                   list current breakpoints\n"
    << "  modify_register <reg> <val> | mreg\n"
    << "  print_mem <hex_addr> <rows> | pmem\n"
    << "  dump_mem <hex_addr> <rows> [<hex_addr> <rows>]... | dmem\n"
    << "  vm_stdin <text> | vmsin       feed input to a program blocked on a read syscall\n"
    << "  regs                          print all registers\n"
    << "  disas                         print disassembly of the loaded program\n"
    << "  info                          print PC/cycles/CPI/IPC/stats\n"
    << "  help                          show this message\n"
    << "  exit | quit | q               leave the REPL\n"
    << "\nCLI / batch-only features (not available with --repl / in REPL):\n"
    << "  --reorder <n[,n...]>          apply built-in reorder heuristic priority vector\n"
    << "                                 (comma-separated indices, e.g. 0,2,3; no spaces)\n"
    << "  --list-heuristics             print heuristic names and indices\n"
    << "  --compare-exe <path>          differential check vs. <path> <asm> <gen>\n"
    << "                                 (copies mismatches to --fail-dir; batch only)\n"
    << "  --compare-reorder <n[,n...]|all>\n"
    << "                                 in-process differential check of reorder heuristic(s)\n"
    << "                                 (repeatable; 'all' runs each heuristic alone; batch only)\n"
    << "  --fail-dir <dir>              directory for failing differential inputs (default: ./kites_failures)\n"
    << "  --timeout <sec>               timeout per generator/Kites run in seconds (default: 60)\n"
    << "  --max-cycles <n>              stop runaway batch runs after n cycles (default: 20000)\n"
    << "  --cycles-out <file>           write total cycles to <file> (pipelined VMs only)\n"
    << "  --cycles-original <file>      with --compare-*: append original program cycles\n"
    << "  --cycles-modified <file>      with --compare-*: append reordered/generated cycles\n"
    << "  --compare-csr                 also compare CSRs during differential runs\n";
}

std::string firstToken(const std::string &line)
{
    std::istringstream iss(line);
    std::string token;
    iss >> token;
    return token;
}
} // namespace

int runRepl(ProcessorManager &manager, command_handler::ReplState &state)
{
    QObject::connect(&manager, &ProcessorManager::runErrorSignal, &manager,
                      [](const QString &message, int sourceLine)
                      {
                          std::cerr << "run error: " << message.toStdString();
                          if (sourceLine > 0)
                          {
                              std::cerr << " (line " << sourceLine << ")";
                          }
                          std::cerr << std::endl;
                      });
    QObject::connect(&manager, &ProcessorManager::processorPausedAtBreakpointSignal, &manager,
                      [&manager]()
                      {
                          std::cout << "paused at breakpoint, PC=0x" << std::hex
                                    << manager.getProgramCounter() << std::dec << std::endl;
                      });

    std::cout << "Kites CLI REPL. Type 'help' for commands, 'exit' to quit.\n";

    std::string line;
    while (true)
    {
        std::cout << "kites> " << std::flush;
        if (!std::getline(std::cin, line))
        {
            std::cout << std::endl;
            break;
        }

        std::string first = firstToken(line);
        if (first.empty())
        {
            continue;
        }

        if (first == "help")
        {
            printHelp(std::cout);
            continue;
        }
        if (first == "regs")
        {
            printRegisters(std::cout, *manager.getRegisterFile());
            continue;
        }
        if (first == "info")
        {
            printInfo(std::cout, manager);
            continue;
        }
        if (first == "breakpoints")
        {
            printBreakpoints(std::cout, state);
            continue;
        }
        if (first == "disas")
        {
            if (!state.programLoaded)
            {
                std::cerr << "error: no program loaded\n";
                continue;
            }
            printDisassembly(std::cout, state.currentProgram);
            continue;
        }

        command_handler::Command command = command_handler::ParseCommand(line);
        if (command.type == command_handler::CommandType::INVALID)
        {
            std::cerr << "error: unknown command '" << first << "' (try 'help')\n";
            continue;
        }
        if (command.type == command_handler::CommandType::EXIT)
        {
            break;
        }

        try
        {
            command_handler::ExecuteCommand(command, manager, state);
        }
        catch (const std::exception &e)
        {
            std::cerr << "error: " << e.what() << std::endl;
        }
    }

    return 0;
}
} // namespace Kites
