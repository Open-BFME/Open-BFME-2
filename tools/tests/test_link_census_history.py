"""link_census_history.csv: rule provenance, UTC dates, validated atomic
writes, and refusal to mix rules or to rewrite a history this tool does not
understand."""
import csv
import io
import os
import sys
import time
from datetime import datetime, timezone
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_census as census

LEGACY_HEADER = census.HISTORY_FIELDS[:23]


def _row(date, commit="abc", rules=None, **extra):
    row = {field: "1" for field in census.HISTORY_FIELDS[2:23]}
    row.update({"date": date, "commit": commit, "scaffold_aliases": "", "scaffold_unresolved": "",
                "scaffold_crashed": ""})
    if rules is not None:
        row.update({"rules": rules, "prev_rules": census.RULES_NO_WRONG_SELECTED,
                    "files_linked_prev_rule": "1", "linked_bytes_prev_rule": "1", "linked_authored_prev_rule": "1"})
    row.update(extra)
    return row


def _write(path, header, rows):
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, header, lineterminator="\n", extrasaction="ignore")
        writer.writeheader()
        writer.writerows(rows)


@pytest.fixture
def history(tmp_path, monkeypatch):
    path = tmp_path / "link_census_history.csv"
    monkeypatch.setattr(census, "HISTORY", path)
    return path


def test_census_dates_are_utc(monkeypatch):
    monkeypatch.setenv("TZ", "America/New_York")
    time.tzset()
    try:
        for _ in range(3):  # a minute boundary between the two reads retries
            before = datetime.now(timezone.utc).strftime("%Y-%m-%d %H:%M")
            stamp = census.utc_now()
            if stamp == before:
                break
        assert stamp == before  # New York is never UTC, so a local stamp cannot pass
    finally:
        monkeypatch.delenv("TZ")
        time.tzset()


def test_legacy_history_reads_and_upgrades_without_touching_old_values(history):
    _write(history, LEGACY_HEADER, [_row("2026-10-01 19:08", "e36f0de979")])
    original = history.read_text().splitlines()[1]
    rows = census.read_history()
    assert census.row_rules(rows[0]) == census.LEGACY_RULES
    rows.append(_row("2026-10-01 23:00", "f00", rules=census.RULES, prev_rules=census.LEGACY_RULES))
    census.write_history(rows)
    lines = history.read_text().splitlines()
    assert lines[0].split(",") == census.HISTORY_FIELDS
    assert lines[1] == original + ",,,,,"  # the old row: same values, new columns empty
    assert lines[-1].endswith(f",{census.RULES},{census.LEGACY_RULES}")


@pytest.mark.parametrize("header", [LEGACY_HEADER + ["mystery"], ["commit", "date"] + LEGACY_HEADER[2:],
                                    LEGACY_HEADER[:10]])
def test_unknown_or_reordered_columns_refuse(history, header):
    _write(history, header, [_row("2026-10-01 19:08")])
    with pytest.raises(SystemExit, match="columns this tool does not know"):
        census.read_history()


def test_row_with_a_missing_or_extra_field_refuses(history):
    _write(history, LEGACY_HEADER, [_row("2026-10-01 19:08")])
    with history.open("a", encoding="utf-8") as handle:
        handle.write("2026-10-01 20:00,abc,1\n")  # a merge that kept an old-format line
    before = history.read_bytes()
    with pytest.raises(SystemExit, match="has 3 fields"):
        census.read_history()
    assert history.read_bytes() == before


def test_rules_newer_than_this_tool_refuse(history):
    # The forward guard: once the history declares rules this copy of the
    # tool does not know, a stale checkout cannot append under its own.
    _write(history, census.HISTORY_FIELDS, [_row("2026-10-01 19:08", rules="retail-truth-99")])
    with pytest.raises(SystemExit, match="update the tools"):
        census.read_history()


def test_write_is_validated_before_the_file_is_touched(history):
    _write(history, LEGACY_HEADER, [_row("2026-10-01 19:08")])
    before = history.read_bytes()
    rows = census.read_history() + [{**_row("2026-10-01 23:00", rules=census.RULES), "unexpected": "1"}]
    with pytest.raises(SystemExit, match="unknown fields"):
        census.write_history(rows)
    rows[-1].pop("unexpected")
    rows[-1]["linked_bytes"] = "12 345"
    with pytest.raises(SystemExit, match="linked_bytes"):
        census.write_history(rows)
    assert history.read_bytes() == before
    assert not list(history.parent.glob("*.tmp"))


def test_a_failed_replace_leaves_the_old_history_whole(history, monkeypatch):
    _write(history, LEGACY_HEADER, [_row("2026-10-01 19:08")])
    before = history.read_bytes()
    rows = census.read_history() + [_row("2026-10-01 23:00", rules=census.RULES)]

    def crash(*a):
        raise OSError("disk full")
    monkeypatch.setattr(census.os, "replace", crash)
    with pytest.raises(OSError):
        census.write_history(rows)
    assert history.read_bytes() == before


def test_old_writer_on_the_new_header_fails_closed():
    # What the pre-port tool does with the new header: csv.DictWriter with its
    # 23 fields raises on the first row (it cannot publish a row), and this
    # tool writes atomically so it never truncates.
    rows = [_row("2026-10-01 23:00", rules=census.RULES)]
    with pytest.raises(ValueError, match="fields not in fieldnames"):
        writer = csv.DictWriter(io.StringIO(), LEGACY_HEADER, lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)


def _census(when="2026-10-02 00:00"):
    return {"when": when, "rules": census.RULES}


def test_ordinary_census_refuses_until_the_rebaseline_exists():
    legacy = [_row("2026-10-01 19:08")]
    with pytest.raises(SystemExit, match="must be the re-baseline"):
        census.check_history_rules(legacy, _census())
    census.check_history_rules(legacy + [_row("2026-10-01 23:00", rules=census.RULES)], _census())


def test_rebaseline_happens_once_and_carries_the_previous_rules():
    legacy = [_row("2026-10-01 19:08")]
    census.check_history_rules(legacy, _census(), rebaseline={"rules": census.LEGACY_RULES})
    with pytest.raises(SystemExit, match="previous figures"):
        census.check_history_rules(legacy, _census(), rebaseline={"rules": census.RULES})
    done = legacy + [_row("2026-10-01 23:00", rules=census.RULES)]
    with pytest.raises(SystemExit, match="already records"):
        census.check_history_rules(done, _census(), rebaseline={"rules": census.LEGACY_RULES})


def test_status_rerun_cannot_restate_a_legacy_row():
    with pytest.raises(SystemExit, match="restate"):
        census.check_history_rules([_row("2026-10-01 19:08")], _census("2026-10-01 19:08"), rerun=True)


def test_a_census_dated_before_the_last_row_refuses():
    rows = [_row("2026-10-01 23:00", rules=census.RULES)]
    with pytest.raises(SystemExit, match="check the clock"):
        census.check_history_rules(rows, _census("2026-10-01 22:59"))


def test_census_measured_under_other_rules_refuses():
    with pytest.raises(SystemExit, match="measured under"):
        census.check_history_rules([], {"when": "2026-10-02 00:00", "rules": "majority-0"})


def test_repository_history_is_readable_and_append_ordered():
    rows = census.read_history()
    assert rows, "reverse/link_census_history.csv is empty"
    rules = [census.row_rules(r) for r in rows]
    # Once a rule appears, no row of an earlier rule follows it.
    order = [r for i, r in enumerate(rules) if i == 0 or rules[i - 1] != r]
    assert len(order) == len(set(order)), order
    # The first row of each later rule is its re-baseline: it carries the
    # rules before it as prev_rules.
    for before, row in zip(rows, rows[1:]):
        if census.row_rules(row) != census.row_rules(before):
            assert row["prev_rules"] == census.row_rules(before), "the first row of new rules must be the re-baseline"
    strict = [r for r in rows if census.row_rules(r) != census.LEGACY_RULES]
    dates = [r["date"] for r in strict]
    assert dates == sorted(dates)


def test_unknown_prev_rules_are_refused_before_the_file_is_touched(history):
    _write(history, LEGACY_HEADER, [_row("2026-10-01 19:08")])
    before = history.read_bytes()
    rows = census.read_history() + [_row("2026-10-01 23:00", rules=census.RULES, prev_rules="future-unknown")]
    with pytest.raises(SystemExit, match="unknown prev_rules"):
        census.write_history(rows)
    assert history.read_bytes() == before
    assert not list(history.parent.glob("*.tmp"))


@pytest.mark.parametrize("shape", ["absent", "header-only", "empty"])
def test_missing_or_truncated_history_refuses_every_append(history, shape):
    # An old writer truncates the history to its header before it crashes;
    # neither an ordinary census nor a re-baseline may build on that.
    if shape == "header-only":
        history.write_text(",".join(LEGACY_HEADER) + "\n")
    elif shape == "empty":
        history.write_text("")
    rows = census.read_history()
    assert rows == []
    with pytest.raises(SystemExit, match="missing or has no rows"):
        census.check_history_rules(rows, _census())
    with pytest.raises(SystemExit, match="missing or has no rows"):
        census.check_history_rules(rows, _census(), rebaseline={"rules": census.LEGACY_RULES})
