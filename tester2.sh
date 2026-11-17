#!/usr/bin/env bash
# Random differential testing of the instruction reordering on a pipelined Kites VM.
#
# For each iteration:
#   1. call your random program generator to create a test program,
#   2. run `kites-cli <program> --compare-reorder <heuristic>`, which runs the original and the
#      reordered program, compares registers/memory, and appends both programs' total cycles
#      to two text files (one line per comparison, line N of each file belongs together),
#   3. failing programs are copied into <outdir>/failures by kites-cli.
#
# Usage:
#   ./run_random_tests.sh -n 100 -b rand_gen.cpp            # compile rand_gen.cpp and use it
#   ./run_random_tests.sh -n 100 -g "./rand_gen {out} {seed}"
#   ./run_random_tests.sh -n 100 -g "./rand_gen {out} {seed}" -l 60   # fixed program length
#
# The generator command is a template: {out} is replaced by the file to create, {seed} by a
# number that changes every iteration and {len} by the -l value. With -l and no {len} in the
# template, the length is appended as a last argument (rand_gen <out> <seed> <length>).
# The generator must exit 0 and write the program to {out}.

set -u

ITERATIONS=""
GENERATOR="./rand_gen {out} {seed}"
GEN_SOURCE=""
LENGTH=""
KITES="./build/kites-cli"
VM="rv5-h-f"
HEURISTIC="0"        # a heuristic index, or "all"
OUTDIR="./random_test_results"
SEED=100
TIMEOUT=30
KEEP_ALL=0

usage() {
    cat <<USAGE
Usage: $0 -n <iterations> [options]
  -n <num>     number of random programs to test (required)
  -g <cmd>     generator command template with {out} and {seed}   (default: "$GENERATOR")
  -b <file>    generator source (.cpp): compile it with g++ and use it as the generator
  -l <num>     program length (instructions) passed to the generator (default: its own)
  -k <path>    kites-cli executable                               (default: $KITES)
  -vm <vm>      rv5-nh-nf | rv5-h-nf | rv5-nh-f | rv5-h-f          (default: $VM)
  -H <n|all>   heuristic index to test, or "all"                  (default: $HEURISTIC)
  -o <dir>     output directory                                   (default: $OUTDIR)
  -s <seed>    first seed, incremented each iteration             (default: $SEED)
  -t <sec>     time limit for the generator and each Kites run    (default: $TIMEOUT)
  -K           keep every generated program (default: keep only failing ones)
USAGE
    exit 1
}

while getopts "n:g:b:l:k:v:H:o:s:t:Kh" opt; do
    case "$opt" in
        n) ITERATIONS="$OPTARG" ;;
        g) GENERATOR="$OPTARG" ;;
        b) GEN_SOURCE="$OPTARG" ;;
        l) LENGTH="$OPTARG" ;;
        k) KITES="$OPTARG" ;;
        v) VM="$OPTARG" ;;
        H) HEURISTIC="$OPTARG" ;;
        o) OUTDIR="$OPTARG" ;;
        s) SEED="$OPTARG" ;;
        t) TIMEOUT="$OPTARG" ;;
        K) KEEP_ALL=1 ;;
        *) usage ;;
    esac
done

[[ "$ITERATIONS" =~ ^[0-9]+$ ]] && (( ITERATIONS > 0 )) || { echo "Error: -n must be a positive number."; usage; }
[[ "$SEED" =~ ^[0-9]+$ ]] || { echo "Error: -s must be a number."; usage; }
[[ -x "$KITES" ]] || { echo "Error: kites-cli not found or not executable: $KITES (use -k)"; exit 1; }
if [[ "$VM" == "rvss" ]]; then
    echo "Error: cycle comparison needs a pipelined VM (rv5-*), not rvss."; exit 1
fi

[[ -z "$LENGTH" || "$LENGTH" =~ ^[0-9]+$ ]] || { echo "Error: -l must be a number."; usage; }

mkdir -p "$OUTDIR"
if [[ -n "$GEN_SOURCE" ]]; then
    [[ -f "$GEN_SOURCE" ]] || { echo "Error: generator source not found: $GEN_SOURCE"; exit 1; }
    echo "Compiling generator: $GEN_SOURCE"
    g++ -O2 -std=c++17 "$GEN_SOURCE" -o "$OUTDIR/rand_gen" || { echo "Error: generator did not compile."; exit 1; }
    GENERATOR="$(printf '%q' "$OUTDIR/rand_gen") {out} {seed}"
fi

TESTS="$OUTDIR/tests"
FAILS="$OUTDIR/failures"
CYC_ORIG="$OUTDIR/cycles_original.txt"
CYC_NEW="$OUTDIR/cycles_reordered.txt"
mkdir -p "$TESTS" "$FAILS"
: > "$CYC_ORIG"      # start fresh: the CLI appends one line per comparison
: > "$CYC_NEW"

pass=0; mismatch=0; genfail=0; badinput=0; other=0

for (( i = 0; i < ITERATIONS; i++ )); do
    seed=$(( SEED + i ))
    prog="$TESTS/test_${seed}.s"
    rm -f "$prog"

    # 1. generate
    cmd="${GENERATOR//\{out\}/$(printf '%q' "$prog")}"
    cmd="${cmd//\{seed\}/$seed}"
    if [[ -n "$LENGTH" ]]; then
        if [[ "$GENERATOR" == *"{len}"* ]]; then cmd="${cmd//\{len\}/$LENGTH}"; else cmd="$cmd $LENGTH"; fi
    fi
    if ! timeout "$TIMEOUT" bash -c "$cmd" >/dev/null 2>&1 || [[ ! -s "$prog" ]]; then
        printf '[%d/%d] seed=%d  GENERATOR FAILED\n' $((i + 1)) "$ITERATIONS" "$seed"
        genfail=$((genfail + 1))
        continue
    fi

    # 2. compare original vs reordered
    "$KITES" "$prog" --vm "$VM" --compare-reorder "$HEURISTIC" \
        --fail-dir "$FAILS" --timeout "$TIMEOUT" \
        --cycles-original "$CYC_ORIG" --cycles-modified "$CYC_NEW" \
        >"$OUTDIR/last_stdout.txt" 2>"$OUTDIR/last_stderr.txt"
    rc=$?

    case "$rc" in
        0) status="PASS";                    pass=$((pass + 1)) ;;
        4) status="MISMATCH";                mismatch=$((mismatch + 1)) ;;
        5) status="REORDER FAILED/CRASHED";  mismatch=$((mismatch + 1)) ;;
        1) status="BAD INPUT (did not assemble or finish)"; badinput=$((badinput + 1)) ;;
        *) status="UNEXPECTED EXIT $rc";     other=$((other + 1)) ;;
    esac
    printf '[%d/%d] seed=%d  %s  %s\n' $((i + 1)) "$ITERATIONS" "$seed" "$status" \
        "$(grep -hE '^(MATCH|MISMATCH)' "$OUTDIR/last_stdout.txt" "$OUTDIR/last_stderr.txt" | head -1 | grep -o '\[cycles[^]]*\]')"

    # keep only failing programs unless -K was given
    if (( rc == 0 && KEEP_ALL == 0 )); then
        rm -f "$prog"
    fi
done

# 3. summary
echo
echo "================ summary ================"
echo "iterations      : $ITERATIONS (vm: $VM, heuristic: $HEURISTIC, first seed: $SEED)"
echo "passed          : $pass"
echo "mismatch/crash  : $mismatch   (inputs saved in $FAILS)"
echo "generator fails : $genfail"
echo "bad input       : $badinput"
(( other > 0 )) && echo "unexpected      : $other"

lines=$(wc -l < "$CYC_ORIG")
if (( lines > 0 )); then
    paste -d' ' "$CYC_ORIG" "$CYC_NEW" | awk '
        { o += $1; r += $2; n++ ; if ($2 < $1) better++; else if ($2 > $1) worse++; else same++ }
        END {
            printf "cycles compared : %d programs\n", n
            printf "total original  : %d\n", o
            printf "total reordered : %d\n", r
            if (o > 0) printf "difference      : %d cycles (%.2f%% %s)\n", o - r, (o - r) * 100.0 / o, (o >= r ? "fewer" : "more")
            printf "per program     : %d faster, %d slower, %d unchanged\n", better, worse, same
        }'
    paste -d, "$CYC_ORIG" "$CYC_NEW" | awk -F, 'BEGIN{print "comparison,original,reordered,saved"} {print NR","$1","$2","$1-$2}' > "$OUTDIR/cycles_compare.csv"
    echo "cycle logs      : $CYC_ORIG , $CYC_NEW , $OUTDIR/cycles_compare.csv"
else
    echo "no cycle data was recorded"
fi

(( mismatch + genfail + badinput + other > 0 )) && exit 1
exit 0
