#!/usr/bin/env python3
"""A real (linked) BFME2 image for the game harnesses: receipt, check, address map, crash map.

  python3 tools/real_image.py check build/exit_link/exit.exe [--addresses]
  python3 tools/real_image.py where build/exit_link/exit.exe 0xVA [--return 0xVA]

`tools/exit_link.py --link` writes exit.exe, exit.map and image_receipt.json side by
side (build/drift_review/swarm/contract.md). `load()` refuses unless the image's and the
map's SHA-256 equal the receipt's. `check()` replaces boot_image.image_ok, which judges
overlay images built on retail's own bytes: a real image has its own layout, so it is
judged as itself (machine, a non-retail base, relocations present, exports and
resources as the receipt says, the map's base and entry agree with the image, the
imports the harness lies through, `real` means nothing stubbed).

Addresses are mapped fail-closed; there is no fall-back to retail's RVA.
- Code: the functions.csv row holding the retail RVA, found by its name in the map, and
  its whole body compared with retail's, decoded (capstone): the same relocated dwords,
  every relative branch and every relocated code address reaching the same place on both
  sides (the same offset inside the body, else the same named function at the same
  offset), whether its bytes changed or not, and every other byte equal. Decoding stops at
  a relocated table that follows the code; past it only relocated dwords may differ. A mid-function address is the row's image address
  plus its offset, accepted only after that comparison.
- Data: retail's DIR32 references to the address, inside rows whose bodies compare
  equal as above; each gives the image's address from the same relocated dword in the
  image's copy. All must agree. Relocated dwords' values are not otherwise compared
  (tools/image_iso.py judges pointers).
- A crash address maps to the map symbol holding it and, when that symbol is one of
  the receipt's stubs (or a stub body shared by several), to the stubbed name, found
  through the caller: the caller's retail row, retail's call at the same return offset,
  and the retail row it calls. Then to the retail row (RVA) by name.
"""
import argparse
import bisect
import csv
import hashlib
import json
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

RETAIL_BASE = 0x400000
FUNCTIONS = ROOT / "reverse" / "functions.csv"


class RealImageError(Exception):
    """The image cannot be run or an address cannot be placed: the harness must stop."""


def sha256_file(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for block in iter(lambda: f.read(1 << 20), b""):
            h.update(block)
    return h.hexdigest()


# --------------------------------------------------------------------------- receipt
def read_receipt(exe):
    """(receipt dict, map path) for exe, after checking both hashes against the receipt."""
    exe = Path(exe)
    rec_path, map_path = exe.parent / "image_receipt.json", exe.parent / "exit.map"
    for p in (exe, rec_path, map_path):
        if not p.is_file():
            raise RealImageError(f"{p} is missing (the image, exit.map and image_receipt.json must lie together)")
    rec = json.loads(rec_path.read_text(encoding="utf-8"))
    problems = receipt_problems(rec)
    if problems:
        raise RealImageError("image_receipt.json: " + "; ".join(problems))
    got = {"image_sha256": sha256_file(exe), "map_sha256": sha256_file(map_path)}
    for k, v in got.items():
        if v != rec[k].lower():
            raise RealImageError(f"{k} differs: receipt {rec[k]}, file {v}")
    return rec, map_path


def receipt_problems(rec):
    """What makes a receipt unusable (contract fields and their meaning). Pure."""
    out = []
    if rec.get("kind") not in ("real", "diagnostic"):
        out.append(f"kind {rec.get('kind')!r} is neither real nor diagnostic")
    if not re.fullmatch(r"[0-9a-f]{40}", str(rec.get("commit", ""))):
        out.append("commit is not a 40-hex commit")
    for k in ("image_sha256", "map_sha256"):
        if not re.fullmatch(r"[0-9a-fA-F]{64}", str(rec.get(k, ""))):
            out.append(f"{k} is not a SHA-256")
    try:
        int(str(rec.get("base")), 16)
    except ValueError:
        out.append(f"base {rec.get('base')!r} is not hex")
    if not isinstance(rec.get("stubbed"), list):
        out.append("stubbed is not a list")
    elif rec.get("kind") == "real" and rec["stubbed"]:
        out.append(f"a real image with {len(rec['stubbed'])} stubbed name(s)")
    return out


# --------------------------------------------------------------------------- the map
class MapFile:
    """A link.exe /MAP: preferred base, entry point (section, offset), and every public
    and static symbol as (va, name, object, is_function)."""

    LINE = re.compile(r"^ ([0-9a-f]{4}):([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8})( f)?(?: i)?\s+(\S.*)$")

    def __init__(self, text):
        self.base = self.entry = None
        syms = []
        for line in text.splitlines():
            if line.startswith(" Preferred load address is "):
                self.base = int(line.split()[-1], 16)
            elif line.startswith(" entry point at "):
                sec, off = line.split()[-1].split(":")
                self.entry = (int(sec, 16), int(off, 16))
            else:
                m = self.LINE.match(line)
                if m and int(m.group(1), 16) and not m.group(2).startswith("ffff"):
                    syms.append((int(m.group(4), 16), m.group(3), m.group(6).strip(), bool(m.group(5))))
        if self.base is None:
            raise RealImageError("the map has no preferred load address")
        syms.sort()
        self.syms = syms
        self.vas = [s[0] for s in syms]
        self.by_name = {}
        for s in syms:
            self.by_name.setdefault(s[1], []).append(s)

    def names_at(self, va):
        i = bisect.bisect_left(self.vas, va)
        out = []
        while i < len(self.syms) and self.syms[i][0] == va:
            out.append(self.syms[i][1])
            i += 1
        return out

    def holding(self, va):
        """(symbol va, offset) of the last symbol at or below va, or (None, None)."""
        i = bisect.bisect_right(self.vas, va) - 1
        return (self.syms[i][0], va - self.syms[i][0]) if i >= 0 else (None, None)


def object_name(source):
    """The object name link.exe prints for a source path (exit_link's flattening:
    '/' -> '_', an upper-case letter -> '^' + lower case), without extension."""
    stem = str(source).rsplit(".", 1)[0]
    return "".join("^" + c.lower() if c.isupper() else c for c in stem.replace("/", "_"))


# --------------------------------------------------------------------------- the two images
class Sections:
    """Read bytes of a PE by RVA; executable ranges; base relocation sites (DIR32)."""

    def __init__(self, path):
        import pefile
        self.pe = pefile.PE(str(path), fast_load=True)
        self.pe.parse_data_directories([0, 1, 2, 5])
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        self.secs = []
        for s in self.pe.sections:
            raw = s.get_data()[:min(s.SizeOfRawData, s.Misc_VirtualSize or s.SizeOfRawData)]
            size = max(s.Misc_VirtualSize, len(raw))
            self.secs.append((s.VirtualAddress, size, raw.ljust(size, b"\0"),
                              bool(s.Characteristics & 0x20000000), s.Name.rstrip(b"\0").decode("latin-1")))
        self.secs.sort()
        self.relocs = set()
        for block in getattr(self.pe, "DIRECTORY_ENTRY_BASERELOC", []):
            for e in block.entries:
                if e.type == 3:                         # IMAGE_REL_BASED_HIGHLOW
                    self.relocs.add(e.rva)

    def read(self, rva, n):
        for va, size, raw, _, _ in self.secs:
            if va <= rva and rva + n <= va + size:
                return raw[rva - va:rva - va + n]
        raise RealImageError(f"{rva:#x}+{n:#x} lies outside the image's sections")

    def u32(self, rva):
        return struct.unpack("<I", self.read(rva, 4))[0]

    def code(self, rva):
        return any(va <= rva < va + size and x for va, size, _, x, _ in self.secs)

    def section(self, rva):
        return next((n for va, size, _, _, n in self.secs if va <= rva < va + size), None)


class Rows:
    """functions.csv rows: (start, size, name, source), searchable by RVA and by name."""

    def __init__(self, path=FUNCTIONS, rows=None):
        if rows is None:
            rows = []
            with open(path, newline="", encoding="utf-8") as f:
                for r in csv.DictReader(f):
                    if r["target_rva"] and r["target_size"]:
                        rows.append((int(r["target_rva"], 16), int(r["target_size"]), r["name"], r["source"]))
        self.rows = sorted(rows)
        self.starts = [r[0] for r in self.rows]
        self.longest = max((r[1] for r in self.rows), default=0)
        self.by_name = {}
        for r in self.rows:
            self.by_name.setdefault(r[2], []).append(r)

    def holding(self, rva):
        i = bisect.bisect_right(self.starts, rva) - 1
        out = []
        while i >= 0 and self.rows[i][0] > rva - self.longest - 1:
            s, z, _, _ = self.rows[i]
            if s <= rva < s + z:
                out.append(self.rows[i])
            i -= 1
        return out


class Retail:
    """Retail game.dat: bytes by RVA and its DIR32 sites (recovered by boot_image, since
    retail's own table is stripped)."""

    def __init__(self, sections=None, sites=None):
        import boot_image
        self.img = sections or Sections(boot_image.build.EXE)
        self._sites, self._by_value = sites, None

    def read(self, rva, n):
        return self.img.read(rva, n)

    def sites(self):
        if self._sites is None:
            import boot_image
            self._sites = set(boot_image.all_sites(boot_image.Retail())[0])
        return self._sites

    def referring(self, rva):
        """Retail DIR32 sites whose dword is exactly RETAIL_BASE + rva."""
        if self._by_value is None:
            self._by_value = {}
            for s in sorted(self.sites()):
                try:
                    self._by_value.setdefault(self.img.u32(s), []).append(s)
                except RealImageError:
                    pass
        return self._by_value.get(RETAIL_BASE + rva, [])


# --------------------------------------------------------------------------- the mapper
class RealImage:
    """A loaded, hash-checked real image with its map, and the retail side to map from."""

    def __init__(self, exe, receipt, mapfile, image=None, retail=None, rows=None, need_relocs=True):
        self.exe, self.receipt, self.map = Path(exe), receipt, mapfile
        self.img = image or Sections(exe)
        self.base = self.img.base
        self.retail = retail or Retail()
        self.rows = rows or Rows()
        self.stubbed = set(receipt.get("stubbed") or [])
        self.need_relocs = need_relocs
        self._bodies = {}
        self.folds = set()            # (retail row name, image name) accepted as the same body

    # names -> image addresses -------------------------------------------------
    def image_of_name(self, name, source=None):
        """Image VA of the one map symbol with this decorated name (narrowed by object
        when several), else RealImageError."""
        cands = self.map.by_name.get(name, [])
        if len({c[0] for c in cands}) > 1 and source:
            own = [c for c in cands if object_name(source) in c[2]]
            if len({c[0] for c in own}) == 1:
                return own[0][0]
        if len({c[0] for c in cands}) != 1:
            raise RealImageError(f"{name}: {len(cands)} map symbol(s)" + (f", not one from {source}" if source else ""))
        return cands[0][0]

    def verify_body(self, row, iva, depth=0, end=None):
        """None if the image's copy of retail row `row` at image VA iva is the same body
        (see the module doc), else why not; with `end`, only its first `end` bytes (the
        instructions starting there, the relocations starting there). Cached."""
        key = (row, iva, depth, end)
        if key not in self._bodies:
            self._bodies[key] = self._verify_body(row, iva, depth, end)
        return self._bodies[key]

    def _verify_body(self, row, iva, depth, end=None):
        start, size, name, _ = row
        irva = iva - self.base
        end = size if end is None else min(end, size)
        try:
            r, i = self.retail.read(start, size), self.img.read(irva, size)
        except RealImageError as e:
            return str(e)
        rsites = {s - start for s in self.retail.sites() if start <= s < start + size}
        isites = {s - irva for s in self.img.relocs if irva <= s < irva + size}
        if end < size:                                # a prefix: what starts inside it
            rsites, isites = {o for o in rsites if o < end}, {o for o in isites if o < end}
        if self.need_relocs or isites:
            if rsites != isites:
                return (f"relocated dwords differ: retail-only {sorted(hex(x) for x in rsites - isites)[:4]}, "
                        f"image-only {sorted(hex(x) for x in isites - rsites)[:4]}")
        try:
            decoded, data_from = decode(start, r, rsites)
        except ImportError:
            return "capstone is needed to decode the body"
        if data_from < end and data_from not in rsites and any(b not in (0xCC, 0x00) for b in r[data_from:end]):
            return f"+{data_from:#x} neither decodes nor starts a relocated table"
        allowed = set()
        for o, n, rel in decoded:                     # every relative target, changed bytes or not
            if rel and o < end:
                p, k = rel
                fmt = "<i" if k == 4 else "<b"
                why = self._same_place(row, irva, start + o + n + struct.unpack_from(fmt, r, p)[0],
                                       irva + o + n + struct.unpack_from(fmt, i, p)[0], depth)
                if why:
                    return f"branch at +{o:#x}: {why}"
                allowed.update(range(p, p + k))
        for o in sorted(rsites):                      # every relocated address of code (jump tables too)
            rt = struct.unpack_from("<I", r, o)[0] - RETAIL_BASE
            if self.retail.img.code(rt):
                why = self._same_place(row, irva, rt, struct.unpack_from("<I", i, o)[0] - self.base, depth)
                if why:
                    return f"code address at +{o:#x}: {why}"
            allowed.update(range(o, o + 4))
        for o in range(end):
            if r[o] != i[o] and o not in allowed:
                return f"byte +{o:#x} differs ({r[o]:02x} / {i[o]:02x}) outside any relocation or branch operand"
        return None

    def _same_place(self, row, irva, rt, it, depth):
        """None if retail target RVA rt (from inside `row`) and image target RVA it are the
        same place: the same offset inside this body, else the same named function."""
        start, size = row[0], row[1]
        if start <= rt < start + size:
            return None if it - irva == rt - start else f"internal target +{rt - start:#x} lands at +{it - irva:#x}"
        return self._same_target(rt, it, depth)

    def _same_target(self, rt, it, depth):
        """None if retail target RVA rt and image target RVA it are the same named
        function at the same offset, else why not. A differently named image target is
        accepted only at the top level, when its body compares equal to retail's target
        row (one level deeper, where names must agree): a fold retail made and this link
        did not (seen: AsciiString::isEmpty for StringBase<char>::isEmpty)."""
        held = self.rows.holding(rt)
        sym, off = self.map.holding(self.base + it)
        if not held or sym is None:
            return f"target {rt:#x} / {it:#x} unnamed"
        names = set(self.map.names_at(sym))
        for s, _, name, _ in held:
            if name in names and rt - s == off:
                return None
        if depth == 0:
            for row in held:
                if rt - row[0] == off and self.verify_body(row, sym, depth + 1) is None:
                    self.folds.add((row[2], sorted(names)[0]))
                    return None
        return f"retail target {held[0][2]}+{rt - held[0][0]:#x}, image target {sorted(names)[:2]}+{off:#x}"

    def map_code(self, rva):
        """Image VA of retail code RVA rva (a function start or inside one), fail-closed."""
        held = self.rows.holding(rva)
        if not held:
            raise RealImageError(f"{rva:#x}: no functions.csv row holds it")
        found, why = set(), []
        for row in held:
            try:
                iva = self.image_of_name(row[2], row[3])
            except RealImageError as e:
                why.append(str(e))
                continue
            bad = self.verify_body(row, iva)
            if bad:
                why.append(f"{row[2]}: {bad}")
            else:
                found.add(iva + rva - row[0])
        if len(found) != 1:
            raise RealImageError(f"{rva:#x}: {'; '.join(why) if not found else f'{len(found)} different places'}")
        return found.pop()

    def map_data(self, rva):
        """Image VA of retail data RVA rva from retail's DIR32 references to it inside
        rows whose bodies compare equal; every such reference is read, and all must agree."""
        votes, why = {}, []
        for site in self.retail.referring(rva):
            for row in self.rows.holding(site):
                try:
                    iva = self.image_of_name(row[2], row[3])
                except RealImageError as e:
                    why.append(str(e))
                    continue
                bad = self.verify_body(row, iva)
                if bad:
                    why.append(f"{row[2]}: {bad}")
                    continue
                isite = iva - self.base + site - row[0]
                if self.need_relocs and isite not in self.img.relocs:
                    why.append(f"{row[2]}+{site - row[0]:#x}: no relocation in the image")
                    continue
                votes.setdefault("ok", []).append((self.img.u32(isite), row[2], site))
        got = {v for v, _, _ in votes.get("ok", [])}
        if len(got) != 1:
            detail = f"{len(got)} different addresses" if got else ("; ".join(why[:3]) or "no retail reference")
            raise RealImageError(f"{rva:#x}: {detail}")
        return got.pop()

    def map_rva(self, rva):
        """Image VA (at the image's preferred base) for retail RVA rva."""
        return self.map_code(rva) if self.retail.img.code(rva) else self.map_data(rva)

    def rva_map(self):
        """retail RVA -> image RVA, raising KeyError (game_smoke's convention) when unplaceable."""
        cache = {}

        def move(r):
            if r not in cache:
                try:
                    cache[r] = self.map_rva(r) - self.base
                except RealImageError as e:
                    raise KeyError(str(e)) from None
            return cache[r]
        return move

    # crashes ------------------------------------------------------------------
    def where(self, va, return_va=None):
        """The contract's crash fields for image VA va (at the preferred base): map_symbol,
        stubbed_name, retail_rva, plus how they were found. Nothing is chosen among
        aliases: several names at the symbol leave map_symbol null (names_at_symbol lists
        them), and retail_rva is set only when every candidate row gives the same RVA and,
        for a crash inside a function, its image body equals retail's through the crashing
        instruction (else retail_rva_why says why; retail_row and the offset stay)."""
        out = {"address_image": hex(va), "return_address_image": hex(return_va) if return_va else None,
               "map_symbol": None, "stubbed_name": None, "retail_rva": None}
        sym, off = self.map.holding(va)
        if sym is None or not self.img.code(va - self.base):
            out["note"] = "outside the image's code"
            return out
        names = self.map.names_at(sym)
        out["offset"] = hex(off)
        if len(names) == 1:
            out["map_symbol"] = names[0]
        else:
            out["names_at_symbol"] = names[:8]
        stubs = [n for n in names if n in self.stubbed]
        if len(stubs) == 1 and len(names) == 1:
            out["stubbed_name"], out["stubbed_by"] = stubs[0], "map symbol"
        elif stubs or any("stub" in s[2].lower() for n in names for s in self.map.by_name.get(n, [])):
            out["stubbed_name"], out["stubbed_by"] = self.stub_from_caller(sym, return_va)
        if out["stubbed_name"]:
            cands = {(r[0], out["stubbed_name"]) for r in self.rows.by_name.get(out["stubbed_name"], [])}
        elif stubs:                                   # an unresolved stub: its missing functions' entries
            cands = {(r[0], n) for n in stubs for r in self.rows.by_name.get(n, [])}
        else:
            cands, why = set(), []
            rows = [(n, r) for n in names for r in self.rows.by_name.get(n, [])]
            if len({n for n, _ in rows}) == 1:
                out["retail_row"] = rows[0][0]        # named, whether or not its offset maps
            for n, row in rows:
                bad = self.crash_offset_problem(row, sym, off)
                if bad:
                    why.append(f"{n}: {bad}")
                    cands.add((None, n))
                else:
                    cands.add((row[0] + off, n))
                    if len(rows) == 1:
                        out["crash_operands"] = self.crash_operands(row, sym, off)
            if why:
                out["retail_rva_why"] = why[:4]
        if len({c[0] for c in cands}) == 1 and None not in {c[0] for c in cands}:
            out["retail_rva"] = hex(next(iter(cands))[0])
            out["retail_row"] = sorted(c[1] for c in cands)[0] if len(cands) == 1 else sorted(c[1] for c in cands)
        elif len(cands) > 1:
            out["retail_rva_candidates"] = sorted({hex(c[0]) for c in cands if c[0] is not None})[:8]
        return out

    def crash_offset_problem(self, row, sym, off):
        """None if `off` into the image's copy of `row` (at image VA sym) is the same
        instruction as `off` into retail's row: the image body equals retail's from its
        start through that instruction. Else why not (then the offset means nothing in
        retail, as at a rebuilt entry point)."""
        if off >= row[1]:
            return f"+{off:#x} lies beyond the retail row ({row[1]:#x} bytes)"
        try:
            decoded, _ = decode(row[0], self.retail.read(row[0], row[1]),
                                {s - row[0] for s in self.retail.sites() if row[0] <= s < row[0] + row[1]})
        except (ImportError, RealImageError) as e:
            return str(e)
        ins = [(o, n) for o, n, _ in decoded if o == off]
        if not ins:
            return f"+{off:#x} is not an instruction start in retail's body"
        bad = self.verify_body(row, sym, 0, off + ins[0][1])
        return f"the image body differs from retail's before the crash: {bad}" if bad else None

    def crash_operands(self, row, sym, off):
        """The relocated operands of the crashing instruction (at `off` in both bodies,
        which compare equal through it): retail's and the image's targets, with the image's
        map symbol and both sections. The body check does not compare where relocated data
        operands point, so this is where a wrong one shows (seen: retail's .data
        __adjust_fdiv linked to msvcr71's import thunk in .text, LINK-548)."""
        decoded, _ = decode(row[0], self.retail.read(row[0], row[1]),
                            {s - row[0] for s in self.retail.sites() if row[0] <= s < row[0] + row[1]})
        n = next(n for o, n, _ in decoded if o == off)
        out = []
        for s in sorted(x for x in self.retail.sites() if row[0] + off <= x < row[0] + off + n):
            rt = self.retail.img.u32(s) - RETAIL_BASE
            it = self.img.u32(sym - self.base + s - row[0]) - self.base
            isym, ioff = self.map.holding(self.base + it)
            out.append({"retail": hex(RETAIL_BASE + rt), "retail_section": self.retail.img.section(rt),
                        "image": hex(self.base + it), "image_section": self.img.section(it),
                        "image_symbol": f"{'|'.join(self.map.names_at(isym))}+{ioff:#x}" if isym else None})
        return out

    def stub_from_caller(self, stub_va, return_va):
        """(stubbed name, how) for a stub entered by `call rel32` returning to return_va:
        retail's own call at the caller's matching offset names the missing function. The
        caller's image body must compare equal to its retail row first (so the offset means
        the same instruction), and every such caller row must name the same stubbed function."""
        if not return_va:
            return None, "no return address"
        try:
            if self.img.read(return_va - self.base - 5, 1) != b"\xE8" or \
                    return_va + struct.unpack("<i", self.img.read(return_va - self.base - 4, 4))[0] != stub_va:
                return None, "the return address does not follow a call to the stub"
        except RealImageError:
            return None, "the return address lies outside the image"
        csym, coff = self.map.holding(return_va)
        found, why = set(), []
        for name in self.map.names_at(csym):
            for row in self.rows.by_name.get(name, []):
                start, size = row[0], row[1]
                bad = self.verify_body(row, csym)
                if bad:
                    why.append(f"caller {name} differs from retail: {bad}")
                    continue
                ret = start + coff
                if coff > size or self.retail.read(ret - 5, 1) != b"\xE8":
                    why.append(f"retail {name}+{coff - 5:#x} is not a call")
                    continue
                target = ret + struct.unpack("<i", self.retail.read(ret - 4, 4))[0]
                called = [r[2] for r in self.rows.holding(target) if r[0] == target]
                hit = [n for n in called if n in self.stubbed]
                if len(hit) == 1:
                    found.add((hit[0], f"caller {name}+{coff:#x}: retail calls {target:#x}"))
                else:
                    why.append(f"caller {name}+{coff:#x}: retail calls {called[:2] or hex(target)}, not one stubbed name")
        if len({f[0] for f in found}) == 1:
            return next(iter(found))
        return None, "; ".join(why[:3]) or (f"{len(found)} different stubbed names" if found else "the caller has no retail row")


def decode(start, r, rsites):
    """Retail body r at RVA start, decoded linearly: ([(offset, size, (operand offset,
    operand size) of a relative branch or None)], offset where the data begins). Decoding
    stops at an instruction holding a relocated dword that is not its operand (MSVC puts
    switch tables after the code) or at bytes that do not decode."""
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    out, end = [], 0
    for ins in md.disasm(r, start):
        o = ins.address - start
        if o != end or o + ins.size > len(r):
            break
        ops = {o + ins.disp_offset if ins.disp_size == 4 and ins.disp_offset else -1,
               o + ins.imm_offset if ins.imm_size == 4 and ins.imm_offset else -1}
        if any(x in rsites and x not in ops for x in range(o - 3, o + ins.size)):
            break                                     # a relocated dword overlaps it, not as an operand
        rel = (o + ins.imm_offset, ins.imm_size) if ins.group(capstone.CS_GRP_BRANCH_RELATIVE) else None
        out.append((o, ins.size, rel))
        end = o + ins.size
    return out, end


# --------------------------------------------------------------------------- runs
def follows_call(img, rva):
    """Whether the bytes before image RVA rva end in a call (E8 rel32, or FF /2 with a
    register, [reg], [reg+disp8] or [disp32]/[reg+disp32] operand)."""
    try:
        b = img.read(rva - 7, 7)
    except RealImageError:
        return False
    return b[2] == 0xE8 or any(b[7 - n] == 0xFF and b[8 - n] & 0x38 == 0x10 for n in (2, 3, 4, 6))


def crash_fields(ri, address, loaded, words, exception):
    """The contract's crash dict for a run-time fault at `address` with the image loaded
    at `loaded` and `words` the dwords from esp: the return address is the first stack
    word in the image's code that follows a call."""
    size = ri.img.pe.OPTIONAL_HEADER.SizeOfImage
    ret, frames = None, []
    for w in words or []:
        rva = w - loaded
        if 0 <= rva < size and ri.img.code(rva) and follows_call(ri.img, rva):
            if ret is None:
                ret = ri.base + rva
            if len(frames) < 12:
                sym, off = ri.map.holding(ri.base + rva)
                frames.append([hex(ri.base + rva), f"{'|'.join(ri.map.names_at(sym))}+{off:#x}" if sym else None])
    out = {"exception": exception} | ri.where(address - loaded + ri.base, ret)
    out["stack_frames"] = frames
    if loaded != ri.base:
        out["loaded_at"] = hex(loaded)
    return out


def crash_name(crash):
    """What a crash outcome is called: the stubbed name, else the map symbol (null when the
    address has several names), else the address."""
    return crash.get("stubbed_name") or crash.get("map_symbol") or crash.get("address_image")


def rebased_copy(ri, new_base, path):
    """A copy of the image with its relocations applied for `new_base` (G3 asks for two
    non-retail bases); its SHA-256 is reported beside the receipt's."""
    import pefile
    if new_base == RETAIL_BASE or new_base & 0xFFFF:
        raise RealImageError(f"rebase to {new_base:#x}: not retail's base, and 64 KiB aligned")
    pe = pefile.PE(str(ri.exe), fast_load=True)
    pe.parse_data_directories([5])          # only relocations: parsed import thunks would be rewritten too
    pe.relocate_image(new_base)
    pe.OPTIONAL_HEADER.ImageBase = new_base
    pe.write(str(path))
    pe.close()
    return Path(path)


def install_game_dat(exe, game_dir):
    """Copy the image under test to game_dir/game.dat and prove it is there: the copy's
    SHA-256 must equal the source's, so a retail control never runs a leftover image (the
    game queue stages each linked image into the same game folder). Returns the hash."""
    import shutil
    dest = Path(game_dir) / "game.dat"
    shutil.copyfile(exe, dest)
    want, got = sha256_file(exe), sha256_file(dest)
    if want != got:
        raise RealImageError(f"{dest} has SHA-256 {got}, not {want} of {exe}")
    return got


def result_of(outcome):
    """The receipt's result for a harness outcome: crashes and exits by kind, debugger
    failures inconclusive, anything else as the harness named it."""
    if outcome.startswith(("crash-at-", "crash-dialog")):
        return "crashed"
    if outcome.startswith("exit-"):
        return "exited"
    if outcome == "debugger-error":
        return "inconclusive"
    return outcome


def receipt_fields(tool, mode, outcome, image, crash, started, seconds):
    """The harness's part of a run receipt (contract): the game queue adds harness_sha,
    harness_on_master and isolation itself, and names the file."""
    return {"tool": tool, "mode": mode, **image, "result": result_of(outcome), "outcome": outcome,
            "crash": crash, "started": started, "seconds": round(seconds)}


def retail_summary():
    import boot_image
    return {"image_kind": "retail", "image_sha256": sha256_file(boot_image.build.EXE), "image_commit": None,
            "base": hex(RETAIL_BASE)}


# --------------------------------------------------------------------------- the check
def image_facts(img, mapfile):
    """What check() judges, read from the image and its map."""
    pe = img.pe
    oh, fh = pe.OPTIONAL_HEADER, pe.FILE_HEADER
    dirs = oh.DATA_DIRECTORY
    entry_va = None
    if mapfile.entry and 0 < mapfile.entry[0] <= len(pe.sections):
        entry_va = mapfile.base + pe.sections[mapfile.entry[0] - 1].VirtualAddress + mapfile.entry[1]
    exports = getattr(pe, "DIRECTORY_ENTRY_EXPORT", None)
    imports = {}
    for d in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
        for imp in d.imports:
            if imp.name:
                key = (d.dll.decode("latin-1").lower(), imp.name.decode("latin-1"))
                imports[key] = imports.get(key, 0) + 1
    return {"machine": fh.Machine, "base": oh.ImageBase, "relocs_stripped": bool(fh.Characteristics & 1),
            "reloc_sites": len(img.relocs), "export_names": len(exports.symbols) if exports else 0,
            "resource_dir": dirs[2].Size, "entry": oh.ImageBase + oh.AddressOfEntryPoint,
            "map_base": mapfile.base, "map_entry": entry_va,
            "imports": {f"{d}!{n}": c for (d, n), c in imports.items()
                        if n in ("SHGetSpecialFolderPathW", "GetVersion", "GetVersionExA")}}


def judge(facts, receipt):
    """[problem] for an image that must not run as a real image (empty: it may). Pure."""
    out = []
    base = int(str(receipt["base"]), 16)
    if facts["machine"] != 0x14C:
        out.append(f"machine {facts['machine']:#x} is not i386")
    if facts["base"] != base:
        out.append(f"image base {facts['base']:#x} is not the receipt's {base:#x}")
    if facts["base"] == RETAIL_BASE:
        out.append("image base is retail's 0x400000")
    if facts["relocs_stripped"] or not facts["reloc_sites"]:
        out.append("no base relocations (not linked /FIXED:NO)")
    if not receipt.get("fixed_no"):
        out.append("receipt says not /FIXED:NO")
    if facts["map_base"] != facts["base"]:
        out.append(f"map's preferred base {facts['map_base']:#x} is not the image's")
    if facts["map_entry"] != facts["entry"]:
        out.append(f"map's entry point {facts['map_entry']} is not the image's {facts['entry']:#x}")
    want = receipt.get("exports_requested") or 0
    if facts["export_names"] < max(want, 1):
        out.append(f"{facts['export_names']} exported name(s), {want} requested")
    if receipt.get("rsrc") is not True or not facts["resource_dir"]:
        out.append("no .rsrc (receipt rsrc must be true and the resource directory present)")
    for need in ("shell32.dll!SHGetSpecialFolderPathW", "kernel32.dll!GetVersion", "kernel32.dll!GetVersionExA"):
        if facts["imports"].get(need) != 1:
            out.append(f"{need} imported {facts['imports'].get(need, 0)} time(s), the harness needs exactly one")
    return out


def load(exe, **kw):
    """A RealImage for exe (hashes checked against its receipt), or RealImageError."""
    receipt, map_path = read_receipt(exe)
    return RealImage(exe, receipt, MapFile(map_path.read_text(encoding="latin-1")), **kw)


def check(ri):
    """(ok, report): replaces boot_image.image_ok for a real image."""
    facts = image_facts(ri.img, ri.map)
    problems = judge(facts, ri.receipt)
    return not problems, {"kind": ri.receipt["kind"], "commit": ri.receipt["commit"],
                          "image_sha256": ri.receipt["image_sha256"], "base": hex(ri.base),
                          "stubbed": len(ri.stubbed), "facts": facts, "problems": problems}


def summary(ri):
    """The image fields of a harness receipt (contract)."""
    return {"image_kind": ri.receipt["kind"], "image_sha256": ri.receipt["image_sha256"],
            "image_commit": ri.receipt["commit"], "base": hex(ri.base)}


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("check")
    p.add_argument("exe", type=Path)
    p.add_argument("--addresses", action="store_true", help="also map game_smoke's retail addresses")
    p = sub.add_parser("where")
    p.add_argument("exe", type=Path)
    p.add_argument("va", type=lambda v: int(v, 0))
    p.add_argument("--return", dest="ret", type=lambda v: int(v, 0))
    a = ap.parse_args(argv)
    try:
        ri = load(a.exe)
    except RealImageError as e:
        print(json.dumps({"refused": str(e)}, indent=1))
        return 1
    if a.cmd == "where":
        print(json.dumps(ri.where(a.va, a.ret), indent=1))
        return 0
    ok, rep = check(ri)
    if a.addresses:
        import game_smoke
        move, placed = ri.rva_map(), {}
        for name, rva in game_smoke.RVA.items():
            try:
                placed[name] = hex(ri.base + move(rva))
            except KeyError as e:
                placed[name] = f"refused: {e}"
                ok = False
        rep["addresses"] = placed
    print(json.dumps(rep, indent=1))
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
