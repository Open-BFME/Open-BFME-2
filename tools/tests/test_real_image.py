"""real_image: receipt, check, fail-closed address map and crash map of a linked image.

Synthetic retail/image pairs stand in for exit_link's image until a real one exists; on
srv1 the census link's stubbed image (base 0x400000, no relocations) and a 32-bit Wine
DLL are also used when present."""
import hashlib
import json
import struct
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import real_image as ri  # noqa: E402

RB, IB = 0x400000, 0x10000000
F1, F2, F3, MISS, MISS2 = "?f1@@YAXXZ", "?f2@@YAXXZ", "?f3@@YAXXZ", "?missing@@YAXXZ", "?missing2@@YAXXZ"


class FakeSections:
    def __init__(self, base, blobs, relocs=(), code=((0x1000, 0x3000),)):
        self.base, self.blobs, self.relocs, self.ranges = base, dict(blobs), set(relocs), code

    def read(self, rva, n):
        for at, b in self.blobs.items():
            if at <= rva and rva + n <= at + len(b):
                return b[rva - at:rva - at + n]
        raise ri.RealImageError(f"{rva:#x} outside")

    def u32(self, rva):
        return struct.unpack("<I", self.read(rva, 4))[0]

    def code(self, rva):
        return any(a <= rva < a + n for a, n in self.ranges)

    def section(self, rva):
        return ".text" if self.code(rva) else ".data"


def f1_body(base, g, g2, here, f2, miss):
    """push ebp; mov ebp, esp; mov eax, [g]; call f2; mov byte [g2], 1; call miss; pop ebp; ret.
    Returns (bytes, offsets of the DIR32 dwords)."""
    b = bytearray(b"\x55\x8B\xEC")
    sites = [len(b) + 1]
    b += b"\xA1" + struct.pack("<I", base + g)
    b += b"\xE8" + struct.pack("<i", f2 - (here + len(b) + 5))
    sites.append(len(b) + 2)
    b += b"\xC6\x05" + struct.pack("<I", base + g2) + b"\x01"
    b += b"\xE8" + struct.pack("<i", miss - (here + len(b) + 5))
    b += b"\x5D\xC3"
    return bytes(b.ljust(0x20, b"\xCC")), sites


F2_BODY = b"\x33\xC0\xC3".ljust(0x10, b"\xCC")
MISS_BODY = b"\xB8\x01\x00\x00\x00\xC3".ljust(0x10, b"\xCC")


def build(tamper=None, call_to=None, stub_shared=True, drop_reloc=False, dup_name=False, copy_rel=False):
    """A retail side (F1 0x1000, F2 0x1020, MISS 0x1040, MISS2 0x1050, a copy of F2 at 0x1060; globals 0x5000,
    0x5008) and an image at IB laid out differently (F2 0x2000, F1 0x2100, the missing
    functions as int3 stubs at 0x2200, globals 0x8000, 0x8010), with its map."""
    r1, rs = f1_body(RB, 0x5000, 0x5008, 0x1000, 0x1020, 0x1040)
    retail = FakeSections(RB, {0x1000: r1 + F2_BODY + b"\xCC" * 0x10 + MISS_BODY + MISS_BODY + F2_BODY,
                                0x5000: bytes(0x20)},
                          code=((0x1000, 0x1000),))
    target = {"f2": 0x2000, "f3": 0x2300}[call_to or "f2"]
    i1, isites = f1_body(IB, 0x8000, 0x8010, 0x2100, target, 0x2200)
    if copy_rel:                                       # retail's call operand, unchanged, in the moved body
        i1 = i1[:9] + r1[9:13] + i1[13:]
    if tamper is not None:
        i1 = i1[:tamper] + bytes([i1[tamper] ^ 0xFF]) + i1[tamper + 1:]
    stub = b"\xCC" * 0x10
    image = FakeSections(IB, {0x2000: F2_BODY.ljust(0x100, b"\xCC") + i1.ljust(0x100, b"\xCC") +
                              stub.ljust(0x100, b"\xCC") + b"\x31\xC0\xC3".ljust(0x10, b"\xCC"),
                              0x8000: bytes(0x20)},
                         relocs={0x2100 + s for s in isites[(1 if drop_reloc else 0):]},
                         code=((0x2000, 0x1000),))
    lines = [" Preferred load address is 10000000", "", " entry point at        0001:00001000", ""]
    syms = [(0x2000, F2, "a.obj"), (0x2100, F1, "a.obj"), (0x2200, MISS, "stubs.obj"), (0x2300, F3, "b.obj"),
            (0x8000, "?g@@3HA", "a.obj"), (0x8010, "?g2@@3EA", "a.obj")]
    if stub_shared:
        syms.append((0x2200, MISS2, "stubs.obj"))
    if dup_name:
        syms.append((0x2300, F1, "b.obj"))
    for va, name, obj in sorted(syms):
        lines.append(f" 0001:{va - 0x1000:08x}       {name:<26} {IB + va:08x} f   {obj}")
    m = ri.MapFile("\n".join(lines))
    rows = ri.Rows(rows=[(0x1000, 0x20, F1, "Code/A.cpp"), (0x1020, 0x10, F2, "Code/A.cpp"),
                         (0x1040, 0x10, MISS, "Code/M.cpp"), (0x1050, 0x10, MISS2, "Code/M.cpp")])
    return ri.RealImage("exit.exe", {"stubbed": [MISS, MISS2] if stub_shared else [MISS], "kind": "diagnostic"},
                        m, image=image, retail=ri.Retail(retail, sites={0x1000 + s for s in rs}), rows=rows)


class AddressMap(unittest.TestCase):
    def test_function_start_and_mid_function_map_by_name(self):
        img = build()
        self.assertEqual(img.map_code(0x1000), IB + 0x2100)
        self.assertEqual(img.map_code(0x100D), IB + 0x210D)            # mid-function: + its offset
        self.assertEqual(img.map_code(0x1021), IB + 0x2001)

    def test_globals_map_through_retail_references(self):
        img = build()
        self.assertEqual(img.map_data(0x5000), IB + 0x8000)
        self.assertEqual(img.map_data(0x5008), IB + 0x8010)
        move = img.rva_map()
        self.assertEqual(move(0x5008), 0x8010)
        self.assertEqual(move(0x1003), 0x2103)

    def test_changed_byte_refuses_mid_function_address(self):
        img = build(tamper=1)
        with self.assertRaisesRegex(ri.RealImageError, "differs"):
            img.map_code(0x100D)
        with self.assertRaises(KeyError):                             # game_smoke's convention
            img.rva_map()(0x1003)

    def test_call_to_another_function_refuses(self):
        img = build(call_to="f3")                                     # f3: a different body
        with self.assertRaisesRegex(ri.RealImageError, "branch at"):
            img.map_code(0x1000)

    def test_missing_relocation_refuses(self):
        with self.assertRaisesRegex(ri.RealImageError, "relocated dwords differ"):
            build(drop_reloc=True).map_code(0x1000)

    def test_unreferenced_or_unrowed_address_refuses(self):
        img = build()
        with self.assertRaisesRegex(ri.RealImageError, "no retail reference"):
            img.map_data(0x5010)
        with self.assertRaisesRegex(ri.RealImageError, "no functions.csv row"):
            img.map_code(0x1800)

    def test_ambiguous_name_refuses(self):
        with self.assertRaisesRegex(ri.RealImageError, "2 map symbol"):
            build(dup_name=True).map_code(0x1000)

    def test_globals_inherit_the_body_check(self):                   # the only reference is in a changed body
        with self.assertRaises(ri.RealImageError):
            build(tamper=1).map_data(0x5000)

    def test_folded_callee_with_equal_body_is_accepted_once(self):
        img = build()
        img.rows = ri.Rows(rows=img.rows.rows + [(0x1060, 0x10, "?f2copy@@YAXXZ", "Code/A.cpp")])
        f1 = bytearray(img.retail.img.blobs[0x1000])                  # retail calls the copy
        struct.pack_into("<i", f1, 9, 0x1060 - (0x1000 + 13))
        img.retail.img.blobs[0x1000] = bytes(f1)
        self.assertEqual(img.map_code(0x1000), IB + 0x2100)
        self.assertEqual(img.folds, {("?f2copy@@YAXXZ", F2)})


def build_refs(values):
    """Retail functions ?r<k>@@YAXXZ at 0x1000 + 0x10k, each `mov eax, [0x5000]; ret`; the
    image's copies at 0x2000 + 0x10k read values[k] (an image VA) instead."""
    names = [f"?r{k}@@YAXXZ" for k in range(len(values))]
    body = lambda v: (b"\xA1" + struct.pack("<I", v) + b"\xC3").ljust(0x10, b"\xCC")
    retail = FakeSections(RB, {0x1000: b"".join(body(RB + 0x5000) for _ in values), 0x5000: bytes(0x20)},
                          code=((0x1000, 0x1000),))
    image = FakeSections(IB, {0x2000: b"".join(body(v) for v in values), 0x8000: bytes(0x20)},
                         relocs={0x2000 + 0x10 * k + 1 for k in range(len(values))}, code=((0x2000, 0x1000),))
    m = ri.MapFile("\n".join([" Preferred load address is 10000000"] + [
        f" 0001:{0x1000 + 0x10 * k:08x}       {n:<26} {IB + 0x2000 + 0x10 * k:08x} f   a.obj" for k, n in enumerate(names)]))
    rows = ri.Rows(rows=[(0x1000 + 0x10 * k, 0x10, n, "Code/A.cpp") for k, n in enumerate(names)])
    return ri.RealImage("exit.exe", {"stubbed": []}, m, image=image,
                        retail=ri.Retail(retail, sites={0x1000 + 0x10 * k + 1 for k in range(len(values))}), rows=rows)


class ReviewFindings(unittest.TestCase):
    """Codex's review of the first real-image path (2026-11-05), each through real code."""

    def test_unchanged_branch_operand_into_the_wrong_place_is_refused(self):     # finding 1
        img = build(copy_rel=True)                    # bytes equal retail's, so the call lands at +0x20
        with self.assertRaisesRegex(ri.RealImageError, "branch at"):
            img.map_code(0x1000)
        self.assertEqual(build().map_code(0x1000), IB + 0x2100)

    def test_every_reference_votes(self):                                      # finding 2
        self.assertEqual(build_refs([IB + 0x8000] * 9).map_data(0x5000), IB + 0x8000)
        with self.assertRaisesRegex(ri.RealImageError, "2 different addresses"):
            build_refs([IB + 0x8000] * 8 + [IB + 0x8010]).map_data(0x5000)

    def test_ambiguous_crash_names_no_alias(self):                             # finding 3
        w = build().where(IB + 0x2200)
        self.assertIsNone(w["map_symbol"])
        self.assertIsNone(w["stubbed_name"])
        self.assertIsNone(w["retail_rva"])
        self.assertEqual(sorted(w["retail_rva_candidates"]), ["0x1040", "0x1050"])
        self.assertEqual(ri.crash_name(w), hex(IB + 0x2200))

    def test_caller_must_match_retail_before_its_offset_is_used(self):         # finding 3
        w = build(tamper=1).where(IB + 0x2200, IB + 0x2100 + 25)
        self.assertIsNone(w["stubbed_name"])
        self.assertIn("differs from retail", w["stubbed_by"])
        self.assertIsNone(w["retail_rva"])

    def test_relocated_code_address_must_reach_the_same_function(self):
        img = build()
        f1 = bytearray(img.retail.img.blobs[0x1000])  # retail's first dword now points at F2 (code)
        struct.pack_into("<I", f1, 4, RB + 0x1020)
        img.retail.img.blobs[0x1000] = bytes(f1)
        with self.assertRaisesRegex(ri.RealImageError, "code address"):
            img.map_code(0x1000)                      # the image's dword still points at data


class GameDat(unittest.TestCase):
    """The game folder's game.dat must be the image under test, proven by hash."""

    def test_installed_copy_is_proven(self):
        with tempfile.TemporaryDirectory() as d:
            src = Path(d) / "retail.dat"
            src.write_bytes(b"MZ retail")
            self.assertEqual(ri.install_game_dat(src, d), hashlib.sha256(b"MZ retail").hexdigest())

    def test_a_copy_that_left_another_image_is_refused(self):
        from unittest import mock
        with tempfile.TemporaryDirectory() as d:
            src = Path(d) / "retail.dat"
            src.write_bytes(b"MZ retail")
            (Path(d) / "game.dat").write_bytes(b"MZ our linked image")    # what the queue left behind
            with mock.patch("shutil.copyfile"), self.assertRaisesRegex(ri.RealImageError, "not "):
                ri.install_game_dat(src, d)


class Crashes(unittest.TestCase):
    def test_crash_in_a_function_names_symbol_and_retail_row(self):
        w = build().where(IB + 0x2103)                # mov eax, [g]: +3 in both bodies
        self.assertEqual((w["map_symbol"], w["stubbed_name"], w["retail_rva"]), (F1, None, "0x1003"))
        self.assertEqual(w["crash_operands"], [{"retail": hex(RB + 0x5000), "retail_section": ".data",
                                                "image": hex(IB + 0x8000), "image_section": ".data",
                                                "image_symbol": "?g@@3HA+0x0"}])

    def test_crash_in_a_body_that_differs_before_it_maps_no_retail_rva(self):
        # 2026-11-05 receipt: _WinMainCRTStartup+0xa9 reported as retail's entry + 0xa9,
        # though our entry body is not retail's; the offset means nothing in retail then.
        w = build(tamper=1).where(IB + 0x2108)        # the body differs at +1, the crash is at +8
        self.assertIsNone(w["retail_rva"])
        self.assertEqual((w["map_symbol"], w["retail_row"], w["offset"]), (F1, F1, "0x8"))
        self.assertIn("differs from retail's before the crash", w["retail_rva_why"][0])
        self.assertEqual(ri.crash_name(w), F1)

    def test_a_difference_after_the_crash_does_not_matter(self):
        img = build(tamper=0x19)                      # pop ebp, after the crash at +3
        with self.assertRaises(ri.RealImageError):
            img.map_code(0x1000)                      # the whole body does not map
        self.assertEqual(img.where(IB + 0x2103)["retail_rva"], "0x1003")

    def test_a_crash_inside_an_instruction_maps_no_retail_rva(self):
        w = build().where(IB + 0x2105)
        self.assertIsNone(w["retail_rva"])
        self.assertIn("not an instruction start", w["retail_rva_why"][0])

    def test_shared_stub_is_named_through_the_caller(self):
        img = build()
        ret = IB + 0x2100 + 25                                       # after F1's call to the stub
        w = img.where(IB + 0x2200, ret)
        self.assertEqual(w["stubbed_name"], MISS)
        self.assertIn("caller", w["stubbed_by"])
        self.assertEqual(w["retail_rva"], "0x1040")

    def test_shared_stub_without_a_return_address_is_not_guessed(self):
        w = build().where(IB + 0x2200)
        self.assertIsNone(w["stubbed_name"])
        self.assertEqual(sorted(w["names_at_symbol"]), sorted([MISS, MISS2]))

    def test_single_stub_is_named_by_the_map(self):
        w = build(stub_shared=False).where(IB + 0x2200)
        self.assertEqual((w["stubbed_name"], w["stubbed_by"]), (MISS, "map symbol"))

    def test_crash_fields_find_the_return_address_on_the_stack(self):
        img = build()
        img.img.pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(SizeOfImage=0x9000))
        loaded = 0x20000000                                          # loaded away from the preferred base
        words = [0x1234, loaded + 0x2100 + 25, loaded + 0x2100 + 3]
        c = ri.crash_fields(img, loaded + 0x2200, loaded, words, "0x80000003")
        self.assertEqual(c["return_address_image"], hex(IB + 0x2119))
        self.assertEqual(c["stubbed_name"], MISS)
        self.assertEqual(ri.crash_name(c), MISS)
        self.assertEqual(c["loaded_at"], hex(loaded))

    def test_an_address_outside_the_image_is_not_moved_by_a_rebase(self):
        # A null call on a rebased image read crash-at-0xf800000: eip 0 mapped through the rebase's delta.
        img = build()
        img.img.pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(SizeOfImage=0x9000))
        for loaded, address in ((0x800000, 0), (0x20000000, 0x7BBBB0B7), (0x20000000, 0x20000000 - 1), (0x20000000, 0x20009000)):
            c = ri.crash_fields(img, address, loaded, [loaded + 0x2100 + 25], "0xc0000005")
            self.assertEqual(ri.crash_name(c), hex(address))
            self.assertEqual((c["map_symbol"], c["retail_rva"], c["note"]), (None, None, "outside the image"))
            self.assertEqual(c["return_address_image"], hex(IB + 0x2119))

    def test_the_image_ends_are_still_the_image(self):
        img = build()
        img.img.pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(SizeOfImage=0x9000))
        for offset in (0, 0x8FFF):
            self.assertEqual(ri.crash_fields(img, 0x20000000 + offset, 0x20000000, [], "0xc0000005")["address_image"], hex(IB + offset))


GOOD = {"machine": 0x14C, "base": IB, "relocs_stripped": False, "reloc_sites": 9, "export_names": 1964,
        "resource_dir": 0x55C8, "entry": IB + 0x1000, "map_base": IB, "map_entry": IB + 0x1000,
        "imports": {"shell32.dll!SHGetSpecialFolderPathW": 1, "kernel32.dll!GetVersion": 1,
                    "kernel32.dll!GetVersionExA": 1}}
RECEIPT = {"kind": "real", "commit": "a" * 40, "base": "0x10000000", "image_sha256": "0" * 64,
           "map_sha256": "1" * 64, "stubbed": [], "exports_requested": 1964, "rsrc": True, "fixed_no": True}


class Check(unittest.TestCase):
    def test_good_image_passes(self):
        self.assertEqual(ri.judge(GOOD, RECEIPT), [])

    def test_each_defect_is_refused(self):
        cases = {"machine": 0x8664, "base": RB, "relocs_stripped": True, "reloc_sites": 0, "export_names": 10,
                 "resource_dir": 0, "map_base": RB, "map_entry": IB + 4,
                 "imports": {"kernel32.dll!GetVersion": 1, "kernel32.dll!GetVersionExA": 1}}
        for k, v in cases.items():
            self.assertTrue(ri.judge(GOOD | {k: v}, RECEIPT), k)

    def test_retail_base_is_refused_even_when_the_receipt_says_so(self):
        self.assertTrue(any("retail" in p for p in ri.judge(GOOD | {"base": RB}, RECEIPT | {"base": "0x400000"})))

    def test_receipt_flags(self):
        self.assertTrue(ri.judge(GOOD, RECEIPT | {"fixed_no": False}))
        self.assertTrue(ri.judge(GOOD, RECEIPT | {"rsrc": False}))

    def test_receipt_problems(self):
        self.assertEqual(ri.receipt_problems(RECEIPT), [])
        self.assertTrue(ri.receipt_problems(RECEIPT | {"stubbed": ["?x@@YAXXZ"]}))      # real, yet stubbed
        self.assertEqual(ri.receipt_problems(RECEIPT | {"kind": "diagnostic", "stubbed": ["?x"]}), [])
        for bad in ({"kind": "retail"}, {"commit": "abc"}, {"base": "zz"}, {"image_sha256": "x"}):
            self.assertTrue(ri.receipt_problems(RECEIPT | bad), bad)

    def test_hashes_must_match_the_receipt(self):
        with tempfile.TemporaryDirectory() as d:
            d = Path(d)
            (d / "exit.exe").write_bytes(b"MZ image")
            (d / "exit.map").write_text(" Preferred load address is 10000000\n")
            rec = RECEIPT | {"image_sha256": hashlib.sha256(b"MZ image").hexdigest(),
                             "map_sha256": hashlib.sha256((d / "exit.map").read_bytes()).hexdigest()}
            (d / "image_receipt.json").write_text(json.dumps(rec))
            self.assertEqual(ri.read_receipt(d / "exit.exe")[0]["kind"], "real")
            (d / "exit.exe").write_bytes(b"MZ other")
            with self.assertRaisesRegex(ri.RealImageError, "image_sha256 differs"):
                ri.read_receipt(d / "exit.exe")
            (d / "exit.map").unlink()
            with self.assertRaisesRegex(ri.RealImageError, "missing"):
                ri.read_receipt(d / "exit.exe")


class Receipts(unittest.TestCase):
    def test_results(self):
        self.assertEqual(ri.result_of("crash-at-?f@@YAXXZ"), "crashed")
        self.assertEqual(ri.result_of("exit-0x1"), "exited")
        self.assertEqual(ri.result_of("debugger-error"), "inconclusive")
        self.assertEqual(ri.result_of("reached-menu"), "reached-menu")

    def test_fields(self):
        r = ri.receipt_fields("boot_smoke", "boot", "no-picture", {"image_kind": "real", "base": "0x10000000"},
                              None, "2026-11-05T00:00:00Z", 12.4)
        self.assertEqual((r["tool"], r["mode"], r["result"], r["image_kind"], r["seconds"]),
                         ("boot_smoke", "boot", "no-picture", "real", 12))

    def test_map_parsing(self):
        m = build().map
        self.assertEqual((m.base, m.entry), (IB, (1, 0x1000)))
        self.assertEqual(sorted(m.names_at(IB + 0x2200)), sorted([MISS, MISS2]))
        self.assertEqual(m.holding(IB + 0x2105), (IB + 0x2100, 5))
        self.assertEqual(ri.object_name("Code/GameEngine/Source/Common/DispDwordFieldGetters.cpp"),
                         "^code_^game^engine_^source_^common_^disp^dword^field^getters")


CENSUS = Path.home() / "bfme2-ops/swarm/game-queue/fixtures/census-20261104"


@unittest.skipUnless((CENSUS / "selected.map").exists(), "srv1's census image fixture")
class CensusImage(unittest.TestCase):
    """A real link of our objects (census 2026-11-04, stubbed, base 0x400000, no relocations)."""

    @classmethod
    def setUpClass(cls):
        m = ri.MapFile((CENSUS / "selected.map").read_text(encoding="latin-1"))
        cls.img = ri.RealImage(CENSUS / "selected.exe", {"stubbed": []}, m, need_relocs=False)

    def test_functions_and_mid_function_addresses_map(self):
        import game_smoke
        for name in ("GameEngine::update", "InitRandom", "Debug::AssertDone/exit", "handleCRCMessage"):
            va = self.img.map_rva(game_smoke.RVA[name])
            self.assertTrue(self.img.img.code(va - self.img.base), name)

    def test_globals_map(self):
        import game_smoke
        got = {n: self.img.map_rva(game_smoke.RVA[n]) for n in ("TheGameLogic", "crcSkip:objects", "crcSkip:ai")}
        self.assertEqual(len(set(got.values())), 3)

    def test_a_real_defect_is_refused(self):                         # fs:[0] linked as an address there
        with self.assertRaisesRegex(ri.RealImageError, "differs"):
            self.img.map_rva(0x23CB2C)                               # GameLogic::getCRC


WINE_DLL = Path.home() / "bfme2-retail/prefix64/drive_c/windows/syswow64/version.dll"


@unittest.skipUnless(WINE_DLL.exists(), "a 32-bit relocatable DLL from srv1's Wine prefix")
class Rebase(unittest.TestCase):
    def test_only_relocated_dwords_move_by_the_delta(self):
        old = ri.Sections(WINE_DLL)
        with tempfile.TemporaryDirectory() as d:
            new_base = old.base + 0x01000000
            new = ri.Sections(ri.rebased_copy(SimpleNamespace(exe=WINE_DLL), new_base, Path(d) / "r.dll"))
        self.assertEqual(new.base, new_base)
        self.assertTrue(old.relocs)
        for va, size, raw, _, _ in old.secs:
            nraw = new.read(va, size)
            diff = {va + o for o in range(size) if raw[o] != nraw[o]}
            near = {s + k for s in old.relocs for k in range(4)}
            self.assertLessEqual(diff, near)
        for s in list(old.relocs)[:200]:
            self.assertEqual((new.u32(s) - old.u32(s)) & 0xFFFFFFFF, 0x01000000)

    def test_retail_base_is_refused(self):
        with self.assertRaises(ri.RealImageError):
            ri.rebased_copy(SimpleNamespace(exe=WINE_DLL), RB, Path("x.dll"))


if __name__ == "__main__":
    unittest.main()
