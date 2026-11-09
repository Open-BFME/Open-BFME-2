"""boot_image: retail .reloc parsing and the linked-image equivalence check.

The check tests need a linked image (`python3 tools/boot_image.py link`, about
15 s with the VS2003 toolchain); they skip without one.
"""
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

BOOT = ROOT / "build" / "boot"


def test_objects_digest_binds_source():
    entries = [["build/x.obj", "a" * 64, "Code/A.cpp"]]
    original = boot_image.objects_digest(entries)
    entries[0][2] = "Code/B.cpp"
    assert boot_image.objects_digest(entries) != original


def block(page, offsets):
    entries = [0x3000 | o for o in offsets]
    if len(entries) % 2:
        entries.append(0)
    return struct.pack("<II", page, 8 + 2 * len(entries)) + struct.pack(f"<{len(entries)}H", *entries)


class ParseBlocks(unittest.TestCase):
    def test_stops_at_overwritten_block_and_resumes(self):
        good = block(0x1000, [0x10, 0x20]) + block(0x2000, [0x30])
        junk = b"\xe0\x2d\xa7\x00" * 6                    # import descriptors written over the table
        tail = block(0x9000, [0x40])
        sites, pages, stop = boot_image.parse_blocks(good + junk + tail)
        self.assertEqual(sites, [0x1010, 0x1020, 0x2030])
        self.assertEqual(stop, len(good))
        more, more_pages, _ = boot_image.parse_blocks(good + junk + tail, len(good + junk))
        self.assertEqual((more, more_pages), ([0x9040], [0x9000]))

    def test_rejects_pages_out_of_order(self):
        sites, _, _ = boot_image.parse_blocks(block(0x2000, [1]) + block(0x1000, [2]))
        self.assertEqual(sites, [0x2001])


@unittest.skipUnless((BOOT / "boot.exe").exists() and (BOOT / "boot.json").exists(), "no linked boot image")
class CheckImage(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.r = boot_image.Retail()
        rep = json.loads((BOOT / "boot.json").read_text())
        if rep.get("relayout"):
            raise unittest.SkipTest("build/boot holds a boot_relayout.py image (test_boot_relayout.py checks those)")
        cls.pieces = boot_image.layout(cls.r, rep.get("overlay", {}).get("specs", ()))[0]   # boot_smoke may overlay
        cls.base = int(rep["base"], 16)
        cls.publics = boot_image.read_publics(BOOT / "boot.map", cls.base)
        cls.tmp = Path(tempfile.mkdtemp())

    @classmethod
    def tearDownClass(cls):
        shutil.rmtree(cls.tmp, ignore_errors=True)

    def mutated(self, rva_in_piece, piece, value):
        """A copy of boot.exe with the dword at retail RVA `rva_in_piece` set to value."""
        import pefile
        exe = self.tmp / f"m_{rva_in_piece:x}_{value:x}.exe"     # pefile keeps earlier copies mapped
        shutil.copyfile(BOOT / "boot.exe", exe)
        pe = pefile.PE(str(exe))
        new_rva = self.publics[piece.public] + rva_in_piece - piece.start
        off = pe.get_offset_from_rva(new_rva)
        pe.close()
        data = bytearray(exe.read_bytes())
        data[off:off + 4] = struct.pack("<I", value)
        exe.write_bytes(bytes(data))
        return exe

    def text_piece(self):
        return max((p for p in self.pieces if p.name.startswith(".text") and p.unit is None), key=lambda p: p.size)

    def test_clean_image_is_equivalent(self):
        counts, bad = boot_image.check_image(self.r, self.pieces, BOOT / "boot.exe", self.base, self.publics)
        self.assertEqual((counts.get("reloc-bad", 0), counts["bytes-differ"], bad), (0, 0, []))

    def test_wrong_pointer_is_caught(self):
        p = self.text_piece()
        site, _, tgt = next(x for x in p.relocs if x[2][0] == "piece")
        counts, _ = boot_image.check_image(self.r, self.pieces, self.mutated(site, p, self.base + 0x1234),
                                           self.base, self.publics)
        self.assertEqual(counts.get("reloc-bad"), 1)

    def test_unrelocated_retail_address_is_caught(self):
        p = self.text_piece()
        site, _, tgt = next(x for x in p.relocs if x[2][0] == "piece")
        retail_value = self.r.u32(site)                    # the 0x400000-based address, not moved
        counts, _ = boot_image.check_image(self.r, self.pieces, self.mutated(site, p, retail_value),
                                           self.base, self.publics)
        self.assertEqual(counts.get("reloc-bad"), 1)

    def test_changed_byte_is_caught(self):
        p = self.text_piece()
        sites = {s for s, _, _ in p.relocs}
        a = next(x for x in range(p.start + 0x100, p.start + 0x1000, 4)
                 if not any(x - 3 <= s <= x + 3 for s in sites))
        original = self.r.u32(a)
        counts, _ = boot_image.check_image(self.r, self.pieces, self.mutated(a, p, original ^ 0xFF),
                                           self.base, self.publics)
        self.assertEqual(counts["bytes-differ"], 1)

    def test_wrong_entry_point_is_caught(self):
        import pefile
        exe = self.tmp / "m_entry.exe"
        pe = pefile.PE(str(BOOT / "boot.exe"))
        pe.OPTIONAL_HEADER.AddressOfEntryPoint += 1
        pe.write(str(exe))
        pe.close()
        counts, _ = boot_image.check_image(self.r, self.pieces, exe, self.base, self.publics)
        self.assertEqual(counts["entry-ok"], 0)


def fake_object(sec_name, ptr, payload=b"", relocs=()):
    """(secs, syms, data) as link_cycle.Objects returns them: one 960-byte section
    with external symbols at 0 and 640 and its section symbol."""
    s = SimpleNamespace(name=sec_name, size=960, ptr=ptr, flags=0x40000040, relocs=list(relocs))
    syms = {0: SimpleNamespace(name="_a", sec=1, value=0, cls=boot_image.EXTERNAL),
            1: SimpleNamespace(name="_b", sec=1, value=640, cls=boot_image.EXTERNAL),
            2: SimpleNamespace(name=sec_name, sec=1, value=0, cls=boot_image.STATIC)}
    return [s], syms, bytes(ptr) + payload


class ObjectDatum(unittest.TestCase):
    """The datum a reference means starts at its symbol, not at whatever symbol
    precedes symbol + addend."""
    payload = bytes(k & 0xFF for k in range(960))

    def test_bss_reference_before_its_symbol(self):
        o = fake_object(".bss", 0)
        self.assertEqual(boot_image.object_datum(o, 1, -20, at=640), (640, bytes(320), set()))
        self.assertEqual(boot_image.object_datum(o, 1, -20), (-20, b"", set()))     # was bytes(-640): ValueError

    def test_rdata_reference_before_its_symbol(self):
        o = fake_object(".rdata", 16, self.payload, [(644, 0, boot_image.DIR32)])
        self.assertEqual(boot_image.object_datum(o, 1, -4, at=640), (640, self.payload[640:], {4, 5, 6, 7}))
        self.assertEqual(boot_image.object_datum(o, 1, -4, at=0), (0, self.payload[:640], set()))
        self.assertEqual(boot_image.object_datum(o, 1, -4), (-4, b"", set()))       # was silently b""

    def test_reference_into_the_previous_datum_is_its_symbols(self):
        o = fake_object(".rdata", 16, self.payload)
        y = o[1][1]
        at = boot_image.datum_anchor(o, y, 600)                  # _b - 40
        self.assertEqual(at, 640)
        self.assertEqual(boot_image.object_datum(o, 1, 600, at=at)[:2], (640, self.payload[640:]))
        self.assertEqual(boot_image.object_datum(o, 1, 600)[0], 0)   # the datum holding q: the wrong one

    def test_section_symbol_anchors_at_the_offset(self):
        o = fake_object(".rdata", 16, self.payload)
        self.assertEqual(boot_image.datum_anchor(o, o[1][2], 700), 700)
        self.assertEqual(boot_image.object_datum(o, 1, 700, at=700)[0], 640)

    def test_anchor_outside_the_section_is_empty(self):
        o = fake_object(".rdata", 16, self.payload)
        for at in (960, 4000, -1):
            self.assertEqual(boot_image.object_datum(o, 1, 0, at=at), (at, b"", set()))


class EntryOk(unittest.TestCase):
    """entry-ok: the image entry is `_boot_entry` and that is the moved copy of retail's entry."""
    pieces = [SimpleNamespace(start=0x1000, size=0x100), SimpleNamespace(start=0x1100, size=0x100)]
    new = {0x1000: 0x5000, 0x1100: 0x5200}

    def ok(self, image_entry, publics, entry=0x1120):
        return boot_image.entry_ok(image_entry, entry, self.pieces, lambda p: self.new[p.start], publics)

    def test_moved_entry(self):
        self.assertEqual(self.ok(0x5220, {"_boot_entry": 0x5220}), 1)

    def test_mutated_entry_point(self):
        self.assertEqual(self.ok(0x5221, {"_boot_entry": 0x5220}), 0)

    def test_boot_entry_defined_elsewhere(self):
        # image and map agree (the old, circular test passed) but not on retail's entry
        self.assertEqual(self.ok(0x5224, {"_boot_entry": 0x5224}), 0)
        self.assertEqual(self.ok(0x5220, {}), 0)
        self.assertEqual(self.ok(0x5220, {"_boot_entry": 0x5220}, entry=0x3000), 0)


class EntryInAUnit(unittest.TestCase):
    """An overlay unit holding the entry point defines `_boot_entry`; the scaffold does not."""
    def test_entry_defined_inside_the_unit(self):
        import link_cycle
        r = SimpleNamespace(entry=0x1120, secs={".text": (0x1000, 0x200, bytes(0x200))})
        unit = SimpleNamespace(label="_bootu_00001100", body=b"\xcc" * 0x100, relocs=[])
        pieces = [boot_image.Piece(".text$p000000", 0x1000, 0x100, boot_image.CODE),
                  boot_image.Piece(".text$p000001", 0x1100, 0x100, boot_image.CODE | boot_image.ALIGN_1, unit)]
        names = {"_boot_entry": r.entry, unit.label: 0x1100}
        tmp = Path(tempfile.mkdtemp())
        try:
            _, (scaffold,) = boot_image.write_scaffold(r, pieces, tmp / "scaffold.obj", names)  # was StopIteration
            _, (overlay,) = boot_image.write_overlay(pieces, tmp / "overlay.obj", names)
            defined = {}
            for path in (scaffold, overlay):
                for y in link_cycle.parse_coff(path.read_bytes())[1].values():
                    if y.sec > 0:
                        defined.setdefault(y.name, []).append((path.name, y.value))
        finally:
            shutil.rmtree(tmp, ignore_errors=True)
        self.assertEqual(defined["_boot_entry"], [("overlay.obj", 0x20)])


class FuncletUnits(unittest.TestCase):
    """find_units resolves a funclet pin as build.read_funclet does, never by the first look-alike."""
    TARGET = bytes(range(1, 9))

    def setUp(self):
        import link_cycle
        self.tmp = Path(tempfile.mkdtemp())
        self.obj = self.tmp / "f.obj"
        # $L100: the stale pin (another body now); $L200 and $L300: two bodies equal to retail's
        boot_image.write_coff(self.obj, [(".text$x", boot_image.CODE | boot_image.COMDAT,
                                          b"\x8b\x4d\xf0" + bytes(5) + self.TARGET * 2, [])],
                              [("$L100", 1, 0, 3), ("$L200", 1, 8, 3), ("$L300", 1, 16, 3)])
        self.objs = link_cycle.Objects([])
        text = bytearray(0x100)
        text[0x10:0x18] = self.TARGET
        self.r = SimpleNamespace(secs={".text": (0x1000, 0x100, bytes(text))})

    def tearDown(self):
        shutil.rmtree(self.tmp, ignore_errors=True)

    def find(self, pin="$L100", located=None, candidates=(), scoped=False):
        row = {"name": "uw_00001010", "target_rva": "0x00001010", "target_size": "8", "source": "Code/x.cpp",
               "status": "matched", "notes": f"gen-funclet;object-symbol={pin};parent=?f@@YAXXZ"}
        self.calls = []

        def locate(row, path, target):
            self.calls.append("located")
            if isinstance(located, BaseException):
                raise located
            self.assertEqual((path, target), (self.obj, self.TARGET))
            return located

        def cands(path, row, target):
            self.calls.append("candidates")
            return list(candidates)
        b = boot_image.build
        with mock.patch.object(b, "row_object", lambda row: self.obj), \
                mock.patch.object(b, "located_funclet", locate), \
                mock.patch.object(b, "funclet_candidates", cands), \
                mock.patch.object(b, "scoped_funclet_collision", lambda row: scoped):
            units, refused = boot_image.find_units(self.r, [row], self.objs)
        return [(u.rva, u.off, u.size) for u in units], [why for _, why in refused]

    def test_stale_pin_resolves_to_the_eh_proven_label(self):
        self.assertEqual(self.find(located="$L200", candidates=["$L300"]), ([(0x1010, 8, 8)], []))
        self.assertEqual(self.calls, ["located"])

    def test_pin_that_still_holds_is_kept(self):
        self.assertEqual(self.find(pin="$L300", candidates=["$L200"]), ([(0x1010, 16, 8)], []))
        self.assertNotIn("candidates", self.calls)

    def test_unique_candidate(self):
        self.assertEqual(self.find(candidates=["$L200"]), ([(0x1010, 8, 8)], []))

    def test_tie_is_refused(self):
        self.assertEqual(self.find(candidates=["$L200", "$L300"]), ([], ["funclet-ambiguous:2"]))

    def test_nothing_holds_it(self):
        # read_funclet's last resort, "the body that label names now" ($L100), is never taken
        self.assertEqual(self.find(), ([], ["funclet-unresolved"]))
        self.assertEqual(self.find(pin="$L999"), ([], ["funclet-unresolved"]))

    def test_scoped_collision_needs_eh_proof(self):
        self.assertEqual(self.find(pin="$L200", candidates=["$L200"], scoped=True), ([], ["funclet-scoped-unlocated"]))
        self.assertNotIn("candidates", self.calls)
        self.assertEqual(self.find(located="$L200", scoped=True), ([(0x1010, 8, 8)], []))

    def test_eh_proof_failure_is_refused_with_its_cause(self):
        self.assertEqual(self.find(pin="$L200", located=SystemExit("uw_00001010 (Code/x.cpp): parent EH graph\nmore")),
                         ([], ["funclet-unresolved:uw_00001010 (Code/x.cpp): parent EH graph"]))
        self.assertEqual(self.find(pin="$L200", located=ValueError("symbol not found in object: ?f@@YAXXZ")),
                         ([], ["funclet-unresolved:symbol not found in object: ?f@@YAXXZ"]))

    def test_environment_fault_is_not_a_refusal(self):
        with self.assertRaises(FileNotFoundError):            # e.g. no retail image for eh_verify
            self.find(located=FileNotFoundError("game.dat"))
        with self.assertRaises(SystemExit) as e:              # names no row: git, the toolchain
            self.find(located=SystemExit("git rev-parse failed"))
        self.assertEqual(str(e.exception), "git rev-parse failed")

    def rows(self, n):
        return [{"name": f"uw_{k}", "target_rva": "0x00001010", "target_size": "8", "source": "Code/x.cpp",
                 "status": "matched", "notes": "gen-funclet;object-symbol=$L100;parent=?f@@YAXXZ"} for k in range(n)]

    def find_all(self, rows, cause):
        b = boot_image.build

        def broken(row, path, target):
            raise SystemExit(cause(row))
        with mock.patch.object(b, "row_object", lambda row: self.obj), \
                mock.patch.object(b, "located_funclet", broken), \
                mock.patch.object(b, "scoped_funclet_collision", lambda row: False):
            return boot_image.find_units(self.r, rows, self.objs)

    def test_every_funclet_failing_is_loud(self):
        # at quorum, whatever the causes
        rows = self.rows(boot_image.FUNCLET_QUORUM)
        with self.assertRaises(SystemExit) as e:
            self.find_all(rows, lambda row: f"{row['name']}: cause {row['name'][3:]}")
        self.assertIn("none of 10 funclet rows", str(e.exception))
        # two or more, all for one cause (the row's own names aside)
        with self.assertRaises(SystemExit) as e:
            self.find_all(self.rows(2), lambda row: f"{row['name']} ({row['source']}): parent EH graph")
        self.assertIn("none of 2 funclet rows", str(e.exception))
        # two causes, or one row: per-row trouble
        units, refused = self.find_all(self.rows(2), lambda row: f"{row['name']}: cause {row['name'][3:]}")
        self.assertEqual([why for _, why in refused], ["funclet-unresolved:uw_0: cause 0",
                                                       "funclet-unresolved:uw_1: cause 1"])
        units, refused = self.find_all(self.rows(1), lambda row: f"{row['name']}: parent EH graph")
        self.assertEqual([why for _, why in refused], ["funclet-unresolved:uw_0: parent EH graph"])
        # one readable row among them is per-row trouble, not a broken environment
        ok = dict(rows[0], notes="gen-funclet;object-symbol=$L200;parent=?f@@YAXXZ")
        b = boot_image.build

        def some(row, path, target):
            if "$L200" in row["notes"]:
                return "$L200"
            raise SystemExit(row["name"] + ": parent EH graph")
        with mock.patch.object(b, "row_object", lambda row: self.obj), \
                mock.patch.object(b, "located_funclet", some), \
                mock.patch.object(b, "scoped_funclet_collision", lambda row: False):
            units, refused = boot_image.find_units(self.r, rows[1:] + [ok], self.objs)
        self.assertEqual((len(units), len(refused)), (1, 9))

    def test_quorum_counts_every_failure(self):
        # ten scoped rows no EH proof locates, or unresolved and ambiguous rows mixed: none placed
        b = boot_image.build
        rows = self.rows(boot_image.FUNCLET_QUORUM)

        def run(located, scoped, candidates=()):
            with mock.patch.object(b, "row_object", lambda row: self.obj), \
                    mock.patch.object(b, "located_funclet", located), \
                    mock.patch.object(b, "funclet_candidates", lambda path, row, target: list(candidates)), \
                    mock.patch.object(b, "scoped_funclet_collision", lambda row: scoped):
                return boot_image.find_units(self.r, rows, self.objs)
        with self.assertRaises(SystemExit) as e:
            run(lambda row, path, target: None, True)
        self.assertIn("funclet-scoped-unlocated 10", str(e.exception))

        def mixed(row, path, target):
            if int(row["name"][3:]) % 2:
                raise SystemExit(f"{row['name']}: cause {row['name'][3:]}")
            return None
        with self.assertRaises(SystemExit) as e:
            run(mixed, False, ["$L200", "$L300"])
        self.assertIn("funclet-ambiguous 5", str(e.exception))
        rows = rows[1:]                                    # below quorum: per-row trouble
        self.assertEqual(len(run(lambda row, path, target: None, True)[1]), 9)

    def test_quorum_counts_missing_funclet_objects(self):
        rows = self.rows(boot_image.FUNCLET_QUORUM)
        with mock.patch.object(boot_image.build, "row_object", lambda row: None):
            with self.assertRaises(SystemExit) as e:
                boot_image.find_units(self.r, rows, self.objs)
        self.assertIn("no-object 10", str(e.exception))

    def test_scoped_label_must_be_local(self):
        # the EH-proven label of a scoped collision, defined external or twice, is not the TU's own
        import link_cycle
        body = b"\x8b\x4d\xf0" + bytes(5) + self.TARGET * 2
        for syms in ([("$L200", 1, 8, boot_image.EXTERNAL)], [("$L200", 1, 8, 3), ("$L200", 1, 16, 3)]):
            with self.subTest(syms=syms):
                boot_image.write_coff(self.obj, [(".text$x", boot_image.CODE | boot_image.COMDAT, body, [])], syms)
                self.objs = link_cycle.Objects([])
                self.assertEqual(self.find(located="$L200", scoped=True), ([], ["funclet-scoped-not-local"]))


PILOT = "Code/Libraries/Source/profile/"


def pilot_ready():
    """The pilot's objects are built and the toolchain is here."""
    try:
        rows = boot_image.overlay_rows([PILOT])
        boot_image.build.vc71_root()
    except (SystemExit, Exception):
        return False
    return bool(rows) and all(boot_image.build.row_object(r).exists() for r in rows)


class MutatedObjects:
    """link_cycle.Objects, but one object comes back changed by `edit(secs, syms, data)`."""
    def __init__(self, path, edit):
        import link_cycle
        self.inner, self.path, self.edit = link_cycle.Objects([]), Path(path), edit

    def get(self, p):
        o = self.inner.get(p)
        if o is not None and Path(p) == self.path and self.edit:
            secs, syms, data = o
            o = self.inner.cache[Path(p)] = self.edit(secs, syms, bytearray(data))
            self.edit = None
        return o


@unittest.skipUnless(pilot_ready(), "pilot objects not built (tools/build.py on Code/Libraries/Source/profile)")
class OverlayPlan(unittest.TestCase):
    """Admission: a unit replaces retail only when its bytes and every relocation agree."""
    @classmethod
    def setUpClass(cls):
        cls.r = boot_image.Retail()
        cls.sites, info = boot_image.all_sites(cls.r)
        cls.lost = tuple(int(x, 16) for x in info["lost_pages"])
        cls.rows = boot_image.overlay_rows([PILOT])

    def plan(self, objs=None):
        units, refused, names = boot_image.overlay_plan(self.r, self.sites, self.lost, self.rows, objs)
        return {u.rva: u for u in units}, {int(x["target_rva"], 16): why for x, why in refused}, names

    def unit_of(self, rva):
        units, _, _ = self.plan()
        return units[rva]

    def test_pilot_rows_are_all_admitted(self):
        units, refused, names = self.plan()
        self.assertEqual({why.split(":")[0] for why in refused.values()}, {"folded-into"})
        self.assertEqual(refused, {0x6C74C0: "folded-into:?Delete@ProfileResultFileCSV@@UAEXXZ"})   # one ICF body
        self.assertEqual(sum(len(u.rows) for u in units.values()) + 2, len(self.rows))
        self.assertEqual(names["?AddProfile@ProfileHighLevel@@SA?AVId@1@PBD00HH@Z"], 0x6C6500)
        # AddProfile's call to the ProfileId constructor the pilot has not matched binds to retail's, by its pin
        self.assertEqual(names["??0ProfileId@@QAE@PBD00HH@Z"], 0x6C5C60)

    def test_wrong_relocation_target_is_refused(self):
        stop = self.unit_of(0x6C57B0)                        # Profile::StopRange calls ProfileAllocMemory
        secs, syms, _ = stop.obj

        def edit(secs, syms, data):
            s = secs[stop.sec - 1]
            other = next(i for i, y in syms.items() if y.name == "?ProfileReAllocMemory@@YAPAXPAXI@Z")
            s.relocs = [(o, other if syms[i].name == "?ProfileAllocMemory@@YAPAXI@Z" else i, k)
                        for o, i, k in s.relocs]
            return secs, syms, bytes(data)
        _, refused, _ = self.plan(MutatedObjects(stop.path, edit))
        self.assertEqual(refused.get(0x6C57B0), "identity-differs:?ProfileReAllocMemory@@YAPAXPAXI@Z")

    def test_wrong_byte_is_refused(self):
        start = self.unit_of(0x6C5940)                       # Profile::StartRange
        masked = {o + k for o, _, _ in start.relocs for k in range(4)}
        at = next(o for o in range(8, start.size) if o not in masked)

        def edit(secs, syms, data):
            data[secs[start.sec - 1].ptr + start.off + at] ^= 0x01
            return secs, syms, bytes(data)
        _, refused, _ = self.plan(MutatedObjects(start.path, edit))
        self.assertEqual(refused.get(0x6C5940), "bytes-differ")


@unittest.skipUnless(pilot_ready(), "pilot objects not built (tools/build.py on Code/Libraries/Source/profile)")
class OverlayCheck(unittest.TestCase):
    """The linked overlay image: authored pieces checked field by field like the scaffold."""
    @classmethod
    def setUpClass(cls):
        cls.tmp = Path(tempfile.mkdtemp())
        cls.base = boot_image.real_image.IMAGE_BASE
        cls.rep = boot_image.build_image(cls.base, cls.tmp, "ov", [PILOT])
        cls.r = boot_image.Retail()
        cls.pieces = boot_image.layout(cls.r, [PILOT])[0]
        cls.publics = boot_image.read_publics(cls.tmp / "ov.map", cls.base)

    @classmethod
    def tearDownClass(cls):
        shutil.rmtree(cls.tmp, ignore_errors=True)

    def mutated(self, rva, piece, value):
        import pefile
        exe = self.tmp / f"m_{rva:x}_{value:x}.exe"
        shutil.copyfile(self.tmp / "ov.exe", exe)
        pe = pefile.PE(str(exe))
        off = pe.get_offset_from_rva(self.publics[piece.public] + rva - piece.start)
        pe.close()
        data = bytearray(exe.read_bytes())
        data[off:off + 4] = struct.pack("<I", value)
        exe.write_bytes(bytes(data))
        return exe

    def authored(self, rva):
        return next(p for p in self.pieces if p.unit is not None and p.start == rva)

    def test_overlay_links_and_is_equivalent(self):
        ov, chk = self.rep["overlay"], self.rep["check"]
        self.assertTrue(boot_image.image_ok(self.rep), self.rep.get("check_bad"))
        self.assertEqual(ov["rows_overlaid"] + ov["rows_folded_into_an_overlaid_body"], ov["rows_requested"])
        self.assertEqual(chk["authored-bytes-equal"], ov["bytes"])
        self.assertEqual((chk.get("authored-bytes-differ"), chk.get("authored-reloc-bad", 0)), (0, 0))
        self.assertTrue(any(line.endswith("overlay.obj") and "?StartRange@Profile@@SAXPBD@Z" in line
                            for line in (self.tmp / "ov.map").read_text(encoding="latin-1").splitlines()))

    def test_split_objects_link_the_same(self):
        """Past MAX_SECTIONS the scaffold and the overlay split into several objects."""
        saved, boot_image.MAX_SECTIONS = boot_image.MAX_SECTIONS, 20
        try:
            rep = boot_image.build_image(self.base, self.tmp / "split", "sp", [PILOT])
        finally:
            boot_image.MAX_SECTIONS = saved
        self.assertTrue(boot_image.image_ok(rep), rep.get("check_bad"))
        self.assertEqual(rep["check"]["authored-bytes-equal"], self.rep["check"]["authored-bytes-equal"])
        self.assertGreater(len(list((self.tmp / "split").glob("overlay*.obj"))), 1)

    def test_authored_wrong_relocation_target_is_caught(self):
        p = self.authored(0x6C5940)
        site, _, tgt = next(x for x in p.relocs if x[2][0] == "piece")
        good = self.publics[tgt[1].public] + tgt[2] - tgt[1].start + self.base
        counts, _ = boot_image.check_image(self.r, self.pieces, self.mutated(site, p, good + 0x10), self.base,
                                           self.publics)
        self.assertEqual((counts.get("authored-reloc-bad"), counts.get("reloc-bad")), (1, 1))

    def test_authored_wrong_byte_is_caught(self):
        p = self.authored(0x6C5940)
        masked = {s + k for s, _, _ in p.relocs for k in range(-3, 4)}
        a = next(x for x in range(p.start + 8, p.start + p.size - 4) if x not in masked)
        counts, _ = boot_image.check_image(self.r, self.pieces, self.mutated(a, p, self.r.u32(a) ^ 0xFF), self.base,
                                           self.publics)
        self.assertEqual(counts["authored-bytes-differ"], 1)


class Bisect(unittest.TestCase):
    """boot_smoke --bisect: deterministic halving to the rows that fail alone."""
    def setUp(self):
        try:
            import boot_smoke
        except (ImportError, ValueError, OSError):
            self.skipTest("boot_smoke needs Win32")
        self.bs = boot_smoke
        self.rows = [{"target_rva": f"0x{0x1000 + 0x10 * k:08X}", "name": f"f{k}", "source": "Code/x.cpp",
                      "target_size": "16"} for k in range(37)]
        self.runs = []

    def fake_smoke(self, bad):
        def smoke(a, rows=None, tag="boot"):
            got = {r["name"] for r in rows}
            self.runs.append(len(got))
            return {"outcome": "crash-at-x" if bad(got) else "reached-menu"}
        return smoke

    def run_bisect(self, bad, executed=None):
        saved = self.bs.smoke
        self.bs.smoke = self.fake_smoke(bad)
        try:
            return self.bs.bisect_rows(None, self.rows, executed)
        finally:
            self.bs.smoke = saved

    def test_one_guilty_row_is_found(self):
        guilty, steps = self.run_bisect(lambda names: "f23" in names)
        self.assertEqual([r["name"] for r in guilty], ["f23"])
        self.assertLessEqual(len(steps), 2 * 6)

    def test_only_executed_units_are_candidates(self):
        guilty, _ = self.run_bisect(lambda names: "f5" in names, executed={0x1050, 0x1060})
        self.assertEqual([r["name"] for r in guilty], ["f5"])
        self.assertEqual(self.runs[0], 1)

    def test_an_interaction_is_reported_together(self):
        guilty, _ = self.run_bisect(lambda names: {"f2", "f30"} <= names)
        self.assertEqual(len(guilty), 37)           # neither half fails alone: the whole set is the finding

    def test_queue_items_carry_the_rows(self):
        tmp = Path(tempfile.mkdtemp())
        try:
            path = self.bs.write_queue(self.rows[3:4], "crash-at-x", tmp / "q.json")
            items = json.loads(path.read_text())["items"]
            self.assertEqual((items[0]["target_rva"], items[0]["name"], items[0]["size"]), ("0x00001030", "f3", 16))
        finally:
            shutil.rmtree(tmp, ignore_errors=True)


class FocusLieAndMenu(unittest.TestCase):
    """boot_smoke: the WM_ACTIVATEAPP arm is found by its bytes; the menu bar decides reached-menu."""
    def setUp(self):
        try:
            import boot_smoke
        except (ImportError, ValueError, OSError):
            self.skipTest("boot_smoke needs Win32")
        self.bs = boot_smoke

    def test_arm_found_in_retail_and_not_in_a_copy_without_it(self):
        exe = boot_image.build.EXE
        if not Path(exe).exists():
            self.skipTest("no retail image")
        self.assertEqual(self.bs.focus_arm_rva(exe), 0x19A5)
        tmp = Path(tempfile.mkdtemp())
        try:
            data = bytearray(Path(exe).read_bytes())
            at = data.index(bytes.fromhex("837D10000F95C03A05"))
            data[at + 3] = 1                               # cmp [ebp+10h], 1: no longer the arm
            (tmp / "g.dat").write_bytes(bytes(data))
            self.assertIsNone(self.bs.focus_arm_rva(tmp / "g.dat"))
        finally:
            shutil.rmtree(tmp, ignore_errors=True)

    def test_menu_bar_needs_the_green_buttons(self):
        from PIL import Image, ImageDraw
        img = Image.new("RGB", (640, 360), (90, 110, 140))           # a shell-map-like frame
        self.assertLess(self.bs.menu_bar(img), self.bs.MENU_BAR)
        ImageDraw.Draw(img).rectangle((0, 322, 639, 348), fill=(60, 120, 60))   # the button bar
        self.assertGreater(self.bs.menu_bar(img), self.bs.MENU_BAR)


if __name__ == "__main__":
    unittest.main()
