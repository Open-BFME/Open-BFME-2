"""pin_consistency --audit: existing pins re-judged against the row at their address.

pin_admission's one-address-one-identity rule (and its fold proof) runs only
when a pin is added. A pin admitted earlier keeps lending its address to every
caller of its name: 0x000365F0 carried list<FXNugget*>'s copy constructor over
StringBase<char>'s, and FXList's copy constructor matched through it
(LINK-629). These tests pin down what the audit must do:

  * judge only a real name stacked on an address whose rows carry another real
    name (placeholders on either side are not identities);
  * replay a recorded fold-proof= source before guessing one from the census;
  * read a wrong body as DIFFERS, not as an inconclusive proof;
  * report worst first, callers named, and never fail the run (shadow).
"""
import importlib.util
import json
import os
import pickle
import sys
import time
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]


def _load(name):
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


sys.path.insert(0, str(TOOLS))
build = _load("build")
pin_consistency = _load("pin_consistency")

OWNER = "??0?$StringBase@D@@AAE@ABV0@@Z"
WRONG = "??0?$list@PAVFXNugget@@V?$allocator@PAVFXNugget@@@_STL@@@_STL@@QAE@ABV01@@Z"
FOLD = "??0AsciiStringWI@@QAE@ABV0@@Z"
CALLER = "??0FXList@@QAE@ABV0@@Z"


def row(name, rva, source="Code/A.cpp", status="matched", notes=""):
    return {"name": name, "export_rva": "", "target_rva": f"0x{rva:08X}", "target_size": "66",
            "source": source, "status": status, "notes": notes}


def pin(name, rva, notes=""):
    return {"name": name, "address": f"0x{rva:08X}", "notes": notes}


class FakeIndex:
    def __init__(self, sources=None, callers=None):
        self._sources, self._callers = sources or {}, callers or {}

    def sources(self, name):
        return list(self._sources.get(name, ()))

    def matched_callers(self, name):
        return sorted(self._callers.get(name, ()))


def test_only_real_names_stacked_on_real_names_are_judged():
    rows = [row(OWNER, 0x365F0), row("?Rva00012345@@YAXXZ", 0x12345), row("?own@@YAXXZ", 0x20000)]
    pins = [pin(WRONG, 0x365F0),                       # real on real: judged
            pin("?Rva000365F0@@YAXXZ", 0x365F0),       # placeholder pin: adds no identity
            pin("?named@@YAXXZ", 0x12345),             # the row there is a placeholder
            pin("?own@@YAXXZ", 0x20000),               # its own row
            pin("?free@@YAXXZ", 0x30000)]              # no row at all
    found = pin_consistency.stacked_pins(pins, rows)
    assert [(p["name"], rva, others) for p, rva, others in found] == [(WRONG, 0x365F0, [OWNER])]


@pytest.mark.parametrize("problems, verdict", [
    ([], "PROVEN"),
    (["Code/A.cpp's X differs from retail 0x000365F0 at +0x1d"], "DIFFERS"),
    (["Code/A.cpp compiles X to 88 bytes; the ledger body at 0x000365F0 is 66"], "DIFFERS"),
    (["X's relocations are not those of the ledger body at 0x000365F0: ..."], "DIFFERS-RELOC"),
    (["X already has its own address 0x00030830; an ICF fold ..."], "IDENTITY-ELSEWHERE"),
    (["X: unresolved callees ['?y@@YAXXZ']"], "INCONCLUSIVE"),
])
def test_verdict_reads_the_first_refusal(problems, verdict):
    assert pin_consistency.audit_verdict(problems) == verdict


def test_a_recorded_fold_proof_source_is_replayed_first():
    seen = []

    def prove(p, rva):
        seen.append(p["notes"])
        return []
    rows = [row(OWNER, 0x365F0)]
    pins = [pin(FOLD, 0x365F0, "folds with the StringBase copy; fold-proof=Code/Recorded.cpp")]
    index = FakeIndex(sources={FOLD: ["Code/Census.cpp"]})
    findings = pin_consistency.audit(pins, rows, index, prove)
    assert seen == ["fold-proof=Code/Recorded.cpp"]
    assert findings[0]["verdict"] == "PROVEN" and findings[0]["fold_proof_noted"]


def test_a_name_no_unit_defines_is_reported_without_a_proof():
    def prove(p, rva):
        raise AssertionError("nothing to compile")
    findings = pin_consistency.audit([pin(WRONG, 0x365F0)], [row(OWNER, 0x365F0)], FakeIndex(), prove)
    assert findings[0]["verdict"] == "NO-DEFINING-OBJECT"


def test_wrong_bodies_come_first_with_their_matched_callers():
    rows = [row(OWNER, 0x365F0), row("?releaseBuffer@?$StringBase@G@@AAEXXZ", 0x36E70)]
    pins = [pin(FOLD, 0x365F0), pin(WRONG, 0x365F0), pin("??1?$_List_base@X@@QAE@XZ", 0x36E70)]
    index = FakeIndex(sources={FOLD: ["Code/F.cpp"], WRONG: ["Code/FXList.cpp"],
                               "??1?$_List_base@X@@QAE@XZ": ["Code/FXList.cpp"]},
                      callers={WRONG: [CALLER]})
    verdicts = {FOLD: [], WRONG: ["Code/FXList.cpp's W differs from retail 0x000365F0 at +0x10"],
                "??1?$_List_base@X@@QAE@XZ": ["Code/FXList.cpp's L differs from retail 0x00036E70 at +0x2"]}
    findings = pin_consistency.audit(pins, rows, index, lambda p, rva: verdicts[p["name"]])
    assert [(f["name"], f["verdict"]) for f in findings] == [
        (WRONG, "DIFFERS"), ("??1?$_List_base@X@@QAE@XZ", "DIFFERS"), (FOLD, "PROVEN")]
    assert findings[0]["callers"] == [CALLER]


def test_a_proof_that_cannot_run_is_inconclusive_not_a_crash():
    def prove(p, rva):
        raise SystemExit("Code/F.cpp does not compile")
    findings = pin_consistency.audit([pin(FOLD, 0x365F0)], [row(OWNER, 0x365F0)],
                                     FakeIndex(sources={FOLD: ["Code/F.cpp"]}), prove)
    assert findings[0]["verdict"] == "INCONCLUSIVE"


def test_audit_is_shadow(monkeypatch, capsys):
    monkeypatch.setattr(pin_consistency, "audit", lambda limit=None: [
        {"name": WRONG, "address": "0x000365F0", "others": [OWNER], "fold_proof_noted": False,
         "source": "Code/FXList.cpp", "callers": [CALLER], "verdict": "DIFFERS",
         "problems": ["differs from retail"]}])
    assert pin_consistency.main(["--audit"]) == 0
    out = capsys.readouterr().out
    assert "DIFFERS  0x000365F0" in out and CALLER in out


def test_census_index_names_ledger_units_and_matched_callers(tmp_path):
    rows = [row(CALLER, 0x52BD3A, source="Code/FXList.cpp"),
            row("?unmatched@@YAXXZ", 0x1000, source="Code/Other.cpp", status="blocked")]
    fx = build.obj_path(build.ROOT / "Code/FXList.cpp").name
    index = {"objects": [fx, "^stranger.obj"],
             "comdat": {WRONG: [(0, "digest", "retail"), (1, "digest", "retail")]},
             "strong": {},
             "references": {"edges": {CALLER: {WRONG}, "?unmatched@@YAXXZ": {WRONG}}}}
    path = tmp_path / "link_index.pkl"
    path.write_bytes(pickle.dumps(index))
    census = pin_consistency.CensusIndex(rows, path)
    assert census.sources(WRONG) == ["Code/FXList.cpp"]
    assert census.matched_callers(WRONG) == [CALLER]


def test_a_missing_census_index_names_nothing(tmp_path):
    census = pin_consistency.CensusIndex([row(CALLER, 0x52BD3A)], tmp_path / "absent.pkl")
    assert census.sources(WRONG) == [] and census.matched_callers(WRONG) == []


def test_a_refusal_about_a_callee_is_marked_as_one():
    rows = [row(OWNER, 0x365F0)]
    pins = [pin(WRONG, 0x365F0), pin(FOLD, 0x365F0)]
    index = FakeIndex(sources={WRONG: ["Code/FXList.cpp"], FOLD: ["Code/F.cpp"]})
    verdicts = {WRONG: [f"Code/FXList.cpp compiles {WRONG} to 88 bytes; the ledger body at 0x000365F0 is 66"],
                FOLD: ["Code/F.cpp compiles ?callee@@YAXXZ to 9 bytes; the ledger body at 0x00001000 is 11"]}
    findings = {f["name"]: f for f in pin_consistency.audit(pins, rows, index, lambda p, rva: verdicts[p["name"]])}
    assert not findings[WRONG]["on_callee"] and findings[FOLD]["on_callee"]


def test_an_empty_census_index_leaves_pins_unjudged(tmp_path):
    path = tmp_path / "link_index.pkl"
    path.write_bytes(b"")
    census = pin_consistency.CensusIndex([row(CALLER, 0x52BD3A)], path)
    assert census.problem and census.sources(WRONG) == [] and census.matched_callers(WRONG) == []
    findings = pin_consistency.audit([pin(WRONG, 0x365F0)], [row(OWNER, 0x365F0)], census,
                                     lambda p, rva: [])
    assert findings[0]["verdict"] == "UNJUDGED"


def test_an_index_entry_outside_its_object_list_makes_it_unreadable(tmp_path):
    fx = build.obj_path(build.ROOT / "Code/FXList.cpp").name
    index = {"objects": [fx], "comdat": {WRONG: [(7, "d", "retail"), (0, "d", "retail")]},
             "strong": {WRONG: [3]}, "references": {"edges": {}}}
    path = tmp_path / "link_index.pkl"
    path.write_bytes(pickle.dumps(index))
    census = pin_consistency.CensusIndex([row(CALLER, 0x52BD3A, source="Code/FXList.cpp")], path)
    assert census.problem and census.sources(WRONG) == []          # out of range: unreadable


def test_a_current_object_is_seeded_into_the_scratch_cache(tmp_path):
    real, scratch = tmp_path / "match", tmp_path / "scratch"
    real.mkdir(); scratch.mkdir()
    name = build.obj_path(build.ROOT / "Code/F.cpp").name
    (real / name).write_bytes(b"obj")
    build._deps_sidecar(real / name).write_text("{}")
    pin_consistency.seed_isolated("Code/F.cpp", real, scratch)
    assert (scratch / name).read_bytes() == b"obj" and (real / name).exists()


class FakeChild:
    """A Popen stand-in: `run` plays the child (it may write the output file); `interrupt`
    makes the first wait raise KeyboardInterrupt, as Ctrl-C in the parent would."""

    def __init__(self, argv, run=None, code=0, interrupt=False):
        self.argv, self.code, self.interrupt, self.killed, self.done = argv, code, interrupt, False, False
        if run:
            run(argv)

    def wait(self):
        if self.interrupt and not self.killed:
            raise KeyboardInterrupt
        self.done = True
        return self.code

    def poll(self):
        return self.code if self.done else None

    def kill(self):
        self.killed = True


def _jobs():
    return [{"name": FOLD, "address": "0x000365F0", "source": "Code/F.cpp"},
            {"name": WRONG, "address": "0x000365F0", "source": "Code/FXList.cpp"}]


def test_the_proofs_run_in_a_child_and_this_process_keeps_its_settings(monkeypatch, tmp_path):
    monkeypatch.setenv("BFME_OBJSTORE", "on")
    before_dir, seen = build.BUILD_DIR, {}

    def spawn(argv, env):
        seen.update(argv=argv, env=env)

        def run(argv):
            request, output, scratch = argv[-3:]
            assert Path(request).parent == Path(scratch).parent        # one private directory
            jobs = json.loads(Path(request).read_text())
            Path(output).write_text(json.dumps([[] for _ in jobs]))
        return FakeChild(argv, run)
    results = pin_consistency.isolated_proofs(_jobs(), spawn, parent=tmp_path)
    assert results == [[], []]
    assert "--audit-child" in seen["argv"] and seen["env"]["BFME_OBJSTORE"] == "off"
    scratch = Path(seen["argv"][-1]).parent
    assert scratch.parent == tmp_path and scratch.name.startswith("pin-audit-")
    assert not scratch.exists()                                        # removed
    assert build.BUILD_DIR == before_dir and os.environ["BFME_OBJSTORE"] == "on"


def test_overlapping_audits_never_touch_each_other_or_this_process(monkeypatch, tmp_path):
    # Review probe 1: two isolations alive at once. Each lives in its own child; this process
    # never changes BUILD_DIR or the store setting, so neither can restore the other's.
    monkeypatch.delenv("BFME_OBJSTORE", raising=False)
    before_dir, dirs = build.BUILD_DIR, []

    def inner_spawn(argv, env):
        def run(argv):
            dirs.append(Path(argv[-1]).parent)
            Path(argv[-2]).write_text(json.dumps([[] for _ in json.loads(Path(argv[-3]).read_text())]))
        return FakeChild(argv, run)

    def outer_spawn(argv, env):
        def run(argv):
            dirs.append(Path(argv[-1]).parent)
            assert pin_consistency.isolated_proofs(_jobs(), inner_spawn, parent=tmp_path) == [[], []]
            assert build.BUILD_DIR == before_dir and "BFME_OBJSTORE" not in os.environ
            Path(argv[-2]).write_text(json.dumps([[] for _ in json.loads(Path(argv[-3]).read_text())]))
        return FakeChild(argv, run)
    assert pin_consistency.isolated_proofs(_jobs(), outer_spawn, parent=tmp_path) == [[], []]
    assert len(set(dirs)) == 2 and not any(d.exists() for d in dirs)
    assert build.BUILD_DIR == before_dir and "BFME_OBJSTORE" not in os.environ


def test_an_interrupt_kills_the_child_and_removes_the_directory(tmp_path):
    children = []

    def spawn(argv, env):
        children.append(FakeChild(argv, interrupt=True))
        return children[-1]
    with pytest.raises(KeyboardInterrupt):
        pin_consistency.isolated_proofs(_jobs(), spawn, parent=tmp_path)
    assert children[0].killed and list(tmp_path.iterdir()) == []


def test_an_interrupt_while_starting_the_child_still_removes_the_directory(tmp_path):
    def spawn(argv, env):
        raise KeyboardInterrupt
    with pytest.raises(KeyboardInterrupt):
        pin_consistency.isolated_proofs(_jobs(), spawn, parent=tmp_path)
    assert list(tmp_path.iterdir()) == []


def test_a_failed_child_leaves_every_job_unproven(tmp_path):
    results = pin_consistency.isolated_proofs(_jobs(), lambda argv, env: FakeChild(argv, code=3),
                                              parent=tmp_path)
    assert [pin_consistency.audit_verdict(r) for r in results] == ["INCONCLUSIVE"] * 2
    assert "exited 3" in results[0][0] and list(tmp_path.iterdir()) == []


def test_a_directory_that_cannot_be_removed_is_named(monkeypatch, tmp_path, capsys):
    stuck = tmp_path / "pin-audit-stuck"
    stuck.mkdir()

    def refuse(path, *args, **kwargs):
        raise PermissionError("held open")
    monkeypatch.setattr(pin_consistency.shutil, "rmtree", refuse)
    assert pin_consistency.remove_scratch(stuck) is False
    assert str(stuck) in capsys.readouterr().err and stuck.exists()


def test_scratch_directories_older_than_a_day_are_swept(tmp_path):
    old, fresh, other = tmp_path / "pin-audit-old", tmp_path / "pin-audit-fresh", tmp_path / "match"
    for path in (old, fresh, other):
        path.mkdir()
    now = time.time()
    os.utime(old, (now - 2 * 86400, now - 2 * 86400))
    os.utime(other, (now - 2 * 86400, now - 2 * 86400))
    assert pin_consistency.sweep_stale_scratch(tmp_path, now, root=tmp_path.parent) == [old]
    assert not old.exists() and fresh.exists() and other.exists()


def test_the_child_compiles_into_its_scratch_directory(monkeypatch, tmp_path):
    monkeypatch.setattr(build, "BUILD_DIR", build.BUILD_DIR)          # restored after the test
    monkeypatch.setenv("BFME_OBJSTORE", "off")
    scratch, seen = tmp_path / "match", {}

    def proof(p, rva, rows, symbol_map, pins):
        seen[p["name"]] = build.BUILD_DIR
        return [] if p["name"] == FOLD else ["x differs from retail 0x000365F0 at +0x1"]
    import pin_admission
    monkeypatch.setattr(pin_admission, "fold_proof_problems", proof)
    monkeypatch.setattr(build, "load_all_function_rows", lambda: [])
    request, output = tmp_path / "request.json", tmp_path / "result.json"
    request.write_text(json.dumps(_jobs()))
    assert pin_consistency.audit_child(str(request), str(output), str(scratch)) == 0
    assert seen == {FOLD: scratch, WRONG: scratch}
    assert json.loads(output.read_text()) == [[], ["x differs from retail 0x000365F0 at +0x1"]]


def test_the_child_refuses_to_run_with_the_shared_store_on(monkeypatch, tmp_path):
    monkeypatch.setenv("BFME_OBJSTORE", "on")
    with pytest.raises(SystemExit):
        pin_consistency.audit_child(str(tmp_path / "r"), str(tmp_path / "o"), str(tmp_path / "s"))


@pytest.mark.parametrize("data", [
    b"\x80\xff.",                                                       # review probe: another pickle protocol
    pickle.dumps({"objects": [], "comdat": {}, "strong": {}, "references": {"edges": None}}),
    pickle.dumps(["not", "an", "index"]),
    pickle.dumps({"objects": None, "comdat": {}, "strong": {}, "references": {"edges": {}}}),
])
def test_any_unreadable_index_leaves_pins_unjudged(tmp_path, data):
    path = tmp_path / "link_index.pkl"
    path.write_bytes(data)
    census = pin_consistency.CensusIndex([row(CALLER, 0x52BD3A)], path)
    assert census.problem and census.sources(WRONG) == [] and census.matched_callers(WRONG) == []
    findings = pin_consistency.audit([pin(WRONG, 0x365F0)], [row(OWNER, 0x365F0)], census,
                                     lambda p, rva: [])
    assert findings[0]["verdict"] == "UNJUDGED"


def test_a_malformed_entry_read_later_makes_the_index_unreadable(tmp_path):
    index = {"objects": ["a.obj"], "comdat": {WRONG: 5}, "strong": {}, "references": {"edges": {}}}
    path = tmp_path / "link_index.pkl"
    path.write_bytes(pickle.dumps(index))
    census = pin_consistency.CensusIndex([], path)
    assert census.sources(WRONG) == [] and census.problem


def test_audit_main_exits_zero_and_says_why_on_an_unreadable_index(monkeypatch, tmp_path, capsys):
    path = tmp_path / "link_index.pkl"
    path.write_bytes(b"\x80\xff.")
    census = pin_consistency.CensusIndex([], path)
    real_audit = pin_consistency.audit
    monkeypatch.setattr(pin_consistency, "audit", lambda limit=None: real_audit(
        [pin(WRONG, 0x365F0)], [row(OWNER, 0x365F0)], census, lambda p, rva: []))
    assert pin_consistency.main(["--audit"]) == 0
    assert "unreadable" in capsys.readouterr().out


def test_late_index_corruption_judges_no_pin(tmp_path):
    # Review probe 3: a bad entry for the second pin left the first one PROVEN.
    obj_name = build.obj_path(build.ROOT / "Code/A.cpp").name
    index = {"objects": [obj_name], "comdat": {"?first@@YAXXZ": [(0, "d", "retail")], "?bad@@YAXXZ": 5},
             "strong": {}, "references": {"edges": {}}}
    path = tmp_path / "late.pkl"
    path.write_bytes(pickle.dumps(index))
    census = pin_consistency.CensusIndex([row(OWNER, 0x365F0, source="Code/A.cpp")], path)

    def prove(p, rva):
        raise AssertionError("an unreadable index judges nothing")
    findings = pin_consistency.audit([pin("?first@@YAXXZ", 0x365F0), pin("?bad@@YAXXZ", 0x365F0)],
                                     [row(OWNER, 0x365F0, source="Code/A.cpp")], census, prove)
    assert census.problem and {f["verdict"] for f in findings} == {"UNJUDGED"}


def test_an_index_whose_existence_cannot_be_checked_is_unreadable(monkeypatch, tmp_path):
    # Review probe 4: Path.exists raising before the handler.
    path = tmp_path / "link_index.pkl"
    path.write_bytes(pickle.dumps({"objects": [], "comdat": {}, "strong": {}, "references": {"edges": {}}}))
    monkeypatch.setattr(Path, "exists", lambda self: (_ for _ in ()).throw(PermissionError("denied")))
    census = pin_consistency.CensusIndex([], path)
    assert "PermissionError" in census.problem


def test_a_well_formed_index_names_sources_and_callers(tmp_path):
    fx = build.obj_path(build.ROOT / "Code/FXList.cpp").name
    index = {"objects": [fx], "comdat": {WRONG: [(0, "d", "retail")]}, "strong": {FOLD: [0]},
             "references": {"edges": {CALLER: {WRONG}}}}
    path = tmp_path / "link_index.pkl"
    path.write_bytes(pickle.dumps(index))
    census = pin_consistency.CensusIndex([row(CALLER, 0x52BD3A, source="Code/FXList.cpp")], path)
    assert census.problem is None
    assert census.sources(WRONG) == census.sources(FOLD) == ["Code/FXList.cpp"]
    assert census.matched_callers(WRONG) == [CALLER]


def _stale(path):
    path.mkdir(parents=True)
    (path / "sentinel").write_text("keep")
    then = time.time() - 2 * 86400
    os.utime(path, (then, then))


@pytest.mark.skipif(os.name == "nt", reason="symlinks need privileges on Windows; junctions below")
def test_the_sweep_never_follows_a_linked_build_directory(tmp_path):
    # Review probe 2: build/ is a link to a directory outside the checkout.
    checkout, outside = tmp_path / "checkout", tmp_path / "outside"
    checkout.mkdir()
    _stale(outside / "pin-audit-old")
    (checkout / "build").symlink_to(outside, target_is_directory=True)
    assert pin_consistency.sweep_stale_scratch(checkout / "build", root=checkout) == []
    assert (outside / "pin-audit-old" / "sentinel").exists()


@pytest.mark.skipif(os.name != "nt", reason="Windows junction")
def test_the_sweep_never_follows_a_build_junction(tmp_path):
    import _winapi
    checkout, outside = tmp_path / "checkout", tmp_path / "outside"
    checkout.mkdir()
    _stale(outside / "pin-audit-old")
    _winapi.CreateJunction(str(outside), str(checkout / "build"))
    try:
        assert pin_consistency.sweep_stale_scratch(checkout / "build", root=checkout) == []
        assert (outside / "pin-audit-old" / "sentinel").exists()
    finally:
        os.rmdir(checkout / "build")                                # the junction, not its target


@pytest.mark.skipif(os.name == "nt", reason="symlinks need privileges on Windows")
def test_the_sweep_never_deletes_through_a_linked_entry(tmp_path):
    checkout, outside = tmp_path / "checkout", tmp_path / "outside"
    (checkout / "build").mkdir(parents=True)
    _stale(outside / "victim")
    link = checkout / "build" / "pin-audit-link"
    link.symlink_to(outside / "victim", target_is_directory=True)
    _stale(checkout / "build" / "pin-audit-real")
    swept = pin_consistency.sweep_stale_scratch(checkout / "build", root=checkout)
    assert [p.name for p in swept] == ["pin-audit-real"]
    assert link.is_symlink() and (outside / "victim" / "sentinel").exists()


def test_the_sweep_skips_a_build_directory_outside_the_checkout(tmp_path):
    checkout, elsewhere = tmp_path / "checkout", tmp_path / "elsewhere" / "build"
    checkout.mkdir()
    _stale(elsewhere / "pin-audit-old")
    assert pin_consistency.sweep_stale_scratch(elsewhere, root=checkout) == []
    assert (elsewhere / "pin-audit-old").exists()


_DESCENDANTS = (
    "import subprocess, sys, time\n"
    "from pathlib import Path\n"
    "grandchild = subprocess.Popen([sys.executable, '-c', 'import time; time.sleep(120)'])\n"
    "Path(sys.argv[1]).write_text(str(grandchild.pid))\n"
    "time.sleep(120)\n")


def _alive(pid):
    if os.name == "nt":
        import subprocess
        out = subprocess.run(["tasklist", "/FI", f"PID eq {pid}", "/NH"], capture_output=True, text=True).stdout
        return str(pid) in out
    try:
        os.kill(pid, 0)
    except ProcessLookupError:
        return False
    try:                                                            # a zombie awaiting its reaper is dead
        return Path(f"/proc/{pid}/stat").read_text().split(") ")[1][0] != "Z"
    except (OSError, IndexError):
        return True


def _wait_for(predicate, seconds=10):
    end = time.time() + seconds
    while time.time() < end:
        if predicate():
            return True
        time.sleep(0.05)
    return predicate()


@pytest.mark.skipif(os.name == "nt", reason="the audit refuses to run on Windows")
def test_an_interrupt_kills_the_proof_process_and_what_it_started(tmp_path):
    # Review probe 1: child.kill() alone left the grandchild (a compiler) running.
    pidfile = tmp_path / "grandchild.pid"

    class Interrupted:
        def __init__(self, child):
            self.child, self.pid, self.audit_group = child, child.pid, child.audit_group

        def wait(self):
            if self.child.poll() is None and _wait_for(pidfile.exists):
                raise KeyboardInterrupt
            return self.child.wait()

        def poll(self):
            return self.child.poll()

        def kill(self):
            self.child.kill()

    def spawn(argv, env):
        script = tmp_path / "descendants.py"
        script.write_text(_DESCENDANTS)
        return Interrupted(pin_consistency.start_child([sys.executable, str(script), str(pidfile)], env))
    with pytest.raises(KeyboardInterrupt):
        pin_consistency.isolated_proofs(_jobs(), spawn, parent=tmp_path / "build")
    grandchild = int(pidfile.read_text())
    assert _wait_for(lambda: not _alive(grandchild))
    assert list((tmp_path / "build").glob("pin-audit-*")) == []


_MIDDLE = (
    "import subprocess, sys\n"
    "from pathlib import Path\n"
    "grandchild = subprocess.Popen([sys.executable, '-c', 'import time; time.sleep(120)'])\n"
    "Path(sys.argv[1]).write_text(str(grandchild.pid))\n")             # and exits at once
_LEADER = (
    "import subprocess, sys, time\n"
    "from pathlib import Path\n"
    "subprocess.Popen([sys.executable, sys.argv[1], sys.argv[2]]).wait()\n"
    "Path(sys.argv[3]).write_text('ready')\n"
    "time.sleep(120)\n")


@pytest.mark.skipif(os.name == "nt", reason="the audit refuses to run on Windows")
def test_a_grandchild_orphaned_by_an_exited_intermediate_is_killed_too(tmp_path):
    # Review probe 4: the compiler driver has exited; its compiler must still die with the tree.
    middle, leader = tmp_path / "middle.py", tmp_path / "leader.py"
    middle.write_text(_MIDDLE)
    leader.write_text(_LEADER)
    pidfile, ready = tmp_path / "orphan.pid", tmp_path / "ready"
    child = pin_consistency.start_child(
        [sys.executable, str(leader), str(middle), str(pidfile), str(ready)], dict(os.environ))
    try:
        assert _wait_for(ready.exists)
        orphan = int(pidfile.read_text())
        assert _alive(orphan)
        pin_consistency.kill_tree(child)
        child.wait(timeout=10)
        assert _wait_for(lambda: not _alive(orphan))
    finally:
        child.kill()
        child.wait()


def test_the_audit_refuses_to_run_on_windows(monkeypatch):
    monkeypatch.setattr(pin_consistency, "on_windows", lambda: True)
    monkeypatch.setattr(pin_consistency, "audit", lambda limit=None: (_ for _ in ()).throw(
        AssertionError("nothing may be judged")))
    for argv in (["--audit"], ["--audit-child", "r", "o", "s"]):
        with pytest.raises(SystemExit) as refused:
            pin_consistency.main(argv)
        assert "srv1" in str(refused.value)
    with pytest.raises(SystemExit):
        pin_consistency.start_child([sys.executable, "-c", "pass"], dict(os.environ))
