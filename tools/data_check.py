#!/usr/bin/env python3
"""DIR32 data references must bind to the data ledger's global (shadow mode).

reverse/data_ledger.csv (tools/data_ledger.py) names one symbol per retail data
address. For each checked source's matched rows this reads the compiled
object and flags:

  wrong-name     a DIR32 relocation reaches ledger address A through a symbol
                 that is not A's ledger name (an invented second global for
                 retail's one: `g_Va009FE16C` where the ledger has
                 `TheScriptEngine`). Compiler-emitted names (string and float
                 literals, vftables, RTTI, imports) are the compiler's and are
                 not judged.
  duplicate-def  the object defines (non-COMDAT, external or static) a data
                 symbol that reaches a ledger address another TU owns.

Existing violations are keyed in reverse/data_check_baseline.txt
(`source<TAB>check<TAB>symbol<TAB>address`), which may only shrink:
--write-baseline never adds a key unless --init, and --assert-shrink-only REF
fails when the file gained a line against git REF. In shadow mode (the
default) findings are printed and the exit status is 0; --enforce exits 1 on
a finding outside the baseline.

  python3 tools/data_check.py --staged          # pre-commit: staged C/C++ sources
  python3 tools/data_check.py SOURCE...
  python3 tools/data_check.py --all [--write-baseline [--init]]
  python3 tools/data_check.py --assert-shrink-only HEAD
"""
import argparse
import collections
import csv
import struct
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import data_ledger as dl  # noqa: E402

BASELINE = ROOT / "reverse" / "data_check_baseline.txt"
HEADER = "# source\tcheck\tsymbol\taddress -- shrink-only; written by tools/data_check.py\n"


def source_rows(sources):
    wanted = set(sources)
    return [r for r in dl.matched_rows() if r["source"] in wanted]


def object_facts(rows):
    """{source: (bindings {(symbol, base)}, defined data symbols {name})}."""
    sections = dl.retail_sections()
    text = next((s for s in sections if s[0] == ".text"), None)
    out = {}
    for row in rows:
        obj = build.row_object(row)
        if not obj.exists():
            continue
        binds, defined = out.setdefault(row["source"], (set(), set()))
        if not defined:
            _d, osecs, symbols = dl.layout(obj)
            for s in symbols:
                if s["section"] <= 0 or s.get("storage") not in (dl.EXTERNAL, dl.STATIC) or s["name"].startswith(("$", ".")):
                    continue
                flags = osecs[s["section"] - 1]["characteristics"]
                if not flags & (dl.CODE | dl.COMDAT):
                    defined.add(s["name"])
        try:
            rva, size = int(row["target_rva"], 16), int(row["target_size"], 0)
            target = build.read_target_bytes(rva, size)
            body, relocs = build.read_object_symbol_bytes(obj, build.ledger_object_symbol(row), size)
        except (ValueError, OSError, SystemExit):
            continue
        for offset, kind, symbol in relocs:
            if kind != dl.DIR32 or offset + 4 > min(size, len(body), len(target)) or symbol.startswith(("$", "__ehhandler$")):
                continue
            base = (struct.unpack_from("<I", target, offset)[0] - struct.unpack_from("<I", body, offset)[0]
                    - dl.IMAGE_BASE) & 0xFFFFFFFF
            if text and text[1] <= base < text[1] + text[3]:
                continue
            binds.add((symbol, base))
    return out


def findings(facts, ledger):
    """[(source, check, symbol, '0xADDR')] for the given object facts."""
    out = set()
    for source, (binds, defined) in facts.items():
        for symbol, base in binds:
            row = ledger.get(base)
            if row is None or dl.kind_of(symbol) != "global" or row["kind"] != "global":
                continue
            if symbol != row["name"]:
                out.add((source, "wrong-name", symbol, f"0x{base:08X}"))
            if symbol in defined and row["source"] and row["source"] != source:
                out.add((source, "duplicate-def", symbol, f"0x{base:08X}"))
    return sorted(out)


def read_baseline(text=None):
    if text is None:
        text = BASELINE.read_text(encoding="utf-8") if BASELINE.exists() else ""
    return {tuple(line.split("\t")) for line in text.splitlines() if line and not line.startswith("#")}


def write_baseline(keys):
    BASELINE.write_text(HEADER + "".join("\t".join(k) + "\n" for k in sorted(keys)), encoding="utf-8", newline="")


def staged_sources():
    names = subprocess.run(["git", "diff", "--cached", "--name-only", "--diff-filter=ACMR"], cwd=ROOT,
                           capture_output=True, text=True).stdout.split()
    return [n for n in names if n.lower().endswith((".c", ".cpp"))]


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("sources", nargs="*")
    parser.add_argument("--staged", action="store_true")
    parser.add_argument("--all", action="store_true")
    parser.add_argument("--enforce", action="store_true", help="exit 1 on a finding outside the baseline")
    parser.add_argument("--write-baseline", action="store_true")
    parser.add_argument("--init", action="store_true", help="with --write-baseline: allow new keys")
    parser.add_argument("--assert-shrink-only", metavar="REF")
    args = parser.parse_args(argv)
    if args.assert_shrink_only:
        old = subprocess.run(["git", "show", f"{args.assert_shrink_only}:reverse/data_check_baseline.txt"],
                             cwd=ROOT, capture_output=True, text=True)
        grown = read_baseline() - read_baseline(old.stdout) if old.returncode == 0 else set()
        for key in sorted(grown):
            print("data_check: baseline gained", "\t".join(key))
        return 1 if grown else 0
    started = time.time()
    ledger = dl.load()
    if not ledger:
        print("data_check: no reverse/data_ledger.csv; nothing to check")
        return 0
    if args.all:
        sources = sorted({r["source"] for r in dl.matched_rows()})
    elif args.staged:
        sources = staged_sources()
    else:
        sources = args.sources
    found = findings(object_facts(source_rows(sources)), ledger)
    baseline = read_baseline()
    if args.write_baseline:
        keys = set(found) if args.init else set(found) & baseline
        if args.all:
            write_baseline(keys)
        else:   # a partial run only drops keys of the sources it checked
            write_baseline({k for k in baseline if k[0] not in set(sources)} | keys)
        print(f"data_check: baseline {len(keys)} key(s)")
        return 0
    new = [f for f in found if f not in baseline]
    for f in new:
        print("data_check:", "\t".join(f))
    kinds = collections.Counter(f[1] for f in new)
    mode = "enforce" if args.enforce else "shadow"
    print(f"data_check ({mode}): {len(sources)} source(s), {len(found)} finding(s), {len(new)} outside the "
          f"baseline {dict(kinds)}; {time.time() - started:.1f}s")
    return 1 if new and args.enforce else 0


if __name__ == "__main__":
    sys.exit(main())
