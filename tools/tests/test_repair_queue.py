"""repair_queue: gate-debt and link-cycle repairs carry their check and a machine pass
test; new matches are told which unit they belong in (never a fresh one-function file)."""
import importlib
import json
import os
import random
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


@pytest.fixture(autouse=True)
def no_origin(tmp_path_factory, monkeypatch):
    """No test here reaches this checkout's origin (item 8): claims start in a directory
    with no repository, so a fetch fails at once; tests that need one set up a bare origin."""
    import claims
    monkeypatch.setattr(claims, "ROOT", tmp_path_factory.mktemp("no-origin"))
    claims.active.cache_clear()
    claims.mirrored.cache_clear()


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


def test_dest_routes_to_the_approved_tu_before_neighbouring_files(tmp_path):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, [
        ("reverse/tu_map.csv",
         "rva,size,kind,tu,confidence,by,evidence,source\n"
         "0x00001000,64,code,Code/GameEngine/Locomotor.cpp,approved,Z,,Code/GameEngine/Loco.cpp\n"
         "0x00001040,64,code-unledgered,Code/GameEngine/Locomotor.cpp,approved,C,,\n"
         "0x00001080,64,code,Code/GameEngine/Locomotor.cpp,approved,Z,,Code/GameEngine/Loco.cpp\n"
         "0x00002000,32,code,Code/GameEngine/Body.cpp,proposed,N,,Code/GameEngine/Body.cpp\n")])
    got = rq.dest_tu(0x1040)                                                     # an unconverted function's row
    assert got["dest"] == "Code/GameEngine/Locomotor.cpp"
    assert got["basis"] == "approved TU in tu_map.csv (by C; the file does not exist yet: create it)"
    assert rq.dest_tu(0x1060)["dest"] == "Code/GameEngine/Locomotor.cpp"         # no row: inside 0x1040's body
    got = rq.dest_tu(0x1F00)                                                     # proposed only: neighbours
    assert got["dest"] == "Code/GameEngine/Body.cpp" and "nearest neighbour" in got["basis"]
    assert got["basis"].startswith("neighbour heuristic, no usable approved TU")


TURRET = [("?a@StateMachine@@QAEXXZ", 0x1000, 16, "GameEngine/Source/Common/StateMachineA.cpp"),
          ("?x@TurretAI@@QAEXXZ", 0x1040, 16, "GameEngine/Source/GameLogic/AI/TurretAI.cpp"),
          ("?b@StateMachine@@QAEXXZ", 0x1080, 16, "GameEngine/Source/Common/StateMachineB.cpp"),
          ("?rva000010C0@Rva000010C0@@QAEXXZ", 0x10C0, 16, "GameEngine/Source/Common/Rva000010C0.cpp"),
          ("?y@TurretAI@@QAEXXZ", 0x1100, 16, "GameEngine/Source/GameLogic/AI/TurretAIY.cpp")]
ZH = "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/"
TURRET_AI = "Code/GameEngine/Source/GameLogic/AI/TurretAI.cpp"
STATE_MACHINE = "Code/GameEngine/Source/Common/StateMachine.cpp"


def test_dest_never_routes_an_f_turretai_row_to_a_merged_statemachine_tu(tmp_path):
    # Retail interleaves StateMachine.cpp and TurretAI.cpp, and 0x10C0 pushes TurretAI.cpp's
    # __FILE__. The old cluster union renamed every TurretAI row StateMachine.cpp, approved
    # them, and dest said "create StateMachine.cpp" while TurretAI.cpp existed.
    rq, rev, _ = load(tmp_path, "bfme2", TURRET, [
        (TURRET_AI, "//\n"),
        (ZH + "Common/StateMachine.cpp", "void StateMachine::a()\n{\n}\nvoid StateMachine::b()\n{\n}\n"),
        (ZH + "GameLogic/AI/TurretAI.cpp", "void TurretAI::x()\n{\n}\nvoid TurretAI::y()\n{\n}\n"),
        ("reverse/string_xrefs.tsv", "C:\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\TurretAI.cpp\t0x10C4\n")])
    import tu_map
    (rev / "tu_map.csv").write_text(tu_map.render(tu_map.build(tu_map.Layout(tmp_path))), newline="\n")
    got = rq.dest_tu(0x10C0)
    assert got["dest"] == TURRET_AI and got["basis"].startswith("retail __FILE__ string at this address")
    for rva in (0x1040, 0x1048, 0x10C0, 0x10C8, 0x1100):
        assert rq.dest_tu(rva)["dest"] != STATE_MACHINE, hex(rva)


def test_dest_distrusts_a_stale_approval_its_own_anchors_contradict(tmp_path):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, [
        (TURRET_AI, "//\n"),
        ("reverse/tu_map.csv",
         "rva,size,kind,tu,confidence,by,evidence,source\n"
         f"0x00001000,64,code,{STATE_MACHINE},approved,Z,Z={STATE_MACHINE},\n"
         f"0x00001040,64,code,{STATE_MACHINE},approved,N,F={TURRET_AI},\n"          # old rules' mislabel
         f"0x00001080,64,code-unledgered,{STATE_MACHINE},approved,C,C=0x00001040..0x000010C0,\n"
         f"0x000010C0,64,code,{STATE_MACHINE},approved,Z,Z={STATE_MACHINE},\n")])
    got = rq.dest_tu(0x1040)                                       # its own __FILE__ string wins
    assert got["dest"] == TURRET_AI and f"contradicted by 0x00001040 F={TURRET_AI}" in got["basis"]
    got = rq.dest_tu(0x1080)                                       # C resting on that row: not trusted either
    assert got["dest"] != STATE_MACHINE and got["basis"].startswith("neighbour heuristic")
    got = rq.dest_tu(0x1000)                                       # an uncontested approval still routes
    assert got["dest"] == STATE_MACHINE and "create it" in got["basis"]


def test_dest_refuses_padding(tmp_path):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, [
        ("reverse/tu_map.csv",
         "rva,size,kind,tu,confidence,by,evidence,source\n"
         "0x00001000,60,code,Code/GameEngine/Locomotor.cpp,approved,Z,,Code/GameEngine/Loco.cpp\n"
         "0x00001080,64,code,Code/GameEngine/Locomotor.cpp,approved,Z,,Code/GameEngine/Loco.cpp\n")])
    import tu_map

    class Image:
        def read(self, rva, n):
            return bytes(0xCC if 0x103C <= a < 0x1040 else 0x55 for a in range(rva, rva + n))
    rq.tu_routes.cache_clear()
    m = tu_map.load(tmp_path)
    rq.tu_routes = lambda: (tu_map, m, tu_map.code_index(m, Image()))
    assert rq.dest_tu(0x103C) == {"dest": None, "basis": "retail padding (0xCC) inside no known body: "
                                                         "no function starts here"}
    got = rq.dest_tu(0x1040)                                       # where the next body starts
    assert got["dest"] == "Code/GameEngine/Locomotor.cpp" and got["basis"].startswith("approved TU")


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


@pytest.mark.parametrize("layout", ["bfme1", "bfme2"])
@pytest.mark.parametrize("error", [FileNotFoundError, PermissionError, KeyboardInterrupt])
def test_interrupted_pass_test_restores_baseline_bytes(tmp_path, monkeypatch, layout, error):
    rq, rev, _ = load(tmp_path, layout, LEDGER)
    if layout == "bfme1":
        path = rev / "body_guard_baseline.csv"
        line = "tail,0x00001000,?a@Loco@@QAEXXZ,tail mismatch"
        raw = ("check,target_rva,name,detail\r\n" + line + "\r\n"
               "strnul,0x00002000,?c@Body@@QAEXXZ,literal mismatch\n").encode()
    else:
        path = rev / "gate_baseline.txt"
        line = "tail 0x00001000 ?a@Loco@@QAEXXZ"
        raw = ("# gate debt\r\n" + line + "\r\n"
               "strnul 0x00002000 ?c@Body@@QAEXXZ\n").encode()
    path.write_bytes(raw)

    def interrupted_build(*args, **kwargs):
        # The checker must see the debt removed, but that removal is provisional.
        assert line.encode() not in path.read_bytes()
        raise error("build did not complete")

    monkeypatch.setattr(rq.subprocess, "run", interrupted_build)
    with pytest.raises(error, match="build did not complete"):
        rq.pass_test(line)
    assert path.read_bytes() == raw


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
    assert rq.verify_removed(fail)                                        # staged sources need the same gate, too


def test_the_default_order_is_repair_link_data_header_identity_then_new_matches():
    """Every pick, no rotation: each queue is served only once every queue above it is empty."""
    import next_work
    one = lambda name: [{"function": name, "target_rva": "0x1", "size": 4}]   # noqa: E731
    queues = {"repair": one("r"), "link": one("l"), "data": one("d"), "header": one("h"), "identity": one("i")}
    named, packets = one("n"), one("p")
    expected = ["gate-debt repair", "link-cycle repair", "data-identity debt", "class-header adoption",
                "code-identity debt", "Zero Hour work packet", "reloc-named unclaimed function"]
    got = []
    while True:
        label, picked = next_work.selected_queue(None, [], [], [], [], named, packets, **queues)
        got.append(label)
        if label == "Zero Hour work packet":
            packets = []
        elif label == "reloc-named unclaimed function":
            break
        else:
            name = next(k for k, v in queues.items() if v is picked)
            queues[name] = []
    assert got == expected
    assert next_work.selected_queue(None, [], [], [], [], [])[0] == next_work.EMPTY_LABEL
    assert not hasattr(rq_module(), "repair_turn")                       # the 1-in-3 cap is gone
    for tier, label in (("data", "data-identity debt"), ("header", "class-header adoption"),
                        ("identity", "code-identity debt")):
        assert next_work.selected_queue(tier, [], [], [], [], named, **{tier: one(tier)})[0] == label


def rq_module():
    import repair_queue
    return repair_queue


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


# ---- link-cycle bundles (tools/cycle_artifacts.py) and gzip status files

RICH_STATUS = (CYCLE_STATUS.splitlines(True)[0] +
               "?ok@@YAXXZ,real,Code/a.cpp,0x00001000,64,0x00001000,1,,1,1,1,1,1,0,0,\n"
               "?far@@YAXXZ,real,Code/a.cpp,0x00002000,500,0x007BBD80,0,retail start violates section alignment,"
               "1,1,1,1,0,0,0,\n"
               "?wire@@YAXXZ,real,Code/b.cpp,0x00003000,40,0x00003000,1,,0,0,0,0,0,0,1,data-back:g_x\n"
               "?big@@YAXXZ,real,Code/c.cpp,0x00005000,90,0x00005000,1,,0,0,0,0,0,0,2,data-fwd:g_y;eh\n"
               "?gen@@YAXXZ,gen-funclet,Code/gen_small/u.cpp,0x00004000,9,,0,not COMDAT,0,0,0,0,0,0,0,\n")
GOLDEN = {  # tools/repair_queue.py at 9897d8f693 (before --bundle), on these fixtures; the census
            # entries since gained the unit-link check, the file: claim and the freshness note
    'cycle': (0,
        '1 row(s) from the local link cycle <root>/build/link_cycle/link_status.csv (commit f00dfeedbe, written <when>)\n'
        '      40B  0x00003000 ?wire@@YAXXZ\n'
        '         Code/b.cpp: data-back:g_x\n'
        '         pass test: python3 tools/link_cycle.py --measure-only: this row placed=1 self_strict=1\n',
        ''),
    'census': (0,
        '2 unit(s) that do not link, from the committed link census reverse/link_status.csv (measured at commit '
        '086d0a7aaa, 2026-10-07 21:52 UTC); freshness not checked: census commit 086d0a7aaa is not in this clone\n'
        '      32B unit-link 0x00002000 ?c@Body@@QAEXXZ  [claims file:Code/GameEngine/Body.cpp]\n'
        '         Code/GameEngine/Body.cpp: unit does not link (1 matched row(s)): unresolved 1\n'
        '         pass test: python3 tools/link_check.py Code/GameEngine/Body.cpp: LINKS (the next census: linked=yes)\n'
        '     128B unit-link 0x00001000 ?a@Loco@@QAEXXZ  [claims file:Code/GameEngine/Loco.cpp]\n'
        '         Code/GameEngine/Loco.cpp: unit does not link (2 matched row(s)): unresolved 2, comdat_losers 1\n'
        '         pass test: python3 tools/link_check.py Code/GameEngine/Loco.cpp: LINKS (the next census: linked=yes)\n',
        ''),
    'census_limit': (0,
        '2 unit(s) that do not link, from the committed link census reverse/link_status.csv (measured at commit '
        '086d0a7aaa, 2026-10-07 21:52 UTC); freshness not checked: census commit 086d0a7aaa is not in this clone\n'
        '      32B unit-link 0x00002000 ?c@Body@@QAEXXZ  [claims file:Code/GameEngine/Body.cpp]\n'
        '         Code/GameEngine/Body.cpp: unit does not link (1 matched row(s)): unresolved 1\n'
        '         pass test: python3 tools/link_check.py Code/GameEngine/Body.cpp: LINKS (the next census: linked=yes)\n',
        ''),
    'named': (0,
        '3 row(s) from the local link cycle <root>/s/link_status.csv (commit unknown (no receipt.json), written <when>)\n'
        '      90B  0x00005000 ?big@@YAXXZ\n'
        '         Code/c.cpp: data-fwd:g_y;eh\n'
        '         pass test: python3 tools/link_cycle.py --measure-only: this row placed=1 self_strict=1\n'
        '      40B  0x00003000 ?wire@@YAXXZ\n'
        '         Code/b.cpp: data-back:g_x\n'
        '         pass test: python3 tools/link_cycle.py --measure-only: this row placed=1 self_strict=1\n'
        '     500B  0x00002000 ?far@@YAXXZ\n'
        '         Code/a.cpp: retail start violates section alignment\n'
        '         pass test: python3 tools/link_cycle.py --measure-only: this row placed=1 self_strict=1\n',
        ''),
    'repair': (0,
        '2 baseline line(s), plus tier C / diffexec / boot, game and static queues\n'
        '      64B tail 0x00001000 ?a@Loco@@QAEXXZ\n'
        "         Code/GameEngine/Loco.cpp: compiled bytes past the row's extent differ from retail; fix the tail (or "
        "the extent)\n"
        "         pass test: python3 tools/repair_queue.py pass-test 'tail 0x00001000 ?a@Loco@@QAEXXZ'\n"
        '      32B ltable 0x00002000 ?c@Body@@QAEXXZ\n'
        '         Code/GameEngine/Body.cpp: a jump-table entry or same-section pointer lands on the wrong case; fix the '
        'case mapping\n'
        "         pass test: python3 tools/repair_queue.py pass-test 'ltable 0x00002000 ?c@Body@@QAEXXZ'\n",
        ''),
    'none': (1,
        '',
        'repair_queue: no link status: no link-cycle status at <root>/build/link_cycle/link_status.csv (run '
        'tools/link_cycle.py) and no committed census at reverse/link_status.csv with a '
        'reverse/link_census_history.csv row\n'),
}


def _main(rq, argv, capsys, root, when=None):
    code = rq.main(argv)
    got = capsys.readouterr()

    def norm(text):
        text = text.replace(str(root), "<root>").replace("\\", "/")
        return text.replace(when, "<when>") if when else text
    return code, norm(got.out), norm(got.err)


def test_link_and_repair_output_without_a_bundle_is_unchanged(tmp_path, monkeypatch, capsys):
    """The --bundle path changes nothing when it is not used: these fixtures give, byte for
    byte, the output the tool gave before it existed (GOLDEN)."""
    import time
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    root = tmp_path / "a"
    _cycle(root, CENSUS_TIME + 3600, commit="f00dfeedbeef0123")
    rq, _, _ = load(root, "bfme2", LEDGER, CENSUS_FILES)
    assert _main(rq, ["link"], capsys, root, time.ctime(CENSUS_TIME + 3600)) == GOLDEN["cycle"]
    root = tmp_path / "b"
    rq, _, _ = load(root, "bfme2", LEDGER, CENSUS_FILES)
    rq.changed_since = lambda commit: None                               # the fixture is no clone
    assert _main(rq, ["link"], capsys, root) == GOLDEN["census"]
    assert _main(rq, ["link", "--limit", "1"], capsys, root) == GOLDEN["census_limit"]
    root = tmp_path / "c"
    (root / "s").mkdir(parents=True)
    (root / "s/link_status.csv").write_text(RICH_STATUS, newline="\n")
    monkeypatch.setenv("REPAIR_LINK_STATUS", str(root / "s/link_status.csv"))
    rq, _, _ = load(root, "bfme2", LEDGER, [("reverse/gate_baseline.txt",
                                             "tail 0x00001000 ?a@Loco@@QAEXXZ\nltable 0x00002000 ?c@Body@@QAEXXZ\n")])
    monkeypatch.delenv("REPAIR_LINK_STATUS")
    when = time.ctime((root / "s/link_status.csv").stat().st_mtime)
    assert _main(rq, ["link", "--limit", "3"], capsys, root, when) == GOLDEN["named"]
    assert _main(rq, ["repair"], capsys, root) == GOLDEN["repair"]
    root = tmp_path / "d"
    rq, _, _ = load(root, "bfme2", LEDGER)
    assert _main(rq, ["link"], capsys, root) == GOLDEN["none"]


def test_link_items_read_a_gzip_status(tmp_path, monkeypatch, capsys):
    import gzip
    rq, _, _ = load(tmp_path, "bfme2", LEDGER)
    plain, packed = tmp_path / "link_status.csv", tmp_path / "link_status.csv.gz"
    plain.write_text(RICH_STATUS, newline="\n")
    with gzip.open(packed, "wb") as f:
        f.write(plain.read_bytes())
    items, _ = rq.link_items(plain)
    assert [i["function"] for i in items] == ["?big@@YAXXZ", "?wire@@YAXXZ", "?far@@YAXXZ"]
    assert rq.link_items(packed)[0] == items
    monkeypatch.setenv("REPAIR_LINK_STATUS", str(packed))
    rq, _, _ = load(tmp_path / "named", "bfme2", LEDGER)
    monkeypatch.delenv("REPAIR_LINK_STATUS")
    assert rq.main(["link"]) == 0 and "3 row(s) from the local link cycle" in capsys.readouterr().out


def _fixtures():
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    import cycle_artifacts as ca
    import cycle_fixture as cf
    import test_cycle_artifacts as tc
    return ca, cf, tc


def _checkout(root):
    """ROOT measures link-cycle-2: the rules a served bundle must positively match."""
    (root / "tools").mkdir(parents=True, exist_ok=True)
    (root / "tools/link_cycle.py").write_text('SHADOW_RULES = ["data-fold-1"]\nCANON_RULES = "coff-canon-1"\n'
                                              'receipt = dict(tool="link_cycle", rules="link-cycle-2")\n')


def _bundle(tmp_path, date_utc=None, **kw):
    ca, cf, _ = _fixtures()
    out = tmp_path / "bundle"
    kw.setdefault("rank_files", True)
    cf.bundle(cf.make_run(tmp_path / "snaps", date_utc=date_utc or cf.recent(), **kw), out, "laptop/watchdog")
    return out


def _closure_bundle(tmp_path, **kw):
    _, cf, _ = _fixtures()
    kw.setdefault("closure", True)
    return _bundle(tmp_path, status=cf.CLOSURE_STATUS, **kw)


def _store(tmp_path, *bundles):
    """BUNDLES published on a fake GitHub (in the order given) and fetched into a store."""
    ca, _, tc = _fixtures()
    gh = tc.FakeGitHub()
    for n, b in enumerate(bundles):
        tc.released(gh, b, "2026-10-12T00:%02d:00Z" % n)
    store = tmp_path / "store"
    ca.fetch(tc.REPO, store, gh=gh)
    return store


def test_link_tier_reads_a_published_bundle_from_the_store(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    store = _store(tmp_path, _bundle(tmp_path))
    root = tmp_path / "root"
    _cycle(root, CENSUS_TIME + 3600, commit="f00dfeedbeef0123")           # a local cycle and a census: unused
    rq, _, _ = load(root, "bfme2", LEDGER, CENSUS_FILES)
    _checkout(root)
    assert rq.main(["link", "--bundle", str(store)]) == 0
    got = capsys.readouterr()
    head, *rows = got.out.splitlines()
    assert head.startswith("3 row(s) from link-cycle bundle link-cycle/275a758e4cbb-")
    assert "1.0 h ago; authenticated publication; ancestry unknown" in head and "STALE" not in head
    assert "census" not in got.out and "local link cycle" not in got.out and got.err == ""
    assert [r.split()[2] for r in rows if r.lstrip()[0].isdigit()] == ["?wire@@YAXXZ", "?nul@@YAXXZ", "?far@@YAXXZ"]


def test_a_stale_bundle_is_refused_with_its_reason_unless_allowed(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    store = _store(tmp_path, _bundle(tmp_path, "2026-01-01 00:00:00"))
    root = tmp_path / "root"
    _cycle(root, CENSUS_TIME + 3600, commit="f00dfeedbeef0123")
    rq, _, _ = load(root, "bfme2", LEDGER, CENSUS_FILES)
    _checkout(root)
    assert rq.main(["link", "--bundle", str(store)]) == 4                  # stale: refused, nothing served
    got = capsys.readouterr()
    assert got.out == "" and "link-cycle bundle refused [reason=stale]:" in got.err and "--allow-stale" in got.err
    assert rq.main(["link", "--bundle", str(store), "--allow-stale"]) == 0
    got = capsys.readouterr()
    head = got.out.splitlines()[0]
    assert "measured 2026-01-01T00:00:00Z UTC" in head and ", STALE;" in head
    assert "repair_queue: STALE: measured" in got.err
    ca, _, _ = _fixtures()
    items, note, warnings = rq.bundle_link_items(store, now=ca.parse_utc("2026-01-01 01:00:00"))
    assert len(items) == 3 and warnings == [] and "1.0 h ago" in note and "STALE" not in note


def test_every_bundle_refusal_exits_with_its_own_reason_and_never_falls_back(tmp_path, monkeypatch, capsys):
    """An orchestrator routes on the exit code or on `[reason=...]`, not on prose."""
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    root = tmp_path / "root"
    _cycle(root, CENSUS_TIME + 3600, commit="f00dfeedbeef0123")           # a local cycle and a census exist
    rq, _, _ = load(root, "bfme2", LEDGER, CENSUS_FILES)

    def refused(argv, code, reason, text):
        assert rq.main(["link", *argv]) == code
        got = capsys.readouterr()
        assert got.out == "" and f"[reason={reason}]" in got.err and text in got.err, got.err
    fresh = _bundle(tmp_path / "fresh")
    # this checkout's rules cannot be read: compatibility is not established, whatever is allowed
    for extra in ([], ["--allow-stale"]):
        refused(["--bundle", str(fresh), "--local-unpublished", *extra], 5, "incompatible-rules", "RULES UNKNOWN")
    _checkout(root)
    refused(["--bundle", str(tmp_path / "missing")], 2, "unavailable", "no bundle at")
    refused(["--bundle", str(fresh)], 6, "unauthenticated", "has no fetch evidence")
    rules = _bundle(tmp_path / "rules", rules="link-cycle-3")
    for extra in ([], ["--allow-stale"], ["--closure"]):
        refused(["--bundle", str(rules), "--local-unpublished", *extra], 5, "incompatible-rules",
                "RULES MISMATCH: measured under link-cycle-3")
    stale = _bundle(tmp_path / "stale", "2026-01-01 00:00:00")
    refused(["--bundle", str(stale), "--local-unpublished"], 4, "stale", "STALE: measured")
    refused(["--bundle", str(fresh), "--local-unpublished", "--closure"], 7, "no-closure-report",
            "carries no closure report (published diagnostic-only")
    (fresh / "link_status.csv.gz").write_bytes(b"not the measured rows")
    refused(["--bundle", str(fresh), "--local-unpublished"], 1, "corrupt", "invalid [reason=corrupt]: member "
                                                                          "link_status.csv.gz")
    assert rq.main(["link", "--closure"]) == 1                             # no bundle: no local or census fallback
    got = capsys.readouterr()
    assert got.out == "" and "need --bundle STORE" in got.err


def test_a_local_unpublished_bundle_is_served_only_on_request_and_labelled(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    bundle = _bundle(tmp_path)
    root = tmp_path / "root"
    rq, _, _ = load(root, "bfme2", LEDGER)
    _checkout(root)
    assert rq.main(["link", "--bundle", str(bundle), "--local-unpublished"]) == 0
    got = capsys.readouterr()
    assert "; UNAUTHENTICATED LOCAL BUNDLE; " in got.out.splitlines()[0]
    assert "repair_queue: UNAUTHENTICATED LOCAL BUNDLE (--local-unpublished)" in got.err


# ---- closure roots from a bundle (tools/closure_report.py): link --closure

def test_link_closure_serves_roots_by_conditional_gain_with_their_limits(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    store = _store(tmp_path, _closure_bundle(tmp_path))
    root = tmp_path / "root"
    _cycle(root, CENSUS_TIME + 3600, commit="f00dfeedbeef0123")           # a local cycle and a census: unused
    rq, _, _ = load(root, "bfme2", LEDGER, CENSUS_FILES)
    _checkout(root)
    assert rq.main(["link", "--closure", "--bundle", str(store), "--limit", "1"]) == 0
    got = capsys.readouterr()
    lines = got.out.splitlines()
    assert lines[0].startswith("2 closure root(s) with a gain from link-cycle bundle link-cycle/275a758e4cbb-")
    assert "authenticated publication" in lines[0]
    assert lines[1] == "  graph: measured graph, bound to the receipt"
    assert "credit 64 B" in lines[2] and "64 B fail their own checks" in lines[2]
    assert "46 B are self-strict but closure-blocked; closed-strict but not placed: 500 B" in lines[2]
    assert lines[3].startswith("  COVERAGE: single roots cover only 30 B of the 46 B closure bucket (65.2%); 16 B sit "
                               "behind two or more roots and 0 B behind one filler or unknown target")
    assert lines[3].endswith("1 of the 2 roots unblock only their own failing rows.")
    assert "CONDITIONAL single-address gain = credit(graph with every failed node at that retail address passing) " \
           "- credit(graph)" in lines[4]
    assert lines[5].startswith("  limits: conditional on the frozen graph") and "not a repair proof" in lines[5]
    assert "do not add them" in lines[5] and "never ranked" in lines[5] and "not its cause or its repair site" in lines[5]
    assert lines[6].split() == ["70B", "closure", "0x00003000", "?wire@@YAXXZ"]
    assert lines[7].strip().startswith("Code/b.cpp: beneficiaries 1 row(s) 30 B + own failing rows 1 / 40 B; 1 "
                                       "failed node(s) at this address; 2 failure(s) to clear: data-back:")
    assert "no longer lists root 0x00003000 and its rows are closed_strict=1" in lines[8]
    assert len(lines) == 9 and "census" not in got.out and "local link cycle" not in got.out
    items, notes, _ = rq.closure_items(store)
    assert [(i["target_rva"], i["size"]) for i in items] == [("0x00003000", 70), ("0x00004000", 24)]


def test_the_closure_queue_says_when_its_graph_is_a_replay(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    store = _store(tmp_path, _closure_bundle(tmp_path, closure="replay"))
    root = tmp_path / "root"
    rq, _, _ = load(root, "bfme2", LEDGER)
    _checkout(root)
    assert rq.main(["link", "--closure", "--bundle", str(store), "--limit", "1"]) == 0
    assert capsys.readouterr().out.splitlines()[1] == (
        "  graph: replayed, graph not receipt-bound: the edges were rebuilt after the run, not written by its measure")


def test_the_closure_queue_keeps_its_last_bundle_when_a_newer_one_has_no_report(tmp_path, monkeypatch, capsys):
    """A measurement published without a closure report does not silently disable the queue:
    it serves the newest bundle that has one, and says which and why."""
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    ca, cf, _ = _fixtures()
    ready = _closure_bundle(tmp_path / "ready", date_utc=cf.recent(6), commit=cf.OTHER)
    bare = _bundle(tmp_path / "bare", cf.recent(1))
    store = _store(tmp_path, ready, bare)
    root = tmp_path / "root"
    rq, _, _ = load(root, "bfme2", LEDGER)
    _checkout(root)
    assert rq.main(["link", "--bundle", str(store), "--limit", "0"]) == 0
    assert "link-cycle bundle link-cycle/275a758e4cbb-" in capsys.readouterr().out      # the newest measurement
    assert rq.main(["link", "--closure", "--bundle", str(store), "--limit", "1"]) == 0
    got = capsys.readouterr()
    assert "link-cycle bundle link-cycle/31d8b0fddd01-" in got.out.splitlines()[0] and "6.0 h ago" in got.out
    assert "repair_queue: NOT THE NEWEST MEASUREMENT: serving link-cycle/31d8b0fddd01-" in got.err
    assert "was published without one (published diagnostic-only" in got.err
    lone = _store(tmp_path / "lone", bare)
    assert rq.main(["link", "--closure", "--bundle", str(lone)]) == 7
    got = capsys.readouterr()
    assert got.out == "" and "[reason=no-closure-report]" in got.err and "nothing else is served in its place" in got.err


def test_a_corrupted_closure_report_and_one_of_another_algorithm_are_refused(tmp_path, monkeypatch, capsys):
    import gzip
    import hashlib
    import json
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    root = tmp_path / "root"
    rq, _, _ = load(root, "bfme2", LEDGER)
    _checkout(root)
    corrupt = _closure_bundle(tmp_path / "corrupt")
    data = bytearray((corrupt / "closure_roots.json.gz").read_bytes())
    data[len(data) // 2] ^= 1
    (corrupt / "closure_roots.json.gz").write_bytes(bytes(data))
    assert rq.main(["link", "--closure", "--bundle", str(corrupt), "--local-unpublished"]) == 1
    got = capsys.readouterr()
    assert got.out == "" and "invalid [reason=corrupt]: member closure_roots.json.gz: sha256" in got.err
    bundle = _closure_bundle(tmp_path / "algo")
    path = bundle / "closure_roots.json.gz"
    doc = json.loads(gzip.decompress(path.read_bytes()))
    doc["algorithm"] = "affected-bytes/1"
    raw = json.dumps(doc).encode()
    path.write_bytes(gzip.compress(raw))
    manifest = json.loads((bundle / "manifest.json").read_text())
    manifest["members"][path.name].update(sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
                                          size=path.stat().st_size,
                                          content_sha256=hashlib.sha256(raw).hexdigest(), content_size=len(raw))
    manifest["components"]["closure_report"]["algorithm"] = "affected-bytes/1"     # a self-consistent other ranking
    (bundle / "manifest.json").write_text(json.dumps(manifest))
    assert rq.main(["link", "--closure", "--bundle", str(bundle), "--local-unpublished"]) == 5
    got = capsys.readouterr()
    assert got.out == "" and "[reason=incompatible-rules]" in got.err and "algorithm 'affected-bytes/1'" in got.err


# ---- a stale census: units changed since its commit are re-predicted before they are served

FRESH_STATUS = (CENSUS_STATUS + "Code/Gone.cpp,no,1,0,0,0,0\n" + "Code/Rehomed.cpp,no,1,0,0,0,0\n")
FRESH_FILES = [("reverse/link_status.csv", FRESH_STATUS), ("reverse/link_census_history.csv", CENSUS_HISTORY),
               ("reverse/symbols.csv", "name,rva\n"),
               ("Code/GameEngine/Loco.cpp", "//\n"), ("Code/GameEngine/Body.cpp", "//\n"),
               ("Code/Rehomed.cpp", "//\n")]


def test_census_units_changed_since_the_census_are_re_predicted(tmp_path, monkeypatch):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, FRESH_FILES)
    asked = []
    monkeypatch.setattr(rq, "changed_since", lambda commit: {"Code/GameEngine/Loco.cpp", "Code/GameEngine/Body.cpp"}
                        if commit == "086d0a7aaa" else None)

    def predict(sources, commit):
        assert commit == "086d0a7aaa"
        asked.extend(sources)
        return {"Code/GameEngine/Loco.cpp": (True, "LINKS"),
                "Code/GameEngine/Body.cpp": (None, "no object built for it (./build.sh Code/GameEngine/Body.cpp)")}
    monkeypatch.setattr(rq, "link_predictions", predict)
    items, note = rq.link_items()
    assert sorted(asked) == ["Code/GameEngine/Body.cpp", "Code/GameEngine/Loco.cpp"]
    assert [i["source"] for i in items] == ["Code/GameEngine/Body.cpp"]          # Loco proven LINKS: dropped
    assert "no link_check verdict, kept: no object built" in items[0]["why"]     # said, never guessed
    assert "1 proven LINKS and dropped, 0 still do not link, 1 kept with no verdict" in note
    assert "1 census unit(s) whose source no longer exists, not served: Code/Gone.cpp" in note
    assert "1 census unit(s) whose source holds no matched row now (re-homed?), not served: Code/Rehomed.cpp" in note
    monkeypatch.setattr(rq, "link_predictions", lambda sources, commit: {s: (False, "unresolved 1") for s in sources})
    items, note = rq.link_items()
    assert [i["source"] for i in items] == ["Code/GameEngine/Body.cpp", "Code/GameEngine/Loco.cpp"]
    assert all("link_check now: does not link (unresolved 1)" in i["why"] for i in items)
    assert all(i["claim"] == [f"file:{i['source']}"] for i in items)
    monkeypatch.setattr(rq, "changed_since", lambda commit: set())                # nothing changed: no prediction
    monkeypatch.setattr(rq, "link_predictions", lambda *a: pytest.fail("predicted an unchanged unit"))
    items, _ = rq.link_items()
    assert len(items) == 2 and all("unchanged since the census" in i["fresh"] for i in items)


def test_a_header_change_marks_the_units_that_include_it(tmp_path, monkeypatch):
    """A unit whose own source is untouched but whose recorded header changed is not
    'unchanged': it is re-predicted; one with no build receipt is labelled honestly."""
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, FRESH_FILES)
    monkeypatch.setattr(rq, "changed_since", lambda commit: {"Code/Include/Shared.h"})
    monkeypatch.setattr(rq, "unit_deps", lambda source: {"Code/Include/Shared.h", "Code/Other.h"}
                        if source.endswith("Loco.cpp") else None)
    asked = []
    monkeypatch.setattr(rq, "link_predictions", lambda sources, commit: asked.extend(sources) or
                        {s: (None, "a changed provider has no current object") for s in sources})
    items, note = rq.link_items()
    by = {i["source"]: i for i in items}
    assert asked == ["Code/GameEngine/Loco.cpp"]
    assert by["Code/GameEngine/Loco.cpp"]["fresh"].startswith("1 header(s) it includes changed since the census")
    assert "own source unchanged since the census; its headers unchecked" in by["Code/GameEngine/Body.cpp"]["fresh"]
    assert len(items) == 2                                                       # nothing proven: both kept
    assert "1 unit(s) have no build receipt" in note


def _index(path, commit="086d0a7aaa", census_commit=None):
    import pickle
    meta = {"date": "2026-10-07 21:52", "commit": commit}
    if census_commit:
        meta["census_commit"] = census_commit
    path.write_bytes(pickle.dumps({"meta": meta, "blockers": {}, "objects": []}))


def _predict_env(tmp_path, monkeypatch, rq, current, moved, links=True):
    """link_predictions over fixture objects: `current` are the units whose object
    link_census.object_current proves current; check_object says LINKS (or not)."""
    import build
    import link_census
    import link_check
    monkeypatch.setenv("BFME_PICKER_CACHE", str(tmp_path / "cache"))
    monkeypatch.setattr(link_check, "INDEX", tmp_path / "link_index.pkl")
    objs = tmp_path / "objs"
    objs.mkdir(exist_ok=True)
    monkeypatch.setattr(build, "obj_path", lambda source: objs / (Path(source).stem + ".obj"))
    for name in ("Loco", "Body"):
        (objs / f"{name}.obj").write_bytes(name.encode())
    fresh_flags = []

    def object_current(source, obj, allow_fresh=True, **_):
        fresh_flags.append(allow_fresh)
        return Path(source).as_posix().endswith(tuple(current))
    monkeypatch.setattr(link_census, "object_current", object_current)
    monkeypatch.setattr(link_census, "ledger", lambda: [
        {"source": "Code/GameEngine/Loco.cpp"}, {"source": "Code/GameEngine/Body.cpp"}])
    monkeypatch.setattr(link_census, "RetailTruth", lambda rows: None)
    monkeypatch.setattr(rq, "changed_since", lambda commit: set(moved))
    monkeypatch.setattr(rq, "ledger_units_at", lambda commit: rq.units_of(link_census.ledger()))   # unchanged
    monkeypatch.setattr(link_check, "forget", lambda index, names: None)
    loads, refreshed = [], []
    monkeypatch.setattr(link_check, "load_index", lambda: loads.append(1) or {"objects": ["Loco.obj", "Body.obj"]})
    monkeypatch.setattr(link_check, "require_common_index", lambda index: None)
    monkeypatch.setattr(link_check, "in_census", lambda index, name: name in index["objects"])
    monkeypatch.setattr(link_check, "refresh", lambda index, objects, truth: refreshed.append(
        sorted(o.name for o in objects)))
    blockers = {k: [] for k in rq.LINK_BLOCKERS}
    if not links:
        blockers["unresolved"] = ["?gone@@YAXXZ"]
    monkeypatch.setattr(link_check, "check_object", lambda obj, index, truth, source: blockers)
    return loads, refreshed, fresh_flags


def test_an_index_of_another_census_commit_gives_no_verdict(tmp_path, monkeypatch):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, FRESH_FILES)
    loads, _, _ = _predict_env(tmp_path, monkeypatch, rq, current=("Loco.cpp", "Body.cpp"),
                               moved={"Code/GameEngine/Loco.cpp"})
    _index(tmp_path / "link_index.pkl", commit="1111111111")
    got = rq.link_predictions(["Code/GameEngine/Loco.cpp"], "086d0a7aaa")
    assert got["Code/GameEngine/Loco.cpp"][0] is None
    assert "measures commit 1111111111, the census 086d0a7aaa" in got["Code/GameEngine/Loco.cpp"][1]
    assert loads == []                                                          # never loaded, never checked
    _index(tmp_path / "link_index.pkl", commit="2222222222", census_commit="086d0a7aaa")   # an updated index
    assert rq.link_predictions(["Code/GameEngine/Loco.cpp"], "086d0a7aaa")["Code/GameEngine/Loco.cpp"][0] is True


def test_a_changed_provider_without_a_current_object_keeps_the_unit(tmp_path, monkeypatch):
    """Body.cpp (a provider) changed -- say it removed a definition Loco.cpp uses. Its old
    definitions are still in the index, so a check of Loco.cpp alone would say LINKS
    falsely. With no current Body object there is no verdict, and the unit is kept."""
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, FRESH_FILES)
    moved = {"Code/GameEngine/Loco.cpp", "Code/GameEngine/Body.cpp"}
    loads, refreshed, fresh = _predict_env(tmp_path, monkeypatch, rq, current=("Loco.cpp",), moved=moved)
    _index(tmp_path / "link_index.pkl")
    got = rq.link_predictions(["Code/GameEngine/Loco.cpp"], "086d0a7aaa")
    assert got["Code/GameEngine/Loco.cpp"][0] is None and "Body.cpp" in got["Code/GameEngine/Loco.cpp"][1]
    assert loads == [] and set(fresh) == {False}                               # never a fresh preprocess
    # census_items keeps it, with the reason
    monkeypatch.setattr(rq, "changed_since", lambda commit: moved)
    items, note = rq.census_items(tmp_path / "reverse/link_status.csv", "086d0a7aaa")
    assert "Code/GameEngine/Loco.cpp" in [i["source"] for i in items]
    assert "kept with no verdict" in "; ".join(note)
    # once Body's object is current too, both are refreshed into the index before the check
    loads, refreshed, _ = _predict_env(tmp_path, monkeypatch, rq, current=("Loco.cpp", "Body.cpp"), moved=moved)
    got = rq.link_predictions(["Code/GameEngine/Loco.cpp"], "086d0a7aaa")
    assert got["Code/GameEngine/Loco.cpp"] == (True, "LINKS")
    assert refreshed == [["Body.obj", "Loco.obj"]] and loads == [1]
    # the verdict is cached by object digest: a second pick loads nothing
    rq.link_predictions(["Code/GameEngine/Loco.cpp"], "086d0a7aaa")
    assert loads == [1]
    (tmp_path / "objs" / "Body.obj").write_bytes(b"rebuilt")                   # a provider moved: re-checked
    rq.link_predictions(["Code/GameEngine/Loco.cpp"], "086d0a7aaa")
    assert loads == [1, 1]


def test_a_unit_deleted_since_the_index_gives_no_verdict(tmp_path, monkeypatch):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, FRESH_FILES)
    _predict_env(tmp_path, monkeypatch, rq, current=("Loco.cpp", "Body.cpp"),
                 moved={"Code/GameEngine/Loco.cpp", "Code/GameEngine/Removed.cpp"})
    _index(tmp_path / "link_index.pkl")
    got = rq.link_predictions(["Code/GameEngine/Loco.cpp"], "086d0a7aaa")
    assert got["Code/GameEngine/Loco.cpp"][0] is None and "Removed.cpp" in got["Code/GameEngine/Loco.cpp"][1]


def test_link_predictions_say_why_without_an_index(tmp_path, monkeypatch):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER)
    import link_check
    monkeypatch.setattr(link_check, "INDEX", tmp_path / "no_index.pkl")
    got = rq.link_predictions(["Code/GameEngine/Loco.cpp"], "086d0a7aaa")
    assert got == {"Code/GameEngine/Loco.cpp": (None, "no census index to predict against "
                                                      "(python3 tools/link_check.py --fetch-index)")}


def test_the_census_commit_is_used_only_for_the_committed_census(tmp_path, monkeypatch):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, FRESH_FILES)
    seen = []
    monkeypatch.setattr(rq, "census_items", lambda path, commit=None: seen.append(commit) or ([], []))
    monkeypatch.setattr(rq, "link_source", lambda path=None: ("census", tmp_path / "elsewhere.csv", "other file"))
    rq.link_items()
    monkeypatch.setattr(rq, "link_source", lambda path=None: ("census", tmp_path / "reverse/link_status.csv", "c"))
    rq.link_items()
    assert seen == [None, "086d0a7aaa"]


LOCO, BODY = "Code/GameEngine/Loco.cpp", "Code/GameEngine/Body.cpp"


def _predict(tmp_path, monkeypatch, current=("Loco.cpp", "Body.cpp"), moved=(LOCO,)):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, FRESH_FILES + [("Code/Include/Shared.h", "//\n")])
    env = _predict_env(tmp_path, monkeypatch, rq, current=current, moved=set(moved))
    _index(tmp_path / "link_index.pkl")
    return rq, env


def test_a_unit_without_a_build_receipt_is_a_provider_when_headers_moved(tmp_path, monkeypatch):
    """F02: Body.cpp has no receipt, so a moved header may be in it: it must be refreshed
    too, and with no current object there is no verdict."""
    rq, _ = _predict(tmp_path, monkeypatch, current=("Loco.cpp",), moved=("Code/Include/Shared.h",))
    monkeypatch.setattr(rq, "unit_deps", lambda source: {"Code/Include/Shared.h"} if source == LOCO else None)
    got = rq.link_predictions([LOCO], "086d0a7aaa")[LOCO]
    assert got[0] is None and "Body.cpp" in got[1]


def test_a_provider_outside_the_census_gives_no_verdict(tmp_path, monkeypatch):
    """F06: a changed unit the index has no place for cannot have its definitions refreshed."""
    import link_check
    rq, _ = _predict(tmp_path, monkeypatch, moved=(LOCO, BODY))
    monkeypatch.setattr(link_check, "load_index", lambda: {"objects": ["Loco.obj"]})
    got = rq.link_predictions([LOCO], "086d0a7aaa")[LOCO]
    assert got[0] is None and "not in the census" in got[1]


@pytest.mark.parametrize("what", ["object", "object same stamp", "source", "header", "currency"])
def test_anything_moving_while_it_is_checked_gives_no_verdict(tmp_path, monkeypatch, what):
    """F07 and item 5: an object rewritten, a provider's source or a recorded header edited,
    or an object no longer proven current, between the start of the check and its end."""
    import link_census
    import link_check
    rq, _ = _predict(tmp_path, monkeypatch, moved=(LOCO, BODY))
    monkeypatch.setattr(rq, "unit_deps", lambda source: {"Code/Include/Shared.h"})
    stale = []
    real_current = link_census.object_current
    monkeypatch.setattr(link_census, "object_current", lambda s, o, **k: not stale and real_current(s, o, **k))

    def check_object(obj, index, truth, source):
        target = {"object": tmp_path / "objs/Body.obj", "object same stamp": tmp_path / "objs/Body.obj",
                  "source": tmp_path / BODY,
                  "header": tmp_path / "Code/Include/Shared.h"}.get(what)
        if target:
            if what == "object same stamp":
                stamp = target.stat()
                target.write_bytes(b"new!")
                os.utime(target, ns=(stamp.st_atime_ns, stamp.st_mtime_ns))
            else:
                target.write_bytes(b"changed during the check")
        else:
            stale.append(1)
        return {k: [] for k in rq.LINK_BLOCKERS}
    monkeypatch.setattr(link_check, "check_object", check_object)
    got = rq.link_predictions([LOCO], "086d0a7aaa")[LOCO]
    assert got[0] is None and "moved while they were checked" in got[1], got


def test_an_unchanged_provider_edited_during_the_check_has_no_verdict(tmp_path, monkeypatch):
    import link_check
    rq, _ = _predict(tmp_path, monkeypatch, moved=(LOCO,))
    changed = {LOCO}
    monkeypatch.setattr(rq, "changed_since", lambda commit: set(changed))

    def check_object(obj, index, truth, source):
        changed.add(BODY)                  # Body was not among the initial refreshed objects
        return {kind: [] for kind in rq.LINK_BLOCKERS}

    monkeypatch.setattr(link_check, "check_object", check_object)
    verdict = rq.link_predictions([LOCO], "086d0a7aaa")[LOCO]
    assert verdict[0] is None and "changed source/header paths" in verdict[1]


def test_units_whose_ledger_rows_changed_since_the_index_are_forgotten_or_judged_unknown(tmp_path, monkeypatch):
    """Item 5: a unit the index's ledger held and the current one does not is forgotten
    before the check; a checked unit whose own rows changed gets no verdict; another
    unit whose rows changed must be refreshed like a changed source."""
    import link_census
    import link_check
    rq, _ = _predict(tmp_path, monkeypatch)
    rows = link_census.ledger()
    forgot = []
    monkeypatch.setattr(link_check, "forget", lambda index, names: forgot.append(sorted(names)))
    monkeypatch.setattr(rq, "ledger_units_at", lambda commit: dict(
        rq.units_of(rows), **{"Code/GameEngine/Dropped.cpp": frozenset({("?x@@YAXXZ", "0x9000", "8")})}))
    assert rq.link_predictions([LOCO], "086d0a7aaa")[LOCO] == (True, "LINKS")
    assert forgot == [["Dropped.obj"]]
    monkeypatch.setattr(rq, "ledger_units_at", lambda commit: dict(
        rq.units_of(rows), **{LOCO: frozenset({("?moved@@YAXXZ", "0x1000", "64")})}))
    got = rq.link_predictions([LOCO], "086d0a7aaa")[LOCO]
    assert got[0] is None and "ledger rows changed" in got[1]
    rq2, _ = _predict(tmp_path / "again", monkeypatch, current=("Loco.cpp",))
    monkeypatch.setattr(rq2, "ledger_units_at", lambda commit: dict(
        rq2.units_of(rows), **{BODY: frozenset({("?moved@@YAXXZ", "0x2000", "32")})}))
    got = rq2.link_predictions([LOCO], "086d0a7aaa")[LOCO]
    assert got[0] is None and "Body.cpp" in got[1]                          # rehomed provider, no current object


def test_a_cached_verdict_is_keyed_on_ledger_pins_and_index_content(tmp_path, monkeypatch):
    import link_census
    rq, (loads, _, _) = _predict(tmp_path, monkeypatch)
    assert rq.link_predictions([LOCO], "086d0a7aaa")[LOCO] == (True, "LINKS") and loads == [1]
    rq.link_predictions([LOCO], "086d0a7aaa")
    assert loads == [1]                                                      # cached
    (tmp_path / "reverse/symbols.csv").write_text("name,rva\n?p@@YAXXZ,0x10\n")
    rq.link_predictions([LOCO], "086d0a7aaa")
    assert loads == [1, 1]                                                   # a pin changed
    rows = [dict(r, notes="x") for r in link_census.ledger()]
    monkeypatch.setattr(link_census, "ledger", lambda: rows)
    rq.link_predictions([LOCO], "086d0a7aaa")
    assert loads == [1, 1, 1]                                                # the ledger changed
    with (tmp_path / "link_index.pkl").open("ab") as handle:
        handle.write(b"\0")                                                  # same meta, other content
    rq.link_predictions([LOCO], "086d0a7aaa")
    assert loads == [1, 1, 1, 1]
    digest = rq.digest_of
    monkeypatch.setattr(rq, "digest_of", lambda path: "changed picker" if str(path) == rq.__file__
                        else digest(path))
    rq.link_predictions([LOCO], "086d0a7aaa")
    assert loads == [1, 1, 1, 1, 1]                                           # the picker tool changed


def test_link_verdict_requires_readable_inputs_and_hashes_same_stamp_index(tmp_path, monkeypatch):
    import os
    import pickle
    rq, (loads, _, _) = _predict(tmp_path, monkeypatch)
    index = tmp_path / "link_index.pkl"
    stamp = index.stat()
    assert rq.link_predictions([LOCO], "086d0a7aaa")[LOCO] == (True, "LINKS")
    revised = pickle.loads(index.read_bytes())
    revised["meta"]["date"] = "2026-10-07 21:53"
    assert len(pickle.dumps(revised)) == stamp.st_size
    index.write_bytes(pickle.dumps(revised))
    os.utime(index, ns=(stamp.st_atime_ns, stamp.st_mtime_ns))
    rq.link_predictions([LOCO], "086d0a7aaa")
    assert len(loads) == 2                     # size and mtime are not a cache key
    (tmp_path / "reverse/symbols.csv").unlink()
    verdict = rq.link_predictions([LOCO], "086d0a7aaa")[LOCO]
    assert verdict[0] is None and "unreadable" in verdict[1]


# ---- data-identity, class-header and code-identity debt

def test_hook_rechecks_all_three_owned_debt_registers():
    hook = (TOOLS.parent / ".githooks/pre-commit").read_text(encoding="utf-8")
    arm = ("reverse/data_check_baseline.txt|reverse/code_identity_baseline.tsv|"
           "reverse/header_queue.tsv) baseline_changed=1 ;;")
    assert hook.count(arm) == 2


DEBT_FILES = [
    ("Code/GameEngine/Loco.cpp", "//\n"), ("Code/GameEngine/Body.cpp", "//\n"),
    ("reverse/data_check_baseline.txt",
     "# source\tcheck\tsymbol\taddress -- shrink-only; written by tools/data_check.py\n"
     "Code/GameEngine/Loco.cpp\twrong-name\t?g_00A00000@@3HA\t0x00A00000\n"
     "Code/GameEngine/Body.cpp\twrong-name\t?g_00A00000@@3HA\t0x00A00000\n"
     "Code/GameEngine/Body.cpp\tduplicate-def\t?TheX@@3HA\t0x00A00004\n"
     "Code/Gone.cpp\twrong-name\t?g@@3HA\t0x00A00000\n"),
    ("reverse/header_queue.tsv",
     "class\tsource\tretail_rvas\theader\tfailure\tretry_budget\tacceptance\n"
     "AsciiString\tCode/GameEngine/Loco.cpp\t0x00001000\tascii_string.h\terror C2248\t3\t"
     "python3 tools/header_adopt_lane.py accept --class AsciiString Code/GameEngine/Loco.cpp\n"
     "Coord3D\tCode/GameEngine/Body.cpp\t0x00002000\tCoord3D.h\tFAIL ?c@Body@@QAEXXZ\t3\t"
     "python3 tools/header_adopt_lane.py accept --class Coord3D Code/GameEngine/Body.cpp\n"
     "Coord3D\tCode/Gone.cpp\t0x00009000\tCoord3D.h\terror C2039\t3\tx\n"),
    ("reverse/code_identity_baseline.tsv",
     "# Wrong code bindings\n# mode: shadow\n"
     "Code/GameEngine/Loco.cpp\t?a@Loco@@QAEXXZ\t??1AsciiString@@QAE@XZ\t0x00002000\tdivergent\n"
     "Code/GameEngine/Body.cpp\t?c@Body@@QAEXXZ\t?f@@YAXXZ\t0x00001000\twrong\n"),
]


def test_debt_queues_serve_one_key_each_with_the_tools_verdict_as_pass_test(tmp_path, monkeypatch):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES)
    import data_ledger
    monkeypatch.setattr(data_ledger, "load", lambda path=None: {
        0xA00000: {"name": "?TheReal@@3HA", "source": ""}, 0xA00004: {"name": "?TheX@@3HA", "source": "Code/Own.cpp"}})
    items, note = rq.data_identity_items()
    assert [(i["check"], i["source"]) for i in items] == [
        ("vanished-source", "Code/Gone.cpp"),                              # a regression, first, never dropped
        ("duplicate-def", "Code/GameEngine/Body.cpp"),                     # a link blocker next
        ("wrong-name", "Code/GameEngine/Body.cpp"), ("wrong-name", "Code/GameEngine/Loco.cpp")]
    assert "Code/Own.cpp owns" in items[1]["why"] and "?TheReal@@3HA" in items[2]["why"]
    assert items[2]["baseline_line"] == "Code/GameEngine/Body.cpp\twrong-name\t?g_00A00000@@3HA\t0x00A00000"
    assert "repair_queue.py retire data Code/GameEngine/Body.cpp" in items[2]["pass_test"]
    assert "--write-baseline" not in items[2]["pass_test"] and "never by hand" in items[2]["pass_test"]
    assert items[2]["claim"] == ["file:Code/GameEngine/Body.cpp"]
    assert "served first as regressions (Code/Gone.cpp)" in note

    items, note = rq.header_items()
    assert [(i["check"], i["source"]) for i in items] == [
        ("vanished-source", "Code/Gone.cpp"),
        ("class-header", "Code/GameEngine/Body.cpp"), ("class-header", "Code/GameEngine/Loco.cpp")]
    assert items[1]["claim"] == ["class:Coord3D", "file:Code/GameEngine/Body.cpp", "file:Code/Gone.cpp"]
    assert "accept --class Coord3D Code/GameEngine/Body.cpp" in items[1]["pass_test"]
    assert items[1]["rank"] < items[2]["rank"]                              # DEPENDENCY_ORDER carried

    items, note = rq.identity_items()
    by_check = {i["check"]: i for i in items}
    assert by_check["divergent"]["claim"] == ["class:AsciiString"]
    assert by_check["wrong"]["claim"] == [] and by_check["wrong"]["target_rva"] == "0x00002000"
    assert "retire identity Code/GameEngine/Body.cpp" in by_check["wrong"]["pass_test"]
    assert "delete the line" not in by_check["wrong"]["pass_test"]


def test_debt_queues_skip_an_absent_file_with_a_note(tmp_path):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER)
    for name, (path, build_queue) in rq.DEBT_QUEUES.items():
        items, note = build_queue()
        assert items == [] and note.startswith(f"{path} absent") and "skipped" in note, name
    assert rq.main(["data"]) == 0


def test_class_of_names_member_scopes_only():
    import repair_queue as rq
    assert rq.class_of("?a@Loco@@QAEXXZ") == "Loco"
    assert rq.class_of("??1AsciiString@@QAE@XZ") == "AsciiString"
    assert rq.class_of("?f@Inner@Outer@@QAEXXZ") == "Outer::Inner"
    assert rq.class_of("?s_count@Loco@@2HA") == "Loco"                     # a static data member
    assert rq.class_of("?f@ns@@YAXXZ") is None                             # a namespace's free function
    assert rq.class_of("?f@@YAXXZ") is None
    assert rq.class_of("?f@?$vector@H@_STL@@QAEXXZ") is None               # a template scope
    assert rq.class_of("?TheAI@@3PAVAI@@A") is None                        # a global


# ---- retiring debt: the tool's verdict on fresh evidence, never a hand deletion

def _git_repo(root):
    import subprocess

    def git(*args):
        return subprocess.run(["git", "-C", str(root), *args], capture_output=True, text=True, check=True)
    git("init", "-q")
    git("add", ".")
    git("-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "init")
    return git


DATA_KEY = ("Code/GameEngine/Body.cpp", "wrong-name", "?g_00A00000@@3HA", "0x00A00000")


class DataWorld:
    """tools/data_check.py's inputs for the fixture: rows, objects and DIR32 bindings."""

    def __init__(self, tmp_path, monkeypatch, rq):
        import build
        import data_check
        import data_ledger
        self.rq, self.objs = rq, tmp_path / "objs"
        self.objs.mkdir()
        self.binds = {"Code/GameEngine/Body.cpp": {("?g_00A00000@@3HA", 0xA00000), ("?TheX@@3HA", 0xA00004)},
                      "Code/GameEngine/Loco.cpp": {("?g_00A00000@@3HA", 0xA00000)}}
        self.defined = {"Code/GameEngine/Body.cpp": {"?TheX@@3HA"}}            # the duplicate-def key stays
        self.unread, self.stale, self.missing = [], set(), set()
        self.ledger = {0xA00000: {"name": "?TheReal@@3HA", "kind": "global", "source": ""},
                       0xA00004: {"name": "?TheX@@3HA", "kind": "global", "source": "Code/Own.cpp"}}
        for name in ("Body", "Loco"):
            (self.objs / f"{name}.obj").write_bytes(b"obj")
        monkeypatch.setattr(data_check, "source_rows", lambda sources: [
            {"name": r["name"], "source": r["source"]} for rows in rq.ledger()[0].values() for r in rows
            if r["source"] in sources])
        monkeypatch.setattr(build, "row_object", lambda row: self.objs / (
            "missing.obj" if row["source"] in self.missing else Path(row["source"]).stem + ".obj"))
        monkeypatch.setattr(build, "compile_is_current", lambda source, obj, **_: Path(source).stem not in self.stale)
        monkeypatch.setattr(data_check, "object_facts", lambda rows, unread=None: (
            unread.extend(self.unread) if unread is not None else None,
            {r["source"]: (set(self.binds.get(r["source"], ())), set(self.defined.get(r["source"], ())))
             for r in rows})[1])
        monkeypatch.setattr(data_ledger, "load", lambda path=None: self.ledger)


def _data_fixture(tmp_path, monkeypatch):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES[:3])
    git = _git_repo(tmp_path)
    rq.head_ledger_rows.cache_clear()
    return rq, rev, git, DataWorld(tmp_path, monkeypatch, rq)


def test_a_row_lost_since_head_blocks_the_verdict(tmp_path, monkeypatch):
    rq, rev, git, world = _data_fixture(tmp_path, monkeypatch)
    ledger_path = rev / "functions.csv"                     # Loco keeps ?a, loses ?b (the row that bound it)
    ledger_path.write_text("".join(l for l in ledger_path.read_text().splitlines(True) if "?b@Loco" not in l),
                           newline="\n")
    rq.ledger.cache_clear()
    world.binds["Code/GameEngine/Loco.cpp"] = set()
    ok, message = rq.retire("data", "Code/GameEngine/Loco.cpp")
    assert not ok and "1 row(s) HEAD held are gone from Code/GameEngine/Loco.cpp" in message


def test_retire_deletes_exactly_the_keys_the_tool_no_longer_finds(tmp_path, monkeypatch):
    rq, rev, git, world = _data_fixture(tmp_path, monkeypatch)
    before = (rev / "data_check_baseline.txt").read_text()
    ok, message = rq.retire("data", "Code/GameEngine/Body.cpp")
    assert not ok and "still found" in message and (rev / "data_check_baseline.txt").read_text() == before
    world.binds["Code/GameEngine/Body.cpp"] = {("?TheReal@@3HA", 0xA00000), ("?TheX@@3HA", 0xA00004)}  # the fix
    ok, message = rq.retire("data", "Code/GameEngine/Body.cpp")
    assert ok and "1 key(s)" in message
    after = (rev / "data_check_baseline.txt").read_text()
    assert "\t".join(DATA_KEY) not in after
    assert after.count("\n") == before.count("\n") - 1                      # that key only; duplicate-def stays
    git("add", "reverse/data_check_baseline.txt")
    assert rq.verify_removed_debt(build_cmd=[sys.executable, "-c", "pass"]) == []


@pytest.mark.parametrize("attempt", ["hand-deletion", "rename", "missing-object", "stale-object", "unreadable",
                                     "lost-row", "deleted-source", "no-ledger"])
def test_every_way_to_clear_data_debt_without_fixing_it_is_refused(tmp_path, monkeypatch, attempt):
    rq, rev, git, world = _data_fixture(tmp_path, monkeypatch)
    body = "Code/GameEngine/Body.cpp"
    if attempt == "rename":                      # a renamed wrong global: old key gone, a new wrong name
        world.binds[body] = {("?g_renamed@@3HA", 0xA00000), ("?TheX@@3HA", 0xA00004)}
    elif attempt == "missing-object":
        world.binds[body] = {("?TheX@@3HA", 0xA00004)}
        world.missing.add(body)
    elif attempt == "stale-object":
        world.binds[body] = {("?TheX@@3HA", 0xA00004)}
        world.stale.add("Body")
    elif attempt == "unreadable":                # the body unreadable: its bindings vanish from the facts
        world.binds[body] = {("?TheX@@3HA", 0xA00004)}
        world.unread.append((body, "?c@Body@@QAEXXZ", "unreadable: truncated"))
    elif attempt == "lost-row":                  # the binding row deleted from the ledger
        world.binds[body] = {("?TheX@@3HA", 0xA00004)}
        ledger_path = rev / "functions.csv"
        ledger_path.write_text("".join(l for l in ledger_path.read_text().splitlines(True) if "?c@Body" not in l),
                               newline="\n")
        rq.ledger.cache_clear()
    elif attempt == "deleted-source":            # the source deleted, its rows and bindings with it
        world.binds[body] = {("?TheX@@3HA", 0xA00004)}
        (tmp_path / body).unlink()
    elif attempt == "no-ledger":
        world.binds[body] = {("?TheX@@3HA", 0xA00004)}
        world.ledger.clear()
    before = (rev / "data_check_baseline.txt").read_text()
    if attempt != "hand-deletion":
        ok, message = rq.retire("data", body)
        assert not ok, message
        assert (rev / "data_check_baseline.txt").read_text() == before    # nothing written
    # the hand deletion of the key, staged: the hook's verify-removed refuses it
    (rev / "data_check_baseline.txt").write_text(before.replace("\t".join(DATA_KEY) + "\n", ""), newline="\n")
    git("add", "reverse/data_check_baseline.txt")
    failures = rq.verify_removed_debt(build_cmd=[sys.executable, "-c", "pass"])
    assert len(failures) == 1 and body in failures[0], failures


def test_a_source_that_never_held_a_row_cannot_vouch_for_its_debt(tmp_path, monkeypatch):
    """R05: a register key of a source with no matched row now or at HEAD: nothing judges
    it, so neither tool's verdict may retire it."""
    orphan = "Code/GameEngine/Orphan.cpp"
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES[:3] + [DEBT_FILES[4], (orphan, "//\n")])
    for name in ("data_check_baseline.txt", "code_identity_baseline.tsv"):
        path = rev / name
        key = (f"{orphan}\twrong-name\t?g@@3HA\t0x00A00000" if name.startswith("data")
               else f"{orphan}\t?o@@YAXXZ\t?f@@YAXXZ\t0x00001000\twrong")
        path.write_text(path.read_text() + key + "\n", newline="\n")
    _git_repo(tmp_path)
    rq.head_ledger_rows.cache_clear()
    DataWorld(tmp_path, monkeypatch, rq)
    IdentityWorld(tmp_path, monkeypatch, rq, objs=tmp_path / "objs")
    for kind in ("data", "identity"):
        ok, message = rq.retire(kind, orphan)
        assert not ok and "holds no matched row" in message, (kind, message)


def test_verify_removed_refuses_a_failed_build_a_vanished_header_unit_and_the_cli_runs_it(tmp_path, monkeypatch):
    """R18: a removed key whose source does not build. R21: a removed header row whose
    unit was deleted, even when acceptance would pass. R22: the CLI judges debt removals."""
    rq, rev, git, world = _data_fixture(tmp_path, monkeypatch)
    body = "Code/GameEngine/Body.cpp"
    world.binds[body] = {("?TheReal@@3HA", 0xA00000), ("?TheX@@3HA", 0xA00004)}   # really fixed
    assert rq.retire("data", body)[0]
    git("add", "reverse/data_check_baseline.txt")
    assert rq.verify_removed_debt(build_cmd=[sys.executable, "-c", "pass"]) == []
    failures = rq.verify_removed_debt(build_cmd=[sys.executable, "-c", "raise SystemExit(1)"])
    assert len(failures) == 1 and "does not build" in failures[0]
    rq2, rev2, git2, _ = _header_fixture(tmp_path / "h", monkeypatch)
    queue = rev2 / "header_queue.tsv"
    queue.write_text("".join(l for l in queue.read_text().splitlines(True) if "\tCode/GameEngine/Body.cpp\t" not in l),
                     newline="\n")
    (tmp_path / "h/Code/GameEngine/Body.cpp").unlink()
    git2("add", "-A")
    failures = rq2.verify_removed_debt(build_cmd=[sys.executable, "-c", "pass"], header_verdict=lambda n, s: [])
    assert len(failures) == 1 and "went with the source" in failures[0]
    monkeypatch.setattr(rq2, "verify_removed", lambda build_cmd=None: [])
    monkeypatch.setattr(rq2, "verify_removed_debt", lambda build_cmd=None, header_verdict=None: ["a debt failure"])
    assert rq2.main(["verify-removed"]) == 1


class FakeObj:
    def __init__(self, names):
        self.by_name = {n: {"name": n} for n in names}

    def is_code(self, sym):
        return True


class IdentityWorld:
    """allowed_symbols' inputs for the fixture: Body.obj references ?f@@YAXXZ, which
    Loco.obj (a participating provider) defines."""

    def __init__(self, tmp_path, monkeypatch, rq, objs=None):
        import allowed_symbols
        import build
        self.objs = objs or tmp_path / "objs"
        self.objs.mkdir(exist_ok=True)
        for name in ("Loco", "Body", "Rva00003000Noop", "uw"):
            (self.objs / f"{name}.obj").write_bytes(b"obj")
        self.symbols = {"?c@Body@@QAEXXZ", "?a@Loco@@QAEXXZ", "?b@Loco@@QAEXXZ"}
        self.refs = {"?c@Body@@QAEXXZ": [(4, 20, "?f@@YAXXZ", 0x1000, "wrong", "")]}
        self.stale, self.unreadable, self.retail, self.scan_error = set(), False, True, False
        world = self
        defs = allowed_symbols._Defs(list, {"?f@@YAXXZ": [(str(self.objs / "Loco.obj"), "d", 8, False)]})
        defs.referrers = {"?f@@YAXXZ": {str(self.objs / "Body.obj")}}

        class Ident:
            def __init__(self):
                self.defs = defs

            def obj(self, path):
                return FakeObj(world.symbols)

            def read(self, rva, size):
                return b"\0" * size if world.retail else None

            def row_refs(self, row):
                if world.scan_error:
                    raise ValueError("truncated relocation table")
                return list(world.refs.get(row["name"], ()))
        rows = [dict(r) for rs in rq.ledger()[0].values() for r in rs]

        def load_rows(sources=None, strict=False):
            if strict and world.unreadable:
                raise allowed_symbols.Unreadable("Loco.obj cannot be parsed")
            return Ident(), [r for r in rows if not sources or r["source"] in sources]
        monkeypatch.setattr(allowed_symbols, "load", load_rows)
        monkeypatch.setattr(allowed_symbols.census, "ledger", lambda: rows)
        monkeypatch.setattr(allowed_symbols, "row_object", lambda row: self.objs / (Path(row["source"]).stem + ".obj"))
        monkeypatch.setattr(build, "compile_is_current", lambda source, obj, **_: Path(source).stem not in world.stale)
        monkeypatch.setattr(build, "ledger_object_symbol", lambda row: row["name"])


IDENTITY_KEY = "Code/GameEngine/Body.cpp\t?c@Body@@QAEXXZ\t?f@@YAXXZ\t0x00001000\twrong"


def test_identity_verdict_refuses_a_row_lost_since_head(tmp_path, monkeypatch):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, [DEBT_FILES[0], DEBT_FILES[1], DEBT_FILES[4]])
    _git_repo(tmp_path)
    rq.head_ledger_rows.cache_clear()
    path = rev / "functions.csv"
    path.write_text("".join(line for line in path.read_text().splitlines(True) if "?b@Loco" not in line),
                    newline="\n")
    rq.ledger.cache_clear()
    IdentityWorld(tmp_path, monkeypatch, rq)
    problems, _ = rq.identity_verdict("Code/GameEngine/Loco.cpp", set())
    assert any("HEAD held are gone" in problem for problem in problems)


@pytest.mark.parametrize("attempt", ["fixed", "hand-deletion", "missing-symbol", "missing-elsewhere", "new-binding",
                                     "stale-object", "stale-provider", "unreadable-object", "retail-unreadable",
                                     "scan-error", "deleted-source"])
def test_identity_debt_retires_only_on_allowed_symbols_verdict(tmp_path, monkeypatch, attempt):
    """Every attempt but `fixed` clears the binding without evidence the tool can stand
    behind (the fix is simulated in each), so retire and verify-removed both refuse."""
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, [DEBT_FILES[0], DEBT_FILES[1], DEBT_FILES[4]])
    git = _git_repo(tmp_path)
    rq.head_ledger_rows.cache_clear()
    world = IdentityWorld(tmp_path, monkeypatch, rq)
    body = "Code/GameEngine/Body.cpp"
    if attempt != "new-binding" and attempt != "hand-deletion":
        world.refs.clear()                       # the binding no longer found in every other case
    if attempt == "missing-symbol":              # the row's symbol gone from its object: scan() skips it silently
        world.symbols.discard("?c@Body@@QAEXXZ")
    elif attempt == "missing-elsewhere":         # another unit's object missing: the kept copy is unknown
        (world.objs / "Loco.obj").unlink()
    elif attempt == "new-binding":               # one binding traded for another
        world.refs["?c@Body@@QAEXXZ"] = [(4, 20, "?g@@YAXXZ", 0x1000, "wrong", "")]
    elif attempt == "stale-object":              # Body.obj predates its source
        world.stale.add("Body")
    elif attempt == "stale-provider":            # Loco.obj, which defines ?f@@YAXXZ, predates its source
        world.stale.add("Loco")
    elif attempt == "unreadable-object":         # an object allowed_symbols cannot parse
        world.unreadable = True
    elif attempt == "retail-unreadable":
        world.retail = False
    elif attempt == "scan-error":
        world.scan_error = True
    elif attempt == "deleted-source":
        (tmp_path / body).unlink()
    path = rev / "code_identity_baseline.tsv"
    before = path.read_text()
    if attempt != "hand-deletion":
        ok, message = rq.retire("identity", body)
        assert ok == (attempt == "fixed"), message
        if attempt != "fixed":
            assert path.read_text() == before
    if attempt != "fixed":
        path.write_text(before.replace(IDENTITY_KEY + "\n", ""), newline="\n")
    assert IDENTITY_KEY not in path.read_text()
    git("add", "reverse/code_identity_baseline.tsv")
    failures = rq.verify_removed_debt(build_cmd=[sys.executable, "-c", "pass"])
    assert (failures == []) == (attempt == "fixed"), failures


@pytest.mark.parametrize("case", ["fixed", "wrong", "divergent", "no-proof", "resolver-exit", "stale"])
def test_identity_retirement_checks_the_located_funclet(tmp_path, monkeypatch, case):
    """Retirement and the outgoing check must judge the located cleanup relocation."""
    import struct
    import allowed_symbols as allowed
    import build
    from test_gate_exploits import coff, TEXT

    source = "Code/GameEngine/Body.cpp"
    key = f"{source}\t$L4992\t_cleanup\t0x00002000\twrong"
    baseline = "# Wrong code bindings\n# mode: shadow\n" + key + "\n"
    rq, rev, _ = load(tmp_path, "bfme2", [("$L4992", 0x1000, 8, "GameEngine/Body.cpp")], [
        (source, "//\n"), ("reverse/code_identity_baseline.tsv", baseline)])
    ledger = rev / "functions.csv"
    ledger.write_text(ledger.read_text().replace(
        ",matched,\n", ",matched,gen-funclet;parent=_parent\n"), newline="\n")
    git = _git_repo(tmp_path)
    rq.head_ledger_rows.cache_clear()
    objpath = tmp_path / "Body.obj"
    objpath.write_bytes(coff([(".text", TEXT, b"\x8d\x4d\xf0\xe9\0\0\0\0", [(4, 1, allowed.REL32)])], [
        ("$L5053", 0, 1, 0x20, allowed.STATIC, 0), ("_cleanup", 0, 0, 0x20, allowed.EXTERNAL, 0)]))
    row = dict(name="$L4992", target_rva="0x1000", target_size="8", source=source,
               notes="gen-funclet;parent=_parent", status="matched")
    ident = allowed.Identity.__new__(allowed.Identity)
    ident.defs = allowed._Defs(list)
    ident.defs.referrers = {}
    ident.obj = lambda _: allowed.Obj(objpath)
    ident.read = lambda *_: b"\x8d\x4d\xf0\xe9" + struct.pack("<i", 0x2000 - 0x1008)
    ident.text = (0x1000, 0x3000)
    classified = []

    def classify(actual_row, obj, sym, where, kind, ref, target):
        classified.append((actual_row["name"], sym["name"], ref["name"], target))
        return (case if case in ("wrong", "divergent") else "owner"), "fixture"

    def locate(*_):
        if case == "resolver-exit":
            raise SystemExit("parent verification failed")
        return None if case == "no-proof" else "$L5053"

    ident.classify = classify
    monkeypatch.setattr(allowed, "load", lambda *_, **__: (ident, [row]))
    monkeypatch.setattr(allowed.census, "ledger", lambda: [row])
    monkeypatch.setattr(allowed, "row_object", lambda _: objpath)
    monkeypatch.setattr(build, "compile_is_current", lambda *_, **__: case != "stale")
    monkeypatch.setattr(build, "located_funclet", locate)
    ok, message = rq.retire("identity", source)
    assert ok == (case == "fixed"), message
    path = rev / "code_identity_baseline.tsv"
    if case != "fixed":
        assert path.read_text() == baseline
        path.write_text(baseline.replace(key + "\n", ""), newline="\n")
    if case in ("fixed", "wrong", "divergent"):
        assert classified == [("$L4992", "$L5053", "_cleanup", 0x2000)]
    git("add", "reverse/code_identity_baseline.tsv")
    failures = rq.verify_removed_debt(build_cmd=[sys.executable, "-c", "pass"])
    assert (failures == []) == (case == "fixed"), failures


# ---- the header queue: acceptance verifies the real include and retires its own row

def _header_fixture(tmp_path, monkeypatch):
    import header_adopt_lane as hal
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES[:2] + [DEBT_FILES[3]] + [
        ("Code/Include/Coord3D.h", "struct Coord3D { float x, y, z; };\n"),
        ("Code/Other/Coord3D.h", "// another header of the same name\n")])
    git = _git_repo(tmp_path)
    monkeypatch.setattr(hal, "ROOT", tmp_path)
    monkeypatch.setattr(hal, "QUEUE", rev / "header_queue.tsv")
    monkeypatch.setattr(hal, "registered", lambda: {"Coord3D": "Code/Include/Coord3D.h"})
    monkeypatch.setattr(rq, "_head_header_verdict", lambda name, source: hal.verdict(name, source))
    monkeypatch.setattr(hal, "gate_one", lambda source: None)               # the byte gate passes
    monkeypatch.setattr(hal, "link_ok", lambda sources: dict.fromkeys(sources, True))
    return rq, rev, git, hal


def test_a_header_row_leaves_the_queue_only_when_acceptance_passes(tmp_path, monkeypatch):
    rq, rev, git, hal = _header_fixture(tmp_path, monkeypatch)
    body = tmp_path / "Code/GameEngine/Body.cpp"
    queue = rev / "header_queue.tsv"
    for text in ('// #include "../Include/Coord3D.h"\n',                     # a comment
                 '/* #include "../Include/Coord3D.h" */\n',
                 '#include "Coord3D.h"\n',                                  # a basename two headers share
                 'const char *s = "Coord3D.h";\n'):
        body.write_text(text)
        assert hal.accept("Coord3D", ["Code/GameEngine/Body.cpp"]) == 1, text
        assert "Coord3D\tCode/GameEngine/Body.cpp" in queue.read_text()
    body.write_text('#include "../Include/Coord3D.h"\n')
    assert hal.accept("Coord3D", ["Code/GameEngine/Body.cpp"]) == 0
    assert "Coord3D\tCode/GameEngine/Body.cpp" not in queue.read_text()     # retired by the verdict
    assert "AsciiString\tCode/GameEngine/Loco.cpp" in queue.read_text()
    git("add", "-A")
    assert rq.verify_removed_debt(build_cmd=[sys.executable, "-c", "pass"]) == []


@pytest.mark.parametrize("linked", [False, None])
def test_header_debt_hook_refuses_lost_linking_or_missing_preview(tmp_path, monkeypatch, linked):
    rq, rev, git, hal = _header_fixture(tmp_path, monkeypatch)
    source = "Code/GameEngine/Body.cpp"
    (tmp_path / source).write_text('#include "../Include/Coord3D.h"\n')
    queue = rev / "header_queue.tsv"
    original = queue.read_text()
    monkeypatch.setattr(hal, "link_ok", lambda sources: dict.fromkeys(sources, linked))
    assert hal.accept("Coord3D", [source]) == 1
    assert queue.read_text() == original
    queue.write_text("\n".join(line for line in original.splitlines()
                               if not line.startswith("Coord3D\t")) + "\n")
    git("add", "reverse/header_queue.tsv", source)
    failures = rq.verify_removed_debt(build_cmd=[sys.executable, "-c", "pass"])
    assert any("link_check" in failure for failure in failures), failures


def test_a_hand_deleted_header_row_is_refused(tmp_path, monkeypatch):
    rq, rev, git, hal = _header_fixture(tmp_path, monkeypatch)
    queue = rev / "header_queue.tsv"
    queue.write_text("".join(l for l in queue.read_text().splitlines(True) if "\tCode/GameEngine/Body.cpp\t" not in l),
                     newline="\n")
    git("add", "reverse/header_queue.tsv")
    failures = rq.verify_removed_debt(build_cmd=[sys.executable, "-c", "pass"])
    assert len(failures) == 1 and "does not #include Code/Include/Coord3D.h" in failures[0]


@pytest.mark.parametrize("case,text,why", [
    ("block comment", '/*\n#include "../Include/Coord3D.h"\n*/\n', "does not #include"),          # H01
    ("#if 0", '#if 0\n#include "../Include/Coord3D.h"\n#endif\n', "does not #include"),
    ("nested #if 0", '#if 0\n#ifdef X\n#endif\n#include "../Include/Coord3D.h"\n#endif\n', "does not #include"),
    ("macro text", '#define INC include "../Include/Coord3D.h"\n', "does not #include"),             # H08
    ("private body", 'struct Coord3D { float x, y, z; };\n#include "../Include/Coord3D.h"\n',
     "private body"),                                                                                # H04
])
def test_header_acceptance_refuses_an_include_the_compiler_never_sees(tmp_path, monkeypatch, case, text, why):
    rq, rev, git, hal = _header_fixture(tmp_path, monkeypatch)
    (tmp_path / "Code/GameEngine/Body.cpp").write_text(text)
    problems = hal.verdict("Coord3D", "Code/GameEngine/Body.cpp")
    assert any(why in p for p in problems), (case, problems)


def test_header_acceptance_needs_the_header_and_the_byte_gate(tmp_path, monkeypatch):
    rq, rev, git, hal = _header_fixture(tmp_path, monkeypatch)
    body = tmp_path / "Code/GameEngine/Body.cpp"
    body.write_text('#if 0\n#include "nothing.h"\n#else\n#include "../Include/Coord3D.h"\n#endif\n')
    assert hal.verdict("Coord3D", "Code/GameEngine/Body.cpp") == []                     # the #else branch is live
    assert hal.verdict("Coord3D", "Code/GameEngine/Body.cpp",
                       gate=lambda source: "byte mismatch at 0x2000") == ["byte mismatch at 0x2000"]   # H05
    body.write_text('#include "../Include/Missing.h"\n')
    problems = hal.verdict("Coord3D", "Code/GameEngine/Body.cpp", header="Code/Include/Missing.h")
    assert problems and "does not exist" in problems[0]                                  # H07


# ---- claims fence across namespaces

SCOPE_LEDGER = {0x1000: ("Code/GameEngine/Loco.cpp", "Loco"), 0x1080: ("Code/GameEngine/Loco.cpp", "Loco"),
                0x2000: ("Code/GameEngine/Body.cpp", "Body"), 0x2100: ("Code/GameEngine/Body.cpp", "Coord3D")}


@pytest.fixture
def fenced(monkeypatch):
    """claims' scope index over SCOPE_LEDGER, and a settable set of live claims."""
    import claims
    of_rva, classes, files = {}, {}, {}
    for rva, (source, cls) in SCOPE_LEDGER.items():
        fkey, ckey = claims.file_key(source), claims.class_key(cls)
        of_rva[rva] = (fkey, ckey)
        classes.setdefault(fkey, set()).add(ckey)
        files.setdefault(ckey, set()).add(fkey)
    monkeypatch.setattr(claims, "scope_index", lambda root=None: (of_rva, classes, files))
    monkeypatch.delenv("BFME_CLAIMS", raising=False)
    live = {}
    monkeypatch.setattr(claims, "active", lambda root=None: dict(live))
    claims.active.cache_clear = lambda: None
    # Busy checks now inspect each namespace separately to preserve foreign
    # authority and footprints even when active() displays a later own record.
    monkeypatch.setattr(claims, "_read_local", lambda root=None, seen=claims.SEEN:
                        {k: ("fixture", dict(info, expires=float("inf"))) for k, info in live.items()}
                        if seen == claims.SEEN else {})
    monkeypatch.setattr(claims, "_local_lock_records", lambda root: dict(live))
    monkeypatch.setattr(claims, "mirrored", lambda root=None: {})
    return live


def test_scope_claims_lock_every_file_their_work_touches(fenced):
    import claims
    body, loco = claims.file_key("Code/GameEngine/Body.cpp"), claims.file_key("Code/GameEngine/Loco.cpp")
    fenced["class/Coord3D"] = {"owner": "peer"}
    assert claims.busy_rvas() == {0x2000, 0x2100}       # every body of the file a member lives in, not the member only
    assert claims.busy_keys() == {"class/Coord3D", body}
    fenced.clear()
    fenced[loco] = {"owner": "peer"}
    assert claims.busy_rvas() == {0x1000, 0x1080} and claims.busy_keys() == {loco}   # a file locks itself only
    fenced.clear()
    fenced[0x2000] = {"owner": "peer"}
    assert claims.busy_keys() == {0x2000, body} and claims.busy_rvas() == {0x2000, 0x2100}


def test_collision_is_symmetric_and_the_stored_claim_rule_agrees(fenced, monkeypatch):
    """collide(a, b) == collide(b, a) for every pair of works, and a live claim on a
    collides with work b exactly when a live claim on b collides with work a."""
    import claims
    import next_work
    monkeypatch.setattr(claims, "owner", lambda root=None: "me")
    monkeypatch.setattr(claims, "legacy_owner", lambda root=None: None)
    universe = [0x1000, 0x1080, 0x2000, 0x2100, 0x3000, "class/Coord3D", "class/Loco", "class/Body", "class/Other",
                claims.file_key("Code/GameEngine/Loco.cpp"), claims.file_key("Code/GameEngine/Body.cpp"),
                claims.file_key("Code/Elsewhere.cpp")]
    rng = random.Random(2026)
    for _ in range(400):
        a, b = (set(rng.sample(universe, rng.randint(1, 3))) for _ in range(2))
        collide = bool(claims.lock_keys(a) & claims.lock_keys(b))
        assert collide == bool(claims.lock_keys(b) & claims.lock_keys(a))
        fenced.clear()
        fenced.update({k: {"owner": "peer"} for k in a})
        theirs_a = bool(claims.conflicts(b))
        fenced.clear()
        fenced.update({k: {"owner": "peer"} for k in b})
        assert theirs_a == bool(claims.conflicts(a)) == collide, (a, b)
    rva_item = {"function": "?c@Body@@QAEXXZ", "source": "Code/GameEngine/Body.cpp", "target_rva": "0x00002000"}
    header = {"function": "Coord3D", "class": "Coord3D", "source": "Code/GameEngine/Loco.cpp",
              "claim": ["class:Coord3D", "file:Code/GameEngine/Loco.cpp"]}
    ka, kb = next_work.claim_keys(rva_item), next_work.claim_keys(header)
    assert bool(claims.lock_keys(ka) & claims.lock_keys(kb))                 # Coord3D has a member in Body.cpp
    assert next_work.without_busy([header], ka) == [] and next_work.without_busy([rva_item], kb) == []


def test_next_work_skips_work_that_collides_in_another_namespace(fenced):
    import claims
    import next_work
    header = {"tier": "header", "function": "Coord3D", "class": "Coord3D", "source": "Code/GameEngine/Loco.cpp",
              "target_rva": "0x00001000", "claim": ["class:Coord3D", "file:Code/GameEngine/Loco.cpp"]}
    data = {"tier": "data", "function": "?g@@3HA", "source": "Code/GameEngine/Body.cpp", "target_rva": "",
            "claim": ["file:Code/GameEngine/Body.cpp"]}
    body = {"tier": "identity", "function": "?a@Loco@@QAEXXZ", "source": "Code/GameEngine/Loco.cpp",
            "target_rva": "0x00001080"}
    work = [header, data, body]
    fenced[claims.file_key("Code/GameEngine/Loco.cpp")] = {"owner": "peer"}   # a link unit's file claim
    assert next_work.without_busy(work, claims.busy_keys()) == [data]       # header and the RVA inside it fenced
    fenced.clear()
    fenced["class/Coord3D"] = {"owner": "peer"}                              # Body.cpp defines a Coord3D member
    assert next_work.without_busy(work, claims.busy_keys()) == [body]
    fenced.clear()
    fenced[0x2000] = {"owner": "peer"}                                       # one body of Body.cpp
    assert next_work.without_busy(work, claims.busy_keys()) == [body]        # Coord3D's header work touches it too


def test_conflicts_honours_the_off_switch_without_a_fetch(monkeypatch):
    import claims
    monkeypatch.setenv("BFME_CLAIMS", "off")
    monkeypatch.setattr(claims, "active", lambda root=None: pytest.fail("fetched origin with BFME_CLAIMS=off"))
    assert claims.conflicts({0x2000}) == {} and claims.busy_rvas() == set() and claims.busy_keys() == set()


# ---- mutual exclusion against a local bare origin: file locks, never timestamps

DATA_BODY = {"tier": "data", "function": "?g@@3HA", "source": "Code/GameEngine/Body.cpp", "target_rva": "",
             "claim": ["file:Code/GameEngine/Body.cpp"]}
DATA_LOCO = {"tier": "data", "function": "?h@@3HA", "source": "Code/GameEngine/Loco.cpp", "target_rva": "",
             "claim": ["file:Code/GameEngine/Loco.cpp"]}
HEADER_COORD = {"tier": "header", "function": "Coord3D", "class": "Coord3D", "source": "Code/GameEngine/Other.cpp",
                "target_rva": "", "claim": ["class:Coord3D", "file:Code/GameEngine/Other.cpp"]}


@pytest.fixture
def seats(tmp_path, monkeypatch):
    """Clones of one local bare origin; seats(name) switches to that seat. claims' scope
    index is SCOPE_LEDGER's (Coord3D has a member in Body.cpp)."""
    import subprocess
    import claims
    import next_work

    def git(cwd, *args):
        return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True).stdout
    origin = tmp_path / "origin.git"
    git(tmp_path, "init", "-q", "--bare", str(origin))
    of_rva, classes, files = {}, {}, {}
    for rva, (source, cls) in SCOPE_LEDGER.items():
        fkey, ckey = claims.file_key(source), claims.class_key(cls)
        of_rva[rva] = (fkey, ckey)
        classes.setdefault(fkey, set()).add(ckey)
        files.setdefault(ckey, set()).add(fkey)
    monkeypatch.setattr(claims, "scope_index", lambda root=None: (of_rva, classes, files))
    monkeypatch.delenv("BFME_RUN_ID", raising=False)
    monkeypatch.delenv("BFME_CLAIMS", raising=False)
    monkeypatch.setattr(claims, "NS", "refs/claims/")
    monkeypatch.setattr(claims, "REMOTE", "origin")
    # These transports use a local bare repository, and some tests skew time
    # by an hour. Production host pacing must not turn that into a real sleep.
    monkeypatch.setenv("BFME_CLAIM_PUSHES_PER_MINUTE", "0")
    monkeypatch.setattr(next_work, "weighted_choice", lambda candidates: candidates[0])

    def act(name):
        clone = tmp_path / name
        if not clone.exists():
            git(tmp_path, "init", "-q", str(clone))
            git(clone, "remote", "add", "origin", str(origin))
        monkeypatch.setattr(claims, "ROOT", clone)
        monkeypatch.setenv("BFME_CLAIM_OWNER", name)
        claims.active.cache_clear()
        claims.mirrored.cache_clear()
        return clone

    def on_origin():
        out = git(origin, "for-each-ref", "--format=%(refname)%09%(contents:subject)", "refs/claims/")
        return {line.split("\t")[0][len("refs/claims/"):]: json.loads(line.split("\t", 1)[1])["owner"]
                for line in out.splitlines()}
    act.on_origin = on_origin
    return act


def test_colliding_work_is_exclusive_whatever_the_clocks_say(seats, monkeypatch):
    """Item 1: the second seat is refused by the ref itself, even when its clock is earlier
    (a skewed host, a same-second tie, a delayed publish): there is no timestamp to win."""
    import claims
    import next_work
    real = claims.time.time
    for skew in (-3600, 0, 3600):                       # b's clock behind, tied with, ahead of a's
        seats("a")
        got, held = next_work.claim_choice([HEADER_COORD], "class-header adoption")
        assert got is HEADER_COORD and held == ["class/Coord3D"]
        seats("b")
        monkeypatch.setattr(claims.time, "time", lambda: real() + skew)
        got, acquired = next_work.claim_choice([DATA_BODY], "data-identity debt")
        monkeypatch.setattr(claims.time, "time", real)
        assert got is None and acquired == [], skew
        assert set(seats.on_origin().values()) == {"a"}                    # b left nothing behind
        seats("a")
        claims.release_work(held)
        assert seats.on_origin() == {}


def test_the_loser_of_a_race_keeps_nothing_and_takes_the_next_draw(seats):
    """Both seats saw the pool before either claimed (stale busy views): the second is
    refused on the file lock, releases every ref it took and serves non-colliding work."""
    import claims
    import next_work
    seats("a")
    pool_a = next_work.without_busy([DATA_BODY, DATA_LOCO], next_work.busy_keys())
    seats("b")
    pool_b = next_work.without_busy([HEADER_COORD, DATA_LOCO], next_work.busy_keys())
    seats("a")
    assert next_work.claim_choice(pool_a, "data-identity debt")[0] is DATA_BODY
    seats("b")
    got, acquired = next_work.claim_choice(pool_b, "class-header adoption")
    assert got is DATA_LOCO
    held = seats.on_origin()
    assert held[claims.file_key("Code/GameEngine/Body.cpp")] == "a"
    assert "class/Coord3D" not in held and claims.file_key("Code/GameEngine/Other.cpp") not in held


def test_partial_acquisition_cas_cleans_up_when_fetch_fails(seats, monkeypatch):
    import claims
    seats("a")
    assert claims.acquire(DATA_BODY["claim"]).claimed
    seats("b")
    monkeypatch.setattr(claims, "release", lambda *args, **kwargs: [])
    result = claims.acquire(HEADER_COORD["claim"])
    assert result.claimed == [] and result.refused
    assert seats.on_origin() == {claims.file_key("Code/GameEngine/Body.cpp"): "a"}


def test_unreleasable_partial_claim_stops_picker(seats, monkeypatch):
    import claims
    import next_work
    import subprocess
    seats("a")
    assert claims.acquire(DATA_BODY["claim"]).claimed
    seats("b")
    monkeypatch.setattr(claims, "release", lambda *args, **kwargs: [])
    real_git = claims._git

    def interrupted(*args, **kwargs):
        if args[:2] == ("push", "-q") and any(str(arg).startswith(":refs/claims/") for arg in args):
            return subprocess.CompletedProcess(args, 1, "", "origin unavailable")
        return real_git(*args, **kwargs)

    monkeypatch.setattr(claims, "_git", interrupted)
    with pytest.raises(SystemExit, match="partial claims remain"):
        next_work.claim_choice([HEADER_COORD, DATA_LOCO], "class-header adoption")


def test_an_older_clients_claim_is_honoured_and_its_own_claims_are_not_conflicts(seats):
    """Backward compatibility: a live RVA claim an older client took (no file lock) makes
    colliding work yield, and every ref the yielding seat took is released. A seat's own
    claims never count against it (C15), and a ref it held before a failed acquire stays."""
    import claims
    seats("old")
    assert claims.claim([0x2000]) == ([0x2000], [])                         # an old client: no file lock
    seats("a")
    result = claims.acquire(DATA_BODY["claim"], next_work_keys(DATA_BODY))
    assert result.claimed == [] and result.refused == [0x2000]
    assert set(seats.on_origin()) == {"0x00002000"}                          # a's file ref released again
    seats("old")
    claims.release([0x2000])
    seats("a")
    first = claims.acquire(DATA_BODY["claim"], next_work_keys(DATA_BODY))
    assert first.claimed == [claims.file_key("Code/GameEngine/Body.cpp")]
    again = claims.acquire(["0x00002000"])                                   # own file claim: no conflict
    assert not again.refused and 0x2000 in again.claimed
    seats("b")
    assert claims.acquire(DATA_LOCO["claim"]).claimed                       # b holds Loco.cpp
    seats("a")
    both = claims.acquire(["class:Loco", "file:Code/GameEngine/Body.cpp"])   # needs Loco.cpp: refused
    assert both.claimed == [] and both.refused
    held = seats.on_origin()
    assert held[claims.file_key("Code/GameEngine/Body.cpp")] == "a" and "class/Loco" not in held


def next_work_keys(item):
    import next_work
    return next_work.claim_keys(item)


def test_conflicts_rereads_origin_past_a_cached_view(seats):
    """C06: conflicts() clears the active() cache, or a claim made after this process
    first looked would never be seen."""
    import subprocess
    import time
    import claims
    clone = seats("a")
    assert claims.active() == {}                                             # cached
    origin = clone.parent / "origin.git"                                     # another host claims 0x2100

    def git(*args, text=None):
        return subprocess.run(["git", "-C", str(origin), *args], input=text, capture_output=True, text=True,
                              check=True).stdout.strip()
    info = {"owner": "peer", "nonce": "n", "lease": "n", "created": int(time.time()),
            "expires": int(time.time()) + 3600}
    sha = git("-c", "user.name=p", "-c", "user.email=p@x", "commit-tree", git("mktree", text=""),
              "-m", json.dumps(info))
    git("update-ref", "refs/claims/0x00002100", sha)
    assert claims.active() == {}                                             # the cache has not seen it
    assert 0x2100 in claims.conflicts({claims.file_key("Code/GameEngine/Body.cpp")})


def test_a_body_file_lock_goes_once_no_claim_of_its_owner_needs_it(seats):
    import claims
    body = claims.file_key("Code/GameEngine/Body.cpp")
    seats("a")
    claims.acquire(["0x00002000"])
    claims.acquire(["0x00002100"])                                           # the same file, already locked
    assert claims.active()[body].get("lock")
    assert claims.release_work([0x2000]) == [0x2000]                         # 0x2100 still needs Body.cpp
    assert body in seats.on_origin()
    assert set(claims.release_work([0x2100])) == {0x2100, body}
    assert seats.on_origin() == {}


def test_scope_claims_record_their_debt_lines_and_settle_releases_them_once_published(tmp_path, monkeypatch):
    """Against a local bare origin: a data item's file claim carries `debt=`; settle keeps
    it while origin/master still holds the line and releases it once the fix is pushed."""
    import subprocess
    import claims
    import next_work

    def git(cwd, *args):
        return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True).stdout
    origin, clone = tmp_path / "origin.git", tmp_path / "a"
    git(tmp_path, "init", "-q", "--bare", str(origin))
    git(tmp_path, "init", "-q", "-b", "master", str(clone))
    git(clone, "remote", "add", "origin", str(origin))
    git(clone, "config", "user.name", "a")
    git(clone, "config", "user.email", "a@example.com")
    line = "\t".join(DATA_KEY)
    (clone / "reverse").mkdir()
    (clone / "reverse/data_check_baseline.txt").write_text("# header\n" + line + "\n", newline="\n")
    git(clone, "add", ".")
    git(clone, "commit", "-qm", "debt")
    git(clone, "push", "-q", "origin", "master")
    monkeypatch.delenv("BFME_RUN_ID", raising=False)
    monkeypatch.delenv("BFME_CLAIMS", raising=False)
    monkeypatch.setattr(claims, "NS", "refs/claims/")
    monkeypatch.setattr(claims, "REMOTE", "origin")
    monkeypatch.setattr(claims, "ROOT", clone)
    monkeypatch.setenv("BFME_CLAIM_OWNER", "a")
    claims.active.cache_clear()
    claims.mirrored.cache_clear()
    item = {"tier": "data", "function": DATA_KEY[2], "source": DATA_KEY[0], "claim": [f"file:{DATA_KEY[0]}"],
            "baseline": "reverse/data_check_baseline.txt", "debt_lines": [line]}
    note = next_work.claim_note("data-identity debt", item)
    assert "debt=reverse/data_check_baseline.txt#" in note
    got, refused = claims.claim(item["claim"], note=note)
    key = claims.file_key(DATA_KEY[0])
    assert got == [key] and not refused
    assert claims.settle_scopes() == []                                     # the line is still on origin/master
    (clone / "reverse/data_check_baseline.txt").write_text("# header\n", newline="\n")
    git(clone, "commit", "-qam", "fix")
    assert claims.settle_scopes() == []                                     # committed, not pushed: kept
    git(clone, "push", "-q", "origin", "master")
    assert claims.settle_scopes() == [key]
    claims.active.cache_clear()
    assert key not in claims.active()
    plain, _ = claims.claim(["file:Code/Link.cpp"], note="next_work link-cycle repair")
    assert claims.settle_scopes() == []                                     # no debt note: released by hand only
    assert next_work.scope_release_note({"claim": ["file:Code/Link.cpp"]}, plain).endswith(
        "python3 tools/claims.py release file:Code/Link.cpp")


@pytest.fixture
def published(tmp_path, monkeypatch):
    """A clone of a local bare origin whose master holds FILES; returns (commit_and_push, claims)."""
    import subprocess
    import claims

    def git(cwd, *args):
        return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True).stdout
    origin, clone = tmp_path / "origin.git", tmp_path / "a"
    git(tmp_path, "init", "-q", "--bare", str(origin))
    git(tmp_path, "init", "-q", "-b", "master", str(clone))
    git(clone, "remote", "add", "origin", str(origin))
    git(clone, "config", "user.name", "a")
    git(clone, "config", "user.email", "a@example.com")
    monkeypatch.delenv("BFME_RUN_ID", raising=False)
    monkeypatch.delenv("BFME_CLAIMS", raising=False)
    monkeypatch.setattr(claims, "NS", "refs/claims/")
    monkeypatch.setattr(claims, "REMOTE", "origin")
    monkeypatch.setattr(claims, "ROOT", clone)
    monkeypatch.setenv("BFME_CLAIM_OWNER", "a")
    claims.active.cache_clear()
    claims.mirrored.cache_clear()

    def push(files):
        for rel, text in files.items():
            (clone / rel).parent.mkdir(parents=True, exist_ok=True)
            (clone / rel).write_text(text, newline="\n")
        git(clone, "add", ".")
        git(clone, "commit", "-qm", "x", "--allow-empty")
        git(clone, "push", "-q", "origin", "master")
    return push


CENSUS_LINE = "source,linked,unresolved,duplicates,comdat_losers,addresses,wrong_selected\n"


def test_every_debt_item_records_its_debt_and_settles_when_published(published, monkeypatch):
    """Item 9: an identity RVA claim, a census unit's file claim and a gate-debt RVA claim
    carry `debt=`, so settle releases them once origin/master drops the line, never before
    -- and never one the caller holds."""
    import claims
    import next_work
    import repair_queue as rq
    gate = "byte-gate 0x00003000 ?h@@YAXXZ"
    published({"reverse/code_identity_baseline.tsv": "# mode: shadow\n" + IDENTITY_KEY + "\n",
               "reverse/link_status.csv": CENSUS_LINE + "Code/Link.cpp,no,1,0,0,0,0\n",
               "reverse/gate_baseline.txt": gate + "\n"})
    identity = {"tier": "identity", "function": "?c@Body@@QAEXXZ", "source": "Code/GameEngine/Body.cpp",
                "target_rva": "0x00002000", "baseline": rq.IDENTITY_BASELINE, "debt_lines": [IDENTITY_KEY]}
    census = {"tier": "link", "function": "?l@@YAXXZ", "source": "Code/Link.cpp", "target_rva": "0x00004000",
              "claim": ["file:Code/Link.cpp"], "baseline": rq.CENSUS_STATUS, "debt_lines": ["Code/Link.cpp"]}
    repair = {"tier": "repair", "function": "?h@@YAXXZ", "source": "Code/H.cpp", "target_rva": "0x00003000",
              "baseline": "reverse/gate_baseline.txt", "baseline_line": gate}
    for item in (identity, census, repair):
        note = next_work.claim_note("x", item)
        assert "debt=" in note, item["tier"]
        assert not claims.acquire(next_work.claim_targets(item), next_work.claim_keys(item), note=note).refused
        assert next_work.scope_release_note(item, ["x"]) is None
    assert claims.settle_scopes() == []                                     # every line still on master
    published({"reverse/code_identity_baseline.tsv": "# mode: shadow\n",
               "reverse/link_status.csv": CENSUS_LINE + "Code/Link.cpp,yes,0,0,0,0,0\n",
               "reverse/gate_baseline.txt": ""})
    assert claims.settle_scopes(hold={0x3000}) == [0x2000, claims.file_key("Code/Link.cpp")]
    assert claims.settle_scopes() == [0x3000]


def test_settle_keeps_a_claim_whose_debt_it_cannot_read_or_whose_origin_is_down(published, monkeypatch):
    """C13: a debt file origin/master cannot show keeps the claim. C14: with origin's claims
    unreadable nothing is released, even when the tip shows the debt gone."""
    import claims
    published({"reverse/data_check_baseline.txt": "# header\n"})
    claims.claim(["file:Code/A.cpp"], note="next_work x debt=reverse/missing.txt#0123456789ab")
    claims.claim(["file:Code/B.cpp"], note="next_work x debt=reverse/data_check_baseline.txt#0123456789ab")
    assert claims.settle_scopes(hold={claims.file_key("Code/B.cpp")}) == []          # A.cpp's debt unreadable
    tip = claims._fetch_master(None)
    released = []
    monkeypatch.setattr(claims, "fetch", lambda root=None: False)
    monkeypatch.setattr(claims, "release", lambda keys, **_: released.extend(keys) or list(keys))
    assert claims.settle_scopes(tip=tip) == [] and released == []


# ---- next_work: lazy, weighted debt tiers with fallthrough

class FakeQueues:
    """repair_queue's builders for next_work, recording which were built."""

    def __init__(self, tmp_path, **queues):
        self.ROOT = tmp_path
        self.queues = queues
        self.DEBT_QUEUES = {name: (f"{name}.txt", (lambda n=name: (list(self.queues.get(n, [])), n)))
                            for name in ("data", "header", "identity")}
        for name in self.DEBT_QUEUES:
            (tmp_path / f"{name}.txt").write_text("")

    def all_repair_items(self):
        return list(self.queues.get("repair", []))

    def link_items(self):
        return list(self.queues.get("link", [])), "link"


def _item(tier, name, **kw):
    return dict({"tier": tier, "function": name, "source": f"Code/{name}.cpp", "target_rva": "", "size": 0,
                 "claim": [f"file:Code/{name}.cpp"]}, **kw)


@pytest.fixture
def picker(tmp_path, monkeypatch):
    import argparse
    import claims
    import next_work
    monkeypatch.setattr(next_work, "BUILT", [])
    monkeypatch.setattr(next_work, "_DEBT", {})
    monkeypatch.setattr(next_work, "SKIPPED", [])
    monkeypatch.setattr(next_work, "annotate_attempts", lambda pool: pool)
    monkeypatch.setattr(next_work.re_log, "is_dead_end", lambda *a, **k: False)
    monkeypatch.setattr(next_work.re_log, "is_deferred", lambda *a, **k: False)
    monkeypatch.setattr(claims, "work_keys", lambda rva=None, source=None, cls=None, root=None:
                        {claims.file_key(source)} if source else set())
    args = argparse.Namespace(shard=None, include_logged=False, claim=False)

    def run(order, busy=frozenset(), **queues):
        next_work.repair_queue = FakeQueues(tmp_path, **queues)
        next_work.BUILT.clear()
        next_work._DEBT.clear()
        return next_work.pick_debt(order, args, set(busy))
    run.args = args
    return run


def test_debt_tiers_are_built_lazily(picker):
    import next_work
    got = picker(["repair", "link", "data", "header", "identity"], link=[_item("link", "L")],
                 data=[_item("data", "D")])
    assert got["name"] == "link" and next_work.BUILT == ["repair", "link"]   # data/header/identity never built
    got = picker(["repair", "data", "link"], data=[_item("data", "D")], link=[_item("link", "L")])
    assert got["name"] == "data" and next_work.BUILT == ["repair", "data"]


def test_a_claimed_out_queue_falls_through_to_the_next(picker, monkeypatch):
    import claims
    import next_work
    link = [_item("link", "L1"), _item("link", "L2")]
    busy = {claims.file_key("Code/L1.cpp"), claims.file_key("Code/L2.cpp")}
    got = picker(["repair", "link", "header", "data"], busy=busy, link=link, header=[_item("header", "H")])
    assert got["name"] == "header" and got["tried"] == ["repair", "link"]
    picker.args.claim = True                                                # every link claim lost to a peer
    monkeypatch.setattr(next_work, "claim_choice", lambda pool, label: (None, []) if label == "link-cycle repair"
                        else (pool[0], ["x"]))
    got = picker(["repair", "link", "header"], link=link, header=[_item("header", "H")])
    picker.args.claim = False
    assert got["name"] == "header" and got["tried"] == ["repair", "link"] and got["acquired"] == ["x"]


def test_debt_order_interleaves_every_lane_by_weight(monkeypatch):
    import collections
    import next_work
    monkeypatch.delenv("BFME_TIER_WEIGHTS", raising=False)
    monkeypatch.setenv("BFME_TIER_TUNING", "off")          # the priors; tools/tests/test_tier_tuning.py tunes
    rng = random.Random(20261024)
    firsts = collections.Counter()
    for _ in range(4000):
        order = next_work.debt_order(rng)
        assert order[0] == "repair" and sorted(order) == sorted(next_work.DEBT_TIERS)
        firsts[order[1]] += 1
    share = {name: firsts[name] / 4000 for name in next_work.TIER_WEIGHTS}
    total = sum(next_work.TIER_WEIGHTS.values())
    for name, weight in next_work.TIER_WEIGHTS.items():     # every lane, structural ones included
        assert abs(share[name] - weight / total) < 0.03, name
    others = [name for name in next_work.DEBT_TIERS[1:] if name != "header"]
    monkeypatch.setenv("BFME_TIER_WEIGHTS", ",".join(f"{name}=0" for name in others) + ",header=1")
    assert next_work.debt_order(rng) == ["repair", "header", *others]


def test_a_blocked_debt_item_is_served_last_and_a_dead_end_never(picker, monkeypatch):
    import next_work
    blocked, fresh, dead = _item("data", "Blocked"), _item("data", "Fresh"), _item("data", "Dead")
    monkeypatch.setattr(next_work.re_log, "is_deferred", lambda name, rva, **_: name == "Blocked")
    monkeypatch.setattr(next_work.re_log, "attempts", lambda name: 1)
    monkeypatch.setattr(next_work.re_log, "is_dead_end", lambda name, rva, **_: name == "Dead")
    for _ in range(20):
        got = picker(["data"], data=[blocked, fresh, dead])
        assert got["candidate"]["function"] == "Fresh" and got["suppressed"] == 1
    got = picker(["data"], data=[dict(blocked), dict(dead)])
    assert got["candidate"]["function"] == "Blocked"                        # only once nothing untried is left


def test_blocked_work_waits_for_the_untried_work_of_every_queue(picker, monkeypatch):
    """Item 7: a blocked repair item is not served before untried link, data or header work;
    deferred-only queues are retried, in order, once every queue's untried work is gone."""
    import next_work
    monkeypatch.setattr(next_work.re_log, "is_deferred", lambda name, rva, **_: name.startswith("Blocked"))
    monkeypatch.setattr(next_work.re_log, "attempts", lambda name: 1)
    blocked = _item("repair", "BlockedR")
    got = picker(["repair", "link", "data"], repair=[blocked], data=[_item("data", "Fresh")])
    assert got["candidate"]["function"] == "Fresh" and got["tried"] == ["repair", "link"]
    got = picker(["repair", "link", "data"], repair=[dict(blocked), _item("repair", "FreshR")],
                 data=[_item("data", "Fresh")])
    assert got["candidate"]["function"] == "FreshR"                         # the queue's own untried item first
    got = picker(["repair", "link", "data"], repair=[dict(blocked)], data=[_item("data", "BlockedD")])
    assert got["candidate"]["function"] == "BlockedR" and got["name"] == "repair"   # then in order
    picker.args.claim = True                                                # the untried data item lost to a peer
    monkeypatch.setattr(next_work, "claim_choice", lambda pool, label: (None, []) if
                        pool[0]["function"] == "Fresh" else (pool[0], ["x"]))
    got = picker(["repair", "data"], repair=[dict(blocked)], data=[_item("data", "Fresh")])
    picker.args.claim = False
    assert got["candidate"]["function"] == "BlockedR"


def test_an_empty_debt_order_reaches_the_new_match_tiers(monkeypatch, capsys):
    """W06: when every debt queue is empty or claimed, the default pick serves new matches."""
    import build
    import next_work
    import repair_queue
    monkeypatch.setattr(sys, "argv", ["next_work.py", "--json"])
    monkeypatch.setattr(next_work, "check_ledger", lambda: "ledger healthy")
    monkeypatch.setattr(next_work, "pick_debt", lambda order, args, busy: {
        "name": None, "label": next_work.EMPTY_LABEL, "pool": [], "candidate": None, "acquired": [],
        "tried": list(order), "suppressed": 0})
    monkeypatch.setattr(next_work, "busy_keys", lambda: set())
    drift = {"function": "?f@@YAXXZ", "source": "Code/X.cpp", "candidate_rva": "0x00401000", "aligned_pct": 99,
             "class": "imm", "hint": "h", "command": "c", "size": 16}
    monkeypatch.setattr(next_work, "drift_quick_wins", lambda: [drift])
    monkeypatch.setattr(build, "load_claim_rows", lambda **_: [])
    monkeypatch.setattr(next_work, "structural_candidates", lambda *a, **k: [])
    monkeypatch.setattr(next_work, "packet_candidates", lambda *a, **k: [])
    for name in ("reloc_named_candidates", "anchored_candidates", "ghidra_absent_candidates"):
        monkeypatch.setattr(next_work, name, lambda *a, **k: ([], ""))
    monkeypatch.setattr(next_work, "wpo_detect", None)
    monkeypatch.setattr(next_work, "drop_logged", lambda candidates: (candidates, 0))
    for name in ("annotate_attempts", "annotate_stashes", "annotate_wb"):
        monkeypatch.setattr(next_work, name, lambda candidates: candidates)
    monkeypatch.setattr(repair_queue, "annotate_dest", lambda candidates: candidates)
    next_work.main()
    out = json.loads(capsys.readouterr().out)
    assert out["tier"] == "drift quick win" and out["selection"]["function"] == "?f@@YAXXZ"


def test_debt_ranking_reaches_the_draw():
    import next_work
    first = next_work.candidate_weight({"tier": "header", "rank": 0, "ranks": 8, "size": 0})
    last = next_work.candidate_weight({"tier": "header", "rank": 7, "ranks": 8, "size": 0})
    assert first == 8 * last
    dup = next_work.candidate_weight({"tier": "data", "check": "duplicate-def", "keys_at_address": 3})
    one = next_work.candidate_weight({"tier": "data", "check": "wrong-name", "keys_at_address": 1})
    assert dup == 6 * one
    assert next_work.candidate_weight({"check": "vanished-source"}) > dup


# ---- next_work: an absent new-match input is skipped, never an exit; class: claims

def test_a_missing_drift_report_skips_its_tiers_with_a_note(tmp_path, monkeypatch):
    import next_work
    monkeypatch.setattr(next_work, "SKIPPED", [])
    monkeypatch.setattr(next_work, "DRIFT", tmp_path / "drift_report.csv")
    monkeypatch.setattr(next_work, "RELOC_NAMES", tmp_path / "reloc_names.csv")
    monkeypatch.setattr(next_work, "PACKETS", tmp_path / "packets")
    assert next_work.drift_quick_wins() == []
    assert next_work.structural_candidates(set(), set(), []) == []
    assert next_work.reloc_named_candidates(set(), [])[0] == []
    assert next_work.packet_candidates(set()) == []
    if next_work.GHIDRA_FUNCTIONS.exists() and next_work.STRING_XREFS.exists():
        assert next_work.ghidra_absent_candidates(set(), set())[0] == []
    tiers = [line.split(":")[0] for line in next_work.SKIPPED]
    assert {"harvest", "structural", "named", "packet"} <= set(tiers)
    assert all("absent, tier skipped" in line for line in next_work.SKIPPED)
    assert len(tiers) == len(set(tiers))                                     # one line per tier


def test_claim_takes_the_class_scope_of_a_class_scoped_item(fenced, monkeypatch):
    import claims
    import next_work
    asked = []
    monkeypatch.setattr(claims, "conflicts", lambda keys, root=None, who=None: {})

    def claim(targets, **_kwargs):
        asked.append(list(targets))
        key = claims.key_of(targets[0])
        return ([], [key]) if key == "class/Coord3D" else ([key], [])
    monkeypatch.setattr(claims, "claim", claim)
    monkeypatch.setattr(next_work, "weighted_choice", lambda candidates: candidates[0])
    work = [{"function": "Coord3D", "target_rva": "0x00002000", "claim": ["class:Coord3D"]},
            {"function": "AsciiString", "target_rva": "0x00001000", "claim": ["class:AsciiString"]},
            {"function": "?f@@YAXXZ", "target_rva": "0x00003000"}]
    assert next_work.claim_choice(work, "test") == (work[1], ["class/AsciiString"])
    assert [a[0] for a in asked] == ["class:Coord3D", "class:AsciiString"]   # a peer held Coord3D: next draw
    assert asked[0] == ["class:Coord3D"]                                  # class-only physical reservation
    assert next_work.claim_choice(work[2:], "test") == (work[2], [0x3000])   # no scope: the RVA, as before
    assert next_work.without_busy(work, {"class/Coord3D", 0x1000}) == work[2:]

    def offline(targets, **_kwargs):
        raise claims.ClaimsUnavailable("claims: offline", refused=["class/Coord3D"])
    monkeypatch.setattr(claims, "claim", offline)
    assert next_work.claim_choice(work, "test") == (work[1], [])             # known peer scope skipped


@pytest.mark.parametrize("kind", ["structural", "register-swap", "immediate-only"])
def test_unrelated_drift_candidates_do_not_take_a_fleet_class_lock(fenced, kind):
    import claims
    import next_work
    a, b = [{"function": f"f{i}", "source": f"Code/Unrelated{i}.cpp", "target_rva": hex(0x9000+i),
             "drift_class": kind} for i in range(2)]
    assert not claims.lock_keys(next_work.claim_keys(a)) & claims.lock_keys(next_work.claim_keys(b))
    assert all(not isinstance(k, str) or not k.startswith("class/") for k in next_work.claim_keys(a))
    # Exercise the real producers too: their classification fields cannot be passed as C++ class names.
    import inspect
    assert '"class": row["class"]' not in inspect.getsource(next_work)


@pytest.mark.parametrize("kind", ["data", "identity", "header"])
@pytest.mark.parametrize("accounting", ["transfer", "deleted", "trailer", "generic-trailer", "partial-trailer", "none"])
def test_disappearing_debt_requires_explicit_accounting(tmp_path, monkeypatch, kind, accounting):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES)
    git = _git_repo(tmp_path)
    source, dest = "Code/GameEngine/Body.cpp", "Code/Moved.cpp"
    if kind == "header":
        path = rev / "header_queue.tsv"
        lines = path.read_text().splitlines(True)
        key_lines = [line for line in lines if "\t" + source + "\t" in line]
    else:
        path = rev / ("data_check_baseline.txt" if kind == "data" else "code_identity_baseline.tsv")
        lines = path.read_text().splitlines(True)
        key_lines = [line for line in lines if line.startswith(source + "\t")]
    assert key_lines
    path.write_text("".join(line for line in lines if line not in key_lines) +
                    ("".join(line.replace(source, dest) for line in key_lines) if accounting == "transfer" else ""))
    (tmp_path / source).unlink()
    if accounting == "transfer":
        (tmp_path / dest).write_text("// moved\n")
    if accounting == "deleted":
        ledger = rev / "functions.csv"
        ledger.write_text("".join(line for line in ledger.read_text().splitlines(True) if source not in line))
        (rev / "deleted_rows.csv").write_text("name,target_rva,reason\n?c@Body@@QAEXXZ,0x00002000,retired\n")
    git("add", "-A")
    keys = [line.split("\t", 1)[0] if kind == "header" else line.rstrip("\n") for line in key_lines]
    message = "Verifier-Change: explain intentional retirement\n"
    if accounting in ("trailer", "partial-trailer"):
        message += "".join(f"Debt-Retired: {key} {source} redundant unit retired\n"
                           for key in (keys if accounting == "trailer" else keys[:-1]))
    refused = accounting in ("none", "generic-trailer", "partial-trailer")
    assert bool(rq.verify_missing_debt(message)) == refused
    # Pre-commit defers only missing units; commit-msg enforces the real message.
    monkeypatch.setattr(rq, "verdict_of", lambda *a: pytest.fail("vanished source was compiled"))
    assert rq.verify_removed_debt(defer_missing=True) == []
    if not refused:
        assert rq.verify_removed_debt(message=message) == []


@pytest.mark.parametrize("kind", ["data", "identity", "header"])
@pytest.mark.parametrize("change", ["deleted", "edited", "ledger", "header"])
def test_retirement_cannot_judge_unstaged_inputs(tmp_path, monkeypatch, kind, change):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES + [("Code/Include/C.h", "// staged\n")])
    git = _git_repo(tmp_path)
    source = "Code/GameEngine/Body.cpp"
    register = {"data": "data_check_baseline.txt", "identity": "code_identity_baseline.tsv",
                "header": "header_queue.tsv"}[kind]
    path = rev / register
    path.write_text("".join(line for line in path.read_text().splitlines(True) if source not in line))
    git("add", str(path))
    target = tmp_path / ({"ledger": "reverse/functions.csv", "header": "Code/Include/C.h"}.get(change, source))
    if change == "deleted":
        target.unlink()
    else:
        target.write_text("// unstaged replacement\n")
    monkeypatch.setattr(rq, "verdict_of", lambda *a: ([], set()))
    failures = rq.verify_removed_debt(build_cmd=[sys.executable, "-c", "pass"],
                                     header_verdict=lambda *a: [], defer_missing=True)
    assert failures and "staged" in " ".join(failures)
    assert rq.verify_missing_debt("Verifier-Change: explain intentional retirement\n")


def test_push_rechecks_retirement_over_outgoing_range(tmp_path, monkeypatch):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES)
    git = _git_repo(tmp_path)
    base = git("rev-parse", "HEAD").stdout.strip()
    source = "Code/GameEngine/Body.cpp"
    path = rev / "code_identity_baseline.tsv"
    path.write_text(path.read_text().replace(IDENTITY_KEY + "\n", ""))
    git("add", str(path))
    git("-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "Verifier-Change: testing range checks")
    tip = git("rev-parse", "HEAD").stdout.strip()
    # A clean index has no retirement diff against HEAD, but the outgoing range does.
    monkeypatch.setattr(rq, "verify_removed", lambda **kw: [])
    monkeypatch.setattr(rq, "verdict_of", lambda *a: ([], {IDENTITY_KEY}))
    def build(*args, **kwargs):
        return type("Result", (), {"returncode": 0})()
    real_run = rq.subprocess.run
    monkeypatch.setattr(rq.subprocess, "run", lambda cmd, **kw: real_run(cmd, **kw) if cmd[0] == "git" else build())
    assert rq.main(["verify-removed", "--range", base, tip]) == 1
    hook = (TOOLS.parent / ".githooks/pre-push").read_text()
    assert 'verify-removed --range "$base" "$local_sha"' in hook
    assert 'verify-missing --range "$base" "$local_sha"' in hook


@pytest.mark.parametrize("change", ["source", "header", "index"])
def test_retirement_rejects_inputs_changed_during_judgment(tmp_path, monkeypatch, change):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES + [("Code/Include/C.h", "// original\n")])
    git = _git_repo(tmp_path)
    path = rev / "code_identity_baseline.tsv"
    path.write_text(path.read_text().replace(IDENTITY_KEY + "\n", ""))
    git("add", str(path))
    def verdict(*args):
        target = tmp_path / ("Code/Include/C.h" if change == "header" else "Code/GameEngine/Body.cpp")
        target.write_text("// changed during judgment\n")
        if change == "index":
            git("add", str(target))
        return [], set()
    monkeypatch.setattr(rq, "verdict_of", verdict)
    failures = rq.verify_removed_debt(build_cmd=[sys.executable, "-c", "pass"])
    assert failures and "staged" in " ".join(failures)


@pytest.mark.parametrize("kind", ["data", "identity", "header"])
@pytest.mark.parametrize("dirty", ["unrelated-source", "submodule"])
def test_retirement_ignores_unrelated_dirty_work(tmp_path, monkeypatch, kind, dirty):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES)
    sub = tmp_path / "reference/open-bfme-1"
    sub.mkdir(parents=True)
    (sub / "input.h").write_text("// committed donor input\n")
    _git_repo(sub)
    git = _git_repo(tmp_path)
    source = "Code/GameEngine/Body.cpp"
    register = {"data": "data_check_baseline.txt", "identity": "code_identity_baseline.tsv",
                "header": "header_queue.tsv"}[kind]
    path = rev / register
    path.write_text("".join(line for line in path.read_text().splitlines(True) if source not in line))
    git("add", str(path))
    target = sub / "input.h" if dirty == "submodule" else tmp_path / "Code/GameEngine/Loco.cpp"
    target.write_text("// unrelated seat's uncommitted work\n")
    monkeypatch.setattr(rq, "unit_deps", lambda source: set())
    monkeypatch.setattr(rq, "verdict_of", lambda *a: ([], set()))
    assert rq.verify_removed_debt(build_cmd=[sys.executable, "-c", "pass"],
                                  header_verdict=lambda *a: []) == []
    assert rq.verify_missing_debt() == []


@pytest.mark.parametrize("staged_dependency", [False, True])
@pytest.mark.parametrize("hook_environment", [False, True])
def test_retirement_checks_recorded_submodule_input(tmp_path, monkeypatch, staged_dependency, hook_environment):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES)
    sub = tmp_path / "reference/open-bfme-1"
    sub.mkdir(parents=True)
    (sub / "input.h").write_text("// committed donor input\n")
    subgit = _git_repo(sub)
    git = _git_repo(tmp_path)
    if hook_environment:
        for key, value in {"GIT_DIR": tmp_path / ".git", "GIT_WORK_TREE": tmp_path,
                           "GIT_INDEX_FILE": tmp_path / ".git/index"}.items():
            monkeypatch.setenv(key, str(value))
    monkeypatch.setattr(rq, "unit_deps", lambda source: {"reference/open-bfme-1/input.h"})
    tree = rq._verification_tree()
    assert rq._verification_problems(tree, ["Code/GameEngine/Body.cpp"]) == []
    (sub / "input.h").write_text("// changed relevant donor input\n")
    if staged_dependency:
        import claims
        assert claims._git("add", "input.h", cwd=sub).returncode == 0
    assert "dependency blobs" in " ".join(rq._verification_problems(tree, ["Code/GameEngine/Body.cpp"]))


def test_retirement_checks_recorded_nonheader_input(tmp_path, monkeypatch):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES + [("assets/table.bin", "original")])
    _git_repo(tmp_path)
    monkeypatch.setattr(rq, "unit_deps", lambda source: {"assets/table.bin"})
    tree = rq._verification_tree()
    (tmp_path / "assets/table.bin").write_text("changed")
    assert rq._verification_problems(tree, ["Code/GameEngine/Body.cpp"])


@pytest.mark.parametrize("length", [0, 1, 19, 20, 30])
def test_debt_retired_reason_minimum_length(tmp_path, monkeypatch, length):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES)
    git = _git_repo(tmp_path)
    source = "Code/GameEngine/Body.cpp"
    path = rev / "data_check_baseline.txt"
    keys = rq.register_keys("data", path.read_text())
    keys = [key for key in keys if rq.key_source("data", key) == source]
    path.write_text("".join(line for line in path.read_text().splitlines(True) if source not in line))
    (tmp_path / source).unlink()
    git("add", "-u")
    message = "\n".join(f"Debt-Retired: {rq.key_line('data', key)} {source} {'x' * length}   " for key in keys)
    assert bool(rq.verify_missing_debt(message)) == (length < 20)


def test_retired_command_lists_committed_trailers_with_commit_ids(tmp_path, capsys):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES)
    git = _git_repo(tmp_path)
    for index in range(2):
        git("-c", "user.name=t", "-c", "user.email=", "commit", "--allow-empty", "-qm",
            f"Retire unused donor {index}\n\nDebt-Retired: key Code/Old.cpp redundant donor unit {index}")
    sha = git("rev-parse", "--short", "HEAD").stdout.strip()
    assert rq.main(["retired", "--limit", "1"]) == 0
    lines = capsys.readouterr().out.splitlines()
    assert lines == [f"{sha} Debt-Retired: key Code/Old.cpp redundant donor unit 1"]
    assert rq.main(["retired"]) == 0
    assert len(capsys.readouterr().out.splitlines()) == 2


@pytest.mark.parametrize("kind", ["data", "identity", "header"])
def test_transfer_requires_destination_in_index_not_just_worktree(tmp_path, monkeypatch, kind):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES)
    git = _git_repo(tmp_path)
    source, dest = "Code/GameEngine/Body.cpp", "Code/Untracked.cpp"
    path = rev / {"data": "data_check_baseline.txt", "identity": "code_identity_baseline.tsv",
                  "header": "header_queue.tsv"}[kind]
    path.write_text(path.read_text().replace(source, dest))
    (tmp_path / source).unlink()
    (tmp_path / dest).write_text("// exists only in working tree\n")
    git("add", "-u")
    assert rq.verify_missing_debt("Verifier-Change: this cannot explain debt\n")
    git("add", dest)
    assert rq.verify_missing_debt() == []


MERGE_PAYLOAD = {
    "classes": {
        "AsciiString": {"donors": 40, "rows": 90, "tus": ["Code/T.cpp"], "kinds": {"canonical-copy": 1},
                        "bases": [], "files": ["Code/GameEngine/Loco.cpp"]},
        "Coord3D": {"donors": 2, "rows": 3, "tus": ["Code/T.cpp"], "kinds": {"canonical-copy": 1},
                    "bases": [], "files": ["Code/GameEngine/Body.cpp"]},
        "UpdateModule": {"donors": 300, "rows": 900, "tus": ["Code/U.cpp", "Code/V.cpp"], "kinds": {"base": 2},
                         "bases": ["BehaviorModule"], "files": ["Code/U.cpp", "Code/U_xfer.cpp"], "virtual": True},
        "BehaviorModule": {"donors": 5, "rows": 9, "tus": ["Code/U.cpp"], "kinds": {"base": 1}, "bases": [],
                           "files": ["Code/U.cpp"], "virtual": False},
        "Plain": {"donors": 3, "rows": 3, "tus": ["Code/P.cpp"], "kinds": {"base": 1}, "bases": [],
                  "files": ["Code/P.cpp"], "virtual": False},
        "Contracted": {"donors": 2, "rows": 2, "tus": ["Code/Q.cpp"], "kinds": {"base": 1}, "bases": [],
                       "files": ["Code/Q.cpp"], "virtual": False},
        "Uncensused": {"donors": 4, "rows": 4, "tus": ["Code/W.cpp"], "kinds": {"base": 1}, "bases": [],
                       "files": ["Code/W.cpp"]}},
    # run --apply rewrites every census unit, including ones no merge donor names
    "census": {"UpdateModule": ["Code/U.cpp", "Code/Elsewhere/NoRows.cpp"], "BehaviorModule": ["Code/U.cpp"],
               "Plain": ["Code/P.cpp"], "Contracted": ["Code/Q.cpp"]},
    "destinations": {"UpdateModule": {"header": "Code/GameEngine/Include/GameLogic/Module/UpdateModule.h",
                                      "evidence": "bfme1: game/GameEngine/Include/GameLogic/Module/UpdateModule.h"},
                     "BehaviorModule": {"header": None, "why": "bfme1 defines BehaviorModule in 2 headers"},
                     "Plain": {"header": "Code/GameEngine/Include/Common/Plain.h", "evidence": "zh: Plain.h"},
                     "Contracted": {"header": "Code/GameEngine/Include/Common/Contracted.h", "evidence": "zh: C.h"}},
}


def _merge_lane(rq, monkeypatch, payload, note=""):
    import header_adopt_lane
    contracts = Path(rq.ROOT) / "reverse/class_contracts"
    contracts.mkdir(parents=True, exist_ok=True)
    (contracts / "Contracted.json").write_text(json.dumps({"fields": [{"kind": "VPTR"}], "vslots": {"0": {}}}))
    monkeypatch.setattr(header_adopt_lane.class_contract, "CONTRACTS", contracts)
    monkeypatch.setattr(header_adopt_lane, "ROOT", Path(rq.ROOT))
    monkeypatch.setattr(header_adopt_lane, "registered", lambda: {"Coord3D": "Coord3D.h", "AsciiString": "a.h"})
    monkeypatch.setattr(header_adopt_lane, "merge_payload_nonblocking", lambda: (payload, note))
    monkeypatch.setattr(header_adopt_lane, "merge_payload", lambda refresh=False: pytest.fail("the picker computed"))


def test_header_items_rank_by_merge_donors_and_serve_headerless_blockers(tmp_path, monkeypatch):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES)
    import next_work
    _merge_lane(rq, monkeypatch, MERGE_PAYLOAD)
    items, note = rq.header_items()
    queued = [(i["class"], i["source"]) for i in items if i["check"] == "class-header"]
    # Coord3D's two donors rank with AsciiString's 40, and first: DEPENDENCY_ORDER puts value types before strings
    assert queued == [("Coord3D", "Code/GameEngine/Body.cpp"), ("AsciiString", "Code/GameEngine/Loco.cpp")]
    assert [i["merge_donors"] for i in items if i["check"] == "class-header"] == [40, 40]
    establish = {i["class"]: i for i in items if i["check"] == "class-header-establish"}
    assert [(i["class"], i["merge_donors"]) for i in items if i["check"] == "class-header-establish"] == [
        ("BehaviorModule", 300), ("UpdateModule", 300), ("Plain", 3), ("Contracted", 2)]  # not Uncensused
    assert "1 more without a cached census not served" in note
    assert "4 class(es) without a header ranked by merge donors" in note
    um = establish["UpdateModule"]
    assert um["claim"] == ["class:UpdateModule", "file:Code/Elsewhere/NoRows.cpp",
                           "file:Code/GameEngine/Include/GameLogic/Module/UpdateModule.h",
                           "file:Code/U.cpp", "file:Code/U_xfer.cpp"]
    # polymorphic: generate() writes no virtuals, so the header is written by hand and adopted as given
    assert "generate() emits no virtual functions" in um["obstacle"] and "OBSTACLE" in um["why"]
    assert "by hand at Code/GameEngine/Include/GameLogic/Module/UpdateModule.h" in um["start"]
    assert "--header Code/GameEngine/Include/GameLogic/Module/UpdateModule.h --sample 60 (no --generate)" in um["start"]
    assert " --generate --sample" not in um["start"]
    plain, contracted = establish["Plain"], establish["Contracted"]
    assert "obstacle" not in plain and "--header Code/GameEngine/Include/Common/Plain.h --generate" in plain["start"]
    assert "obstacle" in contracted and " --generate --sample" not in contracted["start"]   # its contract has slots
    bm = establish["BehaviorModule"]
    assert "--header" not in bm["start"].split("then python3")[0] and "dest --class BehaviorModule" in bm["start"]
    assert "never invent" in bm["start"] and "class_contract.py --class BehaviorModule" in bm["start"]
    assert "canonical_classes.csv registers BehaviorModule" in bm["pass_test"]
    factor = {i["class"]: next_work.debt_rank_factor(i) for i in items if i["check"] != "vanished-source"}
    assert factor["UpdateModule"] == 10 and factor["BehaviorModule"] == 10  # 1 + bit length of the donors
    assert factor["AsciiString"] == max(7, items[2]["ranks"] - items[2]["rank"])  # the larger of the two weights
    assert next_work.debt_rank_factor({"tier": "header", "rank": 0, "ranks": 9}) == 9


def test_header_items_on_a_cache_miss_rank_by_dependency_order_only(tmp_path, monkeypatch):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES)
    _merge_lane(rq, monkeypatch, None, "merge ranking not cached for this tree, DEPENDENCY_ORDER only; "
                                       "a background refresh started")
    items, note = rq.header_items()
    assert [(i["class"], i["merge_donors"]) for i in items if i["check"] == "class-header"] == [
        ("Coord3D", 0), ("AsciiString", 0)]
    assert not [i for i in items if i["check"] == "class-header-establish"]
    assert "DEPENDENCY_ORDER only" in note


def test_header_claim_includes_queued_private_views_without_member_rows(tmp_path, monkeypatch, seats):
    import claims
    import next_work
    rq, rev, _ = load(tmp_path / "queue", "bfme2", LEDGER, DEBT_FILES + [("Code/Bar.cpp", "struct Coord3D {};\n")])
    queue = rev / "header_queue.tsv"
    with queue.open("a") as handle:
        handle.write("Coord3D\tCode/Bar.cpp\t\tCoord3D.h\tprivate view\t3\tx\n")
    header = next(i for i in rq.header_items()[0] if i.get("class") == "Coord3D"
                  and i["source"] == "Code/GameEngine/Body.cpp")
    assert claims.file_key("Code/Bar.cpp") in next_work.claim_keys(header)
    seats("header")
    assert claims.acquire(next_work.claim_targets(header), next_work.claim_keys(header)).claimed
    seats("body")
    body = {"source": "Code/Bar.cpp", "target_rva": "0x9000", "function": "?f@@YAXXZ"}
    assert next_work.claim_choice([body], "test") == (None, [])


def test_header_verdict_uses_head_helpers_despite_worktree_edits(tmp_path, monkeypatch):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER)
    tools = tmp_path / "tools"
    tools.mkdir()
    (tools / "class_layouts.py").write_text('answer = "HEAD layout"\n')
    (tools / "class_contract.py").write_text('import class_layouts\nanswer = class_layouts.answer\n')
    (tools / "header_adopt_lane.py").write_text(
        'import class_contract\ndef verdict(name, source):\n    return [class_contract.answer]\n')
    _git_repo(tmp_path)
    for path in tools.glob("*.py"):
        path.write_text('raise AssertionError("working-tree helper executed")\n')
    assert rq._head_header_verdict("C", "Code/A.cpp") == ["HEAD layout"]


def test_deferred_hook_checks_run_in_commit_msg():
    root = Path(__file__).resolve().parents[2]
    assert "debt_args=(--defer-missing)" in (root / ".githooks/pre-commit").read_text()
    assert 'verify-missing "$1"' in (root / ".githooks/commit-msg").read_text()


@pytest.mark.parametrize("kind", ["data", "identity", "header"])
def test_debt_can_follow_a_rehomed_row_while_old_source_still_exists(tmp_path, monkeypatch, kind):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, DEBT_FILES)
    git = _git_repo(tmp_path)
    source, dest = "Code/GameEngine/Body.cpp", "Code/Rehomed.cpp"
    (tmp_path / dest).write_text("// rehomed body\n")
    register = {"data": "data_check_baseline.txt", "identity": "code_identity_baseline.tsv",
                "header": "header_queue.tsv"}[kind]
    path = rev / register
    path.write_text(path.read_text().replace(source, dest))
    ledger = rev / "functions.csv"
    ledger.write_text(ledger.read_text().replace(source, dest))
    git("add", "-A")
    assert (tmp_path / source).exists()
    monkeypatch.setattr(rq, "verdict_of", lambda *a: pytest.fail("unchanged source was treated as a repair"))
    assert rq.verify_removed_debt(header_verdict=lambda *a: pytest.fail("transfer mistaken for adoption")) == []


# Microsoft-header migrations use the same logical file locks as the debt picker.
def ms_header_fixture(tmp_path):
    import csv
    import ms_header_audit
    files = [("Code/GameEngine/Body.cpp", "// body\n"), ("Code/GameEngine/Loco.cpp", "// loco\n")]
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, files)
    rows = [("Code/GameEngine/Loco.cpp", "adapt", "20"),
            ("Code/Missing.cpp", "drop-in candidate", "100"),
            ("Code/GameEngine/Body.cpp", "drop-in candidate", "2")]
    with (rev / "ms_header_queue.tsv").open("w", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=ms_header_audit.QUEUE_HEADER, delimiter="\t")
        writer.writeheader()
        for source, classification, defs in rows:
            writer.writerow(dict(file=source, **{"class": classification}, defs=defs,
                                 headers="<windows.h>", platformsdk="yes", names="DWORD:same"))
    return rq


def test_ms_header_items_rank_real_files_and_fence_rvas(tmp_path, fenced):
    import claims
    import next_work
    rq = ms_header_fixture(tmp_path)
    items = rq.ms_header_items()
    assert [i["classification"] for i in items] == ["drop-in candidate", "adapt"]
    assert "class" not in items[0]  # a migration category must never become class:drop-in candidate
    assert items[0]["claim"] == ["file:Code/GameEngine/Body.cpp"]
    assert rq.ms_header_items("adapt") == [items[1]]
    fenced[0x2000] = {"owner": "peer"}
    assert next_work.without_busy(items, claims.busy_keys()) == [items[1]]
    assert "./build.sh" in items[0]["pass_test"]


def test_ms_headers_cli_claim_retries_atomic_file_contention(tmp_path, seats, monkeypatch, capsys):
    import claims
    import next_work
    rq = ms_header_fixture(tmp_path)
    items = rq.ms_header_items()
    seats("a")
    assert next_work.claim_choice([items[0]], "ms-headers")[0] == items[0]
    seats("b")
    monkeypatch.setattr(claims, "settle", lambda **_: None)
    monkeypatch.setattr(next_work, "busy_keys", lambda: set())  # stale view; acquire must arbitrate
    assert rq.main(["ms-headers", "--claim"]) == 0
    out = capsys.readouterr()
    assert "held by another worker" in out.err
    assert "claim held: file:Code/GameEngine/Loco.cpp" in out.out
    owners = seats.on_origin()
    assert owners[claims.file_key("Code/GameEngine/Body.cpp")] == "a"
    assert owners[claims.file_key("Code/GameEngine/Loco.cpp")] == "b"
    assert not any(key.startswith("class/") for key in owners)


def test_root_from_stdin_uses_cwd_even_when_file_is_a_pseudo_path(tmp_path):
    """The pre-push hook pipes HEAD's repair_queue.py into `python3 -`. Python 3.13 sets
    __file__ to "<stdin>" there; resolving it put ROOT one directory above the checkout,
    so every outgoing debt retirement failed with "cannot read outgoing retirement messages"."""
    source = (TOOLS / "repair_queue.py").read_text(encoding="utf-8")
    old = os.getcwd()
    os.chdir(tmp_path)
    env_root = os.environ.pop("REPAIR_ROOT", None)
    try:
        scope = {"__file__": "<stdin>", "__name__": "repair_queue_stdin_probe"}
        exec(compile(source, "<stdin>", "exec"), scope)
        assert Path(scope["ROOT"]).resolve() == tmp_path.resolve()
    finally:
        os.chdir(old)
        if env_root is not None:
            os.environ["REPAIR_ROOT"] = env_root


def test_verification_diff_chunks_long_pathspecs_below_the_windows_limit():
    """A 186-source retirement read so many dependency paths that the inputs check
    hit CreateProcess's 32,767-character cap (WinError 206) and refused every key.
    Each git diff now gets a pathspec chunk under the budget; any chunk that
    differs (or fails) still fails closed."""
    import repair_queue
    paths = [f"inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/H{i:05}.h"
             for i in range(3000)]
    chunks = list(repair_queue._pathspec_chunks(paths))
    assert len(chunks) > 1 and [p for c in chunks for p in c] == paths
    assert all(sum(len(p) + 1 for p in c) <= repair_queue._PATHSPEC_BUDGET for c in chunks)

    class Result:
        def __init__(self, code):
            self.returncode = code

    seen = []
    assert not repair_queue._diff_differs(lambda a: seen.append(a) or Result(0), ["git", "diff"], paths)
    assert len(seen) == len(chunks) and all(a[:3] == ["git", "diff", "--"] for a in seen)
    calls = iter([0, 1] + [0] * len(chunks))
    assert repair_queue._diff_differs(lambda a: Result(next(calls)), ["git", "diff"], paths)



@pytest.mark.parametrize("layout", ["bfme1", "bfme2"])
@pytest.mark.parametrize("target_eol", [b"\n", b"\r\n"])
@pytest.mark.parametrize("last_eol", [b"\n", b"\r\n", b""])
@pytest.mark.parametrize("returncode", [0, 1])
def test_pass_test_removes_only_target_with_mixed_line_endings(
        tmp_path, monkeypatch, layout, target_eol, last_eol, returncode):
    rq, rev, src = load(tmp_path, layout, LEDGER)
    if layout == "bfme1":
        path = rev / "body_guard_baseline.csv"
        header = b"check,target_rva,name,detail\r\n"
        line = "tail,0x00001000,?a@Loco@@QAEXXZ,tail mismatch"
        other = b"strnul,0x00002000,?c@Body@@QAEXXZ,literal mismatch"
    else:
        path = rev / "gate_baseline.txt"
        header = b"# gate debt\r\n"
        line = "tail 0x00001000 ?a@Loco@@QAEXXZ"
        other = b"strnul 0x00002000 ?c@Body@@QAEXXZ"
    raw = header + line.encode() + target_eol + other + last_eol
    expected = header + other + last_eol
    path.write_bytes(raw)
    calls = []

    def run_gate(command, **kwargs):
        # The normal checker must see the exemption removed, while all other
        # bytes (including a missing final newline) retain their original form.
        assert command == [sys.executable, str(tmp_path / "tools/build.py"),
                           f"{src}/GameEngine/Loco.cpp"]
        assert path.read_bytes() == expected
        calls.append(command)
        return rq.subprocess.CompletedProcess(command, returncode)

    monkeypatch.setattr(rq.subprocess, "run", run_gate)
    ok, _ = rq.pass_test(line)
    assert len(calls) == 1
    assert ok == (returncode == 0)
    assert path.read_bytes() == (expected if ok else raw)
