#!/usr/bin/env python3
"""What the linker cannot see: kept objects against retail. Reads no game assets; called by real-link.yml.

Initializers: retail's `.CRT$XCU` table against what our objects register. A body that exists only
as a plain function compiles, matches and links, and never runs. Order needs an image. A `_$E<n>`
is looked up in its own object (every object numbers its own); an unrowed one by its shape and
its relocations' targets. `twice` lists registrations that build an entry another object registers.
A slot associative with a public COMDAT (a template static's) runs once, however many objects emit it.
A credit is only as good as those targets: a relocation the ledger cannot place votes neither way, so a
registration can be credited with an entry that builds another global or runs another constructor, and
retail's own body then never runs. `credit_conflicts` lists each, naming ours and what the ledger names at
retail's address (LINK-634). It reports; it does not change what is credited.
Vtables: every kept copy's length against retail's run of code pointers. COMDAT selection may keep
any copy, so the shortest one counts.
Globals and FieldParse tables: bytes against retail, each comparison bounded by the symbol's own
extent. A relocation's bytes are masked, so its target is compared with retail's pointer where the
ledger knows the target's address: a table copied from another game can agree on every offset and
hold its entries in the wrong order.
Undersized globals: an object source constructs in place in a global smaller than the ledger's gap
to the next symbol. The constructor overwrites whatever follows it in our image. The gap is an upper
bound on retail's size, so read each row, but the source does construct an object there.
Duplicates: strong data defined twice, and one retail address with several defined names.

Usage: image_report.py [--out DIR]
"""
import argparse
import bisect
import collections
import csv
import json
import re
import struct
import sys
from pathlib import Path

import build
import exit_link
import ledger_io
import link_census as census
import link_cycle

UNINITIALIZED = 0x80
COMDAT = 0x1000
OUT = Path("build/exit_link")
# `new (&g_x)` and `((T *)&g_x)->T::T(`
CONSTRUCTED = re.compile(r"new\s*\(\s*&\s*(g_\w+)\s*\)|\(\s*(\w+)\s*\*\s*\)\s*&?\s*(g_\w+)\s*\)\s*->\s*\2::\2\s*\(")


def retail_function_spans(root=None):
    """(sorted [(start rva, size)] of Ghidra's retail functions, {every known start rva}).

    Starts are Ghidra's plus every ledger row's target, so a row that splits a
    Ghidra function still counts as a start."""
    root = Path(root or build.ROOT)
    spans, starts = [], set()
    with (root / "reverse/ghidra_functions.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            start = int(row["rva"], 16)
            spans.append((start, int(row["size"], 0)))
            starts.add(start)
    with (root / "reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            if (row.get("target_rva") or "").startswith("0x"):
                starts.add(int(row["target_rva"], 16))
    return sorted(spans), starts


class Retail:
    def __init__(self, data, function_spans=None):
        self.data = data
        self.function_spans = function_spans
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

    def mid_function(self, value):
        """Does the VA `value` land strictly inside a known retail function, never a
        function start? No vftable slot can; it is the next datum (a string that
        reads as a .text address). False when no function spans were supplied."""
        if not self.function_spans:
            return False
        spans, starts = self.function_spans
        rva = value - self.base
        if rva in starts:
            return False
        index = bisect.bisect_right(spans, (rva, float("inf"))) - 1
        return index >= 0 and spans[index][0] < rva < spans[index][0] + spans[index][1]

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
        while (words + 1) * 4 <= limit:
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


ASSOCIATIVE = 5


def comdat_owners(raw, sections, symbols):
    """{section number: public name} for each section linked only with another object's choice of a
    COMDAT: an associative section (selection 5) whose associated section's COMDAT symbol is public.

    A template static data member with a dynamic initializer (`ModuleTag<...>::s_key`) is emitted in
    every object that instantiates it: its data as a pick-any COMDAT, and its `.CRT$XCU` slot in a
    section associative with that data. The linker keeps one copy of the data and drops every other
    object's associated sections, so the slot runs once however many objects register it.
    """
    _, count, _, table, total, _, _ = struct.unpack_from("<HHIIIHH", raw, 0)
    associated, index = {}, 0
    while index < total:
        at = table + 18 * index
        value, sec, _type, cls, extra = struct.unpack_from("<IhHBB", raw, at + 8)
        if cls == link_cycle.STATIC and extra and 0 < sec <= count and value == 0 \
                and sections[sec - 1].flags & COMDAT:
            number, selection = struct.unpack_from("<HB", raw, at + 18 + 12)
            if selection == ASSOCIATIVE and 0 < number <= count:
                associated[sec] = number
        index += 1 + extra
    public = {}
    for i in sorted(symbols):
        symbol = symbols[i]
        if symbol.sec > 0 and symbol.cls == link_cycle.EXTERNAL and symbol.value == 0:
            public.setdefault(symbol.sec, symbol.name)
    return {sec: public[number] for sec, number in associated.items() if number in public}


def scan_objects(paths):
    """({external name: [Definition]} for non-code symbols, [(object, symbol, body, masked, relocs,
    local statics, owning public COMDAT or None)] registered, {external names defined in code})."""
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
        owners = comdat_owners(raw, sections, symbols)
        for section in sections:
            if not section.name.startswith(".CRT$XCU"):
                continue
            owner = owners.get(section.idx)
            for _offset, index, _kind in section.relocs:
                symbol = symbols.get(index)
                if symbol is None:
                    continue
                target = sections[symbol.sec - 1] if symbol.sec > 0 else None
                body = (raw[target.ptr + symbol.value:target.ptr + target.size]
                        if target and not target.flags & UNINITIALIZED else b"")
                masked = ({off - symbol.value + k for off, _i, _t in target.relocs for k in range(4)}
                          if target else set())
                relocs = ([(off - symbol.value, symbols[i].name, kind,
                            struct.unpack_from("<i", raw, target.ptr + off)[0])
                           for off, i, kind in target.relocs if i in symbols and off >= symbol.value]
                          if target and not target.flags & UNINITIALIZED else [])
                # Data only this object can name: its own statics, such as a header constant's copy.
                local = frozenset(symbols[i].name for off, i, _kind in (target.relocs if target else [])
                                  if i in symbols and off >= symbol.value and symbols[i].cls != link_cycle.EXTERNAL
                                  and symbols[i].sec > 0 and not sections[symbols[i].sec - 1].name.startswith(".text"))
                registered.append((path.name, symbol.name, body, masked, relocs, local, owner))
    return definitions, registered, code


def relocation_votes(retail, rva, relocs, places):
    """(agree, disagree) over a body's relocations whose targets the ledger places, read at rva.

    A DIR32 operand holds its target's address; a REL32 one its distance from the next instruction.
    `places(name)` is the set of RVAs the ledger gives that name, empty when it does not know it.
    """
    agree = disagree = 0
    for offset, target, kind, addend in relocs:
        known = places(target)
        raw = retail.read(rva + offset, 4) if known and kind in (link_cycle.DIR32, link_cycle.REL32) else None
        if raw is None:
            continue
        value = struct.unpack("<i", raw)[0]
        if kind == link_cycle.DIR32:
            got = (value & 0xFFFFFFFF) - retail.base - addend
        else:
            got = rva + offset + 4 + value - addend
        if got in known:
            agree += 1
        else:
            disagree += 1
    return agree, disagree


def credit_conflicts(retail, credits, places, addresses, code_bodies=None):
    """[{entry, object, symbol, how, kind, ours, retail_rva, retail_name, same_code}] for each relocation of
    a credited registration the ledger does not place, where it names something else at retail's address. A
    compiler-local target says nothing: every object numbers its own `_$E<n>`. `same_code` compares a called
    body with retail's row outside relocations, when `code_bodies(name)` gives (body, masked, size of retail's
    row by rva); None when it cannot be read, as for a body no object defines."""
    named = collections.defaultdict(set)
    for name, rvas in addresses.items():
        for rva in rvas:
            named[rva].add(name)
    found = []
    for (obj, symbol, relocs), (hit, how) in credits.items():
        for offset, target, kind, addend in relocs:
            if ledger_io.LOCAL_STATIC.fullmatch(target) or places(obj)(target) \
                    or kind not in (link_cycle.DIR32, link_cycle.REL32):
                continue
            raw = retail.read(hit + offset, 4)
            if raw is None:
                continue
            value = struct.unpack("<i", raw)[0]
            got = (value & 0xFFFFFFFF) - retail.base - addend if kind == link_cycle.DIR32 else hit + offset + 4 + value - addend
            names = named.get(got)
            if not names or target in names:
                continue
            same = None
            if kind == link_cycle.REL32 and code_bodies is not None:
                same = code_bodies(target, got)
            found.append({"entry": hex(hit), "object": obj, "symbol": symbol, "how": how,
                          "kind": "call" if kind == link_cycle.REL32 else "address", "ours": target,
                          "retail_rva": hex(got), "retail_name": sorted(names)[0], "same_code": same})
    return found


def reads_operand(body, offset):
    """True when the instruction whose absolute operand sits at `offset` only reads that address.

    Anything not recognised counts as building it, so a rare read form can only excuse a registration,
    the safe direction for a count of false doubles; `push offset s` and `mov ecx, offset s` hand the
    address on, which is how a constructor or memset builds it.
    """
    if offset >= 1 and body[offset - 1] in (0xA0, 0xA1):                  # mov al/eax, [m]
        return True
    if offset < 2 or body[offset - 1] & 0xC7 != 0x05:                     # not an absolute ModRM operand
        return False
    opcode, reg = body[offset - 2], body[offset - 1] >> 3 & 7
    if opcode in (0x02, 0x03, 0x0A, 0x0B, 0x12, 0x13, 0x1A, 0x1B, 0x22, 0x23, 0x2A, 0x2B, 0x32, 0x33,
                  0x38, 0x39, 0x3A, 0x3B, 0x84, 0x85, 0x8A, 0x8B, 0xD8, 0xDC):
        return True
    if opcode in (0xD9, 0xDB, 0xDD):                                      # fld, fild: the store forms have another /reg
        return reg == 0
    if opcode in (0xF6, 0xF7):                                            # test [m], imm
        return reg == 0
    if opcode == 0xFF:                                                    # push [m]
        return reg == 6
    return offset >= 3 and body[offset - 3] == 0x0F and opcode in (0xB6, 0xB7, 0xBE, 0xBF)


def builds_private_static(entry):
    """True when a registration builds storage only its own object can name. That is its own, whatever
    the ledger calls some other object's copy: a name is not an address, and 198 ledger rows share
    `_DRAWABLE_FRAMES_PER_FLASH`. Only reading a private static says nothing about what it builds."""
    _obj, _symbol, body, _masked, relocs, *rest = entry
    local = rest[0] if rest else frozenset()
    return any(target in local and not reads_operand(body, offset) for offset, target, *_kind in relocs)


def initializer_report(retail, rows, registered, addresses=None, code_bodies=None):
    addresses = addresses or {}
    in_order = retail.initializers()
    table = set(in_order)
    rva_of, row_at, local_of = {}, {}, {}
    for row in rows:
        try:
            rva = int(row["target_rva"], 16)
        except ValueError:
            continue
        # Every object numbers its own `_$E<n>`: two TUs' `_$E1` are different initializers, so a
        # compiler-local name is looked up only in the row's own object, never across the ledger.
        for symbol in {build.ledger_object_symbol(row) or row["name"], row["name"]}:
            if ledger_io.LOCAL_STATIC.fullmatch(symbol):
                local_of.setdefault((build.row_object(row).name, symbol), rva)
            else:
                rva_of.setdefault(symbol, rva)
        row_at.setdefault(rva, row)

    def rowed(entry):
        return (local_of.get((entry[0], entry[1])) if ledger_io.LOCAL_STATIC.fullmatch(entry[1])
                else rva_of.get(entry[1]))

    # Registrations a public COMDAT owns (`comdat_owners`: a template static's slot, emitted by every
    # object that instantiates it) run once, beside the copy of the data the link keeps. Keep one per
    # owner, a rowed one where there is one; the others are no second construction and no extra
    # initializer. Which object's copy survives follows link order, and every copy builds that global.
    kept = {}
    for entry in registered:
        owner = entry[6] if len(entry) > 6 else None
        if owner is not None and (owner not in kept or rowed(kept[owner]) is None and rowed(entry) is not None):
            kept[owner] = entry
    runs = [entry for entry in registered if len(entry) <= 6 or entry[6] is None or kept[entry[6]] is entry]
    discarded, registered = len(registered) - len(runs), runs
    mapped, pending, unmapped = set(), [], []
    for entry in registered:
        rva = rowed(entry)
        if rva is None:
            pending.append(entry)
        else:
            mapped.add(rva)
    # A compiler-local `_$E37` with no row in its own object: its masked bytes narrow it to retail
    # entries of the same shape, and its relocations' targets, where the ledger places them, pick
    # one. Many entries share a shape (`mov ecx, g; call ctor; push cleanup; call atexit`), so a
    # shape alone credits an arbitrary entry: those are taken last, in retail's order, and listed.
    bodies = {rva: retail.read(rva, 4096) for rva in in_order}

    def places(obj):
        def known(name):
            if ledger_io.LOCAL_STATIC.fullmatch(name):
                return {local_of[(obj, name)]} if (obj, name) in local_of else set()
            return addresses.get(name, set())
        return known

    def shaped(body, masked, taken=False):
        return [rva for rva in in_order if len(body) >= 5 and (rva in mapped) == taken
                and all(k in masked or body[k] == bodies[rva][k] for k in range(len(body)))]

    # A vote every remaining candidate shares picks none of them: `mov eax, [rate]; ...; mov [s], eax`
    # agrees on the rate with all 442 of retail's entries of that shape. Only a single best entry is
    # an identification; a tie is a shape credit. A registration that builds its own static (data only
    # its object names, such as a header constant's copy) where the ledger places none builds no other
    # object's global, so a tie credits it only when its object's like registrations use up the tie
    # (four `static StateVectorClass` in one unit and four retail entries calling that ctor); among
    # more entries, only a row names which one it is.
    def unplaced_local(entry):
        obj, _symbol, _body, _masked, relocs, *rest = entry
        local = rest[0] if rest else frozenset()
        return any(target in local and not places(obj)(target) for _offset, target, *_kind in relocs)

    def ties(entry):
        obj, _symbol, body, masked, relocs, *_local = entry
        votes = [(relocation_votes(retail, rva, relocs, places(obj)), rva) for rva in shaped(body, masked)]
        votes = [(agree, rva) for (agree, disagree), rva in votes if not disagree]
        best = max((agree for agree, _rva in votes), default=-1)
        return best, [rva for agree, rva in votes if agree == best]

    first = {id(entry): (entry[0], tuple(ties(entry)[1])) for entry in pending if unplaced_local(entry)}
    owned = collections.Counter(first.values())
    unowned = {key for key, count in owned.items() if count < len(key[1])}

    by_shape, credits = [], {}
    for strong in (True, False):
        waiting = []
        for entry in pending:
            obj, symbol, *_rest = entry
            best, tied = ties(entry)
            hit = tied[0] if tied else None
            if (hit is None or (strong and (best <= 0 or len(tied) > 1))
                    or (len(tied) > 1 and first.get(id(entry)) in unowned)):
                waiting.append(entry)
                continue
            mapped.add(hit)
            credits[(obj, symbol, tuple(entry[4]))] = (hit, "votes" if strong else "shape")
            if not strong:
                by_shape.append([obj, symbol, hex(hit)])
        pending = waiting
    unmapped = [[obj, symbol] for obj, symbol, *_rest in pending]
    # One left over whose relocations agree with an entry another registration already took builds
    # that entry's global a second time. One that builds its own static builds no other's.
    twice = []
    for entry in pending:
        obj, symbol, body, masked, relocs, *_local = entry
        if builds_private_static(entry):
            continue
        for rva in shaped(body, masked, taken=True):
            agree, disagree = relocation_votes(retail, rva, relocs, places(obj))
            if agree and not disagree:
                twice.append([obj, symbol, hex(rva)])
                break
    conflicts = credit_conflicts(retail, {key: credit for key, credit in credits.items() if key[2]}, places, addresses,
                                 code_bodies)
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
            "registered_comdat_copies_discarded": discarded,
            "registered_retail_entries": len(table & mapped), "not_registered": len(table - mapped),
            "not_registered_kinds": dict(kinds), "registered_not_in_retail": len(mapped - table),
            "registered_unidentified": len(unmapped), "registered_by_shape_only": len(by_shape),
            "registered_twice": len(twice), "twice": twice,
            "credit_conflicts": len(conflicts), "conflicts": conflicts,
            "order": "needs an image", "by_shape_only": by_shape,
            "not_registered_rvas": [hex(rva) for rva in in_order if rva not in mapped],
            "plain_functions": plain, "unidentified": unmapped}


def constructed_names(texts):
    """The plain names these source texts construct an object in."""
    return {m.group(1) or m.group(3) for text in texts for m in CONSTRUCTED.finditer(text)}


def undersized(names, size, extent, constructed):
    """True when one of a ledger row's names is constructed in storage smaller than the row's gap."""
    plain = {found.group(1) for found in (re.match(r"\?(g_\w+)@@", n) for n in names) if found}
    return extent < size and bool(plain & constructed)


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


def code_body_reader(paths, retail, rows, wanted):
    """code_bodies for credit_conflicts: does the first defining object's `name` equal retail's row at rva, outside
    relocations? A second pass over the objects, for the few names `wanted` holds."""
    sizes = {}
    for row in rows:
        try:
            sizes.setdefault(int(row["target_rva"], 16), int(row["target_size"] or 0))
        except ValueError:
            continue
    bodies = {}
    for path in paths:
        raw = path.read_bytes()
        sections, symbols = link_cycle.parse_coff(raw)
        for symbol in symbols.values():
            if symbol.sec > 0 and symbol.name in wanted and symbol.name not in bodies:
                section = sections[symbol.sec - 1]
                if section.name.startswith(".text"):
                    bodies[symbol.name] = (raw[section.ptr + symbol.value:section.ptr + section.size],
                                           {off - symbol.value + k for off, _i, _t in section.relocs for k in range(4)})

    def same_code(name, rva):
        size = sizes.get(rva)
        if name not in bodies or not size or len(bodies[name][0]) < size:
            return None
        body, masked = bodies[name]
        theirs = retail.read(rva, size)
        return theirs is not None and all(k in masked or body[k] == theirs[k] for k in range(size))
    return same_code


def bridge_entries(rows, paths):
    """([(rva, symbol)] of retail's initializers nothing registers, in retail's order, for a table
    built at link time; [rva] of those no kept object defines externally)."""
    retail = Retail(build.EXE.read_bytes())
    _definitions, registered, code = scan_objects(paths)
    report = initializer_report(retail, rows, registered, known_addresses(rows))
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


def ledger_report(retail, definitions, addresses, constructed=frozenset()):
    pointer_rows = []
    undersized_rows = []
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
                if size < 4 or size % 4:
                    vtables["retail_extent_unanalyzed"] += 1
                    if not found:
                        vtables["no_object_defines_it"] += 1
                    vtable_rows.append([hex(rva), row["name"], "retail_extent_unanalyzed", 0, 0, 0])
                    continue
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
            if undersized(names, size, found_def.extent, constructed):
                data["constructed_undersized"] += 1
                undersized_rows.append([hex(rva), name, found_def.extent, size, found_def.object])
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
    return ({**vtables, "rows": vtable_rows}, {**data, "rows": data_rows, "pointer_rows": pointer_rows, "undersized_rows": undersized_rows}, dict(tables),
            {"strong_data_defined_twice": len(strong), "strong": sorted(strong.items())[:200],
             "one_address_several_names": len(several), "several": several[:200]})


def summary(report):
    keys = {"initializers": ("retail", "registered_retail_entries", "not_registered", "registered_twice", "credit_conflicts"),
            "vtables": ("same_length", "ours_shorter", "ours_longer", "no_object_defines_it", "retail_extent_unanalyzed"),
            "globals": ("same", "contents_differ", "ours_zero_retail_not", "with_wrong_pointers",
                        "pointers_unchecked", "no_object_retail_nonzero", "constructed_undersized"),
            "fieldparse": ("same", "contents_differ", "ours_zero_retail_not", "with_wrong_pointers",
                           "no_object_defines_it"),
            "duplicates": ("strong_data_defined_twice", "one_address_several_names")}
    return {area: {key: report[area].get(key, 0) for key in wanted} for area, wanted in keys.items()}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--out", type=Path, default=OUT)
    parser.add_argument("--image", type=Path, help="compare actual linked copies via image_iso.py")
    parser.add_argument("--map", type=Path, help="MAP for --image")
    parser.add_argument("--objects", type=Path, help="hash-bound winning-object manifest for --image")
    parser.add_argument("--retail", type=Path, default=build.EXE)
    args = parser.parse_args(argv)
    if args.image:
        if not args.map:
            parser.error("--image requires --map")
        import image_iso
        command = ["--image", str(args.image), "--map", str(args.map),
                   "--retail", str(args.retail)]
        if args.out != OUT:
            command += ["--out", str(args.out)]
        if args.objects:
            command += ["--objects", str(args.objects)]
        return image_iso.main(command)
    if args.map or args.objects:
        parser.error("--map/--objects require --image")
    csv.field_size_limit(10 ** 8)
    rows = build.load_function_rows()
    omitted = set(exit_link.placement_objects(rows))
    kept = [path for path in census._object_sources(rows) if path not in omitted]
    present = [path for path in kept if path.exists()]
    retail = Retail(build.EXE.read_bytes())
    definitions, registered, _code = scan_objects(present)
    addresses = known_addresses(rows)
    called = {target for entry in registered for _offset, target, kind, _addend in entry[4] if kind == link_cycle.REL32}
    report = {"objects_kept": len(kept), "objects_missing": len(kept) - len(present),
              "initializers": initializer_report(retail, rows, registered, addresses,
                                                 code_body_reader(present, retail, rows, called))}
    sources = (path.read_text(encoding="utf-8", errors="replace") for path in (build.ROOT / "Code").rglob("*.cpp"))
    report["vtables"], report["globals"], report["fieldparse"], report["duplicates"] = \
        ledger_report(retail, definitions, addresses, constructed_names(sources))
    report["summary"] = summary(report)
    report["analysis_scope"] = {
        "linked_image_analyzed": False,
        "vtable_same_length_means": "length only; neither slots nor ABI verified",
        "constructed_undersized_means": "source-pattern and ledger-gap leads, not proven storage defects",
        "wrong_pointers_requires": "read beside pointers_unchecked; zero is not a clean pointer census",
    }
    args.out.mkdir(parents=True, exist_ok=True)
    (args.out / "image_report.json").write_text(json.dumps(report, indent=1) + "\n", encoding="utf-8")
    print(json.dumps(report["summary"], indent=1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
