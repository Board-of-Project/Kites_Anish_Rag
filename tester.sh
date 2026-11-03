#!/usr/bin/env bash
#
# Differential fuzzing loop for Kites + your reordering tool.
# Run it from the repo root, exactly where you run the commands by hand.
#
# Each iteration runs these commands AS WRITTEN (same cwd, no cd, no env changes, no extra flags):
#   1. ./rand_gen /tmp/comp_arch/tests/code1.s <seed> <len>     (random program; see GEN_CMD)
#   2. ./build/kites-cli /tmp/comp_arch/tests/code1.s           (run 1)
#   3. ./Reodering_Temp/main                                    (no arguments; writes code2.s itself)
#   4. ./build/kites-cli /tmp/comp_arch/tests/code2.s           (run 2)
#   5. compare run 1 and run 2 (program output + all registers)
#
# If ANY step errors out or the two runs differ, code1.s is saved into the fail folder
# (together with code2.s and a .log explaining why).
#
# Usage:   ./tester.sh [iterations]            (default 1000)
# Example: ITER_LEN=200 ./tester.sh 500
#
# Settings (environment variables, all optional):
#   KITES       kites-cli command                    default ./build/kites-cli
#   GEN         random generator binary              default ./rand_gen
#               (built from rand_gen.cpp next to this script if missing)
#   GEN_CMD     full generator command line, if yours is called differently. Run through bash;
#               the variables $SEED_I (this iteration's seed), $CODE1 and $ITER_LEN are available.
#               e.g.  GEN_CMD='./my_gen'     or     GEN_CMD='./my_gen $CODE1'
#   REORDER     your reordering program, run with no arguments    default ./Reodering_Temp/main
#   CODE1/CODE2 generated / reordered file           default /tmp/comp_arch/tests/code1.s, code2.s
#   FAIL_DIR    where failing programs are stored    default /tmp/comp_arch/fail
#   WORK_DIR    scratch copies of each run's output  default /tmp/comp_arch/work
#   CYCLES1/2   files kites-cli writes its cycle count to (--OUTFILECYCLES), run 1 / run 2
#               default /tmp/comp_arch/cycles1.txt, /tmp/comp_arch/cycles2.txt
#               (emptied once at script start, then appended to by every run)
#   VM          only if set, adds "--vm $VM" to both Kites runs     default: not passed
#   ITER_LEN    instructions per random program      default: generator picks a random 10..15
#   SEED        base seed; iteration i uses SEED+i   default random
#   TIMEOUT     seconds per Kites/reorder run, 0 = no timeout        default 0
#   STOP_ON_FAIL=1   stop at the first failure
#
# Exit status: 0 if every iteration passed, 1 if any failed, 2 for setup problems.

set -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ITERATIONS="${1:-530}"
KITES="${KITES:-./build/kites-cli}"
GEN="${GEN:-./rand_gen}"
COMB="${COMB:-./data_collector}"
GEN_CMD="${GEN_CMD:-}"
COMB_CMD="${COMB_CMD:-}"
REORDER="${REORDER:-./Reodering_Temp/main}"
CODE1="${CODE1:-/tmp/comp_arch/tests/code1.s}"
CODE2="${CODE2:-/tmp/comp_arch/tests/code2.s}"
FAIL_DIR="${FAIL_DIR:-/tmp/comp_arch/fail}"
WORK_DIR="${WORK_DIR:-/tmp/comp_arch/work}"
CYCLES1="${CYCLES1:-/tmp/comp_arch/cycles1.txt}"
CYCLES2="${CYCLES2:-/tmp/comp_arch/cycles2.txt}"
VM="${VM:-rv5-h-nf}"
ITER_LEN="${ITER_LEN:-20}"
TIMEOUT="${TIMEOUT:-0}"
STOP_ON_FAIL="${STOP_ON_FAIL:-0}"
SEED="${SEED:-$(( (RANDOM << 15 | RANDOM) ))}"

if ! [[ "$ITERATIONS" =~ ^[0-9]+$ ]] || [ "$ITERATIONS" -lt 1 ]; then
    echo "usage: $0 [iterations]" >&2; exit 2
fi

# Optional timeout wrapper (only used when TIMEOUT > 0).
TIMEOUT_CMD=""
if [ "$TIMEOUT" -gt 0 ]; then
    if command -v timeout >/dev/null 2>&1; then TIMEOUT_CMD="timeout $TIMEOUT"
    elif command -v gtimeout >/dev/null 2>&1; then TIMEOUT_CMD="gtimeout $TIMEOUT"
    else echo "warning: TIMEOUT set but no timeout/gtimeout command found; ignoring" >&2; fi
fi

# Kites writes its dumps to <cwd>/vm_state (macOS: ~/Library/Application Support/Kites/vm_state).
if [ "$(uname)" = "Darwin" ]; then
    VM_STATE_DIR="$HOME/Library/Application Support/Kites/vm_state"
else
    VM_STATE_DIR="$PWD/vm_state"
fi

# Build the generator on demand.
if [ -z "$GEN_CMD" ] && [ ! -x "$GEN" ] && [ -f "$SCRIPT_DIR/rand_gen.cpp" ]; then
    echo "building generator from $SCRIPT_DIR/rand_gen.cpp -> $GEN"
    g++ -std=c++20 -O2 "$SCRIPT_DIR/rand_gen.cpp" -o "$GEN" || { echo "generator build failed" >&2; exit 2; }
fi
tools=("$KITES" "$REORDER")
[ -z "$GEN_CMD" ] && tools+=("$GEN")
for tool in "${tools[@]}"; do
    if [ ! -x "$tool" ]; then echo "error: '$tool' not found or not executable (run from the repo root)" >&2; exit 2; fi
done

mkdir -p "$(dirname "$CODE1")" "$(dirname "$CODE2")" "$FAIL_DIR" "$WORK_DIR" "$(dirname "$CYCLES1")" "$(dirname "$CYCLES2")" || exit 2
RUN1="$WORK_DIR/run1"; RUN2="$WORK_DIR/run2"

# run_kites <asm> <save_dir> <cycles_file>
# Runs exactly:  <KITES> <asm> --OUTFILECYCLES <cycles_file> [--vm $VM]    from the current directory, then copies the
# results it left behind into <save_dir> so the next run can't overwrite them.
run_kites() {
    local asm="$1" dir="$2" cyc="$3"
    local cmd=("$KITES" "$asm" --OUTFILECYCLES "$cyc")
    [ -n "$VM" ] && cmd+=(--vm "$VM")
    rm -rf "$dir"; mkdir -p "$dir"
    rm -f "$VM_STATE_DIR/registers_dump.json" "$VM_STATE_DIR/memory_dump.json"   # no stale dumps
    $TIMEOUT_CMD "${cmd[@]}" >"$dir/stdout" 2>"$dir/stderr"
    echo $? > "$dir/rc"
    # Program output = everything before Kites' own "Assembled '<path>'..." summary block
    # (that block contains the file path, which legitimately differs between code1 and code2).
    sed '/^Assembled /,$d' "$dir/stdout" > "$dir/output.txt"
    cp "$VM_STATE_DIR/registers_dump.json" "$dir/regs.json" 2>/dev/null || : > "$dir/regs.json"
}

: > "$CYCLES1"; : > "$CYCLES2"   # start empty once; kites-cli appends one line per run
pass=0; fail=0
echo "base seed $SEED | $ITERATIONS iteration(s) | ${ITER_LEN:-random 10-15} instr | vm=${VM:-default}"
echo "code1: $CODE1   code2: $CODE2   failures: $FAIL_DIR"
echo

for ((i = 0; i < ITERATIONS; i++)); do
    SEED_I=$((SEED + i))
    reason=""; detail=""
    rm -f "$CODE1" "$CODE2"

    # 1. generator
    if [ -n "$GEN_CMD" ]; then
        export SEED_I CODE1 ITER_LEN
        bash -c "$GEN_CMD"
    else
        "$GEN" "$CODE1" "$SEED_I" ${ITER_LEN:+"$ITER_LEN"}
    fi
    grc=$?
    if [ $grc -ne 0 ]; then
        reason="generator_error"; detail="generator exited with code $grc"
    elif [ ! -s "$CODE1" ]; then
        reason="generator_no_output"; detail="generator did not write $CODE1"
    fi

    # 2. kites on code1
    if [ -z "$reason" ]; then
        run_kites "$CODE1" "$RUN1" "$CYCLES1"
        rc1=$(cat "$RUN1/rc")
        if [ "$rc1" -ne 0 ]; then
            reason="kites_error_on_code1"
            detail="kites-cli exit code $rc1 (124 = timeout; 1 = assembly failed; 2 = runtime error)
$(tail -n 5 "$RUN1/stderr")"
        fi
    fi

    # 3. reordering tool (no arguments, writes code2.s itself)
    if [ -z "$reason" ]; then
        $TIMEOUT_CMD "$REORDER" >"$WORK_DIR/reorder.stdout" 2>"$WORK_DIR/reorder.stderr"
        rrc=$?
        if [ $rrc -ne 0 ]; then
            reason="reorder_tool_error"
            detail="$REORDER exited with code $rrc (124 = timeout)
$(tail -n 5 "$WORK_DIR/reorder.stderr")"
        elif [ ! -s "$CODE2" ]; then
            reason="reorder_no_output"; detail="reordering tool did not write $CODE2"
        fi
    fi

    # 4. kites on code2
    if [ -z "$reason" ]; then
        run_kites "$CODE2" "$RUN2" "$CYCLES2"
        rc2=$(cat "$RUN2/rc")
        if [ "$rc2" -ne 0 ]; then
            reason="kites_error_on_code2"
            detail="kites-cli exit code $rc2 (124 = timeout; 1 = assembly failed; 2 = runtime error)
$(tail -n 5 "$RUN2/stderr")"
        fi
    fi

    # 5. compare
    if [ -z "$reason" ]; then
        d_out="$(diff "$RUN1/output.txt" "$RUN2/output.txt")"
        d_reg="$(diff "$RUN1/regs.json" "$RUN2/regs.json")"
        if [ ! -s "$RUN1/regs.json" ] || [ ! -s "$RUN2/regs.json" ]; then
            reason="missing_register_dump"; detail="registers_dump.json missing for one of the runs ($VM_STATE_DIR)"
        elif [ -n "$d_out" ] || [ -n "$d_reg" ]; then
            reason="output_mismatch"
            detail="--- program output diff (code1 vs code2) ---
${d_out:-<identical>}
--- register diff (code1 vs code2) ---
${d_reg:-<identical>}"
        fi
    fi

    if [ -z "$reason" ]; then
        pass=$((pass + 1))
        printf '[PASS] #%d seed=%d\n' "$i" "$SEED_I"
    else
        fail=$((fail + 1))
        base="$FAIL_DIR/test_number_${i}_${reason}"
        cp "$CODE1" "$base.s" 2>/dev/null
        [ -s "$CODE2" ] && cp "$CODE2" "$base.code2.s"
        {
            echo "reason: $reason"
            echo "seed:   $SEED_I   (regenerate: $GEN out.s $SEED_I ${ITER_LEN:-})"
            echo "vm:     ${VM:-default}"
            echo "$detail"
        } > "$base.log"
        printf '[FAIL] #%d seed=%d  %s  -> %s\n' "$i" "$SEED_I" "$reason" "$base.s"
        [ "$STOP_ON_FAIL" = "1" ] && break
    fi
done

echo
echo "done: $pass passed, $fail failed (failing programs in $FAIL_DIR)"
if [ -z "$COMB_CMD" ] && [ ! -x "$COMB" ] && [ -f "$SCRIPT_DIR/data_collector.cpp" ]; then
    echo "building generator from $SCRIPT_DIR/data_collector.cpp -> $COMB"
    g++ -std=c++20 -O2 "$SCRIPT_DIR/data_collector.cpp" -o "$COMB" || { echo "\combiner build failed" >&2; exit 2; }
fi
"$COMB"
echo "data stored in /tmp/comp_arch/data.csv"

[ "$fail" -eq 0 ]
