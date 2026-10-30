"""merge_all (tu_skeleton --merge-all): planning, waves, decisions, state, integration and the worker."""
import json
import subprocess
import sys
import threading
import time
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import merge_all as M  # noqa: E402

HEADER = "name,target_rva,target_size,source,status\n"


def git(cwd, *args):
    return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True).stdout.strip()


def repo(path, files):
    path.mkdir(parents=True, exist_ok=True)
    git(path, "init", "-q", "-b", "main")
    git(path, "config", "user.email", "t@example.com")
    git(path, "config", "user.name", "t")
    git(path, "config", "core.autocrlf", "false")
    for rel, text in files.items():
        (path / rel).parent.mkdir(parents=True, exist_ok=True)
        (path / rel).write_text(text, newline="\n")
    git(path, "add", "-A")
    git(path, "commit", "-q", "-m", "base")
    return path


def ledger(rows):
    return HEADER + "".join(f"{n},{r},8,{s},matched\n" for n, r, s in rows)


@pytest.fixture(autouse=True)
def private_cache(tmp_path, monkeypatch):
    """Decisions go to a private picker cache, never the clone's shared one."""
    monkeypatch.setenv("BFME_PICKER_CACHE", str(tmp_path / "picker-cache"))


# ---- the fake tu_skeleton the coordinator drives

class FakeTs:
    def __init__(self, tus, held=(), mixed=None):
        self.tus = tus                  # {tu: {donor: rows}}
        self.held = set(held)
        self.mixed = mixed or {}
        self._CACHE = {}
        self.released = []
        self.claims = SimpleNamespace(owner=lambda root=None: "seat-test",
                                      busy_keys=lambda root=None: set(self.held),
                                      release=self.released.extend,
                                      key_of=lambda k: k)

    def queue(self, under="", limit=None, root=None):
        out = [{"tu": tu, "removes": len(d) - 1, "rows": sum(map(len, d.values()))} for tu, d in self.tus.items()]
        return sorted(out, key=lambda e: (-e["removes"], e["tu"]))

    def skeleton(self, tu):
        return tu

    def donors(self, tu, sk):
        return dict(self.tus[tu]), dict(self.mixed.get(tu, {})), {}

    def claim_keys(self, tu, don):
        return [f"file:{tu}"] + [f"file:{f}" for f in sorted(don) if f != tu]

    def breakdown(self, path):
        return {"Code/T1.cpp": [1, 2], "Code/Other.cpp": [3]}

    def header_queue_rows(self):
        return {}


def args(**kw):
    base = dict(dry_run=False, static=False, jobs=2, budget_min=0, passes=3, under="", limit=None,
                worktree_root=None, state_dir=None, release=False)
    base.update(kw)
    return SimpleNamespace(**base)


class FakeWorkers:
    def ready(self, i, tip):
        return f"w{i}"


@pytest.fixture
def tree(tmp_path, monkeypatch):
    files = {f"Code/{n}.cpp": f"// {n}\n" for n in ("T1", "A1", "A2", "T2", "B1", "T3", "C1", "T4", "D1")}
    root = repo(tmp_path / "root", {**files, "reverse/functions.csv": HEADER})
    monkeypatch.setattr(M, "header_payload", lambda: {})
    return root


TUS = {"Code/T1.cpp": {"Code/T1.cpp": [1], "Code/A1.cpp": [1], "Code/A2.cpp": [1]},
       "Code/T2.cpp": {"Code/T2.cpp": [1], "Code/B1.cpp": [1]},
       "Code/T3.cpp": {"Code/T3.cpp": [1], "Code/A1.cpp": [1]},     # shares A1 with T1
       "Code/T4.cpp": {"Code/T4.cpp": [1], "Code/D1.cpp": [1]}}


def merged_report(tu, don):
    return {"accepted": sorted(don), "subject": f"Merge {len(don)} files into {tu}", "rejected": {}}


# ---- claims

def test_a_tu_another_seat_holds_is_never_run_and_is_recorded_with_its_holders(tree, tmp_path):
    ts = FakeTs(TUS, held={"file:Code/B1.cpp"})
    ran = []

    def run(wt, tu, dry_run, owner):
        ran.append(tu)
        return {"report": {"accepted": [], "blocked": "no verified merge"}}
    doc = M.coordinate(args(dry_run=True, state_dir=tmp_path / "s"), ts=ts, run=run, root=tree, log=lambda *a: None)
    assert "Code/T2.cpp" not in ran and "Code/T1.cpp" in ran
    claimed = [i for i in doc["items"] if i["kind"] == "claimed"]
    assert claimed == [dict(claimed[0], tu="Code/T2.cpp", holders=["file:Code/B1.cpp"])]
    assert claimed[0]["frees"] == 1


def test_a_class_claim_holds_the_tus_whose_files_define_that_class(tree, tmp_path):
    ts = FakeTs(TUS)       # header work holds only class:X; busy_keys expands it to X's member files
    ts.claims.busy_keys = lambda root=None: {"class/Thing", "file:Code/B1.cpp"}
    ran = []

    def run(wt, tu, dry_run, owner):
        ran.append(tu)
        return {"report": {"accepted": [], "blocked": "no verified merge"}}
    M.coordinate(args(dry_run=True, state_dir=tmp_path / "s"), ts=ts, run=run, root=tree, log=lambda *a: None)
    assert "Code/T2.cpp" not in ran


def test_a_merge_that_does_not_integrate_gives_its_claims_back(tree, tmp_path):
    ts = FakeTs({"Code/T1.cpp": TUS["Code/T1.cpp"]})

    def run(wt, tu, dry_run, owner):
        return {"report": {"accepted": [tu, "Code/A1.cpp"], "subject": "Merge"}, "commit": "c1",
                "claim_keys": ["file:Code/T1.cpp", "file:Code/A1.cpp"]}
    M.coordinate(args(state_dir=tmp_path / "s", passes=1), ts=ts, run=run, workers=FakeWorkers(),
                 integrate_fn=lambda root, commit, tu, absorbed: ("conflict", "CONFLICT"), root=tree,
                 log=lambda *a: None)
    assert ts.released == ["file:Code/T1.cpp", "file:Code/A1.cpp"]


def test_a_conflict_after_a_partial_merge_keeps_the_claims_that_merge_still_needs(tree, tmp_path):
    ts = FakeTs({"Code/T1.cpp": TUS["Code/T1.cpp"]})
    (tmp_path / "s").mkdir()
    (tmp_path / "s" / "state.json").write_text(json.dumps({"merged": {"Code/T1.cpp": {
        "commit": "c0", "claim_keys": ["file:Code/A1.cpp", "file:Code/T1.cpp"], "follow_up": []}}}))

    def run(wt, tu, dry_run, owner):
        return {"report": {"accepted": [tu, "Code/A2.cpp"], "subject": "Merge"}, "commit": "c1",
                "claim_keys": ["file:Code/T1.cpp", "file:Code/A2.cpp"]}
    M.coordinate(args(state_dir=tmp_path / "s", passes=1), ts=ts, run=run, workers=FakeWorkers(),
                 integrate_fn=lambda root, commit, tu, absorbed: ("conflict", "CONFLICT"), root=tree,
                 log=lambda *a: None)
    assert ts.released == ["file:Code/A2.cpp"]


def test_a_second_partial_merge_keeps_the_first_ones_claims(tmp_path):
    state = M.State(tmp_path / "state.json")
    state.merged("Code/T.cpp", "c1", ["file:Code/T.cpp", "file:Code/A.cpp"], [])
    state.merged("Code/T.cpp", "c2", ["file:Code/T.cpp", "file:Code/B.cpp"], [])
    assert state.data["merged"]["Code/T.cpp"]["claim_keys"] == [
        "file:Code/A.cpp", "file:Code/B.cpp", "file:Code/T.cpp"]


# ---- parallel

def test_waves_never_share_a_file_and_keep_queue_order():
    jobs = M.plan(FakeTs(TUS).queue(), lambda tu: (TUS[tu], {}, {}), set(), lambda k: k, FakeTs(TUS).claim_keys)
    got = M.waves(jobs, 3)
    for wave in got:
        files = [f for job in wave for f in job["files"]]
        assert len(files) == len(set(files))
    assert [j["tu"] for j in got[0]] == ["Code/T1.cpp", "Code/T2.cpp", "Code/T4.cpp"]   # T3 waits: A1
    assert [j["tu"] for j in got[1]] == ["Code/T3.cpp"]


def test_parallel_workers_never_overlap_in_files_or_worktrees(tree, tmp_path):
    ts = FakeTs(TUS)
    active, seen, lock = {}, [], threading.Lock()

    def run(wt, tu, dry_run, owner):
        files = set(TUS[tu]) | {tu}
        with lock:
            for other_wt, (other_tu, other_files) in active.items():
                assert other_wt != wt and not files & other_files, (tu, other_tu)
            active[wt] = (tu, files)
            seen.append((wt, tu))
        time.sleep(0.05)
        with lock:
            del active[wt]
        return {"report": {"accepted": [], "blocked": "no verified merge"}}
    M.coordinate(args(jobs=3, state_dir=tmp_path / "s"), ts=ts, run=run, workers=FakeWorkers(), root=tree,
                 log=lambda *a: None)
    assert {tu for _, tu in seen} == set(TUS)
    assert len({wt for wt, _ in seen}) == 3          # three slots for the first wave of three


# ---- resume and the budget

def test_resume_skips_an_unchanged_failure_and_retries_after_a_donor_edit(tree, tmp_path):
    ts = FakeTs({"Code/T2.cpp": TUS["Code/T2.cpp"]})
    calls = []

    def run(wt, tu, dry_run, owner):
        calls.append(tu)
        return {"report": {"accepted": ["Code/T2.cpp"], "blocked": "no verified merge of two or more donors",
                           "rejected": {"Code/B1.cpp": "compile: x.cpp(3): error C2065: 'm_x': undeclared identifier"}}}
    a = args(state_dir=tmp_path / "s")
    M.coordinate(a, ts=ts, run=run, workers=FakeWorkers(), root=tree, log=lambda *a: None)
    M.coordinate(a, ts=ts, run=run, workers=FakeWorkers(), root=tree, log=lambda *a: None)
    assert calls == ["Code/T2.cpp"]                                     # resumed: not run again
    state = json.loads((tmp_path / "s/state.json").read_text())
    assert state["failed"]["Code/T2.cpp"]["kind"] == "compile-error"
    assert [i["kind"] for i in state["decisions"]["Code/T2.cpp"]] == ["compile-error"]
    (tree / "Code/B1.cpp").write_text("// edited\n")
    git(tree, "commit", "-qam", "edit B1")
    M.coordinate(a, ts=ts, run=run, workers=FakeWorkers(), root=tree, log=lambda *a: None)
    assert calls == ["Code/T2.cpp", "Code/T2.cpp"]


def test_budget_stops_new_waves(tree, tmp_path):
    ts, calls, clock = FakeTs(TUS), [], [0.0]

    def run(wt, tu, dry_run, owner):
        calls.append(tu)
        clock[0] += 120                                                 # each wave costs two minutes
        return {"report": {"accepted": [], "blocked": "no verified merge"}}
    M.coordinate(args(jobs=1, budget_min=3, state_dir=tmp_path / "s"), ts=ts, run=run, workers=FakeWorkers(),
                 root=tree, log=lambda *a: None, now=lambda: clock[0])
    assert len(calls) == 2


def test_conflicts_are_retried_next_pass_and_merges_recorded(tree, tmp_path):
    ts = FakeTs({"Code/T2.cpp": TUS["Code/T2.cpp"], "Code/T4.cpp": TUS["Code/T4.cpp"]})
    picks = {"Code/T2.cpp": ["conflict", "merged"], "Code/T4.cpp": ["merged"]}

    def run(wt, tu, dry_run, owner):
        return {"report": merged_report(tu, TUS[tu]), "commit": "c-" + tu, "claim_keys": [f"file:{tu}"]}

    def integrate(root, commit, tu, accepted):
        status = picks[tu].pop(0)
        if status == "merged":
            ts.tus.pop(tu)                                              # merged: gone from the next queue
        return status, ("sha-" + tu if status == "merged" else "CONFLICT (content): reverse/functions.csv")
    doc = M.coordinate(args(state_dir=tmp_path / "s"), ts=ts, run=run, workers=FakeWorkers(), integrate_fn=integrate,
                       root=tree, log=lambda *a: None)
    assert sorted(doc["merged"]) == ["Code/T2.cpp", "Code/T4.cpp"] and doc["files_removed"] == 2
    state = json.loads((tmp_path / "s/state.json").read_text())
    assert set(state["merged"]) == {"Code/T2.cpp", "Code/T4.cpp"} and state["retry"] == {}
    released = []
    M.release(tmp_path / "s", release_fn=lambda keys: released.extend(keys) or keys)
    assert released == ["file:Code/T2.cpp", "file:Code/T4.cpp"]


def test_a_dirty_checkout_is_refused(tree, tmp_path):
    (tree / "Code/T1.cpp").write_text("// dirty\n")
    with pytest.raises(SystemExit, match="uncommitted"):
        M.coordinate(args(state_dir=tmp_path / "s"), ts=FakeTs(TUS), run=None, workers=FakeWorkers(), root=tree,
                     log=lambda *a: None)


# ---- the decision queue

def test_classify_records_the_reason_and_evidence_of_every_kind():
    job = {"tu": "Code/T1.cpp", "removes": 4, "rows": 9, "files": [], "held": [],
           "donors": {"Code/T1.cpp": 2, "Code/A.cpp": 3, "Code/B.cpp": 1, "Code/C.cpp": 2, "Code/D.cpp": 1,
                      "Code/E.cpp": 1},
           "mixed": {"Code/Mixed.cpp": 1}, "refused": {"Code/Inc.cpp": "#included by Code/X.cpp"}}
    report = {"rejected": {
        "Code/A.cpp": "compile: a.cpp(9): error C2039: 'm_x': is not a member of 'UpdateModule' | more",
        "Code/B.cpp": "compile: b.cpp(1): error C2143: syntax error",
        "Code/C.cpp": "link: Code/C.cpp links at the census; the merged object would not: unresolved ?f@G@@QAEXXZ",
        "Code/D.cpp": "bytes",
        "Code/E.cpp": "no baseline match"},
        "reconcile": "python3 tools/tu_views.py Code/T1.cpp --dry-run, then without --dry-run: the donors declare "
                     "their own views of Team (docs/consolidation.md)"}
    payload = {"classes": {"UpdateModule": {"tus": ["Code/T1.cpp"], "files": ["Code/A.cpp"]}}}
    got = {i["file"]: i for i in M.classify(job, report, payload, {}, lambda f: {"Code/T1.cpp": [1, 2], "": [3]})}
    assert got["Code/A.cpp"]["kind"] == "blocked-by-classes"
    assert got["Code/A.cpp"]["classes"] == ["Team", "UpdateModule"] and "--tier header" in got["Code/A.cpp"]["header_queue"]
    assert got["Code/B.cpp"]["kind"] == "blocked-by-classes"          # the tu_views hint names Team for the TU
    assert got["Code/C.cpp"]["kind"] == "link-regression" and got["Code/C.cpp"]["symbols"] == ["?f@G@@QAEXXZ"]
    assert got["Code/D.cpp"]["kind"] == "row-loss" and got["Code/E.cpp"]["kind"] == "baseline"
    split = got["Code/Mixed.cpp"]
    assert split["kind"] == "split" and split["split"] == {"Code/T1.cpp": 2, "(no approved TU)": 1}
    assert split["frees"] == 0 and "--split Code/Mixed.cpp --for Code/T1.cpp" in split["start"]
    assert got["Code/Inc.cpp"]["kind"] == "refused"
    plain = M.classify(job, {"rejected": {"Code/B.cpp": report["rejected"]["Code/B.cpp"]}}, {}, {}, lambda f: {})
    b = next(i for i in plain if i["file"] == "Code/B.cpp")
    assert b["kind"] == "compile-error" and b["diagnostic"] == "error C2143: syntax error"
    blocked = M.classify(dict(job, mixed={}, refused={}), {"blocked": "link guard: no census index; census-linked: "
                         "Code/T1.cpp"}, {}, {}, lambda f: {})
    assert blocked == [dict(blocked[0], kind="link-regression", file="Code/T1.cpp", frees=4)]


def test_decisions_are_ranked_by_files_freed_and_served_to_the_picker(tmp_path, monkeypatch):
    items = [M.item("compile-error", "Code/T.cpp", "Code/A.cpp", 1, 3, "compile: x", diagnostic="error C1"),
             M.item("link-regression", "Code/U.cpp", "Code/U.cpp", 5, 9, "link guard", symbols=["?s@@3HA"]),
             M.item("split", "Code/T.cpp", "Code/M.cpp", 1, 2, "mixed", split={"Code/T.cpp": 2}),
             M.item("blocked-by-classes", "Code/T.cpp", "Code/B.cpp", 1, 1, "compile", classes=["X"]),
             M.item("compile-error", "Code/T.cpp", "Code/Gone.cpp", 1, 1, "compile: y")]
    shared = tmp_path / "shared/decisions.json"
    doc = M.write_decisions(items, "abc123", tmp_path / "state", shared)
    assert [i["file"] for i in doc["items"]][:3] == ["Code/U.cpp", "Code/A.cpp", "Code/M.cpp"]
    assert doc["histogram"]["compile-error"] == [2, 2] and json.loads(shared.read_text())["measured_at"] == "abc123"
    import repair_queue
    monkeypatch.setattr(repair_queue, "ROOT", tmp_path)
    for f in ("Code/T.cpp", "Code/A.cpp", "Code/U.cpp", "Code/M.cpp", "Code/B.cpp"):
        (tmp_path / f).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / f).write_text("//\n")
    served, note = repair_queue.merge_decision_items(shared, alive=lambda kind, tu, f: True)
    assert [(i["check"], i["source"], i["count"]) for i in served] == [
        ("merge-link-regression", "Code/U.cpp", 5), ("merge-compile-error", "Code/A.cpp", 1),
        ("merge-split", "Code/M.cpp", 1)]                              # no class item; Gone.cpp is gone
    assert served[1]["claim"] == ["file:Code/A.cpp", "file:Code/T.cpp"] and "error C1" in served[1]["why"]
    assert "--merge Code/T.cpp --dry-run accepts Code/A.cpp" in served[1]["pass_test"]
    assert "3 bulk-merge decision(s)" in note


def test_decisions_the_current_map_no_longer_supports_are_not_served(tmp_path, monkeypatch):
    """The decisions are a snapshot of an older commit's map; the picker serves only those the
    map from the current inputs still supports (fleet 2026-10-29: split items whose file had no
    row approved for the TU any more, claimed and released by every seat that drew them)."""
    import repair_queue
    import tu_skeleton

    def led(name, rva, source):
        return {"name": name, "target_rva": rva, "source": source, "status": "matched", "notes": ""}

    def at(rva, tu):
        return {"rva": rva, "kind": "code", "tu": tu, "confidence": "approved"}

    ledger = [led("?m1@@YAXXZ", "0x10", "Code/M.cpp"), led("?m2@@YAXXZ", "0x20", "Code/M.cpp"),
              led("?a@@YAXXZ", "0x30", "Code/A.cpp"), led("?t@@YAXXZ", "0x40", "Code/T.cpp")]
    tree = SimpleNamespace(refusals=lambda f, rows: [])

    def use(rows):
        monkeypatch.setattr(tu_skeleton, "_CACHE", {"ledger": ledger, "map": rows, "stale": ["x"], "tree": tree})

    items = [M.item("split", "Code/T.cpp", "Code/M.cpp", 1, 1, "mixed"),
             M.item("compile-error", "Code/T.cpp", "Code/A.cpp", 1, 1, "compile: x", diagnostic="error C1")]
    shared = M.write_decisions(items, "old", tmp_path / "state", tmp_path / "shared/decisions.json")
    assert shared["measured_at"] == "old"
    monkeypatch.setattr(repair_queue, "ROOT", tmp_path)
    for f in ("Code/T.cpp", "Code/M.cpp", "Code/A.cpp"):
        (tmp_path / f).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / f).write_text("//\n")
    path = tmp_path / "shared/decisions.json"
    use([at("0x10", "Code/T.cpp"), at("0x20", "Code/U.cpp"), at("0x30", "Code/T.cpp"), at("0x40", "Code/T.cpp")])
    served, note = repair_queue.merge_decision_items(path)
    assert sorted(i["check"] for i in served) == ["merge-compile-error", "merge-split"] and "no longer" not in note
    # the map moved on: M.cpp holds nothing of T.cpp's and A.cpp's row is another TU's
    use([at("0x10", "Code/U.cpp"), at("0x20", "Code/U.cpp"), at("0x30", "Code/U.cpp"), at("0x40", "Code/T.cpp")])
    served, note = repair_queue.merge_decision_items(path)
    assert served == [] and "2 the current TU map no longer supports not served" in note
    assert tu_skeleton.split_rows("Code/M.cpp", "Code/T.cpp")[0] == "no row of that file is approved for that TU"


def test_static_dry_run_reports_without_compiling(tree, tmp_path, monkeypatch):
    monkeypatch.setattr(M, "header_payload", lambda: {"classes": {"Team": {"tus": ["Code/T1.cpp"],
                                                                           "files": ["Code/A1.cpp"]}}})
    lines = []
    doc = M.coordinate(args(dry_run=True, static=True, state_dir=tmp_path / "s"), ts=FakeTs(TUS),
                       run=lambda *a: pytest.fail("compiled"), root=tree, log=lines.append)
    classes = [i for i in doc["items"] if i["kind"] == "blocked-by-classes"]
    assert [(i["file"], i["classes"], i["static"]) for i in classes] == [("Code/A1.cpp", ["Team"], True)]
    assert any("blockers (items, files freed)" in line for line in lines)
    assert not (tmp_path / "s/state.json").exists()                 # a dry run records no state


# ---- no row lost

def test_rows_kept_finds_a_lost_or_unmoved_row():
    before = ledger([("?a@@YAXXZ", "0x10", "Code/A.cpp"), ("?b@@YAXXZ", "0x20", "Code/B.cpp"),
                     ("?c@@YAXXZ", "0x30", "Code/C.cpp")])
    good = ledger([("?a@@YAXXZ", "0x10", "Code/T.cpp"), ("?b@@YAXXZ", "0x20", "Code/T.cpp"),
                   ("?c@@YAXXZ", "0x30", "Code/C.cpp")])
    assert M.rows_kept(before, good, "Code/T.cpp", ["Code/T.cpp", "Code/A.cpp", "Code/B.cpp"]) == []
    lost = ledger([("?a@@YAXXZ", "0x10", "Code/T.cpp"), ("?c@@YAXXZ", "0x30", "Code/C.cpp")])
    assert "lost" in M.rows_kept(before, lost, "Code/T.cpp", ["Code/A.cpp", "Code/B.cpp"])[0]
    stray = ledger([("?a@@YAXXZ", "0x10", "Code/T.cpp"), ("?b@@YAXXZ", "0x20", "Code/B.cpp"),
                    ("?c@@YAXXZ", "0x30", "Code/C.cpp")])
    assert "do not name Code/T.cpp" in M.rows_kept(before, stray, "Code/T.cpp", ["Code/A.cpp", "Code/B.cpp"])[0]


def test_integrate_picks_checks_rows_and_undoes_a_loss_or_a_conflict(tmp_path):
    base = ledger([("?a@@YAXXZ", "0x10", "Code/A.cpp"), ("?b@@YAXXZ", "0x20", "Code/B.cpp")])
    root = repo(tmp_path / "root", {"reverse/functions.csv": base, "Code/A.cpp": "a\n", "Code/B.cpp": "b\n"})
    tip = git(root, "rev-parse", "HEAD")

    def worker_commit(name, text, extra=None):
        wt = tmp_path / name
        git(root, "worktree", "add", "-q", "--detach", str(wt), tip)
        (wt / "reverse/functions.csv").write_text(text, newline="\n")
        for rel, body in (extra or {}).items():
            (wt / rel).write_text(body, newline="\n")
        git(wt, "commit", "-qam", name)
        return git(wt, "rev-parse", "HEAD")
    good = worker_commit("good", ledger([("?a@@YAXXZ", "0x10", "Code/T.cpp"), ("?b@@YAXXZ", "0x20", "Code/B.cpp")]))
    status, sha = M.integrate(root, good, "Code/T.cpp", ["Code/A.cpp"])
    assert status == "merged" and git(root, "rev-parse", "HEAD") == sha
    losing = worker_commit("losing", ledger([("?b@@YAXXZ", "0x20", "Code/B.cpp")]))
    before = git(root, "rev-parse", "HEAD")
    status, why = M.integrate(root, losing, "Code/T.cpp", ["Code/A.cpp"])
    assert status in ("row-loss", "conflict") and git(root, "rev-parse", "HEAD") == before
    clash = worker_commit("clash", base, {"Code/A.cpp": "changed elsewhere\n"})
    (root / "Code/A.cpp").write_text("changed here\n", newline="\n")
    git(root, "commit", "-qam", "here")
    before = git(root, "rev-parse", "HEAD")
    status, why = M.integrate(root, clash, "Code/T.cpp", [])
    assert status == "conflict" and git(root, "rev-parse", "HEAD") == before
    assert git(root, "status", "--porcelain") == ""                   # the aborted pick left nothing behind


def test_integrate_undoes_a_clean_pick_that_loses_a_row(tmp_path):
    base = ledger([("?a@@YAXXZ", "0x10", "Code/A.cpp"), ("?b@@YAXXZ", "0x20", "Code/B.cpp")])
    root = repo(tmp_path / "root", {"reverse/functions.csv": base})
    tip = git(root, "rev-parse", "HEAD")
    wt = tmp_path / "w"
    git(root, "worktree", "add", "-q", "--detach", str(wt), tip)
    (wt / "reverse/functions.csv").write_text(ledger([("?a@@YAXXZ", "0x10", "Code/T.cpp")]), newline="\n")
    git(wt, "commit", "-qam", "drops b")
    status, why = M.integrate(root, git(wt, "rev-parse", "HEAD"), "Code/T.cpp", ["Code/A.cpp"])
    assert status == "row-loss" and "lost" in why and git(root, "rev-parse", "HEAD") == tip


# ---- the worker

def test_worker_commits_a_verified_merge_and_gives_back_a_refused_one(tmp_path, monkeypatch):
    import tu_skeleton as T
    root = repo(tmp_path / "root", {"Code/T.cpp": "t\n", "Code/A.cpp": "a\n"})
    monkeypatch.setattr(T, "ROOT", root)
    order = []

    def merge(tu, dry_run, claim):
        order.append("merge")
        (root / "Code/T.cpp").write_text("t+a\n")
        git(root, "rm", "-q", "Code/A.cpp")
        git(root, "add", "Code/T.cpp")
        return {"accepted": ["Code/T.cpp", "Code/A.cpp"], "subject": "Merge 2 files into T.cpp", "text": "x",
                "trailer": "Verifier-Change: carried", "debt-retired": ["Debt-Retired: k s r"]}
    messages = []
    out = tmp_path / "res.json"
    res = M.worker("Code/T.cpp", out, merge=merge, scope=lambda: order.append("scope") or ["file:Code/T.cpp"],
                   commit=lambda msg: messages.append(msg) or (git(root, "commit", "-qm", msg) or True, ""),
                   release=lambda keys: pytest.fail("released a committed merge"))
    assert order == ["scope", "merge"]                                # keys read before the donors are gone
    assert res["commit"] == git(root, "rev-parse", "HEAD") and res["claim_keys"] == ["file:Code/T.cpp"]
    assert messages[0].splitlines()[0] == "Merge 2 files into T.cpp" and "Debt-Retired: k s r" in messages[0]
    assert "text" not in json.loads(out.read_text())["report"]
    tip = git(root, "rev-parse", "HEAD")
    (root / "Code/A.cpp").write_text("a\n")
    git(root, "add", "Code/A.cpp")
    git(root, "commit", "-qm", "restore A")
    tip = git(root, "rev-parse", "HEAD")
    released = []
    res = M.worker("Code/T.cpp", out, merge=merge, scope=lambda: ["file:Code/T.cpp", "file:Code/A.cpp"],
                   commit=lambda msg: (False, "pre-commit: Functions: FAIL"), release=released.extend)
    assert res["commit"] is None and "FAIL" in res["hook"] and released == ["file:Code/T.cpp", "file:Code/A.cpp"]
    assert git(root, "rev-parse", "HEAD") == tip and git(root, "status", "--porcelain") == ""
    assert (root / "Code/A.cpp").exists()


def test_a_dry_run_worker_claims_and_commits_nothing(tmp_path, monkeypatch):
    import tu_skeleton as T
    monkeypatch.setattr(T, "ROOT", tmp_path)
    seen = {}
    res = M.worker("Code/T.cpp", tmp_path / "r.json", dry_run=True,
                   merge=lambda tu, dry_run, claim: seen.update(dry_run=dry_run, claim=claim) or {"accepted": []},
                   scope=lambda: pytest.fail("claimed in a dry run"), commit=lambda m: pytest.fail("committed"))
    assert seen == {"dry_run": True, "claim": False} and res["commit"] is None
