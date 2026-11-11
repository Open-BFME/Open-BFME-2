"""A missing census entry is unknown, and a provider refresh is not a new census."""
import json
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_check
import link_rank


@pytest.fixture
def snapshot(monkeypatch):
    index = {
        "meta": {"date": "2026-10-24 10:28", "commit": "refreshed",
                 "census_date": "2026-10-24 02:54", "census_commit": "measured"},
        "blockers": {"Code/known.cpp": {
            "linked": True, "unresolved": [], "duplicates": [], "losers": [],
            "addresses": [], "wrong_selected": [], "unreferenced_differs": []}},
    }
    monkeypatch.setattr(link_check, "load_index", lambda: index)
    monkeypatch.setattr(link_rank.lc, "ledger", lambda: [
        dict(source="Code/known.cpp", target_rva="0x100", target_size="0x10"),
        dict(source="Code/new.cpp", target_rva="0x200", target_size="0x20"),
    ])
    return index


@pytest.mark.parametrize("mode", [[], ["--owner-gaps"], ["--stale-views"]])
def test_new_matched_unit_has_unknown_link_state(snapshot, capsys, mode):
    assert link_rank.main(["--file", "Code/new.cpp", *mode]) == 2
    output = capsys.readouterr().out
    assert "Code/new.cpp: not in census" in output
    assert "unknown" in output
    assert "32 matched bytes, links" not in output


def test_typo_is_not_reported_as_linked(snapshot, capsys):
    assert link_rank.main(["--file", "Code/typo.cpp"]) == 2
    assert "Code/typo.cpp: not in census" in capsys.readouterr().out


def test_known_unit_is_labelled_as_historical(snapshot, capsys):
    assert link_rank.main(["--file", "Code/known.cpp"]) == 0
    output = capsys.readouterr().out
    assert "16 matched bytes, linked in census" in output
    assert "Census blockers: 2026-10-24 02:54 at measured" in output
    assert "Provider index updated 2026-10-24 10:28 at refreshed" in output
    assert "current objects have not been checked" in output
    # The scoped-naming handoff is switched off until the rebuilt game reaches
    # the menu (AGENTS.md; name_scoped.RELATED_WORK_HANDOFF is False), so
    # link_rank prints none. Asserting it unconditionally when it was added left
    # this file red ever since; the test below covers it for when it is enabled.
    assert "--files Code/known.cpp" not in output
    assert "Name locals/parameters while inspecting this unit" not in output


def test_a_known_unit_offers_the_naming_handoff_once_it_is_enabled(snapshot, capsys, monkeypatch):
    import name_scoped
    monkeypatch.setattr(name_scoped, "RELATED_WORK_HANDOFF", True)
    assert link_rank.main(["--file", "Code/known.cpp"]) == 0
    output = capsys.readouterr().out
    assert "--files Code/known.cpp" in output
    assert "Name locals/parameters while inspecting this unit" in output


def test_legacy_index_uses_its_original_timestamp(snapshot, capsys):
    snapshot["meta"] = {"date": "2026-10-23 03:12", "commit": "original"}
    assert link_rank.main(["--file", "Code/known.cpp"]) == 0
    output = capsys.readouterr().out
    assert "Census blockers: 2026-10-23 03:12 at original" in output
    assert "Provider index updated" not in output


def test_ranking_exposes_unmeasured_current_units_without_fabricating_json(snapshot, capsys, tmp_path):
    destination = tmp_path / "rank.json"
    assert link_rank.main(["--top", "1", "--json", str(destination)]) == 0
    output = capsys.readouterr().out
    assert "1 current matched unit(s) absent from the census; link state unknown" in output
    assert json.loads(destination.read_text()) == {"Code/known.cpp": []}


def test_recorded_blockers_remain_visible(snapshot, capsys):
    snapshot["blockers"]["Code/known.cpp"].update(linked=False, unresolved=["missing"])
    assert link_rank.main(["--file", "Code/known.cpp"]) == 0
    output = capsys.readouterr().out
    assert "1 blocker(s)" in output
    assert "U missing" in output
