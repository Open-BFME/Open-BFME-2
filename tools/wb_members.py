#!/usr/bin/env python3
"""Harvest class member names and byte offsets from WorldBuilder's assertions.

BFME 2's worldbuilder.exe is an unoptimised internal build of the game's
source tree. Its assert macro evaluates the condition and then pushes the
condition text, the enclosing "Class::method", the line and the source path:

    <condition code> ; push 0 ; call <ignored?> ; ... jne skip
    push "m_template != NULL" ; push "Thing::foo" ; push <line> ; push <file>

Debug code spills `this` to a frame slot at entry (`mov [ebp-x], ecx`) and
reloads it before every member access, so each reference the condition makes
to a member of `this` shows up as one reload followed by `[reg + disp]`.
Pairing the m_ tokens of the condition text with those displacements gives
member names at byte offsets, as evidence for class-layout reconciliation.

Pairing is conservative. The condition code runs back from the assert gate
to the nearest statement boundary (a label reached from outside, a ret/jmp,
or the `this` spill). A pair is kept only when:

  * the code makes no more calls than the text does (no leaked statement);
  * the reloads of `this` that touch memory equal the member references in
    the text, one displacement each; vtable fetches for virtual calls on
    `this` are not member accesses;
  * with several distinct members, the condition has no calls or
    arithmetic and the reloads dereference in load order (a call, pointer
    scaling or an x87 compare can evaluate the right operand first), and
    names map to offsets one-to-one;
  * no offset is folded: `m_pos.x` and `m_a[CONST]` are refused, `m_x[i]`
    needs an indexed access and `m_x.f()` an address taken for the call
    (an inlined f reads some field inside m_x);
  * the assert's "Class::method" is carried by at most MAX_SPREAD functions,
    so an inline body expanded into another class's method is not credited
    to that method's `this`.

A method reached only through a secondary-base vtable receives `this` at
that base's subobject. The subobject offset comes from the constructors'
`mov [reg + d], vtable` stores, and offsets are shifted to the full object;
methods whose vtables disagree are skipped, as is any function left with a
negative offset.

`obj->m_x` / `obj.m_x` (a member of some other object) pairs the same way
against a pointer reloaded from another frame slot, only when it is the
condition's sole reference and no calls are made; its class is written "?".

Asserting accessors (Class::getFoo / isFoo / setFoo whose code outside the
assert is a single `this`-relative load or store) give kind=accessor rows
with the member written as the accessor's stem ("Foo"); these are weaker.

Function boundaries and names come from pe_features.py's WB output:

  python3 tools/pe_features.py <worldbuilder.exe> --wb-names \\
      --out build/wb/wb_functions.jsonl
  python3 tools/wb_members.py [--zh-check 10]

Output: build/wb/wb_members.csv, one row per (class, member, kind, offset);
`conflict` lists the member's other offsets for that kind. The report goes
to stdout and build/wb/wb_members_report.txt. --zh-check N compares the N
classes with the most assert members against Zero Hour and BFME 1 headers:
whether each name is declared in that class and whether offset order
follows declaration order, plus the same totals over every class found.
"""
import argparse
import csv
import json
import re
import sys
from collections import Counter, defaultdict
from dataclasses import dataclass, field
from pathlib import Path

import pe_features as pf

ROOT = Path(__file__).resolve().parents[1]
WB_EXE = ROOT / "baselines/bfme2/workshop-vanilla-1.06/files/worldbuilder.exe"
FUNCTIONS = ROOT / "build/wb/wb_functions.jsonl"
OUT_DIR = ROOT / "build/wb"
ZH_CODE = ROOT / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
BFME1_GAME = ROOT / "reference/open-bfme-1/game"

MAX_SPREAD = 2       # functions that may carry one assert name before it counts as inlined
GATE_WINDOW = 16     # instructions between the gate's `push 0; call` and the condition push
SPILL_WINDOW = 32    # prologue instructions searched for the `this` spill
ACCESSOR_BODY = 8    # instructions an accessor may have outside prologue, epilogue and asserts

REGISTERS = {
    "eax": "eax", "ax": "eax", "al": "eax", "ah": "eax",
    "ebx": "ebx", "bx": "ebx", "bl": "ebx", "bh": "ebx",
    "ecx": "ecx", "cx": "ecx", "cl": "ecx", "ch": "ecx",
    "edx": "edx", "dx": "edx", "dl": "edx", "dh": "edx",
    "esi": "esi", "si": "esi", "edi": "edi", "di": "edi",
}
CALL_CLOBBERS = ("eax", "ecx", "edx")
NON_WRITING = {"cmp", "test", "push", "call", "jmp", "ret", "fld", "fild", "fcomp", "fcom",
               "fcompp", "fucomp", "fucompp", "fst", "fstp", "fistp", "nop"}
FPU_STORES = {"fst", "fstp", "fist", "fistp"}
EPILOGUE = {"pop", "ret", "leave"}
MEM_RE = re.compile(r"(?:(byte|word|dword|qword|tbyte) ptr )?\[([^\]]*)\]")
TERM_RE = re.compile(r"([+-])?\s*([\w*]+)")
FPU_SIZES = {"dword": "float", "qword": "double", "tbyte": "ldouble"}

REF_RE = re.compile(r"""
      \bthis\s*->\s*(?P<tmember>\w+)
    | \(\s*\*\s*this\s*\)\s*\.\s*(?P<smember>\w+)
    | (?P<qualifier>[\w\]\)]+)\s*(?P<sep>->|\.)\s*(?P<fmember>m_\w+)
    | (?<![\w.>])(?P<member>m_\w+)
    """, re.X)
CALL_TEXT_RE = re.compile(r"\b(?!sizeof\b|if\b|while\b)[A-Za-z_]\w*\s*\(")
LOGIC_RE = re.compile(r"&&|\|\||->|[<>!=]=|(?<![<>])[<>](?![<>])")
ARITHMETIC_RE = re.compile(r"[-+*/%&|^~]|<<|>>")
ACCESSOR_RE = re.compile(r"^(?P<kind>get|is|set)(?P<stem>[A-Z]\w*)$")


# ------------------------------------------------------------ instructions

@dataclass
class Mem:
    size: str
    base: str
    index: str
    disp: int


def parse_mem(operand):
    """The memory operand in capstone's text, or None."""
    match = MEM_RE.search(operand)
    if not match:
        return None
    base, index, disp = "", "", 0
    for sign, term in TERM_RE.findall(match.group(2)):
        if "*" in term:
            index = term.split("*")[0]
        elif term in REGISTERS or term in ("ebp", "esp"):
            base = term
        else:
            value = int(term, 0)
            disp += -value if sign == "-" else value
    return Mem(match.group(1) or "", base, index, disp)


def operands_of(text):
    return text.split(", ") if text else []


def register(operand):
    return REGISTERS.get(operand)


def written_registers(mnemonic, ops):
    """Full registers the instruction overwrites."""
    if mnemonic == "call":
        return set(CALL_CLOBBERS)
    if mnemonic == "cdq":
        return {"edx"}
    if mnemonic.startswith("rep"):
        return {"ecx", "edi", "esi"}
    if mnemonic in NON_WRITING or mnemonic.startswith("j") or not ops:
        return set()
    written = {register(ops[0])} - {None}
    if mnemonic == "xchg" and len(ops) == 2:
        written |= {register(ops[1])} - {None}
    return written


def disassemble(ctx, va, size):
    """[(address, size, mnemonic, operands)] for one function, skipping jump tables."""
    tables = {}
    insns = []
    for insn in pf.instructions(ctx, va, va + size, tables):
        pf.note_table(ctx.image, va, va + size, insn[2], insn[3], tables)
        insns.append(insn)
    return insns


def branch_sources(insns):
    """{target address: [source addresses]} for direct jumps."""
    sources = defaultdict(list)
    for address, _, mnemonic, operands in insns:
        if mnemonic.startswith("j") and operands.startswith("0x"):
            sources[int(operands, 16)].append(address)
    return sources


def this_slot(insns):
    """(slot displacement, index after the spill) of `mov [ebp - x], ecx`, or None."""
    saved = False
    for index, (_, _, mnemonic, operands) in enumerate(insns[:SPILL_WINDOW]):
        ops = operands_of(operands)
        if mnemonic == "mov" and len(ops) == 2 and ops[1] == "ecx":
            mem = parse_mem(ops[0])
            if mem and mem.base == "ebp" and not mem.index and mem.size == "dword":
                return mem.disp, index + 1
        if mnemonic == "push" and operands == "ecx":
            saved = True
        elif mnemonic == "pop" and operands == "ecx":
            saved = False
        elif "ecx" in written_registers(mnemonic, ops) and not saved:
            return None
    return None


# ------------------------------------------------------------ this tracking

@dataclass
class Access:
    disp: int
    size: str
    store: bool
    indexed: bool = False
    vptr: bool = False
    seq: int = 0     # position among all accesses the tracker saw


@dataclass
class Load:
    """One reload of a frame slot into a register, and what it dereferenced."""
    slot: int
    accesses: list = field(default_factory=list)

    def members(self):
        return [a for a in self.accesses if not a.vptr]


def access_size(mnemonic, mem):
    if mnemonic == "lea":
        return "addr"
    if mnemonic.startswith("f") and mem.size in FPU_SIZES:
        return FPU_SIZES[mem.size]
    return mem.size or "?"


class Tracker:
    """Follows registers reloaded from frame slots through straight-line code."""

    def __init__(self):
        self.loads = []
        self.held = {}   # register -> Load
        self.vptrs = {}  # register -> Access that read [this]
        self.calls = 0
        self.other_memory = 0  # accesses through neither a frame slot nor a reload
        self.accesses = 0

    def step(self, mnemonic, operands):
        ops = operands_of(operands)
        mem = next((m for m in map(parse_mem, ops) if m), None)
        dest = register(ops[0]) if ops else None
        if mnemonic == "call":
            self.calls += 1
            if mem and mem.base in self.vptrs:
                self.vptrs[mem.base].vptr = True
        loaded = self._reload(mnemonic, dest, mem)
        access = None
        if not loaded and mem and mem.base in self.held:
            access = self._access(mnemonic, ops, mem)
        elif mem and not loaded and mem.base != "ebp":
            self.other_memory += 1
        elif mnemonic in ("add", "sub") and dest in self.held and ops[1][0].isdigit():
            disp = int(ops[1], 0)
            self._record(dest, Access(disp if mnemonic == "add" else -disp, "addr", False))
        copied = self.held.get(register(ops[1])) if mnemonic == "mov" and len(ops) == 2 else None
        for reg in written_registers(mnemonic, ops):
            self.held.pop(reg, None)
            self.vptrs.pop(reg, None)
        if loaded or copied:
            self.held[dest] = loaded or copied
        elif access and mnemonic == "mov" and dest and mem.disp == 0 and mem.size == "dword":
            self.vptrs[dest] = access

    def _reload(self, mnemonic, dest, mem):
        """A Load when the instruction is `mov reg, dword ptr [ebp +/- x]`."""
        if mnemonic != "mov" or not mem or not dest or mem.base != "ebp":
            return None
        if mem.index or mem.size != "dword":
            return None
        load = Load(mem.disp)
        self.loads.append(load)
        return load

    def _access(self, mnemonic, ops, mem):
        writes_first = ops and "[" in ops[0] and mnemonic not in ("cmp", "test", "push", "lea")
        store = writes_first and (not mnemonic.startswith("f") or mnemonic in FPU_STORES)
        return self._record(mem.base, Access(mem.disp, access_size(mnemonic, mem), bool(store),
                                             bool(mem.index)))

    def _record(self, reg, access):
        access.seq = self.accesses
        self.accesses += 1
        self.held[reg].accesses.append(access)
        return access


def track(insns, start, stop):
    tracker = Tracker()
    for _, _, mnemonic, operands in insns[start:stop]:
        tracker.step(mnemonic, operands)
    return tracker


# --------------------------------------------------------------- asserts

@dataclass
class Assert:
    owner: str        # "Class::method"
    condition: str
    start: int        # first instruction of the condition code
    gate: int         # first instruction of the gate (`push 0; call`)
    skip: int         # address the gate jumps to when the assert holds


def pushed_string(image, insn):
    _, _, mnemonic, operands = insn
    if mnemonic != "push" or not operands.startswith("0x"):
        return None
    return image.string_at(int(operands, 16))


def find_gate(insns, push):
    """Index of the gate's `push 0` before the condition push, or None."""
    for g in range(push - 2, max(-1, push - GATE_WINDOW), -1):
        _, _, mnemonic, operands = insns[g]
        nxt = insns[g + 1]
        if mnemonic == "push" and operands == "0" and nxt[2] == "call" and nxt[3].startswith("0x"):
            return g
    return None


def gate_skip(insns, gate, push):
    """Target of the gate's first conditional jump (the assert-holds label)."""
    for _, _, mnemonic, operands in insns[gate:push]:
        if mnemonic.startswith("j") and operands.startswith("0x"):
            return int(operands, 16)
    return None


def condition_start(insns, gate, floor, sources):
    """First instruction of the condition: walk back to a statement boundary."""
    gate_address = insns[gate][0]
    start = gate
    while start > floor:
        if insns[start - 1][2] in ("jmp", "ret"):
            break
        start -= 1
        address = insns[start][0]
        if any(src < address or src >= gate_address for src in sources.get(address, ())):
            break
    return start


def find_asserts(image, insns, floor, sources):
    """Every assert with a condition text and a Class::method owner."""
    found = []
    for i in range(floor, len(insns) - 3):
        condition = pushed_string(image, insns[i])
        owner = condition and pushed_string(image, insns[i + 1])
        if not owner or "::" not in owner or not pf.NAME_RE.match(owner):
            continue
        if insns[i + 2][2] != "push" or not pf.LINE_RE.fullmatch(insns[i + 2][3]):
            continue
        path = pushed_string(image, insns[i + 3])
        gate = find_gate(insns, i) if path and pf.FILE_RE.search(path) else None
        if gate is None or gate <= floor:
            continue
        skip = gate_skip(insns, gate, i)
        start = condition_start(insns, gate, floor, sources)
        found.append(Assert(owner, condition, start, gate, skip))
    return found


# ---------------------------------------------------------- condition text

@dataclass
class Refs:
    members: list     # (name, shape) uses of `this` members in source order
    foreign: list     # (qualifier, name) members of other objects
    unsafe: bool      # a use whose offset is folded or whose order is unknown
    calls: int        # call-like tokens in the text
    simple: bool      # no calls or arithmetic: reloads follow source order


def after_subscripts(text, pos):
    """Position after any [..] subscripts and spaces starting at pos."""
    while True:
        while pos < len(text) and text[pos] == " ":
            pos += 1
        if pos >= len(text) or text[pos] != "[":
            return pos
        depth = 0
        while pos < len(text):
            depth += {"[": 1, "]": -1}.get(text[pos], 0)
            pos += 1
            if depth == 0:
                break


def use_shape(text, start, end):
    """How a member use at text[start:end] is accessed.

    "call" (a method of `this`, not a member), "method" (m_x.f(): only an
    address taken for a call gives the member's offset), "subscript"
    (m_x[i]: only an indexed access does, a constant index is folded),
    "plain", or "unsafe" (m_pos.x folds the field; a subscript naming a
    member reorders the reloads).
    """
    after = after_subscripts(text, end)
    subscript = text[end:after].strip()
    if "m_" in subscript or "this" in subscript:
        return "unsafe"
    if after < len(text) and text[after] == "(":
        return "call"
    field_use = re.match(r"\.\s*\w+\s*(\()?", text[after:])
    if field_use:
        return "method" if field_use.group(1) and not subscript else "unsafe"
    return "subscript" if subscript else "plain"


def parse_refs(text):
    members, foreign, unsafe = [], [], False
    for match in REF_RE.finditer(text):
        shape = use_shape(text, match.start(), match.end())
        if shape == "call":
            continue
        if match.group("fmember"):
            qualifier = match.group("qualifier")
            if re.fullmatch(r"m_\w+", qualifier) and not re.search(r"(->|\.)\s*$", text[:match.start()]):
                members.append((qualifier, "plain"))
                unsafe = unsafe or match.group("sep") == "."  # m_pos.m_x folds the field
            foreign.append((qualifier, match.group("fmember")))
            unsafe = unsafe or shape != "plain"
            continue
        unsafe = unsafe or shape == "unsafe"
        name = match.group("tmember") or match.group("smember") or match.group("member")
        members.append((name, shape))
    calls = len(CALL_TEXT_RE.findall(text))
    simple = not calls and not ARITHMETIC_RE.search(LOGIC_RE.sub(" ", text))
    return Refs(members, foreign, unsafe, calls, simple)


# ---------------------------------------------------------------- pairing

@dataclass
class Pair:
    cls: str
    member: str
    offset: int
    size: str
    kind: str
    function: str
    condition: str


def single_offset(load, shape="plain"):
    """(disp, size) if the load's member accesses fit `shape` at one offset, else None."""
    accesses = load.members()
    if len({a.disp for a in accesses}) != 1:
        return None
    if shape == "method" and any(a.size != "addr" for a in accesses):
        return None
    if any(a.indexed != (shape == "subscript") for a in accesses):
        return None
    sizes = [a.size for a in accesses if a.size != "addr"] or [accesses[0].size]
    return accesses[0].disp, sizes[0]


def pair_members(uses, loads, simple):
    """[(name, disp, size)] pairing member uses with reloads in order, or None.

    Several distinct names pair by order only in a simple condition whose
    reloads dereference in the order they load: a call, arithmetic (pointer
    scaling) or an x87 compare can evaluate the right operand first.
    """
    used = [load for load in loads if load.members()]
    if not uses or len(used) != len(uses):
        return None
    firsts = [load.members()[0].seq for load in used]
    if len({name for name, _ in uses}) > 1 and (not simple or firsts != sorted(firsts)):
        return None
    seen, pairs = {}, []
    for (name, shape), load in zip(uses, used):
        found = single_offset(load, shape)
        if found is None or seen.setdefault(name, found[0]) != found[0]:
            return None
        pairs.append((name, *found))
    if len(set(seen.values())) != len(seen):
        return None
    return list(dict.fromkeys(pairs))


def assert_pairs(item, insns, slot, func_name):
    """Pairs for one assert: this-members, or a sole foreign member."""
    refs = parse_refs(item.condition)
    tracker = track(insns, item.start, item.gate)
    if refs.unsafe or tracker.calls > refs.calls:
        return []
    cls = item.owner.rsplit("::", 1)[0]
    this_loads = [load for load in tracker.loads if load.slot == slot]
    if refs.members:
        found = pair_members(refs.members, this_loads, refs.simple) or []
        return [Pair(cls, n, d, s, "assert", func_name, item.condition) for n, d, s in found]
    other = [load for load in tracker.loads if load.slot != slot and load.members()]
    touches_this = any(load.members() for load in this_loads)
    if len(refs.foreign) != 1 or tracker.calls or touches_this or len(other) != 1:
        return []
    found = single_offset(other[0])
    if found is None:
        return []
    qualifier, name = refs.foreign[0]
    return [Pair("?", name, found[0], found[1], "assert", func_name,
                 f"[{qualifier}] {item.condition}")]


def accessor_pair(owner, asserts, insns, floor, slot, func_name):
    """kind=accessor pair when the body outside its asserts is one this access."""
    cls, method = owner.rsplit("::", 1)
    match = ACCESSOR_RE.match(method)
    if not match:
        return None
    body = outside_asserts(insns, floor, asserts)
    if not body or len(body) > ACCESSOR_BODY:
        return None
    tracker = Tracker()
    for _, _, mnemonic, operands in body:
        tracker.step(mnemonic, operands)
    used = [load for load in tracker.loads if load.slot == slot and load.members()]
    reads_params = any(load.slot > 0 for load in tracker.loads)
    if tracker.calls or tracker.other_memory or len(used) != 1:
        return None
    if reads_params != (match.group("kind") == "set"):
        return None
    found = single_offset(used[0])
    stores = {a.store for a in used[0].members()}
    if found is None or stores != {match.group("kind") == "set"}:
        return None
    return Pair(cls, match.group("stem"), found[0], found[1], "accessor", func_name, "")


def outside_asserts(insns, floor, asserts):
    """Instructions after the prologue that are neither assert code nor epilogue."""
    spans = [(insns[a.start][0], a.skip or insns[a.gate][0]) for a in asserts]
    body = [i for i in insns[floor:] if not any(lo <= i[0] < hi for lo, hi in spans)]
    while body and (body[-1][2] in EPILOGUE or body[-1][3] in ("esp, ebp", "ebp, esp")
                    or body[-1][2] == "int3"):
        body.pop()
    return body


# ------------------------------------------------------------- subobjects

def vtable_offsets(image, vtables):
    """{vtable: offset in the object where constructors store it}.

    Found from relocated `mov dword ptr [reg + d], vtable` (C7 /0). A vtable
    ever stored at 0 is primary; one stored at a single other offset belongs
    to a secondary base; several nonzero offsets leave it unknown (None).
    """
    stored = defaultdict(set)
    for site in image.relocs:
        value = image.dword(site)
        if value in vtables and image.contains(site, image.text):
            disp = vtable_store_disp(image.data, site - image.base)
            if disp is not None:
                stored[value].add(disp)
    return {vt: 0 if 0 in disps else (min(disps) if len(disps) == 1 else None)
            for vt, disps in stored.items()}


def vtable_store_disp(data, imm):
    """Displacement of the C7 /0 store whose imm32 sits at offset imm, or None."""
    for back, mod, width in ((2, 0x00, 0), (3, 0x40, 1), (6, 0x80, 4)):
        op = imm - back
        modrm = data[op + 1]
        if data[op] != 0xC7 or modrm & 0xC0 != mod or modrm & 0x38 or modrm & 7 in (4, 5):
            continue
        return int.from_bytes(data[op + 2:op + 2 + width], "little", signed=True)
    return None


def this_delta(vt, offsets):
    """Where a method's `this` sits in the full object: 0 unless it is only
    reached through a secondary-base vtable, None when that is ambiguous."""
    deltas = {offsets.get(vtable) for vtable, _ in vt}
    if not deltas:
        return 0
    if len(deltas) != 1 or None in deltas:
        return None
    return deltas.pop()


# ---------------------------------------------------------------- harvest

@dataclass
class Function:
    va: int
    size: int
    vt: list


def load_functions(path):
    """(WB functions carrying assert names, names' function counts, all vtables)."""
    functions, spread, vtables = [], Counter(), set()
    with open(path) as handle:
        for line in handle:
            record = json.loads(line)
            vtables.update(vtable for vtable, _ in record["vt"])
            if record["names"]:
                functions.append(Function(record["va"], record["size"], record["vt"]))
                spread.update(record["names"])
    return functions, spread, vtables


def function_pairs(ctx, func, spread, delta):
    """Pairs from one function, offsets relative to the full object."""
    insns = disassemble(ctx, func.va, func.size)
    spill = this_slot(insns)
    if spill is None:
        return []
    slot, floor = spill
    sources = branch_sources(insns)
    asserts = [a for a in find_asserts(ctx.image, insns, floor, sources)
               if spread[a.owner] <= MAX_SPREAD]
    pairs = []
    for item in asserts:
        pairs += assert_pairs(item, insns, slot, f"{item.owner}@{func.va:#x}")
    for owner in dict.fromkeys(a.owner for a in asserts):
        accessor = accessor_pair(owner, asserts, insns, floor, slot, f"{owner}@{func.va:#x}")
        if accessor:
            pairs.append(accessor)
    for pair in pairs:
        if pair.cls != "?":
            pair.offset += delta
    if any(p.offset < 0 for p in pairs if p.cls != "?"):
        return []
    return pairs


def harvest(exe, functions_path):
    image = pf.Image(str(exe))
    ctx = pf.Context(image, {}, False)
    functions, spread, vtables = load_functions(functions_path)
    offsets = vtable_offsets(image, vtables)
    pairs = []
    for func in functions:
        delta = this_delta(func.vt, offsets)
        if delta is not None:
            pairs += function_pairs(ctx, func, spread, delta)
    return pairs


@dataclass
class Row:
    cls: str
    member: str
    offset: int
    size: str
    kind: str
    occurrences: int
    conflict: str
    example_function: str
    example_condition: str


def aggregate(pairs):
    """One Row per (class, member, kind, offset); conflict lists the other offsets."""
    groups = defaultdict(list)
    for pair in pairs:
        groups[(pair.cls, pair.member, pair.kind, pair.offset)].append(pair)
    offsets = defaultdict(set)
    for cls, member, kind, offset in groups:
        offsets[(cls, member, kind)].add(offset)
    rows = []
    for (cls, member, kind, offset), seen in sorted(groups.items()):
        size = Counter(p.size for p in seen).most_common(1)[0][0]
        others = sorted(offsets[(cls, member, kind)] - {offset})
        conflict = "n/a" if cls == "?" else ";".join(f"{o:#x}" for o in others)
        rows.append(Row(cls, member, offset, size, kind, len(seen), conflict,
                        seen[0].function, seen[0].condition))
    return rows


def write_csv(rows, path):
    with open(path, "w", newline="") as handle:
        writer = csv.writer(handle)
        writer.writerow(["class", "member", "offset", "size", "kind", "occurrences", "conflict",
                         "example_function", "example_condition"])
        for r in rows:
            writer.writerow([r.cls, r.member, f"{r.offset:#x}", r.size, r.kind, r.occurrences,
                             r.conflict, r.example_function, r.example_condition])


# ------------------------------------------------------------- ZH check

CLASS_HEAD_RE = re.compile(r"^\s*(?:class|struct)\s+(?:\w+\s+)?(\w+)\s*(?::[^;{]*)?\{", re.M)


def reference_class_bodies(roots):
    """{class name: body text} for classes defined in the roots' headers (longest wins)."""
    bodies = {}
    for header in sorted(h for root in roots for h in root.rglob("*.h")):
        text = header.read_text(errors="replace")
        for match in CLASS_HEAD_RE.finditer(text):
            body = braced_body(text, match.end())
            if len(body) > len(bodies.get(match.group(1), "")):
                bodies[match.group(1)] = body
    return bodies


def braced_body(text, start):
    """text from start (just inside an opening brace) to its matching close."""
    depth = 1
    for pos in range(start, len(text)):
        depth += {"{": 1, "}": -1}.get(text[pos], 0)
        if depth == 0:
            return text[start:pos]
    return text[start:]


def declaration_order(body, members):
    """{member: position of its declaration in body} (`Type m_a, m_b[4];`, not `return m_a;`)."""
    positions = {}
    for member in members:
        found = re.search(rf"^[ \t]*(?!return\b)[A-Za-z_][\w:<>,*& \t]*[\s*&,]({re.escape(member)})"
                          rf"\s*(?:\[[^\]]*\]\s*)*(?::\s*\d+\s*)?[;,=]", body, re.M)
        if found:
            positions[member] = found.start(1)
    return positions


def order_agreement(offsets, positions):
    """(concordant, comparable) member pairs: offset order vs declaration order."""
    names = [m for m in offsets if m in positions]
    concordant = comparable = 0
    for i, a in enumerate(names):
        for b in names[i + 1:]:
            if offsets[a] == offsets[b]:
                continue
            comparable += 1
            concordant += (offsets[a] < offsets[b]) == (positions[a] < positions[b])
    return concordant, comparable


def zh_check(rows, count, roots):
    """Report lines comparing harvested classes with reference headers: a total
    over every class the headers define, then the `count` best-covered ones."""
    bodies = reference_class_bodies(roots)
    per_class = defaultdict(dict)
    for r in rows:
        if r.kind == "assert" and r.cls != "?" and not r.conflict and r.cls.split("<")[0] in bodies:
            per_class[r.cls][r.member] = r.offset
    results = {cls: class_agreement(offsets, bodies[cls.split("<")[0]])
               for cls, offsets in per_class.items()}
    declared = sum(len(found) for found, _, _ in results.values())
    total = sum(len(offsets) for offsets in per_class.values())
    concordant = sum(c for _, c, _ in results.values())
    comparable = sum(n for _, _, n in results.values())
    lines = [f"reference check: {len(results)} classes defined in ZH/BFME 1 headers; "
             f"{declared}/{total} names declared there; offset order agrees with "
             f"declaration order for {concordant}/{comparable} member pairs",
             f"spot-check, {count} classes with the most members:"]
    for cls in sorted(per_class, key=lambda c: (-len(per_class[c]), c))[:count]:
        found, agree, pairs = results[cls]
        missing = sorted(set(per_class[cls]) - set(found))
        lines.append(f"  {cls}: {len(found)}/{len(per_class[cls])} names declared, offset order "
                     f"{agree}/{pairs} pairs agree"
                     + (f"; undeclared: {', '.join(missing[:6])}" if missing else ""))
    return lines


def class_agreement(offsets, body):
    """(declared positions, concordant pairs, comparable pairs) for one class."""
    positions = declaration_order(body, offsets)
    return (positions, *order_agreement(offsets, positions))


# ---------------------------------------------------------------- report

def report(rows, samples=15, top=20):
    named = [r for r in rows if r.cls != "?"]
    members = {(r.cls, r.member, r.kind) for r in named}
    conflicted = {(r.cls, r.member, r.kind) for r in named if r.conflict}
    by_class = Counter(cls for cls, _, kind in members if kind == "assert")
    lines = [
        f"classes: {len({r.cls for r in named})}  members: {len(members)} "
        f"(assert {sum(k == 'assert' for _, _, k in members)}, "
        f"accessor {sum(k == 'accessor' for _, _, k in members)})  "
        f"conflicted: {len(conflicted)} ({100 * len(conflicted) / max(1, len(members)):.1f}%)  "
        f"foreign (class ?): {len(rows) - len(named)} rows",
        f"top {top} classes by assert members:",
    ]
    lines += [f"  {count:4d}  {cls}" for cls, count in by_class.most_common(top)]
    lines.append(f"{samples} sample rows:")
    step = max(1, len(named) // samples)
    for r in named[::step][:samples]:
        lines.append(f"  {r.cls}::{r.member} @{r.offset:#x} {r.size} {r.kind} x{r.occurrences}"
                     f"{' conflict ' + r.conflict if r.conflict else ''}  <- {r.example_condition}")
    return lines


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--exe", default=WB_EXE, type=Path)
    parser.add_argument("--functions", default=FUNCTIONS, type=Path,
                        help="pe_features.py --wb-names output for the exe")
    parser.add_argument("--out-dir", default=OUT_DIR, type=Path)
    parser.add_argument("--zh-check", type=int, default=0, metavar="N",
                        help="compare the N best-covered classes with reference headers")
    parser.add_argument("--zh-root", action="append", type=Path,
                        help="reference header tree (repeatable; default: ZH Code and BFME 1 game)")
    args = parser.parse_args(argv)
    if not args.functions.exists():
        sys.exit(f"{args.functions} missing: run tools/pe_features.py {args.exe} --wb-names --out ...")
    rows = aggregate(harvest(args.exe, args.functions))
    args.out_dir.mkdir(parents=True, exist_ok=True)
    write_csv(rows, args.out_dir / "wb_members.csv")
    lines = report(rows)
    if args.zh_check:
        lines += zh_check(rows, args.zh_check, args.zh_root or [ZH_CODE, BFME1_GAME])
    text = "\n".join(lines) + "\n"
    (args.out_dir / "wb_members_report.txt").write_text(text)
    print(f"{len(rows)} rows -> {args.out_dir / 'wb_members.csv'}\n{text}", end="")


if __name__ == "__main__":
    main()
