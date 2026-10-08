"""link_cycle: the order/quarantine plan and the per-row measure's rules.

Each rule research 31 / the round-2 review found missing has a positive control
(the pilot's rule passes it, this one fails it) and a negative control."""
import collections
import os
import struct
import subprocess
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
    assert lc.greatest_closure(ok, edges, bad_targets=(), unknown_closes=True) == {"a", "b", "c"}
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


@pytest.mark.parametrize("platform, first", [("linux", "wine"), ("win32", "lib.exe")])
def test_import_libs_run_lib_exe_through_wine_off_windows(tmp_path, monkeypatch, platform, first):
    # lib.exe is a Windows binary checked in without an exec bit: off Windows it runs under wine, as link.exe does
    calls = []

    def run(cmd, **kw):
        calls.append(cmd)
        Path(next(a for a in cmd if a.startswith("/OUT:"))[5:]).write_bytes(b"!<arch>\n")
        return subprocess.CompletedProcess(cmd, 0, "", "")
    monkeypatch.setattr(lc.sys, "platform", platform)
    monkeypatch.setattr(lc.subprocess, "run", run)
    monkeypatch.setattr(lc.build, "vc71_root", lambda: tmp_path)
    monkeypatch.setattr(lc.build, "compiler_environment", lambda root: {})
    libs = lc.make_import_libs({"KERNEL32.dll": ["Sleep@4"]}, tmp_path)
    assert [p.name for p in libs] == ["imp_kernel32.lib"]
    assert Path(calls[0][0]).name == first and Path(calls[0][1 if first == "wine" else 0]).name == "lib.exe"


def test_link_inputs_are_never_read_as_options_under_wine(tmp_path, monkeypatch):
    # link.exe under wine reads an absolute POSIX path in the response file as an option (LNK4044) and
    # drops the input: every input is named relative to the link's working directory instead
    calls = []

    def run(cmd, **kw):
        calls.append((cmd, kw.get("cwd")))
        return subprocess.CompletedProcess(cmd, 0, "", "")
    monkeypatch.setattr(lc.sys, "platform", "linux")
    monkeypatch.setattr(lc.subprocess, "run", run)
    monkeypatch.setattr(lc.build, "vc71_root", lambda: tmp_path)
    monkeypatch.setattr(lc.build, "compiler_environment", lambda root: {})
    (tmp_path / "zzobj").mkdir()
    inputs = [tmp_path / "fill00.obj", tmp_path / "zzobj" / "o00000.obj", tmp_path / "imp_kernel32.lib"]
    lc.link("base", inputs, tmp_path / "order.txt", "_start", lc.BASE, tmp_path)
    cmd, cwd = calls[0]
    assert cmd[0] == "wine" and Path(cwd) == tmp_path
    listed = [line.strip('"') for line in (tmp_path / "base.rsp").read_text().splitlines()]
    assert listed == ["fill00.obj", "zzobj/o00000.obj", "imp_kernel32.lib"]
    assert [(Path(cwd) / p).resolve() for p in listed] == [p.resolve() for p in inputs]


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
    tag = bytes.fromhex("68746e6900c3")                             # push 0x696E74 ("int")
    retail_data = (B + 0x7BA000, B + 0xADA000)
    assert lc.hardcoded_operands(tag, B + 0x1000, set(), *retail_data) == []
    assert lc.hardcoded_operands(tag, B + 0x1000, set(), *retail_data, starts={0x696E74}) == [1]
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
    m._init_state()
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
    assert m.data_ref(0x3000, 0x3100, "_g", obj[1][0], obj, 0) == ([], {("datum", (0x3000, 0x3100, 4))}, True)
    m = _measure(I, R, [], [(0x3000, "_g", "a.obj")], pins={"_g": B + 0x3100})   # pinned as a VA
    assert m.data_ref(0x3000, 0x3100, "_g", obj[1][0], obj, 0)[0::2] == ([], True)


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
    m._init_state()
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
    assert fails == [] and edges == {("datum", (0x3000, 0x3100, 4))}
    assert m.dnodes[(0x3000, 0x3100, 4)]["edges"] == {("fill", 0x1900)}   # a filler edge: not closed later
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
    fails, _, masked, _, rels = m.relocs(0x1000, 0x1000, 11, o, 1, 0, "?f@@YAXXZ")
    assert fails == ["code-unmapped:?a@@YAXXZ", "code-unmapped:?b@@YAXXZ", "bytes:1"]
    assert masked == set(range(1, 5)) | set(range(6, 10))
    assert rels == [(1, lc.REL32, False), (6, lc.REL32, False)]


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


# ---- link-cycle-2: closure through data, shifted base, imports, selected copies, receipts ----
def _ptr_setup(target_linked, target_retail_bytes=b"BBBB", pins=None):
    """Linked datum A at 0x3000 holds a pointer (DIR32) to target_linked (_b at 0x3010
    or _c at 0x3020); retail's A at 0x3100 points at retail's B, 0x3110."""
    I, R = bytearray(0x6000), bytearray(0x6000)
    _put(I, 0x3000, struct.pack("<I", B + target_linked))
    _put(R, 0x3100, struct.pack("<I", B + 0x3110))
    _put(I, 0x3010, b"BBBB")
    _put(I, 0x3020, b"CCCC")
    _put(R, 0x3110, target_retail_bytes)
    syms = {0: _sym(0, "_a", 1), 1: _sym(1, "_b", 1, value=0x10), 2: _sym(2, "_c", 1, value=0x20)}
    target = 1 if target_linked == 0x3010 else 2
    o = ([_sec(1, ".data", 0x30, relocs=[(0, target, lc.DIR32)], ptr=0)], syms, bytes(0x30))
    objs = FakeObjs({"a.obj": o})
    objs.cache = {Path("a.obj"): o}
    m = _measure(I, R, [], [(0x3000, "_a", "a.obj"), (0x3010, "_b", "a.obj"), (0x3020, "_c", "a.obj")],
                 objs=objs, pins=pins, pub={"_a": 0x3000, "_b": 0x3010, "_c": 0x3020},
                 pubobj={"_a": "a.obj", "_b": "a.obj", "_c": "a.obj"})
    return m, o


def test_pointer_inside_data_must_reach_retails_datum():
    """link-cycle-1 masked data pointers inside data: a wrong pointer kept full credit."""
    m, o = _ptr_setup(0x3010)                                  # negative control: points at B, B equal
    fails, edges, _ = m.data_ref(0x3000, 0x3100, "_a", o[1][0], o, 0)
    assert fails == [] and edges == {("datum", (0x3000, 0x3100, 0x10))}
    a = m.dnodes[(0x3000, 0x3100, 0x10)]
    assert a["fails"] == [] and a["edges"] == {("datum", (0x3010, 0x3110, 0x10))}
    assert m.dnodes[(0x3010, 0x3110, 0x10)]["fails"] == []
    m, o = _ptr_setup(0x3020)                                  # positive control: points at C ("CCCC")
    m.data_ref(0x3000, 0x3100, "_a", o[1][0], o, 0)
    assert m.dnodes[(0x3020, 0x3110, 0x10)]["fails"] == ["data-content:_c"]
    ok = {("datum", k): not n["fails"] for k, n in m.dnodes.items()}
    edges = {("datum", k): n["edges"] for k, n in m.dnodes.items()}
    assert ("datum", (0x3000, 0x3100, 0x10)) not in lc.greatest_closure(ok, edges)   # A no longer closes


def test_pointer_inside_data_checks_pin_and_one_to_one():
    m, o = _ptr_setup(0x3010, pins={"_b": 0x3200})             # B pinned elsewhere
    assert m.data_ref(0x3000, 0x3100, "_a", o[1][0], o, 0)[0] == ["data-ptr-pin:_b"]
    m, o = _ptr_setup(0x3010)
    m.discover([(0x3010, 0x3120, "_b", o[1][1], o, 0, "addr")])   # code elsewhere maps B to another retail datum
    assert "data-ptr-fwd:_b" in m.data_ref(0x3000, 0x3100, "_a", o[1][0], o, 0)[0]


def _shifted(I, S):
    sh = lc.Shifted.__new__(lc.Shifted)
    sh.I, sh.S, sh.delta, sh.base_s, sh.why, sh.failed = I, S, lc.SHIFT_BASE - B, lc.SHIFT_BASE, None, collections.Counter()
    sh.lo, sh.hi, sh.starts = B + 0x1F00, B + 0x2000, set()
    return sh


def test_shifted_link_checks_every_relocation_moves():
    I, S = bytearray(0x2000), bytearray(0x2000)
    _put(I, 0x1000, b"\xa1" + struct.pack("<I", B + 0x1800) + b"\xc3")             # mov eax,[0x401800]; ret
    _put(S, 0x1000, b"\xa1" + struct.pack("<I", lc.SHIFT_BASE + 0x1800) + b"\xc3")
    sh = _shifted(I, S)
    rels, masked = [(1, lc.DIR32, False)], {1, 2, 3, 4}
    assert sh.code(0x1000, 6, masked, rels) is None                   # negative control
    _put(S, 0x1001, struct.pack("<I", B + 0x1800))                    # the word did not move
    assert sh.code(0x1000, 6, masked, rels) == "relocation not adjusted"
    raw = b"\xa1" + struct.pack("<I", B + 0x1F10) + b"\xc3"          # raw address: no relocation at all
    _put(I, 0x1100, raw)
    _put(S, 0x1100, raw)
    assert sh.code(0x1100, 6, set(), []) == "hardcoded address"
    sh.S, sh.why = None, "no shifted link"                            # nothing verified, nothing credited
    assert sh.code(0x1000, 6, masked, rels) == "no shifted link"


def test_field_retail_relocates_must_carry_a_relocation():
    """The boot overlay's field check found 25 closed-strict rows (e.g.
    ?Rva0006182EGet: `mov eax,0x461834`, an immediate) holding a code address
    retail relocates. Not a data VA, not a row start: the operand scan passed it,
    and an unrelocated word does not move in the shifted link either."""
    code = b"\xb8" + struct.pack("<I", B + 0x1834) + b"\xc3"              # mov eax,0x401834; ret
    I, S = bytearray(0x4000), bytearray(0x4000)
    _put(I, 0x1000, code)
    _put(S, 0x1000, code)
    sh = _shifted(I, S)
    assert sh.code(0x1000, 6, set(), [], 0x1000) is None                 # what the old rule saw
    sh.sites = [0x1001]                                                   # retail's table relocates it
    assert sh.code(0x1000, 6, set(), [], 0x1000) == "retail relocates a hardcoded field"
    assert lc.unrelocated_sites([0x1001], 0x1000, 6, [(1, lc.REL32, False)]) == [1]
    _put(S, 0x1001, struct.pack("<I", lc.SHIFT_BASE + 0x1834))           # negative control: relocated
    assert sh.code(0x1000, 6, {1, 2, 3, 4}, [(1, lc.DIR32, False)], 0x1000) is None
    # a datum (a pointer table) whose second slot is a hard-coded address
    node = {"rels": [(0, lc.DIR32, False)], "masked": {0, 1, 2, 3}}
    sh.sites = [0x3100, 0x3104]
    for buf, base in ((I, B), (S, lc.SHIFT_BASE)):
        _put(buf, 0x3000, struct.pack("<II", base + 0x1000, B + 0x1000))
    assert sh.data((0x3000, 0x3100, 8), node) == "retail relocates a hardcoded field"
    node["rels"].append((4, lc.DIR32, False))
    node["masked"] |= {4, 5, 6, 7}
    _put(S, 0x3004, struct.pack("<I", lc.SHIFT_BASE + 0x1000))
    assert sh.data((0x3000, 0x3100, 8), node) is None


def test_retail_relocation_table_resumes_after_overwritten_blocks():
    def block(page, offs):
        ents = [0x3000 | o for o in offs] + ([0] if len(offs) % 2 else [])
        return struct.pack("<II", page, 8 + 2 * len(ents)) + b"".join(struct.pack("<H", e) for e in ents)
    head = block(0x1000, [0x10, 0x20]) + block(0x2000, [0x4])
    tail = b"".join(block(0x9000 + 0x1000 * k, [0x8]) for k in range(17))
    blob = head + b"\xff" * 40 + tail + b"\0" * 16                        # an overwrite between them
    sites, lost = lc.reloc_table_sites(blob)
    assert sites[:3] == [0x1010, 0x1020, 0x2004] and len(sites) == 3 + 17 and sites[3] == 0x9008
    assert lost == (0x3000, 0x9000)
    assert lc.reloc_table_sites(head)[1] is None                          # an intact table: nothing lost


def test_shift_failure_invalidates_the_dependent_closure():
    """link-cycle-1 only flagged the row; its callers kept closed credit."""
    ok = {("unit", 1): True, ("unit", 2): True, ("unit", 3): True, ("datum", 9): False}
    edges = {("unit", 1): {("unit", 2)}, ("unit", 2): {("datum", 9)}, ("unit", 3): set()}
    assert lc.greatest_closure(ok, edges) == {("unit", 3)}            # the datum's pointer did not move
    ok[("datum", 9)] = True
    assert lc.greatest_closure(ok, edges) == {("unit", 1), ("unit", 2), ("unit", 3), ("datum", 9)}
    del ok[("datum", 9)]                                                # an edge the graph does not hold
    assert lc.greatest_closure(ok, edges) == {("unit", 3)}


def test_eh_tables_must_move_with_the_base():
    I, S = bytearray(0x6000), bytearray(0x6000)
    for buf, base in ((I, B), (S, lc.SHIFT_BASE)):
        _put(buf, 0x1C00, b"\xb8" + struct.pack("<I", base + 0x3000) + b"\xe9\0\0\0\0")
        _funcinfo(buf, 0x3000, [-1, 0], base=base)
    sh = _shifted(I, S)
    assert sh.eh(0x1C00) is None
    _put(S, 0x3008, struct.pack("<I", B + 0x3020))                     # unwind map pointer left at the old base
    assert sh.eh(0x1C00) in ("FuncInfo not adjusted", "FuncInfo unparsable")


def _import_measure(limports, rimports):
    I, R = bytearray(0x8000), bytearray(0x8000)
    m = _measure(I, R, [], [])
    m.isecs = lc.SectionList([(".text", 0x1000, 0x1000), (".rdata", 0x6000, 0x1000), (".data", 0x3000, 0x1000)])
    m.limports, m.rimports = limports, rimports
    return m


def test_import_identity_is_dll_and_name():
    k32, usr = lc.import_key("KERNEL32.dll", b"Foo"), lc.import_key("USER32.dll", b"Foo")
    m = _import_measure({0x6000: k32}, {0x6100: usr})
    assert m.data_ref(0x6000, 0x6100, "__imp__Foo@4", None, None, 0)[0] == ["import-mismatch:__imp__Foo@4"]
    m = _import_measure({0x6000: k32}, {0x6100: lc.import_key("kernel32.dll", "Foo")})
    assert m.data_ref(0x6000, 0x6100, "__imp__Foo@4", None, None, 0)[0] == []
    assert lc.import_key("ws2_32.dll", None, 23) == ("ws2_32.dll", "#23")
    assert lc.import_key("x.dll", "Bar@8") == ("x.dll", "Bar")


def test_duplicate_retail_iat_slots_are_one_import_only_when_read_through():
    """Retail has two IAT slots for msvcr71 strncpy; the link has one. A call through
    either reads the same function: equivalent. Taking a slot's address is not."""
    imp = lc.import_key("msvcr71.dll", "strncpy")
    m = _import_measure({0x6000: imp}, {0x6100: imp, 0x6104: imp})
    refs = [(0x6000, 0x6100, "__imp__strncpy", None, None, 0, "read"),
            (0x6000, 0x6104, "__imp__strncpy", None, None, 0, "read")]
    m.discover(refs)
    assert [m.ref_check(r)[0] for r in refs] == [[], []] and m.import_equiv == 2
    observe = (0x6000, 0x6104, "__imp__strncpy", None, None, 0, "addr")
    m.discover([observe])
    assert m.ref_check(observe)[0] == ["data-fwd:__imp__strncpy"]
    other = lc.import_key("msvcr71.dll", "toupper")                   # wrong import, read through: still fails
    m = _import_measure({0x6000: imp}, {0x6100: imp, 0x6104: other})
    bad = (0x6000, 0x6104, "__imp__strncpy", None, None, 0, "read")
    m.discover([bad, refs[0]])
    assert m.ref_check(bad)[0] == ["import-mismatch:__imp__strncpy", "data-fwd:__imp__strncpy"]


def test_read_through_operand_forms():
    assert lc.read_through(b"\xff\x15\0\0\0\0", 2)             # call [m32]
    assert lc.read_through(b"\xff\x25\0\0\0\0", 2)             # jmp [m32]
    assert lc.read_through(b"\x8b\x3d\0\0\0\0", 2)             # mov edi,[m32]
    assert lc.read_through(b"\xa1\0\0\0\0", 1)                 # mov eax,[m32]
    assert not lc.read_through(b"\x68\0\0\0\0", 1)             # push offset slot: address taken
    assert not lc.read_through(b"\xc7\x05\0\0\0\0", 2)         # mov [slot], imm: a store
    assert not lc.read_through(b"\x8d\x05\0\0\0\0", 2)         # lea eax,[slot]


def test_twin_is_judged_on_the_selected_copy_inside_its_section():
    """A section holding two functions: link-cycle-1 rejected the second on
    'extent' (offset != 0); the /MAP's copy at its own offset is judged now."""
    I, R = bytearray(0x6000), bytearray(0x6000)
    body = b"\x90" * 0x10 + b"\xe8\0\0\0\0\xc3" + b"\xcc" * 10
    _put(I, 0x1C00, b"\x90" * 0x10 + b"\xe8" + struct.pack("<i", 0x1800 - 0x1C15) + b"\xc3")
    _put(R, 0x1D00, b"\xe8" + struct.pack("<i", 0x1900 - 0x1D05) + b"\xc3")
    tw = ([_sec(1, ".text", 0x20, relocs=[(0x11, 0, lc.REL32)], ptr=4)],      # raw data at file offset 4
          {0: _sym(0, "?f@@YAXXZ", 1), 1: _sym(1, "?g@@YAXXZ", 1, value=0x10)}, b"\0" * 4 + body)
    m = _measure(I, R, [(0x1800, 0x1810, 0x1900, ("unit", 7))],
                 [(0x1C00, "?f@@YAXXZ", "b.obj"), (0x1C10, "?g@@YAXXZ", "b.obj")],
                 objs=FakeObjs({"b.obj": tw}), ledger_starts={0x1D00: 6})
    assert m.code_ref(0x1C10, 0x1D00, "?g@@YAXXZ", "?r@@YAXXZ") == (None, ("twin", 0x1C10, 0x1D00))
    m.judge_twins()
    assert m.twins[(0x1C10, 0x1D00)] == (True, "certified")
    m = _measure(I, R, [], [(0x1C10, "?g@@YAXXZ", "b.obj")], objs=FakeObjs({"b.obj": tw}),
                 ledger_starts={0x1D00: 0x12})                          # retail's row is longer: not this copy
    m.code_ref(0x1C10, 0x1D00, "?g@@YAXXZ", "?r@@YAXXZ")
    m.judge_twins()
    assert m.twins[(0x1C10, 0x1D00)] == (False, "extent differs")


def test_unit_whose_copy_the_link_did_not_select_is_not_measured():
    u = {"id": 0, "obj": "x/a.obj", "sec": 1, "secname": ".text", "size": 4, "head": "?f@@YAXXZ",
         "head_cls": lc.EXTERNAL, "starts": [0x1000],
         "rows": [{"name": "?f@@YAXXZ", "rva": 0x1000, "size": 4, "off": 0, "sym": "?f@@YAXXZ"}]}
    mapped = ({"?f@@YAXXZ": 0x1000}, {}, [(0x1000, "?f@@YAXXZ", "b.obj")], {"?f@@YAXXZ": "b.obj"})
    m = lc.Measure([u], [], mapped, bytearray(0x2000), bytearray(0x2000), {".text": (0x1000, 0x1000)},
                   {}, {}, {}, FakeObjs({}), {})
    assert u["linked"] is None and u["not_selected"] == "b.obj"
    rec = m.run()[0]
    assert rec["fails"] == ["not-selected:b.obj"] and not rec["measured"]
    mapped[3]["?f@@YAXXZ"] = "a.obj"                                   # negative control: its own copy
    lc.Measure([u], [], mapped, bytearray(0x2000), bytearray(0x2000), {".text": (0x1000, 0x1000)},
               {}, {}, {}, FakeObjs({}), {})
    assert u["linked"] == 0x1000 and "not_selected" not in u


def _three_rejected_twins():
    """One row calling three twin candidates, each rejected for another reason:
    t1 has no map definition, t2's extent is longer than retail's row, t3's bytes
    differ. Returns the row's failures."""
    a = Path("x/a.obj")
    code = b"\xe8\0\0\0\0" * 3
    row = ([_sec(1, ".text", 15, relocs=[(1, 1, lc.REL32), (6, 2, lc.REL32), (11, 3, lc.REL32)])],
           {0: _sym(0, "?f@@YAXXZ", 1), 1: _sym(1, "?t1@@YAXXZ", 0), 2: _sym(2, "?t2@@YAXXZ", 0),
            3: _sym(3, "?t3@@YAXXZ", 0)}, code)
    tw = ([_sec(1, ".text", 0x20, ptr=4)], {0: _sym(0, "?t2@@YAXXZ", 1), 1: _sym(1, "?t3@@YAXXZ", 1, value=0x10)},
          b"\0" * 4 + b"\x55\x8b\xec\x33\xc0\x5d\xc3\x90" + b"\xcc" * 8 + b"\x33\xc0\xc3" + b"\xcc" * 13)
    I, R = bytearray(0x2000), bytearray(0x2000)
    for k, (lt, rt) in enumerate(((0x1C00, 0x1D00), (0x1C20, 0x1D20), (0x1C40, 0x1D40))):
        _put(I, 0x1000 + 5 * k, b"\xe8" + struct.pack("<i", lt - (0x1005 + 5 * k)))
        _put(R, 0x1000 + 5 * k, b"\xe8" + struct.pack("<i", rt - (0x1005 + 5 * k)))
    _put(I, 0x1C40, b"\x33\xc0\xc3")
    _put(R, 0x1D40, b"\x31\xc0\xc3")                                   # t3: a byte differs
    objs = FakeObjs({"b.obj": tw})
    objs.cache[a] = row
    u = {"id": 0, "obj": str(a), "sec": 1, "secname": ".text", "size": 15, "head": "?f@@YAXXZ",
         "head_cls": lc.EXTERNAL, "starts": [0x1000],
         "rows": [{"name": "?f@@YAXXZ", "rva": 0x1000, "size": 15, "off": 0, "sym": "?f@@YAXXZ"}]}
    mapped = ({"?f@@YAXXZ": 0x1000}, {},
              [(0x1000, "?f@@YAXXZ", "a.obj"), (0x1C00, "?t1@@YAXXZ", "gone.obj"),
               (0x1C20, "?t2@@YAXXZ", "b.obj"), (0x1C40, "?t3@@YAXXZ", "b.obj")], {"?f@@YAXXZ": "a.obj"})
    m = lc.Measure([u], [], mapped, I, R, {".text": (0x1000, 0x1000)}, {}, {}, {}, objs,
                   {0x1000: 15, 0x1D00: 3, 0x1D20: 3, 0x1D40: 3})
    return m.run()[0]["fails"]


def test_row_failures_do_not_depend_on_the_hash_seed():
    """A cold and a cached cycle of one snapshot gave different link_status.csv
    (so different receipt cores) with identical links: a row's twin-rejected
    failures came out in set order, which follows each process's string hash
    seed. They now come out in address order, under every seed."""
    want = ["twin-rejected:no map definition", "twin-rejected:extent differs", "twin-rejected:bytes"]
    assert _three_rejected_twins() == want
    here = Path(__file__).resolve().parent
    seen = set()
    for seed in ("0", "1", "2", "3", "4", "5", "6", "7"):
        res = subprocess.run([sys.executable, "-c", "import test_link_cycle as t; print(t._three_rejected_twins())"],
                             cwd=here, capture_output=True, text=True, check=True,
                             env=dict(os.environ, PYTHONHASHSEED=seed, PYTHONDONTWRITEBYTECODE="1"))
        seen.add(res.stdout.strip())
    assert seen == {str(want)}


def test_unit_the_map_puts_outside_code_is_not_measured():
    """A cold and a cached cycle of 83b55dd426 disagreed on one row: uw_0075be41's
    static head is a label of a discarded COMDAT, listed in the /MAP at
    0001:fffff0f1 (VA 0x004000F1), so its 'linked bytes' were the PE header, time
    stamp included, which differs per link (bytes:25 vs bytes:26)."""
    line = " 0001:fffff0f1       $L15608                    004000f1 f   o00202.obj\n"
    good = " 0001:00000010       $L1                        00401010 f   o00202.obj\n"
    pub, stat, allsyms, _ = lc.read_map(" Static symbols\n" + line + good, B, {"o00202.obj": "a.obj"})
    assert stat == {("$L1", "a.obj"): 0x1010} and [s[1] for s in allsyms] == ["$L1"]
    u = {"id": 0, "obj": "x/a.obj", "sec": 1, "secname": ".text", "size": 4, "head": "$L1",
         "head_cls": lc.STATIC, "starts": [0x1000],
         "rows": [{"name": "uw_1", "rva": 0x1000, "size": 4, "off": 0, "sym": "$L1"}]}
    mapped = ({}, {("$L1", "a.obj"): 0xF1}, [], {})                   # an address in the headers
    m = lc.Measure([u], [], mapped, bytearray(0x2000), bytearray(0x2000), {".text": (0x1000, 0x1000)},
                   {}, {}, {}, FakeObjs({}), {})
    assert u["linked"] is None and u["outside_code"] == 0xF1
    rec = m.run()[0]
    assert rec["fails"] == ["linked-outside-code"] and not rec["measured"]
    mapped[1][("$L1", "a.obj")] = 0x1000                              # negative control: in .text
    lc.Measure([u], [], mapped, bytearray(0x2000), bytearray(0x2000), {".text": (0x1000, 0x1000)},
               {}, {}, {}, FakeObjs({}), {})
    assert u["linked"] == 0x1000 and "outside_code" not in u


def test_object_identity_ignores_time_stamp_and_debug_records(tmp_path):
    def ident(raw):
        return lc.object_identity(lc.parse_coff(bytes(raw)) + (bytes(raw),))
    a = lc.write_coff(tmp_path / "a.obj", [(".text", 0x60500020, b"\x90\xc3", 0), (".debug$S", 0x42100040, b"C:/x", 0)],
                      [("_f", 1, 0, lc.EXTERNAL)]).read_bytes()
    b = bytearray(lc.write_coff(tmp_path / "b.obj", [(".text", 0x60500020, b"\x90\xc3", 0),
                                                     (".debug$S", 0x42100040, b"D:/yyy", 0)],
                                [("_f", 1, 0, lc.EXTERNAL)]).read_bytes())
    b[4:8] = b"\x01\x02\x03\x04"                                       # a compile time stamp
    assert ident(b) == ident(a)
    b[b.index(b"\x90\xc3")] = 0xCC                                     # positive control: a code byte
    assert ident(b) != ident(a)


TEXT, RDATA, ANON = 0x60500020, 0x40300040, "?A0x{}"


def emit(secs, syms, order=None, stamp=0, anon="218df5bc", shuffle=False):
    """A COFF object as cl writes one: a section definition (with its aux: COMDAT
    selection and parent) for each section in file `order`, its own symbols after
    it (a COMDAT's leader first), then the undefined names (reversed if `shuffle`,
    which also reverses each section's relocation records). secs: dicts name,
    flags, body, sel, assoc (logical index), relocs [(site, target, type)], target
    a symbol name or ("sec", logical index); syms: dicts name, sec (logical index,
    or 0 undefined), value, cls, weak (default's name). "{}" in names and bodies
    takes the anonymous namespace's hash."""
    order = list(range(len(secs))) if order is None else order
    fileno = {k: n + 1 for n, k in enumerate(order)}
    A = ANON.format(anon)
    strings = bytearray()

    def field(n):
        raw = n.replace("{}", A).encode("latin-1")
        if len(raw) <= 8:
            return raw.ljust(8, b"\0")
        strings.extend(raw + b"\0")
        return struct.pack("<II", 0, 4 + len(strings) - len(raw) - 1)
    table, index = [], {}                     # [(name, secno, value, cls, aux: bytes / weak default / None)]
    for k in order:
        s = secs[k]
        index[("sec", k)] = len(table)
        table.append((s["name"], fileno[k], 0, lc.STATIC,
                      struct.pack("<IHHIHBBH", len(s["body"]), len(s.get("relocs", ())), 0, 0,
                                  fileno[s["assoc"]] if s.get("assoc") is not None else 0, s.get("sel", 0), 0, 0)))
        for y in syms:
            if y.get("sec") == k:
                index[y["name"]] = len(table)
                table.append((y["name"], fileno[k], y.get("value", 0), y.get("cls", lc.EXTERNAL), None))
    rest = [y for y in syms if y.get("sec") is None]
    for y in reversed(rest) if shuffle else rest:
        index[y["name"]] = len(table)
        table.append((y["name"], 0, 0, y.get("cls", lc.EXTERNAL), y.get("weak")))
    raw_index, at = [], 0
    for t in table:
        raw_index.append(at)
        at += 2 if t[4] else 1
    real = {key: raw_index[v] for key, v in index.items()}
    symtab = bytearray()
    for name, sec, val, cls, aux in table:
        if isinstance(aux, str):
            aux = struct.pack("<II", real[aux], 3).ljust(18, b"\0")
        symtab += field(name) + struct.pack("<IhHBB", val, sec, 0x20 if sec > 0 else 0, cls, 1 if aux else 0)
        symtab += aux or b""
    hdr_end = 20 + 40 * len(order)
    shdr, bodies = bytearray(), bytearray()
    for k in order:
        s = secs[k]
        body = s["body"].replace(b"{}", A.encode()) if isinstance(s["body"], bytes) else s["body"]
        ptr = hdr_end + len(bodies)
        bodies += body
        relocs = list(s.get("relocs", ()))
        relocs = relocs[::-1] if shuffle else relocs
        rptr = hdr_end + len(bodies) if relocs else 0
        for va, target, ty in relocs:
            bodies += struct.pack("<IIH", va, real[target], ty)
        shdr += field(s["name"]) + struct.pack("<IIIIIIHHI", 0, 0, len(body), ptr if body else 0, rptr, 0,
                                               len(relocs), 0, s["flags"])
    return (struct.pack("<HHIIIHH", 0x14C, len(order), stamp, hdr_end + len(bodies), len(symtab) // 18, 0, 0)
            + shdr + bodies + symtab + struct.pack("<I", 4 + len(strings)) + strings)


def canon(raw):
    return lc.canonical_identity(lc.parse_coff(raw) + (raw,))


def ident(raw):
    return lc.object_identity(lc.parse_coff(raw) + (raw,))


def thunk_object():
    """Two adjustor thunks (COMDATs cl permutes), each with an associative .rdata,
    a .text holding a call through an anonymous-namespace function, RTTI-like
    bytes naming it, and a weak external."""
    C = lc.COMDAT
    secs = [dict(name=".drectve", flags=0x100A00, body=b"/DEFAULTLIB:LIBC "),
            dict(name=".text", flags=TEXT, body=b"\xe8\0\0\0\0\xc3", relocs=[(1, "?f@{}@@YAXXZ", lc.REL32)]),
            dict(name=".text", flags=TEXT | C, sel=2, body=b"\x83\xe9\x04\xe9\0\0\0\0",
                 relocs=[(4, "??_GA@@UAEPAXI@Z", lc.REL32)]),
            dict(name=".text", flags=TEXT | C, sel=2, body=b"\x83\xe9\x08\xe9\0\0\0\0",
                 relocs=[(4, "??_GB@@UAEPAXI@Z", lc.REL32)]),
            dict(name=".rdata", flags=RDATA | C, sel=5, assoc=2, body=b"\0\0\0\0", relocs=[(0, ("sec", 2), 6)]),
            dict(name=".rdata", flags=RDATA | C, sel=5, assoc=3, body=b"\0\0\0\0", relocs=[(0, ("sec", 3), 6)]),
            dict(name=".data", flags=0xC0300040, body=b".?AVV@{}@@\0\0\0\0\0\0",
                 relocs=[(12, "?f@{}@@YAXXZ", 6), (16, "_weak", 6)]),
            dict(name=".text", flags=TEXT | C, sel=2, body=b"\xc3")]
    syms = [dict(name="_main", sec=1), dict(name="$L1", sec=1, value=5, cls=lc.STATIC),
            dict(name="??_EA@@W3AEPAXI@Z", sec=2), dict(name="??_EB@@W7AEPAXI@Z", sec=3),
            dict(name="_vt", sec=6), dict(name="?f@{}@@YAXXZ", sec=7, cls=lc.STATIC),
            dict(name="??_GA@@UAEPAXI@Z"), dict(name="??_GB@@UAEPAXI@Z"), dict(name="_dflt"),
            dict(name="_weak", cls=lc.WEAK, weak="_dflt")]
    return secs, syms


def test_canonical_identity_drops_what_two_compiles_of_one_tu_vary_in():
    """Research lc-repro-bfme2: 20 of 18,301 objects of two exports of one tree
    differed by anonymous-namespace hash (4), relocation symbol indices (6) and
    permuted adjustor-thunk COMDATs (10). Each, and all together, compare equal."""
    secs, syms = thunk_object()
    base = emit(secs, syms)
    variants = {"time stamp": emit(secs, syms, stamp=0x5F00AA11),
                "anonymous-namespace hash": emit(secs, syms, anon="6a92f4f5"),
                "symbol and relocation order": emit(secs, syms, shuffle=True),
                "COMDAT numbering": emit(secs, syms, order=[0, 1, 3, 2, 5, 4, 6, 7]),
                "all of them": emit(secs, syms, order=[0, 1, 7, 3, 2, 6, 5, 4], anon="c4c9395d", shuffle=True,
                                    stamp=7)}
    for why, raw in variants.items():
        assert canon(raw) == canon(base), why
        if why != "time stamp":
            assert ident(raw) != ident(base), why          # what object_identity (core_sha256) refuses


def test_canonical_identity_binds_code_relocations_and_bindings():
    """No over-acceptance: every change the linker or the image would see moves
    the canonical identity."""
    import copy
    secs, syms = thunk_object()
    base = canon(emit(secs, syms))

    def mutated(f, **kw):
        s, y = copy.deepcopy(secs), copy.deepcopy(syms)
        f(s, y)
        return canon(emit(s, y, **kw))

    def sym(y, name):
        return next(x for x in y if x["name"] == name)
    mutations = {
        "code byte": lambda s, y: s[2].update(body=b"\x83\xe9\x08\xe9\0\0\0\0"),
        "thunk bodies swapped between leaders": lambda s, y: (
            s[2].update(body=secs[3]["body"], relocs=secs[3]["relocs"]),
            s[3].update(body=secs[2]["body"], relocs=secs[2]["relocs"])),
        "data byte": lambda s, y: s[6].update(body=b".?AVW@{}@@\0\0\0\0\0\0"),
        "relocation target (another symbol)": lambda s, y: s[2].update(relocs=[(4, "??_GB@@UAEPAXI@Z", lc.REL32)]),
        "relocation target (another section)": lambda s, y: s[4].update(relocs=[(0, ("sec", 3), 6)]),
        "relocation site": lambda s, y: s[1].update(relocs=[(0, "?f@{}@@YAXXZ", lc.REL32)]),
        "relocation type": lambda s, y: s[1].update(relocs=[(1, "?f@{}@@YAXXZ", 6)]),
        "relocation dropped": lambda s, y: s[6].update(relocs=s[6]["relocs"][:1]),
        "binding external -> static": lambda s, y: sym(y, "_main").update(cls=lc.STATIC),
        "binding static -> external": lambda s, y: sym(y, "?f@{}@@YAXXZ").update(cls=lc.EXTERNAL),
        "symbol value": lambda s, y: sym(y, "$L1").update(value=4),
        "symbol section": lambda s, y: sym(y, "_vt").update(sec=1),
        "symbol renamed": lambda s, y: sym(y, "??_EA@@W3AEPAXI@Z").update(name="??_EA@@W7AEPAXI@Z"),
        "COMDAT selection": lambda s, y: s[2].update(sel=1),
        "associative parent": lambda s, y: s[4].update(assoc=3),
        "weak external default": lambda s, y: sym(y, "_weak").update(weak="??_GA@@UAEPAXI@Z"),
        "section flags": lambda s, y: s[1].update(flags=TEXT | 0x2000),
        "directive": lambda s, y: s[0].update(body=b"/DEFAULTLIB:LIBCMT "),
    }
    for why, f in mutations.items():
        assert mutated(f) != base, why
        assert mutated(f, order=[0, 1, 3, 2, 5, 4, 6, 7], shuffle=True, anon="6a92f4f5") != base, why


def test_canonical_identity_keeps_plain_section_order_and_mixed_anonymous_hashes():
    secs = [dict(name=".text", flags=TEXT, body=b"\x90\xc3"), dict(name=".text", flags=TEXT, body=b"\xcc\xc3")]
    syms = [dict(name="_a", sec=0), dict(name="_b", sec=1)]
    # two non-COMDAT .text sections link in object order: swapping them is a different object
    assert canon(emit(secs, syms)) != canon(emit(secs, syms, order=[1, 0]))
    # one hash is renamed; two different ones in one object are not taken for one
    one = [dict(name=".text", flags=TEXT, body=b"?A0x218df5bc\0")]
    two = [dict(name=".text", flags=TEXT, body=b"?A0x6a92f4f5\0")]
    named = [dict(name="?f@?A0x218df5bc@@YAXXZ", sec=0)]
    assert canon(emit(one, named)) != canon(emit(two, named))
    assert canon(emit(one, named)) == canon(emit(two, [dict(name="?f@?A0x6a92f4f5@@YAXXZ", sec=0)]))


def test_receipt_canon_core_replaces_the_object_digests_only():
    r = {"rules": "link-cycle-2", "commit": "c", "series": {"credit_unique_bytes": 5}, "objects_digest": "o1",
         "provenance_sha256": "p1", "canon_rules": lc.CANON_RULES, "objects_canon_digest": "k",
         "provenance_canon_sha256": "q"}
    other_builder = dict(r, objects_digest="o2", provenance_sha256="p2")
    lc.stamp_cores(r)
    lc.stamp_cores(other_builder)
    assert r["core_sha256"] != other_builder["core_sha256"]
    assert r["core_canon_sha256"] == other_builder["core_canon_sha256"]
    for k, v in (("objects_canon_digest", "k2"), ("provenance_canon_sha256", "q2"), ("series", {})):
        moved = dict(r, **{k: v})
        lc.stamp_cores(moved)
        assert moved["core_canon_sha256"] != r["core_canon_sha256"], k
    old = {"rules": "link-cycle-2", "objects_digest": "o1"}            # a receipt from before: no canon core
    lc.stamp_cores(old)
    assert "core_canon_sha256" not in old


def test_warm_start_caches_are_bound_to_their_objects(tmp_path):
    q = tmp_path / "quarantine.json"
    lc.save_cache(q, "digest-A", ["?x@@YAXXZ"])
    assert lc.cache_file(q, "digest-A", False) == (["?x@@YAXXZ"], False)
    assert lc.cache_file(q, "digest-B", False) == (None, False)        # stale: a cold start
    assert lc.cache_file(q, "digest-B", True) == (["?x@@YAXXZ"], True)   # allowed, but marked
    q.write_text('["?x@@YAXXZ"]')                                       # an unstamped (link-cycle-1) cache
    assert lc.cache_file(q, "digest-A", False) == (None, False)


def test_receipt_core_leaves_out_times_and_history():
    r = {"rules": "link-cycle-2", "commit": "c", "series": {"credit_unique_bytes": 5}, "objects_digest": "o",
         "date_utc": "now", "seconds": {"total": 1}, "links": [{"secs": 3}], "warm_start": {"stubs": True}}
    cold = dict(r, date_utc="then", seconds={"total": 99}, links=[{"secs": 1}, {"secs": 2}], warm_start={})
    assert lc.digest_of(lc.receipt_core(r)) == lc.digest_of(lc.receipt_core(cold))
    assert lc.digest_of(lc.receipt_core(r)) != lc.digest_of(lc.receipt_core(dict(r, series={"credit_unique_bytes": 4})))
    env = dict(r, measure_env={"capstone": "5.0.7"})                   # the decoder is bound
    assert lc.digest_of(lc.receipt_core(env)) != lc.digest_of(lc.receipt_core(dict(env, measure_env={"capstone": "6"})))


def test_text_digests_ignore_the_hosts_line_endings(tmp_path):
    """git archive writes text with the host's core.autocrlf endings: two builders
    of one commit must bind one tool digest and one ledger digest."""
    (tmp_path / "crlf.py").write_bytes(b"a = 1\r\nb = 2\r\n")
    (tmp_path / "lf.py").write_bytes(b"a = 1\nb = 2\n")
    (tmp_path / "other.py").write_bytes(b"a = 1\nb = 3\n")
    assert lc.text_sha256(tmp_path / "crlf.py") == lc.text_sha256(tmp_path / "lf.py")
    assert lc.text_sha256(tmp_path / "other.py") != lc.text_sha256(tmp_path / "lf.py")


if __name__ == "__main__":
    sys.exit(pytest.main([__file__, "-q"]))
