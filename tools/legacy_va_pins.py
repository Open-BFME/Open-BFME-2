#!/usr/bin/env python3
"""Function pins in reverse/symbols.csv written as VAs: rewrite the proven ones.

A pin is an RVA (tools/pin_admission.py admits it only as an in-image RVA in
code), and tools/data_rows.py reads a function pin by its RVA alone. Pins
written before that rule as VAs (0x00401010 meaning RVA 0x00001010) name nothing
then. Reading such a pin as a VA wherever the VA reading lands in code is no
proof: the data pin _bfmeVftSF at 0x00816778 has a VA reading in .text too.
So a pin is rewritten only on evidence, when

  (a) its name is a function: decorated with a function type code, or it has a
      matched functions.csv row (under its name or its object symbol);
  (b) its RVA reading is not in an executable retail section; and
  (c) its value minus the image base is the start of a matched functions.csv
      row with that name or object symbol. (A Ghidra function start whose
      matched row has that name is the same fact: that row starts there.)

Exactly those pins become value - 0x400000; only their address field changes.
A pin meeting (a) and (b) but not (c) is reported as unresolved and left alone.

  python3 tools/legacy_va_pins.py           # report what would change
  python3 tools/legacy_va_pins.py --apply   # rewrite the proven pins
"""
import argparse
import csv
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

IMAGE_BASE = 0x400000
# ?name@scope@@<access/type code>: a letter is a function, a digit data. Only a
# plain qualified name is judged (no template or nested scope); anything else is
# not proven a function by its decoration.
DECORATED_FUNCTION = re.compile(r"^\?{1,2}[^@?$][^@]*@(?:[^@?$]+@)*@[A-Z]")
STDCALL_FUNCTION = re.compile(r"^[_@][A-Za-z_]\w*@\d+$")  # _name@8 / @name@8


def decorated_function(name):
    """True when the decoration itself says `name` is a function."""
    return bool(DECORATED_FUNCTION.match(name) or STDCALL_FUNCTION.match(name))


def plan(pins, rows, sections, object_symbol=lambda row: row["name"]):
    """(rewrites, unresolved) for symbols.csv `pins` [(name, address text)]:
    rewrites [(name, old, new, evidence)], unresolved [(name, address, why)].
    `rows` are matched functions.csv rows; `sections` retail_sections' 4-tuples."""
    import data_rows
    starts, owners = {}, {}
    for row in rows:
        start = int(row["target_rva"], 16)
        owners.setdefault(start, set()).add(row["name"])
        for key in {row["name"], object_symbol(row)}:
            starts.setdefault(key, set()).add(start)
    rewrites, unresolved = [], []
    for name, address in pins:
        value = int(address, 16)
        rowed = starts.get(name, set())
        if not (rowed or decorated_function(name)):
            continue                                                       # (a)
        if data_rows.section_kind(sections, IMAGE_BASE + value) == "code":
            continue                                                       # (b)
        rva = value - IMAGE_BASE
        if rva in rowed:                                                   # (c)
            rewrites.append((name, address, f"0x{rva:08X}",
                             f"matched functions.csv row {name} starts at 0x{rva:08X}"))
        else:
            why = (f"its rows start at {', '.join(f'0x{s:08X}' for s in sorted(rowed))}" if rowed
                   else "no matched functions.csv row has the name")
            there = sorted(owners.get(rva, ()))
            held = (f"; 0x{rva:08X} is the matched start of {there[0]}"
                    + (f" (+{len(there) - 1} more)" if len(there) > 1 else "") if there
                    else f"; no matched row starts at 0x{rva:08X}")
            kind = data_rows.section_kind(sections, value)
            unresolved.append((name, address, f"VA reading {kind or 'outside the image'}; {why}{held}"))
    return sorted(rewrites), sorted(unresolved)


def apply(text, rewrites):
    """symbols.csv text with exactly the rewritten pins' address field changed
    (notes are kept byte for byte: some hold unquoted commas)."""
    new = {(name, old): address for name, old, address, _ in rewrites}
    out, done = [], set()
    for line in text.splitlines(keepends=True):
        name, _, rest = line.partition(",")
        old, comma, notes = rest.partition(",")
        if (name, old) in new and comma:
            line = f"{name},{new[(name, old)]},{notes}"
            done.add((name, old))
        out.append(line)
    missing = set(new) - done
    if missing:
        raise SystemExit(f"legacy_va_pins: pins not found as lines: {sorted(missing)}")
    return "".join(out)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--apply", action="store_true", help="rewrite the proven pins in symbols.csv")
    args = parser.parse_args(argv)
    import build
    import data_rows
    text = build.SYMBOLS.read_bytes().decode("utf-8")
    pins = [(r[0], r[1]) for r in csv.reader(text.splitlines()) if len(r) >= 2 and r[1].startswith("0x")]
    rewrites, unresolved = plan(pins, build.load_function_rows(), data_rows.retail_sections(),
                                build.ledger_object_symbol)
    for name, old, new, evidence in rewrites:
        print(f"rewrite    {name} {old} -> {new}: {evidence}")
    for name, address, why in unresolved:
        print(f"unresolved {name} {address}: {why}")
    print(f"legacy_va_pins: {len(rewrites)} to rewrite, {len(unresolved)} unresolved")
    if args.apply and rewrites:
        build.SYMBOLS.write_bytes(apply(text, rewrites).encode("utf-8"))
    return 0


if __name__ == "__main__":
    sys.exit(main())
