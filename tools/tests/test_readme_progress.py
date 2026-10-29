"""README card and Discord post; no network requests."""
import csv
import html
import io
import re
import json
import subprocess
import sys
import xml.etree.ElementTree as ET
from pathlib import Path
from urllib.error import URLError

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import readme_progress as daily
import progress

UP = "▲"
P2 = (progress.PHASE2_HATCH_ITEMS, progress.PHASE2_SOURCE_FILES, progress.PHASE2_CLASS_COPIES)


def sample(authored=40, linked_authored=9, linked_game_code=90):
    # rebuilt 60 of 100; game's own code = 100 - 5 vendored - 5 library = 90;
    # hand-written 40 of it; the census's authored-only Linking figure is 9/90.
    return {"total": 100, "linked": 12, "linked_authored": linked_authored, "linked_game_code": linked_game_code,
            "authored": authored, "vendored": 5, "generated": 10, "library": 5, "census": None,
            "cpp_rules": daily.progress.GAME_CPP_RULES}


def cleanup(items=P2[0] - 3_000, files=P2[1] - 2_000, target=2_000, copies=P2[2] - 1_000, **changes):
    """The Phase 2 counts: 3,000 hatch items, 2,000 files and 1,000 class copies gone."""
    return {"hatch_items": items, "asm_bytes": 67_972, "source_files": files, "tu_target": target,
            "class_copies": copies, **changes}


def census(date="2026-10-28 10:03", rules="retail-truth-4", unresolved=3_090, addresses=1_043, duplicates=1):
    return {"date": date, "commit": "c8734bec0c", "rules": rules, "unresolved": str(unresolved),
            "addresses": str(addresses), "duplicates": str(duplicates), "linked_bytes": "12"}


def problems(**changes):
    """Every link problem one census recorded: 4,777 of them."""
    counts = {"unresolved": 3_090, "addresses": 1_043, "duplicates": 1, "comdat_losers": 285, "wrong_selected": 358,
              **changes}
    return {**counts, "total": sum(counts.values())}


def full(**changes):
    """A state with every figure on the card."""
    return {**sample(), **cleanup(), "declared_names": 200, "readable_names": 142, "census": census(),
            "census_tool_rules": "retail-truth-4", "link_problems": problems(), **changes}


def previous(**changes):
    """A saved post state: the figures the last post was drawn from."""
    return {**sample(), **changes, "message_id": "1", "run_id": "old"}


def setup_state(tmp_path, monkeypatch, state=None):
    (tmp_path / "docs").mkdir()
    monkeypatch.setattr(daily.progress, "ROOT", tmp_path)
    path = tmp_path / daily.STATE
    if state:
        path.write_text(json.dumps(state), encoding="utf-8")
    return path


def fake_collection(monkeypatch, split=None):
    """main() without the repository: every source of a figure replaced."""
    for name, value in (("matched_at", lambda *a: []), ("notes_at", lambda *a: {}), ("retail_text", lambda: (0, 100)),
                        ("naked_cpp_rows_at", lambda *a: []), ("real_split", lambda *a, **k: split or sample()),
                        ("census_at", lambda *a: None), ("real_code_denominator", lambda *a: (0, 100)),
                        ("census_tool_rules_at", lambda *a: "retail-truth-4"), ("link_problems_at", lambda *a: None),
                        ("cleanup_figures_at", lambda *a: cleanup())):
        monkeypatch.setattr(daily.progress, name, value)
    monkeypatch.setattr(daily.name_metric, "readable", lambda: (200, 58))


def text_of(svg):
    return " ".join(" ".join(ET.fromstring(svg).itertext()).split())


def test_retry_does_not_duplicate_post(tmp_path, monkeypatch):
    monkeypatch.setenv("GITHUB_RUN_ID", "run-123")
    setup_state(tmp_path, monkeypatch, {"total": 100, "message_id": "123", "run_id": "run-123"})
    monkeypatch.setattr(daily, "urlopen", lambda *a, **k: pytest.fail("Unexpected post"))
    daily.notify(sample())


def test_success_posts_the_card_and_saves_the_figures(tmp_path, monkeypatch):
    path = setup_state(tmp_path, monkeypatch)
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token\n")

    def send(request, timeout):
        assert request.full_url.endswith("token?wait=true")
        payload = json.loads(request.data)
        assert payload["allowed_mentions"] == {"parse": []}
        assert payload["embeds"][0]["title"] == "BFME 2 · Road to a finished decomp"
        assert "**Byte match: 60.00%**" in payload["embeds"][0]["description"]
        return io.BytesIO(b'{"id":"123"}')
    monkeypatch.setattr(daily, "urlopen", send)
    daily.notify(full())
    state = json.loads(path.read_text())
    assert state["message_id"] == "123"
    assert daily.measures(state) == daily.measures(full())  # the next post's arrows start from these


def test_each_daily_run_posts_new_message_even_if_unchanged(tmp_path, monkeypatch):
    monkeypatch.setenv("GITHUB_RUN_ID", "new-run")
    path = setup_state(tmp_path, monkeypatch, previous())
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token")
    monkeypatch.setattr(daily, "urlopen", lambda request, timeout: io.BytesIO(b'{"id":"456"}'))
    daily.notify(sample())
    assert json.loads(path.read_text())["message_id"] == "456"


def test_hourly_runs_post_only_when_a_does_it_work_figure_moves(tmp_path, monkeypatch):
    monkeypatch.setenv("GITHUB_RUN_ID", "hourly")
    path = setup_state(tmp_path, monkeypatch, {**full(), "message_id": "1", "run_id": "daily"})
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token")
    monkeypatch.setattr(daily, "urlopen", lambda *a, **k: pytest.fail("Unexpected post"))
    # the source-cleanup figures move every hour; they wait for the daily post
    daily.notify(full(**cleanup(items=P2[0] - 3_100), declared_names=210), on_change=True)
    assert json.loads(path.read_text())["message_id"] == "1"
    posted = []
    monkeypatch.setattr(daily, "urlopen", lambda request, timeout: posted.append(request) or io.BytesIO(b'{"id":"2"}'))
    for moved in (full(link_problems=problems(comdat_losers=200)),      # a new census: fewer problems
                  full(census_tool_rules="retail-truth-5"),             # a rule change awaiting its census
                  full(linked_authored=10)):                            # linking moved
        monkeypatch.setenv("GITHUB_RUN_ID", f"hourly-{len(posted)}")
        path.write_text(json.dumps({**full(), "message_id": "1", "run_id": "daily"}), encoding="utf-8")
        daily.notify(moved, on_change=True)
    assert len(posted) == 3 and json.loads(path.read_text())["message_id"] == "2"


def test_failed_post_does_not_advance_state_or_leak_url(tmp_path, monkeypatch):
    path = setup_state(tmp_path, monkeypatch)
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/secret")

    def fail(*args, **kwargs):
        raise URLError("secret")
    monkeypatch.setattr(daily, "urlopen", fail)
    with pytest.raises(SystemExit, match="^Discord update failed: connection error$"):
        daily.notify(sample())
    assert not path.exists()


def test_discord_post_mirrors_the_card():
    embed = daily.announcement(full(), previous(authored=36, generated=10, declared_names=200, readable_names=140,
                                                **cleanup(items=P2[0] - 2_900)))["embeds"][0]
    M, L, A, N, S, F, D = (daily.BLOCK[key] for key in
                           ("matched", "linked", "authored", "names", "shortcuts", "layout", "classes"))
    R = daily.REST_BLOCK
    shortcuts, was = 100 * 3000 / P2[0], 100 * 2900 / P2[0]
    assert embed["title"] == "BFME 2 · Road to a finished decomp"
    assert embed["description"].split("\n") == [
        "*Finished means: the whole game is built from readable source, builds the normal way, and plays*",
        "",
        "**Does it work?**",
        f"**Byte match: 60.00%**  {UP} 4.00",
        f"{M * 6}{R * 4}",
        "Every byte of the game's program code is recreated by compiling our source "
        "(game data & assets: not measured yet)",
        "",
        "**Linking: 10.00%**",
        f"{L * 1}{R * 9}",
        "Share of game code that links into one program; 4,777 problems recorded (measured 2026-10-28)",
        "",
        "> Next milestone: first normal build, then the first playtest",
        "",
        "**Is the source clean?**",
        f"{A * 4}{R * 6} **44.44%** Hand-written code  {UP} 4.44",
        f"{N * 7}{R * 3} **71.00%** Readable names  {UP} 1.00",
        f"{S * 0}{R * 10} **{shortcuts:.2f}%** Shortcuts removed  {UP} {round(shortcuts, 2) - round(was, 2):.2f}",
        f"{F * 0}{R * 10} **{100 * 2000 / (P2[1] - 2000):.2f}%** Original file layout  {daily.DOT} 0.00",
        f"{D * 0}{R * 10} **{100 * 1000 / P2[2]:.2f}%** Shared class definitions  {daily.DOT} 0.00",
        "",
        "Shortcuts, file layout and shared classes count from the start of Phase 2 (Oct 25). "
        f"[How each figure is measured: README]({daily.README})"]


def test_card_shows_both_sections():
    svg = daily.render(full(), previous(authored=36, generated=10))
    text = text_of(svg)
    for piece in ("BFME 2 · Road to a finished decomp", daily.SUBTITLE, "DOES IT WORK?", "Byte match", "60.00%",
                  "Linking", "10.00%", "Share of game code that links into one program; 4,777 problems recorded",
                  "game data & assets: not measured yet", "measured 2026-10-28",
                  "Next milestone: first normal build, then the first playtest", "IS THE SOURCE CLEAN?",
                  "Hand-written code", "44.44%", "Readable names", "71.00%", "Shortcuts removed",
                  "Original file layout", "Shared class definitions", daily.FOOTER, f"{UP} 4.44"):
        assert piece in text, piece
    assert "game data &amp; assets" in svg   # escaped XML
    assert "Game code in C++" not in text and "55.56%" not in text   # the approved layout: not on the card
    assert "prefers-color-scheme: light" in svg and "Plays" not in text and "Rebuilt from source" not in text
    for colour in ("#2ea043", "#d29922", "#a371f7", "#58a6ff", "#f0883e", "#e05c7a"):
        assert f'fill="{colour}"' in svg
    assert "#388bfd" not in svg


def test_the_card_keeps_the_owner_approved_layout():
    """Does it work? is byte match and linking (with the milestone); Is the source
    clean? opens with hand-written code. GAME CODE C++* also counts generated C++
    and retained assembly: it describes how the code is stored, not whether the
    game works, so progress.py prints it and the card does not (24454a208b had
    put it back on the card)."""
    assert [label for _, label, _ in daily.WORKS] == ["Byte match", "Linking"]
    assert [label for _, label in daily.CLEAN] == ["Hand-written code", "Readable names", "Shortcuts removed",
                                                   "Original file layout", "Shared class definitions"]
    post = daily.announcement(full(), None)["embeds"][0]["description"]
    works, clean = post.split("**Is the source clean?**")
    assert "Game code in C++" not in post and "Byte match" in works and "Linking" in works
    assert clean.strip().split("\n")[0].endswith("Hand-written code")


STATUS_HEADER = "source,linked,unresolved,duplicates,comdat_losers,addresses,wrong_selected\n"


def test_link_problems_count_every_recorded_category():
    # Three files: one links; one is blocked by an unresolved name; one only by a losing
    # COMDAT copy and a wrongly selected provider, which the old three-field count missed.
    status = (STATUS_HEADER + "Code/a.cpp,yes,0,0,0,0,0\nCode/b.cpp,no,2,0,0,0,0\nCode/c.cpp,no,0,0,3,0,4\n")
    row = {**census(), "files": "3", "files_linked": "1"}
    assert progress.link_problems(row, status) == {"unresolved": 3_090, "addresses": 1_043, "duplicates": 1,
                                                   "comdat_losers": 3, "wrong_selected": 4, "total": 4_141}
    assert progress.link_problems(None, status) is None
    assert progress.link_problems(row, None) is None
    assert progress.link_problems({**row, "addresses": ""}, status) is None           # a row before the column
    # a status file another census wrote (other file or linked-file counts) is not counted
    assert progress.link_problems({**row, "files": "4"}, status) is None
    assert progress.link_problems({**row, "files_linked": "2"}, status) is None
    assert progress.link_problems(row, status.replace(",wrong_selected", "")) is None
    assert daily.caption({"link_problems": None}, "linked", "Share") == "Share"


def test_linking_never_claims_a_normal_build():
    svg, post = daily.render(full()), daily.announcement(full(), None)["embeds"][0]["description"]
    for text in (text_of(svg), post):
        assert "Builds normally" not in text and "builds without shortcuts" not in text
        assert "4,777 problems recorded" in text


def test_milestone_waits_for_a_recorded_exit_test():
    # No census or link_cycle record shows a whole-program link without /FORCE and
    # stubs, so the milestone stays put however few problems are counted.
    done = full(census=census(unresolved=0, addresses=0, duplicates=0),
                link_problems=problems(unresolved=0, addresses=0, duplicates=0, comdat_losers=0, wrong_selected=0))
    for state in (full(), full(census=None, link_problems=None), done):
        assert daily.milestone(state) == "Next milestone: first normal build, then the first playtest"
    assert "Next milestone: first normal build, then the first playtest" in text_of(daily.render(done))
    assert "0 problems recorded" in text_of(daily.render(done))


def test_a_pending_census_rule_change_shows_being_re_measured(tmp_path, monkeypatch):
    tool = tmp_path / progress.CENSUS_TOOL
    tool.parent.mkdir()
    tool.write_text('RULES_X = "no"\nRULES = "retail-truth-5"\nRULES_NO_WRONG_SELECTED = "x"\n', encoding="utf-8")
    monkeypatch.setattr(progress, "ROOT", tmp_path)
    assert progress.census_tool_rules_at(None) == "retail-truth-5"
    pending = full(census_tool_rules="retail-truth-5", linked_authored=12)
    old = {**full(), "message_id": "1"}
    assert daily.remeasuring(pending) == ("retail-truth-5", "retail-truth-4")
    assert daily.delta_since(old, "linked", *daily.measures(pending)["linked"], pending) is None
    svg, post = daily.render(pending, old), daily.announcement(pending, old)["embeds"][0]["description"]
    assert ">being re-measured<" in svg and UP not in svg.split(">Hand-written code<")[0]
    assert "**Linking: 13.33%**  (being re-measured)" in post
    assert "(retail-truth-4 to retail-truth-5): this is the last figure under the old rules" in post
    # once the census measures under the new rules the row compares again (accounting changed vs the last post)
    measured = full(census=census(rules="retail-truth-5"), census_tool_rules="retail-truth-5")
    assert daily.remeasuring(measured) is None
    assert "**Linking: 10.00%**  (accounting changed)" in daily.announcement(measured, old)["embeds"][0][
        "description"]
    assert daily.remeasuring(full(census_tool_rules=None)) is None  # unreadable tool: the normal delta


def test_phase2_figures_count_from_the_start_of_phase_2():
    rows = daily.measures(full())
    assert rows["shortcuts"] == (3_000, P2[0])
    assert rows["layout"] == (2_000, P2[1] - 2_000)
    assert rows["classes"] == (1_000, P2[2])
    assert progress.phase2_share(100, 100) == 0 and progress.phase2_share(100, 40, 40) == 100
    grown = full(**cleanup(items=P2[0] + 10))
    assert daily.measures(grown)["shortcuts"][0] < 0  # a register that grew shows below zero ...
    assert daily.share(*daily.measures(grown)["shortcuts"]).startswith("-")
    assert 'width="0.00" height="10" rx="5" fill="#e05c7a"' in daily.render(grown)  # ... with an empty bar
    assert daily.measures(sample())["shortcuts"] == (None, None)
    assert "Shortcuts removed: soon" in daily.announcement(sample(), None)["embeds"][0]["description"]
    for bad in ({"hatch_items": -1}, {"source_files": "9"}, {"tu_target": P2[1]}, {"class_copies": 1.5}):
        with pytest.raises(ValueError):
            daily.measures(full(**bad))


def test_a_new_tu_estimate_is_not_progress():
    old = {**full(), "message_id": "1"}
    now = full(tu_target=1_900)
    assert daily.delta_since(old, "layout", *daily.measures(now)["layout"], now) is None
    post = daily.announcement(now, old)["embeds"][0]["description"]
    assert "Original file layout  (accounting changed)" in post
    assert "-# The TU map's estimate moved from 2,000 to 1,900 files, not a change in progress" in post
    assert "estimate moved from 2,000 to 1,900" in text_of(daily.render(now, old))


def test_count_figures_compare_displayed_percentages():
    old = {**full(), "message_id": "1"}
    now = full(**cleanup(items=P2[0] - 3_001))     # one more item: below a displayed hundredth
    assert daily.delta_since(old, "shortcuts", *daily.measures(now)["shortcuts"], now) == 0
    assert f"Shortcuts removed  {daily.DOT} 0.00" in daily.announcement(now, old)["embeds"][0]["description"]


def test_hatch_items_leave_asm_bytes_apart(monkeypatch):
    register = ("# Escape-hatch register\n# mode: enforce\n"
                "pin\tCode/a.cpp\t?f@@\t3\naddress_global\tCode/a.cpp\tg_Va1\t2\n"
                "asm_bytes\tCode/b.asm\t*\t5000\npresent_unmatched\tCode/c.cpp\t?g@@\t1\tallow=abc\n")
    monkeypatch.setattr(progress, "_text_at", lambda ref, path: register if path == progress.HATCHES else None)
    assert progress.hatch_items_at(None) == (6, 5000)
    monkeypatch.setattr(progress, "_text_at", lambda ref, path: "pin\tCode/a.cpp\t?f@@\n")
    with pytest.raises(ValueError, match="no count"):
        progress.hatch_items_at(None)
    monkeypatch.setattr(progress, "_text_at", lambda ref, path: None)
    assert progress.hatch_items_at(None) is None


def test_tu_target_counts_the_committed_maps_code_units(monkeypatch):
    table = ("rva,size,kind,tu,confidence,by,evidence,source\n"
             "0x1,1,code,Code/A.cpp,approved,-,,Code/x.cpp\n0x2,1,code,code/a.CPP,proposed,-,,Code/y.cpp\n"
             "0x3,1,code,Code/B.cpp,proposed,-,,Code/y.cpp\n0x4,1,code,,displaced,-,,Code/z.cpp\n"
             "0x5,1,data:.rdata,Code/C.cpp,approved,-,,Code/z.cpp\n")
    monkeypatch.setattr(progress, "_text_at", lambda ref, path: table if path == progress.TU_MAP else None)
    assert progress.tu_target_at(None) == 2


def test_class_copies_count_copies_beyond_one_definition(tmp_path, monkeypatch):
    files = {"Code/a.cpp": "class Foo { int a; };\nstruct Bar { int b; };\nclass Fwd;\n",
             "Code/b.cpp": "class Foo { int a; int c; };\nclass Solo { };\nvoid f() { struct Local { }; }\n",
             "Code/c.c": "struct Bar { int b; };\n",
             "Code/gen_small/g.cpp": "class Foo { };\n",
             "Code/d.cpp": "template <class T> class Tmpl { };\nclass Hdr { };\n"}
    for path, text in files.items():
        (tmp_path / path).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / path).write_text(text, encoding="utf-8")
    (tmp_path / "reverse").mkdir()
    (tmp_path / progress.CANONICAL_CLASSES).write_text("class,header,notes\nHdr,Code/Hdr.h,\n", encoding="utf-8")
    monkeypatch.setattr(progress, "ROOT", tmp_path)
    monkeypatch.setattr(progress, "matched_at", lambda ref: {(path, "0x1"): (4, path) for path in files})
    # Foo twice (+1), Bar twice (+1), Solo once (0), Hdr once but registered (+1); generated
    # sources, forward declarations, local and template classes are not private copies.
    assert progress.class_copies_at(None) == {"extra": 3, "copies": 6, "classes": 4}


def test_recorded_phase2_counts_match_the_commit():
    have = subprocess.run(["git", "cat-file", "-e", f"{progress.PHASE2_START}^{{commit}}"],
                          cwd=progress.ROOT, capture_output=True).returncode == 0
    if not have:
        pytest.skip(f"{progress.PHASE2_START} not in this clone (CI checks out one commit)")
    assert progress.hatch_items_at(progress.PHASE2_START)[0] == progress.PHASE2_HATCH_ITEMS
    assert len(progress.source_files_at(progress.PHASE2_START)) == progress.PHASE2_SOURCE_FILES
    # The class-copy count parses every unit at that commit (about a minute):
    # `python3 tools/readme_progress.py --check-baselines` compares all three.


def test_image_ownership_replaces_not_measured_once_recorded(tmp_path):
    assert daily.ownership(tmp_path) is None
    path = tmp_path / daily.OWNERSHIP
    path.parent.mkdir()
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, ["date", "ours", "content_bytes", "north_star"])
        writer.writeheader()
        writer.writerow({"date": "2026-11-02 04:00", "ours": 750, "content_bytes": 1000, "north_star": 250})
    owned = daily.ownership(tmp_path)
    assert owned == {"date": "2026-11-02", "ours": 750, "content": 1000}
    assert daily.side_note(full(ownership=owned), "matched") == "whole game file: 75.00% ours (2026-11-02)"
    assert daily.side_note(full(), "matched") == daily.NOT_MEASURED_DATA


def test_hand_written_code_is_authored_cpp_only():
    current = dict(sample(), total=7_978_500, authored=7_240_277,
                   generated=267_704, assembly=7_986, vendored=457_607,
                   library=822, data=4_104)
    assert daily.measures(current)['authored'] == (7_240_277, 7_515_967)
    assert daily.measures(current)['cpp'] == (7_515_967, 7_515_967)
    text = daily.announcement(current, None)['embeds'][0]['description']
    assert '**96.33%** Hand-written code' in text and 'Game code in C++' not in text
    # Replacing a generated body with recovered C++ is new hand-written code; the
    # inclusive figure measures() still checks against stays full.
    reconciled = dict(current, authored=current['authored'] + 1_000, generated=current['generated'] - 1_000)
    assert daily.measures(reconciled)['cpp'] == (7_515_967, 7_515_967)
    assert daily.delta_since(current, 'authored', *daily.measures(reconciled)['authored'], reconciled) > 0
    assert daily.measures(current)['linked'] == (9, 90)


def test_linking_is_one_census_snapshot():
    # The census tree's game code (80) is the denominator, not today's (90).
    current = sample(linked_authored=8, linked_game_code=80)
    assert daily.measures(current)["linked"] == (8, 80)
    assert "**Linking: 10.00%**" in daily.announcement(current, None)["embeds"][0]["description"]
    with pytest.raises(ValueError):
        daily.measures(sample(linked_game_code=None))  # bytes without their denominator
    with pytest.raises(ValueError):
        daily.measures(sample(linked_authored=91))  # more linked than there is code


def test_linking_without_a_census_figure_says_so():
    current = sample(linked_authored=None, linked_game_code=None)
    assert "**Linking:** not measured yet" in daily.announcement(current, None)["embeds"][0]["description"]
    assert ">not measured<" in daily.render(current)


def test_arrow_is_the_change_in_the_figures_percentage():
    # Linking went from 9/90 = 10.00% to 8/80 = 10.00%: same share, no arrow,
    # though the bytes and the denominator both moved.
    text = daily.announcement(sample(linked_authored=8, linked_game_code=80), previous())["embeds"][0]["description"]
    assert UP not in text and "▼" not in text
    # 9/90 -> 12/90: +3.33 points.
    assert f"**Linking: 13.33%**  {UP} 3.33" in daily.announcement(sample(linked_authored=12), previous())[
        "embeds"][0]["description"]
    # A move that rounds to 0.00 shows nothing.
    assert UP not in daily.announcement(sample(), previous(authored=39.999))["embeds"][0]["description"]


def test_old_state_without_figures_gives_no_arrow():
    old = {"total": 100, "matched_total": 55, "message_id": "1", "run_id": "old"}  # before these figures existed
    assert UP not in daily.announcement(sample(), old)["embeds"][0]["description"]
    # A state from before the census stored Linking: the other figures still compare.
    text = daily.announcement(sample(), previous(authored=36, generated=10, linked_authored=None,
                                                 linked_game_code=None))["embeds"][0]["description"]
    assert f"**44.44%** Hand-written code  {UP} 4.44" in text and "**Linking: 10.00%**\n" in text
    # A state saved by the old four-bar card has no Phase 2 counts: no arrow on them.
    text = daily.announcement(full(), previous())["embeds"][0]["description"]
    assert re.search(r"Shortcuts removed$", text, re.M) and re.search(r"Shared class definitions$", text, re.M)


def test_nothing_claims_the_game_is_100_percent_done():
    text = daily.announcement(full(), previous())["embeds"][0]["description"] + text_of(daily.render(full(), previous()))
    assert "100%" not in text and "100.00%" not in text


@pytest.mark.parametrize("value", [-5, 0, 1, 4, 5, 49, 50, 95, 96, 100, 120])
def test_blocks_always_fill_exactly_ten(value):
    text = daily.blocks(value, 100, daily.BLOCK["matched"])
    assert text.count(daily.BLOCK["matched"]) + text.count(daily.REST_BLOCK) == 10


@pytest.mark.parametrize("value, total, full_squares", [
    (7_154_889, 7_512_658, 9),      # 95.24% linking: never drawn as complete
    (99_999, 100_000, 9), (100_000, 100_000, 10), (19, 100, 1), (9, 100, 0), (0, 100, 0),
])
def test_blocks_are_floor_bands_so_ten_squares_mean_exactly_100_percent(value, total, full_squares):
    assert daily.blocks(value, total, daily.BLOCK["linked"]).count(daily.BLOCK["linked"]) == full_squares
    assert daily.blocks(value + 0.5, total, daily.BLOCK["linked"]).count(daily.REST_BLOCK) <= 10   # bytes may be fractional


@pytest.mark.parametrize("before, after, change", [
    (71.014, 71.016, "▲ 0.01"),
    (71.016, 71.014, "▼ 0.01"),
    (71.011, 71.014, "· 0.00"),
    (71.01, 71.01, "· 0.00"),
])
def test_names_always_compare_the_displayed_percentages(before, after, change):
    current = {**sample(), "declared_names": 100_000, "readable_names": round(after * 1000)}
    old = previous(declared_names=100_000, readable_names=round(before * 1000))
    text = daily.announcement(current, old)["embeds"][0]["description"]
    assert f"**{after:.2f}%** Readable names  {change}" in text
    assert f">{change}<" in daily.render(current, old)
    if change.startswith("·"):
        assert f'class="muted" dx="10" font-size="12" font-weight="600">{change}<' in daily.render(current, old)


def test_names_compare_shares_not_counts():
    current = {**sample(), "declared_names": 400, "readable_names": 280}
    old = previous(declared_names=200, readable_names=142)
    assert "**70.00%** Readable names  ▼ 1.00" in daily.announcement(current, old)["embeds"][0]["description"]


def test_first_names_measurement_has_no_invented_delta():
    current = {**sample(), "declared_names": 200, "readable_names": 142}
    for old in (None, previous()):
        assert "**71.00%** Readable names\n" in daily.announcement(current, old)["embeds"][0]["description"]


@pytest.mark.parametrize("counts", [
    {"declared_names": 10}, {"readable_names": 5},
    {"declared_names": 10, "readable_names": 11},
    {"declared_names": 10, "readable_names": -1},
])
def test_invalid_names_counts_fail(counts):
    with pytest.raises(ValueError, match="Invalid readable-names count"):
        daily.measures({**sample(), **counts})


def test_main_measures_every_figure_and_persists_them(tmp_path, monkeypatch):
    path = setup_state(tmp_path, monkeypatch)
    monkeypatch.setattr(sys, "argv", ["readme_progress.py", "--discord"])
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token")
    monkeypatch.setattr(daily, "urlopen", lambda *a, **k: io.BytesIO(b'{"id":"123"}'))
    fake_collection(monkeypatch, dict(sample(), data=7))
    daily.main()
    state = json.loads(path.read_text())
    assert state['data'] == 7 and daily.measures(state)['matched'] == (67, 100)
    assert state["declared_names"] == 200 and state["readable_names"] == 142
    assert state["hatch_items"] == cleanup()["hatch_items"] and state["census_tool_rules"] == "retail-truth-4"
    svg = (tmp_path / "docs/progress.svg").read_text(encoding="utf-8")
    assert ">71.00%<" in svg and ">Shortcuts removed<" in svg


def test_on_change_main_renders_but_does_not_post_an_unchanged_headline(tmp_path, monkeypatch):
    fake_collection(monkeypatch)
    state = setup_state(tmp_path, monkeypatch)
    monkeypatch.setattr(sys, "argv", ["readme_progress.py"])
    daily.main()                                       # the card alone: no webhook needed
    assert (tmp_path / "docs/progress.svg").exists() and not state.exists()
    current = daily.collect()
    state.write_text(json.dumps({**current, "message_id": "5", "run_id": "daily"}), encoding="utf-8")
    monkeypatch.setattr(sys, "argv", ["readme_progress.py", "--discord-on-change"])
    monkeypatch.setattr(daily, "urlopen", lambda *a, **k: pytest.fail("Unexpected post"))
    daily.main()
    assert json.loads(state.read_text())["message_id"] == "5"


def real_size(**changes):
    """A state with the tree's real magnitudes, so the card's longest lines are tested."""
    return {"total": 7_978_500, "authored": 7_243_014, "vendored": 460_881, "generated": 261_693, "library": 857,
            "data": 4_104, "assembly": 7_951, "linked": 7_384_266, "linked_authored": 6_898_514,
            "linked_game_code": 7_520_010, "declared_names": 543_787,
            "readable_names": 374_965, "census": census(date="2026-10-24 06:00"),
            "cpp_rules": progress.GAME_CPP_RULES, "census_tool_rules": "retail-truth-4",
            "link_problems": problems(unresolved=103_091),   # a six-figure count still fits its line
            **cleanup(items=22_241, files=21_324, target=2_264, copies=75_134), **changes}


# Advance widths, in font units (2048 an em), of the card's characters, read
# from the hmtx tables of Windows 11's segoeui.ttf, seguisb.ttf, segoeuib.ttf
# (Segoe UI 5.72) and arial.ttf, arialbd.ttf (Arial 7.06), sha256 as recorded
# beside progress.GLYPH_EM: a record separate from GLYPH_EM (the wrapper's own
# estimate), so the card is checked against the fonts it names.
MEASURED_CHARS = (" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
                  "abcdefghijklmnopqrstuvwxyz{|}~\u00b7\u25b2\u25bc\u2013\u2014\u2192\u00d7\u2248")
MEASURED = {face: dict(zip(MEASURED_CHARS, map(int, units.split()), strict=True)) for face, units in (
    ("Segoe UI", (
        "561 582 803 1210 1104 1676 1639 471 618 618 854 1401 444 819 444 798 1104 1104 1104 1104 1104 1104 "
        "1104 1104 1104 1104 444 444 1401 1401 1401 918 1956 1321 1174 1268 1436 1036 1000 1405 1454 545 731 "
        "1188 964 1839 1532 1544 1147 1544 1225 1088 1073 1407 1272 1913 1208 1132 1168 618 776 618 1401 850 "
        "549 1042 1204 946 1206 1071 641 1206 1159 496 496 1018 496 1764 1159 1200 1204 1206 712 869 694 1159 "
        "981 1480 940 991 926 618 490 618 1401 444 1764 1764 1024 2048 1767 1401 1403")),
    ("Arial", (
        "569 569 727 1139 1139 1821 1366 391 682 682 797 1196 569 682 569 569 1139 1139 1139 1139 1139 1139 "
        "1139 1139 1139 1139 569 569 1196 1196 1196 1139 2079 1366 1366 1479 1479 1366 1251 1593 1479 569 "
        "1024 1366 1139 1706 1479 1593 1366 1593 1479 1366 1251 1479 1366 1933 1366 1366 1251 569 569 569 961 "
        "1139 682 1139 1139 1024 1139 1139 569 1139 1139 455 455 1024 455 1706 1139 1139 1139 1139 682 1024 "
        "569 1139 1024 1479 1024 1024 1024 684 532 684 1196 682 2027 2027 1139 2048 2048 1196 1124")),
    ("Segoe UI Semibold", (
        "563 622 896 1211 1137 1721 1465 529 680 680 889 1422 494 823 494 847 1137 824 1137 1137 1180 1137 "
        "1143 1098 1137 1143 494 494 1422 1422 1422 909 1955 1375 1237 1272 1469 1060 1029 1428 1506 597 812 "
        "1251 1001 1893 1571 1548 1197 1548 1275 1115 1130 1440 1314 1978 1268 1182 1202 680 829 680 1422 850 "
        "591 1069 1234 963 1234 1088 706 1234 1192 535 535 1075 535 1814 1195 1223 1234 1234 758 883 740 1195 "
        "1039 1549 1026 1041 951 680 570 680 1422 494 1764 1764 1024 2048 1767 1422 1424")),
    ("Segoe UI Bold", (
        "565 670 1010 1213 1178 1776 1740 600 756 756 932 1448 555 828 555 908 1178 1178 1178 1178 1178 1178 "
        "1178 1178 1178 1178 555 555 1448 1448 1448 897 1954 1440 1313 1278 1510 1090 1065 1456 1569 649 912 "
        "1329 1047 1960 1618 1553 1258 1553 1337 1148 1200 1481 1366 2058 1342 1243 1243 756 893 756 1448 850 "
        "643 1102 1270 983 1268 1108 785 1268 1233 582 582 1145 582 1876 1239 1252 1270 1268 815 901 797 1239 "
        "1110 1633 1131 1102 981 756 668 756 1448 555 1764 1764 1024 2048 1767 1448 1450")),
    ("Arial Bold", (
        "569 682 971 1139 1139 1821 1479 487 682 682 797 1196 569 682 569 569 1139 1139 1139 1139 1139 1139 "
        "1139 1139 1139 1139 682 682 1196 1196 1196 1251 1997 1479 1479 1479 1479 1366 1251 1593 1479 569 "
        "1139 1479 1251 1706 1479 1593 1366 1593 1479 1366 1251 1479 1366 1933 1366 1366 1251 682 569 682 "
        "1196 1139 682 1139 1251 1139 1251 1139 682 1251 1251 569 569 1139 569 1821 1251 1251 1251 1251 797 "
        "1139 682 1251 1139 1593 1139 1139 1024 797 573 797 1196 682 2027 2027 1139 2048 2048 1196 1124")),
)}
REGULAR, SEMIBOLD, BOLD = ("Segoe UI", "Arial"), ("Segoe UI Semibold", "Arial Bold"), ("Segoe UI Bold", "Arial Bold")
# Positive kerning, in font units, of some pairs, from the same files: the
# larger of the kern table and GPOS PairPos under 'kern' (Segoe UI Regular's
# GPOS omits the bracket pairs its kern table widens; Arial kerns none of
# these). A record separate from progress.KERN_EM.
KERN_UNITS = {
    "(j": {"Segoe UI": 233, "Segoe UI Semibold": 214, "Segoe UI Bold": 190},
    "[j": {"Segoe UI": 233, "Segoe UI Semibold": 205, "Segoe UI Bold": 170},
    "{j": {"Segoe UI": 203, "Segoe UI Semibold": 184, "Segoe UI Bold": 160},
    "f)": {"Segoe UI": 141, "Segoe UI Semibold": 113, "Segoe UI Bold": 78},
    "qj": {"Segoe UI": 102, "Segoe UI Semibold": 97, "Segoe UI Bold": 90},
    "LJ": {"Segoe UI": 100, "Segoe UI Semibold": 81, "Segoe UI Bold": 57},
    "rv": {"Segoe UI": 82, "Segoe UI Semibold": 82, "Segoe UI Bold": 82},
}


def measured(text, size, faces):
    """The widest of `faces`' widths of the rendered `text` at `size` px,
    kerned where KERN_UNITS records the pair."""
    text = html.unescape(text)
    return max(size * (sum(MEASURED[face][char] for char in text)
                       + sum(KERN_UNITS.get(text[i:i + 2], {}).get(face, 0) for i in range(len(text) - 1))) / 2048
               for face in faces)


@pytest.mark.parametrize("pair", sorted(KERN_UNITS))
def test_text_width_bounds_kerned_pairs(pair):
    # A renderer that ignores font-kerning="none" widens these pairs; the
    # bound still holds in every face, alone and inside a longer run.
    for face in MEASURED:
        assert progress.text_width(pair, 2048) >= measured(pair, 2048, (face,)), (pair, face)
    assert progress.text_width(pair, 1000) == sum(progress.GLYPH_EM[c] for c in pair) + progress.KERN_EM[pair]
    run = f"x{pair}{pair}x"
    assert progress.text_width(run, 1000) == sum(progress.GLYPH_EM[c] for c in run) + 2 * progress.KERN_EM[pair]


def test_kerning_breaks_advances_alone_for_paren_j():
    # Segoe UI Bold kerns (j by +190 units (kern and GPOS): 0.746 em, past
    # the advances alone (0.655 em); Semibold (+214) is over too.
    advances = sum(progress.GLYPH_EM[c] for c in "(j") / 1000
    assert measured("(j", 1, ("Segoe UI Bold",)) > advances and measured("(j", 1, ("Segoe UI Semibold",)) > advances
    assert progress.text_width("(j", 1) >= measured("(j", 1, MEASURED)
    assert progress.text_width("j(", 1) == advances  # pairs are ordered
    assert all(value > 0 for value in progress.KERN_EM.values()) and set("".join(progress.KERN_EM)) <= set(MEASURED_CHARS)


def test_glyph_estimate_bounds_every_measured_advance():
    # The wrapper's estimate is at least every measured face's advance, at
    # every weight the SVGs use, for every character it knows, and covers
    # every character measured; text_width adds no allowance on top.
    assert set(progress.GLYPH_EM) == set(MEASURED_CHARS)
    for face in MEASURED:
        assert all(progress.GLYPH_EM[char] / 1000 >= units / 2048 for char, units in MEASURED[face].items()), face
    assert progress.text_width("I|*", 1000) == sum(progress.GLYPH_EM[char] for char in "I|*")
    assert measured("0123456789", 12.5, REGULAR) == pytest.approx(10 * 12.5 * 1139 / 2048)  # Arial digits, 0.556 em
    assert measured("W", 12.5, REGULAR) == pytest.approx(12.5 * 1933 / 2048)  # 0.94 em
    with pytest.raises(ValueError, match="No measured glyph advance"):
        progress.text_width("\u4e2d", 12.5)


# The measured faces of each family the SVGs may name.
FAMILIES = {"Segoe UI": ("Segoe UI", "Segoe UI Semibold", "Segoe UI Bold"), "Arial": ("Arial", "Arial Bold")}
# Noto Sans 2.008 Regular (notofonts/noto-fonts hinted/ttf, 1000 units an em),
# which an earlier stack named: wider than the bound it was given.
NOTO_SANS = {"I": 339, "*": 551, "|": 551}


def test_svgs_name_only_measured_faces():
    # Every family in the stack has a measured face at each weight, no generic
    # family closes it, and every SVG generator declares that stack and no other.
    families = [name.strip().strip("'\"") for name in progress.FONT_STACK.split(",")]
    assert families == list(FAMILIES) and set(MEASURED) == {face for faces in FAMILIES.values() for face in faces}
    tools = Path(progress.__file__).resolve().parent
    for name in ("readme_progress.py", "progress_v2.py", "progress_site.py"):
        source = (tools / name).read_text(encoding="utf-8")
        declared = re.findall(r'font-family="([^"]*)"', source)
        assert declared and set(declared) <= {"{progress.FONT_STACK}", "{FONT}"}, (name, declared)
        # ... and turns kerning off wherever it names the stack.
        assert source.count("{progress.NO_KERN}") == len(declared), name
    assert f'font-family="{progress.FONT_STACK}" {progress.NO_KERN}' in daily.render(real_size())
    assert 'style="font-kerning:none;' in progress.NO_KERN and 'text-rendering="optimizeSpeed"' in progress.NO_KERN
    # The stack dropped Noto Sans because its advances exceed what the old
    # table allowed; the new table still does not bound them, so it stays out.
    assert any(units / 1000 > progress.GLYPH_EM[char] / 1000 for char, units in NOTO_SANS.items())






def inclusive_size(**changes):
    return real_size(linked_game_executable=7_171_638, game_executable=7_512_658,
                     link_coverage_rules=progress.LINK_COVERAGE_RULES, **changes)


OTHER_RULES = {"census": census(date="2026-10-23 06:00", rules="retail-truth-3")}
PENDING = {"census_tool_rules": "retail-truth-5"}
OWNED = {"ownership": {"date": "2026-11-02", "ours": 9_000_000, "content": 12_345_678}}


@pytest.mark.parametrize("now,before,notes", [
    (real_size(), real_size(), []),
    (inclusive_size(), inclusive_size(), []),
    (inclusive_size(), real_size(), ["Generated linked code now counted"]),
    (real_size(), inclusive_size(), ["Census accounting changed to authored-only"]),
    (real_size(), real_size(**OTHER_RULES), ["Census accounting changed to retail-truth-4 (91.74% under retail-truth-3)"]),
    (inclusive_size(), inclusive_size(**OTHER_RULES), ["Census accounting changed to retail-truth-4 (95.46% under retail-truth-3)"]),
    (inclusive_size(**PENDING), inclusive_size(), ["this is the last figure under the old rules"]),
    (inclusive_size(**PENDING, **OWNED), inclusive_size(**OTHER_RULES), ["Census accounting changed to retail-truth-4"]),
    (inclusive_size(tu_target=2_300), inclusive_size(), ["estimate moved from 2,264 to 2,300 files"]),
    ({k: v for k, v in real_size().items() if k not in cleanup()}, real_size(), []),
], ids=["legacy", "inclusive", "accounting", "reverse-accounting", "legacy-rules", "inclusive-rules", "pending",
        "pending-owned", "tu-estimate", "no-phase2-counts"])
def test_card_lines_fit_the_card(now, before, notes):
    svg = daily.render(now, {**before, "message_id": "1"})
    root = ET.fromstring(svg)
    texts = [(int(node.attrib["y"]), node) for node in root.iter() if node.tag.endswith("}text")]
    height = int(root.attrib["height"])
    assert all(y < height - 6 for y, _ in texts)
    weights = {"600": SEMIBOLD, "700": BOLD}
    rows = {}
    for y, node in texts:
        size = float(node.attrib["font-size"])
        used = measured(node.text or "", size, weights.get(node.attrib.get("font-weight"), REGULAR))
        for span in node:                       # a tag beside a label, the milestone's rest
            used += float(span.attrib.get("dx", 0)) + measured(span.text or "", float(span.attrib.get(
                "font-size", size)), weights.get(span.attrib.get("font-weight", node.attrib.get("font-weight")),
                                                 REGULAR))
        x = float(node.attrib["x"])
        left = x - used if node.attrib.get("text-anchor") == "end" else x
        assert 28 <= left and left + used <= 852 + 0.5, (node.text, left, used)
        rows.setdefault(y, []).append((left, left + used, node.text))
    for spans in rows.values():                 # a caption and its note never overlap
        spans.sort()
        assert all(a[1] + 12 <= b[0] for a, b in zip(spans, spans[1:])), spans
    bars = [node for node in root.iter() if node.tag.endswith("}rect") and node.attrib.get("class") == "track"]
    labels = {node.text: node for _, node in texts}
    for _, label in daily.CLEAN:                # every compact label, with its tag, ends before its bar
        node = labels[label]
        end = 28 + measured(label, 14, SEMIBOLD) + sum(10 + measured(span.text, 12, SEMIBOLD) for span in node)
        bar = next(b for b in bars if abs(float(b.attrib["y"]) - (int(node.attrib["y"]) - 10)) < 0.5)
        assert end + 12 <= float(bar.attrib["x"]), (label, end, bar.attrib["x"])
        assert float(bar.attrib["x"]) + float(bar.attrib["width"]) + 12 <= 852 - measured("-100.00%", 15, BOLD)
    joined = text_of(svg)
    for note in notes:
        assert note in joined, (note, joined)
    assert "Byte match" in labels and "Linking" in labels


def test_rule_note_tells_an_absent_figure_from_invalid_saved_data():
    rules = {"census": census(date="2026-10-24 06:00")}
    current = {**sample(), **rules}
    old_rules = {"census": census(date="2026-10-23 06:00", rules="retail-truth-3")}
    absent = previous(linked_authored=None, linked_game_code=None, **old_rules)
    text = daily.announcement(current, absent)["embeds"][0]["description"]
    assert ("Census accounting changed to retail-truth-4 (was retail-truth-3; the last post saved no Linking figure)"
            in text)
    text = daily.announcement(current, previous(**old_rules))["embeds"][0]["description"]
    assert "Census accounting changed to retail-truth-4 (10.00% under retail-truth-3)" in text
    for bad in ({"linked_authored": "9"}, {"linked_authored": 100}, {"linked_game_code": 5},
                {"linked_authored": None}, {"linked_game_code": None}):
        with pytest.raises(ValueError, match="saved"):
            daily.rule_note(previous(**old_rules, **bad), ("retail-truth-3", "retail-truth-4"))
        for draw in (daily.announcement, daily.render):
            with pytest.raises((ValueError, TypeError)):
                draw(current, previous(**old_rules, **bad))


@pytest.mark.parametrize("bad", [
    {"linked_game_executable": "9"}, {"game_executable": None}, {"linked_game_executable": None},
    {"linked_game_executable": -1}, {"linked_game_executable": 8_000_000}, {"game_executable": False},
    {"link_coverage_rules": ""}, {"game_executable": 8_000_000},
])
def test_invalid_inclusive_saved_linking_raises(bad):
    saved = inclusive_size()
    saved.update(bad)
    for change in (("retail-truth-3", "retail-truth-4"), ("authored-only", progress.LINK_COVERAGE_RULES)):
        with pytest.raises(ValueError, match="saved"):
            daily.rule_note(saved, change)
    with pytest.raises(ValueError, match="saved"):
        daily.saved_linking(saved)


def test_saved_linking_uses_upstream_inclusive_fields():
    assert daily.saved_linking(inclusive_size()) == (7_171_638, 7_512_658)
    assert daily.saved_linking(real_size()) == (6_898_514, 7_520_010)
    assert daily.saved_linking({}) is None


def test_workflow_posts_daily_and_refreshes_hourly():
    flow = (Path(progress.ROOT) / ".github/workflows/readme-progress.yml").read_text(encoding="utf-8")
    assert "cron: '37 8 * * *'" in flow and re.search(r"cron: '\d+ \* \* \* \*'", flow)
    assert "--discord-on-change" in flow and "--discord" in flow


def test_fresh_checkout_retry_of_a_run_that_posted_does_not_post_again(tmp_path, monkeypatch):
    """The run posts, then a later render or push fails and docs/discord-progress.json
    never reaches master. A re-run with the same run ID checks out master afresh;
    the post record (kept by actions/cache, outside the checkout) stops a second
    post and puts the post's figures back for the commit."""
    record = tmp_path / "cache" / "discord-post.json"            # outside every checkout
    old = {**full(), "message_id": "1", "run_id": "yesterday", "updated_at": "2026-10-28T12:37:00+00:00"}
    monkeypatch.setenv("GITHUB_RUN_ID", "run-7")
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token")
    posts = []
    monkeypatch.setattr(daily, "urlopen", lambda request, timeout: posts.append(request) or io.BytesIO(b'{"id":"8"}'))
    fake_collection(monkeypatch)

    def checkout(name):          # master as the workflow checks it out: yesterday's post state
        root = tmp_path / name
        root.mkdir()
        setup = root / "docs"
        setup.mkdir()
        (setup / "discord-progress.json").write_text(json.dumps(old), encoding="utf-8")
        monkeypatch.setattr(daily.progress, "ROOT", root)
        return root

    checkout("attempt-1")
    monkeypatch.setattr(sys, "argv", ["readme_progress.py", "--discord", "--post-record", str(record)])
    daily.main()
    assert len(posts) == 1 and json.loads(record.read_text())["message_id"] == "8"
    # ... the push fails; attempt 2 starts from a fresh checkout of master
    root = checkout("attempt-2")
    daily.main()
    assert len(posts) == 1, "a retried run posted twice"
    saved = json.loads((root / daily.STATE).read_text())
    assert saved["message_id"] == "8" and saved["run_id"] == "run-7"   # the commit now carries the post
    # another run's record, or one older than master's state, is never restored
    monkeypatch.setenv("GITHUB_RUN_ID", "run-9")
    root = checkout("next-run")
    assert daily.restore_post(record) is False
    monkeypatch.setenv("GITHUB_RUN_ID", "run-7")
    (root / daily.STATE).write_text(json.dumps({**old, "updated_at": "2026-12-01T00:00:00+00:00"}), encoding="utf-8")
    assert daily.restore_post(record) is False


def test_a_post_is_recorded_before_the_repository_state(tmp_path, monkeypatch):
    setup_state(tmp_path, monkeypatch)
    record = tmp_path / "cache" / "post.json"
    monkeypatch.setenv("GITHUB_RUN_ID", "run-3")
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token")
    monkeypatch.setattr(daily, "urlopen", lambda request, timeout: io.BytesIO(b'{"id":"4"}'))
    order = []
    real = daily._write_json
    monkeypatch.setattr(daily, "_write_json", lambda path, value: order.append(Path(path).name) or real(path, value))
    daily.notify(full(), record_path=record)
    assert order == ["post.json", "discord-progress.json"]


def test_a_game_data_measurement_alone_triggers_the_hourly_post(tmp_path, monkeypatch):
    owned = {"date": "2026-11-02", "ours": 750, "content": 1000}
    before, after = full(), full(ownership=owned)
    assert daily.headline(before) != daily.headline(after)
    assert daily.headline(after) != daily.headline(full(ownership={**owned, "ours": 760}))
    # the note carries its own label and its own share; byte match keeps its bytes and its bar
    post = daily.announcement(after, None)["embeds"][0]["description"]
    assert "**Byte match: 60.00%**" in post and "(whole game file: 75.00% ours (2026-11-02))" in post
    svg = daily.render(after)
    assert 'width="494.40" height="14" rx="7" fill="#2ea043"' in svg            # 60% of 824 px
    assert ">whole game file: 75.00% ours (2026-11-02)<" in svg and ">60.00%<" in svg
    path = setup_state(tmp_path, monkeypatch, {**before, "message_id": "1", "run_id": "daily"})
    monkeypatch.setenv("GITHUB_RUN_ID", "hourly")
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token")
    monkeypatch.setattr(daily, "urlopen", lambda request, timeout: io.BytesIO(b'{"id":"2"}'))
    daily.notify(after, on_change=True)
    assert json.loads(path.read_text())["message_id"] == "2"


def git_in(path, *args):
    return subprocess.run(["git", *args], cwd=path, check=True, capture_output=True, text=True).stdout.strip()


def test_publish_draws_the_card_again_on_the_tree_it_pushes_onto(tmp_path, monkeypatch):
    """A rebase would carry a card drawn from the older tree onto newer inputs;
    publish draws it again whenever commits that landed meanwhile changed an input."""
    for key, value in (("GIT_AUTHOR_NAME", "t"), ("GIT_AUTHOR_EMAIL", "t@t"), ("GIT_COMMITTER_NAME", "t"),
                       ("GIT_COMMITTER_EMAIL", "t@t"), ("GIT_CONFIG_NOSYSTEM", "1")):
        monkeypatch.setenv(key, value)
    origin, ci, fleet = tmp_path / "origin.git", tmp_path / "ci", tmp_path / "fleet"
    git_in(tmp_path, "init", "-q", "--bare", "-b", "master", str(origin))
    git_in(tmp_path, "clone", "-q", str(origin), str(fleet))
    git_in(fleet, "symbolic-ref", "HEAD", "refs/heads/master")
    (fleet / "Code").mkdir()
    (fleet / "Code/count.txt").write_text("1\n")
    git_in(fleet, "add", ".")
    git_in(fleet, "commit", "-q", "-m", "inputs")
    git_in(fleet, "push", "-q", "origin", "master")
    git_in(tmp_path, "clone", "-q", "-b", "master", str(origin), str(ci))
    monkeypatch.setattr(daily.progress, "ROOT", ci)
    drawn = []

    def render():                # the card states the input it was drawn from
        (ci / "docs").mkdir(exist_ok=True)
        (ci / "docs/progress.svg").write_text("card " + (ci / "Code/count.txt").read_text())
        drawn.append((ci / "Code/count.txt").read_text())

    render()
    # while the card was drawn, the fleet landed a commit that changes an input
    (fleet / "Code/count.txt").write_text("2\n")
    git_in(fleet, "commit", "-q", "-am", "fleet")
    git_in(fleet, "push", "-q", "origin", "master")
    daily.publish(render, wait=lambda seconds: None)
    assert git_in(origin, "show", "master:docs/progress.svg") == "card 2", "a card of the older tree was pushed"
    assert drawn == ["1\n", "2\n"]
    # nothing landed since: no second drawing, just the push
    drawn.clear()
    (ci / "docs/progress.svg").write_text("card 2 restyled\n")
    daily.publish(render, wait=lambda seconds: None)
    assert drawn == [] and git_in(origin, "show", "master:docs/progress.svg") == "card 2 restyled"
    # a commit that touched no input (another card) is rebased onto, not drawn again
    git_in(fleet, "pull", "-q", "--rebase", "origin", "master")
    (fleet / "docs/progress_map.svg").write_text("map\n")
    git_in(fleet, "add", "docs/progress_map.svg")
    git_in(fleet, "commit", "-q", "-m", "map")
    git_in(fleet, "push", "-q", "origin", "master")
    (ci / "docs/progress.svg").write_text("card 2 again\n")
    daily.publish(render, wait=lambda seconds: None)
    assert drawn == [] and git_in(origin, "show", "master:docs/progress.svg") == "card 2 again"
    assert git_in(origin, "show", "master:docs/progress_map.svg") == "map"


def test_render_again_runs_the_workflows_render_steps_without_posting():
    flow = (Path(progress.ROOT) / ".github/workflows/readme-progress.yml").read_text(encoding="utf-8")
    for step in daily.RENDER:
        assert "python " + " ".join(step) in flow, step
    assert all("--discord" not in part for step in daily.RENDER for part in step)
    assert set(daily.OUTPUTS) >= {"docs/progress.svg", daily.STATE}


def test_workflow_keeps_every_pending_run_and_the_post_record():
    flow = (Path(progress.ROOT) / ".github/workflows/readme-progress.yml").read_text(encoding="utf-8")
    concurrency = flow.split("concurrency:", 1)[1].split("jobs:", 1)[0]
    # the default queue (single) lets a newer hourly run replace a pending daily run
    assert re.search(r"^\s+queue: max\s*$", concurrency, re.M)
    assert "cancel-in-progress: false" in concurrency          # queue: max refuses cancel-in-progress: true
    assert "actions/cache/restore@v5" in flow and "actions/cache/save@v5" in flow
    assert flow.count("key: discord-post-${{ github.run_id }}") == 2
    assert "--post-record build/discord-post.json" in flow and "--publish" in flow
    assert "git pull --rebase" not in flow                     # publish draws again instead of rebasing a stale card
