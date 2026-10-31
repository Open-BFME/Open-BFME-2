"""Proposal validation, scoped collisions, picker reuse and bounded review packets."""
import argparse
import json
from pathlib import Path
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_lane
import name_review
from test_name_lane import tree, seat, serve, vote, lane_of, rows, SOURCE, FN_KEY, FN_ANSWER, BOX, _git
from test_name_review import enable, first, answer


def test_members_can_reuse_other_classes_names_but_not_own_scope(tree):
    path = tree / SOURCE
    path.write_text(BOX + "\nstruct Other { int m_width; };\n")
    lane = lane_of(tree)
    args = dict(rel=SOURCE, scope="Rva00401000Box")
    assert lane.problem("member", "m_x2C", "m_width", {"m_width"}, **args) is None
    assert lane.problem("member", "m_x2C", "m_count", set(), **args)
    path.write_text(path.read_text() + "\nint Rva00401000Box::read() { int m_width=1; return m_x2C+m_width; }\n")
    assert lane_of(tree).problem("member", "m_x2C", "m_width", set(), **args)


def test_methods_can_reuse_other_classes_names(tree):
    path = tree / SOURCE
    path.write_text("class Widget { int rva00401000(); }; class Other { int countItems(); };\n"
                    "int Widget::rva00401000() { return 1; }\n")
    ledger = tree / "reverse/functions.csv"
    ledger.write_text(ledger.read_text().replace("?rva00401000@@YAHPAURva00401000Box@@H@Z",
                                                "?rva00401000@Widget@@QAEHXZ"))
    assert lane_of(tree).problem("function", "rva00401000", "countItems", {"countItems"},
                                 rel=SOURCE, scope="0x00401000") is None
    path.write_text(path.read_text().replace("int rva00401000();", "int rva00401000(); int countItems();"))
    assert lane_of(tree).problem("function", "rva00401000", "countItems", set(),
                                 rel=SOURCE, scope="0x00401000")


def test_macro_expansions_remain_conservative_collisions(tree):
    (tree / SOURCE).write_text("#define FIELD int m_width;\n" + BOX)
    assert lane_of(tree).problem("member", "m_x2C", "m_width", set(),
                                 rel=SOURCE, scope="Rva00401000Box")


@pytest.mark.parametrize("same_class, accepted", [(False, 2), (True, 1)])
def test_duplicate_proposals_are_compared_in_their_class_scope(tree, tmp_path, same_class, accepted):
    source = BOX.replace("int m_count;", "int m_count; int m_x30;") if same_class else (
        BOX + "\nstruct Rva00403000Box { int m_x30; };\n")
    source += "int use(Rva00401000Box *p) { return p->m_x30; }\n" if same_class else (
        "int use(Rva00403000Box *p) { return p->m_x30; }\n")
    (tree / SOURCE).write_text(source)
    other = "Rva00401000Box" if same_class else "Rva00403000Box"
    vote(tree, tmp_path, "scopes", {"Rva00401000Box::m_x2C": "m_width", f"{other}::m_x30": "m_width"})
    assert len(rows(tree, name_lane.VOTES)) == accepted


def test_validation_preserves_votes_and_session_until_submit(tree, tmp_path):
    serve(tree, "preflight")
    session = tree / "build/name_lane/sessions/preflight.json"
    before = session.read_bytes()
    source = (tree / SOURCE).read_bytes()
    path = tmp_path / "answer.json"
    path.write_text(json.dumps({**FN_ANSWER, "Rva00401000Box::m_x2C": "m_count"}))
    args = argparse.Namespace(answer=str(path), session="preflight", model="claude-opus-5-5")
    assert name_lane.cmd_validate(lane_of(tree), args) == 1
    assert not rows(tree, name_lane.VOTES) and not rows(tree, name_lane.AGREED)
    assert session.read_bytes() == before and (tree / SOURCE).read_bytes() == source
    report = json.loads((tree / "build/name_lane/validation/preflight.json").read_text())
    assert report["valid"] == [FN_KEY]
    assert report["rejected"][0]["retryable"]
    path.write_text(json.dumps({**FN_ANSWER, "Rva00401000Box::m_x2C": "m_width"}))
    assert name_lane.cmd_validate(lane_of(tree), args) == 0
    assert not rows(tree, name_lane.VOTES)
    name_lane.cmd_submit(lane_of(tree), args)
    assert len(rows(tree, name_lane.VOTES)) == 2


def test_changed_source_is_not_repaired_under_a_stale_session(tree, tmp_path):
    serve(tree, "stale")
    path = tmp_path / "answer.json"
    path.write_text(json.dumps(FN_ANSWER))
    (tree / SOURCE).write_text(BOX + "// changed\n")
    report = name_lane.cmd_submit(lane_of(tree), argparse.Namespace(
        answer=str(path), session="stale", model="claude-opus-5-5"), validate_only=True)
    assert report["rejected"] and not any(r["retryable"] for r in report["rejected"])
    assert not rows(tree, name_lane.VOTES)


def test_picker_reuses_ownership_and_invalidates_on_other_source_changes(tree, monkeypatch):
    calls = []
    original = name_lane.Lane.owned
    def counted(lane, *args, **kwargs):
        calls.append(args[0])
        return original(lane, *args, **kwargs)
    monkeypatch.setattr(name_lane.Lane, "owned", counted)
    source = (tree / SOURCE).read_text()
    cache = name_lane.PickerCache(lane_of(tree))
    assert cache.stamp
    expected = cache.items(SOURCE, source)
    cache.save()
    # Naming votes do not change the ownership/protection inputs.
    (tree / name_lane.VOTES).write_text("key,hash,model,session,worker,date\n")
    warm = name_lane.PickerCache(lane_of(tree))
    assert warm.items(SOURCE, source) == expected and warm.hits == 1
    assert calls == [SOURCE]
    (tree / "Code/Game/NewView.h").write_text("struct Rva00401000Box { int m_x2C; };\n")
    changed = name_lane.PickerCache(lane_of(tree))
    changed.items(SOURCE, source)
    assert changed.misses == 1 and len(calls) == 2


def test_picker_tracks_used_donor_tree_without_unrelated_nested_submodules(tree):
    donor = tree / "reference/open-bfme-1"
    (donor / "game").mkdir(parents=True)
    header = donor / "game/names.h"
    header.write_text("struct OriginalName {};\n")
    _git(donor, "init", "-q")
    _git(donor, "add", "game")
    _git(donor, "-c", "user.name=Test", "-c", "user.email=test@example.invalid", "commit", "-qm", "donor")
    sha = _git(donor, "rev-parse", "HEAD").strip()
    # BFME 1's unrelated reciprocal reference is absent in real worktrees too.
    _git(donor, "update-index", "--add", "--cacheinfo", f"160000,{sha},inputs/reference/open-bfme-2")
    _git(tree, "update-index", "--add", "--cacheinfo", f"160000,{sha},reference/open-bfme-1")
    first_stamp = name_lane.PickerCache(lane_of(tree)).stamp
    assert first_stamp
    header.write_text("struct ChangedOriginalName {};\n")
    assert name_lane.PickerCache(lane_of(tree)).stamp != first_stamp


@pytest.mark.parametrize("repair", ["sumBox", "m_count"])
def test_reviewer_revises_invalid_answer_only_once_before_voting(tree, tmp_path, repair):
    first(tree, tmp_path)
    calls = []
    def runner(packet, *_):
        calls.append(packet)
        assert len(rows(tree, name_lane.VOTES)) == 1
        if packet.get("revision"):
            assert "sumBox" not in json.dumps(packet)
            assert packet["targets"][0]["proposed_name"] == "m_count"
            assert "collides" in packet["targets"][0]["validation_error"]
            return answer(packet, repair)
        return answer(packet, "m_count")
    result = name_review.dispatch(lane_of(tree), runner=runner)
    assert len(calls) == 2
    assert result["revision"] == dict(attempted=1, revised=1)
    assert result["votes_recorded"] == (1 if repair == "sumBox" else 0)


def three_pending(tree, tmp_path, **options):
    paths = [SOURCE]
    for n in (3, 4):
        rel = f"Code/Game/Box{n}.cpp"
        (tree / rel).write_text(BOX.replace("00401000", f"0040{n}000"))
        with (tree / "reverse/functions.csv").open("a") as handle:
            handle.write(f"?rva0040{n}000@@YAHPAURva0040{n}000Box@@H@Z,,0x0040{n}000,20,{rel},matched,\n")
        paths.append(rel)
    for index, rel in enumerate(paths):
        old = "rva00401000" if index == 0 else f"rva0040{index+2}000"
        serve(tree, f"p{index}", file=rel, worker="original")
        path = tmp_path / f"p{index}.json"
        path.write_text(json.dumps({old: "sumBox"}))
        name_lane.cmd_submit(lane_of(tree), argparse.Namespace(answer=str(path), session=f"p{index}",
                             model="claude-opus-5-5", no_auto_review=True))
    enable(tree, count=1, max_keys=3, **options)


@pytest.mark.parametrize("strict, batches", [(False, 1), (True, 3)])
def test_review_fills_key_budget_and_honors_explicit_hard_file_cap(tree, tmp_path, strict, batches):
    three_pending(tree, tmp_path, strict_count=strict)
    result = name_review.dispatch(lane_of(tree), runner=lambda p, *_: answer(p, "sumBox"))
    assert result["batch_count"] == batches and result["reviewed"] == 3


def test_review_splits_to_character_budget_instead_of_failing(tree, tmp_path):
    three_pending(tree, tmp_path, max_chars=700)
    sizes = []
    def runner(packet, *_):
        sizes.append(len(json.dumps(packet, ensure_ascii=True)))
        return answer(packet, "sumBox")
    result = name_review.dispatch(lane_of(tree), runner=runner)
    assert result["reviewed"] == 3 and result["batch_count"] == 3
    assert sizes and max(sizes) <= 700
