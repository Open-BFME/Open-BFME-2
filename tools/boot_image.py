#!/usr/bin/env python3
"""Link a runnable game image from relocatable retail scaffolding (and, later, the tree).

link_cycle.py measures where matched rows land; its image is not meant to run.
This tool builds the image that does run, so startup can be tested:

  1. Retail's own base relocations. The unwrapped game.dat keeps link.exe's
     .reloc blocks in its blank-named section, but the unwrapper wrote the
     rebuilt import directory over part of it: pages 0x6A6000..0x6E8FFF (67
     .text pages) are gone. Those pages are recovered by disassembly
     (absolute imm/disp operands in image range, jump-table entries); the same
     recovery run over pages the table does cover measures its precision and
     recall (`relocs --validate`).
  2. Scaffold: every retail section becomes a COFF section of one object; each
     relocation site becomes a DIR32 against the section that owns the target
     (DIR32NB for resource data entries); IAT references become __imp_
     references to import libraries written from retail's import table
     (DLL + name, or ordinal); the CRT initializer tables become real
     .CRT$XIA/XIC/XIZ and .CRT$XCA/XCU/XCZ sections; the entry point is
     retail's CRT start. Nothing is unresolved, nothing is duplicated, so the
     link needs no /FORCE and runs at any base.
  3. Check: the linked image is compared to retail field by field: every
     non-relocated byte equal, every relocated field pointing at the moved
     copy of retail's target, every IAT slot the same (dll, name), every .text
     piece at one offset from retail, base relocations exactly those fields.
  4. Overlay (`--overlay SET`): authored units, the tree's compiled function
     sections, replace the retail pieces at their RVAs (see "overlay" below);
     the check holds them to the same rule and counts them apart, and the
     report gives their share of retail .text.

The scaffold is retail bytes. It is never progress: no row is credited here.
The overlay's authored share is what the image runs of the tree's own code.

  python3 tools/boot_image.py relocs [--validate]
  python3 tools/boot_image.py link [--base 0x2000000] [--out build/boot] [--tag boot]
  python3 tools/boot_image.py link --overlay Code/Libraries/Source/profile/   # a tree path prefix
  python3 tools/boot_image.py link --overlay closed [--status build/link_cycle/link_status.csv]
  python3 tools/boot_image.py link --overlay shift-safe | --overlay rows:FILE
"""
import argparse
import bisect
import collections
import csv
import hashlib
import json
import os
import re
import shutil
import struct
import subprocess
import sys
import tempfile
import time
from pathlib import Path

import capstone
import pefile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import real_image  # noqa: E402

RETAIL_BASE = 0x400000
OUT = ROOT / "build" / "boot"
KEEP = (".text", ".rdata", ".data", "STLPORT_", "rts.ver", ".rsrc")
RELOC_SECTION = b"        "             # retail's .reloc, renamed by the wrapper
DIR32, DIR32NB = 6, 7
FUNCLETS = 0x75B460                     # .text$x, $yc, $yd: EH funclets and initializers
ALIGN_4096 = 0x00D00000
ALIGN_1 = 0x00100000
CODE = 0x60000020
NRELOC_OVFL = 0x01000000
FLAGS = {
    ".text": 0x60000020 | ALIGN_4096,
    ".rdata": 0x40000040 | ALIGN_4096,
    ".data": 0xC0000040 | ALIGN_4096,
    "STLPORT_": 0xC0000040 | ALIGN_4096,
    "rts.ver": 0x40000040 | ALIGN_4096,
    ".rsrc$01": 0x40000040 | ALIGN_4096,
    ".CRT": 0x40000040 | 0x00300000,     # 4-byte aligned pieces of a pointer table
    ".edata": 0x40000040 | 0x00300000,   # retail's export directory: the game GetProcAddress()es itself
}


# ---------------------------------------------------------------- retail
class Retail:
    def __init__(self, path=build.EXE):
        self.data = Path(path).read_bytes()
        self.pe = pefile.PE(data=self.data)
        self.size_of_image = self.pe.OPTIONAL_HEADER.SizeOfImage
        self.entry = self.pe.OPTIONAL_HEADER.AddressOfEntryPoint
        self.secs = {}
        for s in self.pe.sections:
            name = s.Name.rstrip(b"\0").decode("latin-1")
            if name in KEEP:
                raw = s.get_data()[:min(s.SizeOfRawData, s.Misc_VirtualSize)]
                vsize = max(s.Misc_VirtualSize, len(raw))
                self.secs[name] = (s.VirtualAddress, vsize, raw.ljust(vsize, b"\0"))
        self.starts = sorted((v[0], k) for k, v in self.secs.items())

    def section_of(self, rva, end_ok=False):
        i = bisect.bisect_right(self.starts, (rva, "\xff")) - 1
        if i >= 0:
            name = self.starts[i][1]
            start, size, _ = self.secs[name]
            if rva < start + size or (end_ok and rva == start + size):
                return name
        return None

    def u32(self, rva):
        name = self.section_of(rva)
        start, _, raw = self.secs[name]
        return struct.unpack_from("<I", raw, rva - start)[0]

    def imports(self):
        """{iat slot rva: (dll, name or None, ordinal or None)}"""
        out = {}
        for d in self.pe.DIRECTORY_ENTRY_IMPORT:
            for imp in d.imports:
                name = imp.name.decode("latin-1") if imp.name else None
                out[imp.address - RETAIL_BASE] = (d.dll.decode("latin-1").lower(), name,
                                                  None if name else imp.ordinal)
        return out


def parse_blocks(blob, p=0):
    """(HIGHLOW site RVAs, pages, offset after the last block) from offset p."""
    sites, pages = [], []
    while p + 8 <= len(blob):
        page, size = struct.unpack_from("<II", blob, p)
        if size < 8 or size % 2 or page % 0x1000 or p + size > len(blob) or (pages and page <= pages[-1]):
            break
        for (e,) in struct.iter_unpack("<H", blob[p + 8:p + size]):
            if e >> 12 == 3:
                sites.append(page + (e & 0xFFF))
            elif e >> 12:
                raise ValueError(f"base relocation type {e >> 12} at page {page:#x}")
        pages.append(page)
        p += size
    return sites, pages, p


def table_sites(r):
    """(sorted HIGHLOW site RVAs from retail's table, (first lost page, end of lost pages))."""
    sec = next(s for s in r.pe.sections if s.Name == RELOC_SECTION)
    blob = sec.get_data()
    sites, pages, stop = parse_blocks(blob)
    for q in range(stop, len(blob) - 8, 2):
        more, morepages, end = parse_blocks(blob, q)
        if len(morepages) > 16 and morepages[0] > pages[-1] and blob[end:].strip(b"\0") == b"":
            return sorted(sites + more), (pages[-1] + 0x1000, morepages[0])
    raise SystemExit("boot_image: retail .reloc copy has no resumable tail")


def function_starts():
    starts = set()
    for path, col in (("reverse/functions.csv", "target_rva"), ("reverse/ghidra_functions.csv", "rva")):
        with open(ROOT / path, newline="", encoding="utf-8") as f:
            for row in csv.DictReader(f):
                if row.get(col):
                    starts.add(int(row[col], 16))
    return sorted(starts)


def recover_sites(r, lo, hi, starts):
    """Absolute-address dword sites in .text [lo, hi) by a linear sweep that
    resynchronises at every known function start: 4-byte imm operands (not
    relative branches) and 4-byte displacements inside the image, plus the
    entries of `[reg*4 + table]` jump tables. A table is skipped as data; a
    byte index table (`byte ptr [reg + table]`) is skipped to the next known
    start. An immediate into .text counts only when it is a known function
    start, a funclet, or neither three printable characters nor a 2^n / 2^n-1
    mask ('Sun\0' and 0x7FFFFF are otherwise in range)."""
    tstart, tsize, text = r.secs[".text"]
    tend = tstart + tsize
    img_lo, img_hi = RETAIL_BASE + 0x1000, RETAIL_BASE + r.size_of_image
    startset = set(starts)

    def code_imm(v):
        t = v - RETAIL_BASE
        if not tstart <= t < tend or t in startset or t >= FUNCLETS:
            return True
        text_like = all(0x20 <= c < 0x7F for c in v.to_bytes(4, "little")[:3])
        return not (text_like or v & (v + 1) == 0 or v & (v - 1) == 0)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    sites, byte_tables = set(), set()
    dw_tables, inline_data = {}, {}           # table start -> start of the referencing function
    k = max(bisect.bisect_right(starts, lo - 0x1000) - 1, 0)
    a, fstart = starts[k], starts[k]
    while a < min(hi, tend):
        if a in startset:
            fstart = a
        if a in dw_tables:
            q = a
            while q + 4 <= tend and (q == a or q not in startset):
                v = struct.unpack_from("<I", text, q - tstart)[0] - RETAIL_BASE
                if not (fstart <= v < q):
                    break
                sites.add(q)
                q += 4
            if q > a:
                a = q
                continue
        nxt = starts[bisect.bisect_right(starts, a)] if bisect.bisect_right(starts, a) < len(starts) else tend
        if a in byte_tables:
            later = [t for t in dw_tables if t > a]
            a = min([nxt] + later)
            continue
        ins = next(md.disasm(text[a - tstart:min(tend, a + 16) - tstart], a, 1), None)
        if ins is None or a + ins.size > nxt:
            a = nxt if ins is None or a + ins.size > nxt else a + ins.size
            continue
        branch = ins.group(capstone.CS_GRP_JUMP) or ins.group(capstone.CS_GRP_CALL)
        for op in ins.operands:
            if op.type == capstone.x86.X86_OP_IMM and not branch and ins.imm_size == 4:
                v = op.imm & 0xFFFFFFFF
                if img_lo <= v < img_hi and code_imm(v):
                    sites.add(a + ins.imm_offset)
                    if tstart <= v - RETAIL_BASE < FUNCLETS and v - RETAIL_BASE not in startset:
                        inline_data.setdefault(v - RETAIL_BASE, fstart)
            elif op.type == capstone.x86.X86_OP_MEM and ins.disp_size == 4:
                d = op.mem.disp & 0xFFFFFFFF
                if img_lo <= d < img_hi:
                    sites.add(a + ins.disp_offset)
                    t = d - RETAIL_BASE
                    if not op.mem.index and tstart <= t < FUNCLETS and t not in startset:
                        inline_data.setdefault(t, fstart)
                    if a < t < tend and op.mem.index:
                        if op.size == 4 and op.mem.scale == 4:
                            dw_tables.setdefault(t, fstart)
                        else:
                            byte_tables.add(t)
        a += ins.size
    for t, fs in dw_tables.items():
        q = t
        while q + 4 <= tend and (q == t or q not in startset):
            v = struct.unpack_from("<I", text, q - tstart)[0] - RETAIL_BASE
            if not (fs <= v < q):
                break
            sites.add(q)
            q += 4
    for t, fs in inline_data.items():  # e.g. /RTC frame descriptors {count, vars*}, {offset, size, name*}
        for q in range(t, min(t + 0x100, tend - 3), 4):
            v = struct.unpack_from("<I", text, q - tstart)[0]
            if fs <= v - RETAIL_BASE < t + 0x100:
                sites.add(q)
            elif not (v < 0x100 or v >= 0xFFFFFF00):
                break
    return sorted(x for x in sites if lo <= x < hi)


def all_sites(r):
    """(sorted site RVAs: retail table + recovered lost pages, info dict)."""
    sites, (lost_lo, lost_hi) = table_sites(r)
    rec = recover_sites(r, lost_lo, lost_hi, function_starts())
    info = {"table_sites": len(sites), "lost_pages": [hex(lost_lo), hex(lost_hi)], "recovered_sites": len(rec)}
    return sorted(set(sites) | set(rec)), info


def validate_recovery(r):
    """Precision / recall of recover_sites on table-covered .text next to the hole."""
    sites, (lost_lo, lost_hi) = table_sites(r)
    starts = function_starts()
    out = {}
    for lo, hi in ((lost_lo - 0x60000, lost_lo), (lost_hi, lost_hi + 0x60000)):
        want = set(sites[bisect.bisect_left(sites, lo):bisect.bisect_left(sites, hi)])
        got = set(recover_sites(r, lo, hi, starts))
        out[f"{lo:#x}-{hi:#x}"] = {
            "table": len(want), "recovered": len(got), "true": len(want & got),
            "missed": [hex(x) for x in sorted(want - got)][:20], "n_missed": len(want - got),
            "false": [hex(x) for x in sorted(got - want)][:20], "n_false": len(got - want)}
    return out


# ---------------------------------------------------------------- scaffold
def crt_tables(r):
    """[(first, end)] RVAs of the __xi_a..__xi_z and __xc_a..__xc_z tables: the two
    `push end; push first; call _initterm` sequences of retail's CRT start."""
    tstart, _, text = r.secs[".text"]
    slot = next(k for k, v in r.imports().items() if v[1] == "_initterm")
    thunk = text.index(b"\xff\x25" + struct.pack("<I", slot + RETAIL_BASE)) + tstart
    out = []
    for a in range(r.entry, r.entry + 0x300):
        o = a - tstart
        if text[o] == 0xE8 and o + struct.unpack_from("<i", text, o + 1)[0] + 5 == thunk - tstart \
                and text[o - 10] == 0x68 and text[o - 5] == 0x68:
            end, first = (struct.unpack_from("<I", text, o - k)[0] - RETAIL_BASE for k in (9, 4))
            out.append((first, end))
    if len(out) != 2:
        raise SystemExit(f"boot_image: expected two _initterm tables near the entry, found {out}")
    return sorted(out)


def crt_pieces(r):
    """{.CRT$ name: (start, size)}: retail's initializer tables as real CRT sections."""
    # the __xi table (C initializers) is the short one; __xc holds every C++ initializer
    (xi_a, xi_z), (xc_a, xc_z) = sorted(crt_tables(r), key=lambda t: t[1] - t[0])
    pieces = {".CRT$XCA": (xc_a, 4), ".CRT$XCU": (xc_a + 4, xc_z - xc_a - 4), ".CRT$XCZ": (xc_z, 4),
              ".CRT$XIA": (xi_a, 4), ".CRT$XIC": (xi_a + 4, xi_z - xi_a - 4), ".CRT$XIZ": (xi_z, 4)}
    for name in (".CRT$XCA", ".CRT$XCZ", ".CRT$XIA", ".CRT$XIZ"):
        if r.u32(pieces[name][0]):
            raise SystemExit(f"boot_image: {name} sentinel at {pieces[name][0]:#x} is not null")
    return {k: v for k, v in pieces.items() if v[1]}


def resource_fields(r):
    """RVAs of every IMAGE_RESOURCE_DATA_ENTRY.OffsetToData (an image-relative address)."""
    start, size, raw = r.secs[".rsrc"]
    out = []

    def walk(off):
        named, ids = struct.unpack_from("<HH", raw, off + 12)
        for k in range(named + ids):
            _, child = struct.unpack_from("<II", raw, off + 16 + 8 * k)
            if child & 0x80000000:
                walk(child & 0x7FFFFFFF)
            else:
                out.append(start + child)
    walk(0)
    return out


def export_fields(r):
    """RVAs of every image-relative field of retail's export directory: the
    directory's Name and three table pointers, each EAT entry and name pointer."""
    d = r.pe.OPTIONAL_HEADER.DATA_DIRECTORY[0].VirtualAddress
    nfun, nnames, eat, enpt = (r.u32(d + o) for o in (20, 24, 28, 32))
    out = [d + 12, d + 28, d + 32, d + 36]
    out += [eat + 4 * i for i in range(nfun) if r.u32(eat + 4 * i)]
    out += [enpt + 4 * i for i in range(nnames)]
    return out


class Piece:
    __slots__ = ("name", "start", "size", "flags", "relocs", "label", "pad", "unit", "public", "fill")

    def __init__(self, name, start, size, flags, unit=None):
        self.name, self.start, self.size, self.flags, self.relocs = name, start, size, flags, []
        self.label, self.unit, self.fill = None, unit, None    # fill: a byte replacing retail's (relayout)
        self.public = unit.label if unit else f"_bootp_{start:08X}"
        # a page-aligned piece cut from mid-section keeps retail's address mod 4096
        # (movdqa on a .data table faults when a carve shifts it by 8)
        self.pad = start & 0xFFF if flags & 0x00F00000 == ALIGN_4096 else 0


def plan(r, sites, units=()):
    """(pieces sorted by start, problems). Each piece carries its relocations
    [(site, type, target)]; target = ("piece", Piece, rva) | ("imp", (dll, name,
    ordinal)) | ("base", offset). Overlay units cut .text into pieces in retail
    order, each 1-byte aligned so it keeps its retail offset."""
    pieces = []
    carve = crt_pieces(r)
    exp = r.pe.OPTIONAL_HEADER.DATA_DIRECTORY[0]
    carve[".edata"] = (exp.VirtualAddress, exp.Size)
    by_label = {u.label: u for u in units}
    for sec, (start, size, _) in r.secs.items():
        coff = ".rsrc$01" if sec == ".rsrc" else sec
        cuts = sorted([(s, sz, n) for n, (s, sz) in carve.items() if start <= s < start + size]
                      + [(u.rva, u.size, u.label) for u in units if sec == ".text"])
        cur = start
        for s, sz, n in cuts + [(start + size, 0, None)]:
            if s > cur:
                pieces.append(Piece(coff, cur, s - cur, FLAGS[coff]))
            if n in by_label:
                pieces.append(Piece(".text", s, sz, CODE | ALIGN_1, by_label[n]))
            elif n:
                pieces.append(Piece(n, s, sz, FLAGS[".CRT" if n.startswith(".CRT") else n]))
            cur = max(cur, s + sz)
    pieces.sort(key=lambda p: p.start)
    if units:
        for k, p in enumerate(x for x in pieces if x.name == ".text"):
            p.name, p.flags, p.pad = f".text$p{k:06d}", CODE | (ALIGN_4096 if k == 0 else ALIGN_1), 0
    starts = [p.start for p in pieces]

    def owner(rva, end_ok=False):
        i = bisect.bisect_right(starts, rva) - 1
        if i >= 0 and (rva < pieces[i].start + pieces[i].size or (end_ok and rva == pieces[i].start + pieces[i].size)):
            return pieces[i]
        return None
    iat = r.imports()
    problems = collections.Counter()
    for site in sites:
        p = owner(site)
        if p is None or site + 4 > p.start + p.size:
            problems["site-outside-kept-or-straddles"] += 1
            continue
        t = r.u32(site) - RETAIL_BASE
        if t in iat:
            p.relocs.append((site, DIR32, ("imp", iat[t])))
        elif owner(t, end_ok=True) is not None:
            p.relocs.append((site, DIR32, ("piece", owner(t, end_ok=True), t)))
        elif 0 <= t < 0x1000:
            p.relocs.append((site, DIR32, ("base", t)))
        else:
            problems["target-outside-kept"] += 1
    for f in resource_fields(r) + export_fields(r):
        t = r.u32(f)
        owner(f).relocs.append((f, DIR32NB, ("piece", owner(t), t)))
    for p in pieces:
        p.relocs.sort(key=lambda x: x[0])
    return pieces, problems


def import_symbol(entry):
    dll, name, ordinal = entry
    return name if name else f"{dll.rsplit('.', 1)[0]}_ordinal_{ordinal}"


def coff_name(name, strings):
    raw = name.encode("latin-1")
    if len(raw) <= 8:
        return raw.ljust(8, b"\0")
    o = len(strings)
    strings.extend(raw + b"\0")
    return struct.pack("<II", 0, o)


def section_name(name, strings):
    """A COFF section name field: longer than 8 bytes is `/<string table offset>`."""
    raw = name.encode("latin-1")
    if len(raw) <= 8:
        return raw.ljust(8, b"\0")
    o = len(strings)
    strings.extend(raw + b"\0")
    return f"/{o}".encode().ljust(8, b"\0")


def write_coff(path, sections, syms):
    """sections [(name, flags, body, [(offset, symbol index, type)])], syms
    [(name, section number (0 undefined, -1 absolute), value, storage class)]."""
    strings = bytearray(4)
    hdr_end = 20 + 40 * len(sections)
    shdr, blob = bytearray(), bytearray()
    for name, flags, body, rels in sections:
        ptr = hdr_end + len(blob) if body else 0
        blob += body
        n = len(rels)
        rptr = hdr_end + len(blob) if n else 0
        count = n
        if n >= 0xFFFF:                       # IMAGE_SCN_LNK_NRELOC_OVFL: the first entry holds the count
            blob += struct.pack("<IIH", n + 1, 0, 0)
            flags, count = flags | NRELOC_OVFL, 0xFFFF
        blob += b"".join(struct.pack("<IIH", *x) for x in rels)
        shdr += section_name(name, strings) + struct.pack("<IIIIIIHHI", 0, 0, len(body), ptr, rptr, 0, count, 0,
                                                          flags)
    symtab = bytearray()
    for name, sec, value, cls in syms:
        symtab += coff_name(name, strings) + struct.pack("<IHHBB", value, sec & 0xFFFF, 0, cls, 0)
    strings[0:4] = struct.pack("<I", len(strings))
    path.write_bytes(struct.pack("<HHIIIHH", 0x14C, len(sections), 0, hdr_end + len(blob), len(syms), 0, 0)
                     + shdr + blob + symtab + strings)


class Symbols(list):
    """A COFF symbol table under construction; one entry per name."""
    def __init__(self):
        super().__init__()
        self.index = {}

    def add(self, name, sec=0, value=0, cls=2):
        if name not in self.index:
            self.index[name] = len(self)
            self.append((name, sec, value, cls))
        return self.index[name]


MAX_SECTIONS = 60000                    # a COFF object holds at most 65,279 sections


def chunk_paths(path, n):
    """`path` for the first object of a split, path stem + index for the rest."""
    return [path if i == 0 else path.with_name(f"{path.stem}{i}{path.suffix}") for i in range(n)]


def write_scaffold(r, pieces, path, names=None):
    """COFF objects (several when the pieces exceed MAX_SECTIONS): one section per
    retail piece, DIR32/DIR32NB relocations against the owning piece's label
    (addend in place), __imp_ and ___ImageBase externals, and a `_bootp_<rva>`
    public at each piece start. Overlay pieces are not in them: a reference into
    one names the authored definition, and every name in `names` {name: rva}
    outside the overlay (`_boot_entry` among them, unless an authored unit holds
    the entry point) is defined here at its retail address.
    Returns (the import symbols referenced, the object paths)."""
    own = [p for p in pieces if p.unit is None]
    chunks = [own[i:i + MAX_SECTIONS] for i in range(0, len(own), MAX_SECTIONS)]
    home = {p.start: (c, k) for c, chunk in enumerate(chunks) for k, p in enumerate(chunk, 1)}
    starts = [p.start for p in pieces]
    defs = collections.defaultdict(list)                  # chunk -> [(name, section, value)]
    for name, rva in sorted((names or {}).items()):
        p = pieces[bisect.bisect_right(starts, rva) - 1]
        if p.unit is None and name not in ABSOLUTE:
            c, k = home[p.start]
            defs[c].append((name, k, rva - p.start + p.pad))
    imports, paths = set(), chunk_paths(path, len(chunks))
    for c, chunk in enumerate(chunks):
        syms = Symbols()
        for k, p in enumerate(chunk, 1):
            syms.add(p.public, k, p.pad)
        for name, k, value in defs[c]:
            syms.add(name, k, value)
        if c == 0:
            for name in sorted(set(names or ()) & set(ABSOLUTE)):
                syms.add(name, -1, ABSOLUTE[name])
        sections = []
        for p in chunk:
            s0, _, raw = next(v for v in r.secs.values() if v[0] <= p.start < v[0] + v[1])
            body = bytearray(p.pad) + (bytearray([p.fill]) * p.size if p.fill is not None
                                       else bytearray(raw[p.start - s0:p.start - s0 + p.size]))
            rl = []
            for site, kind, tgt in p.relocs:
                if tgt[0] == "piece" and tgt[1].unit is not None:
                    si, add = syms.add(unit_public(tgt[1].unit, names)), tgt[2] - tgt[1].start
                elif tgt[0] == "piece":
                    si, add = syms.add(tgt[1].public), tgt[2] - tgt[1].start
                elif tgt[0] == "imp":
                    si, add = syms.add("__imp_" + import_symbol(tgt[1])), 0
                else:
                    si, add = syms.add("___ImageBase"), tgt[1]
                struct.pack_into("<I", body, site - p.start + p.pad, add & 0xFFFFFFFF)
                rl.append((site - p.start + p.pad, si, kind))
            sections.append((p.name, p.flags, bytes(body), rl))
        write_coff(paths[c], sections, syms)
        imports |= {n[len("__imp_"):] for n in syms.index if n.startswith("__imp_")}
    return sorted(imports), paths


def write_import_lib(entries, path):
    """A COFF archive of short import objects (IMPORT_DATA: only `__imp_` is
    defined, so no unused jump thunks are emitted; IMPORT_NAME or
    IMPORT_ORDINAL): each symbol is retail's own import name, so `__imp_<name>`
    imports exactly retail's (dll, name) with nothing undecorated or guessed."""
    members = []
    for sym_name, (dll, name, ordinal) in entries:
        data = sym_name.encode("latin-1") + b"\0" + dll.encode("latin-1") + b"\0"
        members.append(struct.pack("<HHHHIIHH", 0, 0xFFFF, 0, 0x14C, 0, len(data), ordinal or 0,
                                   (1 if name else 0) << 2 | 1) + data)

    def mhdr(name, size):
        return (name.ljust(16) + "0".ljust(12) + "".ljust(6) + "".ljust(6) + "0".ljust(8)
                + str(size).ljust(10) + "`\n").encode("latin-1")
    table = sorted(("__imp_" + e[0], k) for k, e in enumerate(entries))
    strtab = b"".join(n.encode("latin-1") + b"\0" for n, _ in table)
    first_size = 4 + 4 * len(table) + len(strtab)
    off = 8 + 60 + first_size + (first_size & 1)
    offsets = []
    for m in members:
        offsets.append(off)
        off += 60 + len(m) + (len(m) & 1)
    first = struct.pack(">I", len(table)) + b"".join(struct.pack(">I", offsets[k]) for _, k in table) + strtab
    out = bytearray(b"!<arch>\n" + mhdr("/", len(first)) + first + (b"\n" if len(first) & 1 else b""))
    for (_, (dll, _, _)), m in zip(entries, members):
        out += mhdr((dll[:15] + "/")[:16], len(m)) + m + (b"\n" if len(m) & 1 else b"")
    path.write_bytes(bytes(out))


def descriptor_libs(dlls, out):
    """lib.exe import libraries that only supply each DLL's import descriptor and
    null thunk (their one export, `boot_descriptor_<dll>`, is never referenced)."""
    root = build.vc71_root()
    libs = []
    for dll in dlls:
        stem = dll.rsplit(".", 1)[0]
        d, lib = out / f"desc_{stem}.def", out / f"desc_{stem}.lib"
        d.write_text(f"LIBRARY {dll}\nEXPORTS\n  boot_descriptor_{stem}\n", encoding="latin-1")
        cmd = [str(root / "Vc7/bin/lib.exe"), "/NOLOGO", "/MACHINE:X86",
               f"/DEF:{build.wine_path(d)}", f"/OUT:{build.wine_path(lib)}"]
        if sys.platform != "win32":
            cmd.insert(0, "wine")
        res = subprocess.run(cmd, capture_output=True, text=True, errors="replace",
                             env=build.compiler_environment(root))
        if res.returncode or not lib.exists():
            raise SystemExit(f"boot_image: lib.exe failed for {dll}:\n{res.stdout}{res.stderr}")
        libs.append(lib)
    return libs


# ---------------------------------------------------------------- overlay
# `link --overlay SET` puts authored code in the image. A unit is one COMDAT
# function section of a tree object (for an EH funclet, the slice at its label),
# admitted to replace retail [rva, rva + size) only when, against retail:
#   - every byte outside its relocation fields is equal;
#   - every relocation resolves to retail's target at that site: a name with a
#     retail identity (ledger row or symbols.csv pin) or an authored definition
#     must denote that address; an import must be the same (dll, name); a target
#     in its own section the same offset; any other target (TU statics,
#     literals, EH thunks) binds to retail's address, with the object's bytes
#     for it equal to retail's there when the object defines it;
#   - every retail relocation site inside it is one of its DIR32 fields, and in
#     pages retail's table covers, every DIR32 field is a retail site.
# .text is cut in retail order (`.text$pNNNNNN`, 1-byte aligned, so every piece
# keeps its retail offset and the rel32 operands retail never relocated stay
# right). Units go to their own object with their compiled bytes and
# relocations; names resolve to definitions the scaffold makes at retail
# addresses, and scaffold references into a unit to the authored definition.
# A name is used only while it denotes one address; otherwise the reference
# binds to an address label (`_boota_<rva>`). Refusals iterate to a fixpoint:
# a refused unit no longer defines names the others resolved to.
ABSOLUTE = {"__except_list": 0}         # exsup.asm: an FS: offset, not an address (as link_cycle.py)
REL32, EXTERNAL, STATIC, WEAK = 0x14, 2, 3, 105
COMDAT = 0x1000
LINK_STATUS = ROOT / "build" / "link_cycle" / "link_status.csv"
# byte-true placeholders, not authored code: never overlaid from a path spec
GENERATED = ("Code/gen_small/", "Code/gen_asm/", "Code/masm_dumps/")
GENERATED_KIND = re.compile(r"(?:^|;)gen-(?:alias|import)(?:;|$)")
SETS = {   # link_cycle.py's certification (link_status.csv columns), real rows only
    "closed": lambda s: s["placed"] == "1" and s["closed_strict"] == "1",
    "shift-safe": lambda s: s["placed"] == "1" and s["self_strict"] == "1" and s["hardcoded"] == "0",
}


class Unit:
    __slots__ = ("rows", "obj", "path", "sec", "off", "size", "rva", "body", "relocs", "folded", "label", "why",
                 "bind")

    def __init__(self, rows, obj, path, sec, off, size, rva):
        self.rows, self.obj, self.path, self.sec, self.off, self.size, self.rva = rows, obj, path, sec, off, size, rva
        self.body, self.relocs, self.folded, self.why, self.bind = b"", [], [], None, collections.Counter()
        self.label = f"_bootu_{rva:08X}"


def ledger_rows():
    with open(ROOT / "reverse/functions.csv", newline="", encoding="utf-8") as f:
        return [r for r in csv.DictReader(f) if r.get("target_rva")]


def overlay_rows(specs, status=LINK_STATUS):
    """Matched ledger rows a list of specs names: `closed` / `shift-safe` (link_cycle
    certification in link_status.csv), `rows:FILE` (lines `0xRVA [name]`), `rva:0xA,0xB` or a
    source path prefix (`Code/Libraries/Source/profile/`)."""
    by_key = {(int(r["target_rva"], 16), r["name"]): r for r in ledger_rows() if r["status"] == "matched"}
    out = {}
    for spec in specs:
        if spec in SETS:
            with open(status, newline="", encoding="utf-8") as f:
                for s in csv.DictReader(f):
                    key = (int(s["retail_rva"], 16), s["name"])
                    if s["kind"] == "real" and SETS[spec](s) and key in by_key:
                        out[key] = by_key[key]
        elif spec.startswith(("rows:", "rva:")):
            want = collections.defaultdict(set)
            lines = spec[4:].split(",") if spec.startswith("rva:") else \
                Path(spec[5:]).read_text(encoding="utf-8").splitlines()
            for line in lines:
                f = line.split(None, 1)
                if f and not f[0].startswith("#"):
                    want[int(f[0], 16)].add(f[1].strip() if len(f) > 1 else None)
            out.update({k: r for k, r in by_key.items()
                        if k[0] in want and (None in want[k[0]] or k[1] in want[k[0]])})
        else:
            prefix = spec.replace("\\", "/")
            if not (ROOT / prefix).exists():
                raise SystemExit(f"boot_image: overlay set {spec!r} is not {'/'.join(SETS)}, rows:FILE, rva:LIST "
                                 "or a tree path")
            out.update({k: r for k, r in by_key.items() if r["source"].startswith(prefix)
                        and not r["source"].startswith(GENERATED) and not GENERATED_KIND.search(r.get("notes", ""))})
    return [out[k] for k in sorted(out)]


def funclet_symbol(row, path, o, pin, target):
    """(symbol, None) or (None, why) for a funclet row pinned to a `$L` label (an
    edit to the TU renumbers them), resolved as build.read_funclet resolves it: the
    label the parent's verified EH data places at the row's RVA; else, unless the
    label repeats across TUs (which needs that proof), the pin while its bytes still
    hold retail's `target`; else the one label of the parent's group whose bytes do.
    A tie, and read_funclet's last resort (whatever the pin names now), are refused.
    So is a row whose object or parent build cannot read (a ValueError or SystemExit
    naming the row, its parent, pin, source or object: `funclet-unresolved:<cause>`);
    one naming none of them (git, the toolchain), and anything else (a missing retail
    image, ledger or module), is the environment's and propagates."""
    secs, syms, _ = o
    try:
        label = build.located_funclet(row, path, target)
        scoped = build.scoped_funclet_collision(row)
        if label is None and not scoped:
            try:
                body, relocs = build.read_object_symbol_bytes(path, pin, len(target), code_only=True)
            except ValueError:                          # the pinned label is gone
                body, relocs = b"", []
            if build.holds_funclet(body, relocs, target):
                label = pin
            else:
                hits = build.funclet_candidates(path, row, target)
                if len(hits) > 1:
                    return None, f"funclet-ambiguous:{len(hits)}"
                label = hits[0] if hits else None
    except (ValueError, SystemExit) as e:              # what read_funclet raises for one row
        if not any(k in str(e) for k in funclet_keys(row, path, pin)):
            raise
        return None, "funclet-unresolved:" + ((str(e).strip().splitlines() or [type(e).__name__])[0][:160])
    if label is None:
        return None, "funclet-scoped-unlocated" if scoped else "funclet-unresolved"
    named = [y for y in syms.values() if y.name == label]
    if scoped and (len(named) != 1 or named[0].cls != STATIC):
        return None, "funclet-scoped-not-local"
    y = next((y for y in named if 0 < y.sec <= len(secs)), None)       # the first definition, as build reads
    return (y, None) if y is not None else (None, "symbol-not-in-object")


def funclet_keys(row, path, pin):
    """What a per-row funclet failure names: the row, its parent, pin, source or object."""
    parent = re.search(r"(?:^|;)parent=([^;]+)", row.get("notes", ""))
    return [k for k in (row["name"], parent and parent[1], pin, row.get("source"), str(path), Path(path).name) if k]


FUNCLET_QUORUM = 10     # this many funclet rows, none readable: the EH evidence itself is broken


def find_units(r, rows, objs):
    """(units sorted by RVA, refusals [(row, why)]): one unit per object section
    (COMDAT) or funclet slice holding the rows."""
    tstart, tsize, text = r.secs[".text"]
    units, refused = {}, []
    funclets, placed, errors, failed = 0, 0, [], collections.Counter()
    for row in rows:
        rva, size = int(row["target_rva"], 16), int(row["target_size"] or 0)
        name = (re.search(r"(?:^|;)object-symbol=([^;]+)", row.get("notes", "")) or [None, row["name"]])[1]
        funclet = build.is_funclet_row(row, name)
        try:
            p = build.row_object(row)
        except SystemExit:
            p = None
        o = objs.get(p) if p else None
        if o is None:
            refused.append((row, "no-object"))
            if funclet:
                funclets += 1
                failed["no-object"] += 1
            continue
        secs, syms, _ = o
        if funclet:
            y, why = funclet_symbol(row, p, o, name, text[rva - tstart:rva - tstart + size])
            funclets += 1
            if why and why.startswith("funclet-unresolved:"):
                cause = why
                for k in sorted(funclet_keys(row, p, name), key=len, reverse=True):
                    cause = cause.replace(k, "<row>")
                errors.append(cause)
        else:
            y = next((y for y in syms.values() if y.name == name and 0 < y.sec <= len(secs)), None)
            why = "symbol-not-in-object"
        if y is not None:
            s = secs[y.sec - 1]
            # a function's COMDAT is the unit; funclets share an associative .text$x COMDAT, one slice each
            whole = s.flags & COMDAT and y.value == 0 and not s.name.startswith(".text$x")
            off, n = (0, s.size) if whole else (y.value, size)
            start = rva - (y.value - off)
            why = ("not-code" if not s.name.startswith(".text") or not size else
                   "outside-text" if not (tstart <= start and start + n <= tstart + tsize) else None)
        if why:
            refused.append((row, why))
            if funclet:
                failed[why.split(":")[0]] += 1
            continue
        placed += funclet
        # one compiled body may be several retail copies (one name at several RVAs): a unit each,
        # and the name, denoting several addresses, binds by address
        key = (str(p), y.sec, off, start)
        if key not in units:
            units[key] = Unit([], o, str(p), y.sec, off, n, start)
        units[key].rows.append(row)
    # no funclet row placed, at quorum (whatever the failures) or two or more unresolved for one
    # cause: the EH evidence is broken, not the rows
    if funclets and not placed and (funclets >= FUNCLET_QUORUM or
                                    funclets >= 2 and len(errors) == funclets and len(set(errors)) == 1):
        raise SystemExit(f"boot_image: none of {funclets} funclet rows could be placed "
                         f"({', '.join(f'{k} {v}' for k, v in failed.most_common())}; {(errors or ['-'])[0]}); "
                         "the EH evidence (retail image, ledger, objects) is broken, not the rows")
    return sorted(units.values(), key=lambda u: (u.rva, -u.size, u.rows[0]["name"])), refused


def identities(r):
    """{name: RVAs}: ledger rows, data_ledger.csv names and symbols.csv pins. A pin
    is an RVA (code pins must be) unless it lies past the image, then a VA:
    retail's data VAs start at 0xBBA000, beyond SizeOfImage, so the two
    spellings cannot be confused."""
    out = collections.defaultdict(set)
    for row in ledger_rows():
        out[row["name"]].add(int(row["target_rva"], 16))
    with open(ROOT / "reverse/data_ledger.csv", newline="", encoding="utf-8") as f:
        for row in csv.DictReader(f):
            a = int(row["address"], 16)
            if row["kind"] != "import" and row["name"] and 0 < a < r.size_of_image:
                out[row["name"]].add(a)
    with open(ROOT / "reverse/symbols.csv", newline="", encoding="utf-8") as f:
        for row in csv.DictReader(f):
            if row["address"].startswith("0x"):
                a = int(row["address"], 16)
                a = a if a < r.size_of_image else a - RETAIL_BASE
                if 0 < a < r.size_of_image:
                    out[row["name"]].add(a)
    return out


def import_entry_names(sym):
    """Retail import names an `__imp_` reference can denote: a C name without its
    `_` and stdcall @N, or (mss32 exports decorated names) as spelled."""
    rest = sym[len("__imp_"):]
    if rest.startswith("?"):
        return {rest}
    bare = rest[1:] if rest.startswith("_") else rest
    return {bare, re.sub(r"@\d+$", "", bare)}


def is_section_symbol(o, y):
    return y.cls == STATIC and y.value == 0 and y.name == o[0][y.sec - 1].name


def datum_anchor(o, y, q):
    """The section offset whose datum a reference to symbol y + addend means: y's
    own offset (table[i - K] still names table, even when q lies before it or in
    the datum before), or q itself when y is the section symbol (statics the object
    addresses as section + offset: which datum a biased one means is unknown)."""
    return q if is_section_symbol(o, y) else y.value


def object_datum(o, sec, q, cap=0x1000, at=None):
    """(start offset, bytes, masked offsets) of the object datum starting at the
    last symbol at or before `at` (default q, the referenced offset): to the next
    symbol or the section end (at most `cap` bytes). Empty when `at` lies outside
    the section."""
    secs, syms, data = o
    s = secs[sec - 1]
    a = q if at is None else at
    if not 0 <= a < s.size:
        return a, b"", set()                             # bind_unit refuses
    offs = section_symbols(o)[1].get(sec, [0])
    i = bisect.bisect_right(offs, a)
    lo = offs[i - 1]
    hi = min(offs[i] if i < len(offs) else s.size, s.size, lo + cap)
    raw = data[s.ptr + lo:s.ptr + hi] if s.ptr else bytes(hi - lo)
    masked = {k for off, _, _ in s.relocs if lo - 4 < off < hi for k in range(off - lo, off - lo + 4)}
    return lo, raw, masked


_SECTION_SYMBOLS = {}


def section_symbols(o):
    """({section: [(external name, value)]}, {section: sorted symbol offsets incl. 0}) of object o."""
    key = id(o)
    if key not in _SECTION_SYMBOLS:
        secs, syms, _ = o
        ext, offs = collections.defaultdict(list), collections.defaultdict(set)
        for y in syms.values():
            if 0 < y.sec <= len(secs):
                offs[y.sec].add(y.value)
                if y.cls == EXTERNAL:
                    ext[y.sec].append((y.name, y.value))
        _SECTION_SYMBOLS[key] = (o, dict(ext), {k: sorted(v | {0}) for k, v in offs.items()})
    return _SECTION_SYMBOLS[key][1:]


def bind_unit(u, r, ctx):
    """Check u against retail and bind its relocations [(offset, type, name)];
    returns None, or why it is refused.

    boot_relayout.py's check-driven modes set ctx flags: `defer` links a name that
    denotes another address than retail's target (or an internal target that
    differs) as the object says, for its semantic image check to judge; `own`
    {retail start: size} binds references to data the object defines to the
    object's own copy (`_bootd_<rva>`), `defer_data` skips the content comparison,
    and `datum_refs` collects {unit rva: [(retail start, size, path, section, offset,
    bias, by section symbol)]} of the data `datum_extent(obj, section, offset, anchor)
    -> (start, size)` delimits (bias: the reference's offset from that start;
    table[i - 10] is -40; a section-symbol reference hides it).
    With `datum_refs`, ctx["biased_refs"] {("unit", rva): [(site, retail target, base)]}
    also collects every reference whose retail target is not the address it means
    (`base`: its datum's start, else target - addend), and a reference whose target
    and base lie in different owned data (`own`) is refused: bound by either, an
    index off it would reach the wrong copy."""
    secs, syms, data = u.obj
    defer, own, refs = ctx.get("defer"), ctx.get("own"), ctx.get("datum_refs")
    if refs is not None:
        refs[u.rva] = []
        biased = ctx.setdefault("biased_refs", {})[("unit", u.rva)] = []
    s = secs[u.sec - 1]
    tstart, _, text = r.secs[".text"]
    body = bytearray(data[s.ptr + u.off:s.ptr + u.off + u.size])
    want = text[u.rva - tstart:u.rva - tstart + u.size]
    # bytes outside relocation fields first: a wrong slice reports bytes-differ, not the
    # first relocation it happens to trip over
    masks = {k for off, _, _ in s.relocs for k in range(off - u.off, off - u.off + 4) if 0 <= k < u.size}
    if any(body[k] != want[k] for k in range(u.size) if k not in masks):
        return "bytes-differ"
    relocs, bind, need = [], collections.Counter(), {}
    for off, si, kind in s.relocs:
        o = off - u.off
        if o + 4 <= 0 or o >= u.size:
            continue
        if o < 0 or o + 4 > u.size:
            return "reloc-straddles-extent"
        if kind not in (DIR32, REL32):
            return f"reloc-type-{kind:#x}"
        y = syms[si]
        add = struct.unpack_from("<i", body, o)[0]
        if kind == DIR32:
            v = struct.unpack_from("<I", want, o)[0]
            if y.sec == 0 and y.name in ABSOLUTE:
                if v != (ABSOLUTE[y.name] + add) & 0xFFFFFFFF:
                    return f"absolute-differs:{y.name}"
                relocs.append((o, kind, y.name))
                need[y.name] = ABSOLUTE[y.name]
                bind["absolute"] += 1
                continue
            t = v - RETAIL_BASE
            if not 0 < t < r.size_of_image:
                return "dir32-retail-not-an-address"
            if u.rva + o not in ctx["sites"] and not ctx["lost"][0] <= u.rva + o < ctx["lost"][1]:
                return "dir32-not-a-retail-site"
        else:
            t = u.rva + o + 4 + struct.unpack_from("<i", want, o)[0]
        if y.sec == u.sec and u.off <= y.value + add <= u.off + u.size:        # its own section
            if t != u.rva + y.value + add - u.off:
                if not defer:
                    return "internal-target-differs"
                bind["internal-deferred"] += 1
            struct.pack_into("<i", body, o, y.value + add - u.off)
            relocs.append((o, kind, u.label))
            bind["internal"] += 1
        elif y.sec == 0 and y.name.startswith("__imp_"):
            e = ctx["iat"].get(t)
            if kind != DIR32 or add or e is None or (e[1] or "") not in import_entry_names(y.name):
                return f"import-differs:{y.name}"
            relocs.append((o, kind, "__imp_" + import_symbol(e)))
            bind["import"] += 1
        elif t in ctx["iat"]:
            # retail reads an import slot here through a name standing in for it (a global pinned
            # at the slot): the image's slots are the linker's, so it binds to the import itself
            if kind != DIR32 or add or 0 < y.sec <= len(secs):
                return f"import-slot-differs:{y.name}"
            if y.name in ctx["ident"] and t not in ctx["ident"][y.name]:
                return f"identity-differs:{y.name}"
            relocs.append((o, kind, "__imp_" + import_symbol(ctx["iat"][t])))
            bind["import-slot-by-other-name"] += 1
        else:
            named = y.cls in (EXTERNAL, WEAK) and (y.name in ctx["ident"] or y.name in ctx["authored"])
            defined = 0 < y.sec <= len(secs)
            if named:                                   # a retail identity: it must be this address
                at = t - add
                known = ctx["ident"].get(y.name, set()) | ctx["authored"].get(y.name, set())
                if at not in known:
                    if not (defer and len(known) == 1):
                        return f"identity-differs:{y.name}"
                    at = next(iter(known))              # the name's own address; the image check judges it
                    bind["identity-deferred"] += 1
                name = y.name if known == {at} else f"_boota_{at:08X}"
                bind["name" if known == {at} else "name-of-several-addresses"] += 1
            else:                                       # TU statics, literals, unidentified externals
                at, name = t, f"_boota_{t:08X}"
                struct.pack_into("<i", body, o, 0)
                bind["site-content" if defined else "site"] += 1
            base = t - add                              # the retail address the reference means
            datum = refs is not None and defined and not secs[y.sec - 1].name.startswith(".text")
            if datum:
                q = y.value + add
                lo, n = ctx["datum_extent"](u.obj, y.sec, q, datum_anchor(u.obj, y, q))
                base = rlo = t - (q - lo)
                refs[u.rva].append((rlo, n, u.path, y.sec, lo, q - lo, is_section_symbol(u.obj, y)))
            if refs is not None and t != base:
                biased.append((u.rva + o, t, base))
                if owned_span(ctx, t) != owned_span(ctx, base):
                    return f"biased-across-owned-data:{y.name}"
            # data the object defines (and code it defines under no identity) must equal retail's there
            if datum:
                if (own or {}).get(rlo) == n:           # the object's own copy of its data
                    struct.pack_into("<i", body, o, q - lo)
                    relocs.append((o, kind, f"_bootd_{rlo:08X}"))
                    need[f"_bootd_{rlo:08X}"] = rlo
                    bind["own-data"] += 1
                    continue
                if ctx.get("defer_data"):
                    defined = False
                    bind["content-deferred"] += 1
            if defined and not (named and secs[y.sec - 1].name.startswith(".text")):
                q = y.value + add
                lo, raw, masked = object_datum(u.obj, y.sec, q, at=datum_anchor(u.obj, y, q))
                rlo = t - (q - lo)
                rsec = r.section_of(rlo)
                if not raw or rsec is None or r.section_of(rlo + len(raw) - 1) != rsec:
                    return f"datum-outside-retail:{y.name}"
                s0, _, rraw = r.secs[rsec]
                rb = rraw[rlo - s0:rlo - s0 + len(raw)]
                if any(raw[k] != rb[k] for k in range(len(raw)) if k not in masked):
                    return f"datum-differs:{y.name}"
                bind["content-equal"] += 1
            if r.section_of(at, end_ok=True) is None:   # nothing of the image's to define the name in
                return f"target-outside-kept-sections:{y.name}"
            relocs.append((o, kind, name))
            need[name] = at
    dir32 = {u.rva + o for o, k, n in relocs if k == DIR32 and n not in ABSOLUTE}
    sl = ctx["site_list"]
    if any(x not in dir32 for x in sl[bisect.bisect_left(sl, u.rva):bisect.bisect_left(sl, u.rva + u.size)]):
        return "retail-site-unrelocated"
    u.body, u.relocs, u.bind = bytes(body), relocs, bind
    ctx["need"].update(need)
    return None


def owned_span(ctx, a):
    """(retail start, size) of the owned datum (ctx["own"]) holding a, or None."""
    own = ctx.get("own") or {}
    spans = ctx.get("_own_spans")
    if spans is None or spans[0] is not own:
        spans = ctx["_own_spans"] = (own, sorted(own.items()))
    i = bisect.bisect_right(spans[1], (a, float("inf"))) - 1
    return spans[1][i] if i >= 0 and a < spans[1][i][0] + spans[1][i][1] else None


def unit_names(u):
    """{external name: rva} the unit's own section defines."""
    return {n: u.rva + v - u.off for n, v in section_symbols(u.obj)[0].get(u.sec, ())
            if u.off <= v < u.off + u.size}


def overlay_plan(r, sites, lost, rows, objs=None, opts=None):
    """(admitted units, refusals [(row, why)], names {name: rva}) for the rows;
    `names` holds every name the units reference or define, each one address.
    `opts` (boot_relayout.py) are extra bind_unit flags; the context is left in
    opts["ctx"]."""
    if objs is None:
        import link_cycle
        objs = link_cycle.Objects([])
    units, refused = find_units(r, rows, objs)
    kept = []
    for u in units:
        if kept and u.rva < kept[-1].rva + kept[-1].size:
            if (u.rva, u.size) == (kept[-1].rva, kept[-1].size):     # ICF: one body, several rows
                kept[-1].folded += [x["name"] for x in u.rows]
                refused += [(x, "folded-into:" + kept[-1].rows[0]["name"]) for x in u.rows]
            else:
                refused += [(x, "overlaps-another-unit") for x in u.rows]
            continue
        kept.append(u)
    ident = identities(r)
    ctx = {"sites": set(sites), "site_list": sites, "lost": lost, "iat": r.imports(), "ident": ident}
    ctx.update(opts or {})
    live = kept
    while True:
        authored = collections.defaultdict(set)
        for u in live:
            for n, a in unit_names(u).items():
                authored[n].add(a)
        ctx.update(authored=authored, need={})
        ok = []
        for u in live:
            u.why = bind_unit(u, r, ctx)
            if u.why is None:
                ok.append(u)
        if len(ok) == len(live):
            break
        live = ok
    refused += [(x, u.why) for u in kept if u.why for x in u.rows]
    if opts is not None:
        opts["ctx"] = ctx
    names = dict(ctx["need"])
    for u in live:
        names[u.label] = u.rva
        for n, a in unit_names(u).items():
            if ctx["authored"][n] == {a} and ident.get(n, {a}) == {a}:
                names.setdefault(n, a)
        for n in u.folded:
            if ident.get(n) == {u.rva}:
                names.setdefault(n, u.rva)
    return live, refused, names


def unit_public(u, names):
    """The name scaffold references into u resolve to: its row's own name when that
    is the authored definition at u's start, else u's label."""
    n = u.rows[0]["name"]
    return n if (names or {}).get(n) == u.rva else u.label


def write_overlay(pieces, path, names):
    """The authored objects: one section per unit piece (its compiled bytes, its
    relocations against the bound names) and a public for every name in `names`
    that lies inside a unit. Returns (the import symbols referenced, the paths)."""
    mine = [p for p in pieces if p.unit is not None]
    chunks = [mine[i:i + MAX_SECTIONS] for i in range(0, len(mine), MAX_SECTIONS)]
    starts = [p.start for p in mine]
    defs = collections.defaultdict(list)
    for name, rva in sorted(names.items()):
        i = bisect.bisect_right(starts, rva) - 1
        if name not in ABSOLUTE and i >= 0 and rva < mine[i].start + mine[i].size:
            defs[i // MAX_SECTIONS].append((name, i % MAX_SECTIONS + 1, rva - mine[i].start))
    imports, paths = set(), chunk_paths(path, len(chunks))
    for c, chunk in enumerate(chunks):
        syms = Symbols()
        for k, p in enumerate(chunk, 1):
            syms.add(p.public, k, 0)
        for name, k, value in defs[c]:
            syms.add(name, k, value)
        sections = [(p.name, p.flags, p.unit.body, [(o, syms.add(n), k) for o, k, n in p.unit.relocs])
                    for p in chunk]
        write_coff(paths[c], sections, syms)
        imports |= {n[len("__imp_"):] for n in syms.index if n.startswith("__imp_")}
    return sorted(imports), paths


def link_image(objs, base, out, tag, entry="boot_entry"):
    """link.exe without /FORCE: (exit code, log, seconds)."""
    root = build.vc71_root()
    cmd = [str(root / "Vc7/bin/link.exe"), "/NOLOGO", "/NODEFAULTLIB", "/INCREMENTAL:NO", "/MACHINE:X86",
           "/SUBSYSTEM:WINDOWS", "/FIXED:NO", f"/BASE:0x{base:X}", "/OPT:NOREF", "/OPT:NOICF",
           f"/ENTRY:{entry}", f"/MAP:{build.wine_path(out / (tag + '.map'))}",
           f"/OUT:{build.wine_path(out / (tag + '.exe'))}"] + [build.wine_path(o) for o in objs]
    if sys.platform != "win32":
        cmd.insert(0, "wine")
    for p in (out / (tag + ".map"), out / (tag + ".exe")):
        p.unlink(missing_ok=True)
    t = time.time()
    res = subprocess.run(cmd, capture_output=True, text=True, errors="replace",
                         env=build.compiler_environment(root), cwd=out)
    log = res.stdout + res.stderr
    (out / (tag + ".log")).write_text(log, encoding="utf-8")
    return res.returncode, log, time.time() - t


def read_publics(mapfile, base):
    """{public name: rva} from a link.exe map (Rva+Base column)."""
    out = {}
    for line in Path(mapfile).read_text(encoding="latin-1").splitlines():
        f = line.split()
        if len(f) >= 4 and len(f[0]) == 13 and f[0][4] == ":" and len(f[2]) == 8:
            try:
                out[f[1]] = int(f[2], 16) - base
            except ValueError:
                pass
    return out


def entry_ok(image_entry, entry, pieces, new_start, publics):
    """1 when the image's AddressOfEntryPoint is `_boot_entry` and that is the moved
    copy of retail's entry: the new address (`new_start(piece)`) of the piece holding
    it plus the entry's offset in the piece. Else 0."""
    p = next((p for p in pieces if p.start <= entry < p.start + p.size), None)
    return int(p is not None and image_entry == publics.get("_boot_entry") == new_start(p) + entry - p.start)


def check_image(r, pieces, exe, base, publics):
    """Field-by-field equivalence of the linked image with retail: every
    non-relocated byte equal; every relocated field points at the moved copy of
    retail's target; every IAT reference imports retail's (dll, name). Overlaid
    (authored) pieces are held to the same rule and also counted apart. Every
    .text piece keeps one offset from retail (rel32 operands are not relocated),
    and the image's base relocations are exactly the relocated fields."""
    pe = pefile.PE(str(exe))
    img = pe.get_memory_mapped_image()
    new_iat = {}
    for d in pe.DIRECTORY_ENTRY_IMPORT:
        for imp in d.imports:
            new_iat[imp.address - base] = (d.dll.decode("latin-1").lower(),
                                           imp.name.decode("latin-1") if imp.name else None,
                                           None if imp.name else imp.ordinal)
    moved = {p.start: publics[p.public] for p in pieces}
    c, bad = collections.Counter(), []
    fields = set()
    for p in pieces:
        s0, _, raw = next(v for v in r.secs.values() if v[0] <= p.start < v[0] + v[1])
        want = bytearray(raw[p.start - s0:p.start - s0 + p.size])
        got = bytearray(img[moved[p.start]:moved[p.start] + p.size])
        tag = "authored-" if p.unit is not None else ""
        for site, kind, tgt in p.relocs:
            o = site - p.start
            v = struct.unpack_from("<I", got, o)[0]
            if tgt[0] == "piece":
                ok = v == moved[tgt[1].start] + tgt[2] - tgt[1].start + (base if kind == DIR32 else 0)
            elif tgt[0] == "imp":
                ok = new_iat.get(v - base) == tgt[1]
            else:
                ok = v == base + tgt[1]
            c["reloc-ok" if ok else "reloc-bad"] += 1
            if tag:
                c[tag + ("reloc-ok" if ok else "reloc-bad")] += 1
            if not ok and len(bad) < 20:
                bad.append(f"{site:#x} {tgt[0]} got {v:#x}" + (f" in authored {p.unit.rows[0]['name']}" if tag else ""))
            if kind == DIR32:
                fields.add(moved[p.start] + o)
            got[o:o + 4] = want[o:o + 4] = b"\0\0\0\0"
        diff = sum(1 for x, y in zip(got, want) if x != y)
        c["bytes-equal"] += p.size - diff
        c["bytes-differ"] += diff
        if tag:
            c["authored-bytes-equal"] += p.size - diff
            c["authored-bytes-differ"] += diff
            if diff and len(bad) < 20:
                bad.append(f"{p.start:#x} authored {p.unit.rows[0]['name']}: {diff} byte(s) differ")
    text = [p for p in pieces if p.name.startswith(".text")]
    c["text-pieces-moved"] = sum(1 for p in text if moved[p.start] - p.start != moved[text[0].start] - text[0].start)
    dd = pe.OPTIONAL_HEADER.DATA_DIRECTORY[5]
    image_fields = set(parse_blocks(pe.get_data(dd.VirtualAddress, dd.Size))[0]) if dd.Size else set()
    c["baserelocs-missing"] = len(fields - image_fields)
    c["baserelocs-extra"] = len(image_fields - fields)
    c["imports"] = len(new_iat)
    c["resource-dir"] = int(pe.OPTIONAL_HEADER.DATA_DIRECTORY[2].VirtualAddress == moved[r.secs[".rsrc"][0]])
    c["entry-ok"] = entry_ok(pe.OPTIONAL_HEADER.AddressOfEntryPoint, r.entry, pieces, lambda p: moved[p.start],
                             publics)
    exp = r.pe.OPTIONAL_HEADER.DATA_DIRECTORY[0].VirtualAddress
    c["export-dir"] = int(pe.OPTIONAL_HEADER.DATA_DIRECTORY[0].VirtualAddress == moved[exp])
    c["exports"] = len(pe.DIRECTORY_ENTRY_EXPORT.symbols) if hasattr(pe, "DIRECTORY_ENTRY_EXPORT") else 0
    return dict(c), bad


def overlay_report(r, units, refused, rows, path):
    """Summary of an overlay, and <tag>.overlay.csv: one line per requested row."""
    with open(path, "w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(["retail_rva", "size", "name", "source", "overlay"])
        lines = [(u.rva, u.size, x["name"], x["source"], "overlaid") for u in units for x in u.rows]
        lines += [(int(x["target_rva"], 16), int(x["target_size"] or 0), x["name"], x["source"],
                   why if why.startswith("folded") else "refused:" + why) for x, why in refused]
        for rva, size, name, source, st in sorted(lines):
            w.writerow(["0x%08X" % rva, size, name, source, st])
    reasons, binds = collections.Counter(), collections.Counter()
    for _, why in refused:
        reasons[why.split(":")[0]] += 1
    folded = sum(v for k, v in reasons.items() if k.startswith("folded"))
    reasons = {k: v for k, v in reasons.items() if not k.startswith("folded")}
    for u in units:
        binds.update(u.bind)
    nbytes = sum(u.size for u in units)
    return {"rows_requested": len(rows), "rows_overlaid": sum(len(u.rows) for u in units),
            "rows_folded_into_an_overlaid_body": folded, "units": len(units),
            "bytes": nbytes, "share_of_text": round(nbytes / r.secs[".text"][1], 6),
            "refused": dict(sorted(reasons.items(), key=lambda kv: -kv[1])), "bindings": dict(sorted(binds.items())),
            "rows_csv": str(path)}


def layout(r, overlay=(), status=LINK_STATUS, rows=None):
    """(pieces, problems, reloc info, units, refusals, names, rows): the scaffold's
    pieces with the overlay's admitted units cut in (rows None: no overlay)."""
    sites, info = all_sites(r)
    units, refused, names = (), [], {}
    if overlay or rows is not None:
        rows = overlay_rows(overlay, status) if rows is None else rows
        lost = tuple(int(x, 16) for x in info["lost_pages"])
        units, refused, names = overlay_plan(r, sites, lost, rows)
        # a unit's DIR32 fields in pages the table lost are checked like retail's sites
        sites = sorted(set(sites) | {u.rva + o for u in units for o, k, n in u.relocs
                                     if k == DIR32 and n not in ABSOLUTE})
    pieces, problems = plan(r, sites, units)
    return pieces, problems, info, units, refused, names, rows


# ---------------------------------------------------------------- provenance
# What a report was built from, so tools/image_ownership.py can bind a measurement
# to one commit, one image file, one map and the exact objects the link consumed,
# and refuse a stale, dirty or moving one. Untracked files count: an untracked .cpp
# or .h a unit compiled is an input no commit holds.
PROVENANCE_INPUTS = ("Code", "reference", "vendor", "reverse/functions.csv", "reverse/symbols.csv",
                     "reverse/data_ledger.csv", "reverse/ghidra_functions.csv")
BUILD_TOOLS = ("boot_image.py", "boot_relayout.py", "link_cycle.py", "build.py")
TIME_FORMAT = "%Y-%m-%dT%H:%M:%SZ"


def sha256_file(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for block in iter(lambda: f.read(1 << 20), b""):
            h.update(block)
    return h.hexdigest()


def _git(*a):
    return subprocess.run(["git", *a], cwd=ROOT, capture_output=True, text=True, errors="replace").stdout


def _rel(path):
    try:
        return Path(path).resolve().relative_to(ROOT).as_posix()
    except ValueError:
        return Path(path).as_posix()


def spec_files(specs, status):
    """The files the overlay specs read besides the tree: the link status
    (closed / shift-safe) and each rows:FILE."""
    out = [Path(status)] if any(s in ("closed", "shift-safe") for s in specs) else []
    return out + [Path(s[len("rows:"):]) for s in specs if s.startswith("rows:")]


def snapshot_specs(specs, status, into):
    """(specs, status, {file: sha256}) reading private copies in `into`: every spec
    file (spec_files) is read once, before selection, and the overlay selects from
    that copy, so the digests are of the bytes selected from (None: missing). The
    link status lies under build/, outside input_state's paths: only this binds it."""
    digests, copy = {}, {}
    for k, p in enumerate(spec_files(specs, status)):
        try:
            data = p.read_bytes()
        except FileNotFoundError:
            digests[_rel(p)] = None
            continue
        q = Path(into) / f"spec{k}{p.suffix}"
        q.write_bytes(data)
        digests[_rel(p)] = hashlib.sha256(data).hexdigest()
        copy[str(p)] = q
    return ([f"rows:{copy.get(str(Path(s[5:])), s[5:])}" if s.startswith("rows:") else s for s in specs],
            copy.get(str(Path(status)), status), digests)


def snapshot_artifacts(exe, into):
    """(image, map) copied once into the private directory `into`: the image check
    and provenance read these, so the digests bind exactly the checked bytes even
    when another build rewrites out/ meanwhile (measure then finds out/ unbound)."""
    exe, copies = Path(exe), []
    Path(into).mkdir(parents=True, exist_ok=True)
    for p in (exe, exe.with_suffix(".map")):
        q = Path(into) / p.name
        q.write_bytes(p.read_bytes())
        copies.append(q)
    return copies


def input_state():
    """HEAD, and the uncommitted state (tracked edits and untracked files) of every
    build input and build tool: equal at a build's start and end when nothing moved
    under it. `status` lists what is not committed."""
    paths = [*PROVENANCE_INPUTS, *("tools/" + t for t in BUILD_TOOLS)]
    status = _git("status", "--porcelain", "--untracked-files=all", "--", *paths)
    diff = _git("diff", "HEAD", "--", *paths)
    return {"head": _git("rev-parse", "HEAD").strip(), "status": status.splitlines(),
            "digest": hashlib.sha256((status + "\0" + diff).encode()).hexdigest()}


def object_untracked_deps(obj, tracked):
    """Recorded dependencies of `obj` (its .deps.json) inside the tree, outside
    build/ (extracted toolchains), that HEAD does not track."""
    sidecar = build._deps_sidecar(Path(obj))
    try:
        deps = json.loads(sidecar.read_text()).get("deps", {})
    except (OSError, ValueError):
        return ["<no dependency record>"]
    out = []
    for dep in deps:
        rel = dep.replace("\\", "/")
        if os.path.isabs(rel):
            try:
                rel = Path(rel).resolve().relative_to(ROOT).as_posix()
            except ValueError:
                continue                                 # outside the tree: the toolchain
        if not rel.startswith("build/") and rel not in tracked:
            out.append(rel)
    return out


def objects_now(entries, tracked=None):
    """Re-judge objects [[path, sha256, source]] as they are now: changed (the file
    is not the bytes consumed), not current, untracked dependencies. Current is
    build.compile_is_current(strict=True), link_census' receipt: source, compile
    command, every recorded header and the include search inventory unchanged. A
    prebuilt-library member has no source."""
    if tracked is None:
        tracked = set(_git("ls-files", "--recurse-submodules").splitlines())
    changed, stale, untracked, cache = [], [], [], {}
    for rel, digest, source in entries:
        path = Path(rel) if os.path.isabs(rel) else ROOT / rel
        if not path.exists() or sha256_file(path) != digest:
            changed.append(rel)
            continue
        if Path(source).suffix.lower() == build.LIB_SUFFIX:
            continue
        if not build.compile_is_current(ROOT / source, path, strict=True, inventory_cache=cache):
            stale.append(rel)
        untracked += [f"{rel}: {d}" for d in object_untracked_deps(path, tracked)]
    return {"changed": changed, "not_current": stale, "untracked_deps": untracked}


def objects_digest(entries):
    """The digest of an object manifest [[path, sha256, source]] (image_ownership re-derives it)."""
    h = hashlib.sha256()
    for rel, digest, source in entries:
        h.update(f"{rel}\0{digest}\0{source}\n".encode())
    return h.hexdigest()


def objects_state(units):
    """The objects the units were read from, as consumed: [[path, sha256 of the bytes
    the overlay read, source]], their digest, objects_now's verdicts on them, and
    where each unit's bytes lie in them: [[retail rva, size, path, section number,
    offset]] (image_ownership compares the image with those bytes)."""
    by_path = {}
    for u in units:
        by_path.setdefault(_rel(u.path), (u.obj[2], u.rows[0]["source"]))
    entries = [[rel, hashlib.sha256(data).hexdigest(), source] for rel, (data, source) in sorted(by_path.items())]
    now = objects_now(entries)
    return {"count": len(entries), "digest": objects_digest(entries), "entries": entries,
            "units": sorted([u.rva, u.size, _rel(u.path), u.sec, u.off] for u in units),
            "changed": len(now["changed"]), "not_current": len(now["not_current"]),
            "untracked_deps": len(now["untracked_deps"]),
            "examples": (now["changed"] + now["not_current"] + now["untracked_deps"])[:20]}


def provenance(r, units, exe, rows_csv=None, start=None, specs=(), status=LINK_STATUS, seed=None, spec_digests=None):
    """The build's commit and input state (at `start` and now: moved means dirty),
    digests of the retail baseline, every ledger and spec file it read (`spec_digests`:
    snapshot_specs' digests of the copies selected from; a spec file that differs
    from them now moved under the build), the build tools, the consumed objects and
    the linked image and map (`exe`: snapshot_artifacts' copy, the bytes checked)."""
    tools = hashlib.sha256()
    for name in BUILD_TOOLS:
        tools.update(name.encode() + b"\0" + (ROOT / "tools" / name).read_bytes())
    end = input_state()
    start = start or end

    def lf_sha(path):                    # LF line ends, as the committed blob: one digest on any checkout
        p = ROOT / path
        return hashlib.sha256(p.read_bytes().replace(b"\r\n", b"\n")).hexdigest() if p.exists() else None
    exe = Path(exe)
    specs_now = {_rel(p): sha256_file(p) if p.exists() else None for p in spec_files(specs, status)}
    spec_digests = specs_now if spec_digests is None else spec_digests
    specs_moved = specs_now != spec_digests
    out = {"commit": end["head"], "dirty": bool(end["status"]) or start != end or specs_moved,
           "inputs_moved": start != end or specs_moved, "specs_moved": specs_moved,
           "dirty_paths": end["status"][:20], "inputs_start": start["digest"], "inputs_end": end["digest"],
           "built_utc": time.strftime(TIME_FORMAT, time.gmtime()),
           "retail_sha256": hashlib.sha256(r.data).hexdigest(),
           "ledger_sha256": lf_sha("reverse/functions.csv"),
           "inputs_sha256": {p: lf_sha(p) for p in PROVENANCE_INPUTS if p.startswith("reverse/")},
           "spec_files_sha256": dict(spec_digests),
           "overlay_specs": list(specs), "seed": seed,
           "build_tools_sha256": tools.hexdigest(), "objects": objects_state(units),
           "image_sha256": sha256_file(exe) if exe.exists() else None,
           "map_sha256": sha256_file(exe.with_suffix(".map")) if exe.with_suffix(".map").exists() else None}
    if rows_csv is not None and Path(rows_csv).exists():
        out["rows_csv_sha256"] = sha256_file(rows_csv)
    return out


def build_image(base=real_image.IMAGE_BASE, out=OUT, tag="boot", overlay=(), status=LINK_STATUS, rows=None):
    """Link (and check) the image; `overlay` specs (or explicit ledger `rows`) put
    authored units in it."""
    # Paths passed to Wine link.exe must remain valid when cwd is changed to out.
    out = out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    start = input_state()                        # provenance: what moved while this built
    snap = Path(tempfile.mkdtemp(prefix="boot_image_"))       # the spec files and artifacts as read
    specs, status_read, spec_digests = snapshot_specs(overlay, status, snap)
    r = Retail()
    t = time.time()
    pieces, problems, info, units, refused, names, rows = layout(r, specs, status_read, rows)
    ov = None
    if rows is not None:
        ov = overlay_report(r, units, refused, rows, out / (tag + ".overlay.csv"))
        ov["specs"] = list(overlay)
    for stale in list(out.glob("scaffold*.obj")) + list(out.glob("overlay*.obj")):
        stale.unlink()
    names = dict(names, _boot_entry=r.entry)     # defined by whichever object holds the entry point
    used, objs = write_scaffold(r, pieces, out / "scaffold.obj", names)
    if units:
        more, paths = write_overlay(pieces, out / "overlay.obj", names)
        used, objs = sorted(set(used) | set(more)), objs + paths
    by_sym = {}
    for e in r.imports().values():
        by_sym.setdefault(import_symbol(e), e)
    write_import_lib([(n, by_sym[n]) for n in used], out / "retail_imports.lib")
    descs = descriptor_libs(sorted({by_sym[n][0] for n in used}), out)
    rc, log, secs = link_image(objs + [out / "retail_imports.lib"] + descs, base, out, tag)
    report = {"base": hex(base), "relocs": info, "problems": dict(problems), "pieces": len(pieces),
              "imports_used": len(used), "link_exit": rc, "link_seconds": round(secs, 1),
              "link_log": log.strip().splitlines()[-20:],
              "crt": {p.name: [hex(p.start), p.size] for p in pieces if p.name.startswith(".CRT")}}
    if ov is not None:
        report["overlay"] = ov
    if rc == 0:
        exe, mapfile = snapshot_artifacts(out / (tag + ".exe"), snap)
        publics = read_publics(mapfile, base)
        counts, bad = check_image(r, pieces, exe, base, publics)
        report.update(check=counts, check_bad=bad)
        report["pieces_map"] = [[p.name, p.start, publics[p.public], p.size] for p in pieces]
        report["authored"] = [[u.rva, u.size, u.rows[0]["name"]] for u in units]
        if ov is not None:
            ok = not (counts.get("authored-bytes-differ") or counts.get("authored-reloc-bad"))
            ov["verified_bytes"] = ov["bytes"] if ok else 0
            ov["verified_share_of_text"] = ov["share_of_text"] if ok else 0
        report["provenance"] = provenance(r, units, exe, out / (tag + ".overlay.csv") if ov else None,
                                          start, overlay, status, spec_digests=spec_digests)
    shutil.rmtree(snap, ignore_errors=True)
    report["seconds"] = round(time.time() - t, 1)
    (out / (tag + ".json")).write_text(json.dumps(report, indent=1), encoding="utf-8")
    return report


def image_ok(rep):
    """The link succeeded and the check found no difference of any kind."""
    chk = rep.get("check", {})
    return rep["link_exit"] == 0 and bool(chk) and not any(
        chk.get(k) for k in ("reloc-bad", "bytes-differ", "text-pieces-moved", "scaffold-pieces-moved",
                             "baserelocs-missing", "baserelocs-extra")) and all(
        chk.get(k) == 1 for k in ("entry-ok", "export-dir", "resource-dir"))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("relocs")
    p.add_argument("--validate", action="store_true")
    p = sub.add_parser("link")
    p.add_argument("--base", type=lambda v: int(v, 0), default=real_image.IMAGE_BASE)
    p.add_argument("--out", type=Path, default=OUT)
    p.add_argument("--tag", default="boot")
    p.add_argument("--overlay", action="append", default=[], metavar="SET",
                   help="authored units to link in: closed | shift-safe (link_cycle certification), "
                        "rows:FILE, or a tree path prefix; repeatable (union)")
    p.add_argument("--status", type=Path, default=LINK_STATUS, help="link_cycle link_status.csv for closed/shift-safe")
    p.add_argument("--relayout", action="store_true",
                   help="move the overlay's units to a fresh section, int3 their retail ranges (boot_relayout.py)")
    p.add_argument("--own-data", action="store_true",
                   help="place data the units' objects define in our own sections and bind to it (boot_relayout.py)")
    p.add_argument("--seed", type=int, default=0, help="--relayout: the moved units' shuffle")
    p.add_argument("--ownership", action="store_true",
                   help="then print who owns every byte of the image (tools/image_ownership.py; records nothing)")
    args = ap.parse_args(argv)
    if args.cmd == "link":
        if args.relayout or args.own_data:
            import boot_relayout
            rep = boot_relayout.build_image(args.base, args.out, args.tag, args.overlay, args.status,
                                            relayout=args.relayout, own_data=args.own_data, seed=args.seed)
        else:
            rep = build_image(args.base, args.out, args.tag, args.overlay, args.status)
        print(json.dumps({k: v for k, v in rep.items() if k not in ("pieces_map", "authored", "_layout")}, indent=1))
        if args.ownership and rep["link_exit"] == 0:
            import image_ownership
            receipt = image_ownership.measure(args.out.resolve() / (args.tag + ".json"))
            print("\n".join(image_ownership.summary_lines(receipt)))
        return 0 if image_ok(rep) else 1
    r = Retail()
    if args.cmd == "relocs":
        if args.validate:
            print(json.dumps(validate_recovery(r), indent=1))
        else:
            print(json.dumps(all_sites(r)[1], indent=1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
