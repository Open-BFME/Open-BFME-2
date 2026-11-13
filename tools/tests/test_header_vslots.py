"""header_adopt_lane: a generated header declares the contract's virtual slots in slot order."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import header_adopt_lane as lane  # noqa: E402

BASE_HEADER = """class Base {
public:
    virtual ~Base() {}
    virtual void xfer(Xfer *x) = 0;
protected:
    const ModuleData *m_moduleData;
};
"""

DERIVED_VIEW = """class Derived : public Base
{
public:
    virtual ~Derived();
    virtual void onCapture(Player *a, Player *b) {}
    virtual NameKeyType getKey() const = 0;
    virtual void xfer(Xfer *x);
private:
    Object *m_object;
};
"""
# A view that copied the base into the class: its xfer is no override.
FLAT_VIEW = """class Derived
{
public:
    virtual void s00();
    virtual void xfer(Xfer *x) { }
    virtual void onCapture(Player *, Player *) {}
    virtual NameKeyType getKey() const = 0;
    const ModuleData *m_moduleData;
    Object *m_object;
};
"""


def contract(vslots, queue=(), bases=("Base",), inherited=2):
    return {"class": "Derived", "key": "class", "key_by": "bytes", "size": 12, "size_by": "majority",
            "bases": list(bases), "fields": [{"offset": 8, "size": 4, "kind": "P", "type": "Object*",
                                              "name": "m_object"}],
            "vslots": {str(k): {"member": m, "decided_by": "bytes"} for k, m in vslots.items()},
            "evidence": {"inherited": {"inherited_slots": inherited}}, "queue": list(queue)}


@pytest.fixture
def base_header(tmp_path, monkeypatch):
    (tmp_path / "Base.h").write_text(BASE_HEADER, encoding="utf-8")
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(lane.class_contract, "ROOT", tmp_path)
    monkeypatch.setattr(lane.class_contract, "CONTRACTS", tmp_path / "contracts")
    return {"Base": "Base.h"}


def declare(c, views, known):
    return lane.slot_declarations(c, sorted(views), read=views.__getitem__, known=known)


def test_derived_class_declares_its_own_slots_in_order_and_overrides_its_bases(base_header, monkeypatch):
    monkeypatch.setattr(lane, "registered", lambda: base_header)
    c = contract({2: "onCapture(Player*,Player*)", 3: "getKey()"})
    views = {"a.cpp": DERIVED_VIEW, "b.cpp": DERIVED_VIEW, "flat.cpp": FLAT_VIEW}
    own, overrides, problems = declare(c, views, base_header)
    assert problems == []
    assert own == ["virtual void onCapture(Player *a, Player *b) {}", "virtual NameKeyType getKey() const = 0;"]
    assert overrides == ["virtual void xfer(Xfer *x);", "virtual ~Derived();"]
    text = lane.generate(c, "data", {"m": "virtual void s00();"}, "Derived.h", (own, overrides))
    body = text[text.index("class Derived"):]
    assert body.index("onCapture") < body.index("getKey") < body.index("xfer")
    assert "s00" not in text and '#include "Base.h"' in text


def test_inherited_slot_is_not_re_emitted(base_header):
    # Only the flattened view spells xfer: it copied the base, so it overrides nothing.
    c = contract({2: "onCapture(Player*,Player*)", 3: "getKey()"})
    own, overrides, problems = declare(c, {"flat.cpp": FLAT_VIEW}, base_header)
    assert problems == [] and overrides == []
    assert not any("xfer" in d or "s00" in d for d in own)


def test_pure_slot_is_pure_when_any_view_spells_it_pure(base_header, monkeypatch):
    monkeypatch.setattr(lane, "_matched_index", lambda: {})
    pure = "class Derived : public Base { public: virtual NameKeyType getKey() const = 0; };\n"
    plain = "class Derived : public Base { public: virtual NameKeyType getKey() const; };\n"
    inline = "class Derived : public Base { public: virtual NameKeyType getKey() const { return 0; } };\n"
    c = contract({2: "getKey()"})
    for views in ({"a.cpp": pure, "b.cpp": pure, "c.cpp": plain}, {"a.cpp": pure, "c.cpp": plain},
                  {"a.cpp": pure, "b.cpp": plain, "c.cpp": plain}):
        own, _, problems = declare(c, views, base_header)
        assert problems == [] and own == ["virtual NameKeyType getKey() const = 0;"]
    # a pure spelling beside an inline body contradicts it: the class is held
    _, _, problems = declare(c, {"a.cpp": pure, "b.cpp": inline, "c.cpp": inline}, base_header)
    assert problems == ["slot2 getKey(): pure in one view, an inline body in another"]
    # a matched row defines the member: `= 0` would put _purecall in its slot
    monkeypatch.setattr(lane, "_matched_index", lambda: {"?getKey@Derived@@": ["?getKey@Derived@@UBEHXZ"]})
    _, _, problems = declare(c, {"a.cpp": pure, "c.cpp": plain}, base_header)
    assert problems == ["slot2 getKey(): pure in a view, but a matched row defines it"]
    # an overload the row may define is no contradiction: non-virtual, another arity, or one of several
    for rows in (["?getKey@Derived@@QBEHH@Z"], ["?getKey@Derived@@UBEHH@Z"],
                 ["?getKey@Derived@@UBEHXZ", "?getKey@Derived@@UBEHH@Z"]):
        monkeypatch.setattr(lane, "_matched_index", lambda rows=rows: {"?getKey@Derived@@": rows})
        own, _, problems = declare(c, {"a.cpp": pure, "c.cpp": plain}, base_header)
        assert problems == [] and own == ["virtual NameKeyType getKey() const = 0;"]


def test_a_pure_slot_with_parameters_is_never_contradicted_by_a_same_arity_row(monkeypatch):
    # f(int) pure, f(double) defined: one virtual row of that name and arity is no proof.
    monkeypatch.setattr(lane, "_matched_index", lambda: {"?f@Solo@@": ["?f@Solo@@UAEXN@Z"]})
    view = "class Solo {\npublic:\n    virtual void f(int a) = 0;\n};\n"
    c = contract({0: "f(int)"}, bases=(), inherited=0)
    c["class"] = "Solo"
    own, _, problems = lane.slot_declarations(c, ["s.cpp"], read={"s.cpp": view}.__getitem__, known={})
    assert problems == [] and own == ["virtual void f(int a) = 0;"]


def test_a_pure_destructor_with_its_required_definition_stays_pure(monkeypatch):
    monkeypatch.setattr(lane, "_matched_index", lambda: {"??1Solo@@": ["??1Solo@@UAE@XZ"]})
    view = "class Solo {\npublic:\n    virtual ~Solo() = 0;\n};\n"
    c = contract({0: "__vecDelDtor(uint)"}, bases=(), inherited=0)
    c["class"] = "Solo"
    own, _, problems = lane.slot_declarations(c, ["s.cpp"], read={"s.cpp": view}.__getitem__, known={})
    assert problems == [] and own == ["virtual ~Solo() = 0;"]


def test_rva00589079_e1_views_keep_the_pure_specifier(monkeypatch):
    # The four views cd45be6a0c adopted (read at its parent): DeflectSpecialPower.cpp spells
    # `= 0`, the other three leave it out. The majority vote declared `virtual void fe();`,
    # an undefined virtual the link stubbed (round 13's stubbed.tsv).
    monkeypatch.setattr(lane, "_matched_index", lambda: {})
    pure = "class Rva00589079_E1\n{\npublic:\n\tvirtual void fe() = 0;\n};\n"
    plain = "class Rva00589079_E1\n{\npublic:\n\tvirtual void fe();\n};\n"
    views = {"DeflectSpecialPower.cpp": pure, "SiegeDeployHordeSpecialPowerXfer.cpp": plain,
             "SiegeDeploySpecialPower.cpp": plain, "WeaponModeSpecialPowerUpdateBase.cpp": plain}
    c = {"class": "Rva00589079_E1", "key": "class", "key_by": "majority", "size": 4, "size_by": "majority",
         "bases": [], "fields": [{"kind": "VPTR", "name": "__vfptr", "offset": 0, "size": 4, "type": "void*"}],
         "vslots": {"0": {"member": "fe()", "decided_by": "bytes"}}, "evidence": {}, "queue": []}
    own, overrides, problems = lane.slot_declarations(c, sorted(views), read=views.__getitem__, known={})
    assert problems == [] and own == ["virtual void fe() = 0;"]
    monkeypatch.setattr(lane, "registered", lambda: {})
    for variant in ("data", "data+ctor", "data+methods", "data+includes"):
        assert "virtual void fe() = 0;" in lane.generate(c, variant, {}, None, (own, overrides))


@pytest.mark.parametrize("vslots,queue,expected", [
    ({2: "onCapture(Player*,Player*)", 4: "getKey()"}, [], ["slot3 undecided"]),
    ({2: "onCapture(Player*,Player*)"}, [{"attribute": "slot3", "candidates": {}}], ["slot3 undecided"]),
    ({2: "onCapture(Player*,Player*)", 3: "missing()"}, [], ["slot3 missing(): no view spells it"]),
])
def test_undecided_slot_refuses_generation(base_header, vslots, queue, expected):
    own, _, problems = declare(contract(vslots, queue), {"a.cpp": DERIVED_VIEW}, base_header)
    assert problems == expected


def test_destructor_takes_its_target_slot_and_overloads_reverse():
    view = """class Solo {
public:
    virtual ~Solo() {}
    virtual void f(int a);
    virtual void f(float a);
    virtual int g();
};
"""
    c = contract({0: "__vecDelDtor(uint)", 1: "f(float)", 2: "f(int)", 3: "g()"}, bases=(), inherited=0)
    c["class"] = "Solo"
    own, overrides, problems = lane.slot_declarations(c, ["s.cpp"], read={"s.cpp": view}.__getitem__, known={})
    assert problems == [] and overrides == []
    # slot 1 f(float), slot 2 f(int): MSVC needs the group declared in reverse.
    assert own == ["virtual ~Solo() {}", "virtual void f(int a);", "virtual void f(float a);", "virtual int g();"]


def test_run_refuses_a_contract_with_an_undeclarable_slot(base_header, tmp_path, monkeypatch):
    import json
    import class_contract
    monkeypatch.setattr(class_contract, "CONTRACTS", tmp_path / "contracts")
    monkeypatch.setattr(class_contract, "census", lambda name: ["a.cpp"])
    monkeypatch.setattr(lane, "registered", lambda: base_header)
    (tmp_path / "a.cpp").write_text(DERIVED_VIEW, encoding="utf-8")
    path = class_contract.contract_path("Derived")
    path.parent.mkdir()
    path.write_text(json.dumps(contract({2: "onCapture(Player*,Player*)", 4: "getKey()"})), encoding="utf-8")
    args = type("A", (), {"name": "Derived", "header": "Derived.h", "generate": True, "sample": None, "seed": 1,
                          "jobs": 1, "variants": "data", "apply": False})()
    monkeypatch.setattr(lane, "tournament", lambda *a, **k: pytest.fail("generated despite an undecided slot"))
    assert lane.run(args) == 2


def test_slot_declarations_include_the_registered_classes_they_name(monkeypatch):
    monkeypatch.setattr(lane, "registered", lambda: {"Coord3D": "Code/Lib/Coord3D.h", "Iface": "Code/Iface.h"})
    c = contract({0: "onCollide(Object*,Coord3D*)"}, bases=(), inherited=0)
    c["class"] = "Iface"
    own = ["virtual void onCollide(Object *other, const Coord3D *loc) = 0;"]
    assert "Coord3D.h" not in lane.generate(c, "data", {}, "Code/Iface.h", (own, []))
    text = lane.generate(c, "data+includes", {}, "Code/Iface.h", (own, []))
    assert '#include "Lib/Coord3D.h"' in text
    assert lane.nested_includes(c, "Code/Iface.h") == []


if __name__ == "__main__":
    sys.exit(pytest.main([__file__, "-q"]))


# ---- P147: no inline body for a slot a matched row's source defines out of line

def owned_view(dtor, get="virtual int get() const;"):
    return f"""class Owned
{{
public:
    Owned(int x);
    {dtor}
    {get}
    int m_04;
}};
"""


OWNED_DTOR = {"??1Owned@@": [("??1Owned@@UAE@XZ", "Base.cpp")]}
STRONG_DTOR = "class Owned\n{\npublic:\n    virtual ~Owned();\n};\n\nOwned::~Owned()\n{\n}\n"
INLINE_DTOR = "class Owned\n{\npublic:\n    virtual ~Owned();\n};\n\ninline Owned::~Owned()\n{\n}\n"


def owned_contract(vslots):
    c = contract(vslots, bases=(), inherited=0)
    c["class"] = "Owned"
    return c


def owned_slots(tmp_path, monkeypatch, views, owner_text, owners=OWNED_DTOR, vslots=None):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    if owner_text is not None:
        (tmp_path / "Base.cpp").write_text(owner_text, encoding="latin-1")
    texts = {f"v{i}.cpp": v for i, v in enumerate(views)}
    return lane.slot_declarations(owned_contract(vslots or {0: "__vecDelDtor(uint)"}), sorted(texts),
                                  read=texts.__getitem__, known={}, owners=owners)


def test_p147_an_out_of_line_owner_wins_over_one_inline_view(tmp_path, monkeypatch):
    # 242fa829c92: one view spelled `virtual ~Rva0058AD7A() {}`, five declared it without a body, and
    # Rva0058AD7ABase.cpp defines it out of line; the header's inline body made a duplicate definition
    views = [owned_view("virtual ~Owned() {}")] + [owned_view("virtual ~Owned();")] * 5
    own, _, problems = owned_slots(tmp_path, monkeypatch, views, STRONG_DTOR)
    assert problems == [] and own == ["virtual ~Owned();"]


def test_an_out_of_line_owner_strips_the_body_every_view_spells(tmp_path, monkeypatch):
    own, _, problems = owned_slots(tmp_path, monkeypatch, [owned_view("virtual ~Owned() {}")] * 3, STRONG_DTOR)
    assert problems == [] and own == ["virtual ~Owned();"]


def test_a_split_with_no_out_of_line_owner_holds_the_class(tmp_path, monkeypatch):
    views = [owned_view("virtual ~Owned() {}")] + [owned_view("virtual ~Owned();")] * 2
    own, _, problems = owned_slots(tmp_path, monkeypatch, views, None, owners={})
    assert own == [] and problems and "an inline body in one view, none in another" in problems[0]
    # an owner that spells the definition `inline` is a COMDAT copy like the header's: still a split
    own, _, problems = owned_slots(tmp_path, monkeypatch, views, INLINE_DTOR)
    assert own == [] and "no matched row defines it out of line" in problems[0]


def test_an_inline_owner_keeps_an_inline_body_every_view_spells(tmp_path, monkeypatch):
    # Rva00074626 / Region3D: the owner's copy comes from an `inline` definition, as the header's would
    own, _, problems = owned_slots(tmp_path, monkeypatch, [owned_view("virtual ~Owned() {}")] * 2, INLINE_DTOR)
    assert problems == [] and own == ["virtual ~Owned() {}"]


def test_the_rule_holds_for_a_virtual_that_is_not_the_destructor(tmp_path, monkeypatch):
    views = [owned_view("virtual ~Owned();", "virtual int get() const { return 1; }")] + \
            [owned_view("virtual ~Owned();", "virtual int get() const;")] * 2
    owners = {"?get@Owned@@": [("?get@Owned@@UBEHXZ", "Base.cpp")]}
    strong = "int Owned::get() const\n{\n    return 1;\n}\n"
    own, _, problems = owned_slots(tmp_path, monkeypatch, views, strong, owners=owners,
                                   vslots={0: "__vecDelDtor(uint)", 1: "get()"})
    assert problems == [] and "virtual int get() const;" in own
    # another overload's definition is not this slot's owner: the split holds
    other = "int Owned::get(int a) const\n{\n    return a;\n}\n"
    own, _, problems = owned_slots(tmp_path, monkeypatch, views, other, owners=owners,
                                   vslots={0: "__vecDelDtor(uint)", 1: "get()"})
    assert any("slot1" in p and "an inline body in one view" in p for p in problems), problems


def test_a_call_or_a_declaration_is_no_owner_definition(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Base.cpp").write_text("class Owned { public: virtual ~Owned(); };\n"
                                       "void f(Owned *p) { p->Owned::~Owned(); }\n", encoding="latin-1")
    assert lane.owner_definitions("Owned", "virtual ~Owned() {}", OWNED_DTOR) == []
    (tmp_path / "Base.cpp").write_text("// Owned::~Owned() { } in a comment\n#include \"x.h\"\n"
                                       "Owned::~Owned() { }\n", encoding="latin-1")
    assert lane.owner_definitions("Owned", "virtual ~Owned() {}", OWNED_DTOR) == [("Base.cpp", False)]


def test_generate_refuses_an_inline_virtual_a_strong_owner_defines(base_header, tmp_path):
    # the check that keeps P147 from coming back by any path: whatever declares a virtual member
    # with an inline body beside a strong out-of-line definition, generate refuses the header
    (tmp_path / "Base.cpp").write_text(STRONG_DTOR, encoding="latin-1")
    c = owned_contract({0: "__vecDelDtor(uint)"})
    with pytest.raises(lane.LayoutError, match="Base.cpp defines it out of line"):
        lane.generate(c, "data", {}, None, (["virtual ~Owned() {}"], []), (), owners=OWNED_DTOR)
    assert "virtual ~Owned();" in lane.generate(c, "data", {}, None, (["virtual ~Owned();"], []), (),
                                                owners=OWNED_DTOR)


def test_generate_keeps_a_non_virtual_inline_body_beside_a_strong_owner(base_header, tmp_path):
    # Region3D::depth: the units that inline a non-virtual body need it, and none emits a copy
    # unless it does not inline it, so that shape is not refused
    (tmp_path / "Base.cpp").write_text("int Owned::get() const\n{\n    return 1;\n}\n", encoding="latin-1")
    c = owned_contract({})
    c["vslots"] = {}
    special = [{"role": "method", "access": "public", "sig": "get()const", "text": "int get() const { return 1; }"}]
    text = lane.generate(c, "data", {}, None, None, special,
                         owners={"?get@Owned@@": [("?get@Owned@@QBEHXZ", "Base.cpp")]})
    assert "int get() const { return 1; }" in text
