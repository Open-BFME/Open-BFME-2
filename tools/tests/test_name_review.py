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


def test_response_schema_requires_every_declared_answer_field():
    item = name_review.response_schema([FN_KEY])["properties"]["answers"]["items"]
    assert set(item["required"]) == set(item["properties"])


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


def test_comparison_receives_independent_role_descriptions(tree, tmp_path):
    vote(tree, tmp_path, "first", {"rva00401000": {
        "name": "sumBox", "role": "Adds the box width to the supplied count."}},
        worker="original-worker")
    enable(tree, resolve_disagreements=True)
    def runner(packet, _config, _job, *, resolution=False):
        if resolution:
            assert packet["targets"][0]["roles"] == [
                "Adds the box width to the supplied count.",
                "Computes the sum using the box width."]
            return {"answers": [{"key": FN_KEY, "name": "sumBox",
                                 "reason": "The function sums the box width and count"}]}
        assert "sumBox" not in json.dumps(packet)
        return {"answers": [{"key": FN_KEY, "name": "addBoxWidth",
                             "role": "Computes the sum using the box width.",
                             "reason": "The body reads width and adds the argument"}]}
    result = name_review.dispatch(lane_of(tree), runner=runner)
    assert result["newly_agreed"] == [FN_KEY]
    assert result["blind_seconds"] >= 0
    assert result["resolution"]["seconds"] >= 0


def test_comparison_leaves_conflicting_interpretations_unresolved(tree, tmp_path):
    first(tree, tmp_path, resolve_disagreements=True)
    def runner(packet, _config, _job, *, resolution=False):
        if resolution:
            return {"answers": [{"key": FN_KEY, "name": "skip",
                "reason": "The two names claim different effects and the body is inconclusive"}]}
        return answer(packet, "advanceQueue")
    result = name_review.dispatch(lane_of(tree), runner=runner)
    assert result["resolution_counts"] == {"unresolved": 1}
    assert FN_KEY not in lane_of(tree).state()


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
    assert args[0][-2:] == ["review", "--propose-only"]
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


def test_automatic_setup_uses_installed_model_and_a_stable_identity(tree, tmp_path, monkeypatch):
    vote(tree, tmp_path, "original", FN_ANSWER, worker="original-worker")
    monkeypatch.setattr(name_review, "codex_command", lambda: ["codex"])
    monkeypatch.setattr(name_review, "configured_model", lambda: "gpt-6.1-sol")
    monkeypatch.delenv("CLAUDECODE", raising=False)
    monkeypatch.delenv("CLAUDE_CODE_SESSION_ID", raising=False)
    launches = []
    assert name_review.maybe_launch(lane_of(tree), auto_configure=True,
                                    launch=lambda *a, **kw: launches.append((a, kw)))
    config = name_review.load_config(lane_of(tree))
    assert config["worker"] == name_review.default_worker(lane_of(tree))
    assert config["model"] == "gpt-6.1-sol" and config["resolve_disagreements"]
    assert config["max_keys"] == 10 and config["timeout"] == 300
    monkeypatch.setattr(name_review, "configured_model", lambda: pytest.fail("must reuse fleet configuration"))
    assert name_review.ensure_automatic_config(lane_of(tree)) == config
    assert len(launches) == 1


def test_automatic_setup_honors_explicit_disable(tree, monkeypatch):
    enable(tree, enabled=False)
    monkeypatch.setattr(name_review, "codex_command", lambda: pytest.fail("disabled reviewer"))
    assert not name_review.maybe_launch(lane_of(tree), auto_configure=True,
                                       launch=lambda *_: pytest.fail("disabled reviewer"))
    assert name_review.ensure_automatic_config(lane_of(tree))["enabled"] is False


def test_default_review_identity_is_stable_and_distinct_between_accounts(tree, monkeypatch):
    lane = lane_of(tree)
    monkeypatch.setattr(lane, "git", lambda *args: "first@example.test")
    first = name_review.default_worker(lane)
    assert name_review.default_worker(lane) == first
    monkeypatch.setattr(lane, "git", lambda *args: "second@example.test")
    assert name_review.default_worker(lane) != first


def test_automatic_setup_needs_no_model_without_pending_second_reviews(tree, monkeypatch):
    monkeypatch.setattr(name_review, "codex_command", lambda: pytest.fail("no pending review"))
    assert not name_review.maybe_launch(lane_of(tree), auto_configure=True)
    assert name_review.load_config(lane_of(tree)) is None


def test_missing_runtime_does_not_create_a_broken_configuration(tree, tmp_path, monkeypatch):
    vote(tree, tmp_path, "original", FN_ANSWER, worker="original-worker")
    def unavailable():
        raise name_review.ReviewError("Codex CLI is not installed on PATH")
    monkeypatch.setattr(name_review, "codex_command", unavailable)
    monkeypatch.setattr(name_review, "claude_command", unavailable)
    monkeypatch.setattr(name_review, "opencode_command", unavailable)
    with pytest.raises(name_review.ReviewError, match="not installed"):
        name_review.maybe_launch(lane_of(tree), auto_configure=True)
    assert name_review.load_config(lane_of(tree)) is None


@pytest.mark.parametrize("options, automatic, limit", [
    ([], True, None), (["--propose-only"], False, None), (["--apply-ready", "1"], False, 1),
])
def test_review_cli_applies_new_batches_by_default(tree, monkeypatch, options, automatic, limit):
    calls = []
    monkeypatch.setattr(name_review, "dispatch", lambda lane, **kw: calls.append(kw) or {})
    assert name_lane.main(["review", *options], lane=lane_of(tree)) == 0
    assert calls[0]["apply_new"] is automatic and calls[0]["apply_ready"] == limit


@pytest.mark.parametrize("host, expected", [("codex", "codex"), ("claude", "claude")])
def test_runtime_detection_prefers_the_submitting_provider(monkeypatch, host, expected):
    monkeypatch.delenv("CLAUDECODE", raising=False)
    monkeypatch.delenv("CLAUDE_CODE_SESSION_ID", raising=False)
    monkeypatch.delenv("OPENCODE", raising=False)
    if host == "claude":
        monkeypatch.setenv("CLAUDECODE", "1")
    monkeypatch.setattr(name_review, "codex_command", lambda: ["codex"])
    monkeypatch.setattr(name_review, "claude_command", lambda: ["claude"])
    monkeypatch.setattr(name_review, "configured_model", lambda: "gpt-6.1-sol")
    monkeypatch.setattr(name_review, "configured_claude_model", lambda: "sonnet")
    provider, model = name_review.reviewer_runtime()
    assert provider == expected
    assert model == ("sonnet" if provider == "claude" else "gpt-6.1-sol")


def test_runtime_detection_works_on_a_claude_only_host(monkeypatch):
    monkeypatch.delenv("CLAUDECODE", raising=False)
    monkeypatch.delenv("CLAUDE_CODE_SESSION_ID", raising=False)
    monkeypatch.delenv("OPENCODE", raising=False)
    def unavailable():
        raise name_review.ReviewError("Codex CLI is not installed on PATH")
    monkeypatch.setattr(name_review, "codex_command", unavailable)
    monkeypatch.setattr(name_review, "claude_command", lambda: ["claude"])
    monkeypatch.setattr(name_review, "configured_claude_model", lambda: "sonnet")
    assert name_review.reviewer_runtime() == ("claude", "sonnet")
    with pytest.raises(name_review.ReviewError, match="Codex"):
        name_review.reviewer_runtime("codex")


@pytest.mark.parametrize("provider", ["codex", "claude", "opencode"])
def test_model_adapter_uses_configured_provider(monkeypatch, provider):
    calls = []
    monkeypatch.setattr(name_review, "run_codex", lambda *a, **kw: calls.append("codex") or {})
    monkeypatch.setattr(name_review, "run_claude", lambda *a, **kw: calls.append("claude") or {})
    monkeypatch.setattr(name_review, "run_opencode", lambda *a, **kw: calls.append("opencode") or {})
    name_review.run_model({}, {"provider": provider}, None)
    assert calls == [provider]


FAKE_CLAUDE = r'''
import json, os, sys, time
mode=sys.argv[1]
flags=sys.argv[2:]
assert '--safe-mode' in flags and '--no-session-persistence' in flags
assert flags[flags.index('--tools')+1] == ''
assert flags[flags.index('--disallowedTools')+1] == 'mcp__*'
assert '--strict-mcp-config' in flags
assert '--resume' not in flags and '--continue' not in flags
assert 'CLAUDECODE' not in os.environ and 'BFME_CLAIM_OWNER' not in os.environ
assert os.environ.get('BFME_NAME_REVIEW_CHILD') == '1'
assert not os.path.exists('reverse/name_votes.csv')
prompt=sys.stdin.read()
assert 'packet' in prompt
if mode == 'timeout': time.sleep(10)
if mode == 'failure': sys.exit(7)
if mode == 'tool':
    print(json.dumps({'type':'assistant','message':{'content':[{'type':'tool_use','name':'Read'}]}}))
if mode == 'error':
    print(json.dumps({'type':'result','subtype':'error_during_execution','is_error':True})); sys.exit(0)
result={'type':'result','subtype':'success','is_error':False}
if mode != 'missing':
    result['structured_output']={'answers':[{'key':'key','name':'name','reason':'body'}]}
print(json.dumps(result))
'''


@pytest.mark.parametrize("mode", ["success", "tool", "timeout", "failure", "error", "missing"])
def test_claude_adapter_is_packet_only_and_fails_closed(tmp_path, monkeypatch, mode):
    script = tmp_path / "fake-claude.py"
    script.write_text(FAKE_CLAUDE)
    job = tmp_path / "claude-job"
    job.mkdir()
    monkeypatch.setattr(name_review, "claude_command", lambda: [sys.executable, str(script), mode])
    monkeypatch.setenv("CLAUDECODE", "1")
    monkeypatch.setenv("CLAUDE_CODE_SESSION_ID", "original-session")
    config = {"provider": "claude", "model": "sonnet", "timeout": 0.3 if mode == "timeout" else 10}
    packet = {"targets": [{"key": "key"}], "sources": [{"file": "packet", "source": "packet"}]}
    if mode == "success":
        result = name_review.run_claude(packet, config, job)
        assert result["answers"][0]["name"] == "name"
        assert json.loads((job / "response.json").read_text()) == result
    else:
        with pytest.raises(name_review.ReviewError):
            name_review.run_claude(packet, config, job)


@pytest.mark.parametrize("backend, model", [("codex", "gpt-6.1-sol"), ("claude", "sonnet"),
                                           ("opencode", "test-provider/test-model")])
def test_t3_uses_a_fresh_underlying_cli_without_starting_a_t3_server(monkeypatch, backend, model):
    monkeypatch.delenv("BFME_NAME_REVIEW_T3_BACKEND", raising=False)
    monkeypatch.setattr(name_review, "codex_command", lambda: ["codex"])
    monkeypatch.setattr(name_review, "claude_command", lambda: ["claude"])
    monkeypatch.setattr(name_review, "opencode_command", lambda: ["opencode"])
    assert name_review.reviewer_runtime("t3", model, t3_backend=backend) == (backend, model)
    assert name_review.reviewer_runtime("t3", model) == (backend, model)


def test_opencode_model_detection_reads_jsonc_without_exposing_other_config(tmp_path, monkeypatch):
    monkeypatch.setenv("XDG_CONFIG_HOME", str(tmp_path / "config"))
    for key in ("OPENCODE_CONFIG", "OPENCODE_CONFIG_DIR", "OPENCODE_CONFIG_CONTENT"):
        monkeypatch.delenv(key, raising=False)
    config = tmp_path / "config/opencode/opencode.jsonc"
    config.parent.mkdir(parents=True)
    config.write_text('{ // default\n "model":"test-provider/global", "url":"https://example.test/a,}", }')
    assert name_review.configured_opencode_model() == "test-provider/global"
    root = tmp_path / "project"
    root.mkdir()
    (root / "opencode.json").write_text('{"model":"test-provider/project"}')
    assert name_review.configured_opencode_model(root) == "test-provider/project"
    monkeypatch.setenv("OPENCODE_CONFIG_CONTENT", '{"model":"test-provider/inline"}')
    assert name_review.configured_opencode_model(root) == "test-provider/inline"
    monkeypatch.setenv("OPENCODE_CONFIG_CONTENT", '{"model":{"providerID":"test-provider","model":"native","variant":"high"}}')
    assert name_review.configured_opencode_model(root) == "test-provider/native#high"


def test_opencode_reviewer_keeps_inline_provider_routes_but_denies_tools(monkeypatch):
    provider = {"test-provider": {"options": {"baseURL": "https://example.test", "apiKey": "fixture-only"}}}
    monkeypatch.setenv("OPENCODE_CONFIG_CONTENT", json.dumps({"provider": provider, "permission": {"*": "allow"}}))
    env = name_review.opencode_environment()
    restricted = json.loads(env["OPENCODE_CONFIG_CONTENT"])
    assert restricted["provider"] == provider
    assert restricted["permission"] == {"*": "deny"}
    assert env["OPENCODE_PERMISSION"] == '{"*":"deny"}'


def test_opencode_real_model_id_is_preserved_while_votes_use_a_safe_label(tree, tmp_path):
    first(tree, tmp_path, provider="opencode", model="test-provider/test-model#high")
    def runner(packet, config, job):
        assert config["model"] == "test-provider/test-model#high"
        return answer(packet)
    result = name_review.dispatch(lane_of(tree), runner=runner, apply_new=True, verify=ok_verify, checks=no_checks)
    assert lane_of(tree).state()[FN_KEY]["status"] == "landed"
    assert result["model"] == "test-provider/test-model#high"
    assert "/" not in result["model_label"] and "#" not in result["model_label"]
    assert any(r["model"] == result["model_label"] for r in rows(tree, name_lane.VOTES))


FAKE_OPENCODE = r'''
import json, os, sys, time
mode=sys.argv[1]
flags=sys.argv[2:]
assert flags[0] == 'run'
if '--help' in flags:
    print('run --format json' + ('' if mode == 'v1' else ' --standalone')); sys.exit(0)
assert ('--standalone' in flags) == (mode != 'v1')
assert '--session' not in flags and '--continue' not in flags and '--attach' not in flags
assert '--auto' not in flags
assert json.loads(os.environ['OPENCODE_PERMISSION']) == {'*':'deny'}
config=json.loads(os.environ['OPENCODE_CONFIG_CONTENT'])
assert config['agent']['bfme-name-reviewer']['tools'] == {'*':False}
assert os.environ['OPENCODE_PURE'] == '1'
assert os.environ['OPENCODE_DISABLE_PROJECT_CONFIG'] == '1'
assert 'BFME_CLAIM_OWNER' not in os.environ and 'CODEX_THREAD_ID' not in os.environ
assert not os.path.exists('reverse/name_votes.csv')
assert 'packet' in sys.stdin.read()
if mode == 'timeout': time.sleep(10)
if mode == 'failure': sys.exit(7)
if mode == 'tool': print(json.dumps({'type':'tool_use','part':{'type':'tool','tool':'read'}}))
if mode == 'error': print(json.dumps({'type':'error','error':{'message':'provider failed'}})); sys.exit(0)
text=json.dumps({'answers':[{'key':'key','name':'name','reason':'body'}]})
print(json.dumps({'type':'text','part':{'type':'text','text':text}}))
if mode != 'unfinished': print(json.dumps({'type':'step_finish','part':{'reason':'stop'}}))
'''


@pytest.mark.parametrize("mode", ["success", "v1", "tool", "timeout", "failure", "error", "unfinished"])
def test_opencode_adapter_is_fresh_and_fails_closed(tmp_path, monkeypatch, mode):
    script = tmp_path / "fake-opencode.py"
    script.write_text(FAKE_OPENCODE)
    job = tmp_path / "opencode-job"
    job.mkdir()
    monkeypatch.setattr(name_review, "opencode_command", lambda: [sys.executable, str(script), mode])
    monkeypatch.setenv("CODEX_THREAD_ID", "original-thread")
    config = {"provider": "opencode", "model": "test-provider/test-model",
              "timeout": 0.3 if mode == "timeout" else 10}
    packet = {"targets": [{"key": "key"}], "sources": [{"file": "packet", "source": "packet"}]}
    if mode in ("success", "v1"):
        result = name_review.run_opencode(packet, config, job)
        assert result["answers"][0]["name"] == "name"
    else:
        with pytest.raises(name_review.ReviewError):
            name_review.run_opencode(packet, config, job)


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


def test_automatic_review_applies_each_new_batch_without_leaving_ready_names(tree, tmp_path):
    two_pending(tree, tmp_path)
    builds = []
    result = name_review.dispatch(lane_of(tree), runner=matching_batch, apply_new=True,
        verify=lambda ctx, sources: builds.append(sources) or True, checks=no_checks)
    assert result["reviewed"] == 2 and result["apply_selected"] == 2
    assert result["batch_count"] == 2
    assert all(lane_of(tree).state()[key]["status"] == "landed" for key in (FN_KEY, MEMBER_KEY))
    assert builds == [[SOURCE], [SOURCE]]


def test_immediate_scoped_landing_preserves_later_disagreement_comparison(tree, tmp_path):
    from test_name_lane import serve
    serve(tree, "mixed-submit", worker="original-worker")
    path = tmp_path / "mixed-submit.json"
    path.write_text(json.dumps({**FN_ANSWER, "rva00401000:a2": "increment"}))
    name_lane.cmd_submit(lane_of(tree), argparse.Namespace(session="mixed-submit", model="claude-opus-5-5",
        answer=str(path), auto_workflow=True, no_auto_review=True), verify=ok_verify, checks=no_checks)
    assert "increment" in (tree / SOURCE).read_text()
    enable(tree, resolve_disagreements=True)
    def runner(packet, _config, _job, *, resolution=False):
        if resolution:
            assert "increment" in packet["sources"][0]["source"]
            return {"answers": [{"key": FN_KEY, "name": "sumBox",
                                  "reason": "The function adds the box width to the increment"}]}
        return answer(packet, "addBoxWidth")
    result = name_review.dispatch(lane_of(tree), runner=runner, apply_new=True,
                                  verify=ok_verify, checks=no_checks)
    assert result["resolution_counts"] == {"accepted_by_reviewer": 1}
    assert lane_of(tree).state()[FN_KEY]["status"] == "landed"


def test_verified_source_carry_does_not_refresh_a_proposal_over_an_unrelated_edit(tree, tmp_path):
    vote(tree, tmp_path, "original", FN_ANSWER, worker="original-worker")
    original = json.loads(name_lane.proposal_path(lane_of(tree), FN_KEY, lane_of(tree).worker()).read_text())
    before = (tree / SOURCE).read_bytes() + b"\n// unrelated edit\n"
    after = before.replace(b"a2", b"increment")
    (tree / SOURCE).write_bytes(after)
    name_lane.carry_verified_proposals(lane_of(tree), [argparse.Namespace(
        before={SOURCE: before}, after={SOURCE: after})])
    carried = json.loads(name_lane.proposal_path(lane_of(tree), FN_KEY, lane_of(tree).worker()).read_text())
    assert carried["source_sha"] == original["source_sha"]
    assert "verified_source_carry" not in carried


def test_source_carry_checks_disk_instead_of_a_cached_source(tree, tmp_path):
    vote(tree, tmp_path, "original", FN_ANSWER, worker="original-worker")
    lane = lane_of(tree)
    before = (tree / SOURCE).read_bytes()
    after = before.replace(b"a2", b"increment")
    (tree / SOURCE).write_bytes(after)
    assert lane.ctx.read(SOURCE) == after
    (tree / SOURCE).write_bytes(after + b"\n// concurrent edit\n")
    name_lane.carry_verified_proposals(lane, [argparse.Namespace(before={SOURCE: before}, after={SOURCE: after})])
    proposal = json.loads(name_lane.proposal_path(lane, FN_KEY, lane.worker()).read_text())
    assert "verified_source_carry" not in proposal
