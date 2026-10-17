"""A change of census rules is reported as a rule change, never as lost
progress: progress.py compares like for like through the re-baseline row,
the README card and Discord post show "rules changed" instead of an arrow,
and the chart breaks its Linking line at the re-baseline."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_census
import progress
import progress_site
import readme_progress as daily


def census_row(date, authored, game=1000, rules=None, prev=None, prev_rules=None, linked=None):
    row = {"date": date, "commit": date[-5:].replace(":", ""), "linked_bytes": str(linked or authored + 10),
           "linked_authored": str(authored), "game_code": str(game), "rules": rules or ""}
    if prev is not None:
        row.update({"linked_authored_prev_rule": str(prev), "linked_bytes_prev_rule": str(prev + 10),
                    "prev_rules": prev_rules})
    return row


LEGACY_A = census_row("2026-10-01 18:00", 150)
LEGACY_B = census_row("2026-10-01 19:00", 160)
REBASE = census_row("2026-10-01 23:00", 90, rules=link_census.RULES, prev=165, prev_rules=link_census.LEGACY_RULES)
STRICT = census_row("2026-10-02 01:00", 95, rules=link_census.RULES, prev=99,
                    prev_rules=link_census.RULES_NO_WRONG_SELECTED)
HISTORY = [LEGACY_A, LEGACY_B, REBASE, STRICT]


def test_progress_knows_the_census_rule_ids():
    assert progress.LEGACY_CENSUS_RULES == link_census.LEGACY_RULES
    assert progress.census_rules(LEGACY_A) == link_census.LEGACY_RULES
    assert progress.census_rules(STRICT) == link_census.RULES


def test_same_rules_change_is_plain():
    change = progress.census_change(LEGACY_A, LEGACY_B, "linked_authored", "game_code", HISTORY)
    assert change["bytes"] == 10 and abs(change["pp"] - 1.0) < 1e-9 and not change["rule_changes"]


def test_change_across_the_rebaseline_is_counted_within_rules():
    # 160 -> 165 under the old rules (same objects as the re-baseline), then
    # 90 -> 95 under the new: +10 bytes, +1.0 pp of real progress, not -6.5 pp.
    change = progress.census_change(LEGACY_B, STRICT, "linked_authored", "game_code", HISTORY)
    assert change["bytes"] == 10
    assert abs(change["pp"] - 1.0) < 1e-9
    (row, before, after, at_before, at_after), = change["rule_changes"]
    assert row is REBASE and before == link_census.LEGACY_RULES and after == link_census.RULES
    assert (round(at_before, 2), round(at_after, 2)) == (16.5, 9.0)


def test_rule_change_without_previous_figures_has_no_delta():
    bare = dict(REBASE)
    for key in ("linked_authored_prev_rule", "linked_bytes_prev_rule", "prev_rules"):
        bare.pop(key)
    assert progress.census_change(LEGACY_B, bare, "linked_authored", "game_code", [LEGACY_B, bare]) is None


def test_headline_prints_a_rule_change_not_a_loss(monkeypatch, capsys):
    monkeypatch.setattr(progress, "data_denominator", lambda: 0)
    split = {"authored": 300, "vendored": 10, "generated": 5, "library": 5, "dump": 100}
    progress.print_headline(0, 2000, split, split, LEGACY_B, STRICT, HISTORY)
    out = capsys.readouterr().out
    line = next(l for l in out.splitlines() if l.startswith("LINKING"))
    assert "+10 bytes" in line and "+1.00 pp" in line and "RULES CHANGED 2026-10-01" in line
    assert "-65" not in line  # 160 -> 95 raw would read as a 65-byte loss
    assert f"({link_census.RULES})" in line


def current(census, authored):
    return {"total": 2000, "census": census, "linked": int(census["linked_bytes"]),
            "linked_authored": authored, "linked_game_code": 1000,
            "authored": 300, "vendored": 10, "generated": 5, "library": 5}


def test_card_and_post_mark_the_rule_change_instead_of_an_arrow():
    before = {**current(LEGACY_B, 160), "message_id": "1", "run_id": "old"}
    now = current(REBASE, 90)
    svg = daily.render(now, before)
    assert "rules changed" in svg
    assert daily.DOWN not in svg  # no "lost 7 points" arrow on Linking
    assert "16.00% under majority-0" in svg
    post = daily.announcement(now, before)["embeds"][0]["description"]
    assert "**Linking: 9.00%**  (rules changed)" in post
    assert daily.DOWN not in post


def test_card_keeps_arrows_within_one_rule():
    before = {**current(REBASE, 90), "message_id": "1", "run_id": "old"}
    svg = daily.render(current(STRICT, 95), before)
    assert "rules changed" not in svg and daily.UP in svg


def test_chart_breaks_the_linking_line_at_the_rule_change():
    history = [{"date": "2026-10-01", "total": "100", "byte_matched": "10"},
               {"date": "2026-10-02", "total": "100", "byte_matched": "11"}]
    chart = progress_site._chart(history, HISTORY)
    assert chart.count("<polyline") == 3  # byte-matched + one Linking line per rules
    assert f"census rules changed majority-0 -&gt; {link_census.RULES}" in chart or \
        f"census rules changed majority-0 -> {link_census.RULES}" in chart
    assert "16.50% under majority-0" in chart
