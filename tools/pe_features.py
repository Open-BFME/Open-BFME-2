#!/usr/bin/env python3
"""Per-function feature records for a 32-bit PE, for cross-build name transfer.

BFME 2's WorldBuilder.exe is an unoptimised internal build of the same source
tree as the retail game.dat, and its assertion macros push the enclosing
function's name ("Coord3D::length"), the source path and the line number.
This module disassembles every function of either binary once (capstone) and
writes one JSON object per function, holding the build-independent evidence a
matcher can compare across the two builds:

  va, size   function start (absolute VA) and length in bytes; trailing int3
             padding is trimmed from boundaries this module derives itself
  names      WB only (--wb-names): Class::method strings pushed in the
             function, plus bare identifiers pushed in the assert shape
             (push cond; push name; push line; push file); most frequent first
  files      WB only: source paths pushed by the function, first-use order
  lines      WB only: line numbers pushed just before a source path
  debug      WB only: true for an out-of-line debug-object call (a tiny
             function that loads the debug object and calls one of its
             slots, e.g. the "is this assert site ignored?" check every
             macro makes); retail has no counterpart
  debug_calls WB only: the entries of `calls` made inside debug macros (from
             the macro's first debug-object call to the macro's skip
             target), duplicates kept; retail compiles these out
  name_files WB only: [name, path] for each name pushed in the assert shape,
             with the source path pushed beside it (first pairing per name);
             a name whose path is the function's own .cpp is the function's
             own, one whose path is a header was inlined from it
  strings    ASCII (>= 4 chars) and UTF-16LE strings whose address is an
             immediate or absolute operand, first-reference order, unique; in
             WB mode the assert condition, name and file strings are left out
             so the WB and retail sets are comparable
  imports    imported functions called or referenced (call/jmp [IAT],
             mov reg, [IAT], and calls through jmp [IAT] / ILT thunks), unique;
             a by-ordinal import is written dll#ordinal
  calls      direct E8 call targets in address order with duplicates;
             incremental-link (ILT) thunks are resolved to the real body
  icalls     indirect calls that are not import calls
  consts     unique, first-use order: float/double constants read from .rdata
             (shortest round-trip repr, "0.5"); immediates >= 0x10000 that are
             not image addresses, written as a float when they read as a plain
             float32 (optimised code stores 1.0f as mov [x], 0x3f800000) and
             as hex otherwise
  vt         [vtable_va, slot] for every vtable slot holding the function
  rtti       class names (.?AV...) from the vtables' RTTI locators, if any
  nbytes     bytes decoded as instructions (padding and jump tables excluded)

Function boundaries come from --boundaries (Ghidra's rva,size,name CSV) when
given. Otherwise they are derived from the image, which needs a .reloc
directory: ILT thunk targets, code addresses relocated from outside .text
(vtables, EH tables, callbacks), relocated immediates inside .text that are
not jump tables, and `push ebp; mov ebp, esp` after padding or a return;
then, to a fixpoint, every direct call target and any code that follows a
ret/jmp and int3 padding (WB links optimised library code without frames).
Each function runs to the next start. EH unwind funclets and __ehhandler
stubs come out as small functions of their own, as Ghidra lists them.
Switch tables inside a function are skipped, never decoded as code.

WB is not purely unoptimised: small inline functions (BitFlags<>::test,
Vector3::Length2, RefCountClass::ReleaseRef...) are expanded into callers,
so their assert names appear in many functions. A matcher should weight a
name by how few WB functions carry it.

With --augment-starts the Ghidra list is extended, to a fixpoint, by the
code it misses: vtable slots and direct call targets that land in .text
outside every listed body and outside int3 padding. A vtable slot counts
only beside a slot that already points at a known start, so string data
that happens to look like a .text address is not taken. Listed functions
keep their sizes; added ones run to the next start, minus int3 padding.

Vtables carry no RTTI in these builds (/GR-), so a vtable is a run of code
pointers in .rdata, split wherever code takes the address of a slot (the
constructor's `mov [this], offset vtable`).

  python3 tools/pe_features.py <pe> --out <jsonl> [--boundaries CSV] [--wb-names]
"""
import argparse
import bisect
import csv
import json
import math
import multiprocessing
import re
import struct
import sys
import time
from collections import Counter

import capstone
import pefile

NAME_RE = re.compile(r"^[A-Za-z_][\w:<>~ ,*&]*::[~\w]+$")
BARE_NAME_RE = re.compile(r"^~?[A-Za-z_]\w*$")
FILE_RE = re.compile(r"\.(?:cpp|c|cxx|h|hpp|inl)$", re.I)
LINE_RE = re.compile(r"0x[0-9a-f]+|\d+")
OPERAND_HEX_RE = re.compile(r"0x[0-9a-f]{5,}")  # values below 0x10000 never matter
ABS_MEM_RE = re.compile(r"\[(0x[0-9a-f]+)\]$")
JUMP_TABLE_RE = re.compile(r"^dword ptr \[\w+\*4 \+ (0x[0-9a-f]+)\]$")
INDEX_TABLE_RE = re.compile(r"^\w+, byte ptr \[\w+ \+ (0x[0-9a-f]+)\]$")
PRINTABLE = frozenset(range(0x20, 0x7F)) | {0x09, 0x0A, 0x0D}
MIN_STRING = 4
MAX_STRING = 4096
PADDING = (0xCC, 0x90)
PROLOGUE = b"\x55\x8b\xec"
FLOAT_SUFFIXES = ("ss", "sd")


class Image:
    """A PE mapped at its preferred base, with the tables feature extraction needs."""

    def __init__(self, path):
        pe = pefile.PE(path, fast_load=True)
        pe.parse_data_directories(directories=[
            pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]])
        self.base = pe.OPTIONAL_HEADER.ImageBase
        self.data = bytes(pe.get_memory_mapped_image())
        self.end = self.base + len(self.data)
        self.sections = {}
        for section in pe.sections:
            name = section.Name.rstrip(b"\0").decode("latin-1")
            start = self.base + section.VirtualAddress
            self.sections.setdefault(name, (start, start + section.Misc_VirtualSize))
        self.text = self.sections[".text"]
        self.rdata = self.sections[".rdata"]
        self.data_sections = [self.rdata] + ([self.sections[".data"]] if ".data" in self.sections else [])
        self.imports = self._imports(pe)
        reloc = pe.OPTIONAL_HEADER.DATA_DIRECTORY[5]
        self.relocs = self._relocs(reloc.VirtualAddress, reloc.Size) if reloc.Size else []

    @staticmethod
    def _imports(pe):
        imports = {}
        for entry in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
            dll = entry.dll.decode("latin-1").lower()
            for imp in entry.imports:
                imports[imp.address] = imp.name.decode("latin-1") if imp.name else f"{dll}#{imp.ordinal}"
        return imports

    def _relocs(self, rva, size):
        """VAs of every HIGHLOW fixup, sorted."""
        sites = []
        pos, stop = rva, rva + size
        while pos < stop:
            page, block = struct.unpack_from("<II", self.data, pos)
            if block < 8:
                break
            for (entry,) in struct.iter_unpack("<H", self.data[pos + 8:pos + block]):
                if entry >> 12 == 3:
                    sites.append(self.base + page + (entry & 0xFFF))
            pos += block
        return sorted(sites)

    @staticmethod
    def contains(va, span):
        return span[0] <= va < span[1]

    def in_data(self, va):
        return any(lo <= va < hi for lo, hi in self.data_sections)

    def dword(self, va):
        return struct.unpack_from("<I", self.data, va - self.base)[0]

    def string_at(self, va):
        """The ASCII or UTF-16LE string at va, or None."""
        if not self.in_data(va):
            return None
        offset = va - self.base
        raw = self.data[offset:offset + MAX_STRING]
        end = raw.find(b"\0")
        if end >= MIN_STRING and all(b in PRINTABLE for b in raw[:end]):
            return raw[:end].decode("latin-1")
        if end == 1:
            return self._utf16_at(raw)
        return None

    @staticmethod
    def _utf16_at(raw):
        chars = []
        for low, high in zip(raw[0::2], raw[1::2]):
            if high == 0 and low == 0:
                break
            if high != 0 or low not in PRINTABLE:
                return None
            chars.append(chr(low))
        return "".join(chars) if len(chars) >= MIN_STRING else None


def float32_repr(raw):
    """Shortest decimal that round-trips the float32 bit pattern raw (bytes)."""
    value = struct.unpack("<f", raw)[0]
    if math.isfinite(value):
        for digits in range(1, 10):
            text = f"{value:.{digits}g}"
            if abs(float(text)) <= 3.4028234663852886e38 and struct.pack("<f", float(text)) == raw:
                return repr(float(text))
    return repr(value)


def plain_float32(raw):
    """float32_repr(raw) if the bits read as an ordinary float literal, else None."""
    value = struct.unpack("<f", raw)[0]
    if not math.isfinite(value) or not 1e-4 <= abs(value) <= 1e7:
        return None
    text = float32_repr(raw)
    digits = text.lstrip("-").replace(".", "").lstrip("0").rstrip("0").split("e")[0]
    return text if len(digits) <= 4 else None


# ---------------------------------------------------------------- boundaries

def ghidra_boundaries(image, path):
    """[(start, end)] from a Ghidra rva,size,name CSV."""
    with open(path, newline="") as handle:
        rows = csv.DictReader(handle)
        spans = {image.base + int(r["rva"], 16): int(r["size"]) for r in rows}
    return [(va, va + size) for va, size in sorted(spans.items())]


def find_ilt(image):
    """{thunk_va: target} for the incremental-link jump table at the start of .text."""
    pos = image.text[0]
    while image.data[pos - image.base] in PADDING:
        pos += 1
    thunks = {}
    while image.data[pos - image.base] == 0xE9:
        thunks[pos] = pos + 5 + struct.unpack_from("<i", image.data, pos - image.base + 1)[0]
        pos += 5
    return thunks if len(thunks) >= 16 else {}


def resolve(ilt, va):
    """Follow ILT thunks to the real body."""
    for _ in range(4):
        if va not in ilt:
            break
        va = ilt[va]
    return va


def static_starts(image, ilt):
    """Function starts visible without disassembly (needs .reloc)."""
    if not image.relocs:
        sys.exit("no .reloc directory: pass --boundaries")
    return set(ilt.values()) | reloc_code_targets(image, ilt) | prologue_starts(image)


def derived_boundaries(image, ilt, starts):
    """[(start, end)]: each start runs to the next, minus trailing int3 padding."""
    ilt_span = (min(ilt), max(ilt) + 5) if ilt else (0, 0)
    ordered = sorted(s for s in starts
                     if image.contains(s, image.text) and not ilt_span[0] <= s < ilt_span[1])
    ends = ordered[1:] + [image.text[1]]
    return [(start, trim_padding(image, start, end)) for start, end in zip(ordered, ends)]


def reloc_code_targets(image, ilt):
    """Code addresses the image relocates, minus jump-table entries and table bases."""
    text = image.text
    in_text = {}
    targets = set()
    for site in image.relocs:
        value = image.dword(site)
        if not image.contains(value, text):
            continue
        if image.contains(site, text):
            in_text[site] = value
        else:
            targets.add(resolve(ilt, value))
    for site, value in in_text.items():
        in_table = site - 4 in in_text or site + 4 in in_text
        if not in_table and value not in in_text:
            targets.add(resolve(ilt, value))
    return targets


def prologue_starts(image):
    """`push ebp; mov ebp, esp` preceded by padding or a return."""
    lo, hi = image.text[0] - image.base, image.text[1] - image.base
    starts = set()
    pos = image.data.find(PROLOGUE, lo, hi)
    while pos != -1:
        before = image.data[pos - 1]
        if before in PADDING or before == 0xC3 or image.data[pos - 3] == 0xC2:
            starts.add(image.base + pos)
        pos = image.data.find(PROLOGUE, pos + 1, hi)
    return starts


def trim_padding(image, start, end):
    while end > start + 1 and image.data[end - 1 - image.base] == 0xCC:
        end -= 1
    return end


# ------------------------------------------------------------- disassembly

class Context:
    """Read-only state shared with worker processes (inherited through fork)."""

    def __init__(self, image, ilt, wb_names):
        self.image = image
        self.ilt = ilt
        self.wb_names = wb_names
        self.import_thunks = {}
        self.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    def find_import_thunks(self, starts):
        """Functions that are a lone `jmp [IAT]`."""
        for start in starts:
            offset = start - self.image.base
            if self.image.data[offset:offset + 2] == b"\xff\x25":
                slot = struct.unpack_from("<I", self.image.data, offset + 2)[0]
                if slot in self.image.imports:
                    self.import_thunks[start] = self.image.imports[slot]

    def import_at_target(self, va):
        return self.import_thunks.get(resolve(self.ilt, va))


CTX = None


def instructions(ctx, start, end, tables):
    """disasm_lite tuples over [start, end), skipping the data ranges in tables.

    tables ({start: end}) may grow while iterating; decoding restarts so a
    table discovered from its `jmp [reg*4 + table]` is never decoded as code.
    """
    data, base = ctx.image.data, ctx.image.base
    pos = start
    while pos < end:
        if pos in tables:
            pos = max(pos + 1, tables[pos])
            continue
        stop = min([t for t in tables if t > pos] + [end])
        known = len(tables)
        resume = None
        for insn in ctx.md.disasm_lite(data[pos - base:stop - base], pos):
            yield insn
            resume = insn[0] + insn[1]
            if len(tables) != known:
                break
        if resume is None or (resume < stop and len(tables) == known):
            resume = (resume or pos) + 1  # undecodable byte
        pos = resume


def note_table(image, start, end, mnemonic, operands, tables):
    """Record a switch table that lives inside the function."""
    jump = JUMP_TABLE_RE.match(operands) if mnemonic == "jmp" else None
    if jump:
        table = int(jump.group(1), 16)
        if start <= table < end:
            stop = table
            while stop + 4 <= end and start <= image.dword(stop) < end:
                stop += 4
            tables[table] = max(stop, table + 4)
        return
    index = INDEX_TABLE_RE.match(operands) if mnemonic == "movzx" else None
    if index:
        table = int(index.group(1), 16)
        if start <= table < end and table not in tables:
            tables[table] = min([t for t in tables if t > table] + [end])


class Features:
    """Accumulates one function's record while its instructions stream past."""

    def __init__(self, start, end):
        self.start, self.end = start, end
        self.strings = []
        self.string_set = set()
        self.names = Counter()
        self.files, self.lines = [], []
        self.name_files = {}
        self.hidden = set()
        self.imports = []
        self.calls = []
        self.icalls = 0
        self.consts = []
        self.refs = set()
        self.nbytes = 0
        self.recent = []  # trailing run of pushes: (operands, string or None)

    def add_unique(self, items, value):
        if value not in items:
            items.append(value)

    def record(self):
        return {
            "va": self.start, "size": self.end - self.start,
            "names": [n for n, _ in sorted(self.names.items(), key=lambda kv: (-kv[1], kv[0]))],
            "files": self.files, "lines": self.lines,
            "name_files": [[n, f] for n, f in self.name_files.items()],
            "strings": [s for s in self.strings if s not in self.hidden],
            "imports": self.imports, "calls": self.calls, "icalls": self.icalls,
            "consts": self.consts, "vt": [], "rtti": [], "nbytes": self.nbytes,
        }


def scan_function(span):
    """(record, .rdata addresses taken, starts exposed) for one function.

    The exposed starts are call targets and code that follows a return or
    jump and int3 padding; derived boundaries feed them back.
    """
    ctx, image = CTX, CTX.image
    start, end = span
    feats = Features(start, end)
    tables = {}
    exposed = set()
    padding = False  # inside int3 padding that follows a ret/jmp
    previous = None
    for address, size, mnemonic, operands in instructions(ctx, start, end, tables):
        if mnemonic == "int3":
            padding = padding or previous in ("ret", "jmp")
        elif padding:
            exposed.add(address)
            padding = False
        previous = mnemonic
        feats.nbytes += size
        note_table(image, start, end, mnemonic, operands, tables)
        string = None
        if mnemonic == "call" or mnemonic == "jmp":
            scan_branch(ctx, feats, mnemonic, operands)
        elif "0x" in operands:
            string = scan_operands(ctx, feats, mnemonic, operands)
        if ctx.wb_names:
            track_assert(feats, mnemonic, operands, string)
    exposed.update(feats.calls)
    return feats.record(), feats.refs, exposed


def scan_branch(ctx, feats, mnemonic, operands):
    image = ctx.image
    absolute = ABS_MEM_RE.search(operands)
    if absolute:
        name = image.imports.get(int(absolute.group(1), 16))
        if name:
            feats.add_unique(feats.imports, name)
        elif mnemonic == "call":
            feats.icalls += 1
        return
    if not operands.startswith("0x"):
        if mnemonic == "call":
            feats.icalls += 1
        return
    target = int(operands, 16)
    name = ctx.import_at_target(target)
    if name:
        feats.add_unique(feats.imports, name)
    elif mnemonic == "call" and image.contains(target, image.text):
        feats.calls.append(resolve(ctx.ilt, target))


def scan_operands(ctx, feats, mnemonic, operands):
    """Strings, import refs and constants in a non-branch instruction.

    Returns the string an immediate operand points at (for the assert shape).
    """
    image = ctx.image
    found = None
    for operand in operands.split(", "):
        if "[" in operand:
            absolute = ABS_MEM_RE.search(operand)
            if absolute:
                scan_memory(image, feats, mnemonic, operand, int(absolute.group(1), 16))
            continue
        if not OPERAND_HEX_RE.fullmatch(operand):
            continue
        value = int(operand, 16)
        if image.base <= value < image.end:
            string = image.string_at(value)
            if string is not None:
                found = string
                if string not in feats.string_set:
                    feats.string_set.add(string)
                    feats.strings.append(string)
            if image.contains(value, image.rdata):
                feats.refs.add(value)
        elif value < 0xFFFF0000:
            raw = struct.pack("<I", value)
            feats.add_unique(feats.consts, plain_float32(raw) or f"0x{value:x}")
    return found


def scan_memory(image, feats, mnemonic, operand, address):
    name = image.imports.get(address)
    if name:
        feats.add_unique(feats.imports, name)
        return
    if not image.contains(address, image.rdata):
        return
    floating = mnemonic.startswith("f") or mnemonic.endswith(FLOAT_SUFFIXES)
    if not floating:
        return
    offset = address - image.base
    if operand.startswith("dword"):
        feats.add_unique(feats.consts, float32_repr(image.data[offset:offset + 4]))
    elif operand.startswith("qword"):
        feats.add_unique(feats.consts, repr(struct.unpack_from("<d", image.data, offset)[0]))


def track_assert(feats, mnemonic, operands, string):
    """Harvest names, files and lines from WB's name pushes and assert shape.

    Any Class::method string an instruction takes is a name. The assert shape
    (push cond; push name; push line; push file) also yields bare names, and
    only its three strings are hidden from `strings`: a path or name used
    elsewhere (allocation macros, Apt callbacks) survives into retail too.
    """
    if string is not None and NAME_RE.match(string):
        feats.names[string] += 1
    if mnemonic != "push":
        feats.recent = []
        return
    feats.recent = (feats.recent + [(operands, string)])[-4:]
    if string is None or not FILE_RE.search(string):
        return
    feats.add_unique(feats.files, string)
    pushes = feats.recent[:-1]
    line = pushes[-1][0] if pushes else ""
    if not LINE_RE.fullmatch(line):
        return
    feats.add_unique(feats.lines, int(line, 0))
    name = pushes[-2][1] if len(pushes) >= 2 else None
    if name is None or not (NAME_RE.match(name) or BARE_NAME_RE.match(name)):
        return
    if not NAME_RE.match(name):
        feats.names[name] += 1
    feats.name_files.setdefault(name, string)
    condition = pushes[-3][1] if len(pushes) >= 3 else None
    feats.hidden.update(s for s in (condition, name, string) if s is not None)


# ------------------------------------------------------------------ vtables

def code_pointer_slots(image, ilt, starts):
    """{slot_va: function_va} for aligned .rdata dwords pointing at a start.

    starts includes import thunks (a vtable's _purecall slot) so they do not
    split the run; images without .reloc accept any dword equal to a start.
    """
    lo, hi = image.rdata
    reloc_sites = set(image.relocs) if image.relocs else None
    slots = {}
    offset = (lo + 3 & ~3) - image.base
    for index, (value,) in enumerate(struct.iter_unpack("<I", image.data[offset:hi - image.base & ~3])):
        site = image.base + offset + 4 * index
        if reloc_sites is not None and site not in reloc_sites:
            continue
        target = resolve(ilt, value)
        if target in starts:
            slots[site] = target
    return slots


def vtables(slots, refs):
    """[(vtable_va, [function_va, ...])]: slot runs split at code-referenced addresses.

    A lone slot nobody references is an EH unwind or handler entry, not a vtable.
    """
    runs = []
    for site in sorted(slots):
        if site - 4 in slots and site not in refs:
            runs[-1][1].append(slots[site])
        else:
            runs.append((site, [slots[site]]))
    return [(start, functions) for start, functions in runs if len(functions) > 1 or start in refs]


def rtti_name(image, vtable):
    """Class name from the CompleteObjectLocator before the vtable, if present."""
    locator = image.dword(vtable - 4)
    if not image.contains(locator, image.rdata) or image.dword(locator) != 0:
        return None
    descriptor = image.dword(locator + 12)
    if not image.base <= descriptor < image.end - 8:
        return None
    name = image.string_at(descriptor + 8)
    return name if name and name.startswith((".?AV", ".?AU")) else None


def attach_vtables(image, ilt, records, refs, import_thunks):
    """Fill each record's vt and rtti from the vtables found in .rdata."""
    by_va = {r["va"]: r for r in records}
    slots = code_pointer_slots(image, ilt, by_va.keys() | import_thunks.keys())
    for vtable, functions in vtables(slots, refs):
        rtti = rtti_name(image, vtable)
        for slot, va in enumerate(functions):
            record = by_va.get(va)
            if record is None:
                continue
            record["vt"].append([vtable, slot])
            if rtti and rtti not in record["rtti"]:
                record["rtti"].append(rtti)


# -------------------------------------------------------- WB debug macros

DEBUG_WRAPPER_SIZE = 48   # an out-of-line debug-object call is at most this long
DEBUG_SAMPLE = 400        # assert-bearing functions sampled to find the debug object
MACRO_SPAN = 600          # bytes a debug macro's skip target may lie past its first call
SLOT_CALL_RE = re.compile(r"^dword ptr \[(?:e[a-d]x|e[sd]i)(?: \+ 0x[0-9a-f]+)?\]$")
CONDITIONAL_RE = re.compile(r"^j(?!mp)")


def body(ctx, record):
    """Decoded (address, size, mnemonic, operands) of one record's span."""
    start = record["va"]
    end = start + record["size"]
    tables = {}
    insns = []
    for insn in instructions(ctx, start, end, tables):
        note_table(ctx.image, start, end, insn[2], insn[3], tables)
        insns.append(insn)
    return insns


def debug_global(ctx, records):
    """VA of the global most often loaded into ecx right before a vtable call
    in functions that push source paths: WB's debug object."""
    votes = Counter()
    for record in [r for r in records if r["files"]][:DEBUG_SAMPLE]:
        previous = None
        for insn in body(ctx, record):
            if insn[2] == "call" and SLOT_CALL_RE.match(insn[3]) and previous \
                    and previous[3].startswith("ecx, dword ptr [0x"):
                votes[previous[3][len("ecx, dword ptr ["):-1]] += 1
            previous = insn
    return votes.most_common(1)[0][0] if votes else None


def is_debug_wrapper(insns, load):
    """A tiny body that loads the debug object and calls or jumps to a slot."""
    loads = any(operands == load for _, _, _, operands in insns)
    branches = [operands for _, _, mnemonic, operands in insns if mnemonic in ("call", "jmp")]
    return loads and bool(branches) and bool(SLOT_CALL_RE.match(branches[0]))


def macro_calls(ctx, insns, load, wrappers):
    """Direct call targets inside debug macros, duplicates kept.

    A macro starts at a call to a debug wrapper or an inline debug-object
    slot call, and runs to the target of the first forward conditional jump
    after it (the macro's skip target), or just that call when there is none.
    """
    calls, end, previous = [], 0, None
    for i, (address, _, mnemonic, operands) in enumerate(insns):
        target = int(operands, 16) if mnemonic == "call" and operands.startswith("0x") else None
        if target is not None:
            target = resolve(ctx.ilt, target)
        starts = target in wrappers or (
            mnemonic == "call" and SLOT_CALL_RE.match(operands) and previous == load)
        if starts and address >= end:
            end = skip_target(insns, i, address)
        if target is not None and (address < end or target in wrappers) \
                and ctx.image.contains(target, ctx.image.text):
            calls.append(target)
        previous = operands
    return calls


def skip_target(insns, i, address):
    """End of the macro whose first debug call is insns[i]."""
    for _, _, mnemonic, operands in insns[i + 1:]:
        if CONDITIONAL_RE.match(mnemonic) and operands.startswith("0x"):
            target = int(operands, 16)
            if address < target <= address + MACRO_SPAN:
                return target
    return address + 1


def mark_debug(ctx, records):
    """Fill WB records' debug and debug_calls from the debug object's uses."""
    for record in records:
        record["debug"], record["debug_calls"] = False, []
    global_va = debug_global(ctx, records)
    if global_va is None:
        return
    load = f"ecx, dword ptr [{global_va}]"
    wrappers = set()
    for record in records:
        if record["size"] <= DEBUG_WRAPPER_SIZE and is_debug_wrapper(body(ctx, record), load):
            record["debug"] = True
            wrappers.add(record["va"])
    for record in records:
        if record["files"] or wrappers.intersection(record["calls"]):
            record["debug_calls"] = macro_calls(ctx, body(ctx, record), load, wrappers)


# --------------------------------------------------------------------- main

def extract(path, boundaries=None, wb_names=False, jobs=4, augment=False):
    """Feature records for every function of the PE at path, sorted by VA."""
    global CTX
    image = Image(path)
    ilt = find_ilt(image)
    CTX = Context(image, ilt, wb_names)
    if boundaries and augment:
        results = scan_augmented(image, ghidra_boundaries(image, boundaries), jobs)
    elif boundaries:
        results = scan_all(ghidra_boundaries(image, boundaries), jobs)
    else:
        results = scan_derived(image, ilt, jobs)
    records = [record for record, _, _ in results]
    refs = set().union(*(r for _, r, _ in results))
    attach_vtables(image, ilt, records, refs, CTX.import_thunks)
    if wb_names:
        mark_debug(CTX, records)
    return records


def scan_all(spans, jobs):
    """scan_function over every span that is not an import thunk."""
    CTX.find_import_thunks(start for start, _ in spans)
    spans = [s for s in spans if s[0] not in CTX.import_thunks]
    with multiprocessing.get_context("fork").Pool(jobs) as pool:
        return pool.map(scan_function, spans, chunksize=256)


def scan_derived(image, ilt, jobs, rounds=4):
    """Scan, then rescan with the starts disassembly exposed, to a fixpoint.

    Calls into a span and code after a return and int3 padding are starts the
    static rules miss (frameless library code, CRT assembly).
    """
    starts = static_starts(image, ilt)
    for _ in range(rounds):
        results = scan_all(derived_boundaries(image, ilt, starts), jobs)
        found = set().union(*(f for _, _, f in results))
        found = {va for va in found if image.contains(va, image.text)} - starts
        if not found:
            break
        starts |= found
    return results


class Gaps:
    """.text bytes outside every listed function body and outside int3 padding."""

    def __init__(self, image, spans):
        self.image = image
        self.starts = [start for start, _ in spans]
        self.ends = [end for _, end in spans]

    def __contains__(self, va):
        image = self.image
        if not image.contains(va, image.text) or image.data[va - image.base] == 0xCC:
            return False
        index = bisect.bisect_right(self.starts, va) - 1
        return index < 0 or va >= self.ends[index]


def vtable_gap_targets(image, gaps, known):
    """Gap addresses held by .rdata slots next to a slot that holds a known start."""
    lo, hi = image.rdata
    offset = (lo + 3 & ~3) - image.base
    words = [w for (w,) in struct.iter_unpack("<I", image.data[offset:hi - image.base & ~3])]
    candidates = [i for i, word in enumerate(words) if word not in known and word in gaps]
    known = set(known)
    found = set()
    while True:
        added = {words[i] for i in candidates
                 if words[i] not in known
                 and ((i > 0 and words[i - 1] in known)
                      or (i + 1 < len(words) and words[i + 1] in known))}
        if not added:
            return found
        found |= added
        known |= added


def augmented_spans(image, listed, starts):
    """Listed spans unchanged; each added start runs to the next start."""
    listed_end = dict(listed)
    ordered = sorted(starts)
    ends = ordered[1:] + [image.text[1]]
    return [(start, listed_end.get(start) or trim_padding(image, start, end))
            for start, end in zip(ordered, ends)]


def scan_augmented(image, listed, jobs, rounds=4):
    """Scan the listed functions plus the gap code they and their vtables reach."""
    gaps = Gaps(image, listed)
    starts = {start for start, _ in listed}
    spans = listed
    for _ in range(rounds):
        results = scan_all(spans, jobs)
        calls = set().union(*(f for _, _, f in results))
        found = {va for va in calls if va in gaps}
        found |= vtable_gap_targets(image, gaps, starts | CTX.import_thunks.keys())
        found -= starts
        if not found:
            break
        starts |= found
        spans = augmented_spans(image, listed, starts)
    return results


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("pe")
    parser.add_argument("--out", required=True)
    parser.add_argument("--boundaries", help="Ghidra rva,size,name CSV (default: derive from .reloc)")
    parser.add_argument("--augment-starts", action="store_true",
                        help="with --boundaries: add vtable and call targets the list misses")
    parser.add_argument("--wb-names", action="store_true", help="harvest WorldBuilder assert names")
    parser.add_argument("--jobs", type=int, default=4)
    args = parser.parse_args(argv)
    began = time.time()
    if args.augment_starts and not args.boundaries:
        parser.error("--augment-starts needs --boundaries")
    records = extract(args.pe, args.boundaries, args.wb_names, args.jobs, args.augment_starts)
    with open(args.out, "w") as handle:
        for record in records:
            handle.write(json.dumps(record, separators=(",", ":")) + "\n")
    print(f"{len(records)} functions -> {args.out} in {time.time() - began:.0f}s")


if __name__ == "__main__":
    main()
