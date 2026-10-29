"""tools/name_lane.py on a miniature tree: a temporary git repository with
small ledgers and one source, so serving, blind hashed voting, agreement
(two sessions agreeing, disagreeing, ties), landing through tools/rename.py
and disputes all run without the real ledger or a compiler (verification is
injected). A real-tree `next --list-only` smoke closes the file."""
import csv
import io
import json
import os
import subprocess
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import name_agreement  # noqa: E402
import name_lane  # noqa: E402
import rename  # noqa: E402

SOURCE = "Code/Game/Box.cpp"
FN = "?rva00401000@@YAHPAURva00401000Box@@H@Z"
BOX = """// cl: /O2
struct Rva00401000Box {
    int m_x2C;
    int m_count;
};
int g_00A01000;
int rva00401000(Rva00401000Box *param_1, int a2)
{
    int iVar3 = param_1->m_x2C + a2;
    g_00A01000 = iVar3;
    return iVar3;
}
"""
SLOW = """// cl: /Od
struct Rva00402000Slow { int m_x10; int m_y; };
int rva00402000(Rva00402000Slow *param_1)
{
    int iVar1 = param_1->m_x10;
    return iVar1 + param_1->m_x10;
}
"""
FILES = {
    "reverse/functions.csv": "name,export_rva,target_rva,target_size,source,status,notes\n"
                             f"{FN},,0x00401000,20,{SOURCE},matched,\n"
                             "?rva00402000@@YAHPAURva00402000Slow@@@Z,,0x00402000,12,Code/Game/Slow.cpp,matched,\n",
    "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n"
                             f"?g_00A01000@@3HA,0x00A01000,rva,4,.data,{SOURCE},matched,ev,m\n",
    "reverse/symbols.csv": "name,address,notes\n",
    "reverse/deleted_rows.csv": "name,target_rva,reason\n",
    SOURCE: BOX,
    "Code/Game/Slow.cpp": SLOW,
}


def _git(root, *args):
    return subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True, text=True).stdout


@pytest.fixture
def tree(tmp_path):
    for rel, text in FILES.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(tmp_path, "init", "-q")
    _git(tmp_path, "add", "-A")
    return tmp_path


@pytest.fixture(autouse=True)
def seat(monkeypatch):
    """Each test sets its seats' worker identity through BFME_CLAIM_OWNER."""
    monkeypatch.setenv("BFME_CLAIM_OWNER", "seat-default")
    # Miniature repositories have no coordination remote. Claim tests opt in;
    # ordinary naming tests must not spend time retrying a nonexistent origin.
    monkeypatch.setenv("BFME_CLAIMS", "off")


@pytest.fixture
def claim_coordination(monkeypatch):
    monkeypatch.setenv("BFME_CLAIMS", "on")


def be(worker):
    os.environ["BFME_CLAIM_OWNER"] = worker


def lane_of(root):
    return name_lane.Lane(root, rename.Context(root, object_scan=False))


def rows(root, rel):
    path = root / rel
    return list(csv.DictReader(io.StringIO(path.read_text(encoding="utf-8")))) if path.exists() else []


def serve(root, session, model="claude-opus-5-5", worker=None, **kw):
    be(worker or f"seat-{session}")
    args = SimpleNamespace(session=session, model=model, count=1, file=kw.get("file", SOURCE), list_only=False)
    assert name_lane.cmd_next(lane_of(root), args) == 0
    return json.loads((root / f"build/name_lane/sessions/{session}.json").read_text())


def vote(root, tmp_path, session, answers, model="claude-opus-5-5", lead=2, min_models=1, worker=None):
    serve(root, session, model, worker)
    answer = tmp_path / f"answer-{session}.json"
    answer.write_text(json.dumps(answers))
    args = SimpleNamespace(answer=str(answer), session=session, model=model)
    return name_lane.cmd_submit(lane_of(root), args, lead=lead, min_models=min_models)


def ok_verify(ctx, sources):
    return True


def no_checks(ctx, plan):
    return []


def apply(root, **kw):
    args = SimpleNamespace(retry_blocked=kw.get("retry_blocked", False), lead=2, min_models=1, claim=False,
                           only_labels=kw.get("only_labels"), key=kw.get("key"), no_batch=kw.get("no_batch", False))
    return name_lane.cmd_apply(lane_of(root), args, verify=kw.get("verify", ok_verify),
                               checks=kw.get("checks", no_checks))


FN_KEY = name_lane.key_of(SOURCE, "function", "0x00401000", "rva00401000")
MEMBER_KEY = name_lane.key_of(SOURCE, "member", "Rva00401000Box", "m_x2C")
PARAM_KEY = name_lane.key_of(SOURCE, "param", "rva00401000", "param_1")


# ---------------------------------------------------------------- pure rules

def test_canon_folds_order_plurals_synonyms():
    assert name_lane.canon("m_ladderComboBox") == name_lane.canon("m_comboBoxLadder")
    assert name_lane.canon("numItems") == name_lane.canon("itemCount")
    assert name_lane.digest("k", "boxIndex") == name_lane.digest("k", "idxBox")
    assert name_lane.digest("k", "boxIndex") != name_lane.digest("other", "boxIndex")


@pytest.mark.parametrize("kind", ["param", "local", "function", "class", "member", "global"])
def test_scoped_review_threshold_is_shared_by_lane_and_engine(kind):
    key = name_lane.key_of(SOURCE, kind, "rva00401000", "param_1")
    worker = "w-0123456789ab"
    mine = {worker: "seat-a"}
    vote_row = {"key": key, "hash": name_agreement.digest(key, "box"),
                "worker": worker, "model": "seat-a"}
    scoped = kind in ("param", "local")
    assert name_agreement.wins(mine, [], key=key) == scoped
    assert (not name_agreement.verify([vote_row], [], key, "box")) == scoped
    assert not name_agreement.wins(mine, [], key=key, min_models=2)
    assert name_agreement.verify([], [], key, "box")
    assert name_agreement.verify([{**vote_row, "worker": "fake"}], [], key, "box")


@pytest.mark.parametrize("kind", ["param", "local"])
def test_scoped_competing_and_disputed_proposals_keep_review(kind):
    key = name_lane.key_of(SOURCE, kind, "rva00401000", "param_1")
    votes = [{"key": key, "hash": name_agreement.digest(key, name), "worker": worker,
              "model": "seat-a"} for name, worker in
             [("box", "w-0123456789ab"), ("destination", "w-abcdef012345")]]
    assert name_agreement.verify(votes, [], key, "box")
    assert not name_agreement.wins({"a": "m"}, [{"b": "m"}], key=key)
    assert not name_agreement.wins({"a": "m", "b": "m"}, [{"c": "m"}], key=key)
    assert name_agreement.wins({"a": "m", "b": "m", "c": "m"}, [{"d": "m"}], key=key)
    assert name_agreement.verify(votes[:1], [{"key": key, "new": "box", "status": "disputed"}],
                                 key, "box")


@pytest.mark.parametrize("key", [None, "param", "Code/Game/Test.cpp|param||a",
                                 "Code/Game/Test.cpp|local|run|", "vendor/Test.cpp|local|run|a"])
def test_malformed_or_non_game_keys_do_not_get_single_proposal_review(key):
    assert not name_agreement.wins({"w-0123456789ab": "seat-a"}, [], key=key)


def test_wins_rules():
    two = {"s1": "a", "s2": "a"}
    assert name_lane.wins(two, [])
    assert not name_lane.wins({"s1": "a"}, [])
    assert not name_lane.wins(two, [{"s3": "a"}])                  # tie-ish: lead 1
    assert name_lane.wins(two, [{"s3": "a"}], lead=1)
    assert not name_lane.wins(two, [], min_models=2)
    assert name_lane.wins({"s1": "a", "s2": "b"}, [], min_models=2)


def role_descriptor(**changes):
    return dict(dict(role="source", entity="box", units="none", ownership="borrowed"), **changes)


def semantic_votes(entries, key=PARAM_KEY):
    votes, meanings = [], []
    for i, (name, descriptor) in enumerate(entries):
        vote_row = dict(key=key, hash=name_agreement.digest(key, name), model=f"seat-{i}",
                        worker=f"w-{i:012x}", session=f"s{i}", date="2026-10-28")
        votes.append(vote_row)
        if descriptor is not None:
            meanings.append(dict(vote_row, meaning=name_agreement.meaning_digest(key, descriptor)))
    return votes, meanings


def test_explicit_same_role_combines_different_spellings_but_not_unvoted_names():
    votes, meanings = semantic_votes([("box", role_descriptor()), ("inputBox", role_descriptor())])
    assert name_agreement.digest(PARAM_KEY, "box") != name_agreement.digest(PARAM_KEY, "inputBox")
    mine, rivals, role = name_agreement.support(name_agreement.tally(votes, meanings), {}, PARAM_KEY, "box")
    assert len(mine) == 2 and rivals == [] and role == meanings[0]["meaning"]
    assert name_agreement.verify(votes, [], PARAM_KEY, "box", meaning_votes=meanings, meaning=role) == []
    assert name_agreement.verify(votes, [], PARAM_KEY, "sourceBox", meaning_votes=meanings, meaning=role)


@pytest.mark.parametrize("difference", [dict(role="destination"), dict(units="bytes"), dict(ownership="owned")])
def test_same_spelling_cannot_hide_explicit_meaning_disagreement(difference):
    votes, meanings = semantic_votes([("box", role_descriptor()), ("box", role_descriptor(**difference))])
    role = meanings[0]["meaning"]
    assert name_agreement.verify(votes, [], PARAM_KEY, "box", meaning_votes=meanings, meaning=role)
    mine, rivals, _ = name_agreement.support(name_agreement.tally(votes, meanings), {}, PARAM_KEY, "box", role)
    assert len(mine) == 1 and [len(v) for v in rivals] == [1]


@pytest.mark.parametrize("field,value", [("worker", "w-abcdef123456"), ("key", PARAM_KEY + "x"),
                                         ("session", "other-session"), ("hash", "0" * 24), ("meaning", None)])
def test_meaning_annotation_must_bind_an_actual_vote(field, value):
    votes, meanings = semantic_votes([("box", role_descriptor()), ("inputBox", role_descriptor())])
    meanings[1][field] = value
    assert name_agreement.verify(votes, [], PARAM_KEY, "box", meaning_votes=meanings,
                                 meaning=meanings[0]["meaning"])


def test_legacy_exact_spelling_remains_compatible_and_unknown_alias_is_a_rival():
    votes, meanings = semantic_votes([("box", role_descriptor()), ("box", None)])
    mine, rivals, _ = name_agreement.support(name_agreement.tally(votes, meanings), {}, PARAM_KEY, "box")
    assert len(mine) == 2 and not rivals
    votes, meanings = semantic_votes([("box", role_descriptor()), ("inputBox", None)])
    assert name_agreement.verify(votes, [], PARAM_KEY, "box", meaning_votes=meanings)


def test_conflicting_annotations_fail_closed_and_disputes_cover_equivalent_aliases():
    votes, meanings = semantic_votes([("box", role_descriptor()), ("inputBox", role_descriptor())])
    role = meanings[0]["meaning"]
    disputed = [dict(key=PARAM_KEY, new="box", status="disputed", id=name_lane.record_id(PARAM_KEY, "box", role))]
    assert name_agreement.verify(votes, disputed, PARAM_KEY, "inputBox", meaning_votes=meanings, meaning=role)
    meanings.append(dict(meanings[0], meaning=name_agreement.meaning_digest(PARAM_KEY, role_descriptor(role="destination"))))
    assert name_agreement.verify(votes, [], PARAM_KEY, "box", meaning_votes=meanings, meaning=role)


@pytest.mark.parametrize("descriptor", [None, {}, dict(role="source"), role_descriptor(entity="unknown"),
                                         role_descriptor(role=[]), role_descriptor(units="metres_per_second")])
def test_meaning_contract_rejects_missing_generic_or_malformed_fields(descriptor):
    with pytest.raises(ValueError):
        name_agreement.meaning_digest(PARAM_KEY, descriptor)
    with pytest.raises(ValueError):
        name_agreement.meaning_digest(FN_KEY, role_descriptor())


def test_owned_kinds(tree):
    items = lane_of(tree).owned(SOURCE)
    got = {(k, s, i) for k, s, i, _ in items}
    assert ("class", "", "Rva00401000Box") in got
    assert ("member", "Rva00401000Box", "m_x2C") in got
    assert ("member", "Rva00401000Box", "m_count") not in got        # real name
    assert ("function", "0x00401000", "rva00401000") in got
    assert ("param", "rva00401000", "param_1") in got and ("param", "rva00401000", "a2") in got
    assert ("local", "rva00401000", "iVar3") in got
    assert ("global", "", "g_00A01000") in got


def test_owned_skips_locals_under_od(tree):
    got = {(k, i) for k, _, i, _ in lane_of(tree).owned("Code/Game/Slow.cpp")}
    assert ("param", "param_1") in got and ("local", "iVar1") not in got


@pytest.mark.parametrize("kinds", [{"param"}, {"local"}, {"param", "local"}, {"class"}, {"member"},
                                  {"function"}, {"global"}, {"member", "param"}, set()])
def test_owned_kind_selection_keeps_the_same_candidates(tree, kinds):
    expected = [item for item in lane_of(tree).owned(SOURCE) if item[0] in kinds]
    assert lane_of(tree).owned(SOURCE, kinds=kinds) == expected


def test_scoped_owned_skips_unrelated_type_searches_and_preserves_od_rule(tree, monkeypatch):
    lane = lane_of(tree)
    monkeypatch.setattr(lane, "type_definers", lambda *args: pytest.fail("unrelated type ownership scan"))
    got = {(k, i) for k, _, i, _ in lane.owned(SOURCE, kinds={"param", "local"})}
    assert ("param", "param_1") in got and ("local", "iVar3") in got
    assert not lane.owned("Code/Game/Slow.cpp", kinds={"local"})


def test_selected_type_renames_still_check_other_definers(tree, monkeypatch):
    lane = lane_of(tree)
    calls = []
    monkeypatch.setattr(lane, "type_definers", lambda word: calls.append(word) or [SOURCE, "Code/Other.cpp"])
    assert not lane.owned(SOURCE, kinds={"class", "member"})
    assert calls


def test_local_selection_keeps_parameter_shadowing_deduplication(tree):
    (tree / SOURCE).write_text(BOX.replace("    return iVar3;", "    { int a2 = 0; }\n    return iVar3;"))
    expected = [item for item in lane_of(tree).owned(SOURCE) if item[0] == "local"]
    selected = lane_of(tree).owned(SOURCE, kinds={"local"})
    assert selected == expected
    assert not any(ident == "a2" for _, _, ident, _ in selected)


def test_owned_keeps_donor_spelled_weak_params(tree):
    """WWMath's own Dot_Product(const Vector3 &a, const Vector3 &b): a weak
    spelling the donor wrote is not served; a placeholder always is."""
    donor = tree / "reference/open-bfme-1/game/Libraries/vector3.h"
    donor.parent.mkdir(parents=True)
    donor.write_text("inline float Dot_Product(const Vector3 &a, const Vector3 &b) { return 0; }\n"
                     "x = Dot_Product(v, w);\n")
    src = tree / SOURCE
    src.write_text(BOX + "static inline int Dot_Product(const int &a, const int &w, int param_3)"
                         " { return a + w + param_3; }\n")
    got = {i for _, s, i, _ in lane_of(tree).owned(SOURCE) if s == "Dot_Product"}
    assert got == {"w", "param_3"}      # w appears only in a call, param_3 is a placeholder


def test_owned_ignores_macros_in_class_bodies(tree):
    """A #define/#undef inside a class body (DrawablePhysicsXformTreads.cpp's
    BFME_AI_SLOT(n) slot table) is not a member declaration."""
    src = tree / SOURCE
    src.write_text(BOX + "class Rva00402000View\n{\npublic:\n#define BFME_SLOT(n) virtual void slot##n();\n"
                         "\tBFME_SLOT(00) BFME_SLOT(01)\n\tvirtual int slot02();\n\tint m_x10;\n#undef BFME_SLOT\n};\n"
                         "int use(Rva00402000View *v) { return v->m_x10 + v->m_x10; }\n")
    got = {(k, s, i) for k, s, i, _ in lane_of(tree).owned(SOURCE)}
    assert ("member", "Rva00402000View", "m_x10") in got
    assert not any(i == "BFME_SLOT" for _, _, i in got)


def test_owned_skips_members_of_classes_other_files_view(tree):
    """A placeholder member of a class another file also defines (Object's many
    private views) is renamed across every view: not this file's to decide."""
    other = tree / "Code/Game/Other.cpp"
    other.write_text("struct Rva00401000Box { int m_x2C; int m_count; };\n")
    _git(tree, "add", "-A")
    got = {(k, i) for k, _, i, _ in lane_of(tree).owned(SOURCE)}
    assert ("member", "m_x2C") not in got
    assert ("param", "param_1") in got


def test_problem_rules(tree):
    lane = lane_of(tree)
    words = {"m_count", "rva00401000"}
    assert lane.problem("member", "m_x2C", "health", words) == "members are m_camelCase"
    assert lane.problem("member", "m_x2C", "m_count", words) == "collides with a name already in the file"
    assert lane.problem("class", "X", "boxThing", words) == "types are CamelCase"
    assert lane.problem("param", "a2", "Delta", words) == "params and locals are camelCase"
    assert lane.problem("param", "a2", "tmp", words) == "still a placeholder"
    assert lane.problem("function", "f", "data", words) == "too generic to help a reader"
    assert lane.problem("function", "f", "Rva00401000", words) == "still a placeholder"
    assert lane.problem("function", "f", "int", words) == "not a C++ identifier"
    assert lane.problem("member", "m_x2C", "m_width", words) is None


# ---------------------------------------------------------------- next

def test_next_writes_brief_and_list_only_writes_nothing(tree, capsys):
    args = SimpleNamespace(session="s1", model="claude-opus-5-5", count=1, file=None, list_only=True)
    name_lane.cmd_next(lane_of(tree), args)
    listed = json.loads(capsys.readouterr().out)
    assert {e["file"] for e in listed} <= {SOURCE, "Code/Game/Slow.cpp"} and listed
    assert not (tree / "build/name_lane").exists()
    served = serve(tree, "s1")
    brief = (tree / "build/name_lane/briefs/s1.txt").read_text()
    assert "types CamelCase, members m_camelCase" in brief and "Rva00401000Box::m_x2C" in brief
    assert "int rva00401000(Rva00401000Box *param_1, int a2)" in brief
    assert SOURCE in served["files"]


def add_subsystem_source(tree, subsystem, number):
    rel = f"Code/Game/{subsystem}/Part{number}.cpp"
    word = f"rva{0x00410000 + number * 0x100:08X}"
    path = tree / rel
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes((f"// cl: /O2\nint {word}(int param_1, int a2) {{ int iVar3 = param_1 + a2; return iVar3; }}\n").encode())
    ledger = tree / "reverse/functions.csv"
    ledger.write_bytes(ledger.read_bytes() +
        f"?{word}@@YAHHH@Z,,0x{0x00410000 + number * 0x100:08X},10,{rel},matched,\n".encode())
    _git(tree, "add", rel, "reverse/functions.csv")
    return rel


def subsystem_next(tree, session="group", count=3, **kwargs):
    args = SimpleNamespace(session=session, model="seat-a", count=count, file=None,
                           list_only=False, subsystem=None, mixed=False)
    args.__dict__.update(kwargs)
    name_lane.cmd_next(lane_of(tree), args)
    record = tree / f"build/name_lane/sessions/{session}.json"
    return json.loads(record.read_text()) if record.exists() else None


def test_subsystem_batch_keeps_related_files_and_shared_context(tree):
    ai = [add_subsystem_source(tree, "AI", n) for n in range(3)]
    add_subsystem_source(tree, "Audio", 4)
    record = subsystem_next(tree, subsystem="Code/Game/AI", count=10)
    assert set(record["files"]) == set(ai)  # do not fill with unrelated files
    assert record["subsystem"] == "Code/Game/AI"
    brief = (tree / "build/name_lane/briefs/group.txt").read_text()
    assert brief.startswith("SUBSYSTEM CONTEXT: Code/Game/AI")
    assert "source-directory" in brief and "not canonical naming or TU evidence" in brief
    assert all(rel in brief for rel in ai)


def test_worker_keeps_subsystem_then_moves_on_when_voted_files_are_exhausted(tree):
    ai = [add_subsystem_source(tree, "AI", n) for n in range(3)]
    audio = add_subsystem_source(tree, "Audio", 4)
    first = subsystem_next(tree, "first", count=1, subsystem="Code/Game/AI")
    assert first["subsystem"] == "Code/Game/AI"
    second = subsystem_next(tree, "second", count=1)
    assert second["subsystem"] == "Code/Game/AI"
    lane = lane_of(tree)
    lane.append(name_lane.VOTES, name_lane.VOTE_COLUMNS, [
        {"key": name_lane.key_of(rel, "param", "run", "param_1"), "hash": "x",
         "worker": lane.worker(), "model": "seat-a", "session": "done", "date": "2026-10-28"}
        for rel in ai])
    moved = subsystem_next(tree, "third", count=1)
    assert moved["subsystem"] != "Code/Game/AI"
    assert all(rel not in ai for rel in moved["files"])


def test_related_context_does_not_authorize_answers_for_unserved_files(tree, tmp_path):
    ai = {add_subsystem_source(tree, "AI", n) for n in range(2)}
    record = subsystem_next(tree, count=1, subsystem="Code/Game/AI")
    related = next(iter(ai - set(record["files"])))
    brief = (tree / "build/name_lane/briefs/group.txt").read_text()
    assert related in brief and "read-only related source" in brief
    answer = tmp_path / "outside.json"
    answer.write_text(json.dumps({related: {"madeUp": "name"}}))
    with pytest.raises(SystemExit, match="not served"):
        name_lane.cmd_submit(lane_of(tree), SimpleNamespace(session="group", model="seat-a", answer=str(answer)))
    assert not rows(tree, name_lane.VOTES)


def test_review_priority_still_selects_the_initial_subsystem(tree):
    for n in range(3):
        add_subsystem_source(tree, "AI", n)
    rel = add_subsystem_source(tree, "Audio", 4)
    lane = lane_of(tree)
    lane.append(name_lane.VOTES, name_lane.VOTE_COLUMNS, [{
        "key": name_lane.key_of(rel, "function", "0x00410400", "rva00410400"),
        "hash": "x", "worker": "w-0123456789ab", "model": "other-model",
        "session": "other", "date": "2026-10-28"}])
    record = subsystem_next(tree)
    assert set(record["files"]) == {rel}
    assert record["subsystem"] == "Code/Game/Audio"


@pytest.mark.parametrize("bad", ["../Code/Game", "Code/Game/../Audio", "Code//Game", "vendor", "/Code/Game"])
def test_subsystem_prefix_rejects_ambiguous_paths(tree, bad):
    with pytest.raises(SystemExit):
        subsystem_next(tree, subsystem=bad)


def test_explicit_file_is_respected_and_conflicting_subsystem_is_refused(tree):
    ai = add_subsystem_source(tree, "AI", 1)
    subsystem_next(tree, "first", subsystem="Code/Game/AI")
    record = subsystem_next(tree, "override", file=SOURCE)
    assert set(record["files"]) == {SOURCE}
    with pytest.raises(SystemExit, match="outside subsystem"):
        subsystem_next(tree, "bad", file=ai, subsystem="Code/Game/Audio")


def test_subsystem_list_only_is_read_only_and_mixed_mode_can_span_groups(tree, capsys):
    ai = add_subsystem_source(tree, "AI", 1)
    audio = add_subsystem_source(tree, "Audio", 2)
    subsystem_next(tree, list_only=True, subsystem="Code/Game/AI")
    entries = json.loads(capsys.readouterr().out)
    assert [e["file"] for e in entries] == [ai]
    assert entries[0]["group_basis"] == "source-directory"
    assert not (tree / "build/name_lane").exists()
    record = subsystem_next(tree, count=20, mixed=True)
    assert {ai, audio} <= set(record["files"])
    with pytest.raises(SystemExit, match="cannot be combined"):
        subsystem_next(tree, mixed=True, subsystem="Code/Game/AI")


@pytest.mark.parametrize("stale,provisional", [(False, False), (True, False), (False, True)])
def test_subsystem_uses_only_fresh_nonprovisional_approved_routes(tree, monkeypatch, stale, provisional):
    import tu_map
    monkeypatch.setattr(tu_map, "check_fresh", lambda layout: ["changed"] if stale else [])
    row = {"rva": "0x00401000", "kind": "code", "source": SOURCE, "tu": "Code/Game/AI/Owner.cpp",
           "confidence": "approved", "by": "F", "evidence": "provisional" if provisional else "F=Code/Game/AI/Owner.cpp"}
    def load(root):
        assert not stale, "stale map must not be used for scheduling routes"
        return {0x00401000: [row]}
    monkeypatch.setattr(tu_map, "load", load)
    lane = lane_of(tree)
    expected = ("Code/Game/AI", "approved-tu-directory") if not (stale or provisional) \
        else ("Code/Game", "source-directory")
    assert lane.subsystem(SOURCE) == expected
    if expected[1] == "approved-tu-directory":
        assert set(subsystem_next(tree, subsystem="Code/Game/AI")["files"]) == {SOURCE}


def test_one_approved_row_cannot_route_a_mixed_source(tree, monkeypatch):
    import tu_map
    ledger = tree / "reverse/functions.csv"
    ledger.write_bytes(ledger.read_bytes() +
        f"?other@@YAHXZ,,0x00401100,10,{SOURCE},matched,\n".encode())
    monkeypatch.setattr(tu_map, "check_fresh", lambda layout: [])
    row = {"rva": "0x00401000", "kind": "code", "source": SOURCE, "tu": "Code/Game/AI/Owner.cpp",
           "confidence": "approved", "by": "F", "evidence": "F=Code/Game/AI/Owner.cpp"}
    monkeypatch.setattr(tu_map, "load", lambda root: {0x00401000: [row]})
    assert lane_of(tree).subsystem(SOURCE) == ("Code/Game", "source-directory")


@pytest.mark.usefixtures("claim_coordination")
def test_next_reads_one_claim_snapshot_and_skips_busy_files_before_owned_scan(tree, monkeypatch, capsys):
    from unittest.mock import Mock
    import claims
    free = add_subsystem_source(tree, "AI", 1)
    snapshot = Mock(return_value={claims.file_key(SOURCE)})
    monkeypatch.setattr(claims, "busy_keys", snapshot)
    owned = name_lane.Lane.owned
    def scan(self, rel, *args, **kwargs):
        assert rel != SOURCE, "busy source must not undergo naming analysis"
        return owned(self, rel, *args, **kwargs)
    monkeypatch.setattr(name_lane.Lane, "owned", scan)
    subsystem_next(tree, count=20, list_only=True, subsystem="Code/Game/AI")
    output = capsys.readouterr()
    assert [r["file"] for r in json.loads(output.out)] == [free]
    assert "held by other workers" in output.err
    snapshot.assert_called_once_with(tree)


@pytest.mark.parametrize("kind", ["file", "rva", "class", "persisted"])
@pytest.mark.usefixtures("claim_coordination")
def test_next_uses_standard_expanded_claim_footprints(tree, monkeypatch, capsys, kind):
    import claims
    if kind == "class":
        ledger = tree / "reverse/functions.csv"
        ledger.write_bytes(ledger.read_bytes() +
            f"?run@BusyType@@QAEXXZ,,0x00403000,10,{SOURCE},matched,\n".encode())
    key = {"file": claims.file_key(SOURCE), "rva": 0x00401000,
           "class": claims.class_key("BusyType"), "persisted": 0x00ABCDEF}[kind]
    info = {"owner": "other-worker"}
    if kind == "persisted":
        info["locks"] = [claims.file_key(SOURCE)]
    monkeypatch.setattr(claims, "_blocking_records", lambda root: iter([{key: info}]))
    subsystem_next(tree, file=SOURCE, list_only=True)
    assert json.loads(capsys.readouterr().out) == []
    assert not (tree / "build/name_lane").exists()


@pytest.mark.usefixtures("claim_coordination")
def test_busy_priority_file_cannot_anchor_the_subsystem(tree, monkeypatch):
    import claims
    free = add_subsystem_source(tree, "Audio", 1)
    lane = lane_of(tree)
    lane.append(name_lane.VOTES, name_lane.VOTE_COLUMNS, [{"key": FN_KEY, "hash": "x",
        "worker": "w-0123456789ab", "model": "other-model", "session": "other", "date": "2026-10-28"}])
    monkeypatch.setattr(claims, "busy_keys", lambda root: {claims.file_key(SOURCE),
                         claims.file_key("Code/Game/Slow.cpp")})
    record = subsystem_next(tree)
    assert set(record["files"]) == {free}
    assert record["subsystem"] == "Code/Game/Audio"


@pytest.mark.usefixtures("claim_coordination")
def test_a_new_claim_after_serving_still_blocks_apply(tree, tmp_path, monkeypatch):
    import claims
    monkeypatch.setattr(claims, "busy_keys", lambda root: set())
    vote(tree, tmp_path, "single", {"rva00401000:param_1": "box"})
    before = (tree / SOURCE).read_bytes()
    def refused(*args, **kwargs):
        raise rename.Refusal("claimed by another worker after serving")
    monkeypatch.setattr(rename, "take_claims", refused)
    args = SimpleNamespace(retry_blocked=False, lead=2, min_models=1, claim=True,
                           only_labels=None, key=None, no_batch=False)
    name_lane.cmd_apply(lane_of(tree), args,
        verify=lambda *args: pytest.fail("claim refusal must precede compilation"), checks=no_checks)
    assert (tree / SOURCE).read_bytes() == before
    assert lane_of(tree).state()[PARAM_KEY]["status"] == "blocked"
    assert not rows(tree, "reverse/name_basis.csv")


# ---------------------------------------------------------------- submit

def test_second_reviewer_can_revisit_file_for_a_different_key(tree, tmp_path):
    vote(tree, tmp_path, "first", {"rva00401000": "sumBox"}, worker="first-worker")
    vote(tree, tmp_path, "earlier", {"rva00401000:param_1": "box"}, worker="second-worker")
    be("second-worker")
    record = subsystem_next(tree, "second-review", count=1)
    assert set(record["files"]) == {SOURCE}
    assert record["files"][SOURCE]["items"] == [["function", "0x00401000", "rva00401000", 0x00401000]]
    assert record["files"][SOURCE]["second_review"]
    brief = (tree / "build/name_lane/briefs/second-review.txt").read_text()
    assert "INDEPENDENT SECOND REVIEW" in brief and "sumBox" not in brief
    answer = tmp_path / "review.json"
    answer.write_text(json.dumps({"rva00401000": "sumBox"}))
    name_lane.cmd_submit(lane_of(tree), SimpleNamespace(session="second-review", model="seat-a", answer=str(answer)))
    assert len(lane_of(tree).state()[FN_KEY]["agents"].split(";")) == 2
    assert apply(tree, key=[FN_KEY]) == 0
    assert lane_of(tree).state()[FN_KEY]["status"] == "landed"


def legacy_scoped_disagreement(tree, tmp_path):
    for seat in ("legacy-a", "legacy-b"):
        serve(tree, seat)
    for seat, name in (("legacy-a", "box"), ("legacy-b", "inputBox")):
        be("seat-" + seat)
        answer = tmp_path / (seat + ".json")
        answer.write_text(json.dumps({"rva00401000:param_1": name}))
        name_lane.cmd_submit(lane_of(tree), SimpleNamespace(session=seat, model="claude-opus-5-5", answer=str(answer)))


@pytest.mark.parametrize("second_role,landed", [("source", True), ("destination", False)])
def test_original_workers_can_clarify_without_extra_votes(tree, tmp_path, second_role, landed):
    legacy_scoped_disagreement(tree, tmp_path)
    original = rows(tree, name_lane.VOTES)
    for seat, name, role in (("legacy-a", "box", "source"), ("legacy-b", "inputBox", second_role)):
        be("seat-" + seat)
        record = subsystem_next(tree, "meaning-" + seat, file=SOURCE, meaning_review_only=True)
        assert record["files"][SOURCE]["meaning_review"]
        answer = tmp_path / (seat + "-role.json")
        answer.write_text(json.dumps({"rva00401000:param_1": {"name": name, "meaning": role_descriptor(role=role)}}))
        name_lane.cmd_submit(lane_of(tree), SimpleNamespace(session="meaning-" + seat, model="seat-a", answer=str(answer)))
    assert rows(tree, name_lane.VOTES) == original
    annotations = rows(tree, name_lane.MEANINGS)
    assert len(annotations) == 2
    assert all({k: r[k] for k in name_lane.VOTE_COLUMNS} in original for r in annotations)
    if landed:
        assert name_agreement.record_meaning(lane_of(tree).state()[PARAM_KEY]["id"])
    apply(tree, key=[PARAM_KEY])
    assert (lane_of(tree).state()[PARAM_KEY]["status"] == "landed") == landed


def test_meaning_clarification_cannot_change_the_original_spelling(tree, tmp_path):
    legacy_scoped_disagreement(tree, tmp_path)
    before = rows(tree, name_lane.VOTES)
    be("seat-legacy-a")
    subsystem_next(tree, "clarify", file=SOURCE, meaning_review_only=True)
    answer = tmp_path / "changed-choice.json"
    answer.write_text(json.dumps({"rva00401000:param_1": {"name": "otherBox", "meaning": role_descriptor()}}))
    name_lane.cmd_submit(lane_of(tree), SimpleNamespace(session="clarify", model="seat-a", answer=str(answer)))
    assert rows(tree, name_lane.VOTES) == before
    assert rows(tree, name_lane.MEANINGS) == []


def test_meaning_clarification_cannot_replace_an_existing_descriptor(tree, tmp_path):
    legacy_scoped_disagreement(tree, tmp_path)
    be("seat-legacy-a")
    for session in ("clarify-first", "clarify-second"):
        subsystem_next(tree, session, file=SOURCE, meaning_review_only=True)
    for session, role in (("clarify-first", "source"), ("clarify-second", "destination")):
        answer = tmp_path / (session + ".json")
        answer.write_text(json.dumps({"rva00401000:param_1": {"name": "box", "meaning": role_descriptor(role=role)}}))
        name_lane.cmd_submit(lane_of(tree), SimpleNamespace(session=session, model="seat-a", answer=str(answer)))
    assert len(rows(tree, name_lane.VOTES)) == 2
    annotations = rows(tree, name_lane.MEANINGS)
    assert len(annotations) == 1
    assert annotations[0]["meaning"] == name_agreement.meaning_digest(PARAM_KEY, role_descriptor())


def test_shared_review_only_does_not_serve_own_meaning_clarifications(tree, tmp_path, capsys):
    legacy_scoped_disagreement(tree, tmp_path)
    be("seat-legacy-a")
    capsys.readouterr()
    subsystem_next(tree, "shared-only", review_only=True, list_only=True)
    assert json.loads(capsys.readouterr().out) == []
    with pytest.raises(SystemExit, match="cannot be combined"):
        subsystem_next(tree, "invalid", review_only=True, meaning_review_only=True)


def test_review_only_does_not_fill_with_fresh_names_or_repeat_own_vote(tree, tmp_path, capsys):
    subsystem_next(tree, "empty-review", count=10, review_only=True, list_only=True)
    assert json.loads(capsys.readouterr().out) == []
    vote(tree, tmp_path, "first", {"rva00401000": "sumBox"}, worker="same-worker")
    capsys.readouterr()
    be("same-worker")
    subsystem_next(tree, "self-review", count=10, review_only=True, list_only=True)
    assert json.loads(capsys.readouterr().out) == []


def test_second_review_overrides_affinity_for_fresh_work(tree, tmp_path):
    fresh = add_subsystem_source(tree, "Fresh", 4)
    be("reviewer")
    subsystem_next(tree, "fresh-session", file=fresh)
    vote(tree, tmp_path, "pending", {"rva00401000": "sumBox"}, worker="other-worker")
    be("reviewer")
    record = subsystem_next(tree, "finish-pending", count=1)
    assert set(record["files"]) == {SOURCE}
    assert record["files"][SOURCE]["second_review"]


def test_busy_second_review_is_not_served(tree, tmp_path, monkeypatch, capsys):
    import claims
    vote(tree, tmp_path, "pending", {"rva00401000": "sumBox"}, worker="other-worker")
    capsys.readouterr()
    be("reviewer")
    monkeypatch.setattr(claims, "busy_keys", lambda root: {claims.file_key(SOURCE)})
    subsystem_next(tree, "busy-review", count=10, review_only=True, list_only=True)
    assert json.loads(capsys.readouterr().out) == []

def test_two_sessions_agree(tree, tmp_path):
    assert vote(tree, tmp_path, "s1", {"Rva00401000Box::m_x2C": "m_boxWidth", "rva00401000": "sumBox"}) == 0
    votes = (tree / name_lane.VOTES).read_text()
    assert "m_boxWidth" not in votes and "sumBox" not in votes            # hashes only
    assert not rows(tree, name_lane.AGREED)
    vote(tree, tmp_path, "s2", {"Rva00401000Box::m_x2C": "m_widthBox", "rva00401000": "skip"},
         model="gpt-6.1-sol")
    agreed = rows(tree, name_lane.AGREED)
    assert [(r["key"], r["new"], r["status"]) for r in agreed] == [(MEMBER_KEY, "m_widthBox", "agreed")]
    be("seat-s1")
    w1 = name_agreement.worker_identity()
    be("seat-s2")
    w2 = name_agreement.worker_identity()
    assert set(agreed[0]["agents"].split(";")) == {f"{w1}@claude-opus-5-5", f"{w2}@gpt-6.1-sol"}
    assert agreed[0]["id"].startswith("nl-")
    assert all(name_agreement.WORKER.fullmatch(r["worker"]) for r in rows(tree, name_lane.VOTES))
    assert agreed[0]["old"] == "m_x2C" and agreed[0]["kind"] == "member"


def test_disagreement_and_tie(tree, tmp_path):
    vote(tree, tmp_path, "s1", {"rva00401000": "sumBox"})
    vote(tree, tmp_path, "s2", {"rva00401000": "addBoxWidth"})
    vote(tree, tmp_path, "s3", {"rva00401000": "sumBox"})                 # 2 vs 1: lead 1, not enough
    assert not rows(tree, name_lane.AGREED)
    vote(tree, tmp_path, "s4", {"rva00401000": "boxSum"})                 # 3 vs 1
    agreed = rows(tree, name_lane.AGREED)
    assert [(r["key"], r["new"]) for r in agreed] == [(FN_KEY, "boxSum")]
    assert agreed[0]["rva"] == "0x00401000"


def test_session_votes_once_and_bad_names_rejected(tree, tmp_path, capsys):
    vote(tree, tmp_path, "s1", {"rva00401000": "sumBox", "rva00401000:a2": "Delta"})
    out = capsys.readouterr().out
    assert "params and locals are camelCase" in out
    serve_twice = SimpleNamespace(session="s1", model="claude-opus-5-5", count=1, file=SOURCE, list_only=False)
    name_lane.cmd_next(lane_of(tree), serve_twice)
    assert "no file is left" in capsys.readouterr().out
    with pytest.raises(SystemExit):
        vote(tree, tmp_path, "s2", {"nonexistent": "x"})


# ---------------------------------------------------------------- apply

def agree_on(tree, tmp_path, answers):
    vote(tree, tmp_path, "s1", answers)
    # Uncontested scoped names already have approval after the first proposal.
    approved = {name_lane.answer_key(*name_lane.split_key(k)[1:]): row
                for k, row in lane_of(tree).state().items()}
    pending = {key: value for key, value in answers.items() if key not in approved}
    if pending:
        vote(tree, tmp_path, "s2", pending, model="gpt-6.1-sol")


def test_apply_lands_through_rename(tree, tmp_path):
    agree_on(tree, tmp_path, {"Rva00401000Box::m_x2C": "m_width", "rva00401000": "sumBox",
                              "rva00401000:param_1": "box"})
    assert apply(tree) == 0
    text = (tree / SOURCE).read_text()
    assert "int m_width;" in text and "int sumBox(Rva00401000Box *box, int a2)" in text
    assert "box->m_width + a2" in text
    states = name_lane.Lane(tree).state()
    assert {states[k]["status"] for k in (FN_KEY, MEMBER_KEY, PARAM_KEY)} == {"landed"}
    basis = [b for b in rows(tree, "reverse/name_basis.csv") if b["kind"] != "carry"]
    assert {b["basis"] for b in basis} == {"inferred"} and len(basis) == 3
    assert {b["evidence"] for b in basis} == {f"agree:{states[k]['id']}" for k in (FN_KEY, MEMBER_KEY, PARAM_KEY)}
    assert any(r["name"] == "?sumBox@@YAHPAURva00401000Box@@H@Z" for r in rows(tree, "reverse/functions.csv"))
    assert any(r["name"] == FN for r in rows(tree, "reverse/deleted_rows.csv"))


def test_single_scoped_proposal_lands_and_disputes_through_engine(tree, tmp_path):
    vote(tree, tmp_path, "single", {"rva00401000:param_1": "box"})
    state = lane_of(tree).state()[PARAM_KEY]
    assert state["status"] == "agreed"
    assert state["detail"].startswith("single-worker scoped approval:")
    assert len(rows(tree, name_lane.VOTES)) == 1
    assert apply(tree) == 0
    assert "Rva00401000Box *box" in (tree / SOURCE).read_text()
    assert lane_of(tree).state()[PARAM_KEY]["detail"].startswith("single-worker scoped approval:")
    args = SimpleNamespace(keys=[PARAM_KEY], reason="the proposed role was wrong", claim=False)
    name_lane.cmd_dispute(lane_of(tree), args, verify=ok_verify, checks=no_checks)
    assert "Rva00401000Box *param_1" in (tree / SOURCE).read_text()
    assert lane_of(tree).state()[PARAM_KEY]["status"] == "disputed"


def test_semantic_aliases_land_through_engine_and_the_meaning_is_revocable(tree, tmp_path):
    # Both briefs are served blind before either proposal creates an approval.
    for seat in ("first", "second"):
        serve(tree, seat)
    for seat, name in (("first", "box"), ("second", "inputBox")):
        be("seat-" + seat)
        answer = tmp_path / (seat + "-meaning.json")
        answer.write_text(json.dumps({"rva00401000:param_1": {"name": name, "meaning": role_descriptor()}}))
        name_lane.cmd_submit(lane_of(tree), SimpleNamespace(session=seat, model="claude-opus-5-5", answer=str(answer)))
    state = lane_of(tree).state()[PARAM_KEY]
    assert name_agreement.record_meaning(state["id"])
    assert len(rows(tree, name_lane.MEANINGS)) == 2
    assert "source" not in (tree / name_lane.MEANINGS).read_text()  # role text stays blind
    assert apply(tree) == 0
    landed = lane_of(tree).state()[PARAM_KEY]
    assert landed["status"] == "landed" and len(landed["agents"].split(";")) == 2
    assert "Rva00401000Box *box" in (tree / SOURCE).read_text()
    args = SimpleNamespace(keys=[PARAM_KEY], reason="not a box input", claim=False)
    name_lane.cmd_dispute(lane_of(tree), args, verify=ok_verify, checks=no_checks)
    assert "Rva00401000Box *param_1" in (tree / SOURCE).read_text()
    assert "~meaning:" + name_agreement.record_meaning(state["id"]) in lane_of(tree).disputed()[PARAM_KEY]


def test_forged_meaning_record_without_annotations_cannot_authorize_alias(tree, tmp_path):
    agree_on(tree, tmp_path, {"rva00401000:param_1": "box"})
    state = lane_of(tree).state()[PARAM_KEY]
    forged = dict(state, id=state["id"] + "-m" + "0" * 24)
    lane_of(tree).append(name_lane.AGREED, name_lane.AGREED_COLUMNS, [forged])
    with pytest.raises(rename.Refusal, match="agreement record"):
        rename.plan_rename("param", ctx=rename.Context(tree, object_scan=False), source=SOURCE,
            function="rva00401000", name="param_1", new="box", basis="inferred", evidence="agree:" + forged["id"])


def test_late_rival_stops_single_proposal_before_source_analysis(tree, tmp_path):
    vote(tree, tmp_path, "single", {"rva00401000:param_1": "box"})
    lane = lane_of(tree)
    lane.append(name_lane.VOTES, name_lane.VOTE_COLUMNS, [{"key": PARAM_KEY,
        "hash": name_lane.digest(PARAM_KEY, "destination"), "worker": "w-abcdef012345",
        "model": "seat-b", "session": "prepared-before-first-submission", "date": "2026-10-28"}])
    before = (tree / SOURCE).read_bytes()
    apply(tree, verify=lambda *args: pytest.fail("a contested single vote must not reach verification"))
    assert (tree / SOURCE).read_bytes() == before
    assert lane_of(tree).state()[PARAM_KEY]["status"] == "agreed"
    # A new reviewer can resolve the contest instead of leaving an unservable
    # pending approval. Three proposals beat the original one by default lead 2.
    for seat in ("review-1", "review-2"):
        vote(tree, tmp_path, seat, {"rva00401000:param_1": "destination"})
    assert lane_of(tree).state()[PARAM_KEY]["new"] == "destination"
    assert apply(tree) == 0
    assert "Rva00401000Box *destination" in (tree / SOURCE).read_text()


def test_single_scoped_proposal_keeps_byte_verification_rollback(tree, tmp_path):
    vote(tree, tmp_path, "single", {"rva00401000:param_1": "box"})
    before = (tree / SOURCE).read_bytes()
    builds = []
    def refuse(ctx, sources):
        builds.append(sources)
        return False
    apply(tree, verify=refuse)
    assert builds == [[SOURCE]]
    assert (tree / SOURCE).read_bytes() == before
    assert lane_of(tree).state()[PARAM_KEY]["status"] == "blocked"
    assert not rows(tree, "reverse/name_basis.csv")


def test_local_apply_does_not_search_unselected_types(tree, tmp_path, monkeypatch):
    agree_on(tree, tmp_path, {"rva00401000:iVar3": "sum"})
    monkeypatch.setattr(name_lane.Lane, "type_definers",
                        lambda *args: pytest.fail("local apply must not scan unselected class/member owners"))
    apply(tree)
    assert "int sum = param_1->m_x2C + a2;" in (tree / SOURCE).read_text()
    assert {row["status"] for row in lane_of(tree).state().values()} == {"landed"}


# ---------------------------------------------------------------- apply --only-labels

MEMBER_ANSWER = {"Rva00401000Box::m_x2C": "m_width"}
FN_ANSWER = {"rva00401000": "sumBox"}


def voters(tree, tmp_path, key_answer, labels, tag="v"):
    """One seat per label votes the same answers (a worker per label and tag)."""
    for i, label in enumerate(labels):
        vote(tree, tmp_path, f"{tag}{i}", key_answer, label)


def agreed_keys(tree):
    return {r["key"] for r in rows(tree, name_lane.AGREED)}


def test_only_labels_applies_all_own_voters(tree, tmp_path, capsys):
    voters(tree, tmp_path, MEMBER_ANSWER, ["seat-a", "seat-b"])
    assert apply(tree, only_labels="seat-a,seat-b") == 0
    assert "int m_width;" in (tree / SOURCE).read_text()
    assert name_lane.Lane(tree).state()[MEMBER_KEY]["status"] == "landed"
    assert "0 key(s) with a voter outside" in capsys.readouterr().out


def test_only_labels_skips_mixed_and_foreign_voters_untouched(tree, tmp_path, capsys, monkeypatch):
    voters(tree, tmp_path, MEMBER_ANSWER, ["seat-a", "other-x"])       # one outside voter
    voters(tree, tmp_path, FN_ANSWER, ["other-x", "other-y"], tag="w")  # nobody of ours
    assert agreed_keys(tree) == {MEMBER_KEY, FN_KEY}
    before_text, before_agreed = (tree / SOURCE).read_bytes(), (tree / name_lane.AGREED).read_bytes()
    def unexpected_source_read(*args, **kwargs):
        pytest.fail("excluded agreements must not read or analyze source files")

    with monkeypatch.context() as patch:
        patch.setattr(name_lane.Lane, "text", unexpected_source_read)
        patch.setattr(name_lane.Lane, "owned", unexpected_source_read)
        patch.setattr(name_lane.Lane, "servable", unexpected_source_read)
        assert apply(tree, only_labels="seat-a, seat-b") == 0
    assert (tree / SOURCE).read_bytes() == before_text
    assert (tree / name_lane.AGREED).read_bytes() == before_agreed      # nothing written: no blocked, no stale
    assert {k: r["status"] for k, r in name_lane.Lane(tree).state().items()} == {MEMBER_KEY: "agreed",
                                                                                  FN_KEY: "agreed"}
    assert "2 key(s) with a voter outside" in capsys.readouterr().out
    assert not rows(tree, "reverse/name_basis.csv")
    # whoever applies without the filter still lands them
    apply(tree)
    assert {r["status"] for r in name_lane.Lane(tree).state().values()} == {"landed"}


def test_only_labels_lands_own_key_and_leaves_the_other(tree, tmp_path):
    voters(tree, tmp_path, MEMBER_ANSWER, ["seat-a", "seat-b"])
    voters(tree, tmp_path, FN_ANSWER, ["seat-a", "other-x"], tag="w")
    apply(tree, only_labels="seat-a,seat-b")
    state = name_lane.Lane(tree).state()
    assert state[MEMBER_KEY]["status"] == "landed" and state[FN_KEY]["status"] == "agreed"
    assert "int sumBox(" not in (tree / SOURCE).read_text()


def test_apply_exact_key_leaves_other_agreements_untouched(tree, tmp_path):
    voters(tree, tmp_path, MEMBER_ANSWER, ["seat-a", "seat-b"])
    voters(tree, tmp_path, FN_ANSWER, ["seat-a", "seat-b"], tag="w")
    apply(tree, key=[MEMBER_KEY])
    state = name_lane.Lane(tree).state()
    assert state[MEMBER_KEY]["status"] == "landed"
    assert state[FN_KEY]["status"] == "agreed"
    assert "int m_width;" in (tree / SOURCE).read_text()
    assert "int sumBox(" not in (tree / SOURCE).read_text()


def test_only_labels_skips_a_lead_that_rests_on_an_outside_voter(tree, tmp_path):
    # one seat of ours and two outside voters agree against a rival seat of ours: 3 vs 1 wins only with them
    voters(tree, tmp_path, FN_ANSWER, ["seat-a"], tag="a")
    vote(tree, tmp_path, "r0", {"rva00401000": "addBoxWidth"}, "seat-b")
    voters(tree, tmp_path, FN_ANSWER, ["other-x", "other-y"], tag="o")   # 3 vs 1: wins at lead 2
    assert agreed_keys(tree) == {FN_KEY}
    apply(tree, only_labels="seat-a,seat-b")
    assert name_lane.Lane(tree).state()[FN_KEY]["status"] == "agreed"
    assert "sumBox" not in (tree / SOURCE).read_text()


def test_only_labels_outside_rival_still_counts_against_lead(tree, tmp_path, capsys, monkeypatch):
    vote(tree, tmp_path, "r0", {"rva00401000": "addBoxWidth"}, "other-x")
    voters(tree, tmp_path, FN_ANSWER, ["seat-a", "seat-b"], tag="a")
    assert not rows(tree, name_lane.AGREED)                                     # 2 vs 1 is not a win at lead 2
    voters(tree, tmp_path, FN_ANSWER, ["seat-a"], tag="c")                      # a third own worker: 3 vs 1
    assert agreed_keys(tree) == {FN_KEY}
    # a late outside voter for the rival makes the lead 3 vs 2: the own-only agreement no longer wins
    lane_of(tree).append(name_lane.VOTES, name_lane.VOTE_COLUMNS, [
        {"key": FN_KEY, "hash": name_lane.digest(FN_KEY, "addBoxWidth"), "model": "other-y", "session": "late",
         "worker": "w-0123456789ab", "date": "2026-10-24"}])
    def unexpected_source_read(*args, **kwargs):
        pytest.fail("agreements without a winning vote must not analyze source files")

    monkeypatch.setattr(name_lane.Lane, "text", unexpected_source_read)
    monkeypatch.setattr(name_lane.Lane, "owned", unexpected_source_read)
    monkeypatch.setattr(name_lane.Lane, "servable", unexpected_source_read)
    apply(tree, only_labels="seat-a,seat-b")
    assert "votes no longer agree" in capsys.readouterr().out
    assert name_lane.Lane(tree).state()[FN_KEY]["status"] == "agreed"


def test_only_labels_with_retry_blocked(tree, tmp_path):
    voters(tree, tmp_path, MEMBER_ANSWER, ["seat-a", "seat-b"])
    voters(tree, tmp_path, FN_ANSWER, ["seat-a", "other-x"], tag="w")
    apply(tree, verify=lambda ctx, sources: False)                              # both blocked
    assert {r["status"] for r in name_lane.Lane(tree).state().values()} == {"blocked"}
    count = len(rows(tree, name_lane.AGREED))
    apply(tree, only_labels="seat-a,seat-b")                                    # no retry: nothing waiting
    assert len(rows(tree, name_lane.AGREED)) == count
    apply(tree, retry_blocked=True, only_labels="seat-a,seat-b")
    state = name_lane.Lane(tree).state()
    assert state[MEMBER_KEY]["status"] == "landed" and state[FN_KEY]["status"] == "blocked"
    assert len(rows(tree, name_lane.AGREED)) == count + 1                       # the outside key got no row


def test_only_labels_needs_labels(tree, tmp_path):
    voters(tree, tmp_path, MEMBER_ANSWER, ["seat-a", "seat-b"])
    with pytest.raises(SystemExit):
        apply(tree, only_labels=" , ")


def test_status_counts_waiting_keys_the_filter_selects(tree, tmp_path, capsys):
    voters(tree, tmp_path, MEMBER_ANSWER, ["seat-a", "seat-b"])
    voters(tree, tmp_path, FN_ANSWER, ["seat-a", "other-x"], tag="w")
    args = SimpleNamespace(metric=False, only_labels="seat-a,seat-b", lead=2, min_models=1)
    assert name_lane.cmd_status(lane_of(tree), args) == 0
    out = capsys.readouterr().out
    assert "waiting 2" in out and "would select 1 of 2 waiting" in out
    args.only_labels = None
    name_lane.cmd_status(lane_of(tree), args)
    assert "would select" not in capsys.readouterr().out


def test_default_apply_still_lands_other_contributors_agreements(tree, tmp_path):
    voters(tree, tmp_path, MEMBER_ANSWER, ["other-x", "other-y"])
    apply(tree)
    assert name_lane.Lane(tree).state()[MEMBER_KEY]["status"] == "landed"


def test_cli_parses_only_labels():
    import argparse
    seen = {}
    lane = SimpleNamespace()
    orig_apply, orig_status = name_lane.cmd_apply, name_lane.cmd_status
    try:
        name_lane.cmd_apply = lambda l, a: seen.setdefault("apply", a) and 0
        name_lane.cmd_status = lambda l, a: seen.setdefault("status", a) and 0
        name_lane.main(["apply", "--only-labels", "seat-a,seat-b", "--retry-blocked",
                        "--key", MEMBER_KEY, "--key", FN_KEY, "--no-batch"], lane=lane)
        name_lane.main(["status", "--only-labels", "seat-a"], lane=lane)
        name_lane.main(["apply"], lane=lane)
    finally:
        name_lane.cmd_apply, name_lane.cmd_status = orig_apply, orig_status
    assert seen["apply"].only_labels == "seat-a,seat-b" and seen["apply"].retry_blocked
    assert seen["apply"].key == [MEMBER_KEY, FN_KEY]
    assert seen["apply"].no_batch
    assert seen["status"].only_labels == "seat-a" and seen["status"].lead == 2 and seen["status"].min_models == 1


def test_apply_blocked_restores(tree, tmp_path):
    agree_on(tree, tmp_path, {"Rva00401000Box::m_x2C": "m_width"})
    before = (tree / SOURCE).read_bytes()
    apply(tree, verify=lambda ctx, sources: False)
    assert (tree / SOURCE).read_bytes() == before
    assert name_lane.Lane(tree).state()[MEMBER_KEY]["status"] == "blocked"
    apply(tree, retry_blocked=True)
    assert name_lane.Lane(tree).state()[MEMBER_KEY]["status"] == "landed"


def test_apply_stale_when_placeholder_gone(tree, tmp_path):
    agree_on(tree, tmp_path, {"Rva00401000Box::m_x2C": "m_width"})
    path = tree / SOURCE
    path.write_text(path.read_text().replace("m_x2C", "m_height"))
    apply(tree)
    row = name_lane.Lane(tree).state()[MEMBER_KEY]
    assert row["status"] == "stale" and row["agents"] == ""


def test_rename_refuses_without_lane_record(tree):
    with pytest.raises(rename.Refusal):
        rename.plan_rename("member", ctx=rename.Context(tree, object_scan=False), cls="Rva00401000Box",
                           member="m_x2C", new="m_width", basis="inferred", evidence="agree:nl-000000000000")


# ---------------------------------------------------------------- dispute

def test_dispute_reverts_and_refuses_spelling(tree, tmp_path, capsys):
    agree_on(tree, tmp_path, {"Rva00401000Box::m_x2C": "m_width", "rva00401000": "sumBox"})
    apply(tree)
    args = SimpleNamespace(keys=[MEMBER_KEY, FN_KEY], reason="offset 0x2C is the box height", claim=False)
    assert name_lane.cmd_dispute(lane_of(tree), args, verify=ok_verify, checks=no_checks) == 0
    text = (tree / SOURCE).read_text()
    assert "int m_x2C;" in text and "int rva00401000(" in text
    lane = name_lane.Lane(tree)
    state = lane.state()
    assert state[MEMBER_KEY]["status"] == "disputed" and state[MEMBER_KEY]["agents"] == ""
    assert "offset 0x2C" in state[MEMBER_KEY]["detail"]
    assert any(r["name"] == FN for r in rows(tree, "reverse/functions.csv"))
    # the record no longer authorises a rename, and the spelling is refused for the key
    with pytest.raises(rename.Refusal):
        rename.plan_rename("member", ctx=rename.Context(tree, object_scan=False), cls="Rva00401000Box",
                           member="m_x2C", new="m_width", basis="inferred",
                           evidence=f"agree:{state[MEMBER_KEY]['id']}")
    capsys.readouterr()
    vote(tree, tmp_path, "s3", {"Rva00401000Box::m_x2C": "m_width"})
    assert "disputed for this key" in capsys.readouterr().out
    # a different name can still be agreed and landed for the key
    vote(tree, tmp_path, "s4", {"Rva00401000Box::m_x2C": "m_height"})
    vote(tree, tmp_path, "s5", {"Rva00401000Box::m_x2C": "m_height"}, model="gpt-6.1-sol")
    assert name_lane.Lane(tree).state()[MEMBER_KEY]["status"] == "agreed"
    apply(tree)
    assert "int m_height;" in (tree / SOURCE).read_text()
    assert name_lane.Lane(tree).state()[MEMBER_KEY]["new"] == "m_height"
    # the reverting override is gone again
    with pytest.raises(rename.Refusal):
        rename.check_new_identifier("m_x2C", "member")


def test_dispute_needs_landed(tree):
    args = SimpleNamespace(keys=[MEMBER_KEY], reason="x", claim=False)
    with pytest.raises(SystemExit):
        name_lane.cmd_dispute(lane_of(tree), args)


# ---------------------------------------------------------------- review fix-2: one worker, one vote

def test_one_worker_under_two_session_labels_is_one_vote(tree, tmp_path, capsys):
    """Finding 1: `--session` is a label; the worker identity decides who voted."""
    vote(tree, tmp_path, "s1", {"rva00401000": "sumBox"}, worker="seat-same")
    capsys.readouterr()
    args = SimpleNamespace(session="s2", model="gpt-6.1-sol", count=1, file=SOURCE, list_only=False)
    be("seat-same")
    name_lane.cmd_next(lane_of(tree), args)
    assert "no file is left" in capsys.readouterr().out          # never served again, any label
    assert not rows(tree, name_lane.AGREED)


def test_one_worker_cannot_vote_twice_through_two_served_sessions(tree, tmp_path, capsys):
    serve(tree, "s1", worker="seat-same")
    serve(tree, "s2", worker="seat-same")                         # served before either voted
    for session in ("s1", "s2"):
        answer = tmp_path / f"a-{session}.json"
        answer.write_text(json.dumps({"rva00401000": "sumBox"}))
        be("seat-same")
        name_lane.cmd_submit(lane_of(tree), SimpleNamespace(answer=str(answer), session=session,
                                                            model="claude-opus-5-5"))
    assert "this worker already voted" in capsys.readouterr().out
    assert len(rows(tree, name_lane.VOTES)) == 1 and not rows(tree, name_lane.AGREED)


def test_submit_from_another_worker_is_refused(tree, tmp_path):
    serve(tree, "s1", worker="seat-a")
    answer = tmp_path / "a.json"
    answer.write_text(json.dumps({"rva00401000": "sumBox"}))
    be("seat-b")
    with pytest.raises(SystemExit, match="another worker"):
        name_lane.cmd_submit(lane_of(tree), SimpleNamespace(answer=str(answer), session="s1",
                                                            model="claude-opus-5-5"))
    be("seat-b")
    with pytest.raises(SystemExit, match="another worker"):
        name_lane.cmd_next(lane_of(tree), SimpleNamespace(session="s1", model="claude-opus-5-5", count=1,
                                                          file=SOURCE, list_only=False))


def test_worker_identity_sources(monkeypatch):
    monkeypatch.delenv("BFME_CLAIM_OWNER", raising=False)
    monkeypatch.delenv("BFME_RUN_ID", raising=False)
    monkeypatch.setenv("CLAUDE_CODE_SESSION_ID", "abc")
    a = name_agreement.worker_identity()
    monkeypatch.setenv("CLAUDE_CODE_SESSION_ID", "abd")
    assert name_agreement.worker_identity() != a
    monkeypatch.setenv("BFME_CLAIM_OWNER", "seat-1")           # an orchestrator's seat wins
    b = name_agreement.worker_identity()
    monkeypatch.setenv("CLAUDE_CODE_SESSION_ID", "abc")
    assert name_agreement.worker_identity() == b and name_agreement.WORKER.fullmatch(b)
    assert "seat-1" not in b


def forge_agreement(tree, rid="nl-forged00000", agents="a@m;b@m"):
    with (tree / name_lane.AGREED).open("a") as handle:
        if handle.tell() == 0:
            handle.write(",".join(name_lane.AGREED_COLUMNS) + "\n")
        handle.write(f"{rid},member,m_x2C,m_width,,{agents},{MEMBER_KEY},agreed,forged\n")
    return f"agree:{rid}"


def plan_member(tree, evidence):
    return rename.plan_rename("member", ctx=rename.Context(tree, object_scan=False), cls="Rva00401000Box",
                              member="m_x2C", new="m_width", basis="inferred", evidence=evidence)


def add_vote(tree, name, worker, model="m"):
    with (tree / name_lane.VOTES).open("a") as handle:
        handle.write(f"{MEMBER_KEY},{name_agreement.digest(MEMBER_KEY, name)},{model},x,{worker},2026-10-21\n")


def test_rename_recomputes_agreement_from_votes(tree, tmp_path):
    """Finding 1: a hand-written agreed row with two agent strings authorises nothing."""
    with pytest.raises(rename.Refusal, match="0 distinct worker"):
        plan_member(tree, forge_agreement(tree, "nl-forged00001"))


def test_rename_counts_only_workers_with_an_identity(tree, tmp_path):
    vote(tree, tmp_path, "s1", {"Rva00401000Box::m_x2C": "m_width"})
    add_vote(tree, "m_width", "")                    # no worker id: counts for nothing
    add_vote(tree, "m_width", "bogus")
    with pytest.raises(rename.Refusal, match="1 distinct worker"):
        plan_member(tree, forge_agreement(tree))
    add_vote(tree, "m_width", "w-0123456789ab")      # a second worker's vote carries it
    assert plan_member(tree, forge_agreement(tree)).basis == "inferred"


def test_rename_refuses_a_tied_rival(tree, tmp_path):
    vote(tree, tmp_path, "s1", {"Rva00401000Box::m_x2C": "m_width"})
    vote(tree, tmp_path, "s2", {"Rva00401000Box::m_x2C": "m_width"})
    rid = name_lane.Lane(tree).state()[MEMBER_KEY]["id"]
    assert plan_member(tree, f"agree:{rid}").basis == "inferred"
    add_vote(tree, "m_height", "w-00000000000a")
    add_vote(tree, "m_height", "w-00000000000b")
    with pytest.raises(rename.Refusal, match="rival spelling has 2"):
        plan_member(tree, f"agree:{rid}")


# ---------------------------------------------------------------- review fix-2: dispute through the engine

def test_dispute_uses_the_engine_and_is_append_only(tree, tmp_path):
    """Finding 2: the dispute is rename.revert's exact inverse, recorded as
    basis `restored`; nothing monkeypatches rename.py."""
    agree_on(tree, tmp_path, {"rva00401000": "sumBox"})
    apply(tree)
    checks = (rename.check_new_identifier, rename.check_basis)
    before = rows(tree, "reverse/name_basis.csv")
    args = SimpleNamespace(keys=[FN_KEY], reason="it subtracts", claim=False)
    assert name_lane.cmd_dispute(lane_of(tree), args, verify=ok_verify, checks=no_checks) == 0
    assert (rename.check_new_identifier, rename.check_basis) == checks
    after = rows(tree, "reverse/name_basis.csv")
    assert after[:len(before)] == before                          # append-only
    restored = after[-1]
    assert (restored["kind"], restored["basis"]) == ("function", "restored")
    assert restored["old"] == "?sumBox@@YAHPAURva00401000Box@@H@Z" and restored["new"] == FN
    assert restored["evidence"].startswith("revert:nl-") and "it subtracts" in restored["evidence"]
    deleted = rows(tree, "reverse/deleted_rows.csv")
    assert not any(r["name"] == FN for r in deleted)               # the landing's tombstone is lifted
    assert any(r["name"] == "?sumBox@@YAHPAURva00401000Box@@H@Z" and "(restored)" in r["reason"]
               for r in deleted)
    ctx = rename.Context(tree, object_scan=False)
    assert rename.check_renames(ctx, rename.name_basis_rows(ctx)) == []
    # a union merge that brings the lifted line back is honoured by rename.py and reported by check
    with (tree / "reverse/deleted_rows.csv").open("a") as handle:
        handle.write(f'{FN},0x00401000,"Renamed to ?sumBox@@YAHPAURva00401000Box@@H@Z by tools/rename.py '
                     f'(inferred)"\n')
    ctx = rename.Context(tree, object_scan=False)
    assert (FN, 0x00401000) not in rename._tombstones(ctx)
    assert any("again" in p for p in rename.check_renames(ctx, rename.name_basis_rows(ctx)))


def test_revert_refuses_anything_but_the_exact_inverse(tree, tmp_path):
    agree_on(tree, tmp_path, {"rva00401000": "sumBox", "Rva00401000Box::m_x2C": "m_width"})
    apply(tree)
    rid = name_lane.Lane(tree).state()[FN_KEY]["id"]
    ctx = rename.Context(tree, object_scan=False)
    with pytest.raises(rename.Refusal, match="not the exact inverse"):
        rename.plan_rename("function", ctx=ctx, rva=0x00401000, new="rva00401999", basis="restored",
                           evidence=f"revert:{rid} wrong")
    with pytest.raises(rename.Refusal, match="reason"):
        rename.plan_rename("function", ctx=ctx, rva=0x00401000, new="rva00401000", basis="restored",
                           evidence=f"revert:{rid}")
    with pytest.raises(rename.Refusal, match="no inferred rename"):
        rename.revert(ctx, "nl-nothing", "because", claim=False, dry_run=True)
    with pytest.raises(rename.Refusal, match="placeholder"):     # restoring is not a back door
        rename.plan_rename("function", ctx=ctx, rva=0x00401000, new="rva00401000", basis="inferred",
                           evidence=f"agree:{rid}")
    rename.revert(ctx, rid, "because", claim=False, verify=ok_verify, checks=no_checks)
    with pytest.raises(rename.Refusal, match="already reverted"):
        rename.revert(rename.Context(tree, object_scan=False), rid, "again", claim=False, dry_run=True)


def test_revert_cli_dry_run(tree, tmp_path, capsys):
    agree_on(tree, tmp_path, {"Rva00401000Box::m_x2C": "m_width"})
    apply(tree)
    rid = name_lane.Lane(tree).state()[MEMBER_KEY]["id"]
    before = (tree / SOURCE).read_bytes()
    assert rename.main(["revert", "--record", f"agree:{rid}", "--reason", "it is the height", "--dry-run",
                        "--no-claim", "--root", str(tree)]) == 0
    assert "Rename Rva00401000Box::m_width to m_x2C (restored)" in capsys.readouterr().out
    assert (tree / SOURCE).read_bytes() == before


# ---------------------------------------------------------------- scoped batches

BATCH_ANSWERS = {"rva00401000:param_1": "box", "rva00401000:a2": "increment",
                 "rva00401000:iVar3": "sum"}


def batch_requests(tree):
    requests = []
    for key, row in lane_of(tree).state().items():
        rel, kind, scope, ident = name_lane.split_key(key)
        requests.append((kind, dict(basis="inferred", evidence=f"agree:{row['id']}",
                                   **name_lane.rename_kwargs(kind, scope, ident, row["new"], row["rva"], rel))))
    return requests


def test_scoped_batch_builds_combined_result_once(tree, tmp_path):
    agree_on(tree, tmp_path, BATCH_ANSWERS)
    builds, checked = [], []

    def verify(ctx, sources):
        builds.append(sources)
        text = (tree / SOURCE).read_text()
        assert "int sum = box->m_x2C + increment;" in text
        assert len(rows(tree, rename.NAME_BASIS)) == 3
        return True

    def checks(ctx, plan):
        checked.append(set(plan.written()))
        return []

    apply(tree, verify=verify, checks=checks)
    assert builds == [[SOURCE]]
    assert checked == [set(), {SOURCE, rename.NAME_BASIS, rename.NAME_BINDINGS}]
    assert {r["status"] for r in lane_of(tree).state().values()} == {"landed"}
    assert not list((tree / rename.JOURNAL_DIR).glob("*.json"))


def test_scoped_batch_opt_out_keeps_per_name_verification(tree, tmp_path):
    agree_on(tree, tmp_path, BATCH_ANSWERS)
    builds = []
    apply(tree, no_batch=True, verify=lambda ctx, sources: builds.append(sources) or True)
    assert builds == [[SOURCE]] * 3
    assert {r["status"] for r in lane_of(tree).state().values()} == {"landed"}


def test_scoped_batch_precedes_enclosing_function_rename(tree, tmp_path):
    agree_on(tree, tmp_path, dict(BATCH_ANSWERS, rva00401000="sumBox"))
    builds = []
    apply(tree, verify=lambda ctx, sources: builds.append(sources) or True)
    text = (tree / SOURCE).read_text()
    assert "int sumBox(Rva00401000Box *box, int increment)" in text
    assert "int sum = box->m_x2C + increment;" in text
    assert len(builds) == 2                         # scoped batch, then ordinary symbol rename
    assert {r["status"] for r in lane_of(tree).state().values()} == {"landed"}


def test_failed_scoped_batch_restores_before_individual_fallback(tree, tmp_path):
    agree_on(tree, tmp_path, BATCH_ANSWERS)
    builds = []

    def verify(ctx, sources):
        text = (tree / SOURCE).read_text()
        builds.append(text)
        return len(builds) != 1

    apply(tree, verify=verify)
    assert len(builds) == 4                         # failed batch, then three ordinary attempts
    assert "int sum = box->m_x2C + increment;" in builds[0]
    assert "int iVar3 = box->m_x2C + a2;" in builds[1]  # no edits leaked from failed batch
    assert len(rows(tree, rename.NAME_BASIS)) == 3
    assert {r["status"] for r in lane_of(tree).state().values()} == {"landed"}


@pytest.mark.parametrize("failure", ["build", "checks", "interrupt"])
def test_scoped_batch_failure_restores_all_files_and_journal(tree, tmp_path, failure):
    agree_on(tree, tmp_path, BATCH_ANSWERS)
    before = (tree / SOURCE).read_bytes()
    basis = (tree / rename.NAME_BASIS).read_bytes() if (tree / rename.NAME_BASIS).exists() else None
    ctx = rename.Context(tree, object_scan=False)

    def verify(ctx, sources):
        assert list((tree / rename.JOURNAL_DIR).glob("*.json"))
        if failure == "interrupt":
            raise KeyboardInterrupt
        return failure != "build"

    def checks(ctx, plan):
        return ["test: reject combined result"] if failure == "checks" and plan.written() else []

    with pytest.raises(KeyboardInterrupt if failure == "interrupt" else rename.VerifyFailed):
        rename.run_scoped_batch(ctx, batch_requests(tree), claim=False, verify=verify, checks=checks)
    assert (tree / SOURCE).read_bytes() == before
    assert ((tree / rename.NAME_BASIS).read_bytes() if (tree / rename.NAME_BASIS).exists() else None) == basis
    assert not ctx.kept
    assert not list((tree / rename.JOURNAL_DIR).glob("*.json"))


def test_scoped_batch_planning_refusal_writes_nothing(tree, tmp_path):
    agree_on(tree, tmp_path, BATCH_ANSWERS)
    before = (tree / SOURCE).read_bytes()
    requests = batch_requests(tree)
    requests[1][1]["new"] = "box"                   # captures the preceding parameter rename
    with pytest.raises(rename.Refusal):
        rename.run_scoped_batch(rename.Context(tree, object_scan=False), requests, claim=False,
                                verify=lambda *args: pytest.fail("refused plans must not build"), checks=no_checks)
    assert (tree / SOURCE).read_bytes() == before
    assert not (tree / rename.NAME_BASIS).exists()
    assert not list((tree / rename.JOURNAL_DIR).glob("*.json"))


@pytest.mark.parametrize("success", [True, False])
def test_scoped_batch_claims_union_once_and_releases_on_failure(tree, tmp_path, monkeypatch, success):
    agree_on(tree, tmp_path, BATCH_ANSWERS)
    taken, released = [], []
    claimed = rename.Claimed()
    monkeypatch.setattr(claimed, "release", lambda root: released.append(root))

    def take(keys, enabled, root):
        taken.append((keys, enabled, root))
        return claimed

    monkeypatch.setattr(rename, "take_claims", take)
    ctx = rename.Context(tree, object_scan=False)
    if success:
        rename.run_scoped_batch(ctx, batch_requests(tree), verify=ok_verify, checks=no_checks)
    else:
        with pytest.raises(rename.VerifyFailed):
            rename.run_scoped_batch(ctx, batch_requests(tree), verify=lambda *args: False, checks=no_checks)
    assert taken == [([0x00401000, f"file:{SOURCE}"], True, tree)]
    assert released == ([] if success else [tree])


# ---------------------------------------------------------------- real tree

@pytest.mark.usefixtures("claim_coordination")
def test_real_tree_list_only(capsys):
    lane = name_lane.Lane()
    if not (lane.root / "reverse/functions.csv").exists():
        pytest.skip("no real ledger")
    args = SimpleNamespace(session="pytest-smoke", model="claude-opus-5-5", count=2, file=None, list_only=True)
    assert name_lane.cmd_next(lane, args) == 0
    listed = json.loads(capsys.readouterr().out)
    assert 1 <= len(listed) <= 2  # --count is a cap; do not fill from unrelated groups
    assert len({entry["subsystem"] for entry in listed}) == 1
    for entry in listed:
        assert entry["file"].startswith("Code/") and not entry["file"].startswith(rename.GENERATED)
        assert entry["chars"] <= name_lane.MAX_CHARS and sum(entry["kinds"].values()) >= 1
    assert not (lane.root / "build/name_lane/sessions/pytest-smoke.json").exists()


@pytest.mark.parametrize("symbol,served", [
    ("?linearInsert@@YAHH@Z", False),
    ("?rva00409999@@YAHH@Z", True),
    (FN, True),
])
def test_real_pin_preflight(tree, symbol, served):
    (tree / "reverse/symbols.csv").write_text("name,address,notes\n" + symbol + ",0x00401000,test\n")
    items = lane_of(tree).owned(SOURCE)
    assert any(i[0] == "function" for i in items) is served


def test_existing_header_class_rejected_before_vote(tree, tmp_path, capsys):
    header = tree / "Code/Game/Existing.h"
    header.write_text("struct BoxView { int value; };\n")
    _git(tree, "add", "Code/Game/Existing.h")
    vote(tree, tmp_path, "a", {"Rva00401000Box": "BoxView"})
    assert not rows(tree, name_lane.VOTES)
    assert "reconcile declarations" in capsys.readouterr().out


def test_changed_pin_after_serving_rejected_at_submission(tree, tmp_path, capsys):
    serve(tree, "a")
    (tree / "reverse/symbols.csv").write_text("name,address,notes\n?linearInsert@@YAHH@Z,0x00401000,test\n")
    answer = tmp_path / "answer.json"
    answer.write_text(json.dumps({"rva00401000": "sumBox"}))
    name_lane.cmd_submit(lane_of(tree), SimpleNamespace(session="a", model="claude-opus-5-5", answer=str(answer)))
    assert not rows(tree, name_lane.VOTES)
    assert "already names" in capsys.readouterr().out


def test_class_collision_handoff_is_read_only_and_requires_identity(tree, tmp_path, capsys):
    agree_on(tree, tmp_path, {"Rva00401000Box": "BoxView"})
    header = "Code/Game/BoxView.h"
    (tree / header).write_text("struct BoxView { int m_x2C; int m_count; };\n")
    _git(tree, "add", header)
    (tree / rename.CANONICAL_CLASSES).write_text("class,header,notes\nBoxView," + header + ",test\n")
    apply(tree)
    before = {p: (tree / p).read_bytes() for p in (SOURCE, header, name_lane.AGREED, name_lane.VOTES)}
    capsys.readouterr()
    name_lane.main(["reconcile"], lane=lane_of(tree))
    packets = json.loads(capsys.readouterr().out)
    assert len(packets) == 1
    packet = packets[0]
    assert packet["registered_header"] == header
    assert packet["status"] == "identity-review-required"
    assert "Rva00401000Box" in packet["private_view"]["declarations"][0]
    assert "BoxView" in packet["existing_views"][0]["declarations"][0]
    assert before == {p: (tree / p).read_bytes() for p in before}
    assert lane_of(tree).state()[SOURCE + "|class||Rva00401000Box"]["status"] == "blocked"
    name_lane.main(["reconcile", "--key", "unknown"], lane=lane_of(tree))
    assert json.loads(capsys.readouterr().out) == []


@pytest.mark.parametrize("limit,lands,refuse_verify", [(25, False, False), (40, True, False), (40, False, True)])
def test_configurable_fanout_verifies_all_consumers_and_rolls_back(tree, tmp_path, limit, lands, refuse_verify):
    header = "Code/Game/BoxApi.h"
    (tree / header).write_bytes(b"struct Rva00401000Box; int rva00401000(Rva00401000Box *,int);\n")
    source = tree / SOURCE
    source.write_bytes(b'#include "BoxApi.h"\n' + source.read_bytes())
    for n in range(26):
        rel = f"Code/Game/Consumer{n}.cpp"
        (tree / rel).write_bytes(f'#include "BoxApi.h"\nint consumer{n}() {{ return 0; }}\n'.encode())
        with (tree / "reverse/functions.csv").open("a", newline="") as f:
            f.write(f"?consumer{n}@@YAHXZ,,0x{0x500000+n*16:08X},8,{rel},matched,test\n")
    _git(tree, "add", "Code")
    agree_on(tree, tmp_path, {"rva00401000": "sumBox"})
    before = {p: (tree / p).read_bytes() for p in (SOURCE, header, "reverse/functions.csv")}
    builds = []
    def verify(ctx, sources):
        builds.append(sources)
        return not refuse_verify
    args = SimpleNamespace(key=[FN_KEY], retry_blocked=False, lead=2, min_models=1,
                           claim=False, only_labels=None, max_files=limit)
    name_lane.cmd_apply(lane_of(tree), args, verify=verify, checks=no_checks)
    assert (lane_of(tree).state()[FN_KEY]["status"] == "landed") is lands
    assert len(builds) == (1 if limit > 25 else 0)
    if builds:
        assert set(builds[0]) == {SOURCE} | {f"Code/Game/Consumer{n}.cpp" for n in range(26)}
    if not lands:
        assert before == {p: (tree / p).read_bytes() for p in before}


def test_apply_max_files_must_be_positive(tree):
    with pytest.raises(SystemExit):
        name_lane.main(["apply", "--max-files", "0"], lane=lane_of(tree))
