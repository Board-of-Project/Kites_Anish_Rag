#!/usr/bin/env python3
"""
Heuristic experiments for the Kites instruction reordering.

Experiment 1  (--experiment 1)
    Heuristics 0,1,4,5,6,7 (2 and 3 excluded). For code lengths 20,30,...,100 (loads, no
    branches; generator: rand_gen3.cpp) run N programs (default 70) and report the average
    cycles of the original and of the reordered program for every heuristic.
    Outputs: exp1_length.csv, exp1_cycles.png (avg reordered cycles vs length, original dashed),
             exp1_saved.png (% cycles saved vs length).

Experiment 2  (--experiment 2)
    Generator with adjustable instruction mix (rand_gen5.cpp), code length 200.
      2a: branch % swept (default 0..40 step 5) with load % fixed       -> exp2_branch.png / .csv
      2b: load % swept   (default 0..50 step 5) with branch % fixed     -> exp2_load.png / .csv

Every program is generated once and then run through
    kites-cli <prog> --vm <vm> --compare-reorder <h> [--compare-reorder <h> ...]
    --cycles-original <file> --cycles-modified <file> ...
with all heuristics in one call (one comparison per heuristic = one line per cycle file).
If a call fails (mismatch / reorder crash / timeout) the program is re-run once per heuristic
so only the broken heuristic loses that sample. Failed samples are excluded from the averages
and counted in the CSV (kites-cli itself stores the failing programs in <outdir>/failures).

Examples
    python3 kites_experiments.py --experiment all
    python3 kites_experiments.py --experiment 1 --runs 70 --kites ./build/kites-cli --vm rv5-h-f
    python3 kites_experiments.py --experiment 2 --fixed-load 25 --fixed-branch 10
"""
import argparse
import csv
import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

DEFAULT_HEURISTICS = [0, 1, 4, 5, 6, 7]


# ----------------------------------------------------------------------------------------------
# generators
# ----------------------------------------------------------------------------------------------
def build_generator(src):
    """Compile a generator .cpp with g++ into an executable in the CURRENT folder (next to the
    sources, not in the results subfolder) and return its absolute path. It is only rebuilt when
    the executable is missing or older than the source."""
    src = Path(src)
    if not src.is_file():
        sys.exit(f"generator source not found: {src} (run this script from the folder holding the .cpp files)")
    exe = Path.cwd() / src.stem
    if not exe.exists() or exe.stat().st_mtime < src.stat().st_mtime:
        print(f"compiling {src} -> {exe.name}")
        r = subprocess.run(["g++", "-O2", "-std=c++17", str(src), "-o", str(exe)],
                           capture_output=True, text=True)
        if r.returncode != 0:
            sys.exit(f"{src} did not compile:\n{r.stderr}")
    return str(exe.resolve())


# ----------------------------------------------------------------------------------------------
# running kites-cli
# ----------------------------------------------------------------------------------------------
def read_cycles(path):
    try:
        return [int(line.split()[0]) for line in Path(path).read_text().splitlines() if line.strip()]
    except (OSError, ValueError):
        return []


def run_kites(cfg, prog, heuristics, tag):
    """Returns (exit code, original cycles list, reordered cycles list)."""
    orig = cfg.work / f"{tag}_orig.txt"
    new = cfg.work / f"{tag}_new.txt"
    for f in (orig, new):
        f.unlink(missing_ok=True)
    cmd = [cfg.kites, str(prog), "--vm", cfg.vm]
    for h in heuristics:
        cmd += ["--compare-reorder", str(h)]
    cmd += ["--fail-dir", str(cfg.faildir), "--timeout", str(cfg.timeout),
            "--cycles-original", str(orig), "--cycles-modified", str(new)]
    try:
        p = subprocess.run(cmd, capture_output=True,
                           timeout=cfg.timeout * len(heuristics) + 10)
        rc = p.returncode
    except subprocess.TimeoutExpired:
        rc = 124
    return rc, read_cycles(orig), read_cycles(new)


def measure_program(cfg, gen_cmd, tag):
    """Generate one program and measure every heuristic on it, exactly like doing it by hand:
    run the generator, then run kites-cli from the current folder (it keeps its dump files in its
    own vm_state directory, so runs are strictly one after another).
    Returns {heuristic: (orig_cycles, new_cycles) or None if that sample failed}."""
    prog = cfg.work / f"{tag}.s"
    prog.unlink(missing_ok=True)
    g = subprocess.run(gen_cmd(str(prog)), capture_output=True)
    if g.returncode != 0 or not prog.exists() or prog.stat().st_size == 0:
        return {h: None for h in cfg.heuristics}

    hs = cfg.heuristics
    rc, o, n = run_kites(cfg, prog, hs, tag)
    if rc == 0 and len(o) == len(n) == len(hs):
        res = {h: (o[i], n[i]) for i, h in enumerate(hs)}
    else:  # something failed: isolate the culprit by running each heuristic separately
        res = {}
        for h in hs:
            rc, o, n = run_kites(cfg, prog, [h], f"{tag}_h{h}")
            res[h] = (o[0], n[0]) if rc == 0 and len(o) == len(n) == 1 else None
    prog.unlink(missing_ok=True)
    return res


def evaluate_point(cfg, make_gen_cmd, runs, label):
    """Run `runs` programs for one experiment point. make_gen_cmd(seed) -> (out_path -> argv list).
    Returns {heuristic: dict(orig, new, saved, n, fail)}."""
    samples = []
    for i in range(runs):  # one program at a time
        seed = cfg.seed + i
        samples.append(measure_program(cfg, make_gen_cmd(seed), f"{label}_{seed}"))

    out = {}
    for h in cfg.heuristics:
        ok = [s[h] for s in samples if s[h] is not None]
        n = len(ok)
        if n:
            o = sum(a for a, _ in ok) / n
            r = sum(b for _, b in ok) / n
            out[h] = dict(orig=o, new=r, saved=(100.0 * (o - r) / o) if o else 0.0, n=n, fail=runs - n)
        else:
            out[h] = dict(orig=float("nan"), new=float("nan"), saved=float("nan"), n=0, fail=runs)
    return out


# ----------------------------------------------------------------------------------------------
# output: csv + plots
# ----------------------------------------------------------------------------------------------
def write_csv(path, xname, rows):
    with open(path, "w", newline="") as f:
        w = csv.writer(f)
        w.writerow([xname, "heuristic", "avg_original", "avg_reordered", "percent_saved", "valid_runs", "failed_runs"])
        for x, h, d in rows:
            w.writerow([x, h, f"{d['orig']:.2f}", f"{d['new']:.2f}", f"{d['saved']:.3f}", d["n"], d["fail"]])
    print(f"wrote {path}")


def plot_lines(rows, xname, xlabel, title, path, ylabel, key, baseline=False):
    try:
        import matplotlib
        matplotlib.use("Agg")
        import matplotlib.pyplot as plt
    except ImportError:
        print("matplotlib not installed: skipping plot (CSV is still written). pip install matplotlib")
        return
    xs = sorted({x for x, _, _ in rows})
    hs = sorted({h for _, h, _ in rows})
    fig, ax = plt.subplots(figsize=(8, 5))
    for h in hs:
        d = {x: dd for x, hh, dd in rows if hh == h}
        ax.plot(xs, [d[x][key] for x in xs], marker="o", label=f"heuristic {h}")
    if baseline:
        base = []
        for x in xs:
            vals = [dd["orig"] for xx, _, dd in rows if xx == x and dd["n"]]
            base.append(sum(vals) / len(vals) if vals else float("nan"))
        ax.plot(xs, base, "k--", marker="s", label="original (no reorder)")
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    ax.set_title(title)
    ax.grid(True, alpha=0.3)
    ax.legend()
    fig.tight_layout()
    fig.savefig(path, dpi=150)
    plt.close(fig)
    print(f"wrote {path}")


def print_table(rows, xname):
    print(f"\n{xname:>10} {'heur':>5} {'orig':>10} {'reordered':>10} {'saved %':>8} {'n':>4} {'fail':>5}")
    for x, h, d in rows:
        print(f"{x:>10} {h:>5} {d['orig']:>10.1f} {d['new']:>10.1f} {d['saved']:>8.2f} {d['n']:>4} {d['fail']:>5}")


# ----------------------------------------------------------------------------------------------
# experiments
# ----------------------------------------------------------------------------------------------
def experiment1(cfg):
    gen = build_generator(cfg.gen3)
    rows = []
    for length in cfg.lengths:
        print(f"[exp1] length {length}: {cfg.runs} programs x {len(cfg.heuristics)} heuristics ...", flush=True)
        res = evaluate_point(cfg, lambda seed, L=length: (lambda out: [gen, out, str(seed), str(L)]),
                             cfg.runs, f"e1_L{length}")
        rows += [(length, h, res[h]) for h in cfg.heuristics]
    write_csv(cfg.outdir / "exp1_length.csv", "length", rows)
    print_table(rows, "length")
    plot_lines(rows, "length", "code length (instructions)",
               f"Exp 1: average cycles vs code length ({cfg.runs} runs/point, {cfg.vm})",
               cfg.outdir / "exp1_cycles.png", "average cycles", "new", baseline=True)
    plot_lines(rows, "length", "code length (instructions)",
               "Exp 1: cycles saved by reordering vs code length",
               cfg.outdir / "exp1_saved.png", "cycles saved (%)", "saved")


def experiment2(cfg):
    gen = build_generator(cfg.gen5)
    L = cfg.length2

    # 2a: branch % sweep
    rows = []
    for b in cfg.branch_values:
        if b + cfg.fixed_load > 100:
            print(f"[exp2a] skipping branch={b}% (branch+load > 100)")
            continue
        print(f"[exp2a] branch {b}% (load {cfg.fixed_load}%): {cfg.runs} programs ...", flush=True)
        res = evaluate_point(cfg, lambda seed, b=b: (lambda out: [gen, out, str(seed), str(L), str(b),
                                                                  str(cfg.fixed_load), str(cfg.fixed_store)]),
                             cfg.runs, f"e2a_B{b}")
        rows += [(b, h, res[h]) for h in cfg.heuristics]
    write_csv(cfg.outdir / "exp2_branch.csv", "branch_pct", rows)
    print_table(rows, "branch %")
    plot_lines(rows, "branch_pct", "branch instructions (% of code)",
               f"Exp 2a: avg cycles vs branch % (length {L}, load {cfg.fixed_load}%)",
               cfg.outdir / "exp2_branch.png", "average cycles", "new", baseline=True)
    plot_lines(rows, "branch_pct", "branch instructions (% of code)",
               "Exp 2a: cycles saved vs branch %",
               cfg.outdir / "exp2_branch_saved.png", "cycles saved (%)", "saved")

    # 2b: load % sweep
    rows = []
    for ld in cfg.load_values:
        if ld + cfg.fixed_branch > 100:
            print(f"[exp2b] skipping load={ld}% (branch+load > 100)")
            continue
        print(f"[exp2b] load {ld}% (branch {cfg.fixed_branch}%): {cfg.runs} programs ...", flush=True)
        res = evaluate_point(cfg, lambda seed, ld=ld: (lambda out: [gen, out, str(seed), str(L),
                                                                    str(cfg.fixed_branch), str(ld),
                                                                    str(cfg.fixed_store)]),
                             cfg.runs, f"e2b_L{ld}")
        rows += [(ld, h, res[h]) for h in cfg.heuristics]
    write_csv(cfg.outdir / "exp2_load.csv", "load_pct", rows)
    print_table(rows, "load %")
    plot_lines(rows, "load_pct", "load instructions (% of code)",
               f"Exp 2b: avg cycles vs load % (length {L}, branch {cfg.fixed_branch}%)",
               cfg.outdir / "exp2_load.png", "average cycles", "new", baseline=True)
    plot_lines(rows, "load_pct", "load instructions (% of code)",
               "Exp 2b: cycles saved vs load %",
               cfg.outdir / "exp2_load_saved.png", "cycles saved (%)", "saved")


# ----------------------------------------------------------------------------------------------
def int_list(s):
    return [int(x) for x in s.split(",") if x.strip() != ""]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--experiment", choices=["1", "2", "all"], default="all")
    ap.add_argument("--kites", default="./build/kites-cli", help="kites-cli executable")
    ap.add_argument("--vm", default="rv5-h-f", help="rv5-nh-nf | rv5-h-nf | rv5-nh-f | rv5-h-f")
    ap.add_argument("--runs", type=int, default=70, help="programs per data point (default 70)")
    ap.add_argument("--heuristics", type=int_list, default=DEFAULT_HEURISTICS,
                    help="comma list, default 0,1,4,5,6,7 (0-7 without 2 and 3)")
    ap.add_argument("--lengths", type=int_list, default=list(range(20, 101, 10)), help="exp 1 code lengths")
    ap.add_argument("--length2", type=int, default=200, help="exp 2 code length (default 200)")
    ap.add_argument("--branch-values", type=int_list, default=list(range(0, 41, 5)), help="exp 2a branch %% values")
    ap.add_argument("--load-values", type=int_list, default=list(range(0, 51, 5)), help="exp 2b load %% values")
    ap.add_argument("--fixed-load", type=int, default=25, help="load %% during the branch sweep")
    ap.add_argument("--fixed-branch", type=int, default=10, help="branch %% during the load sweep")
    ap.add_argument("--fixed-store", type=int, default=12, help="store %% in experiment 2")
    ap.add_argument("--gen3", default="rand_gen4.cpp", help="loads/no-branch generator source (exp 1)")
    ap.add_argument("--gen5", default="rand_gen5.cpp", help="adjustable-mix generator source (exp 2)")
    ap.add_argument("--outdir", default="./experiment_results", help="subfolder for CSVs, plots and failing programs only")
    ap.add_argument("--seed", type=int, default=1000, help="first seed (program i uses seed+i)")
    ap.add_argument("--timeout", type=int, default=30, help="seconds per kites-cli comparison")
    cfg = ap.parse_args()

    cfg.kites = str(Path(cfg.kites).resolve())
    if not (os.access(cfg.kites, os.X_OK) and Path(cfg.kites).is_file()):
        sys.exit(f"kites-cli not found or not executable: {cfg.kites} (use --kites)")
    if cfg.vm == "rvss":
        sys.exit("cycle comparison needs a pipelined VM (rv5-*), not rvss")
    if cfg.runs < 1:
        sys.exit("--runs must be >= 1")

    cfg.outdir = Path(cfg.outdir)
    cfg.outdir.mkdir(parents=True, exist_ok=True)
    cfg.faildir = cfg.outdir / "failures"
    cfg.faildir.mkdir(exist_ok=True)
    cfg.work = Path(tempfile.mkdtemp(prefix="kites_exp_"))  # scratch files live in the system temp dir
    print(f"vm={cfg.vm} heuristics={cfg.heuristics} runs/point={cfg.runs}")

    try:
        if cfg.experiment in ("1", "all"):
            experiment1(cfg)
        if cfg.experiment in ("2", "all"):
            experiment2(cfg)
    finally:
        shutil.rmtree(cfg.work, ignore_errors=True)


if __name__ == "__main__":
    main()