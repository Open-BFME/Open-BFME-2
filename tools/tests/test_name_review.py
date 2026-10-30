"""Dispatch real independent votes through the lane; inject only the AI runner.

The subprocess adapter has separate real-process tests with a tiny fake CLI.
No test sends fixture source to a model or uses production claims.
"""
import argparse
import json
import os
from pathlib import Path
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_lane
import name_review
import rename
from test_name_lane import (tree, seat, lane_of, vote, rows, SOURCE, FN_KEY,
                            FN_ANSWER, no_checks, ok_verify)


def enable(root, **options):
    config = dict(enabled=True, worker="independent-reviewer", model="gpt-6.1-sol",
                  count=6, max_keys=10, timeout=30, max_chars=150000,
                  resolve_disagreements=False)
    config.update(options)
    name_review.save_json(name_review.config_path(lane_of(root)), config)
    return config


def first(root, tmp_path, **config):
    vote(root, tmp_path, "first", FN_ANSWER, worker="original-worker")
    return enable(root, **config)


def answer(packet, name="sumBox"):
    return {"answers": [{"key": item["key"], "name": name,
                         "reason": "Computed from the function body"} for item in packet["targets"]]}


def test_independent_dispatch_serves_a_single_review_and_records_real_quorum(tree, tmp_path):
    first(tree, tmp_path)
    owner = os.environ["BFME_CLAIM_OWNER"]
    source = (tree / SOURCE).read_bytes()
    def runner(packet, config, job):
        raw = json.dumps(packet)
        assert "sumBox" not in raw  # the original proposal remains blind
        assert "name_votes" not in raw and "hash" not in raw
        assert [item["key"] for item in packet["targets"]] == [FN_KEY]
        assert packet["sources"][0]["source"] == source.decode()
        return answer(packet)
    result = name_review.dispatch(lane_of(tree), runner=runner)
    assert result["newly_agreed"] == [FN_KEY]
    assert result["votes_recorded"] == 1
    assert len({row["worker"] for row in rows(tree, name_lane.VOTES)}) == 2
    assert lane_of(tree).state()[FN_KEY]["status"] == "agreed"
    assert (tree / SOURCE).read_bytes() == source  # integrator owns application
    assert os.environ["BFME_CLAIM_OWNER"] == owner
    result = name_review.dispatch(lane_of(tree), keys=[FN_KEY],
        runner=lambda *a: pytest.fail("already reviewed keys must not relaunch AI"))
    assert result["status"] == "empty"


def test_integrator_can_apply_new_review_approval_with_normal_verification(tree, tmp_path):
    first(tree, tmp_path)
    builds = []
    result = name_review.dispatch(lane_of(tree), runner=lambda packet, *_: answer(packet),
        apply_ready=1, verify=lambda ctx, sources: builds.append(sources) or True, checks=no_checks)
    assert result["newly_agreed"] == [FN_KEY]
    assert lane_of(tree).state()[FN_KEY]["status"] == "landed"
    assert builds == [[SOURCE]]


def test_disagreement_remains_unapproved(tree, tmp_path):
    first(tree, tmp_path)
    result = name_review.dispatch(lane_of(tree), runner=lambda packet, *_: answer(packet, "advanceQueue"))
    assert result["votes_recorded"] == 1 and result["newly_agreed"] == []
    assert FN_KEY not in lane_of(tree).state()


def test_comparison_accepts_original_without_new_blind_vote(tree, tmp_path):
    first(tree, tmp_path, resolve_disagreements=True)
    packets = []
    def runner(packet, _config, _job, *, resolution=False):
        packets.append((resolution, packet))
        if resolution:
            assert packet["targets"][0]["proposals"] == ["sumBox", "addBoxWidth"]
            return {"answers": [{"key": FN_KEY, "name": "sumBox",
                                 "reason": "The function sums the width into the box value"}]}
        assert "sumBox" not in json.dumps(packet)
        return answer(packet, "addBoxWidth")
    result = name_review.dispatch(lane_of(tree), runner=runner)
    assert [mode for mode, _ in packets] == [False, True]
    assert len(rows(tree, name_lane.VOTES)) == 2
    assert len(rows(tree, name_lane.RESOLUTIONS)) == 1
    assert result["newly_agreed"] == [FN_KEY]
    assert lane_of(tree).state()[FN_KEY]["new"] == "sumBox"


def test_comparison_chooses_reviewer_name_then_original_accepts(tree, tmp_path):
    first(tree, tmp_path, resolve_disagreements=True)
    def runner(packet, _config, _job, *, resolution=False):
        if resolution:
            return {"answers": [{"key": FN_KEY, "name": "addBoxWidth",
                                 "reason": "The body adds width to the box value"}]}
        return answer(packet, "addBoxWidth")
    result = name_review.dispatch(lane_of(tree), runner=runner)
    assert result["newly_agreed"] == []
    assert result["resolution"]["decisions"][0]["status"] == "pending"
    assert FN_KEY not in lane_of(tree).state()
    os.environ["BFME_CLAIM_OWNER"] = "original-worker"
    name_lane.cmd_resolve(lane_of(tree), argparse.Namespace(key=FN_KEY, name="addBoxWidth",
        reason="The body adds width to the box value"))
    assert lane_of(tree).state()[FN_KEY]["status"] == "agreed"


def test_source_change_during_review_rejects_stale_vote(tree, tmp_path):
    first(tree, tmp_path)
    def runner(packet, *_):
        path = tree / SOURCE
        path.write_bytes(path.read_bytes() + b"\n")
        return answer(packet)
    result = name_review.dispatch(lane_of(tree), runner=runner)
    assert result["votes_recorded"] == 0 and result["rejected"] == 1
    assert len(rows(tree, name_lane.VOTES)) == 1


def test_runner_failure_keeps_vote_and_releases_slot(tree, tmp_path):
    first(tree, tmp_path)
    def failure(*_):
        raise name_review.ReviewError("fixture timeout")
    with pytest.raises(name_review.ReviewError):
        name_review.dispatch(lane_of(tree), runner=failure)
    assert len(rows(tree, name_lane.VOTES)) == 1
    assert name_review.dispatch(lane_of(tree), runner=lambda packet, *_: answer(packet))["newly_agreed"] == [FN_KEY]


def test_same_worker_cannot_create_a_second_vote(tree, tmp_path):
    first(tree, tmp_path, worker="original-worker")
    result = name_review.dispatch(lane_of(tree), keys=[FN_KEY], runner=lambda *_: pytest.fail("self review"))
    assert result["status"] == "empty"
    assert len(rows(tree, name_lane.VOTES)) == 1


def test_busy_reviewer_does_not_launch_another_model(tree, tmp_path):
    first(tree, tmp_path)
    path = name_review.config_path(lane_of(tree)).parent / "reviewer.lock"
    with path.open("a+b") as held:
        assert name_review.try_lock(held)
        try:
            result = name_review.dispatch(lane_of(tree), runner=lambda *_: pytest.fail("second model"))
            assert result["status"] == "busy"
        finally:
            name_review.portable_lock.unlock(held)


def test_review_is_bounded_and_key_filtered(tree, tmp_path):
    vote(tree, tmp_path, "first", {**FN_ANSWER, "Rva00401000Box::m_x2C": "m_width"}, worker="original-worker")
    enable(tree, max_keys=1)
    result = name_review.dispatch(lane_of(tree), keys=[FN_KEY], runner=lambda packet, *_: answer(packet))
    assert result["reviewed"] == 1 and result["newly_agreed"] == [FN_KEY]


@pytest.mark.parametrize("bad", [
    {"answers": []},
    {"answers": [{"key": "unknown", "name": "sumBox", "reason": "body"}]},
    {"answers": [{"key": FN_KEY, "name": "sumBox", "reason": ""}]},
    {"answers": [{"key": FN_KEY, "name": "sumBox", "reason": "body"}] * 2},
])
def test_malformed_response_does_not_record_votes(tree, tmp_path, bad):
    first(tree, tmp_path)
    with pytest.raises(name_review.ReviewError):
        name_review.dispatch(lane_of(tree), runner=lambda *_: bad)
    assert len(rows(tree, name_lane.VOTES)) == 1


def test_background_launch_is_noninteractive_and_does_not_recurse(tree, monkeypatch):
    enable(tree)
    calls = []
    assert name_review.maybe_launch(lane_of(tree), launch=lambda *a, **kw: calls.append((a, kw)))
    assert len(calls) == 1
    args, kwargs = calls[0]
    assert args[0][-1] == "review"
    assert kwargs["shell"] is False
    assert kwargs["env"]["BFME_NAME_REVIEW_CHILD"] == "1"
    monkeypatch.setenv("BFME_NAME_REVIEW_CHILD", "1")
    assert not name_review.maybe_launch(lane_of(tree), launch=lambda *_: pytest.fail("recursive review"))


def test_submit_dispatches_after_recording_votes(tree, tmp_path, monkeypatch):
    calls = []
    def launch(lane):
        assert len(lane.votes()) == 1
        calls.append(True)
    monkeypatch.setattr(name_review, "maybe_launch", launch)
    vote(tree, tmp_path, "first", FN_ANSWER, worker="original-worker")
    assert calls == [True]


def test_disabled_dispatch_is_a_noop(tree):
    assert name_review.dispatch(lane_of(tree))["status"] == "disabled"


FAKE_CLI = '''import sys,json,time
from pathlib import Path
prompt=sys.stdin.read()
mode=Path(__file__).stem
if mode=='timeout': time.sleep(10)
if mode=='failure': sys.exit(7)
path=Path(sys.argv[sys.argv.index('--output-last-message')+1])
path.write_text(json.dumps({'answers':[{'key':'key','name':'name','reason':'body'}]}))
kind='command_execution' if mode=='tool' else 'agent_message'
print(json.dumps({'type':'item.completed','item':{'type':kind,'text':'done'}}))
'''


@pytest.mark.parametrize("mode", ["success", "tool", "timeout", "failure"])
def test_cli_adapter_uses_fresh_context_and_fails_closed(tmp_path, monkeypatch, mode):
    script = tmp_path / (mode + ".py")
    script.write_text(FAKE_CLI)
    job = tmp_path / "job"
    job.mkdir()
    monkeypatch.setattr(name_review, "codex_command", lambda: [sys.executable, str(script)])
    packet = {"targets": [{"key": "key"}], "sources": []}
    config = dict(model="gpt-6.1-sol", timeout=0.2 if mode == "timeout" else 10)
    if mode == "success":
        result = name_review.run_codex(packet, config, job)
        assert result["answers"][0]["name"] == "name"
    else:
        with pytest.raises(name_review.ReviewError):
            name_review.run_codex(packet, config, job)



def test_unchanged_skipped_target_is_not_reviewed_repeatedly(tree, tmp_path):
    first(tree, tmp_path)
    first_result = name_review.dispatch(lane_of(tree), runner=lambda packet, *_: answer(packet, "skip"))
    assert first_result["skipped"] == 1
    again = name_review.dispatch(lane_of(tree), runner=lambda *_: pytest.fail("unchanged skip rerolled"))
    assert again["status"] == "empty"


MEMBER_KEY = SOURCE + "|member|Rva00401000Box|m_x2C"


def two_pending(root, tmp_path, **options):
    vote(root, tmp_path, "first", {**FN_ANSWER, "Rva00401000Box::m_x2C": "m_width"},
         worker="original-worker")
    enable(root, max_keys=1, **options)


def matching_batch(packet, *_):
    return {"answers": [{"key": item["key"],
                         "name": "sumBox" if item["key"] == FN_KEY else "m_width",
                         "reason": "Read the declaration and body"} for item in packet["targets"]]}


def test_drain_reviews_every_key_in_multiple_bounded_batches(tree, tmp_path):
    two_pending(tree, tmp_path)
    calls = []
    def runner(packet, *args):
        assert len(packet["targets"]) == 1
        calls.extend(item["key"] for item in packet["targets"])
        return matching_batch(packet)
    result = name_review.dispatch(lane_of(tree), runner=runner)
    assert result["reviewed"] == 2 and result["batch_count"] == 2
    assert result["status"] == "complete" and result["stop_reason"] == "empty"
    assert set(calls) == {FN_KEY, MEMBER_KEY} and len(calls) == len(set(calls))
    assert set(result["newly_agreed"]) == {FN_KEY, MEMBER_KEY}


def test_drain_continues_after_skip_without_rerolling(tree, tmp_path):
    two_pending(tree, tmp_path)
    calls = []
    def runner(packet, *_):
        calls.extend(item["key"] for item in packet["targets"])
        return answer(packet, "skip")
    result = name_review.dispatch(lane_of(tree), runner=runner)
    assert result["skipped"] == 2 and result["batch_count"] == 2
    assert len(calls) == len(set(calls)) == 2
    assert name_review.dispatch(lane_of(tree), runner=lambda *_: pytest.fail("reroll"))["status"] == "empty"


def test_optional_batch_budget_reports_pause_and_next_run_resumes(tree, tmp_path):
    two_pending(tree, tmp_path, max_batches=1)
    result = name_review.dispatch(lane_of(tree), runner=matching_batch)
    assert result["reviewed"] == 1 and result["stop_reason"] == "batch_limit"
    assert result["status"] == "paused"
    again = name_review.dispatch(lane_of(tree), runner=matching_batch)
    assert again["reviewed"] == 1
    assert set(result["keys"]).isdisjoint(again["keys"])


def test_drain_honors_disable_between_batches(tree, tmp_path):
    two_pending(tree, tmp_path)
    def runner(packet, *_):
        config = name_review.load_config(lane_of(tree))
        name_review.save_json(name_review.config_path(lane_of(tree)), dict(config, enabled=False))
        return matching_batch(packet)
    result = name_review.dispatch(lane_of(tree), runner=runner)
    assert result["reviewed"] == 1 and result["stop_reason"] == "disabled"


def test_apply_budget_is_shared_across_the_entire_drain(tree, tmp_path):
    two_pending(tree, tmp_path)
    result = name_review.dispatch(lane_of(tree), runner=matching_batch,
                                 apply_ready=1, verify=ok_verify, checks=no_checks)
    assert result["reviewed"] == 2 and result["apply_selected"] == 1
    assert sorted(lane_of(tree).state()[key]["status"] for key in (FN_KEY, MEMBER_KEY)) == ["agreed", "landed"]
