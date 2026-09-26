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
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import re_log  # noqa: E402


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
