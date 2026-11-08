"""tools/name_lane.py on a miniature tree: a temporary git repository with
small ledgers and one source, so serving, blind hashed voting, agreement
(two sessions agreeing, disagreeing, ties), landing through tools/rename.py
and disputes all run without the real ledger or a compiler (verification is
injected). A real-tree `next --list-only` smoke closes the file."""
import csv
import hashlib
import io
import json
import os
import re
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
    # A miniature ledger's rows are all after the cutoff: no record there is grandfathered.
    monkeypatch.setattr(name_lane, "AGREED_CUTOFF_ROWS", 0)


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
                           only_labels=kw.get("only_labels"), key=kw.get("key"), no_batch=kw.get("no_batch", False),
                           per_file=kw.get("per_file", True))
    return name_lane.cmd_apply(lane_of(root), args, verify=kw.get("verify", ok_verify),
                               checks=kw.get("checks", no_checks))


def test_reviewed_disagreement_can_accept_reviewer_name_and_apply(tree, tmp_path):
    vote(tree, tmp_path, "original", {"rva00401000": "sumBox"}, worker="original-worker")
    vote(tree, tmp_path, "reviewer", {"rva00401000": "addBoxWidth"}, worker="reviewer-worker")
    assert FN_KEY not in lane_of(tree).state()
    be("original-worker")
    args = SimpleNamespace(key=FN_KEY, name="addBoxWidth",
                           reason="The body adds the width to the box count")
    assert name_lane.cmd_resolve(lane_of(tree), args) == 0
    row = lane_of(tree).state()[FN_KEY]
    assert row["status"] == "agreed" and row["id"].startswith("nr-")
    assert len(rows(tree, name_lane.VOTES)) == 2  # no synthetic vote
    assert len(rows(tree, name_lane.RESOLUTIONS)) == 1
    assert apply(tree, key=[FN_KEY]) == 0
    assert lane_of(tree).state()[FN_KEY]["status"] == "landed"


def test_reviewed_resolution_rejects_outsider_and_stale_source(tree, tmp_path):
    vote(tree, tmp_path, "original", {"rva00401000": "sumBox"}, worker="original-worker")
    vote(tree, tmp_path, "reviewer", {"rva00401000": "addBoxWidth"}, worker="reviewer-worker")
    args = SimpleNamespace(key=FN_KEY, name="addBoxWidth",
                           reason="The body adds the width to the box count")
    be("outsider")
    with pytest.raises(SystemExit, match="only an original voter"):
        name_lane.cmd_resolve(lane_of(tree), args)
    be("original-worker")
    name_lane.cmd_resolve(lane_of(tree), args)
    path = tree / SOURCE
    path.write_bytes(path.read_bytes() + b"\n")
    assert apply(tree, key=[FN_KEY]) == 0
    assert lane_of(tree).state()[FN_KEY]["status"] == "agreed"
    assert not rows(tree, "reverse/name_basis.csv")


def test_two_reviewed_names_in_one_source_share_a_batch(tree, tmp_path):
    vote(tree, tmp_path, "original", {"rva00401000": "sumBox",
         "Rva00401000Box::m_x2C": "m_width"}, worker="original-worker")
    vote(tree, tmp_path, "reviewer", {"rva00401000": "addBoxWidth",
         "Rva00401000Box::m_x2C": "m_boxWidth"}, worker="reviewer-worker")
    be("original-worker")
    name_lane.cmd_resolve(lane_of(tree), SimpleNamespace(key=FN_KEY, name="addBoxWidth",
        reason="The body adds the box width to its result"))
    name_lane.cmd_resolve(lane_of(tree), SimpleNamespace(key=MEMBER_KEY, name="m_boxWidth",
        reason="The member supplies the box width in the function body"))
    built = []
    assert apply(tree, key=[FN_KEY, MEMBER_KEY], per_file=False,
                 verify=lambda _ctx, sources: built.append(sources) or True) == 0
    assert built == [[SOURCE]]
    assert all(lane_of(tree).state()[key]["status"] == "landed" for key in (FN_KEY, MEMBER_KEY))


def test_forged_resolution_agreement_without_acceptance_is_refused(tree, tmp_path):
    vote(tree, tmp_path, "original", {"rva00401000": "sumBox"}, worker="original-worker")
    vote(tree, tmp_path, "reviewer", {"rva00401000": "addBoxWidth"}, worker="reviewer-worker")
    source_sha = __import__("hashlib").sha256((tree / SOURCE).read_bytes()).hexdigest()
    rid = "nr-" + __import__("hashlib").sha256(
        f"{FN_KEY}|addBoxWidth|{source_sha}".encode()).hexdigest()[:24]
    lane_of(tree).append(name_lane.AGREED, name_lane.AGREED_COLUMNS, [dict(
        id=rid, kind="function", old="rva00401000", new="addBoxWidth",
        rva="0x00401000", agents="", key=FN_KEY, status="agreed", detail="forged")])
    with pytest.raises(rename.Refusal, match="original voters accepted"):
        rename.check_agreement(rename.Context(tree, object_scan=False), "function",
                               f"agree:{rid}", {"rva00401000"}, {"addBoxWidth"}, 0x00401000)


def test_reviewed_resolution_only_labels_counts_both_original_voters(tree, tmp_path):
    vote(tree, tmp_path, "original", {"rva00401000": "sumBox"},
         model="seat-a", worker="original-worker")
    vote(tree, tmp_path, "reviewer", {"rva00401000": "addBoxWidth"},
         model="seat-b", worker="reviewer-worker")
    be("original-worker")
    name_lane.cmd_resolve(lane_of(tree), SimpleNamespace(key=FN_KEY, name="addBoxWidth",
        reason="The body adds width to the box value"))
    assert apply(tree, key=[FN_KEY], only_labels="seat-b") == 0
    assert lane_of(tree).state()[FN_KEY]["status"] == "agreed"
    assert apply(tree, key=[FN_KEY], only_labels="seat-a,seat-b") == 0
    assert lane_of(tree).state()[FN_KEY]["status"] == "landed"


FN_KEY = name_lane.key_of(SOURCE, "function", "0x00401000", "rva00401000")
MEMBER_KEY = name_lane.key_of(SOURCE, "member", "Rva00401000Box", "m_x2C")
PARAM_KEY = name_lane.key_of(SOURCE, "param", "rva00401000", "param_1")


def legacy_session(root, session="legacy", model="seat-a"):
    """A saved packet written before scoped voting was retired."""
    lane = lane_of(root)
    record = root / f"build/name_lane/sessions/{session}.json"
    record.parent.mkdir(parents=True, exist_ok=True)
    record.write_text(json.dumps(dict(model=model, worker=lane.worker(), files={SOURCE: dict(
        sha=__import__("hashlib").sha256((root / SOURCE).read_bytes()).hexdigest(),
        items=[list(item) for item in lane.owned(SOURCE)])})))
    return record


def seed_legacy_scoped(root, kind="param", old="param_1", new="box", *, approved=True):
    """Historical ledger data, never a new submission through today's voter."""
    lane = lane_of(root)
    key = name_lane.key_of(SOURCE, kind, "rva00401000", old)
    worker, model = "w-0123456789ab", "legacy-model"
    lane.append(name_lane.VOTES, name_lane.VOTE_COLUMNS, [dict(
        key=key, hash=name_lane.digest(key, new), worker=worker, model=model,
        session="historical-scoped", date="2026-11-02")])
    if approved:
        row = dict(id=name_lane.record_id(key, new), kind=kind, old=old, new=new,
                   rva="", agents=f"{worker}@{model}", key=key, status="agreed")
        row["detail"] = name_lane.approval_detail(lane.tally(), lane.disputed(), row)
        lane.append(name_lane.AGREED, name_lane.AGREED_COLUMNS, [row])
    return key


def historical_vote(root, tmp_path, session, answers, model="claude-opus-5-5", lead=2,
                    min_models=1, worker=None, source=SOURCE):
    """Seed pre-migration records for backlog tests, bypassing no current entry point."""
    be(worker or f"seat-{session}")
    lane = lane_of(root)
    inventory = {name_lane.answer_key(kind, scope, old): (kind, scope, old, rva)
                 for kind, scope, old, rva in lane.owned(source)}
    for answer_id, value in answers.items():
        spelling = value.get("name") if isinstance(value, dict) else value
        if str(spelling).lower() == "skip":
            continue
        kind, scope, old, rva = inventory[answer_id]
        key = name_lane.key_of(source, kind, scope, old)
        vote_row = dict(key=key, hash=name_lane.digest(key, spelling), worker=lane.worker(),
                        model=model, session=session, date="2026-11-02")
        lane.append(name_lane.VOTES, name_lane.VOTE_COLUMNS, [vote_row])
        meaning = (name_agreement.meaning_digest(key, value["meaning"])
                   if isinstance(value, dict) and "meaning" in value else None)
        if meaning:
            lane.append(name_lane.MEANINGS, name_lane.MEANING_COLUMNS, [dict(vote_row, meaning=meaning)])
        tally, refused = lane.tally(), lane.disputed()
        mine, rivals, role = name_agreement.support(tally, refused, key, spelling, meaning)
        if name_lane.wins(mine, rivals, lead=lead, min_models=min_models, key=key):
            row = dict(id=name_lane.record_id(key, spelling, role), kind=kind, old=old,
                       new=spelling, rva=f"0x{rva:08X}" if rva is not None else "",
                       agents=";".join(f"{w}@{m}" for w, m in sorted(mine.items())), key=key, status="agreed")
            row["detail"] = name_lane.approval_detail(tally, refused, row)
            lane.append(name_lane.AGREED, name_lane.AGREED_COLUMNS, [row])
    return 0


def test_voting_picker_and_brief_only_offer_shared_names(tree):
    served = serve(tree, "shared-only")
    assert {item[0] for item in served["files"][SOURCE]["items"]} == set(name_lane.NAMED)
    brief = (tree / "build/name_lane/briefs/shared-only.txt").read_text()
    assert "scoped next --session shared-only-scoped" in brief
    assert "rva00401000:param_1" not in brief
    assert "can land from your one proposal" not in brief
    assert "independent\nblind agreement" in brief


def test_scoped_redirect_sanitizes_legacy_session_labels():
    route = name_lane.scoped_route("old.session", "seat-a", [SOURCE])
    assert "scoped next --session old_session-scoped --model seat-a" in route
    assert f"--files {SOURCE}" in route


def test_old_mixed_session_can_still_submit_shared_answers(tree, tmp_path):
    legacy_session(tree)
    path = tmp_path / "shared-answer.json"
    path.write_text(json.dumps({"rva00401000": "sumBox"}))
    assert name_lane.cmd_submit(lane_of(tree), SimpleNamespace(
        session="legacy", model="seat-a", answer=str(path))) == 0
    votes = rows(tree, name_lane.VOTES)
    assert len(votes) == 1 and votes[0]["key"] == FN_KEY


def test_picker_with_only_legacy_scoped_cache_returns_no_voting_tasks(tree, monkeypatch, capsys):
    lane = lane_of(tree)
    scoped = [item for item in lane.owned(SOURCE) if item[0] in name_lane.SCOPED_KINDS]
    monkeypatch.setattr(name_lane.PickerCache, "items", lambda *_a: scoped)
    assert name_lane.cmd_next(lane, SimpleNamespace(session="scoped-only", model="seat-a",
        count=1, file=SOURCE, list_only=False)) == 0
    assert "scoped next" in capsys.readouterr().out
    assert not (tree / "build/name_lane/sessions/scoped-only.json").exists()
    assert not rows(tree, name_lane.VOTES)


@pytest.mark.parametrize("cached", [True, False])
def test_voting_picker_filters_legacy_cached_scoped_items(tree, monkeypatch, cached):
    lane = lane_of(tree)
    inventory = lane.owned(SOURCE)
    if cached:
        monkeypatch.setattr(name_lane.PickerCache, "snapshot", lambda _self: "same-inputs")
        path = tree / "build/name_lane/picker-cache.json"
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(json.dumps(dict(stamp="same-inputs", entries={SOURCE: dict(
            sha=__import__("hashlib").sha256((tree / SOURCE).read_bytes()).hexdigest(),
            items=inventory)})))
        monkeypatch.setattr(name_lane.Lane, "owned", lambda *_a, **_k: pytest.fail("must use saved inventory"))
    else:
        # Defense at the serving boundary, even if a provider returns old kinds.
        monkeypatch.setattr(name_lane.PickerCache, "items", lambda *_a: inventory)
    record = serve(tree, "cached-shared")
    assert {item[0] for item in record["files"][SOURCE]["items"]} == set(name_lane.NAMED)


def test_next_refuses_reusing_a_saved_scoped_voting_session(tree):
    record = legacy_session(tree)
    before = record.read_bytes()
    with pytest.raises(SystemExit, match="scoped next"):
        name_lane.cmd_next(lane_of(tree), SimpleNamespace(session="legacy", model="seat-a",
            count=1, file=SOURCE, list_only=False))
    assert record.read_bytes() == before
    assert not rows(tree, name_lane.VOTES)


@pytest.mark.parametrize("kind,old,answer", [
    ("param", "param_1", "box"),
    ("local", "iVar3", {"name": "sum", "meaning": {"role": "output"}}),
])
@pytest.mark.parametrize("validate_only", [False, True])
def test_old_session_cannot_submit_scoped_votes_even_after_source_changes(
        tree, tmp_path, kind, old, answer, validate_only):
    seed_legacy_scoped(tree)
    record = legacy_session(tree)
    before = {p: (tree / p).read_bytes() for p in (name_lane.VOTES, name_lane.AGREED)}
    source = tree / SOURCE
    source.write_bytes(source.read_bytes() + b"\n")
    response = tmp_path / "retired.json"
    response.write_text(json.dumps({f"rva00401000:{old}": answer,
                                   "Rva00401000Box::m_x2C": "m_width"}))
    args = SimpleNamespace(session="legacy", model="seat-a", answer=str(response), propose_only=True)
    if validate_only:
        report = name_lane.cmd_submit(lane_of(tree), args, validate_only=True)
        assert not report["valid"] and len(report["rejected"]) == 1
        assert "scoped next" in report["rejected"][0]["reason"]
        assert not report["rejected"][0]["retryable"]
    else:
        with pytest.raises(SystemExit, match="scoped next.*--files Code/Game/Box.cpp"):
            name_lane.cmd_submit(lane_of(tree), args)
    assert record.exists()
    assert before == {p: (tree / p).read_bytes() for p in before}
    assert not rows(tree, name_lane.MEANINGS)
    assert not rows(tree, name_lane.RESOLUTIONS)


@pytest.mark.parametrize("options", [dict(key=[PARAM_KEY]), dict(meaning_review_only=True)])
def test_explicit_unfinished_scoped_tasks_redirect_to_batch_review(tree, options):
    args = SimpleNamespace(session="redirect", model="seat-a", file=SOURCE, count=1,
                           list_only=False, **options)
    with pytest.raises(SystemExit, match="scoped next"):
        name_lane.cmd_next(lane_of(tree), args)
    assert not (tree / "build/name_lane/sessions/redirect.json").exists()


def test_unfinished_scoped_resolution_is_redirected_without_writes(tree):
    seed_legacy_scoped(tree, approved=False)
    before = (tree / name_lane.VOTES).read_bytes()
    with pytest.raises(SystemExit, match="scoped next"):
        name_lane.cmd_resolve(lane_of(tree), SimpleNamespace(key=PARAM_KEY, name="box",
            reason="The parameter supplies the box value"))
    assert (tree / name_lane.VOTES).read_bytes() == before
    assert not rows(tree, name_lane.AGREED)
    assert not rows(tree, name_lane.RESOLUTIONS)


def test_historical_scoped_approvals_still_apply_together(tree):
    seed_legacy_scoped(tree)
    seed_legacy_scoped(tree, "local", "iVar3", "sum")
    before = (tree / name_lane.VOTES).read_bytes()
    builds = []
    assert apply(tree, per_file=False, verify=lambda _ctx, sources: builds.append(sources) or True) == 0
    assert builds == [[SOURCE]]
    assert "int sum = box->m_x2C + a2;" in (tree / SOURCE).read_text()
    assert {row["status"] for row in lane_of(tree).state().values()} == {"landed"}
    assert (tree / name_lane.VOTES).read_bytes() == before


def test_unapproved_scoped_votes_are_preserved_without_promotion(tree, capsys):
    seed_legacy_scoped(tree, approved=False)
    before = (tree / SOURCE).read_bytes(), (tree / name_lane.VOTES).read_bytes()
    assert apply(tree) == 0
    assert (tree / SOURCE).read_bytes() == before[0]
    assert (tree / name_lane.VOTES).read_bytes() == before[1]
    assert not rows(tree, name_lane.AGREED)
    be("another-worker")
    name_lane.cmd_next(lane_of(tree), SimpleNamespace(session="no-old-review", model="seat-a",
        count=1, file=SOURCE, list_only=False, review_only=True))
    assert not (tree / "build/name_lane/sessions/no-old-review.json").exists()
    assert "scoped next" in capsys.readouterr().out


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


def test_run_batch_warms_donor_parameter_search_once_across_files():
    class DonorLane:
        texts = {
            "Code/A.cpp": "int Rva00401000(int a) { return a; }\n",
            "Code/B.cpp": "int Rva00402000(int b) { return b; }\n",
        }
        calls = []
        def text(self, rel):
            return self.texts[rel]
        def donor_params(self, functions):
            self.calls.append(set(functions))
            return {name: set() for name in functions}
    lane = DonorLane()
    name_lane.warm_donor_parameters(lane, lane.texts)
    assert lane.calls == [{"Rva00401000", "Rva00402000"}]


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


def test_explicit_files_share_one_claim_snapshot_and_brief(tree, monkeypatch):
    ai = [add_subsystem_source(tree, "AI", n) for n in range(2)]
    real_busy = name_lane.claims.busy_keys
    calls = []
    def busy(root):
        calls.append(root)
        return real_busy(root)
    monkeypatch.setattr(name_lane.claims, "busy_keys", busy)
    record = subsystem_next(tree, "selected", count=1, files=ai,
                            subsystem="Code/Game/AI")
    assert list(record["files"]) == ai
    assert len(calls) == 1
    brief = (tree / "build/name_lane/briefs/selected.txt").read_text()
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
        {"key": name_lane.key_of(rel, "function", "0x00410000", "run"), "hash": "x",
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
    historical_vote(tree, tmp_path, "single", {"rva00401000:param_1": "box"})
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
    historical_vote(tree, tmp_path, "earlier", {"rva00401000:param_1": "box"}, worker="second-worker")
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
    for seat, name in (("legacy-a", "box"), ("legacy-b", "inputBox")):
        historical_vote(tree, tmp_path, seat, {"rva00401000:param_1": name})


@pytest.mark.parametrize("second_role", ["source", "destination"])
def test_original_scoped_workers_are_redirected_instead_of_adding_meanings(tree, tmp_path, second_role):
    legacy_scoped_disagreement(tree, tmp_path)
    original = (tree / name_lane.VOTES).read_bytes()
    for seat, name, role in (("legacy-a", "box", "source"), ("legacy-b", "inputBox", second_role)):
        be("seat-" + seat)
        legacy_session(tree, session="meaning-" + seat)
        answer = tmp_path / (seat + "-role.json")
        answer.write_text(json.dumps({"rva00401000:param_1": {"name": name, "meaning": role_descriptor(role=role)}}))
        with pytest.raises(SystemExit, match="scoped next"):
            name_lane.cmd_submit(lane_of(tree), SimpleNamespace(session="meaning-" + seat, model="seat-a", answer=str(answer)))
    assert (tree / name_lane.VOTES).read_bytes() == original
    assert not rows(tree, name_lane.MEANINGS)


def test_retired_meaning_picker_cannot_restart_with_another_spelling(tree, tmp_path):
    legacy_scoped_disagreement(tree, tmp_path)
    before = (tree / name_lane.VOTES).read_bytes()
    be("seat-legacy-a")
    with pytest.raises(SystemExit, match="scoped next"):
        subsystem_next(tree, "clarify", file=SOURCE, meaning_review_only=True)
    assert (tree / name_lane.VOTES).read_bytes() == before
    assert not rows(tree, name_lane.MEANINGS)


def test_retired_meaning_submission_preserves_existing_descriptors(tree, tmp_path):
    historical_vote(tree, tmp_path, "legacy-a", {"rva00401000:param_1": {"name": "box", "meaning": role_descriptor()}})
    before = {rel: (tree / rel).read_bytes() for rel in (name_lane.VOTES, name_lane.MEANINGS, name_lane.AGREED)}
    legacy_session(tree, "clarify")
    answer = tmp_path / "changed-meaning.json"
    answer.write_text(json.dumps({"rva00401000:param_1": {"name": "box", "meaning": role_descriptor(role="destination")}}))
    with pytest.raises(SystemExit, match="scoped next"):
        name_lane.cmd_submit(lane_of(tree), SimpleNamespace(session="clarify", model="seat-a", answer=str(answer)))
    assert before == {rel: (tree / rel).read_bytes() for rel in before}


def test_shared_review_only_does_not_serve_own_meaning_clarifications(tree, tmp_path, capsys):
    legacy_scoped_disagreement(tree, tmp_path)
    be("seat-legacy-a")
    capsys.readouterr()
    subsystem_next(tree, "shared-only", review_only=True, list_only=True)
    assert json.loads(capsys.readouterr().out) == []
    with pytest.raises(SystemExit, match="scoped next"):
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
    vote(tree, tmp_path, "s1", {"rva00401000": "sumBox", "Rva00401000Box::m_x2C": "bad-name"})
    out = capsys.readouterr().out
    assert "bad-name" in out and "rejected" in out
    serve_twice = SimpleNamespace(session="s1", model="claude-opus-5-5", count=1, file=SOURCE, list_only=False)
    name_lane.cmd_next(lane_of(tree), serve_twice)
    assert "no shared names are left" in capsys.readouterr().out
    with pytest.raises(SystemExit):
        vote(tree, tmp_path, "s2", {"nonexistent": "x"})


# ---------------------------------------------------------------- apply

def grandfather_all(tree, monkeypatch):
    """Pin the ledger's rows as they stand as the grandfathered prefix."""
    rows = lane_of(tree).agreed_rows()
    monkeypatch.setattr(name_lane, "AGREED_CUTOFF_ROWS", len(rows))
    monkeypatch.setattr(name_lane, "AGREED_CUTOFF_SHA256", name_lane.agreed_prefix_hash(rows))


def agree_on(tree, tmp_path, answers):
    inventory = {name_lane.answer_key(k, s, i): k for k, s, i, _ in lane_of(tree).owned(SOURCE)}
    scoped = {key: value for key, value in answers.items() if inventory[key] in name_lane.SCOPED_KINDS}
    shared = {key: value for key, value in answers.items() if key not in scoped}
    if scoped:
        historical_vote(tree, tmp_path, "s1", scoped)
    if shared:
        vote(tree, tmp_path, "s1", shared)
    # Already approved historical scoped names stay usable by backlog tests.
    approved = {name_lane.answer_key(*name_lane.split_key(k)[1:]): row
                for k, row in lane_of(tree).state().items()}
    pending = {key: value for key, value in answers.items() if key not in approved}
    if pending:
        vote(tree, tmp_path, "s2", pending, model="gpt-6.1-sol")


def claim_apply_args(**overrides):
    options = dict(retry_blocked=True, lead=2, min_models=1, claim=True,
                   only_labels=None, key=None, no_batch=False, per_file=False)
    options.update(overrides)
    return SimpleNamespace(**options)


@pytest.mark.parametrize("mode", [{}, {"per_file": True}, {"no_batch": True}])
def test_apply_defers_busy_approval_before_file_analysis_in_every_mode(tree, tmp_path, monkeypatch, capsys, mode):
    from unittest.mock import Mock
    import claims
    historical_vote(tree, tmp_path, "single", {"rva00401000:param_1": "box"})
    lane = lane_of(tree)
    agreed = lane.state()[PARAM_KEY]
    lane.append(name_lane.AGREED, name_lane.AGREED_COLUMNS,
                [dict(agreed, status="blocked", detail="previous attempt")])
    before = (tree / name_lane.AGREED).read_bytes()
    source = (tree / SOURCE).read_bytes()
    monkeypatch.setenv("BFME_CLAIMS", "on")
    snapshot = Mock(return_value={claims.file_key(SOURCE)})
    monkeypatch.setattr(claims, "busy_keys", snapshot)
    def forbidden(*args, **kwargs):
        pytest.fail("held approval reached analysis, planning, claims or verification")
    monkeypatch.setattr(lane, "owned", forbidden)
    monkeypatch.setattr(name_lane, "warm_donor_parameters", forbidden)
    monkeypatch.setattr(rename, "plan_rename", forbidden)
    monkeypatch.setattr(rename, "take_claims", forbidden)
    assert name_lane.cmd_apply(lane, claim_apply_args(**mode), verify=forbidden, checks=forbidden) == 0
    snapshot.assert_called_once_with(tree)
    assert (tree / name_lane.AGREED).read_bytes() == before
    assert (tree / SOURCE).read_bytes() == source
    assert lane.state()[PARAM_KEY]["status"] == "blocked"
    assert not rows(tree, rename.NAME_BASIS)
    assert "deferred: held by another worker" in capsys.readouterr().out


@pytest.mark.parametrize("kind", ["file", "rva", "class", "persisted"])
def test_apply_preflight_uses_standard_expanded_claim_footprints(tree, tmp_path, monkeypatch, kind):
    import claims
    historical_vote(tree, tmp_path, "single", {"rva00401000:param_1": "box"})
    if kind == "class":
        ledger = tree / "reverse/functions.csv"
        ledger.write_bytes(ledger.read_bytes() +
            f"?run@Rva00401000Box@@QAEXXZ,,0x00403000,10,{SOURCE},matched,\n".encode())
    monkeypatch.setenv("BFME_CLAIMS", "on")
    key = {"file": claims.file_key(SOURCE), "rva": 0x00401000,
           "class": claims.class_key("Rva00401000Box"), "persisted": 0x00ABCDEF}[kind]
    info = {"owner": "other-worker"}
    if kind == "persisted":
        info["locks"] = [claims.file_key(SOURCE)]
    monkeypatch.setattr(claims, "_blocking_records", lambda root: iter([{key: info}]))
    monkeypatch.setattr(name_lane, "_apply_run", lambda *args, **kwargs: pytest.fail("busy source was planned"))
    assert name_lane.cmd_apply(lane_of(tree), claim_apply_args(), verify=ok_verify, checks=no_checks) == 0
    assert lane_of(tree).state()[PARAM_KEY]["status"] == "agreed"


@pytest.mark.parametrize("answer,held", [
    ({"rva00401000": "sumBox"}, 0x00401000),
    ({"Rva00401000Box": "GameBox"}, "class:Rva00401000Box"),
    ({"Rva00401000Box::m_x2C": "m_width"}, "class:Rva00401000Box"),
])
def test_apply_preflight_checks_direct_rva_and_class_keys(tree, tmp_path, monkeypatch, answer, held):
    import claims
    agree_on(tree, tmp_path, answer)
    before = (tree / name_lane.AGREED).read_bytes()
    monkeypatch.setenv("BFME_CLAIMS", "on")
    monkeypatch.setattr(claims, "busy_keys", lambda root: {claims.key_of(held)})
    monkeypatch.setattr(name_lane, "_apply_run", lambda *args, **kwargs: pytest.fail("held identity was planned"))
    name_lane.cmd_apply(lane_of(tree), claim_apply_args(), verify=ok_verify, checks=no_checks)
    assert (tree / name_lane.AGREED).read_bytes() == before


def test_deferred_claim_does_not_consume_apply_limit(tree, tmp_path, monkeypatch):
    from unittest.mock import Mock
    import claims
    historical_vote(tree, tmp_path, "single", {"rva00401000:param_1": "box"})
    free = add_subsystem_source(tree, "Available", 1)
    historical_vote(tree, tmp_path, "available", {"rva00410100:param_1": "inputValue"}, source=free)
    monkeypatch.setenv("BFME_CLAIMS", "on")
    snapshot = Mock(return_value={claims.file_key(SOURCE)})
    monkeypatch.setattr(claims, "busy_keys", snapshot)
    monkeypatch.setattr(rename, "take_claims", lambda *args: rename.Claimed())
    builds = []
    name_lane.cmd_apply(lane_of(tree), claim_apply_args(limit=1),
        verify=lambda ctx, sources: builds.append(sources) or True, checks=no_checks)
    snapshot.assert_called_once_with(tree)
    assert builds == [[free]]
    assert lane_of(tree).state()[PARAM_KEY]["status"] == "agreed"
    assert "int inputValue" in (tree / free).read_text()


def test_own_claim_remains_available_and_final_acquisition_still_runs(tree, tmp_path, monkeypatch):
    import claims
    historical_vote(tree, tmp_path, "single", {"rva00401000:param_1": "box"})
    monkeypatch.setenv("BFME_CLAIMS", "on")
    info = {"owner": claims.owner(tree), "expires": float("inf")}
    held = {claims.file_key(SOURCE): ("lease", info)}
    monkeypatch.setattr(claims, "fetch", lambda root: True)
    monkeypatch.setattr(claims, "_read_visible", lambda root: held)
    monkeypatch.setattr(claims, "_namespace_mirrors", lambda seen: [(claims.NS, claims.SEEN)])
    monkeypatch.setattr(claims, "_read_local", lambda root, seen: held)
    monkeypatch.setattr(claims, "mirrored", lambda root: {})
    taken = []
    monkeypatch.setattr(rename, "take_claims", lambda keys, enabled, root:
                        taken.append((keys, enabled)) or rename.Claimed())
    name_lane.cmd_apply(lane_of(tree), claim_apply_args(), verify=ok_verify, checks=no_checks)
    assert taken and all(enabled for _, enabled in taken)
    assert lane_of(tree).state()[PARAM_KEY]["status"] == "landed"


def test_no_claim_mode_does_not_query_shared_claims(tree, tmp_path, monkeypatch):
    import claims
    historical_vote(tree, tmp_path, "single", {"rva00401000:param_1": "box"})
    monkeypatch.setenv("BFME_CLAIMS", "on")
    monkeypatch.setattr(claims, "busy_keys", lambda root: pytest.fail("--no-claim fetched shared claims"))
    name_lane.cmd_apply(lane_of(tree), claim_apply_args(claim=False), verify=ok_verify, checks=no_checks)
    assert lane_of(tree).state()[PARAM_KEY]["status"] == "landed"


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
    historical_vote(tree, tmp_path, "single", {"rva00401000:param_1": "box"})
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
    # Existing semantic approvals retain their historical proof and reversal path.
    for seat, name in (("first", "box"), ("second", "inputBox")):
        historical_vote(tree, tmp_path, seat, {"rva00401000:param_1": {"name": name, "meaning": role_descriptor()}})
    state = lane_of(tree).state()[PARAM_KEY]
    assert name_agreement.record_meaning(state["id"])
    assert len(rows(tree, name_lane.MEANINGS)) == 2
    assert "source" not in (tree / name_lane.MEANINGS).read_text()  # role text stays blind
    assert apply(tree) == 0
    landed = lane_of(tree).state()[PARAM_KEY]
    assert landed["status"] == "landed" and len(landed["agents"].split(";")) == 2
    assert landed["new"] in {"box", "inputBox"}
    assert f"Rva00401000Box *{landed['new']}" in (tree / SOURCE).read_text()
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
    historical_vote(tree, tmp_path, "single", {"rva00401000:param_1": "box"})
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
        historical_vote(tree, tmp_path, seat, {"rva00401000:param_1": "destination"})
    assert lane_of(tree).state()[PARAM_KEY]["new"] == "destination"
    assert apply(tree) == 0
    assert "Rva00401000Box *destination" in (tree / SOURCE).read_text()


def test_single_scoped_proposal_keeps_byte_verification_rollback(tree, tmp_path):
    historical_vote(tree, tmp_path, "single", {"rva00401000:param_1": "box"})
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
        inventory = {name_lane.answer_key(k, s, n): k for k, s, n, _ in lane_of(tree).owned(SOURCE)}
        submit = historical_vote if any(inventory[k] in name_lane.SCOPED_KINDS for k in key_answer) else vote
        submit(tree, tmp_path, f"{tag}{i}", key_answer, label)


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
    assert "no shared names are left" in capsys.readouterr().out  # never served again, any label
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

def test_run_wide_mode_combines_scoped_and_function_approvals(tree, tmp_path):
    agree_on(tree, tmp_path, dict(BATCH_ANSWERS, rva00401000="sumBox"))
    builds = []
    apply(tree, per_file=False, verify=lambda ctx, sources: builds.append(sources) or True)
    assert builds == [[SOURCE]]
    assert "int sumBox(Rva00401000Box *box, int increment)" in (tree / SOURCE).read_text()
    assert {r["status"] for r in lane_of(tree).state().values()} == {"landed"}

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


READY_ANSWERS = {"rva00401000": "sumBox", "g_00A01000": "boxTotal", "Rva00401000Box": "BoxValue"}


def ready_session(tree, tmp_path, session, worker, *, first_vote=True):
    if first_vote:
        vote(tree, tmp_path, session + "-first", READY_ANSWERS, worker="first-" + worker)
    serve(tree, session, worker=worker)


def submit_ready(tree, tmp_path, *, limit=2, verify=ok_verify):
    ready_session(tree, tmp_path, "ready", "ready-worker", first_vote=limit is None or limit > 0)
    answer = tmp_path / "ready-answer.json"
    answer.write_text(json.dumps(READY_ANSWERS))
    args = SimpleNamespace(session="ready", model="claude-opus-5-5", answer=str(answer), apply_ready=limit)
    return name_lane.cmd_submit(lane_of(tree), args, verify=verify, checks=no_checks)


def test_submit_apply_ready_is_bounded_and_leaves_unrelated_backlog(tree, tmp_path, monkeypatch):
    agree_on(tree, tmp_path, MEMBER_ANSWER)
    builds, claims = [], []
    original = rename.take_claims
    def claim(keys, enabled, root):
        claims.append(enabled)
        return original(keys, enabled, root)
    monkeypatch.setattr(rename, "take_claims", claim)
    submit_ready(tree, tmp_path, verify=lambda ctx, sources: builds.append(sources) or True)
    state = lane_of(tree).state()
    assert state[MEMBER_KEY]["status"] == "agreed"
    fresh = [row for key, row in state.items() if key != MEMBER_KEY]
    assert sum(row["status"] == "landed" for row in fresh) == 2
    assert sum(row["status"] == "agreed" for row in fresh) == 1
    assert builds == [[SOURCE]]
    assert claims and all(claims)


def test_submit_apply_ready_restores_failed_names_and_keeps_votes(tree, tmp_path):
    before = (tree / SOURCE).read_bytes()
    submit_ready(tree, tmp_path, verify=lambda ctx, sources: False)
    assert (tree / SOURCE).read_bytes() == before
    state = lane_of(tree).state()
    assert sum(row["status"] == "blocked" for row in state.values()) == 2
    assert sum(row["status"] == "agreed" for row in state.values()) == 1
    assert len(rows(tree, name_lane.VOTES)) == 6


def test_submit_without_new_approval_does_not_apply_backlog(tree, tmp_path, monkeypatch):
    agree_on(tree, tmp_path, MEMBER_ANSWER)
    serve(tree, "no-new", worker="no-new-worker")
    answer = tmp_path / "no-new.json"
    answer.write_text(json.dumps(FN_ANSWER))
    monkeypatch.setattr(name_lane, "cmd_apply", lambda *a, **kw: pytest.fail("unrelated backlog must not apply"))
    name_lane.cmd_submit(lane_of(tree), SimpleNamespace(session="no-new", model="claude-opus-5-5",
                                                       answer=str(answer), apply_ready=5))
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "agreed"


def test_invalid_submit_apply_limit_preserves_session_and_votes(tree, tmp_path):
    with pytest.raises(SystemExit):
        submit_ready(tree, tmp_path, limit=0)
    assert not rows(tree, name_lane.VOTES)
    assert (tree / "build/name_lane/sessions/ready.json").is_file()


def test_apply_limit_composes_with_key_filter_and_drains_on_next_run(tree, tmp_path, monkeypatch):
    agree_on(tree, tmp_path, {**MEMBER_ANSWER, **FN_ANSWER})
    grandfather_all(tree, monkeypatch)                                 # the limit, not source freshness
    args = SimpleNamespace(key=[FN_KEY], retry_blocked=False, lead=2, min_models=1,
                           claim=False, only_labels=None, limit=1)
    name_lane.cmd_apply(lane_of(tree), args, verify=ok_verify, checks=no_checks)
    state = lane_of(tree).state()
    assert state[FN_KEY]["status"] == "landed" and state[MEMBER_KEY]["status"] == "agreed"
    args.key = None
    name_lane.cmd_apply(lane_of(tree), args, verify=ok_verify, checks=no_checks)
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "landed"


def test_apply_limit_must_be_positive(tree):
    with pytest.raises(SystemExit):
        name_lane.main(["apply", "--limit", "0"], lane=lane_of(tree))


def test_ready_cli_options_are_forwarded(tree, monkeypatch):
    seen = {}
    monkeypatch.setattr(name_lane, "cmd_submit", lambda lane, args, **kw: seen.update(submit=args) or 0)
    monkeypatch.setattr(name_lane, "cmd_apply", lambda lane, args, **kw: seen.update(apply=args) or 0)
    name_lane.main(["submit", "answer.json", "--session", "s", "--model", "m",
                    "--apply-ready", "3", "--max-files", "60"], lane=lane_of(tree))
    assert seen["submit"].apply_ready == 3 and seen["submit"].max_files == 60
    name_lane.main(["apply", "--limit", "7", "--max-files", "60"], lane=lane_of(tree))
    assert seen["apply"].limit == 7 and seen["apply"].max_files == 60


@pytest.mark.parametrize("options, lands, reviews", [
    ([], True, True),
    (["--propose-only"], False, False),
    (["--no-auto-review"], True, False),
])
def test_normal_submit_completes_ready_batch_unless_explicitly_opted_out(
        tree, tmp_path, monkeypatch, options, lands, reviews):
    import name_review
    agree_on(tree, tmp_path, MEMBER_ANSWER)
    ready_session(tree, tmp_path, "automatic", "automatic-worker")
    answer = tmp_path / "automatic.json"
    answer.write_text(json.dumps(READY_ANSWERS))
    source = (tree / SOURCE).read_bytes()
    builds, launches = [], []
    original_submit = name_lane.cmd_submit
    monkeypatch.setattr(name_lane, "cmd_submit", lambda lane, args, **kw: original_submit(
        lane, args, verify=lambda ctx, sources: builds.append(sources) or True, checks=no_checks, **kw))
    monkeypatch.setattr(name_review, "maybe_launch", lambda lane, **kw: launches.append(kw))
    assert name_lane.main(["submit", str(answer), "--session", "automatic",
                           "--model", "claude-opus-5-5", *options], lane=lane_of(tree)) == 0
    state = lane_of(tree).state()
    fresh = [r for key, r in state.items() if key != MEMBER_KEY]
    assert len(fresh) == 3
    assert {r["status"] for r in fresh} == {"landed" if lands else "agreed"}
    assert state[MEMBER_KEY]["status"] == "agreed"  # no unrelated backlog application
    assert builds == ([[SOURCE]] if lands else [])
    assert launches == ([{"auto_configure": True, "apply_new": True}] if reviews else [])
    assert ((tree / SOURCE).read_bytes() != source) == lands


def test_default_submit_keeps_rollback_and_votes_when_verification_fails(tree, tmp_path, monkeypatch):
    ready_session(tree, tmp_path, "automatic-failure", "automatic-worker")
    answer = tmp_path / "automatic-failure.json"
    answer.write_text(json.dumps(READY_ANSWERS))
    source = (tree / SOURCE).read_bytes()
    original_submit = name_lane.cmd_submit
    monkeypatch.setattr(name_lane, "cmd_submit", lambda lane, args, **kw: original_submit(
        lane, args, verify=lambda *_: False, checks=no_checks, **kw))
    name_lane.main(["submit", str(answer), "--session", "automatic-failure",
                    "--model", "claude-opus-5-5", "--no-auto-review"], lane=lane_of(tree))
    assert (tree / SOURCE).read_bytes() == source
    assert len(rows(tree, name_lane.VOTES)) == 6
    assert {r["status"] for r in lane_of(tree).state().values()} == {"blocked"}



def test_claim_conflict_diagnostic_is_parsed_for_batch_pruning():
    result = SimpleNamespace(failure=rename.Refusal(
        "claimed by another worker: file/0123456789abcdef, 0x00401000"))
    assert name_lane._claim_conflicts(result) == {"file/0123456789abcdef", 0x00401000}


def test_compiler_diagnostic_maps_back_to_exact_verification_source():
    bad = SimpleNamespace(verify=[SOURCE])
    good = SimpleNamespace(verify=["Code/Game/Slow.cpp"])
    result = SimpleNamespace(diagnostics=(
        "Code/Game/Box.cpp(12): fatal error C1083: Cannot open include file: 'ascii_string.h'\n"))
    sources, detail = name_lane._diagnostic_sources(result, [(0, bad), (1, good)])
    assert sources == {SOURCE}
    assert "C1083" in detail and "ascii_string.h" in detail


def test_retry_blocker_fingerprint_changes_with_verified_input(tree, monkeypatch):
    monkeypatch.setattr(name_lane, "_missing_header_state", lambda *_: {"missing": True})
    lane = lane_of(tree)
    row = {"key": FN_KEY, "new": "sumBox"}
    plan = SimpleNamespace(verify=[SOURCE])
    blockers = {}
    name_lane._remember_blocker(lane, blockers, row, [plan], "missing header", header="missing.h")
    assert name_lane._same_blocker(lane, FN_KEY, row, blockers)
    (tree / SOURCE).write_text((tree / SOURCE).read_text() + "// changed\n")
    assert not name_lane._same_blocker(lane, FN_KEY, row, blockers)


def test_class_scope_estimate_stops_before_rewriting(tree, monkeypatch, capsys):
    lane = lane_of(tree)
    lane.ctx.object_scan = True
    monkeypatch.setattr(rename, "check_basis", lambda *a, **kw: None)
    monkeypatch.setattr(rename, "object_referencers", lambda _ctx, _symbols, **_kw:
                        {"Code/Game/ObjectConsumerA.cpp", "Code/Game/ObjectConsumerB.cpp"})
    with pytest.raises(rename.Refusal, match="object consumers"):
        rename.plan_class(lane.ctx, name="Rva00401000Box", new="BoxRecord", basis="inferred",
                          evidence="test", max_files=1)
    assert "2 object consumer(s)" in capsys.readouterr().out


def test_class_collision_does_not_scan_all_objects(tree, monkeypatch):
    lane = lane_of(tree)
    lane.ctx.object_scan = True
    (tree / "Code/Game/Existing.h").write_text("struct BoxRecord {};\n")
    _git(tree, "add", "--", "Code/Game/Existing.h")
    monkeypatch.setattr(rename, "check_basis", lambda *a, **kw: None)
    monkeypatch.setattr(rename, "object_referencers", lambda *_a, **_kw: pytest.fail("needless object scan"))
    with pytest.raises(rename.Refusal, match="BoxRecord already appears"):
        rename.plan_class(lane.ctx, name="Rva00401000Box", new="BoxRecord", basis="inferred", evidence="test")


def test_apply_prunes_a_claim_race_and_retries_free_names_together(tree, monkeypatch, capsys):
    lane = lane_of(tree)
    monkeypatch.setattr(name_lane, "warm_donor_parameters", lambda *_: {})
    first = {"key": FN_KEY, "id": "one", "kind": "function", "old": "rva00401000",
             "new": "sumBox", "rva": "0x00401000"}
    slow_key = name_lane.key_of("Code/Game/Slow.cpp", "function", "0x00402000", "rva00402000")
    second = {"key": slow_key, "id": "two", "kind": "function", "old": "rva00402000",
              "new": "slowCount", "rva": "0x00402000"}
    # Real plans use file:PATH, while the claims API refuses file/<hash>.
    first_claim = "file:" + SOURCE
    other_claim = "file:Code/Game/Slow.cpp"
    calls = []
    def plan(claim):
        return SimpleNamespace(kind="function", claims=[claim], after={}, moves=[], old_word="", old="",
                               verify=[SOURCE if claim == first_claim else "Code/Game/Slow.cpp"])
    def run_batch(_ctx, requests, **_kwargs):
        calls.append(len(requests))
        plans = [(i, plan(first_claim if i == 0 else other_claim)) for i in range(len(requests))]
        if len(calls) == 1:
            return rename.RunBatchResult(plans=plans,
                failure=rename.ClaimConflict([first_claim]))
        return rename.RunBatchResult(plans=plans)
    monkeypatch.setattr(rename, "run_batch", run_batch)
    tally = {FN_KEY: {}, slow_key: {}}
    name_lane._apply_run(lane, {SOURCE: [first], "Code/Game/Slow.cpp": [second]},
                         SimpleNamespace(claim=True), tally, {}, verify=ok_verify, checks=no_checks, max_files=25)
    assert calls == [2, 1]
    assert "leaving their approvals unchanged" in capsys.readouterr().out
    assert lane.state().get(FN_KEY) is None
    assert lane.state()[slow_key]["status"] == "landed"


def test_apply_uses_compiler_source_to_retry_survivors_as_one_batch(tree, monkeypatch):
    (tree / SOURCE).write_text('#include "ascii_string.h"\n' + (tree / SOURCE).read_text())
    monkeypatch.setattr(name_lane, "_missing_header_state", lambda *_: {"missing": True})
    lane = lane_of(tree)
    monkeypatch.setattr(name_lane, "warm_donor_parameters", lambda *_: {})
    first = {"key": FN_KEY, "id": "one", "kind": "function", "old": "rva00401000",
             "new": "sumBox", "rva": "0x00401000"}
    slow_key = name_lane.key_of("Code/Game/Slow.cpp", "function", "0x00402000", "rva00402000")
    second = {"key": slow_key, "id": "two", "kind": "function", "old": "rva00402000",
              "new": "slowCount", "rva": "0x00402000"}
    calls = []
    def run_batch(_ctx, requests, **_kwargs):
        calls.append(len(requests))
        plans = [(i, SimpleNamespace(verify=[SOURCE if i == 0 else "Code/Game/Slow.cpp"]))
                 for i in range(len(requests))]
        if len(calls) == 1:
            return rename.RunBatchResult(plans=plans, failure=rename.VerifyFailed("build failed"),
                diagnostics=f"{SOURCE}(12): fatal error C1083: Cannot open include file: 'ascii_string.h'")
        return rename.RunBatchResult(plans=plans)
    monkeypatch.setattr(rename, "run_batch", run_batch)
    tally = {FN_KEY: {}, slow_key: {}}
    name_lane._apply_run(lane, {SOURCE: [first], "Code/Game/Slow.cpp": [second]},
                         SimpleNamespace(claim=False), tally, {}, verify=ok_verify, checks=no_checks, max_files=25)
    assert calls == [2, 1]
    assert lane.state()[FN_KEY]["status"] == "blocked"
    assert lane.state()[slow_key]["status"] == "landed"
    blocker = name_lane._blockers(lane)[FN_KEY]
    assert "C1083" in blocker["detail"]


def test_retry_blocked_skips_identical_fingerprint_then_retries_changed_source(tree, tmp_path, monkeypatch,
                                                                               capsys):
    monkeypatch.setattr(name_lane, "_missing_header_state", lambda *_: {"missing": True})
    agree_on(tree, tmp_path, FN_ANSWER)
    grandfather_all(tree, monkeypatch)                                 # the blocker, not source freshness
    lane = lane_of(tree)
    row = lane.state()[FN_KEY]
    lane.append(name_lane.AGREED, name_lane.AGREED_COLUMNS,
                [dict(row, status="blocked", detail="missing include")])
    blockers = {}
    name_lane._remember_blocker(lane, blockers, row, [SimpleNamespace(verify=[SOURCE])], "missing include",
                                header="ascii_string.h")
    name_lane._save_blockers(lane, blockers)
    args = claim_apply_args(claim=False, key=[FN_KEY])
    monkeypatch.setattr(name_lane, "_apply_run", lambda *a, **kw: pytest.fail("same inputs must not retry"))
    name_lane.cmd_apply(lane, args, verify=ok_verify, checks=no_checks)
    assert "skipped unchanged blocker" in capsys.readouterr().out

    (tree / SOURCE).write_text((tree / SOURCE).read_text() + "// dependency changed\n")
    selected = []
    monkeypatch.setattr(name_lane, "_apply_run",
                        lambda _lane, todo, *_a, **_kw: selected.extend(todo) or (0, 0, 0))
    name_lane.cmd_apply(lane, args, verify=ok_verify, checks=no_checks)
    assert selected == [SOURCE]
    assert FN_KEY not in name_lane._blockers(lane)


def test_historical_ready_local_proof_applies_in_one_verified_batch(tree, tmp_path):
    agree_on(tree, tmp_path, BATCH_ANSWERS)
    builds = []
    apply(tree, per_file=False, verify=lambda ctx, sources: builds.append(sources) or True)
    assert builds == [[SOURCE]]
    assert {row["status"] for row in lane_of(tree).state().values()} == {"landed"}
    assert len(rows(tree, rename.NAME_BINDINGS)) == 1


def test_diagnostic_does_not_attribute_non_error_lines_to_failed_sources():
    result = SimpleNamespace(diagnostics=(
        'Code/Game/Slow.cpp(3): note: previously compiled\n'
        '"C:\\repo with space\\Code\\Game\\Box.cpp"(12): fatal error C1083: '
        "Cannot open include file: 'missing.h'\n"))
    plans = [(0, SimpleNamespace(verify=[SOURCE])),
             (1, SimpleNamespace(verify=["Code/Game/Slow.cpp"]))]
    assert name_lane._diagnostic_sources(result, plans)[0] == {SOURCE}


def test_blocker_store_merges_concurrent_keys_and_removes_only_requested_key(tree):
    lane = lane_of(tree)
    name_lane._save_blockers(lane, {"first": {"detail": "a"}})
    name_lane._save_blockers(lane, {"second": {"detail": "b"}})
    assert set(name_lane._blockers(lane)) == {"first", "second"}
    name_lane._save_blockers(lane, {}, remove={"first"})
    assert name_lane._blockers(lane) == {"second": {"detail": "b"}}


def test_blocker_invalidates_for_header_creation_configuration_and_input_edits(tree, monkeypatch):
    monkeypatch.setattr(name_lane, "_missing_header_state", lambda *_: {"missing": True})
    lane = lane_of(tree)
    row = {"key": FN_KEY, "new": "sumBox"}
    blockers = {}
    plan = SimpleNamespace(verify=[SOURCE])
    name_lane._remember_blocker(lane, blockers, row, [plan], "missing header", header="missing.h")
    assert name_lane._same_blocker(lane, FN_KEY, row, blockers)
    assert not name_lane._same_blocker(lane, FN_KEY, row, blockers, max_files=100)
    header = tree / "Code/Game/missing.h"
    header.write_text("// now available\n")
    assert not name_lane._same_blocker(lane, FN_KEY, row, blockers)
    _git(tree, "add", "--", "Code/Game/missing.h")
    name_lane._remember_blocker(lane, blockers, row, [plan], "missing header", header="missing.h")
    header.write_text("// modified existing dependency\n")
    assert not name_lane._same_blocker(lane, FN_KEY, row, blockers)


def test_unproved_or_transient_failure_is_not_persistently_suppressed(tree):
    lane = lane_of(tree)
    row = {"key": FN_KEY, "new": "sumBox"}
    blockers = {}
    name_lane._remember_blocker(lane, blockers, row, [SimpleNamespace(verify=[SOURCE])], "network timeout")
    assert blockers == {}


def test_missing_include_must_be_unchanged_before_and_after_the_proposals(tree):
    lane = lane_of(tree)
    detail = "fatal error C1083: Cannot open include file: 'missing.h'"
    assert name_lane._unchanged_missing_include(lane, [], {SOURCE}, detail) is None
    before = b'#include "missing.h"\n' + (tree / SOURCE).read_bytes()
    (tree / SOURCE).write_bytes(before)
    assert name_lane._unchanged_missing_include(lane, [], {SOURCE}, detail) == "missing.h"
    changed = SimpleNamespace(after={SOURCE: before.replace(b'missing.h', b'other.h')})
    assert name_lane._unchanged_missing_include(lane, [(0, changed)], {SOURCE}, detail) is None


def test_missing_header_state_detects_header_added_to_an_ignored_search_directory(tree, monkeypatch):
    import build
    lane = lane_of(tree)
    (tree / SOURCE).write_text('#include "missing.h"\n')
    include = tree / "build/private-includes"
    include.mkdir(parents=True)
    compiler = tree / "build/cl.exe"
    compiler.write_bytes(b"test compiler identity")
    monkeypatch.setattr(build, "ROOT", tree)
    monkeypatch.setattr(build, "compiler_command", lambda *_: ([str(compiler)], {"INCLUDE": str(include)}))
    monkeypatch.setattr(build, "search_inventory", lambda *_: "inventory")
    monkeypatch.setattr(build, "_include_search_roots", lambda *_: [include])
    monkeypatch.setattr(build, "_SWEEP_INCLUDE_DIRS", [])
    monkeypatch.setattr(build, "row_object", lambda *_: tree / "build/absent.obj")
    before = name_lane._missing_header_state(lane, [SOURCE], "missing.h")
    assert before is not None
    (include / "missing.h").write_text("// now supplied\n")
    after = name_lane._missing_header_state(lane, [SOURCE], "missing.h")
    assert after is not None and before != after



@pytest.fixture
def unrowed(tree, monkeypatch):
    import data_rows
    from test_data_rows import SECTIONS
    monkeypatch.setattr(data_rows, 'ROOT', tree)
    monkeypatch.setattr(data_rows, 'DATA_ROWS', tree / 'reverse/data_rows.csv')
    monkeypatch.setattr(data_rows, 'retail_sections', lambda: SECTIONS)
    (tree / 'reverse/data_rows.csv').write_text(data_rows.HEADER + '\n')
    lane = lane_of(tree)
    key = name_lane.register_data(lane, source=SOURCE, address='0x403100', address_kind='va', size=56,
                                 type_name='SampleContext', users=[SOURCE], evidence='fixture consumer returns this context')
    return tree, key


def serve_unrowed(tree, key, session, worker):
    be(worker)
    args = SimpleNamespace(session=session, model='fixture', count=1, file=SOURCE, key=[key], list_only=False)
    assert name_lane.cmd_next(lane_of(tree), args) == 0
    return json.loads((tree / f'build/name_lane/sessions/{session}.json').read_text())


def unrowed_vote(tree, key, session, worker, name, tmp_path, *, auto_workflow=False):
    record = serve_unrowed(tree, key, session, worker)
    item = record['files'][SOURCE]['items'][0]
    answer_key = name_lane.answer_key(*item[:3])
    answer = tmp_path / (session + '-answer.json')
    answer.write_text(json.dumps({answer_key: name}))
    args = SimpleNamespace(session=session, model='fixture', answer=str(answer), propose_only=not auto_workflow,
                           auto_workflow=auto_workflow, no_auto_review=True)
    assert name_lane.cmd_submit(lane_of(tree), args) == 0
    return lane_of(tree).state().get(key)


def agree_unrowed(tree, key, tmp_path):
    assert unrowed_vote(tree, key, 'first', 'first-worker', 'g_sampleContext', tmp_path) is None
    row = unrowed_vote(tree, key, 'second', 'second-worker', 'g_sampleContext', tmp_path)
    assert row['status'] == 'agreed'
    return row


def test_unrowed_data_uses_normal_blind_agreement_without_creating_placeholder(unrowed, tmp_path):
    tree, key = unrowed
    original = (tree / SOURCE).read_bytes()
    before = (tree / 'reverse/data_rows.csv').read_bytes()
    row = agree_unrowed(tree, key, tmp_path)
    assert row['kind'] == 'global' and row['rva'] == '0x00003100'
    assert (tree / SOURCE).read_bytes() == original
    assert (tree / 'reverse/data_rows.csv').read_bytes() == before
    assert not (tree / rename.NAME_BASIS).exists()
    brief = (tree / 'build/name_lane/briefs/second.txt').read_text()
    assert 'SampleContext' in brief and '0x00003100' in brief
    assert 'g_sampleContext' not in brief  # the second packet is blind


def test_unrowed_data_disagreement_adds_no_name_or_data_row(unrowed, tmp_path):
    tree, key = unrowed
    before = (tree / 'reverse/data_rows.csv').read_bytes()
    unrowed_vote(tree, key, 'first', 'first-worker', 'g_sampleContext', tmp_path)
    assert unrowed_vote(tree, key, 'second', 'second-worker', 'g_sampleState', tmp_path) is None
    assert (tree / 'reverse/data_rows.csv').read_bytes() == before
    assert not (tree / rename.NAME_BASIS).exists()


def test_unrowed_agreement_waits_for_data_admission_not_a_rename(unrowed, tmp_path, capsys):
    tree, key = unrowed
    agree_unrowed(tree, key, tmp_path)
    assert apply(tree, key=[key]) == 0
    assert lane_of(tree).state()[key]['status'] == 'agreed'
    assert '--admit-agreed' in capsys.readouterr().out


def admission_fixture(tree, monkeypatch, *, actual_size=56, wrong_byte=False):
    import data_rows, reloc_ledger
    from test_data_rows import write_coff, image_with, DATA
    obj = tree / 'build' / 'fixture.obj'; obj.parent.mkdir(exist_ok=True)
    symbol = '?g_sampleContext@@3USampleContext@@A'
    initializer = bytes(range(56))
    body = bytes([255]) + initializer[1:] if wrong_byte else initializer
    write_coff(obj, [('.data', DATA, body, len(body), [])], [(symbol, 0, 1, data_rows.EXTERNAL)])
    image = image_with(data=b'\0' * 0x100 + initializer)
    build = data_rows._tools()[0]
    monkeypatch.setattr(rename, 'ledger_checks', lambda ctx, plan: [])
    monkeypatch.setattr(build, 'obj_path', lambda source: obj)
    monkeypatch.setattr(build, 'compile_is_current', lambda *a, **kw: True)
    monkeypatch.setattr(reloc_ledger, 'Image', lambda: image)
    monkeypatch.setattr(data_rows, 'compiled_size', lambda source, symbol: (actual_size, 'fixture compiler sizeof'))
    (tree / SOURCE).write_text((tree / SOURCE).read_text() + '\nSampleContext g_sampleContext;\n')
    return data_rows, symbol


def test_unrowed_admission_records_inferred_basis_and_no_new_hatch(unrowed, tmp_path, monkeypatch):
    import hatch_counters
    tree, key = unrowed
    approval = agree_unrowed(tree, key, tmp_path)
    data_rows, symbol = admission_fixture(tree, monkeypatch)
    before = hatch_counters.scan(SOURCE, (tree / SOURCE).read_text())
    row = data_rows.admit_agreed(approval['id'], symbol, 'fixture')
    assert row['name'] == symbol and row['size'] == '56'
    basis = rows(tree, rename.NAME_BASIS)[-1]
    assert basis['basis'] == 'inferred' and basis['evidence'] == 'agree:' + approval['id']
    assert lane_of(tree).state()[key]['status'] == 'landed'
    assert hatch_counters.scan(SOURCE, (tree / SOURCE).read_text()) == before


@pytest.mark.parametrize('actual_size,wrong_byte,message', [(52, False, 'size 56 unproven'), (56, True, 'initializer differs')])
def test_unrowed_admission_refuses_size_and_byte_mismatches(unrowed, tmp_path, monkeypatch, actual_size, wrong_byte, message):
    tree, key = unrowed
    approval = agree_unrowed(tree, key, tmp_path)
    data_rows, symbol = admission_fixture(tree, monkeypatch, actual_size=actual_size, wrong_byte=wrong_byte)
    before = (tree / 'reverse/data_rows.csv').read_bytes()
    with pytest.raises(rename.Refusal, match=message):
        data_rows.admit_agreed(approval['id'], symbol, 'fixture')
    assert (tree / 'reverse/data_rows.csv').read_bytes() == before
    assert not (tree / rename.NAME_BASIS).exists()
    assert lane_of(tree).state()[key]['status'] == 'agreed'


def test_unrowed_admission_cannot_use_a_forged_agreement(unrowed, tmp_path, monkeypatch):
    tree, key = unrowed
    approval = agree_unrowed(tree, key, tmp_path)
    data_rows, symbol = admission_fixture(tree, monkeypatch)
    # Forged approval metadata is not a vote: the admission recomputes support.
    (tree / name_agreement.VOTES).write_text(','.join(name_agreement.VOTE_COLUMNS) + '\n')
    with pytest.raises(rename.Refusal, match='does not agree'):
        data_rows.admit_agreed(approval['id'], symbol, 'fixture')
    assert not (tree / rename.NAME_BASIS).exists()


def test_unrowed_data_rejects_address_derived_proposals_and_hand_added_hatches(unrowed, tmp_path):
    import hatch_counters
    tree, key = unrowed
    assert unrowed_vote(tree, key, 'first', 'first-worker', 'g_00403100', tmp_path) is None
    assert not lane_of(tree).votes()
    # Hand writing a source/global row still creates the existing address hatch;
    # the new admission path has not whitelisted or grown its baseline.
    source = (tree / SOURCE).read_text() + '\nint g_Va00403100;\n'
    grown = hatch_counters.scan(SOURCE, source) - hatch_counters.scan(SOURCE, (tree / SOURCE).read_text())
    assert grown[('address_global', SOURCE, 'g_Va00403100')] == 1



def test_unrowed_data_va_and_rva_register_same_key(unrowed):
    tree, key = unrowed
    again = name_lane.register_data(lane_of(tree), source=SOURCE, address='0x3100', address_kind='rva', size=56,
                                   type_name='SampleContext', users=[SOURCE], evidence='fixture consumer returns this context')
    assert again == key
    assert len(rows(tree, name_lane.DATA_REQUESTS)) == 1


def test_unrowed_data_changed_user_evidence_cannot_reuse_votes(unrowed):
    tree, key = unrowed
    other = 'Code/Game/Slow.cpp'
    request = name_lane.register_data(lane_of(tree), source=SOURCE, address='0x3200', address_kind='rva', size=56,
                                     type_name='SampleContext', users=[other], evidence='fixture second context')
    (tree / other).write_text('// changed evidence\n')
    row = name_lane.request_for_key(lane_of(tree), request)
    with pytest.raises(rename.Refusal, match='user evidence changed'):
        name_lane.check_unrowed(lane_of(tree), row)


def test_unrowed_admission_rejects_forged_address_name(unrowed, tmp_path, monkeypatch):
    tree, key = unrowed
    approval = agree_unrowed(tree, key, tmp_path)
    data_rows, symbol = admission_fixture(tree, monkeypatch)
    lane = lane_of(tree)
    lane.append(name_agreement.AGREED, name_agreement.AGREED_COLUMNS,
                [{**approval, 'new': 'g_Va00403100'}])
    before = (tree / 'reverse/data_rows.csv').read_bytes()
    with pytest.raises(rename.Refusal):
        data_rows.admit_agreed(approval['id'], '?g_Va00403100@@3HA', 'fixture')
    assert (tree / 'reverse/data_rows.csv').read_bytes() == before
    assert not (tree / rename.NAME_BASIS).exists()


def test_unrowed_request_metadata_change_invalidates_agreement(unrowed, tmp_path, monkeypatch):
    tree, key = unrowed
    approval = agree_unrowed(tree, key, tmp_path)
    data_rows, symbol = admission_fixture(tree, monkeypatch)
    path = tree / name_lane.DATA_REQUESTS
    path.write_text(path.read_text().replace(',56,', ',52,'))
    with pytest.raises(rename.Refusal, match='registered unrowed'):
        data_rows.admit_agreed(approval['id'], symbol, 'fixture')
    assert not (tree / rename.NAME_BASIS).exists()



def test_new_unrowed_key_can_be_served_after_worker_voted_on_same_file(unrowed, tmp_path):
    tree, key = unrowed
    vote(tree, tmp_path, 'prior-function', {'rva00401000': 'sumBox'}, worker='first-worker')
    record = serve_unrowed(tree, key, 'new-data', 'first-worker')
    assert any(name_lane.key_of(SOURCE, *item[:3]) == key for item in record['files'][SOURCE]['items'])



def test_unrowed_admission_rolls_back_if_object_moves_during_size_probe(unrowed, tmp_path, monkeypatch):
    tree, key = unrowed
    approval = agree_unrowed(tree, key, tmp_path)
    data_rows, symbol = admission_fixture(tree, monkeypatch)
    build = data_rows._tools()[0]
    obj = build.obj_path(tree / SOURCE)
    original = data_rows.compiled_size
    def mutate(source, symbol):
        result = original(source, symbol)
        obj.write_bytes(obj.read_bytes() + b'changed')
        return result
    monkeypatch.setattr(data_rows, 'compiled_size', mutate)
    before = (tree / 'reverse/data_rows.csv').read_bytes()
    with pytest.raises(rename.Refusal, match='changed during data admission'):
        data_rows.admit_agreed(approval['id'], symbol, 'fixture')
    assert (tree / 'reverse/data_rows.csv').read_bytes() == before
    assert not (tree / rename.NAME_BASIS).exists()



def test_unrowed_data_stale_user_request_can_be_served_with_fresh_key(unrowed):
    tree, _ = unrowed
    other = 'Code/Game/Slow.cpp'
    kwargs = dict(source=SOURCE, address='0x3200', address_kind='rva', size=56,
                  type_name='SampleContext', users=[other], evidence='fixture refreshed user context')
    first = name_lane.register_data(lane_of(tree), **kwargs)
    (tree / other).write_text('// new user evidence\n')
    second = name_lane.register_data(lane_of(tree), **kwargs)
    assert first != second
    be('fresh-reviewer')
    live = {name_lane.key_of(SOURCE, *item[:3]) for item in name_lane.data_request_items(lane_of(tree), SOURCE)}
    assert second in live and first not in live



def test_unrowed_admission_requires_current_compiled_object(unrowed, tmp_path, monkeypatch):
    tree, key = unrowed
    approval = agree_unrowed(tree, key, tmp_path)
    data_rows, symbol = admission_fixture(tree, monkeypatch)
    monkeypatch.setattr(data_rows._tools()[0], 'compile_is_current', lambda *a, **kw: False)
    before = (tree / 'reverse/data_rows.csv').read_bytes()
    with pytest.raises(rename.Refusal, match='current compiler receipt'):
        data_rows.admit_agreed(approval['id'], symbol, 'fixture')
    assert (tree / 'reverse/data_rows.csv').read_bytes() == before
    assert not (tree / rename.NAME_BASIS).exists()



def test_normal_submit_auto_workflow_defers_unrowed_approval_to_admission(unrowed, tmp_path):
    tree, key = unrowed
    original = (tree / SOURCE).read_bytes()
    unrowed_vote(tree, key, 'first', 'first-worker', 'g_sampleContext', tmp_path)
    result = unrowed_vote(tree, key, 'second', 'second-worker', 'g_sampleContext', tmp_path, auto_workflow=True)
    assert result['status'] == 'agreed'
    assert (tree / SOURCE).read_bytes() == original
    assert not (tree / rename.NAME_BASIS).exists()



@pytest.mark.parametrize('ledger', ['function', 'pin', 'shared_identifier', 'data_row', 'converged'])
def test_unrowed_admission_refuses_name_collisions(unrowed, tmp_path, monkeypatch, ledger):
    import data_rows
    tree, key = unrowed
    approval = agree_unrowed(tree, key, tmp_path)
    data_rows, symbol = admission_fixture(tree, monkeypatch)
    if ledger == 'pin':
        with (tree / 'reverse/symbols.csv').open('a') as f:
            csv.writer(f).writerow([symbol, '0x00002000', 'existing pin'])
    elif ledger in ('function', 'shared_identifier'):
        name = '?g_sampleContext@@YAXXZ' if ledger == 'function' else '?useContext@@YAXPAUg_sampleContext@@@Z'
        with (tree / 'reverse/functions.csv').open('a') as f:
            csv.writer(f).writerow([name, '', '0x00001010', '1', SOURCE, 'matched', ''])
    elif ledger == 'data_row':
        with (tree / 'reverse/data_rows.csv').open('a') as f:
            csv.writer(f).writerow([symbol, '0x00003500', 'rva', '56', '.data', SOURCE, 'matched', 'existing', 'fixture'])
    else:
        (tree / 'reverse/data_converged.csv').write_text('address,name,evidence\n0x00403500,' + symbol + ',existing owner\n')
    before = (tree / 'reverse/data_rows.csv').read_bytes()
    with pytest.raises(rename.Refusal, match='already names|already spells'):
        data_rows.admit_agreed(approval['id'], symbol, 'fixture')
    assert (tree / 'reverse/data_rows.csv').read_bytes() == before
    assert not (tree / rename.NAME_BASIS).exists()


def test_unrowed_admission_refuses_second_thewritableglobaldata_address(unrowed, tmp_path):
    import data_rows
    tree, _ = unrowed
    key = name_lane.register_data(lane_of(tree), source=SOURCE, address='0x3200', address_kind='rva', size=4,
                                 type_name='GlobalData *', users=[SOURCE], evidence='fixture 4-byte global')
    unrowed_vote(tree, key, 'pointer-first', 'first-worker', 'TheWritableGlobalData', tmp_path)
    approval = unrowed_vote(tree, key, 'pointer-second', 'second-worker', 'TheWritableGlobalData', tmp_path)
    symbol = '?TheWritableGlobalData@@3PAVGlobalData@@A'
    (tree / 'reverse/data_converged.csv').write_text('address,name,evidence\n0x009FE758,' + symbol + ',existing owner\n')
    with pytest.raises(rename.Refusal, match='already names a converged global'):
        data_rows.admit_agreed(approval['id'], symbol, 'fixture')
    assert not (tree / rename.NAME_BASIS).exists()


def test_unrowed_admission_runs_ordinary_ledger_checks(unrowed, tmp_path, monkeypatch):
    tree, key = unrowed
    approval = agree_unrowed(tree, key, tmp_path)
    data_rows, symbol = admission_fixture(tree, monkeypatch)
    checked = []
    monkeypatch.setattr(rename, 'ledger_checks', lambda ctx, plan: checked.append(bool(plan.after)) or [])
    data_rows.admit_agreed(approval['id'], symbol, 'fixture')
    assert checked == [False, True]


def test_unrowed_registrant_cannot_be_served_or_submit_a_vote(unrowed, tmp_path):
    tree, key = unrowed
    lane = lane_of(tree)
    request = name_lane.request_for_key(lane, key)
    assert request['registrant'] == lane.worker()
    args = SimpleNamespace(session='registrant', model='fixture', count=1, file=SOURCE, key=[key], list_only=False)
    assert name_lane.cmd_next(lane, args) == 0
    record = tree / 'build/name_lane/sessions/registrant.json'
    assert not record.exists()
    # A manually restored session cannot bypass the submit-time eligibility check.
    _, kind, scope, ident = name_lane.split_key(key)
    text = lane.text(SOURCE)
    import hashlib
    record.parent.mkdir(parents=True, exist_ok=True)
    record.write_text(json.dumps(dict(model='fixture', worker=lane.worker(), files={SOURCE: dict(
        sha=hashlib.sha256(text.encode()).hexdigest(), items=[[kind, scope, ident, 0x3100]])})))
    answer = tmp_path / 'registrant-answer.json'
    answer.write_text(json.dumps({name_lane.answer_key(kind, scope, ident): 'g_keyContext'}))
    submit = SimpleNamespace(session='registrant', model='fixture', answer=str(answer), propose_only=True)
    assert name_lane.cmd_submit(lane, submit) == 0
    assert lane_of(tree).votes() == []


def test_unrowed_blind_packets_hide_evidence_prose_and_keep_only_references(unrowed):
    tree, _ = unrowed
    key = name_lane.register_data(lane_of(tree), source=SOURCE, address='0x3200', address_kind='rva', size=56,
                                 type_name='SampleContext', users=[SOURCE],
                                 evidence='this is g_keyContext; see ' + SOURCE + ':2')
    serve_unrowed(tree, key, 'blind-prose', 'independent-reviewer')
    brief = (tree / 'build/name_lane/briefs/blind-prose.txt').read_text()
    assert 'g_keyContext' not in brief and 'this is' not in brief
    packet = name_lane.request_packet(lane_of(tree), key)
    assert 'g_keyContext' not in json.dumps(packet)
    assert packet['evidence'] == [{'file': SOURCE, 'line': 2}]
    assert packet['type'] == 'SampleContext' and packet['size'] == '56'


def test_unrowed_admission_recomputes_quorum_excluding_registrant(unrowed, tmp_path, monkeypatch):
    tree, key = unrowed
    approval = agree_unrowed(tree, key, tmp_path)
    data_rows, symbol = admission_fixture(tree, monkeypatch)
    registrant = name_lane.request_for_key(lane_of(tree), key)['registrant']
    path = tree / name_agreement.VOTES
    votes = rows(tree, name_agreement.VOTES)
    votes[0]['worker'] = registrant  # forged historical vote, not counted at admission
    with path.open('w') as f:
        writer = csv.DictWriter(f, name_agreement.VOTE_COLUMNS); writer.writeheader(); writer.writerows(votes)
    with pytest.raises(rename.Refusal, match='excludes the registrant'):
        data_rows.admit_agreed(approval['id'], symbol, 'fixture')
    assert not (tree / rename.NAME_BASIS).exists()



def test_unrowed_admission_rolls_back_on_ordinary_ledger_refusal(unrowed, tmp_path, monkeypatch):
    tree, key = unrowed
    approval = agree_unrowed(tree, key, tmp_path)
    data_rows, symbol = admission_fixture(tree, monkeypatch)
    before = (tree / 'reverse/data_rows.csv').read_bytes()
    def reject(ctx, plan):
        if plan.after:
            assert SOURCE in plan.after and name_lane.VOTES in plan.after and name_lane.DATA_REQUESTS in plan.after
            return ['fixture ledger refusal']
        return []
    monkeypatch.setattr(rename, 'ledger_checks', reject)
    with pytest.raises(rename.VerifyFailed, match='fixture ledger refusal'):
        data_rows.admit_agreed(approval['id'], symbol, 'fixture')
    assert (tree / 'reverse/data_rows.csv').read_bytes() == before
    assert not (tree / rename.NAME_BASIS).exists()
    assert lane_of(tree).state()[key]['status'] == 'agreed'


def test_reregistering_data_does_not_replace_original_registrant(unrowed):
    tree, key = unrowed
    original = name_lane.request_for_key(lane_of(tree), key)['registrant']
    be('another-worker')
    repeated = name_lane.register_data(lane_of(tree), source=SOURCE, address='0x403100', address_kind='va', size=56,
                                      type_name='SampleContext', users=[SOURCE], evidence='fixture consumer returns this context')
    assert repeated == key
    assert name_lane.request_for_key(lane_of(tree), key)['registrant'] == original


def write_upper_bound(tree, *, source=''):
    import data_ledger
    row = dict(address='0x000030E0', size=88, section='.data', kind='global',
               name='?g_previous@@3HA', source=source,
               status='owned' if source else 'unowned', names='', defs=1 if source else 0, refs=2)
    (tree / 'reverse/data_ledger.csv').write_text(data_ledger.render([row]))


def test_unrowed_registration_allows_and_notes_unowned_upper_bound(unrowed, capsys):
    tree, key = unrowed
    write_upper_bound(tree)
    again = name_lane.register_data(lane_of(tree), source=SOURCE, address='0x403100', address_kind='va', size=56,
                                   type_name='SampleContext', users=[SOURCE], evidence='fixture consumer returns this context')
    assert again == key
    note = capsys.readouterr().err
    assert 'note:' in note and 'unowned data_ledger.csv upper bound overlaps' in note
    assert '?g_previous@@3HA' in note and '0x000030E0' in note
    assert 'not a proven extent' in note


@pytest.mark.parametrize('overlap', ['owned', 'proven'])
def test_unrowed_registration_refuses_owned_or_proven_overlap(unrowed, overlap):
    tree, _ = unrowed
    write_upper_bound(tree, source=SOURCE if overlap == 'owned' else '')
    if overlap == 'proven':
        import data_rows
        row = dict(name='?g_previous@@3HA', address='0x30E0', address_kind='rva', size='88',
                   section='.data', source=SOURCE, status='matched', evidence='verified', model='fixture')
        (tree / 'reverse/data_rows.csv').write_text(data_rows.HEADER + '\n' + ','.join(row[c] for c in data_rows.FIELDS) + '\n')
    with pytest.raises(rename.Refusal, match='overlapping .* owner'):
        name_lane.register_data(lane_of(tree), source=SOURCE, address='0x403100', address_kind='va', size=56,
                                type_name='SampleContext', users=[SOURCE], evidence='fixture consumer returns this context')


def test_unrowed_admission_splits_unowned_bound_and_keeps_own_verified_extent(unrowed, tmp_path, monkeypatch):
    import data_ledger
    tree, key = unrowed
    write_upper_bound(tree)
    approval = agree_unrowed(tree, key, tmp_path)
    data_rows, symbol = admission_fixture(tree, monkeypatch)
    cache = tree / 'reverse/data_ledger.csv'
    before = cache.read_bytes()
    row = data_rows.admit_agreed(approval['id'], symbol, 'fixture')
    assert row['size'] == '56'
    ledger = data_ledger.load(cache)
    assert ledger[0x30E0]['size'] == 32
    assert ledger[0x3100]['size'] == '56' and ledger[0x3100]['name'] == symbol
    assert cache.read_bytes() == before  # the tool-written cache is reconciled on read


def register_large_data_request(tree, length):
    (tree / name_lane.DATA_REQUESTS).unlink()
    original = (tree / SOURCE).read_text()
    padding = '// padding outside evidence\n' * (length // 28 + 1)
    content = original + padding + '// EVIDENCE_CONTEXT_MARKER\n'
    (tree / SOURCE).write_text(content)
    line = len(content.splitlines())
    return name_lane.register_data(lane_of(tree), source=SOURCE, address='0x403100', address_kind='va', size=56,
                                   type_name='SampleContext', users=[SOURCE], evidence=f'{SOURCE}:{line}')


@pytest.mark.parametrize('length', [19089, 80327])
def test_large_defining_file_serves_registered_data_with_evidence_excerpts(unrowed, length):
    import hashlib
    tree, _ = unrowed
    key = register_large_data_request(tree, length)
    record = serve_unrowed(tree, key, 'large-data', 'independent-worker')
    entry = record['files'][SOURCE]
    assert entry['sha'] == hashlib.sha256((tree / SOURCE).read_bytes()).hexdigest()
    assert len(entry['items']) == 1
    brief = (tree / 'build/name_lane/briefs/large-data.txt').read_text()
    assert 'EXCERPTS' in brief and 'EVIDENCE_CONTEXT_MARKER' in brief
    assert len(brief) < name_lane.MAX_CHARS
    assert (tree / SOURCE).read_text() not in brief
    request = name_lane.request_packet(lane_of(tree), key)
    assert 'EXCERPTS' in request['user_sources'][SOURCE]


def test_oversized_file_without_registered_data_reports_skip_reason(tree, capsys):
    (tree / SOURCE).write_text((tree / SOURCE).read_text() + '// large\n' * 3000)
    args = SimpleNamespace(session='large-no-data', model='fixture', count=1, file=SOURCE, list_only=False)
    assert name_lane.cmd_next(lane_of(tree), args) == 0
    err = capsys.readouterr().err
    assert SOURCE in err and '15000 character limit' in err and 'no eligible registered data request' in err
    assert not (tree / 'build/name_lane/sessions/large-no-data.json').exists()


def test_an_explicit_max_chars_serves_an_oversized_file(tree, capsys):
    """Every key in a long unit is otherwise unreachable for shared naming.

    Without a registered data request the lane passes a long source over
    entirely, so the keys in it can never be voted on, however few of them you
    ask for: `--max-keys` is applied after this gate. An operator who asks for a
    bigger packet is told what they asked for, and sees the whole source, so the
    vote still rests on the full text that its hash fences.
    """
    (tree / SOURCE).write_text((tree / SOURCE).read_text() + '// large\n' * 3000)
    size = len((tree / SOURCE).read_text())
    assert size > name_lane.MAX_CHARS, 'the fixture must exceed the default gate'
    args = SimpleNamespace(session='large-opt-in', model='fixture', count=1, file=SOURCE,
                           list_only=False, max_chars=size * 4)
    assert name_lane.cmd_next(lane_of(tree), args) == 0
    err = capsys.readouterr().err
    assert 'character limit' not in err, err
    record = json.loads((tree / 'build/name_lane/sessions/large-opt-in.json').read_text())
    assert record['files'][SOURCE]['items'], 'the oversized file must serve its keys'


def test_a_small_max_chars_never_makes_a_servable_file_ineligible(tree, capsys):
    """The flag raises the eligibility bar and never lowers it.

    A value under the default would otherwise turn files that serve today into
    skips. Trimming the packet is still allowed to drop targets, which is a
    different outcome with its own message.
    """
    args = SimpleNamespace(session='small-cap', model='fixture', count=1, file=SOURCE,
                           list_only=False, max_chars=200)
    assert name_lane.cmd_next(lane_of(tree), args) == 0
    assert 'character limit' not in capsys.readouterr().err



def resolved_unrowed(tree, key, tmp_path):
    unrowed_vote(tree, key, 'r-first', 'first-worker', 'g_otherContext', tmp_path)
    unrowed_vote(tree, key, 'r-second', 'second-worker', 'g_sampleContext', tmp_path)
    unrowed_vote(tree, key, 'r-third', 'third-worker', 'g_sampleContext', tmp_path)
    be('first-worker')
    name_lane.cmd_resolve(lane_of(tree), SimpleNamespace(key=key, name='g_sampleContext',
                                                       reason='Reviewed the context users and accepted their role'))
    paths = [SOURCE, name_lane.DATA_REQUESTS, name_lane.VOTES, name_lane.AGREED, name_lane.RESOLUTIONS]
    _git(tree, 'add', '--', *paths)
    _git(tree, '-c', 'user.name=Fixture', '-c', 'user.email=fixture@example.invalid', 'commit', '-qm', 'Resolved data name')
    return lane_of(tree).state()[key]


def test_unrowed_resolution_accepts_only_added_definition_and_preserves_ordinary_rename(unrowed, tmp_path, monkeypatch):
    tree, key = unrowed
    approval = resolved_unrowed(tree, key, tmp_path)
    data_rows, symbol = admission_fixture(tree, monkeypatch)
    source = tree / SOURCE
    source.write_text(source.read_text().replace('SampleContext g_sampleContext;', 'SampleContext g_sampleContext = {0};'))
    with pytest.raises(rename.Refusal, match='source changed'):
        rename.check_agreement(lane_of(tree).ctx, 'global', 'agree:' + approval['id'],
                               {approval['old']}, {approval['new']}, 0x3100)
    data_rows.admit_agreed(approval['id'], symbol, 'fixture')
    assert lane_of(tree).state()[key]['status'] == 'landed'


@pytest.mark.parametrize('edit', ['unrelated', 'removed', 'wrong-name', 'wrong-type', 'extra-symbol', 'call', 'size'])
def test_unrowed_resolution_refuses_changes_outside_agreed_definition(unrowed, tmp_path, monkeypatch, edit):
    tree, key = unrowed
    approval = resolved_unrowed(tree, key, tmp_path)
    data_rows, symbol = admission_fixture(tree, monkeypatch, actual_size=52 if edit == 'size' else 56)
    source = tree / SOURCE
    text = source.read_text().replace('SampleContext g_sampleContext;', 'SampleContext g_sampleContext = {0};')
    if edit == 'unrelated': text = text.replace('return iVar3;', 'return 7;')
    elif edit == 'removed': text = text.replace('    int m_count;\n', '')
    elif edit == 'wrong-name': text = text.replace('SampleContext g_sampleContext =', 'SampleContext g_wrongContext =')
    elif edit == 'wrong-type': text = text.replace('SampleContext g_sampleContext =', 'int g_sampleContext =')
    elif edit == 'extra-symbol': text += '\nint unrelatedGlobal = {0};\n'
    elif edit == 'call': text = text.replace('= {0};', '= {sideEffect()};')
    source.write_text(text)
    before = (tree / 'reverse/data_rows.csv').read_bytes()
    with pytest.raises(rename.Refusal):
        data_rows.admit_agreed(approval['id'], symbol, 'fixture')
    assert (tree / 'reverse/data_rows.csv').read_bytes() == before
    assert lane_of(tree).state()[key]['status'] == 'agreed'


def test_unrowed_delta_allows_six_literal_contexts_only():
    import data_rows
    base = b'struct Context { int value[14]; };\n\nint getter();\n'
    candidates = {f'g_context{i}': (dict(type='Context'), {}) for i in range(6)}
    definitions = ''.join(f'Context g_context{i} = {{ {{ 0x41, 0x13, 0 }} }}; // context\n' for i in range(6))
    current = base.replace(b'\nint getter();', ('\n// data definitions\n' + definitions + '\nint getter();').encode())
    assert data_rows._admission_definitions(base, current, candidates) == list(candidates)
    with pytest.raises(rename.Refusal):
        data_rows._admission_definitions(base, current + b'int extra = {0};\n', candidates)



def test_six_resolved_definitions_admit_sequentially_and_verify_peer_sizes(unrowed, tmp_path, monkeypatch):
    import hashlib, data_rows, reloc_ledger
    from test_data_rows import write_coff, image_with, DATA
    tree, key = unrowed
    first = resolved_unrowed(tree, key, tmp_path)
    sha = hashlib.sha256((tree / SOURCE).read_bytes()).hexdigest()
    approvals = [first]
    names = ['g_sampleContext', 'g_alphaKeys', 'g_betaKeys', 'g_gammaKeys', 'g_deltaKeys', 'g_epsilonKeys']
    for i, name in enumerate(names[1:], 1):
        be('registrant-peer')
        lane = lane_of(tree)
        k = name_lane.register_data(lane, source=SOURCE, address=hex(0x3100 + i * 56), address_kind='rva',
                                   size=56, type_name='SampleContext', users=[SOURCE], evidence='synthetic context')
        votes = [dict(key=k, hash=name_agreement.digest(k, name), worker='w-' + digit * 12,
                      model='fixture', session='fixture', date='2026-11-06') for digit in ('a', 'b')]
        lane.append(name_lane.VOTES, name_lane.VOTE_COLUMNS, votes)
        row = dict(first, id='nr-' + hashlib.sha256(f'{k}|{name}|{sha}'.encode()).hexdigest()[:24],
                   key=k, new=name, rva=hex(0x3100 + i * 56), agents='', detail='fixture resolution')
        lane.append(name_lane.AGREED, name_lane.AGREED_COLUMNS, [row])
        approvals.append(row)
    _git(tree, 'add', '--', name_lane.DATA_REQUESTS, name_lane.VOTES, name_lane.AGREED)
    _git(tree, '-c', 'user.name=Fixture', '-c', 'user.email=fixture@example.invalid', 'commit', '-qm', 'Resolve peer names')
    image_class = reloc_ledger.Image
    data_rows, _ = admission_fixture(tree, monkeypatch)
    source = tree / SOURCE
    source.write_text(source.read_text().replace('SampleContext g_sampleContext;',
        '\n'.join(f'SampleContext {name} = {{0}};' for name in names)))
    obj = tree / 'build/fixture.obj'
    symbols = [f'?{name}@@3USampleContext@@A' for name in names]
    initializer = bytes(range(56))
    write_coff(obj, [('.data', DATA, initializer * 6, 56 * 6, [])],
               [(name, i * 56, 1, data_rows.EXTERNAL) for i, name in enumerate(symbols)])
    monkeypatch.setattr(reloc_ledger, 'Image', image_class)
    image = image_with(data=b'\0' * 0x100 + initializer * 6)
    monkeypatch.setattr(reloc_ledger, 'Image', lambda: image)
    # Even an admission of the first symbol must refuse a wrong-sized peer.
    monkeypatch.setattr(data_rows, 'compiled_size', lambda source, symbol: (52 if symbol == symbols[-1] else 56, 'fixture'))
    with pytest.raises(rename.Refusal, match='size 56 unproven'):
        data_rows.admit_agreed(first['id'], symbols[0], 'fixture')
    assert not rows(tree, 'reverse/data_rows.csv')
    monkeypatch.setattr(data_rows, 'compiled_size', lambda *args: (56, 'fixture'))
    for approval, symbol in zip(approvals, symbols):
        data_rows.admit_agreed(approval['id'], symbol, 'fixture')
    assert len(rows(tree, 'reverse/data_rows.csv')) == 6


WB_HEADER = "target_rva,current_name,current_kind,wb_name,wb_file,score,evidence\n"


@pytest.mark.parametrize("wb_name,served", [
    ("", True),                     # a PLACEHOLDER pairing names nothing: the key is the lane's
    ("SampleBox::sumWidth", False),  # a named lead is WorldBuilder's: withheld, as rename.py refuses it
])
def test_only_a_named_worldbuilder_lead_withholds_a_function(tree, wb_name, served):
    """name_lane withholds exactly the leads rename.py's inferred guard counts (rename.wb_lead_names)."""
    (tree / rename.WB_LEADS).write_bytes(
        (WB_HEADER + f"0x00401000,Rva00401000Box::rva00401000,PLACEHOLDER,{wb_name},,1.0000,callgraph\n").encode())
    _git(tree, "add", "-A")
    lane = lane_of(tree)
    function_keys = [i[:3] for i in lane.owned(SOURCE) if i[0] == "function"]
    assert (("function", "0x00401000", "rva00401000") in function_keys) is served
    assert bool(rename.wb_rows(lane.ctx, 0x00401000)) is not served


# ---------------------------------------------------------------- votes that agree with no record

def concurrent_votes(tree, key, answer, count=2, fingerprint=True):
    """`count` workers' votes for `answer`, as if each submit ran before the others existed:
    separate checkouts, separate pushes. Only the vote rows land; no agreement does."""
    lane = lane_of(tree)
    h = name_agreement.digest(key, answer)
    lane.append(name_lane.VOTES, name_lane.VOTE_COLUMNS, [
        dict(key=key, hash=h, model=f"model-{i}", session=f"s{i}", worker=f"w-00000000000{i}", date="2026-11-07")
        for i in range(count)])
    text = lane.text(key.split("|")[0])
    if fingerprint and text is not None:
        sha = hashlib.sha256(text.encode("utf-8", "surrogateescape")).hexdigest()
        lane.append(name_lane.VOTE_SOURCES, name_lane.VOTE_SOURCE_COLUMNS, [
            dict(key=key, hash=h, worker=f"w-00000000000{i}", session=f"s{i}", source_sha=sha) for i in range(count)])


def agree(tree, key, name, *extra):
    return name_lane.main(["agree", "--key", key, "--name", name, *extra], lane=lane_of(tree))


def test_concurrent_votes_are_found_and_recorded_without_a_new_vote(tree, capsys):
    concurrent_votes(tree, MEMBER_KEY, "m_boxWidth")
    assert MEMBER_KEY not in lane_of(tree).state()
    assert name_lane.unrecorded_agreements(lane_of(tree)) == [MEMBER_KEY]
    votes_before = len(lane_of(tree).votes())
    assert name_lane.main(["status"], lane=lane_of(tree)) == 0
    out = capsys.readouterr().out
    assert "1 key(s) have agreeing votes and no agreement record" in out and MEMBER_KEY in out
    assert agree(tree, MEMBER_KEY, "m_boxWidth") == 0
    row = lane_of(tree).state()[MEMBER_KEY]
    assert row["status"] == "agreed" and row["new"] == "m_boxWidth" and len(lane_of(tree).votes()) == votes_before
    assert row["agents"] == "w-000000000000@model-0;w-000000000001@model-1"
    assert name_agreement.verify(lane_of(tree).votes(), lane_of(tree).agreed_rows(), MEMBER_KEY, "m_boxWidth") == []
    assert name_lane.unrecorded_agreements(lane_of(tree)) == []


def test_a_word_order_difference_is_the_same_agreement(tree):
    """Votes match on canon(): any spelling with the voters' hash records their agreement."""
    concurrent_votes(tree, MEMBER_KEY, "m_boxWidth")
    assert agree(tree, MEMBER_KEY, "m_widthBox") == 0
    assert lane_of(tree).state()[MEMBER_KEY]["new"] == "m_widthBox"


def test_a_spelling_the_voters_did_not_propose_is_refused(tree):
    concurrent_votes(tree, MEMBER_KEY, "m_boxWidth")
    with pytest.raises(SystemExit):
        agree(tree, MEMBER_KEY, "m_boxHeight")
    assert MEMBER_KEY not in lane_of(tree).state()


def test_one_vote_is_no_agreement(tree):
    concurrent_votes(tree, MEMBER_KEY, "m_boxWidth", count=1)
    assert name_lane.unrecorded_agreements(lane_of(tree)) == []
    with pytest.raises(SystemExit):
        agree(tree, MEMBER_KEY, "m_boxWidth")


def test_a_recorded_or_tied_key_is_not_unrecorded(tree):
    concurrent_votes(tree, MEMBER_KEY, "m_boxWidth")
    assert agree(tree, MEMBER_KEY, "m_boxWidth") == 0
    with pytest.raises(SystemExit):
        agree(tree, MEMBER_KEY, "m_boxWidth")
    lane_of(tree).append(name_lane.VOTES, name_lane.VOTE_COLUMNS, [
        dict(key=FN_KEY, hash=name_agreement.digest(FN_KEY, spelled), model="m", session=f"s{i}",
             worker=f"w-00000000001{i}", date="2026-11-07")
        for i, spelled in enumerate(("sumBox", "sumBox", "addBox", "addBox"))])
    assert FN_KEY not in name_lane.unrecorded_agreements(lane_of(tree))


def test_a_disputed_spelling_stays_refused(tree):
    concurrent_votes(tree, MEMBER_KEY, "m_boxWidth")
    assert agree(tree, MEMBER_KEY, "m_boxWidth") == 0
    row = lane_of(tree).state()[MEMBER_KEY]
    lane_of(tree).append(name_lane.AGREED, name_lane.AGREED_COLUMNS, [dict(row, agents="", status="disputed")])
    assert name_lane.unrecorded_agreements(lane_of(tree)) == []
    with pytest.raises(SystemExit):
        agree(tree, MEMBER_KEY, "m_boxWidth")


def test_a_placeholder_that_has_gone_is_only_counted(tree, capsys):
    gone = "Code/Game/Gone.cpp|member|Rva00401000Base|m_04"
    concurrent_votes(tree, gone, "m_boxWidth")
    assert name_lane.main(["status"], lane=lane_of(tree)) == 0
    out = capsys.readouterr().out
    assert "0 key(s) have agreeing votes" in out and "1 more name a file or placeholder that has gone" in out
    assert gone not in out
    with pytest.raises(SystemExit):
        agree(tree, gone, "m_boxWidth")


def test_apply_reports_them_and_lands_them_once_recorded(tree, capsys):
    concurrent_votes(tree, MEMBER_KEY, "m_boxWidth")
    assert apply(tree) == 0
    assert "1 key(s) have agreeing votes and no agreement record" in capsys.readouterr().out
    assert MEMBER_KEY not in lane_of(tree).state()
    assert agree(tree, MEMBER_KEY, "m_boxWidth") == 0
    assert apply(tree) == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "landed"


def test_submitting_a_counted_vote_again_records_the_agreement(tree, tmp_path):
    """The live refusal: two sessions served to one worker before its vote; another checkout's
    vote lands between. The second submit adds no vote and records what the votes now say."""
    answers = {"Rva00401000Box::m_x2C": "m_boxWidth", "rva00401000": "skip"}
    serve(tree, "later", worker="seat-a")
    assert vote(tree, tmp_path, "first", answers, worker="seat-a") == 0
    assert MEMBER_KEY not in lane_of(tree).state()
    h = name_agreement.digest(MEMBER_KEY, "m_boxWidth")
    lane_of(tree).append(name_lane.VOTES, name_lane.VOTE_COLUMNS, [dict(
        key=MEMBER_KEY, hash=h, model="other", session="b", worker="w-000000000002", date="2026-11-07")])
    sha = hashlib.sha256(lane_of(tree).text(SOURCE).encode("utf-8", "surrogateescape")).hexdigest()
    lane_of(tree).append(name_lane.VOTE_SOURCES, name_lane.VOTE_SOURCE_COLUMNS, [dict(
        key=MEMBER_KEY, hash=h, worker="w-000000000002", session="b", source_sha=sha)])
    votes_before = len(lane_of(tree).votes())
    answer = tmp_path / "answer-later.json"
    answer.write_text(json.dumps(answers))
    args = SimpleNamespace(answer=str(answer), session="later", model="claude-opus-5-5")
    assert name_lane.cmd_submit(lane_of(tree), args, lead=2, min_models=1) == 0
    row = lane_of(tree).state()[MEMBER_KEY]
    assert row["status"] == "agreed" and len(lane_of(tree).votes()) == votes_before


def test_submitting_again_with_no_agreement_is_still_refused(tree, tmp_path, capsys):
    answers = {"Rva00401000Box::m_x2C": "m_boxWidth", "rva00401000": "skip"}
    serve(tree, "later", worker="seat-a")
    assert vote(tree, tmp_path, "first", answers, worker="seat-a") == 0
    answer = tmp_path / "answer-later.json"
    answer.write_text(json.dumps(answers))
    args = SimpleNamespace(answer=str(answer), session="later", model="claude-opus-5-5")
    name_lane.cmd_submit(lane_of(tree), args, lead=2, min_models=1)
    assert "already voted" in capsys.readouterr().out
    assert MEMBER_KEY not in lane_of(tree).state()


# ---------------------------------------------------------------- compiler-spelled rows

SPELLED_OLD = "??4?$map@URva00401000Box@@H@@QAEAAV0@ABV0@@Z"
SPELLED_NEW = "??4?$set@UBfmeRecord@@@@QAEAAV0@ABV0@@Z"
SPELLED_KEY = name_lane.key_of(SOURCE, "function", "0x00401100", SPELLED_OLD)


@pytest.fixture
def spelled_tree(tree):
    with open(tree / "reverse/functions.csv", "a", encoding="utf-8", newline="") as handle:
        handle.write(f"{SPELLED_OLD},,0x00401100,18,{SOURCE},matched,\n")
    _git(tree, "add", "-A")
    _git(tree, "-c", "user.name=t", "-c", "user.email=t@example.invalid", "commit", "-qm", "an operator row")
    return tree


def serve_key(root, session, worker, key=SPELLED_KEY):
    be(worker)
    args = SimpleNamespace(session=session, model="claude-opus-5-5", count=1, file=SOURCE, list_only=False, key=[key])
    assert name_lane.cmd_next(lane_of(root), args) == 0
    return json.loads((root / f"build/name_lane/sessions/{session}.json").read_text())


def submit_spelled(root, tmp_path, session, spelling=SPELLED_NEW):
    answer = tmp_path / f"answer-{session}.json"
    answer.write_text(json.dumps({SPELLED_OLD: spelling}))
    args = SimpleNamespace(answer=str(answer), session=session, model="claude-opus-5-5")
    return name_lane.cmd_submit(lane_of(root), args, lead=2, min_models=1)


@pytest.mark.parametrize("name,spelled", [
    (SPELLED_OLD, True),
    ("??0Rva00401000Box@@QAE@XZ", True),                         # a special member
    ("?clear@?$_Rb_tree@URva00401000Box@@@@QAEXXZ", True),       # a template's member
    ("?clear@?$_Rb_tree@UBfmeRecord@@@@QAEXXZ", False),          # no placeholder
    ("??4?$map@UBfmeRecord@@H@@QAEAAV0@ABV0@@Z", False),
    ("?rva00401000@@YAHPAURva00401000Box@@H@Z", False),          # an identifier of its own: the ordinary route
    ("_plainC", False),
])
def test_which_rows_are_compiler_spelled(name, spelled):
    assert name_lane.compiler_spelled(name) is spelled


@pytest.mark.parametrize("new,why", [
    (SPELLED_NEW, None),
    ("??4?$set@URva00402000Rec@URva00401000Box@@@@QAEAAV0@ABV0@@Z", "still a placeholder"),
    (SPELLED_OLD, "same spelling"),
    ("betterName", "whole new mangled spelling"),
    ("??4 bad", "whole new mangled spelling"),
    ("??4?$set@UA|B@@@@QAEAAV0@ABV0@@Z", "whole new mangled spelling"),
    ("??0?$set@UBfmeRecord@@@@QAE@XZ", "same operator or member"),
])
def test_a_spelled_answer_must_read_as_this_rows_respelling(new, why):
    got = name_lane.spelled_problem(SPELLED_OLD, new)
    assert (got is None) if why is None else (why in got)


def test_mangled_spellings_hash_exactly():
    """Word order and plurals are the type tree in a mangled name: canon() must not merge them."""
    reversed_args = "??4?$map@UBfmeRecord@@UOtherRecord@@@@QAEAAV0@ABV0@@Z"
    other = "??4?$map@UOtherRecord@@UBfmeRecord@@@@QAEAAV0@ABV0@@Z"
    assert name_agreement.digest(SPELLED_KEY, reversed_args) != name_agreement.digest(SPELLED_KEY, other)
    assert name_agreement.digest(MEMBER_KEY, "m_boxWidth") == name_agreement.digest(MEMBER_KEY, "m_widthBox")


def test_a_spelled_row_is_served_only_by_its_key(spelled_tree, capsys):
    served = serve(spelled_tree, "plain")
    assert not [i for i in served["files"][SOURCE]["items"] if i[2] == SPELLED_OLD]
    served = serve_key(spelled_tree, "keyed", "seat-a")
    assert [tuple(i) for i in served["files"][SOURCE]["items"]] == [("function", "0x00401100", SPELLED_OLD, 0x00401100)]
    brief = (spelled_tree / "build/name_lane/briefs/keyed.txt").read_text(encoding="utf-8")
    assert "COMPILER-SPELLED ROWS" in brief


def test_two_blind_votes_give_the_approval_the_identity_route_checks(spelled_tree, tmp_path, capsys):
    serve_key(spelled_tree, "a", "seat-a")
    assert submit_spelled(spelled_tree, tmp_path, "a") == 0
    assert SPELLED_KEY not in lane_of(spelled_tree).state()
    serve_key(spelled_tree, "b", "seat-b")
    assert submit_spelled(spelled_tree, tmp_path, "b") == 0
    row = lane_of(spelled_tree).state()[SPELLED_KEY]
    assert (row["status"], row["kind"], row["old"], row["new"], row["rva"]) == (
        "agreed", "function", SPELLED_OLD, SPELLED_NEW, "0x00401100")
    assert SPELLED_NEW not in (spelled_tree / name_lane.VOTES).read_text()              # hashes only
    # what rename.py function --respell --identity runs on the record
    ctx = rename.Context(spelled_tree, object_scan=False)
    entry = dict(source=SOURCE, rva=0x00401100, old=SPELLED_OLD, new=SPELLED_NEW)
    rename.identity_approvals(ctx, [entry], f"agree:{row['id']}")
    assert entry["agree"] == f"agree:{row['id']}"
    other = dict(entry, source="Code/Game/Slow.cpp")          # its own key, not another row's
    with pytest.raises(rename.Refusal, match="not this row's key"):
        rename.identity_approvals(ctx, [other], f"agree:{row['id']}")


def test_different_spellings_do_not_agree(spelled_tree, tmp_path):
    serve_key(spelled_tree, "a", "seat-a")
    assert submit_spelled(spelled_tree, tmp_path, "a") == 0
    serve_key(spelled_tree, "b", "seat-b")
    assert submit_spelled(spelled_tree, tmp_path, "b", "??4?$set@UOtherRecord@@@@QAEAAV0@ABV0@@Z") == 0
    assert SPELLED_KEY not in lane_of(spelled_tree).state()


def test_a_bad_spelled_answer_is_rejected_at_submit(spelled_tree, tmp_path, capsys):
    serve_key(spelled_tree, "a", "seat-a")
    submit_spelled(spelled_tree, tmp_path, "a", "betterName")
    assert "whole new mangled spelling" in capsys.readouterr().out
    assert not [v for v in lane_of(spelled_tree).votes() if v["key"] == SPELLED_KEY]


def test_apply_points_a_spelled_agreement_at_the_identity_route(spelled_tree, tmp_path, capsys):
    concurrent_votes(spelled_tree, SPELLED_KEY, SPELLED_NEW)
    assert agree(spelled_tree, SPELLED_KEY, SPELLED_NEW) == 0
    capsys.readouterr()
    assert apply(spelled_tree) == 0
    out = capsys.readouterr().out
    assert "--respell --identity" in out and "agree:" in out
    assert lane_of(spelled_tree).state()[SPELLED_KEY]["status"] == "agreed"
    assert SPELLED_OLD in (spelled_tree / "reverse/functions.csv").read_text()


def test_disputing_a_spelled_agreement_refuses_that_exact_spelling(spelled_tree):
    concurrent_votes(spelled_tree, SPELLED_KEY, SPELLED_NEW)
    assert agree(spelled_tree, SPELLED_KEY, SPELLED_NEW) == 0
    row = lane_of(spelled_tree).state()[SPELLED_KEY]
    lane_of(spelled_tree).append(name_lane.AGREED, name_lane.AGREED_COLUMNS, [dict(row, agents="", status="disputed")])
    assert name_lane.unrecorded_agreements(lane_of(spelled_tree)) == []
    with pytest.raises(SystemExit):
        agree(spelled_tree, SPELLED_KEY, SPELLED_NEW)


# ---------------------------------------------------------------- votes bound to the source they were served

def change_box(tree):
    """The review's repro: the placeholder stays, its meaning does not."""
    path = tree / SOURCE
    data = path.read_bytes()
    assert b"param_1->m_x2C + a2" in data
    path.write_bytes(data.replace(b"param_1->m_x2C + a2", b"param_1->m_x2C - a2"))


def test_votes_for_a_changed_source_record_nothing(tree):
    concurrent_votes(tree, MEMBER_KEY, "m_boxWidth")
    change_box(tree)
    with pytest.raises(SystemExit, match="needs a fresh vote"):
        agree(tree, MEMBER_KEY, "m_boxWidth")
    assert MEMBER_KEY not in lane_of(tree).state()
    assert apply(tree) == 0
    assert MEMBER_KEY not in lane_of(tree).state()


def test_real_votes_then_a_changed_source_record_nothing(tree, tmp_path):
    """The same through next and submit, so the fingerprints are the ones submit writes."""
    answers = {"Rva00401000Box::m_x2C": "m_boxWidth", "rva00401000": "skip"}
    assert vote(tree, tmp_path, "one", answers, worker="seat-one") == 0
    assert [r for r in rows(tree, name_lane.VOTE_SOURCES) if r["key"] == MEMBER_KEY]
    assert vote(tree, tmp_path, "two", answers, worker="seat-two") == 0
    agreed = lane_of(tree).state()[MEMBER_KEY]                    # sequential votes: submit recorded it
    assert agreed["status"] == "agreed"
    (tree / name_lane.AGREED).write_bytes((",".join(name_lane.AGREED_COLUMNS) + "\n").encode())  # as if neither saw the other
    assert name_lane.unrecorded_agreements(lane_of(tree)) == [MEMBER_KEY]
    change_box(tree)
    with pytest.raises(SystemExit):
        agree(tree, MEMBER_KEY, "m_boxWidth")
    assert MEMBER_KEY not in lane_of(tree).state()


def test_the_unchanged_source_still_records_from_real_votes(tree, tmp_path):
    answers = {"Rva00401000Box::m_x2C": "m_boxWidth", "rva00401000": "skip"}
    assert vote(tree, tmp_path, "one", answers, worker="seat-one") == 0
    assert vote(tree, tmp_path, "two", answers, worker="seat-two") == 0
    (tree / name_lane.AGREED).write_bytes((",".join(name_lane.AGREED_COLUMNS) + "\n").encode())
    assert agree(tree, MEMBER_KEY, "m_boxWidth") == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "agreed"


def test_votes_with_no_fingerprint_record_nothing(tree, capsys):
    """Votes from before fingerprints existed: nothing says what their voters read."""
    concurrent_votes(tree, MEMBER_KEY, "m_boxWidth", fingerprint=False)
    with pytest.raises(SystemExit):
        agree(tree, MEMBER_KEY, "m_boxWidth")
    assert name_lane.main(["status"], lane=lane_of(tree)) == 0
    assert "0 key(s) have agreeing votes" in capsys.readouterr().out


def submit_keys(tree, tmp_path, answers, session="full"):
    serve(tree, session, worker=f"seat-{session}")
    answer = tmp_path / f"answer-{session}.json"
    answer.write_text(json.dumps(answers))
    return name_lane.cmd_submit(lane_of(tree), SimpleNamespace(answer=str(answer), session=session,
                                                               model="claude-opus-5-5"), lead=2, min_models=1)


def test_an_answer_file_may_use_the_full_key_form(tree, tmp_path):
    assert submit_keys(tree, tmp_path, {FN_KEY: "sumBox", MEMBER_KEY: "m_width"}) == 0
    tally = lane_of(tree).tally()
    assert FN_KEY in tally and MEMBER_KEY in tally


def test_the_two_key_forms_vote_the_same(tree, tmp_path):
    assert submit_keys(tree, tmp_path, {FN_KEY: "sumBox"}, "full") == 0
    assert submit_keys(tree, tmp_path, FN_ANSWER, "bare") == 0
    assert lane_of(tree).state()[FN_KEY]["new"] == "sumBox"       # two workers, one spelling, either form


SPELLED_SECOND = name_lane.key_of(SOURCE, "function", "0x00401200", SPELLED_OLD)
SPELLED_OTHER = "??4?$set@UBfmeOther@@@@QAEAAV0@ABV0@@Z"


@pytest.fixture
def two_spelled(spelled_tree):
    """One compiler spelling at two addresses of one file."""
    with open(spelled_tree / "reverse/functions.csv", "a", encoding="utf-8", newline="") as handle:
        handle.write(f"{SPELLED_OLD},,0x00401200,18,{SOURCE},matched,\n")
    _git(spelled_tree, "add", "-A")
    return spelled_tree


def spelled_answers(root, tmp_path, answers, session="two", validate=False):
    be(f"seat-{session}")
    args = SimpleNamespace(session=session, model="claude-opus-5-5", count=1, file=SOURCE, list_only=False,
                           key=[SPELLED_KEY, SPELLED_SECOND])
    assert name_lane.cmd_next(lane_of(root), args) == 0
    answer = tmp_path / f"answer-{session}.json"
    answer.write_text(json.dumps(answers))
    args = SimpleNamespace(answer=str(answer), session=session, model="claude-opus-5-5")
    return name_lane.cmd_submit(lane_of(root), args, lead=2, min_models=1, validate_only=validate)


def test_a_full_key_votes_only_its_own_address(two_spelled, tmp_path):
    """The review's repro: only the second full key answered, once it recorded the first address."""
    report = spelled_answers(two_spelled, tmp_path, {SPELLED_SECOND: SPELLED_NEW}, "check", validate=True)
    assert report["valid"] == [SPELLED_SECOND]
    assert spelled_answers(two_spelled, tmp_path, {SPELLED_SECOND: SPELLED_NEW}, "vote") == 0
    assert {row["key"] for row in lane_of(two_spelled).votes()} == {SPELLED_SECOND}
    assert {row["key"] for row in rows(two_spelled, name_lane.VOTE_SOURCES)} == {SPELLED_SECOND}


def test_two_full_keys_may_have_different_answers(two_spelled, tmp_path):
    assert spelled_answers(two_spelled, tmp_path, {SPELLED_KEY: SPELLED_NEW, SPELLED_SECOND: SPELLED_OTHER}) == 0
    tally = lane_of(two_spelled).tally()
    assert name_agreement.digest(SPELLED_KEY, SPELLED_NEW) in tally[SPELLED_KEY]
    assert name_agreement.digest(SPELLED_SECOND, SPELLED_OTHER) in tally[SPELLED_SECOND]


def test_a_bare_spelling_two_keys_share_refuses(two_spelled, tmp_path):
    with pytest.raises(SystemExit, match="is ambiguous"):
        spelled_answers(two_spelled, tmp_path, {SPELLED_OLD: SPELLED_NEW})
    assert not lane_of(two_spelled).votes()


def test_a_bare_spelling_one_key_has_still_answers(spelled_tree, tmp_path):
    serve_key(spelled_tree, "one", "seat-one")
    assert submit_spelled(spelled_tree, tmp_path, "one") == 0
    assert {row["key"] for row in lane_of(spelled_tree).votes()} == {SPELLED_KEY}


def test_the_brief_lists_a_shared_spelling_by_its_full_keys(two_spelled):
    be("seat-brief")
    args = SimpleNamespace(session="brief", model="claude-opus-5-5", count=1, file=SOURCE, list_only=False,
                           key=[SPELLED_KEY, SPELLED_SECOND])
    assert name_lane.cmd_next(lane_of(two_spelled), args) == 0
    brief = (two_spelled / "build/name_lane/briefs/brief.txt").read_text()
    assert SPELLED_KEY in brief and SPELLED_SECOND in brief


def test_one_key_with_two_answers_refuses(tree, tmp_path):
    with pytest.raises(SystemExit):
        submit_keys(tree, tmp_path, {FN_KEY: "sumBox", "rva00401000": "otherName"})
    assert not lane_of(tree).votes()
    assert submit_keys(tree, tmp_path, {FN_KEY: "sumBox", "rva00401000": "sumBox"}, "same") == 0


def test_a_full_key_of_something_not_served_still_refuses(tree, tmp_path):
    with pytest.raises(SystemExit):
        submit_keys(tree, tmp_path, {f"{SOURCE}|function|0x00409000|rva00409000": "sumBox"})


def test_the_brief_says_which_key_form_it_reads(tree):
    record = serve(tree, "brief")
    brief = (tree / "build/name_lane/briefs/brief.txt").read_text()
    assert "a key's full form, as `next --key` takes it, is read as the same key" in brief and record


def test_status_tells_the_two_kinds_apart(tree, capsys):
    concurrent_votes(tree, MEMBER_KEY, "m_boxWidth")
    concurrent_votes(tree, FN_KEY, "sumBox", fingerprint=False)
    assert name_lane.main(["status"], lane=lane_of(tree)) == 0
    out = capsys.readouterr().out
    assert "1 key(s) have agreeing votes" in out and "1 more need fresh votes" in out
    assert MEMBER_KEY in out and FN_KEY not in out


@pytest.mark.parametrize("voters,stale,records", [(3, 1, True), (2, 1, False)])
def test_only_voters_of_the_current_source_count(tree, voters, stale, records):
    """A second fingerprint for one voter, or an older one, takes that vote out of the agreement."""
    concurrent_votes(tree, MEMBER_KEY, "m_boxWidth", count=voters)
    lane = lane_of(tree)
    h = name_agreement.digest(MEMBER_KEY, "m_boxWidth")
    lane.append(name_lane.VOTE_SOURCES, name_lane.VOTE_SOURCE_COLUMNS, [
        dict(key=MEMBER_KEY, hash=h, worker=f"w-00000000000{i}", session="old", source_sha="0" * 64)
        for i in range(stale)])
    if records:
        assert agree(tree, MEMBER_KEY, "m_boxWidth") == 0
        assert "w-000000000000" not in lane_of(tree).state()[MEMBER_KEY]["agents"]
    else:
        with pytest.raises(SystemExit):
            agree(tree, MEMBER_KEY, "m_boxWidth")


def test_a_resubmit_does_not_record_another_voters_stale_vote(tree, tmp_path, capsys):
    answers = {"Rva00401000Box::m_x2C": "m_boxWidth", "rva00401000": "skip"}
    serve(tree, "later", worker="seat-a")
    assert vote(tree, tmp_path, "first", answers, worker="seat-a") == 0
    h = name_agreement.digest(MEMBER_KEY, "m_boxWidth")
    lane_of(tree).append(name_lane.VOTES, name_lane.VOTE_COLUMNS, [dict(
        key=MEMBER_KEY, hash=h, model="other", session="b", worker="w-000000000002", date="2026-11-07")])
    answer = tmp_path / "answer-later.json"
    answer.write_text(json.dumps(answers))
    args = SimpleNamespace(answer=str(answer), session="later", model="claude-opus-5-5")
    name_lane.cmd_submit(lane_of(tree), args, lead=2, min_models=1)
    assert "already voted" in capsys.readouterr().out
    assert MEMBER_KEY not in lane_of(tree).state()


# ---------------------------------------------------------------- spelled keys keep the ordinary exclusions

def named_elsewhere(tree, how):
    if how == "evidence":
        (tree / "reverse/name_tiers.csv").write_bytes(
            f"name,target_rva,name_tier,evidence\n{SPELLED_OLD},0x00401100,evidence,hand\n".encode())
    else:
        with open(tree / "reverse/symbols.csv", "a", encoding="utf-8", newline="") as handle:
            handle.write("?realPinnedName@@YAXXZ,0x00401100,pin\n")


@pytest.mark.parametrize("how", ["evidence", "pin"])
def test_a_spelled_row_another_lane_names_is_not_served(spelled_tree, how):
    named_elsewhere(spelled_tree, how)
    assert not [i for i in name_lane.spelled_items(lane_of(spelled_tree), SOURCE) if i[2] == SPELLED_OLD]
    assert lane_of(spelled_tree).eligibility(SOURCE, "function", "0x00401100", SPELLED_OLD, 0x00401100)
    be("seat-a")
    args = SimpleNamespace(session="named", model="claude-opus-5-5", count=1, file=SOURCE, list_only=False,
                           key=[SPELLED_KEY])
    name_lane.cmd_next(lane_of(spelled_tree), args)
    session = spelled_tree / "build/name_lane/sessions/named.json"
    if session.exists():
        items = [i for f in json.loads(session.read_text())["files"].values() for i in f["items"]]
        assert not [i for i in items if i[2] == SPELLED_OLD]


@pytest.mark.parametrize("how", ["evidence", "pin"])
def test_a_session_served_before_the_row_was_named_records_no_vote(spelled_tree, tmp_path, capsys, how):
    serve_key(spelled_tree, "a", "seat-a")
    named_elsewhere(spelled_tree, how)
    submit_spelled(spelled_tree, tmp_path, "a")
    assert "named by another lane or a real pin" in capsys.readouterr().out
    assert not [v for v in lane_of(spelled_tree).votes() if v["key"] == SPELLED_KEY]


def test_agree_refuses_a_spelled_row_another_lane_names(spelled_tree):
    concurrent_votes(spelled_tree, SPELLED_KEY, SPELLED_NEW)
    named_elsewhere(spelled_tree, "evidence")
    with pytest.raises(SystemExit):
        agree(spelled_tree, SPELLED_KEY, SPELLED_NEW)
    assert SPELLED_KEY not in lane_of(spelled_tree).state()


# ---------------------------------------------------------------- every path that records an agreement

BOX_ANSWERS = {"Rva00401000Box::m_x2C": "m_boxWidth", "rva00401000": "skip"}


def test_new_votes_on_top_of_stale_ones_need_two_of_their_own(tree, tmp_path):
    """The hole by another door: one new vote plus two stale ones is not an agreement."""
    concurrent_votes(tree, MEMBER_KEY, "m_boxWidth")
    change_box(tree)
    assert vote(tree, tmp_path, "new1", BOX_ANSWERS, worker="seat-new1") == 0
    assert MEMBER_KEY not in lane_of(tree).state()
    assert vote(tree, tmp_path, "new2", BOX_ANSWERS, model="gpt-6.1-sol", worker="seat-new2") == 0
    row = lane_of(tree).state()[MEMBER_KEY]
    assert row["status"] == "agreed" and "w-00000000000" not in row["agents"]
    assert len(row["agents"].split(";")) == 2


def test_votes_with_no_fingerprint_do_not_count_towards_a_submit(tree, tmp_path):
    concurrent_votes(tree, MEMBER_KEY, "m_boxWidth", fingerprint=False)
    assert vote(tree, tmp_path, "new1", BOX_ANSWERS, worker="seat-new1") == 0
    assert MEMBER_KEY not in lane_of(tree).state()


def test_two_votes_either_side_of_a_change_do_not_agree(tree, tmp_path):
    assert vote(tree, tmp_path, "one", BOX_ANSWERS, worker="seat-one") == 0
    change_box(tree)
    assert vote(tree, tmp_path, "two", BOX_ANSWERS, worker="seat-two") == 0
    assert MEMBER_KEY not in lane_of(tree).state()


def test_two_votes_for_the_same_text_still_agree_through_submit(tree, tmp_path):
    assert vote(tree, tmp_path, "one", BOX_ANSWERS, worker="seat-one") == 0
    assert vote(tree, tmp_path, "two", BOX_ANSWERS, worker="seat-two") == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "agreed"


def test_status_says_fresh_votes_are_intended(tree, capsys):
    concurrent_votes(tree, MEMBER_KEY, "m_boxWidth", fingerprint=False)
    assert name_lane.main(["status"], lane=lane_of(tree)) == 0
    out = capsys.readouterr().out
    assert "need fresh votes from other workers" in out and "this is intended, not a fault" in out


def existing_record_stands(tree):
    """A record from before the rule: its votes have no fingerprints, and it is left alone."""
    lane = lane_of(tree)
    lane.append(name_lane.VOTES, name_lane.VOTE_COLUMNS, [
        dict(key=MEMBER_KEY, hash=name_agreement.digest(MEMBER_KEY, "m_boxWidth"), model=f"m{i}", session=f"s{i}",
             worker=f"w-00000000000{i}", date="2026-11-07") for i in range(2)])
    lane.append(name_lane.AGREED, name_lane.AGREED_COLUMNS, [dict(
        id="nl-existing", kind="member", old="m_x2C", new="m_boxWidth", rva="",
        agents="w-000000000000@m0;w-000000000001@m1", key=MEMBER_KEY, status="agreed", detail="older record")])


def test_an_existing_record_stands_and_still_lands(tree, monkeypatch):
    existing_record_stands(tree)
    grandfather_all(tree, monkeypatch)
    assert name_agreement.verify(lane_of(tree).votes(), lane_of(tree).agreed_rows(), MEMBER_KEY, "m_boxWidth") == []
    assert apply(tree) == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "landed"


def competing_votes(tree, tmp_path):
    assert vote(tree, tmp_path, "one", {"Rva00401000Box::m_x2C": "m_boxWidth", "rva00401000": "skip"},
                worker="seat-one") == 0
    assert vote(tree, tmp_path, "two", {"Rva00401000Box::m_x2C": "m_boxHeight", "rva00401000": "skip"},
                worker="seat-two") == 0
    assert MEMBER_KEY not in lane_of(tree).state()


def resolve(tree, worker, name):
    be(worker)
    return name_lane.main(["resolve", "--key", MEMBER_KEY, "--name", name, "--reason", "the code reads a box width"],
                          lane=lane_of(tree))


def test_a_stale_blind_vote_is_no_acceptance_until_its_voter_accepts_today(tree, tmp_path, capsys):
    competing_votes(tree, tmp_path)
    change_box(tree)
    assert resolve(tree, "seat-two", "m_boxWidth") == 0
    out = capsys.readouterr().out
    assert "not cast on the source as it reads now" in out
    assert MEMBER_KEY not in lane_of(tree).state()
    assert resolve(tree, "seat-one", "m_boxWidth") == 0              # its voter accepts on today's text
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "agreed"


def test_a_fresh_blind_vote_still_counts_as_acceptance(tree, tmp_path):
    competing_votes(tree, tmp_path)
    assert resolve(tree, "seat-two", "m_boxWidth") == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "agreed"


# ---------------------------------------------------------------- apply, the cutoff, spelled keys again

def agreed_from_real_votes(tree, tmp_path):
    assert vote(tree, tmp_path, "one", BOX_ANSWERS, worker="seat-one") == 0
    assert vote(tree, tmp_path, "two", BOX_ANSWERS, worker="seat-two") == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "agreed"


def test_apply_lands_nothing_when_the_source_changed_since_the_votes(tree, tmp_path, capsys):
    """The review's repro: two votes for m_boxWidth, then + a2 becomes - a2."""
    agreed_from_real_votes(tree, tmp_path)
    change_box(tree)
    assert apply(tree) == 0
    assert "no longer reads as it did for the votes" in capsys.readouterr().out
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "source-changed"
    assert "m_x2C" in (tree / SOURCE).read_text()


def test_a_reopened_key_is_served_and_lands_on_fresh_votes(tree, tmp_path):
    """Not a dead end: other workers vote on today's text, and that agreement replaces the record."""
    agreed_from_real_votes(tree, tmp_path)
    change_box(tree)
    assert apply(tree) == 0
    served = serve(tree, "new1", worker="seat-new1")
    assert [i for i in served["files"][SOURCE]["items"] if i[2] == "m_x2C"]
    assert vote(tree, tmp_path, "new1", BOX_ANSWERS, worker="seat-new1") == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "source-changed"     # one fresh vote is not enough
    assert vote(tree, tmp_path, "new2", BOX_ANSWERS, worker="seat-new2") == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "agreed"
    assert apply(tree) == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "landed"
    assert "m_boxWidth" in (tree / SOURCE).read_text()


def test_apply_still_lands_when_the_source_did_not_change(tree, tmp_path):
    agreed_from_real_votes(tree, tmp_path)
    assert apply(tree) == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "landed"


def test_a_grandfathered_record_lands_on_a_changed_source_and_says_so(tree, monkeypatch, capsys):
    existing_record_stands(tree)
    grandfather_all(tree, monkeypatch)
    change_box(tree)
    assert name_lane.main(["status"], lane=lane_of(tree)) == 0
    assert "1 waiting and 0 blocked record(s) predate vote fingerprints: grandfathered" in capsys.readouterr().out
    assert apply(tree) == 0
    assert "predate vote fingerprints: grandfathered" in capsys.readouterr().out
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "landed"


def test_a_row_after_the_cutoff_gets_no_exemption(tree, capsys):
    """A record with no fingerprints written after the cutoff, by hand or an older tool, lands nothing."""
    existing_record_stands(tree)
    assert apply(tree) == 0
    assert "no longer reads as it did for the votes" in capsys.readouterr().out
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "source-changed"


def test_the_cutoff_is_a_row_count_within_the_real_ledger():
    """The miniature trees run with it at 0 (the seat fixture); the tool's own value is what counts."""
    tool = Path(name_lane.__file__).read_text(encoding="utf-8")
    cutoff = int(re.search(r"^AGREED_CUTOFF_ROWS = (\d+)$", tool, re.M).group(1))
    pinned = re.search(r'^AGREED_CUTOFF_SHA256 = "([0-9a-f]{64})"$', tool, re.M).group(1)
    assert cutoff > 19000
    real = Path(name_lane.__file__).resolve().parents[1] / name_lane.AGREED
    if real.exists():
        with real.open(newline="", encoding="utf-8") as handle:
            rows = list(csv.DictReader(handle))
        assert cutoff <= len(rows) and name_lane.agreed_prefix_hash(rows[:cutoff]) == pinned


def test_a_spelled_disagreement_can_be_resolved(spelled_tree, tmp_path):
    """The review's repro: two spellings, then the voters accept one with `resolve`."""
    serve_key(spelled_tree, "a", "seat-a")
    assert submit_spelled(spelled_tree, tmp_path, "a") == 0
    serve_key(spelled_tree, "b", "seat-b")
    other = "??4?$set@UOtherRecord@@@@QAEAAV0@ABV0@@Z"
    assert submit_spelled(spelled_tree, tmp_path, "b", other) == 0
    be("seat-b")
    assert name_lane.main(["resolve", "--key", SPELLED_KEY, "--name", SPELLED_NEW, "--reason",
                           "the retail callees prove the record type"], lane=lane_of(spelled_tree)) == 0
    row = lane_of(spelled_tree).state()[SPELLED_KEY]
    assert (row["status"], row["new"]) == ("agreed", SPELLED_NEW)


def test_submit_refuses_a_spelled_key_the_ledger_no_longer_spells(spelled_tree, tmp_path, capsys):
    """The review's repro: A votes, the row is respelled, then B's older session submits."""
    serve_key(spelled_tree, "a", "seat-a")
    assert submit_spelled(spelled_tree, tmp_path, "a") == 0
    serve_key(spelled_tree, "b", "seat-b")
    ledger = spelled_tree / "reverse/functions.csv"
    data = ledger.read_bytes()
    assert SPELLED_OLD.encode() in data
    ledger.write_bytes(data.replace(SPELLED_OLD.encode(), SPELLED_OLD.replace("Rva00401000Box", "Rva00402000Other").encode()))
    submit_spelled(spelled_tree, tmp_path, "b")
    assert "its key is obsolete" in capsys.readouterr().out
    assert SPELLED_KEY not in lane_of(spelled_tree).state()
    assert len([v for v in lane_of(spelled_tree).votes() if v["key"] == SPELLED_KEY]) == 1


def test_records_of_one_file_land_together(tree, tmp_path, monkeypatch):
    """Freshness is per file, and one run checks every record before any lands."""
    agree_on(tree, tmp_path, {**MEMBER_ANSWER, **FN_ANSWER})
    assert apply(tree) == 0
    state = lane_of(tree).state()
    assert state[FN_KEY]["status"] == state[MEMBER_KEY]["status"] == "landed"


def carried_rows(tree, key=None):
    return [row for row in rows(tree, name_lane.VOTE_SOURCES) if row["session"].startswith("carried:")
            and (key is None or row["key"] == key)]


def test_a_sibling_left_by_a_key_filter_lands_across_the_verified_landing(tree, tmp_path):
    agree_on(tree, tmp_path, {**MEMBER_ANSWER, **FN_ANSWER})
    before = __import__("hashlib").sha256((tree / SOURCE).read_bytes()).hexdigest()
    assert apply(tree, key=[FN_KEY], per_file=False) == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "agreed"
    after = __import__("hashlib").sha256((tree / SOURCE).read_bytes()).hexdigest()
    carried = carried_rows(tree, MEMBER_KEY)
    assert carried and all(r["source_sha"] == after and r["session"].startswith(f"carried:{before}:") for r in carried)
    assert not carried_rows(tree, FN_KEY)                        # the key that landed needs no carry
    assert apply(tree) == 0
    state = lane_of(tree).state()
    assert state[FN_KEY]["status"] == state[MEMBER_KEY]["status"] == "landed"
    assert "m_width" in (tree / SOURCE).read_text()


@pytest.mark.parametrize("fallback", [dict(per_file=True), dict(no_batch=True)])
def test_the_fallback_landings_do_not_carry(tree, tmp_path, fallback):
    agree_on(tree, tmp_path, {**MEMBER_ANSWER, **FN_ANSWER})
    assert apply(tree, key=[FN_KEY], **fallback) == 0
    assert not carried_rows(tree)
    assert apply(tree) == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "source-changed"


def test_an_edit_after_the_carried_landing_still_reopens(tree, tmp_path):
    agree_on(tree, tmp_path, {**MEMBER_ANSWER, **FN_ANSWER})
    assert apply(tree, key=[FN_KEY], per_file=False) == 0
    with open(tree / SOURCE, "a", newline="\n") as f:
        f.write("// an unrelated edit\n")
    assert apply(tree) == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "source-changed"


def test_an_edit_made_during_the_landing_does_not_carry(tree, tmp_path):
    agree_on(tree, tmp_path, {**MEMBER_ANSWER, **FN_ANSWER})

    def edits_while_verifying(ctx, sources):
        with open(tree / SOURCE, "a", newline="\n") as f:
            f.write("// an unrelated edit in the same run\n")
        return True
    assert apply(tree, key=[FN_KEY], per_file=False, verify=edits_while_verifying) == 0
    assert lane_of(tree).state()[FN_KEY]["status"] == "landed"
    assert not carried_rows(tree)
    assert apply(tree) == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "source-changed"


def test_a_vote_on_an_older_text_does_not_carry(tree, tmp_path):
    agree_on(tree, tmp_path, MEMBER_ANSWER)
    with open(tree / SOURCE, "a", newline="\n") as f:
        f.write("// an unrelated edit before the other key's votes\n")
    voters(tree, tmp_path, FN_ANSWER, ["a", "b"], tag="fn")
    assert lane_of(tree).state()[FN_KEY]["status"] == "agreed"
    assert apply(tree, key=[FN_KEY], per_file=False) == 0
    assert not carried_rows(tree, MEMBER_KEY)
    assert apply(tree) == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "source-changed"


@pytest.mark.parametrize("change", [
    b"// and another edit\n",                                    # the plan's bytes hold more than the rename
])
def test_a_plan_changing_more_than_its_rename_does_not_carry(tree, tmp_path, change):
    agree_on(tree, tmp_path, {**MEMBER_ANSWER, **FN_ANSWER})
    lane = lane_of(tree)
    before = (tree / SOURCE).read_bytes()
    landed = [dict(key=FN_KEY, old="rva00401000", new="sumBox")]
    after = before.replace(b"rva00401000", b"sumBox")
    (tree / SOURCE).write_bytes(after + change)
    plan = SimpleNamespace(before={SOURCE: before}, after={SOURCE: after + change})
    name_lane.carry_verified_votes(lane, [plan], landed)
    assert not carried_rows(tree)
    (tree / SOURCE).write_bytes(after)                           # exactly the rename: it carries
    plan = SimpleNamespace(before={SOURCE: before}, after={SOURCE: after})
    name_lane.carry_verified_votes(lane_of(tree), [plan], landed)
    assert carried_rows(tree, MEMBER_KEY)


def test_a_class_key_keeps_its_own_binding(tree, tmp_path):
    lane = lane_of(tree)
    before = (tree / SOURCE).read_bytes()
    after = before.replace(b"rva00401000", b"sumBox")
    sha = __import__("hashlib").sha256(before).hexdigest()
    class_key = f"{SOURCE}|class||Rva00401000Box"
    lane.append(name_lane.VOTE_SOURCES, name_lane.VOTE_SOURCE_COLUMNS, [
        dict(key=class_key, hash="h", worker="w", session="s", source_sha=sha)])
    (tree / SOURCE).write_bytes(after)
    name_lane.carry_verified_votes(lane_of(tree), [SimpleNamespace(before={SOURCE: before}, after={SOURCE: after})],
                                   [dict(key=FN_KEY, old="rva00401000", new="sumBox")])
    assert not carried_rows(tree)


@pytest.mark.parametrize("rows_,expected", [
    ([dict(session="s", source_sha="a")], "a"),
    ([dict(session="s", source_sha="a"), dict(session="carried:a:s", source_sha="b")], "b"),
    ([dict(session="s", source_sha="a"), dict(session="carried:a:s", source_sha="b"),
      dict(session="carried:b:s", source_sha="c")], "c"),
    ([dict(session="s", source_sha="a"), dict(session="carried:z:s", source_sha="b")], None),      # starts elsewhere
    ([dict(session="carried:a:s", source_sha="b")], None),                                         # no own row
    ([dict(session="s", source_sha="a"), dict(session="t", source_sha="b")], None),                # two own rows
    ([], None),
])
def test_current_fingerprint_follows_only_an_unbroken_chain(rows_, expected):
    assert name_agreement.current_fingerprint(rows_) == expected


@pytest.mark.parametrize("before,after,same", [
    (b"int rva00401000;\n", b"int sumBox;\n", True),
    (b"rva00401000 rva00401000;\n", b"sumBox sumBox;\n", True),
    (b"// ?rva00401000@@YAXXZ\nint rva00401000;\n", b"// ?sumBox@@YAXXZ\nint sumBox;\n", True),   # rename's own
    (b"/* ?rva00401000@@YAXXZ */ int rva00401000;\n", b"/* ?sumBox@@YAXXZ */ int sumBox;\n", True),
    # the review's repro, and the literals around it: a string edit is no rename
    (b'int rva00401000; char *s = "rva00401000";\n', b'int sumBox; char *s = "sumBox";\n', False),
    (b"int rva00401000; int c = 'rva00401000';\n", b"int sumBox; int c = 'sumBox';\n", False),
    (b'int rva00401000; char *s = "?rva00401000@@";\n', b'int sumBox; char *s = "?sumBox@@";\n', False),
    (b'char *s = "??/" rva00401000 ";\nint rva00401000;\n',       # a trigraph: ??/ escapes the quote
     b'char *s = "??/" sumBox ";\nint sumBox;\n', False),
    (b'char *s = "a\\\nrva00401000";\nint rva00401000;\n',        # a spliced string
     b'char *s = "a\\\nsumBox";\nint sumBox;\n', False),
    (b'char *s = "open\nint rva00401000;\n', b'char *s = "open\nint sumBox;\n', False),   # does not read
    # comments: only a mangled spelling beside code, never prose or on its own
    (b"// rva00401000\nint rva00401000;\n", b"// sumBox\nint sumBox;\n", False),
    (b"int rva00401000; // rva00401000\n", b"int sumBox; // sumBox\n", False),
    (b"// ?rva00401000@@YAXXZ\n", b"// ?sumBox@@YAXXZ\n", False),
    # directives: a macro's text or a linker pragma is not read as code
    (b"#define F rva00401000\nint rva00401000;\n", b"#define F sumBox\nint sumBox;\n", False),
    (b'#define S "?rva00401000@"\nint rva00401000;\n', b'#define S "?sumBox@"\nint sumBox;\n', False),
    (b"int rva00401000;\n", b"int  sumBox;\n", False),                 # whitespace
    (b"int rva00401000;\n", b"long sumBox;\n", False),                 # another token
    (b"int rva00401000;\n", b"int sumBox;\n// more\n", False),         # more text
    (b"int rva00401000;\n", b"int other;\n", False),                   # another name
    (b"int sumBox;\n", b"int rva00401000;\n", False),                  # the pair runs one way
])
def test_rename_only_allows_exactly_the_pairs(before, after, same):
    assert name_agreement.rename_only(before, after, {("rva00401000", "sumBox")}) is same


def test_a_string_edit_in_a_real_landing_does_not_carry(tree, tmp_path):
    """The review's repro through carry_verified_votes: the rename, and a literal respelled with it."""
    with open(tree / SOURCE, "a", newline="\n") as f:
        f.write('char *g_label = "rva00401000";\n')
    agree_on(tree, tmp_path, {**MEMBER_ANSWER, **FN_ANSWER})
    before = (tree / SOURCE).read_bytes()
    after = before.replace(b"rva00401000", b"sumBox")
    (tree / SOURCE).write_bytes(after)
    name_lane.carry_verified_votes(lane_of(tree), [SimpleNamespace(before={SOURCE: before}, after={SOURCE: after})],
                                   [dict(key=FN_KEY, old="rva00401000", new="sumBox")])
    assert not carried_rows(tree)


def test_a_row_moved_into_the_prefix_earns_nothing_and_apply_refuses(tree, tmp_path, monkeypatch, capsys):
    """The review's repro: a later record with no fingerprints moved to just below the header."""
    existing_record_stands(tree)
    grandfather_all(tree, monkeypatch)
    ledger = tree / name_lane.AGREED
    lines = ledger.read_bytes().splitlines(keepends=True)
    lane_of(tree).append(name_lane.AGREED, name_lane.AGREED_COLUMNS, [dict(
        id="nl-moved", kind="function", old="rva00401000", new="sumBox", rva="0x00401000", agents="", key=FN_KEY,
        status="agreed", detail="later record")])
    moved = ledger.read_bytes().splitlines(keepends=True)[-1]
    ledger.write_bytes(b"".join([lines[0], moved, *lines[1:]]))
    change_box(tree)
    before = ledger.read_bytes()
    assert lane_of(tree).grandfathered() == set()
    assert apply(tree) == 1
    assert "do not hash to the pinned cutoff" in capsys.readouterr().out
    assert ledger.read_bytes() == before                      # no record reopened, none landed
    assert "m_x2C" in (tree / SOURCE).read_text()
    assert name_lane.main(["status"], lane=lane_of(tree)) == 0
    assert "do not hash to the pinned cutoff" in capsys.readouterr().out


@pytest.mark.parametrize("edit", ["changed", "removed"])
def test_an_edited_or_shortened_prefix_is_refused(tree, monkeypatch, capsys, edit):
    existing_record_stands(tree)
    grandfather_all(tree, monkeypatch)
    ledger = tree / name_lane.AGREED
    data = ledger.read_bytes()
    ledger.write_bytes(data.replace(b"older record", b"edited") if edit == "changed"
                       else b"".join(data.splitlines(keepends=True)[:1]))
    assert lane_of(tree).grandfather_fault()
    assert apply(tree) == 1


def test_the_prefix_hash_ignores_line_endings(tree, monkeypatch):
    existing_record_stands(tree)
    grandfather_all(tree, monkeypatch)
    ledger = tree / name_lane.AGREED
    ledger.write_bytes(ledger.read_bytes().replace(b"\r\n", b"\n").replace(b"\n", b"\r\n"))
    assert lane_of(tree).grandfather_fault() is None


def test_a_blocked_record_reopens_on_a_source_change_and_lands_on_fresh_votes(tree, tmp_path, monkeypatch):
    """The review's repro, the whole path: blocked, source change, reopened, two fresh votes, land."""
    agreed_from_real_votes(tree, tmp_path)
    row = lane_of(tree).state()[MEMBER_KEY]
    lane_of(tree).append(name_lane.AGREED, name_lane.AGREED_COLUMNS, [dict(row, status="blocked", detail="a block")])
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "blocked"
    change_box(tree)
    assert apply(tree, retry_blocked=True) == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "source-changed"
    served = serve(tree, "new1", worker="seat-new1")
    assert [i for i in served["files"][SOURCE]["items"] if i[2] == "m_x2C"]
    assert vote(tree, tmp_path, "new1", BOX_ANSWERS, worker="seat-new1") == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "source-changed"
    assert vote(tree, tmp_path, "new2", BOX_ANSWERS, worker="seat-new2") == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "agreed"
    assert apply(tree) == 0
    assert lane_of(tree).state()[MEMBER_KEY]["status"] == "landed"


def test_a_source_changed_row_never_reopens_a_landing_or_a_dispute(tree, tmp_path):
    agreed_from_real_votes(tree, tmp_path)
    row = lane_of(tree).state()[MEMBER_KEY]
    for status in ("landed", "disputed"):
        lane_of(tree).append(name_lane.AGREED, name_lane.AGREED_COLUMNS, [dict(row, status=status)])
        lane_of(tree).append(name_lane.AGREED, name_lane.AGREED_COLUMNS, [dict(row, status="source-changed")])
        assert lane_of(tree).state()[MEMBER_KEY]["status"] == status
