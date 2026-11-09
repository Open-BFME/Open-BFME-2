"""A reviewer inherits packet-read scope, never the operator's vote or writes."""
import json
import os
from types import SimpleNamespace

import pytest

import claims
import name_lane
import name_review
from test_name_lane import (tree, seat, lane_of, vote, serve, rows, SOURCE, FN_KEY,
                            FN_ANSWER, no_checks, ok_verify)
from test_name_review import enable, answer


SLOW = "Code/Game/Slow.cpp"
SLOW_KEY = f"{SLOW}|function|0x00402000|rva00402000"


def pending_pair(root, tmp_path):
    vote(root, tmp_path, "original", FN_ANSWER, worker="original-worker")
    serve(root, "original-slow", worker="original-worker", file=SLOW)
    proposal = tmp_path / "slow-answer.json"
    proposal.write_text(json.dumps({"rva00402000": "readSlowCount"}))
    name_lane.cmd_submit(lane_of(root), SimpleNamespace(
        session="original-slow", model="claude-opus-5-5", answer=str(proposal)))
    return enable(root)


def scope_key(root, kind, source=SOURCE):
    if kind == "file":
        return claims.file_key(source), {}
    if kind == "rva":
        return (0x00401000 if source == SOURCE else 0x00402000), {}
    if kind == "class":
        # Scope expansion reads the ledger's class identity, independently of
        # the free function being reviewed in the same file.
        ledger = root / "reverse/functions.csv"
        cls = "HeldPrimary" if source == SOURCE else "HeldSlow"
        ledger.write_bytes(ledger.read_bytes() +
            f"?run@{cls}@@QAEXXZ,,0x00403000,1,{source},matched,\n".encode())
        return claims.class_key(cls), {}
    assert kind == "persisted"
    return 0x00ABCDEF, {"locks": [claims.file_key(source)]}


def claim_records(monkeypatch, local, foreign=()):
    """Inject remote records, not picker eligibility or the expanded busy set.

    Local ownership follows the active environment; records supplied as foreign
    represent another namespace/mirror and never grant authority by owner name.
    claims.busy_keys and lock_keys still perform their standard scope expansion.
    """
    monkeypatch.setenv("BFME_CLAIMS", "on")
    reads = []
    def blocking(root=None):
        owner = claims.owner(root)
        reads.append(owner)
        yield {key: info for key, info in local.items() if info["owner"] != owner}
        yield dict(foreign)
    monkeypatch.setattr(claims, "_blocking_records", blocking)
    return reads


@pytest.mark.parametrize("kind", ["file", "rva", "class", "persisted"])
def test_reviewer_reads_operator_reserved_scopes_and_excludes_foreign_source(tree, tmp_path, monkeypatch, kind):
    pending_pair(tree, tmp_path)
    owned, extra = scope_key(tree, kind)
    reads = claim_records(monkeypatch, {
        owned: dict(owner="original-worker", **extra),
        claims.file_key(SLOW): dict(owner="foreign-worker")})
    source = (tree / SOURCE).read_bytes()
    def runner(packet, config, _job):
        assert os.environ["BFME_CLAIM_OWNER"] == config["worker"]
        assert "sumBox" not in json.dumps(packet)
        assert [item["key"] for item in packet["targets"]] == [FN_KEY]
        assert [item["file"] for item in packet["sources"]] == [SOURCE]
        return answer(packet)
    result = name_review.dispatch(lane_of(tree), runner=runner)
    assert result["newly_agreed"] == [FN_KEY]
    assert reads and set(reads) == {"original-worker"}
    assert len({row["worker"] for row in rows(tree, name_lane.VOTES) if row["key"] == FN_KEY}) == 2
    assert len([row for row in rows(tree, name_lane.VOTES) if row["key"] == SLOW_KEY]) == 1
    assert (tree / SOURCE).read_bytes() == source
    assert os.environ["BFME_CLAIM_OWNER"] == "original-worker"


@pytest.mark.parametrize("kind", ["file", "rva", "class", "persisted", "foreign-namespace"])
def test_reviewer_cannot_read_a_foreign_lock_even_with_an_overlapping_own_claim(
        tree, tmp_path, monkeypatch, kind):
    pending_pair(tree, tmp_path)
    key, extra = scope_key(tree, "file" if kind == "foreign-namespace" else kind)
    claim_records(monkeypatch,
        {claims.file_key(SOURCE): dict(owner="original-worker")},
        {key: dict(owner="original-worker" if kind == "foreign-namespace" else "foreign-worker", **extra)})
    result = name_review.dispatch(lane_of(tree), keys=[FN_KEY],
                                  runner=lambda *_: pytest.fail("foreign source reached the reviewer"))
    assert result["status"] == "empty"
    assert len([row for row in rows(tree, name_lane.VOTES) if row["key"] == FN_KEY]) == 1


def test_source_application_keeps_caller_identity(tree, tmp_path, monkeypatch):
    pending_pair(tree, tmp_path)
    claim_records(monkeypatch, {claims.file_key(SOURCE): dict(owner="original-worker")})
    applications = []
    def apply(lane, args, **_kw):
        applications.append((os.environ["BFME_CLAIM_OWNER"], lane.worker(), args.key))
        return 0
    monkeypatch.setattr(name_lane, "cmd_apply", apply)
    result = name_review.dispatch(lane_of(tree), keys=[FN_KEY], runner=lambda packet, *_: answer(packet),
                                  apply_new=True, verify=ok_verify, checks=no_checks)
    assert result["newly_agreed"] == [FN_KEY]
    assert applications == [("original-worker", lane_of(tree).worker(), [FN_KEY])]


def test_application_refreshes_foreign_claims_acquired_during_review(tree, tmp_path, monkeypatch):
    pending_pair(tree, tmp_path)
    local = {claims.file_key(SOURCE): dict(owner="original-worker")}
    foreign = {}
    claim_records(monkeypatch, local, foreign)
    source = (tree / SOURCE).read_bytes()
    def runner(packet, *_):
        foreign[claims.file_key(SOURCE)] = dict(owner="new-foreign-worker")
        return answer(packet)
    result = name_review.dispatch(lane_of(tree), keys=[FN_KEY], runner=runner, apply_new=True,
        verify=lambda *_: pytest.fail("new foreign claim must stop application"), checks=no_checks)
    assert result["newly_agreed"] == [FN_KEY]
    assert lane_of(tree).state()[FN_KEY]["status"] == "agreed"
    assert (tree / SOURCE).read_bytes() == source
    assert os.environ["BFME_CLAIM_OWNER"] == "original-worker"
