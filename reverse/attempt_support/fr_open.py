#!/usr/bin/env python3
"""Triage the false-reject backlog by the only question that matters: is the
address the record names still unowned by the name the record wanted?

My earlier attempt sorted by "has the check's file changed since the record",
which flagged 584 of 601 because these tools change daily -- no signal. This
one reads the current ledger instead: a false reject is CLOSED when the name
the record was trying to land now owns that RVA, whatever repaired it.
"""
import collections
import csv
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SC = os.path.dirname(os.path.abspath(__file__))
os.chdir(ROOT)
sys.path.insert(0, "tools")

# --- current ledger, keyed by address ---------------------------------------
at = collections.defaultdict(list)
by_name = collections.defaultdict(list)
with open("reverse/functions.csv", newline="") as fh:
    for r in csv.DictReader(fh):
        try:
            rva = int(r["target_rva"], 16)
        except (ValueError, TypeError):
            continue
        at[rva].append(r)
        by_name[r["name"]].append(r)

PLACEHOLDER = re.compile(r"(?i)^\?*(rva|bfmeRva|ji_|uw_|dup_|d_)[0-9a-f]{4,}")


def placeholder(row):
    name, notes = row["name"], row.get("notes", "")
    return bool(PLACEHOLDER.match(name)) or "gen-" in notes


# --- the records ------------------------------------------------------------
# re_log's `void` is a RETRACTION, not a verdict: it deletes every EARLIER row at
# exactly its (symbol, rva). A false reject a later void retracted is no longer a
# record of anything, so counting it keeps a cleared blocker in the pile forever.
# (See re_log.VOID_STATUS. 15 records were retracted on 2026-11-10 alone.)
voids = collections.defaultdict(list)
records = []
with open("reverse/re_attempts.log", encoding="utf-8", errors="replace") as fh:
    for lineno, line in enumerate(fh, 1):
        f = line.rstrip("\n").split("\t")
        if len(f) == 5 and f[3] == "void":
            try:
                voids[(f[0], int(f[1], 16))].append(lineno)
            except ValueError:
                pass
        if "false-reject" not in line:
            continue
        if len(f) == 5 and f[3] == "void":
            continue        # a retraction that merely NAMES a false reject is not one
        if len(f) != 5:
            records.append({"line": lineno, "shape": len(f), "raw": line[:120]})
            continue
        sym, rva, size, status, ev = f
        m = re.search(r"false-reject ([A-Za-z0-9_./]+)", ev)
        records.append({
            "line": lineno, "sym": sym, "rva": rva, "size": size,
            "check": (m.group(1) if m else "?").rstrip(".:"),
            "ev": ev,
        })


def retracted(rec):
    """A void at this exact boundary, recorded after this row."""
    if "sym" not in rec:
        return False
    try:
        key = (rec["sym"], int(rec["rva"], 16))
    except ValueError:
        return False
    return any(line > rec["line"] for line in voids.get(key, ()))


live = [rec for rec in records if not retracted(rec)]
print(f"{len(records)} false-reject records, {len(records) - len(live)} of them "
      f"retracted by a later void; {len(live)} stand")
records = live

# --- classify ---------------------------------------------------------------
# A record's symbol is sometimes annotated, e.g. `_$E2(LivingWorldEyeTower)`.
bare = lambda s: re.sub(r"\(.*\)$", "", s).strip()

verdict = collections.Counter()
per_check = collections.defaultdict(collections.Counter)
open_rows = []
for rec in records:
    if "sym" not in rec:
        verdict["UNPARSED"] += 1
        continue
    try:
        rva = int(rec["rva"], 16)
    except ValueError:
        verdict["NO RVA"] += 1
        per_check[rec["check"]]["NO RVA"] += 1
        continue
    here = at.get(rva, [])
    want = bare(rec["sym"])
    if any(row["name"] == want for row in here):
        v = "CLOSED: wanted name owns the address"
    elif not here:
        v = "OPEN: no row at the address"
    elif all(placeholder(row) for row in here):
        v = "OPEN: still a placeholder"
    else:
        v = "OPEN?: a different real name owns it"
    verdict[v] += 1
    per_check[rec["check"]][v] += 1
    if v.startswith("OPEN"):
        rec["verdict"] = v
        rec["here"] = [f"{r['name']} ({r['source']})" for r in here]
        open_rows.append(rec)

print()
for v, n in verdict.most_common():
    print(f"{n:>5}  {v}")

print("\n{:>6} {:>7} {:>7} {:>7}  check".format("recs", "closed", "open", "other"))
tot = collections.Counter()
for check, c in sorted(per_check.items(), key=lambda kv: -sum(kv[1].values())):
    n = sum(c.values())
    closed = sum(v for k, v in c.items() if k.startswith("CLOSED"))
    op = sum(v for k, v in c.items() if k.startswith("OPEN:"))
    other = n - closed - op
    tot["n"] += n; tot["closed"] += closed; tot["open"] += op; tot["other"] += other
    if n >= 5:
        print(f"{n:>6} {closed:>7} {op:>7} {other:>7}  {check}")
print(f"{tot['n']:>6} {tot['closed']:>7} {tot['open']:>7} {tot['other']:>7}  TOTAL")

json.dump(open_rows, open(SC + "/fr_open.json", "w"), indent=1)
print(f"\n{len(open_rows)} open records written to {SC}/fr_open.json")
