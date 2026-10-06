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
     copy of retail's target, every IAT slot the same (dll, name).

The scaffold is retail bytes. It is never progress: no row is credited here.

  python3 tools/boot_image.py relocs [--validate]
  python3 tools/boot_image.py link [--base 0x10000000] [--out build/boot]
"""
import argparse
import bisect
import collections
import csv
import json
import struct
import subprocess
import sys
import time
from pathlib import Path

import capstone
import pefile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402

RETAIL_BASE = 0x400000
OUT = ROOT / "build" / "boot"
KEEP = (".text", ".rdata", ".data", "STLPORT_", "rts.ver", ".rsrc")
RELOC_SECTION = b"        "             # retail's .reloc, renamed by the wrapper
DIR32, DIR32NB = 6, 7
FUNCLETS = 0x75B460                     # .text$x, $yc, $yd: EH funclets and initializers
ALIGN_4096 = 0x00D00000
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
    __slots__ = ("name", "start", "size", "flags", "relocs", "label", "pad")

    def __init__(self, name, start, size, flags):
        self.name, self.start, self.size, self.flags, self.relocs = name, start, size, flags, []
        self.label = None
        # a page-aligned piece cut from mid-section keeps retail's address mod 4096
        # (movdqa on a .data table faults when a carve shifts it by 8)
        self.pad = start & 0xFFF if flags & 0x00F00000 == ALIGN_4096 else 0


def plan(r, sites):
    """(pieces sorted by start, problems). Each piece carries its relocations
    [(site, type, target)]; target = ("piece", Piece, rva) | ("imp", (dll, name,
    ordinal)) | ("base", offset)."""
    pieces = []
    carve = crt_pieces(r)
    exp = r.pe.OPTIONAL_HEADER.DATA_DIRECTORY[0]
    carve[".edata"] = (exp.VirtualAddress, exp.Size)
    for sec, (start, size, _) in r.secs.items():
        coff = ".rsrc$01" if sec == ".rsrc" else sec
        cuts = sorted((s, sz, n) for n, (s, sz) in carve.items() if start <= s < start + size)
        cur = start
        for s, sz, n in cuts + [(start + size, 0, None)]:
            if s > cur:
                pieces.append(Piece(coff, cur, s - cur, FLAGS[coff]))
            if n:
                pieces.append(Piece(n, s, sz, FLAGS[".CRT" if n.startswith(".CRT") else n]))
            cur = max(cur, s + sz)
    pieces.sort(key=lambda p: p.start)
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


def write_scaffold(r, pieces, path):
    """One COFF object: one section per piece, DIR32/DIR32NB relocations against
    the owning piece's label (addend in place), __imp_ and ___ImageBase
    externals, `_boot_entry` and a `_bootp_<rva>` public at each piece start.
    Returns the import symbols it references."""
    syms, index = [], {}

    def sym(name, sec, value, cls):
        if name not in index:
            index[name] = len(syms)
            syms.append((name, sec, value, cls))
        return index[name]
    for k, p in enumerate(pieces, 1):
        p.label = sym(f"_bootp_{p.start:08X}", k, p.pad, 2)
    entry = next(k for k, p in enumerate(pieces, 1) if p.start <= r.entry < p.start + p.size)
    sym("_boot_entry", entry, r.entry - pieces[entry - 1].start + pieces[entry - 1].pad, 2)
    bodies, relocs = [], []
    for p in pieces:
        s0, _, raw = next(v for v in r.secs.values() if v[0] <= p.start < v[0] + v[1])
        body = bytearray(p.pad) + bytearray(raw[p.start - s0:p.start - s0 + p.size])
        rl = bytearray()
        for site, kind, tgt in p.relocs:
            if tgt[0] == "piece":
                si, add = tgt[1].label, tgt[2] - tgt[1].start
            elif tgt[0] == "imp":
                si, add = sym("__imp_" + import_symbol(tgt[1]), 0, 0, 2), 0
            else:
                si, add = sym("___ImageBase", 0, 0, 2), tgt[1]
            struct.pack_into("<I", body, site - p.start + p.pad, add & 0xFFFFFFFF)
            rl += struct.pack("<IIH", site - p.start + p.pad, si, kind)
        bodies.append(bytes(body))
        relocs.append((len(p.relocs), bytes(rl)))
    strings = bytearray(4)
    hdr_end = 20 + 40 * len(pieces)
    shdr, blob = bytearray(), bytearray()
    for p, body, (n, rl) in zip(pieces, bodies, relocs):
        ptr = hdr_end + len(blob) if body else 0
        blob += body
        rptr = hdr_end + len(blob) if n else 0
        flags, count = p.flags, n
        if n >= 0xFFFF:                       # IMAGE_SCN_LNK_NRELOC_OVFL: the first entry holds the count
            blob += struct.pack("<IIH", n + 1, 0, 0)
            flags, count = flags | NRELOC_OVFL, 0xFFFF
        blob += rl
        shdr += coff_name(p.name, strings) + struct.pack("<IIIIIIHHI", 0, 0, len(body), ptr, rptr, 0, count, 0, flags)
    symtab = bytearray()
    for name, sec, value, cls in syms:
        symtab += coff_name(name, strings) + struct.pack("<IhHBB", value, sec, 0, cls, 0)
    strings[0:4] = struct.pack("<I", len(strings))
    path.write_bytes(struct.pack("<HHIIIHH", 0x14C, len(pieces), 0, hdr_end + len(blob), len(syms), 0, 0)
                     + shdr + blob + symtab + strings)
    return sorted(n[len("__imp_"):] for n in index if n.startswith("__imp_"))


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
        res = subprocess.run([str(root / "Vc7/bin/lib.exe"), "/NOLOGO", "/MACHINE:X86", f"/DEF:{d}", f"/OUT:{lib}"],
                             capture_output=True, text=True, errors="replace", env=build.compiler_environment(root))
        if res.returncode or not lib.exists():
            raise SystemExit(f"boot_image: lib.exe failed for {dll}:\n{res.stdout}{res.stderr}")
        libs.append(lib)
    return libs


def link_image(objs, base, out, tag, entry="boot_entry"):
    """link.exe without /FORCE: (exit code, log, seconds)."""
    root = build.vc71_root()
    cmd = [str(root / "Vc7/bin/link.exe"), "/NOLOGO", "/NODEFAULTLIB", "/INCREMENTAL:NO", "/MACHINE:X86",
           "/SUBSYSTEM:WINDOWS", "/FIXED:NO", f"/BASE:0x{base:X}", "/OPT:NOREF", "/OPT:NOICF",
           f"/ENTRY:{entry}", f"/MAP:{out / (tag + '.map')}", f"/OUT:{out / (tag + '.exe')}"] + [str(o) for o in objs]
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


def check_image(r, pieces, exe, base, publics):
    """Field-by-field equivalence of the linked image with retail: every
    non-relocated byte equal; every relocated field points at the moved copy of
    retail's target; every IAT reference imports retail's (dll, name)."""
    pe = pefile.PE(str(exe))
    img = pe.get_memory_mapped_image()
    new_iat = {}
    for d in pe.DIRECTORY_ENTRY_IMPORT:
        for imp in d.imports:
            new_iat[imp.address - base] = (d.dll.decode("latin-1").lower(),
                                           imp.name.decode("latin-1") if imp.name else None,
                                           None if imp.name else imp.ordinal)
    moved = {p.start: publics[f"_bootp_{p.start:08X}"] for p in pieces}
    c, bad = collections.Counter(), []
    for p in pieces:
        s0, _, raw = next(v for v in r.secs.values() if v[0] <= p.start < v[0] + v[1])
        want = bytearray(raw[p.start - s0:p.start - s0 + p.size])
        got = bytearray(img[moved[p.start]:moved[p.start] + p.size])
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
            if not ok and len(bad) < 20:
                bad.append(f"{site:#x} {tgt[0]} got {v:#x}")
            got[o:o + 4] = want[o:o + 4] = b"\0\0\0\0"
        diff = sum(1 for x, y in zip(got, want) if x != y)
        c["bytes-equal"] += p.size - diff
        c["bytes-differ"] += diff
    c["imports"] = len(new_iat)
    c["resource-dir"] = int(pe.OPTIONAL_HEADER.DATA_DIRECTORY[2].VirtualAddress == moved[r.secs[".rsrc"][0]])
    c["entry-ok"] = int(pe.OPTIONAL_HEADER.AddressOfEntryPoint == publics["_boot_entry"])
    exp = r.pe.OPTIONAL_HEADER.DATA_DIRECTORY[0].VirtualAddress
    c["export-dir"] = int(pe.OPTIONAL_HEADER.DATA_DIRECTORY[0].VirtualAddress == moved[exp])
    c["exports"] = len(pe.DIRECTORY_ENTRY_EXPORT.symbols) if hasattr(pe, "DIRECTORY_ENTRY_EXPORT") else 0
    return dict(c), bad


def build_image(base=0x10000000, out=OUT, tag="boot"):
    out.mkdir(parents=True, exist_ok=True)
    r = Retail()
    t = time.time()
    sites, info = all_sites(r)
    pieces, problems = plan(r, sites)
    used = write_scaffold(r, pieces, out / "scaffold.obj")
    by_sym = {}
    for e in r.imports().values():
        by_sym.setdefault(import_symbol(e), e)
    write_import_lib([(n, by_sym[n]) for n in used], out / "retail_imports.lib")
    descs = descriptor_libs(sorted({by_sym[n][0] for n in used}), out)
    rc, log, secs = link_image([out / "scaffold.obj", out / "retail_imports.lib"] + descs, base, out, tag)
    report = {"base": hex(base), "relocs": info, "problems": dict(problems), "pieces": len(pieces),
              "imports_used": len(used), "link_exit": rc, "link_seconds": round(secs, 1),
              "link_log": log.strip().splitlines()[-20:],
              "crt": {p.name: [hex(p.start), p.size] for p in pieces if p.name.startswith(".CRT")}}
    if rc == 0:
        counts, bad = check_image(r, pieces, out / (tag + ".exe"), base, read_publics(out / (tag + ".map"), base))
        report.update(check=counts, check_bad=bad)
        publics = read_publics(out / (tag + ".map"), base)
        report["pieces_map"] = [[p.name, p.start, publics[f"_bootp_{p.start:08X}"], p.size] for p in pieces]
    report["seconds"] = round(time.time() - t, 1)
    (out / (tag + ".json")).write_text(json.dumps(report, indent=1), encoding="utf-8")
    return report


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("relocs")
    p.add_argument("--validate", action="store_true")
    p = sub.add_parser("link")
    p.add_argument("--base", type=lambda v: int(v, 0), default=0x10000000)
    p.add_argument("--out", type=Path, default=OUT)
    p.add_argument("--tag", default="boot")
    args = ap.parse_args(argv)
    if args.cmd == "link":
        rep = build_image(args.base, args.out, args.tag)
        print(json.dumps(rep, indent=1))
        chk = rep.get("check", {})
        return 0 if rep["link_exit"] == 0 and not chk.get("reloc-bad") and not chk.get("bytes-differ") else 1
    r = Retail()
    if args.cmd == "relocs":
        if args.validate:
            print(json.dumps(validate_recovery(r), indent=1))
        else:
            print(json.dumps(all_sites(r)[1], indent=1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
