#!/usr/bin/env python3
"""Class layouts read from retail constructor, destructor and allocation bytes.

WHY. Retail is /GR-: no RTTI descriptors, so no vftable carries a class name and
reverse/vtables.tsv (Ghidra, symbol-name driven) lists only the 160 tables the
PE export directory names. The constructors carry the layout instead, and the
ledger names them (`??0Class@@`, each name verified by the byte gate):

  vftable stores  `mov [this+N], offset vftable` sets the subobject at N. The
                  last store per offset is the class's own table for the base
                  at N; an earlier store at N is an inlined base constructor's
                  table, which names that base through the index of every
                  constructor's own tables.
  vbtable stores  a table of small offsets stored at [this+N] (in the
                  most-derived block) is a vbptr: entry 0 places the subobject
                  that owns it, entries 1.. place the virtual bases.
  base calls      `lea ecx, [this+N]; call ??0Base@@` before the class sets its
                  own vptrs is a base constructor (MSVC builds bases, then sets
                  the vptrs, then the members); after them it is a member.
  operator new    `push SIZE; call ??2@YAPAXI@Z` followed by the constructor
                  call at an allocation site gives sizeof, the virtual bases
                  included.
  field writes    `this`-relative stores in the body are field offsets and widths.

Every fact carries its provenance: the rule, the retail sites that prove it and
whether it is a target fact (read from retail bytes) or an inference (a rule
applied to target facts). Facts that disagree across constructors are flagged,
never voted.

The vftable extractor (`tables`) needs no symbol names: a table is any .rdata
address a matched body stores as a vptr, and its slots run while the words are
code addresses (thunks and stubs included) and stop at the next stored, exported
or listed table.

    python3 tools/retail_layout.py --class Object          one class
    python3 tools/retail_layout.py --tables                 vftable coverage
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

ROOT = Path(__file__).resolve().parent.parent
REVERSE = ROOT / "reverse"
LEDGER = REVERSE / "functions.csv"
VTABLES = REVERSE / "vtables.tsv"
IMAGE_BASE = 0x400000
MAX_SLOTS = 1024
CTOR = re.compile(r"^\?\?0(.+?)@@[AIQ]AE")
DTOR = re.compile(r"^\?\?1(.+?)@@[AIQU]AE")
# Scalar operator new only: `??_U` (operator new[]) allocates count * sizeof
# plus a cookie, which the allocation site does not resolve.
ALLOCATOR = re.compile(r"^\?\?2")


def demangle_scope(scope):
    """`Inner@Outer` -> `Outer::Inner`; template scopes stay mangled."""
    if scope.startswith("?$"):
        return scope
    return "::".join(reversed(scope.split("@")))


# ---------------------------------------------------------------- image

class Image:
    """Retail bytes by RVA with the section ranges the rules need."""

    def __init__(self, read, sections, exports=None):
        self.read = read
        self.sections = sections
        self.exports = exports or {}
        self.code = [(s["rva"], s["rva"] + s["size"]) for s in sections if s["name"] == ".text"]
        self.rdata = [(s["rva"], s["rva"] + s["size"]) for s in sections if s["name"] == ".rdata"]

    @classmethod
    def retail(cls):
        sys.path.insert(0, str(ROOT / "tools"))
        import class_layouts
        build = class_layouts.build_module()
        data, sections = build.exe_image()
        return cls(build.read_target_bytes, sections, pe_exports(data))

    def is_code(self, rva):
        return any(a <= rva < b for a, b in self.code)

    def in_rdata(self, rva):
        return any(a <= rva < b for a, b in self.rdata)

    def dword(self, rva):
        return struct.unpack("<I", self.read(rva, 4))[0]

    def sdword(self, rva):
        return struct.unpack("<i", self.read(rva, 4))[0]


def pe_exports(data):
    """{rva: [names]} of the image's exported `??_7` vftable symbols."""
    try:
        import pefile
    except ImportError:
        return {}
    pe = pefile.PE(data=data, fast_load=True)
    pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_EXPORT"]])
    out = collections.defaultdict(list)
    for sym in getattr(getattr(pe, "DIRECTORY_ENTRY_EXPORT", None), "symbols", []):
        if sym.name and sym.name.startswith(b"??_7"):
            out[sym.address].append(sym.name.decode("ascii", "replace"))
    return dict(out)


def export_class(names):
    """The class a `??_7Class@@6B@` export names (the primary table), else None."""
    found = {m.group(1) for n in names for m in [re.match(r"^\?\?_7(.+?)@@6B@$", n)] if m}
    return demangle_scope(found.pop()) if len(found) == 1 else None


# ---------------------------------------------------------------- ledger

class Ledger:
    """Matched rows by RVA, with every name at an address."""

    def __init__(self, rows):
        self.rows = rows
        self.by_rva = collections.defaultdict(list)
        for r in rows:
            self.by_rva[int(r["target_rva"], 16)].append(r)
        self.starts = sorted(self.by_rva)

    @classmethod
    def load(cls, path=LEDGER):
        with Path(path).open(newline="", encoding="utf-8") as handle:
            return cls([r for r in csv.DictReader(handle) if r["status"] == "matched"])

    def names(self, rva):
        return [r["name"] for r in self.by_rva.get(rva, [])]

    def name(self, rva):
        names = self.names(rva)
        real = [n for n in names if not n.startswith(("gen-", "$L", "__ehhandler"))]
        return (real or names or [None])[0]

    def ctor_classes(self, rva):
        """Classes whose constructor the ledger names at `rva` (ICF folds give several)."""
        return sorted({demangle_scope(m.group(1)) for n in self.names(rva) for m in [CTOR.match(n)] if m})

    def bodies(self):
        """(rva, size) of every distinct matched body."""
        out = {}
        for rva, rows in self.by_rva.items():
            out[rva] = max(int(r["target_size"], 0) for r in rows)
        return sorted(out.items())

    def allocators(self):
        if not hasattr(self, "_allocators"):
            self._allocators = {rva for rva, rows in self.by_rva.items()
                                if any(ALLOCATOR.match(r["name"]) for r in rows)}
        return self._allocators

    def of_class(self, name, pattern):
        """[(rva, size)] of the rows whose name `pattern` (CTOR or DTOR) matches with `name`'s scope."""
        index = self.__dict__.setdefault("_scopes", {})
        if pattern.pattern not in index:
            got = collections.defaultdict(dict)
            for r in self.rows:
                m = pattern.match(r["name"])
                if m:
                    got[m.group(1)][int(r["target_rva"], 16)] = int(r["target_size"], 0)
            index[pattern.pattern] = got
        return sorted(index[pattern.pattern].get("@".join(reversed(name.split("::"))), {}).items())


# ---------------------------------------------------------------- tables

def classify(image, rva):
    """'vftable', 'vbtable' or None for an .rdata address stored as a pointer."""
    if not image.in_rdata(rva) or rva % 4:
        return None
    try:
        first, second = image.dword(rva), image.dword(rva + 4)
    except ValueError:
        return None
    if image.is_code(first - IMAGE_BASE):
        return "vftable"
    s0, s1 = struct.unpack("<ii", struct.pack("<II", first, second))
    # vbtable: entry 0 is minus the vbptr's offset in its subobject (0, -4, ...),
    # entry 1 the first virtual base's distance from the vbptr.
    if -0x1000 < s0 <= 0 and s0 % 4 == 0 and 0 < s1 < 0x10000:
        return "vbtable"
    return None


def vbtable_entries(image, rva):
    out = [image.sdword(rva)]
    for k in range(1, 64):
        value = image.sdword(rva + 4 * k)
        if not 0 < value < 0x10000 or (k > 1 and value <= out[-1]):
            break
        out.append(value)
    return out


def slots(image, rva, boundaries):
    """[(slot, target rva)] of the vftable at `rva`, and why the walk stopped.

    Slots run while the word is a code address (a thunk or stub counts: code
    need not be a known function) and stop at the next known table start. With
    no RTTI between tables, a table nothing stores can still sit inside the
    span: the count is an upper bound unless the next start is known."""
    out = []
    for k in range(MAX_SLOTS):
        at = rva + 4 * k
        if k and at in boundaries:
            return out, "next-table"
        try:
            word = image.dword(at)
        except ValueError:
            return out, "end"
        if not image.is_code(word - IMAGE_BASE):
            return out, "non-code"
        out.append((k, word - IMAGE_BASE))
    return out, "cap"


def listed_tables(path=VTABLES):
    out = collections.defaultdict(dict)
    if Path(path).exists():
        with Path(path).open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle, delimiter="\t"):
                out[int(row["vtable_rva"], 16)][int(row["slot"])] = int(row["func_rva"], 16)
    return out


# ---------------------------------------------------------------- one body

def _cs():
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    return md


# Frame helpers that keep ecx: `mov eax, handler; call __EH_prolog` opens a
# constructor with `this` still in ecx, and __chkstk probes the frame.
TRANSPARENT = ("__EH_prolog", "__SEH_prolog", "__chkstk", "__alloca_probe")


def body_events(image, rva, size, kinds, md=None, transparent=()):
    """Ordered `this`-relative events of one thiscall body.

    kinds(rva) -> 'vftable' | 'vbtable' | None. Events:
      ('vptr', off, table, site)        vftable stored at this+off
      ('vbptr', off, table, site)       vbtable stored at this+off
      ('call', off, callee, site)       direct call with ecx = this+off
      ('field', off, width, site)       other this-relative write
      ('vptr-other', disp, table, site) vftable stored through a pointer that is not this
    `this` is followed through register copies, `lea`, stack spills and the
    vbtable reads that address virtual bases ([vbe + this + d])."""
    from capstone import x86
    md = md or _cs()
    regs = {x86.X86_REG_ECX: ("this", 0)}
    spills, vbptrs, events = {}, {}, []
    code = image.read(rva, size)

    def this_of(mem):
        """Offset from this of a [base + index*1 + disp] operand, else None."""
        b, i = regs.get(mem.base), regs.get(mem.index) if mem.index else None
        if mem.index == 0 and b and b[0] == "this":
            return b[1] + mem.disp
        if i is not None and mem.scale == 1 and b:
            pair = {b[0]: b, i[0]: i}
            if "this" in pair and "vbe" in pair:
                return pair["this"][1] + pair["vbe"][1] + mem.disp
        return None

    for insn in md.disasm(code, rva):
        ops, site = insn.operands, insn.address
        name = insn.mnemonic
        dest = ops[0] if ops else None
        if name == "call":
            target = ops[0].imm if ops and ops[0].type == x86.X86_OP_IMM else None
            ecx = regs.get(x86.X86_REG_ECX)
            if target in transparent:
                continue
            if target is not None and ecx and ecx[0] == "this":
                events.append(("call", ecx[1], target, site))
            for reg in (x86.X86_REG_EAX, x86.X86_REG_ECX, x86.X86_REG_EDX):
                regs.pop(reg, None)
            continue
        if dest is not None and dest.type == x86.X86_OP_MEM and name.startswith(("mov", "and", "or", "inc", "dec",
                                                                                    "add", "sub", "fst", "fist")):
            if dest.mem.base == x86.X86_REG_EBP and dest.mem.index == 0 and name == "mov":
                src = regs.get(ops[1].reg) if len(ops) > 1 and ops[1].type == x86.X86_OP_REG else None
                spills[dest.mem.disp] = src if src and src[0] == "this" else None
                continue
            off = this_of(dest.mem)
            if off is None and name == "mov" and len(ops) == 2 and ops[1].type == x86.X86_OP_IMM                     and dest.mem.base not in (x86.X86_REG_ESP, x86.X86_REG_EBP, 0)                     and kinds((ops[1].imm & 0xFFFFFFFF) - IMAGE_BASE) == "vftable":
                # A vptr stored through another object (an inlined constructor
                # of a member or a new'd object): proves the table, not this layout.
                events.append(("vptr-other", dest.mem.disp, (ops[1].imm & 0xFFFFFFFF) - IMAGE_BASE, site))
                continue
            if off is not None:
                if name == "mov" and len(ops) == 2 and ops[1].type == x86.X86_OP_IMM:
                    table = (ops[1].imm & 0xFFFFFFFF) - IMAGE_BASE
                    kind = kinds(table)
                    if kind == "vftable":
                        events.append(("vptr", off, table, site))
                        continue
                    if kind == "vbtable":
                        vbptrs[off] = table
                        events.append(("vbptr", off, table, site))
                        continue
                events.append(("field", off, dest.size, site))
            continue
        if dest is not None and dest.type == x86.X86_OP_REG and len(ops) == 2:
            src = ops[1]
            value = None
            if name == "mov" and src.type == x86.X86_OP_REG:
                value = regs.get(src.reg)
            elif name == "lea" and src.type == x86.X86_OP_MEM and src.mem.index == 0:
                b = regs.get(src.mem.base)
                if b and b[0] == "this":
                    value = ("this", b[1] + src.mem.disp)
            elif name == "mov" and src.type == x86.X86_OP_MEM:
                if src.mem.base == x86.X86_REG_EBP and src.mem.index == 0:
                    value = spills.get(src.mem.disp)
                else:
                    b = regs.get(src.mem.base) if src.mem.index == 0 else None
                    if b and b[0] == "this" and b[1] + src.mem.disp in vbptrs:
                        value = ("vbp", b[1] + src.mem.disp)
                    elif b and b[0] == "vbp" and src.mem.disp % 4 == 0:
                        value = ("vbe", b[1] + image.sdword(vbptrs[b[1]] + src.mem.disp) - b[1])
                        # [vbe + this + d] addresses vbptr + entry + d; keep the
                        # entry relative to this by folding the vbptr's offset in.
                        value = ("vbe", image.sdword(vbptrs[b[1]] + src.mem.disp))
            regs.pop(dest.reg, None)
            if value is not None:
                regs[dest.reg] = value
            continue
        try:
            written = insn.regs_access()[1]
        except Exception:
            written = ()
        for reg in written:
            if reg != x86.X86_REG_ESP:
                regs.pop(reg, None)
    return events


# ---------------------------------------------------------------- the engine

class Engine:
    """Retail layouts for every ledger class at once, sharing one table index."""

    def __init__(self, image, ledger, listed=None, cache_dir=None):
        self.cache_dir = cache_dir
        self.image, self.ledger = image, ledger
        self.listed = listed if listed is not None else listed_tables()
        self.md = _cs()
        self._kinds, self._events, self._calls = {}, {}, None
        self._owners = None
        self.transparent = {rva for rva, rows in ledger.by_rva.items() if any(r["name"] in TRANSPARENT for r in rows)}

    # ---- table kinds and stores across the ledger
    def kind(self, rva):
        if rva not in self._kinds:
            self._kinds[rva] = classify(self.image, rva)
        return self._kinds[rva]

    def events(self, rva, size):
        if rva not in self._events:
            try:
                self._events[rva] = body_events(self.image, rva, size, self.kind, self.md, self.transparent)
            except ValueError:
                self._events[rva] = []
        return self._events[rva]

    def stored_tables(self):
        """{table rva: store count} of every vftable/vbtable a matched body stores at any this-offset."""
        cached = self._cache("stored")
        if cached is not None:
            return collections.Counter({int(k): v for k, v in cached.items()})
        stores = self._stored_scan()
        self._cache("stored", {str(k): v for k, v in stores.items()})
        return stores

    def _cache(self, key, value=None):
        """build/retail_layout/<key>.json, keyed by the ledger and this tool (no cache for test engines)."""
        if self.cache_dir is None:
            return None
        import hashlib
        stamp = hashlib.sha1()
        for path in (LEDGER, Path(__file__), VTABLES):
            stamp.update(path.read_bytes() if path.exists() else b"")
        path = self.cache_dir / f"{key}.json"
        if value is None:
            try:
                got = json.loads(path.read_text(encoding="utf-8"))
                return got["value"] if got.get("stamp") == stamp.hexdigest() else None
            except (OSError, ValueError):
                return None
        self.cache_dir.mkdir(parents=True, exist_ok=True)
        path.write_text(json.dumps({"stamp": stamp.hexdigest(), "value": value}), encoding="utf-8")
        return value

    def _stored_scan(self):
        stores = collections.Counter()
        for rva, size in self.ledger.bodies():
            if size > 0x8000:
                continue
            for ev in self.events(rva, size):
                if ev[0] in ("vptr", "vbptr", "vptr-other"):
                    stores[ev[2]] += 1
        return stores

    def boundaries(self, stored=None):
        stored = stored if stored is not None else self.stored_tables()
        return set(stored) | set(self.image.exports) | set(self.listed)

    def owners(self):
        """{vftable rva: set of classes whose constructor stores it last at offset 0}."""
        if self._owners is None:
            cached = self._cache("owners")
            if cached is not None:
                self._owners = collections.defaultdict(set, {int(k): set(v) for k, v in cached.items()})
                return self._owners
            out = collections.defaultdict(set)
            for r in self.ledger.rows:
                m = CTOR.match(r["name"])
                if not m:
                    continue
                final = self.final_vptrs(int(r["target_rva"], 16), int(r["target_size"], 0))
                if 0 in final:
                    out[final[0][0]].add(demangle_scope(m.group(1)))
            for rva, names in self.image.exports.items():
                cls = export_class(names)
                if cls:
                    out[rva].add(cls)
            self._owners = out
            self._cache("owners", {str(k): sorted(v) for k, v in out.items()})
        return self._owners

    def table_class(self, table):
        owners = sorted(self.owners().get(table, ()))
        return owners[0] if len(owners) == 1 else None, owners

    def final_vptrs(self, rva, size):
        """{offset: (table, kind, event index)} of the last pointer store per offset."""
        out = {}
        for i, ev in enumerate(self.events(rva, size)):
            if ev[0] in ("vptr", "vbptr"):
                out[ev[1]] = (ev[2], ev[0], i)
        return out

    def call_index(self):
        """{callee rva: [call sites]} for every E8 rel32 in .text."""
        if self._calls is None:
            self._calls = collections.defaultdict(list)
            for start, end in self.image.code:
                code = self.image.read(start, end - start)
                for m in re.finditer(b"\xe8", code):
                    i = m.start()
                    if i + 5 <= len(code):
                        self._calls[start + i + 5 + struct.unpack_from("<i", code, i + 1)[0]].append(start + i)
        return self._calls

    def call_sites_near(self, site):
        """Direct call sites in the 0x60 bytes before `site`."""
        if not hasattr(self, "_sites"):
            self._sites = sorted(s for sites in self.call_index().values() for s in sites)
        i = bisect.bisect_left(self._sites, site - 0x60)
        return self._sites[i:bisect.bisect_left(self._sites, site)]

    def passes_new_pointer(self, start, site):
        """The allocator's result (eax at `start`) reaches the call at `site` unchanged in ecx.

        `lea ecx, [eax+N]` constructs a member of the new object, not the object."""
        from capstone import x86
        held = {x86.X86_REG_EAX}
        for insn in self.md.disasm(self.image.read(start, site - start + 5), start):
            if insn.address == site:
                return x86.X86_REG_ECX in held
            ops = insn.operands
            if insn.mnemonic == "mov" and len(ops) == 2 and ops[0].type == ops[1].type == x86.X86_OP_REG:
                if ops[1].reg in held:
                    held.add(ops[0].reg)
                else:
                    held.discard(ops[0].reg)
                continue
            try:
                written = insn.regs_access()[1]
            except Exception:
                written = ()
            held -= set(written)
        return False

    def vptr_overwritten(self, site):
        """A vftable stored at [reg] in the 16 instructions after the constructor call at `site`.

        An inlined derived constructor calls its base, then installs its own
        table: the allocation then holds the derived object."""
        from capstone import x86
        for n, insn in enumerate(self.md.disasm(self.image.read(site + 5, 0x60), site + 5)):
            if n >= 16 or insn.mnemonic.startswith("ret"):
                return False
            ops = insn.operands
            if insn.mnemonic == "mov" and len(ops) == 2 and ops[0].type == x86.X86_OP_MEM \
                    and ops[0].mem.disp == 0 and ops[0].mem.index == 0 and ops[1].type == x86.X86_OP_IMM \
                    and ops[0].mem.base not in (x86.X86_REG_ESP, x86.X86_REG_EBP) \
                    and self.kind((ops[1].imm & 0xFFFFFFFF) - IMAGE_BASE) == "vftable":
                return True
        return False

    def allocation_sizes(self, ctor):
        """Counter of the `push SIZE; call operator new` sizes that reach a call to `ctor`.

        The size is the last push before the allocator call in the 0x60 bytes
        ahead of the constructor call site, with no other call in between."""
        allocs = self.ledger.allocators()
        found = collections.Counter()
        sites = {}
        for site in self.call_index().get(ctor, []):
            window = self.image.read(site - 0x60, 0x60)
            best = None
            for m in re.finditer(rb"(?:\x68(....)|\x6a(.))\xe8(....)", window, re.S):
                call_at = site - 0x60 + m.start() + (5 if m.group(1) else 2)
                callee = call_at + 5 + struct.unpack("<i", m.group(3))[0]
                if callee in allocs:
                    size = struct.unpack("<I", m.group(1))[0] if m.group(1) else m.group(2)[0]
                    best = (size, call_at)
            if best:
                # Another direct call between the allocation and the constructor
                # (a second object, a helper) would break the link: refuse it.
                if any(best[1] < other < site for other in self.call_sites_near(site)) \
                        or not self.passes_new_pointer(best[1] + 5, site) or self.vptr_overwritten(site):
                    continue
                found[best[0]] += 1
                sites.setdefault(best[0], []).append(site)
        return found, sites

    # ---- one class
    def analyze_ctor(self, rva, size):
        evs = self.events(rva, size)
        final = self.final_vptrs(rva, size)
        # The vbptrs are set first, in the most-derived block, before any base
        # runs: only the class's own vftable stores mark the end of the bases.
        boundary = min((i for _, kind, i in final.values() if kind == "vptr"), default=len(evs))
        facts = {"vptrs": {}, "vbptrs": {}, "subobject_vptrs": {}, "inlined_bases": {}, "base_calls": {},
                 "member_calls": {}, "fields": {}, "boundary": boundary}
        # A vptr store at this+N proves a base only with base-phase evidence at N:
        # a store or a call there before the class installs its own tables. The
        # store that opens the installation is the class's own primary table.
        # A table stored at N only afterwards belongs to a subobject retail
        # cannot place: a member constructed after the vptrs, or a base whose
        # inlined constructor left no store. Recorded, never a base.
        early = {ev[1] for ev in evs[:boundary] if ev[0] in ("vptr", "vbptr", "call")}
        for off, (table, kind, i) in sorted(final.items()):
            if kind == "vbptr":
                facts["vbptrs"][off] = table
            elif off in early or i == boundary:
                facts["vptrs"][off] = table
            else:
                facts["subobject_vptrs"][off] = table
        for i, ev in enumerate(evs):
            tag, off = ev[0], ev[1]
            if tag == "vptr" and i < boundary and final.get(off, (None,))[0] != ev[2]:
                facts["inlined_bases"].setdefault(off, ev[2])
            elif tag == "call":
                (facts["base_calls"] if i < boundary else facts["member_calls"]).setdefault(off, ev[2] - 0)
            elif tag == "field" and i >= boundary:
                facts["fields"].setdefault(off, set()).add(ev[2])
        return facts

    def contract(self, name):
        """The retail layout of `name` with per-fact provenance."""
        ctors = self.ledger.of_class(name, CTOR)
        dtors = self.ledger.of_class(name, DTOR)
        out = {"class": name, "ctors": ["%#x" % r for r, _ in ctors], "dtors": ["%#x" % r for r, _ in dtors],
               "facts": {}, "conflicts": [], "confidence": "none"}
        if not ctors and not dtors:
            return out
        per = {rva: self.analyze_ctor(rva, size) for rva, size in ctors}
        facts, conflicts = out["facts"], out["conflicts"]

        def fact(key, value, rule, sites, kind="target"):
            facts[key] = {"value": value, "rule": rule, "kind": kind, "sites": sorted({"%#x" % s for s in sites})}

        # vptr layout: every constructor must agree.
        layouts = collections.Counter(tuple(sorted(f["vptrs"].items())) for f in per.values())
        if len(layouts) > 1:
            conflicts.append({"fact": "vftables", "candidates": {repr([(hex(o), hex(t)) for o, t in k]): n
                                                                for k, n in layouts.items()}})
        vptrs = dict(layouts.most_common(1)[0][0]) if len(layouts) == 1 else {}
        vbs = collections.Counter(tuple(sorted(f["vbptrs"].items())) for f in per.values())
        if len(vbs) > 1:
            conflicts.append({"fact": "vbtables", "candidates": {repr(k): n for k, n in vbs.items()}})
        vbptrs = dict(vbs.most_common(1)[0][0]) if len(vbs) == 1 else {}
        # Destructors re-store the class's own tables first: corroboration.
        for rva, size in dtors:
            got = {}
            for e in self.events(rva, size)[:64]:
                if e[0] == "vptr":
                    got.setdefault(e[1], e[2])      # the first store; later ones are inlined base dtors
            got = {o: t for o, t in got.items() if o in vptrs}
            if vptrs and got and any(vptrs[o] != t for o, t in got.items()):
                conflicts.append({"fact": "dtor-vftables", "dtor": "%#x" % rva,
                                  "candidates": {"ctor": {hex(o): hex(t) for o, t in vptrs.items()},
                                                 "dtor": {hex(o): hex(t) for o, t in got.items()}}})
        if not ctors and dtors:
            first = self.events(*dtors[0])
            vptrs = {}
            for e in first:
                if e[0] == "vptr":
                    vptrs.setdefault(e[1], e[2])
        subobjects = {}
        for f in per.values():
            for o, t in f["subobject_vptrs"].items():
                subobjects.setdefault(o, set()).add("%#x" % t)
        if subobjects:
            fact("unknown_subobject_vptrs", {"%#x" % o: sorted(t) for o, t in sorted(subobjects.items())},
                 "retail-ctor-vptr-after-own", [r for r, _ in ctors], "inference")
        if vptrs:
            fact("vftables", {"%#x" % o: "%#x" % t for o, t in sorted(vptrs.items())},
                 "retail-ctor-vptr" if ctors else "retail-dtor-vptr", [r for r, _ in ctors or dtors])

        # Virtual bases from the vbtables.
        vbases = {}
        for off, table in sorted(vbptrs.items()):
            entries = vbtable_entries(self.image, table)
            owner = off + entries[0]
            for k, dist in enumerate(entries[1:], 1):
                vbases.setdefault(off + dist, (owner, table, k))
        if vbptrs:
            fact("vbptrs", {"%#x" % o: "%#x" % t for o, t in sorted(vbptrs.items())}, "retail-ctor-vbtable",
                 [r for r, _ in ctors])

        # Bases, in offset order.
        bases = []
        owners = {o + vbtable_entries(self.image, t)[0] for o, t in vbptrs.items()}
        offsets = set(vptrs) | {o for f in per.values() for o in f["base_calls"]} | owners
        covered = set()          # secondary vptrs a named base brings with it
        polymorphic = bool(vptrs)
        unsure = {}
        for off in sorted(offsets):
            if off in vbases or off in covered:
                continue
            calls = {f["base_calls"].get(off) for f in per.values()} - {None}
            calls = {c for c in calls if self.is_ctor(c)}
            inlined = {f["inlined_bases"].get(off) for f in per.values()} - {None}
            names, rule, base_ctor = set(), None, None
            if not polymorphic and calls:
                # No vptr marks the end of the bases: a constructor called on
                # this+N is a base or a member, and retail cannot tell which.
                unsure[off] = sorted({n for c in calls for n in (self.ledger.ctor_classes(c) or ["%#x" % c])})
                continue
            for callee in calls:
                got = self.ledger.ctor_classes(callee)
                if len(got) > 1 and off not in vptrs:
                    unsure[off] = got       # an ICF-folded constructor on a non-polymorphic subobject
                    continue
                if not got:
                    sub = self.analyze_ctor(callee, self._size(callee))
                    cls = self.table_class(sub["vptrs"][0])[0] if 0 in sub["vptrs"] else None
                    got = [cls] if cls else ["<ctor %#x>" % callee]
                    rule = rule or "retail-ctor-call+callee-table"
                else:
                    rule = rule or "retail-ctor-call"
                names.update(got)
                base_ctor = base_ctor or callee
            if not calls:
                for table in inlined:
                    cls, _ = self.table_class(table)
                    names.add(cls or "<vftable %#x>" % table)
                    rule = rule or ("retail-inlined-base-vptr" if cls else "retail-inlined-base-vptr(unnamed)")
                    if cls and self.ledger.of_class(cls, CTOR):
                        base_ctor = base_ctor or self.ledger.of_class(cls, CTOR)[0][0]
            if not names:
                if off in unsure or (off == 0 and off in vptrs) or (off not in vptrs and off not in owners):
                    continue          # off 0: the class's own primary vptr, no polymorphic base proven
                names.add("<polymorphic base>" if off in vptrs else "<non-polymorphic base>")
                rule = "retail-secondary-vptr" if off in vptrs else "retail-vbptr-owner"
            if base_ctor is not None and len(names) == 1:
                sub = self.analyze_ctor(base_ctor, self._size(base_ctor))
                # Not the base's own virtual bases: where those land depends on the most-derived class.
                moved = {o + d for o, t in sub["vbptrs"].items() for d in vbtable_entries(self.image, t)[1:]}
                covered |= {off + o for o in list(sub["vptrs"]) + list(sub["vbptrs"]) if o and o not in moved}
            if len(names) > 1:
                conflicts.append({"fact": f"base@{off:#x}", "candidates": sorted(names)})
            bases.append({"offset": off, "name": sorted(names)[0] if len(names) == 1 else sorted(names),
                          "rule": rule, "kind": "target" if rule in ("retail-ctor-call", "retail-inlined-base-vptr")
                          else "inference", "own_vftable": "%#x" % vptrs[off] if off in vptrs else None})
        if unsure:
            fact("base_or_member_ctor_calls", {"%#x" % o: n for o, n in sorted(unsure.items())},
                 "retail-ctor-call", [r for r, _ in ctors], "inference")
        if bases:
            fact("bases", bases, "retail-ctor", [r for r, _ in ctors])
        if vbases:
            vlist = []
            for off, (owner, table, k) in sorted(vbases.items()):
                firsts = {f["inlined_bases"].get(off) for f in per.values()} - {None}
                cls = None
                for t in firsts:
                    cls = self.table_class(t)[0] or (export_class(self.image.exports.get(t, [])))
                vlist.append({"offset": off, "via_vbptr": owner, "entry": k, "name": cls or "<virtual base>",
                              "own_vftable": "%#x" % vptrs[off] if off in vptrs else None,
                              "first_vftable": sorted("%#x" % t for t in firsts)})
            fact("virtual_bases", vlist, "retail-vbtable", [r for r, _ in ctors],
                 "target" if all(v["name"] != "<virtual base>" for v in vlist) else "inference")

        # sizeof from allocation sites.
        sizes, size_sites = collections.Counter(), {}
        shared = [rva for rva, _ in ctors if len(self.ledger.ctor_classes(rva)) > 1]
        observed = collections.Counter()
        if shared:
            # An ICF-folded constructor is called for every class that folded
            # into it: its allocation sites prove no one class's sizeof.
            fact("icf_shared_ctors", {"%#x" % r: self.ledger.ctor_classes(r) for r in shared},
                 "ledger-names", shared)
        for rva, _ in ctors:
            if rva in shared:
                continue
            got, where = self.allocation_sizes(rva)
            if not self.complete_ctor(name, per[rva]):
                observed.update(got)
                continue
            sizes.update(got)
            for s, w in where.items():
                size_sites.setdefault(s, []).extend(w)
        if observed:
            # The constructor does not install its own class's primary table, so
            # the allocation may hold a derived object: an observation, not sizeof.
            fact("allocation_observed", {"%#x" % s: n for s, n in observed.items()}, "retail-operator-new",
                 [], "inference")
        if len(sizes) > 1:
            conflicts.append({"fact": "sizeof", "candidates": {"%#x" % s: n for s, n in sizes.items()}})
        elif sizes:
            size = next(iter(sizes))
            fact("sizeof", size, "retail-operator-new", size_sites[size])
        # Lower bound from the constructors' own writes (the nv part).
        reach = [o + 4 for f in per.values() for o in f["vptrs"]] + \
                [o + max(w) for f in per.values() for o, w in f["fields"].items()]
        if reach:
            fact("extent_lower_bound", max(reach), "retail-ctor-writes", [r for r, _ in ctors], "inference")
        if "sizeof" in facts and reach and facts["sizeof"]["value"] < max(reach):
            conflicts.append({"fact": "sizeof", "candidates": {"operator-new": facts["sizeof"]["value"],
                                                               "ctor-writes": max(reach)}})

        # Primary vftable slots.
        primary = vptrs.get(0)
        if primary is not None:
            fact("vslots", self.vslots(primary), "retail-vftable-words", [primary])

        # Fields the class itself writes (after its vptrs).
        fields = collections.defaultdict(set)
        for f in per.values():
            for o, w in f["fields"].items():
                fields[o] |= w
        if fields:
            fact("fields", {"%#x" % o: sorted(w) for o, w in sorted(fields.items())}, "retail-ctor-writes",
                 [r for r, _ in ctors])
        members = {}
        for f in per.values():
            for o, callee in f["member_calls"].items():
                members.setdefault(o, set()).add(self.ledger.name(callee) or "%#x" % callee)
        if members:
            fact("member_ctor_calls", {"%#x" % o: sorted(n) for o, n in sorted(members.items())},
                 "retail-ctor-call", [r for r, _ in ctors])
        out["confidence"] = self.confidence(facts, conflicts)
        return out

    def complete_ctor(self, name, facts):
        """The constructor installs the class's own primary vftable at +0 (a table this class alone owns)."""
        table = facts["vptrs"].get(0)
        return table is not None and self.table_class(table)[0] == name

    def is_ctor(self, rva):
        """The ledger names a constructor at `rva`, or its body stores a vftable at this+0."""
        if self.ledger.ctor_classes(rva):
            return True
        return any(e[0] == "vptr" and e[1] == 0 for e in self.events(rva, self._size(rva)))

    def _size(self, rva):
        rows = self.ledger.by_rva.get(rva)
        return max(int(r["target_size"], 0) for r in rows) if rows else 0x400

    def vslots(self, table):
        if not hasattr(self, "_boundaries"):
            self._boundaries = self.boundaries(self._stored_cache())
            self._purecall = {rva for rva, rows in self.ledger.by_rva.items()
                              if any(r["name"] == "__purecall" for r in rows)}
        got, why = slots(self.image, table, self._boundaries)
        listed = self.listed.get(table, {})
        purecall = self._purecall
        return {"table": "%#x" % table, "count": len(got), "end": why,
                "exact": why == "next-table" and False,
                "listed_agrees": all(dict(got).get(k) == v for k, v in listed.items()) if listed else None,
                "slots": [{"slot": k, "target": "%#x" % t,
                           "name": "__purecall" if t in purecall else self.ledger.name(t)} for k, t in got]}

    def _stored_cache(self):
        if not hasattr(self, "_stored"):
            self._stored = self.stored_tables()
        return self._stored

    @staticmethod
    def confidence(facts, conflicts):
        """full: bases named, sizeof proven, vslots read, no conflict; partial: some; none."""
        if conflicts:
            return "conflict"
        named = "bases" not in facts or all(isinstance(b["name"], str) and not b["name"].startswith("<")
                                            for b in facts["bases"]["value"])
        vnamed = "virtual_bases" not in facts or facts["virtual_bases"]["kind"] == "target"
        if "sizeof" in facts and named and vnamed and ("vslots" in facts or "vftables" not in facts):
            return "full"
        if "sizeof" in facts or "vftables" in facts or "bases" in facts:
            return "partial"
        return "none"


# ---------------------------------------------------------------- coverage

def table_coverage(engine, reference=None):
    """Counts of vftables the engine reads slots for, against vtables.tsv and `reference`."""
    stored = engine._stored_cache()
    vft = {t for t in stored if engine.kind(t) == "vftable"}
    boundaries = engine.boundaries(stored)
    read = {t for t in vft if slots(engine.image, t, boundaries)[0]}
    listed = set(engine.listed)
    exported_vft = {t for t in engine.image.exports if engine.kind(t) == "vftable"}
    out = {"stored_tables": len(stored), "stored_vftables": len(vft),
           "stored_vbtables": sum(1 for t in stored if engine.kind(t) == "vbtable"),
           "slots_read": len(read), "listed_before": len(listed), "listed_and_stored": len(vft & listed),
           "exported_vftables": len(exported_vft), "exported_read": len(exported_vft & read)}
    agree = 0
    for t in listed & read:
        got = dict(slots(engine.image, t, boundaries)[0])
        agree += all(got.get(k) == v for k, v in engine.listed[t].items())
    out["listed_slots_agree"] = agree
    if reference is not None:
        out["reference"] = len(reference)
        out["reference_before"] = len(reference & listed)
        out["reference_after"] = len(reference & (read | listed))
    return out


def dd56_reference(image, ledger):
    """dd-56's 1,196: disp-0 .rdata stores with two leading code pointers, scanned as dd-56 did.

    dd-56's scan subtracted the image base from target_rva, which is already
    an RVA: rows below 0x400000 were skipped and the rest read from the wrong
    code. Reproduced here (`buggy=True` in the result) and corrected."""
    from capstone import x86
    md = _cs()

    def scan(shift):
        tables = set()
        for rva, size in ledger.bodies():
            rva -= shift
            if rva < 0 or size <= 0 or size > 8192:
                continue
            try:
                code = image.read(rva, size)
            except ValueError:
                continue
            for insn in md.disasm(code, rva):
                ops = insn.operands
                if insn.mnemonic != "mov" or len(ops) != 2 or ops[0].type != x86.X86_OP_MEM \
                        or ops[0].mem.disp != 0 or ops[1].type != x86.X86_OP_IMM \
                        or ops[0].mem.base in (x86.X86_REG_ESP, x86.X86_REG_EBP):
                    continue
                t = (ops[1].imm & 0xFFFFFFFF) - IMAGE_BASE
                if image.in_rdata(t) and t % 4 == 0:
                    try:
                        if image.is_code(image.dword(t) - IMAGE_BASE) and image.is_code(image.dword(t + 4) - IMAGE_BASE):
                            tables.add(t)
                    except ValueError:
                        pass
        return tables
    return scan(IMAGE_BASE), scan(0)


# ---------------------------------------------------------------- batch report

def current_answers(paths):
    """{class: {size, size_by, bases, bases_by, slots}} from class_contract outputs (.json or the summary .txt)."""
    head = re.compile(r"^(?P<name>\S+): \w+ \(\w+\), sizeof (?P<size>\d+) \((?P<size_by>[\w-]+)\), "
                      r"bases (?P<bases>\[.*?\]) \((?P<bases_by>[\w-]+)\)")
    out = {}
    for path in paths:
        for file in sorted(Path(path).glob("*")):
            if file.suffix == ".json":
                got = json.loads(file.read_text(encoding="utf-8"))
                out[got["class"]] = {"size": got["size"], "size_by": got["size_by"], "bases": got["bases"],
                                     "bases_by": got.get("bases_by", "?"), "slots": len(got.get("vslots", {})),
                                     "source": file.as_posix()}
            elif file.suffix == ".txt":
                text = file.read_text(encoding="utf-8").splitlines()
                m = head.match(text[0]) if text else None
                if m:
                    out.setdefault(m["name"], {"size": int(m["size"]), "size_by": m["size_by"],
                                               "bases": json.loads(m["bases"].replace("'", '"')),
                                               "bases_by": m["bases_by"], "slots": None,
                                               "source": file.as_posix()})
    return out


def every_class(ledger):
    """Plain (non-template) classes with a matched constructor or destructor."""
    out = set()
    for r in ledger.rows:
        m = CTOR.match(r["name"]) or DTOR.match(r["name"])
        if m and "?" not in m.group(1):
            out.add(demangle_scope(m.group(1)))
    return sorted(out)


def placeholder(name):
    return not isinstance(name, str) or name.startswith(("<", "Rva", "Gen", "Bfme"))


def disagreements(retail, answer):
    """Where the retail layout and today's class_contract answer differ."""
    if not answer:
        return []
    f, out = retail["facts"], []
    if "sizeof" in f and answer["size"] != f["sizeof"]["value"]:
        out.append(f"sizeof: retail {f['sizeof']['value']:#x} (operator new) vs {answer['size']:#x} "
                   f"({answer['size_by']})")
    retail_bases = [b["name"] for b in f.get("bases", {}).get("value", [])] + \
                   [v["name"] for v in f.get("virtual_bases", {}).get("value", [])]
    if ("bases" in f or "virtual_bases" in f) and len(retail_bases) != len(answer["bases"]):
        out.append(f"bases: retail {len(retail_bases)} {retail_bases} vs {len(answer['bases'])} "
                   f"{answer['bases']} ({answer['bases_by']})")
    elif retail_bases and answer["bases"]:
        named = [(r, a) for r, a in zip(retail_bases, answer["bases"]) if not placeholder(r) and r != a]
        if named:
            out.append(f"base names: retail {retail_bases} vs {answer['bases']} ({answer['bases_by']})")
    if "vslots" in f and answer.get("slots") and answer["slots"] > f["vslots"]["value"]["count"]:
        out.append(f"vslots: views name {answer['slots']} slots, the retail primary vftable holds at most "
                   f"{f['vslots']['value']['count']}")
    return out


def write_report(engine, focus, answers, path, coverage=None):
    contracts = {name: engine.contract(name) for name in every_class(engine.ledger)}
    for name in focus:
        contracts.setdefault(name, engine.contract(name))
    by_conf = collections.Counter(c["confidence"] for c in contracts.values())
    lines = ["# Retail class layouts (tools/retail_layout.py)", "",
             "Read from retail bytes only: vftable/vbtable stores and base-constructor calls in matched",
             "constructors (names verified by the byte gate), `push SIZE; call operator new` at allocation",
             "sites, and the vftable words in .rdata. Target facts are read from bytes; inferences are a rule",
             "applied to them; donor (ZH) facts are not used. Conflicts between constructors are flagged, not voted.",
             "", "## Every class with a matched constructor or destructor", "",
             f"{len(contracts)} classes: " + ", ".join(f"{k} {v}" for k, v in sorted(by_conf.items())) + ".", "",
             "- **full**: every base named, sizeof proven by operator new, primary vftable slots read, no conflict.",
             "- **partial**: some of those facts; the rest has no retail evidence (abstract class never newed,",
             "  base identity only inferred).",
             "- **conflict**: the class's constructors or destructors disagree.",
             "- **none**: no retail fact (the class has no matched constructor or destructor).", ""]
    for name in ("sizeof", "bases", "vftables", "virtual_bases", "vslots"):
        lines.append(f"- {name}: {sum(1 for c in contracts.values() if name in c['facts'])} classes")
    if coverage:
        lines += ["", "## vftable coverage", "", "```", json.dumps(coverage, indent=1), "```"]
    rows = [(name, contracts[name], disagreements(contracts[name], answers.get(name))) for name in focus]
    every_diff = [(n, c, disagreements(c, answers.get(n))) for n, c in sorted(contracts.items())
                  if n in answers and n not in focus]
    lines += ["", "## Disagreements with today's class_contract answer", ""]
    flagged = [(n, c, d) for n, c, d in rows + every_diff if d]
    for name, c, diffs in flagged:
        lines.append(f"- **{name}** ({c['confidence']}): " + "; ".join(diffs))
    if not flagged:
        lines.append("None.")
    full = [n for n, c, _ in rows if c["confidence"] == "full"]
    lines += ["", f"## Focus classes the engine fully determines ({len(full)} of {len(rows)})", "",
              ", ".join(full) or "None.", "", "## Focus classes", ""]
    for name, c, diffs in rows:
        lines += [f"### {name}", "", "```", summary(c)]
        a = answers.get(name)
        if a:
            lines.append(f"  today: sizeof {a['size']:#x} ({a['size_by']}), bases {a['bases']} ({a['bases_by']})"
                         f"  [{a['source']}]")
        lines += ["```", ""]
    Path(path).parent.mkdir(parents=True, exist_ok=True)
    Path(path).write_text("\n".join(lines) + "\n", encoding="utf-8")
    return contracts


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--class", dest="names", action="append", default=[])
    parser.add_argument("--tables", action="store_true", help="vftable coverage against vtables.tsv")
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--report", help="write a markdown report for every class, detailing --class/--focus")
    parser.add_argument("--focus", help="file of class names, one per line, detailed in --report")
    parser.add_argument("--answers", action="append", default=[str(REVERSE / "class_contracts")],
                        help="directory of class_contract outputs (.json, or --class summaries as .txt)")
    parser.add_argument("--dump", help="with --report: also write every class's retail layout as JSON")
    args = parser.parse_args(argv)
    engine = Engine(Image.retail(), Ledger.load(), cache_dir=ROOT / "build" / "retail_layout")
    if args.tables:
        print(json.dumps(table_coverage(engine), indent=1))
    if args.report:
        focus = list(args.names)
        if args.focus:
            focus += [n.strip() for n in Path(args.focus).read_text(encoding="utf-8").splitlines() if n.strip()]
        contracts = write_report(engine, list(dict.fromkeys(focus)), current_answers(args.answers), args.report,
                                 table_coverage(engine))
        if args.dump:
            Path(args.dump).write_text(json.dumps(contracts, indent=1, default=sorted), encoding="utf-8")
        return 0
    for name in args.names:
        got = engine.contract(name)
        print(json.dumps(got, indent=1, default=sorted) if args.json else summary(got))
    return 0


def summary(c):
    f = c["facts"]
    lines = [f"{c['class']}: {c['confidence']}  ctors {c['ctors']} dtors {c['dtors']}"]
    for b in f.get("bases", {}).get("value", []):
        lines.append(f"  base +{b['offset']:#x} {b['name']} ({b['rule']}, {b['kind']}) vftable {b['own_vftable']}")
    for v in f.get("virtual_bases", {}).get("value", []):
        lines.append(f"  virtual base +{v['offset']:#x} {v['name']} via vbptr of +{v['via_vbptr']:#x}")
    if "sizeof" in f:
        lines.append(f"  sizeof {f['sizeof']['value']:#x} (operator new at {', '.join(f['sizeof']['sites'][:4])})")
    if "extent_lower_bound" in f:
        lines.append(f"  ctor writes reach {f['extent_lower_bound']['value']:#x}")
    if "vslots" in f:
        v = f["vslots"]["value"]
        lines.append(f"  primary vftable {v['table']}: {v['count']} slots (stop: {v['end']}, tsv agrees: {v['listed_agrees']})")
    for x in c["conflicts"]:
        lines.append(f"  CONFLICT {x['fact']}: {x.get('candidates')}")
    return "\n".join(lines)


if __name__ == "__main__":
    sys.exit(main())
