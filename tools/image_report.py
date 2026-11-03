#!/usr/bin/env python3
"""What the linker cannot see: kept objects against retail. Reads no game assets; called by real-link.yml.

Initializers: retail's `.CRT$XCU` table against what our objects register. A body that exists only
as a plain function compiles, matches and links, and never runs. Order needs an image.
Vtables: every kept copy's length against retail's run of code pointers. COMDAT selection may keep
any copy, so the shortest one counts.
Globals and FieldParse tables: bytes against retail, each comparison bounded by the symbol's own
extent. A relocation's bytes are masked, so its target is compared with retail's pointer where the
ledger knows the target's address: a table copied from another game can agree on every offset and
hold its entries in the wrong order.
Duplicates: strong data defined twice, and one retail address with several defined names.

Usage: image_report.py [--out DIR]
"""
import argparse
import collections
import csv
import json
import re
import struct
import sys
from pathlib import Path

import build
import exit_link
import link_census as census
import link_cycle

UNINITIALIZED = 0x80
COMDAT = 0x1000
OUT = Path("build/exit_link")


class Retail:
    def __init__(self, data):
        self.data = data
        pe = struct.unpack_from("<I", data, 0x3C)[0]
        count = struct.unpack_from("<H", data, pe + 6)[0]
        optional = struct.unpack_from("<H", data, pe + 20)[0]
        self.base = struct.unpack_from("<I", data, pe + 52)[0]
        self.sections = []
        for index in range(count):
            at = pe + 24 + optional + 40 * index
            name = data[at:at + 8].rstrip(b"\0").decode()
            virtual_size, va, raw_size, raw = struct.unpack_from("<IIII", data, at + 8)
            self.sections.append((name, va, virtual_size, raw, raw_size))
        self.text = next(s for s in self.sections if s[0] == ".text")

    def read(self, rva, size):
        """Retail's bytes (zero past a section's file extent), or None outside the image."""
        for _name, va, virtual_size, raw, raw_size in self.sections:
            if va <= rva < va + max(virtual_size, raw_size):
                at = rva - va
                have = self.data[raw + at:raw + min(at + size, raw_size)] if at < raw_size else b""
                return have + bytes(size - len(have))
        return None

    def in_text(self, value):
        return self.text[1] <= value - self.base < self.text[1] + self.text[2]

    def initializers(self):
        """Function RVAs of the largest table a `push z; push a; call` pair names (`_initterm`)."""
        _name, _va, _size, raw, raw_size = self.text
        best = []
        for match in re.finditer(rb"(?=\x68(.{4})\x68(.{4})\xE8)", self.data[raw:raw + raw_size], re.S):
            end, start = (struct.unpack("<I", g)[0] - self.base for g in match.groups())
            if not (0 < start < end and end - start <= 0x10000 and (end - start) % 4 == 0):
                continue
            table = self.read(start, end - start)
            if not table:
                continue
            slots = struct.unpack(f"<{(end - start) // 4}I", table)
            if all(v == 0 or self.in_text(v) for v in slots) and sum(1 for v in slots if v) > len(best):
                best = [v - self.base for v in slots if v]
        return best

    def vtable_words(self, rva, limit):
        """Length of the run of code pointers at rva, within the ledger's extent."""
        words = 0
        while words * 4 < max(limit, 4):
            raw = self.read(rva + words * 4, 4)
            if raw is None or not self.in_text(struct.unpack("<I", raw)[0]):
                break
            words += 1
        return words


def data_verdict(ours, retail, masked):
    """'same', 'ours_zero_retail_not' or 'contents_differ', over ours' extent."""
    if all(k in masked or ours[k] == retail[k] for k in range(len(ours))):
        return "same"
    return "ours_zero_retail_not" if not any(ours) and not masked and any(retail) else "contents_differ"


def same_text(retail, first, second, target):
    """Do two addresses hold the same string, wide when the literal's mangled name says so?"""
    width = 2 if target.startswith("??_C@_1") else 1

    def text(rva):
        raw = retail.read(rva, 512) or b""
        for at in range(0, len(raw) - width + 1, width):
            if raw[at:at + width] == bytes(width):
                return raw[:at]
        return raw
    return text(first) == text(second)


def pointer_conflicts(retail, rva, found, addresses, span):
    """(offset, ours, retail's target) for each relocation the ledger can check; and the count it cannot."""
    conflicts, unknown = [], 0
    for offset, target, addend in found.pointers:
        if offset < 0 or offset + 4 > span:
            continue
        known = addresses.get(target)
        if not known:
            unknown += 1
            continue
        raw = retail.read(rva + offset, 4)
        value = struct.unpack("<I", raw)[0] - retail.base
        if any(value == address + addend for address in known):
            continue
        # Retail can hold one string literal several times; another copy of the text is the same data.
        if target.startswith("??_C@") and any(same_text(retail, value, address, target) for address in known):
            continue
        conflicts.append([offset, target, hex(value)])
    return conflicts, unknown


def vtable_verdict(words, lengths):
    """Retail's word count against every kept copy's length in bytes."""
    want = words * 4
    if min(lengths) < want:
        return "ours_shorter"
    return "ours_longer" if max(lengths) > want else "same_length"


class Definition:
    __slots__ = ("object", "extent", "body", "masked", "comdat", "pointers")


def scan_objects(paths):
    """({external name: [Definition]} for non-code symbols, [(object, symbol, body, masked)] registered,
    {external names defined in code})."""
    definitions = collections.defaultdict(list)
    registered = []
    code = set()
    for path in paths:
        raw = path.read_bytes()
        sections, symbols = link_cycle.parse_coff(raw)
        starts = collections.defaultdict(list)
        for symbol in symbols.values():
            if symbol.sec > 0:
                starts[symbol.sec].append(symbol.value)
        for symbol in symbols.values():
            if symbol.sec <= 0 or symbol.cls != link_cycle.EXTERNAL:
                continue
            section = sections[symbol.sec - 1]
            if section.name.startswith(".text"):
                code.add(symbol.name)
            if section.name.startswith((".text", ".debug", ".drectve")):
                continue
            end = min((v for v in starts[symbol.sec] if v > symbol.value), default=section.size)
            found = Definition()
            found.object, found.extent = path.name, end - symbol.value
            found.body = (bytes(found.extent) if section.flags & UNINITIALIZED
                          else raw[section.ptr + symbol.value:section.ptr + end])
            found.masked = {off - symbol.value + k for off, _i, _t in section.relocs for k in range(4)}
            found.comdat = bool(section.flags & COMDAT)
            found.pointers = [(off - symbol.value, symbols[i].name,
                               struct.unpack_from("<I", raw, section.ptr + off)[0] if not section.flags & UNINITIALIZED else 0)
                              for off, i, _t in section.relocs if i in symbols]
            definitions[symbol.name].append(found)
        for section in sections:
            if not section.name.startswith(".CRT$XCU"):
                continue
            for _offset, index, _kind in section.relocs:
                symbol = symbols.get(index)
                if symbol is None:
                    continue
                target = sections[symbol.sec - 1] if symbol.sec > 0 else None
                body = (raw[target.ptr + symbol.value:target.ptr + target.size]
                        if target and not target.flags & UNINITIALIZED else b"")
                masked = ({off - symbol.value + k for off, _i, _t in target.relocs for k in range(4)}
                          if target else set())
                registered.append((path.name, symbol.name, body, masked))
    return definitions, registered, code


def initializer_report(retail, rows, registered):
    in_order = retail.initializers()
    table = set(in_order)
    rva_of, row_at = {}, {}
    for row in rows:
        try:
            rva = int(row["target_rva"], 16)
        except ValueError:
            continue
        rva_of.setdefault(build.ledger_object_symbol(row) or row["name"], rva)
        rva_of.setdefault(row["name"], rva)
        row_at.setdefault(rva, row)
    mapped, pending, unmapped = set(), [], []
    for entry in registered:
        rva = rva_of.get(entry[1])
        if rva is None:
            pending.append(entry)
        else:
            mapped.add(rva)
    # A compiler-local `_$E37` has no ledger name: its masked bytes say which entry it is.
    bodies = {rva: retail.read(rva, 4096) for rva in table}
    for obj, symbol, body, masked in pending:
        hit = None
        if len(body) >= 5:
            hit = next((rva for rva, theirs in bodies.items() if rva not in mapped
                        and all(k in masked or body[k] == theirs[k] for k in range(len(body)))), None)
        if hit is None:
            unmapped.append([obj, symbol])
        else:
            mapped.add(hit)
    kinds = collections.Counter()
    plain = []
    for rva in sorted(table - mapped):
        row = row_at.get(rva)
        if row is None:
            kinds["no_row"] += 1
        elif row["name"].startswith("??__E"):
            kinds["row_named_as_initializer"] += 1
        elif "gen_small" in row["source"] or "gen-" in row["notes"]:
            kinds["generated_row"] += 1
        else:
            kinds["plain_function_row"] += 1
            plain.append([hex(rva), row["name"], row["source"]])
    return {"retail": len(table), "registered_entries": len(registered),
            "registered_retail_entries": len(table & mapped), "not_registered": len(table - mapped),
            "not_registered_kinds": dict(kinds), "registered_not_in_retail": len(mapped - table),
            "registered_unidentified": len(unmapped), "order": "needs an image",
            "not_registered_rvas": [hex(rva) for rva in in_order if rva not in mapped],
            "plain_functions": plain, "unidentified": unmapped}


def known_addresses(rows):
    """{symbol: {rva}} from both ledgers. One name can have several addresses (folds)."""
    addresses = collections.defaultdict(set)
    for row in rows:
        try:
            rva = int(row["target_rva"], 16)
        except ValueError:
            continue
        addresses[build.ledger_object_symbol(row) or row["name"]].add(rva)
        addresses[row["name"]].add(rva)
    with open(build.ROOT / "reverse/data_ledger.csv", newline="", encoding="utf-8", errors="replace") as handle:
        for row in csv.DictReader(handle):
            for name in {row["name"], *(row.get("names") or "").split(";")}:
                if name:
                    addresses[name].add(int(row["address"], 16))
    return addresses


def bridge_entries(rows, paths):
    """([(rva, symbol)] of retail's initializers nothing registers, in retail's order, for a table
    built at link time; [rva] of those no kept object defines externally)."""
    retail = Retail(build.EXE.read_bytes())
    _definitions, registered, code = scan_objects(paths)
    report = initializer_report(retail, rows, registered)
    symbols = collections.defaultdict(list)
    for row in rows:
        try:
            rva = int(row["target_rva"], 16)
        except ValueError:
            continue
        symbols[rva].append(build.ledger_object_symbol(row) or row["name"])
    entries, unreachable = [], []
    for text in report["not_registered_rvas"]:
        rva = int(text, 16)
        name = next((n for n in symbols[rva] if n in code), None)
        if name is None:
            unreachable.append(text)
        else:
            entries.append((rva, name))
    return entries, unreachable


def ledger_report(retail, definitions, addresses):
    pointer_rows = []
    vtables, vtable_rows = collections.Counter(), []
    data, data_rows = collections.Counter(), []
    tables = collections.Counter()
    several = []
    with open(build.ROOT / "reverse/data_ledger.csv", newline="", encoding="utf-8", errors="replace") as handle:
        for row in csv.DictReader(handle):
            kind = row["kind"]
            if kind not in ("vtable", "global"):
                continue
            rva, size = int(row["address"], 16), int(row["size"] or 0)
            names = {n for n in {row["name"], *(row.get("names") or "").split(";")} if n}
            found = [(n, d) for n in sorted(names) for d in definitions.get(n, ())]
            if kind == "vtable":
                if not found:
                    vtables["no_object_defines_it"] += 1
                    continue
                words = retail.vtable_words(rva, size)
                lengths = [d.extent for _n, d in found]
                verdict = vtable_verdict(words, lengths)
                vtables[verdict] += 1
                if verdict != "same_length":
                    vtable_rows.append([hex(rva), row["name"], verdict, words, min(lengths) // 4, max(lengths) // 4])
                continue
            is_table = bool(re.search(r"[Ff]ield[Pp]arse|[Pp]arseTable", " ".join(names)))
            if len({n for n, _d in found}) > 1:
                several.append([hex(rva), sorted({n for n, _d in found})])
            if not found:
                data["no_object_defines_it"] += 1
                retail_bytes = retail.read(rva, size) if size else None
                data["no_object_retail_nonzero"] += bool(retail_bytes and any(retail_bytes))
                tables["no_object_defines_it"] += is_table
                continue
            name, found_def = found[0]
            span = min(size, found_def.extent)
            retail_bytes = retail.read(rva, span)
            if retail_bytes is None:
                continue
            verdict = data_verdict(found_def.body[:span], retail_bytes, found_def.masked)
            data[verdict] += 1
            tables[verdict] += is_table
            conflicts, unknown = pointer_conflicts(retail, rva, found_def, addresses, span)
            data["pointers_unchecked"] += unknown
            if conflicts:
                data["with_wrong_pointers"] += 1
                tables["with_wrong_pointers"] += is_table
                pointer_rows.append([hex(rva), name, len(conflicts), found_def.object, conflicts[:8]])
            if verdict != "same":
                first = next(k for k in range(span) if k not in found_def.masked
                             and found_def.body[k] != retail_bytes[k])
                data_rows.append([hex(rva), name, verdict, first, found_def.body[first:first + 4].hex(),
                                  retail_bytes[first:first + 4].hex(), span, found_def.object])
    strong = {n: [d.object for d in found] for n, found in definitions.items()
              if sum(1 for d in found if not d.comdat) > 1}
    return ({**vtables, "rows": vtable_rows}, {**data, "rows": data_rows, "pointer_rows": pointer_rows}, dict(tables),
            {"strong_data_defined_twice": len(strong), "strong": sorted(strong.items())[:200],
             "one_address_several_names": len(several), "several": several[:200]})


def summary(report):
    keys = {"initializers": ("retail", "registered_retail_entries", "not_registered"),
            "vtables": ("same_length", "ours_shorter", "ours_longer", "no_object_defines_it"),
            "globals": ("same", "contents_differ", "ours_zero_retail_not", "with_wrong_pointers",
                        "pointers_unchecked", "no_object_retail_nonzero"),
            "fieldparse": ("same", "contents_differ", "ours_zero_retail_not", "with_wrong_pointers",
                           "no_object_defines_it"),
            "duplicates": ("strong_data_defined_twice", "one_address_several_names")}
    return {area: {key: report[area].get(key, 0) for key in wanted} for area, wanted in keys.items()}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--out", type=Path, default=OUT)
    args = parser.parse_args(argv)
    csv.field_size_limit(10 ** 8)
    rows = build.load_function_rows()
    omitted = set(exit_link.placement_objects(rows))
    kept = [path for path in census._object_sources(rows) if path not in omitted]
    present = [path for path in kept if path.exists()]
    retail = Retail(build.EXE.read_bytes())
    definitions, registered, _code = scan_objects(present)
    report = {"objects_kept": len(kept), "objects_missing": len(kept) - len(present),
              "initializers": initializer_report(retail, rows, registered)}
    report["vtables"], report["globals"], report["fieldparse"], report["duplicates"] = \
        ledger_report(retail, definitions, known_addresses(rows))
    report["summary"] = summary(report)
    args.out.mkdir(parents=True, exist_ok=True)
    (args.out / "image_report.json").write_text(json.dumps(report, indent=1) + "\n", encoding="utf-8")
    print(json.dumps(report["summary"], indent=1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
