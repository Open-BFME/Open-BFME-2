"""Regressions for the review of tools/rename.py (fix-1): one test or more per
finding, on a miniature git tree with small ledgers and sources (verification
injected), plus dry-runs of the reviewer's real-tree cases."""
import hashlib
import json
import multiprocessing
import os
import signal
import subprocess
import sys
import time
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import name_agreement  # noqa: E402
import name_metric  # noqa: E402
import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

OLD = "?Rva00401000@Widget@@QAEHH@Z"
NEW = "?countParts@Widget@@QAEHH@Z"
UNIT = "Code/Game/WidgetRva00401000.cpp"

FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
{OLD},,0x00401000,40,{UNIT},matched,address-derived
?count@Widget@@QAEHXZ,,0x00403000,6,{UNIT},matched,real name
?f@Foo@@QAEHH@Z,,0x00410000,6,Code/Game/Foo.cpp,matched,
?f@Foo@@QAEHM@Z,,0x00420000,6,Code/Game/Foo.cpp,matched,
?f@Rva00500000@@QAEXXZ,,0x00500000,6,Code/Game/Bar.cpp,matched,
?g@@YAXPAVTRva00500000@@@Z,,0x00510000,6,Code/Game/Bar.cpp,matched,
?URva00500000@Zed@@QAEXXZ,,0x00520000,6,Code/Game/Bar.cpp,matched,
?pushobject@@YAXPAUlua_State@@@Z,,0x00600000,6,Code/Libraries/Source/Lua/lapi.c,matched,vendored=lua-5.0
?initFilters3D@Audio@@QAEXXZ,,0x00700000,6,Code/Game/Audio.cpp,matched,zh twin
"""
SYMBOLS = f"""name,address,notes
{OLD},0x00401000,pin
?h@@YAXPAUTRva00500000@@@Z,0x00530000,pin
"""
WIDGET = """// cl: /O2
class Widget {
public:
    int Rva00401000(int n);
    int count();
};
int Widget::Rva00401000(int param_1) { return param_1 + 1; }
int Widget::count() { return 0; }
"""
FOO = """// cl: /O2
struct Foo { int f(int a); int f(float a); };
int Foo::f(int param_1) { return param_1; }
int Foo::f(float param_1) { return (int)param_1; }
"""
BAR = """// cl: /O2
struct Rva00500000 { void f(); };
struct TRva00500000 { int x; };
struct Zed { void URva00500000(); };
void Rva00500000::f() {}
void g(TRva00500000 *) {}
void Zed::URva00500000() {}
"""
LAPI = "// cl: /O2\nstruct lua_State;\nvoid pushobject(struct lua_State *o) { (void)o; }\n"
AUDIO = "// cl: /O2\nstruct Audio { void initFilters3D(); };\nvoid Audio::initFilters3D() {}\n"


def _git(root, *args):
    return subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True, text=True).stdout


def make_tree(root, extra=None):
    files = {
        "reverse/functions.csv": FUNCTIONS,
        "reverse/symbols.csv": SYMBOLS,
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/body_owners.csv": f"target_rva,name,target_size,source,evidence\n0x00401000,{OLD},40,{UNIT},audited\n",
        "reverse/name_agreed.csv": rename.AGREED_HEADER + "\n",
        UNIT: WIDGET,
        "Code/Game/Foo.cpp": FOO,
        "Code/Game/Bar.cpp": BAR,
        "Code/Game/Audio.cpp": AUDIO,
        "Code/Libraries/Source/Lua/lapi.c": LAPI,
    }
    files.update(extra or {})
    for rel, text in files.items():
        path = root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(root, "init", "-q")
    _git(root, "add", "-A")
    return root


@pytest.fixture
def tree(tmp_path):
    return make_tree(tmp_path)


def ctx_of(root):
    return rename.Context(root, object_scan=False)


def agree(root, rid, kind, old, new, rva="", agents="claude-a;gpt-b"):
    """An agreement record and the votes behind it: one vote per agent, each
    agent its own worker (tools/name_agreement.py recomputes from votes)."""
    key = f"{UNIT}|{kind}|scope|{old}"
    with (root / rename.AGREED).open("a") as handle:
        handle.write(rename.csv_line([rid, kind, old, new, rva, agents, key, "agreed", ""]).decode())
    votes = root / name_agreement.VOTES
    lines = [] if votes.exists() else [",".join(name_agreement.VOTE_COLUMNS) + "\n"]
    for agent in agents.split(";"):
        worker = "w-" + hashlib.sha256(agent.encode()).hexdigest()[:12]
        lines.append(rename.csv_line([key, name_agreement.digest(key, new), "m", agent, worker, "2026-10-21"]).decode())
    with votes.open("a") as handle:
        handle.write("".join(lines))
    return f"agree:{rid}"


def append(root, rel, text):
    with (root / rel).open("a") as handle:
        handle.write(text)
    _git(root, "add", "-A")


def snapshot(root):
    files = {p.relative_to(root).as_posix(): p.read_bytes()
             for p in root.rglob("*") if p.is_file() and ".git" not in p.parts}
    files.pop("reverse/.add_match.lock", None)
    return files


def function_plan(root, **kwargs):
    kwargs.setdefault("rva", 0x00401000)
    kwargs.setdefault("new", "countParts")
    kwargs.setdefault("basis", "inferred")
    if "evidence" not in kwargs:
        kwargs["evidence"] = agree(root, "a1", "function", OLD, "countParts", "0x00401000")
    return rename.plan_rename("function", ctx=ctx_of(root), **kwargs)


OK = (lambda ctx, sources: True)


# ------------------------------------------------- 1, 9: real names are not placeholders

@pytest.mark.parametrize("name", ["?initFilters3D@MilesAudioManager@@QAEXXZ", "?addInt64@Xfer@@QAEX_J@Z",
                                  "parseCoord3D", "parseBitString32", "getInt64", "getCoord3D",
                                  "getCenterPoint2D", "readInt32", "getPosition3D"])
def test_dimension_and_width_names_are_real(name):
    assert not rename.is_placeholder(name)


@pytest.mark.parametrize("kind,name", [("member", "m_sampleCount2D"), ("member", "dwReserved1"),
                                       ("member", "data2"), ("member", "bfReserved1"), ("global", "int64")])
def test_member_shapes_are_real(kind, name):
    assert not rename.is_placeholder(name, kind)


def test_inferred_refused_over_a_zh_shaped_real_name(tree):
    with pytest.raises(Refusal, match="real name"):
        rename.plan_rename("function", ctx=ctx_of(tree), rva=0x00700000, new="initSpatialFilters",
                           basis="inferred", evidence=agree(tree, "z", "function", "?initFilters3D@Audio@@QAEXXZ",
                                                            "initSpatialFilters", "0x00700000"))


def test_getposition3d_is_an_acceptable_new_name(tree):
    p = function_plan(tree, new="getPosition3D",
                      evidence=agree(tree, "p3", "function", OLD, "getPosition3D", "0x00401000"))
    assert p.new_word == "getPosition3D"


def test_shape_only_placeholder_declared_in_a_vendored_view_is_refused(tmp_path):
    root = make_tree(tmp_path, {"Code/Libraries/Source/Lua/lstate.h": "struct lua_Debug { int m_value184; };\n"})
    assert rename.heuristic_placeholder("m_value184", "member")
    assert rename.reference_declarers(ctx_of(root), "m_value184") == ["Code/Libraries/Source/Lua/lstate.h"]
    with pytest.raises(Refusal, match="declared in Code/Libraries/Source/Lua/lstate.h"):
        rename.inferred_guards(ctx_of(root), "member", "X::m_value184", "m_value184", None)


def test_wb_spelled_word_is_refused(tmp_path):
    root = make_tree(tmp_path, {rename.WB_LEADS: "target_rva,current_name,current_kind,wb_name,wb_file,score,"
                                                 "evidence\n0x00999999,,UNROWED,Audio::m_value184,x.cpp,9,cg\n"})
    with pytest.raises(Refusal, match="WorldBuilder"):
        rename.inferred_guards(ctx_of(root), "member", "X::m_value184", "m_value184", None)


# ------------------------------------------------- 2, 15: body_owners.csv follows its row

def test_function_rename_rewrites_body_owners(tree):
    p = function_plan(tree)
    assert p.owner_rows == [(OLD, 0x00401000)]
    rename.apply_rename(p, ctx=ctx_of(tree), verify=OK, checks=None)
    owners = (tree / rename.BODY_OWNERS).read_text()
    assert f"0x00401000,{NEW},40,{UNIT},audited" in owners and OLD not in owners


def test_file_rename_repoints_body_owners(tree):
    ev = "mechanical:rows"
    p = rename.plan_rename("file", ctx=ctx_of(tree), source=UNIT, new="Widget_count", basis="inferred", evidence=ev)
    assert p.path_rows.get(rename.BODY_OWNERS) == 1
    assert b"Code/Game/Widget_count.cpp,audited" in p.after[rename.BODY_OWNERS]


def test_class_rename_rewrites_body_owners(tmp_path):
    root = make_tree(tmp_path, {rename.BODY_OWNERS: "target_rva,name,target_size,source,evidence\n"
                                                    "0x00500000,?f@Rva00500000@@QAEXXZ,6,Code/Game/Bar.cpp,a\n"})
    p = rename.plan_rename("class", ctx=ctx_of(root), name="Rva00500000", new="Barrier", basis="inferred",
                           evidence=agree(root, "c", "class", "Rva00500000", "Barrier"))
    assert b"?f@Barrier@@QAEXXZ" in p.after[rename.BODY_OWNERS]


def test_failing_ledger_checks_restore_everything(tree):
    before = snapshot(tree)
    p = function_plan(tree)
    calls = []

    def checks(ctx, plan):
        calls.append(plan)
        return [] if len(calls) == 1 else ["check_csv: owner disagrees with functions.csv"]
    with pytest.raises(VerifyFailed, match="commit hooks"):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=OK, checks=checks)
    after = snapshot(tree)
    for lane_file in (rename.AGREED, name_agreement.VOTES):    # written by agree() after the snapshot
        after.pop(lane_file, None), before.pop(lane_file, None)
    assert after == before and not rename.journals(ctx_of(tree))


def test_ledger_checks_already_failing_refuse_up_front(tree):
    p = function_plan(tree)
    with pytest.raises(Refusal, match="already fail"):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=OK, checks=lambda ctx, plan: ["check_csv: broken"])


def test_real_check_csv_accepts_the_body_owner_rewrite():
    """The reviewer's case: 0x0004E4BD's audited owner, planned and fed to
    check_csv.check_body_owners together with the planned functions.csv."""
    import check_csv
    if not hasattr(check_csv, "check_body_owners"):
        pytest.skip("check_csv has no check_body_owners")
    ctx = rename.Context()
    rows = [r for r in ctx.rows() if r.get("target_rva") == "0x0004E4BD"]
    if not rows or rows[0]["name"] != "?rva0004E4BD@Rva0004E4BD@@QAEXXZ":
        pytest.skip("0x0004E4BD was renamed upstream")
    old = rows[0]["name"]
    ctx._cache[rename.AGREED] = [{"id": "r", "kind": "function", "old": old,
                                  "new": "forwardToTarget", "rva": "0x0004E4BD", "agents": "a;b"}]
    try:
        p = rename.plan_rename("function", ctx=ctx, rva=0x0004E4BD, new="forwardToTarget", basis="inferred",
                               evidence="agree:r")
    except Refusal as why:
        assert "pin" in str(why) or "WorldBuilder" in str(why)   # finding 17 refuses this body outright
        return
    assert rename.BODY_OWNERS in p.after


# ------------------------------------------------- 3: class tokens are whole fragments

def test_class_rename_never_touches_tbar_or_ubar(tree):
    p = rename.plan_rename("class", ctx=ctx_of(tree), name="Rva00500000", new="Barrier", basis="inferred",
                           evidence=agree(tree, "c", "class", "Rva00500000", "Barrier"))
    functions = p.after[rename.FUNCTIONS].decode()
    assert "?f@Barrier@@QAEXXZ" in functions
    assert "?g@@YAXPAVTRva00500000@@@Z" in functions and "?URva00500000@Zed@@QAEXXZ" in functions
    assert rename.SYMBOLS not in p.after      # ?h@@YAXPAUTRva00500000@@@Z is not Rva00500000
    bar = p.after["Code/Game/Bar.cpp"].decode()
    assert "struct Barrier" in bar and "struct TRva00500000" in bar and "URva00500000()" in bar


@pytest.mark.parametrize("symbol,frags", [
    ("?g@@YAXPAVTBar@@@Z", ["g", "TBar"]), ("?UBar@Zed@@QAEXXZ", ["UBar", "Zed"]),
    ("??RRva00055041AsciiHash@@QBEIABVAsciiString@@@Z", ["Rva00055041AsciiHash", "AsciiString"]),
    ("?s_x@?1??Rva00401000@Widget@@QAEHH@Z@4HA", ["s_x", "Rva00401000", "Widget"]),
    ("??_7Derived@@6BBar@@@", ["Derived", "Bar"]),
    ("?x@?$vector@VBar@@V?$allocator@VBar@@@std@@@std@@QAEXXZ",
     ["x", "vector", "Bar", "allocator", "Bar", "std", "std"]),
])
def test_fragments(symbol, frags):
    assert [symbol[a:b] for a, b in rename.fragments(symbol)] == frags


def test_class_sub_respects_fragment_boundaries():
    assert rename.class_sub("?g@@YAXPAVTBar@@@Z", "Bar", "Barrier") == ("?g@@YAXPAVTBar@@@Z", 0)
    assert rename.class_sub("?UBar@Zed@@QAEXXZ", "Bar", "Barrier") == ("?UBar@Zed@@QAEXXZ", 0)
    assert rename.class_sub("note ?f@Bar@@QAEXXZ;", "Bar", "Barrier") == ("note ?f@Barrier@@QAEXXZ;", 1)


# ------------------------------------------------- 4: one word, one entity

def test_special_member_spelling_is_shared(tmp_path):
    root = make_tree(tmp_path)
    append(root, rename.SYMBOLS, "??RRva00401000@@QBEIABVAsciiString@@@Z,0x00800000,functor\n")
    with pytest.raises(Refusal, match="also spells"):
        function_plan(root)


@pytest.mark.parametrize("rel,text,what", [
    ("Code/Game/Other.h", "struct Other { int Rva00401000; };\n", "data member of Other"),
    ("Code/Game/Gizmo.h", "struct Gizmo { virtual int Rva00401000() = 0; };\n", "method of Gizmo"),
    ("Code/Game/Enum.h", "enum Kind { Rva00401000, Other };\n", "enumerator"),
    ("Code/Game/Free.cpp", "int Rva00401000(int x) { return x; }\n", "function of the global scope"),
])
def test_foreign_declarations_are_refused(tmp_path, rel, text, what):
    root = make_tree(tmp_path, {rel: text})
    with pytest.raises(Refusal, match=what):
        function_plan(root)


def test_class_with_two_enclosing_scopes_is_refused(tmp_path):
    root = make_tree(tmp_path, {"Code/Game/Nodes.h": "struct X { struct Rva00900000 { int a; }; };\n"
                                                     "struct Y { struct Rva00900000 { int b; }; };\n"})
    append(root, rename.FUNCTIONS, "?f@Rva00900000@X@@QAEXXZ,,0x00900000,6,Code/Game/Bar.cpp,matched,\n")
    with pytest.raises(Refusal, match="different scopes"):
        rename.plan_rename("class", ctx=ctx_of(root), name="Rva00900000", new="TreeNode", basis="inferred",
                           evidence=agree(root, "n", "class", "Rva00900000", "TreeNode"))


# ------------------------------------------------- 5: __identifier("?mangled") is code

def test_identifier_call_sites_are_rewritten(tmp_path):
    caller = 'void *table[] = { &__identifier("?Rva00401000@Widget@@QAEHH@Z") };\nconst char *s = "x";\n'
    root = make_tree(tmp_path, {"Code/Game/Table.cpp": caller})
    p = function_plan(root)
    assert p.source_counts["Code/Game/Table.cpp"].get("identifier") == 1
    assert f'__identifier("{NEW}")'.encode() in p.after["Code/Game/Table.cpp"]


def test_other_string_literals_stay_refused(tmp_path):
    root = make_tree(tmp_path, {"Code/Game/Lit.cpp": 'const char *s = "Rva00401000";\n'})
    with pytest.raises(Refusal, match="string literal"):
        function_plan(root)


def test_class_identifier_strings_are_rewritten(tmp_path):
    caller = 'void *p = &__identifier("?f@Rva00500000@@QAEXXZ");\n'
    root = make_tree(tmp_path, {"Code/Game/Ref.cpp": caller})
    p = rename.plan_rename("class", ctx=ctx_of(root), name="Rva00500000", new="Barrier", basis="inferred",
                           evidence=agree(root, "c", "class", "Rva00500000", "Barrier"))
    assert b'__identifier("?f@Barrier@@QAEXXZ")' in p.after["Code/Game/Ref.cpp"]


# ------------------------------------------------- 6: overloads need an explicit pick

def test_param_by_rva_refuses_an_overloaded_scope(tree):
    with pytest.raises(Refusal, match="overloads"):
        rename.plan_rename("param", ctx=ctx_of(tree), source="Code/Game/Foo.cpp", rva=0x00420000, name="param_1",
                           new="ratio", basis="inferred",
                           evidence=agree(tree, "o", "param", "Foo::f::param_1", "Foo::f::ratio", "0x00420000"))


def test_plain_scope_with_overloads_is_ambiguous(tree):
    with pytest.raises(Refusal, match="ambiguous"):
        rename.plan_rename("param", ctx=ctx_of(tree), source="Code/Game/Foo.cpp", function="Foo::f",
                           name="param_1", new="ratio", basis="inferred",
                           evidence=agree(tree, "o", "param", "Foo::f::param_1", "Foo::f::ratio"))


def test_numbered_overload_is_accepted(tree):
    p = rename.plan_rename("param", ctx=ctx_of(tree), source="Code/Game/Foo.cpp", function="Foo::f#2",
                           name="param_1", new="ratio", basis="inferred",
                           evidence=agree(tree, "o", "param", "Foo::f#2::param_1", "Foo::f#2::ratio"))
    text = p.after["Code/Game/Foo.cpp"].decode()
    assert "int Foo::f(int param_1)" in text and "int Foo::f(float ratio) { return (int)ratio; }" in text


# ------------------------------------------------- 7, 18: journal, recover, SIGTERM

def _apply_slowly(root):
    ctx = ctx_of(root)
    p = function_plan(root, evidence="agree:a1")
    rename.apply_rename(p, ctx=ctx, verify=lambda ctx, sources: time.sleep(60) or True, checks=None)


def _run_slowly(root):
    ctx = ctx_of(root)
    rename.run("function", ctx, claim=False, verify=lambda ctx, sources: time.sleep(60) or True, checks=None,
               rva=0x00401000, new="countParts", basis="inferred", evidence="agree:a1")


def _wait_for_journal(root, process, timeout=30):
    deadline = time.time() + timeout
    while time.time() < deadline:
        if list((root / rename.JOURNAL_DIR).glob("*.json")) and \
                b"countParts" in (root / UNIT).read_bytes():
            return
        time.sleep(0.05)
    process.kill()
    pytest.fail("the rename never reached verification")


def test_killed_run_is_recovered(tree):
    agree(tree, "a1", "function", OLD, "countParts", "0x00401000")
    before = snapshot(tree)
    process = multiprocessing.get_context("fork").Process(target=_apply_slowly, args=(tree,))
    process.start()
    _wait_for_journal(tree, process)
    os.kill(process.pid, signal.SIGKILL)
    process.join()
    ctx = ctx_of(tree)
    with pytest.raises(Refusal, match="rename.py recover"):
        rename.run("function", ctx, claim=False, verify=OK, checks=None, rva=0x00403000, new="partCount",
                   basis="inferred", evidence="agree:a1")
    restored, busy = rename.recover(ctx, release_claims=False)
    assert len(restored) == 1 and not busy
    assert snapshot(tree) == before


def test_sigterm_rolls_back(tree):
    agree(tree, "a1", "function", OLD, "countParts", "0x00401000")
    before = snapshot(tree)
    process = multiprocessing.get_context("fork").Process(target=_run_slowly, args=(tree,))
    process.start()
    _wait_for_journal(tree, process)
    os.kill(process.pid, signal.SIGTERM)
    process.join(30)
    assert snapshot(tree) == before and not rename.journals(ctx_of(tree))


def test_live_journal_is_left_alone(tree):
    ctx = ctx_of(tree)
    p = function_plan(tree)
    rename.write_journal(ctx, p)
    record = rename.journals(ctx)[0][1]
    record["pid"] = os.getppid()          # a live process that is not us
    assert rename.journal_alive(record)


# ------------------------------------------------- 8: vendored and SDK sources

def test_vendored_param_is_refused(tree):
    with pytest.raises(Refusal, match="vendored"):
        rename.plan_rename("param", ctx=ctx_of(tree), source="Code/Libraries/Source/Lua/lapi.c",
                           function="pushobject", name="o", new="pushedObject", basis="inferred",
                           evidence=agree(tree, "v", "param", "pushobject::o", "pushobject::pushedObject"))


def test_sdk_shim_member_is_refused(tmp_path):
    header = "typedef struct tagBITMAPFILEHEADER { int bfType; int bfReserved7C; } BITMAPFILEHEADER;\n"
    root = make_tree(tmp_path, {"reference/shims/sweep/windows.h": header,
                                "Code/Game/Bmp.cpp": '#include "windows.h"\nint bmp() { return 0; }\n'})
    append(root, rename.FUNCTIONS, "?bmp@@YAHXZ,,0x00440000,6,Code/Game/Bmp.cpp,matched,\n")
    with pytest.raises(Refusal, match="vendored or SDK"):
        rename.plan_rename("member", ctx=ctx_of(root), cls="tagBITMAPFILEHEADER", member="bfReserved7C",
                           new="bfSpare", basis="inferred",
                           evidence=agree(root, "s", "member", "tagBITMAPFILEHEADER::bfReserved7C",
                                          "tagBITMAPFILEHEADER::bfSpare"))


def test_vendored_paths():
    ctx = rename.Context(object_scan=False)
    assert rename.is_vendored_path(ctx, "Code/Libraries/Source/Lua/lapi.c")
    assert rename.is_vendored_path(ctx, "reference/shims/sweep/windows.h")
    assert rename.is_vendored_path(ctx, "reference/shims/gamespy/gsplatform.h")
    assert not rename.is_vendored_path(ctx, "Code/GameEngine/Source/Common/GameLOD.cpp")


# ------------------------------------------------- 10: inferred needs an agreement record

@pytest.mark.parametrize("evidence,message", [
    ("x", "agree:<record-id>"),
    ("agree:missing", "not in reverse/name_agreed.csv"),
])
def test_inferred_needs_a_real_record(tree, evidence, message):
    with pytest.raises(Refusal, match=message):
        function_plan(tree, evidence=evidence)


@pytest.mark.parametrize("row,message", [
    (("function", OLD, "otherName", "0x00401000", "a;b"), "new"),
    (("class", OLD, "countParts", "0x00401000", "a;b"), "kind"),
    (("function", OLD, "countParts", "0x00402000", "a;b"), "rva"),
    (("function", OLD, "countParts", "0x00401000", "a;a"), "1 distinct worker"),
])
def test_agreement_must_match_this_rename(tree, row, message):
    ev = agree(tree, "m", *row)
    with pytest.raises(Refusal, match=message):
        function_plan(tree, evidence=ev)


def test_mechanical_file_name_must_come_from_its_rows(tree):
    p = rename.plan_rename("file", ctx=ctx_of(tree), source=UNIT, new="Widget_count", basis="inferred",
                           evidence="mechanical:?count@Widget@@QAEHXZ")
    assert p.new.endswith("Widget_count.cpp")
    with pytest.raises(Refusal, match="not derived"):
        rename.plan_rename("file", ctx=ctx_of(tree), source=UNIT, new="InventedName", basis="inferred",
                           evidence="mechanical:x")
    with pytest.raises(Refusal, match="mechanical"):
        function_plan(tree, evidence="mechanical:x")


# ------------------------------------------------- 11: canonical evidence is verified

def test_unverifiable_canonical_kinds_are_gone(tree):
    for kind in ("pin", "caller", "table", "vtable"):
        with pytest.raises(Refusal, match="unknown canonical"):
            function_plan(tree, basis=f"canonical:{kind}", evidence="trust me")


ZH_WIDGET = "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Widget.cpp"


def zh_sweep(size=40, relocs=2, rva=0x00401000):
    return json.dumps([{"sym": NEW, "source": ZH_WIDGET, "size": size, "relocs": relocs, "rva": rva,
                        "bucket": "exact-unique-claimed"}])


def test_canonical_zh_needs_a_citation_that_spells_it(tmp_path):
    root = make_tree(tmp_path, {ZH_WIDGET: "#include \"Widget.h\"\nint Widget::countParts(int n)\n{ return n; }\n",
                                "build/zh_sweep/match.json": zh_sweep()})
    with pytest.raises(Refusal, match="citing"):
        function_plan(root, basis="canonical:zh", evidence="zero hour has it")
    with pytest.raises(Refusal, match="does not spell"):
        function_plan(root, basis="canonical:zh", evidence=f"{ZH_WIDGET}:1")
    assert function_plan(root, basis="canonical:zh", evidence=f"{ZH_WIDGET}:2").basis == "canonical:zh"


@pytest.mark.parametrize("sweep,message", [
    (None, "no zh-body candidate"),                          # a ZH spelling with no same-body record
    (zh_sweep(size=8, relocs=0), "trivial body"),            # a body that places anywhere: a hint
    (zh_sweep(rva=0x00403000), "no zh-body candidate"),      # the record is for another address
])
def test_canonical_zh_needs_the_same_body_record(tmp_path, sweep, message):
    """Review fix-2 finding 3: a cited Zero Hour line is not proof that this body is that function."""
    extra = {ZH_WIDGET: "#include \"Widget.h\"\nint Widget::countParts(int n)\n{ return n; }\n"}
    if sweep:
        extra["build/zh_sweep/match.json"] = sweep
    root = make_tree(tmp_path, extra)
    with pytest.raises(Refusal, match=message):
        function_plan(root, basis="canonical:zh", evidence=f"{ZH_WIDGET}:2")


BFME1_GAME = "reference/open-bfme-1/game/GameEngine/Widget.cpp"
BFME1_LEDGER = "reference/open-bfme-1/targets/game/reverse/functions.csv"
BFME1_EA = "reference/open-bfme-1/targets/game/reverse/ea_evidence.csv"


def bfme1_tree(tmp_path, ea_basis=None):
    extra = {BFME1_GAME: "int Widget::countParts(int n)\n{ return n; }\n",
             BFME1_LEDGER: f"name,export_rva,target_rva,target_size,source,status,notes\n{NEW},,0x7000,40,x,matched,\n",
             "build/bfme1_sweep/match.json": json.dumps({"records": [
                 {"name": NEW, "source": "game/GameEngine/Widget.cpp", "bfme1_rva": 0x7000, "bfme2_rva": 0x401000,
                  "size": 40, "icf_twins": [], "calls": [1], "strings": [], "imports": []}]})}
    if ea_basis:
        extra[BFME1_EA] = f"rva,kind,value,route,basis\n0x00007000,name,Widget::countParts,wb,{ea_basis}\n"
    return make_tree(tmp_path, extra)


def test_canonical_bfme1_refuses_its_ledgers_and_unsupported_names(tmp_path):
    root = bfme1_tree(tmp_path)
    with pytest.raises(Refusal, match="agents"):
        function_plan(root, basis="canonical:bfme1", evidence=f"{BFME1_LEDGER}:2")
    with pytest.raises(Refusal, match="without EA evidence"):
        function_plan(root, basis="canonical:bfme1", evidence=f"{BFME1_GAME}:1")


def test_canonical_bfme1_with_ea_evidence(tmp_path):
    root = bfme1_tree(tmp_path, ea_basis="strong")
    assert function_plan(root, basis="canonical:bfme1", evidence=f"{BFME1_EA}:2").basis == "canonical:bfme1"


def test_canonical_bfme1_weak_ea_is_refused(tmp_path):
    root = bfme1_tree(tmp_path, ea_basis="weak")
    with pytest.raises(Refusal, match="does not grade"):
        function_plan(root, basis="canonical:bfme1", evidence=f"{BFME1_EA}:2")


def test_canonical_export_and_module_are_checked(tree):
    with pytest.raises(Refusal, match="no retail export"):
        function_plan(tree, basis="canonical:export", evidence="exports")
    append(tree, rename.EXPORTS, f"1,0x1,0x00401000,.text,code,{NEW}\n")
    assert function_plan(tree, basis="canonical:export", evidence="exports").basis == "canonical:export"
    with pytest.raises(Refusal, match="module class"):
        rename.plan_rename("class", ctx=ctx_of(tree), name="Rva00500000", new="Barrier",
                           basis="canonical:module", evidence="registry")


def test_canonical_string_needs_the_xref(tmp_path):
    root = make_tree(tmp_path, {rename.STRING_XREFS: "Widget::countParts failed\t0x00401000\n"
                                                     "Widget::countParts too\t0x00123456\n"})
    with pytest.raises(Refusal, match="string"):
        function_plan(root, basis="canonical:string", evidence="a string somewhere")
    assert function_plan(root, basis="canonical:string", evidence="0x00401000").basis == "canonical:string"


def test_canonical_string_must_be_this_functions_own(tmp_path):
    """Review fix-2 finding 3: another function's string names that function,
    and a substring is not the word."""
    root = make_tree(tmp_path, {rename.STRING_XREFS: "Widget::countParts too\t0x00123456\n"
                                                     "Widget::countPartsTotal\t0x00401000\n"})
    with pytest.raises(Refusal, match="own address"):
        function_plan(root, basis="canonical:string", evidence="0x00123456")
    with pytest.raises(Refusal, match="as a word"):
        function_plan(root, basis="canonical:assert", evidence="0x00401000")


def test_canonical_string_for_a_class_needs_one_of_its_functions(tmp_path):
    root = make_tree(tmp_path, {rename.STRING_XREFS: "Barrier::f failed\t0x00500000\nBarrier\t0x00410000\n"})
    plan = rename.plan_rename("class", ctx=ctx_of(root), name="Rva00500000", new="Barrier",
                              basis="canonical:string", evidence="0x00500000")
    assert plan.basis == "canonical:string"
    with pytest.raises(Refusal, match="no function of Rva00500000"):
        rename.plan_rename("class", ctx=ctx_of(root), name="Rva00500000", new="Barrier",
                           basis="canonical:string", evidence="0x00410000")


# ------------------------------------------------- 13, 14: post-rebase check

def test_gitattributes_unions_name_basis():
    attributes = (rename.ROOT / ".gitattributes").read_text()
    assert "reverse/name_basis.csv text eol=lf merge=union" in attributes
    assert "reverse/name_votes.csv text eol=lf merge=union" in attributes      # review fix-2


def test_check_finds_a_resurrected_pin_and_tombstoned_data_row(tree):
    rename.apply_rename(function_plan(tree), ctx=ctx_of(tree), verify=OK, checks=None)
    ctx = ctx_of(tree)
    assert rename.check_renames(ctx, rename.name_basis_rows(ctx)) == []
    append(tree, rename.SYMBOLS, f"{OLD},0x00401000,pin from another seat\n")
    append(tree, rename.DELETED, '?g_x@@3HA,0x00A00000,"Renamed to ?g_y@@3HA"\n')
    append(tree, rename.DATA_ROWS, f"?g_x@@3HA,0x00A00000,rva,4,.data,{UNIT},matched,e,m\n")
    ctx = ctx_of(tree)
    problems = rename.check_renames(ctx, rename.name_basis_rows(ctx))
    assert any("symbols.csv still spells" in p for p in problems)
    assert any("tombstoned" in p for p in problems)


def test_check_cli_range(tree, capsys):
    _git(tree, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-qm", "base")
    rename.apply_rename(function_plan(tree), ctx=ctx_of(tree), verify=OK, checks=None)
    _git(tree, "add", "-A")
    _git(tree, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-qm", "rename")
    assert rename.main(["check", "--range", "HEAD~1..HEAD", "--root", str(tree)]) == 0
    append(tree, UNIT, "int again() { Widget w; return w.Rva00401000(1); }\n")
    assert rename.main(["check", "--range", "HEAD~1..HEAD", "--root", str(tree)]) == 1
    assert "WidgetRva00401000.cpp still spells Rva00401000" in capsys.readouterr().err


# ------------------------------------------------- 16: records move with their scope

def test_function_rename_carries_its_param_record(tree):
    (tree / rename.NAME_BASIS).write_text(rename.NAME_BASIS_HEADER + "\n"
                                          f"param,Widget::Rva00401000::n,Widget::Rva00401000::count,"
                                          f"canonical:zh,x,{UNIT},0x00401000\n")
    p = function_plan(tree)
    assert p.carried == [("Widget::Rva00401000::count", "Widget::countParts::count", "canonical:zh")]
    rename.apply_rename(p, ctx=ctx_of(tree), verify=OK, checks=None)
    rows = (tree / rename.NAME_BASIS).read_text().splitlines()
    assert rows[-1].startswith("carry,Widget::Rva00401000::count,Widget::countParts::count,canonical:zh,")
    assert rename.recorded_basis(ctx_of(tree), "Widget::countParts::count") == "canonical:zh"


def test_class_scoping_a_canonical_record_is_refused(tree):
    (tree / rename.NAME_BASIS).write_text(rename.NAME_BASIS_HEADER + "\n"
                                          "function,?Rva1@Rva00500000@@QAEXXZ,?f@Rva00500000@@QAEXXZ,"
                                          "canonical:export,x,Code/Game/Bar.cpp,0x00500000\n")
    with pytest.raises(Refusal, match=r"scopes \?f@Rva00500000@@QAEXXZ, recorded canonical"):
        rename.plan_rename("class", ctx=ctx_of(tree), name="Rva00500000", new="Barrier", basis="inferred",
                           evidence=agree(tree, "c", "class", "Rva00500000", "Barrier"))


# ------------------------------------------------- 17: no inferred name over evidence on record

def test_inferred_refused_over_a_real_pin(tree):
    append(tree, rename.SYMBOLS, "??1RadarEventRefSlot@@QAE@XZ,0x00401000,harvested\n")
    with pytest.raises(Refusal, match="RadarEventRefSlot"):
        function_plan(tree)


WB_LEAD = ("target_rva,current_name,current_kind,wb_name,wb_file,score,evidence\n"
           "0x00401000,,ROW,Widget::countThings,w.cpp,{score},cg\n")


def wb_tree(tmp_path, score=7, asserts=True):
    body = {"va": 0x1000, "names": ["Widget::countThings"] if asserts else [], "name_files": []}
    return make_tree(tmp_path, {rename.WB_LEADS: WB_LEAD.format(score=score),
                                "build/wb/wb_functions.jsonl": json.dumps(body) + "\n",
                                "build/wb/matches_full.jsonl": json.dumps(
                                    {"gd_va": 0x00401000 + 0x400000, "wb_va": 0x1000,
                                     "wb_name": "Widget::countThings", "score": score}) + "\n"})


def test_inferred_refused_over_a_wb_lead(tmp_path):
    root = wb_tree(tmp_path)
    with pytest.raises(Refusal, match="canonical:wb"):
        function_plan(root)
    p = function_plan(root, new="countThings", basis="canonical:wb", evidence="wb lead 0x00401000")
    assert p.basis == "canonical:wb"


@pytest.mark.parametrize("score,asserts,message", [
    (2, True, "score 2 < 4"),
    (7, False, "does not assert"),
])
def test_canonical_wb_needs_the_graded_proof(tmp_path, score, asserts, message):
    """Review fix-2 finding 3: a lead row at the address is not proof."""
    root = wb_tree(tmp_path, score, asserts)
    with pytest.raises(Refusal, match=message):
        function_plan(root, new="countThings", basis="canonical:wb", evidence="wb lead 0x00401000")


def test_canonical_wb_lead_only_without_wb_data_is_refused(tmp_path):
    root = make_tree(tmp_path, {rename.WB_LEADS: WB_LEAD.format(score=9)})
    with pytest.raises(Refusal, match="does not grade"):
        function_plan(root, new="countThings", basis="canonical:wb", evidence="wb lead")


# ------------------------------------------------- the reviewer's real-tree cases

REAL_REFUSALS = [
    (["function", "--rva", "0x0005BB52", "--new", "initSpatialFilters"], "real name"),
    (["function", "--rva", "0x00055041", "--new", "hashAsciiString"], "also spells"),
    (["function", "--rva", "0x00655F00", "--new", "addSigned64"], "real name"),
    (["function", "--rva", "0x0004E4BD", "--new", "forwardPinned"], "RadarEventRefSlot"),
    (["param", "--source", "Code/Libraries/Source/Lua/lapi.c", "--function", "luaA_pushobject", "--name", "o",
      "--new", "pushedObject"], "vendored"),
    (["member", "--class", "StaticGameLODInfo", "--member", "m_sampleCount2D", "--new", "m_sampleCountTwoD"],
     "real name"),
]


@pytest.mark.parametrize("argv,message", REAL_REFUSALS)
def test_real_tree_reviewer_cases_are_refused(argv, message, capsys, monkeypatch):
    """With the agreement gate passed, each case still meets its own refusal."""
    monkeypatch.setattr(rename, "check_agreement", lambda *a, **k: None)
    code = rename.main(argv + ["--basis", "inferred", "--evidence", "agree:x", "--dry-run", "--no-claim",
                               "--no-object-scan"])
    err = capsys.readouterr().err
    assert code == 2, err
    assert message in err, err


@pytest.mark.parametrize("evidence", ["x", "agree:not-a-record"])
def test_real_tree_inferred_without_agreement_is_refused(evidence):
    """Finding 10: 'x' used to pass as an agreement record."""
    with pytest.raises(Refusal, match="agree:<record-id>|not in reverse/name_agreed.csv"):
        rename.check_basis(rename.Context(object_scan=False), "function", "inferred", evidence,
                           "?Rva00401000@@YAXXZ", "Rva00401000", None, new_word="readToken")


def test_name_metric_shares_the_definition():
    assert rename.name_metric is name_metric
    assert not name_metric.placeholder("parseCoord3D") and name_metric.placeholder("m_0C")


# A byte match cannot detect a rename of the wrong shadowed binding.
@pytest.mark.parametrize("outer", ["global", "header", "member"])
def test_precise_scalar_local_preserves_outer_uses_and_reverts(tmp_path, outer):
    code = "// cl: /O2\nint iVar3;\nint sample(int value) { value += iVar3; { int iVar3 = 2; value += iVar3; } return value + iVar3; }\n"
    function = "sample"
    symbol = "?sample@@YAHH@Z"
    extra = {}
    if outer == "header":
        code = code.replace("int iVar3;", '#include "Outer.h"')
        extra["Code/Game/Outer.h"] = "extern int iVar3;\n"
    if outer == "member":
        code = code.replace("int iVar3;", "struct Widget { int iVar3; int sample(int value); };")
        code = code.replace("int sample(int value) {", "int Widget::sample(int value) {")
        function, symbol = "Widget::sample", "?sample@Widget@@QAEHH@Z"
    extra.update({UNIT: code, "reverse/symbols.csv": "name,address,notes\n",
                  "reverse/functions.csv": f"name,export_rva,target_rva,target_size,source,status,notes\n{symbol},,0x00401000,40,{UNIT},matched,test\n"})
    root = make_tree(tmp_path, extra)
    evidence = agree(root, "precise", "local", "iVar3", "intensity")
    builds = []
    def verify(ctx, sources):
        builds.append(sources)
        return True
    rename.run("local", ctx_of(root), source=UNIT, function=function, name="iVar3", new="intensity",
               basis="inferred", evidence=evidence, local_binding=True, claim=False,
               verify=verify, checks=lambda ctx, plan: [])
    after = (root / UNIT).read_text()
    assert "value += iVar3; { int intensity = 2; value += intensity; } return value + iVar3;" in after
    assert builds == [[UNIT]]
    assert rename.check_renames(ctx_of(root), rename.name_basis_rows(ctx_of(root))) == []
    rename.revert(ctx_of(root), "precise", "fixture exact inverse", claim=False,
                  verify=verify, checks=lambda ctx, plan: [])
    assert (root / UNIT).read_bytes() == code.encode()


@pytest.mark.parametrize("body", [
    "{ use(iVar3); { int iVar3 = 2; use(iVar3); } }",
    "{ int iVar3 = iVar3; use(iVar3); }",
])
def test_precise_binding_starts_at_declarator(body):
    begin, end = rename.scalar_local_binding(body, "iVar3")
    assert body[begin:end].startswith("iVar3 =")


@pytest.mark.parametrize("body", [
    "{ for (int iVar3 = 0; iVar3 < 2; ++iVar3) use(iVar3); use(iVar3); }",
    "{ if (int iVar3 = next()) use(iVar3); else use(iVar3); }",
    "{ { int iVar3 = 1; } { int iVar3 = 2; } use(iVar3); }",
    "{ int iVar3[3]; use(iVar3); }",
    "{ struct Local { int iVar3; }; int iVar3 = 1; }",
    "{ auto fn = [&]() { int iVar3 = 1; return iVar3; }; }",
    "{ Thing iVar3 = value; use(iVar3); }",
    "{ #if FLAG\n int iVar3 = 1;\n #endif\n use(iVar3); }",
])
def test_precise_binding_declines_ambiguous_shapes(body):
    assert rename.scalar_local_binding(body, "iVar3") is None


def test_precise_binding_keeps_macro_member_and_capture_refusals(tmp_path):
    for n, (prefix, body, new) in enumerate([
        ("#define iVar3 alias\n", "int iVar3 = 2; return iVar3;", "intensity"),
        ("", "int iVar3 = 2; return this->iVar3;", "intensity"),
        ("", "int iVar3 = 2; int intensity = 3; return iVar3 + intensity;", "intensity"),
    ]):
        root = tmp_path / str(n); root.mkdir()
        source = "// cl: /O2\n" + prefix + "int iVar3;\nint sample() { " + body + " }\n"
        make_tree(root, {UNIT: source, "reverse/symbols.csv": "name,address,notes\n",
                       "reverse/functions.csv": f"name,export_rva,target_rva,target_size,source,status,notes\n?sample@@YAHXZ,,0x00401000,40,{UNIT},matched,test\n"})
        ev = agree(root, "precise", "local", "iVar3", new)
        with pytest.raises(Refusal):
            rename.plan_rename("local", ctx=ctx_of(root), source=UNIT, function="sample", name="iVar3", new=new,
                               basis="inferred", evidence=ev, local_binding=True)


@pytest.mark.parametrize("body", [
    "{ int iVar3 = 1; void nested(int iVar3); use(iVar3); }",
    "{ goto iVar3; int iVar3 = 1; iVar3: use(iVar3); }",
    "{ auto fn = [&]() mutable { int iVar3 = 1; return iVar3; }; }",
])
def test_precise_binding_declines_other_identifier_namespaces(body):
    assert rename.scalar_local_binding(body, "iVar3") is None


@pytest.mark.parametrize("alias", [False, True])
def test_precise_binding_refuses_scope_changing_header_macros(tmp_path, alias):
    prefix = '#define START {\n#define END }\n'
    if alias:
        prefix += '#define BEGIN START\n'
    begin = "BEGIN" if alias else "START"
    code = f'// cl: /O2\n#include "Scopes.h"\nint iVar3;\nint sample() {{ {begin}; int iVar3 = 1; END; return iVar3; }}\n'
    root = make_tree(tmp_path, {UNIT: code, "Code/Game/Scopes.h": prefix,
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/functions.csv": f"name,export_rva,target_rva,target_size,source,status,notes\n?sample@@YAHXZ,,0x00401000,40,{UNIT},matched,test\n"})
    ev = agree(root, "precise", "local", "iVar3", "intensity")
    with pytest.raises(Refusal, match="scope-changing macro"):
        rename.plan_rename("local", ctx=ctx_of(root), source=UNIT, function="sample", name="iVar3", new="intensity",
                           basis="inferred", evidence=ev, local_binding=True)


def test_precise_binding_rolls_back_failed_verification(tmp_path):
    code = "// cl: /O2\nint iVar3;\nint sample() { int iVar3 = 1; return iVar3; }\n"
    root = make_tree(tmp_path, {UNIT: code, "reverse/symbols.csv": "name,address,notes\n",
        "reverse/functions.csv": f"name,export_rva,target_rva,target_size,source,status,notes\n?sample@@YAHXZ,,0x00401000,40,{UNIT},matched,test\n"})
    ev = agree(root, "precise", "local", "iVar3", "intensity")
    before = snapshot(root)
    with pytest.raises(VerifyFailed):
        rename.run("local", ctx_of(root), source=UNIT, function="sample", name="iVar3", new="intensity",
                   basis="inferred", evidence=ev, local_binding=True, claim=False,
                   verify=lambda ctx, sources: False, checks=lambda ctx, plan: [])
    assert snapshot(root) == before


@pytest.mark.parametrize("change", ["source", "header", "wrong-source"])
def test_precise_inverse_requires_recorded_unchanged_outer_context(tmp_path, change):
    code = '// cl: /O2\n#include "Outer.h"\nint sample() { int value = iVar3; { int iVar3 = 1; value += iVar3; } return value + iVar3; }\n'
    root = make_tree(tmp_path, {UNIT: code, "Code/Game/Outer.h": "extern int iVar3;\n",
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/functions.csv": f"name,export_rva,target_rva,target_size,source,status,notes\n?sample@@YAHXZ,,0x00401000,40,{UNIT},matched,test\n"})
    ev = agree(root, "precise", "local", "iVar3", "intensity")
    rename.run("local", ctx_of(root), source=UNIT, function="sample", name="iVar3", new="intensity",
               basis="inferred", evidence=ev, local_binding=True, claim=False, verify=OK, checks=lambda ctx, plan: [])
    if change == "source":
        path = root / UNIT
        path.write_bytes(path.read_bytes() + b"int iVar3;\n")
    elif change == "header":
        (root / "Code/Game/Outer.h").write_bytes(b"extern int iVar3;\nstruct Other { int iVar3; };\n")
    else:
        path = root / rename.NAME_BINDINGS
        path.write_bytes(path.read_bytes().replace(UNIT.encode(), b"Code/Game/Elsewhere.cpp"))
    before = snapshot(root)
    with pytest.raises(Refusal):
        rename.revert(ctx_of(root), "precise", "changed context", claim=False, verify=OK, checks=lambda ctx, plan: [])
    assert snapshot(root) == before


@pytest.mark.parametrize("success", [True, False])
def test_precise_batch_proofs_are_atomic_and_inverses_compose(tmp_path, success):
    code = "// cl: /O2\nint iVar3; int iVar4;\nint sample() { int result = iVar3 + iVar4; { int iVar3 = 1; result += iVar3; } { int iVar4 = 2; result += iVar4; } return result + iVar3 + iVar4; }\n"
    root = make_tree(tmp_path, {UNIT: code, "reverse/symbols.csv": "name,address,notes\n",
        "reverse/functions.csv": f"name,export_rva,target_rva,target_size,source,status,notes\n?sample@@YAHXZ,,0x00401000,40,{UNIT},matched,test\n"})
    requests = []
    for old, new, record in [("iVar3", "lightLevel", "first"), ("iVar4", "stepCount", "second")]:
        ev = agree(root, record, "local", old, new)
        requests.append(("local", dict(source=UNIT, function="sample", name=old, new=new,
                                      basis="inferred", evidence=ev, local_binding=True)))
    before = snapshot(root)
    builds = []
    def verify(ctx, sources):
        builds.append(sources)
        return success
    if not success:
        with pytest.raises(VerifyFailed):
            rename.run_scoped_batch(ctx_of(root), requests, claim=False, verify=verify, checks=lambda ctx, plan: [])
        assert snapshot(root) == before
    else:
        rename.run_scoped_batch(ctx_of(root), requests, claim=False, verify=verify, checks=lambda ctx, plan: [])
        assert len(ctx_of(root).dicts(rename.NAME_BINDINGS)) == 2
        for record in ("first", "second"):
            rename.revert(ctx_of(root), record, "fixture inverse", claim=False, verify=OK, checks=lambda ctx, plan: [])
        assert (root / UNIT).read_bytes() == code.encode()
    assert builds == [[UNIT]]
