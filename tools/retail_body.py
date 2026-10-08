#!/usr/bin/env python3
"""Shared retail-body plumbing for the advisory byte-tell tools.

flag_hint.py, sig_check.py and wpo_detect.py all start from the same place:
one function of game.dat, its boundary, its disassembly with register
reads and writes, its callers and callees, and the ledger row (if any) that
names it. This module holds that, and nothing that refuses anything.

  * image()            game.dat mapped at its preferred base (pe_features.Image)
  * body_bounds(rva)   (rva, size) from the ledger row, else gd_functions.jsonl
  * disasm(...)        Insn records with full-register read/write masks
  * live_in(insns)     registers a body reads on some path before writing them
  * callers(rva)       functions whose direct calls reach rva
  * ledger_rows(...)   streamed functions.csv rows by rva or name (never loaded whole)
  * build_flags(path)  the flags build.py really passes for a source (its
                       `// cl:` line with the region's codegen flags), and
                       effective_flags(); source_flags(path) is the bare line

Everything here is evidence for a human or a draft, never a byte match.
"""
import bisect
import csv
import functools
import json
import os
import pickle
import re
import struct
import sys
from collections import namedtuple
from pathlib import Path

import capstone
from capstone import x86_const as X

sys.path.insert(0, str(Path(__file__).resolve().parent))

ROOT = Path(__file__).resolve().parent.parent
GD_EXE = ROOT / "baselines" / "bfme2" / "workshop-vanilla-1.06" / "files" / "game.dat"
FUNCTIONS_CSV = ROOT / "reverse" / "functions.csv"
CACHE_DIR = ROOT / "build" / "retail_body"
IMAGE_BASE = 0x400000
INDEX_VERSION = 1

# Capstone register name -> (full 32-bit register, byte mask). Bit 0 is the low
# byte, bit 1 the second byte, bit 2 the upper half, so `mov al, 1` defines
# only part of eax and a later `push eax` still reads the caller's upper bytes.
_PARTS = {"l": 1, "h": 2, "x": 3, "e": 7}
REG_PARTS = {}
for _full, _names in {"eax": ("al", "ah", "ax"), "ebx": ("bl", "bh", "bx"),
                      "ecx": ("cl", "ch", "cx"), "edx": ("dl", "dh", "dx"),
                      "esi": ("sil", None, "si"), "edi": ("dil", None, "di"),
                      "ebp": ("bpl", None, "bp")}.items():
    REG_PARTS[_full] = (_full, 7)
    low, high, word = _names
    REG_PARTS[low] = (_full, 1)
    if high:
        REG_PARTS[high] = (_full, 2)
    REG_PARTS[word] = (_full, 3)
GPRS = ("eax", "ecx", "edx", "ebx", "esi", "edi", "ebp")
CALLEE_SAVED = ("ebx", "esi", "edi", "ebp")
SCRATCH = ("eax", "ecx", "edx")
# `push reg` of these is a register save (or, for ecx, MSVC's 4-byte stack
# reservation), not a use of the incoming value.
SAVE_PUSHES = frozenset(CALLEE_SAVED + ("ecx",))

JCC = frozenset({"ja", "jae", "jb", "jbe", "je", "jne", "jg", "jge", "jl", "jle",
                 "jo", "jno", "js", "jns", "jp", "jnp", "jecxz", "jcxz"})
JUMP_TABLE_RE = re.compile(r"^dword ptr \[(?:\w+)\*4 \+ (0x[0-9a-f]+)\]$")
INDEX_TABLE_RE = re.compile(r"^\w+, byte ptr \[\w+ \+ (0x[0-9a-f]+)\]$")

Insn = namedtuple("Insn", "rva size mnem ops raw reads writes target imm")


# ------------------------------------------------------------------ image

@functools.lru_cache(maxsize=1)
def image():
    import pe_features
    return pe_features.Image(str(GD_EXE))


def read_bytes(rva, size):
    img = image()
    off = rva + IMAGE_BASE - img.base
    return img.data[off:off + size]


def dword_at(rva):
    return struct.unpack_from("<I", read_bytes(rva, 4))[0]


def in_text(rva):
    img = image()
    lo, hi = img.text
    return lo <= rva + IMAGE_BASE < hi


# ------------------------------------------------------------ disassembly

@functools.lru_cache(maxsize=1)
def _md():
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    return md


def _regs(md, ids):
    out = {}
    for reg in ids:
        part = REG_PARTS.get(md.reg_name(reg))
        if part:
            out[part[0]] = out.get(part[0], 0) | part[1]
    return out


def _decode(md, ins):
    """Insn for one capstone instruction, with zero-idiom and save fixups."""
    try:
        read_ids, write_ids = ins.regs_access()
    except capstone.CsError:
        read_ids, write_ids = [], []
    reads, writes = _regs(md, read_ids), _regs(md, write_ids)
    mnem, ops = ins.mnemonic, ins.op_str
    operands = ins.operands
    target = imm = None
    if mnem == "call" or mnem == "jmp" or mnem in JCC:
        if operands and operands[0].type == X.X86_OP_IMM:
            target = operands[0].imm - IMAGE_BASE
    regs = [op for op in operands if op.type == X.X86_OP_REG]
    same = (len(regs) == 2 and len(operands) == 2
            and regs[0].reg == regs[1].reg)
    if mnem in ("xor", "sub", "sbb") and same:
        # Zero / all-ones idioms: the old value is never consumed.
        reads = {}
    if mnem in ("or", "and") and len(operands) == 2 and operands[0].type == X.X86_OP_REG \
            and operands[1].type == X.X86_OP_IMM \
            and operands[1].imm & 0xFFFFFFFF in ((0xFFFFFFFF if mnem == "or" else 0),):
        reads = {}  # or reg, -1 / and reg, 0 materialise a constant
    if mnem == "lea" and re.fullmatch(r"(e[a-z]{2}), \[\1(?: \+ 0)?\]", ops) \
            or mnem == "mov" and len(regs) == 2 and same:
        reads, writes = {}, {}  # alignment filler: lea ecx, [ecx] / mov edi, edi
    if mnem == "call":
        # The callee clobbers the scratch registers; the call itself reads none
        # of them unless it is indirect through one (kept from capstone).
        for reg in SCRATCH:
            writes[reg] = 7
    for op in operands:
        if op.type == X.X86_OP_IMM:
            imm = op.imm
    return Insn(ins.address - IMAGE_BASE, ins.size, mnem, ops, bytes(ins.bytes),
                reads, writes, target, imm)


def disasm(rva, size, data=None):
    """Insn list for [rva, rva+size), skipping in-body switch tables.

    data defaults to game.dat's bytes; tests pass assembled bytes instead.
    """
    if data is None:
        data = read_bytes(rva, size)
    md = _md()
    tables = {}
    out = []
    pos, end = rva, rva + size
    while pos < end:
        if pos in tables:
            pos = max(pos + 1, tables[pos])
            continue
        stop = min([t for t in tables if t > pos] + [end])
        known = len(tables)
        resume = None
        for ins in md.disasm(data[pos - rva:stop - rva], pos + IMAGE_BASE):
            insn = _decode(md, ins)
            out.append(insn)
            resume = insn.rva + insn.size
            _note_table(insn, rva, end, data, tables)
            if len(tables) != known:
                break
        if resume is None or (resume < stop and len(tables) == known):
            resume = (resume or pos) + 1
        pos = resume
    return out


def _note_table(insn, start, end, data, tables):
    match = JUMP_TABLE_RE.match(insn.ops) if insn.mnem == "jmp" else None
    if match:
        table = int(match.group(1), 16) - IMAGE_BASE
        if start <= table < end:
            stop = table
            while stop + 4 <= end:
                value = struct.unpack_from("<I", data, stop - start)[0] - IMAGE_BASE
                if not start <= value < end:
                    break
                stop += 4
            tables[table] = max(stop, table + 4)
        return
    match = INDEX_TABLE_RE.match(insn.ops) if insn.mnem == "movzx" else None
    if match:
        table = int(match.group(1), 16) - IMAGE_BASE
        if start <= table < end and table not in tables:
            tables[table] = min([t for t in tables if t > table] + [end])


def table_targets(insns, rva, size, data=None):
    """{jmp rva: [case targets]} for in-body jump tables."""
    if data is None:
        data = read_bytes(rva, size)
    out = {}
    for insn in insns:
        match = JUMP_TABLE_RE.match(insn.ops) if insn.mnem == "jmp" else None
        if not match:
            continue
        table = int(match.group(1), 16) - IMAGE_BASE
        targets = []
        pos = table
        while rva <= pos and pos + 4 <= rva + size:
            value = struct.unpack_from("<I", data, pos - rva)[0] - IMAGE_BASE
            if not rva <= value < rva + size:
                break
            targets.append(value)
            pos += 4
        out[insn.rva] = targets
    return out


# --------------------------------------------------------------- liveness

def successors(insns, index, by_rva, tables):
    insn = insns[index]
    if insn.mnem.startswith("ret"):
        return []
    if insn.mnem == "jmp":
        if insn.target is not None:
            return [by_rva[insn.target]] if insn.target in by_rva else []
        return [by_rva[t] for t in tables.get(insn.rva, ()) if t in by_rva]
    nxt = [index + 1] if index + 1 < len(insns) else []
    if insn.mnem in JCC and insn.target in by_rva:
        nxt.append(by_rva[insn.target])
    if insn.mnem == "call" and insn.target is not None and _is_noreturn(insn.target):
        return []
    return nxt


def _is_noreturn(target):
    return target in _noreturn_targets()


@functools.lru_cache(maxsize=1)
def _noreturn_targets():
    """Addresses of _CxxThrowException-style calls are not modelled; empty."""
    return frozenset()


def live_in(insns, tables=None, ignore_saves=True):
    """{full reg: rva of first read} for registers read before being written on
    some path from the entry. `push` of ecx (a stack reservation) or of a
    callee-saved register the body pops again counts as a save, not a read,
    when ignore_saves is set."""
    if not insns:
        return {}
    tables = tables or {}
    by_rva = {insn.rva: i for i, insn in enumerate(insns)}
    full = {reg: 7 for reg in GPRS}
    # A push is a save only if the body restores that register somewhere; an
    # unmatched `push esi` is the incoming value passed on.
    restored = {insn.ops for insn in insns if insn.mnem == "pop"}
    # Forward must-define analysis: state is {reg: defined byte mask}.
    states = {0: {}}
    work = [0]
    found = {}
    visits = 0
    while work and visits < 20000:
        visits += 1
        index = work.pop()
        state = dict(states[index])
        insn = insns[index]
        reads = insn.reads
        if ignore_saves and insn.mnem == "push" and insn.ops in SAVE_PUSHES \
                and (insn.ops == "ecx" or insn.ops in restored):
            reads = {}
        for reg, mask in reads.items():
            if reg not in full:
                continue
            # Only a read of a register this body has not touched at all counts:
            # `mov al, x; and eax, 1` merges stale upper bytes the code ignores.
            if mask and not state.get(reg, 0) and reg not in found:
                found[reg] = insn.rva
        for reg, mask in insn.writes.items():
            state[reg] = state.get(reg, 0) | mask
        for nxt in successors(insns, index, by_rva, tables):
            old = states.get(nxt)
            if old is None:
                states[nxt] = state
                work.append(nxt)
                continue
            merged = {reg: old[reg] & state.get(reg, 0) for reg in old if old[reg] & state.get(reg, 0)}
            if merged != old:
                states[nxt] = merged
                work.append(nxt)
    return found


# ------------------------------------------------------- function index

def _gd_functions():
    import wb_data
    return wb_data.ensure("gd_functions.jsonl")


@functools.lru_cache(maxsize=1)
def function_index():
    """{"starts": sorted rvas, "size": {rva: size}, "callers": {rva: [rvas]}},
    from gd_functions.jsonl, pickled under build/retail_body/."""
    source = _gd_functions()
    stamp = [INDEX_VERSION, os.stat(source).st_mtime_ns]
    path = CACHE_DIR / "function_index.pkl"
    if path.exists():
        try:
            with open(path, "rb") as fh:
                cached = pickle.load(fh)
            if cached.get("stamp") == stamp:
                return cached
        except (OSError, pickle.UnpicklingError, EOFError):
            pass
    size, callers = {}, {}
    with open(source) as fh:
        for record in map(json.loads, fh):
            rva = record["va"] - IMAGE_BASE
            size[rva] = record["size"]
            for target in set(record.get("calls", ())):
                callers.setdefault(target - IMAGE_BASE, []).append(rva)
    index = {"stamp": stamp, "starts": sorted(size), "size": size, "callers": callers}
    CACHE_DIR.mkdir(parents=True, exist_ok=True)
    tmp = path.with_suffix(".tmp")
    with open(tmp, "wb") as fh:
        pickle.dump(index, fh, protocol=pickle.HIGHEST_PROTOCOL)
    tmp.replace(path)
    return index


def function_size(rva):
    return function_index()["size"].get(rva)


def containing(rva):
    """(start, size) of the indexed function that holds rva, or None."""
    index = function_index()
    starts = index["starts"]
    i = bisect.bisect_right(starts, rva) - 1
    if i < 0:
        return None
    start = starts[i]
    size = index["size"][start]
    return (start, size) if start <= rva < start + size else None


def callers(rva):
    return sorted(index_callers for index_callers in function_index()["callers"].get(rva, ()))


def follow_jumps(rva, depth=4):
    """Resolve `jmp rel32` stubs to the body they forward to."""
    for _ in range(depth):
        raw = read_bytes(rva, 5)
        if len(raw) == 5 and raw[0] == 0xE9:
            rva = (rva + 5 + struct.unpack_from("<i", raw, 1)[0]) & 0xFFFFFFFF
            continue
        break
    return rva


# ---------------------------------------------------------------- ledger

def ledger_rows(rva=None, name=None, path=FUNCTIONS_CSV):
    """Ledger rows at rva or with this exact name, streamed with a cheap
    substring prefilter (functions.csv is never held in memory)."""
    needle = f"0x{rva:08X}" if rva is not None else name
    header = None
    out = []
    with open(path, newline="", encoding="utf-8") as fh:
        for line in fh:
            if header is None:
                header = next(csv.reader([line]))
                continue
            if needle not in line and (rva is None or f"0x{rva:X}" not in line.upper()):
                continue
            row = dict(zip(header, next(csv.reader([line]))))
            if rva is not None:
                try:
                    if int(row.get("target_rva") or "-1", 16) != rva:
                        continue
                except ValueError:
                    continue
            elif row.get("name") != name:
                continue
            out.append(row)
    return out


def stream_matched(path=FUNCTIONS_CSV):
    with open(path, newline="", encoding="utf-8") as fh:
        for row in csv.DictReader(fh):
            if row.get("status") == "matched" and row.get("target_rva") and row.get("target_size"):
                yield row


def best_row(rows):
    """The matched row if there is one, else the first."""
    for row in rows:
        if row.get("status") == "matched":
            return row
    return rows[0] if rows else None


def resolve_target(text):
    """(rva, row or None) for '0x1234', '1234h' or a ledger name."""
    value = text.strip()
    rva = None
    if re.fullmatch(r"(?:0x)?[0-9A-Fa-f]+", value) and (value.lower().startswith("0x")
                                                       or not value.isalpha()):
        rva = int(value, 16)
        if rva >= IMAGE_BASE and function_size(rva - IMAGE_BASE) is not None \
                and function_size(rva) is None:
            rva -= IMAGE_BASE
        return rva, best_row(ledger_rows(rva=rva))
    rows = ledger_rows(name=value)
    row = best_row(rows)
    if row is None or not row.get("target_rva"):
        raise SystemExit(f"{text}: no ledger row with that name")
    return int(row["target_rva"], 16), row


def body_bounds(rva, row=None):
    """(rva, size): the ledger row's extent, else the gd_functions boundary."""
    if row and row.get("target_size"):
        try:
            return rva, int(row["target_size"])
        except ValueError:
            pass
    size = function_size(rva)
    if size is None:
        found = containing(rva)
        if found and found[0] == rva:
            size = found[1]
    if size is None:
        raise SystemExit(f"0x{rva:08X}: no known boundary (not a gd_functions start, no ledger size)")
    return rva, size


# ------------------------------------------------------------------ flags

CL_RE = re.compile(r"^﻿?// cl:(.*)$")


def source_flags(path):
    """The `// cl:` tokens of a source (empty: base flags only), or None if the
    file cannot be read."""
    try:
        text = Path(path).read_text(encoding="utf-8-sig", errors="replace")
    except OSError:
        return None
    for line in text.splitlines():
        match = CL_RE.match(line)
        if match:
            return match.group(1).split()
    return []


def build_flags(path):
    """The tokens tools/build.py passes after `cl -O2 -GR- -EHsc-` for a source,
    or None if the file cannot be read.

    For most Code/ units the `// cl:` line is not what compiles: the region
    decides /O, /arch and /G (tools/flag_defaults.py), so a source whose line
    says nothing still builds /O1 /arch:SSE /G7. Read the build's own answer;
    the bare `// cl:` tokens only if build.py cannot be loaded."""
    path = Path(path)
    if not path.is_file():
        return None
    try:
        import build
        return list(build.source_extra_flags(path.resolve()))
    except (Exception, SystemExit):  # advice only: fall back, never fail
        return source_flags(path)


def effective_flags(tokens):
    """What build.py's `cl -O2 -GR- -EHsc- <tokens>` turns on, as a dict."""
    flags = {"opt": "/O2", "G7": False, "arch": None, "GS": False, "EH": None,
             "Oy-": False, "Ob": None}
    for raw in tokens or ():
        token = "/" + raw[1:] if raw.startswith("-") else raw
        low = token.lower()
        if low in ("/od", "/o1", "/o2", "/ox"):
            flags["opt"] = {"/od": "/Od", "/o1": "/O1", "/o2": "/O2", "/ox": "/Ox"}[low]
        elif low == "/os" or low == "/ot":
            flags.setdefault("favor", token)
        elif low in ("/g7", "/g6", "/g5", "/gb"):
            flags["G7"] = low == "/g7"
        elif low.startswith("/arch:"):
            flags["arch"] = token[6:].upper()
        elif low == "/gs":
            flags["GS"] = True
        elif low == "/gs-":
            flags["GS"] = False
        elif low in ("/ehsc", "/gx", "/ehs", "/eha"):
            flags["EH"] = {"/ehsc": "/EHsc", "/gx": "/GX", "/ehs": "/EHs", "/eha": "/EHa"}[low]
        elif low in ("/ehsc-", "/gx-"):
            flags["EH"] = None
        elif low == "/oy-":
            flags["Oy-"] = True
        elif low.startswith("/ob"):
            flags["Ob"] = token
    return flags


def describe_flags(tokens):
    """The codegen part of a flag list (include and define paths dropped)."""
    shown = [t for t in tokens or () if not t[1:2] in ("I", "D")]
    return " ".join(shown) if shown else "(base flags only: -O2 -GR- -EHsc-)"
