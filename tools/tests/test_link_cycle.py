"""link_cycle: the order/quarantine plan and the per-row measure's rules.

Each rule research 31 / the round-2 review found missing has a positive control
(the pilot's rule passes it, this one fails it) and a negative control."""
import collections
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_cycle as lc

B = lc.BASE


def test_order_name_drops_one_underscore():
    assert lc.order_name("_fill_00001000") == "fill_00001000"
    assert lc.order_name("__ehhandler$x") == "_ehhandler$x"
    assert lc.order_name("?f@@YAXXZ") == "?f@@YAXXZ"


def test_drift_names_the_unit_that_grew():
    items = [(0x1000, "_a", "unit"), (0x1010, "_fill_00001010", "fill"), (0x1020, "_b", "unit")]
    exact = {"_a": 0x1000, "_fill_00001010": 0x1010, "_b": 0x1020}
    assert lc.drift_culprits(items, exact) == ([], 0)
    grew = dict(exact, _fill_00001010=0x1014, _b=0x1024)          # _a linked 4 bytes longer
    assert lc.drift_culprits(items, grew)[0] == ["_a"]
    padded = dict(exact, _b=0x1030)                              # filler 'grew': _b's alignment padded it
    assert lc.drift_culprits(items, padded)[0] == ["_b"]


def test_fillers_cover_every_gap_split_at_cuts_and_groups():
    placed = [{"starts": [0x1010], "size": 0x10}]
    chunks = lc.filler_chunks(placed, [0x1008, 0x1030], 0x1000, 0x40)
    assert chunks == [(0x1000, 0x1008), (0x1008, 0x1010), (0x1020, 0x1030), (0x1030, 0x1040)]
    assert lc.region(0x75B45F) == ".text" and lc.region(0x75B460) == ".text$x"


def _unit(i, start, head="_f", cls=lc.EXTERNAL, secname=".text", flags=0x60100020, size=0x10):
    return {"id": i, "obj": f"o{i}.obj", "sec": 1, "secname": secname, "size": size, "comdat": True,
            "flags": flags, "rows": [{"size": size}], "starts": [start], "head": head, "head_cls": cls}


def test_plan_reasons():
    us = [_unit(0, 0x1000, "_a"), _unit(1, 0x1008, "_b"), _unit(2, 0x1020, "_c", cls=lc.STATIC),
          _unit(3, 0x1040, "_d", flags=0x60000020 | (5 << 20)),     # ALIGN_16 at 0x1040: fine
          _unit(4, 0x1058, "_e", flags=0x60000020 | (5 << 20)),     # ALIGN_16 at 0x1058: refused
          _unit(5, 0x75B460, "_x"), _unit(6, 0x1080, "_q")]
    placed, reasons, _ = lc.plan_order(us, {"_q"}, 0x1000, 0x7B8CE2)
    assert [u["head"] for u in placed] == ["_a", "_d"]
    assert us[1]["why"] == "overlaps previous unit"
    assert us[2]["why"] == "static COMDAT"
    assert us[4]["why"] == "retail start violates section alignment"
    assert us[5]["why"].startswith("section group mismatch")
    assert us[6]["why"].startswith("quarantined")


def test_closure_fillers_are_not_leaves():
    ok = {"a": True, "b": True, "c": True, "d": False}
    edges = {"a": {"b"}, "b": {("fill", 0x1000)}, "c": {"c"}, "e": {"d"}}
    # pilot rule (fillers are leaves): a and b close. Positive control: they no longer do.
    assert lc.greatest_closure(ok, edges, bad_targets=()) == {"a", "b", "c"}
    assert lc.greatest_closure(ok, edges) == {"c"}                  # c: a self-cycle stays closed
    assert lc.greatest_closure({"x": True, "y": True}, {"x": {"y"}}) == {"x", "y"}   # negative control


def test_credit_counts_unique_bytes():
    assert lc.unique_bytes([(0, 10), (5, 15), (20, 30), (20, 30)]) == 25


def test_import_def_entries_follow_retail_names():
    retail = {"CreateFileA": {"kernel32.dll"}, "free": {"msvcr71.dll"}, "?x@@YAXXZ": {"msvcp71.dll"}}
    names = {"__imp__CreateFileA@28", "__imp__free", "__imp_?x@@YAXXZ", "__imp__NotRetail@4"}
    entries, missing = lc.import_def_entries(names, retail)
    assert entries == {"kernel32.dll": ["CreateFileA@28"], "msvcr71.dll": ["free"], "msvcp71.dll": ["?x@@YAXXZ"]}
    assert missing == ["__imp__NotRetail@4"]
    assert lc.import_name("GetUserNameA@8") == "GetUserNameA" and lc.import_name("free") == "free"


def test_coff_round_trip_with_absolute_symbol(tmp_path):
    p = lc.write_coff(tmp_path / "a.obj", [(".text$x", 0x60101020, b"\x90\xc3", 2)],
                      [("_f", 1, 0, lc.EXTERNAL), ("__except_list", -1, 0, lc.EXTERNAL)])
    secs, syms = lc.parse_coff(p.read_bytes())
    assert secs[0].name == ".text$x" and secs[0].size == 2 and secs[0].sel == 2
    by = {y.name: y for y in syms.values()}
    assert by["__except_list"].sec == -1 and by["_f"].sec == 1


def test_hardcoded_operand_needs_no_relocation():
    code = bytes.fromhex("8b0db0a3c200") + bytes.fromhex("c3")   # mov ecx,[0xc2a3b0]; ret
    assert lc.hardcoded_operands(code, B + 0x1000, set(), B + 0x1000, B + 0xADA000) == [2]
    assert lc.hardcoded_operands(code, B + 0x1000, {2, 3, 4, 5}, B + 0x1000, B + 0xADA000) == []
    # an opcode byte plus an immediate's low bytes (25 ff ff 00 = 0x00FFFF25) is not an operand
    masked = bytes.fromhex("25ffff00000d00000780c3")             # and eax,0xffff; or eax,0x80070000
    assert lc.hardcoded_operands(masked, B + 0x1000, set(), B + 0x1000, B + 0xADA000) == []
    small = bytes.fromhex("b810000000c3")                           # mov eax,0x10: not an address
    assert lc.hardcoded_operands(small, B + 0x1000, set(), B + 0x1000, B + 0xADA000) == []


# ---- a synthetic image for the measure ------------------------------------------------
def _sec(idx, name, size, relocs=(), ptr=0):
    s = lc.Sec()
    s.idx, s.name, s.size, s.ptr, s.flags, s.relocs, s.sel = idx, name, size, ptr, 0, list(relocs), 0
    return s


def _sym(i, name, sec, value=0, cls=lc.EXTERNAL):
    y = lc.Sym()
    y.i, y.name, y.value, y.sec, y.cls = i, name, value, sec, cls
    return y


class FakeObjs(lc.Objects):
    def __init__(self, table):
        super().__init__([])
        self.table = table

    def lookup(self, objbase, name):
        o = self.table.get(objbase)
        return (o, self.defined(o)[0][name]) if o and name in self.defined(o)[0] else None


def _measure(I, R, items, allsyms, objs=None, pins=None, ledger_starts=None, pub=None, pubobj=None):
    m = lc.Measure.__new__(lc.Measure)
    m.I, m.R, m.lbase, m.rbase = I, R, B, B
    m.isecs = {".text": (0x1000, 0x1000), ".data": (0x3000, 0x1000), ".stubd": (0x5000, 0x100)}
    m.ltext = m.isecs[".text"]
    m.items, m.istarts = sorted(items), [t[0] for t in sorted(items)]
    m.allsyms, m.avas = sorted(allsyms), [s[0] for s in sorted(allsyms)]
    m.pub, m.stat, m.pubobj = pub or {}, {}, pubobj or {}
    m.pins, m.objs, m.ledger_starts = pins or {}, objs or FakeObjs({}), ledger_starts or {}
    m.rimports, m.limports = {}, {}
    m.fwd, m.back = collections.defaultdict(set), collections.defaultdict(set)
    m.datum_memo, m.twins, m.eh = {}, {}, collections.Counter()
    return m


def _put(buf, at, raw):
    buf[at:at + len(raw)] = raw


def test_data_reference_checks_content_not_only_the_map():
    """Research 31: a datum that maps 1:1 but whose bytes differ from retail used to count."""
    I, R = bytearray(0x6000), bytearray(0x6000)
    _put(I, 0x3000, b"Default\0")
    _put(R, 0x3100, b"Default \0")                         # retail's literal is longer
    data_sec = _sec(2, ".rdata", 8)
    obj = ([_sec(1, ".text", 8), data_sec], {0: _sym(0, "_s", 2, 0, lc.STATIC)}, b"")
    m = _measure(I, R, [], [(0x3000, "_s", "a.obj")])
    fails, _, pinned = m.data_ref(0x3000, 0x3100, "_s", obj[1][0], obj, 0)
    assert fails == ["data-content:_s"] and not pinned
    _put(R, 0x3100, b"Default\0")                          # negative control
    m = _measure(I, R, [], [(0x3000, "_s", "a.obj")])
    assert m.data_ref(0x3000, 0x3100, "_s", obj[1][0], obj, 0)[0] == []


def test_data_reference_checks_the_pinned_address():
    I, R = bytearray(0x6000), bytearray(0x6000)
    _put(I, 0x3000, b"\1\2\3\4")
    _put(R, 0x3100, b"\1\2\3\4")
    obj = ([_sec(1, ".data", 4)], {0: _sym(0, "_g", 1)}, b"")
    m = _measure(I, R, [], [(0x3000, "_g", "a.obj")], pins={"_g": 0x3200})
    assert m.data_ref(0x3000, 0x3100, "_g", obj[1][0], obj, 0)[0] == ["data-pin:_g"]
    m = _measure(I, R, [], [(0x3000, "_g", "a.obj")], pins={"_g": 0x3100})
    assert m.data_ref(0x3000, 0x3100, "_g", obj[1][0], obj, 0) == ([], set(), True)
    m = _measure(I, R, [], [(0x3000, "_g", "a.obj")], pins={"_g": B + 0x3100})   # pinned as a VA
    assert m.data_ref(0x3000, 0x3100, "_g", obj[1][0], obj, 0) == ([], set(), True)


def test_repeated_section_names_are_all_kept():
    secs = lc.SectionList([(".data", 0x3000, 0x100), (".CRT", 0x4000, 0x10), (".data", 0x5000, 0x10)])
    assert secs[".data"] == (0x3000, 0x100)
    assert secs.name_at(0x3010) == ".data" and secs.name_at(0x5004) == ".data" and secs.name_at(0x6000) == "outside"


def test_communal_global_is_sized_by_its_reference():
    I, R = bytearray(0x6000), bytearray(0x6000)
    ref = ([_sec(1, ".text", 8)], {0: _sym(0, "?TheX@@3PAVX@@A", 0)}, b"")            # an extern
    definer = ([_sec(1, ".text", 8)], {0: _sym(0, "?TheX@@3PAVX@@A", 0, value=4)}, b"")  # COMMON, 4 bytes
    objs = FakeObjs({})
    objs.cache = {Path("d.obj"): definer}
    m = _measure(I, R, [], [(0x3000, "?TheX@@3PAVX@@A", "other.obj")], pub={"?TheX@@3PAVX@@A": 0x3000},
                 pubobj={"?TheX@@3PAVX@@A": "other.obj"}, objs=objs)
    assert m.data_ref(0x3000, 0x3100, "?TheX@@3PAVX@@A", ref[1][0], ref, 0)[0] == []
    _put(R, 0x3102, bytes.fromhex('01'))  # retail holds a non-zero byte there
    m = _measure(I, R, [], [(0x3000, "?TheX@@3PAVX@@A", "other.obj")], pub={"?TheX@@3PAVX@@A": 0x3000},
                 pubobj={"?TheX@@3PAVX@@A": "other.obj"}, objs=objs)
    assert m.data_ref(0x3000, 0x3100, "?TheX@@3PAVX@@A", ref[1][0], ref, 0)[0] == ["data-content:?TheX@@3PAVX@@A"]


def test_alternatename_alias_resolves_through_the_real_definition():
    I, R = bytearray(0x6000), bytearray(0x6000)
    _put(I, 0x3000, bytes.fromhex('07000000'))
    _put(R, 0x3100, bytes.fromhex('07000000'))
    definer = ([_sec(1, ".data", 4)], {0: _sym(0, "?Real@@3HA", 1)}, b"")
    ref = ([_sec(1, ".text", 8)], {0: _sym(0, "?Alias@@3HA", 0)}, b"")
    m = _measure(I, R, [], [(0x3000, "?Alias@@3HA", "d.obj"), (0x3000, "?Real@@3HA", "d.obj")],
                 objs=FakeObjs({"d.obj": definer}), pub={"?Alias@@3HA": 0x3000, "?Real@@3HA": 0x3000},
                 pubobj={"?Alias@@3HA": "d.obj", "?Real@@3HA": "d.obj"})
    assert m.data_ref(0x3000, 0x3100, "?Alias@@3HA", ref[1][0], ref, 0)[0] == []
    _put(R, 0x3100, bytes.fromhex('08'))  # the content check still applies
    m.datum_memo.clear()
    assert m.data_ref(0x3000, 0x3100, "?Alias@@3HA", ref[1][0], ref, 0)[0] == ["data-content:?Alias@@3HA"]


def test_data_stub_and_vtable_code_pointer():
    I, R = bytearray(0x6000), bytearray(0x6000)
    m = _measure(I, R, [], [])
    assert m.data_ref(0x5004, 0x3100, "_x", None, None, 0)[0] == ["data-stub:_x"]
    # a vtable slot (DIR32) must translate through the unit/filler holding its target
    _put(I, 0x3000, struct.pack("<I", B + 0x1800))
    _put(R, 0x3100, struct.pack("<I", B + 0x1900))
    vt = ([_sec(1, ".rdata", 4, relocs=[(0, 0, lc.DIR32)])], {0: _sym(0, "??_7X@@6B@", 1)}, b"")
    items = [(0x1800, 0x1810, 0x1900, ("fill", 0x1900))]
    m = _measure(I, R, items, [(0x3000, "??_7X@@6B@", "a.obj")])
    fails, edges, _ = m.data_ref(0x3000, 0x3100, "??_7X@@6B@", vt[1][0], vt, 0)
    assert fails == [] and edges == {("fill", 0x1900)}         # a filler edge: not closed later
    m = _measure(I, R, [(0x1800, 0x1810, 0x1A00, ("unit", 1))], [(0x3000, "??_7X@@6B@", "a.obj")])
    assert m.data_ref(0x3000, 0x3100, "??_7X@@6B@", vt[1][0], vt, 0)[0] == ["data-codeptr:??_7X@@6B@"]


def _funcinfo(buf, at, unwind_to, base=B):
    _put(buf, at, struct.pack("<IiIIII", 0x19930520, len(unwind_to), base + at + 0x20, 0, 0, 0))
    for i, to in enumerate(unwind_to):
        _put(buf, at + 0x20 + 8 * i, struct.pack("<iI", to, 0))


def test_eh_thunk_counts_for_its_owner_only_when_funcinfo_matches():
    I, R = bytearray(0x6000), bytearray(0x6000)
    for buf, thunk, fi in ((I, 0x1C00, 0x3000), (R, 0x1D00, 0x3400)):
        _put(buf, thunk, b"\xb8" + struct.pack("<I", B + fi) + b"\xe9\0\0\0\0")
        _funcinfo(buf, fi, [-1, 0])
    m = _measure(I, R, [], [(0x1C00, "__ehhandler$?f@@YAXXZ", "a.obj")])
    assert m.code_ref(0x1C00, 0x1D00, "__ehhandler$?f@@YAXXZ", "?f@@YAXXZ") == (None, ("eh", 0x1C00))
    assert m.code_ref(0x1C00, 0x1D00, "x", "?g@@YAXXZ")[0].startswith("eh-foreign")   # not its owner
    _funcinfo(R, 0x3400, [-1, -1])                          # positive control: unwind map differs
    m = _measure(I, R, [], [(0x1C00, "__ehhandler$?f@@YAXXZ", "a.obj")])
    assert m.code_ref(0x1C00, 0x1D00, "x", "?f@@YAXXZ")[0] == "eh:unwind map differs"


def _twin_setup(callee_retail):
    """Linked other-name copy at 0x1C00 (call +0 -> 0x1800) vs retail row at 0x1D00."""
    I, R = bytearray(0x6000), bytearray(0x6000)
    body = b"\xe8\0\0\0\0\xc3"
    _put(I, 0x1C00, b"\xe8" + struct.pack("<i", 0x1800 - 0x1C05) + b"\xc3")
    _put(R, 0x1D00, b"\xe8" + struct.pack("<i", callee_retail - 0x1D05) + b"\xc3")
    tw = ([_sec(1, ".text", 6, relocs=[(1, 0, lc.REL32)])], {0: _sym(0, "?copy@@YAXXZ", 1)}, body)
    items = [(0x1800, 0x1810, 0x1900, ("unit", 7))]
    m = _measure(I, R, items, [(0x1C00, "?copy@@YAXXZ", "b.obj")], objs=FakeObjs({"b.obj": tw}),
                 ledger_starts={0x1D00: 6})
    return m


def test_icf_twin_needs_resolved_relocations_not_masked_bytes():
    m = _twin_setup(0x1900)                                  # same bytes and same resolved callee
    assert m.code_ref(0x1C00, 0x1D00, "?copy@@YAXXZ", "?r@@YAXXZ") == (None, ("twin", 0x1C00, 0x1D00))
    m.judge_twins()
    assert m.twins[(0x1C00, 0x1D00)] == (True, "certified")
    assert m.twin_edges[(0x1C00, 0x1D00)] == {("unit", 7)}
    m = _twin_setup(0x1950)                                  # masked bytes equal, callee differs
    m.code_ref(0x1C00, 0x1D00, "?copy@@YAXXZ", "?r@@YAXXZ")
    m.judge_twins()
    assert m.twins[(0x1C00, 0x1D00)] == (False, "code-wrong")


def test_unmapped_call_without_ledger_target_fails():
    I, R = bytearray(0x6000), bytearray(0x6000)
    m = _measure(I, R, [], [(0x1C00, "?copy@@YAXXZ", "b.obj")])
    assert m.code_ref(0x1C00, 0x1D00, "?copy@@YAXXZ", "?r@@YAXXZ") == ("code-unmapped:?copy@@YAXXZ", None)


def test_relocs_records_every_failure_not_the_first():
    I, R = bytearray(0x6000), bytearray(0x6000)
    code = b"\xe8\0\0\0\0\xe8\0\0\0\0\x90"
    _put(I, 0x1000, b"\xe8" + struct.pack("<i", 0x1C00 - 0x1005) + b"\xe8" + struct.pack("<i", 0x1C00 - 0x100A) + b"\x90")
    _put(R, 0x1000, b"\xe8" + struct.pack("<i", 0x1D00 - 0x1005) + b"\xe8" + struct.pack("<i", 0x1D00 - 0x100A) + b"\x91")
    o = ([_sec(1, ".text", 11, relocs=[(1, 0, lc.REL32), (6, 1, lc.REL32)])],
         {0: _sym(0, "?a@@YAXXZ", 0), 1: _sym(1, "?b@@YAXXZ", 0)}, code)
    m = _measure(I, R, [], [])
    fails, _, masked, _ = m.relocs(0x1000, 0x1000, 11, o, 1, 0, "?f@@YAXXZ")
    assert fails == ["code-unmapped:?a@@YAXXZ", "code-unmapped:?b@@YAXXZ", "bytes:1"]
    assert masked == set(range(1, 5)) | set(range(6, 10))


def test_absolute_except_list_compares_raw_value():
    I, R = bytearray(0x6000), bytearray(0x6000)
    code = b"\x64\xa1\0\0\0\0"
    _put(I, 0x1000, code)
    _put(R, 0x1000, code)
    o = ([_sec(1, ".text", 6, relocs=[(2, 0, lc.DIR32)])], {0: _sym(0, "__except_list", 0)}, code)
    m = _measure(I, R, [], [])
    assert m.relocs(0x1000, 0x1000, 6, o, 1, 0, "?f@@YAXXZ")[0] == []
    _put(I, 0x1002, struct.pack("<I", B + 0x5000))           # positive control: a stub, not absolute 0
    assert m.relocs(0x1000, 0x1000, 6, o, 1, 0, "?f@@YAXXZ")[0] == ["abs:__except_list"]


if __name__ == "__main__":
    sys.exit(pytest.main([__file__, "-q"]))
