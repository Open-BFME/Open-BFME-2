#!/usr/bin/env python3
"""Show the WorldBuilder (debug) body of a game.dat function, for RE agents.

worldbuilder.exe is an unoptimised internal build of the source tree game.dat
was compiled from, so its body of a function reads far closer to the C++ than
retail's optimised one. Given a game.dat function, this prints the WB body
that tools/wb_match.py paired with it, annotated so an agent can write C++
from it:

  * each assertion / debug-message macro collapses to one line,
        ASSERT(<condition>) "<message>"  @MathCoord3D.h:374
        DEBUG("Unknown ScriptAction type %d")  @ScriptActions.cpp:12265
    hiding the guard, the debug-object vtable call and the message stream;
    the inline condition code before an ASSERT is folded in when it provably
    feeds nothing but the assertion
  * call targets are named: a WB name unique to the callee, else its
    game.dat counterpart ("-> gd 0x00XXXXXX <ledger name>"), else the
    import, else sub_<va>; incremental-link thunks are resolved
  * string immediates show their literal, .rdata float loads their value
  * [ebp-x] / [ebp+x] read local_x / arg_n; once `mov [ebp-x], ecx` saves
    `this`, that slot reads `this` and members read [this->+0xNN]

A callee table then maps every WB callee to its game.dat match (rva, ledger
name, REAL/PARTIAL/PLACEHOLDER or unrowed), or flags a small unmatched one as
probably inlined in retail. --gd adds retail's own body with its calls named
from the ledger.

    python3 tools/wb_show.py <target> [--gd] [--raw] [--max-lines N]

<target> is a game.dat RVA or VA (rva:0x... / va:0x... force one reading; a
bare number below the 0x400000 image base is an RVA, and one above it is read
as the RVA a function starts at when it is not also a function-start VA, since
ledger RVAs run past 0x400000), a
ledger symbol (mangled or demangled), a WB name ("Class::method"), or
wb:0x... for the WB function containing that WB address.

Inputs: build/wb/{wb,gd}_functions.jsonl (tools/pe_features.py),
build/wb/matches_full.jsonl (tools/wb_match.py) and reverse/functions.csv,
indexed into build/wb/show_index.pkl and re-indexed whenever one changes. A
WB pairing is identity evidence only; nothing here proves a byte match.
"""
import argparse
import bisect
import collections
import functools
import json
import os
import pickle
import re
import struct
import sys
from pathlib import Path

import pe_features as pf
import wb_data
import wb_gold

ROOT = Path(__file__).resolve().parent.parent
FILES = ROOT / "baselines" / "bfme2" / "workshop-vanilla-1.06" / "files"
WB_EXE = FILES / "worldbuilder.exe"
GD_EXE = FILES / "game.dat"
WB_DIR = ROOT / "build" / "wb"
# Unpacked from the committed reverse/wb/ archives when missing (tools/wb_data.py).
WB_JSONL = wb_data.ensure("wb_functions.jsonl")
GD_JSONL = wb_data.ensure("gd_functions.jsonl")
MATCHES = wb_data.ensure("matches_full.jsonl")
INDEX = WB_DIR / "show_index.pkl"
INPUTS = (WB_EXE, GD_EXE, WB_JSONL, GD_JSONL, MATCHES, wb_gold.FUNCTIONS_CSV)
INDEX_VERSION = 4
IMAGE_BASE = wb_gold.IMAGE_BASE

GUARD_SLOT = 0x60                           # debug object: "is this site ignored?"
MESSAGE_SLOTS = {0x64: 4, 0x68: 1, 0x6C: 3}  # slot -> pushes (cond, name, line, file)
ASSERT_SLOT = 0x64
FILE_ONLY_SLOT = 0x68
STREAM_END_SLOTS = {0x44, 0x48, 0x4C}        # message stream: "end of message"
ENABLED_SLOT = 0x70                         # "is debug output on for this file?"
FORMATTER_IMPORTS = {"_vsnprintf", "vsprintf", "_vsnwprintf", "vsnprintf"}
SMALL = 96              # an unmatched WB callee this small was probably inlined
CONDITION_WINDOW = 80   # instructions an ASSERT's condition code may span
WRAPPER_SIZE = 48       # an out-of-line debug-object call is at most this long
GUARD_WINDOW = 150      # instructions between a guard and its message call
CALLEE_ROWS = 150

SLOT_CALL_RE = re.compile(r"^dword ptr \[(e[a-d]x|e[sd]i)(?: \+ (0x[0-9a-f]+|\d+))?\]$")
EBP_RE = re.compile(r"(?:(?:byte|word|dword|qword|tbyte) ptr )?\[ebp ([-+]) (0x[0-9a-f]+|\d+)\]")
THIS_STORE_RE = re.compile(r"^dword ptr \[ebp - (?:0x[0-9a-f]+|\d+)\], ecx$")
LOCAL_RE = re.compile(r"\[ebp - (?:0x[0-9a-f]+|\d+)\]")
REG_MEM_RE = re.compile(r"\[(e[a-d]x|e[sd]i)(?: \+ (0x[0-9a-f]+|\d+))?\]")
HEX_RE = re.compile(r"0x[0-9a-f]{5,}")
RESULT_RE = re.compile(r"\b(?:al|ax|eax)\b")
REGISTERS = {alias: full for full, aliases in {
    "eax": ("eax", "ax", "al", "ah"), "ebx": ("ebx", "bx", "bl", "bh"),
    "ecx": ("ecx", "cx", "cl", "ch"), "edx": ("edx", "dx", "dl", "dh"),
    "esi": ("esi", "si"), "edi": ("edi", "di")}.items() for alias in aliases}
NON_WRITING = {"cmp", "test", "push", "call", "ret", "bt"}
CALL_CLOBBERS = {"eax", "ecx", "edx"}


# ------------------------------------------------------------------- index

def load_index():
    """The cached lookup index, rebuilt when any input changed."""
    stamp = [INDEX_VERSION] + [os.stat(p).st_mtime_ns for p in INPUTS]
    if INDEX.exists():
        with open(INDEX, "rb") as fh:
            index = pickle.load(fh)
        if index["stamp"] == stamp:
            return index
    print("wb_show: indexing inputs (once per input change) ...", file=sys.stderr)
    index = build_index()
    index["stamp"] = stamp
    INDEX.parent.mkdir(parents=True, exist_ok=True)
    with open(INDEX, "wb") as fh:
        pickle.dump(index, fh, protocol=pickle.HIGHEST_PROTOCOL)
    return index


def build_index():
    wb = read_functions(WB_JSONL, ("size", "names", "files", "lines", "imports"))
    gd = read_functions(GD_JSONL, ("size",))
    spread = collections.Counter(n for rec in wb.values() for n in set(rec["names"]))
    wb_by_name = collections.defaultdict(list)
    for va, rec in wb.items():
        for name in rec["names"]:
            wb_by_name[name].append(va)
    by_gd, by_wb = collections.defaultdict(list), collections.defaultdict(list)
    with open(MATCHES) as fh:
        for match in map(json.loads, fh):
            by_gd[match["gd_va"]].append(match)
            by_wb[match["wb_va"]].append(match["gd_va"])
    return {
        "wb": {va: (r["size"], r["names"], r["files"], r["lines"]) for va, r in wb.items()},
        "wb_starts": sorted(wb),
        "gd": {va: r["size"] for va, r in gd.items()},
        "gd_starts": sorted(gd),
        "spread": dict(spread),
        "wb_by_name": dict(wb_by_name),
        "by_gd": dict(by_gd),
        "by_wb": dict(by_wb),
        **read_ledger(),
        "formatters": {va for va, r in wb.items()
                       if r["size"] <= SMALL and FORMATTER_IMPORTS & set(r["imports"])},
        **debug_object(pf.Image(WB_EXE), wb),
    }


def read_functions(path, fields):
    with open(path) as fh:
        return {r["va"]: {f: r[f] for f in fields} for r in map(json.loads, fh)}


def read_ledger():
    """{"ledger": {rva: [(symbol, display, kind)]}, "ledger_names": {name: {rva}}}."""
    rows = collections.defaultdict(list)
    names = collections.defaultdict(set)
    for row in wb_gold.ledger_rows():
        rva = int(row["target_rva"], 16)
        display, kind = describe(row["name"], row["source"])
        rows[rva].append((row["name"], display, kind))
        names[row["name"]].add(rva)
        names[display].add(rva)
    return {"ledger": dict(rows), "ledger_names": dict(names)}


def describe(symbol, source):
    """(demangled name, REAL/PARTIAL/PLACEHOLDER) for a ledger symbol."""
    try:
        info = wb_gold.describe(symbol, source)
    except wb_gold.DemangleError:
        info = None
    if info is None:
        return symbol, wb_gold.classify("", symbol, source)
    return info["name"], info["kind"]


def debug_object(image, wb, sample=400):
    """{"debug_global": VA of the global holding WB's debug object,
        "debug_wrappers": {va: slot} for tiny functions that only call a slot,
        "debug_flags": {va} of tiny functions that only read the object}.

    The global is the one most often loaded into ecx right before a vtable
    call in functions that push source paths. Some files reach the object
    through out-of-line wrappers (mov ecx, [global]; jmp [eax + slot]), and
    some macros first test a flag of it (mov eax, [global]; mov al, [eax+n]).
    """
    md = pf.Context(image, {}, False).md
    votes = collections.Counter()
    for va in [va for va, r in wb.items() if r["files"]][:sample]:
        previous = None
        for insn in disassemble(md, image, va, wb[va]["size"]):
            if (insn[2] == "call" and SLOT_CALL_RE.match(insn[3]) and previous
                    and previous[3].startswith("ecx, dword ptr [0x")):
                votes[int(previous[3][len("ecx, dword ptr ["):-1], 16)] += 1
            previous = insn
    if not votes:
        return {"debug_global": None, "debug_wrappers": {}, "debug_flags": set()}
    debug_va = votes.most_common(1)[0][0]
    load, global_ref = f"ecx, dword ptr [{debug_va:#x}]", f"[{debug_va:#x}]"
    wrappers, flags = {}, set()
    for va, rec in wb.items():
        if rec["size"] > WRAPPER_SIZE:
            continue
        insns = list(disassemble(md, image, va, rec["size"]))
        if not any(insn[3].endswith(global_ref) for insn in insns):
            continue
        slots = [SLOT_CALL_RE.match(o) for _, _, m, o in insns if m in ("call", "jmp")]
        if any(o == load for _, _, _, o in insns) and slots and slots[0]:
            wrappers[va] = int(slots[0].group(2) or "0", 0)
        elif not slots:
            flags.add(va)
    return {"debug_global": debug_va, "debug_wrappers": wrappers, "debug_flags": flags}


def disassemble(md, image, va, size):
    offset = va - image.base
    return md.disasm_lite(image.data[offset:offset + size], va)


# ---------------------------------------------------------------- binaries

class Binary:
    """One image with its incremental-link table."""

    def __init__(self, path):
        self.image = pf.Image(path)
        self.ilt = pf.find_ilt(self.image)
        self.ctx = pf.Context(self.image, self.ilt, False)

    @staticmethod
    @functools.lru_cache(maxsize=None)
    def load(path):
        return Binary(path)

    def body(self, start, end):
        return Body(self, start, end)

    def import_operand(self, operands):
        absolute = pf.ABS_MEM_RE.search(operands)
        return self.image.imports.get(int(absolute.group(1), 16)) if absolute else None

    def call_target(self, operands):
        """Import name, or thunk-resolved branch target VA, or None (indirect)."""
        imported = self.import_operand(operands)
        if imported or not operands.startswith("0x"):
            return imported
        va = pf.resolve(self.ilt, int(operands, 16))
        offset = va - self.image.base
        if self.image.data[offset:offset + 2] == b"\xff\x25":     # jmp [IAT]
            return self.image.imports.get(self.image.dword(va + 2)) or va
        return va

    def string(self, text):
        """The string at hex address text (pe_features' rules), or None."""
        value = int(text, 16)
        return self.image.string_at(value) if self.image.base <= value < self.image.end else None

    def short_string(self, text):
        """Like string(), but also 1-3 character ASCII (an assert's "0")."""
        found = self.string(text)
        value = int(text, 16)
        if found is not None or not self.image.in_data(value):
            return found
        raw = self.image.data[value - self.image.base:value - self.image.base + pf.MIN_STRING]
        end = raw.find(b"\0")
        return raw[:end].decode("latin-1") if end > 0 and set(raw[:end]) <= pf.PRINTABLE else None

    def value_notes(self, mnemonic, operands):
        """Comments for the strings, floats and imports an instruction names."""
        notes = []
        imported = self.import_operand(operands)
        if imported:
            notes.append(imported)
        floating = mnemonic.startswith("f") or mnemonic.endswith(pf.FLOAT_SUFFIXES)
        for text in HEX_RE.findall(operands):
            string = self.string(text)
            if string is not None:
                notes.append(quote(string))
            elif f"[{text}]" in operands and self.image.contains(int(text, 16), self.image.rdata):
                notes.extend(self.rdata_value(int(text, 16), operands, floating))
        return notes

    def rdata_value(self, va, operands, floating):
        offset = va - self.image.base
        if "qword ptr" in operands:
            return [repr(struct.unpack_from("<d", self.image.data, offset)[0])] if floating else []
        raw = self.image.data[offset:offset + 4]
        if floating:
            return [pf.float32_repr(raw) + "f"]
        plain = pf.plain_float32(raw)
        return [plain + "f?"] if plain else []


class Body:
    """A decoded function: instructions, switch tables and branch targets."""

    def __init__(self, binary, start, end):
        self.binary, self.start, self.end = binary, start, end
        self.tables = {}
        self.insns = []
        for insn in pf.instructions(binary.ctx, start, end, self.tables):
            pf.note_table(binary.image, start, end, insn[2], insn[3], self.tables)
            self.insns.append(insn)
        self.addresses = [insn[0] for insn in self.insns]
        self.sources = self._branch_sources()

    def _branch_sources(self):
        """{target: [source addresses]} for branches and switch tables inside."""
        sources = collections.defaultdict(list)
        for address, _, mnemonic, operands in self.insns:
            if mnemonic.startswith("j") and operands.startswith("0x"):
                target = int(operands, 16)
                if self.start <= target < self.end:
                    sources[target].append(address)
        for table, stop in self.tables.items():
            for slot in range(table, stop - 3, 4):
                target = self.binary.image.dword(slot)
                if self.start <= target < self.end:
                    sources[target].append(table)
        return sources

    def index_of(self, address):
        return bisect.bisect_left(self.addresses, address)


def quote(text, limit=90):
    return json.dumps(text if len(text) <= limit else text[:limit] + "...")


def basename(path):
    return re.split(r"[\\/]", path)[-1] if path else ""


# ----------------------------------------------------------------- naming

class Namer:
    """Names WB and game.dat functions from the index."""

    def __init__(self, index):
        self.index = index

    def ledger(self, va):
        return self.index["ledger"].get(va - IMAGE_BASE, [])

    def ledger_label(self, va):
        rows = self.ledger(va)
        if not rows:
            return "unrowed"
        more = f" (+{len(rows) - 1} folded)" if len(rows) > 1 else ""
        return f"{rows[0][1]} [{rows[0][2]}]{more}"

    def gd_for_wb(self, va):
        return self.index["by_wb"].get(va, [])

    def wb_unique(self, va):
        rec = self.index["wb"].get(va)
        return next((n for n in (rec[1] if rec else ()) if self.index["spread"].get(n) == 1), None)

    def match(self, gd_va, wb_va):
        return next((m for m in self.index["by_gd"].get(gd_va, ()) if m["wb_va"] == wb_va), None)

    def wb_name(self, va):
        for gd_va in self.gd_for_wb(va):
            match = self.match(gd_va, va)
            if match and match.get("wb_name"):
                return match["wb_name"]
        rec = self.index["wb"].get(va)
        return self.wb_unique(va) or (rec[1][0] if rec and rec[1] else None)

    def wb_callee(self, va):
        """Label for a WB call target."""
        unique = self.wb_unique(va)
        if unique:
            return unique
        gd_vas = self.gd_for_wb(va)
        if gd_vas:
            return f"-> gd 0x{gd_vas[0] - IMAGE_BASE:08X} {self.ledger_label(gd_vas[0])}"
        return f"sub_{va:x}"

    def gd_callee(self, va):
        """Label for a game.dat call target: ledger name, plus WB's name for it."""
        label = self.ledger_label(va) if self.ledger(va) else f"sub_{va - IMAGE_BASE:08X}"
        matches = self.index["by_gd"].get(va)
        best = max(matches, key=lambda m: m["score"]) if matches else None
        if best and best.get("wb_name"):
            label += f" (WB {best['wb_name']})"
        return label


# ------------------------------------------------------------ debug sites

class Site:
    """Instructions [first, last] (addresses) shown as one line of text."""

    def __init__(self, first, last, text):
        self.first, self.last, self.text = first, last, text


def debug_calls(body, index):
    """{instruction index: (slot, setup)} for every call on the debug object.

    setup is how many instructions before the call load the object (3 for
    the inline `mov r, [g]; mov eax, [r]; mov ecx, [g]`, 0 via a wrapper).
    """
    debug_va = index["debug_global"]
    if debug_va is None:
        return {}
    load = f"ecx, dword ptr [{debug_va:#x}]"
    calls = {}
    for i, (_, _, mnemonic, operands) in enumerate(body.insns):
        if mnemonic != "call":
            continue
        match = SLOT_CALL_RE.match(operands)
        if match and i >= 3 and body.insns[i - 1][3] == load:
            calls[i] = (int(match.group(2) or "0", 0), 3)
        elif not match and (slot := index["debug_wrappers"].get(body.binary.call_target(operands))) is not None:
            calls[i] = (slot, 0)
    return calls


def find_sites(body, frame, index, namer):
    """Debug macro sites of a WB body, in address order, never overlapping."""
    calls = debug_calls(body, index)
    sites = []
    for i, (slot, _) in sorted(calls.items()):
        if slot in MESSAGE_SLOTS:
            site = message_site(body, i, slot, calls, frame, index, namer)
        elif slot == ENABLED_SLOT:
            site = enabled_site(body, i)
        else:
            continue
        if site and not (sites and site.first <= sites[-1].last):
            sites.append(site)
    return sites


def pushes_before(body, i, count):
    """[(index, operand, string)] for the count pushes feeding insns[i]."""
    pushes = []
    j = i - 1
    while j >= 0 and len(pushes) < count and i - j <= count + 6:
        _, _, mnemonic, operand = body.insns[j]
        if mnemonic == "push":
            string = body.binary.short_string(operand) if HEX_RE.fullmatch(operand) else None
            pushes.append((j, operand, string))
        j -= 1
    return pushes[::-1] if len(pushes) == count else None


def guard_before(insns, i, calls):
    """(first guard instruction index, skip target or None) for message call i.

    A guard without a skip branch belongs to a macro that always reports.
    """
    for j in range(i - 1, max(-1, i - GUARD_WINDOW), -1):
        slot, setup = calls.get(j, (None, 0))
        if slot in MESSAGE_SLOTS:
            return None
        if slot == GUARD_SLOT:
            jumps = [k for k in range(j + 1, min(j + 4, len(insns)))
                     if insns[k][2] == "jne" and insns[k][3].startswith("0x")]
            return j - setup, (int(insns[jumps[0]][3], 16) if jumps else None)
    return None


def message_site(body, i, slot, calls, frame, index, namer):
    """ASSERT / DEBUG site whose debug-object call is insns[i]."""
    insns = body.insns
    pushes = pushes_before(body, i, MESSAGE_SLOTS[slot])
    if pushes is None:
        return None
    first, last, plumbing = pushes[0][0], stream_end(body, i), set()
    guard = guard_before(insns, i, calls)
    if guard:
        first, end = guard
        if end is not None:
            last = body.index_of(end) - 1
            if not i <= last < len(insns):
                return None
        check = ignore_check(insns, first, end)
        if check is not None:
            plumbing.add(body.binary.call_target(insns[check + 1][3]))
            first = check
        if slot == ASSERT_SLOT and end is not None:
            first = condition_start(body, first, last, frame)
    first = flag_check(body, first, last, index)
    called = {body.binary.call_target(insns[k][3]) for k in range(first, last + 1)
              if insns[k][2] == "call"} - {None} - plumbing - index["formatters"]
    called -= index["debug_wrappers"].keys()
    text = message_text(body, first, last, slot, pushes) + calls_note(called, namer)
    return Site(insns[first][0], insns[last][0], text)


def ignore_check(insns, first, end):
    """Start of `push n; call X; add esp, 4` (+ `movzx; test; jne end`) before first."""
    k = first - 6 if end is not None else first - 3
    shape = [insn[2] for insn in insns[max(k, 0):first]]
    if k < 0 or shape[:3] != ["push", "call", "add"]:
        return None
    if end is not None and (shape[3:] != ["movzx", "test", "jne"] or insns[first - 1][3] != f"{end:#x}"):
        return None
    return k


def flag_check(body, first, last, index):
    """Fold a preceding `call <debug flag>; movzx; test; j* past the macro`."""
    insns = body.insns
    end = insns[last][0] + insns[last][1]
    k = first - 4
    if k < 0 or [insn[2] for insn in insns[k:first - 1]] != ["call", "movzx", "test"]:
        return first
    if body.binary.call_target(insns[k][3]) not in index["debug_flags"]:
        return first
    target = insns[first - 1][3]
    return k if target.startswith("0x") and int(target, 16) == end else first


def stream_end(body, i):
    """Index of the call ending the message stream after debug call i, else i.

    Used when no guard branch marks the macro's end: the last stream call
    (slot 0x44/0x48/0x4c) within reach, provided no branch in between leaves.
    """
    insns = body.insns
    for j in range(i + 1, min(i + GUARD_WINDOW, len(insns))):
        match = SLOT_CALL_RE.match(insns[j][3]) if insns[j][2] == "call" else None
        if match and int(match.group(2) or "0", 0) in STREAM_END_SLOTS:
            low, high = insns[i][0], insns[j][0] + insns[j][1]
            branches = [insn for insn in insns[i:j] if insn[2].startswith("j")]
            inside = all(b[3].startswith("0x") and low <= int(b[3], 16) <= high for b in branches)
            return j if inside else i
        if insns[j][2] == "ret":
            break
    return i


def message_text(body, first, last, slot, pushes):
    location = ""
    if pushes[-1][2]:
        location = "  @" + basename(pushes[-1][2])
        if slot != FILE_ONLY_SLOT and pf.LINE_RE.fullmatch(pushes[-2][1]):
            location += f":{int(pushes[-2][1], 0)}"
    hidden = {p[2] for p in pushes if p[2]}
    parts = []
    for k in range(first, last + 1):
        for text in HEX_RE.findall(body.insns[k][3]):
            string = body.binary.string(text)
            if string is not None and string not in hidden:
                parts.append(quote(string))
    message = " ".join(dict.fromkeys(parts))
    if slot == ASSERT_SLOT:
        condition = pushes[0][2] if pushes[0][2] is not None else f"<cond {pushes[0][1]}>"
        return f"ASSERT({condition}) {message}".rstrip() + location
    return f"DEBUG({message}){location}"


def calls_note(called, namer):
    names = [c if isinstance(c, str) else namer.wb_callee(c) for c in called]
    return f"  [calls: {', '.join(sorted(names))}]" if names else ""


def enabled_site(body, i):
    """push file; ...; call [debug+0x70]; movzx; test; je X -> one line."""
    insns = body.insns
    pushes = pushes_before(body, i, 1)
    if pushes is None or i + 3 >= len(insns) or insns[i + 3][2] != "je":
        return None
    target = int(insns[i + 3][3], 16)
    text = f"if (!DEBUG_ENABLED) goto L_{target:x}   ; debug-only block  @{basename(pushes[0][2])}"
    return Site(insns[pushes[0][0]][0], insns[i + 3][0], text)


def condition_start(body, first, last, frame):
    """Earliest index from which an ASSERT's inline condition code can fold.

    Walks back from the guard while the code only computes the condition (it
    must end in a branch to the macro's end): no stores but to temporaries
    dead after the macro, no call whose result goes unused, no branch past
    the macro; then shrinks the run until nothing enters its middle from
    outside and nothing in it jumps below its start.
    """
    insns = body.insns
    end = insns[last][0] + insns[last][1]
    jump = insns[first - 1] if first else None
    if (not jump or not jump[2].startswith("j") or jump[2] == "jmp"
            or jump[3] != f"{end:#x}" or insns[first][0] in body.sources):
        return first
    lowest = max(frame.body_index, first - CONDITION_WINDOW)
    live = frame.locals_live_after(last)
    p, has_call = first, False
    while p - 1 >= lowest and folds(insns, p - 1, end, live, has_call):
        has_call = has_call or insns[p - 1][2] == "call"
        p -= 1
    return settle(body, p, first, end)


def folds(insns, k, end, live, has_call):
    _, _, mnemonic, operands = insns[k]
    if mnemonic in ("ret", "leave") or mnemonic.startswith("rep"):
        return False
    if mnemonic.startswith("j"):
        return operands.startswith("0x") and int(operands, 16) <= end
    if mnemonic == "call":
        return uses_result(insns, k + 1)
    if mnemonic == "push":
        return has_call
    destination = operands.split(", ")[0]
    if "[" not in destination or mnemonic in ("cmp", "test") \
            or mnemonic.startswith(("fld", "fild", "fcom", "fucom")):
        return True
    if "[esp" in destination:
        return has_call
    local = LOCAL_RE.search(destination)
    return bool(local) and local.group(0) not in live


def uses_result(insns, k):
    """Does the code after a call (past `add esp, n`) read its result?"""
    while k < len(insns) and insns[k][2] == "add" and insns[k][3].startswith("esp"):
        k += 1
    return k < len(insns) and RESULT_RE.search(insns[k][3].split(", ", 1)[-1]) is not None


def settle(body, p, first, end):
    """Raise p until [p, end) is entered only at p and never jumps below p."""
    while p < first:
        low = body.insns[p][0]
        bad = None
        for k in range(p, first):
            address, _, mnemonic, operands = body.insns[k]
            if k > p and any(not low <= s < end for s in body.sources.get(address, ())):
                bad = k
            elif mnemonic.startswith("j") and int(operands, 16) < low:
                bad = k + 1
            if bad is not None:
                break
        if bad is None:
            return p
        p = bad
    return first


# ------------------------------------------------------------ frame / this

class Frame:
    """ebp-frame facts of a WB body: where code starts, which slot holds this."""

    def __init__(self, insns):
        self.this_slot = None
        self.body_index = 0
        self.local_refs = collections.defaultdict(list)
        for k, insn in enumerate(insns):
            for local in LOCAL_RE.findall(insn[3]):
                self.local_refs[local].append(k)
        self._prologue(insns[:24])

    def _prologue(self, insns):
        for k, (_, _, mnemonic, operands) in enumerate(insns):
            if operands == "ebp, esp" or operands.startswith("esp, "):
                self.body_index = k + 1
            if mnemonic == "mov" and THIS_STORE_RE.match(operands):
                self.this_slot = operands[:-len(", ecx")]
                self.body_index = k + 1
                return
            if writes(mnemonic, operands) == "ecx" and mnemonic != "pop":
                return

    def locals_live_after(self, last):
        return {local for local, refs in self.local_refs.items() if refs[-1] > last}


def writes(mnemonic, operands):
    """The full register an instruction overwrites, or None."""
    if mnemonic in NON_WRITING or mnemonic.startswith(("j", "f")):
        return None
    return REGISTERS.get(operands.split(", ")[0])


class ThisTracker:
    """Rewrites ebp slots and this-relative accesses in WB operands."""

    def __init__(self, frame):
        self.slot = frame.this_slot
        self.regs = {"ecx"} if self.slot else set()

    def at_label(self):
        self.regs.clear()

    def rewrite(self, mnemonic, operands):
        """Operands with locals/args/this named; then track the instruction."""
        text = EBP_RE.sub(self._ebp, operands)
        if self.regs:
            text = REG_MEM_RE.sub(self._member, text)
        self.track(mnemonic, operands)
        return text

    def track(self, mnemonic, operands):
        if mnemonic == "call":
            self.regs -= CALL_CLOBBERS
            return
        target = writes(mnemonic, operands)
        if target is None:
            return
        source = operands.split(", ")[-1]
        if mnemonic == "mov" and (source == self.slot or source in self.regs):
            self.regs.add(target)
        else:
            self.regs.discard(target)

    def _ebp(self, match):
        if match.group(0) == self.slot:
            return "this"
        offset = int(match.group(2), 0)
        if match.group(1) == "-":
            name = f"local_{offset:x}"
        elif offset >= 8:
            name = f"arg_{(offset - 8) // 4}"
        else:
            return match.group(0)
        return match.group(0).split("[")[0] + f"[{name}]"

    def _member(self, match):
        if match.group(1) not in self.regs:
            return match.group(0)
        return f"[this->+{int(match.group(2) or '0', 0):#x}]"


# --------------------------------------------------------------- rendering

def render_body(out, body, name_call, max_lines, frame=None, sites=()):
    """Append body's annotated disassembly to out, at most max_lines lines."""
    tracker = ThisTracker(frame) if frame else None
    site_at = {s.first: s for s in sites}
    skip_until, expected, budget = -1, body.start, max_lines
    for address, size, mnemonic, operands in body.insns:
        if budget <= 0:
            out.append(f"  ... truncated at {address:#x}, {body.end - address} bytes more "
                       f"(raise --max-lines)")
            return
        if expected < address:
            out.append(f"  {expected:x}  <{address - expected} bytes of switch-table data>")
        expected = address + size
        if address <= skip_until:
            continue
        if address in body.sources:
            out.append(f"L_{address:x}:")
            if tracker:
                tracker.at_label()
        site = site_at.get(address)
        if site:
            out.append(f"  {address:x}  {site.text}")
            skip_until = site.last
        else:
            out.append(render_insn(body, address, mnemonic, operands, name_call, tracker))
        budget -= 1


def render_insn(body, address, mnemonic, operands, name_call, tracker):
    text, notes = operands, []
    branch = mnemonic == "call" or mnemonic.startswith("j")
    target = body.binary.call_target(operands) if branch else None
    if isinstance(target, str):
        notes.append(target)
    elif target is not None and target in body.sources:
        text = f"L_{target:x}"
    elif target is not None:
        notes.append(name_call(target))
    else:
        notes = body.binary.value_notes(mnemonic, operands)
        if tracker:
            text = tracker.rewrite(mnemonic, operands)
    if tracker and target is not None:
        tracker.track(mnemonic, operands)
    comment = f"  ; {', '.join(notes)}" if notes else ""
    return f"  {address:x}  {mnemonic} {text}".rstrip() + comment


# ------------------------------------------------------------- callee table

def callee_counts(body, sites):
    """{callee va or import name: [calls, calls inside debug sites]}, first-use order."""
    counts = {}
    for address, _, mnemonic, operands in body.insns:
        if mnemonic != "call":
            continue
        callee = body.binary.call_target(operands)
        if callee is not None:
            entry = counts.setdefault(callee, [0, 0])
            entry[0] += 1
            entry[1] += any(s.first <= address <= s.last for s in sites)
    return counts


def callee_table(out, body, namer, sites):
    counts = callee_counts(body, sites)
    rows = [(c, n) for c, (n, in_debug) in counts.items() if in_debug < n]
    debug_only = [c for c, (n, in_debug) in counts.items() if in_debug == n]
    out.append(f"callees ({len(rows)} distinct outside debug macros; WB callee -> game.dat):")
    for callee, calls in rows[:CALLEE_ROWS]:
        out.append("  " + callee_row(namer, callee, calls))
    if len(rows) > CALLEE_ROWS:
        out.append(f"  ... {len(rows) - CALLEE_ROWS} more callees not shown")
    if debug_only:
        names = [c if isinstance(c, str) else namer.wb_callee(c) for c in debug_only]
        out.append(f"  callees only inside debug macros (normally compiled out of retail): {', '.join(names)}")


def callee_row(namer, callee, calls):
    if isinstance(callee, str):
        return f"{calls:>3}x import {callee}"
    rec = namer.index["wb"].get(callee)
    size = rec[0] if rec else 0
    name = namer.wb_unique(callee) or (rec[1][0] + "?" if rec and rec[1] else "?")
    head = f"{calls:>3}x wb {callee:#x} {name} ({size or '?'}b)"
    gd_vas = namer.gd_for_wb(callee)
    if gd_vas:
        return head + "  -> gd " + "; ".join(
            f"0x{va - IMAGE_BASE:08X} {namer.ledger_label(va)}" for va in gd_vas[:3])
    if size and size <= SMALL:
        return head + "  -> unmatched: inlined in retail?"
    return head + "  -> unmatched"


# ------------------------------------------------------------------ report

def header(out, namer, gd_va, wb_va):
    index = namer.index
    if gd_va is not None:
        out.append(f"game.dat rva 0x{gd_va - IMAGE_BASE:08X} (va {gd_va:#x}) size {index['gd'].get(gd_va, 0)}")
        rows = namer.ledger(gd_va)
        out.extend(f"  ledger: {display} [{kind}]  {symbol}" for symbol, display, kind in rows[:6])
        if not rows:
            out.append("  ledger: unrowed")
    if wb_va is None:
        out.append("WB: no WB match")
        return
    size, names, files, lines = index["wb"][wb_va]
    out.append(f"WB va {wb_va:#x} size {size}  {namer.wb_name(wb_va) or '(unnamed)'}")
    if files:
        out.append(f"  file {files[0]}" + (f" (+{len(files) - 1} more)" if len(files) > 1 else ""))
    if lines:
        out.append(f"  assert lines {min(lines)}..{max(lines)}")
    if len(names) > 1:
        out.append(f"  names pushed: {', '.join(names[:8])}")
    match = namer.match(gd_va, wb_va) if gd_va is not None else None
    if match:
        out.append(f"  match score {match['score']} evidence {','.join(match['evidence'])}")
    elif gd_va is None:
        out.append("  game.dat: no match")


def report(index, gd_va, wb_va, args):
    namer = Namer(index)
    out = []
    header(out, namer, gd_va, wb_va)
    if wb_va is not None:
        wb = Binary.load(WB_EXE)
        body = wb.body(wb_va, wb_va + index["wb"][wb_va][0])
        frame = Frame(body.insns)
        sites = find_sites(body, frame, index, namer)
        out.append("")
        out.append("WB body (local_x = [ebp-x], arg_n = [ebp+8+4n]):")
        render_body(out, body, namer.wb_callee, args.max_lines, frame, [] if args.raw else sites)
        out.append("")
        callee_table(out, body, namer, sites)
    if args.gd and gd_va is not None:
        gd = Binary.load(GD_EXE)
        out.append("")
        out.append("game.dat body:")
        render_body(out, gd.body(gd_va, gd_va + index["gd"][gd_va]), namer.gd_callee, args.max_lines)
    return "\n".join(out)


# ----------------------------------------------------------------- targets

def containing(starts, size_of, va):
    k = bisect.bisect_right(starts, va) - 1
    return starts[k] if k >= 0 and va < starts[k] + max(size_of(starts[k]), 1) else None


def gd_containing(index, va):
    return containing(index["gd_starts"], index["gd"].__getitem__, va)


def wb_for_gd(index, gd_va):
    matches = sorted(index["by_gd"].get(gd_va, ()), key=lambda m: -m["score"])
    return matches[0]["wb_va"] if matches else None


def resolve_target(index, text):
    """(gd_va or None, wb_va or None, note) for a command-line target."""
    if text.lower().startswith("wb:"):
        wb_va = containing(index["wb_starts"], lambda v: index["wb"][v][0], int(text[3:], 16))
        if wb_va is None:
            sys.exit(f"no WB function contains {text[3:]}")
        gd_vas = index["by_wb"].get(wb_va, [])
        return (gd_vas[0] if gd_vas else None), wb_va, ""
    forced = re.fullmatch(r"(rva|va):((?:0x)?[0-9a-fA-F]+)", text, re.I)
    if forced or re.fullmatch(r"(0x)?[0-9a-fA-F]+", text):
        value = int(forced.group(2) if forced else text, 16)
        note = ""
        if forced:
            va = value + IMAGE_BASE if forced.group(1).lower() == "rva" else value
        elif value < IMAGE_BASE:
            va = value + IMAGE_BASE
        else:
            # Ledger RVAs run past 0x400000, so a bare number there reads both
            # ways. A function that STARTS at it as an RVA wins over a VA that
            # only lands inside some function; when both start a function, the
            # VA reading stands and the note says how to get the other.
            as_rva = value + IMAGE_BASE
            rva_start, va_start = as_rva in index["gd"], value in index["gd"]
            va = as_rva if rva_start and not va_start else value
            if rva_start and va_start:
                note = f"read as a VA; rva:{text} shows the function at RVA {text}"
            elif va == as_rva:
                note = f"read as an RVA (a function starts at VA 0x{as_rva:x}); va:{text} forces the VA"
        gd_va = gd_containing(index, va)
        if gd_va is None:
            sys.exit(f"no game.dat function contains {text}")
        return gd_va, wb_for_gd(index, gd_va), note
    rvas = sorted(index["ledger_names"].get(text, ()))
    if rvas:
        gd_va = gd_containing(index, rvas[0] + IMAGE_BASE) or rvas[0] + IMAGE_BASE
        note = "also rowed at " + ", ".join(f"0x{r:08X}" for r in rvas[1:]) if len(rvas) > 1 else ""
        return gd_va, wb_for_gd(index, gd_va), note
    return resolve_wb_name(index, text)


def resolve_wb_name(index, name):
    wb_vas = index["wb_by_name"].get(name)
    if not wb_vas:
        sys.exit(f"{name!r}: not an address, ledger name or WB name")
    by_wb = index["by_wb"]
    ranked = sorted(wb_vas, key=lambda v: (v not in by_wb, index["wb"][v][1][0] != name))
    note = f"{len(ranked) - 1} other WB functions push this name" if len(ranked) > 1 else ""
    gd_vas = by_wb.get(ranked[0], [])
    return (gd_vas[0] if gd_vas else None), ranked[0], note


def main(argv=None):
    parser = argparse.ArgumentParser(
        description=__doc__.split("\n\n")[0],
        formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("target", help="game.dat rva/va, ledger or WB name, or wb:0xVA")
    parser.add_argument("--gd", action="store_true", help="also show the game.dat body")
    parser.add_argument("--raw", action="store_true", help="do not collapse debug macros")
    parser.add_argument("--max-lines", type=int, default=400, help="per body (default 400)")
    args = parser.parse_args(argv)
    index = load_index()
    gd_va, wb_va, note = resolve_target(index, args.target)
    if note:
        print(f"note: {note}")
    print(report(index, gd_va, wb_va, args))


if __name__ == "__main__":
    main()
