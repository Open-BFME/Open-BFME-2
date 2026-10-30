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
P_CTOR, M_CTOR, B2_CTOR, B2_SITE, C3_CTOR, C3_SITE, ARRAY_SITE, NEW_ARRAY = \
    0x1700, 0x1780, 0x1800, 0x1840, 0x1880, 0x18C0, 0x1900, 0x1290
P_VT, M_VT, X_VT, B2_VT, DD_VT = 0x2300, 0x2308, 0x2310, 0x2318, 0x2320
NB_CTOR, ND_CTOR, S2_SITE, S6_SITE = 0x1A00, 0x1A40, 0x1A80, 0x1C00
NB_VT, NM_VT, ND_VT0, S2_D_VT, S6_D_VT = 0x2400, 0x2410, 0x2420, 0x2430, 0x2440
NE_CTOR, MB_CTOR, Q_CTOR, CONT = 0x1D00, 0x1D40, 0x1D80, 0x1DC0
MB_VT, MD_VT, NE_VT, Q_VBT, Q_VT = 0x2450, 0x2458, 0x2460, 0x2470, 0x2478
S_CTOR, S_VBT0, S_VBT8 = 0x1F00, 0x2480, 0x2488
# R3 S6 allocation sites: (ledger name, rva, size) per reproduction.
TAILS = {"jmp": ("?makeJ@@YAXXZ", 0x1E00, 0x17), "cont": ("?makeC@@YAXXZ", 0x1E40, 0x14),
         "lea": ("?makeL@@YAXXZ", 0x1E80, 0x1b), "ebp": ("?makeE@@YAXXZ", 0x1EC0, 0x1a)}


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


def image(sites=("s2", "s6")):
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
    # P::P(): its own table, then a member at +0x10 (ctor call, then a store) and a bare store at +0x20.
    b.code(P_CTOR, b"\x8b\xf1", b"\xc7\x06" + imm(VA + P_VT), b"\x8d\x4e\x10", lambda at: call(at, M_CTOR),
           b"\xc7\x46\x10" + imm(VA + M_VT), b"\xc7\x46\x20" + imm(VA + X_VT), b"\xc3")
    b.code(M_CTOR, b"\xc7\x01" + imm(VA + M_VT), b"\xc3")
    # new(0x24), B2::B2, then a derived table over it: an inlined derived constructor.
    b.code(B2_CTOR, b"\xc7\x01" + imm(VA + B2_VT), b"\xc3")
    b.code(B2_SITE, b"\x6a\x24", lambda at: call(at, NEW), b"\x8b\xc8", lambda at: call(at, B2_CTOR),
           b"\xc7\x00" + imm(VA + DD_VT), b"\xc3")
    # C3::C3 installs B's table, not one of its own: not a complete-object constructor.
    b.code(C3_CTOR, b"\xc7\x01" + imm(VA + B_VT), b"\xc3")
    b.code(C3_SITE, b"\x6a\x30", lambda at: call(at, NEW), b"\x8b\xc8", lambda at: call(at, C3_CTOR), b"\xc3")
    # operator new[](0x40) feeding D::D: count and cookie unresolved.
    b.code(NEW_ARRAY, b"\xc3")
    b.code(ARRAY_SITE, b"\x6a\x40", lambda at: call(at, NEW_ARRAY), b"\x8b\xc8", lambda at: call(at, D_CTOR),
           b"\xc3")
    # NB::NB(): its own table, then a polymorphic member at +0x10 built inline.
    b.code(NB_CTOR, b"\xc7\x01" + imm(VA + NB_VT), b"\xc7\x41\x10" + imm(VA + NM_VT), b"\xc3")
    # ND::ND() inlines NB::NB() (its table and its member), then installs ND's own table at +0.
    b.code(ND_CTOR, b"\xc7\x01" + imm(VA + NB_VT), b"\xc7\x41\x10" + imm(VA + NM_VT),
           b"\xc7\x01" + imm(VA + ND_VT0), b"\xc3")
    # new(0x24); B2::B2(); 20 field stores; then a derived table over the object.
    fields = b"".join(b"\xc7\x40" + bytes([4 + 4 * i]) + imm(0) for i in range(20))
    if "s2" in sites:
        b.code(S2_SITE, b"\x6a\x24", lambda at: call(at, NEW), b"\x8b\xc8", lambda at: call(at, B2_CTOR),
               fields, b"\xc7\x00" + imm(VA + S2_D_VT), b"\xc3")
    # The same, with the derived table stored through an indexed operand.
    if "s6" in sites:
        b.code(S6_SITE, b"\x6a\x24", lambda at: call(at, NEW), b"\x8b\xc8", lambda at: call(at, B2_CTOR),
               b"\xc7\x04\x08" + imm(VA + S6_D_VT), b"\xc3")
    # NE::NE() inlines NB::NB() building a derived member at +0x10 (MB::MB, then
    # MD's table over it), then installs NE's own table at +0.
    b.code(MB_CTOR, b"\xc7\x01" + imm(VA + MB_VT), b"\xc3")
    b.code(NE_CTOR, b"\x8b\xf1", b"\xc7\x06" + imm(VA + NB_VT), b"\x8d\x4e\x10", lambda at: call(at, MB_CTOR),
           b"\xc7\x46\x10" + imm(VA + MD_VT), b"\xc7\x06" + imm(VA + NE_VT), b"\xc3")
    # Q::Q(): a vbptr at +0 and no table at +0; its member at +0x20, then its table at +0x10.
    b.code(Q_CTOR, b"\x8b\xf1", b"\xc7\x06" + imm(VA + Q_VBT), b"\x8d\x4e\x20", lambda at: call(at, MB_CTOR),
           b"\xc7\x46\x20" + imm(VA + MD_VT), b"\xc7\x46\x10" + imm(VA + Q_VT), b"\xc3")
    b.code(CONT, b"\xc7\x01" + imm(VA + DD_VT), b"\xc3")
    # S::S() (strstream's shape): a constructor call at +0, then vbptrs at +0 and +8, no vftable.
    b.code(S_CTOR, b"\x8b\xf1", b"\x8b\xce", lambda at: call(at, B_CTOR), b"\xc7\x06" + imm(VA + S_VBT0),
           b"\xc7\x46\x08" + imm(VA + S_VBT8), b"\xc3")
    new_b2 = (b"\x6a\x24", lambda at: call(at, NEW), b"\x8b\xc8", lambda at: call(at, B2_CTOR))
    new_b2_esi = (b"\x6a\x24", lambda at: call(at, NEW), b"\x8b\xf0", b"\x8b\xce", lambda at: call(at, B2_CTOR))
    tails = {"jmp": new_b2 + (b"\xeb\x00", b"\xc7\x00" + imm(VA + S2_D_VT), b"\xc3"),
             "cont": new_b2 + (lambda at: call(at, CONT), b"\xc3"),
             "lea": new_b2_esi + (b"\x8d\x7e\xf0", b"\xc7\x47\x10" + imm(VA + S2_D_VT), b"\xc3"),
             "ebp": new_b2_esi + (b"\x8b\xee", b"\xc7\x45\x00" + imm(VA + S2_D_VT), b"\xc3")}
    for key, parts in tails.items():
        if key in sites:
            b.code(TAILS[key][1], *parts)
    t = VA + THUNK
    b.words(P_VT, t, 0, t, 0, t, 0, t, 0, t, 0)
    b.words(B_VT, t, t + 4)
    b.words(I_VT, t, t + 8)
    b.words(D_VT0, t, t + 1, t + 2, t + 3)
    b.words(D_VT10, t + 5, 0)
    b.words(VBT, -4, 0x0C)
    b.words(W_VT, t, 0, t, 0, t, 0)
    b.words(NB_VT, t, 0)
    b.words(NM_VT, t, 0)
    b.words(ND_VT0, t, t + 1)
    b.words(S2_D_VT, t, 0)
    b.words(S6_D_VT, t, 0)
    b.words(MB_VT, t, 0)
    b.words(MD_VT, t, 0)
    b.words(NE_VT, t, 0)
    b.words(Q_VBT, 0, 0x30)
    b.words(Q_VT, t, 0)
    b.words(S_VBT0, 0, 0x30)
    b.words(S_VBT8, 0, 0x28)
    sections = [{"name": ".text", "rva": 0x1000, "size": 0x1000}, {"name": ".rdata", "rva": 0x2000, "size": 0x1000}]
    return rl.Image(lambda rva, size: bytes(b.mem[rva:rva + size]), sections)


def ledger(conflict=False):
    rows = [("__EH_prolog", EH_PROLOG, 1), ("??0B@@QAE@XZ", B_CTOR, 7), ("??0I@@QAE@XZ", I_CTOR, 7),
            ("??0D@@QAE@XZ", D_CTOR, 0x2e), ("??2@YAPAXI@Z", NEW, 1), ("?make@@YAPAVD@@XZ", MAKE, 15),
            ("??0W@@QAE@XZ", W_CTOR, 0x2d), ("??0V@@QAE@XZ", V_CTOR, 7), ("??0P@@QAE@XZ", P_CTOR, 0x1f),
            ("??0M@@QAE@XZ", M_CTOR, 7), ("??0B2@@QAE@XZ", B2_CTOR, 7), ("?make2@@YAXXZ", B2_SITE, 0x15),
            ("??0C3@@QAE@XZ", C3_CTOR, 7), ("?make3@@YAXXZ", C3_SITE, 0x0f), ("??_U@YAPAXI@Z", NEW_ARRAY, 1),
            ("?makeArray@@YAXXZ", ARRAY_SITE, 0x0f), ("??0NB@@QAE@XZ", NB_CTOR, 0x0f),
            ("??0ND@@QAE@XZ", ND_CTOR, 0x15), ("?makeS2@@YAXXZ", S2_SITE, 0xa1),
            ("?makeS6@@YAXXZ", S6_SITE, 0x16), ("??0NE@@QAE@XZ", NE_CTOR, 0x1e), ("??0MB@@QAE@XZ", MB_CTOR, 7),
            ("??0Q@@QAE@XZ", Q_CTOR, 0x1f), ("?cont@@YAXXZ", CONT, 7), ("??0S@@QAE@XZ", S_CTOR, 0x17)]
    if conflict:
        rows.append(("??0D@@QAE@H@Z", D_CTOR2, 7))
    return rl.Ledger([{"name": n, "target_rva": "%#x" % r, "target_size": str(s), "status": "matched"}
                      for n, r, s in rows])


def without(*names):
    """The test ledger minus the named rows (one reproduction at a time)."""
    return rl.Ledger([r for r in ledger().rows if r["name"] not in names])


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


def test_tables_stored_after_the_own_vptr_are_unknown_subobjects_not_bases(engine):
    # S1 (Player +0x90/+0x1BC): a member's table stored after the class installs its own.
    got = engine.contract("P")
    assert "bases" not in got["facts"]
    assert got["facts"]["vftables"]["value"] == {"0x0": "%#x" % P_VT}
    assert set(got["facts"]["unknown_subobject_vptrs"]["value"]) == {"0x10", "0x20"}
    assert got["facts"]["unknown_subobject_vptrs"]["kind"] == "inference"
    assert "0x10" in got["facts"]["member_ctor_calls"]["value"]


def test_base_ctor_inside_an_inlined_derived_ctor_gets_no_sizeof(engine):
    # S2: new(0x24); B2::B2; then the derived table over the same object.
    assert "sizeof" not in engine.contract("B2")["facts"]


def test_ctor_that_installs_no_table_of_its_own_only_observes_the_allocation(engine):
    # S2: C3::C3 stores B's table, so the allocation may hold a derived object.
    got = engine.contract("C3")["facts"]
    assert "sizeof" not in got and got["allocation_observed"]["value"] == {"0x30": 1}


def test_array_new_is_no_sizeof_evidence(engine):
    # S3: operator new[](0x40) feeds D::D too; only the scalar site counts.
    got = engine.contract("D")
    assert got["facts"]["sizeof"]["value"] == 0x18 and len(got["facts"]["sizeof"]["sites"]) == 1
    assert NEW_ARRAY not in engine.ledger.allocators()


def test_agreeing_view_cannot_rename_a_retail_virtual_base():
    # S4: the view's base shape agrees with retail, but it names the virtual base Wrong.
    good = {"a.cpp": view([("Thing", 0), ("virtual Wrong", -1)])}
    bases, rule, queue = contract.retail_bases("X", retail([(0, "Thing")], ["V"]), good, {"a.cpp": {"Thing": POLY}})
    assert bases == ["Thing", "virtual V"] and rule == "retail-ctor"
    assert [q["attribute"] for q in queue] == ["virtual-base"]


def test_an_inlined_base_member_vptr_stays_a_member_in_the_derived_class(engine):
    # S1/S5: NB-vptr@0; member-vptr@0x10; ND-vptr@0. +0x10 is NB's member, not an ND base.
    got = engine.contract("ND")
    bases = {b["offset"]: (b["name"], b["rule"]) for b in got["facts"]["bases"]["value"]}
    assert bases == {0: ("NB", "retail-inlined-base-vptr")}
    assert set(got["facts"]["unknown_subobject_vptrs"]["value"]) == {"0x10"}
    # Standalone NB treats the same store as its own member.
    nb = engine.contract("NB")
    assert "bases" not in nb["facts"]
    assert set(nb["facts"]["unknown_subobject_vptrs"]["value"]) == {"0x10"}


def test_a_derived_table_after_many_field_stores_blocks_sizeof():
    # S2/S6: new(0x24); B2::B2(); 20 field stores; then a derived table. A fixed
    # 16-instruction window never reaches the store.
    got = rl.Engine(image(("s2",)), without("?makeS6@@YAXXZ"), listed={}).contract("B2")["facts"]
    assert "sizeof" not in got
    assert got["allocation_observed"]["value"] == {"0x24": 2}


def test_an_indexed_derived_table_store_blocks_sizeof():
    # S6: the derived table is stored through an indexed operand, so retail
    # does not resolve the allocation's dynamic type.
    got = rl.Engine(image(("s6",)), without("?makeS2@@YAXXZ"), listed={}).contract("B2")["facts"]
    assert "sizeof" not in got
    assert got["allocation_observed"]["value"] == {"0x24": 2}


def test_replacing_a_called_ctor_table_before_the_primary_proves_no_base(engine):
    # R3 S5: NB inlined into NE builds a derived member: MB::MB at +0x10, MD's
    # table over it, then NE's own table at +0. MB is NE's member, not a base.
    got = engine.contract("NE")["facts"]
    assert {b["offset"]: b["name"] for b in got["bases"]["value"]} == {0: "NB"}
    assert got["vftables"]["value"] == {"0x0": "%#x" % NE_VT}
    assert got["unknown_subobject_vptrs"]["value"] == {"0x10": ["%#x" % MD_VT]}
    assert "0x10" in got["member_ctor_calls"]["value"]


def test_without_a_primary_store_no_other_offset_store_becomes_a_base(engine):
    # R3 S5: vbptr at +0, its member at +0x20 stored first, its table at +0x10.
    got = engine.contract("Q")["facts"]
    assert {b["offset"] for b in got.get("bases", {}).get("value", [])} <= {0}
    assert "vftables" not in got
    assert set(got["unknown_subobject_vptrs"]["value"]) == {"0x10", "0x20"}
    assert "0x20" in got["member_ctor_calls"]["value"]


def test_a_base_or_member_call_leaves_the_base_clause_unproven(engine):
    # R4: with no vftable, the call at +0 may be a base or a member, so a
    # clause of the vbptr owner at +8 plus the virtual bases would be false.
    got = engine.contract("S")["facts"]
    assert "bases" not in got and "virtual_bases" not in got
    assert got["bases_unproven"]["kind"] == got["virtual_bases_unproven"]["kind"] == "inference"
    assert set(got["base_or_member_ctor_calls"]["value"]) == {"0x0"}
    assert contract.retail_bases("S", {"facts": got}, {}, {}) is None


@pytest.mark.parametrize("tail", sorted(TAILS))
def test_an_unresolved_allocation_tail_gives_no_sizeof(tail):
    # R3 S6: B2(); jmp L; L: derived store / B2(); call continuation; ret /
    # lea edi,[esi-0x10]; store via [edi+0x10] / mov ebp,esi; store via [ebp].
    name, rva, size = TAILS[tail]
    rows = without("?makeS2@@YAXXZ", "?makeS6@@YAXXZ").rows
    rows.append({"name": name, "target_rva": "%#x" % rva, "target_size": str(size), "status": "matched"})
    got = rl.Engine(image((tail,)), rl.Ledger(rows), listed={}).contract("B2")["facts"]
    assert "sizeof" not in got
    assert got["allocation_observed"]["value"] == {"0x24": 2}
