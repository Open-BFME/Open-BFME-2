"""`tools/rename.py function --respell --identity`: compiler-spelled rows respelled
by code identity, with no naming vote.

The shape is P29's: an `operator=` rowed on a map-shaped `_Rb_tree` over a
placeholder element (and its wrapper), whose bytes match retail while its calls
bind local COMDATs of the wrong instantiation. Retail's callees (the rowed clear
and _M_copy of the set-shaped tree) prove the real type, so the respelled name is
derived, not chosen. The rule is mechanical:

  1. the code-identity check reports a wrong binding before the respell (or the
     row is a wrapper of a row the same plan respells);
  2. after ./build.sh every reference of every respelled row binds its owner,
     and no touched row gains a wrong binding;
  3. the new name is owned by nothing, and both names are compiler-spelled with
     the same operator code or identifier;
  4. the evidence records the callee RVAs.

The scan itself (tools/allowed_symbols.py) needs objects, so these tests supply
its results through ctx.identity_refs.
"""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

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
OWNER = "Code/Lib/StlSweepW5Rva002D07F4.cpp"
TU = "Code/Thing/ThingFactory.cpp"
CALLER = "Code/Thing/ThingTemplateAssignment.cpp"

FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
{OLD_OP},,0x002D07F4,115,{OWNER},matched,sweep row
{OLD_WRAP},,0x002D0B36,18,{OWNER},matched,sweep row
{CLEAR_NAME},,0x002572AE,41,Code/Lib/Cleanup.cpp,matched,owner
{COPY_NAME},,0x002D0326,115,Code/Lib/Copy.cpp,matched,owner
?ctor@ThingFactory@@QAEXXZ,,0x002D0000,16,{TU},matched,tu row
??4ThingTemplate@@QAEAAV0@ABV0@@Z,,0x002D1101,900,{CALLER},matched,caller of 0x002D07F4
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
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(tmp_path, "init", "-q")
    _git(tmp_path, "add", "-A")
    _git(tmp_path, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "seed")
    return tmp_path


def ref(row, rva, target, cls, symbol="x", source=OWNER):
    return dict(source=source, row=row, rva=rva, symbol=symbol, target=target, cls=cls)


BEFORE = [ref(OLD_OP, OP, CLEAR, "wrong", "?clear@?$_Rb_tree@URva002D07F4Element@@"),
          ref(OLD_OP, OP, COPY, "wrong", "?_M_copy@?$_Rb_tree@URva002D07F4Element@@"),
          ref(OLD_WRAP, WRAP, OP, "owner", OLD_OP),
          ref("??4ThingTemplate@@QAEAAV0@ABV0@@Z", 0x002D1101, OP, "owner", OLD_OP, CALLER)]
AFTER = [ref(NEW_OP, OP, CLEAR, "owner", CLEAR_NAME, TU),
         ref(NEW_OP, OP, COPY, "owner", COPY_NAME, TU),
         ref(NEW_WRAP, WRAP, OP, "owner", NEW_OP, TU),
         ref("??4ThingTemplate@@QAEAAV0@ABV0@@Z", 0x002D1101, OP, "owner", NEW_OP, CALLER)]


def context(root, refs):
    ctx = rename.Context(root, object_scan=False)
    state = {"refs": refs}
    ctx.identity_refs = lambda sources: [r for r in state["refs"] if r["source"] in sources]
    return ctx, state


def plan(ctx, **overrides):
    kwargs = dict(rva=OP, new=NEW_OP, respell=True, identity=True,
                  prepared={TU: TU_PREPARED.encode(), CALLER: CALLER_PREPARED.encode()},
                  also=[(WRAP, NEW_WRAP)], move_to=TU)
    kwargs.update(overrides)
    return rename.plan_rename("function", ctx=ctx, **kwargs)


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


def test_evidence_records_the_callee_rvas_and_needs_no_vote(tree):
    ctx, _ = context(tree, BEFORE)
    got = plan(ctx)
    basis = got.after["reverse/name_basis.csv"].decode()
    assert "code-identity:" in basis and "0x002572AE" in basis and "0x002D0326" in basis
    assert ",inferred," in basis and "agree:" not in basis
    assert "wrapper of the respelled 0x002D07F4" in got.evidence


def test_apply_writes_moves_and_deletes_when_the_scan_proves_it(tree):
    ctx, state = context(tree, BEFORE)
    got = plan(ctx)

    def verify(c, sources):
        state["refs"] = AFTER
        return True
    rename.apply_rename(got, ctx=ctx, verify=verify, checks=None)
    assert not (tree / OWNER).exists()
    assert (tree / TU).read_text() == TU_PREPARED
    assert NEW_OP in (tree / "reverse/functions.csv").read_text()


def test_respell_without_move_keeps_the_source(tree):
    ctx, _ = context(tree, BEFORE)
    got = plan(ctx, move_to=None, prepared={OWNER: (OWNER_SRC.replace(OLD_OP, NEW_OP)
                                                    .replace(OLD_WRAP, NEW_WRAP)).encode()})
    assert not got.removed and f"{NEW_OP},,0x002D07F4,115,{OWNER}," in got.after["reverse/functions.csv"].decode()


# ------------------------------------------------------------- what it refuses

def test_refused_when_the_calls_are_still_wrong_after_the_respell(tree):
    """Rule 2: identical bytes are not enough; the bindings must follow."""
    ctx, state = context(tree, BEFORE)
    got = plan(ctx)
    still = [dict(r, cls="wrong") if r["row"] == NEW_OP and r["target"] == COPY else r for r in AFTER]

    def verify(c, sources):
        state["refs"] = still
        return True
    with pytest.raises(VerifyFailed) as error:
        rename.apply_rename(got, ctx=ctx, verify=verify, checks=None)
    assert "0x002D0326" in str(error.value) and "every file restored" in str(error.value)
    assert (tree / OWNER).read_text() == OWNER_SRC          # the deleted source is back
    assert OLD_OP in (tree / "reverse/functions.csv").read_text()


def test_refused_when_a_touched_row_gains_a_wrong_binding(tree):
    ctx, state = context(tree, BEFORE)
    got = plan(ctx)
    worse = AFTER + [ref("??4ThingTemplate@@QAEAAV0@ABV0@@Z", 0x002D1101, 0x00999999, "wrong", "?y", CALLER)]

    def verify(c, sources):
        state["refs"] = worse
        return True
    with pytest.raises(VerifyFailed) as error:
        rename.apply_rename(got, ctx=ctx, verify=verify, checks=None)
    assert "gains a wrong binding" in str(error.value)


def test_refused_for_a_hand_written_row(tree):
    """A plain function name is a naming claim, not something the compiler spells."""
    ctx, _ = context(tree, BEFORE + [ref(PLAIN, 0x00403000, CLEAR, "wrong", source="Code/Lib/Plain.cpp")])
    with pytest.raises(Refusal) as error:
        plan(ctx, rva=0x00403000, new="?helper2@@YAXXZ", also=[], move_to=None,
             prepared={"Code/Lib/Plain.cpp": b"void helper2() {}\n"})
    assert "hand-written name" in str(error.value)


def test_refused_when_a_template_name_becomes_hand_written(tree):
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal) as error:
        plan(ctx, new="?assign@@YAXXZ", also=[])
    assert "hand-written name" in str(error.value)


def test_refused_when_the_new_name_is_already_owned(tree):
    """Rule 3: one name, one identity."""
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal) as error:
        plan(ctx, also=[(WRAP, NEW_OP)])
    assert "once" in str(error.value)
    owned = (tree / "reverse/functions.csv").read_text() + f"{NEW_OP},,0x00500000,4,Code/Lib/Copy.cpp,matched,x\n"
    (tree / "reverse/functions.csv").write_text(owned)
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal) as error:
        plan(ctx)
    assert "already names a row or pin" in str(error.value)


def test_refused_when_the_operator_changes(tree):
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal) as error:
        plan(ctx, new=NEW_OP.replace("??4", "??8", 1), also=[])
    assert "changes the operator or identifier" in str(error.value)


def test_refused_without_a_wrong_binding_to_prove(tree):
    """Rule 1: a respell the identity check does not ask for is a naming claim."""
    clean = [dict(r, cls="owner") for r in BEFORE]
    ctx, _ = context(tree, clean)
    with pytest.raises(Refusal) as error:
        plan(ctx)
    assert "no wrong binding" in str(error.value)


def test_refused_without_any_scanned_reference(tree):
    ctx, _ = context(tree, [r for r in BEFORE if r["row"] != OLD_OP])
    with pytest.raises(Refusal) as error:
        plan(ctx)
    assert "no references" in str(error.value)


def test_refused_with_a_basis(tree):
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal) as error:
        plan(ctx, basis="inferred")
    assert "pass no --basis" in str(error.value)


def test_move_refused_outside_the_approved_tu(tree):
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal) as error:
        plan(ctx, move_to=CALLER)
    assert "not approved" in str(error.value)


def test_move_refused_when_the_owner_keeps_other_rows(tree):
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal) as error:
        plan(ctx, also=[])
    assert "also holds" in str(error.value)


def test_refused_when_an_unprepared_unit_still_spells_the_old_name(tree):
    (tree / "Code/Lib/Copy.cpp").write_text(f"// calls {OLD_OP}\nvoid d() {{}}\n")
    _git(tree, "add", "-A")
    _git(tree, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "mention")
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal) as error:
        plan(ctx)
    assert "still spells" in str(error.value)


def test_identity_needs_respell(tree):
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal) as error:
        plan(ctx, respell=False)
    assert "--respell --identity" in str(error.value)


def test_cli_refuses_identity_with_a_basis():
    with pytest.raises(SystemExit):
        rename.main(["function", "--rva", "0x2D07F4", "--new", NEW_OP, "--respell", "--identity",
                     "--basis", "inferred", "--evidence", "x", "--prepared", f"{TU}=/dev/null"])


def test_the_plan_names_the_removed_source_and_the_evidence(tree):
    ctx, _ = context(tree, BEFORE)
    text = plan(ctx).report()
    assert f"sources removed (1): {OWNER}" in text and "evidence: code-identity:" in text
