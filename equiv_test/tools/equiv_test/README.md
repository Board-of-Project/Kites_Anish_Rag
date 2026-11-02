# Kites equivalence test module

Automates this loop from the terminal:

```
input.s ──► kites-cli ──► baseline state ─────────────┐
   │                                                  ├─► compare ─► PASS / FAIL
   └──► your C++ transform ──► transformed.s ──► kites-cli ──► candidate state ┘
```

Kept outside `test/` on purpose: `test/CMakeLists.txt` globs every `*.cpp` there into the GoogleTest binary.

## Requirements

- Python 3.8+ (standard library only)
- A built `kites-cli` (see [docs/CLI.md](../../docs/CLI.md))
- Your transform: any executable that is run as `<program> <input-file> <output-file>` and writes the new text file. A `.cpp` can be compiled for you with `--transform-src`.

## Usage

```bash
# compiled transform, a few files / directories (searched for .s .asm .txt)
python3 tools/equiv_test/run_equiv.py --kites build/kites-cli \
    --transform ./my_transform examples/pipeline_test_code_1.s examples/

# compile the .cpp first, run on all five VMs, also compare 4 rows of data memory
python3 tools/equiv_test/run_equiv.py --kites build/kites-cli \
    --transform-src my_transform.cpp --vm all --mem-dump 10000000 4 examples/

# custom argument order via placeholders; inputs from a list file; 4 in parallel
python3 tools/equiv_test/run_equiv.py --kites build/kites-cli \
    --transform "./my_transform --in {in} --out {out}" --list inputs.txt -j 4
```

Useful options: `--vm rvss,rv5-h-f | all`, `--mem-dump HEX_ADDR ROWS` (repeatable),
`--ignore-reg t0,x6,fa0` (temporaries your transform may legitimately change),
`--no-csr`, `--timeout SECS`, `--json-report FILE`, `-v`, `--out-dir DIR`.
Run with `-h` for the full list.

## What is compared (original vs transformed, same VM)

| Item | Source |
|---|---|
| exit code of `kites-cli` (0 ok, 2 runtime error, 1 assembly failure) | process |
| program output (`[Syscall output: ...]`, `Exited with exit code: ...`) | stdout |
| x0–x31, f0–f31, fflags/frm/fcsr | `vm_state/registers_dump.json` |
| memory rows (only with `--mem-dump`) | `vm_state/memory_dump.json` |

Disassembly is deliberately **not** compared (a transform is expected to change it).

## Results

- `PASS` – everything compared matched.
- `FAIL` – transform crashed / produced nothing, the transformed file doesn't assemble or run, or any compared item differs (differences are listed).
- `ERROR` – the *original* file doesn't run cleanly under Kites, so there is no baseline to judge against.

The process exits `0` only if every case passed (`1` on any FAIL/ERROR, `2` for bad invocation), so it drops straight into CI or a shell script.

For each input, `--out-dir` (default `./equiv_results`) keeps `original.s`, `transformed.s`, the transform's stdout/stderr, and per-VM `original/` and `transformed/` folders containing `vm_state/`, `stdout.txt` and `stderr.txt` for debugging a failure.

Notes: a guest program that blocks on a `READ` syscall hangs the CLI (documented limitation), so it is reported after `--timeout`. Each Kites run uses its own working directory, so runs never overwrite each other's `vm_state/`.

## Self-test (no Qt needed)

```bash
bash tools/equiv_test/selftest/selftest.sh
```

Uses `selftest/fake_kites_cli.py`, a tiny stand-in that mimics the CLI's documented output format, to check the harness itself: the good sample transform must pass and the `--inject-bug` variant must fail. It is not a RISC-V simulator; real results need the real `kites-cli`.
