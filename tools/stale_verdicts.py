#!/usr/bin/env python3
"""List deferral verdicts in reverse/re_attempts.log that the ledger has overtaken.

add_match records `landed` since the Seek gap (tools/add_match.py
record_landing); landings before that left the log's last word at whatever the
previous attempt wrote. Five kinds of stale row result:

  landed    the deferral's own RVA now carries a real-source `matched` row under
            the SAME name. Mechanical: --record appends the `landed` verdict the
            landing should have written.
  converted its RVA is matched under a real name and the deferral was logged
            under a d_<rva>/gen_ placeholder name: the dump was converted.
            Mechanical: --record appends `converted`.
  superseded the deferral was logged under an address-derived name for its OWN
            address (?rva<rva>, Rva<rva>, FUN_<va>, T_<rva>, ...) and that RVA now
            carries a real-source matched row whose size equals the size the
            deferral logged. The placeholder named nothing but the address, so the
            body at that address landing is the resolution. Mechanical: --record
            appends `converted`. A size mismatch stays `renamed`.
  renamed   its RVA is matched under a DIFFERENT real name. Reported only -- the
            two names may be one function or a mis-anchor, and that is a judgement.
  cites     its evidence names a now-matched RVA beside a dependency word
            (unresolved, blocked, depends, ...). Reported only: the row may be
            landable now, or still walled for another reason. A worker reviews
            these and lands them or re-records them with blocked-on=.

gen_asm/gen_small placeholder rows never count as matched (re_log.matched_rvas).

  python3 tools/stale_verdicts.py                 # summary + rows
  python3 tools/stale_verdicts.py --kind cites    # one kind
  python3 tools/stale_verdicts.py --json
  python3 tools/stale_verdicts.py --record        # backfill landed, converted, superseded
"""
import argparse
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import re_log  # noqa: E402

# A dependency word within a short window of the address -- what separates
# "unresolved ChunkLoadClass::Seek 6150C0" from "calls 0x6150C0, resolved".
_DEPENDENCY = re.compile(
    r"\b(?:unresolved|unrowed|blocked|blocker|depends?|dependency|waiting|missing|needs|"
    r"wall(?:ed)?|not yet|unmatched|absent)\b", re.IGNORECASE)
_ADDRESS = re.compile(r"(?<![0-9A-Za-z])(?:0[xX])?([0-9A-Fa-f]{5,8})(?![0-9A-Za-z])")
_WINDOW = 80
_PLACEHOLDER_NAME = re.compile(r"^\?(?:d_[0-9A-Fa-f]+|gen_\w+)@@")
# An address embedded in a placeholder name: ?rva0079B250@@, Rva00017890String,
# FUN_00423B30 (a VA), T_009F4FB0, d_7B9C10. Only counts when it is the row's own.
_ADDRESS_IN_NAME = re.compile(r"(?i)(?:rva|fun_|sub_|d_|t_)([0-9a-f]{5,8})(?![0-9a-f])")
_IMAGE_BASE = 0x400000


def ledger_names():
    """{rva: {names}} for real provider rows (re_log's rule, re_log's CSV parse)."""
    names = {}
    for row in re_log.ledger_rows():
        rva = re_log._rva_of(row)
        if rva is not None and re_log._is_provider(row):
            names.setdefault(rva, set()).add(row["name"])
    return names


def ledger_sizes():
    """{rva: {target_size}} for real provider rows."""
    sizes = {}
    for row in re_log.ledger_rows():
        rva = re_log._rva_of(row)
        if rva is not None and re_log._is_provider(row):
            try:
                sizes.setdefault(rva, set()).add(int(row.get("target_size") or "", 0))
            except ValueError:
                pass
    return sizes


def names_own_address(symbol, rva):
    """True when the symbol is address-derived from its own RVA (or VA)."""
    for hit in _ADDRESS_IN_NAME.finditer(symbol):
        if int(hit.group(1), 16) in (rva, rva + _IMAGE_BASE):
            return True
    return False


_LOG_SIZES = None


def logged_size(symbol, rva):
    """Size field of the newest log row for (symbol, rva), or None."""
    global _LOG_SIZES
    if _LOG_SIZES is None:
        _LOG_SIZES = {}
        with re_log.RE_ATTEMPTS.open(encoding="utf-8", errors="replace") as handle:
            for line in handle:
                fields = line.rstrip("\r\n").split("\t")
                if len(fields) < 5:
                    continue
                try:
                    _LOG_SIZES[(fields[0], int(fields[1], 16))] = int(fields[2], 0)
                except ValueError:
                    continue
    return _LOG_SIZES.get((symbol, rva))


def cited_blockers(evidence, own_rva, matched):
    """Matched RVAs the evidence names near a dependency word, excluding its own."""
    found = []
    for hit in _ADDRESS.finditer(evidence):
        try:
            rva = int(hit.group(1), 16)
        except ValueError:
            continue
        if rva == own_rva or rva not in matched or rva in found:
            continue
        window = evidence[max(0, hit.start() - _WINDOW):hit.end() + _WINDOW]
        if _DEPENDENCY.search(window):
            found.append(rva)
    return found


def scan():
    re_log._load()
    names = ledger_names()
    sizes = ledger_sizes()
    matched = set(names)
    rows = []
    for rva, verdicts in sorted(re_log._BY_RVA.items()):
        for symbol, (status, evidence) in sorted(verdicts.items()):
            if status not in re_log.DEFERRED_STATUSES:
                continue
            if rva in matched:
                if symbol in names[rva]:
                    kind = "landed"
                elif _PLACEHOLDER_NAME.match(symbol):
                    kind = "converted"
                elif (names_own_address(symbol, rva)
                      and logged_size(symbol, rva) in sizes.get(rva, ())):
                    kind = "superseded"
                else:
                    kind = "renamed"
                rows.append({"kind": kind, "symbol": symbol, "rva": rva,
                             "status": status, "owners": sorted(names[rva]),
                             "evidence": evidence})
                continue
            if re_log.is_unblocked(symbol, rva):
                continue        # already released by blocked-on=
            blockers = cited_blockers(evidence, rva, matched)
            if blockers:
                rows.append({"kind": "cites", "symbol": symbol, "rva": rva,
                             "status": status,
                             "blockers": [f"0x{b:08X}" for b in blockers],
                             "evidence": evidence})
    return rows


def size_of(symbol, rva):
    """Size field of the newest log row for (symbol, rva), for the backfill row."""
    size = "0"
    text = f"0x{rva:08X}".lower()
    with re_log.RE_ATTEMPTS.open(encoding="utf-8", errors="replace") as handle:
        for line in handle:
            fields = line.rstrip("\r\n").split("\t")
            if len(fields) >= 5 and fields[0] == symbol and fields[1].lower() == text:
                size = fields[2]
    return size


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--kind", choices=("landed", "converted", "superseded", "renamed", "cites"))
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--record", action="store_true",
                        help="append the resolved verdict for kind=landed/converted/superseded")
    args = parser.parse_args()
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")

    rows = scan()
    if args.record:
        todo = [row for row in rows
                if row["kind"] in ("landed", "converted", "superseded")]
        for row in todo:
            superseded = row["kind"] == "superseded"
            re_log.append(row["symbol"], f"0x{row['rva']:08X}",
                          size_of(row["symbol"], row["rva"]),
                          "converted" if superseded else row["kind"],
                          "stale_verdicts backfill: "
                          + ("address-named deferral; same-size " if superseded else "")
                          + "real-source matched row at this "
                          f"RVA ({', '.join(row['owners'])})")
        print(f"stale_verdicts: recorded {len(todo)} resolved verdict(s) -- "
              f"stage reverse/re_attempts.log")
        return
    if args.kind:
        rows = [row for row in rows if row["kind"] == args.kind]
    if args.json:
        print(json.dumps(rows, indent=1))
        return
    counts = {}
    for row in rows:
        counts[row["kind"]] = counts.get(row["kind"], 0) + 1
    for row in rows:
        extra = row.get("owners") or row.get("blockers")
        print(f"{row['kind']:8} 0x{row['rva']:08X} {row['status']:9} {row['symbol']}"
              f"  -> {', '.join(extra)}")
    print(f"stale_verdicts: {counts or 'none'}")


if __name__ == "__main__":
    main()
