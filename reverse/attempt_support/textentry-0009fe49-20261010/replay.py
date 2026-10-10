#!/usr/bin/env python3
"""Materialize and optionally compile the recorded text-entry experiments."""
import argparse
import hashlib
import json
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import build
import permute


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("trials", nargs="*", type=int,
                        help="trial numbers (default: baseline and final bank)")
    parser.add_argument("--all", action="store_true")
    parser.add_argument("--materialize-only", action="store_true")
    args = parser.parse_args()
    evidence = json.loads((HERE / "trials.json").read_text())
    baseline = evidence["baseline_source"]
    assert hashlib.sha256(baseline.encode()).hexdigest() == evidence["baseline_sha256"]
    selected = args.trials or [0, evidence["best_trial"]]
    records = evidence["trials"] if args.all else [evidence["trials"][i] for i in selected]
    output = ROOT / "build" / "textentry-replay"
    output.mkdir(parents=True, exist_ok=True)
    symbols = None if args.materialize_only else build.load_symbol_map()
    target = build.read_target_bytes(int(evidence["rva"], 16), evidence["size"])
    assert hashlib.sha256(target).hexdigest() == evidence["retail_sha256"]
    disagreements = 0
    for record in records:
        lines = baseline.splitlines(keepends=True)
        for edit in reversed(record["edits"]):
            lines[edit["start"]:edit["end"]] = edit["text"].splitlines(keepends=True)
        text = "".join(lines)
        assert hashlib.sha256(text.encode()).hexdigest() == record["sha256"]
        source = output / record["source"]
        source.write_text(text)
        if args.materialize_only:
            continue
        obj = source.with_suffix(".obj")
        ok, message, _ = build.try_compile_source(source, obj)
        if not ok:
            print(json.dumps({"trial": record["trial"], "compile_error": message}))
            disagreements += "error" not in record
            continue
        raw, _ = build.read_object_symbol_bytes(obj, evidence["symbol"], evidence["size"], code_only=True)
        row = dict(name=evidence["symbol"], target_rva=evidence["rva"],
                   target_size=str(max(evidence["size"], len(raw))),
                   source=source.relative_to(ROOT).as_posix(), notes="")
        patch = build.compile_function(row, symbols, obj)
        compiled = bytes(patch["bytes"])
        score = permute.fitness(compiled, target)
        exact = compiled == target and len(raw) == evidence["size"] and not patch["unresolved"]
        same = (len(raw) == record.get("size") and
                abs(score - record.get("score", -1)) < 1e-12 and
                patch["unresolved"] == record.get("unresolved") and exact == record["exact"])
        print(json.dumps(dict(trial=record["trial"], size=len(raw), score=score,
                              exact=exact, unresolved=patch["unresolved"], agrees=same)))
        disagreements += not same
    print(f"{len(records)} snapshots verified; {disagreements} replay disagreements")
    return 1 if disagreements else 0


if __name__ == "__main__":
    raise SystemExit(main())
