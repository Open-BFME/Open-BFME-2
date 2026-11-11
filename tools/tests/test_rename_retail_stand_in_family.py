"""`tools/rename.py function --respell --identity --basis retail` on a stand-in element family
(tools/retail_identity.py StandInElementFamily): the real entry is the fixture, its facts served from an image the
test writes. The stand-in has no constructor, so no table proves the element: the class's own rows do, every row
reaches one by a call, every stride is the registered size, duplicates of the class's own rows are retired, and the
rebuilt rows must bind what retail's calls reach."""
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

F = R.SCORED_KILL_TRACKER_VECTOR
COPY = F.copy
OLD_COPY = F.rows[COPY][0]
NEW_COPY = F.respell(OLD_COPY)
HEADER = "Code/Lib/ScoredKillTrackerView.h"
SOURCES = {0x0055AC1F: "Code/Lib/Assign.cpp", 0x004143A4: "Code/Lib/Bodies.cpp", 0x00414760: "Code/Lib/Erase.cpp",
           0x004149B4: "Code/Lib/Erase.cpp", 0x004146E2: "Code/Lib/Dtor.cpp", 0x0041484C: "Code/Lib/Reserve.cpp"}
DUP_SOURCES = {0x00414793: "Code/Lib/Bodies.cpp", 0x004144F0: "Code/Lib/Destroy.cpp"}
SIZES = {0x0055AC1F: 88, 0x004143A4: 50, 0x00414760: 51, 0x004149B4: 11, 0x004146E2: 63, 0x0041484C: 116,
         0x00414793: 30, 0x004144F0: 24, 0x0055A91A: 34, 0x0055A93C: 40, 0x0041445C: 26, 0x0007E364: 28,
         0x00414359: 38, 0x004143D6: 45, 0x00414403: 29}
PIN_ROWS = {0x004143D6: ("??$_M_allocate_and_copy@PBURva004143D6Element@@@x", "Code/Lib/AllocCopy.cpp"),
            0x00414403: ("_Rva00414403CopyDispatch", "Code/Lib/Dispatch.cpp")}
PREPARED = {src: f"// {src} under its class\n".encode() for src in sorted(set(SOURCES.values()))}
EMPTIED = "Code/Lib/Destroy.cpp"


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


def ledger_rows(skip=(), resize=None, extra=()):
    rows = ["name,export_rva,target_rva,target_size,source,status,notes\n"]
    entries = [(old, at, SOURCES[at]) for at, (old, _f) in sorted(F.rows.items())]
    entries += [(old, at, DUP_SOURCES[at]) for at, (old, _f) in sorted(F.duplicates.items())]
    entries += [(name, at, "Code/Lib/Announcer.cpp") for at, name in sorted(F.members.items())]
    entries += [(name, at, src) for at, (name, src) in sorted(PIN_ROWS.items())]
    for name, at, source in entries:
        if name in skip:
            continue
        size = (resize or {}).get(name, SIZES[at])
        rows.append(f"{name},,0x{at:08X},{size},{source},matched,row\n")
    rows += list(extra)
    return "".join(rows)


def seed(root, files):
    for rel, text in files.items():
        write(root / rel, text)
    git(root, "init", "-q")
    git(root, "add", "-A")
    git(root, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "seed")
    return root


def files(header_size=44, registered=True):
    pins = ["name,address,notes\n"]
    for table in (F.pins, F.retired):
        pins += [f"{old},0x{at:08X},sweep\n" for at, (old, _f) in sorted(table.items())]
    out = {
        "reverse/functions.csv": ledger_rows(),
        "reverse/symbols.csv": "".join(pins),
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/name_basis.csv": "kind,old,new,basis,evidence,source,rva\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "reverse/tu_map.csv": "rva,size,kind,tu,confidence,by,evidence,source\n",
        "reverse/data_ledger.csv": "address,size,section,kind,name,source,status,names,defs,refs\n",
        "reverse/canonical_classes.csv": "class,header,notes\n" + (f"ScoredKillTracker,{HEADER},registered\n" if registered else ""),
        HEADER: f"class ScoredKillTracker;\ntypedef char ScoredKillTrackerSizeIs44[sizeof(ScoredKillTracker)=={header_size}?1:-1];\n",
        "Code/Lib/Announcer.cpp": "// the class's own rows\n",
        "Code/Lib/AllocCopy.cpp": "// the copy helper\n",
        "Code/Lib/Dispatch.cpp": "// the backward move\n",
    }
    for src in set(SOURCES.values()) | set(DUP_SOURCES.values()):
        out[src] = "// stand-in\n"
    return out


@pytest.fixture
def tree(tmp_path, image):
    return seed(tmp_path, files())


GOOD_RELOCS = {}
for _at, _offset, _target in F.bindings:
    GOOD_RELOCS.setdefault(F.respell(F.rows[_at][0]), []).append((_offset, rename.REL32, _target))


def context(root, refs=(), relocs=None):
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
def objects(monkeypatch):
    state = {"consumers": [], "referenced": set()}
    monkeypatch.setattr(rename, "pin_consumers", lambda ctx, names, words, rebuilt: (list(state["consumers"]), 0))
    monkeypatch.setattr(rename, "object_pin_references",
                        lambda objects, names: [f"an object names {n}" for n in names if n in state["referenced"]])
    monkeypatch.setattr(rename, "source_objects", lambda ctx, sources: {})
    return state


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


# ------------------------------------------------------------------ the entry

def test_the_entry_is_what_the_coordinator_reviewed():
    assert F in R.FAMILIES and isinstance(F, R.StandInElementFamily)
    assert (F.old, F.new, F.copy, F.stride) == ("BfmeAssignRecord44", "ScoredKillTracker", 0x0055AC1F, 0x2C)
    assert set(F.rows) == {0x0055AC1F, 0x004143A4, 0x00414760, 0x004149B4, 0x004146E2, 0x0041484C}
    assert set(F.duplicates) == {0x00414793, 0x004144F0} and set(F.retired) == {0x00414793, 0x0007E364}
    assert set(F.pins) == {0x004143D6, 0x00414403}
    assert NEW_COPY == "??4ScoredKillTracker@@QAEAAV0@ABV0@@Z"
    assert F.respell(F.rows[0x00414760][0]) == ("?erase@?$vector@VScoredKillTracker@@V?$allocator@VScoredKillTracker@@@"
                                                "_STL@@@_STL@@QAEPAVScoredKillTracker@@PAV3@0@Z")
    assert all(R.family_of(at, F.respell(old)) is F for at, (old, _f) in F.rows.items())
    assert all(R.family_of(at, F.respell(old)) is None for at, (old, _f) in F.duplicates.items())


def test_the_real_image_states_them_all():
    if not R.build.EXE.exists():
        pytest.skip("no retail image here")
    assert R.facts_problems(F.facts()) == []


def kwargs():
    return dict(old=F.old, new=F.new, copy=F.copy, stride=F.stride, spellings=dict(F.spellings), members=dict(F.members),
                bindings=tuple(F.bindings), rows=dict(F.rows), pins=dict(F.pins), duplicates=dict(F.duplicates),
                retired=dict(F.retired))


ERASE = 0x00414760


@pytest.mark.parametrize("label, change, message", [
    ("a spelling that changes more than the element",
     lambda k: k["spellings"].update({OLD_COPY: NEW_COPY.replace("QAE", "UAE")}), "stand-in swap alone"),
    ("a spelling onto another class",
     lambda k: k["spellings"].update({OLD_COPY: "??4LadderPref@@QAEAAV0@ABV0@@Z"}), "stand-in swap alone"),
    ("a spelling left out", lambda k: k["spellings"].pop(OLD_COPY), "stand-in swap alone"),
    ("a spelling no row has", lambda k: k["spellings"].update({"?x@@YAXXZ": "?y@@YAXXZ"}), "every spelling"),
    ("a row that does not spell the stand-in",
     lambda k: k["rows"].update({0x00001000: ("?other@@YAXXZ", (R.Fact("calls", 0x00001001, 0x0055A91A),))}),
     "does not spell the stand-in"),
    ("a member of another class", lambda k: k["members"].update({0x0055A91A: "?rva0055A91A@LadderPref@@QAEXXZ"}),
     "is no row of"),
    ("a stride of another element size", lambda k: k.update(stride=0x30), "not the element's"),
    ("a duplicate onto another name",
     lambda k: k["members"].update({0x004144F0: "??$_Destroy@PAVScoredKillTracker@@@_STL@@YAXPAVScoredKillTracker@@1@Z"}),
     "retired only onto"),
    ("a retired pin the class does not row",
     lambda k: k["members"].pop(0x0007E364), "only a pin on an address"),
    ("a row reaching nothing",
     lambda k: k["rows"].update({ERASE: (F.rows[ERASE][0], (R.Fact("calls", 0x00414774, 0x00001000),))}),
     "reaches no member"),
    ("a binding no call states", lambda k: k.update(bindings=tuple((a, o + 1 if a == ERASE else o, t) for a, o, t in F.bindings)),
     "not one of the row's own calls"),
    ("a binding to another target",
     lambda k: k.update(bindings=tuple((a, o, "?other@@YAXXZ" if a == 0x004146E2 else t) for a, o, t in F.bindings)),
     "which is not"),
    ("a row with no binding", lambda k: k.update(bindings=tuple(b for b in F.bindings if b[0] != 0x004149B4)),
     "every row needs a binding"),
    ("no members", lambda k: k.update(members={}), "needs its members"),
    ("a duplicate also respelled",
     lambda k: k["rows"].update({0x004144F0: F.duplicates[0x004144F0]}), "never both"),
])
def test_the_constructor_refuses_each_missing_condition(label, change, message):
    k = kwargs()
    change(k)
    with pytest.raises(ValueError, match=message):
        R.StandInElementFamily(**k)


def test_the_real_kwargs_build():
    R.StandInElementFamily(**kwargs())


# ------------------------------------------------------------------ the plan

def test_the_rows_are_respelled_and_the_duplicates_retired(tree):
    ctx, _ = context(tree)
    got = plan(ctx)
    rows = got.after["reverse/functions.csv"].decode()
    for at, (old, _f) in F.rows.items():
        assert old not in rows and f"{F.respell(old)},,0x{at:08X},{SIZES[at]},{SOURCES[at]},matched" in rows
    for at, (old, _f) in F.duplicates.items():
        assert f"{old},," not in rows
        assert rows.count(f",0x{at:08X},") == 1 + (at in PIN_ROWS)          # only the class's own row is left
    deleted = got.after["reverse/deleted_rows.csv"].decode()
    assert all(old in deleted for old, _f in F.duplicates.values()) and OLD_COPY in deleted
    assert got.removed == [EMPTIED] and EMPTIED not in got.verify
    basis = got.after["reverse/name_basis.csv"].decode()
    assert f"function,{OLD_COPY},{NEW_COPY},retail,{F.evidence()},{SOURCES[COPY]},0x{COPY:08X}" in basis
    assert sum(1 for line in basis.splitlines()[1:]) == len(F.rows)
    pins = got.after["reverse/symbols.csv"].decode()
    for at, (old, _f) in F.pins.items():
        assert old not in pins and f"{F.respell(old)},0x{at:08X}" in pins
    for at, (old, _f) in F.retired.items():
        assert f"{old},0x{at:08X}" not in pins
    assert got.identity["bindings"] and got.identity["duplicates"]
    assert {at for _n, at, _s in got.identity["duplicates"]} == set(F.duplicates)


def test_each_byte_of_each_fact_refuses(tree, image):
    ctx, _ = context(tree)
    for fact in F.facts():
        for i in range(len(R.expected(fact))):
            keep = image[fact.site + i]
            image[fact.site + i] = keep ^ 0xFF
            with pytest.raises(Refusal, match="retail does not state"):
                plan(ctx)
            image[fact.site + i] = keep


def test_an_unregistered_class_refuses(tmp_path, image):
    ctx, _ = context(seed(tmp_path, files(registered=False)))
    with pytest.raises(Refusal, match="is not registered"):
        plan(ctx)


@pytest.mark.parametrize("size", [40, 48, 0x2D])
def test_a_class_of_another_size_refuses(tmp_path, image, size):
    """A wrong element type: the registered class is not the size retail's strides state."""
    ctx, _ = context(seed(tmp_path, files(header_size=size)))
    with pytest.raises(Refusal, match="asserts sizeof"):
        plan(ctx)


def test_a_stand_in_with_a_constructor_refuses(tree):
    path = tree / "reverse/functions.csv"
    path.write_text(ledger_rows(extra=["??0BfmeAssignRecord44@@QAE@XZ,,0x00001000,8,Code/Lib/Announcer.cpp,matched,ctor\n"]))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="constructor or destructor row of its own"):
        plan(ctx)


@pytest.mark.parametrize("at", sorted(F.members))
def test_each_member_must_be_rowed(tree, at):
    (tree / "reverse/functions.csv").write_text(ledger_rows(skip={F.members[at]}))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="is not rowed at"):
        plan(ctx)


def test_a_duplicate_of_another_size_refuses(tree):
    name = F.members[0x004144F0]
    (tree / "reverse/functions.csv").write_text(ledger_rows(resize={name: 30}))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="at another size"):
        plan(ctx)


def test_a_fact_outside_its_row_refuses(tree):
    (tree / "reverse/functions.csv").write_text(ledger_rows(resize={F.rows[0x0041484C][0]: 80}))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="is outside"):
        plan(ctx)


def test_a_pin_fact_in_no_row_refuses(tree):
    (tree / "reverse/functions.csv").write_text(ledger_rows(skip={PIN_ROWS[0x00414403][0]}))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="in no row of the family"):
        plan(ctx)


def test_a_consumer_of_the_retired_pins_refuses(tree, objects):
    objects["consumers"] = ["Code/Lib/Other.cpp binds it"]
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="cannot be retired"):
        plan(ctx)


def test_a_unit_still_spelling_a_duplicate_refuses(tree):
    write(tree / "Code/Lib/Other.cpp", f"// {F.duplicates[0x004144F0][0]}\n")
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="still spells"):
        plan(ctx)


def test_an_emptied_source_is_never_prepared(tree):
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="deleted, not prepared"):
        plan(ctx, prepared={**PREPARED, EMPTIED: b"// still here\n"})


def test_the_request_may_not_add_rows_or_change_the_evidence(tree):
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="--evidence must name the proof"):
        plan(ctx, evidence="retail:0x00000001 calls=0x00000002")
    with pytest.raises(Refusal, match="no --old, no --also"):
        plan(ctx, also=[(0x00001000, "?x@@YAXXZ")])
    with pytest.raises(Refusal, match="--prepared"):
        plan(ctx, prepared=None)


def test_another_class_is_no_family(tree):
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="proves only the families"):
        plan(ctx, new="??4LadderPref@@QAEAAV0@ABV0@@Z")


# ------------------------------------------------------------------ the rebuilt objects

def test_the_landing_writes_it_all(tree):
    ctx, state = context(tree)
    land(ctx, plan(ctx), state)
    text = (tree / "reverse/functions.csv").read_text()
    assert NEW_COPY in text and OLD_COPY not in text
    assert not (tree / EMPTIED).exists()


@pytest.mark.parametrize("label, change", [
    ("no relocation at all", lambda relocs: []),
    ("another offset", lambda relocs: [(o + 1, k, t) for o, k, t in relocs]),
    ("another type", lambda relocs: [(o, rename.DIR32, t) for o, k, t in relocs]),
    ("the stand-in's callee", lambda relocs: [(o, k, t.replace("ScoredKillTracker", "BfmeAssignRecord44")) for o, k, t in relocs]),
])
def test_a_rebuilt_row_not_binding_its_target_is_undone(tree, label, change):
    for at in sorted(F.rows):
        name = F.respell(F.rows[at][0])
        ctx, state = context(tree)
        with pytest.raises(VerifyFailed, match="does not bind"):
            land(ctx, plan(ctx), state, relocs={**GOOD_RELOCS, name: change(GOOD_RELOCS[name])})
        assert OLD_COPY in (tree / "reverse/functions.csv").read_text() and (tree / EMPTIED).exists()


def test_a_rebuilt_object_naming_a_retired_duplicate_is_undone(tree, objects):
    objects["referenced"] = {F.duplicates[0x004144F0][0]}
    ctx, state = context(tree)
    with pytest.raises(VerifyFailed, match="an object names"):
        land(ctx, plan(ctx), state)
    assert (tree / EMPTIED).exists()


def test_a_rebuilt_object_binding_a_retired_pin_is_undone(tree):
    (old, _f) = F.retired[0x0007E364]
    ctx, state = context(tree)
    still = dict(source=SOURCES[0x0041484C], row=F.respell(F.rows[0x0041484C][0]), rva=0x0041484C, symbol=old,
                 target=0x0007E364, cls="owner")
    with pytest.raises(VerifyFailed, match="still binds the retired pin"):
        land(ctx, plan(ctx), state, refs=after_refs() + [still])


def test_a_row_with_no_references_is_undone(tree):
    ctx, state = context(tree)
    with pytest.raises(VerifyFailed, match="has no references"):
        land(ctx, plan(ctx), state, refs=after_refs()[:1])


def test_a_new_wrong_binding_is_undone(tree):
    ctx, state = context(tree)
    wrong = dict(source=SOURCES[COPY], row=NEW_COPY, rva=COPY, symbol="x", target=0x1234,
                 cls=next(iter(allowed_symbols.WRONG)))
    with pytest.raises(VerifyFailed, match="gains a wrong binding"):
        land(ctx, plan(ctx), state, refs=after_refs() + [wrong])
