#!/usr/bin/env python3
"""Turn accepted WorldBuilder name matches into a naming lead list.

Reads matches (see tools/wb_score.py for the record shape), keeps those with
score >= --threshold that land where the ledger has no real identity yet --
rowed PARTIAL or PLACEHOLDER addresses, pin-only addresses and unrowed
addresses -- and writes build/wb/name_leads.csv:

    target_rva,current_name,current_kind,wb_name,wb_file,score,evidence

sorted by the target function's size, largest first.  Sizes come from the
ledger, else from an optional game.dat feature file (tools/pe_features.py
output, "va"/"size").  wb_file is the match's "wb_file", else the first of
its "files", else the first "files" entry of the WorldBuilder feature record
at wb_va when --wb-features is given.

A lead is a candidate name, not an identity: it still has to pass the usual
identity, provenance and byte gates before any ledger row changes.

Usage:
    python3 tools/wb_leads.py --threshold 0.9 [--matches build/wb/matches.jsonl]
        [--gd-features build/wb/gd_functions.jsonl]
        [--wb-features build/wb/wb_functions.jsonl]
"""
import argparse
import csv
import json
import sys
from pathlib import Path

import wb_gold
import wb_score

DEFAULT_OUT = wb_gold.DEFAULT_OUT.parent / "name_leads.csv"
COLUMNS = ("target_rva", "current_name", "current_kind", "wb_name",
           "wb_file", "score", "evidence")
LEAD_KINDS = {"PARTIAL", "PLACEHOLDER", "PIN_ONLY", "UNROWED"}


def load_features(path, field):
    """{va: record[field]} from a pe_features JSONL file (streamed)."""
    out = {}
    with open(path, encoding="utf-8") as fh:
        for line in fh:
            rec = json.loads(line)
            out[rec["va"]] = rec[field]
    return out


def wb_file(match, wb_files):
    if match.get("wb_file"):
        return match["wb_file"]
    files = match.get("files") or wb_files.get(match["wb_va"]) or []
    return files[0] if files else ""


def lead_row(match, rec, wb_files):
    kind = wb_score.target_kind(rec)
    return {
        "target_rva": f"0x{match['gd_va'] - wb_gold.IMAGE_BASE:08X}",
        "current_name": rec["name"] if rec else "",
        "current_kind": kind,
        "wb_name": match["wb_name"],
        "wb_file": wb_file(match, wb_files),
        "score": f"{match['score']:.4f}",
        "evidence": ";".join(match.get("evidence", [])),
    }


def target_size(va, gold, gd_sizes):
    rec = gold.get(va)
    if rec and rec["size"]:
        return rec["size"]
    return gd_sizes.get(va, 0)


def build_leads(matches, gold, threshold, gd_sizes, wb_files):
    leads = []
    for m in matches:
        if m["score"] < threshold:
            continue
        rec = gold.get(m["gd_va"])
        if wb_score.target_kind(rec) not in LEAD_KINDS:
            continue
        size = target_size(m["gd_va"], gold, gd_sizes)
        leads.append((size, m["score"], lead_row(m, rec, wb_files)))
    leads.sort(key=lambda t: (-t[0], -t[1], t[2]["target_rva"]))
    return [row for _, _, row in leads]


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--threshold", type=float, required=True)
    ap.add_argument("--matches", type=Path, default=wb_score.DEFAULT_MATCHES)
    ap.add_argument("--gold", type=Path, default=wb_gold.DEFAULT_OUT)
    ap.add_argument("--gd-features", type=Path,
                    help="game.dat pe_features JSONL, for unrowed sizes")
    ap.add_argument("--wb-features", type=Path,
                    help="WorldBuilder pe_features JSONL, for source files")
    ap.add_argument("--out", type=Path, default=DEFAULT_OUT)
    args = ap.parse_args(argv)

    gold = wb_gold.load_gold(args.gold)
    gd_sizes = load_features(args.gd_features, "size") if args.gd_features else {}
    wb_files = load_features(args.wb_features, "files") if args.wb_features else {}
    leads = build_leads(wb_score.load_matches(args.matches), gold,
                        args.threshold, gd_sizes, wb_files)
    with open(args.out, "w", newline="", encoding="utf-8") as fh:
        writer = csv.DictWriter(fh, fieldnames=COLUMNS, lineterminator="\n")
        writer.writeheader()
        writer.writerows(leads)
    print(f"wrote {len(leads)} leads to {args.out}")


if __name__ == "__main__":
    sys.exit(main())
