#!/usr/bin/env python3
"""
STAND-IN for kites-cli, used ONLY to self-test the run_equiv.py harness on
machines where Qt / the real Kites build isn't available.

It mimics the documented CLI contract (docs/CLI.md): same arguments, same
vm_state/ dump files and JSON shape, same stdout markers and exit codes, but
interprets just a tiny RISC-V subset: li, mv, addi, add, sub, ecall (a7=1 print
int, a7=10 exit). It is NOT a RISC-V simulator.
"""
import json
import re
import sys
from pathlib import Path

ABI = (["zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1"]
       + [f"a{i}" for i in range(8)] + [f"s{i}" for i in range(2, 12)]
       + [f"t{i}" for i in range(3, 7)])
IDX = {n: i for i, n in enumerate(ABI)}
IDX.update({f"x{i}": i for i in range(32)})
IDX["fp"] = 8
MASK = (1 << 64) - 1


def main(argv):
    asm, mem_args = None, []
    i = 0
    while i < len(argv):
        a = argv[i]
        if a == "--vm":
            i += 1
        elif a == "--mem-dump":
            mem_args.append((argv[i + 1], int(argv[i + 2])))
            i += 2
        elif asm is None:
            asm = argv[i]
        i += 1
    if asm is None:
        print("usage: fake_kites_cli <file> [--vm x] [--mem-dump a n]", file=sys.stderr)
        return 1

    state = Path.cwd() / "vm_state"
    state.mkdir(exist_ok=True)
    regs = [0] * 32
    out_lines, exit_code = [], None

    def reg(n):
        if n not in IDX:
            raise ValueError(f"bad register '{n}'")
        return IDX[n]

    prog = []
    try:
        for n, raw in enumerate(Path(asm).read_text().splitlines(), 1):
            s = raw.split("#")[0].strip()
            if not s:
                continue
            op, _, rest = s.partition(" ")
            args = [x.strip() for x in rest.split(",")] if rest else []
            if op not in {"li", "mv", "addi", "add", "sub", "ecall"}:
                raise ValueError(f"line {n}: unknown instruction '{op}'")
            prog.append((op, args))
    except ValueError as e:
        print(f"Assembly failed: {e}", file=sys.stderr)
        (state / "errors_dump.json").write_text(json.dumps({"errorCode": 1, "errors": [str(e)]}))
        return 1

    (state / "errors_dump.json").write_text('{"errorCode": 0, "errors": []}')
    (state / "disassembly.txt").write_text("\n".join(f"{op} {', '.join(a)}" for op, a in prog))

    for op, a in prog:
        if exit_code is not None:
            break
        if op == "li":
            regs[reg(a[0])] = int(a[1], 0) & MASK
        elif op == "mv":
            regs[reg(a[0])] = regs[reg(a[1])]
        elif op == "addi":
            regs[reg(a[0])] = (regs[reg(a[1])] + int(a[2], 0)) & MASK
        elif op == "add":
            regs[reg(a[0])] = (regs[reg(a[1])] + regs[reg(a[2])]) & MASK
        elif op == "sub":
            regs[reg(a[0])] = (regs[reg(a[1])] - regs[reg(a[2])]) & MASK
        elif op == "ecall":
            if regs[17] == 1:
                v = regs[10]
                v = v - (1 << 64) if v >> 63 else v
                print(f"[Syscall output: {v}]")
            elif regs[17] == 10:
                exit_code = regs[10]
                print(f"Exited with exit code: {exit_code}")
        regs[0] = 0

    h = lambda v: f"0x{v:016x}"
    dump = {
        "control and status registers": {"fflags": h(0), "frm": h(0), "fcsr": h(0)},
        "gp_registers": {f"x{i}": h(regs[i]) for i in range(32)},
        "fp_registers": {f"f{i}": h(0) for i in range(32)},
    }
    (state / "registers_dump.json").write_text(json.dumps(dump, indent=4))

    if mem_args:
        mem = {}
        for addr, rows in mem_args:
            base = int(addr, 16)
            for r in range(rows):
                mem[f"0x{base + 8 * r:016x}"] = h(0)
        (state / "memory_dump.json").write_text(json.dumps(mem, indent=4))

    print(f"Assembled '{asm}': {len(prog)} instruction word(s), 0 data item(s).\nRun completed.")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
