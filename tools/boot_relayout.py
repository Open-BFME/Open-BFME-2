#!/usr/bin/env python3
"""Relayout and own-data overlays: boot images that are not retail-equivalent by construction.

`boot_image.py link --overlay SET` replaces retail pieces with authored units at
their retail addresses, and binds references to TU statics, literals and
unidentified externals to retail's own data by site, so the image equals retail
whether or not the tree's names and data are right. This module builds two
images in which they matter:

  --relayout   every authored unit moves to a fresh `.text$r` section, in a
               seeded shuffled order and at its retail address mod 16, and its
               retail range is filled with int3. References resolve by symbol
               through the linker: the units' own names (calls, jump tables,
               funclets), and only references into code or data that is not
               overlaid go to scaffold pieces by retail identity. Scaffold
               DIR32 fields into a moved unit name it (retail's relocations);
               scaffold rel32 branches into one get a REL32 relocation from a
               disassembly sweep of retail .text. A unit stays at its retail
               address (counted) when something cannot follow it: a short
               branch into it, a branch out of it its object does not relocate,
               or the entry point.
  --own-data   data the units' objects define (TU statics, literals, constant
               tables, globals) is placed from the objects in our own sections
               (`.ordata` read-only, `.odata` writable) and the units' references
               bind to it, not to retail's copy. Writable data is owned only when
               every retail reference to it lies in an overlaid unit; otherwise
               (shared with code we do not provide yet) it stays retail's, counted.

Admission is check-driven: a unit is refused before the link only for structural
reasons (bytes outside relocations differ, relocation sites disagree, an import
differs). A name that denotes a different address than retail's target, an
internal target that differs, or owned data that differs is linked as the object
says, and the semantic image check judges it: every field must point at the moved
copy of retail's target (the owned copy for references from authored code) and
every other byte must equal retail's. Units and data the check blames are refused
and the image is linked again (at most --rounds times).

  python3 tools/boot_image.py link --overlay SET --relayout [--own-data] [--seed N]
"""
import bisect
import collections
import hashlib
import json
import pickle
import random
import struct
import time
from pathlib import Path

import capstone
import pefile

import boot_image as bi

ALIGN_16 = 0x00500000
DATA_RO, DATA_RW = 0x40000040, 0xC0000040
WRITABLE = 0x80000000
OWN_CAP = 0x10000                        # largest datum placed from an object
SHORT_BRANCH = {0xEB, 0xE0, 0xE1, 0xE2, 0xE3} | set(range(0x70, 0x80))


# ---------------------------------------------------------------- branch sweep
def branch_sweep(r, sites, out=bi.OUT):
    """{site: (width, target)} for every direct call/jmp/jcc operand in retail .text
    (width 4: rel32, 1: rel8). Linear sweep from every known function start to the
    next; an instruction starting on a relocation site is data (a jump table: MSVC
    puts them after the code), so the sweep leaves that function there (resuming
    after a table decodes byte tables and inline data as branches). Code after a
    table with no known start of its own is therefore not swept, so `raw` is also
    returned: {site: target} of every raw E8/E9 byte whose rel32 lands on a known
    function start, for units such an undecoded call reaches to stay put. Cached."""
    starts = bi.function_starts()
    tstart, tsize, text = r.secs[".text"]
    key = hashlib.sha1(repr((4, len(text), starts[:50], len(starts), len(sites), sites[:50])).encode()).hexdigest()
    cache = out / "branches.pkl"
    if cache.exists():
        got = pickle.loads(cache.read_bytes())
        if got.get("key") == key:
            return got["branches"], got["raw"]
    siteset = set(sites)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    branches = {}
    starts = [s for s in starts if tstart <= s < tstart + tsize]
    for k, a in enumerate(starts):
        end = starts[k + 1] if k + 1 < len(starts) else tstart + tsize
        data = False
        while a < end and not data:
            last = a
            for addr, size, mnem, ops in md.disasm_lite(text[a - tstart:end - tstart], a):
                if addr in siteset or any(x in siteset for x in range(addr + max(1, size - 3), addr + size)):
                    data = True                    # data (a table or a straddled field): leave the function
                    break
                if (mnem == "call" or mnem.startswith("j") or mnem.startswith("loop")) and ops.startswith("0x"):
                    op = text[addr - tstart]
                    width = 1 if op in SHORT_BRANCH else 4
                    if op != 0x66 and (width == 1 or size >= 5):   # not rel16 / odd encodings
                        branches[addr + size - width] = (width, int(ops, 16))
                last = addr + size
            a = a + 1 if last == a else last       # an undecodable byte is skipped
    starts_all = set(bi.function_starts())
    raw = {}
    for op in (bytes([0xE8]), bytes([0xE9])):
        k = text.find(op)
        while k >= 0:
            if k + 5 <= len(text):
                t = tstart + k + 5 + struct.unpack_from("<i", text, k + 1)[0]
                if t in starts_all:
                    raw[tstart + k + 1] = t
            k = text.find(op, k + 1)
    cache.write_bytes(pickle.dumps({"key": key, "branches": branches, "raw": raw}))
    return branches, raw


def validate_sweep(units, branches):
    """Recall / precision of the sweep's rel32 fields inside units against the
    units' own objects (their REL32 relocations to targets outside the unit)."""
    want, got = set(), set()
    for u in units:
        for o, k, n in u.relocs:
            if k == bi.REL32 and n != u.label:
                want.add(u.rva + o)
        lo, hi = u.rva, u.rva + u.size
        got |= {s for s in branches_in(branches, lo, hi) if branches[s][0] == 4
                and not lo <= branches[s][1] < hi}
    return {"object_rel32": len(want), "swept": len(got), "true": len(want & got),
            "missed": len(want - got), "false": len(got - want),
            "false_examples": [hex(x) for x in sorted(got - want)[:10]]}


_SORTED = {}


def branches_in(branches, lo, hi):
    keys = _SORTED.get(id(branches))
    if keys is None:
        keys = _SORTED[id(branches)] = (branches, sorted(branches))
    keys = keys[1]
    return keys[bisect.bisect_left(keys, lo):bisect.bisect_left(keys, hi)]


# ---------------------------------------------------------------- relayout
def instruction_starts(r, lo, hi):
    tstart, _, text = r.secs[".text"]
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    return {a for a, _, _, _ in md.disasm_lite(text[lo - tstart:hi - tstart], lo)}


TERMINATORS = {"ret", "retf", "jmp", "ljmp", "int3", "ud2", "hlt", "iretd"}


def falls_through(r, lo, hi, siteset):
    """Whether the code in [lo, hi) can run on past hi: decoded linearly (stopping at
    data, a relocation site where an instruction would start), the last instruction
    ends exactly at hi and is not a ret / jmp / int3."""
    tstart, _, text = r.secs[".text"]
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    last = None
    for addr, size, mnem, _ops in md.disasm_lite(text[lo - tstart:hi - tstart], lo):
        if addr in siteset:
            return False
        last = (addr + size, mnem)
    return last is not None and last[0] == hi and last[1] not in TERMINATORS


def fallthrough_pins(r, units, siteset):
    """{unit rva: why}: units joined to the code before or after them by
    fall-through (no branch to follow: a compiler initializer split in two rows, a
    call to a no-return function at a row's end), which must keep retail's order."""
    starts = sorted(set(bi.function_starts()) | {u.rva for u in units})
    begins = {u.rva for u in units}
    pins = {}
    for u in units:
        i = bisect.bisect_left(starts, u.rva)
        prev = starts[i - 1] if i else None
        if prev is not None and u.rva - prev < 0x4000 and falls_through(r, prev, u.rva, siteset):
            pins[u.rva] = "falls-through-in"
        if falls_through(r, u.rva, u.rva + u.size, siteset):
            pins.setdefault(u.rva, "falls-through-out")
            if u.rva + u.size in begins:
                pins.setdefault(u.rva + u.size, "falls-through-in")
    return pins


def choose_moves(r, units, branches, pinned=None, siteset=frozenset(), raw=None):
    """(moved units, {unit rva: why kept}, scaffold redirects [(site, unit, target)],
    counts). A unit moves unless something that cannot be relocated reaches into
    it or leaves it (a short branch, an unrelocated branch, fall-through); keeping
    one can keep others (fixpoint)."""
    spans = sorted((u.rva, u.rva + u.size, u) for u in units)
    los = [s[0] for s in spans]

    def unit_at(t):
        i = bisect.bisect_right(los, t) - 1
        return spans[i][2] if i >= 0 and t < spans[i][1] else None
    kept, counts = dict(pinned or {}), collections.Counter()
    for k, v in fallthrough_pins(r, units, siteset).items():
        kept.setdefault(k, v)
    begins = {u.rva: u for u in units}
    for site, t in (raw or {}).items():               # a call the sweep did not decode: keep its target
        u = begins.get(t)
        if u is not None and site not in branches and not u.rva <= site < u.rva + u.size:
            kept.setdefault(t, "undecoded-raw-call-in")
    rel32 = {u.rva: {o for o, k, n in u.relocs if k == bi.REL32} for u in units}
    for u in units:
        if u.rva <= r.entry < u.rva + u.size:
            kept[u.rva] = "entry-point"
        rel = rel32[u.rva]
        for s in branches_in(branches, u.rva, u.rva + u.size):
            width, t = branches[s]
            if u.rva <= t < u.rva + u.size:
                continue
            if width == 1:
                kept.setdefault(u.rva, "short-branch-out")
            elif s - u.rva not in rel:
                kept.setdefault(u.rva, "unrelocated-branch-out")
    # branches into a unit from code that keeps retail's bytes (scaffold, or a kept unit's
    # unrelocated operand): rel32 from the scaffold is redirected, anything else pins the target
    inbound = collections.defaultdict(list)
    for s, (width, t) in branches.items():
        v = unit_at(t)
        if v is not None and not v.rva <= s < v.rva + v.size:
            inbound[v.rva].append((s, width, t))
    starts_cache = {}
    redirects = []
    changed = True
    while changed:
        changed, redirects = False, []
        for v in units:
            if v.rva in kept:
                continue
            for s, width, t in inbound.get(v.rva, ()):
                src = unit_at(s)
                if src is not None and width == 4 and s - src.rva in rel32[src.rva]:
                    continue                        # the source object relocates it: by symbol
                if t != v.rva:
                    if v.rva not in starts_cache:
                        starts_cache[v.rva] = instruction_starts(r, v.rva, v.rva + v.size)
                    if t not in starts_cache[v.rva]:
                        # likely data decoded as a branch, but it cannot be told apart: keep the unit
                        kept[v.rva] = "branch-in-not-at-an-instruction"
                        changed = True
                        break
                if width == 1:
                    kept[v.rva] = "short-branch-in"
                    changed = True
                    break
                if src is not None:
                    kept[v.rva] = "unrelocated-branch-in"      # from a kept unit's own bytes
                    changed = True
                    break
                redirects.append((s, v, t))
    moved = [u for u in units if u.rva not in kept]
    counts["redirected-rel32"] = len(redirects)
    counts["redirected-into-unit-middle"] = sum(1 for s, v, t in redirects if t != v.rva)
    return moved, kept, redirects, counts


def relayout_pieces(pieces, moved, redirects, seed):
    """Scaffold pieces (moved units' ranges become int3 fillers), the moved unit
    pieces renamed `.text$rNNNNNN` in a seeded shuffled order, aligned to keep
    their address mod 16; scaffold rel32 redirects become REL32 relocations."""
    moved_rva = {u.rva for u in moved}
    scaffold, out = [], []
    for p in pieces:
        if p.unit is not None and p.unit.rva in moved_rva and p.start == p.unit.rva:
            f = bi.Piece(p.name, p.start, p.size, p.flags)
            f.fill = 0xCC
            scaffold.append(f)
            out.append(p)
        else:
            scaffold.append(p)
    order = list(range(len(out)))
    random.Random(seed).shuffle(order)
    for k, p in zip(order, out):
        p.name, p.flags, p.pad = f".text$r{k:06d}", bi.CODE | ALIGN_16, p.start & 0xF
    starts = [p.start for p in scaffold]
    piece_of = {u.rva: p for p in out for u in (p.unit,)}
    bad = set()                                      # units a scaffold branch cannot be redirected to
    for s, v, t in redirects:
        q = scaffold[bisect.bisect_right(starts, s) - 1]
        if q.unit is not None or q.fill is not None or s + 4 > q.start + q.size or \
                any(x - 3 <= s <= x + 3 for x, _, _ in q.relocs):
            bad.add(v.rva)
            continue
        q.relocs.append((s, bi.REL32, ("piece", piece_of[v.rva], t)))
    for q in scaffold:
        q.relocs.sort(key=lambda x: x[0])
    return scaffold, out, bad


# ---------------------------------------------------------------- own data
def datum_extent(o, sec, q):
    """(start, size) of the object datum holding section offset q: a COMDAT section
    whole (a vtable's symbol is 4 bytes in, after its RTTI locator pointer), else
    from the last symbol at or before q to the next one."""
    s = o[0][sec - 1]
    if s.flags & bi.COMDAT:
        return 0, s.size
    lo, raw, _ = bi.object_datum(o, sec, q, OWN_CAP)
    return lo, len(raw)


def table_continues(r, rlo, n, siteset):
    """Whether retail's table of code pointers runs on past [rlo, rlo + n): the last
    dword of the object's datum and the one after it are both relocation sites into
    .text. A vtable an object defines shorter than retail's (a private class view)
    would otherwise be owned, and a virtual call past its end reads garbage."""
    last, nxt = rlo + n - 4, rlo + n
    return all(a in siteset and r.section_of(r.u32(a) - bi.RETAIL_BASE) == ".text" for a in (last, nxt))


def is_writable(r, rlo, o, sec):
    return r.section_of(rlo) in (".data", "STLPORT_") or bool(o[0][sec - 1].flags & WRITABLE)


def plan_own(r, live, refs, by_target, objs, banned=(), sites=()):
    """({rlo: (size, path, sec, lo, writable)} owned data, Counter of bytes not owned
    by reason, Counter of data not owned by reason). `refs` {unit rva: [(rlo, size,
    path, sec, lo)]} are the defined-data references bind_unit saw; writable data is
    owned only when every retail reference to it lies in a live unit, and data whose
    relocations are not exactly retail's sites there stays retail's."""
    spans = sorted((u.rva, u.rva + u.size) for u in live)
    los = [s[0] for s in spans]
    siteset = set(sites)

    def in_live(site):
        i = bisect.bisect_right(los, site) - 1
        return i >= 0 and site < spans[i][1]
    cands = collections.defaultdict(set)
    for u in live:
        for rlo, n, path, sec, lo in refs.get(u.rva, ()):
            cands[rlo].add((n, path, sec, lo))
    owned, why = {}, {}
    prev_end, prev = -1, None
    for rlo in sorted(cands):
        c = sorted(cands[rlo])
        n, path, sec, lo = c[0]
        o = objs.get(path)
        rsec = r.section_of(rlo)
        if rlo in banned:
            why[rlo] = (n, "refused-by-check")
        elif len({x[0] for x in c}) > 1:
            why[rlo] = (n, "extent-differs-between-objects")
        elif rsec is None or r.section_of(rlo + n - 1) != rsec:
            why[rlo] = (n, "outside-retail-section")
        elif n > OWN_CAP - 1 or n <= 0:
            why[rlo] = (n, "too-large")
        else:
            w = is_writable(r, rlo, o, sec)
            shared = w and any(not in_live(s) for s in sites_into(by_target, rlo, rlo + n))
            secs = o[0]
            relocs = [x for x in secs[sec - 1].relocs if lo - 4 < x[0] < lo + n]
            if shared:
                why[rlo] = (n, "writable-shared-with-retail-code")
            elif n >= 4 and table_continues(r, rlo, n, siteset):
                why[rlo] = (n, "code-pointer-table-continues-in-retail")
            elif any(not lo <= x[0] <= lo + n - 4 or x[2] != bi.DIR32 for x in relocs):
                why[rlo] = (n, "reloc-not-dir32-inside")
            elif {rlo + x[0] - lo for x in relocs} != set(sites[bisect.bisect_left(sites, rlo):
                                                                 bisect.bisect_left(sites, rlo + n - 3)]):
                why[rlo] = (n, "relocs-not-retail-sites")
            else:
                owned[rlo] = (n, path, sec, lo, w)
        if rlo < prev_end:                          # overlapping retail ranges: neither is ours
            if rlo in owned:
                why[rlo] = (owned.pop(rlo)[0], "overlaps-other-datum")
            if prev in owned:
                why[prev] = (owned.pop(prev)[0], "overlaps-other-datum")
        if rlo + n > prev_end:
            prev_end, prev = rlo + n, rlo
    nbytes, ndata = collections.Counter(), collections.Counter()
    for n, reason in why.values():
        nbytes[reason] += n
        ndata[reason] += 1
    return owned, nbytes, ndata


def sites_into(by_target, lo, hi):
    """Retail relocation sites whose target lies in [lo, hi)."""
    keys = by_target[0]
    return [by_target[1][k] for k in range(bisect.bisect_left(keys, lo), bisect.bisect_left(keys, hi))]


def target_index(r, sites):
    """(sorted targets, their fields): retail's DIR32 sites plus the export and
    resource directories' image-relative fields (an exported global is referenced
    from the export table, which the scaffold keeps pointing at retail's copy)."""
    pairs = sorted([(r.u32(s) - bi.RETAIL_BASE, s) for s in sites]
                   + [(r.u32(f), f) for f in bi.export_fields(r) + bi.resource_fields(r)])
    return [p[0] for p in pairs], [p[1] for p in pairs]


def datum_pieces(r, owned, objs, ctx):
    """Pieces for the owned data, each with (body, relocations [(offset, type, name)])
    from its object; names its relocations need go to ctx['need']."""
    iat, ident, authored = ctx["iat"], ctx["ident"], ctx["authored"]
    out = []
    for rlo, (n, path, sec, lo, w) in sorted(owned.items()):
        o = objs.get(path)
        secs, syms, data = o
        s = secs[sec - 1]
        body = bytearray(data[s.ptr + lo:s.ptr + lo + n]) if s.ptr and not s.flags & 0x80 else bytearray(n)
        rels = []
        for off, si, kind in s.relocs:
            if not lo <= off < lo + n:
                continue
            z, d = syms[si], off - lo
            add = struct.unpack_from("<i", body, d)[0]
            t2 = r.u32(rlo + d) - bi.RETAIL_BASE
            name = None
            if 0 < z.sec <= len(secs) and not secs[z.sec - 1].name.startswith(".text"):
                q2 = z.value + add
                lo2, n2 = datum_extent(o, z.sec, q2)
                r2 = t2 - (q2 - lo2)
                if owned.get(r2, (None,))[0] == n2 and owned[r2][1:4] == (path, z.sec, lo2):
                    name, inplace = f"_bootd_{r2:08X}", q2 - lo2
                    ctx["need"][name] = r2
            if name is None and z.sec == 0 and z.name.startswith("__imp_") and t2 in iat:
                name, inplace = "__imp_" + bi.import_symbol(iat[t2]), 0
            if name is None and z.cls in (bi.EXTERNAL, bi.WEAK):
                known = ident.get(z.name, set()) | authored.get(z.name, set())
                if len(known) == 1:
                    name, inplace = z.name, add
                    ctx["need"][name] = next(iter(known))
            if name is None:                          # a static or unidentified target: retail's, by site
                name, inplace = f"_boota_{t2:08X}", 0
                ctx["need"][name] = t2
            struct.pack_into("<i", body, d, inplace)
            rels.append((d, kind, name))
        p = bi.Piece(".odata" if w else ".ordata", rlo, n, (DATA_RW if w else DATA_RO) | ALIGN_16)
        p.public, p.pad = f"_bootd_{rlo:08X}", rlo & 0xF
        out.append((p, bytes(body), rels))
    return out


# ---------------------------------------------------------------- objects
def write_moved(moved, datums, path, names):
    """Objects for the moved units (`.text$r`, int3 before and after each body) and
    the owned data (`.ordata` / `.odata`), with a public at each piece and every
    name in `names` that lies in one. Returns (import symbols, paths)."""
    items = [(p, p.unit.body, p.unit.relocs, 0xCC, True) for p in moved] + \
            [(p, body, rels, 0, False) for p, body, rels in datums]
    spans = sorted((p.start, p.start + p.size, k) for k, (p, *_x) in enumerate(items))
    los = [s[0] for s in spans]
    defs = collections.defaultdict(list)
    for name, rva in sorted(names.items()):
        i = bisect.bisect_right(los, rva) - 1
        if i >= 0 and rva < spans[i][1] and name not in bi.ABSOLUTE:
            defs[spans[i][2]].append((name, rva - spans[i][0]))
    chunks = [list(range(i, min(i + bi.MAX_SECTIONS, len(items)))) for i in range(0, len(items), bi.MAX_SECTIONS)]
    imports, paths = set(), bi.chunk_paths(path, len(chunks))
    for c, chunk in enumerate(chunks):
        syms, sections = bi.Symbols(), []
        for j, k in enumerate(chunk, 1):
            p = items[k][0]
            syms.add(p.public, j, p.pad)
            for name, off in defs[k]:
                syms.add(name, j, p.pad + off)
        for k in chunk:
            p, body, rels, fill, code = items[k]
            raw = bytes([fill]) * p.pad + body + (b"\xCC" if code else b"")
            sections.append((p.name, p.flags, raw, [(o + p.pad, syms.add(n), kind) for o, kind, n in rels]))
        bi.write_coff(paths[c], sections, syms)
        imports |= {n[len("__imp_"):] for n in syms.index if n.startswith("__imp_")}
    return sorted(imports), paths


# ---------------------------------------------------------------- check
class Spans:
    """Retail ranges -> new addresses; `at(t)` is the new address of retail t."""
    def __init__(self, items):
        self.items = sorted(items)                    # (retail start, end, new start, tag)
        self.los = [x[0] for x in self.items]

    def find(self, t, end_ok=False):
        i = bisect.bisect_right(self.los, t) - 1
        if i >= 0 and (t < self.items[i][1] or (end_ok and t == self.items[i][1])):
            return self.items[i]
        return None

    def at(self, t):
        x = self.find(t) or self.find(t, end_ok=True)
        return None if x is None else x[2] + t - x[0]


def check_semantic(r, scaffold, moved, datums, branches, sites, exe, base, publics):
    """Semantic equivalence of the relaid image with retail, judged from retail alone:
    every relocated field points at the moved copy of retail's target (for authored
    code and owned data: the owned copy when the target is owned data; a branch's
    rel32 counts as a field), every other byte equals retail's, moved units' old
    ranges are int3, scaffold .text keeps one offset, base relocations are exactly
    the DIR32 fields. Returns (counts, examples, blame {('unit'|'datum', rva): kind})."""
    pe = pefile.PE(str(exe))
    img = pe.get_memory_mapped_image()
    new_iat = {}
    for d in pe.DIRECTORY_ENTRY_IMPORT:
        for imp in d.imports:
            new_iat[imp.address - base] = (d.dll.decode("latin-1").lower(),
                                           imp.name.decode("latin-1") if imp.name else None,
                                           None if imp.name else imp.ordinal)
    iat = r.imports()
    new = {id(p): publics[p.public] for p in scaffold + moved + [d[0] for d in datums]}
    smap = Spans([(p.start, p.start + p.size, new[id(p)], "s") for p in scaffold if p.fill is None]
                 + [(p.start, p.start + p.size, new[id(p)], "m") for p in moved])
    owned = Spans([(p.start, p.start + p.size, new[id(p)], "d") for p, _, _ in datums])
    writable = Spans([(p.start, p.start + p.size, 0, "w") for p, _, _ in datums if p.name == ".odata"])
    c, bad, blame, fields = collections.Counter(), [], {}, set()

    def u_at(t):                                       # authored side: owned data first
        return owned.at(t) if owned.find(t) else smap.at(t)

    def note(cls, ok, what, who):
        c[cls + ("-reloc-ok" if ok else "-reloc-bad")] += 1
        if not ok:
            c["reloc-bad"] += 1
            if who:
                blame.setdefault(who, "field")
            if len(bad) < 30:
                bad.append(what)

    def judge(cls, p, want, who, field_list):
        n0 = new[id(p)]
        got = bytearray(img[n0:n0 + p.size])
        want = bytearray(want)
        for o, kind, exp_fn in field_list:
            v = struct.unpack_from("<I", got, o)[0]
            exp = exp_fn(n0 + o)
            if isinstance(exp, tuple):
                ok = new_iat.get(v - base) == exp
            else:
                ok = exp is not None and v == exp
            note(cls, ok, "%s %#x: got %#x, want %s" % (cls, p.start + o, v, exp if isinstance(exp, tuple)
                                                         else hex(exp or 0)), who)
            if kind == bi.DIR32:
                fields.add(n0 + o)
            got[o:o + 4] = want[o:o + 4] = b"\0\0\0\0"
        diff = sum(1 for x, y in zip(got, want) if x != y)
        c[cls + "-bytes-equal"] += p.size - diff
        c[cls + "-bytes-differ"] += diff
        c["bytes-differ"] += diff
        if diff:
            if who:
                blame.setdefault(who, "bytes")
            if len(bad) < 30:
                bad.append("%s %#x: %d byte(s) differ" % (cls, p.start, diff))

    def rel(mapper, t):
        return lambda a: None if mapper(t) is None else (mapper(t) - a - 4) & 0xFFFFFFFF

    def piece_fields(p, mapper, rel32=()):
        out = []
        for site, kind, tgt in p.relocs:
            o = site - p.start
            if tgt[0] == "imp":
                out.append((o, kind, lambda a, e=tgt[1]: e))
            elif tgt[0] == "base":
                out.append((o, kind, lambda a, x=tgt[1]: base + x))
            elif kind == bi.REL32:
                out.append((o, kind, rel(mapper, tgt[2])))
            else:
                out.append((o, kind, lambda a, t=tgt[2], k=kind: None if mapper(t) is None
                            else mapper(t) + (base if k == bi.DIR32 else 0)))
                if p.unit is None and writable.find(tgt[2]):
                    note("scaffold", False, "scaffold %#x refers to owned writable data %#x" % (site, tgt[2]), None)
                    c["owned-writable-referenced-by-retail-code"] += 1
        for s, t in rel32:
            out.append((s - p.start, bi.REL32, rel(mapper, t)))
        return out
    tstart, _, text = r.secs[".text"]
    moved_ids = {id(p) for p in moved}
    for p in scaffold + moved:
        if p.fill is not None:
            got = img[new[id(p)]:new[id(p)] + p.size]
            n = sum(1 for x in got if x != p.fill)
            c["filler-bytes"] += p.size
            c["filler-bytes-not-int3"] += n
            c["bytes-differ"] += n
            continue
        s0, _, raw = next(v for v in r.secs.values() if v[0] <= p.start < v[0] + v[1])
        want = raw[p.start - s0:p.start - s0 + p.size]
        if p.unit is None:
            judge("scaffold", p, want, None, piece_fields(p, smap.at))
            continue
        u = p.unit
        cls = "moved" if id(p) in moved_ids else "inplace"
        # rel32 fields of the unit: from retail (branches leaving it) and from its object
        out = {s: branches[s][1] for s in branches_in(branches, u.rva, u.rva + u.size)
               if branches[s][0] == 4 and not u.rva <= branches[s][1] < u.rva + u.size}
        for o, k, n in u.relocs:
            if k == bi.REL32 and u.rva + o not in out:
                t = u.rva + o + 4 + struct.unpack_from("<i", text, u.rva + o - tstart)[0]
                if not u.rva <= t < u.rva + u.size:
                    out[u.rva + o] = t
        dir32 = {x[0] for x in p.relocs}
        judge(cls, p, want, ("unit", u.rva),
              piece_fields(p, u_at, sorted((s, t) for s, t in out.items() if s not in dir32)))
    for p, body, rels in datums:
        s0, _, raw = next(v for v in r.secs.values() if v[0] <= p.start < v[0] + v[1])
        want = raw[p.start - s0:p.start - s0 + p.size]
        fl = []
        for s in sites[bisect.bisect_left(sites, p.start):bisect.bisect_left(sites, p.start + p.size)]:
            if s + 4 > p.start + p.size:
                continue
            t = r.u32(s) - bi.RETAIL_BASE
            if t in iat:
                fl.append((s - p.start, bi.DIR32, lambda a, e=iat[t]: e))
            elif 0 <= t < 0x1000:
                fl.append((s - p.start, bi.DIR32, lambda a, x=t: base + x))
            else:
                fl.append((s - p.start, bi.DIR32, lambda a, t=t: None if u_at(t) is None else u_at(t) + base))
        c["owned-data-bytes"] += p.size
        judge("owned", p, want, ("datum", p.start), fl)
    # scaffold branches that still land in a moved unit's old (int3) range
    redirected = {s for p in scaffold for s, k, _ in p.relocs if k == bi.REL32}
    mspans = Spans([(p.start, p.start + p.size, 0, "m") for p in moved])
    uspans = Spans([(p.start, p.start + p.size, 0, "u") for p in scaffold + moved if p.unit is not None])
    for s, (w, t) in branches.items():
        if mspans.find(t) and s not in redirected and not uspans.find(s) and not mspans.find(s):
            c["branch-into-filler"] += 1
            c["reloc-bad"] += 1
            if len(bad) < 30:
                bad.append("scaffold branch %#x -> %#x lands in a moved unit's old range" % (s, t))
    text_pieces = [p for p in scaffold if p.name.startswith(".text")]
    d0 = new[id(text_pieces[0])] - text_pieces[0].start
    c["text-pieces-moved"] = sum(1 for p in text_pieces if new[id(p)] - p.start != d0)
    c["units-moved"] = len(moved)
    c["units-moved-at-retail-offset"] = sum(1 for p in moved if new[id(p)] - p.start == d0)
    dd = pe.OPTIONAL_HEADER.DATA_DIRECTORY[5]
    image_fields = set(bi.parse_blocks(pe.get_data(dd.VirtualAddress, dd.Size))[0]) if dd.Size else set()
    c["baserelocs-missing"] = len(fields - image_fields)
    c["baserelocs-extra"] = len(image_fields - fields)
    c["imports"] = len(new_iat)
    rsrc = next(p for p in scaffold if p.start == r.secs[".rsrc"][0])
    c["resource-dir"] = int(pe.OPTIONAL_HEADER.DATA_DIRECTORY[2].VirtualAddress == new[id(rsrc)])
    c["entry-ok"] = int(pe.OPTIONAL_HEADER.AddressOfEntryPoint == publics["_boot_entry"])
    exp = r.pe.OPTIONAL_HEADER.DATA_DIRECTORY[0].VirtualAddress
    c["export-dir"] = int(pe.OPTIONAL_HEADER.DATA_DIRECTORY[0].VirtualAddress == smap.at(exp))
    c["exports"] = len(pe.DIRECTORY_ENTRY_EXPORT.symbols) if hasattr(pe, "DIRECTORY_ENTRY_EXPORT") else 0
    c.setdefault("reloc-bad", 0)
    pe.close()
    return dict(c), bad, blame


# ---------------------------------------------------------------- build
def admit(r, sites, lost, rows, objs, own_data, banned_data):
    """(live units, refusals, names, ctx, owned, not-owned bytes/data by reason).
    Own-data iterates: ownership depends on which units are live (writable data
    must be referenced only from them), and units binding data that is not owned
    are held to retail's content again."""
    opts = {"defer": True}
    if not own_data:
        live, refused, names = bi.overlay_plan(r, sites, lost, rows, objs, opts)
        return live, refused, names, opts["ctx"], {}, collections.Counter(), collections.Counter()
    by_target = target_index(r, sites)
    opts.update(datum_extent=datum_extent, datum_refs={}, defer_data=True, own={})
    live, refused, names = bi.overlay_plan(r, sites, lost, rows, objs, opts)
    owned, nb, nd = {}, collections.Counter(), collections.Counter()
    for _ in range(6):
        owned, nb, nd = plan_own(r, live, opts["ctx"]["datum_refs"], by_target, objs, banned_data, sites)
        opts.update(defer_data=False, own={k: v[0] for k, v in owned.items()}, datum_refs={})
        live2, refused, names = bi.overlay_plan(r, sites, lost, rows, objs, opts)
        stable = {u.rva for u in live2} == {u.rva for u in live}
        live = live2
        if stable:
            again = plan_own(r, live, opts["ctx"]["datum_refs"], by_target, objs, banned_data, sites)[0]
            if again.keys() == owned.keys():
                break
    return live, refused, names, opts["ctx"], owned, nb, nd


def build_image(base=0x10000000, out=bi.OUT, tag="boot", overlay=(), status=bi.LINK_STATUS, rows=None,
                relayout=True, own_data=False, seed=0, rounds=3, objs=None):
    """Link and check a relaid (and/or own-data) overlay image; the report has
    boot_image.build_image's keys (`check` holds the semantic check) plus `relayout`
    (and `own_data`). `objs` replaces link_cycle.Objects (tests mutate objects);
    report["_layout"] (not written to JSON) holds the last round's pieces."""
    import link_cycle
    out = Path(out).resolve()                         # link.exe runs in `out`
    out.mkdir(parents=True, exist_ok=True)
    r = bi.Retail()
    t0 = time.time()
    sites, info = bi.all_sites(r)
    lost = tuple(int(x, 16) for x in info["lost_pages"])
    rows = bi.overlay_rows(overlay, status) if rows is None else rows
    branches, raw = branch_sweep(r, sites, out)
    objs = objs or link_cycle.Objects([])
    refused_by_check, banned_data, history = [], set(), []
    for rnd in range(rounds):
        drop = {x["target_rva"] for x, _ in refused_by_check}
        todo = [x for x in rows if x["target_rva"] not in drop]
        live, refused, names, ctx, owned, nb, nd = admit(r, sites, lost, todo, objs, own_data, banned_data)
        refused = refused + refused_by_check
        usites = sorted(set(sites) | {u.rva + o for u in live for o, k, n in u.relocs
                                      if k == bi.DIR32 and n not in bi.ABSOLUTE})
        pinned = {} if relayout else {u.rva: "relayout-off" for u in live}
        for _ in range(4):
            pieces, problems = bi.plan(r, usites, live)
            moved_units, kept, redirects, mcounts = choose_moves(r, live, branches, pinned, set(usites), raw)
            scaffold, moved, bad_redirects = relayout_pieces(pieces, moved_units, redirects, seed)
            if not bad_redirects:
                break
            pinned.update({x: "redirect-not-placeable" for x in bad_redirects})
        datums = datum_pieces(r, owned, objs, ctx)
        names = dict(names)
        names.update(ctx["need"])
        mspans = Spans([(p.start, p.start + p.size, 0, "m") for p in moved]
                       + [(p.start, p.start + p.size, 0, "d") for p, _, _ in datums])
        inner = {n: a for n, a in names.items() if mspans.find(a)}
        outer = {n: a for n, a in names.items() if n not in inner}
        for stale in list(out.glob("scaffold*.obj")) + list(out.glob("overlay*.obj")) + list(out.glob("moved*.obj")):
            stale.unlink()
        used, objfiles = bi.write_scaffold(r, scaffold, out / "scaffold.obj", outer)
        inplace = [p for p in scaffold if p.unit is not None]
        if inplace:
            more, paths = bi.write_overlay(inplace, out / "overlay.obj", outer)
            used, objfiles = sorted(set(used) | set(more)), objfiles + paths
        if moved or datums:
            more, paths = write_moved(moved, datums, out / "moved.obj", inner)
            used, objfiles = sorted(set(used) | set(more)), objfiles + paths
        by_sym = {}
        for e in r.imports().values():
            by_sym.setdefault(bi.import_symbol(e), e)
        bi.write_import_lib([(n, by_sym[n]) for n in used], out / "retail_imports.lib")
        descs = bi.descriptor_libs(sorted({by_sym[n][0] for n in used}), out)
        rc, log, secs = bi.link_image(objfiles + [out / "retail_imports.lib"] + descs, base, out, tag)
        ov = bi.overlay_report(r, live, refused, rows, out / (tag + ".overlay.csv"))
        ov["specs"] = list(overlay)
        report = {"base": hex(base), "relocs": info, "problems": dict(problems), "pieces": len(scaffold) + len(moved),
                  "imports_used": len(used), "link_exit": rc, "link_seconds": round(secs, 1),
                  "link_log": log.strip().splitlines()[-20:], "overlay": ov}
        moved_bytes = sum(p.size for p in moved)
        report["relayout"] = {
            "mode": ("relayout" if relayout else "in-place") + ("+own-data" if own_data else ""), "seed": seed,
            "round": rnd + 1, "units": len(live), "units_moved": len(moved), "units_kept": len(kept),
            "kept_by_reason": dict(collections.Counter(kept.values()).most_common()),
            "bytes_moved": moved_bytes, "share_of_overlay_bytes_moved": round(moved_bytes / max(1, ov["bytes"]), 4),
            "moves": dict(mcounts), "redirects_not_placed": len(bad_redirects),
            "sweep": validate_sweep(live, branches)}
        if own_data:
            refs = ctx.get("datum_refs", {})
            refd = {x[0]: x[1] for u in live for x in refs.get(u.rva, ())}
            report["own_data"] = {
                "data_owned": len(datums), "bytes_ours": sum(p.size for p, _, _ in datums),
                "bytes_ours_writable": sum(p.size for p, _, _ in datums if p.name == ".odata"),
                "data_referenced": len(refd), "bytes_referenced": sum(refd.values()),
                "bytes_still_retail_by_reason": dict(nb.most_common()),
                "data_still_retail_by_reason": dict(nd.most_common())}
        if rc:
            break
        publics = bi.read_publics(out / (tag + ".map"), base)
        counts, bad, blame = check_semantic(r, scaffold, moved, datums, branches, usites, out / (tag + ".exe"),
                                            base, publics)
        report.update(check=counts, check_bad=bad)
        report["check_blame"] = sorted("%s %#x %s" % (k[0], k[1], v) for k, v in blame.items())[:50]
        report["pieces_map"] = [[p.name, p.start, publics[p.public], p.size] for p in scaffold] + \
                               [[p.name, p.start, publics[p.public], p.size] for p in moved] + \
                               [[p.name, p.start, publics[p.public], p.size] for p, _, _ in datums]
        report["authored"] = [[u.rva, u.size, u.rows[0]["name"]] for u in live]
        layout = {"scaffold": scaffold, "moved": moved, "datums": datums, "branches": branches, "sites": usites,
                  "publics": publics}
        history.append({"round": rnd + 1, "units": len(live), "moved": len(moved), "blamed": len(blame),
                        "reloc-bad": counts.get("reloc-bad"), "bytes-differ": counts.get("bytes-differ"),
                        "examples": bad[:8]})
        unit_blame = {k[1]: v for k, v in blame.items() if k[0] == "unit"}
        data_blame = {k[1] for k in blame if k[0] == "datum"}
        if not blame or rnd + 1 == rounds:
            break
        by_rva = {u.rva: u for u in live}
        refused_by_check += [(x, "check-" + why) for rva, why in unit_blame.items() for x in by_rva[rva].rows]
        banned_data |= data_blame
    report["rounds"] = history
    ok = bi.image_ok(report) and not report.get("check", {}).get("reloc-bad")
    report["overlay"]["verified_bytes"] = report["overlay"]["bytes"] if ok else 0
    report["seconds"] = round(time.time() - t0, 1)
    (out / (tag + ".json")).write_text(json.dumps(report, indent=1), encoding="utf-8")
    if not rc:
        report["_layout"] = layout
    return report


# ---------------------------------------------------------------- static findings
STATIC_QUEUE = bi.OUT / "static_queue.json"
INLINE_GAP = 16


def inline_data_findings(r, sites, rows, starts, ledger=None):
    """Rows that read retail bytes just past their own extent: a relocated field in the
    row points into .text after the row's end and before the next known function start,
    where no ledger row is (an /RTC frame descriptor `lea edx, [desc]`, a constant the
    row returns the address of), within INLINE_GAP bytes of the end and with no int3
    padding before it (past padding it is an unnamed function's entry). In place this works only because retail's bytes follow
    the row; moved, the row reads whatever follows its copy. `ledger` (all matched rows,
    default `rows`) decides what another row owns."""
    tstart, _, text = r.secs[".text"]
    ext = sorted({(int(x["target_rva"], 16), int(x["target_size"] or 0)) for x in (ledger or rows)})
    los = [e[0] for e in ext]
    starts = sorted(starts)
    startset = set(starts)

    def owned(t):
        i = bisect.bisect_right(los, t) - 1
        while i >= 0 and los[i] > t - OWN_CAP:
            if t < los[i] + ext[i][1]:
                return True
            i -= 1
        return False
    out = []
    for row in rows:
        lo, n = int(row["target_rva"], 16), int(row["target_size"] or 0)
        if n <= 0 or not tstart <= lo < bi.FUNCLETS:
            continue
        k = bisect.bisect_right(starts, lo)
        nxt = min(starts[k] if k < len(starts) else bi.FUNCLETS, bi.FUNCLETS)
        reads = []
        for s in sites[bisect.bisect_left(sites, lo):bisect.bisect_left(sites, lo + n - 3)]:
            t = r.u32(s) - bi.RETAIL_BASE
            if lo + n <= t < min(nxt, lo + n + INLINE_GAP) and t not in startset and not owned(t)                     and 0xCC not in text[lo + n - tstart:t - tstart]:
                reads.append((s, t))
        if reads:
            last = max(t for _, t in reads)
            out.append({"target_rva": row["target_rva"], "name": row["name"], "source": row["source"],
                        "size": n, "check": "inline-data",
                        "why": f"reads retail .text past its extent: field {reads[0][0]:#x} -> {reads[0][1]:#x} "
                               f"({len(reads)} field(s), up to +{last - lo - n:#x} past its end {lo + n:#x}, next "
                               f"known start {nxt:#x}) that no row owns; row the data or raise the extent over it "
                               "(an object label at its end binds to the moved copy's end)",
                        "fields": [[f"{s:#x}", f"{t:#x}"] for s, t in reads]})
    return out


def table_slots(r, rlo, siteset, starts=frozenset()):
    """Dwords from rlo that are relocation sites into .text, up to the next datum the
    data ledger starts (retail's table length)."""
    n = 0
    while rlo + 4 * n in siteset and r.section_of(r.u32(rlo + 4 * n) - bi.RETAIL_BASE) == ".text" and             (n == 0 or rlo + 4 * n not in starts):
        n += 1
    return n


def datum_starts():
    """Retail addresses reverse/data_ledger.csv starts a datum at (vtables abut without
    RTTI: one class's table runs straight into the next one's)."""
    import csv
    path = bi.ROOT / "reverse" / "data_ledger.csv"
    if not path.exists():
        return frozenset()
    with open(path, newline="", encoding="utf-8") as f:
        return frozenset(int(x["address"], 16) for x in csv.DictReader(f) if x.get("address"))


def truncated_table_findings(r, sites, rows, objs, starts=None):
    """Rows whose object defines a table of code pointers (a vtable, a dispatch table)
    shorter than retail's: plan_own's `code-pointer-table-continues-in-retail` rule,
    applied to every DIR32 reference a row's unit makes to data its object defines. The
    datum's retail start is the row's retail field minus the reference's offset in the
    datum. Owned (--own-data), a call through a slot past the object's copy reads
    garbage (Debug's 1-slot vtable against retail's 49). A table that ends where the
    data ledger (`starts`) starts another datum is whole: the next class's vtable."""
    siteset = set(sites)
    starts = datum_starts() if starts is None else starts
    units, _ = bi.find_units(r, rows, objs)
    found = {}
    for u in units:
        secs, syms, data = u.obj
        s = secs[u.sec - 1]
        for off, si, kind in s.relocs:
            o = off - u.off
            if kind != bi.DIR32 or not 0 <= o <= u.size - 4 or not r.section_of(u.rva + o):
                continue
            y = syms[si]
            if not 0 < y.sec <= len(secs) or secs[y.sec - 1].name.startswith(".text"):
                continue
            q = y.value + struct.unpack_from("<i", data, s.ptr + off)[0]
            lo, n = datum_extent(u.obj, y.sec, q)
            rlo = r.u32(u.rva + o) - bi.RETAIL_BASE - (q - lo)
            if n < 4 or r.section_of(rlo) is None or rlo + n in starts or                     not table_continues(r, rlo, n, siteset):
                continue
            slots = table_slots(r, rlo, siteset, starts)
            if 4 * slots <= n:                          # the object's copy is not shorter
                continue
            for row in u.rows:
                f = found.setdefault((row["target_rva"], row["name"]), {
                    "target_rva": row["target_rva"], "name": row["name"], "source": row["source"],
                    "size": int(row["target_size"] or 0), "check": "truncated-table", "tables": []})
                if all(x[0] != f"{rlo:#x}" for x in f["tables"]):
                    f["tables"].append([f"{rlo:#x}", y.name, n, 4 * slots])
    out = []
    for f in found.values():
        rlo, name, n, rn = f["tables"][0]
        more = len(f["tables"]) - 1
        f["why"] = (f"its object defines {name} at retail {rlo} as {n} byte(s); retail's code-pointer table "
                    f"runs on ({rn} bytes of .text pointers from there)" + (f", and {more} more table(s)" if more
                                                                             else "")
                    + "; declare the whole class / table in the object")
        out.append(f)
    return out


def static_findings(overlay=("Code/",), rows=None, objs=None, tables=True, ledger=None):
    """{"inline-data": [...], "truncated-table": [...]} for the overlay's rows, judged
    from the ledger, retail game.dat and (tables) the rows' objects: no link, no run."""
    import link_cycle
    r = bi.Retail()
    sites, _ = bi.all_sites(r)
    rows = bi.overlay_rows(overlay) if rows is None else rows
    if ledger is None:
        ledger = [x for x in bi.ledger_rows() if x["status"] == "matched"]
    out = {"inline-data": inline_data_findings(r, sites, rows, bi.function_starts(), ledger)}
    if tables:
        out["truncated-table"] = truncated_table_findings(r, sites, rows, objs or link_cycle.Objects([]))
    return out


def queue_items(found):
    """repair_queue items, each with its own check and pass test."""
    return [dict(f, pass_test=f"python3 tools/boot_relayout.py findings --overlay rva:{f['target_rva']} "
                              f"--only {check} --no-write  (exit 0: the row is no longer flagged)")
            for check, fs in found.items() for f in fs]


def main(argv=None):
    import argparse
    import sys
    ap = argparse.ArgumentParser(description="Static relayout findings: no link, no game run")
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("findings", help="rows that read data past their extent, or whose object defines a "
                                        "truncated code-pointer table; writes build/boot/static_queue.json")
    p.add_argument("--overlay", action="append", help="row set, as boot_image.py link --overlay (default Code/)")
    p.add_argument("--only", choices=("inline-data", "truncated-table"))
    p.add_argument("--out", type=Path, default=STATIC_QUEUE, help="repair_queue reads it (REPAIR_STATIC)")
    p.add_argument("--no-write", action="store_true", help="list only; exit 1 when a row is flagged")
    p.add_argument("--limit", type=int, default=20)
    a = ap.parse_args(argv)
    overlay = a.overlay or ["Code/"]
    t0 = time.time()
    found = static_findings(overlay, tables=a.only != "inline-data")
    if a.only:
        found = {a.only: found[a.only]}
    for check, fs in found.items():
        extra = (f", {len({t[0] for f in fs for t in f['tables']})} distinct table(s)"
                 if check == "truncated-table" else "")
        print(f"{check}: {len(fs)} row(s){extra}")
        for f in fs[:a.limit]:
            print(f"  {f['target_rva']} {f['name'][:70]}  {f['source']}\n      {f['why'][:220]}")
    items = queue_items(found)
    print(f"{len(items)} item(s), {time.time() - t0:.0f} s", file=sys.stderr)
    if a.no_write:
        return 1 if items else 0
    a.out.parent.mkdir(parents=True, exist_ok=True)
    a.out.write_text(json.dumps({"tool": "boot_relayout findings", "overlay": overlay, "items": items}, indent=1),
                     encoding="utf-8")
    print(f"-> {a.out}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
