#!/usr/bin/env python3
"""Score WorldBuilder -> game.dat name matches against the ledger gold set.

Each match record (one JSON object per line) is

    {"gd_va": int, "wb_va": int, "wb_name": str, "score": float,
     "evidence": [str, ...]}            # optional "wb_file"

and is judged against build/wb/gold.jsonl (tools/wb_gold.py) at gd_va:

    CORRECT  the address is rowed REAL and wb_name equals one of its REAL
             names, compared as normalized "Class::method"
    WRONG    the address is rowed REAL and no REAL name agrees
    NEW      the address is rowed PARTIAL or PLACEHOLDER, or not rowed at
             all -- the names this tool exists to find

Precision is CORRECT / (CORRECT + WRONG); recall is the share of rowed REAL
addresses that receive a CORRECT match.  NEW matches on PARTIAL rows are also
checked for class agreement, and NEW matches on pin-only addresses against
the symbols.csv pin, as two weaker, independent sanity signals.

Usage:
    python3 tools/wb_score.py [--matches build/wb/matches.jsonl]
    python3 tools/wb_score.py --synthesize build/wb/matches_synthetic.jsonl
"""
import argparse
import collections
import json
import random
import sys
from pathlib import Path

import wb_gold

DEFAULT_MATCHES = wb_gold.DEFAULT_OUT.parent / "matches.jsonl"
DEFAULT_BUCKETS = (0.5, 0.6, 0.7, 0.8, 0.9, 0.95)
OUTCOMES = ("CORRECT", "WRONG", "NEW")


def load_matches(path):
    with open(path, encoding="utf-8") as fh:
        return [json.loads(line) for line in fh if line.strip()]


def evidence_type(item):
    """'string:Foo::bar' -> 'string'; the type is the text before ':'."""
    return item.split(":", 1)[0].strip()


def target_kind(rec):
    if rec is None:
        return "UNROWED"
    return rec["kind"] if rec["rowed"] else "PIN_ONLY"


def method_of(norm):
    return norm.rsplit("::", 1)[-1]


def judge(match, gold):
    """Verdict for one match: outcome, target kind and sanity signals."""
    rec = gold.get(match["gd_va"])
    kind = target_kind(rec)
    norm = wb_gold.normalize(match["wb_name"])
    verdict = {"outcome": "NEW", "kind": kind, "norm": norm,
               "class_agree": None, "pin_agree": None, "method_agree": None}
    if kind == "REAL":
        verdict["outcome"] = "CORRECT" if norm in rec["norms"] else "WRONG"
        verdict["method_agree"] = method_of(norm) in map(method_of, rec["norms"])
    elif kind == "PARTIAL":
        wb_class = norm.split("::")[0] if "::" in norm else ""
        verdict["class_agree"] = wb_class == rec["class"]
    if rec is not None and rec["pin_norms"]:
        verdict["pin_agree"] = norm in rec["pin_norms"]
    return verdict


def tally(pairs):
    return collections.Counter(v["outcome"] for _, v in pairs)


def precision(counts):
    judged = counts["CORRECT"] + counts["WRONG"]
    return counts["CORRECT"] / judged if judged else float("nan")


def fmt_counts(counts):
    return (f"correct {counts['CORRECT']:>6}  wrong {counts['WRONG']:>6}  "
            f"new {counts['NEW']:>6}  precision {precision(counts):6.3f}")


def recall(pairs, real_total):
    """Share of gold REAL addresses holding at least one CORRECT match."""
    hit = {m["gd_va"] for m, v in pairs if v["outcome"] == "CORRECT"}
    return len(hit) / real_total if real_total else float("nan")


def bucket_label(score, edges):
    lo = max((e for e in edges if score >= e), default=None)
    hi = min((e for e in edges if score < e), default=None)
    return (f"[{lo:.2f}, {hi:.2f})" if lo is not None and hi is not None
            else f"< {hi:.2f}" if lo is None else f">= {lo:.2f}")


def report_buckets(pairs, edges, real_total):
    print("\n== by score bucket ==")
    groups = collections.defaultdict(list)
    for m, v in pairs:
        groups[bucket_label(m["score"], edges)].append((m, v))
    for label in sorted(groups, key=lambda k: min(m["score"] for m, _ in groups[k])):
        print(f"  {label:<14} {fmt_counts(tally(groups[label]))}")
    print("\n== cumulative (score >= threshold) ==")
    for edge in (float("-inf"),) + tuple(edges):
        kept = [(m, v) for m, v in pairs if m["score"] >= edge]
        label = "all" if edge == float("-inf") else f">= {edge:.2f}"
        print(f"  {label:<14} {fmt_counts(tally(kept))}"
              f"  recall {recall(kept, real_total):6.4f}")


def report_evidence(pairs):
    print("\n== by evidence type (a match counts under each type it cites) ==")
    groups = collections.defaultdict(list)
    for m, v in pairs:
        for etype in sorted({evidence_type(e) for e in m.get("evidence", [])}
                            or {"(none)"}):
            groups[etype].append((m, v))
    for etype in sorted(groups, key=lambda k: -len(groups[k])):
        print(f"  {etype:<20} {fmt_counts(tally(groups[etype]))}")


def report_disagreements(pairs, gold, top):
    wrong = sorted((p for p in pairs if p[1]["outcome"] == "WRONG"),
                   key=lambda p: -p[0]["score"])
    print(f"\n== top {min(top, len(wrong))} disagreements of {len(wrong)} ==")
    same_method = sum(1 for _, v in wrong if v["method_agree"])
    pin_agree = sum(1 for _, v in wrong if v["pin_agree"])
    print(f"  same method, other class (base/derived or ICF fold): {same_method}"
          f"  agreeing with a symbols.csv pin instead: {pin_agree}")
    for m, v in wrong[:top]:
        rec = gold[m["gd_va"]]
        print(f"  0x{m['gd_va']:08X} score {m['score']:.3f}  wb {m['wb_name']}"
              f"  ledger {' | '.join(rec['norms'])}"
              f"  [{', '.join(m.get('evidence', []))}]")


def report_new(pairs, top):
    new = [(m, v) for m, v in pairs if v["outcome"] == "NEW"]
    by_kind = collections.Counter(v["kind"] for _, v in new)
    print(f"\n== NEW names: {len(new)} ==")
    for kind, count in by_kind.most_common():
        print(f"  on {kind:<12} {count:>6}")
    partial = [v for _, v in new if v["kind"] == "PARTIAL"]
    if partial:
        agree = sum(1 for v in partial if v["class_agree"])
        print(f"  PARTIAL rows whose class agrees with WB: {agree}/{len(partial)}")
    pinned = [v for _, v in new if v["pin_agree"] is not None]
    if pinned:
        agree = sum(1 for v in pinned if v["pin_agree"])
        print(f"  pinned (symbols.csv REAL) addresses agreeing: "
              f"{agree}/{len(pinned)}")
    for m, v in sorted(new, key=lambda p: -p[0]["score"])[:top]:
        print(f"  0x{m['gd_va']:08X} score {m['score']:.3f}  {v['kind']:<11}"
              f"  {m['wb_name']}")


def report_collisions(matches):
    per_gd = collections.Counter(m["gd_va"] for m in matches)
    per_wb = collections.Counter(m["wb_va"] for m in matches)
    multi_gd = sum(1 for c in per_gd.values() if c > 1)
    multi_wb = sum(1 for c in per_wb.values() if c > 1)
    print(f"\nmatches {len(matches)}  game.dat addresses {len(per_gd)} "
          f"({multi_gd} with several matches)  WB functions {len(per_wb)} "
          f"({multi_wb} matched to several addresses)")


def score(matches, gold, edges, top):
    real_total = sum(1 for r in gold.values()
                     if r["rowed"] and r["kind"] == "REAL")
    # wb_match.py also pairs functions WB names nothing in (the lead is then
    # only a source file): there is no name to judge, so they are not scored.
    matches = [m for m in matches if m.get("wb_name")]
    pairs = [(m, judge(m, gold)) for m in matches]
    report_collisions(matches)
    print(f"gold REAL addresses: {real_total}")
    report_buckets(pairs, edges, real_total)
    report_evidence(pairs)
    report_disagreements(pairs, gold, top)
    report_new(pairs, top)
    return pairs


def synthesize(gold, n_correct, n_wrong, n_new, seed):
    """Matches with known outcomes, for testing this scorer end to end."""
    rng = random.Random(seed)
    real = sorted((r for r in gold.values()
                   if r["rowed"] and r["kind"] == "REAL" and r["norms"]),
                  key=lambda r: r["va"])
    def rowed(kind):
        return sorted((r for r in gold.values()
                       if r["rowed"] and r["kind"] == kind),
                      key=lambda r: r["va"])
    picked = rng.sample(real, n_correct + n_wrong)
    out = []
    for i, rec in enumerate(picked[:n_correct]):
        out.append({"gd_va": rec["va"], "wb_va": 0x1000000 + i,
                    "wb_name": rec["norms"][0],
                    "score": round(rng.uniform(0.6, 1.0), 3),
                    "evidence": rng.sample(["string:assert", "callgraph:3",
                                            "xref:vtable"], 2)})
    for i, rec in enumerate(picked[n_correct:]):
        decoy = next(r for r in rng.sample(real, 50)
                     if not set(r["norms"]) & set(rec["norms"]))
        out.append({"gd_va": rec["va"], "wb_va": 0x2000000 + i,
                    "wb_name": decoy["norms"][0],
                    "score": round(rng.uniform(0.3, 0.9), 3),
                    "evidence": ["callgraph:1"]})
    targets = (rng.sample(rowed("PARTIAL"), n_new // 2)
               + rng.sample(rowed("PLACEHOLDER"), n_new - n_new // 2))
    for i, rec in enumerate(targets):
        cls = rec["class"] if rec["kind"] == "PARTIAL" and i % 2 else "WBClass"
        out.append({"gd_va": rec["va"], "wb_va": 0x3000000 + i,
                    "wb_name": f"{cls}::wbMethod{i}",
                    "score": round(rng.uniform(0.5, 1.0), 3),
                    "evidence": ["string:assert"],
                    "wb_file": f"Code/Tools/WorldBuilder/src/WB{i}.cpp"})
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--matches", type=Path, default=DEFAULT_MATCHES)
    ap.add_argument("--gold", type=Path, default=wb_gold.DEFAULT_OUT)
    ap.add_argument("--buckets", default=",".join(map(str, DEFAULT_BUCKETS)),
                    help="comma-separated score bucket edges")
    ap.add_argument("--top", type=int, default=20)
    ap.add_argument("--synthesize", type=Path, metavar="OUT",
                    help="write a synthetic matches file (50 correct, "
                         "10 wrong, 20 new) to OUT and score it")
    ap.add_argument("--seed", type=int, default=0)
    args = ap.parse_args(argv)

    gold = wb_gold.load_gold(args.gold)
    edges = tuple(sorted(float(e) for e in args.buckets.split(",")))
    if args.synthesize:
        with open(args.synthesize, "w", encoding="utf-8") as fh:
            for m in synthesize(gold, 50, 10, 20, args.seed):
                fh.write(json.dumps(m) + "\n")
        print(f"wrote {args.synthesize}")
        args.matches = args.synthesize
    score(load_matches(args.matches), gold, edges, args.top)


if __name__ == "__main__":
    sys.exit(main())
