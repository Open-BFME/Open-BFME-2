"""header_adopt_lane: a generated header declares the contract's virtual slots in slot order."""
import subprocess
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


# ---- P147: no inline body for a slot a matched row's owner defines exclusively

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


DTOR_ROW = "??1Owned@@UAE@XZ"
GET_ROW = "?get@Owned@@UBEHXZ"
OWNED_DTOR = {"??1Owned@@": [(DTOR_ROW, "Base.cpp")]}
OWNED_GET = {"?get@Owned@@": [(GET_ROW, "Base.cpp")]}


def objects(monkeypatch, local=None, census=None):
    """The owner's current object here: {source: (exclusive, defined)} (absent: none current);
    the census index: {(row, source): 'strong' | 'inline'} (absent: it does not show the row)."""
    local, census = local or {}, census or {}
    monkeypatch.setattr(lane, "local_facts", lambda source: local.get(source))
    monkeypatch.setattr(lane, "census_strength", lambda row, source: census.get((row, source)))


STRONG = {"Base.cpp": ({DTOR_ROW, GET_ROW}, {DTOR_ROW, GET_ROW})}
INLINE = {"Base.cpp": (set(), {DTOR_ROW, GET_ROW})}


def owned_contract(vslots):
    c = contract(vslots, bases=(), inherited=0)
    c["class"] = "Owned"
    return c


def owned_slots(views, owners=OWNED_DTOR, vslots=None):
    texts = {f"v{i}.cpp": v for i, v in enumerate(views)}
    return lane.slot_declarations(owned_contract(vslots or {0: "__vecDelDtor(uint)"}), sorted(texts),
                                  read=texts.__getitem__, known={}, owners=owners)


def test_p147_an_exclusive_owner_wins_over_one_inline_view(monkeypatch):
    # 242fa829c92: one view spelled `virtual ~Rva0058AD7A() {}`, five declared it without a body, and
    # Rva0058AD7ABase.cpp defines it out of line; the header's inline body made a duplicate definition
    objects(monkeypatch, local=STRONG)
    views = [owned_view("virtual ~Owned() {}")] + [owned_view("virtual ~Owned();")] * 5
    own, _, problems = owned_slots(views)
    assert problems == [] and own == ["virtual ~Owned();"]


def test_an_exclusive_owner_strips_the_body_every_view_spells(monkeypatch):
    objects(monkeypatch, census={(DTOR_ROW, "Base.cpp"): "strong"})       # from the census when not built here
    own, _, problems = owned_slots([owned_view("virtual ~Owned() {}")] * 3)
    assert problems == [] and own == ["virtual ~Owned();"]


def test_a_split_with_no_exclusive_owner_holds_the_class(monkeypatch):
    objects(monkeypatch, local=INLINE)
    views = [owned_view("virtual ~Owned() {}")] + [owned_view("virtual ~Owned();")] * 2
    own, _, problems = owned_slots(views, owners={})
    assert own == [] and problems and "an inline body in one view, none in another" in problems[0]
    # an owner whose copy is a discardable COMDAT (an `inline` definition) is no exclusive owner: still a split
    own, _, problems = owned_slots(views)
    assert own == [] and "no matched row defines it out of line" in problems[0]


def test_an_inline_owner_keeps_an_inline_body_every_view_spells(monkeypatch):
    # Rva00074626 / Region3D: the owner's copy is a COMDAT like the header's would be
    objects(monkeypatch, local=INLINE)
    own, _, problems = owned_slots([owned_view("virtual ~Owned() {}")] * 2)
    assert problems == [] and own == ["virtual ~Owned() {}"]


def test_the_rule_holds_for_a_virtual_that_is_not_the_destructor(monkeypatch):
    objects(monkeypatch, local=STRONG)
    views = [owned_view("virtual ~Owned();", "virtual int get() const { return 1; }")] + \
            [owned_view("virtual ~Owned();", "virtual int get() const;")] * 2
    own, _, problems = owned_slots(views, owners=OWNED_GET, vslots={0: "__vecDelDtor(uint)", 1: "get()"})
    assert problems == [] and "virtual int get() const;" in own


@pytest.mark.parametrize("local,census,owners,why", [
    ({}, {}, OWNED_DTOR, "census index does not show its definition"),         # not built here, not in the census
    ({"Base.cpp": (set(), set())}, {}, OWNED_DTOR, "does not define it"),         # the current object lacks the row
    (STRONG, {}, {"??1Owned@@": [(DTOR_ROW, "Base.cpp"), ("??1Owned@@QAE@XZ", "Other.cpp")]},
     "census index does not show"),
    ({"Base.cpp": ({DTOR_ROW}, {DTOR_ROW}), "Other.cpp": (set(), {"??1Owned@@QAE@XZ"})}, {},
     {"??1Owned@@": [(DTOR_ROW, "Base.cpp"), ("??1Owned@@QAE@XZ", "Other.cpp")]}, "differ"),
], ids=["no-evidence", "object-lacks-row", "second-owner-unknown", "owners-disagree"])
def test_an_owner_it_cannot_establish_holds_the_class(monkeypatch, local, census, owners, why):
    # review r1: unavailable owner evidence failed open (an unreadable source was skipped)
    objects(monkeypatch, local=local, census=census)
    own, _, problems = owned_slots([owned_view("virtual ~Owned() {}")] * 2, owners=owners)
    assert own == [] and any(why in p for p in problems), problems


def test_an_unreadable_ledger_is_never_no_owners(base_header, tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "LEDGER", tmp_path / "missing" / "functions.csv")
    with pytest.raises(lane.OwnerUnknown, match="cannot be read"):
        lane.owner_strength("Owned", "virtual ~Owned() {}")
    c = owned_contract({0: "__vecDelDtor(uint)"})
    with pytest.raises(lane.LayoutError, match="cannot be read"):
        lane.generate(c, "data", {}, None, (["virtual ~Owned() {}"], []), ())


@pytest.mark.parametrize("member,prefix", [
    ("virtual ~Owned() {}", "??1Owned@@"),
    ("virtual int operator()(int a) { return a; }", "??ROwned@@"),
    ("virtual bool operator == (const Owned &o) const { return true; }", "??8Owned@@"),
    ("virtual int &operator[](int i) { return m; }", "??AOwned@@"),
    ("virtual int get() const volatile { return 1; }", "?get@Owned@@"),
])
def test_rows_are_found_by_their_mangled_prefix(member, prefix):
    # review r1: a definition's spelling (`::Owned::~Owned`, a namespace, a macro, operator()) no longer
    # matters: the rows are found by name and judged by their owner's object
    assert lane.member_prefix("Owned", member) == prefix
    assert lane.member_prefix("Outer::Owned", member) == prefix.replace("Owned@@", "Owned@Outer@@")


def test_a_member_it_cannot_mangle_is_unknown():
    with pytest.raises(lane.OwnerUnknown):
        lane.member_prefix("Owned", "virtual operator int() const { return 1; }")


def coff(sections, symbols, strings=b""):
    """A minimal COFF object: sections [(name, characteristics)], symbols [(name, value, section, storage,
    aux selection or None)]; a section symbol with a selection carries its aux record."""
    import struct
    header_size, section_size = 20, 40
    table = header_size + section_size * len(sections)
    records, count, table_strings = b"", 0, b""
    for name, value, section, storage, selection in symbols:
        raw = name.encode()
        if len(raw) <= 8:
            field = raw.ljust(8, b"\0")
        else:
            field = struct.pack("<II", 0, 4 + len(table_strings))
            table_strings += raw + b"\0"
        aux = 1 if selection is not None else 0
        records += field + struct.pack("<IhHBB", value, section, 0, storage, aux)
        count += 1
        if aux:
            records += struct.pack("<IHHIHB3x", 0, 0, 0, 0, 0, selection)
            count += 1
    data = struct.pack("<HHIIIHH", 0x14C, len(sections), 0, table, count, 0, 0)
    for name, characteristics in sections:
        data += name.encode().ljust(8, b"\0") + struct.pack("<IIIIIIHHI", 0, 0, 0, 0, 0, 0, 0, 0, characteristics)
    return data + records + struct.pack("<I", 4 + len(table_strings)) + table_strings


def test_exclusive_definitions_follow_the_linkers_rule():
    # an ordinary section and a NODUPLICATES COMDAT (/Gy's non-inline function) are exclusive; an ANY
    # COMDAT (an inline body's copy) is a definition only; an undefined external is neither
    data = coff([(".text", 0x60000020), (".text", 0x60001020), (".text", 0x60001020)],
                [("?strong@@YAXXZ", 0, 1, 2, None),
                 (".text", 0, 2, 3, 1), ("?nodup@@YAXXZ", 0, 2, 2, None),
                 (".text", 0, 3, 3, 2), ("?any@@YAXXZ", 0, 3, 2, None),
                 ("?ref@@YAXXZ", 0, 0, 2, None)])
    exclusive, defined = lane.exclusive_definitions(data)
    assert exclusive == {"?strong@@YAXXZ", "?nodup@@YAXXZ"}
    assert defined == {"?strong@@YAXXZ", "?nodup@@YAXXZ", "?any@@YAXXZ"}


def test_generate_refuses_an_inline_virtual_an_exclusive_owner_defines(base_header, monkeypatch):
    # the check that keeps P147 from coming back by any path
    objects(monkeypatch, local=STRONG)
    c = owned_contract({0: "__vecDelDtor(uint)"})
    with pytest.raises(lane.LayoutError, match="defines it exclusively"):
        lane.generate(c, "data", {}, None, (["virtual ~Owned() {}"], []), (), owners=OWNED_DTOR)
    assert "virtual ~Owned();" in lane.generate(c, "data", {}, None, (["virtual ~Owned();"], []), (),
                                                owners=OWNED_DTOR)
    objects(monkeypatch)
    with pytest.raises(lane.LayoutError, match="census index does not show"):
        lane.generate(c, "data", {}, None, (["virtual ~Owned() {}"], []), (), owners=OWNED_DTOR)


def test_generate_keeps_a_non_virtual_inline_body_beside_an_exclusive_owner(base_header, monkeypatch):
    # Region3D::depth: the units that inline a non-virtual body need it, and none emits a copy
    # unless it does not inline it, so that shape is not refused
    objects(monkeypatch, local=STRONG)
    c = owned_contract({})
    c["vslots"] = {}
    special = [{"role": "method", "access": "public", "sig": "get()const", "text": "int get() const { return 1; }"}]
    assert "int get() const { return 1; }" in lane.generate(c, "data", {}, None, None, special, owners=OWNED_GET)


# ---- review r2: overloads, attributes, ledger reads, census freshness

def test_another_overloads_owner_is_not_this_ones(monkeypatch):
    # only get(int) is rowed (and strong); the inline virtual get() has no owner of its own
    other = "?get@Owned@@UAEHH@Z"
    objects(monkeypatch, local={"Base.cpp": ({other}, {other})})
    owners = {"?get@Owned@@": [(other, "Base.cpp")]}
    assert lane.owner_strength("Owned", "virtual int get() { return 1; }", owners) is None
    assert lane.owner_strength("Owned", "virtual int get(int a) { return a; }", owners) == "strong"
    assert lane.owner_strength("Owned", "virtual int get(int a) const { return a; }", owners) is None
    views = [owned_view("virtual ~Owned();", "virtual int get() { return 1; }")] * 2
    own, _, problems = owned_slots(views, owners=owners, vslots={0: "__vecDelDtor(uint)", 1: "get()"})
    assert problems == [] and "virtual int get() { return 1; }" in own


@pytest.mark.parametrize("member,row", [
    ("virtual void f(const DamageInfo *info, BodyDamageType a, BodyDamageType b) {}",
     "?f@Owned@@UAEXPBVDamageInfo@@W4BodyDamageType@@1@Z"),               # a parameter back-reference
    ("virtual void f(Owned *o) {}", "?f@Owned@@UAEXPAV1@@Z"),             # a name back-reference
    ("virtual bool f(LivingWorldArmy *a, Rva00318C32Ret *r) {}",
     "?f@Owned@@UAE_NPAULivingWorldArmy@@PAVRva00318C32Ret@@@Z"),
    ("virtual void f(unsigned int n, const char *s) const {}", "?f@Owned@@UBEXIPBD@Z"),
    ("virtual void f(int *const p, int &r) {}", "?f@Owned@@UAEXQAHAAH@Z"),
])
def test_a_rows_signature_is_matched_to_the_declaration(member, row):
    owners = {"?f@Owned@@": [(row, "Base.cpp")]}
    assert lane.rows_of("Owned", member, owners) == [(row, "Base.cpp")]
    assert lane.rows_of("Owned", member.replace(" f(", " f(int extra, "), owners) == []


@pytest.mark.parametrize("member", [
    "virtual void f(int a = 3) {}",                                       # a default argument
    "virtual void f(std::vector<int> v) {}",                              # a template
    "virtual void f(void (*cb)(int)) {}",                                 # a function pointer
])
def test_a_declaration_it_cannot_read_is_unknown(member):
    with pytest.raises(lane.OwnerUnknown):
        lane.rows_of("Owned", member, {"?f@Owned@@": [("?f@Owned@@UAEXH@Z", "Base.cpp")]})


def test_an_attribute_does_not_hide_the_declarator(base_header, monkeypatch):
    # review r2: `virtual __declspec(noinline) int get()` named `?__declspec@Owned@@` and found no owner
    member = "virtual __declspec(noinline) int get() const { return 1; }"
    assert lane.member_prefix("Owned", member) == "?get@Owned@@"
    objects(monkeypatch, local=STRONG)
    assert lane.owner_strength("Owned", member, OWNED_GET) == "strong"
    c = owned_contract({0: "__vecDelDtor(uint)", 1: "get()"})
    with pytest.raises(lane.LayoutError, match="defines it exclusively"):
        lane.generate(c, "data", {}, None, (["virtual ~Owned();", member], []), (), owners=OWNED_GET)


def test_a_ledger_that_cannot_be_read_after_its_stat_is_unknown(tmp_path, monkeypatch):
    # review r2: a PermissionError from the rows escaped the hold
    ledger = tmp_path / "functions.csv"
    ledger.write_text("name\n")
    monkeypatch.setattr(lane, "LEDGER", ledger)
    monkeypatch.setattr(lane, "_matched_owners", lane._matched_owners)
    lane._matched_owners.cache = (None, {})

    def refuse():
        raise PermissionError("denied")
    monkeypatch.setattr(lane.class_contract, "ledger_rows", refuse)
    with pytest.raises(lane.OwnerUnknown, match="cannot be read"):
        lane.owner_strength("Owned", "virtual ~Owned() {}")
    lane._matched_owners.cache = (None, {})


@pytest.fixture
def census_repo(tmp_path, monkeypatch):
    repo = tmp_path / "repo"
    (repo / "Code").mkdir(parents=True)
    (repo / "Code/a.cpp").write_text("a\n")
    for args in (["init", "-q"], ["config", "user.email", "t@t"], ["config", "user.name", "t"], ["add", "."],
                 ["commit", "-qm", "census"]):
        subprocess.run(["git", *args], cwd=repo, check=True, capture_output=True)
    sha = subprocess.run(["git", "rev-parse", "HEAD"], cwd=repo, capture_output=True, text=True).stdout.strip()
    monkeypatch.setattr(lane, "ROOT", repo)
    return repo, {"meta": {"commit": sha, "census_commit": sha}}


def test_census_evidence_counts_only_for_an_owner_unaffected_since(census_repo, monkeypatch):
    # review r2: a census object of an owner changed since (a macro, an include, a flag) proved nothing
    repo, index = census_repo
    monkeypatch.setattr(lane, "_since_census", lambda commits, head: {"Code/a.cpp"})
    assert lane.census_fresh(index, "Code/b.cpp") and not lane.census_fresh(index, "Code/a.cpp")
    monkeypatch.setattr(lane, "_since_census", lambda commits, head: None)    # unbounded, or a build input
    assert not lane.census_fresh(index, "Code/b.cpp")
    monkeypatch.setattr(lane, "_since_census", lambda commits, head: set())
    assert not lane.census_fresh({"meta": {"commit": index["meta"]["commit"]}}, "Code/b.cpp")
    assert not lane.census_fresh({"meta": {"commit": "0" * 40, "census_commit": "0" * 40}}, "Code/b.cpp")
    (repo / "Code/a.cpp").write_text("dirty\n")
    assert not lane.census_fresh(index, "Code/b.cpp")


def test_census_strength_needs_a_fresh_owner(census_repo, monkeypatch):
    import link_check
    repo, index = census_repo
    (repo / "index.pkl").write_bytes(b"x")
    monkeypatch.setattr(link_check, "INDEX", repo / "index.pkl")
    index.update({"blockers": {"Code/a.cpp": {"object": "a.obj"}}, "objects": ["a.obj"],
                  "strong": {DTOR_ROW: [0]}, "comdat": {}})
    monkeypatch.setattr(lane, "_census_index", lambda state: index)
    monkeypatch.setattr(lane, "census_fresh", lambda idx, source: True)
    assert lane.census_strength(DTOR_ROW, "Code/a.cpp") == "strong"
    monkeypatch.setattr(lane, "census_fresh", lambda idx, source: False)
    assert lane.census_strength(DTOR_ROW, "Code/a.cpp") is None
