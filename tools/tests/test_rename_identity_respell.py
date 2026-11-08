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
NEW_OP = "??4?$_Rb_tree@UBfmeStringRecord002CF550@@U?$pair@HH@@@@QAEAAV0@ABV0@@Z"
OLD_WRAP = "??4?$map@URva002D07F4Element@@H@@QAEAAV0@ABV0@@Z"
NEW_WRAP = "??4?$map@UBfmeStringRecord002CF550@@H@@QAEAAV0@ABV0@@Z"
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


STLPORT_HEADER = """_STLP_BEGIN_NAMESPACE
template <class _T1, class _T2> struct pair {};
template <class _Tp> struct less {};
template <class _Tp> class allocator {};
template <class _Pair> struct _Select1st {};
template <class _Tp> struct _Identity {};
template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc> class _Rb_tree {};
template <class _Key, class _Tp, class _Compare, class _Alloc> class map { typedef _Rb_tree<_Key> _Rep_type; };
template <class _Key, class _Compare, class _Alloc> class set {};
_STLP_END_NAMESPACE
"""
STLPORT = frozenset({"pair", "less", "allocator", "_Select1st", "_Identity", "_Rb_tree", "map", "set", "_Rep_type"})


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


def agree(root, rid, old, new, rva, agents=("seat-a", "seat-b"), source=OWNER):
    """An agreement record and the two blind votes behind it (name_agreement recomputes from
    votes), on the row's own key: source|function|0xRVA|placeholder."""
    key = f"{source}|function|0x{rva:08X}|{old}"
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
        "vendor/stlport-4.6/stlport/stl/_tree.h": STLPORT_HEADER,
    }
    for rel, text in files.items():
        write(tmp_path / rel, text)
    pinned = rename.stlport_files(rename.Context(tmp_path, object_scan=False))
    write(tmp_path / rename.STLPORT_MANIFEST, f"sha256 {rename.stlport_manifest(pinned)}\nfiles {len(pinned)}\n")
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
    member = OLD_OP.replace("Rva002D07F4Element", "BfmeContainedMember00500000")
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
    more than a placeholder change, and no approval covers it either."""
    invented = NEW_OP.replace("ABV0@", "ABVInventedRealType@@")
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="changes more than an identity respell may"):
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
    """link_objects over real objects, every one current; a test edits `state`."""
    state = {"objects": {src: [obj(tree, Path(src).stem + ".obj")] for src in
                         ("Code/Lib/Cleanup.cpp", "Code/Lib/Copy.cpp", "Code/Lib/Plain.cpp", *SKIPPED)},
             "stale": set(), "rebuilt": [], "rebuild_ok": True}
    monkeypatch.setattr(rename, "link_objects", lambda ctx: dict(state["objects"]))
    monkeypatch.setattr(rename, "source_objects",
                        lambda ctx, sources: {src: state["objects"].get(src, []) for src in sources})
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
    with pytest.raises(Refusal, match="Broken.obj is unreadable: shorter than a COFF header"):
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



# ------------------------------------------------- round 3 of the review (r3_probes.py)

def test_an_approval_on_another_units_key_does_not_cover_the_row(tree):
    """Finding 2 ('wrong source key'): genuine votes on the same placeholder under
    Code/Unrelated.cpp's key do not authorise this row."""
    for rel in (rename.AGREED, name_agreement.VOTES):
        text = (tree / rel).read_text(encoding="utf-8").replace(OWNER, "Code/Unrelated.cpp")
        write(tree / rel, text)
    votes = (tree / name_agreement.VOTES).read_text(encoding="utf-8").splitlines()
    rebuilt = [votes[0]]
    for line in votes[1:]:
        cells = line.split(",")
        cells[1] = name_agreement.digest(cells[0], NEW_OP if cells[0].endswith(OLD_OP) else NEW_WRAP)
        rebuilt.append(",".join(cells))
    write(tree / name_agreement.VOTES, "\n".join(rebuilt) + "\n")
    commit(tree)
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="is not this row's key"):
        plan(ctx)


def test_an_approval_index_without_votes_is_refused(tree):
    """'approval index without supporting votes': the record alone authorises nothing."""
    write(tree / name_agreement.VOTES, ",".join(name_agreement.VOTE_COLUMNS) + "\n")
    commit(tree)
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="no naming approval covers"):
        plan(ctx)


REAL_OLD = "??4ExistingRealType@@QAEAAV0@ABURva002D07F4Element@@@Z"
REAL_NEW = REAL_OLD.replace("ExistingRealType", "InventedRealType")


def real_class_tree(tree):
    for rel in ("reverse/functions.csv", OWNER):
        write(tree / rel, (tree / rel).read_text().replace(OLD_OP, REAL_OLD))
    token = agree(tree, "nl-real", REAL_OLD, REAL_NEW, OP)
    commit(tree)
    ctx, _ = context(tree, [dict(r, row=REAL_OLD) if r["row"] == OLD_OP else r for r in BEFORE])
    return ctx, token


def test_a_placeholder_parameter_does_not_unlock_a_real_class(tree):
    """Finding 3 ('real class changed using placeholder parameter'), voted or not."""
    ctx, token = real_class_tree(tree)
    with pytest.raises(Refusal, match="changes more than an identity respell may"):
        plan(ctx, new=REAL_NEW, evidence=token, also=[], move_to=None,
             prepared={OWNER: OWNER_SRC.replace(OLD_OP, REAL_NEW).encode()})


def test_a_canonical_real_class_is_never_replaced(tree):
    """Finding 3 ('canonical real class changed'): the record of a canonical name changes nothing."""
    recommit(tree, "reverse/name_basis.csv", "kind,old,new,basis,evidence,source,rva\n"
             "class,Original,ExistingRealType,canonical:zh,proof,Code/X.cpp,0x00000001\n")
    recommit(tree, "reverse/canonical_classes.csv", "class,header,notes\nExistingRealType,Code/X.h,x\n")
    ctx, token = real_class_tree(tree)
    with pytest.raises(Refusal, match="changes more than an identity respell may"):
        plan(ctx, new=REAL_NEW, evidence=token, also=[], move_to=None,
             prepared={OWNER: OWNER_SRC.replace(OLD_OP, REAL_NEW).encode()})


def test_a_placeholder_shaped_canonical_class_is_never_replaced(tree):
    """A registered canonical class keeps its spelling even when its name looks like a placeholder."""
    recommit(tree, "reverse/canonical_classes.csv", "class,header,notes\nRva002D07F4Element,Code/X.h,x\n")
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="replaces the canonical class Rva002D07F4Element"):
        plan(ctx)


P29_OLD_OP = ("??4?$_Rb_tree@URva002D07F4Element@@U?$pair@$$CBURva002D07F4Element@@H@_STL@@"
              "U?$_Select1st@U?$pair@$$CBURva002D07F4Element@@H@_STL@@@3@U?$less@URva002D07F4Element@@@3@"
              "V?$allocator@U?$pair@$$CBURva002D07F4Element@@H@_STL@@@3@@_STL@@QAEAAV01@ABV01@@Z")
P29_NEW_OP = ("??4?$_Rb_tree@UBfmeStringRecord002CF550@@U1@U?$_Identity@UBfmeStringRecord002CF550@@@_STL@@"
              "U?$less@UBfmeStringRecord002CF550@@@3@V?$allocator@UBfmeStringRecord002CF550@@@3@@_STL@@"
              "QAEAAV01@ABV01@@Z")
P29_OLD_WRAP = ("??4?$map@URva002D07F4Element@@HU?$less@URva002D07F4Element@@@_STL@@"
                "V?$allocator@U?$pair@$$CBURva002D07F4Element@@H@_STL@@@3@@_STL@@QAEAAV01@ABV01@@Z")
P29_NEW_WRAP = ("??4?$set@UBfmeStringRecord002CF550@@U?$less@UBfmeStringRecord002CF550@@@_STL@@"
                "V?$allocator@UBfmeStringRecord002CF550@@@3@@_STL@@QAEAAV01@ABV01@@Z")
# an _STL::map<Rva..., ProjectA>: a project class inside an STLport template argument (in map's
# argument table 0 map, 1 Rva..., 2 ProjectA, 3 less<...>, 4 _STL)
STL_MAP = ("??4?$map@URva002D07F4Element@@VProjectA@@U?$less@URva002D07F4Element@@@_STL@@"
           "V?$allocator@U?$pair@$$CBURva002D07F4Element@@VProjectA@@@_STL@@@4@@_STL@@QAEAAV01@ABV01@@Z")


def test_stlport_names_and_placeholders_may_change():
    """P29's shapes: map -> set and pair/_Select1st -> _Identity are STLport's subtrees
    (an `_STL` scope, declared in the vendored headers) with only placeholders inside."""
    assert rename.identity_shape_problem(P29_OLD_OP, P29_NEW_OP, set(), STLPORT) is None
    assert rename.identity_shape_problem(P29_OLD_WRAP, P29_NEW_WRAP, set(), STLPORT) is None


def test_a_global_template_is_a_project_name():
    """Without the `_STL` scope, map is the project's name and stays: OLD_WRAP is a global map."""
    assert "replaces the real name map" in rename.identity_shape_problem(
        OLD_WRAP, OLD_WRAP.replace("?$map@", "?$set@"), set(), STLPORT)


def test_a_project_class_inside_an_stl_argument_cannot_be_swapped():
    swapped = STL_MAP.replace("VProjectA@@", "VProjectB@@")
    assert "replaces the real name ProjectA with ProjectB" in rename.identity_shape_problem(
        STL_MAP, swapped, set(), STLPORT)
    # the placeholder beside it may still be named
    named = STL_MAP.replace("Rva002D07F4Element", "BfmeStringRecord002CF550")
    assert rename.identity_shape_problem(STL_MAP, named, set(), STLPORT) is None


def test_a_canonical_class_inside_an_stl_argument_cannot_be_replaced():
    renamed = STL_MAP.replace("VProjectA@@", "VProjectRenamed@@")
    assert "replaces the canonical class ProjectA" in rename.identity_shape_problem(
        STL_MAP, renamed, {"ProjectA"}, STLPORT)
    # a placeholder-shaped canonical class is a real name too
    assert "replaces the canonical class Rva002D07F4Element" in rename.identity_shape_problem(
        P29_OLD_OP, P29_NEW_OP, {"Rva002D07F4Element"}, STLPORT)


def test_a_moved_back_reference_or_an_added_name_is_a_change():
    assert rename.identity_shape_problem(NEW_OP, NEW_OP.replace("ABV0@", "ABVInventedRealType@@"),
                                         set(), STLPORT) is not None
    assert "changes its argument count" in rename.identity_shape_problem(
        STL_MAP, STL_MAP.replace("VProjectA@@U?$less", "VProjectA@@VProjectC@@U?$less")
        .replace("@@@4@@_STL", "@@@5@@_STL"), set(), STLPORT)


def test_p29s_shapes_pass_the_token_stage_and_still_need_votes(tree):
    for rel in ("reverse/functions.csv", OWNER):
        write(tree / rel, (tree / rel).read_text().replace(OLD_OP, P29_OLD_OP).replace(OLD_WRAP, P29_OLD_WRAP))
    commit(tree)
    rows = {OLD_OP: P29_OLD_OP, OLD_WRAP: P29_OLD_WRAP}
    before = [dict(r, row=rows.get(r["row"], r["row"]),
                   symbol=rows.get(r["symbol"], r["symbol"])) for r in BEFORE]
    prepared = {TU: TU_PREPARED.replace(NEW_OP, P29_NEW_OP).replace(NEW_WRAP, P29_NEW_WRAP).encode(),
                CALLER: CALLER_PREPARED.encode()}
    ctx, _ = context(tree, before)
    with pytest.raises(Refusal, match="no naming approval covers"):
        plan(ctx, new=P29_NEW_OP, also=[(WRAP, P29_NEW_WRAP)], prepared=prepared)
    votes = " ".join([agree(tree, "nl-p29-op", P29_OLD_OP, P29_NEW_OP, OP),
                      agree(tree, "nl-p29-wrap", P29_OLD_WRAP, P29_NEW_WRAP, WRAP)])
    commit(tree)
    ctx, _ = context(tree, before)
    got = plan(ctx, new=P29_NEW_OP, also=[(WRAP, P29_NEW_WRAP)], prepared=prepared, evidence=votes)
    assert (P29_OLD_OP, P29_NEW_OP, OP) in got.renamed_rows and (P29_OLD_WRAP, P29_NEW_WRAP, WRAP) in got.renamed_rows


def test_a_data_only_provider_is_a_consumer(tree, objects):
    """Finding 1 ('data-only consumer'): the link takes data_rows.csv providers too."""
    recommit(tree, "Code/DataOnly.cpp", "void *table[] = {0};\n")
    objects["objects"]["Code/DataOnly.cpp"] = [obj(tree, "data.obj", references=(OLD_CLEAR,))]
    ctx, _ = context(tree, BEFORE)
    with pytest.raises(Refusal, match="Code/DataOnly.cpp's object data.obj references"):
        plan(ctx)


def test_the_link_inventory_is_exit_links(monkeypatch, tmp_path):
    """link_objects reads tools/exit_link.py's expected_objects (function and data
    providers), less its placement-only objects."""
    import exit_link
    import link_census
    code, data, placed, member = (tmp_path / n for n in ("code.obj", "data.obj", "placed.obj", "crt_x.obj"))
    root = rename.ROOT
    monkeypatch.setattr(link_census, "ledger", lambda: [{"source": "Code/Code.cpp"}])
    monkeypatch.setattr(exit_link, "expected_objects", lambda rows: [code, data, placed, member])
    monkeypatch.setattr(exit_link, "placement_objects", lambda rows: {placed: "Code/Placed.cpp"})
    monkeypatch.setattr(link_census, "_object_sources", lambda rows: {
        code: root / "Code/Code.cpp", data: root / "Code/DataOnly.cpp", placed: root / "Code/Placed.cpp"})
    got = rename.link_objects(rename.Context(root, object_scan=False))
    assert got == {"Code/Code.cpp": [code], "Code/DataOnly.cpp": [data], "(crt_x.obj)": [member]}
    with pytest.raises(Refusal, match="from the repository itself"):
        rename.link_objects(rename.Context(tmp_path, object_scan=False))


def test_a_malformed_object_without_the_pin_bytes_is_not_clean(tmp_path):
    """Finding 4: every object is parsed whole; a damaged one refuses even when the
    pin's name is not among its bytes."""
    broken = tmp_path / "not-coff.obj"
    broken.write_bytes(b"not a COFF object" * 5)
    problems = rename.object_pin_references({"Code/Broken.cpp": [broken]}, ["?retired@@YAXXZ"])
    assert problems and "is unreadable" in problems[0]


def test_a_truncated_object_is_not_clean(tmp_path):
    whole = obj(tmp_path, "whole.obj")
    truncated = tmp_path / "truncated.obj"
    truncated.write_bytes(whole.read_bytes()[:-6])
    assert rename.object_pin_references({"Code/A.cpp": [whole]}, ["?retired@@YAXXZ"]) == []
    problems = rename.object_pin_references({"Code/A.cpp": [truncated]}, ["?retired@@YAXXZ"])
    assert problems and "runs past the end" in problems[0]



# ------------------------------------------------- round 4 of the review (r4_plan_probes.py)

SHAPE_OLD = "??4?$map@URva00123456@@VProjectB@ProjectA@@@_STL@@QAEAAV01@ABV01@@Z"     # map<Rva, ProjectA::ProjectB>
SHAPE_NEW = "??4?$map@URva00123456@@V?$ProjectB@VProjectA@@@@@_STL@@QAEAAV01@ABV01@@Z"  # map<Rva, ProjectB<ProjectA>>


def test_a_protected_name_keeps_its_qualified_path():
    """Finding 1: both spellings flatten to Rva, ProjectB, ProjectA; the trees differ."""
    assert "changes its scope" in rename.identity_shape_problem(SHAPE_OLD, SHAPE_NEW, set(), STLPORT)


def test_a_protected_name_keeps_its_argument_index_and_depth():
    flat = "??4?$map@URva00123456@@VProjectA@@VProjectB@@@_STL@@QAEXXZ"          # map<Rva, A, B>
    swapped = "??4?$map@URva00123456@@VProjectB@@VProjectA@@@_STL@@QAEXXZ"       # map<Rva, B, A>
    nested = "??4?$map@URva00123456@@V?$pair@VProjectA@@VProjectB@@@_STL@@@_STL@@QAEXXZ"   # map<Rva, pair<A, B>>
    assert "replaces the real name ProjectA with ProjectB" in rename.identity_shape_problem(flat, swapped, set(), STLPORT)
    assert rename.identity_shape_problem(flat, nested, set(), STLPORT) is not None


def test_the_shape_probe_is_refused_by_the_planner(tree):
    for rel in ("reverse/functions.csv", OWNER):
        write(tree / rel, (tree / rel).read_text().replace(OLD_OP, SHAPE_OLD))
    token = agree(tree, "r4-shape", SHAPE_OLD, SHAPE_NEW, OP)
    commit(tree)
    ctx, _ = context(tree, [dict(r, row=SHAPE_OLD) if r["row"] == OLD_OP else r for r in BEFORE])
    with pytest.raises(Refusal, match="changes its scope"):
        plan(ctx, new=SHAPE_NEW, evidence=token, also=[], move_to=None,
             prepared={OWNER: OWNER_SRC.replace(OLD_OP, SHAPE_NEW).encode()})


def test_a_canonical_class_under_the_stl_scope_is_never_replaced():
    """Finding 2: canonical protection comes before any _STL filtering."""
    old = "??4?$map@URva00123456@@VRegistered@_STL@@@_STL@@QAEXXZ"
    new = "??4?$map@URva00123456@@VOther@_STL@@@_STL@@QAEXXZ"
    assert "replaces the canonical class Registered" in rename.identity_shape_problem(
        old, new, {"Registered"}, STLPORT | {"Registered", "Other"})


def test_an_stl_scoped_name_must_be_declared_by_the_vendored_headers():
    """Finding 2: `_STL` is reopened in this codebase; the vendored STLport tree decides."""
    old = "??4?$map@URva00123456@@VMine@_STL@@@_STL@@QAEXXZ"
    new = "??4?$map@URva00123456@@VYours@_STL@@@_STL@@QAEXXZ"
    assert "do not declare" in rename.identity_shape_problem(old, new, set(), STLPORT)
    assert rename.identity_shape_problem(old, new, set(), STLPORT | {"Mine", "Yours"}) is None
    assert "do not declare: " not in (rename.identity_shape_problem(P29_OLD_WRAP, P29_NEW_WRAP, set(), STLPORT) or "")
    assert "map" in rename.identity_shape_problem(P29_OLD_WRAP, P29_NEW_WRAP, set(), STLPORT - {"map"})


def test_the_vendored_stlport_names_are_read_from_the_tree(tree):
    declared = rename.stlport_declared(rename.Context(tree, object_scan=False))
    assert STLPORT <= declared


def coff_with(symbols=(("dummy", 0, 1, 0x20, 2, 0),), relocs=()):
    import struct  # noqa: F401
    return bytearray(coff([(".text", TEXT, b"\xc3", list(relocs))], list(symbols)))


def test_an_aux_count_past_the_symbol_table_is_unreadable(tmp_path):
    """Finding 3 (AUX OVERRUN)."""
    import struct
    data = coff_with()
    table = struct.unpack_from("<I", data, 8)[0]
    data[table + 17] = 255
    assert "auxiliary record(s) run past the symbol table" in rename.coff_layout_problem(bytes(data))
    path = tmp_path / "aux.obj"
    path.write_bytes(data)
    assert rename.object_pin_references({"Code/X.cpp": [path]}, ["?retired@@YAXXZ"])


def test_a_long_name_outside_the_string_table_is_unreadable(tmp_path):
    """Finding 3 (STRING OVERRUN): the offset points into bytes appended past the declared table."""
    import struct
    data = coff_with((("dummy", 0, 0, 0, 2, 0),))
    table = struct.unpack_from("<I", data, 8)[0]
    struct.pack_into("<II", data, table, 0, 4)
    data += b"?other@@YAXXZ\0"
    assert "name offset 4 is outside the string table" in rename.coff_layout_problem(bytes(data))


def test_a_relocation_past_the_symbol_table_is_unreadable():
    data = coff_with(relocs=[(0, 7, 0x14)])
    assert "past the symbol table" in rename.coff_layout_problem(bytes(data))


def test_a_symbol_in_no_section_is_unreadable():
    data = coff_with((("dummy", 0, 5, 0x20, 2, 0),))
    assert "names no section" in rename.coff_layout_problem(bytes(data))
    assert rename.coff_layout_problem(bytes(coff_with((("abs", 0, -1, 0, 2, 0),)))) is None



# ------------------------------------------------- round 5 of the review (review-identity-respell-r5)

def test_a_member_pointer_keeps_its_pointer_code():
    """Finding 1 (r5_mp.py): Owner::* and Owner::* const differ."""
    old = "?f@@YAXURva00123456@@P8Owner@@AEXVProject@@@Z@Z"
    assert "MP: 'P8' -> 'Q8'" in rename.identity_shape_problem(old, old.replace("P8", "Q8"), set(), STLPORT)
    template = "??$f@P8Owner@@AEXVProject@@@Z@@YAXXZ"
    assert rename.identity_shape_problem(template, template.replace("P8", "Q8"), set(), STLPORT) is not None


def test_the_member_pointer_probe_is_refused_by_the_planner(tree):
    """r5_mp_plan.py: a placeholder template whose argument is a member pointer."""
    old = "?f@?$Rva00123456@P8Owner@@AEXVProject@@@Z@@SAXXZ"
    new = old.replace("P8", "Q8")
    for rel in ("reverse/functions.csv", OWNER):
        write(tree / rel, (tree / rel).read_text().replace(OLD_OP, old))
    token = agree(tree, "r5-mp", old, new, OP)
    commit(tree)
    ctx, _ = context(tree, [dict(r, row=old) if r["row"] == OLD_OP else r for r in BEFORE])
    with pytest.raises(Refusal, match="changes more than an identity respell may"):
        plan(ctx, new=new, evidence=token, also=[], move_to=None,
             prepared={OWNER: OWNER_SRC.replace(OLD_OP, new).encode()})


def test_a_variadic_signature_is_read_and_differs():
    fixed = "?f@@YAXURva00123456@@P6AXVProject@@@Z@Z"
    variadic = fixed.replace("Project@@@Z", "Project@@ZZ")
    rename.type_tree(variadic)                      # read, not refused as unreadable
    assert "cannot be read" not in rename.identity_shape_problem(fixed, variadic, set(), STLPORT)


SCOPED = "??4Project@Rva00123456@@QAEAAV01@ABV01@@Z"            # Rva00123456::Project


def test_a_protected_name_keeps_its_placeholder_scopes():
    """Finding 2 (r5_scope_plan.py): Rva00123456::Project -> NamedScope::Project moves Project."""
    moved = SCOPED.replace("Rva00123456", "NamedScope")
    assert "enclosing scope Rva00123456 of the protected name Project" in rename.identity_shape_problem(
        SCOPED, moved, set(), STLPORT)
    assert "enclosing scope Rva00123456 of the protected name Project" in rename.identity_shape_problem(
        SCOPED, moved, {"Project"}, STLPORT)


def test_a_placeholder_inside_a_protected_scope_may_be_named():
    """Project::Rva00123456 -> Project::Named: the placeholder is not on Project's path."""
    inner = "??4Rva00123456@Project@@QAEAAV01@ABV01@@Z"
    assert rename.identity_shape_problem(inner, inner.replace("Rva00123456", "NamedThing"), set(), STLPORT) is None


def test_the_scope_probe_is_refused_by_the_planner(tree):
    moved = SCOPED.replace("Rva00123456", "NamedScope")
    for rel in ("reverse/functions.csv", OWNER):
        write(tree / rel, (tree / rel).read_text().replace(OLD_OP, SCOPED))
    write(tree / "reverse/canonical_classes.csv", "class,header,notes\nProject,Code/Project.h,canonical\n")
    token = agree(tree, "r5-scope", SCOPED, moved, OP)
    commit(tree)
    ctx, _ = context(tree, [dict(r, row=SCOPED) if r["row"] == OLD_OP else r for r in BEFORE])
    with pytest.raises(Refusal, match="of the protected name Project"):
        plan(ctx, new=moved, evidence=token, also=[], move_to=None,
             prepared={OWNER: OWNER_SRC.replace(OLD_OP, moved).encode()})


def test_stlport_names_come_from_declarations_only():
    """Finding 3: comments, string literals and template parameters declare nothing."""
    text = """// class FakeComment;
/* typedef int FakeAlias; */
const char *s = "struct FakeString {";
template <class _Tp, class _Alloc = allocator<_Tp> > class vector : protected _Vector_base<_Tp> {};
struct _Identity : public unary_function<int, int> {};
template <class _T1, class _T2> struct pair;
typedef unsigned int size_type;
template <> struct less<int> {};
"""
    assert rename.stlport_names(text) == {"vector", "_Identity", "pair", "size_type", "less"}


def test_the_stlport_index_is_pinned_by_its_manifest(tree):
    """Round 6, findings 2-3: no git ref or replace object decides; the headers on disk
    must hash to the pin, committed or not."""
    header = tree / "vendor/stlport-4.6/stlport/stl/_tree.h"
    write(header, header.read_text() + "class Injected {};\n")
    with pytest.raises(Refusal, match="not the pinned"):
        rename.stlport_declared(rename.Context(tree, object_scan=False))
    commit(tree, "vendored change on the branch")
    with pytest.raises(Refusal, match="not the pinned"):
        rename.stlport_declared(rename.Context(tree, object_scan=False))


def test_the_real_vendored_headers_match_the_pin():
    """The committed pin is the repository's vendored tree, and its index holds P29's names."""
    declared = rename.stlport_declared(rename.Context(rename.ROOT, object_scan=False))
    assert STLPORT - {"_Rep_type"} <= declared
    assert {"raw_storage_iterator", "__oom_handler_type", "facet"} <= declared
    assert not {"test_class", "Class"} & declared


def test_only_the_public_headers_are_read(tree):
    """Round 6, finding 4: config/ and configure probes are never read (nor hashed)."""
    write(tree / "vendor/stlport-4.6/stlport/config/new_compiler/configure.in", "class test_class {};\n")
    write(tree / "vendor/stlport-4.6/stlport/BC50/x.h", "class Elsewhere {};\n")
    write(tree / "vendor/stlport-4.6/stlport/stl/debug/_x.h", "class DebugOne {};\n")
    files = [rel for rel, _data in rename.stlport_files(rename.Context(tree, object_scan=False))]
    assert "stl/_tree.h" in files and "stl/debug/_x.h" in files
    assert not [rel for rel in files if rel.startswith(("config/", "BC50/"))]


def test_declarations_split_by_directives_and_function_pointer_typedefs():
    """Round 6, finding 5 (r6_decl_extra.py)."""
    assert rename.stlport_names("template <class T> class Foo\n#ifdef FLAG\n: public Bar\n#endif\n{};") == {"Foo"}
    assert rename.stlport_names("#define DECLARE(classname) class classname;") == set()
    assert rename.stlport_names("typedef struct tag* Handle;") == {"Handle"}
    assert rename.stlport_names("typedef int (*callback)(int);") == {"callback"}
    assert rename.stlport_names("typedef void (_STLP_CALL * __oom_handler_type)();") == {"__oom_handler_type"}
    assert rename.stlport_names("#  define _STLP_X \\\n  class Hidden {};\nclass Shown {};") == {"Shown"}


def test_a_configure_probe_name_is_not_stlport():
    """r6_index_shape.py: _STL::map -> _STL::test_class is not an STLport change."""
    old = "?f@@YAXURva00123456@@Vmap@_STL@@@Z"
    assert "do not declare" in rename.identity_shape_problem(old, old.replace("map@", "test_class@"),
                                                             set(), STLPORT)


SCOPE_TEMPLATE = "??4Project@?$Rva00123456@URva00654321@@@@QAEAAV01@ABV01@@Z"     # Rva00123456<Rva00654321>::Project


def test_an_enclosing_scopes_template_arguments_are_part_of_the_path():
    """Round 6, finding 1: Rva00123456<Rva00654321>::Project -> Rva00123456<NamedThing>::Project."""
    moved = SCOPE_TEMPLATE.replace("Rva00654321", "NamedThing")
    for canonical in (set(), {"Project"}):
        assert "enclosing scope Rva00123456 of the protected name Project" in rename.identity_shape_problem(
            SCOPE_TEMPLATE, moved, canonical, STLPORT)


def test_the_scope_template_probe_is_refused_by_the_planner(tree):
    moved = SCOPE_TEMPLATE.replace("Rva00654321", "NamedThing")
    for rel in ("reverse/functions.csv", OWNER):
        write(tree / rel, (tree / rel).read_text().replace(OLD_OP, SCOPE_TEMPLATE))
    write(tree / "reverse/canonical_classes.csv", "class,header,notes\nProject,Code/Project.h,canonical\n")
    token = agree(tree, "r6-scope", SCOPE_TEMPLATE, moved, OP)
    commit(tree)
    ctx, _ = context(tree, [dict(r, row=SCOPE_TEMPLATE) if r["row"] == OLD_OP else r for r in BEFORE])
    with pytest.raises(Refusal, match="enclosing scope Rva00123456 of the protected name Project"):
        plan(ctx, new=moved, evidence=token, also=[], move_to=None,
             prepared={OWNER: OWNER_SRC.replace(OLD_OP, moved).encode()})


def test_overlapping_sections_are_unreadable():
    """Finding 4: two sections' raw data overlap."""
    import struct
    data = bytearray(coff([(".text", TEXT, b"\xc3", []), (".other", TEXT, b"\xc3", [])],
                          [("dummy", 0, 1, 0x20, 2, 0)]))
    struct.pack_into("<I", data, 20 + 40 + 20, struct.unpack_from("<I", data, 20 + 20)[0])
    assert "overlap in the file" in rename.coff_layout_problem(bytes(data))


def test_a_symbol_value_past_its_section_is_unreadable():
    data = coff_with((("dummy", 9999, 1, 0x20, 2, 0),))
    assert "is past section 1" in rename.coff_layout_problem(bytes(data))


def test_a_relocation_overflow_with_no_count_is_unreadable():
    data = bytearray(coff([(".text", TEXT | 0x01000000, b"\xc3", [])], [("dummy", 0, 1, 0x20, 2, 0)]))
    assert "relocation overflow" in rename.coff_layout_problem(bytes(data))


def test_every_relocation_of_an_overflowed_section_is_walked():
    """r5_overflow.py: 65,537 relocations, the last against symbol 7 of 1."""
    import struct
    data = bytearray(coff([(".text", TEXT | 0x01000000, b"\xc3", [(65537, 0, 0)] + [(0, 0, 6)] * 65534)],
                          [("dummy", 0, 1, 0x20, 2, 0)]))
    symbols = struct.unpack_from("<I", data, 8)[0]
    data[symbols:symbols] = struct.pack("<IIHIIH", 0, 0, 6, 0, 7, 6)
    struct.pack_into("<I", data, 8, symbols + 20)
    assert "relocates against symbol 7" in rename.coff_layout_problem(bytes(data))
    data = bytearray(coff([(".text", TEXT | 0x01000000, b"\xc3", [(1, 0, 0)])], [("dummy", 0, 1, 0x20, 2, 0)]))
    struct.pack_into("<H", data, 20 + 32, 0xFFFF)
    assert "overflow relocation count is 1" in rename.coff_layout_problem(bytes(data))



# ------------------------------------------------- round 7 of the review (review-identity-respell-r7)

def test_the_manifest_is_a_protected_path():
    """Finding 1: the pin lives in a data file the Verifier-Change hook protects (the
    trailerless-commit refusal itself runs in test_protected_new_lanes.py)."""
    import protected_paths
    assert rename.STLPORT_MANIFEST == "reverse/stlport_manifest.txt"
    assert protected_paths.protected([rename.STLPORT_MANIFEST])


def test_the_committed_manifest_pins_the_real_headers():
    sha, count = rename.stlport_pin(rename.Context(rename.ROOT, object_scan=False))
    files = rename.stlport_files(rename.Context(rename.ROOT, object_scan=False))
    assert (sha, count) == (rename.stlport_manifest(files), len(files)) == (sha, 236)


def test_a_missing_or_malformed_manifest_refuses(tree):
    for text in (None, "sha256 abc\nfiles 1\n", "sha256 " + "0" * 64 + "\n"):
        path = tree / rename.STLPORT_MANIFEST
        if text is None:
            path.unlink()
        else:
            write(path, text)
        with pytest.raises(Refusal, match="no pin"):
            rename.stlport_declared(rename.Context(tree, object_scan=False))


def test_a_wrong_file_count_refuses(tree):
    sha, count = rename.stlport_pin(rename.Context(tree, object_scan=False))
    write(tree / rename.STLPORT_MANIFEST, f"sha256 {sha}\nfiles {count + 1}\n")
    with pytest.raises(Refusal, match="not the pinned"):
        rename.stlport_declared(rename.Context(tree, object_scan=False))


def test_member_pointer_typedefs_and_keywords():
    """Finding 2: `typedef int (Owner::*Callback)() const;` declares Callback, never `const`."""
    assert rename.stlport_names("typedef int (Owner::*Callback)() const;") == {"Callback"}
    assert rename.stlport_names("typedef void (_Tp::*_Fn)(int) const;") == {"_Fn"}
    assert rename.stlport_names("typedef unsigned const;") == set()      # the keyword guard
    # a macro's parentheses inside a plain typedef do not hide its name
    assert rename.stlport_names("typedef rope<char, _STLP_DEFAULT_ALLOCATOR(char) > crope;") == {"crope"}


def test_continued_comments_and_macros_declare_nothing():
    """Finding 2: a continuation joins first, so a `//` comment or a directive swallows the next line."""
    assert rename.stlport_names("// comment \\\nclass FakeComment {};") == set()
    assert rename.stlport_names("#define X // comment \\\nclass FakeMacro {};") == set()
    assert rename.stlport_names("#define M \\\r\nclass Leak {};\r\nclass Kept {};\r\n") == {"Kept"}


def test_the_real_index_has_no_keyword():
    declared = rename.stlport_declared(rename.Context(rename.ROOT, object_scan=False))
    assert not declared & rename.C_KEYWORDS
    assert "const" not in declared
    assert {"crope", "wrope", "bit_vector"} <= declared
