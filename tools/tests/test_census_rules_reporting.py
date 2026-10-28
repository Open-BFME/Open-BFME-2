"""A change of census rules is reported as a rule change, never as lost
progress: progress.py compares like for like through the re-baseline row,
the README card and Discord post show "accounting changed" instead of an arrow,
and the chart breaks its Linking line at the re-baseline."""
import re
import string
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
    assert "+10 bytes" in line and "+1.00 pp" in line and "accounting changed 2026-10-01" in line
    assert "-65" not in line  # 160 -> 95 raw would read as a 65-byte loss
    assert f"({link_census.RULES})" in line


def test_linked_line_uses_own_source_denominator(monkeypatch, capsys):
    monkeypatch.setattr(progress, "data_denominator", lambda: 0)
    split = {"authored": 300, "vendored": 10, "generated": 5, "library": 5, "dump": 100}
    progress.print_headline(0, 2000, split, split, STRICT, STRICT, [STRICT])
    line = next(l for l in capsys.readouterr().out.splitlines() if l.startswith("LINKED"))
    assert "105 bytes" in line
    assert "( 33.87%)" in line  # 105 linked / (300 authored + 10 vendored)


def current(census, authored):
    return {"total": 2000, "census": census, "linked": int(census["linked_bytes"]),
            "linked_authored": authored, "linked_game_code": 1000,
            "authored": 300, "vendored": 10, "generated": 5, "library": 5}


def test_card_and_post_mark_the_rule_change_instead_of_an_arrow():
    before = {**current(LEGACY_B, 160), "message_id": "1", "run_id": "old"}
    now = current(REBASE, 90)
    svg = daily.render(now, before)
    assert "accounting changed" in svg
    assert daily.DOWN not in svg  # no "lost 7 points" arrow on Linking
    assert "16.00% under majority-0" in svg
    post = daily.announcement(now, before)["embeds"][0]["description"]
    assert "**Linking: 9.00%**  (accounting changed)" in post
    assert daily.DOWN not in post


def test_card_keeps_arrows_within_one_rule():
    before = {**current(REBASE, 90), "message_id": "1", "run_id": "old"}
    svg = daily.render(current(STRICT, 95), before)
    assert "accounting changed" not in svg and daily.UP in svg


def test_chart_breaks_the_linking_line_at_the_rule_change():
    history = [{"date": "2026-10-01", "total": "100", "byte_matched": "10"},
               {"date": "2026-10-02", "total": "100", "byte_matched": "11"}]
    chart = progress_site._chart(history, HISTORY)
    assert chart.count("<polyline") == 3  # byte-matched + one Linking line per rules
    assert f"census accounting changed majority-0 -&gt; {link_census.RULES}" in chart or \
        f"census accounting changed majority-0 -> {link_census.RULES}" in chart
    assert "16.50% under majority-0" in chart


def change_labels(chart):
    """[(x, anchor, text)] of the chart's "... changed" labels."""
    return [(float(x), anchor or "start", text) for x, anchor, text in
            re.findall(r'<text x="([\d.]+)"(?: text-anchor="(\w+)")? y="\d+" class="axis">([^<]*changed)</text>', chart)]


def test_chart_keeps_a_change_label_on_the_latest_date_inside_the_plot():
    # The accounting changes on the chart's last day (x = 1100 - 8): its label
    # sits left of the break, never past the 1100-wide viewport. 1.2 em a
    # character bounds every glyph the label uses (the widest, W, is 0.94 em).
    history = [{"date": "2026-10-01", "total": "100", "byte_matched": "10"},
               {"date": "2026-10-02", "total": "100", "byte_matched": "11"}]
    labels = change_labels(progress_site._chart(history, HISTORY + [inclusive_row()]))
    assert [text for *_, text in labels] == ["accounting changed", "accounting changed"]
    x, anchor, text = labels[-1]
    assert x == 1092 - 4 and anchor == "end" and x - 1.2 * 12 * len(text) >= 40
    # Earlier in the chart the same label starts beside its break.
    history.append({"date": "2026-10-20", "total": "100", "byte_matched": "12"})
    x, anchor, text = change_labels(progress_site._chart(history, HISTORY + [inclusive_row()]))[-1]
    assert anchor == "start" and x + 1.2 * 12 * len(text) <= 1092


def test_inline_chart_declares_the_measured_stack():
    # Embedded in the page, the chart would inherit the body's font; it names
    # FONT_STACK (kerning off) itself, so text_width's bound holds where its
    # labels are placed, and the page body uses the same stack, no Noto.
    history = [{"date": "2026-10-01", "total": "100", "byte_matched": "10"},
               {"date": "2026-10-02", "total": "100", "byte_matched": "11"}]
    chart = progress_site._chart(history, HISTORY + [inclusive_row()])
    fields = {name: "" for _, name, _, _ in string.Formatter().parse(progress_site.PAGE) if name}
    page = progress_site.PAGE.format(**{**fields, "chart": chart, "font": progress_site.FONT})
    inline = re.search(r'<svg [^>]*class="chart"[^>]*>', page).group(0)
    assert f'font-family="{progress.FONT_STACK}" {progress.NO_KERN}' in inline
    assert f"font:14px/1.5 {progress.FONT_STACK}}}" in page and "Noto" not in page
    # The README copy keeps the declaration inside its frame too.
    assert f'font-family="{progress.FONT_STACK}" {progress.NO_KERN}' in progress_site.chart_svg(chart)




def inclusive_row():
    return dict(STRICT, date="2026-10-02 03:00", link_coverage_rules=progress.LINK_COVERAGE_RULES,
                linked_game_executable="990", game_executable="1000")


def test_chart_breaks_at_upstream_inclusive_accounting_transition():
    history = [{"date": "2026-10-01", "total": "100", "byte_matched": "10"},
               {"date": "2026-10-02", "total": "100", "byte_matched": "11"}]
    rows = HISTORY + [inclusive_row(), dict(inclusive_row(), date="2026-10-02 05:00")]
    chart = progress_site._chart(history, rows)
    assert chart.count("<polyline") == 4
    assert chart.count("accounting changed</text>") == 2
    assert "linking 99.00%" in chart
    assert progress.LINK_COVERAGE_RULES in chart
