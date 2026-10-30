"""retail_layout: class layouts from retail constructor, vftable and operator-new bytes."""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_contract as contract  # noqa: E402
import retail_layout as rl  # noqa: E402

pytest.importorskip("capstone")

VA = rl.IMAGE_BASE
EH_PROLOG, B_CTOR, I_CTOR, NEW, MAKE, D_CTOR, D_CTOR2 = 0x1000, 0x1200, 0x1240, 0x1280, 0x1300, 0x1100, 0x1600
W_CTOR, V_CTOR, THUNK = 0x1500, 0x1560, 0x1400
B_VT, I_VT, D_VT0, D_VT10 = 0x2000, 0x2008, 0x2010, 0x2020
VBT, W_VT, W_VT_V, V_VT = 0x2100, 0x2110, 0x2118, 0x2120


def imm(value):
    return struct.pack("<I", value & 0xFFFFFFFF)


def call(at, target):
    return b"\xe8" + struct.pack("<i", target - (at + 5))


class Builder:
    def __init__(self):
        self.mem = bytearray(0x3000)

    def code(self, at, *parts):
        out = b""
        for part in parts:
            out += part(at + len(out)) if callable(part) else part
        self.mem[at:at + len(out)] = out

    def words(self, at, *values):
        for i, v in enumerate(values):
            self.mem[at + 4 * i:at + 4 * i + 4] = imm(v)


def image():
    b = Builder()
    b.code(EH_PROLOG, b"\xc3")
    b.code(NEW, b"\xc3")
    b.code(THUNK, b"\x90" * 16 + b"\xc3")
    # D::D(): EH frame, B at +0 by call, I at +0x10 inlined, then D's own tables and a field.
    b.code(D_CTOR, b"\xb8" + imm(VA + 0x1fff), lambda at: call(at, EH_PROLOG),
           b"\x8b\xf1", b"\x8b\xce", lambda at: call(at, B_CTOR),
           b"\xc7\x46\x10" + imm(VA + I_VT), b"\xc7\x06" + imm(VA + D_VT0), b"\xc7\x46\x10" + imm(VA + D_VT10),
           b"\xc7\x46\x14" + imm(0), b"\xc3")
    # D::D(int) disagrees: it stores the +0x10 table at +0.
    b.code(D_CTOR2, b"\xc7\x01" + imm(VA + D_VT10), b"\xc3")
    b.code(B_CTOR, b"\xc7\x01" + imm(VA + B_VT), b"\xc3")
    b.code(I_CTOR, b"\xc7\x01" + imm(VA + I_VT), b"\xc3")
    b.code(V_CTOR, b"\xc7\x01" + imm(VA + V_VT), b"\xc3")
    # make(): push 0x18; call operator new; mov ecx, eax; call D::D
    b.code(MAKE, b"\x6a\x18", lambda at: call(at, NEW), b"\x8b\xc8", lambda at: call(at, D_CTOR), b"\xc3")
    # W::W(): vbptr at +4, the virtual base's vptr through the vbtable, then W's own tables.
    vbase_store = b"\x8b\x46\x04\x8b\x40\x04\xc7\x44\x30\x04"
    b.code(W_CTOR, b"\x8b\xf1", b"\xc7\x46\x04" + imm(VA + VBT), vbase_store + imm(VA + V_VT),
           b"\xc7\x06" + imm(VA + W_VT), vbase_store + imm(VA + W_VT_V), b"\xc3")
    t = VA + THUNK
    b.words(B_VT, t, t + 4)
    b.words(I_VT, t, t + 8)
    b.words(D_VT0, t, t + 1, t + 2, t + 3)
    b.words(D_VT10, t + 5, 0)
    b.words(VBT, -4, 0x0C)
    b.words(W_VT, t, 0, t, 0, t, 0)
    sections = [{"name": ".text", "rva": 0x1000, "size": 0x1000}, {"name": ".rdata", "rva": 0x2000, "size": 0x1000}]
    return rl.Image(lambda rva, size: bytes(b.mem[rva:rva + size]), sections)


def ledger(conflict=False):
    rows = [("__EH_prolog", EH_PROLOG, 1), ("??0B@@QAE@XZ", B_CTOR, 7), ("??0I@@QAE@XZ", I_CTOR, 7),
            ("??0D@@QAE@XZ", D_CTOR, 0x2e), ("??2@YAPAXI@Z", NEW, 1), ("?make@@YAPAVD@@XZ", MAKE, 15),
            ("??0W@@QAE@XZ", W_CTOR, 0x2d), ("??0V@@QAE@XZ", V_CTOR, 7)]
    if conflict:
        rows.append(("??0D@@QAE@H@Z", D_CTOR2, 7))
    return rl.Ledger([{"name": n, "target_rva": "%#x" % r, "target_size": str(s), "status": "matched"}
                      for n, r, s in rows])


@pytest.fixture
def engine():
    return rl.Engine(image(), ledger(), listed={})


def test_tables_are_classified_and_slots_stop_at_the_next_stored_table(engine):
    img = engine.image
    assert rl.classify(img, D_VT0) == "vftable" and rl.classify(img, VBT) == "vbtable"
    assert rl.classify(img, 0x2200) is None
    stored = engine.stored_tables()
    assert {B_VT, I_VT, D_VT0, D_VT10, VBT, V_VT} <= set(stored)
    got, why = rl.slots(img, D_VT0, engine.boundaries(stored))
    # Stub and mid-function targets are code, not known functions: still slots.
    assert [t for _, t in got] == [THUNK, THUNK + 1, THUNK + 2, THUNK + 3] and why == "next-table"
    assert rl.slots(img, D_VT10, engine.boundaries(stored)) == ([(0, THUNK + 5)], "non-code")


def test_constructor_proves_bases_by_call_and_by_inlined_table(engine):
    got = engine.contract("D")
    bases = {b["offset"]: (b["name"], b["rule"]) for b in got["facts"]["bases"]["value"]}
    assert bases == {0: ("B", "retail-ctor-call"), 0x10: ("I", "retail-inlined-base-vptr")}
    assert got["facts"]["vftables"]["value"] == {"0x0": "%#x" % D_VT0, "0x10": "%#x" % D_VT10}
    assert got["facts"]["fields"]["value"] == {"0x14": [4]}
    assert got["facts"]["vslots"]["value"]["count"] == 4
    assert got["conflicts"] == []


def test_operator_new_at_the_allocation_site_gives_sizeof(engine):
    got = engine.contract("D")
    assert got["facts"]["sizeof"]["value"] == 0x18
    assert got["facts"]["sizeof"]["rule"] == "retail-operator-new"
    assert got["confidence"] == "full"


def test_vbtable_places_and_names_the_virtual_base(engine):
    got = engine.contract("W")
    assert got["facts"]["vbptrs"]["value"] == {"0x4": "%#x" % VBT}
    (vbase,) = got["facts"]["virtual_bases"]["value"]
    assert (vbase["offset"], vbase["name"], vbase["via_vbptr"]) == (0x10, "V", 0)
    assert got["facts"]["vftables"]["value"]["0x10"] == "%#x" % W_VT_V
    assert "bases" not in got["facts"]


def test_disagreeing_constructors_are_flagged_not_voted():
    got = rl.Engine(image(), ledger(conflict=True), listed={}).contract("D")
    assert got["confidence"] == "conflict"
    assert [c["fact"] for c in got["conflicts"]] == ["vftables"]
    assert "vftables" not in got["facts"]


def retail(bases=(), virtual=(), size=None):
    facts = {}
    if bases:
        facts["bases"] = {"value": [{"offset": o, "name": n} for o, n in bases]}
    if virtual:
        facts["virtual_bases"] = {"value": [{"offset": 0x40, "name": n} for n in virtual]}
    if size is not None:
        facts["sizeof"] = {"value": size}
    return {"facts": facts, "conflicts": [], "confidence": "partial"}


def view(bases, size=0x20):
    return {"fwd": False, "key": "class", "size": size, "bases": [list(b) for b in bases], "fields": [],
            "vslots": {}, "vfptr": False}


POLY = {"vfptr": True, "bases": []}


def test_retail_bases_overrule_the_majority_and_keep_real_names():
    good = {"a.cpp": view([("Thing", 0)]), "b.cpp": view([("Thing", 0)]), "c.cpp": view([("ThingView", 0)])}
    every = {s: {"Thing": POLY, "ThingView": POLY} for s in good}
    got = contract.retail_bases("Object", retail([(0, "Thing"), (0x60, "Snapshot")], ["Iface"]), good, every)
    assert got == (["Thing", "Snapshot", "virtual Iface"], "retail-ctor", [])


def test_placeholder_base_takes_the_spelling_of_views_that_agree_with_retail():
    good = {"a.cpp": view([("Thing", 0), ("Snapshot", 0x60)]), "b.cpp": view([("Thing", 0)])}
    every = {s: {"Thing": POLY, "Snapshot": POLY} for s in good}
    got = contract.retail_bases("Object", retail([(0, "Thing"), (0x60, "Rva001234")]), good, every)
    assert got == (["Thing", "Snapshot"], "retail-ctor", [])


def test_a_base_no_one_names_is_queued():
    good = {"a.cpp": view([("Thing", 0)])}
    bases, rule, queue = contract.retail_bases("Object", retail([(0, "Thing"), (0x60, "<polymorphic base>")]),
                                               good, {"a.cpp": {"Thing": POLY}})
    assert bases == ["Thing", "<polymorphic base>"] and [q["attribute"] for q in queue] == ["base@0x60"]


def test_decide_takes_sizeof_and_bases_from_retail(monkeypatch):
    views = {"a.cpp": view([("Thing", 0)], 0x4D0), "b.cpp": view([("Thing", 0)], 0x4D0),
             "c.cpp": view([], 0x10)}
    every = {s: {"X": v, "Thing": POLY} for s, v in views.items()}
    monkeypatch.setattr(contract.class_layouts, "build_module", lambda: object())
    monkeypatch.setattr(contract, "ledger_rows", lambda: [])
    monkeypatch.setattr(contract, "views", lambda n, sources, jobs=8: (views, every))
    monkeypatch.setattr(contract, "zh_layout", lambda n, builder: None)
    monkeypatch.setattr(contract, "retail_access", lambda n, rows, builder: {})
    monkeypatch.setattr(contract, "retail_vtable", lambda n, rows, builder: {})
    monkeypatch.setattr(contract, "witnesses", lambda n: {})
    monkeypatch.setattr(contract, "retail_layout",
                        lambda n, rows, builder: retail([(0, "Thing"), (0x60, "Snapshot")], size=0x4D8))
    got = contract.decide("X", sources=sorted(views))
    assert (got["size"], got["size_by"]) == (0x4D8, "retail-new")
    assert (got["bases"], got["bases_by"]) == (["Thing", "Snapshot"], "retail-ctor")
    assert got["evidence"]["bases_overruled"]["majority"] == ["Thing"]


def test_without_a_retail_constructor_the_old_rules_decide(monkeypatch):
    assert contract.retail_layout("X", [], None) == {}
