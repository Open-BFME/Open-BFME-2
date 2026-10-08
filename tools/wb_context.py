#!/usr/bin/env python3
"""WorldBuilder lead context, shared by the work queues.

reverse/wb_name_leads.csv pairs each game.dat function (target_rva, an RVA
below the 0x400000 image base) with the WorldBuilder function tools/wb_match.py
matched it to: a likely original name (wb_name) and source file (wb_file),
with the match score and the evidence that voted for it. reverse/wb_members.csv
holds class member names and offsets read from WB assertions.

tools/wb_match.py and tools/wb_members.py own those files. A lead is IDENTITY
evidence -- it says what a body probably is and which source file it came from.
It never proves a byte match, and nothing here lands or claims work: the queues
use it to annotate candidates, to point at `tools/wb_show.py <rva> --gd`, and to
nudge ordering.

The leads CSV is a snapshot, so its current_kind goes stale as bodies land.
leads() therefore drops, at read time, every lead whose address a matched
reverse/functions.csv row already covers under a REAL name (wb_gold's
classifier, the one wb_match.py used to write the snapshot): the queues shrink
as work lands without waiting for a regenerated CSV. `--refresh` rewrites the
snapshot's current_name/current_kind columns from the same live check.

    import wb_context
    lead = wb_context.lead(0x003CA4BE)       # None when WB has nothing to say
    print(wb_context.line(lead))             # WB: ScriptActions::executeAction  (...)
    wb_context.members("Object")             # [{member, offset, ...}, ...]

Every file is parsed once per process and re-parsed only when its mtime or
size changes, so a long-running caller sees a regenerated CSV without a restart.
"""
import bisect
import csv
import os
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
LEADS_CSV = ROOT / "reverse" / "wb_name_leads.csv"
MEMBERS_CSV = ROOT / "reverse" / "wb_members.csv"
FUNCTIONS_CSV = ROOT / "reverse" / "functions.csv"

# A "high-score named lead" is one with a WB function name AND a score at or
# above this. Over the 2,862 named leads the median score is 2.0, the 75th
# percentile 3.0 and the 90th 5.0, so 4.0 keeps roughly the top fifth -- the
# leads several independent votes (callgraph, strings, vtable...) agreed on.
HIGH_SCORE = 4.0
# Multiplier the queues apply to a candidate carrying a high-score named lead.
# Deliberately modest: the lead is identity evidence, not landing evidence, and
# tools/yield_model.py's measured size curve stays the dominant term.
BOOST = 1.5

_CACHE = {}

# Leading checkout prefixes WB's debug strings carry ("C:\Projects\bfme2\",
# "c:\projects\bfme2\code\...", "..\..\") -- dropped so the path reads like a
# repo path (Code/GameEngine/...).
_PREFIX = re.compile(r"^(?:[a-z]:)?[\\/]?(?:projects[\\/]bfme2[\\/])?", re.I)
_UPDIRS = re.compile(r"^(?:\.\.[\\/])+")


def _cached(path, parse):
    """parse(path) once per (mtime, size); {} when the file is missing."""
    try:
        stat = os.stat(path)
    except OSError:
        return {}
    key = (stat.st_mtime_ns, stat.st_size)
    hit = _CACHE.get(path)
    if hit and hit[0] == key:
        return hit[1]
    value = parse(path)
    _CACHE[path] = (key, value)
    return value


def clear_cache():
    _CACHE.clear()


def wb_path(raw):
    """WB's recorded file path as a forward-slash repo-style path."""
    if not raw:
        return ""
    text = _UPDIRS.sub("", _PREFIX.sub("", raw.strip()))
    return text.replace("\\", "/")


def to_rva(value):
    """int RVA from an int or a '0x...' string; None when it is neither."""
    if value is None:
        return None
    if isinstance(value, int):
        return value
    try:
        return int(str(value), 16)
    except ValueError:
        return None


def _parse_leads(path):
    out = {}
    with open(path, newline="", encoding="utf-8") as fh:
        for row in csv.DictReader(fh):
            name, raw = row.get("wb_name", ""), row.get("wb_file", "")
            rva = to_rva(row.get("target_rva"))
            if rva is None or not (name or raw):
                continue  # a lead that names nothing tells a seat nothing
            try:
                score = float(row.get("score") or 0)
            except ValueError:
                score = 0.0
            relpath = wb_path(raw)
            out[rva] = {
                "rva": rva,
                "wb_name": name,
                "wb_class": name.rsplit("::", 1)[0] if "::" in name else "",
                "wb_file": raw,
                "wb_path": relpath,
                "wb_base": relpath.rsplit("/", 1)[-1],
                "score": score,
                "evidence": row.get("evidence", ""),
                "kind": row.get("current_kind", ""),
                "current_name": row.get("current_name", ""),
            }
    return out


def _parse_members(path):
    out = {}
    with open(path, newline="", encoding="utf-8") as fh:
        for row in csv.DictReader(fh):
            out.setdefault(row["class"], []).append(dict(row))
    for rows in out.values():
        rows.sort(key=lambda r: (to_rva(r.get("offset")) or 0, r.get("member", "")))
    return out


def _parse_landed(path):
    """Ranges matched ledger rows hold under a REAL name, as (starts, ranges).

    A row without a size covers its start address only. Rows outside the
    demangler's subset are skipped: they cannot be classified, so they retire
    nothing.
    """
    wb_gold = _wb_gold()
    ranges = []
    with open(path, newline="", encoding="utf-8") as fh:
        for row in csv.DictReader(fh):
            if row.get("status") != "matched":
                continue
            start = to_rva(row.get("target_rva"))
            if start is None:
                continue
            try:
                info = wb_gold.describe(row["name"], row.get("source", ""))
            except Exception:  # DemangleError
                continue
            if not info or info["kind"] != "REAL":
                continue
            try:
                size = int(row.get("target_size") or 0)
            except ValueError:
                size = 0
            ranges.append((start, start + max(size, 1), info["name"]))
    ranges.sort()
    return [r[0] for r in ranges], ranges


def landed(rva, ledger=None):
    """'Class::method' of the REAL-named matched row covering `rva`, or None."""
    value = to_rva(rva)
    if value is None:
        return None
    starts, ranges = _cached(str(ledger or FUNCTIONS_CSV), _parse_landed)
    if not ranges:
        return None
    index = bisect.bisect_right(starts, value)
    # Rows nest or alias only locally (ICF aliases, a funclet beside its
    # parent), so a short look back over the nearest starts is enough.
    for start, end, name in reversed(ranges[max(0, index - 64):index]):
        if start <= value < end:
            return name
    return None


def _live(snapshot, ledger):
    return {rva: entry for rva, entry in snapshot.items()
            if landed(rva, ledger) is None}


def leads(path=None, ledger=None, live=True):
    """{rva: lead} for every lead naming a function or a file.

    live (default): leads whose address has since landed under a REAL name in
    `ledger` (reverse/functions.csv) are dropped. live=False is the raw
    snapshot.
    """
    path = str(path or LEADS_CSV)
    snapshot = _cached(path, _parse_leads)
    if not live or not snapshot:
        return snapshot
    ledger = str(ledger or FUNCTIONS_CSV)
    # A missing ledger raises: serving the unchecked snapshot would hand out
    # landed work as open.
    stamp = tuple((st.st_mtime_ns, st.st_size)
                  for st in (os.stat(path), os.stat(ledger)))
    key = ("live", path, ledger)
    hit = _CACHE.get(key)
    if hit and hit[0] == stamp:
        return hit[1]
    value = _live(snapshot, ledger)
    _CACHE[key] = (stamp, value)
    return value


def lead(rva, path=None, ledger=None):
    """The live lead for one game.dat RVA (int or '0x...'), or None."""
    value = to_rva(rva)
    return None if value is None else leads(path, ledger).get(value)


def members(cls, path=None):
    """WB member rows for one class, offset order; [] when WB knows none."""
    return list(_cached(str(path or MEMBERS_CSV), _parse_members).get(cls, ()))


def named(entry):
    return bool(entry and entry["wb_name"])


def is_high(entry):
    """A named lead at or above HIGH_SCORE."""
    return named(entry) and entry["score"] >= HIGH_SCORE


def boost(entry):
    """Selection multiplier for a candidate carrying `entry` (BOOST or 1.0)."""
    return BOOST if is_high(entry) else 1.0


def line(entry):
    """'WB: Class::method  (File.cpp, score s, evidence)', or '' for no lead."""
    if not entry:
        return ""
    where = entry["wb_base"] or "file unknown"
    return (f"WB: {entry['wb_name'] or '(unnamed)'}  "
            f"({where}, score {entry['score']:g}, {entry['evidence'] or 'no evidence'})")


def show_command(rva):
    """The exact command printing WB's near-source body beside retail's."""
    return f"python3 tools/wb_show.py 0x{to_rva(rva):08X} --gd"


def norm_name(name):
    """'Class::method' comparison form of a mangled or demangled name, or ''."""
    if not name:
        return ""
    wb_gold = _wb_gold()
    text = name
    if name.startswith("?"):
        try:
            d = wb_gold.demangle(name)
        except Exception:  # outside the demangler's subset: no comparison
            return ""
        text = wb_gold.qualified(d.scopes, d.name)
    return wb_gold.normalize(text)


def _wb_gold():
    if str(ROOT / "tools") not in sys.path:
        sys.path.insert(0, str(ROOT / "tools"))
    import wb_gold
    return wb_gold


def _stem(path):
    base = re.split(r"[\\/]", path or "")[-1]
    return base.rsplit(".", 1)[0].lower()


def agreement(entry, name=None, source=None):
    """How a candidate's own identity agrees with its lead.

    "name" when its name normalizes to the lead's wb_name (Class::method),
    "file" when only its source file stem equals the lead's file stem, else
    None. Agreement is strong identity evidence; disagreement is not refutation
    (WB names are ~95% precise on held-out pairs, and a ZH/BFME1 donor may
    carry a renamed or moved function).
    """
    if not entry:
        return None
    if name and entry["wb_name"]:
        mine = norm_name(name)
        if mine and mine == norm_name(entry["wb_name"]):
            return "name"
    if source and entry["wb_path"] and _stem(source) == _stem(entry["wb_path"]):
        return "file"
    return None


AGREE_RANK = {"name": 0, "file": 1, None: 2}


def refresh(path=None, ledger=None):
    """Rewrite the snapshot's current_name/current_kind for landed leads.

    A lead whose address a REAL-named matched row now covers gets
    current_kind=REAL and that row's 'Class::method'; every other column and
    row is kept byte for byte in order. Returns how many rows changed.
    """
    path = Path(path or LEADS_CSV)
    with open(path, newline="", encoding="utf-8") as fh:
        reader = csv.DictReader(fh)
        fields, rows = reader.fieldnames, list(reader)
    changed = 0
    for row in rows:
        name = landed(row.get("target_rva"), ledger)
        if name is None or (row.get("current_kind") == "REAL"
                            and row.get("current_name") == name):
            continue
        row["current_kind"], row["current_name"] = "REAL", name
        changed += 1
    if changed:
        tmp = path.with_suffix(path.suffix + ".tmp")
        with open(tmp, "w", newline="", encoding="utf-8") as fh:
            writer = csv.DictWriter(fh, fieldnames=fields, lineterminator="\n")
            writer.writeheader()
            writer.writerows(rows)
        os.replace(tmp, path)
        clear_cache()
    return changed


def main(argv=None):
    import argparse
    ap = argparse.ArgumentParser(description="print the WB lead for RVAs")
    ap.add_argument("rvas", nargs="*")
    ap.add_argument("--refresh", action="store_true",
                    help="mark leads landed under a REAL name in "
                         "reverse/functions.csv as REAL in the leads CSV")
    args = ap.parse_args(argv)
    if args.refresh:
        print(f"wb_context: {refresh()} lead(s) marked REAL in {LEADS_CSV.name}")
    elif not args.rvas:
        ap.error("give RVAs, or --refresh")
    for rva in args.rvas:
        entry = lead(rva)
        if entry is None and to_rva(rva) in leads(live=False):
            print(f"0x{to_rva(rva):08X}  landed as {landed(rva)}; WB lead retired")
            continue
        print(f"0x{to_rva(rva):08X}  {line(entry) or 'no WB lead'}")
        if entry:
            print(f"            {show_command(rva)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
