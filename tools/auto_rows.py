#!/usr/bin/env python3
"""Ledger rows for code the tree already compiles at an address no row owns.

A matched row often calls a static helper or an inline copy compiled in its
own object, or a function another object defines, at a retail address no row
claims. The byte gate passes the call (the displacement is masked or pinned)
but a link cannot place that code at retail's address, so every caller fails
the link measurement (research 29: "calls own-file non-ledger code").

allowed_symbols.py classifies such a reference `unowned/match` only when the
definition the link would use has the retail extent of the target (its Ghidra
boundary) and equals retail there in bytes and resolved relocations. This
tool turns each such target into a row: the definition's own symbol at the
target, the retail extent, the defining object's source, and an
`auto-row=allowed_symbols` note. It never names anything (the symbol is the
one the source already defines) and never claims a byte another row holds.
EH thunks and funclets (__ehhandler$ ...) are not rows: they are (owner, eh).
A body whose own references bind outside their allowed sets is not rowed
either: the row would add wrong bindings to the debt.

  python3 tools/auto_rows.py                 list the rows it would add
  python3 tools/auto_rows.py --write [--limit N] [--source F ...]
                                             append them to reverse/functions.csv
Then verify with the gate (`py -3 tools/build.py <sources>`); the commit hook
re-verifies every source a row is added for.
"""
import argparse
import bisect
import collections
import csv
import io
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import allowed_symbols as allowed  # noqa: E402
import build  # noqa: E402
import ledger_io  # noqa: E402

NOTE = "auto-row=allowed_symbols"
MIN_SIZE = 5


def candidates(ident, found, rows):
    """[(row dict)] one per unowned retail target whose definition certifies there."""
    source_of = {}
    for row in rows:
        source_of.setdefault(str(allowed.row_object(row)), row["source"])
    names = {row["name"] for row in rows}
    starts = ident.span_starts
    picked, out = set(), []
    for row, _, _, name, t, cls, detail in found:
        if cls != "unowned" or detail != "match" or t in picked:
            continue
        sym_local = name not in ident.defs
        if sym_local:
            path = str(allowed.row_object(row))        # a static of the referencing object
        else:
            path, _ = ident.kept(name)
        src = source_of.get(path)
        if src is None or src.lower().endswith((".asm", build.LIB_SUFFIX)):
            continue
        if name in names or name.startswith(allowed.EH_PREFIX) or name.startswith(("$", ".", "_$")):
            continue                                 # a name the ledger holds elsewhere, or not a function
        if ident.certify(path, name, t) != "retail":
            continue
        size = ident._extents[(path, name, t)]
        if size < MIN_SIZE:
            continue                                 # a ret/jmp-sized body folds anywhere: no identity
        i = bisect.bisect_left(starts, t)
        if i < len(starts) and starts[i] < t + size:
            continue                                 # another row starts inside the extent
        if ident.container(t)[0] is not None:
            continue
        new = {"name": name, "export_rva": "", "target_rva": "0x%08X" % t, "target_size": str(size),
               "source": src, "status": "matched", "notes": NOTE}
        if any(ref[4] in allowed.WRONG for ref in ident.row_refs(new)):
            continue                                 # the body's own calls bind wrongly: no new debt
        picked.add(t)
        names.add(name)
        out.append(new)
    return sorted(out, key=lambda r: (r["source"], int(r["target_rva"], 16)))


def append_rows(new):
    path = build.FUNCTIONS
    raw = path.read_bytes()
    term = ledger_io.lf_terminator(raw, "functions.csv")
    buf = io.StringIO()
    w = csv.writer(buf, lineterminator="\n")
    for r in new:
        w.writerow([r["name"], r["export_rva"], r["target_rva"], r["target_size"], r["source"], r["status"], r["notes"]])
    text = buf.getvalue().encode("utf-8").replace(b"\n", term)
    path.write_bytes(raw + text)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--limit", type=int, default=0, help="at most N rows (whole sources, in order)")
    ap.add_argument("--source", nargs="*", help="only rows for these sources")
    args = ap.parse_args(argv)
    ident, rows = allowed.load()
    found = allowed.scan(ident, rows)
    new = candidates(ident, found, rows)
    if args.source:
        want = {s.replace("\\", "/") for s in args.source}
        new = [r for r in new if r["source"] in want]
    if args.limit:
        keep, sources = [], []
        for r in new:
            if r["source"] not in sources:
                if len(keep) >= args.limit:
                    break
                sources.append(r["source"])
            keep.append(r)
        new = keep
    by = collections.Counter(r["source"] for r in new)
    print("rows:", len(new), "bytes:", sum(int(r["target_size"]) for r in new), "sources:", len(by))
    if args.write:
        append_rows(new)
        for s in sorted(by):
            print(s)
    else:
        for r in new[:40]:
            print(r["target_rva"], r["target_size"], r["name"], r["source"])
    return 0


if __name__ == "__main__":
    sys.exit(main())
