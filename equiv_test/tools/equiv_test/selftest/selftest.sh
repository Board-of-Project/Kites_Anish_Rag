#!/usr/bin/env bash
# Self-test for run_equiv.py using the stand-in kites-cli (no Qt needed).
#   1. correct transform must PASS
#   2. transform with an injected bug must be reported as FAIL (exit code 1)
set -u
HERE="$(cd "$(dirname "$0")" && pwd)"
TOOL="$HERE/.."
FAKE="$HERE/fake_kites_cli.py"
OUT="$(mktemp -d)"
trap 'rm -rf "$OUT"' EXIT
chmod +x "$FAKE"

echo "== expect PASS =="
python3 "$TOOL/run_equiv.py" --kites "$FAKE" --transform-src "$TOOL/sample/sample_transform.cpp" \
    --mem-dump 10000000 2 --out-dir "$OUT/good" "$TOOL/sample/inputs"
good=$?

echo; echo "== expect FAIL (injected bug) =="
python3 "$TOOL/run_equiv.py" --kites "$FAKE" --transform "$OUT/good/transform_bin {in} {out} --inject-bug" \
    --mem-dump 10000000 2 --out-dir "$OUT/bad" "$TOOL/sample/inputs"
bad=$?

echo
if [ $good -eq 0 ] && [ $bad -eq 1 ]; then echo "SELFTEST OK"; exit 0; fi
echo "SELFTEST FAILED (good=$good bad=$bad)"; exit 1
