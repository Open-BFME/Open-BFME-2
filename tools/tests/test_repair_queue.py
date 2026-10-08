"""repair_queue: gate-debt and link-cycle repairs carry their check and a machine pass
test; new matches are told which unit they belong in (never a fresh one-function file)."""
import importlib
import os
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


def load(tmp_path, layout, ledger, files=()):
    rev = tmp_path / ("targets/game/reverse" if layout == "bfme1" else "reverse")
    rev.mkdir(parents=True)
    src = "game" if layout == "bfme1" else "Code"
    (rev / "functions.csv").write_text(HEADER + "".join(
        f"{n},,0x{r:08X},{s},{src}/{f},matched,\n" for n, r, s, f in ledger), newline="\n")
    for rel, text in files:
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, newline="\n")
    os.environ["REPAIR_ROOT"] = str(tmp_path)
    try:
        import repair_queue
        return importlib.reload(repair_queue), rev, src
    finally:
        del os.environ["REPAIR_ROOT"]


LEDGER = [("?a@Loco@@QAEXXZ", 0x1000, 0x40, "GameEngine/Loco.cpp"),
          ("?b@Loco@@QAEXXZ", 0x1080, 0x40, "GameEngine/Loco.cpp"),
          ("?c@Body@@QAEXXZ", 0x2000, 0x20, "GameEngine/Body.cpp"),
          ("?d_00003000@@YAXXZ", 0x3000, 0x8, "GameEngine/Rva00003000Noop.cpp"),
          ("?g@@YAXXZ", 0x3100, 0x8, "gen_small/uw.cpp")]


@pytest.mark.parametrize("layout", ["bfme1", "bfme2"])
def test_dest_prefers_the_unit_around_the_address(tmp_path, layout):
    rq, _, src = load(tmp_path, layout, LEDGER)
    assert rq.dest_tu(0x1040)["dest"] == f"{src}/GameEngine/Loco.cpp"            # between two Loco rows
    assert "between two rows" in rq.dest_tu(0x1040)["basis"]
    assert rq.dest_tu(0x1F00)["dest"] == f"{src}/GameEngine/Body.cpp"            # nearest, 0x100 away
    got = rq.dest_tu(0x3010)                                                     # only an address-named file
    assert got["dest"] == f"{src}/GameEngine/Body.cpp"                           # and a generated one nearby
    got = rq.dest_tu(0x40000)
    assert got["dest"] is None and "never a new one-function file" in got["basis"]


def test_dest_takes_ea_file_evidence_first(tmp_path):
    rq, rev, src = load(tmp_path, "bfme1", LEDGER, [
        ("game/GameEngine/Source/Snapshot.cpp", "//\n"),
        ("targets/game/reverse/ea_evidence.csv",
         "rva,kind,value,route,basis\n0x00001040,file,GameEngine/Source/Snapshot.cpp,zh,\n")])
    got = rq.dest_tu(0x1040)
    assert got == {"dest": "game/GameEngine/Source/Snapshot.cpp", "basis": "EA source-file evidence (zh)"}


def test_bfme2_gate_debt_items_and_pass_test(tmp_path):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, [
        ("reverse/gate_baseline.txt", "# header\ntail 0x00001000 ?a@Loco@@QAEXXZ\nstrnul 0x00002000 ?c@Body@@QAEXXZ\n")])
    items = rq.repair_items()
    assert [(i["check"], i["source"], i["size"]) for i in items] == [
        ("tail", "Code/GameEngine/Loco.cpp", 0x40), ("strnul", "Code/GameEngine/Body.cpp", 0x20)]
    assert "pass-test 'tail 0x00001000 ?a@Loco@@QAEXXZ'" in items[0]["pass_test"]
    ok, _ = rq.pass_test("tail 0x00001000 ?a@Loco@@QAEXXZ", build_cmd=[sys.executable, "-c", "raise SystemExit(1)"])
    assert not ok and "tail 0x00001000" in (rev / "gate_baseline.txt").read_text()     # restored
    ok, message = rq.pass_test("tail 0x00001000 ?a@Loco@@QAEXXZ", build_cmd=[sys.executable, "-c", "pass"])
    assert ok and "tail 0x00001000" not in (rev / "gate_baseline.txt").read_text()
    assert "strnul 0x00002000" in (rev / "gate_baseline.txt").read_text()
    assert rq.pass_test("tail 0x00001000 ?a@Loco@@QAEXXZ")[0] is False                  # already gone


def test_bfme1_body_guard_items(tmp_path):
    rq, rev, _ = load(tmp_path, "bfme1", LEDGER, [
        ("targets/game/reverse/body_guard_baseline.csv",
         "check,target_rva,name,detail\nltable,0x00001080,?b@Loco@@QAEXXZ,+12 $L9 wants 0x1 retail 0x2\n"
         "dir32,0x00401942,?g_00401942@@YAXXZ,\"nothing owns 0x00401942, give it a data row\"\n"),
        ("targets/game/reverse/full_gate_baseline.txt", "# full-gate red rows\n")])
    items = rq.repair_items()
    assert items[0]["check"] == "ltable" and items[0]["source"] == "game/GameEngine/Loco.cpp"
    assert items[0]["why"].startswith("+12 $L9")
    assert items[1]["check"] == "dir32" and items[1]["source"].startswith("(git grep")


def test_link_items_serve_placed_unwired_rows_first(tmp_path):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER)
    status = tmp_path / "link_status.csv"
    status.write_text(
        "name,kind,source,retail_rva,size,linked_rva,placed,placement_reason,self_strict,closed_strict,"
        "closed_strict_pilot_rule,pinned_strict,byte_equal,hardcoded,failure_count,failures\n"
        "?ok@@YAXXZ,real,Code/a.cpp,0x00001000,64,0x00001000,1,,1,1,1,1,1,0,0,\n"
        "?far@@YAXXZ,real,Code/a.cpp,0x00002000,500,0x007BBD80,0,retail start violates section alignment,1,1,1,1,0,0,0,\n"
        "?wire@@YAXXZ,real,Code/b.cpp,0x00003000,40,0x00003000,1,,0,0,0,0,0,0,1,data-back:g_x\n"
        "?gen@@YAXXZ,gen-funclet,Code/gen_small/u.cpp,0x00004000,9,,0,not COMDAT,0,0,0,0,0,0,0,\n", newline="\n")
    items, note = rq.link_items(status)
    assert [(i["function"], i["why"]) for i in items] == [
        ("?wire@@YAXXZ", "data-back:g_x"), ("?far@@YAXXZ", "retail start violates section alignment")]
    assert "2 row(s)" in note


# ---- link tier sources: a local link cycle (build product) first, else the committed census

CYCLE_STATUS = (
    "name,kind,source,retail_rva,size,linked_rva,placed,placement_reason,self_strict,closed_strict,"
    "closed_strict_pilot_rule,pinned_strict,byte_equal,hardcoded,failure_count,failures\n"
    "?wire@@YAXXZ,real,Code/b.cpp,0x00003000,40,0x00003000,1,,0,0,0,0,0,0,1,data-back:g_x\n")
CENSUS_STATUS = (
    "source,linked,unresolved,duplicates,comdat_losers,addresses,wrong_selected\n"
    "Code/GameEngine/Loco.cpp,no,2,0,1,0,0\n"
    "Code/GameEngine/Body.cpp,no,1,0,0,0,0\n"
    "Code/GameEngine/Rva00003000Noop.cpp,yes,0,0,0,0,0\n")
CENSUS_HISTORY = "date,commit,objects\n2026-09-29 11:03,c4d3910546,9016\n2026-10-07 21:52,086d0a7aaa,19715\n"
CENSUS_FILES = [("reverse/link_status.csv", CENSUS_STATUS), ("reverse/link_census_history.csv", CENSUS_HISTORY)]
CENSUS_TIME = 1791409920                     # 2026-10-07 21:52 UTC, the history row's date


def _cycle(tmp_path, when, commit=None):
    out = tmp_path / "build/link_cycle"
    out.mkdir(parents=True)
    (out / "link_status.csv").write_text(CYCLE_STATUS, newline="\n")
    if commit:
        (out / "receipt.json").write_text('{"commit": "%s", "dirty": false}' % commit)
    os.utime(out / "link_status.csv", (when, when))


def test_link_tier_prefers_a_newer_local_link_cycle(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    _cycle(tmp_path, CENSUS_TIME + 3600, commit="f00dfeedbeef0123")
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, CENSUS_FILES)
    items, note = rq.link_items()
    assert [i["function"] for i in items] == ["?wire@@YAXXZ"]
    assert "local link cycle" in note and "commit f00dfeedbe" in note
    assert rq.main(["link"]) == 0 and "local link cycle" in capsys.readouterr().out


def test_link_tier_falls_back_to_the_committed_census(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, CENSUS_FILES)
    items, note = rq.link_items()                                        # no local cycle at all
    assert [(i["source"], i["target_rva"], i["size"]) for i in items] == [
        ("Code/GameEngine/Body.cpp", "0x00002000", 0x20),                 # one blocker: nearest to linking
        ("Code/GameEngine/Loco.cpp", "0x00001000", 0x80)]                 # both Loco rows credited
    assert items[1]["why"] == "unit does not link (2 matched row(s)): unresolved 2, comdat_losers 1"
    assert "link_check.py Code/GameEngine/Body.cpp" in items[0]["pass_test"]
    assert "committed link census reverse/link_status.csv" in note and "086d0a7aaa" in note
    assert rq.main(["link"]) == 0 and "measured at commit 086d0a7aaa" in capsys.readouterr().out
    _cycle(tmp_path, CENSUS_TIME - 3600)                                  # a local cycle older than the census
    items, note = rq.link_items()
    assert len(items) == 2 and "not newer" in note and "commit unknown" in note


def test_link_tier_with_no_status_says_so_and_fails(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    rq, _, _ = load(tmp_path, "bfme2", LEDGER)
    items, note = rq.link_items()
    assert items == [] and "no link status" in note
    assert rq.main(["link"]) == 1
    err = capsys.readouterr().err
    assert "run tools/link_cycle.py" in err and "reverse/link_status.csv" in err


def test_next_work_serves_repairs_before_new_matches():
    import next_work
    repair = [{"function": "r", "target_rva": "0x1", "size": 4}]
    named = [{"function": "n", "target_rva": "0x2", "size": 4}]
    assert next_work.selected_queue(None, [], [], [], [], named, repair=repair)[0] == "gate-debt repair"
    assert next_work.selected_queue(None, [], [], [], [], named, repair=[])[1] == named
    assert next_work.selected_queue("named", [], [], [], [], named, repair=repair)[1] == named
    assert next_work.selected_queue("repair", [], [], [], [], named, repair=repair)[1] == repair


def test_a_removed_debt_line_is_reverified(tmp_path):
    import subprocess
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, [
        ("reverse/gate_baseline.txt", "tail 0x00001000 ?a@Loco@@QAEXXZ\nstrnul 0x00002000 ?c@Body@@QAEXXZ\n"),
        ("Code/GameEngine/Loco.cpp", "//\n"), ("Code/GameEngine/Body.cpp", "//\n")])

    def git(*args):
        return subprocess.run(["git", "-C", str(tmp_path), *args], capture_output=True, text=True, check=True)
    git("init", "-q")
    git("add", ".")
    git("-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "init")
    fail, ok = [sys.executable, "-c", "raise SystemExit(1)"], [sys.executable, "-c", "pass"]
    assert rq.verify_removed(fail) == []                                   # nothing removed
    (rev / "gate_baseline.txt").write_text("strnul 0x00002000 ?c@Body@@QAEXXZ\n", newline="\n")
    git("add", "reverse/gate_baseline.txt")
    got = rq.verify_removed(fail)                                          # credited without a fix
    assert len(got) == 1 and "Code/GameEngine/Loco.cpp" in got[0]
    assert rq.verify_removed(ok) == []                                     # the row really passes
    (tmp_path / "Code/GameEngine/Loco.cpp").write_text("// fixed\n")
    git("add", "Code/GameEngine/Loco.cpp")
    assert rq.verify_removed(fail) == []                                   # staged: the hook builds it


def test_repairs_are_capped_to_one_pick_in_n(tmp_path, monkeypatch):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER)
    monkeypatch.delenv("BFME_REPAIR_EVERY", raising=False)
    turns = [rq.repair_turn(owner="seat-a") for _ in range(9)]
    assert sum(turns) == 3 and turns[:3].count(True) == 1                 # default: 1 in 3, rotated
    assert sum(rq.repair_turn(4, owner="seat-b") for _ in range(8)) == 2
    assert all(rq.repair_turn(1, owner="x") for _ in range(3))
    assert not any(rq.repair_turn(0, owner="x") for _ in range(3))
    monkeypatch.setenv("BFME_REPAIR_EVERY", "1")
    assert rq.repair_turn(owner="seat-c")


def test_off_turn_picks_skip_repairs_unless_nothing_else():
    import next_work
    repair = [{"function": "r", "target_rva": "0x1", "size": 4}]
    named = [{"function": "n", "target_rva": "0x2", "size": 4}]
    assert next_work.selected_queue(None, [], [], [], [], named, repair=repair, repair_turn=False)[1] == named
    assert next_work.selected_queue(None, [], [], [], [], [], repair=repair, repair_turn=False)[1] == repair
    assert next_work.selected_queue(None, [], [], [], [], named, repair=repair, repair_turn=True)[1] == repair


def test_tier_c_and_diffexec_findings_feed_the_repair_queue(tmp_path):
    rq, rev, src = load(tmp_path, "bfme2", LEDGER, [
        ("reverse/gate_baseline.txt", "tail 0x00001000 ?a@Loco@@QAEXXZ\n"),
        ("reverse/match_tiers.csv", "target_rva,target_size,name,source,tier,reasons\n"
         "0x00001000,64,?a@Loco@@QAEXXZ,Code/GameEngine/Loco.cpp,C,gate:tail\n"
         "0x00002000,32,?c@Body@@QAEXXZ,Code/GameEngine/Body.cpp,C,identity:wrong\n"
         "0x00001080,64,?b@Loco@@QAEXXZ,Code/GameEngine/Loco.cpp,A,\n")])
    dx = tmp_path / "results.jsonl"
    dx.write_text('{"name":"?d@@YAXXZ","rva":"0x00004000","size":9,"source":"Code/d.cpp","verdict":"binding",'
                  '"reason":"objects: call #0: retail rva:0x1 rebuilt rva:0x2"}\n'
                  '{"name":"?e@@YAXXZ","rva":"0x00005000","size":9,"source":"Code/e.cpp","verdict":"binding",'
                  '"reason":"objects: call #0 (twin bodies)"}\n'
                  '{"name":"?f@@YAXXZ","rva":"0x00006000","size":9,"source":"Code/f.cpp","verdict":"none"}\n')
    rq.DIFFEXEC = str(dx)
    items = rq.all_repair_items()
    assert [(i["check"], i["target_rva"]) for i in items] == [
        ("tail", "0x00001000"), ("tier-C", "0x00002000"), ("diffexec-binding", "0x00004000")]
    assert "diffexec.py --row 0x00004000" in items[2]["pass_test"]


def test_boot_smoke_bisection_feeds_the_repair_queue(tmp_path):
    rq, rev, src = load(tmp_path, "bfme2", LEDGER, [("reverse/gate_baseline.txt", "tail 0x00001000 ?a@Loco@@QAEXXZ\n")])
    bq = tmp_path / "boot_queue.json"
    bq.write_text('{"tool": "boot_smoke", "items": [{"target_rva": "0x00001080", "name": "?b@Loco@@QAEXXZ", '
                  '"source": "Code/GameEngine/Loco.cpp", "size": 64, "outcome": "crash-at-?b@Loco@@QAEXXZ", '
                  '"why": "boot smoke crash with this row overlaid alone"}, {"target_rva": "0x00001000", '
                  '"name": "?a@Loco@@QAEXXZ", "source": "Code/GameEngine/Loco.cpp", "size": 64, "why": "dup"}]}')
    rq.BOOT_QUEUE = str(bq)
    items = rq.all_repair_items()
    assert [(i["check"], i["target_rva"]) for i in items] == [("tail", "0x00001000"), ("boot-crash", "0x00001080")]
    assert "boot_smoke.py --game-dir SANDBOX --overlay rva:0x00001080" in items[1]["pass_test"]
    rq.BOOT_QUEUE = str(tmp_path / "missing.json")
    assert rq.boot_items() == []


def test_game_smoke_desync_and_static_findings_feed_the_repair_queue(tmp_path):
    import json
    rq, rev, src = load(tmp_path, "bfme2", LEDGER, [("reverse/gate_baseline.txt", "tail 0x00001000 ?a@Loco@@QAEXXZ\n")])
    (tmp_path / "build" / "game").mkdir(parents=True)
    (tmp_path / "build" / "boot").mkdir(parents=True)
    # the default paths: what game_smoke.py bisect and boot_relayout.py findings write
    desync = {"tool": "game_smoke", "items": [
        {"target_rva": "0x00001080", "name": "?b@Loco@@QAEXXZ", "source": "Code/GameEngine/Loco.cpp", "size": 64,
         "outcome": "desync", "check": "desync", "why": "game_smoke determinism desync with this row alone",
         "pass_test": "python3 tools/game_smoke.py determinism --image one"}]}
    static = {"tool": "boot_relayout findings", "items": [
        {"target_rva": "0x00001080", "name": "?b@Loco@@QAEXXZ", "source": "Code/GameEngine/Loco.cpp", "size": 64,
         "check": "inline-data", "why": "dup of the desync row", "pass_test": "x"},
        {"target_rva": "0x00002000", "name": "?c@Body@@QAEXXZ", "source": "Code/GameEngine/Body.cpp", "size": 32,
         "check": "truncated-table", "why": "its object defines ??_7Body@@6B@ as 4 byte(s)",
         "pass_test": "python3 tools/boot_relayout.py findings --overlay rva:0x00002000 --only truncated-table"},
        {"target_rva": "0x00003000", "name": "?d_00003000@@YAXXZ", "source": "Code/GameEngine/Rva00003000Noop.cpp",
         "size": 8, "check": "inline-data", "why": "reads retail .text past its extent"}]}
    boot = {"tool": "boot_smoke", "items": [
        {"target_rva": "0x00003100", "name": "?g@@YAXXZ", "source": "Code/gen_small/uw.cpp", "size": 8,
         "outcome": "crash-at-x", "why": "boot smoke crash"}]}
    (tmp_path / "build/game/desync_queue.json").write_text(json.dumps(desync))
    (tmp_path / "build/boot/static_queue.json").write_text(json.dumps(static))
    (tmp_path / "build/boot/boot_queue.json").write_text(json.dumps(boot))
    items = rq.all_repair_items()
    # static findings come after run failures, whatever their size; a row once (the desync wins)
    assert [(i["check"], i["target_rva"]) for i in items] == [
        ("tail", "0x00001000"), ("desync", "0x00001080"), ("boot-crash", "0x00003100"),
        ("truncated-table", "0x00002000"), ("inline-data", "0x00003000")]
    assert items[1]["pass_test"].startswith("python3 tools/game_smoke.py determinism")
    assert "--only truncated-table" in items[3]["pass_test"]
    assert "boot_smoke.py --game-dir SANDBOX --overlay rva:0x00003100" in items[2]["pass_test"]
    assert items[1]["queue"].endswith("desync_queue.json")
    # one path: that queue alone
    assert [i["check"] for i in rq.boot_items(tmp_path / "build/game/desync_queue.json")] == ["desync"]


def test_game_smoke_queue_items_round_trip(tmp_path):
    """What game_smoke.desync_items writes is what repair_queue serves."""
    import json
    pytest.importorskip("capstone")
    try:
        import game_smoke
    except (ImportError, SystemExit) as e:
        pytest.skip(f"game_smoke not importable: {e}")
    rq, rev, src = load(tmp_path, "bfme2", LEDGER)
    rows = [{"target_rva": "0x00001080", "name": "?b@Loco@@QAEXXZ", "source": "Code/GameEngine/Loco.cpp",
             "target_size": "64"}]
    path = tmp_path / "desync_queue.json"
    path.write_text(json.dumps({"tool": "game_smoke", "items": game_smoke.desync_items(rows, "desync", "--overlay closed --relayout")}))
    rq.DESYNC_QUEUE = str(path)
    (item,) = rq.boot_items()
    assert (item["check"], item["function"], item["size"]) == ("desync", "?b@Loco@@QAEXXZ", 64)
    assert "game_smoke.py determinism --image one" in item["pass_test"]
