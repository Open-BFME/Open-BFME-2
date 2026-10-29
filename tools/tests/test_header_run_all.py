"""header_adopt_lane run --all: ordering, claims, the link-check drop, the decision queue, resume."""
import json
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_contract  # noqa: E402
import header_adopt_lane as lane  # noqa: E402


def contract(name, queue=()):
    return {"class": name, "key": "class", "key_by": "bytes", "size": 4, "size_by": "majority", "bases": [],
            "fields": [], "vslots": {}, "queue": list(queue), "evidence": {}}


def args(**kw):
    base = dict(dry_run=False, sample=None, seed=1, unit_jobs=1, variants="data", trailer=None, only=None,
                resume=False, limit=None, jobs=1, budget_min=None)
    base.update(kw)
    return SimpleNamespace(**base)


@pytest.fixture
def world(tmp_path, monkeypatch):
    """A tree under tmp_path with fake evidence: every heavy step is a recorded fake."""
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(lane, "REGISTRY", tmp_path / "reverse" / "canonical_classes.csv")
    monkeypatch.setattr(lane, "QUEUE", tmp_path / "reverse" / "header_queue.tsv")
    monkeypatch.setattr(lane, "LEDGER", tmp_path / "reverse" / "functions.csv")
    monkeypatch.setattr(class_contract, "ROOT", tmp_path)
    monkeypatch.setattr(class_contract, "CONTRACTS", tmp_path / "reverse" / "class_contracts")
    w = SimpleNamespace(root=tmp_path, registered={}, claimed_by={}, contracts={}, units={}, tournaments=[],
                        link={}, commits=[], queued={}, released=[], verdicts={})
    monkeypatch.setattr(lane, "registered", lambda: dict(w.registered))
    monkeypatch.setattr(lane, "claim_class", lambda name: w.claimed_by.get(f"class:{name}"))
    monkeypatch.setattr(lane, "held_elsewhere", lambda keys: {k: w.claimed_by[k] for k in keys if k in w.claimed_by})
    monkeypatch.setattr(class_contract, "census", lambda name, rows=None: list(w.units.get(name, ())))
    monkeypatch.setattr(class_contract, "decide", lambda name, sources=None, jobs=8: w.contracts[name])

    def tournament(name, c, sources, header, variants, jobs, fixed_header=False):
        w.tournaments.append(name)
        verdicts = {s: w.verdicts.get(s) for s in sources}
        return {"data": {"verdicts": verdicts, "texts": {s: f"#include \"{header}\"\n// adopted\n" for s in sources},
                         "renames": {}, "header": f"// {name}\n", "seconds": 0}}

    monkeypatch.setattr(lane, "tournament", tournament)
    monkeypatch.setattr(lane, "claim_rewrites", lambda name, files: [])
    monkeypatch.setattr(lane, "release_rewrites", lambda name: w.released.append(name) or 0)
    monkeypatch.setattr(lane, "register", lambda name, header, note: w.registered.__setitem__(name, header))
    monkeypatch.setattr(lane, "rewrite_ledger", lambda renames: None)
    monkeypatch.setattr(lane, "write_queue", lambda name, header, failures: w.queued.__setitem__(name, dict(failures)))

    def commit(paths, message):
        w.commits.append((list(paths), message))
        return True, f"{len(w.commits):040d}", ""

    w.ctx = lambda blockers, ranked: {
        "blockers": blockers, "ranked": ranked, "rows": [],
        "destination": lambda n: {"header": f"Code/Include/{n}.h", "evidence": "test"},
        "link_check": lambda sources: {s: w.link.get(s, True) for s in sources},
        "commit": commit, "undo": lambda paths, new_header=None: None,
        "state_path": tmp_path / "state.json", "decisions_path": tmp_path / "reverse" / "header_decisions.jsonl"}

    def unit(name, *sources):
        w.units[name] = list(sources)
        w.contracts.setdefault(name, contract(name))
        for s in sources:
            (tmp_path / s).parent.mkdir(parents=True, exist_ok=True)
            (tmp_path / s).write_text(f"class {name} {{ int x; }};\n", encoding="latin-1")

    w.unit = unit
    return w


def test_plan_order_never_puts_a_class_before_its_base():
    blockers = {"Derived": {"bases": ["Base"]}, "Base": {"bases": []}, "Other": {}, "Done": {"bases": []}}
    ranked = [("Derived", 50, 50), ("Other", 40, 40), ("Base", 30, 30), ("Done", 20, 20)]
    assert lane.plan_order(ranked, blockers, {"Done": "x.h"}) == ["Base", "Derived", "Other"]
    # a virtual base spelling still names its class
    assert lane.plan_order([("D", 2, 2), ("B", 1, 1)], {"D": {"bases": ["virtual B"]}}, {}) == ["B", "D"]


def test_batches_share_no_file_and_wait_for_a_pending_base():
    order = ["A", "B", "C", "D"]
    files = {"A": {"a.cpp"}, "B": {"a.cpp"}, "C": {"c.cpp"}, "D": {"d.cpp"}}
    needs = {"D": {"A"}}
    batches = lane.bulk_batches(order, files, needs, jobs=3)
    assert batches[0] == ["A", "C"]                      # B shares a.cpp, D needs A
    assert all(not (files[x] & files[y]) for b in batches for x in b for y in b if x != y)
    flat = [c for b in batches for c in b]
    assert flat.index("A") < flat.index("D") and sorted(flat) == order


def test_claimed_class_is_skipped_and_recorded(world):
    world.unit("Held", "Code/held.cpp")
    world.unit("Free", "Code/free.cpp")
    world.claimed_by["class:Held"] = "seat-7"
    ctx = world.ctx({}, [("Held", 9, 9), ("Free", 5, 5)])
    assert lane.run_all(args(), ctx) == 0
    assert world.tournaments == ["Free"]
    rows = lane.read_decisions(ctx["decisions_path"])
    assert [(r["class"], r["kind"], r["holder"]) for r in rows] == [("Held", "claimed", "seat-7")]
    assert json.loads(ctx["state_path"].read_text())["Held"]["status"] == "claimed"


def test_held_units_are_left_out_of_the_class(world):
    world.unit("Cls", "Code/a.cpp", "Code/b.cpp")
    world.claimed_by["file:Code/b.cpp"] = "seat-2"
    ctx = world.ctx({}, [("Cls", 3, 3)])
    lane.run_all(args(), ctx)
    paths, _ = world.commits[0]
    assert "Code/a.cpp" in paths and "Code/b.cpp" not in paths
    assert (world.root / "Code/b.cpp").read_text(encoding="latin-1").startswith("class Cls")
    assert world.queued["Cls"]["Code/b.cpp"].startswith("held by seat-2")      # S4: queued, not forgotten


def test_a_claim_on_the_header_or_on_a_units_rows_or_class_is_respected(world):
    import claims
    world.unit("Hdr", "Code/h.cpp")
    world.unit("Cls", "Code/a.cpp", "Code/b.cpp")
    ctx = world.ctx({}, [("Hdr", 5, 5), ("Cls", 3, 3)])
    ctx["busy"] = {claims.key_of("file:Code/Include/Hdr.h"), claims.key_of("file:Code/b.cpp")}
    lane.run_all(args(), ctx)
    assert world.tournaments == ["Cls"]                      # Hdr's header is held: no tournament writes it
    assert "Code/b.cpp" not in world.commits[0][0] and "Code/b.cpp" in world.queued["Cls"]
    assert json.loads(ctx["state_path"].read_text())["Hdr"]["status"] == "claimed"


def test_claims_are_read_afresh_for_each_class_and_the_header_is_held_before_the_tournament(world, monkeypatch):
    import claims
    world.unit("First", "Code/f.cpp")
    world.unit("Second", "Code/s.cpp")
    world.unit("Third", "Code/t.cpp")
    reads = iter([set(), {claims.key_of("file:Code/Include/Second.h")}, set()])
    ctx = world.ctx({}, [("First", 9, 9), ("Second", 5, 5), ("Third", 3, 3)])
    ctx["busy"] = lambda: next(reads)              # Second's header is claimed while First runs
    monkeypatch.setattr(lane, "claim_rewrites",
                        lambda name, files: [(files[0], "seat-9")] if files == ["Code/Include/Third.h"] else [])
    lane.run_all(args(), ctx)
    assert world.tournaments == ["First"]           # Second: held at its turn; Third: its header claim refused
    state = json.loads(ctx["state_path"].read_text())
    assert state["Second"]["status"] == state["Third"]["status"] == "claimed"


def test_a_refused_decision_queue_commit_fails_the_pass_and_unstages_the_queue(world, capsys):
    world.unit("Big", "Code/b.cpp")
    world.contracts["Big"] = contract("Big", [{"class": "Big", "attribute": "size", "candidates": {"8": 1, "4": 1}}])
    unstaged = []
    ctx = world.ctx({}, [("Big", 4, 4)])
    ctx["commit"] = lambda paths, message: (False, None, "PRE-COMMIT REFUSED")
    ctx["unstage"] = unstaged.extend
    assert lane.run_all(args(), ctx) == 1
    assert unstaged == ["reverse/header_decisions.jsonl"] and "left unstaged" in capsys.readouterr().out


def test_jobs_run_one_class_at_a_time(world, capsys):
    world.unit("A", "Code/a.cpp")
    world.unit("B", "Code/b.cpp")
    a = args(jobs=4)
    lane.run_all(a, world.ctx({}, [("A", 2, 2), ("B", 1, 1)]))
    assert a.jobs == 1 and "one class at a time" in capsys.readouterr().out


def test_the_guard_refuses_any_staged_or_uncommitted_code_or_reverse_edit(monkeypatch):
    monkeypatch.setattr(lane, "_git", lambda *a: " M Code/x.cpp" if a[0] == "status" else "")
    assert lane.bulk_guard()
    monkeypatch.setattr(lane, "_git", lambda *a: "tools/x.py" if a[0] == "diff" else "")
    assert lane.bulk_guard()
    monkeypatch.setattr(lane, "_git", lambda *a: "")
    assert not lane.bulk_guard()


def test_link_regression_drops_the_unit_and_keeps_the_rest(world):
    world.unit("Iface", "Code/keep.cpp", "Code/regress.cpp", "Code/unknown.cpp", "Code/fails.cpp")
    world.verdicts["Code/fails.cpp"] = "error C2065: 'x' : undeclared identifier"
    world.link.update({"Code/regress.cpp": False, "Code/unknown.cpp": None})
    ctx = world.ctx({}, [("Iface", 12, 4)])
    assert lane.run_all(args(), ctx) == 0
    paths, message = world.commits[0]
    assert "Code/keep.cpp" in paths
    assert not {"Code/regress.cpp", "Code/unknown.cpp", "Code/fails.cpp"} & set(paths)
    assert "adopted" in (world.root / "Code/keep.cpp").read_text(encoding="latin-1")
    for dropped in ("Code/regress.cpp", "Code/unknown.cpp"):    # restored byte for byte
        assert (world.root / dropped).read_text(encoding="latin-1") == "class Iface { int x; };\n"
    queued = world.queued["Iface"]
    assert queued["Code/regress.cpp"].startswith("link regression") and queued["Code/unknown.cpp"].startswith("link unverified")
    assert "Code/fails.cpp" in queued and "2 dropped by the link check" in message
    # The class is registered now: its dropped units are header-queue rows, not a class decision.
    assert lane.read_decisions(ctx["decisions_path"]) == []
    state = json.loads(ctx["state_path"].read_text())["Iface"]
    assert state["status"] == "adopted" and state["kind"] == "link-regression"


def test_class_whose_every_unit_regresses_is_queued_and_its_header_removed(world):
    world.unit("Bad", "Code/only.cpp")
    world.link["Code/only.cpp"] = False
    ctx = world.ctx({}, [("Bad", 2, 2)])
    lane.run_all(args(), ctx)
    assert [paths for paths, _ in world.commits] == [["reverse/header_decisions.jsonl"]]
    assert "Bad" not in world.registered and world.released == ["Bad"]
    assert not (world.root / "Code/Include/Bad.h").exists()
    assert (world.root / "Code/only.cpp").read_text(encoding="latin-1") == "class Bad { int x; };\n"
    assert lane.read_decisions(ctx["decisions_path"])[0]["kind"] == "link-regression"


def test_decision_queue_records_the_competing_evidence_ranked_by_donors(world):
    world.unit("Small", "Code/s.cpp")
    world.unit("Big", "Code/b.cpp")
    world.contracts["Small"] = contract("Small", [{"class": "Small", "attribute": "size", "candidates": {"8": 2, "12": 2}}])
    world.contracts["Big"] = contract("Big", [
        {"class": "Big", "attribute": "slot3", "candidates": {"xfer(Xfer*)": 2, "s03()": 2}},
        {"class": "Big", "attribute": "field@0x8", "candidates": {"4:f4": 1, "4:i4": 1}}])
    ctx = world.ctx({}, [("Small", 5, 5), ("Big", 40, 40)])
    lane.run_all(args(), ctx)
    rows = lane.read_decisions(ctx["decisions_path"])
    assert [r["class"] for r in rows] == ["Big", "Small"]           # by merge donors unblocked
    big = rows[0]
    assert big["kind"] == "undecided" and big["detail"] == "decide slot3 of Big (+1 more)"
    assert big["attributes"][0] == {"attribute": "slot3", "candidates": {"xfer(Xfer*)": 2, "s03()": 2}}
    assert big["merge_donors"] == 40 and big["resume"].endswith("--only Big")
    assert big["contract"].startswith("not written yet: python3 tools/class_contract.py --class Big")
    assert world.tournaments == []
    assert world.commits[-1][0] == ["reverse/header_decisions.jsonl"]     # the queue is committed for other seats


def test_base_without_a_header_waits(world, monkeypatch):
    world.unit("Kid", "Code/k.cpp")
    world.contracts["Kid"] = dict(contract("Kid"), bases=["Parent"])
    ctx = world.ctx({}, [("Kid", 3, 3)])
    lane.run_all(args(), ctx)
    (row,) = lane.read_decisions(ctx["decisions_path"])
    assert row["kind"] == "base-unheadered" and row["bases"] == ["Parent"]
    assert json.loads(ctx["state_path"].read_text())["Kid"]["status"] == "waiting"    # --resume retries it


def test_resume_skips_classes_a_pass_finished(world):
    world.unit("Done", "Code/d.cpp")
    world.unit("Next", "Code/n.cpp")
    ctx = world.ctx({}, [("Done", 9, 9), ("Next", 5, 5)])
    ctx["state_path"].write_text(json.dumps({"Done": {"status": "queued"}}))
    lane.run_all(args(resume=True), ctx)
    assert world.tournaments == ["Next"]


def test_dry_run_claims_writes_and_commits_nothing(world, monkeypatch):
    world.unit("Cls", "Code/c.cpp")
    monkeypatch.setattr(lane, "claim_class", lambda name: pytest.fail("a dry run claimed"))
    ctx = world.ctx({}, [("Cls", 3, 3)])
    lane.run_all(args(dry_run=True), ctx)
    assert world.tournaments == [] and world.commits == [] and not ctx["state_path"].exists()


def test_budget_stops_before_the_next_class(world, monkeypatch):
    world.unit("A", "Code/a.cpp")
    world.unit("B", "Code/b.cpp")
    clock = iter([0.0] + [10_000.0] * 50)
    monkeypatch.setattr(lane.time, "time", lambda: next(clock))
    ctx = world.ctx({}, [("A", 2, 2), ("B", 1, 1)])
    lane.run_all(args(budget_min=1), ctx)
    assert world.tournaments == []


def test_refused_commit_is_undone_and_recorded(world):
    world.unit("Cls", "Code/c.cpp")
    undone = []
    ctx = world.ctx({}, [("Cls", 3, 3)])
    ctx["commit"] = lambda paths, message: (False, None, "PRE-COMMIT REFUSED: bytes")
    ctx["undo"] = lambda paths, new_header=None: undone.append((paths, new_header))
    lane.run_all(args(), ctx)
    (row,) = lane.read_decisions(ctx["decisions_path"])
    assert row["kind"] == "commit-refused" and "REFUSED" in row["hook_tail"]
    assert undone and undone[0][1] == "Code/Include/Cls.h"


def test_write_decisions_drops_registered_classes(tmp_path):
    path = tmp_path / "d.jsonl"
    lane.write_decisions({"A": {"class": "A", "kind": "undecided", "merge_donors": 1}}, path, canon=set())
    lane.write_decisions({"B": {"class": "B", "kind": "claimed", "merge_donors": 3}}, path, canon={"A"})
    assert [r["class"] for r in lane.read_decisions(path)] == ["B"]


if __name__ == "__main__":
    sys.exit(pytest.main([__file__, "-q"]))
