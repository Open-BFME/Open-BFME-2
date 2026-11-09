"""boot_relayout: relaid and own-data overlay images, and controls for their semantic check.

In these images a wrong name or wrong data in an authored object is no longer
hidden by retail's bytes at the old address: the controls mutate one object,
let check-driven admission link it as the object says, and require the image
check to fail (and the next round to refuse what it blamed). Each build links
an image with the VS2003 toolchain (about 30 s); the tests skip without the
pilot's objects.
"""
import bisect
import collections
import contextlib
import json
import shutil
import struct
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import boot_image  # noqa: E402

PILOT = "Code/Libraries/Source/profile/"
JUMP = 0x1381B0                       # ShaderClass::Guess_Sort_Level: a five-entry switch jump table
COPY = "Code/GameEngine/Source/Common/System/CopyProtectVerified.cpp"   # int CopyProtect::s_verified = -1
SET = [PILOT, f"rva:{JUMP:#x}", COPY]
STOP_RANGE = 0x6C57B0                 # Profile::StopRange calls ProfileAllocMemory
S_VERIFIED = 0x9A7574


def ready():
    try:
        rows = boot_image.overlay_rows(SET)
        boot_image.build.vc71_root()
        import boot_relayout
        boot_relayout.build_image  # noqa: B018
    except (SystemExit, Exception):
        return False
    return len(rows) > 50 and all(boot_image.build.row_object(r).exists() for r in rows)


class Mutated:
    """link_cycle.Objects whose objects at the given paths come back changed by
    edit(secs, syms, bytearray data) -> (secs, syms, bytes)."""
    def __init__(self, edits):
        import link_cycle
        self.inner, self.edits = link_cycle.Objects([]), {Path(k): v for k, v in edits.items()}

    def get(self, p):
        o = self.inner.get(p)
        edit = self.edits.pop(Path(p), None)
        if o is not None and edit:
            o = self.inner.cache[Path(p)] = edit(o[0], o[1], bytearray(o[2]))
        return o


def obj_of(spec_or_rva):
    rows = boot_image.overlay_rows([spec_or_rva])
    return boot_image.build.row_object(rows[0]), rows


def overlay_status(rep):
    import csv
    with open(rep["overlay"]["rows_csv"], newline="", encoding="utf-8") as f:
        return {int(x["retail_rva"], 16): x["overlay"] for x in csv.DictReader(f)}


@unittest.skipUnless(ready(), "pilot objects not built")
class Relayout(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        import boot_relayout
        cls.br = boot_relayout
        cls.tmp = Path(tempfile.mkdtemp())
        cls.rep = boot_relayout.build_image(out=cls.tmp / "clean", tag="rl", overlay=SET, rounds=1)

    @classmethod
    def tearDownClass(cls):
        shutil.rmtree(cls.tmp, ignore_errors=True)

    def build(self, name, edits, rounds=1, **kw):
        return self.br.build_image(out=self.tmp / name, tag=name, overlay=SET, rounds=rounds, objs=Mutated(edits),
                                   **kw)

    def test_clean_overlay_moves_and_passes(self):
        rl, chk = self.rep["relayout"], self.rep["check"]
        self.assertTrue(boot_image.image_ok(self.rep), self.rep.get("check_bad"))
        self.assertEqual(rl["units_moved"], rl["units"])               # every unit left retail's address
        self.assertEqual(chk["units-moved-at-retail-offset"], 0)
        self.assertEqual(chk["filler-bytes"], rl["bytes_moved"])
        self.assertEqual(chk["filler-bytes-not-int3"], 0)
        self.assertGreater(rl["moves"]["redirected-rel32"], 0)          # scaffold calls follow the moved units
        self.assertEqual((rl["sweep"]["missed"], rl["sweep"]["false"]), (0, 0))
        self.assertGreater(chk["moved-reloc-ok"], chk.get("moved-bytes-differ", 0))
        self.assertIn(JUMP, {p.start for p in self.rep["_layout"]["moved"]})

    def test_wrong_callee_name_fails_the_check(self):
        path = next(boot_image.build.row_object(r) for r in boot_image.overlay_rows([PILOT])
                    if int(r["target_rva"], 16) == STOP_RANGE)

        def edit(secs, syms, data):
            other = next(i for i, y in syms.items() if y.name == "?ProfileReAllocMemory@@YAPAXPAXI@Z")
            for s in secs:
                s.relocs = [(o, other if syms[i].name == "?ProfileAllocMemory@@YAPAXI@Z" else i, k)
                            for o, i, k in s.relocs]
            return secs, syms, bytes(data)
        rep = self.build("callee", {path: edit}, rounds=2)
        first = rep["rounds"][0]
        self.assertGreaterEqual(first["reloc-bad"], 1)                   # round 1: linked as written, check fails
        self.assertEqual(overlay_status(rep)[STOP_RANGE], "refused:check-field")
        self.assertTrue(boot_image.image_ok(rep), rep.get("check_bad"))  # round 2: refused, the rest passes

    def test_wrong_jump_table_target_fails_the_check(self):
        path, _ = obj_of(f"rva:{JUMP:#x}")
        unit = next(p for p in self.rep["_layout"]["moved"] if p.start == JUMP).unit

        def edit(secs, syms, data):
            s = secs[unit.sec - 1]
            jt = [(o, i) for o, i, k in s.relocs if k == boot_image.DIR32 and syms[i].sec == unit.sec
                  and unit.off <= o < unit.off + unit.size]
            target = lambda e: syms[e[1]].value + struct.unpack_from("<i", data, s.ptr + e[0])[0]  # noqa: E731
            first = jt[-1]                                      # the table is the function's tail
            other = next(e for e in reversed(jt) if target(e) != target(first))
            self.assertIn(first[0] - other[0], (4, 8, 12))      # both entries of the table
            s.relocs = [(o, other[1] if o == first[0] else i, k) for o, i, k in s.relocs]
            struct.pack_into("<i", data, s.ptr + first[0], struct.unpack_from("<i", data, s.ptr + other[0])[0])
            self.assertEqual(target((first[0], other[1])), target(other))   # case 0 now jumps to another label
            return secs, syms, bytes(data)
        rep = self.build("jump", {path: edit})
        self.assertGreaterEqual(rep["check"]["reloc-bad"], 1)
        self.assertIn("unit %#x field" % JUMP, rep["check_blame"])
        self.assertFalse(boot_image.image_ok(rep))

    def test_hardcoded_call_in_a_moved_unit_is_caught(self):
        """A moved unit's call written as retail's raw rel32 (an unrelocated field) is caught."""
        lay = self.rep["_layout"]
        p = next(p for p in lay["moved"] if p.start == STOP_RANGE)
        o = next(o for o, k, n in p.unit.relocs if k == boot_image.REL32 and n != p.unit.label)
        raw = struct.unpack_from("<I", boot_image.Retail().secs[".text"][2], p.start + o - 0x1000)[0]
        exe = self.tmp / "hard.exe"
        shutil.copyfile(self.tmp / "clean" / "rl.exe", exe)
        import pefile
        pe = pefile.PE(str(exe))
        off = pe.get_offset_from_rva(lay["publics"][p.public] + o)
        pe.close()
        data = bytearray(exe.read_bytes())
        data[off:off + 4] = struct.pack("<I", raw)
        exe.write_bytes(bytes(data))
        counts, _, blame = self.br.check_semantic(boot_image.Retail(), lay["scaffold"], lay["moved"], lay["datums"],
                                                  lay["branches"], lay["sites"], exe, 0x10000000, lay["publics"])
        self.assertEqual(counts["moved-reloc-bad"], 1)
        self.assertEqual(blame, {("unit", STOP_RANGE): "field"})


@unittest.skipUnless(ready(), "pilot objects not built")
class OwnData(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        import boot_relayout
        cls.br = boot_relayout
        cls.tmp = Path(tempfile.mkdtemp())
        cls.rep = boot_relayout.build_image(out=cls.tmp / "clean", tag="od", overlay=SET, rounds=1, own_data=True)

    @classmethod
    def tearDownClass(cls):
        shutil.rmtree(cls.tmp, ignore_errors=True)

    def owned(self, start):
        return next((p, body) for p, body, _ in self.rep["_layout"]["datums"] if p.start == start)

    def test_clean_overlay_owns_its_data_and_passes(self):
        od, chk = self.rep["own_data"], self.rep["check"]
        self.assertTrue(boot_image.image_ok(self.rep), self.rep.get("check_bad"))
        self.assertGreater(od["bytes_ours"], 1000)
        self.assertEqual(chk["owned-data-bytes"], od["bytes_ours"])
        self.assertEqual(chk.get("owned-bytes-differ"), 0)
        p, body = self.owned(S_VERIFIED)
        self.assertEqual((p.name, body), (".odata", struct.pack("<i", -1)))
        # the image's copy is ours, not retail's: our section, at another address
        self.assertNotEqual(self.rep["_layout"]["publics"][p.public] - p.start,
                            self.rep["_layout"]["publics"]["_boot_entry"] - boot_image.Retail().entry)

    def test_wrong_literal_fails_the_check(self):
        p, body = next((p, b) for p, b, rels in self.rep["_layout"]["datums"]
                       if p.name == ".ordata" and not rels and len(b) > 8 and b.rstrip(b"\0").isascii()
                       and b[:4].isalpha())
        target = bytes(body)

        def edit(secs, syms, data):
            at = bytes(data).find(target)
            self.assertGreater(at, 0)
            data[at] ^= 0x20                                            # one letter's case
            return secs, syms, bytes(data)
        paths = {boot_image.build.row_object(r) for r in boot_image.overlay_rows([PILOT])}
        holder = next(q for q in paths if target in q.read_bytes())
        rep = self.br.build_image(out=self.tmp / "lit", tag="lit", overlay=SET, rounds=1, own_data=True,
                                  objs=Mutated({holder: edit}))
        self.assertGreaterEqual(rep["check"]["owned-bytes-differ"], 1)
        self.assertIn("datum %#x bytes" % p.start, rep["check_blame"])
        self.assertFalse(boot_image.image_ok(rep))

    def test_wrong_initializer_fails_the_check_then_is_refused(self):
        path, rows = obj_of(COPY)

        def edit(secs, syms, data):
            s = next(s for s in secs if s.name == ".data" and s.size >= 4)
            self.assertEqual(struct.unpack_from("<i", data, s.ptr)[0], -1)
            struct.pack_into("<i", data, s.ptr, 0)                       # int s_verified = 0
            return secs, syms, bytes(data)
        rep = self.br.build_image(out=self.tmp / "init", tag="init", overlay=SET, rounds=2, own_data=True,
                                  objs=Mutated({path: edit}))
        self.assertGreaterEqual(rep["rounds"][0]["bytes-differ"], 1)    # round 1: our copy differs from retail's
        status = overlay_status(rep)
        self.assertTrue(all(status[int(r["target_rva"], 16)].startswith("refused:datum-differs") for r in rows))
        self.assertTrue(boot_image.image_ok(rep), rep.get("check_bad"))  # round 2: retail's copy, units refused

    def test_without_own_data_a_wrong_initializer_is_refused_at_admission(self):
        path, rows = obj_of(COPY)

        def edit(secs, syms, data):
            s = next(s for s in secs if s.name == ".data" and s.size >= 4)
            struct.pack_into("<i", data, s.ptr, 0)
            return secs, syms, bytes(data)
        r = boot_image.Retail()
        sites, info = boot_image.all_sites(r)
        lost = tuple(int(x, 16) for x in info["lost_pages"])
        live, refused, *_ = self.br.admit(r, sites, lost, rows, Mutated({path: edit}), False, set())
        self.assertEqual(live, [])
        self.assertTrue(all(why.startswith("datum-differs") for _, why in refused))


class FallThrough(unittest.TestCase):
    """A row entered by fall-through cannot move: nothing branches to it."""
    def test_split_initializer_tail_is_pinned(self):
        import types
        import boot_relayout
        r = boot_image.Retail()
        sites = set(boot_image.all_sites(r)[0])
        # 0x7AE8B0: mov ecx, theSystemString; call ctor -- then runs on into the
        # ??__EtheSystemString row at 0x7AE8BA (push dtor; call _atexit; pop ecx; ret)
        tail = types.SimpleNamespace(rva=0x7AE8BA, size=12)
        whole = types.SimpleNamespace(rva=0x7AE8B0, size=22)
        self.assertEqual(boot_relayout.fallthrough_pins(r, [tail], sites), {0x7AE8BA: "falls-through-in"})
        self.assertEqual(boot_relayout.fallthrough_pins(r, [whole], sites), {})



class TruncatedTable(unittest.TestCase):
    """A vtable an object defines shorter than retail's is not owned (own-data boot of
    every row: WWDebug/DebugConstructor's 4-byte ??_7Debug@@6B@ vs retail's 49 slots)."""
    def test_debug_vtable_continues_past_one_slot(self):
        import boot_relayout
        r = boot_image.Retail()
        sites = set(boot_image.all_sites(r)[0])
        self.assertTrue(boot_relayout.table_continues(r, 0x7BE810, 4, sites))
        self.assertFalse(boot_relayout.table_continues(r, 0x7BE810, 196, sites))   # all 49 slots


DEBUG_CTOR = "Code/Libraries/Source/WWVegas/WWDebug/DebugConstructor.cpp"


def debug_rows():
    try:
        rows = boot_image.overlay_rows([DEBUG_CTOR])
        return rows if rows and all(boot_image.build.row_object(r).exists() for r in rows) else []
    except (SystemExit, Exception):
        return []


class StaticFindings(unittest.TestCase):
    """`boot_relayout.py findings`: the relayout findings, from the ledger, retail and
    the rows' objects, without a link or a run."""
    @classmethod
    def setUpClass(cls):
        import boot_relayout
        cls.br = boot_relayout
        cls.r = boot_image.Retail()
        cls.sites = boot_image.all_sites(cls.r)[0]
        cls.starts = boot_image.function_starts()

    def row(self, rva, size, name="f", source="Code/x.c"):
        return {"target_rva": f"0x{rva:08X}", "target_size": str(size), "name": name, "source": source}

    def test_dirtysock_row_cut_before_its_rtc_descriptor_is_flagged(self):
        # _Rva007FD080 was ledgered 210 bytes (relayout-bfme2 finding 3): `lea edx, [0x669622]`
        # reads the /RTC frame descriptor that follows; cc908a06d9 raised it to 235.
        short = self.row(0x669550, 210)
        got = self.br.inline_data_findings(self.r, self.sites, [short], self.starts)
        self.assertEqual([x["check"] for x in got], ["inline-data"])
        self.assertIn(["0x6695fd", "0x669622"], got[0]["fields"])
        whole = self.row(0x669550, 235)
        self.assertEqual(self.br.inline_data_findings(self.r, self.sites, [whole], self.starts), [])

    def test_own_jump_table_and_calls_are_not_inline_data(self):
        rows = boot_image.overlay_rows([f"rva:{JUMP:#x}"])
        self.assertEqual(self.br.inline_data_findings(self.r, self.sites, rows, self.starts), [])

    def test_data_another_row_owns_is_not_flagged(self):
        short = self.row(0x669550, 210)
        tail = self.row(0x669622, 25, "desc")                  # a row owning the descriptor
        self.assertEqual(self.br.inline_data_findings(self.r, self.sites, [short], self.starts, [short, tail]), [])

    @unittest.skipUnless(debug_rows(), "WWDebug objects not built")
    def test_debug_constructor_defines_a_one_slot_vtable(self):
        import link_cycle
        got = self.br.truncated_table_findings(self.r, self.sites, debug_rows(), link_cycle.Objects([]))
        tables = {t[1]: t for f in got for t in f["tables"]}
        self.assertIn("??_7Debug@@6B@", tables)
        rlo, _, n, rn = tables["??_7Debug@@6B@"]
        self.assertEqual((rlo, n), ("0x7be810", 4))
        self.assertGreaterEqual(rn, 140)                       # debug.obj alone defines 35 slots
        self.assertTrue(all(f["check"] == "truncated-table" and "pass_test" not in f for f in got))

    @unittest.skipUnless(ready(), "pilot objects not built")
    def test_pilot_rows_define_no_truncated_table(self):
        import link_cycle
        rows = boot_image.overlay_rows([PILOT])
        self.assertEqual(self.br.truncated_table_findings(self.r, self.sites, rows, link_cycle.Objects([])), [])


class FindingsCli(unittest.TestCase):
    def test_queue_and_exit_codes(self):
        import boot_relayout
        found = {"inline-data": [{"target_rva": "0x00669550", "name": "f", "source": "Code/x.c", "size": 210,
                                  "check": "inline-data", "why": "w"}], "truncated-table": []}
        saved = boot_relayout.static_findings
        try:
            boot_relayout.static_findings = lambda overlay, tables=True: found
            with tempfile.TemporaryDirectory() as d:
                out = Path(d) / "q.json"
                self.assertEqual(boot_relayout.main(["findings", "--out", str(out)]), 0)
                item = json.loads(out.read_text())["items"][0]
                self.assertEqual(item["check"], "inline-data")
                self.assertIn("--overlay rva:0x00669550 --only inline-data --no-write", item["pass_test"])
                self.assertEqual(boot_relayout.main(["findings", "--no-write"]), 1)
                found["inline-data"] = []
                self.assertEqual(boot_relayout.main(["findings", "--no-write"]), 0)
        finally:
            boot_relayout.static_findings = saved


class DatumExtent(unittest.TestCase):
    """datum_extent takes the datum at the referenced symbol (bi.datum_anchor), not the
    one holding symbol + addend; a COMDAT stays whole."""
    def obj(self, flags):
        from types import SimpleNamespace
        s = SimpleNamespace(name=".bss", size=960, ptr=0, flags=flags, relocs=[])
        syms = {0: SimpleNamespace(name="_a", sec=1, value=0, cls=boot_image.EXTERNAL),
                1: SimpleNamespace(name="_b", sec=1, value=640, cls=boot_image.EXTERNAL)}
        return [s], syms, b""

    def test_reference_before_its_symbol(self):
        import boot_relayout
        o = self.obj(0xC0000080)
        q = 640 - 660                                      # _b[-165]: q < 0
        self.assertEqual(boot_relayout.datum_extent(o, 1, q, boot_image.datum_anchor(o, o[1][1], q)), (640, 320))
        self.assertEqual(boot_relayout.datum_extent(o, 1, 600, boot_image.datum_anchor(o, o[1][1], 600)), (640, 320))
        self.assertEqual(boot_relayout.datum_extent(o, 1, q, 960), (960, 0))
        self.assertEqual(boot_relayout.datum_extent(o, 1, q), (q, 0))
        self.assertEqual(boot_relayout.datum_extent(self.obj(0xC0000080 | boot_image.COMDAT), 1, q, 640), (0, 960))


# ---------------------------------------------------------------- fake retail + objects
# A tiny retail image and one object, run through admit (bind_unit + plan_own),
# boot_image.plan, datum_pieces, a model of the linker (build_image's writers, with
# base relocations and `_boot_entry`) and check_semantic, judged by image_ok: no
# toolchain, so biased references can be tested end to end.
RBASE, IBASE, ENTRY, EXPORTS = boot_image.RETAIL_BASE, 0x10000000, 0x10F0, 0x3008
A, B, P = 0x2000, 0x2280, 0x22C0           # A: 640 bytes, B: a 16-slot table, P: a pointer to B - 40
TABLE = struct.pack("<16I", *(0xB0000000 + k for k in range(16)))
LAYOUT = [("_A", A, bytes((7 * k + 3) & 0xFF for k in range(640)), []),
          ("_B", B, TABLE, []),
          ("_P", P, bytes(4), [(0, "_B", -40)])]
# scaffold instruction forms before a 4-byte field: only a plain [disp32] access has a known target
KNOWN, IMM, BASED, INDEXED, LEA = b"\xa1", b"\x68", b"\x8b\x83", b"\x8b\x04\x8d", b"\x8d\x05"


class FakeRetail(boot_image.Retail):
    def __init__(self, secs):
        self.secs, self.entry, self.size_of_image = secs, ENTRY, 0x4000
        self.starts = sorted((v[0], k) for k, v in secs.items())
        dd = [SimpleNamespace(VirtualAddress=0, Size=0) for _ in range(16)]
        dd[0].VirtualAddress, dd[2].VirtualAddress = EXPORTS, 0x3000
        self.pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(DATA_DIRECTORY=dd))

    def imports(self):
        return {}


class FakePE:
    def __init__(self, img, entry, reloc):
        self.img, self.DIRECTORY_ENTRY_IMPORT = img, []
        dd = [SimpleNamespace(VirtualAddress=0, Size=0) for _ in range(16)]
        dd[0].VirtualAddress, dd[2].VirtualAddress = EXPORTS, 0x3000
        dd[5].VirtualAddress, dd[5].Size = reloc
        self.OPTIONAL_HEADER = SimpleNamespace(AddressOfEntryPoint=entry, DATA_DIRECTORY=dd)

    def get_memory_mapped_image(self):
        return bytes(self.img)

    def get_data(self, rva, size):
        return bytes(self.img[rva:rva + size])

    def close(self):
        pass


def fixture(tmp, units, data=LAYOUT, scaffold=(), sec=".data", flags=0xC0000040):
    """(retail, sites, rows, objects, path, data section index, function starts).
    units [(name, rva, code before the field, symbol, addend)]: 16 bytes each, `code
    field ret`; data [(symbol, retail rva, bytes, pointers [(offset, symbol, addend)])],
    laid out in one object section (symbol `sec`: that section's symbol);
    scaffold [(rva, code, symbol, addend)]: retail functions `code field ret` we do
    not provide."""
    import link_cycle
    at = {n: rva for n, rva, *_ in units} | {n: rva for n, rva, *_ in data} | {sec: 0x2000}
    text, dat, sites = bytearray(b"\xcc" * 0x100), bytearray(0x300), []
    sections, syms, obj_data, relocs = [], [], bytearray(), []
    dsec = len(units) + 1
    for k, (name, rva, code, sym, add) in enumerate(units, 1):
        body = (code + struct.pack("<i", add) + b"\xc3").ljust(16, b"\xcc")
        text[rva - 0x1000:rva - 0x1000 + 16] = body
        struct.pack_into("<I", text, rva - 0x1000 + len(code), at[sym] + add + RBASE)
        sites.append(rva + len(code))
        syms.append((name, k, 0, boot_image.EXTERNAL))
        sections.append((f".text$u{k}", boot_image.CODE | boot_image.COMDAT, bytes(body),
                         [(len(code), None, boot_image.DIR32, sym)]))
    if any(u[3] == sec for u in units):
        syms.append((sec, dsec, 0, boot_image.STATIC))
    for name, rva, body, ptrs in data:
        syms.append((name, dsec, len(obj_data), boot_image.EXTERNAL))
        dat[rva - 0x2000:rva - 0x2000 + len(body)] = body
        start = len(obj_data)
        obj_data += body
        for off, sym, add in ptrs:
            struct.pack_into("<I", dat, rva - 0x2000 + off, at[sym] + add + RBASE)
            struct.pack_into("<i", obj_data, start + off, add)
            relocs.append((start + off, None, boot_image.DIR32, sym))
            sites.append(rva + off)
    for rva, code, sym, add in scaffold:
        text[rva - 0x1000:rva - 0x1000 + len(code) + 5] = code + struct.pack("<I", at[sym] + add + RBASE) + b"\xc3"
        sites.append(rva + len(code))
    index = {n: i for i, (n, *_x) in enumerate(syms)}
    sections = [(n, f, b, [(o, index[s], t) for o, _, t, s in rl]) for n, f, b, rl in sections]
    sections.append((sec, flags, bytes(obj_data), [(o, index[s], t) for o, _, t, s in relocs]))
    path = Path(tmp) / "fake.obj"
    boot_image.write_coff(path, sections, syms)
    r = FakeRetail({".text": (0x1000, 0x100, bytes(text)), sec: (0x2000, 0x300, bytes(dat)),
                    ".rsrc": (0x3000, 0x10, bytes(0x10))})
    rows = [{"name": n, "target_rva": f"0x{rva:08X}", "target_size": "16", "source": "Code/fake.cpp",
             "status": "matched", "notes": ""} for n, rva, *_ in units]
    starts = sorted({rva for _, rva, *_x in units} | {rva for rva, *_x in scaffold})
    return SimpleNamespace(r=r, sites=sorted(sites), rows=rows, objs=link_cycle.Objects([]), path=path, dsec=dsec,
                           starts=starts)


def reloc_blocks(fields):
    """A base relocation table (HIGHLOW entries) for the image fields."""
    out, pages = bytearray(), collections.defaultdict(list)
    for f in sorted(fields):
        pages[f & ~0xFFF].append(0x3000 | f & 0xFFF)
    for page, entries in sorted(pages.items()):
        entries += [0] * (len(entries) % 2)
        out += struct.pack("<II", page, 8 + 2 * len(entries)) + struct.pack(f"<{len(entries)}H", *entries)
    return bytes(out)


def model_link(r, pieces, datums, names, shift=None):
    """(image, publics, base relocation directory) as link.exe lays out build_image's
    objects: scaffold and in-place units at their retail addresses (plus `shift`
    {piece start: delta}, or a function of the piece start), owned data after them; a
    name inside owned data is defined in its copy (write_moved), any other in the piece
    holding it."""
    move = shift if callable(shift) else (lambda a: (shift or {}).get(a, 0))
    new = {id(p): p.start + move(p.start) for p in pieces}
    at = 0x8000
    for p, _, _ in datums:
        at = (at + 15) // 16 * 16 + (p.start & 0xF)
        new[id(p)], at = at, at + p.size
    publics = {p.public: new[id(p)] for p in list(pieces) + [d[0] for d in datums]}
    starts = [p.start for p in pieces]

    def addr(name):
        if name in publics:
            return publics[name]
        rva = names[name]
        for p, _, _ in datums:
            if p.start <= rva < p.start + p.size:
                return new[id(p)] + rva - p.start
        p = pieces[bisect.bisect_right(starts, rva) - 1]
        return new[id(p)] + rva - p.start
    img, fields = bytearray(0x10000), []

    def put(p, body, rels):
        n0 = new[id(p)]
        img[n0:n0 + len(body)] = body
        for o, kind, v in rels:
            struct.pack_into("<I", img, n0 + o, (v + IBASE if kind == boot_image.DIR32 else
                                                 v if kind == boot_image.DIR32NB else v - (n0 + o + 4)) & 0xFFFFFFFF)
            if kind == boot_image.DIR32:
                fields.append(n0 + o)
    for p in pieces:
        if p.unit is not None:
            body = p.unit.body
            put(p, body, [(o, k, addr(n) + struct.unpack_from("<i", body, o)[0]) for o, k, n in p.unit.relocs])
        else:
            s0, _, raw = next(v for v in r.secs.values() if v[0] <= p.start < v[0] + v[1])
            put(p, raw[p.start - s0:p.start - s0 + p.size],
                [(s - p.start, k, new[id(t[1])] + t[2] - t[1].start) for s, k, t in p.relocs if t[0] == "piece"])
    for p, body, rels in datums:
        put(p, body, [(o, k, addr(n) + struct.unpack_from("<i", body, o)[0]) for o, k, n in rels])
    publics["_boot_entry"] = addr("_boot_entry")
    blob = reloc_blocks(fields)
    img[0xF000:0xF000 + len(blob)] = blob
    return img, publics, (0xF000, len(blob))


def ea(run, field, delta=0):
    """The image address the field at `field` holds, plus an index `delta` off it."""
    return struct.unpack_from("<I", run.img, field)[0] - IBASE + delta


def write_seen(run, write, read):
    """Whether a store through (field, delta) `write` is what a load through `read` sees."""
    img = bytearray(run.img)
    struct.pack_into("<I", img, ea(run, *write), 0x12345678)
    return struct.unpack_from("<I", img, ea(run, *read))[0] == 0x12345678


class BiasedData(unittest.TestCase):
    """Own-data with references through a biased base (table[i - 10], an end pointer,
    a pointer to table - 40 in data) and retail code we do not provide: the image is
    refused or behaves like retail."""
    def setUp(self):
        import boot_relayout
        self.br = boot_relayout
        self.tmp = tempfile.mkdtemp()
        self.n = 0

    def tearDown(self):
        shutil.rmtree(self.tmp, ignore_errors=True)

    def fixture(self, *a, **k):
        self.n += 1
        d = Path(self.tmp) / str(self.n)
        d.mkdir()
        return fixture(d, *a, **k)

    def patches(self, fx):
        b = boot_image
        return [mock.patch.object(b.build, "row_object", lambda row: fx.path),
                mock.patch.object(b, "identities", lambda r: collections.defaultdict(set)),
                mock.patch.object(b, "export_fields", lambda r: list(getattr(fx, "exports", ()))),
                mock.patch.object(b, "resource_fields", lambda r: list(getattr(fx, "resources", ()))),
                mock.patch.object(b, "crt_pieces", lambda r: {}),
                mock.patch.object(b, "function_starts", lambda: fx.starts)]

    def run_image(self, fx, owned=None, guard=True, shift=None, biased=None):
        """admit -> plan -> datum_pieces -> link -> check_semantic -> image_ok. `owned`
        forces the data owned (as a plan_own without the rules would), keeping the
        bindings; `biased` replaces the biased references the check is given."""
        with contextlib.ExitStack() as stack:
            for p in self.patches(fx):
                stack.enter_context(p)
            live, refused, names, ctx, own, _, nd = self.br.admit(fx.r, fx.sites, (0, 0), fx.rows, fx.objs,
                                                                  True, set())
            if owned is not None:
                own = owned
            usites = sorted(set(fx.sites) | {u.rva + o for u in live for o, k, n in u.relocs
                                             if k == boot_image.DIR32})
            pieces, _ = boot_image.plan(fx.r, usites, live)
            datums = self.br.datum_pieces(fx.r, own, fx.objs, ctx)
            names = dict(names)
            names.update(ctx["need"])
            names["_boot_entry"] = fx.r.entry                     # as build_image
            img, publics, reloc = model_link(fx.r, pieces, datums, names, shift)
        if biased is None:
            biased = ctx.get("biased_refs") if guard else None
        with mock.patch.object(self.br.pefile, "PE", lambda path: FakePE(img, publics["_boot_entry"], reloc)):
            counts, bad, blame = self.br.check_semantic(fx.r, pieces, [], datums, {}, usites, "fake.exe", IBASE,
                                                        publics, biased)
        ok = boot_image.image_ok({"link_exit": 0, "check": counts}) and not counts.get("reloc-bad")
        return SimpleNamespace(live=live, refused=refused, ctx=ctx, owned=own, not_owned=nd, img=img, ok=ok,
                               counts=counts, bad=bad, blame=blame)

    def load(self, run, field, k):
        """mov eax, [field's address + 4k] in the image."""
        return struct.unpack_from("<I", run.img, ea(run, field, 4 * k))[0]

    def test_complete_image_passes(self):
        # nothing biased, nothing retail reaches: B is ours, and production image_ok holds
        fx = self.fixture([("_u2", 0x1020, KNOWN, "_B", 40)], data=LAYOUT[:2])
        run = self.run_image(fx)
        self.assertEqual((set(run.owned), run.ok), ({B}, True))
        self.assertEqual((run.counts["entry-ok"], run.counts["baserelocs-missing"],
                          run.counts["baserelocs-extra"]), (1, 0, 0))
        self.assertEqual(self.load(run, 0x1021, 0), fx.r.u32(B + 40))

    def test_biased_table_after_an_owned_datum(self):
        # A is referenced only by U2, B (writable) also by retail code: the old plan owned A,
        # and table[i - 10] bound to `_boota_<B - 40>`, i.e. into owned A (and the check agreed).
        # (No P here: retail's own pointer to B - 40 would fail an owned A on its own.)
        fx = self.fixture([("_u1", 0x1010, INDEXED, "_B", -40), ("_u2", 0x1020, KNOWN, "_A", 0)],
                          data=LAYOUT[:2], scaffold=[(0x1080, KNOWN, "_B", 0)])
        run = self.run_image(fx)
        self.assertEqual(run.not_owned, collections.Counter({"contains-biased-base": 1,
                                                              "referenced-outside-extent": 1}))
        self.assertEqual((run.owned, run.ok, run.blame), ({}, True, {}))
        self.assertEqual(self.load(run, 0x1013, 10), fx.r.u32(B))           # B[0], as retail
        self.assertEqual(run.ctx["datum_refs"][0x1010], [(B, 64, str(fx.path), fx.dsec, 640, -40, False)])

        # what the old plan did: own A anyway. The binding lands in A's copy, so index 10
        # reads past it; the check fails it on the base guard (without the guard it passed)
        bad = self.run_image(fx, owned={A: (640, str(fx.path), fx.dsec, 0, True)})
        self.assertNotEqual(self.load(bad, 0x1013, 10), fx.r.u32(B))
        self.assertFalse(bad.ok)
        self.assertEqual(bad.blame, {("unit", 0x1010): "field"})
        self.assertTrue(self.run_image(fx, owned={A: (640, str(fx.path), fx.dsec, 0, True)}, guard=False).ok)

    def test_biased_table_alone(self):
        # nothing else references B: the old plan owned B; the checker mapped retail's B - 40
        # through scaffold A and blamed the correct binding moved(B) - 40
        fx = self.fixture([("_u1", 0x1010, INDEXED, "_B", -40)])
        run = self.run_image(fx)
        self.assertEqual(run.not_owned, collections.Counter({"referenced-outside-extent": 1}))
        self.assertEqual((run.owned, run.ok, run.blame), ({}, True, {}))
        self.assertEqual(self.load(run, 0x1013, 10), fx.r.u32(B))

    def test_owned_datum_is_never_bound_across(self):
        # binding against a stale plan (B owned) refuses the unit instead of linking moved(B) - 40
        fx = self.fixture([("_u1", 0x1010, INDEXED, "_B", -40)])
        ctx = {"sites": set(fx.sites), "site_list": fx.sites, "lost": (0, 0), "iat": {},
               "ident": collections.defaultdict(set), "authored": collections.defaultdict(set), "need": {},
               "defer": True, "datum_extent": self.br.datum_extent, "datum_refs": {}, "own": {B: 64}}
        with mock.patch.object(boot_image.build, "row_object", lambda row: fx.path):
            (u,), _ = boot_image.find_units(fx.r, fx.rows, fx.objs)
        self.assertEqual(boot_image.bind_unit(u, fx.r, ctx), "biased-across-owned-data:_B")
        self.assertEqual(ctx["biased_refs"][("unit", 0x1010)], [(0x1013, B - 40, B)])

    def test_end_pointer(self):
        # cmp esi, offset _B + 64 (U1) ends the loop U2 starts at _B + 40; U3 owns P, which
        # starts where B ends
        fx = self.fixture([("_u1", 0x1010, b"\x81\xfe", "_B", 64), ("_u2", 0x1020, KNOWN, "_B", 40),
                           ("_u3", 0x1030, KNOWN, "_P", 0)])
        run = self.run_image(fx)
        self.assertEqual(run.not_owned, collections.Counter({"referenced-outside-extent": 1,
                                                              "contains-biased-base": 1}))
        self.assertEqual((run.owned, run.ok, run.blame), ({}, True, {}))
        self.assertEqual(self.load(run, 0x1021, 0), fx.r.u32(B + 40))       # B[10], as retail
        end, start = (struct.unpack_from("<I", run.img, f)[0] for f in (0x1012, 0x1021))
        self.assertEqual(end - (start - 40), 64)                            # the same copy of B

    def test_pointer_to_a_biased_base_in_owned_data(self):
        # P (owned) holds &B - 40 and A is referenced too: owning A would put P's target in
        # A's copy; A stays retail's, P is ours and still leads to retail's B
        fx = self.fixture([("_u2", 0x1020, KNOWN, "_A", 0), ("_u3", 0x1030, KNOWN, "_P", 0)])
        run = self.run_image(fx)
        self.assertEqual(run.not_owned, collections.Counter({"contains-biased-base": 1}))
        self.assertEqual((set(run.owned), run.ok, run.blame), ({P}, True, {}))
        self.assertEqual(run.ctx["biased_refs"][("datum", P)], [(P, B - 40, B)])
        p = self.load(run, 0x1031, 0) - IBASE                               # [P]: retail B - 40, moved
        self.assertEqual(struct.unpack_from("<I", run.img, p + 40)[0], fx.r.u32(B))

        # A forced owned as well: P's copy now points into A's copy, 40 bytes short of its end,
        # and index 10 off it reads past A. The guard fails P; without it the check passed
        forced = {A: (640, str(fx.path), fx.dsec, 0, True), P: (4, str(fx.path), fx.dsec, 704, True)}
        bad = self.run_image(fx, owned=forced)
        p = self.load(bad, 0x1031, 0) - IBASE
        self.assertNotEqual(struct.unpack_from("<I", bad.img, p + 40)[0], fx.r.u32(B))
        self.assertFalse(bad.ok)
        self.assertEqual(bad.blame, {("datum", P): "field"})
        self.assertTrue(self.run_image(fx, owned=forced, guard=False).ok)

    def test_retail_code_with_an_unknown_bias_keeps_writable_data_shared(self):
        # U2 reads B[10]. Retail code we do not provide holds B through a base of unknown bias
        # (B - 0x44, B - 0x100: table[i - 1] of a struct array; an address constant, [ebx + d],
        # [ecx*4 + d], lea): no window catches every such base, so B stays retail's and U2's
        # store is what retail code loads
        for code in (IMM, BASED, INDEXED, LEA):
            for bias in (-0x44, -0x100):
                with self.subTest(code=code.hex(), bias=bias):
                    fx = self.fixture([("_u2", 0x1020, KNOWN, "_B", 40)], data=LAYOUT[:2],
                                      scaffold=[(0x1080, code, "_B", bias)])
                    run = self.run_image(fx)
                    self.assertEqual(run.not_owned,
                                     collections.Counter({"writable-reachable-from-scaffold": 1}))
                    self.assertEqual((run.owned, run.ok), ({}, True))
                    self.assertTrue(write_seen(run, (0x1021, 0), (0x1080 + len(code), 40 - bias)))
        # If ownership is forced, the semantic check also refuses the split.
        bad = self.run_image(fx, owned={B: (64, str(fx.path), fx.dsec, 640, True)})
        self.assertFalse(bad.ok)
        self.assertGreater(bad.counts["biased-displacement-differs"], 0)
        self.assertFalse(write_seen(bad, (0x1021, 0), (0x1080 + len(LEA), 40 + 0x100)))

    def test_retail_code_past_the_end(self):
        # retail's base B + n + 8 (in P) indexes back into B
        for code in (IMM, BASED):
            with self.subTest(code=code.hex()):
                fx = self.fixture([("_u2", 0x1020, KNOWN, "_B", 40)], scaffold=[(0x1080, code, "_B", 72)])
                run = self.run_image(fx)
                self.assertEqual(run.not_owned, collections.Counter({"writable-reachable-from-scaffold": 1}))
                self.assertEqual((run.owned, run.ok), ({}, True))
                self.assertTrue(write_seen(run, (0x1021, 0), (0x1080 + len(code), 40 - 72)))

    def test_retail_code_with_a_base_outside_the_section(self):
        # a base of unknown bias in the neighbouring section (.rsrc here), or in none, may
        # cross the edge into B
        for add in (0x3004 - B, 0x1F00 - B):
            with self.subTest(target=hex(B + add)):
                fx = self.fixture([("_u2", 0x1020, KNOWN, "_B", 40)], data=LAYOUT[:2], scaffold=[(0x1080, IMM, "_B", add)])
                run = self.run_image(fx)
                self.assertEqual(run.not_owned, collections.Counter({"writable-reachable-from-scaffold": 1}))
                self.assertEqual((run.owned, run.ok), ({}, True))

    def test_known_target_access(self):
        # `mov eax, [B - 0x44]` reads A, exactly: B is still ours. `mov eax, [B + 8]` reads B:
        # B stays retail's, and U2's store to B[2] is what it loads
        fx = self.fixture([("_u2", 0x1020, KNOWN, "_B", 40)], data=LAYOUT[:2], scaffold=[(0x1080, KNOWN, "_B", -0x44)])
        run = self.run_image(fx)
        self.assertEqual((set(run.owned), run.ok), ({B}, True))
        self.assertEqual(ea(run, 0x1081), B - 0x44)                         # retail A
        fx = self.fixture([("_u2", 0x1020, KNOWN, "_B", 40)], data=LAYOUT[:2], scaffold=[(0x1080, KNOWN, "_B", 8)])
        run = self.run_image(fx)
        self.assertEqual(run.not_owned, collections.Counter({"writable-reachable-from-scaffold": 1}))
        self.assertEqual((run.owned, run.ok), ({}, True))
        self.assertTrue(write_seen(run, (0x1021, -32), (0x1081, 0)))

    def test_pointer_in_retail_data_reaches_writable_data(self):
        # P's pointer to B is retail's while P is (banned: retail's copy stays live), and it
        # reaches B; owned, P's retail copy is unreachable and does not count
        data = LAYOUT[:2] + [("_P", P, bytes(4), [(0, "_B", 0)])]
        fx = self.fixture([("_u2", 0x1020, KNOWN, "_B", 40), ("_u3", 0x1030, KNOWN, "_P", 0)], data=data)
        run = self.run_image(fx)
        self.assertEqual((set(run.owned), run.ok), ({B, P}, True))
        with contextlib.ExitStack() as stack:
            for p in self.patches(fx):
                stack.enter_context(p)
            *_, own, _, nd = self.br.admit(fx.r, fx.sites, (0, 0), fx.rows, fx.objs, True, {P})
        self.assertEqual((own, nd), ({}, collections.Counter({"refused-by-check": 1,
                                                               "writable-reachable-from-scaffold": 1})))

    def test_section_symbol_reference(self):
        # `mov eax, [.data + 680]`: the object names no datum, so which one (and the bias) is unknown
        fx = self.fixture([("_u2", 0x1020, KNOWN, ".data", 680)], data=LAYOUT[:2])
        run = self.run_image(fx)
        self.assertEqual(run.ctx["datum_refs"][0x1020], [(B, 64, str(fx.path), fx.dsec, 640, 40, True)])
        self.assertEqual(run.not_owned, collections.Counter({"section-symbol-only": 1}))
        self.assertEqual((run.owned, run.ok), ({}, True))
        self.assertEqual(self.load(run, 0x1021, 0), fx.r.u32(B + 40))

    def test_read_only_address_identity(self):
        # U1 pushes &B and retail code pushes &B (an end pointer too): one copy, one address.
        # A plain load in retail code takes no address: B is ours, and its values equal retail's
        units = [("_u1", 0x1010, IMM, "_B", 0), ("_u2", 0x1020, KNOWN, "_B", 40)]
        ro = {"data": LAYOUT[:2], "sec": ".rdata", "flags": 0x40000040}
        for add in (0, 64):
            with self.subTest(add=add):
                fx = self.fixture(units, scaffold=[(0x1080, IMM, "_B", add)], **ro)
                run = self.run_image(fx)
                self.assertEqual(run.not_owned, collections.Counter({"readonly-address-shared": 1}))
                self.assertEqual((run.owned, run.ok), ({}, True))
                self.assertEqual(ea(run, 0x1011, add), ea(run, 0x1081))
        bad = self.run_image(fx, owned={B: (64, str(fx.path), fx.dsec, 640, False)})
        self.assertFalse(bad.ok)
        self.assertGreater(bad.counts["biased-displacement-differs"], 0)
        self.assertNotEqual(ea(bad, 0x1011, 64), ea(bad, 0x1081))         # what owning it did
        fx = self.fixture(units, scaffold=[(0x1080, KNOWN, "_B", 8)], **ro)
        run = self.run_image(fx)
        self.assertEqual((set(run.owned), run.ok), ({B}, True))
        self.assertEqual(self.load(run, 0x1021, 0), fx.r.u32(B + 40))

    def test_every_biased_field_keeps_its_displacement(self):
        # neither end owned, but in pieces the image moved apart (or in none): failed
        fx = self.fixture([("_u2", 0x1020, KNOWN, "_B", 40)], data=LAYOUT[:2])
        biased = {("unit", 0x1020): [(0x1021, B + 40, 0x3004)]}
        self.assertEqual(self.run_image(fx, owned={}, biased=biased).counts.get("biased-displacement-differs"),
                         None)
        moved = self.run_image(fx, owned={}, biased=biased, shift={0x3000: 0x100})
        self.assertEqual((moved.counts["biased-displacement-differs"], moved.blame), (1, {("unit", 0x1020): "field"}))
        nowhere = self.run_image(fx, owned={}, biased={("unit", 0x1020): [(0x1021, B + 40, 0x5000)]})
        self.assertEqual((nowhere.counts["biased-displacement-differs"], nowhere.ok), (1, False))

    def test_pointer_in_owned_data_binds_the_owned_table(self):
        # datum_pieces resolves P's `_B - 40` to B's datum: owned, it binds moved(B) - 40
        fx = self.fixture([])
        owned = {B: (64, str(fx.path), fx.dsec, 640, True), P: (4, str(fx.path), fx.dsec, 704, True)}
        ctx = {"iat": {}, "ident": {}, "authored": {}, "need": {}}
        (pb, _, _), (pp, body, rels) = self.br.datum_pieces(fx.r, owned, fx.objs, ctx)
        self.assertEqual((pb.start, pp.start, rels, body), (B, P, [(0, boot_image.DIR32, f"_bootd_{B:08X}")],
                                                            struct.pack("<i", -40)))

    def test_content_check_of_a_biased_reference(self):
        # plain overlay (content check, no own-data): `_B - 40` is checked against retail B
        fx = self.fixture([("_u1", 0x1010, INDEXED, "_B", -40)])
        with contextlib.ExitStack() as stack:
            for p in self.patches(fx)[:2]:
                stack.enter_context(p)
            (u,), refused, names = boot_image.overlay_plan(fx.r, fx.sites, (0, 0), fx.rows, fx.objs)
            self.assertEqual((refused, u.bind["content-equal"], names[f"_boota_{B - 40:08X}"]), ([], 1, B - 40))
            # an object whose table differs from retail's (fx.r) in one byte
            changed = [(n, rva, body[:8] + b"\xff" + body[9:] if n == "_B" else body, ptrs)
                       for n, rva, body, ptrs in LAYOUT]
            fx2 = self.fixture([("_u1", 0x1010, INDEXED, "_B", -40)], data=changed)
            stack.enter_context(mock.patch.object(boot_image.build, "row_object", lambda row: fx2.path))
            _, refused, _ = boot_image.overlay_plan(fx.r, fx.sites, (0, 0), fx2.rows, fx2.objs)
        self.assertEqual([why for _, why in refused], ["datum-differs:_B"])

    def test_truncated_table_through_a_biased_reference(self):
        # `mov eax, [ecx*4 + _T - 4]`, _T one slot in the object, four code pointers in retail
        data = [("_X", 0x2000, bytes(4), []), ("_T", 0x2004, bytes(4), [])]
        fx = self.fixture([("_u1", 0x1010, INDEXED, "_T", -4)], data=data, sec=".rdata", flags=0x40000040)
        text = fx.r.secs[".rdata"]
        raw = bytearray(text[2])
        for k in range(4):
            struct.pack_into("<I", raw, 4 + 4 * k, 0x1010 + RBASE)
        fx.r.secs[".rdata"] = (text[0], text[1], bytes(raw))
        sites = sorted(set(fx.sites) | {0x2004 + 4 * k for k in range(4)})
        with mock.patch.object(boot_image.build, "row_object", lambda row: fx.path):
            got = self.br.truncated_table_findings(fx.r, sites, fx.rows, fx.objs, starts=frozenset())
        self.assertEqual([f["tables"] for f in got], [[["0x2004", "_T", 4, 16]]])

    def test_read_only_address_identity_through_any_bias(self):
        # U1 pushes &B; retail code holds B - 0x44 (or B - 0x100, B + 0x70: outside B and its
        # end) and adds the bias back later. Owned, the two sides compare 0x8000 with 0x2280
        units = [("_u1", 0x1010, IMM, "_B", 0), ("_u2", 0x1020, KNOWN, "_B", 40)]
        ro = {"data": LAYOUT[:2], "sec": ".rdata", "flags": 0x40000040}
        for bias in (-0x44, -0x100, 0x70):
            with self.subTest(bias=bias):
                fx = self.fixture(units, scaffold=[(0x1080, IMM, "_B", bias)], **ro)
                run = self.run_image(fx)
                self.assertEqual(run.not_owned, collections.Counter({"readonly-address-shared": 1}))
                self.assertEqual((run.owned, run.ok), ({}, True))
                self.assertEqual(ea(run, 0x1011), ea(run, 0x1081, -bias))
        bad = self.run_image(fx, owned={B: (64, str(fx.path), fx.dsec, 640, False)})
        self.assertFalse(bad.ok)
        self.assertGreater(bad.counts["biased-displacement-differs"], 0)
        self.assertNotEqual(ea(bad, 0x1011), ea(bad, 0x1081, -0x70))       # what owning it did

    def test_scaffold_displacement_needs_one_offset(self):
        # retail code holds .rsrc + 4 and means B[10] (bias B + 40 - 0x3004), as U2 does. With the
        # data section moved 0x100 from .rsrc, U2 reaches 0x23a8 and retail code 0x22a8, and every
        # field still points at the moved copy of its own target
        fx = self.fixture([("_u2", 0x1020, KNOWN, "_B", 40)], data=LAYOUT[:2],
                          scaffold=[(0x1080, IMM, "_B", 0x3004 - B)])
        bias = B + 40 - 0x3004
        same = self.run_image(fx, owned={})
        self.assertEqual((same.ok, same.counts["scaffold-pieces-moved"]), (True, 0))
        self.assertEqual(ea(same, 0x1021), ea(same, 0x1081, bias))
        run = self.run_image(fx, owned={}, shift=lambda a: 0x100 if 0x2000 <= a < 0x2300 else 0)
        self.assertEqual((ea(run, 0x1021), ea(run, 0x1081, bias)), (0x23A8, 0x22A8))
        self.assertGreater(run.counts["scaffold-pieces-moved"], 0)
        self.assertFalse(run.ok)
        self.assertGreater(run.counts["biased-displacement-differs"], 0)
        unguarded = dict(run.counts, **{"scaffold-pieces-moved": 0})
        self.assertFalse(boot_image.image_ok({"link_exit": 0, "check": unguarded}))

    def test_scaffold_movement_guard_with_only_fixed_accesses(self):
        fx = self.fixture([("_u2", 0x1020, KNOWN, "_B", 40)], data=LAYOUT[:2],
                          scaffold=[(0x1080, KNOWN, "_B", 0)])
        run = self.run_image(fx, owned={}, shift=lambda a: 0x100 if 0x2000 <= a < 0x2300 else 0)
        self.assertEqual((run.counts.get("biased-displacement-differs", 0), run.counts["reloc-bad"]), (0, 0))
        self.assertGreater(run.counts["scaffold-pieces-moved"], 0)
        self.assertFalse(run.ok)

    def test_retail_code_based_beyond_an_intervening_section(self):
        # rts.ver lies between .data and .rsrc: a base in .rsrc is two sections from B, and its
        # bias still reaches B
        fx = self.fixture([("_u2", 0x1020, KNOWN, "_B", 40)], data=LAYOUT[:2],
                          scaffold=[(0x1080, IMM, "_B", 0x3004 - B)])
        fx.r = FakeRetail(dict(fx.r.secs, **{"rts.ver": (0x2400, 0x10, bytes(0x10))}))
        run = self.run_image(fx)
        self.assertEqual(run.not_owned, collections.Counter({"writable-reachable-from-scaffold": 1}))
        self.assertEqual((run.owned, run.ok), ({}, True))
        self.assertTrue(write_seen(run, (0x1021, 0), (0x1081, B + 40 - 0x3004)))

    def test_pointer_in_an_owned_read_only_datum(self):
        # R (read-only) holds &W (writable); retail code loads R. R's retail copy stays readable
        # when R is owned, so its pointer still reaches retail's W: neither is owned, and U2's
        # store is what retail code finds through R
        data = [("_R", 0x2000, bytes(4), [(0, "_W", 0)]), ("_W", 0x2100, bytes(range(16)), [])]
        units = [("_u1", 0x1010, KNOWN, "_R", 0), ("_u2", 0x1020, KNOWN, "_W", 0)]
        fx = self.fixture(units, data=data, scaffold=[(0x1080, KNOWN, "_R", 0)], sec=".rdata", flags=0x40000040)
        raw = fx.r.secs[".rdata"][2]
        fx.r = FakeRetail({".text": fx.r.secs[".text"], ".rdata": (0x2000, 0x100, raw[:0x100]),
                           "STLPORT_": (0x2100, 0x200, raw[0x100:]), ".rsrc": fx.r.secs[".rsrc"]})
        run = self.run_image(fx)
        self.assertEqual(run.not_owned, collections.Counter({"readonly-address-shared": 1,
                                                              "writable-reachable-from-scaffold": 1}))
        self.assertEqual((run.owned, run.ok), ({}, True))
        self.assertEqual(struct.unpack_from("<I", run.img, ea(run, 0x1081))[0] - IBASE, ea(run, 0x1021))

    def test_exported_or_resource_referenced_data_stays_retail(self):
        # the export or resource directory holds B: the scaffold keeps it pointing at retail's copy
        for kind in ("exports", "resources"):
            with self.subTest(kind=kind):
                fx = self.fixture([("_u2", 0x1020, KNOWN, "_B", 40)], data=LAYOUT[:2])
                rsrc = bytearray(fx.r.secs[".rsrc"][2])
                struct.pack_into("<I", rsrc, 0xC, B)
                fx.r.secs[".rsrc"] = (0x3000, 0x10, bytes(rsrc))
                setattr(fx, kind, [0x300C])
                run = self.run_image(fx)
                self.assertEqual(run.not_owned, collections.Counter({"writable-reachable-from-scaffold": 1}))
                self.assertEqual((run.owned, run.ok), ({}, True))

    def test_wide_access_from_before_the_datum(self):
        # mov eax, [B - 3], fld qword [B - 4], and movups xmm0, [B - 8]
        # start in A and read B's first bytes (mov reads exactly B[0]).
        for code, add in ((KNOWN, -3), (b"\xdd\x05", -4), (b"\x0f\x10\x05", -8)):
            with self.subTest(code=code.hex()):
                fx = self.fixture([("_u2", 0x1020, KNOWN, "_B", 40)], data=LAYOUT[:2],
                                  scaffold=[(0x1080, code, "_B", add)])
                run = self.run_image(fx)
                self.assertEqual(run.not_owned, collections.Counter({"writable-reachable-from-scaffold": 1}))
                self.assertEqual((run.owned, run.ok), ({}, True))

    def test_wide_access_ending_at_datum_start(self):
        # mov eax, [B - 4] ends where B starts: B is ours
        fx = self.fixture([("_u2", 0x1020, KNOWN, "_B", 40)], data=LAYOUT[:2], scaffold=[(0x1080, KNOWN, "_B", -4)])
        run = self.run_image(fx)
        self.assertEqual((set(run.owned), run.ok), ({B}, True))

    def test_field_at_a_unit_end_is_outside_it(self):
        # a scaffold field at U2's end (0x1030) is retail code's, not U2's
        fx = self.fixture([("_u2", 0x1020, KNOWN, "_B", 40)], data=LAYOUT[:2], scaffold=[(0x1030, b"", "_B", 0)])
        run = self.run_image(fx)
        self.assertEqual(run.not_owned, collections.Counter({"writable-reachable-from-scaffold": 1}))
        self.assertEqual((run.owned, run.ok), ({}, True))


class KnownAccesses(unittest.TestCase):
    """Only a plain [disp32] access names its target; the sweep leaves a function at data."""
    def test_forms(self):
        import boot_relayout
        text = bytearray(b"\xcc" * 0x100)
        forms = [KNOWN, b"\x8b\x0d", b"\xdd\x05", IMM, BASED, INDEXED, LEA, b"\xc7\x05"]
        for k, code in enumerate(forms):
            text[16 * k:16 * k + len(code) + 4] = code + struct.pack("<I", 0x402000)
        text[16 * 7 + 6:16 * 7 + 10] = struct.pack("<I", 0x402000)              # mov [d], imm32: an address
        sites = [0x1000 + 16 * k + len(code) for k, code in enumerate(forms)] + [0x1000 + 16 * 7 + 6]
        r = SimpleNamespace(secs={".text": (0x1000, 0x100, bytes(text))})
        starts = [0x1000 + 16 * k for k in range(len(forms))]
        self.assertEqual(boot_relayout.known_accesses(r, sites, starts, sites),
                         {0x1001: 4, 0x1012: 4, 0x1022: 8, 0x1072: 4})
        # an instruction starting on a site (a table), or straddling one it does not own, is data:
        # the sweep leaves the function, and the load decoded after it is not trusted
        text[0x80:0x8B] = b"\x90\x90" + b"\x90" * 4 + KNOWN + struct.pack("<I", 0x402000)
        text[0xA0:0xAC] = b"\xc7\x45\xf8" + bytes(4) + KNOWN + struct.pack("<I", 0x402000)
        r = SimpleNamespace(secs={".text": (0x1000, 0x100, bytes(text))})
        sweep = boot_relayout.known_accesses
        self.assertEqual(sweep(r, [0x1087, 0x10A8], [0x1080, 0x10A0], [0x1087, 0x10A8]), {0x1087: 4, 0x10A8: 4})
        self.assertEqual(sweep(r, [0x1082, 0x1087], [0x1080], [0x1087]), {})
        self.assertEqual(sweep(r, [0x10A2, 0x10A8], [0x10A0], [0x10A8]), {})

    D = struct.pack("<I", 0x402000)

    def sweep(self, code, sites, starts=(0x1000,), want=None, at=0):
        import boot_relayout
        text = bytearray(b"\xcc" * 0x100)
        text[at:at + len(code)] = code
        r = SimpleNamespace(secs={".text": (0x1000, 0x100, bytes(text))})
        return boot_relayout.known_accesses(r, sites, list(starts), sites if want is None else want)

    def test_access_width_allowlist(self):
        for code, size in ((b"\xdd\x05", 8), (b"\x0f\x10\x05", 16), (b"\x0f\xb6\x05", 1), (b"\xd9\x05", 4)):
            with self.subTest(code=code.hex()):
                self.assertEqual(self.sweep(code + self.D, [0x1000 + len(code)]), {0x1000 + len(code): size})
        # capstone sizes fnsave / frstor (108 bytes), fxsave / fxrstor (512), lds, call far and
        # jmp far (6) as 4; bt / bts select another word through the register
        for code in (b"\xdd\x35", b"\xdd\x25", b"\x0f\xae\x05", b"\x0f\xae\x0d", b"\xc5\x05", b"\xff\x1d",
                     b"\xff\x2d", b"\x0f\xa3\x05", b"\x0f\xab\x05"):
            with self.subTest(code=code.hex()):
                self.assertEqual(self.sweep(code + self.D, [0x1000 + len(code)]), {})

    def test_sweep_stops_where_the_code_ends(self):
        D = self.D
        # C3 A1 <ptr>: past the ret, and no branch lands there
        self.assertEqual(self.sweep(b"\xc3" + KNOWN + D, [0x1002]), {})
        # ret then padding to the next start; code after a ret that a branch before it targets
        self.assertEqual(self.sweep(KNOWN + D + b"\xc3\x90", [0x1001]), {0x1001: 4})
        self.assertEqual(self.sweep(b"\x74\x01\xc3" + KNOWN + D, [0x1004]), {0x1004: 4})
        # an undecodable byte: the function's sweep is out of step, its accesses are dropped
        self.assertEqual(self.sweep(KNOWN + D + b"\x0f\x04", [0x1001]), {})
        # a start one byte late: `8B 84 05 X` at 0x1010 decodes from 0x1011 as `test [X], al`;
        # the sweep before runs over that start
        self.assertEqual(self.sweep(b"\x8b\x84\x05" + D, [0x1013], starts=(0x1000, 0x1011), at=0x10), {})
        self.assertEqual(self.sweep(b"\x8b\x84\x05" + D, [0x1013], starts=(0x1011,), at=0x10), {0x1013: 1})

    def test_branch_rel32_is_never_a_field(self):
        # a site on a call's rel32 is data: the sweep stops before the load after it
        self.assertEqual(self.sweep(b"\xe8" + self.D + KNOWN + self.D, [0x1001, 0x1006], want=[0x1006]), {})
        self.assertEqual(self.sweep(b"\xe8" + self.D + KNOWN + self.D, [0x1006]), {0x1006: 4})

    def test_site_straddled_one_byte_in(self):
        # a site at 0x1001 inside `mov ecx, [d]` (disp32 at 0x1002) is not its field: data
        self.assertEqual(self.sweep(b"\x8b\x0d" + self.D + KNOWN + self.D, [0x1001, 0x1007], want=[0x1007]), {})
        self.assertEqual(self.sweep(b"\x8b\x0d" + self.D + KNOWN + self.D, [0x1007]), {0x1007: 4})
        # A site two bytes into an instruction, rather than at its disp32, also ends the sweep.
        self.assertEqual(self.sweep(b"\x8b\x84\x05" + self.D + KNOWN + self.D, [0x1002, 0x1008],
                                    want=[0x1008]), {})


if __name__ == "__main__":
    unittest.main()


class AddressesAtTheNewBase(unittest.TestCase):
    def test_publics_read_from_a_map_at_the_new_base(self):
        base = boot_image.real_image.IMAGE_BASE
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "a.map"
            path.write_text(f" 0001:00000010       _boot_entry                {base + 0x1010:08x} f   a.obj\n")
            self.assertEqual(boot_image.read_publics(path, base), {"_boot_entry": 0x1010})
