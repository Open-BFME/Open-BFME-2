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


# ------------------------------------------------------------------ --forced-move, the owner's exception

HOMELESS = 0x005DFF76
HOMELESS_NAME = F.forced_moves[HOMELESS][0]
TREE_DTOR = 0x005DFE18
TREE_DTOR_NAME = "??1tree@@QAE@XZ"
PLACED = "Code/Lib/Placed.cpp"
JMP = bytes.fromhex("e900000000")
BODY = ("the body", 0)


@pytest.fixture
def forced(tree, monkeypatch, image):
    """A tree with one row the rename forces out of UNIT, and objects the test states: the first
    coff_definitions and section_identity read the state before the rename, then `after` applies."""
    import build
    import tu_map
    import tu_skeleton
    monkeypatch.setattr(F, "forced_moves", {HOMELESS: (HOMELESS_NAME, UNIT)})
    rows = tree / "reverse/functions.csv"
    rows.write_bytes(rows.read_bytes() + (
        f"{HOMELESS_NAME},,0x{HOMELESS:08X},5,{UNIT},matched,placed\n"
        f"{TREE_DTOR_NAME},,0x{TREE_DTOR:08X},56,Code/Lib/Member.cpp,matched,tree\n"
        f"?placed@@YAXXZ,,0x00700100,8,{PLACED},matched,a row of the destination\n").encode())
    write(tree / "reverse/forced_row_moves.csv", "target_rva,name,moved_from,placed_in,evidence,statement\n")
    write(tree / PLACED, "// a unit that emits the row\n")
    write(tree / "reverse/tu_map.csv", "rva,size,kind,tu,confidence,by,evidence,source\n"
          f"0x{HOMELESS:08X},5,code,,,-,,{UNIT}\n")
    git(tree, "add", "-A")
    git(tree, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "forced")
    jump = bytes.fromhex("e99dfeffff")
    for i, byte in enumerate(jump):
        image[HOMELESS + i] = byte
    state = {
        "units": {HOMELESS: ("", ""), COPY: ("", "")}, "stale": False,
        "defs": {UNIT: {HOMELESS_NAME: (True, True, 2)}, PLACED: {HOMELESS_NAME: (True, True, 2)}},
        "bodies": {UNIT: BODY, PLACED: BODY},
        "code": JMP, "relocs": [(1, rename.REL32, TREE_DTOR_NAME)], "current": True,
        "named_after": False,
    }

    def current_rows(layout):
        return ([dict(rva=f"0x{at:08X}", tu=tu, confidence=confidence) for at, (tu, confidence) in state["units"].items()],
                state["stale"])
    monkeypatch.setattr(tu_map, "current_rows", current_rows)
    monkeypatch.setattr(tu_skeleton, "coff_definitions", lambda obj: state["defs"].get(obj))
    monkeypatch.setattr(tu_skeleton, "section_identity", lambda obj, name: state["bodies"].get(obj))
    monkeypatch.setattr(build, "read_object_symbol_bytes", lambda path, name, **kw: (state["code"], state["relocs"]))
    monkeypatch.setattr(rename, "forced_move_references", lambda path, name: state["named_after"])
    return state


FORCED_STATE = {}


def forced_context(root, forced_state=None):
    ctx, state = context(root)
    ctx.forced_move_object = lambda source: source
    ctx.forced_move_current = lambda source: FORCED_STATE["current"]
    return ctx, state


def forced_plan(ctx, **overrides):
    return plan(ctx, forced_moves=[(HOMELESS, PLACED)], **overrides)


def land_forced(ctx, got, state, forced_state, *, old_still_defines=False):
    def verify(c, sources):
        state["refs"] = after_refs()
        if not old_still_defines:
            forced_state["defs"][UNIT] = {}
        return True
    return rename.apply_rename(got, ctx=ctx, verify=verify, checks=None)


def register(root):
    return (root / "reverse/forced_row_moves.csv").read_text()


@pytest.fixture(autouse=True)
def forced_state_link(request):
    if "forced" in request.fixturenames:
        FORCED_STATE.clear()
        FORCED_STATE["current"] = True
    yield


def test_the_real_family_lists_only_the_row_the_owner_approved():
    assert list(R.HERO_RECORD_SET.forced_moves) == [0x005DFF76]
    assert R.HERO_RECORD_SET.forced_moves[0x005DFF76][1] == "Code/GameEngine/Source/Common/Rva0021E85ACopy.cpp"
    assert R.forced_move_table() == R.HERO_RECORD_SET.forced_moves


def test_the_constructor_refuses_a_forced_row_that_does_not_spell_the_old_class():
    with pytest.raises(ValueError, match="does not spell the old class"):
        R.BodyFamily(**{**good_kwargs(), "old": "Old"}, forced_moves={9: ("??1Other@@QAE@XZ", "Code/A.cpp")})
    with pytest.raises(ValueError, match="family's own row"):
        R.BodyFamily(**{**good_kwargs(), "old": "Old"}, forced_moves={1: ("??1?$map@VOld@@@@QAE@XZ", "Code/A.cpp")})


def test_a_forced_move_lands_with_its_record_and_no_approval(tree, forced):
    ctx, state = forced_context(tree)
    got = forced_plan(ctx)
    land_forced(ctx, got, state, forced)
    rows = (tree / "reverse/functions.csv").read_text()
    assert f"{HOMELESS_NAME},,0x{HOMELESS:08X},5,{PLACED},matched" in rows
    lines = register(tree).splitlines()
    assert len(lines) == 2 and f"0x{HOMELESS:08X}" in lines[1] and "not in its true unit" in lines[1]
    assert UNIT in lines[1] and PLACED in lines[1]
    mapped = (tree / "reverse/tu_map.csv").read_text().splitlines()[1].split(",")
    assert mapped[3:5] == ["", ""]
    assert mapped[7] == PLACED
    assert PLACED in got.verify and UNIT in got.verify


def test_an_approved_unit_refuses_the_exception(tree, forced):
    forced["units"][HOMELESS] = ("Code/Lib/True.cpp", "approved")
    ctx, _state = forced_context(tree)
    with pytest.raises(Refusal, match="has a unit"):
        forced_plan(ctx)


def test_a_provisional_unit_refuses_the_exception(tree, forced):
    forced["units"][HOMELESS] = ("Code/Lib/True.cpp", "provisional")
    ctx, _state = forced_context(tree)
    with pytest.raises(Refusal, match="has a unit"):
        forced_plan(ctx)


def test_a_row_the_map_does_not_list_refuses(tree, forced):
    del forced["units"][HOMELESS]
    ctx, _state = forced_context(tree)
    with pytest.raises(Refusal, match="cannot show"):
        forced_plan(ctx)


def test_the_map_is_the_one_the_current_inputs_build(tree, forced):
    # The committed file lists the row with no unit; the rebuilt map gives it one, and that is the answer.
    forced["stale"] = True
    forced["units"][HOMELESS] = ("Code/Lib/True.cpp", "approved")
    ctx, _state = forced_context(tree)
    with pytest.raises(Refusal, match="has a unit"):
        forced_plan(ctx)


def test_a_row_no_family_lists_refuses(tree, forced, monkeypatch):
    # an identical homeless COMDAT the rename could be made to suppress: the rename alone cannot move it
    monkeypatch.setattr(F, "forced_moves", {})
    ctx, _state = forced_context(tree)
    with pytest.raises(Refusal, match="reviewed forced_moves"):
        forced_plan(ctx)


def test_a_row_that_is_not_the_reviewed_one_refuses(tree, forced, monkeypatch):
    ctx, _state = forced_context(tree)
    monkeypatch.setattr(F, "forced_moves", {HOMELESS: (HOMELESS_NAME, "Code/Lib/Other.cpp")})
    with pytest.raises(Refusal, match="the family reviewed"):
        forced_plan(ctx)
    monkeypatch.setattr(F, "forced_moves", {HOMELESS: ("??1?$map@VLadderPref@@@@QAE@XZ", UNIT)})
    with pytest.raises(Refusal, match="the family reviewed"):
        forced_plan(ctx)


def test_no_rename_forcing_it_refuses(tree, forced, monkeypatch):
    monkeypatch.setattr(F, "forced_moves", {HOMELESS: (HOMELESS_NAME, "Code/Lib/Member.cpp")})
    rows = tree / "reverse/functions.csv"
    rows.write_bytes(rows.read_bytes().replace(f"0x{HOMELESS:08X},5,{UNIT}".encode(),
                                               f"0x{HOMELESS:08X},5,Code/Lib/Member.cpp".encode()))
    git(tree, "add", "-A")
    git(tree, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "elsewhere")
    with pytest.raises(Refusal, match="no rename forces"):
        forced_plan(_fresh(tree))


def _fresh(root):
    ctx, _state = forced_context(root)
    return ctx


@pytest.fixture
def receipted(tmp_path, monkeypatch):
    """A real census-grade sidecar over a real source and object, as test_build_include_inventory writes one."""
    import build
    root = tmp_path / "receipted"
    source = root / "Code" / "Unit.cpp"
    source.parent.mkdir(parents=True)
    source.write_text("// the unit\n")
    output = root / "Unit.obj"
    output.write_bytes(b"the object the compiler wrote")
    command, env = ["cl"], {}
    monkeypatch.setattr(build, "ROOT", root)
    monkeypatch.setattr(build, "compiler_command", lambda *_: (command, env))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda *_: "command")
    inventory = build.search_inventory(source, command, env)
    build._write_deps_sidecar(source, output, "command", "", True, command, env, inventory, [])
    assert build.compile_is_current(source, output)
    return source, output


def test_the_receipt_holds_for_the_object_it_recorded(receipted):
    assert rename.object_receipt_holds(*receipted)


def test_replaced_object_bytes_with_the_receipt_kept_refuse(receipted):
    import build
    source, output = receipted
    output.write_bytes(b"other bytes in the same object")
    # what the plan used to rely on still says current: only the recorded hash catches this
    assert build.compile_is_current(source, output)
    assert not rename.object_receipt_holds(source, output)


def test_a_receipt_with_no_object_hash_refuses(receipted):
    import build
    import json
    source, output = receipted
    sidecar = build._deps_sidecar(output)
    meta = json.loads(sidecar.read_text())
    del meta["object"]
    sidecar.write_text(json.dumps(meta))
    assert not rename.object_receipt_holds(source, output)


def test_a_plain_sidecar_is_not_census_grade(receipted, monkeypatch):
    import build
    import json
    source, output = receipted
    sidecar = build._deps_sidecar(output)
    meta = json.loads(sidecar.read_text())
    assert meta.pop("version") == 2
    meta["deps"] = {"Code/Unit.cpp": build._hash_file(str(source))}
    sidecar.write_text(json.dumps(meta))
    assert build.compile_is_current(source, output)
    assert not rename.object_receipt_holds(source, output)


def test_an_old_object_with_no_current_receipt_refuses(tree, forced):
    FORCED_STATE["current"] = False
    ctx, _state = forced_context(tree)
    with pytest.raises(Refusal, match="census-grade"):
        forced_plan(ctx)


def test_a_batch_refuses_the_exception(tree, forced):
    ctx, _state = forced_context(tree)
    request = dict(rva=COPY, new=NEW_COPY, respell=True, identity=True, basis="retail", evidence=F.evidence(),
                   prepared=dict(PREPARED), forced_moves=[(HOMELESS, PLACED)])
    result = rename.run_batch(ctx, [("function", request)], claim=False, verify=lambda *_: True, checks=lambda *_: [])
    assert "does not take --forced-move" in result.refused[0]
    assert not result.plans
    assert f"{HOMELESS_NAME},,0x{HOMELESS:08X},5,{UNIT}," in (tree / "reverse/functions.csv").read_text()
    assert len(register(tree).splitlines()) == 1


@pytest.mark.parametrize("basis, evidence", [("retail", F.evidence()), ("inferred", "agree:x")])
def test_a_batch_refuses_every_identity_respell(tree, forced, basis, evidence):
    ctx, _state = forced_context(tree)
    before = (tree / "reverse/functions.csv").read_bytes()
    request = dict(rva=COPY, new=NEW_COPY, respell=True, identity=True, basis=basis, evidence=evidence,
                   prepared=dict(PREPARED))
    result = rename.run_batch(ctx, [("function", request)], claim=False, verify=lambda *_: True, checks=lambda *_: [])
    assert "does not take an identity respell" in result.refused[0]
    assert not result.plans
    assert (tree / "reverse/functions.csv").read_bytes() == before


def test_a_batch_refuses_a_plan_carrying_identity_however_it_was_asked_for(tree, forced, monkeypatch):
    ctx, _state = forced_context(tree)
    real = rename.plan_rename

    def carrying(kind, *, ctx=None, **kwargs):
        got = real("function", ctx=ctx, rva=COPY, new=NEW_COPY, respell=True, identity=True, basis="retail",
                   evidence=F.evidence(), prepared=dict(PREPARED))
        assert got.identity
        return got
    monkeypatch.setattr(rename, "plan_rename", carrying)
    result = rename.run_batch(ctx, [("function", dict(rva=COPY, new="unused"))], claim=False,
                              verify=lambda *_: True, checks=lambda *_: [])
    assert "does not take an identity plan" in result.refused[0]
    assert not result.plans


def test_a_row_its_old_file_does_not_define_today_refuses(tree, forced):
    forced["defs"][UNIT] = {}
    ctx, _state = forced_context(tree)
    with pytest.raises(Refusal, match="nothing is forced"):
        forced_plan(ctx)


def test_the_familys_own_row_refuses(tree, forced):
    ctx, _state = forced_context(tree)
    with pytest.raises(Refusal, match="family's own row"):
        plan(ctx, forced_moves=[(COPY, PLACED)])


def test_a_weak_destination_refuses(tree, forced):
    ctx, _state = forced_context(tree)
    with pytest.raises(Refusal, match="missing or outside"):
        plan(ctx, forced_moves=[(HOMELESS, "Code/Lib/Nowhere.cpp")])
    with pytest.raises(Refusal, match="already in"):
        plan(ctx, forced_moves=[(HOMELESS, UNIT)])
    for dest in ("reverse/attempts/00000001.cpp", "Code/../Code/Lib/Placed.cpp", "Code/Lib/Placed.asm", "Code/Lib/Placed.h"):
        with pytest.raises(Refusal, match="existing Code C\\+\\+ source"):
            plan(ctx, forced_moves=[(HOMELESS, dest)])
    for dest, message in (("Code/gen_small/x.cpp", "generated"), ("Code/gen_asm/x.cpp", "generated"),
                          ("Code/Lib/NoRows.cpp", "no matched rows")):
        write(tree / dest, "// here\n")
        git(tree, "add", "-A")
        git(tree, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", dest)
        with pytest.raises(Refusal, match=message):
            plan(_fresh(tree), forced_moves=[(HOMELESS, dest)])
    write(tree / "Code/Lib/Loose.cpp", "// not tracked\n")
    rows = tree / "reverse/functions.csv"
    rows.write_bytes(rows.read_bytes() + b"?loose@@YAXXZ,,0x00700200,8,Code/Lib/Loose.cpp,matched,loose\n")
    git(tree, "add", "reverse/functions.csv")
    git(tree, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "loose")
    with pytest.raises(Refusal, match="untracked"):
        plan(_fresh(tree), forced_moves=[(HOMELESS, "Code/Lib/Loose.cpp")])


def test_an_old_object_still_naming_the_symbol_restores_everything(tree, forced):
    ctx, state = forced_context(tree)
    before = (tree / "reverse/functions.csv").read_bytes()
    got = forced_plan(ctx)
    forced["named_after"] = True
    with pytest.raises(VerifyFailed, match="still refers to"):
        land_forced(ctx, got, state, forced)
    assert (tree / "reverse/functions.csv").read_bytes() == before
    forced["named_after"] = None
    forced["defs"][UNIT] = {HOMELESS_NAME: (True, True, 2)}
    got = forced_plan(ctx)
    with pytest.raises(VerifyFailed, match="inconclusive"):
        land_forced(ctx, got, state, forced)


# The proof on the real objects of the P51 respell: nothing about them is mocked but the retail read, the map
# and the row table. Built by ./build.sh from Rva0021E85ACopy.cpp before and after the respell (424095f914)
# and OnlinePreferences_Unresolved.cpp, which the respell did not change.
REAL = Path(__file__).resolve().parent / "fixtures" / "forced_move"
REAL_NAME = F.forced_moves[HOMELESS][0]
REAL_OLD, REAL_NEW = "Code/Common/Copy.cpp", "Code/Net/Prefs.cpp"


@pytest.fixture
def real_objects(tmp_path, monkeypatch):
    import build
    import tu_skeleton
    before = REAL / "rva0021e85acopy_before.obj"
    after = REAL / "rva0021e85acopy_after.obj"
    dest = REAL / "onlinepreferences_unresolved.obj"
    relocs = build.read_object_symbol_bytes(dest, REAL_NAME, code_only=True)[1]
    assert [(offset, kind) for offset, kind, _target in relocs] == [(1, rename.REL32)]
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(
        "name,export_rva,target_rva,target_size,source,status,notes\n"
        f"{relocs[0][2]},,0x{TREE_DTOR:08X},56,Code/Tree.cpp,matched,tree\n")
    monkeypatch.setattr(R, "read_retail", lambda rva, size: bytes.fromhex("e99dfeffff")[:size])
    monkeypatch.setattr(rename, "map_units", lambda ctx: {HOMELESS: ("", "")})
    files = {REAL_OLD: after, REAL_NEW: dest}

    class Ctx:
        root = tmp_path

        @staticmethod
        def path(rel):
            return tmp_path / rel

        @staticmethod
        def forced_move_object(source):
            return files[source]

    identity = dict(forced=[dict(rva=HOMELESS, name=REAL_NAME, size=5, old=REAL_OLD, dest=REAL_NEW,
                                 before=tu_skeleton.section_identity(before, REAL_NAME))],
                    units_before={HOMELESS: ("", "")})
    return Ctx, identity, files, before


def test_the_real_objects_pass_the_proof(real_objects):
    ctx, identity, _files, before = real_objects
    assert identity["forced"][0]["before"] is not None
    assert rename.forced_move_references(before, REAL_NAME) is True
    assert rename.forced_move_references(REAL / "rva0021e85acopy_after.obj", REAL_NAME) is False
    assert rename.forced_move_problems(ctx, identity) == []


def test_the_real_old_object_before_the_respell_is_refused(real_objects):
    ctx, identity, files, before = real_objects
    files[REAL_OLD] = before
    assert "still defines" in rename.forced_move_problems(ctx, identity)[0]


def test_a_real_destination_with_a_changed_body_is_refused(real_objects, tmp_path):
    import build
    import struct
    ctx, identity, files, _before = real_objects
    data = bytearray((REAL / "onlinepreferences_unresolved.obj").read_bytes())
    detail = build.read_object_symbol_bytes(
        REAL / "onlinepreferences_unresolved.obj", REAL_NAME, code_only=True, detail=True)[2]
    section, value = detail["section"], detail["value"]
    pointer = struct.unpack_from("<I", data, 20 + (section - 1) * 40 + 20)[0]
    assert data[pointer + value] == 0xE9
    data[pointer + value] = 0xE8
    changed = tmp_path / "changed.obj"
    changed.write_bytes(data)
    files[REAL_NEW] = changed
    assert "body differs" in rename.forced_move_problems(ctx, identity)[0]


def test_a_real_destination_without_the_body_is_refused(real_objects):
    ctx, identity, files, _before = real_objects
    files[REAL_NEW] = REAL / "rva0021e85acopy_after.obj"
    assert "define" in rename.forced_move_problems(ctx, identity)[0]


def test_a_real_body_retail_does_not_hold_is_refused(real_objects, monkeypatch):
    ctx, identity, _files, _before = real_objects
    monkeypatch.setattr(R, "read_retail", lambda rva, size: bytes.fromhex("e89dfeffff")[:size])
    assert "differ from retail" in rename.forced_move_problems(ctx, identity)[0]
    monkeypatch.setattr(R, "read_retail", lambda rva, size: bytes.fromhex("e900000000")[:size])
    assert "no row of that name" in rename.forced_move_problems(ctx, identity)[0]


def test_a_row_with_funclets_refuses(tree, forced):
    rows = tree / "reverse/functions.csv"
    rows.write_bytes(rows.read_bytes() + f"$L1,,0x00700000,8,{UNIT},matched,parent={HOMELESS_NAME}\n".encode())
    git(tree, "add", "-A")
    git(tree, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "funclet")
    with pytest.raises(Refusal, match="funclets"):
        forced_plan(_fresh(tree))


def test_the_old_file_still_defining_it_restores_everything(tree, forced):
    ctx, state = forced_context(tree)
    before = (tree / "reverse/functions.csv").read_bytes()
    got = forced_plan(ctx)
    with pytest.raises(VerifyFailed, match="still defines"):
        land_forced(ctx, got, state, forced, old_still_defines=True)
    assert (tree / "reverse/functions.csv").read_bytes() == before
    assert len(register(tree).splitlines()) == 1


@pytest.mark.parametrize("change, message", [
    ({"bodies": {PLACED: ("another body", 0)}}, "body differs"),
    ({"defs": {PLACED: {}}}, "define"),
    ({"code": bytes.fromhex("e800000000")}, "differ from retail"),
    ({"code": bytes.fromhex("e9000000")}, "bytes, its row"),
    ({"relocs": [(1, rename.REL32, "??1other@@QAE@XZ")]}, "no row of that name"),
    ({"relocs": [(1, 7, TREE_DTOR_NAME)]}, "cannot compare"),
])
def test_a_new_body_that_is_not_retails_restores_everything(tree, forced, change, message):
    ctx, state = forced_context(tree)
    before = (tree / "reverse/functions.csv").read_bytes()
    got = forced_plan(ctx)
    for key, value in change.items():
        if isinstance(value, dict):
            forced[key].update(value)
        else:
            forced[key] = value
    with pytest.raises(VerifyFailed, match=message):
        land_forced(ctx, got, state, forced)
    assert (tree / "reverse/functions.csv").read_bytes() == before
    assert len(register(tree).splitlines()) == 1


@pytest.mark.parametrize("at, unit", [(HOMELESS, ("Code/Lib/Placed.cpp", "approved")), (COPY, ("Code/Lib/X.cpp", "approved"))])
def test_a_move_that_would_change_the_map_restores_everything(tree, forced, at, unit):
    ctx, state = forced_context(tree)
    before = (tree / "reverse/functions.csv").read_bytes()
    got = forced_plan(ctx)
    forced["units"] = {**forced["units"], at: unit}
    with pytest.raises(VerifyFailed, match="approves nothing"):
        land_forced(ctx, got, state, forced)
    assert (tree / "reverse/functions.csv").read_bytes() == before


def test_the_exception_is_for_the_retail_route_only(tree, forced):
    ctx, _state = forced_context(tree)
    with pytest.raises(Refusal, match="--basis retail only"):
        rename.plan_rename("function", ctx=ctx, rva=COPY, new=NEW_COPY, respell=True, identity=True, basis="inferred",
                           evidence="agree:x", prepared=dict(PREPARED), forced_moves=[(HOMELESS, PLACED)])


def test_a_missing_register_refuses(tree, forced):
    (tree / "reverse/forced_row_moves.csv").unlink()
    git(tree, "add", "-A")
    git(tree, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "gone")
    with pytest.raises(Refusal, match="every forced move is recorded"):
        forced_plan(_fresh(tree))
