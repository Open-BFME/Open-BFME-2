"""boot_relayout: relaid and own-data overlay images, and controls for their semantic check.

In these images a wrong name or wrong data in an authored object is no longer
hidden by retail's bytes at the old address: the controls mutate one object,
let check-driven admission link it as the object says, and require the image
check to fail (and the next round to refuse what it blamed). Each build links
an image with the VS2003 toolchain (about 30 s); the tests skip without the
pilot's objects.
"""
import json
import shutil
import struct
import sys
import tempfile
import unittest
from pathlib import Path

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

if __name__ == "__main__":
    unittest.main()
