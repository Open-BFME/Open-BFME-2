"""`tools/rename.py function --respell --identity`: a placeholder-typed,
compiler-spelled row respelled by the naming route, gated by code identity.

The shape is P29's: an `operator=` rowed on a map-shaped `_Rb_tree` over a
placeholder element (and its wrapper), whose bytes match retail while its calls
bind local COMDATs of the wrong instantiation. Which spelling is right is a
naming judgement -- a callee's class does not prove the caller's -- so each row
needs its naming approval (`--basis inferred --evidence agree:<id>`, two blind
votes on its placeholder key). The code-identity checks are hard gates on top:

  1. the code-identity check reports a wrong binding before the respell (or the
     row calls a row the same plan respells);
  2. no callee is ICF-marked or doubly named; a callee pin refuses unless it is
     the old-type spelling the respell retires, and that only when no object
     outside the rebuilt units references it;
  3. after ./build.sh every reference of every respelled row binds its owner
     directly (no alias, pin or folded callee), and no touched row gains a wrong
     binding;
  4. the new name is owned by nothing, and both names are compiler-spelled with
     the same operator code or identifier.

The scan itself (tools/allowed_symbols.py) needs objects, so these tests supply
its results through ctx.identity_refs; the pin consumer scan reads real COFF
objects the tests write.
"""
import hashlib
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
sys.path.insert(0, str(TOOLS / "tests"))

import name_agreement  # noqa: E402
import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402
from test_gate_exploits import TEXT, coff  # noqa: E402

OP = 0x002D07F4
WRAP = 0x002D0B36
CLEAR = 0x002572AE
COPY = 0x002D0326
OLD_OP = "??4?$_Rb_tree@URva002D07F4Element@@U?$pair@HH@@@@QAEAAV0@ABV0@@Z"
NEW_OP = "??4?$_Rb_tree@UBfmeStringRecord002CF550@@U1@@@QAEAAV0@ABV0@@Z"
OLD_WRAP = "??4?$map@URva002D07F4Element@@H@@QAEAAV0@ABV0@@Z"
NEW_WRAP = "??4?$set@UBfmeStringRecord002CF550@@@@QAEAAV0@ABV0@@Z"
CLEAR_NAME = "?clear@?$_Rb_tree@UBfmeStringRecord002CF550@@U1@@@QAEXXZ"
COPY_NAME = "?_M_copy@?$_Rb_tree@UBfmeStringRecord002CF550@@U1@@@AAEPAXPAX0@Z"
PLAIN = "?helper@@YAXXZ"
OLD_SCOPE = "?$_Rb_tree@URva002D07F4Element@@U?$pair@HH@@@@"
OLD_CLEAR = f"?clear@{OLD_SCOPE}QAEXXZ"
OLD_COPY = f"?_M_copy@{OLD_SCOPE}AAEPAXPAX0@Z"
PINS = f"name,address,notes\n{OLD_CLEAR},0x002572AE,sweep\n{OLD_COPY},0x002D0326,sweep\n"
OWNER = "Code/Lib/StlSweepW5Rva002D07F4.cpp"
TU = "Code/Thing/ThingFactory.cpp"
CALLER = "Code/Thing/ThingTemplateAssignment.cpp"
CALLER_ROW = "??4ThingTemplate@@QAEAAV0@ABV0@@Z"

FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
{OLD_OP},,0x002D07F4,115,{OWNER},matched,sweep row
{OLD_WRAP},,0x002D0B36,18,{OWNER},matched,sweep row
{CLEAR_NAME},,0x002572AE,41,Code/Lib/Cleanup.cpp,matched,owner
{COPY_NAME},,0x002D0326,115,Code/Lib/Copy.cpp,matched,owner
?ctor@ThingFactory@@QAEXXZ,,0x002D0000,16,{TU},matched,tu row
{CALLER_ROW},,0x002D1101,900,{CALLER},matched,caller of 0x002D07F4
{PLAIN},,0x00403000,8,Code/Lib/Plain.cpp,matched,hand-written
"""
TU_MAP = f"""rva,size,kind,tu,confidence,by,evidence,source
0x002D07F4,115,code,{TU},approved,N,N={TU},{OWNER}
0x002D0B36,18,code,{TU},approved,N,N={TU},{OWNER}
0x00403000,8,code,Code/Lib/Plain.cpp,approved,N,N=x,Code/Lib/Plain.cpp
"""
OWNER_SRC = f"// {OLD_OP}\n// {OLD_WRAP}\nint sweep() {{ return 0; }}\n"
TU_SRC = "void factory() {}\n"
TU_PREPARED = f"// {NEW_OP}\n// {NEW_WRAP}\nvoid factory() {{}}\nint moved() {{ return 0; }}\n"
CALLER_SRC = "struct T { int m388; };\n"
CALLER_PREPARED = "struct T { int m388set; };\n"


def _git(root, *args):
    subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True)


def write(path, text):
    """LF bytes on every host: write_text would write CRLF on Windows."""
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(text.encode("utf-8"))


def commit(root, message="edit"):
    _git(root, "add", "-A")
    _git(root, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", message)


def recommit(root, rel, text):
    write(root / rel, text)
    commit(root)


def agree(root, rid, old, new, rva, agents=("seat-a", "seat-b")):
    """An agreement record and the two blind votes behind it (name_agreement recomputes from votes)."""
    key = f"{OWNER}|function|scope|{old}"
    agreed = root / rename.AGREED
    text = agreed.read_text(encoding="utf-8") if agreed.exists() else rename.AGREED_HEADER + "\n"
    text += rename.csv_line([rid, "function", old, new, f"0x{rva:08X}", ";".join(agents), key, "agreed",
                             ""]).decode()
    write(agreed, text)
    votes = root / name_agreement.VOTES
    text = votes.read_text(encoding="utf-8") if votes.exists() else ",".join(name_agreement.VOTE_COLUMNS) + "\n"
    for agent in agents:
        worker = "w-" + hashlib.sha256(agent.encode()).hexdigest()[:12]
        text += rename.csv_line([key, name_agreement.digest(key, new), "m", agent, worker, "2026-11-08"]).decode()
    write(votes, text)
    return f"agree:{rid}"


@pytest.fixture
def tree(tmp_path):
    files = {
        "reverse/functions.csv": FUNCTIONS,
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/name_basis.csv": "kind,old,new,basis,evidence,source,rva\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "reverse/tu_map.csv": TU_MAP,
        OWNER: OWNER_SRC,
        TU: TU_SRC,
        CALLER: CALLER_SRC,
        "Code/Lib/Cleanup.cpp": "void c() {}\n",
        "Code/Lib/Copy.cpp": "void d() {}\n",
        "Code/Lib/Plain.cpp": "void helper() {}\n",
    }
    for rel, text in files.items():
        write(tmp_path / rel, text)
    agree(tmp_path, "nl-op", OLD_OP, NEW_OP, OP)
    agree(tmp_path, "nl-wrap", OLD_WRAP, NEW_WRAP, WRAP)
    _git(tmp_path, "init", "-q")
    commit(tmp_path, "seed")
    return tmp_path


VOTES = "agree:nl-op agree:nl-wrap"
OLD_PLAIN_SPARE, NEW_PLAIN_SPARE = PLAIN, "?helperSpare@@YAXXZ"
MAP_STATE = {"stale": [], "error": None, "rows": None}


@pytest.fixture(autouse=True)
def fresh_map(monkeypatch):
    """tu_map.current_rows over the fixture's map: fresh unless a test says otherwise."""
    import csv
    import tu_map
    MAP_STATE.update(stale=[], error=None, rows=None)

    def current_rows(layout):
        if MAP_STATE["error"]:
            raise tu_map.NoZhTree(MAP_STATE["error"])
        if MAP_STATE["rows"] is not None:
            return list(MAP_STATE["rows"]), list(MAP_STATE["stale"])
        with open(layout.root / "reverse/tu_map.csv", newline="") as handle:
            return list(csv.DictReader(handle)), list(MAP_STATE["stale"])
    monkeypatch.setattr(tu_map, "current_rows", current_rows)


def ref(row, rva, target, cls, symbol="x", source=OWNER):
    return dict(source=source, row=row, rva=rva, symbol=symbol, target=target, cls=cls)


BEFORE = [ref(OLD_OP, OP, CLEAR, "wrong", OLD_CLEAR),
          ref(OLD_OP, OP, COPY, "wrong", OLD_COPY),
          ref(OLD_WRAP, WRAP, OP, "owner", OLD_OP),
          ref(CALLER_ROW, 0x002D1101, OP, "owner", OLD_OP, CALLER)]
AFTER = [ref(NEW_OP, OP, CLEAR, "owner", CLEAR_NAME, TU),
         ref(NEW_OP, OP, COPY, "owner", COPY_NAME, TU),
         ref(NEW_WRAP, WRAP, OP, "owner", NEW_OP, TU),
         ref(CALLER_ROW, 0x002D1101, OP, "owner", NEW_OP, CALLER)]


def context(root, refs):
    ctx = rename.Context(root, object_scan=False)
    state = {"refs": refs}
    ctx.identity_refs = lambda sources: [r for r in state["refs"] if r["source"] in sources]
    return ctx, state


def plan(ctx, **overrides):
    kwargs = dict(rva=OP, new=NEW_OP, respell=True, identity=True, basis="inferred", evidence=VOTES,
                  prepared={TU: TU_PREPARED.encode(), CALLER: CALLER_PREPARED.encode()},
                  also=[(WRAP, NEW_WRAP)], move_to=TU)
    kwargs.update(overrides)
    return rename.plan_rename("function", ctx=ctx, **kwargs)


def apply(ctx, got, state, after):
    def verify(c, sources):
        state["refs"] = after
        return True
    return rename.apply_rename(got, ctx=ctx, verify=verify, checks=None)


# ------------------------------------------------------------------ the P29 shape

def test_respells_both_rows_into_the_approved_tu(tree):
    ctx, _ = context(tree, BEFORE)
    got = plan(ctx)
    assert (OLD_OP, NEW_OP, OP) in got.renamed_rows and (OLD_WRAP, NEW_WRAP, WRAP) in got.renamed_rows
    rows = got.after["reverse/functions.csv"].decode()
    assert f"{NEW_OP},,0x002D07F4,115,{TU}," in rows and f"{NEW_WRAP},,0x002D0B36,18,{TU}," in rows
    assert OLD_OP not in rows and OWNER not in rows
    assert got.removed == [OWNER]
    assert OWNER not in got.verify and TU in got.verify and CALLER in got.verify
    tu_map = got.after["reverse/tu_map.csv"].decode()
    assert f",{TU}\n" in tu_map.split("\n", 1)[1] and OWNER not in tu_map


def test_each_row_is_recorded_by_its_own_approval(tree):
    """The record is agree:<id> alone, as every inferred landing's (revert finds it by that)."""
    ctx, _ = context(tree, BEFORE)
    got = plan(ctx)
    basis = got.after["reverse/name_basis.csv"].decode()
    assert f"function,{OLD_OP},{NEW_OP},inferred,agree:nl-op,{TU},0x002D07F4" in basis
    assert f"function,{OLD_WRAP},{NEW_WRAP},inferred,agree:nl-wrap,{TU},0x002D0B36" in basis
    assert rename.inferred_record("agree:nl-op") == "nl-op"
    assert got.evidence.startswith("agree:nl-op agree:nl-wrap; code-identity: 0x002D07F4 calls 0x002572AE, "
                                   "0x002D0326 (wrong before: 0x002572AE, 0x002D0326)")
    assert "0x002D0B36 calls 0x002D07F4 (calls the respelled 0x002D07F4)" in got.evidence


def test_apply_writes_moves_and_deletes_when_the_scan_proves_it(tree):
    ctx, state = context(tree, BEFORE)
    apply(ctx, plan(ctx), state, AFTER)
    assert not (tree / OWNER).exists()
    assert (tree / TU).read_bytes() == TU_PREPARED.encode()
    assert NEW_OP in (tree / "reverse/functions.csv").read_text()


def test_respell_without_move_keeps_the_source(tree):
    ctx, _ = context(tree, BEFORE)
    got = plan(ctx, move_to=None, prepared={OWNER: (OWNER_SRC.replace(OLD_OP, NEW_OP)
                                                    .replace(OLD_WRAP, NEW_WRAP)).encode()})
    assert not got.removed and f"{NEW_OP},,0x002D07F4,115,{OWNER}," in got.after["reverse/functions.csv"].decode()


def test_the_plan_names_the_removed_source_and_the_evidence(tree):
    ctx, _ = context(tree, BEFORE)
    text = plan(ctx).report()
    assert f"sources removed (1): {OWNER}" in text and "evidence: agree:nl-op agree:nl-wrap; code-identity:" in text


# --------------------------------------------- the naming route (review round 2: findings 1, 5)

def test_refused_without_the_naming_basis(tree):
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="naming route's approval"):
        plan(ctx, basis=None, evidence="")
    with pytest.raises(Refusal, match="naming route's approval"):
        plan(ctx, basis="canonical:zh")


def test_refused_without_an_approval_token(tree):
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="one naming approval per"):
        plan(ctx, evidence="code-identity")


def test_a_callees_class_proves_nothing_without_votes(tree):
    """Finding 1 (review_receiver_repro.py): `mov ecx,[ecx+4]; call clear` acts on a
    contained object, so the callees' class is not the caller's. A spelling no vote
    approved is refused whatever the callees bind; the voters' spelling lands."""
    member = "??4?$_Rb_tree@UBfmeStringRecord002CF550@@H@@QAEAAV0@ABV0@@Z"
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="no naming approval covers"):
        plan(ctx, new=member, evidence="agree:nl-op", also=[], move_to=None,
             prepared={OWNER: OWNER_SRC.replace(OLD_OP, member).replace(OLD_WRAP, NEW_WRAP).encode()})
    voted = agree(tree, "nl-member", OLD_OP, member, OP, agents=("seat-a", "seat-b", "seat-c"))
    commit(tree)
    ctx, _ = context(tree, BEFORE)
    got = plan(ctx, new=member, evidence=voted, also=[], move_to=None,
               prepared={OWNER: OWNER_SRC.replace(OLD_OP, member).encode()})
    assert (OLD_OP, member, OP) in got.renamed_rows


def test_an_approval_covers_its_exact_signature_only(tree):
    """Finding 5 (review_r2_repros.py): a parameter respelled to an invented type is
    another spelling, which the approval of NEW_OP does not cover."""
    invented = NEW_OP.replace("ABV0@", "ABVInventedRealType@@")
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="no naming approval covers"):
        plan(ctx, new=invented, prepared={TU: TU_PREPARED.replace(NEW_OP, invented).encode(),
                                          CALLER: CALLER_PREPARED.encode()})


def test_refused_when_an_approval_is_left_over_or_reused(tree):
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="one approval per respelled row, each once"):
        plan(ctx, evidence="agree:nl-op agree:nl-wrap agree:nl-op")
    agree(tree, "nl-spare", OLD_PLAIN_SPARE, NEW_PLAIN_SPARE, 0x00403000)
    commit(tree)
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="one approval per respelled row, each once"):
        plan(ctx, evidence="agree:nl-op agree:nl-wrap agree:nl-spare")
    with pytest.raises(Refusal, match="no naming approval covers"):
        plan(ctx, evidence="agree:nl-op")


def test_cli_requires_the_basis_for_identity():
    with pytest.raises(SystemExit):
        rename.main(["function", "--rva", "0x2D07F4", "--new", NEW_OP, "--respell", "--identity",
                     "--prepared", f"{TU}=/dev/null"])


# ------------------------------------------------------------- what it refuses

def test_refused_when_the_calls_are_still_wrong_after_the_respell(tree):
    """Identical bytes are not enough; the bindings must follow."""
    ctx, state = context(tree, BEFORE)
    got = plan(ctx)
    still = [dict(r, cls="wrong") if r["row"] == NEW_OP and r["target"] == COPY else r for r in AFTER]
    with pytest.raises(VerifyFailed) as error:
        apply(ctx, got, state, still)
    assert "0x002D0326" in str(error.value) and "every file restored" in str(error.value)
    assert (tree / OWNER).read_bytes() == OWNER_SRC.encode()          # the deleted source is back
    assert OLD_OP in (tree / "reverse/functions.csv").read_text()


def test_refused_when_a_respelled_row_binds_an_alias_after_the_build(tree):
    ctx, state = context(tree, BEFORE)
    got = plan(ctx)
    aliased = [dict(r, cls="alias") if r["row"] == NEW_OP and r["target"] == CLEAR else r for r in AFTER]
    with pytest.raises(VerifyFailed, match=r"0x002572AE \(alias\), not retail's row"):
        apply(ctx, got, state, aliased)


def test_refused_when_a_respelled_row_binds_nothing_directly(tree):
    ctx, state = context(tree, BEFORE)
    got = plan(ctx)
    with pytest.raises(VerifyFailed, match="binds no retail row directly"):
        apply(ctx, got, state, [dict(r, cls="label") if r["row"] == NEW_OP else r for r in AFTER])


def test_refused_when_a_touched_row_gains_a_wrong_binding(tree):
    ctx, state = context(tree, BEFORE)
    got = plan(ctx)
    worse = AFTER + [ref(CALLER_ROW, 0x002D1101, 0x00999999, "wrong", "?y", CALLER)]
    with pytest.raises(VerifyFailed, match="gains a wrong binding"):
        apply(ctx, got, state, worse)


def test_a_touched_rows_wrong_binding_of_another_symbol_is_new(tree):
    """The key names the referenced symbol: another wrong symbol at the same target is new."""
    before = BEFORE + [ref(CALLER_ROW, 0x002D1101, 0x00999999, "wrong", "?a@@YAXXZ", CALLER)]
    after = AFTER + [ref(CALLER_ROW, 0x002D1101, 0x00999999, "wrong", "?b@@YAXXZ", CALLER)]
    ctx, state = context(tree, before)
    got = plan(ctx)
    with pytest.raises(VerifyFailed, match=r"gains a wrong binding of \?b@@YAXXZ"):
        apply(ctx, got, state, after)


def test_a_touched_rows_unchanged_wrong_binding_is_known(tree):
    kept = ref(CALLER_ROW, 0x002D1101, 0x00999999, "wrong", "?a@@YAXXZ", CALLER)
    ctx, state = context(tree, BEFORE + [kept])
    apply(ctx, plan(ctx), state, AFTER + [kept])
    assert NEW_OP in (tree / "reverse/functions.csv").read_text()


def test_refused_for_a_hand_written_row(tree):
    """A plain function name is a naming claim for function --new, not this route."""
    ctx, _ = context(tree, BEFORE + [ref(PLAIN, 0x00403000, CLEAR, "wrong", source="Code/Lib/Plain.cpp")])
    with pytest.raises(Refusal, match="hand-written name"):
        plan(ctx, rva=0x00403000, new="?helper2@@YAXXZ", also=[], move_to=None,
             prepared={"Code/Lib/Plain.cpp": b"void helper2() {}\n"})


def test_refused_when_a_template_name_becomes_hand_written(tree):
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="hand-written name"):
        plan(ctx, new="?assign@@YAXXZ", also=[])


def test_a_free_function_taking_a_template_is_hand_written():
    """`?$` in a parameter does not make a template member."""
    assert rename.identity_head("?helper@@YAXV?$vector@URva00400000Thing@@@@@Z") is None
    assert rename.identity_head("?helper@Plain@@QAEXV?$vector@H@@@Z") is None
    assert rename.identity_head(CLEAR_NAME) == "clear"
    assert rename.identity_head(OLD_OP) == "??4"


def test_refused_for_a_respell_between_real_types(tree):
    real = "??4?$_Rb_tree@UThingTemplate@@U?$pair@HH@@@@QAEAAV0@ABV0@@Z"
    recommit(tree, "reverse/functions.csv", FUNCTIONS.replace(OLD_OP, real))
    recommit(tree, OWNER, OWNER_SRC.replace(OLD_OP, real))
    ctx, _ = context(tree, [dict(r, row=real) if r["row"] == OLD_OP else r for r in BEFORE])
    with pytest.raises(Refusal, match="names no placeholder type"):
        plan(ctx, also=[], move_to=None, prepared={OWNER: OWNER_SRC.replace(OLD_OP, NEW_OP).encode()})


def test_refused_when_the_new_name_is_already_owned(tree):
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="once"):
        plan(ctx, also=[(WRAP, NEW_OP)])
    owned = (tree / "reverse/functions.csv").read_text() + f"{NEW_OP},,0x00500000,4,Code/Lib/Copy.cpp,matched,x\n"
    recommit(tree, "reverse/functions.csv", owned)
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="already names a row or pin"):
        plan(ctx)


def test_refused_when_the_operator_changes(tree):
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="changes the operator or identifier"):
        plan(ctx, new=NEW_OP.replace("??4", "??8", 1), also=[])


def test_refused_without_a_wrong_binding_to_prove(tree):
    ctx, _ = context(tree, [dict(r, cls="owner") for r in BEFORE])
    with pytest.raises(Refusal, match="no wrong binding"):
        plan(ctx)


def test_refused_without_any_scanned_reference(tree):
    ctx, _ = context(tree, [r for r in BEFORE if r["row"] != OLD_OP])
    with pytest.raises(Refusal, match="no references"):
        plan(ctx)


def test_refused_when_a_callee_is_icf_marked(tree):
    """Finding 2 (review_fold_repro.py): a folded callee's binding proves no one name."""
    recommit(tree, "reverse/functions.csv", FUNCTIONS.replace("matched,owner", "matched,ICF folded member owner"))
    recommit(tree, "reverse/symbols.csv", PINS)
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="ICF-marked .*a folded callee's binding proves no one name"):
        plan(ctx)


def test_refused_when_a_callee_carries_two_names(tree):
    recommit(tree, "reverse/functions.csv", FUNCTIONS + "?twin@@YAXXZ,,0x002572AE,41,Code/Lib/Plain.cpp,matched,x\n")
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="names .*a folded callee's binding proves no one name"):
        plan(ctx)


def test_refused_when_a_callee_is_folded_after_the_build(tree):
    ctx, state = context(tree, BEFORE)
    got = plan(ctx)

    def verify(c, sources):
        state["refs"] = AFTER
        text = (tree / "reverse/functions.csv").read_text().replace(",0x002572AE,41,Code/Lib/Cleanup.cpp,matched,owner",
                                                                   ",0x002572AE,41,Code/Lib/Cleanup.cpp,matched,icf-owner=x")
        write(tree / "reverse/functions.csv", text)
        return True
    with pytest.raises(VerifyFailed, match="binds 0x002572AE, which ICF-marked"):
        rename.apply_rename(got, ctx=ctx, verify=verify, checks=None)


def test_refused_when_a_callee_carries_a_pin_after_the_build(tree):
    ctx, state = context(tree, BEFORE)
    got = plan(ctx)

    def verify(c, sources):
        state["refs"] = AFTER
        write(tree / "reverse/symbols.csv", "name,address,notes\n?late@@YAXXZ,0x002D0326,x\n")
        return True
    with pytest.raises(VerifyFailed, match=r"binds 0x002D0326, which carries pin \?late@@YAXXZ"):
        rename.apply_rename(got, ctx=ctx, verify=verify, checks=None)


def test_move_refused_outside_the_approved_tu(tree):
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="not approved"):
        plan(ctx, move_to=CALLER)


def test_move_plans_by_the_rebuilt_map_when_the_committed_one_is_stale(tree):
    MAP_STATE["stale"] = ["functions.csv"]
    ctx, _ = context(tree, BEFORE)
    assert plan(ctx).removed == [OWNER]


def test_move_refused_when_the_rebuilt_map_does_not_approve(tree):
    MAP_STATE["stale"] = ["functions.csv"]
    MAP_STATE["rows"] = [dict(rva="0x002D07F4", tu=TU, confidence="approved"),
                         dict(rva="0x002D0B36", tu=TU, confidence="hinted")]
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="0x002D0B36 is not approved for .*rebuilt in memory"):
        plan(ctx)


def test_move_refused_when_the_map_cannot_be_checked(tree):
    MAP_STATE["error"] = "no ZH tree"
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="cannot rebuild reverse/tu_map.csv from current inputs: no ZH tree"):
        plan(ctx)


def test_move_refused_when_the_owner_keeps_other_rows(tree):
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="also holds"):
        plan(ctx, also=[], evidence="agree:nl-op")


def test_refused_when_an_unprepared_unit_still_spells_the_old_name(tree):
    recommit(tree, "Code/Lib/Copy.cpp", f"// calls {OLD_OP}\nvoid d() {{}}\n")
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="still spells"):
        plan(ctx)


def test_identity_needs_respell(tree):
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="--respell --identity"):
        plan(ctx, respell=False)


# ------------------------------------------- old-type callee pins: consumers read from objects

SKIPPED = (OWNER, TU, CALLER)        # owner and prepared units: the plan rebuilds them


def obj(root, name, references=(), defines=("?f@@YAXXZ",), directives=""):
    """A real COFF object: `defines` in .text, `references` external, `directives` in .drectve."""
    sections = [(".text", TEXT, b"\xc3", [])]
    if directives:
        sections.append((".drectve", 0x00100A00, directives.encode(), []))
    symbols = [(n, 0, 1, 0x20, 2, 0) for n in defines] + [(n, 0, 0, 0x20, 2, 0) for n in references]
    path = root / "objects" / name
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(coff(sections, symbols))
    return path


@pytest.fixture
def objects(tree, monkeypatch):
    """rowed_objects over real objects, every one current; a test edits `state`."""
    state = {"objects": {src: [obj(tree, Path(src).stem + ".obj")] for src in
                         ("Code/Lib/Cleanup.cpp", "Code/Lib/Copy.cpp", "Code/Lib/Plain.cpp", *SKIPPED)},
             "stale": set(), "rebuilt": [], "rebuild_ok": True}
    monkeypatch.setattr(rename, "rowed_objects", lambda ctx: dict(state["objects"]))
    monkeypatch.setattr(rename, "object_is_current", lambda ctx, src, path: src not in state["stale"])

    def rebuild(ctx, sources):
        state["rebuilt"].append(sorted(sources))
        if state["rebuild_ok"]:
            state["stale"] -= set(sources)
        return state["rebuild_ok"]
    monkeypatch.setattr(rename, "rebuild_sources", rebuild)
    recommit(tree, "reverse/symbols.csv", PINS)
    return state


def other_unit(tree, state, text, **objargs):
    """Code/Lib/Other.cpp, rowed, with its object."""
    recommit(tree, "Code/Lib/Other.cpp", text)
    recommit(tree, "reverse/functions.csv", FUNCTIONS + "?o@@YAXXZ,,0x00650000,8,Code/Lib/Other.cpp,matched,x\n")
    state["objects"]["Code/Lib/Other.cpp"] = [obj(tree, "Other.obj", **objargs)]


def test_the_old_type_callee_pins_are_retired(tree, objects):
    ctx, _ = context(tree, BEFORE)
    got = plan(ctx)
    assert sorted(got.dropped_pins) == sorted([(OLD_CLEAR, CLEAR_NAME, "0x002572AE"),
                                               (OLD_COPY, COPY_NAME, "0x002D0326")])
    assert got.after["reverse/symbols.csv"].decode() == "name,address,notes\n"
    assert ("retires the old-type pin(s) at 0x002572AE, 0x002D0326 (0 stale object(s) rebuilt for the "
            "consumer scan)") in got.evidence
    assert CLEAR in got.claims and COPY in got.claims


def test_apply_retires_the_pins_when_the_row_binds_the_real_rows(tree, objects):
    ctx, state = context(tree, BEFORE)
    apply(ctx, plan(ctx), state, AFTER)
    assert OLD_CLEAR not in (tree / "reverse/symbols.csv").read_text()


def test_refused_when_the_row_still_binds_the_pin_name_after_the_build(tree, objects):
    ctx, state = context(tree, BEFORE)
    got = plan(ctx)
    via_pin = [dict(r, symbol=OLD_CLEAR) if r["row"] == NEW_OP and r["target"] == CLEAR else r for r in AFTER]
    with pytest.raises(VerifyFailed, match="still binds the retired pin"):
        apply(ctx, got, state, via_pin)
    assert OLD_CLEAR in (tree / "reverse/symbols.csv").read_text()      # restored


def test_refused_when_a_rebuilt_object_references_the_pin_after_the_build(tree, objects):
    ctx, state = context(tree, BEFORE)
    got = plan(ctx)
    objects["objects"][CALLER] = [obj(tree, "CallerAfter.obj", references=(OLD_COPY,))]
    with pytest.raises(VerifyFailed, match=f"{CALLER}'s object CallerAfter.obj references"):
        apply(ctx, got, state, AFTER)


def test_refused_when_a_header_consumer_references_the_pin(tree, objects):
    """Finding 2, header mode: Other.cpp spells no placeholder itself; its object references the pin."""
    recommit(tree, "Code/Lib/Other.h", "struct Rva002D07F4Element;\n")
    other_unit(tree, objects, '#include "Other.h"\nvoid o() {}\n', references=(OLD_CLEAR,))
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="Code/Lib/Other.cpp's object Other.obj references"):
        plan(ctx)


def test_refused_when_an_alternatename_names_the_pin(tree, objects):
    """Finding 2, alternatename mode: a /alternatename binding the pin is a consumer."""
    other_unit(tree, objects, "void o() {}\n",
               directives=f"/alternatename:?bridge@@YAXXZ={OLD_CLEAR} ")
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="Code/Lib/Other.cpp's object Other.obj references"):
        plan(ctx)


def test_refused_when_a_rowed_object_is_missing(tree, objects):
    """Finding 2, partial-object mode: an object that cannot be read is never read as clean."""
    other_unit(tree, objects, "void o() {}\n")
    objects["objects"]["Code/Lib/Other.cpp"] = []
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="Code/Lib/Other.cpp has no object to read"):
        plan(ctx)


def test_refused_when_a_rowed_object_is_unreadable(tree, objects):
    other_unit(tree, objects, "void o() {}\n")
    broken = tree / "objects" / "Broken.obj"
    broken.write_bytes(b"\0" * 4)
    objects["objects"]["Code/Lib/Other.cpp"] = [broken]
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="Broken.obj is missing or unreadable"):
        plan(ctx)


def test_a_stale_object_that_spells_the_type_is_rebuilt_first(tree, objects):
    recommit(tree, "Code/Lib/Other.h", "struct Rva002D07F4Element;\n")
    other_unit(tree, objects, '#include "Other.h"\nvoid o() {}\n')
    objects["stale"] = {"Code/Lib/Other.cpp", "Code/Lib/Plain.cpp"}       # Plain.cpp spells neither
    ctx, _ = context(tree, BEFORE)
    got = plan(ctx)
    assert objects["rebuilt"] == [["Code/Lib/Other.cpp"]]
    assert "(1 stale object(s) rebuilt for the consumer scan)" in got.evidence


def test_refused_when_a_stale_object_cannot_be_rebuilt(tree, objects):
    other_unit(tree, objects, "struct Rva002D07F4Element; void o() {}\n")
    objects["stale"] = {"Code/Lib/Other.cpp"}
    objects["rebuild_ok"] = False
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="could not rebuild the stale object"):
        plan(ctx)


def test_a_header_spelling_the_old_type_is_not_a_consumer(tree, objects):
    recommit(tree, "Code/Lib/Other.h", "struct Rva002D07F4Element;\n")
    ctx, _ = context(tree, BEFORE)
    assert len(plan(ctx).dropped_pins) == 2


def test_refused_when_a_callee_carries_an_unrelated_pin(tree, objects):
    recommit(tree, "reverse/symbols.csv", "name,address,notes\n?clearPin@@YAXXZ,0x002572AE,pin\n")
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match=r"carries pin \?clearPin@@YAXXZ.*proves nothing"):
        plan(ctx)


def test_refused_for_an_old_type_pin_of_another_member(tree, objects):
    other = f"?_M_erase@{OLD_SCOPE}AAEXPAX@Z"
    recommit(tree, "reverse/symbols.csv", f"name,address,notes\n{other},0x002572AE,sweep\n")
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="proves nothing"):
        plan(ctx)


def test_refused_for_an_old_type_pin_the_row_does_not_bind(tree, objects):
    before = [dict(r, symbol="?clear@other@@QAEXXZ") if r["target"] == CLEAR else r for r in BEFORE]
    ctx, _ = context(tree, before)
    with pytest.raises(Refusal, match="proves nothing"):
        plan(ctx)


def test_refused_for_a_pin_naming_a_second_address(tree, objects):
    recommit(tree, "reverse/symbols.csv", PINS + f"{OLD_CLEAR},0x00700000,elsewhere\n")
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="proves nothing"):
        plan(ctx)
