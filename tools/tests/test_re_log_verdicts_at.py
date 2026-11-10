#!/usr/bin/env python3
"""Tests for re_log.verdicts_at(): standing verdicts indexed by BOUNDARY.

A verdict retires the name it was recorded against, not the address. One retail
address routinely carries several drifted names (next_work.py prints "+21
name(s) at this address"), so the queue re-serves the same bytes under the next
name -- correctly, because "not A" is no proof of "not B". What was missing is
the evidence: 0x0054C5D5 was recorded mis-anchored as
deque<BfmeE8>::_M_range_check, the body being a formatted-exception builder, and
came back as deque<BfmeE8>::resize with no sign anybody had disassembled it.
verdicts_at() is what next_work.py prints so that no longer happens; it must
never filter, only report.
"""
import json
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import re_log  # noqa: E402
import next_work  # noqa: E402


@pytest.fixture
def log(tmp_path, monkeypatch):
    path = tmp_path / "reverse" / "re_attempts.log"
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("", encoding="utf-8")
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", path)
    re_log._reset()
    try:
        yield path
    finally:
        re_log._reset()


def write(log, *rows):
    log.write_text(
        "".join("\t".join(row) + "\n" for row in rows), encoding="utf-8")
    re_log._reset()


def test_a_verdict_is_found_under_the_address_it_was_recorded_against(log):
    write(log, ("?range_check@A@@", "0x0054C5D5", "117", "mis-anchored?",
                "body builds a formatted exception message"))
    assert re_log.verdicts_at(0x0054C5D5) == [
        ("?range_check@A@@", "mis-anchored?",
         "body builds a formatted exception message")]


def test_the_asking_symbol_is_excluded_so_it_does_not_cite_itself(log):
    write(log, ("?resize@A@@", "0x0054C5D5", "94", "blocked", "shape gap"))
    assert re_log.verdicts_at(0x0054C5D5, exclude="?resize@A@@") == []
    assert re_log.verdicts_at(0x0054C5D5, exclude="?other@A@@") != []


def test_a_sibling_name_at_the_same_address_is_reported_not_suppressed(log):
    """The whole point: the queue keeps serving the address, with the evidence."""
    write(log, ("?range_check@A@@", "0x0054C5D5", "117", "mis-anchored?", "why"))
    found = re_log.verdicts_at(0x0054C5D5, exclude="?resize@A@@")
    assert [row[0] for row in found] == ["?range_check@A@@"]
    # and it stays servable -- verdicts_at reports, is_dead_end decides
    assert not re_log.is_dead_end("?resize@A@@", 0x0054C5D5)


def test_boundary_findings_sort_ahead_of_resolved_ahead_of_deferrals(log):
    write(log,
          ("?c@A@@", "0x00401000", "8", "blocked", "deferral"),
          ("?b@A@@", "0x00401000", "8", "converted", "resolved"),
          ("?a@A@@", "0x00401000", "8", "refuted", "boundary finding"))
    assert [row[1] for row in re_log.verdicts_at(0x00401000)] == [
        "refuted", "converted", "blocked"]


def test_a_void_row_removes_the_verdict_from_the_address_index(log):
    write(log,
          ("?a@A@@", "0x00401000", "8", "mis-anchored?", "typed the wrong rva"),
          ("?a@A@@", "0x00401000", "8", "void", "retracted"))
    assert re_log.verdicts_at(0x00401000) == []


def test_a_later_verdict_at_the_same_boundary_supersedes_the_earlier_one(log):
    write(log,
          ("?a@A@@", "0x00401000", "8", "blocked", "first look"),
          ("?a@A@@", "0x00401000", "8", "mis-anchored?", "second look"))
    assert re_log.verdicts_at(0x00401000) == [
        ("?a@A@@", "mis-anchored?", "second look")]


def test_a_verdict_recorded_with_no_rva_is_not_attributed_to_any_address(log):
    write(log, ("?a@A@@", "", "8", "mis-anchored?", "no boundary examined"))
    assert re_log.verdicts_at(0x00401000) == []
    # it still governs the symbol itself
    assert re_log.standing_status("?a@A@@") == "mis-anchored?"


def test_an_address_nobody_has_touched_reports_nothing(log):
    write(log, ("?a@A@@", "0x00401000", "8", "refuted", "why"))
    assert re_log.verdicts_at(0x00402000) == []


def test_an_annotation_status_never_reaches_the_address_index(log):
    """Only verdicts stand; a free-text annotation must not masquerade as one."""
    write(log, ("?a@A@@", "0x00401000", "8", "note", "just an observation"))
    assert re_log.verdicts_at(0x00401000) == []


def test_picker_prints_own_latest_attempt_and_untruncated_evidence(log, capsys):
    path = "reverse/attempt_support/vision-investigation/readme.md"
    evidence = "Failed instruction scheduling trials. " * 12 + "Evidence: " + path
    write(log,
          ("?vision@@", "0x0028F326", "294", "blocked", "obsolete hypothesis"),
          ("?vision@@", "0x0028F326", "294", "blocked", evidence))
    candidate = {"function": "?vision@@", "target_rva": "0x0028F326",
                 "size": 294, "notes": "caller lead", "source": "Code/Caller.cpp",
                 "command": "python3 tools/explain_mismatch.py 0x0028F326"}
    next_work.print_candidate("reloc-named unclaimed function", candidate, {"pool": 1})
    output = capsys.readouterr().out
    assert "prior attempt: blocked" in output
    assert evidence in output and path in output
    assert "obsolete hypothesis" not in output
    assert output.index(path) < output.index("start:")
    assert "Read the prior evidence before retrying" in output
    assert candidate["prior_attempt"] == {
        "status": "blocked", "evidence": evidence, "log": "reverse/re_attempts.log"}


def test_picker_still_shows_other_names_and_their_evidence_links(log, capsys):
    path = "reverse/attempt_support/other-name/readme.md"
    evidence = "Independent boundary findings. " * 12 + path
    write(log,
          ("?old@@", "0x00401000", "8", "mis-anchored?", evidence),
          ("?new@@", "0x00401000", "8", "blocked", "different hypothesis"))
    next_work._print_boundary_verdicts({"function": "?new@@", "target_rva": "0x00401000"})
    output = capsys.readouterr().out
    assert "prior attempt: blocked" in output
    assert "mis-anchored? as ?old@@" in output
    assert evidence in output


def test_picker_does_not_present_a_voided_attempt_as_a_blocker(log, capsys):
    write(log,
          ("?vision@@", "0x0028F326", "294", "blocked", "retracted hypothesis"),
          ("?vision@@", "0x0028F326", "294", "void", "bad trial"))
    candidate = {"function": "?vision@@", "target_rva": "0x0028F326",
                 "prior_attempt": {"status": "blocked", "evidence": "stale annotation"}}
    next_work._print_boundary_verdicts(candidate)
    assert capsys.readouterr().out == ""
    assert "prior_attempt" not in candidate


def test_picker_does_not_attach_an_old_boundary_to_a_corrected_candidate(log):
    write(log, ("?vision@@", "0x0028F320", "300", "blocked", "old boundary"))
    candidate = {"function": "?vision@@", "candidate_rva": "0x0028F326",
                 "hint": "drift-corrected"}
    next_work.annotate_attempts([candidate])
    assert "prior_attempt" not in candidate


def test_picker_keeps_a_symbol_only_verdict_after_a_boundary_correction(log):
    write(log, ("?vision@@", "", "294", "blocked", "symbol-wide evidence"))
    candidate = {"function": "?vision@@", "candidate_rva": "0x0028F326",
                 "hint": "drift-corrected"}
    next_work.annotate_attempts([candidate])
    assert candidate["prior_attempt"]["evidence"] == "symbol-wide evidence"


def test_picker_history_is_advisory_when_a_prerequisite_has_landed(log):
    write(log, ("?vision@@", "0x0028F326", "294", "blocked",
                "blocked-on=0x00401000 Evidence: reverse/attempt_support/vision.json"))
    re_log._MATCHED = {0x00401000}
    candidate = {"function": "?vision@@", "target_rva": "0x0028F326"}
    next_work.annotate_attempts([candidate])
    assert candidate["prior_attempt"]["status"] == "blocked"
    assert not re_log.is_deferred("?vision@@", 0x0028F326)
    assert next_work.drop_logged([candidate]) == ([candidate], 0)
    assert "deferred_attempts" not in candidate


@pytest.mark.parametrize("ranked", [False, True])
def test_picker_json_includes_prior_evidence(log, monkeypatch, capsys, ranked):
    import build
    import repair_queue

    evidence = "Failed scheduling trial; reverse/attempt_support/vision/readme.md"
    write(log, ("?vision@@", "0x0028F326", "294", "blocked", evidence))
    candidate = {"function": "?vision@@", "target_rva": "0x0028F326",
                 "size": 294, "source": "Code/Caller.cpp"}
    args = ["next_work.py", "--tier", "named", "--json"]
    monkeypatch.setattr(sys, "argv", args + (["--ranked"] if ranked else []))
    monkeypatch.setattr(next_work, "check_ledger", lambda: "ledger healthy")
    monkeypatch.setattr(build, "load_claim_rows", lambda **kwargs: [])
    # next_work.without_busy consults next_work.busy_keys() (claims.busy_keys),
    # not claims.busy_rvas. Stubbing only the latter left the queue filtered
    # against the fleet's LIVE claims, so this test dropped its own candidate and
    # failed -- and would have passed or failed depending on what peers held.
    monkeypatch.setattr(next_work, "busy_keys", lambda: set())
    monkeypatch.setattr(next_work.claims, "busy_rvas", lambda: set())
    monkeypatch.setattr(next_work, "reloc_named_candidates",
                        lambda *args: ([candidate], "fixture"))
    monkeypatch.setattr(next_work, "annotate_wb", lambda queue: queue)
    monkeypatch.setattr(next_work, "annotate_wpo", lambda queue: queue)
    monkeypatch.setattr(next_work, "wpo_detect", None)
    monkeypatch.setattr(repair_queue, "annotate_dest", lambda queue: queue)
    monkeypatch.setattr(next_work, "weighted_choice",
                        lambda queue: queue[0] if queue else None)
    next_work.main()
    output = json.loads(capsys.readouterr().out)
    served = output["reloc_named"][0] if ranked else output["selection"]
    assert served["function"] == candidate["function"]
    assert served["prior_attempt"] == {
        "status": "blocked", "evidence": evidence, "log": "reverse/re_attempts.log"}
