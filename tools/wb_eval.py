#!/usr/bin/env python3
"""Exact-pair precision and recall of a WorldBuilder match file on held-out gold.

tools/wb_score.py judges the *names* a matcher emits; this tool judges the
*pairs*, which is what a matcher change actually moves. A held-out truth pair
is a game.dat address the ledger rows with a REAL name (build/wb/gold.jsonl)
whose normalized name equals the unique assertion name of exactly one WB
function. Only the addresses wb_match.py did not seed from are scored:
`wb_match.py --holdout P` seeds from gold addresses whose hash parity is not
P, and `--parity P` here scores the rest. Running both parities and adding
the counts doubles the sample.

For each held-out pair the match file either pairs gd_va with the true WB
function (correct), with another one (wrong), or not at all (unmatched).
A match elsewhere that claims a held-out pair's WB function is counted per
evidence kind as a collateral error, since it is wrong too. Separately, the
WB name each match emits is judged at every held-out REAL address, which
also covers names the unique-name truth cannot prove (overloads, say).

    wb_eval.py --matches build/wb/v2/matches.jsonl [--parity 1]
"""
import argparse
import collections
import json
import sys

import wb_gold
import wb_match


def real_gold(gold_path, gd_vas):
    """{gd_va: set of normalized names} for ledger-rowed REAL gold addresses in game.dat."""
    real = {}
    with open(gold_path) as fh:
        for rec in map(json.loads, fh):
            if rec.get("kind") == "REAL" and rec.get("rowed") and rec["va"] in gd_vas:
                real[rec["va"]] = set(rec.get("norms") or ())
    return real


def truth_pairs(wb, real):
    """{gd_va: wb_va} for every gold REAL address provable by a unique WB name.

    A WB function proves a pair only when it carries exactly one assertion
    name that no other WB function carries; this is fixed here rather than
    borrowed from the matcher, so matcher naming changes cannot move truth.
    A WB function claimed by several gold addresses (overloads sharing one
    normalized name, retail copies of one inline) proves none of them.
    """
    counts = wb_match.name_counts(wb)
    by_norm = collections.defaultdict(list)
    for va, rec in wb.items():
        unique = [n for n in rec.get("names") or () if counts[n] == 1]
        if len(unique) == 1:
            by_norm[wb_gold.normalize(unique[0])].append(va)
    truth = {}
    for g, norms in real.items():
        hits = {w for norm in norms for w in by_norm.get(norm, ())}
        if len(hits) == 1:
            truth[g] = hits.pop()
    claims = collections.Counter(truth.values())
    return {g: w for g, w in truth.items() if claims[w] == 1}


def evaluate(matches, held):
    """(totals Counter, {evidence: Counter}) for matches judged against held."""
    totals = collections.Counter()
    by_evidence = collections.defaultdict(collections.Counter)
    for g, w in held.items():
        m = matches.get(g)
        verdict = "unmatched" if m is None else "correct" if m["wb_va"] == w else "wrong"
        totals[verdict] += 1
        for kind in (m or {}).get("evidence", ()):
            by_evidence[kind][verdict] += 1
    owner = {w: g for g, w in held.items()}
    for g, m in matches.items():
        if g not in held and m["wb_va"] in owner:
            totals["collateral"] += 1
            for kind in m["evidence"]:
                by_evidence[kind]["wrong"] += 1
    return totals, by_evidence


def judge_names(matches, real):
    """Counter of correct/wrong emitted names at the given gold REAL addresses."""
    verdicts = collections.Counter()
    for g, norms in real.items():
        name = (matches.get(g) or {}).get("wb_name")
        if name:
            verdicts["correct" if wb_gold.normalize(name) in norms else "wrong"] += 1
    return verdicts


def ratio(num, den):
    return num / den if den else 0.0


def report(totals, by_evidence, n_held, matches, names):
    named = sum(1 for m in matches.values() if m.get("wb_name"))
    c, w = totals["correct"], totals["wrong"]
    print(f"matches {len(matches)}, named {named}")
    print(f"names at held-out REAL addresses: correct {names['correct']}, wrong {names['wrong']}  "
          f"precision {ratio(names['correct'], names['correct'] + names['wrong']):.3f}")
    print(f"held-out provable pairs {n_held}: correct {c}, wrong {w}, "
          f"unmatched {totals['unmatched']}, collateral {totals['collateral']}  "
          f"precision {ratio(c, c + w):.3f} recall {ratio(c, n_held):.3f}")
    for kind, cnt in sorted(by_evidence.items()):
        print(f"  {kind:10} correct {cnt['correct']:4} wrong {cnt['wrong']:4} "
              f"precision {ratio(cnt['correct'], cnt['correct'] + cnt['wrong']):.3f}")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--matches", required=True)
    ap.add_argument("--wb", default="build/wb/wb_functions.jsonl")
    ap.add_argument("--gd", default="build/wb/gd_functions.jsonl")
    ap.add_argument("--gold", default="build/wb/gold.jsonl")
    ap.add_argument("--parity", type=int, choices=(0, 1), default=1,
                    help="hash parity held out by the matcher run (its --holdout value)")
    args = ap.parse_args(argv)
    wb = wb_match.load(args.wb)
    with open(args.gd) as fh:
        gd_vas = {json.loads(line)["va"] for line in fh}
    real = real_gold(args.gold, gd_vas)
    held = {g: w for g, w in truth_pairs(wb, real).items() if wb_match.holdout_parity(g) == args.parity}
    real = {g: n for g, n in real.items() if wb_match.holdout_parity(g) == args.parity}
    with open(args.matches) as fh:
        matches = {r["gd_va"]: r for r in map(json.loads, fh)}
    totals, by_evidence = evaluate(matches, held)
    report(totals, by_evidence, len(held), matches, judge_names(matches, real))


if __name__ == "__main__":
    sys.exit(main())
