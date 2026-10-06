#!/usr/bin/env python3
"""Link the tree at retail's addresses and measure every matched row in the image.

link_census.py asks "does the tree link?". This tool asks "where does each
matched row land in a real link, and is it wired the way retail is?". It is the
productionised /ORDER pilot (research 14), with the link-setup and measurement
fixes of research 29, 31 and the round-2 review:

  1. Collect the object of every matched row (link_census.objects; --build
     compiles stale ones first). Each object section holding matched rows is a
     unit; a unit is ordered at its retail start when its COMDAT head can be
     named in /ORDER and its section group and alignment allow it.
  2. Every retail .text byte no ordered unit covers becomes a retail-byte
     filler COMDAT, so ordered units land at their retail RVAs. Unplaced code
     moves to .text$zz (private object copies) so it cannot push retail's
     groups. A unit whose linked footprint differs from its retail extent is
     quarantined and the link repeats until no order item drifts.
  3. Link setup: __except_list is an absolute 0 (the CRT's definition);
     import libraries are generated from retail's own import table for every
     __imp_ name an object references; /OPT:NOICF. Unresolved names get 4-byte
     data stubs, duplicate definitions need /FORCE; both are counted.
  4. Measure (per ledger row, every failing relocation, not the first):
     - code references translate through the unit or filler that holds the
       linked target and must equal retail's target;
     - an __ehhandler$ thunk counts as its owner function's (owner + offset)
       only when the row is that owner and the FuncInfo, unwind and try maps
       and funclet bodies equal retail's;
     - an other-name copy is an ICF twin only from the fold list this tool
       builds: a retail-owned row start, equal extent, equal non-relocation
       bytes and every relocation resolving to retail's target;
     - data references must map 1:1, and the linked datum's bytes must equal
       retail's at the referenced address (relocated words: code pointers
       translated, data pointers masked); a datum whose name is pinned in
       symbols.csv must sit at its pin (the `pinned` series also fails
       unpinned data);
     - import slots must be the same (dll, name) as retail's slot.
     Closed-strict: self-strict and every code edge (calls and code pointers
     in referenced data) reaches a closed ledger unit or certified twin.
     A filler or stub is never a leaf. Credit = unique retail bytes of placed,
     closed-strict authored rows; fillers, stubs and aliases never count.
  5. A second link at a shifted base (default 0x10000000) with the same
     inputs; a row whose code holds an absolute image address that did not
     move with the base (a hard-coded address) is reported.
  6. A receipt (build/link_cycle/receipt.json) pins the cycle: commit, dirty
     state, toolchain and retail hashes, this tool's digest, objects digest,
     every series and the wall time of each phase.

  python3 tools/link_cycle.py [--build] [--max-iter 6] [--shift-base 0x10000000]
  python3 tools/link_cycle.py --measure-only     # re-measure the last links

Outputs in build/link_cycle/: link_status.csv (one row per matched ledger
row), fold_list.csv, receipt.json, base.map/.exe/.log, shift.*. Diagnostic:
the image is not expected to run.
"""
import argparse
import bisect
import collections
import concurrent.futures
import csv
import hashlib
import json
import os
import re
import struct
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import link_census as census  # noqa: E402

OUT = ROOT / "build" / "link_cycle"
BASE = 0x400000
SHIFT_BASE = 0x10000000
# retail .text is four groups: .text | .text$x (EH funclets) | .text$yc (dynamic
# initializers) | .text$yd (atexit dtors). /ORDER sorts only within a group, so
# a filler carries its region's group name. Boundaries: retail BFME2 1.06.
REGIONS = [(0x1000, ".text"), (0x75B460, ".text$x"), (0x7AB900, ".text$yc"), (0x7B68D0, ".text$yd")]
ABSOLUTE = {"__except_list": 0}          # exsup.asm: __except_list equ 0 (an FS: offset)
TOOL_FILES = ("link_cycle.py", "link_census.py", "build.py")
COMDAT, EXTERNAL, STATIC, WEAK = 0x1000, 2, 3, 105
REL32, DIR32 = 0x14, 6


# ---------------------------------------------------------------- COFF
class Sec:
    __slots__ = ("idx", "name", "size", "ptr", "flags", "relocs", "sel")


class Sym:
    __slots__ = ("i", "name", "value", "sec", "cls")


def parse_coff(data):
    """(sections, {raw index: Sym}) of an i386 COFF object."""
    _, nsec, _, symptr, nsym, opt, _ = struct.unpack_from("<HHIIIHH", data, 0)
    strtab = symptr + nsym * 18

    def text(raw):
        if raw[:4] == b"\0\0\0\0":
            off = strtab + struct.unpack_from("<I", raw, 4)[0]
            return data[off:data.index(b"\0", off)].decode("latin-1")
        return raw.rstrip(b"\0").decode("latin-1")
    secs = []
    for k in range(nsec):
        o = 20 + opt + 40 * k
        s = Sec()
        s.idx = k + 1
        nm = data[o:o + 8].rstrip(b"\0").decode("latin-1")
        if nm.startswith("/"):
            off = strtab + int(nm[1:])
            nm = data[off:data.index(b"\0", off)].decode("latin-1")
        s.name = nm
        s.size, s.ptr, rptr = struct.unpack_from("<III", data, o + 16)
        nrel = struct.unpack_from("<H", data, o + 32)[0]
        s.flags = struct.unpack_from("<I", data, o + 36)[0]
        s.relocs = [struct.unpack_from("<IIH", data, rptr + 10 * r) for r in range(nrel)]
        s.sel = 0
        secs.append(s)
    syms, i = {}, 0
    while i < nsym:
        o = symptr + 18 * i
        y = Sym()
        y.i, y.name = i, text(data[o:o + 8])
        y.value, y.sec, _, y.cls, naux = struct.unpack_from("<IhHBB", data, o + 8)
        syms[i] = y
        if y.cls == STATIC and naux and 0 < y.sec <= nsec and y.value == 0:
            s = secs[y.sec - 1]
            if s.flags & COMDAT and s.name == y.name:
                s.sel = struct.unpack_from("<B", data, o + 18 + 14)[0]
        i += 1 + naux
    return secs, syms


def write_coff(path, sections, symbols):
    """sections [(name, flags, body, comdat_sel)], symbols [(name, secno, value, cls)];
    secno -1 = absolute."""
    strings = bytearray(4)

    def field(n):
        raw = n.encode("latin-1")
        if len(raw) <= 8:
            return raw.ljust(8, b"\0")
        o = len(strings)
        strings.extend(raw + b"\0")
        return struct.pack("<II", 0, o)
    symtab = bytearray()
    for k, (name, flags, body, sel) in enumerate(sections, 1):
        if sel:
            symtab += field(name) + struct.pack("<IhHBB", 0, k, 0, STATIC, 1)
            symtab += struct.pack("<IHHIHBBH", len(body), 0, 0, 0, 0, sel, 0, 0)
    for name, sec, val, cls in symbols:
        symtab += field(name) + struct.pack("<IhHBB", val, sec, 0x20 if sec > 0 else 0, cls, 0)
    hdr_end = 20 + 40 * len(sections)
    shdr, bodies = bytearray(), bytearray()
    for name, flags, body, sel in sections:
        ptr = hdr_end + len(bodies) if body else 0
        shdr += name.encode().ljust(8, b"\0") + struct.pack("<IIIIIIHHI", 0, 0, len(body), ptr, 0, 0, 0, 0, flags)
        bodies += body
    strings[0:4] = struct.pack("<I", len(strings))
    path.write_bytes(struct.pack("<HHIIIHH", 0x14C, len(sections), 0, hdr_end + len(bodies), len(symtab) // 18, 0, 0)
                     + shdr + bodies + symtab + strings)
    return path


def region(a):
    g = REGIONS[0][1]
    for s, n in REGIONS:
        if a >= s:
            g = n
    return g


def align_of(flags):
    n = (flags >> 20) & 0xF
    return 1 << (n - 1) if n else 16


def order_name(name):
    """link.exe 7.1 /ORDER drops one leading underscore of each entry."""
    return name[1:] if name.startswith("_") else name


def row_kind(row):
    notes = row.get("notes", "")
    for k in ("gen-funclet", "gen-import", "gen-alias"):
        if k in notes:
            return k
    return "real"


# ---------------------------------------------------------------- analyze
class Objects:
    """Parsed link objects, cached; lower-case basename -> path for map lookups."""
    def __init__(self, paths):
        self.paths = list(paths)
        self.by_base = {p.name.lower(): p for p in self.paths}
        self.cache, self.index = {}, {}

    def get(self, p):
        """(sections, symbols, raw bytes) of an object; None when it is missing."""
        p = Path(p)
        if p not in self.cache:
            try:
                data = p.read_bytes()
                self.cache[p] = parse_coff(data) + (data,)
            except FileNotFoundError:
                self.cache[p] = None
        return self.cache[p]

    def defined(self, o):
        """{name: Sym} defined in object o, and {section: sorted symbol offsets}."""
        key = id(o)
        if key not in self.index:
            secs, syms, _ = o
            names, vals = {}, collections.defaultdict(set)
            for y in syms.values():
                if 0 < y.sec <= len(secs):
                    names.setdefault(y.name, y)
                    vals[y.sec].add(y.value)
            self.index[key] = (names, {k: sorted(v) for k, v in vals.items()})
        return self.index[key]

    def lookup(self, objbase, name):
        """(object, Sym) for `name` defined by the object a map line names."""
        p = self.by_base.get(objbase.lower())
        o = self.get(p) if p else None
        y = self.defined(o)[0].get(name) if o else None
        return (o, y) if y else None


def analyze(rows, objs):
    """Units: one per object section holding >= 1 matched row."""
    units, keyed = [], {}
    stat = collections.Counter()
    for r in rows:
        rva, size = int(r["target_rva"], 16), int(r.get("target_size") or 0)
        p = build.row_object(r)
        sym = (re.search(r"(?:^|;)object-symbol=([^;]+)", r.get("notes", "")) or [None, r["name"]])[1]
        rec = {"name": r["name"], "sym": sym, "rva": rva, "size": size, "kind": row_kind(r), "source": r["source"]}
        o = objs.get(p)
        y = None
        if o is not None:
            secs, syms, _ = o
            y = next((s for s in syms.values() if s.name == sym and s.sec > 0 and s.cls in (2, 3, 6)), None)
        if y is None:
            stat["no object" if o is None else "symbol not in object"] += 1
            units.append({"obj": str(p), "sec": 0, "rows": [dict(rec, off=0)], "why": "no object" if o is None
                          else "symbol not in object", "starts": [rva], "head": None, "size": 0})
            continue
        s = secs[y.sec - 1]
        key = (str(p), y.sec)
        u = keyed.get(key)
        if u is None:
            u = keyed[key] = {"obj": str(p), "sec": y.sec, "secname": s.name, "size": s.size,
                              "comdat": bool(s.flags & COMDAT), "flags": s.flags, "rows": [], "starts": set()}
            units.append(u)
        u["rows"].append(dict(rec, off=y.value))
        u["starts"].add(rva - y.value)
    for u in keyed.values():
        secs, syms, _ = objs.get(u["obj"])
        heads = [y for y in syms.values() if y.sec == u["sec"] and y.cls in (2, 3) and y.value == 0
                 and y.name != u["secname"]]
        u["head"] = heads[0].name if heads else None
        u["head_cls"] = heads[0].cls if heads else None
        u["starts"] = sorted(u["starts"])
    for k, u in enumerate(units):
        u["id"] = k
    return units, stat


# ---------------------------------------------------------------- plan
def plan_order(units, quarantine, text0, textsz):
    """(placed units in retail order, Counter reasons, Counter bytes). Sets u['why']."""
    reasons, rbytes, cand = collections.Counter(), collections.Counter(), []

    def refuse(u, why):
        u["why"] = why
        reasons[why] += 1
        rbytes[why] += sum(r["size"] for r in u["rows"])
    for u in units:
        u.pop("placed", None)
        if u.get("sec", 0) == 0:
            refuse(u, u["why"])
            continue
        u["why"] = None
        if not u["secname"].startswith(".text"):
            refuse(u, "not code (%s)" % u["secname"])
        elif len(u["starts"]) == 1 and region(u["starts"][0]) != u["secname"]:
            refuse(u, "section group mismatch: compiled %s, retail %s" % (u["secname"], region(u["starts"][0])))
        elif not u["comdat"]:
            refuse(u, "not COMDAT")
        elif u["head"] is None:
            refuse(u, "no head symbol")
        elif u["head_cls"] != EXTERNAL:
            refuse(u, "static COMDAT")
        elif len(u["starts"]) != 1:
            refuse(u, "rows disagree on section start")
        elif not text0 <= u["starts"][0] < text0 + textsz:
            refuse(u, "start outside .text")
        elif u["starts"][0] % align_of(u["flags"]):
            refuse(u, "retail start violates section alignment")
        elif u["head"] in quarantine:
            refuse(u, "quarantined: linked footprint != retail extent")
        else:
            cand.append(u)
    cand.sort(key=lambda u: (u["starts"][0], u["obj"]))
    placed, seen, end = [], set(), 0
    for u in cand:
        s = u["starts"][0]
        if s < end:
            refuse(u, "overlaps previous unit")
        elif u["head"] in seen:
            refuse(u, "head already ordered (duplicate COMDAT)")
        else:
            seen.add(u["head"])
            u["placed"] = True
            placed.append(u)
            end = s + u["size"]
    return placed, reasons, rbytes


def filler_chunks(placed, cuts, text0, textsz):
    """[(start, end)] of every .text byte no placed unit covers, split at `cuts`."""
    cuts = sorted(set(cuts) | {s for s, _ in REGIONS})
    chunks, cur = [], text0
    for s, e in [(u["starts"][0], u["starts"][0] + u["size"]) for u in placed] + [(text0 + textsz,) * 2]:
        if s > cur:
            i = bisect.bisect_right(cuts, cur)
            pts = [cur] + cuts[i:bisect.bisect_left(cuts, s)] + [s]
            chunks += [(a, b) for a, b in zip(pts, pts[1:]) if b > a]
        cur = max(cur, e)
    return chunks


def fill_name(a):
    return "_fill_%08X" % a


def drift_culprits(items, linked):
    """Order items [(retail start, name, kind)] whose linked distance to the next
    item differs from retail's: the unit that grew or shrank is quarantined (a
    filler 'growing' means the next unit's alignment padded it)."""
    items = sorted(items)
    bad, missing = set(), 0
    for (r0, n0, k0), (r1, n1, k1) in zip(items, items[1:]):
        if n0 not in linked or n1 not in linked:
            missing += 1
            continue
        if linked[n1] - linked[n0] != r1 - r0:
            bad.add(n0 if k0 == "unit" else n1 if k1 == "unit" else n0)
    return sorted(b for b in bad if not b.startswith("_fill_")), missing


# ---------------------------------------------------------------- link inputs
def undefined_imports(objs):
    names = set()
    for p in objs.paths:
        o = objs.get(p)
        if o:
            names |= {y.name for y in o[1].values() if y.sec == 0 and y.cls == EXTERNAL and y.name.startswith("__imp_")}
    return names


def import_def_entries(imp_names, retail_imports):
    """{dll: [def entry]} for every referenced __imp_ name retail imports; and the
    names retail does not import (left to stubs)."""
    by_dll, missing = collections.defaultdict(set), []
    for n in sorted(imp_names):
        rest = n[len("__imp_"):]
        if rest.startswith("?"):
            base, entry = rest, rest
        elif rest.startswith("_"):
            entry = rest[1:]
            base = re.sub(r"@\d+$", "", entry)
        else:
            missing.append(n)
            continue
        dlls = retail_imports.get(base)
        if not dlls:
            missing.append(n)
            continue
        by_dll[sorted(dlls)[0]].add(entry)
    return {d: sorted(e) for d, e in by_dll.items()}, missing


def import_name(name):
    """An imported function's name without the stdcall @N lib.exe /DEF keeps on it
    (its import objects use IMPORT_NAME_NOPREFIX; retail's are undecorated)."""
    return re.sub(r"@\d+$", "", name)


def make_import_libs(entries, outdir):
    root = build.vc71_root()
    libs = []
    for dll, names in sorted(entries.items()):
        stem = re.sub(r"\W", "_", dll.rsplit(".", 1)[0].lower())
        d = outdir / f"imp_{stem}.def"
        d.write_text(f"LIBRARY {dll}\nEXPORTS\n" + "".join(f"  {n}\n" for n in names), encoding="latin-1")
        lib = outdir / f"imp_{stem}.lib"
        res = subprocess.run([str(root / "Vc7/bin/lib.exe"), "/NOLOGO", "/MACHINE:X86", f"/DEF:{d}", f"/OUT:{lib}"],
                             capture_output=True, text=True, errors="replace", env=build.compiler_environment(root))
        if res.returncode or not lib.exists():
            raise SystemExit(f"link_cycle: lib.exe failed for {dll}:\n{res.stdout}{res.stderr}")
        libs.append(lib)
    return libs


def zz_objects(objs, placed, ordered_names, zzdir):
    """Private copies with every unplaced code section renamed .text$zz, so unplaced
    code lands after retail's last group instead of inside it."""
    zzdir.mkdir(parents=True, exist_ok=True)
    placed_secs = {(u["obj"], u["sec"]) for u in placed}
    out, renamed = [], 0
    for p in objs.paths:
        secs, syms, raw = objs.get(p)
        d = bytearray(raw)
        opt = struct.unpack_from("<H", d, 16)[0]
        heads = {}
        for y in sorted(syms.values(), key=lambda y: y.i):
            if y.sec > 0 and y.cls in (2, 3) and y.name != secs[y.sec - 1].name and y.sec not in heads:
                heads[y.sec] = y.name if y.cls == EXTERNAL else None
        hit = False
        for s in secs:
            if s.name not in (".text", ".text$x", ".text$yc", ".text$yd") or (str(p), s.idx) in placed_secs:
                continue
            if s.flags & COMDAT and heads.get(s.idx) in ordered_names:
                continue
            struct.pack_into("8s", d, 20 + opt + 40 * (s.idx - 1), b".text$zz")
            hit = True
            renamed += 1
        if hit:
            q = zzdir / p.name
            if not q.exists() or q.read_bytes() != d:
                q.write_bytes(bytes(d))
            out.append(q)
        else:
            out.append(p)
    return out, renamed


def link(tag, inputs, order, entry, base, outdir):
    rsp = outdir / f"{tag}.rsp"
    rsp.write_text("\n".join(f'"{p}"' for p in inputs) + "\n", encoding="latin-1")
    root = build.vc71_root()
    cmd = [str(root / "Vc7/bin/link.exe"), "/NOLOGO", "/FORCE", "/NODEFAULTLIB", "/INCREMENTAL:NO", "/MACHINE:X86",
           "/SUBSYSTEM:WINDOWS", "/FIXED", f"/BASE:0x{base:X}", "/OPT:NOREF", "/OPT:NOICF",
           "/ENTRY:" + order_name(entry), f"/ORDER:@{order}", f"/MAP:{outdir / (tag + '.map')}",
           f"/OUT:{outdir / (tag + '.exe')}", f"@{rsp}"]
    if sys.platform != "win32":
        cmd.insert(0, "wine")
    for p in (outdir / (tag + ".map"), outdir / (tag + ".exe")):
        p.unlink(missing_ok=True)
    t = time.time()
    res = subprocess.run(cmd, capture_output=True, text=True, errors="replace",
                         env=build.compiler_environment(root), cwd=outdir)
    log = res.stdout + res.stderr
    (outdir / (tag + ".log")).write_text(log, encoding="utf-8")
    print(f"link_cycle: link {tag} base 0x{base:X} exit {res.returncode} {time.time() - t:.0f}s", flush=True)
    return log, res.returncode, time.time() - t


UNRES = re.compile(r'unresolved external symbol (?:"[^"]*" \((\S+)\)|(\S+))')
DUP = re.compile(r'warning LNK4006: (?:"[^"]*" \((\S+)\)|(\S+)) already defined')


def diagnostics(log):
    return {"codes": dict(collections.Counter(re.findall(r"(?:error|warning) (LNK\d+)", log))),
            "unresolved": sorted({a or b for a, b in UNRES.findall(log)}),
            "duplicates": sorted({a or b for a, b in DUP.findall(log)})}


# ---------------------------------------------------------------- map
MAPLINE = re.compile(r"^\s*([0-9a-f]{4}):([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8})\s+(?:f\s+)?(?:i\s+)?(\S+)\s*$")


def read_map(text, base):
    """(publics {name: rva}, statics {(name, objbase): rva}, sorted [(rva, name, objbase)],
    {public: objbase})."""
    pub, stat, allsyms, static, pubobj = {}, {}, [], False, {}
    for line in text.splitlines():
        if "Static symbols" in line:
            static = True
        m = MAPLINE.match(line)
        if not m or m.group(1) == "0000":
            continue
        va = int(m.group(4), 16) - base
        ob = m.group(5).split(":")[-1].lower()
        if static:
            stat.setdefault((m.group(3), ob), va)
        else:
            pub.setdefault(m.group(3), va)
            pubobj.setdefault(m.group(3), ob)
        allsyms.append((va, m.group(3), ob))
    allsyms.sort()
    return pub, stat, allsyms, pubobj


# ---------------------------------------------------------------- measure helpers
def u32(m, a):
    return struct.unpack_from("<I", m, a)[0]


def nonreloc_diffs(got, want, masked):
    return sum(1 for k in range(len(want)) if k not in masked and (k >= len(got) or got[k] != want[k]))


def pin_matches(pin, rva, base=BASE):
    """symbols.csv pins data both as RVAs and as VAs (138 VA, 30 RVA on
    2026-10-05). A retail datum's RVA (>= .rdata) and any datum's VA lie in
    disjoint bands, so either spelling of the same address is accepted."""
    return pin == rva or pin == rva + base


def unique_bytes(spans):
    """Bytes covered by the union of [start, end) spans."""
    total, cur = 0, -1
    for s, e in sorted(spans):
        if e > cur:
            total += e - max(s, cur)
            cur = e
    return total


def greatest_closure(ok, edges, bad_targets=("fill", "stub")):
    """Nodes that are ok and reach only ok nodes (cycles optimistic). An edge to a
    node kind in `bad_targets` (fillers, stubs) closes nothing: it is not a leaf."""
    closed = {n for n in ok if ok[n]}
    for n in list(closed):
        if any(t[0] in bad_targets for t in edges.get(n, ())):
            closed.discard(n)
    rev = collections.defaultdict(set)
    for n, ts in edges.items():
        for t in ts:
            rev[t].add(n)
    work = [n for n in ok if n not in closed]
    while work:
        t = work.pop()
        for n in rev.get(t, ()):
            if n in closed:
                closed.discard(n)
                work.append(n)
    return closed


try:
    import capstone
    _CS = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    _CSD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    _CSD.detail = True
except ImportError:  # pragma: no cover
    _CS = _CSD = None


def _norm(ins):
    return ins.mnemonic + " " + re.sub(r"0x[0-9a-f]{6,8}", "ADDR", ins.op_str)


def funclet_equal(I, la, R, ra, lbase, rbase, translate=None):
    """Funclet bodies equal up to the first ret/jmp, address operands masked; a
    direct call/jmp target must translate to retail's when it is mapped."""
    a = list(_CS.disasm(bytes(I[la:la + 64]), la + lbase))
    b = list(_CS.disasm(bytes(R[ra:ra + 64]), ra + rbase))
    for x, y in zip(a, b):
        if _norm(x) != _norm(y):
            return False
        if translate and x.mnemonic in ("call", "jmp") and x.op_str.startswith("0x") and y.op_str.startswith("0x"):
            t = translate(int(x.op_str, 16) - lbase)
            if t is not None and t != int(y.op_str, 16) - rbase:
                return False
        if x.mnemonic in ("jmp", "ret"):
            return True
    return len(a) == len(b)


def funcinfo(m, a, base):
    magic, maxst, pu, ntry, ptry, _ = struct.unpack_from("<IiIIII", m, a)
    un = [struct.unpack_from("<iI", m, pu - base + 8 * i) for i in range(max(0, min(maxst, 400)))] if pu else []
    tr = []
    for i in range(min(ntry, 50)):
        lo, hi, ch, nc, ph = struct.unpack_from("<iiiiI", m, ptry - base + 20 * i)
        tr.append((lo, hi, ch, nc, [struct.unpack_from("<IIiI", m, ph - base + 16 * j) for j in range(min(nc, 20))]))
    return magic, maxst, ntry, un, tr


def eh_verdict(I, lt, R, rt, lbase, rbase, translate=None):
    """None when the linked __ehhandler$ thunk at lt and retail's at rt (mov eax,
    FuncInfo; jmp handler) carry equal EH data; else the first difference."""
    if I[lt] != 0xB8 or R[rt] != 0xB8 or I[lt + 5] != 0xE9 or R[rt + 5] != 0xE9:
        return "thunk shape differs"
    try:
        a = funcinfo(I, u32(I, lt + 1) - lbase, lbase)
        b = funcinfo(R, u32(R, rt + 1) - rbase, rbase)
    except (struct.error, IndexError):
        return "FuncInfo unparsable"
    if a[:3] != b[:3]:
        return "FuncInfo header differs"
    if [x[0] for x in a[3]] != [x[0] for x in b[3]]:
        return "unwind map differs"
    if any((x[1] == 0) != (y[1] == 0) for x, y in zip(a[3], b[3])):
        return "unwind action presence differs"
    if not all(funclet_equal(I, x[1] - lbase, R, y[1] - rbase, lbase, rbase, translate)
               for x, y in zip(a[3], b[3]) if x[1] and y[1]):
        return "unwind funclet differs"
    if [t[:4] for t in a[4]] != [t[:4] for t in b[4]]:
        return "try map differs"
    for t, v in zip(a[4], b[4]):
        if [(h[0], h[2]) for h in t[4]] != [(h[0], h[2]) for h in v[4]]:
            return "catch map differs"
        if not all(funclet_equal(I, h[3] - lbase, R, g[3] - rbase, lbase, rbase, translate)
                   for h, g in zip(t[4], v[4])):
            return "catch funclet differs"
    return None


def hardcoded_operands(code, va, masked, lo, hi):
    """Offsets of 32-bit displacement/immediate operands in `code` (at `va`)
    holding an absolute address in [lo, hi) that no relocation covers: they
    cannot follow a rebase. Relative branch targets are not operands here."""
    if _CSD is None:
        return []
    out = []
    for ins in _CSD.disasm(bytes(code), va):
        at = ins.address - va
        for off, size in ((ins.disp_offset, ins.disp_size), (ins.imm_offset, ins.imm_size)):
            if size != 4 or not off or ins.mnemonic == "call" or ins.mnemonic.startswith("j"):
                continue
            k = at + off
            if lo <= u32(code, k) < hi and not any(j in masked for j in range(k, k + 4)):
                out.append(k)
    return out


# ---------------------------------------------------------------- measure
class Measure:
    def __init__(self, units, chunks, mapped, I, R, isecs, rimports, limports, pins, objs, ledger_starts,
                 lbase=BASE, rbase=BASE):
        self.units, self.I, self.R, self.isecs = units, I, R, isecs
        self.pins, self.objs, self.ledger_starts = pins, objs, ledger_starts
        self.lbase, self.rbase = lbase, rbase
        self.rimports, self.limports = rimports, limports
        self.pub, self.stat, self.allsyms, self.pubobj = mapped
        self.avas = [s[0] for s in self.allsyms]
        self.ltext = isecs.get(".text", (0, 0))
        items = []
        for u in units:
            if u.get("head") is None:
                continue
            ob = Path(u["obj"]).name.lower()
            la = self.pub.get(u["head"]) if u["head_cls"] == EXTERNAL else self.stat.get((u["head"], ob))
            u["linked"] = la
            if la is not None and len(u["starts"]) == 1:
                items.append((la, la + u["size"], u["starts"][0], ("unit", u["id"])))
        for a, b in chunks:
            la = self.pub.get(fill_name(a))
            if la is not None:
                items.append((la, la + b - a, a, ("fill", a)))
        items.sort()
        self.items, self.istarts = items, [t[0] for t in items]
        self.fwd, self.back = collections.defaultdict(set), collections.defaultdict(set)
        self.datum_memo, self.twins, self.eh = {}, {}, collections.Counter()

    def T(self, a):
        i = bisect.bisect_right(self.istarts, a) - 1
        if i >= 0 and self.items[i][0] <= a < self.items[i][1]:
            return self.items[i][2] + a - self.items[i][0], self.items[i][3]
        return None, None

    def translate(self, a):
        return self.T(a)[0]

    def sym_at(self, a):
        i = bisect.bisect_right(self.avas, a) - 1
        if i < 0:
            return None
        va, name, ob = self.allsyms[i]
        j = i + 1
        while j < len(self.allsyms) and self.allsyms[j][0] == va:
            j += 1
        return va, name, ob, self.allsyms[j][0] if j < len(self.allsyms) else va + 1

    def lsec(self, a):
        if hasattr(self.isecs, "name_at"):
            return self.isecs.name_at(a)
        return next((n for n, (s, z) in self.isecs.items() if s <= a < s + max(z, 1)), "outside")

    def relocs(self, L, rva, size, o, secno, off, owner):
        """Check every relocation of [off, off+size) of section `secno` of object o
        linked at L against retail at rva. Returns (failures, edges, masked
        offsets, data references [(lt, rt, target name, Sym, object, addend)])."""
        I, R = self.I, self.R
        secs, syms, raw = o
        sec = secs[secno - 1]
        got, want = I[L:L + size], R[rva:rva + size]
        fails, edges, masked, data = [], set(), set(), []
        for va, si, ty in sec.relocs:
            if not off <= va < off + size:
                continue
            fo = va - off
            masked.update(range(fo, min(fo + 4, size)))
            y = syms.get(si)
            tn = y.name if y else "?"
            if ty not in (DIR32, REL32):
                fails.append(f"rtype:{ty}")
                continue
            if fo + 4 > size:
                fails.append(f"straddle:{tn}")
                continue
            lv, rv = u32(got, fo), u32(want, fo)
            if tn in ABSOLUTE:
                if ty != DIR32 or lv != rv:
                    fails.append(f"abs:{tn}")
                continue
            if ty == REL32:
                lt, rt = (L + fo + 4 + lv) & 0xFFFFFFFF, (rva + fo + 4 + rv) & 0xFFFFFFFF
            else:
                lt, rt = (lv - self.lbase) & 0xFFFFFFFF, (rv - self.rbase) & 0xFFFFFFFF
            if self.ltext[0] <= lt < self.ltext[0] + self.ltext[1]:
                f, e = self.code_ref(lt, rt, tn, owner)
                if f:
                    fails.append(f)
                elif e:
                    edges.add(e)
            else:
                addend = u32(raw, sec.ptr + va) if sec.ptr else 0
                data.append((lt, rt, tn, y, o, addend))
        nd = nonreloc_diffs(got, want, masked)
        if nd:
            fails.append(f"bytes:{nd}")
        return fails, edges, masked, data

    def code_ref(self, lt, rt, tn, owner):
        tr, item = self.T(lt)
        if tr is not None and tr == rt:
            return None, item
        s = self.sym_at(lt)
        if s and s[1].startswith("__ehhandler$"):
            if s[1][len("__ehhandler$"):] != owner:
                self.eh["foreign thunk"] += 1
                return f"eh-foreign:{tn}", None
            v = eh_verdict(self.I, s[0], self.R, rt - (lt - s[0]), self.lbase, self.rbase, self.translate)
            self.eh[v or "verified"] += 1
            return (f"eh:{v}", None) if v else (None, ("eh", lt))
        if s and s[0] == lt and rt in self.ledger_starts:
            self.twins.setdefault((lt, rt), None)
            return None, ("twin", lt, rt)          # judged in judge_twins; a rejected twin fails the row
        if tr is None:
            return f"code-unmapped:{tn}", None
        return f"code-wrong:{tn}", None

    def datum(self, lt, tn, y, o, addend):
        """The datum a data reference reaches, from the relocation's own target:
        (linked start of the datum, its size, offset of lt in it, defining object,
        section, section offset of the datum, linked address of the named symbol)."""
        if y is not None and y.sec > 0:              # defined in the referencing object
            sec, P, S = o[0][y.sec - 1], y.value + addend, lt - addend
        else:                                        # defined elsewhere: the map names its object
            S, ob = self.pub.get(tn), self.pubobj.get(tn)
            found = self.objs.lookup(ob, tn) if ob else None
            if S is not None and not found and self.communal(tn):
                # an uninitialized global: a COMMON record sizes it (the linker takes the
                # largest), and the map names an object that does not define it
                return S, self.communal(tn), lt - S, o, None, 0, S
            if S is None or not found:
                return None
            o, ys = found
            sec, P = o[0][ys.sec - 1], ys.value + (lt - S)
        vals = self.objs.defined(o)[1].get(sec.idx, [])
        q = max(0, min(P, sec.size - 1))
        i = bisect.bisect_right(vals, q) - 1
        v0 = vals[i] if i >= 0 else 0
        v1 = vals[i + 1] if i + 1 < len(vals) else sec.size
        return lt - (P - v0), v1 - v0, P - v0, o, sec, v0, S

    def communal(self, name):
        """Size of a COMMON global across every parsed link object (0: none)."""
        if getattr(self, "commons", None) is None:
            self.commons = {}
            for o in list(self.objs.cache.values()):
                for z in (o[1].values() if o else ()):
                    if z.sec == 0 and z.cls == EXTERNAL and z.value > 0:
                        self.commons[z.name] = max(self.commons.get(z.name, 0), z.value)
        return self.commons.get(name, 0)

    def data_ref(self, lt, rt, tn, y, o, addend):
        """(failures, code edges, pinned?) of one data reference beyond the 1:1 rule:
        the datum's content at retail's address, and its pin when it has one."""
        sec = self.lsec(lt)
        if sec == ".stubd":
            return [f"data-stub:{tn}"], set(), False
        if sec == "outside":
            return [f"data-outside-image:{tn}"], set(), False
        if lt in self.limports:
            want = self.rimports.get(rt)
            same = want and import_name(want[1]) == import_name(self.limports[lt][1])
            return ([] if same else [f"import-mismatch:{tn}"]), set(), True
        d = self.datum(lt, tn, y, o, addend)
        if d is None:
            return [f"data-unmapped:{tn}"], set(), False
        start, size, k, do, sec, v0, S = d
        fails, pinned = [], tn in self.pins
        if pinned and not pin_matches(self.pins[tn], rt - (lt - S), self.rbase):
            fails.append(f"data-pin:{tn}")
        key = (start, rt - k, size)
        if key not in self.datum_memo:
            self.datum_memo[key] = self.datum_content(start, size, rt - k, sec, v0, tn)
        cf, edges = self.datum_memo[key]
        return fails + cf, edges, pinned

    def datum_content(self, start, size, rstart, sec, value, name):
        if size <= 0 or rstart < 0 or rstart + size > len(self.R) or start < 0 or start + size > len(self.I):
            return [f"data-extent:{name}"], set()
        got, want = self.I[start:start + size], self.R[rstart:rstart + size]
        masked, edges, fails = set(), set(), []
        for va, si, ty in (sec.relocs if sec is not None else ()):
            fo = va - value
            if not 0 <= fo < size:
                continue
            masked.update(range(fo, min(fo + 4, size)))
            if ty == DIR32 and fo + 4 <= size:
                lt = (u32(got, fo) - self.lbase) & 0xFFFFFFFF
                rt = (u32(want, fo) - self.rbase) & 0xFFFFFFFF
                if self.ltext[0] <= lt < self.ltext[0] + self.ltext[1]:
                    tr, item = self.T(lt)
                    if tr != rt:
                        fails.append(f"data-codeptr:{name}")
                    else:
                        edges.add(item)
        if nonreloc_diffs(got, want, masked):
            fails.append(f"data-content:{name}")
        return fails, edges

    def run(self):
        """Per ledger row: dict with failures, edges, placement."""
        out = []
        self.pending = []
        for u in self.units:
            la = u.get("linked")
            o = self.objs.get(u["obj"]) if la is not None else None
            for r in u["rows"]:
                rec = {"row": r, "unit": u, "linked": None, "placed": 0, "fails": [], "edges": set(),
                       "unpinned": 0, "masked": set(), "measured": False}
                out.append(rec)
                if la is None or not o:
                    continue
                L = la + r["off"]
                rec["linked"], rec["placed"], rec["measured"] = L, int(L == r["rva"]), True
                f, e, m, data = self.relocs(L, r["rva"], r["size"], o, u["sec"], r["off"], r["sym"])
                rec["fails"], rec["edges"], rec["masked"] = f, e, m
                for ref in data:
                    self.fwd[ref[0]].add(ref[1])
                    self.back[ref[1]].add(ref[0])
                    self.pending.append((rec, ref))
        self.judge_twins()
        for rec, ref in self.pending:
            lt, rt, tn = ref[:3]
            if len(self.fwd[lt]) != 1:
                rec["fails"].append(f"data-fwd:{tn}")
            if len(self.back[rt]) != 1:
                rec["fails"].append(f"data-back:{tn}")
            f, e, pinned = self.data_ref(*ref)
            rec["fails"] += f
            rec["edges"] |= e
            rec["unpinned"] += 0 if pinned or lt in self.limports else 1
        for rec in out:
            for e in list(rec["edges"]):
                if e[0] == "twin" and not self.twins.get((e[1], e[2]), (False,))[0]:
                    rec["fails"].append(f"twin-rejected:{self.twins.get((e[1], e[2]), (0, 'unjudged'))[1]}")
        return out

    def judge_twins(self):
        """Certify each candidate ICF twin: a linked function start reached where
        retail calls a ledger row start. Same extent, same non-relocation bytes,
        every relocation resolving to retail's target (twins of twins included)."""
        work = list(self.twins)
        body = {}
        while work:
            lt, rt = work.pop()
            if (lt, rt) in body:
                continue
            s = self.sym_at(lt)
            found = self.objs.lookup(s[2], s[1]) if s else None
            size = self.ledger_starts[rt]
            if not found or found[1].value != 0 or found[0][0][found[1].sec - 1].size != size:
                body[(lt, rt)] = (["extent differs"], set(), [])
                continue
            o, ys = found
            f, e, _, data = self.relocs(lt, rt, size, o, ys.sec, 0, s[1])
            body[(lt, rt)] = (f, e, data)
            for x in e:
                if x[0] == "twin" and (x[1], x[2]) not in body:
                    self.twins.setdefault((x[1], x[2]), None)
                    work.append((x[1], x[2]))
        ok = {}
        for key, (f, e, data) in body.items():
            fails = list(f)
            for ref in data:
                fails += self.data_ref(*ref)[0]
            ok[key] = fails
        good = {k for k, v in ok.items() if not v}
        changed = True
        while changed:
            changed = False
            for k in list(good):
                if any(x[0] == "twin" and (x[1], x[2]) not in good for x in body[k][1]):
                    good.discard(k)
                    ok[k] = ["calls a rejected twin"]
                    changed = True
        self.twin_edges = {k: body[k][1] for k in body}
        for k in body:
            self.twins[k] = (k in good, (ok[k] or ["certified"])[0].split(":")[0])


# ---------------------------------------------------------------- cycle
def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for b in iter(lambda: f.read(1 << 20), b""):
            h.update(b)
    return h.hexdigest()


def git(*args):
    return subprocess.run(["git", *args], capture_output=True, text=True, cwd=ROOT).stdout.strip()


def tool_digest():
    h = hashlib.sha256()
    for n in TOOL_FILES:
        h.update(n.encode() + b"\0" + (ROOT / "tools" / n).read_bytes())
    return h.hexdigest()


def objects_digest(paths):
    h = hashlib.sha256()
    for p in sorted(paths, key=lambda p: p.as_posix()):
        h.update(p.relative_to(ROOT).as_posix().encode() + b"\0" + hashlib.sha256(p.read_bytes()).digest())
    return h.hexdigest()


def load_pins():
    pins, byaddr = {}, collections.defaultdict(list)
    with (ROOT / "reverse/symbols.csv").open(newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            if r["address"].startswith("0x") and r["name"] not in pins:
                a = int(r["address"], 16)
                pins[r["name"]] = a
                byaddr[a].append(r["name"])
    return pins, byaddr


class SectionList(dict):
    """{name: (rva, size)} of an image's sections (the first of a repeated name),
    keeping every section for address lookups: link.exe can emit two .data."""
    def __init__(self, entries):
        super().__init__()
        self.all = list(entries)
        for n, a, z in self.all:
            self.setdefault(n, (a, z))

    def name_at(self, a):
        return next((n for n, s, z in self.all if s <= a < s + max(z, 1)), "outside")


def pe_view(path):
    import pefile
    pe = pefile.PE(str(path), fast_load=True)
    secs = SectionList((s.Name.rstrip(b"\0").decode("latin-1"), s.VirtualAddress, s.Misc_VirtualSize)
                       for s in pe.sections)
    pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]])
    imps = {}
    for dll in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
        for e in dll.imports:
            imps[e.address - pe.OPTIONAL_HEADER.ImageBase] = (dll.dll.decode("latin-1").lower(),
                                                             (e.name or b"").decode("latin-1"))
    return pe, pe.get_memory_mapped_image(), secs, imps


def cycle(args):
    t_all = time.time()
    times = {}
    out = Path(args.out)
    out.mkdir(parents=True, exist_ok=True)
    census.refuse_unsupported_ledgers()
    rows = census.ledger()
    if args.build:
        t = time.time()
        os.environ.setdefault("BUILD_POOL", str(max(1, (os.cpu_count() or 2) - 2)))
        build.ensure_case_shims()
        build.compile_rows(rows, census.compile_sources(rows))
        times["compile"] = round(time.time() - t)
    t = time.time()
    present, missing = census.objects(rows)
    objs = Objects(present)
    units, astat = analyze(rows, objs)
    pe_r, R, rsecs, rimp = pe_view(build.EXE)
    text0, textsz = rsecs[".text"]
    pins, byaddr = load_pins()
    with (ROOT / "reverse/ghidra_functions.csv").open(newline="") as f:
        ghidra = [int(r["rva"], 16) for r in csv.DictReader(f)]
    cuts = [a for a in ghidra + list(byaddr) if text0 <= a < text0 + textsz]
    retail_imports = census.retail_imports()
    entries, imp_missing = import_def_entries(undefined_imports(objs), retail_imports)
    libs = make_import_libs(entries, out)
    absobj = write_coff(out / "absolute.obj", [], [(n, -1, v, EXTERNAL) for n, v in ABSOLUTE.items()])
    times["analyze"] = round(time.time() - t)
    print(f"link_cycle: {len(rows):,} rows, {len(units):,} units, {len(present):,} objects "
          f"({len(missing):,} missing), import entries {sum(map(len, entries.values())):,}", flush=True)

    quarantine, stubs, iters, history = set(), None, 0, []
    qfile = out / "quarantine.json"
    if args.reuse_quarantine and qfile.exists():
        quarantine = set(json.loads(qfile.read_text()))
    sfile = out / "stubs.json"
    if args.reuse_stubs and sfile.exists():
        stubs = json.loads(sfile.read_text())
    raw = R[text0:text0 + textsz]
    t_link = time.time()
    while True:
        iters += 1
        placed, reasons, rbytes = plan_order(units, quarantine, text0, textsz)
        chunks = filler_chunks(placed, cuts, text0, textsz)
        fill_objs = []
        for k in range(0, len(chunks), 15000):
            part = chunks[k:k + 15000]
            fill_objs.append(write_coff(out / ("fill%02d.obj" % (k // 15000)),
                                        [(region(a), 0x60101020, bytes(raw[a - text0:b - text0]), 2) for a, b in part],
                                        [(fill_name(a), j, 0, EXTERNAL) for j, (a, b) in enumerate(part, 1)]))
        items = sorted([(u["starts"][0], u["head"], "unit") for u in placed] + [(a, fill_name(a), "fill") for a, b in chunks])
        order = out / "order.txt"
        order.write_text("\n".join(order_name(n) for _, n, _ in items) + "\n", encoding="latin-1")
        at = {a: n for a, n, _ in items}
        aliases = {n: at[a] for n, a in pins.items() if a in at and at[a] != n and not n.startswith("??_E")}
        census.alias_object(aliases, out / "alias.obj")
        linkobjs, renamed = zz_objects(objs, placed, {n for _, n, _ in items}, out / "zzobj")
        base_inputs = fill_objs + linkobjs + libs + [absobj, out / "alias.obj"]
        entry = placed[0]["head"]
        if stubs is None:
            log1, _, secs1 = link("pass1", base_inputs, order, entry, BASE, out)
            d1 = diagnostics(log1)
            exported = set()
            for p in linkobjs:
                b = p.read_bytes()
                if b"EXPORT:" in b:
                    exported |= {m.decode("latin-1") for m in re.findall(rb"/EXPORT:(\S+)", b)}
            stubs = sorted(set(d1["unresolved"]) - exported - set(ABSOLUTE))
            sfile.write_text(json.dumps(stubs))
            history.append({"link": "pass1", "secs": round(secs1), "unresolved": len(d1["unresolved"]),
                            "codes": d1["codes"]})
        write_coff(out / "stubs.obj", [(".stubd", 0xC0300040, bytes(4 * max(1, len(stubs))), 0)],
                   [(n, 1, 4 * i, EXTERNAL) for i, n in enumerate(stubs)])
        inputs = base_inputs + [out / "stubs.obj"]
        shift = None
        if args.shift_base:   # the shifted link runs alongside; it is used when this iteration converges
            pool = concurrent.futures.ThreadPoolExecutor(1)
            shift = pool.submit(link, "shift", inputs, order, entry, args.shift_base, out)
        log, code, secs = link("base", inputs, order, entry, BASE, out)
        d = diagnostics(log)
        mapped = read_map((out / "base.map").read_text(encoding="latin-1"), BASE)
        culprits, nmiss = drift_culprits(items, mapped[0])
        history.append({"link": f"iter{iters}", "secs": round(secs), "exit": code, "placed_units": len(placed),
                        "drift": len(culprits), "missing_names": nmiss, "new_unresolved": len(d["unresolved"])})
        print(f"link_cycle: iteration {iters}: {len(placed):,} units ordered, {len(culprits):,} drift culprits, "
              f"{len(d['unresolved'])} new unresolved", flush=True)
        if d["unresolved"]:
            stubs = sorted(set(stubs) | set(d["unresolved"]))
            sfile.write_text(json.dumps(stubs))
        if (not culprits and not d["unresolved"]) or iters >= args.max_iter:
            break
        if shift:
            shift.cancel()
            shift.result()
        quarantine |= set(culprits)
        qfile.write_text(json.dumps(sorted(quarantine)))
    shift_res = shift.result() if shift else None
    times["link"] = round(time.time() - t_link)

    t = time.time()
    res = measure(out, units, chunks, objs, R, rsecs, rimp, pins, shift_res is not None, args.shift_base)
    times["measure"] = round(time.time() - t)
    times["total"] = round(time.time() - t_all)
    root = build.vc71_root()
    receipt = {
        "tool": "link_cycle", "rules": "link-cycle-1",
        "commit": git("rev-parse", "HEAD"), "dirty": bool(git("status", "--porcelain", "--untracked-files=no")),
        "date_utc": time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime()),
        "retail_sha256": sha256(build.EXE),
        "toolchain_sha256": {n: sha256(root / "Vc7/bin" / n) for n in ("link.exe", "cl.exe", "lib.exe")},
        "tool_digest": tool_digest(), "objects_digest": objects_digest(present),
        "objects": len(present), "objects_missing": len(missing),
        "inputs": {"functions_csv": sha256(ROOT / "reverse/functions.csv"),
                   "symbols_csv": sha256(ROOT / "reverse/symbols.csv")},
        "links": history, "iterations": iters, "quarantined_units": len(quarantine),
        "not_ordered": dict(reasons), "not_ordered_bytes": dict(rbytes), "analyze": dict(astat),
        "scaffold": {"filler_chunks": len(chunks), "filler_bytes": sum(b - a for a, b in chunks),
                     "stubs": len(stubs), "aliases": len(aliases), "zz_sections": renamed,
                     "import_entries": sum(map(len, entries.values())), "imports_not_in_retail": len(imp_missing)},
        "final_link": {"exit": code, "codes": d["codes"], "force_duplicates": len(diagnostics(log)["duplicates"]),
                       "force_duplicate_diagnostics": d["codes"].get("LNK4006", 0)},
        "unresolved_pass1": len(stubs),
        "series": res, "seconds": times,
    }
    (out / "receipt.json").write_text(json.dumps(receipt, indent=1), encoding="utf-8")
    print(json.dumps(res, indent=1))
    print(f"link_cycle: receipt {out / 'receipt.json'}; wall {times}")
    return receipt


def measure(out, units, chunks, objs, R, rsecs, rimp, pins, have_shift, shift_base):
    pe, I, isecs, limp = pe_view(out / "base.exe")
    mapped = read_map((out / "base.map").read_text(encoding="latin-1"), BASE)
    ledger_starts = {}
    for u in units:
        for r in u["rows"]:
            ledger_starts[r["rva"]] = max(ledger_starts.get(r["rva"], 0), r["size"])
    # the linked image's code pointers live in the map's object basenames: index zz copies too
    zz = out / "zzobj"
    if zz.exists():
        for p in zz.iterdir():
            objs.by_base[p.name.lower()] = p
    m = Measure(units, chunks, mapped, I, R, isecs, rimp, limp, pins, objs, ledger_starts)
    recs = m.run()
    textsz = rsecs[".text"][1]
    # closure: node per unit / twin; edges to fillers or stubs are not leaves
    ok, edges = {}, collections.defaultdict(set)
    for rec in recs:
        n = ("unit", rec["unit"]["id"])
        ok[n] = ok.get(n, True) and rec["measured"] and not rec["fails"]
        for e in rec["edges"]:
            edges[n].add(e if e[0] != "eh" else ("leaf",))
    for k, (good, _) in m.twins.items():
        n = ("twin", k[0], k[1])
        ok[n] = good
        edges[n] |= {e if e[0] != "eh" else ("leaf",) for e in m.twin_edges.get(k, ())}
    for n in ok:
        edges[n] = {e for e in edges[n] if e[0] != "leaf"}
    closed = greatest_closure(ok, edges)
    # the pilot's rule, for comparison: code edges only, fillers are leaves
    pilot_edges = {n: {e for e in es if e[0] == "unit"} for n, es in edges.items()}
    closed_pilot = greatest_closure(ok, pilot_edges, bad_targets=())
    hard = shifted_rows(out, recs, I, isecs, objs, have_shift, shift_base)
    fold = out / "fold_list.csv"
    with fold.open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(["linked_rva", "retail_rva", "symbol", "object", "verdict"])
        for (lt, rt), (good, why) in sorted(m.twins.items()):
            s = m.sym_at(lt)
            w.writerow(["0x%08X" % lt, "0x%08X" % rt, s[1], s[2], why])
    cols = ["name", "kind", "source", "retail_rva", "size", "linked_rva", "placed", "placement_reason", "self_strict",
            "closed_strict", "closed_strict_pilot_rule", "pinned_strict", "byte_equal", "hardcoded", "failure_count",
            "failures"]
    series = collections.Counter()
    spans = collections.defaultdict(list)
    with (out / "link_status.csv").open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(cols)
        for rec in sorted(recs, key=lambda r: (r["row"]["rva"], r["row"]["name"])):
            r, u = rec["row"], rec["unit"]
            n = ("unit", u["id"])
            st = int(rec["measured"] and not rec["fails"])
            L = rec["linked"]
            be = int(rec["placed"] and I[r["rva"]:r["rva"] + r["size"]] == R[r["rva"]:r["rva"] + r["size"]])
            row = {"name": r["name"], "kind": r["kind"], "source": r["source"], "retail_rva": "0x%08X" % r["rva"],
                   "size": r["size"], "linked_rva": "" if L is None else "0x%08X" % L, "placed": rec["placed"],
                   "placement_reason": u.get("why") or "", "self_strict": st,
                   "closed_strict": int(st and n in closed), "closed_strict_pilot_rule": int(st and n in closed_pilot),
                   "pinned_strict": int(st and not rec["unpinned"]), "byte_equal": be,
                   "hardcoded": int(id(rec) in hard), "failure_count": len(rec["fails"]),
                   "failures": ";".join(f"{k}x{v}" if v > 1 else k for k, v in collections.Counter(rec["fails"]).items())}
            w.writerow([row[c] for c in cols])
            k = r["kind"]
            span = (r["rva"], r["rva"] + r["size"])
            flags = {"all": 1, "placed": rec["placed"], "self_strict_any": st, "placed_self_strict": rec["placed"] and st,
                     "placed_pinned_strict": rec["placed"] and row["pinned_strict"],
                     "placed_closed_strict": rec["placed"] and row["closed_strict"],
                     "placed_closed_strict_pilot_rule": rec["placed"] and row["closed_strict_pilot_rule"],
                     "placed_byte_equal": be, "placed_self_strict_hardcoded": rec["placed"] and st and row["hardcoded"],
                     "placed_self_strict_shift_safe": rec["placed"] and st and not row["hardcoded"]}
            for name, v in flags.items():
                if v:
                    series[(k, name, "rows")] += 1
                    series[(k, name, "bytes")] += r["size"]
                    spans[(k, name)].append(span)
    res = {}
    for (k, name), sp in spans.items():
        res.setdefault(k, {})[name] = {"rows": series[(k, name, "rows")], "bytes": series[(k, name, "bytes")],
                                       "unique_bytes": unique_bytes(sp),
                                       "pct_text": round(100 * unique_bytes(sp) / textsz, 2)}
    reasons = collections.Counter()
    rbytes = collections.Counter()
    for rec in recs:
        if rec["row"]["kind"] == "real" and rec["placed"]:
            for c in {f.split(":")[0] for f in rec["fails"]}:
                reasons[c] += 1
                rbytes[c] += rec["row"]["size"]
    res["credit_unique_bytes"] = res.get("real", {}).get("placed_closed_strict", {}).get("unique_bytes", 0)
    res["placed_failure_classes"] = {c: [reasons[c], rbytes[c]] for c, _ in reasons.most_common()}
    res["twins"] = dict(collections.Counter(v[1] for v in m.twins.values()))
    res["eh_thunks"] = dict(m.eh)
    res["retail_text_bytes"] = textsz
    return res


def shifted_rows(out, recs, I, isecs, objs, have_shift, shift_base):
    """ids of rows whose code holds an unrelocated absolute image address. With a
    shifted link, also confirm the linker laid the image out identically and every
    relocated word moved by exactly the base delta; rows that do not are added."""
    hard = set()
    lo, hi = BASE + 0x1000, BASE + max(s + z for _, s, z in isecs.all)
    S = None
    if have_shift and (out / "shift.exe").exists():
        _, S, ssecs, _ = pe_view(out / "shift.exe")

    for rec in recs:
        if not rec["measured"]:
            continue
        r, L = rec["row"], rec["linked"]
        code = I[L:L + r["size"]]
        if hardcoded_operands(code, L + BASE, rec["masked"], lo, hi):
            hard.add(id(rec))
            continue
        if S is not None:
            moved = S[L:L + r["size"]]
            for k in range(len(code)):
                if k in rec["masked"]:
                    continue
                if code[k] != moved[k]:
                    hard.add(id(rec))
                    break
    return hard


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--build", action="store_true", help="compile stale objects first (BUILD_POOL = cores - 2)")
    ap.add_argument("--max-iter", type=int, default=6, help="links in the quarantine loop (default 6)")
    ap.add_argument("--shift-base", type=lambda s: int(s, 0), default=SHIFT_BASE,
                    help="second link's base (0 = none; default 0x10000000)")
    ap.add_argument("--reuse-quarantine", action="store_true", help="start from the last cycle's quarantine list")
    ap.add_argument("--reuse-stubs", action="store_true", help="skip pass 1, reuse the last cycle's stub names")
    ap.add_argument("--measure-only", action="store_true", help="re-measure the last links (no link)")
    ap.add_argument("--out", default=str(OUT))
    args = ap.parse_args(argv)
    if args.measure_only:
        return remeasure(args)
    cycle(args)
    return 0


def remeasure(args):
    out = Path(args.out)
    rows = census.ledger()
    present, _ = census.objects(rows)
    objs = Objects(present)
    units, _ = analyze(rows, objs)
    _, R, rsecs, rimp = pe_view(build.EXE)
    text0, textsz = rsecs[".text"]
    pins, byaddr = load_pins()
    quarantine = set(json.loads((out / "quarantine.json").read_text())) if (out / "quarantine.json").exists() else set()
    with (ROOT / "reverse/ghidra_functions.csv").open(newline="") as f:
        ghidra = [int(r["rva"], 16) for r in csv.DictReader(f)]
    placed, _, _ = plan_order(units, quarantine, text0, textsz)
    chunks = filler_chunks(placed, [a for a in ghidra + list(byaddr) if text0 <= a < text0 + textsz], text0, textsz)
    t = time.time()
    res = measure(out, units, chunks, objs, R, rsecs, rimp, pins, True, args.shift_base)
    print(json.dumps(res, indent=1))
    path = out / "receipt.json"
    if path.exists():   # the links are the receipt's; the measure, its digest and series are replaced
        receipt = json.loads(path.read_text(encoding="utf-8"))
        receipt.update(series=res, tool_digest=tool_digest(),
                       measure_dirty=bool(git("status", "--porcelain", "--untracked-files=no")),
                       remeasured_utc=time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime()),
                       measure_commit=git("rev-parse", "HEAD"))
        receipt["seconds"]["measure"] = round(time.time() - t)
        path.write_text(json.dumps(receipt, indent=1), encoding="utf-8")
    return 0


if __name__ == "__main__":
    sys.exit(main())
