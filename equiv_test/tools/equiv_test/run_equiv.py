#!/usr/bin/env python3
"""
Kites equivalence test runner.

For every input assembly/text file:

  1. run the ORIGINAL file through kites-cli          -> baseline state
  2. run YOUR C++ transform on it, producing a NEW file
  3. run the NEW file through kites-cli               -> candidate state
  4. compare baseline and candidate (exit code, syscall output, registers,
     CSRs, optional memory dumps) and report PASS / FAIL / ERROR

Everything is done through the terminal, with isolated working directories so
the `vm_state/` dumps written by kites-cli never collide. Standard library only.

Examples
--------
  # your transform is a compiled program invoked as:  prog <input> <output>
  python3 tools/equiv_test/run_equiv.py \\
      --kites build/kites-cli --transform ./my_transform examples/*.s

  # compile your .cpp first, test on all five VMs, dump 4 rows of memory @0x10000000
  python3 tools/equiv_test/run_equiv.py --kites build/kites-cli \\
      --transform-src my_transform.cpp --vm all \\
      --mem-dump 10000000 4 examples/

Exit status: 0 if every case passed, 1 if any case FAILED or ERRORED,
2 for bad invocation.
"""
from __future__ import annotations

import argparse
import json
import re
import shlex
import shutil
import subprocess
import sys
import time
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass, field
from pathlib import Path

ALL_VMS = ["rvss", "rv5-nh-nf", "rv5-h-nf", "rv5-nh-f", "rv5-h-f"]
INPUT_SUFFIXES = {".s", ".asm", ".txt"}
SUMMARY_MARKER = "Assembled '"  # first line of kites-cli's own summary block
MAX_DETAIL_LINES = 20

_ABI = (
    ["zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1"]
    + [f"a{i}" for i in range(8)]
    + [f"s{i}" for i in range(2, 12)]
    + [f"t{i}" for i in range(3, 7)]
)
REG_ALIASES = {name: f"x{i}" for i, name in enumerate(_ABI)}
REG_ALIASES["fp"] = "x8"
_FABI = (
    [f"ft{i}" for i in range(8)]
    + ["fs0", "fs1"]
    + [f"fa{i}" for i in range(8)]
    + [f"fs{i}" for i in range(2, 12)]
    + [f"ft{i}" for i in range(8, 12)]
)
REG_ALIASES.update({name: f"f{i}" for i, name in enumerate(_FABI)})


# --------------------------------------------------------------------------- #
# data
# --------------------------------------------------------------------------- #
@dataclass
class RunResult:
    cmd: list[str]
    returncode: int | None = None
    timed_out: bool = False
    spawn_error: str = ""
    stdout: str = ""
    stderr: str = ""
    program_output: list[str] = field(default_factory=list)
    registers: dict[str, str] = field(default_factory=dict)
    memory: dict[str, str] = field(default_factory=dict)
    errors: list = field(default_factory=list)
    run_error: str = ""
    seconds: float = 0.0

    @property
    def ok(self) -> bool:
        # 0 = ran fine, 2 = ran but the guest program raised a runtime error
        # (a legitimate, comparable outcome).
        return not self.timed_out and not self.spawn_error and self.returncode in (0, 2)

    def describe_failure(self) -> str:
        if self.spawn_error:
            return f"could not start: {self.spawn_error}"
        if self.timed_out:
            return "timed out"
        msg = f"exit code {self.returncode}"
        if self.errors:
            msg += f", assembler errors: {json.dumps(self.errors)[:300]}"
        elif self.stderr.strip():
            msg += f", stderr: {self.stderr.strip().splitlines()[-1][:300]}"
        return msg


@dataclass
class CaseResult:
    input: Path
    vm: str
    status: str  # PASS | FAIL | ERROR
    details: list[str] = field(default_factory=list)
    seconds: float = 0.0
    case_dir: Path | None = None


# --------------------------------------------------------------------------- #
# running things
# --------------------------------------------------------------------------- #
def _vm_state_dir(workdir: Path) -> Path:
    # kites-cli writes to <cwd>/vm_state, except on macOS where it uses
    # ~/Library/Application Support/Kites/vm_state (so we redirect HOME).
    if sys.platform == "darwin":
        return workdir / "Library" / "Application Support" / "Kites" / "vm_state"
    return workdir / "vm_state"


def _flatten(obj, out: dict[str, str]) -> None:
    for k, v in obj.items():
        if isinstance(v, dict):
            _flatten(v, out)
        else:
            out[str(k)] = str(v)


def _load_json(path: Path):
    try:
        return json.loads(path.read_text())
    except (OSError, ValueError):
        return None


def run_kites(kites: str, asm: Path, vm: str, mem_dumps: list[tuple[str, str]],
              workdir: Path, timeout: float) -> RunResult:
    workdir.mkdir(parents=True, exist_ok=True)
    state_dir = _vm_state_dir(workdir)
    if state_dir.exists():
        shutil.rmtree(state_dir)  # never read a stale dump from a previous run

    cmd = [kites, str(asm.resolve()), "--vm", vm]
    for addr, rows in mem_dumps:
        cmd += ["--mem-dump", addr, rows]
    res = RunResult(cmd=cmd)

    env = None
    if sys.platform == "darwin":
        import os
        env = {**os.environ, "HOME": str(workdir)}

    t0 = time.monotonic()
    try:
        p = subprocess.run(cmd, cwd=workdir, env=env, capture_output=True, text=True,
                           errors="replace", timeout=timeout)
        res.returncode, res.stdout, res.stderr = p.returncode, p.stdout, p.stderr
    except subprocess.TimeoutExpired as e:
        res.timed_out = True
        res.stdout = (e.stdout or b"").decode(errors="replace") if isinstance(e.stdout, bytes) else (e.stdout or "")
        res.stderr = (e.stderr or b"").decode(errors="replace") if isinstance(e.stderr, bytes) else (e.stderr or "")
    except OSError as e:
        res.spawn_error = str(e)
    res.seconds = time.monotonic() - t0

    (workdir / "stdout.txt").write_text(res.stdout)
    (workdir / "stderr.txt").write_text(res.stderr)

    # Program output = everything before kites-cli's own summary block.
    for line in res.stdout.splitlines():
        if line.startswith(SUMMARY_MARKER):
            break
        res.program_output.append(line)
    for line in res.stderr.splitlines():
        if line.startswith("Run failed:"):
            res.run_error = line

    regs = _load_json(state_dir / "registers_dump.json")
    if isinstance(regs, dict):
        _flatten(regs, res.registers)
    mem = _load_json(state_dir / "memory_dump.json")
    if isinstance(mem, dict):
        _flatten(mem, res.memory)
    errs = _load_json(state_dir / "errors_dump.json")
    if isinstance(errs, dict):
        res.errors = errs.get("errors", [])
    return res


def build_transform_cmd(template: list[str], inp: Path, out: Path) -> list[str]:
    if any("{in}" in t or "{out}" in t for t in template):
        return [t.replace("{in}", str(inp)).replace("{out}", str(out)) for t in template]
    return template + [str(inp), str(out)]


def run_transform(template: list[str], inp: Path, out: Path, cwd: Path,
                  timeout: float) -> str | None:
    """Run the user's program. Returns an error string, or None on success."""
    if out.exists():
        out.unlink()
    cmd = build_transform_cmd(template, inp.resolve(), out.resolve())
    try:
        p = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True,
                           errors="replace", timeout=timeout)
    except subprocess.TimeoutExpired:
        return f"transform timed out after {timeout:g}s: {shlex.join(cmd)}"
    except OSError as e:
        return f"could not start transform ({shlex.join(cmd)}): {e}"
    (cwd / "transform.stdout.txt").write_text(p.stdout)
    (cwd / "transform.stderr.txt").write_text(p.stderr)
    if p.returncode != 0:
        tail = (p.stderr.strip().splitlines() or p.stdout.strip().splitlines() or [""])[-1]
        return f"transform exited with code {p.returncode}: {tail[:300]}"
    if not out.exists():
        return f"transform exited 0 but did not create the output file {out.name}"
    if out.stat().st_size == 0:
        return "transform produced an empty output file"
    return None


# --------------------------------------------------------------------------- #
# comparing
# --------------------------------------------------------------------------- #
def _norm_val(v: str):
    try:
        return int(v, 16)
    except ValueError:
        return v


def resolve_ignored(names: list[str]) -> set[str]:
    return {REG_ALIASES.get(n.lower(), n.lower()) for n in names if n}


def _diff_maps(label: str, a: dict[str, str], b: dict[str, str], ignore: set[str]) -> list[str]:
    out = []
    for k in sorted(set(a) | set(b), key=_natural_key):
        if k.lower() in ignore:
            continue
        va, vb = a.get(k), b.get(k)
        if va is None or vb is None or _norm_val(va) != _norm_val(vb):
            out.append(f"{label} {k}: original={va} transformed={vb}")
    return out


def _natural_key(s: str):
    return [int(t) if t.isdigit() else t for t in re.split(r"(\d+)", s)]


def compare_runs(orig: RunResult, new: RunResult, args) -> list[str]:
    diffs: list[str] = []
    if orig.returncode != new.returncode:
        diffs.append(f"exit code: original={orig.returncode} transformed={new.returncode}")

    if orig.program_output != new.program_output:
        a, b = orig.program_output, new.program_output
        diffs.append(f"program (syscall) output differs: {len(a)} vs {len(b)} line(s)")
        for i in range(max(len(a), len(b))):
            la = a[i] if i < len(a) else "<missing>"
            lb = b[i] if i < len(b) else "<missing>"
            if la != lb:
                diffs.append(f"  line {i + 1}: original={la!r} transformed={lb!r}")

    ignore = resolve_ignored(args.ignore_reg)
    regs_a, regs_b = dict(orig.registers), dict(new.registers)
    if args.no_csr:
        csrs = {"fflags", "frm", "fcsr"}
        regs_a = {k: v for k, v in regs_a.items() if k not in csrs}
        regs_b = {k: v for k, v in regs_b.items() if k not in csrs}
    if not regs_a or not regs_b:
        diffs.append("registers_dump.json missing or unreadable for one of the runs")
    else:
        diffs += _diff_maps("register", regs_a, regs_b, ignore)

    if args.mem_dump:
        if not orig.memory or not new.memory:
            diffs.append("memory_dump.json missing for one of the runs")
        else:
            diffs += _diff_maps("memory", orig.memory, new.memory, set())
    return diffs


# --------------------------------------------------------------------------- #
# orchestration
# --------------------------------------------------------------------------- #
def run_input(idx: int, inp: Path, args, transform_cmd: list[str], out_root: Path) -> list[CaseResult]:
    case_dir = out_root / f"{idx:03d}_{inp.stem}"
    case_dir.mkdir(parents=True, exist_ok=True)
    original = case_dir / "original.s"
    transformed = case_dir / "transformed.s"
    shutil.copyfile(inp, original)

    t0 = time.monotonic()
    err = run_transform(transform_cmd, original, transformed, case_dir, args.timeout)
    if err:
        return [CaseResult(inp, vm, "FAIL", [err], time.monotonic() - t0, case_dir)
                for vm in args.vm_list]

    results = []
    mem_dumps = [(a, r) for a, r in args.mem_dump]
    for vm in args.vm_list:
        t1 = time.monotonic()
        base = run_kites(args.kites, original, vm, mem_dumps, case_dir / vm / "original", args.timeout)
        if not base.ok:
            results.append(CaseResult(
                inp, vm, "ERROR",
                [f"baseline (original file) did not run cleanly: {base.describe_failure()}"],
                time.monotonic() - t1, case_dir))
            continue
        cand = run_kites(args.kites, transformed, vm, mem_dumps, case_dir / vm / "transformed", args.timeout)
        if not cand.ok:
            results.append(CaseResult(
                inp, vm, "FAIL",
                [f"transformed file did not run cleanly: {cand.describe_failure()}"],
                time.monotonic() - t1, case_dir))
            continue
        diffs = compare_runs(base, cand, args)
        results.append(CaseResult(inp, vm, "FAIL" if diffs else "PASS", diffs,
                                  time.monotonic() - t1, case_dir))
    return results


def collect_inputs(paths: list[str], list_file: str | None) -> list[Path]:
    found: list[Path] = []
    raw = list(paths)
    if list_file:
        raw += [ln.strip() for ln in Path(list_file).read_text().splitlines()
                if ln.strip() and not ln.lstrip().startswith("#")]
    for p in map(Path, raw):
        if p.is_dir():
            found += sorted(f for f in p.rglob("*") if f.is_file() and f.suffix.lower() in INPUT_SUFFIXES)
        elif p.is_file():
            found.append(p)
        else:
            print(f"warning: input not found: {p}", file=sys.stderr)
    seen, unique = set(), []
    for f in found:
        r = f.resolve()
        if r not in seen:
            seen.add(r)
            unique.append(f)
    return unique


def compile_transform(src: Path, out_root: Path, cxx: str, cxxflags: str) -> list[str]:
    exe = out_root / ("transform_bin.exe" if sys.platform == "win32" else "transform_bin")
    cmd = [cxx, *shlex.split(cxxflags), str(src), "-o", str(exe)]
    print(f"compiling transform: {shlex.join(cmd)}")
    p = subprocess.run(cmd, capture_output=True, text=True)
    if p.returncode != 0:
        print(p.stderr, file=sys.stderr)
        sys.exit("error: failed to compile transform source")
    return [str(exe)]


def parse_args(argv=None):
    ap = argparse.ArgumentParser(
        description="Run a file through Kites, run your C++ transform on it, run the "
                    "transformed file through Kites, and compare the results.")
    ap.add_argument("inputs", nargs="*", help="input files and/or directories (searched for .s/.asm/.txt)")
    ap.add_argument("--list", help="text file with one input path per line ('#' comments allowed)")
    ap.add_argument("--kites", default="build/kites-cli", help="path to kites-cli (default: build/kites-cli)")

    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--transform", help="your program/command. Invoked as '<cmd> <in> <out>', or "
                                       "use {in} and {out} placeholders, e.g. \"python3 t.py {in} -o {out}\"")
    g.add_argument("--transform-src", help="your .cpp file; compiled with --cxx, then used as above")
    ap.add_argument("--cxx", default="g++")
    ap.add_argument("--cxxflags", default="-std=c++20 -O2")

    ap.add_argument("--vm", default="rvss",
                    help="comma-separated VMs, or 'all' (choices: " + ", ".join(ALL_VMS) + "). Default: rvss")
    ap.add_argument("--mem-dump", nargs=2, action="append", default=[], metavar=("HEX_ADDR", "ROWS"),
                    help="also compare memory: dump ROWS 8-byte rows from HEX_ADDR (repeatable)")
    ap.add_argument("--ignore-reg", default="", help="comma-separated registers excluded from comparison "
                    "(x5, t0, a0, f3, fa0, fflags ...). Use when your transform may clobber temporaries")
    ap.add_argument("--no-csr", action="store_true", help="don't compare fflags/frm/fcsr")
    ap.add_argument("--timeout", type=float, default=60, help="seconds per kites/transform run (default 60)")
    ap.add_argument("-j", "--jobs", type=int, default=1, help="inputs processed in parallel (default 1)")
    ap.add_argument("--out-dir", default="equiv_results", help="where transformed files and dumps are kept")
    ap.add_argument("--json-report", help="also write a machine-readable report to this path")
    ap.add_argument("-v", "--verbose", action="store_true", help="print details for passing cases too")
    args = ap.parse_args(argv)

    args.ignore_reg = [s for s in args.ignore_reg.split(",") if s.strip()]
    vms = ALL_VMS if args.vm == "all" else [v.strip() for v in args.vm.split(",") if v.strip()]
    bad = [v for v in vms if v not in ALL_VMS]
    if bad:
        ap.error(f"unknown VM(s): {', '.join(bad)}")
    args.vm_list = vms
    if not args.inputs and not args.list:
        ap.error("give at least one input file/directory (or --list FILE)")
    return args


def main(argv=None) -> int:
    args = parse_args(argv)

    kites = shutil.which(args.kites) or args.kites
    if not Path(kites).is_file():
        print(f"error: kites-cli not found at '{args.kites}'. Build it first "
              f"(see docs/CLI.md) or pass --kites PATH.", file=sys.stderr)
        return 2
    args.kites = kites

    inputs = collect_inputs(args.inputs, args.list)
    if not inputs:
        print("error: no input files found", file=sys.stderr)
        return 2

    out_root = Path(args.out_dir).resolve()
    out_root.mkdir(parents=True, exist_ok=True)

    if args.transform_src:
        transform_cmd = compile_transform(Path(args.transform_src), out_root, args.cxx, args.cxxflags)
    else:
        transform_cmd = shlex.split(args.transform)

    print(f"{len(inputs)} input file(s) x {len(args.vm_list)} VM(s): {', '.join(args.vm_list)}\n")

    with ThreadPoolExecutor(max_workers=max(1, args.jobs)) as pool:
        futures = [pool.submit(run_input, i, f, args, transform_cmd, out_root) for i, f in enumerate(inputs)]
        all_results: list[CaseResult] = [r for fut in futures for r in fut.result()]

    color = sys.stdout.isatty()
    paint = {"PASS": "32", "FAIL": "31", "ERROR": "33"}
    for r in all_results:
        tag = f"\033[{paint[r.status]}m{r.status}\033[0m" if color else r.status
        print(f"[{tag}] {str(r.input):<50} {r.vm:<10} ({r.seconds:.2f}s)")
        if r.details and (r.status != "PASS" or args.verbose):
            for line in r.details[:MAX_DETAIL_LINES]:
                print(f"         {line}")
            if len(r.details) > MAX_DETAIL_LINES:
                print(f"         ... {len(r.details) - MAX_DETAIL_LINES} more (see {r.case_dir})")

    counts = {s: sum(1 for r in all_results if r.status == s) for s in ("PASS", "FAIL", "ERROR")}
    print(f"\n{counts['PASS']} passed, {counts['FAIL']} failed, {counts['ERROR']} errored "
          f"({len(all_results)} total). Artifacts: {out_root}")

    if args.json_report:
        Path(args.json_report).write_text(json.dumps([
            {"input": str(r.input), "vm": r.vm, "status": r.status, "details": r.details,
             "seconds": round(r.seconds, 3), "artifacts": str(r.case_dir)} for r in all_results
        ], indent=2))

    return 0 if counts["FAIL"] == 0 and counts["ERROR"] == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
