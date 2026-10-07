#!/usr/bin/env python3
"""Admission rules for the two ledger inputs the byte gate takes on trust.

reverse/symbols.csv pins and `object-symbol=` alias rows in functions.csv both
add a NAME -> ADDRESS fact that the REL32 resolver then believes for every
caller. Neither is proven by bytes: a pin naming the wrong function, or a row
renamed through object-symbol=, makes a wrong callee byte-match (audit
exploits 3 and 6, both passed the real pre-commit hook). So new ones are
admitted only under rules a reviewer could check by hand:

symbols.csv, per ADDED line (an edited line counts as added):
  * the address is an RVA inside the image. 108 pins were written as VAs
    (0x400000 too high) and silently named nothing;
  * it lies in an executable section. Data pins do nothing for REL32
    resolution and were the bypass for the data-identity checks; data gets a
    data ledger, not pins;
  * it does not give an address that already has a real (non-placeholder)
    name -- a ledger row or an existing pin -- a DIFFERENT name. One address,
    one identity; an ICF fold is recorded by renaming the owner row, not by
    stacking names.
There is no count limit: bulk generators add thousands of legitimate pins in
one commit, and every one of them is judged by the rules above.

functions.csv, per ADDED row:
  * no new alias row (build.is_alias_row): object-symbol= binding a real
    name to bytes compiled under another symbol. The existing ones are keyed
    `alias-row` lines in reverse/gate_baseline.txt (shrink-only), and only
    those still resolve callers (build.load_symbol_map). A tool-generated ICF
    fold list is the only future way in.

Existing violations are reported by --report and not re-judged per commit.

  python3 tools/pin_admission.py --staged          # pre-commit: index vs HEAD
  python3 tools/pin_admission.py --range OLD NEW   # pre-push
  python3 tools/pin_admission.py --report          # every current violation
"""
import argparse
import csv
import functools
import io
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402

ROOT = build.ROOT
PINS = "reverse/symbols.csv"
LEDGER = "reverse/functions.csv"
IMAGE_BASE = 0x400000


def git_text(spec):
    out = subprocess.run(["git", "-C", str(ROOT), "show", spec], capture_output=True)
    return out.stdout.decode("utf-8", errors="replace") if out.returncode == 0 else ""


def csv_rows(text):
    return list(csv.DictReader(io.StringIO(text)))


@functools.lru_cache(maxsize=1)
def image_layout():
    """(SizeOfImage, [(start, end, executable)]) of the retail image."""
    data = build.EXE.read_bytes()
    pe = build.u32(data, 0x3C)
    coff = pe + 4
    count = build.u16(data, coff + 2)
    optional = coff + 20
    size_of_image = build.u32(data, optional + 56)
    table = optional + build.u16(data, coff + 16)
    sections = []
    for i in range(count):
        at = table + i * 40
        start = build.u32(data, at + 12)
        size = max(build.u32(data, at + 8), build.u32(data, at + 16))
        executable = bool(build.u32(data, at + 36) & 0x20000020)
        sections.append((start, start + size, executable))
    return size_of_image, sections


# Address-derived names (Rva00380459Dtor, ?ji_0062af44, Gen004ED3A2) disclaim
# identity whatever follows the digits; GEN_PLACEHOLDER_RE stops at a trailing
# hex letter (the D of "Dtor"), so it is widened here.
ADDRESS_NAME_RE = re.compile(r"(?:[Rr]va|[Gg]en|ji|dup)_?[0-9A-Fa-f]{8}")


def is_placeholder(name, rva):
    return bool(build.GEN_PLACEHOLDER_RE.search(name) or build.DUP_ALIAS_RE.match(name)
                or ADDRESS_NAME_RE.search(name) or build.is_ghidra_autoname(name, rva))


def pin_problems(pin, names_at):
    """Why one pin line may not be added ([] = admissible)."""
    try:
        rva = int(pin["address"], 16)
    except (KeyError, TypeError, ValueError):
        return [f"unparseable address {pin.get('address')!r}"]
    size_of_image, sections = image_layout()
    if not 0 < rva < size_of_image:
        hint = (f" (a VA? the RVA would be 0x{rva - IMAGE_BASE:08X})"
                if 0 < rva - IMAGE_BASE < size_of_image else "")
        return [f"0x{rva:08X} is outside the image (SizeOfImage 0x{size_of_image:X}){hint}"]
    section = next((s for s in sections if s[0] <= rva < s[1]), None)
    if section is None or not section[2]:
        return [f"0x{rva:08X} is not in an executable section: data is not pinned here"]
    # A placeholder pin name adds no identity; a real one may not stack on
    # another real one.
    others = [] if is_placeholder(pin["name"], rva) else sorted(
        n for n in names_at.get(rva, ()) if n != pin["name"] and not is_placeholder(n, rva))
    if others:
        return [f"0x{rva:08X} already carries the real name {others[0]}; one address, one "
                "identity (rename the owner instead of stacking a second name)"]
    return []


def names_by_address(ledger_rows, pins):
    names = {}
    for row in ledger_rows:
        if build.is_alias_row(row) or "gen-alias" in build.notes_tokens(row):
            continue
        names.setdefault(int(row["target_rva"], 16), set()).add(row["name"])
    for pin in pins:
        try:
            names.setdefault(int(pin["address"], 16), set()).add(pin["name"])
        except (KeyError, TypeError, ValueError):
            continue
    return names


def pin_key(pin):
    return (pin.get("name"), pin.get("address"), pin.get("notes"))


def row_key(row):
    return tuple(row.get(f) for f in ("name", "export_rva", "target_rva", "target_size",
                                      "source", "status", "notes"))


def judge(old_pins, new_pins, old_rows, new_rows):
    problems = []
    before = {pin_key(p) for p in old_pins}
    after = {pin_key(p) for p in new_pins}
    # Rewriting a VA-stored pin as its RVA (same name and notes, address
    # lowered by the image base) repairs an existing line; it adds nothing.
    repaired = set()
    for pin in old_pins:
        try:
            if pin_key(pin) not in after:
                repaired.add((pin["name"], pin.get("notes"), int(pin["address"], 16) - IMAGE_BASE))
        except (KeyError, TypeError, ValueError):
            continue
    added = []
    for pin in new_pins:
        if pin_key(pin) in before:
            continue
        try:
            if (pin["name"], pin.get("notes"), int(pin["address"], 16)) in repaired:
                continue
        except (KeyError, TypeError, ValueError):
            pass
        added.append(pin)
    # Judge the proposed ownership state. Removed pins/rows must not block a
    # corrected owner, and a newly added ledger owner must still block an alias.
    # Added pins are checked and accumulated below so two new names also conflict.
    retained_pins = [p for p in new_pins if pin_key(p) in before]
    names_at = names_by_address(new_rows, retained_pins)
    for pin in added:
        for why in pin_problems(pin, names_at):
            problems.append(f"{PINS}: {pin['name']},{pin['address']}: {why}")
        try:
            names_at.setdefault(int(pin["address"], 16), set()).add(pin["name"])
        except (KeyError, TypeError, ValueError):
            pass
    old_keys = {row_key(r) for r in old_rows}
    for row in new_rows:
        if row_key(row) in old_keys or not build.is_alias_row(row):
            continue
        if build.gate_baselined("alias-row", row):
            continue
        problems.append(f"{LEDGER}: {row['name']} @{row['target_rva']}: new object-symbol= "
                        f"alias of {build.ledger_object_symbol(row)}; aliases are admitted only "
                        "from a tool-generated ICF fold list (none exists yet)")
    return problems


def add_pins(pins, notes="", reason=None):
    """The tool path for new pins: [(name, address)] -> problems ([] = written).

    Each pin is judged by the rules above against the working tree (ledger rows and
    pins), and a name that would then pin several addresses must stay consistent
    (pin_consistency: one name, one body). Nothing is written if any pin fails.
    Otherwise the lines are appended and tools/hatch_counters.py admits exactly these
    addresses, so the hatch register lets a checked, tool-written pin through and
    still refuses one typed into symbols.csv by hand."""
    import hatch_counters
    import pin_consistency
    path = ROOT / PINS
    raw = path.read_bytes()
    eol = b"\r\n" if raw.split(b"\n", 1)[0].endswith(b"\r") else b"\n"
    current = csv_rows(raw.decode("utf-8"))
    names_at = names_by_address(build.load_all_function_rows(), current)
    have = {(p.get("name"), p.get("address", "").upper().replace("0X", "0x")) for p in current}
    notes = (notes or "").replace(",", ";").replace("\n", " ").strip()
    problems, new = [], []
    for name, address in pins:
        try:
            address = f"0x{int(address, 16):08X}"
        except ValueError:
            problems.append(f"{name},{address}: unparseable address")
            continue
        if (name, address) in have or any(p["name"] == name and p["address"] == address for p in new):
            continue
        pin = {"name": name, "address": address, "notes": notes}
        problems += [f"{name},{address}: {why}" for why in pin_problems(pin, names_at)]
        names_at.setdefault(int(address, 16), set()).add(name)
        new.append(pin)
    if not problems and new:
        pinned = pin_consistency.load_pins(path)
        stacked = {p["name"] for p in new if pinned.get(p["name"])}
        if stacked:
            scanner, baseline = pin_consistency.Scanner(), pin_consistency.read_baseline()
            for name in sorted(stacked):
                addresses = list(pinned[name]) + [int(p["address"], 16) for p in new if p["name"] == name]
                found = scanner.inspect(name, addresses)
                if found and pin_consistency.key_of(name, found["bodies"]) not in baseline:
                    problems.append(f"{name}: {found['kind']}: {found['evidence']} "
                                    "(pin_consistency: one name, one function)")
    if problems or not new:
        return problems
    if raw and not raw.endswith(b"\n"):
        raw += eol
    lines = b"".join(f"{p['name']},{p['address']},{p['notes']}".encode("utf-8") + eol for p in new)
    path.write_bytes(raw + lines)
    hatch_counters.admit(PINS, reason or f"pin_admission --add: {len(new)} checked pin(s)",
                         tokens={p["address"] for p in new}, before=hatch_counters.blob_id(PINS, raw))
    for pin in new:
        print(f"pin admission: added {pin['name']},{pin['address']}")
    return []


def report():
    pins =csv_rows((ROOT / PINS).read_text(encoding="utf-8"))
    rows = build.load_all_function_rows()
    names_at = names_by_address(rows, [])
    count = 0
    by_address = {}
    for pin in pins:
        try:
            by_address.setdefault(int(pin["address"], 16), []).append(pin)
        except ValueError:
            pass
    for pin in pins:
        for why in pin_problems(pin, names_at):
            count += 1
            print(f"pin\t{pin['name']}\t{pin['address']}\t{why}")
    for row in rows:
        if build.is_alias_row(row):
            count += 1
            print(f"alias-row\t{row['name']}\t{row['target_rva']}\t"
                  f"{'baselined' if build.gate_baselined('alias-row', row) else 'NEW'}")
    print(f"{count} finding(s)", file=sys.stderr)


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true")
    mode.add_argument("--range", nargs=2, metavar=("OLD", "NEW"))
    mode.add_argument("--report", action="store_true")
    mode.add_argument("--add", nargs="+", metavar="NAME ADDRESS",
                      help="append checked pins (pairs) and admit them in the hatch register")
    parser.add_argument("--notes", default="", help="--add: notes column for the new lines")
    args = parser.parse_args()
    if args.add:
        if len(args.add) % 2:
            parser.error("--add takes NAME ADDRESS pairs")
        problems = add_pins(list(zip(args.add[::2], args.add[1::2])), args.notes)
        if problems:
            print(f"pin admission: REFUSED {len(problems)}; nothing written")
            for line in problems[:20]:
                print(f"  {line}")
            raise SystemExit(1)
        return
    if args.report:
        report()
        return
    old, new = ("HEAD", "") if args.staged else args.range
    problems = judge(csv_rows(git_text(f"{old}:{PINS}")), csv_rows(git_text(f"{new}:{PINS}")),
                     csv_rows(git_text(f"{old}:{LEDGER}")), csv_rows(git_text(f"{new}:{LEDGER}")))
    if problems:
        print(f"pin admission: FAIL {len(problems)}")
        for line in problems[:20]:
            print(f"  {line}")
        raise SystemExit(1)
    print("pin admission: OK")


if __name__ == "__main__":
    main()
