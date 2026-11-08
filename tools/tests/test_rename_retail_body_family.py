"""`tools/rename.py function --respell --identity --basis retail` on a family with no vftable
(tools/retail_identity.py BodyFamily): the real entry is the fixture, its facts served from an image the
test writes, and the shape takes nothing away from a table family's checks."""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import allowed_symbols  # noqa: E402
import rename  # noqa: E402
import retail_identity as R  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

F = R.HERO_RECORD_SET
COPY = F.copy
OLD_COPY = F.rows[COPY][0]
NEW_COPY = F.respell(OLD_COPY)
UNIT = "Code/Lib/Tree.cpp"
OUTER = "Code/Lib/Outer.cpp"
SOURCES = {0x0021DBBA: UNIT, 0x0021E134: OUTER}
PREPARED = {UNIT: b"// the tree copy under its new class\n", OUTER: b"// the outer copy under its new class\n"}


def write(path, text):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(text.encode("utf-8"))


def git(root, *args):
    subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True)


@pytest.fixture
def image(monkeypatch):
    bytes_at = {}
    for fact in F.facts():
        for i, byte in enumerate(R.expected(fact)):
            bytes_at[fact.site + i] = byte

    def read(rva, size):
        return bytes(bytes_at[rva + i] for i in range(size))
    monkeypatch.setattr(R, "read_retail", read)
    return bytes_at


@pytest.fixture
def tree(tmp_path, image):
    rows = ["name,export_rva,target_rva,target_size,source,status,notes\n"]
    for at, (old, _facts) in sorted(F.rows.items()):
        rows.append(f"{old},,0x{at:08X},8,{SOURCES[at]},matched,family row\n")
    for members in (F.members, F.old_members):
        for at, name in sorted(members.items()):
            rows.append(f"{name},,0x{at:08X},8,Code/Lib/Member.cpp,matched,member\n")
    pins = ["name,address,notes\n"]
    for table in (F.pins, F.retired):
        pins += [f"{old},0x{at:08X},sweep\n" for at, (old, _f) in sorted(table.items())]
    files = {
        "reverse/functions.csv": "".join(rows),
        "reverse/symbols.csv": "".join(pins),
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/name_basis.csv": "kind,old,new,basis,evidence,source,rva\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "reverse/tu_map.csv": "rva,size,kind,tu,confidence,by,evidence,source\n",
        "reverse/data_ledger.csv": "address,size,section,kind,name,source,status,names,defs,refs\n",
        UNIT: "// tree\n",
        OUTER: "// outer\n",
        "Code/Lib/Member.cpp": "// members\n",
    }
    for rel, text in files.items():
        write(tmp_path / rel, text)
    git(tmp_path, "init", "-q")
    git(tmp_path, "add", "-A")
    git(tmp_path, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "seed")
    return tmp_path


GOOD_RELOCS = {name: [(offset, rename.REL32, target)]
               for name, offset, target in ((F.respell(F.rows[at][0]), offset, target) for at, offset, target in F.bindings)}


def context(root, refs=(), relocs=None, consumers=()):
    ctx = rename.Context(root, object_scan=False)
    state = {"refs": list(refs), "relocs": GOOD_RELOCS if relocs is None else relocs}
    ctx.identity_refs = lambda sources: [r for r in state["refs"] if r["source"] in sources]
    ctx.object_symbol_relocs = lambda source, name: state["relocs"].get(name, [])
    return ctx, state


def plan(ctx, **overrides):
    kwargs = dict(rva=COPY, new=NEW_COPY, respell=True, identity=True, basis="retail", evidence=F.evidence(),
                  prepared=dict(PREPARED))
    kwargs.update(overrides)
    return rename.plan_rename("function", ctx=ctx, **kwargs)


@pytest.fixture(autouse=True)
def no_consumers(monkeypatch):
    calls = {"names": None, "words": None, "problems": []}

    def consumers(ctx, names, words, rebuilt):
        calls["names"], calls["words"] = names, words
        return list(calls["problems"]), 0
    monkeypatch.setattr(rename, "pin_consumers", consumers)
    monkeypatch.setattr(rename, "object_pin_references", lambda objects, names: [])
    monkeypatch.setattr(rename, "source_objects", lambda ctx, sources: {})
    return calls


def after_refs():
    return [dict(source=SOURCES[at], row=F.respell(old), rva=at, symbol="x", target=0x1234, cls="owner")
            for at, (old, _f) in F.rows.items()]


def land(ctx, got, state, refs=None, relocs=None):
    def verify(c, sources):
        state["refs"] = after_refs() if refs is None else refs
        if relocs is not None:
            state["relocs"] = relocs
        return True
    return rename.apply_rename(got, ctx=ctx, verify=verify, checks=None)


# ------------------------------------------------------------------ the shape

@pytest.mark.parametrize("missing", ["element", "old_element", "old_members", "members", "member_facts", "bindings"])
def test_no_table_never_means_no_check(missing):
    kwargs = dict(old="a", new="b", copy=1, spellings={"x": "y"}, element=(R.Fact("calls", 1, 2),),
                  old_element=(R.Fact("calls", 1, 2),), old_members={1: "n"}, members={1: "m"},
                  member_facts=(R.Fact("calls", 1, 2),), bindings=((1, 0, "t"),), rows={1: ("x", ())}, pins={})
    R.BodyFamily(**kwargs)
    kwargs[missing] = ()
    with pytest.raises(ValueError, match=missing):
        R.BodyFamily(**kwargs)


def test_every_row_needs_a_binding():
    kwargs = dict(old="a", new="b", copy=1, spellings={"x": "y", "z": "w"}, element=(R.Fact("calls", 1, 2),),
                  old_element=(R.Fact("calls", 1, 2),), old_members={1: "n"}, members={1: "m"},
                  member_facts=(R.Fact("calls", 1, 2),), rows={1: ("x", ()), 2: ("z", ())}, pins={})
    with pytest.raises(ValueError, match="binding"):
        R.BodyFamily(bindings=((1, 0, "t"),), **kwargs)
    with pytest.raises(ValueError, match="binding"):
        R.BodyFamily(bindings=((1, 0, "t"), (2, 0, "t"), (3, 0, "t")), **kwargs)


def good_kwargs():
    return dict(old="a", new="b", copy=1, spellings={"x": "y", "p": "q"}, element=(R.Fact("calls", 1, 2),),
                old_element=(R.Fact("calls", 1, 2),), old_members={1: "n"}, members={1: "m"},
                member_facts=(R.Fact("calls", 1, 2),), bindings=((1, 0, "t"),), rows={1: ("x", ())},
                pins={5: ("p", ())})


@pytest.mark.parametrize("label, change, message", [
    ("a row left out of the spellings", {"spellings": {"p": "q"}}, "spelling of its own"),
    ("a pin left out of the spellings", {"spellings": {"x": "y"}}, "spelling of its own"),
    ("a row spelled as itself", {"spellings": {"x": "x", "p": "q"}}, "spelling of its own"),
    ("a key row that is no row", {"copy": 2}, "not a row of the family"),
    ("a retired pin on an address the class does not row", {"retired": {9: ("r", ())}}, "only a pin on an address"),
])
def test_the_constructor_refuses_what_the_plan_assumes(label, change, message):
    R.BodyFamily(**good_kwargs())
    with pytest.raises(ValueError, match=message):
        R.BodyFamily(**{**good_kwargs(), **change})


def test_the_consumer_scan_searches_the_old_classs_word(tree, no_consumers):
    ctx, _ = context(tree)
    plan(ctx)
    assert no_consumers["words"] == [F.old]


def test_a_name_the_family_does_not_spell_proves_nothing():
    assert F.respell("??0Stranger@@QAE@XZ") == "??0Stranger@@QAE@XZ"
    assert R.family_of(COPY, "??0Stranger@@QAE@XZ") is None
    assert R.family_of(COPY, NEW_COPY) is F


def test_the_elements_are_told_apart_by_their_own_bytes():
    new = {(f.site, f.value) for f in F.element}
    old = {(f.site, f.value) for f in F.old_element}
    assert (0x00219B4B, 0x000365F0) in new and (0x005BA40B, 0x00037050) in old
    assert not any(value == 0x00037050 for _site, value in new)     # no wide string in the new element


def test_the_real_image_states_them_all(monkeypatch):
    if not R.build.EXE.exists():
        pytest.skip("no retail image here")
    assert R.facts_problems(F.facts()) == []


# ------------------------------------------------------------------ records and pins

def bases(tmp_path, *records):
    path = tmp_path / "name_basis.csv"
    write(path, "kind,old,new,basis,evidence,source,rva\n" + "".join(f"{r}\n" for r in records))
    return allowed_symbols.Bases(path)


def test_its_own_record_is_evidence_and_no_other(tmp_path):
    good = bases(tmp_path, f"function,{OLD_COPY},{NEW_COPY},retail,{F.evidence()},{UNIT},0x{COPY:08X}")
    assert good.lookup(NEW_COPY, COPY) == ("evidence", "retail")
    assert not R.record_proven(OLD_COPY, NEW_COPY, "0x0021E134", F.evidence())
    assert not R.record_proven(OLD_COPY, "??0Other@@QAE@ABV0@@Z", f"0x{COPY:08X}", F.evidence())
    assert not R.record_proven(OLD_COPY, NEW_COPY, f"0x{COPY:08X}", R.record(F.rows[0x0021E134][1]))


def test_the_pin_respelled_is_proven_only_at_its_address(image):
    at, (old, _f) = next(iter(F.pins.items()))
    assert R.pin_respell_proven(old, F.respell(old), at)
    assert not R.pin_respell_proven(old, F.respell(old), at + 1)
    assert not R.pin_respell_proven(old, "?other@@YAXXZ", at)


def test_a_retired_pin_is_not_a_respelling(image):
    at, (old, _f) = next(iter(F.retired.items()))
    assert not R.pin_respell_proven(old, F.members[at], at)


# ------------------------------------------------------------------ the plan

def test_the_rows_and_pin_are_respelled_and_the_old_pin_goes(tree):
    ctx, _ = context(tree)
    got = plan(ctx)
    rows = got.after["reverse/functions.csv"].decode()
    for at, (old, _f) in F.rows.items():
        assert old not in rows and f"{F.respell(old)},,0x{at:08X},8,{SOURCES[at]},matched" in rows
    pins = got.after["reverse/symbols.csv"].decode()
    for at, (old, _f) in F.pins.items():
        assert old not in pins and f"{F.respell(old)},0x{at:08X},sweep" in pins
    for at, (old, _f) in F.retired.items():
        assert old not in pins
    basis = got.after["reverse/name_basis.csv"].decode()
    assert f"function,{OLD_COPY},{NEW_COPY},retail,{F.evidence()},{UNIT},0x{COPY:08X}" in basis
    assert got.identity["bindings"] and "table_name" not in got.identity
    assert got.subject().endswith("by retail identity")


def test_each_byte_of_each_fact_refuses(tree, image):
    ctx, _ = context(tree)
    for fact in F.facts():
        keep = image[fact.site]
        image[fact.site] = keep ^ 0xFF
        with pytest.raises(Refusal, match="retail does not state"):
            plan(ctx)
        image[fact.site] = keep


@pytest.mark.parametrize("table", ["members", "old_members"])
def test_each_member_must_be_rowed_at_its_address(tree, table):
    for at, name in getattr(F, table).items():
        path = tree / "reverse/functions.csv"
        keep = path.read_bytes()
        path.write_bytes(keep.replace(f"{name},,0x{at:08X}".encode(), f"{name},,0x{at + 1:08X}".encode()))
        ctx, _ = context(tree)
        with pytest.raises(Refusal, match="is not rowed"):
            plan(ctx)
        path.write_bytes(keep)


def test_a_missing_pin_refuses(tree):
    path = tree / "reverse/symbols.csv"
    keep = path.read_bytes()
    for table in (F.pins, F.retired):
        for at, (old, _f) in table.items():
            path.write_bytes(keep.replace(f"{old},0x{at:08X},sweep\n".encode(), b""))
            ctx, _ = context(tree)
            with pytest.raises(Refusal, match="is not at"):
                plan(ctx)
    path.write_bytes(keep)


def test_a_consumer_of_the_retired_pin_refuses(tree, no_consumers):
    no_consumers["problems"] = ["Code/Lib/Other.cpp binds it"]
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="cannot be retired"):
        plan(ctx)
    assert no_consumers["names"] == [old for old, _f in F.retired.values()]


def test_a_unit_still_spelling_the_retired_pin_refuses(tree):
    (old, _f) = next(iter(F.retired.values()))
    write(tree / "Code/Lib/Other.cpp", f"// {old}\n")
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="still spells"):
        plan(ctx)


def test_prepared_sources_are_required(tree):
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="--prepared"):
        plan(ctx, prepared=None)


def test_the_request_may_not_add_rows_or_change_the_evidence(tree):
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="--evidence must name the proof"):
        plan(ctx, evidence="retail:0x00000001 calls=0x00000002")
    with pytest.raises(Refusal, match="no --old, no --also"):
        plan(ctx, also=[(0x00001000, "?x@@YAXXZ")])


# ------------------------------------------------------------------ the rebuilt objects

def test_the_landing_writes_it_all(tree):
    ctx, state = context(tree)
    land(ctx, plan(ctx), state)
    assert NEW_COPY in (tree / "reverse/functions.csv").read_text()
    assert OLD_COPY not in (tree / "reverse/functions.csv").read_text()


@pytest.mark.parametrize("label, change", [
    ("no relocation at all", lambda at, offset, target: []),
    ("another offset", lambda at, offset, target: [(offset + 1, rename.REL32, target)]),
    ("another type", lambda at, offset, target: [(offset, rename.DIR32, target)]),
    ("another target", lambda at, offset, target: [(offset, rename.REL32, "?other@@YAXXZ")]),
])
def test_a_rebuilt_row_not_binding_its_target_is_undone(tree, label, change):
    for at, offset, target in F.bindings:
        name = F.respell(F.rows[at][0])
        ctx, state = context(tree)
        with pytest.raises(VerifyFailed, match="does not bind"):
            land(ctx, plan(ctx), state, relocs={**GOOD_RELOCS, name: change(at, offset, target)})
        assert OLD_COPY in (tree / "reverse/functions.csv").read_text()


def test_a_row_with_no_references_is_undone(tree):
    ctx, state = context(tree)
    with pytest.raises(VerifyFailed, match="has no references"):
        land(ctx, plan(ctx), state, refs=after_refs()[:1])


def test_a_new_wrong_binding_is_undone(tree):
    ctx, state = context(tree)
    wrong = dict(source=UNIT, row=NEW_COPY, rva=COPY, symbol="x", target=0x1234,
                 cls=next(iter(allowed_symbols.WRONG)))
    with pytest.raises(VerifyFailed, match="gains a wrong binding"):
        land(ctx, plan(ctx), state, refs=after_refs() + [wrong])


def test_a_rebuilt_object_binding_the_retired_pin_is_undone(tree):
    (old, _f) = next(iter(F.retired.values()))
    ctx, state = context(tree)
    still = dict(source=UNIT, row=NEW_COPY, rva=COPY, symbol=old, target=0x1234, cls="owner")
    with pytest.raises(VerifyFailed, match="still binds the retired pin"):
        land(ctx, plan(ctx), state, refs=after_refs() + [still])


# ------------------------------------------------------------------ a table family gives up nothing

def test_a_table_family_still_needs_its_table_store(tmp_path):
    table = R.ENABLE_REGION_RECORD
    assert table.table and table.owner and table.copy_store
    identity = dict(rows=[], sources=[], wrong_before=[], copy_name="c", copy_source="s", copy_store=0x10, table_name="t")
    ctx = rename.Context(tmp_path, object_scan=False)
    ctx.identity_refs = lambda sources: []
    ctx.object_symbol_relocs = lambda source, name: []
    assert any("does not store" in p for p in rename.retail_identity_problems(ctx, identity))


def test_empty_bindings_are_a_problem(tmp_path):
    identity = dict(rows=[], sources=[], wrong_before=[], bindings=[])
    ctx = rename.Context(tmp_path, object_scan=False)
    ctx.identity_refs = lambda sources: []
    ctx.object_symbol_relocs = lambda source, name: []
    assert any("no bindings" in p for p in rename.retail_identity_problems(ctx, identity))
