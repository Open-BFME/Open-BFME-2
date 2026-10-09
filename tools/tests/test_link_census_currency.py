"""The census counts only objects proven current, and only a run whose
objects, compiler inputs and tools held still from the first check to the
record (ported from Open-BFME-1's test_link_census_currency.py, plus this
port's own refusals)."""
import json
import os
import subprocess
import sys
import types
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_census as census
from test_build_include_inventory import _fixture


@pytest.fixture(autouse=True)
def isolated_data_ledger(tmp_path, monkeypatch):
    # Synthetic census/order fixtures must not inherit live repository data
    # providers. Tests of populated/malformed data rows still supply their own
    # rows/path and exercise the unchanged real data loader and byte gate.
    import data_rows
    empty = tmp_path / "data_rows.csv"
    empty.write_bytes((data_rows.HEADER + "\n").encode())
    loader = data_rows.load
    monkeypatch.setattr(data_rows, "DATA_ROWS", empty)
    monkeypatch.setattr(data_rows, "load", lambda path=None: loader(path or data_rows.DATA_ROWS))


def test_new_shadowing_shim_header_invalidates_census_object(tmp_path, monkeypatch):
    source, obj, early, original, _, _ = _fixture(tmp_path, monkeypatch)
    assert census.object_current(source, obj)
    (early / "Common" / "MessageStream.h").write_text("#define PACKET_RANGE 7\n")
    assert original.read_text() == "#define PACKET_RANGE 6\n"
    assert not census.object_current(source, obj)


def test_receiptless_object_is_never_current_however_new(tmp_path, monkeypatch):
    # The pre-port object_current accepted an object with no sidecar when it
    # was newer than its source; the build cache never did.
    source, obj = tmp_path / "unit.cpp", tmp_path / "unit.obj"
    source.write_text("int f() { return 1; }\n")
    obj.write_bytes(b"object")
    os.utime(obj, ns=(source.stat().st_mtime_ns + 10**9,) * 2)
    monkeypatch.setattr(census, "_INPUT_RECEIPTS", None)
    monkeypatch.setattr(census, "input_receipts", lambda: None)
    assert not census.object_current(source, obj)
    assert census.stale_objects([obj], {obj: source}) == [obj]


def test_ordinary_sidecar_is_not_census_proof(tmp_path, monkeypatch):
    # A legacy (gate-only) sidecar proves recorded header bytes, not search
    # order: the census refuses it, the gate still reuses it.
    source, obj, _, _, _, _ = _fixture(tmp_path, monkeypatch)
    sidecar = census.build._deps_sidecar(obj)
    meta = json.loads(sidecar.read_text())
    for key in ("version", "inventory", "retry_dirs", "search_roots"):
        meta.pop(key)
    sidecar.write_text(json.dumps(meta))
    monkeypatch.setattr(census, "input_receipts", lambda: None)
    assert census.build.compile_is_current(source, obj)
    assert not census.object_current(source, obj)


def test_selected_refuses_changed_tracked_reference_header(tmp_path, monkeypatch):
    root = tmp_path / "repo"
    header = root / "reference/shims/Common/Test.h"
    header.parent.mkdir(parents=True)
    header.write_text("#define VALUE 1\n")
    subprocess.run(["git", "init", "-q", str(root)], check=True)
    subprocess.run(["git", "-C", str(root), "add", "reference/shims/Common/Test.h"], check=True)
    subprocess.run(["git", "-C", str(root), "-c", "user.name=Test", "-c", "user.email=test@example.invalid",
                    "commit", "-qm", "fixture"], check=True)
    commit = subprocess.check_output(["git", "-C", str(root), "rev-parse", "HEAD"], text=True).strip()
    header.write_text("#define VALUE 2\n")
    monkeypatch.setattr(census, "ROOT", root)
    monkeypatch.setattr(census, "read_history", lambda: [{"commit": commit}])
    monkeypatch.setattr(census, "ledger", lambda: pytest.fail("passed the commit-input guard"))
    with pytest.raises(SystemExit, match="this tree differs"):
        census.selected_main()
    with pytest.raises(SystemExit, match="uncommitted source or ledger edits"):
        census.record({"missing": 0}, [])


def test_inventory_change_during_currency_check_refuses_snapshot(monkeypatch):
    monkeypatch.setattr(census.build, "_inventory_cache_still_current", lambda cache: False)
    with pytest.raises(SystemExit, match="changed while checking"):
        census.stale_objects([], {})


def test_fresh_uncacheable_compile_passes_census_currency(tmp_path, monkeypatch):
    from test_census_receipts import fixture
    import census_receipts
    source, header, obj, _, _, _ = fixture(tmp_path, monkeypatch)
    receipts = census_receipts.Receipts(tmp_path / "proof.json")
    assert census.build.try_compile_source(source, obj, input_proof=receipts)[0]
    monkeypatch.setattr(census, "_INPUT_RECEIPTS", receipts)
    assert census.stale_objects([obj], {obj: source}) == []
    header.write_text("#define VALUE 18\n")
    assert census.stale_objects([obj], {obj: source}) == [obj]


def test_ordinary_sidecar_from_a_census_compile_gets_a_receipt(tmp_path, monkeypatch):
    # The compile could not record an inventory (an ordinary sidecar): the
    # witnessed compile is then the census's proof.
    from test_census_receipts import fixture
    import census_receipts
    source, header, obj, _, _, _ = fixture(tmp_path, monkeypatch)
    monkeypatch.setattr(census.build, "_write_deps_sidecar",
                        lambda *a: census.build._deps_sidecar(obj).write_text(json.dumps({"cmd": "flags"})))
    receipts = census_receipts.Receipts(tmp_path / "proof.json")
    assert census.build.try_compile_source(source, obj, input_proof=receipts)[0]
    assert str(obj.resolve()) in receipts.entries


def test_inventory_change_during_fresh_proof_is_refused(tmp_path, monkeypatch):
    obj, source = tmp_path / "f.obj", tmp_path / "f.cpp"
    monkeypatch.setattr(census, "object_current", lambda *a, **k: False)
    monkeypatch.setattr(census, "input_receipts", lambda: SimpleNamespace(current=lambda *a: True))
    stable = iter([True, False])
    monkeypatch.setattr(census.build, "_inventory_cache_still_current", lambda cache: next(stable))
    with pytest.raises(SystemExit, match="changed while checking"):
        census.stale_objects([obj], {obj: source})


def test_data_ledger_is_read_not_refused(tmp_path, monkeypatch):
    """Before data rows were ported, a data_rows.csv refused the census (no
    loader). Now the header-only ledger passes the data check and the record
    goes on to its own refusals; a malformed one is refused for what it is."""
    import data_rows
    assert not hasattr(census, "refuse_unsupported_ledgers")
    empty = tmp_path / "data_rows.csv"
    empty.write_text(data_rows.HEADER + "\n")
    monkeypatch.setattr(data_rows, "DATA_ROWS", empty)
    with pytest.raises(SystemExit, match="objects were missing"):
        census.record({"missing": 1}, [])
    empty.write_text("name\n")
    with pytest.raises(SystemExit, match="invalid data rows"):
        census.record({"missing": 1}, [])


def test_dir32_ledger_is_a_monitored_census_input():
    assert "reverse/dir32_addresses.csv" in census.CENSUS_INPUTS


def test_data_ledger_and_its_tools_are_monitored():
    assert "reverse/data_rows.csv" in census.CENSUS_INPUTS
    assert {"data_rows.py", "reloc_ledger.py"} <= set(census.TOOL_FILES)


# --- the run must hold still -------------------------------------------------

def _quiet_git(monkeypatch):
    monkeypatch.setattr(census.subprocess, "run", lambda *a, **k: SimpleNamespace(stdout="", returncode=0))


def _main_harness(tmp_path, monkeypatch, obj, source):
    _quiet_git(monkeypatch)
    # main(--build) does os.environ.setdefault("BUILD_POOL", ...): owned here, so
    # monkeypatch removes it again and later tests (test_hook_argmax) see none.
    monkeypatch.setenv("BUILD_POOL", "4")
    monkeypatch.setattr(census, "OUT", tmp_path / "out")
    monkeypatch.setattr(census, "ledger", lambda: [])
    monkeypatch.setattr(census, "objects", lambda rows, data=None: ([obj], []))
    monkeypatch.setattr(census, "_object_sources", lambda rows: {obj: source})
    monkeypatch.setattr(census, "fresh_outputs", lambda *p: None)
    monkeypatch.setattr(census, "unexplained_exit", lambda *a: None)
    monkeypatch.setattr(census, "classify", lambda log, rows: ({}, {}, {}, []))
    monkeypatch.setattr(census, "comdat_conflicts", lambda objs: {})
    monkeypatch.setattr(census, "report", lambda c: None)
    monkeypatch.setattr(census, "head", lambda: "abc")


def test_build_never_skips_the_currency_check(tmp_path, monkeypatch):
    # --build used to trust compile_rows and skip the check altogether.
    obj, source = tmp_path / "f.obj", tmp_path / "f.cpp"
    obj.write_bytes(b"object")
    _main_harness(tmp_path, monkeypatch, obj, source)
    monkeypatch.setattr(census.build, "ensure_case_shims", lambda: None)
    monkeypatch.setattr(census.build, "compile_rows", lambda *a, **k: {})
    monkeypatch.setattr(census, "stale_objects", lambda present, sources: list(present))
    monkeypatch.setattr(census, "link", lambda *a, **k: pytest.fail("linked a stale object"))
    with pytest.raises(SystemExit, match="stale"):
        census.main(["--build"])


def test_object_replaced_during_the_link_refuses(tmp_path, monkeypatch):
    obj, source = tmp_path / "f.obj", tmp_path / "f.cpp"
    obj.write_bytes(b"object")
    _main_harness(tmp_path, monkeypatch, obj, source)
    monkeypatch.setattr(census, "stale_objects", lambda present, sources: [])

    def link(*a, **k):
        replacement = tmp_path / "new.obj"
        replacement.write_bytes(b"object")  # same bytes, another file: still a different object
        replacement.replace(obj)
        return "", 1.0, 0
    monkeypatch.setattr(census, "link", link)
    with pytest.raises(SystemExit, match="changed during link"):
        census.main([])
    assert not (tmp_path / "out" / "census.json").exists()


def test_tools_changed_during_the_link_refuses(tmp_path, monkeypatch):
    obj, source = tmp_path / "f.obj", tmp_path / "f.cpp"
    obj.write_bytes(b"object")
    _main_harness(tmp_path, monkeypatch, obj, source)
    monkeypatch.setattr(census, "stale_objects", lambda present, sources: [])
    digests = iter(["before", "after", "after"])
    monkeypatch.setattr(census, "tools_digest", lambda: next(digests))
    monkeypatch.setattr(census, "link", lambda *a, **k: ("", 1.0, 0))
    with pytest.raises(SystemExit, match="tools or objects changed during link"):
        census.main([])


def _record_harness(tmp_path, monkeypatch, obj, source, on_selection=None, on_status=None):
    _quiet_git(monkeypatch)
    monkeypatch.setattr(census, "STATUS", tmp_path / "link_status.csv")
    monkeypatch.setattr(census, "HISTORY", tmp_path / "history.csv")
    history = [{"date": "2026-10-01 00:00", "commit": "abc", "rules": census.RULES}]
    monkeypatch.setattr(census, "read_history", lambda: [dict(r) for r in history])
    monkeypatch.setattr(census, "objects", lambda rows, data=None: ([obj], []))
    monkeypatch.setattr(census, "_object_sources", lambda rows: {obj: source})
    monkeypatch.setattr(census, "stale_objects", lambda present, sources: [])
    monkeypatch.setattr(census, "head", lambda: "abc")
    monkeypatch.setattr(census, "final_log", lambda c: "")
    monkeypatch.setattr(census, "selected_definitions", lambda text: {})
    monkeypatch.setattr(census, "linked_figures", lambda clean: {"linked_bytes": 1, "linked_authored": 1,
                                                                  "game_code": 10})
    monkeypatch.setitem(sys.modules, "link_debt", types.SimpleNamespace(per_file=lambda f: [], addresses=None))
    accepted = []

    def selection_link(present, log):
        if on_selection:
            on_selection()
        return ""

    def write_status(*a, **k):
        assert k.get("publish") is False, "record must defer the status until its last check"
        if on_status:
            on_status()
        return set(), 1, 0, set(), {"accept": lambda: accepted.append(True)}
    monkeypatch.setattr(census, "selection_link", selection_link)
    monkeypatch.setattr(census, "write_status", write_status)
    return accepted


CENSUS = {"missing": 0, "when": "2026-10-02 00:00", "objects": 1, "unresolved_classes": {},
          "duplicate_classes": {}, "commit": "abc"}


def linked(obj, **changes):
    """census.json as main() writes it: the commit, tools and objects it linked."""
    return {**CENSUS, "objects_digest": census.objects_digest([obj]), "tools": census.tools_digest(), **changes}


def test_record_reproves_currency_even_after_a_fresh_build(tmp_path, monkeypatch):
    obj, source = tmp_path / "f.obj", tmp_path / "f.cpp"
    obj.write_bytes(b"object")
    _record_harness(tmp_path, monkeypatch, obj, source)
    monkeypatch.setattr(census, "stale_objects", lambda present, sources: list(present))
    with pytest.raises(SystemExit, match="not current"):
        census.record(dict(CENSUS), [])


def test_object_replaced_during_selection_link_records_nothing(tmp_path, monkeypatch):
    obj, source = tmp_path / "f.obj", tmp_path / "f.cpp"
    obj.write_bytes(b"object")
    accepted = _record_harness(tmp_path, monkeypatch, obj, source,
                               on_selection=lambda: obj.write_bytes(b"object"))
    with pytest.raises(SystemExit, match="during the selection link"):
        census.record(linked(obj), [])
    assert not accepted and not census.HISTORY.exists()


def test_object_replaced_while_facts_are_read_records_nothing(tmp_path, monkeypatch):
    obj, source = tmp_path / "f.obj", tmp_path / "f.cpp"
    obj.write_bytes(b"object")
    accepted = _record_harness(tmp_path, monkeypatch, obj, source,
                               on_status=lambda: obj.write_bytes(b"object"))
    with pytest.raises(SystemExit, match="during judgment"):
        census.record(linked(obj), [])
    assert not accepted and not census.HISTORY.exists()


def test_objects_other_than_the_linked_ones_refuse(tmp_path, monkeypatch):
    obj, source = tmp_path / "f.obj", tmp_path / "f.cpp"
    obj.write_bytes(b"object")
    accepted = _record_harness(tmp_path, monkeypatch, obj, source)
    with pytest.raises(SystemExit, match="objects changed since this census linked"):
        census.record(linked(obj, objects_digest="another run's objects"), [])
    assert not accepted


def test_a_still_run_records_status_then_history(tmp_path, monkeypatch):
    obj, source = tmp_path / "f.obj", tmp_path / "f.cpp"
    obj.write_bytes(b"object")
    accepted = _record_harness(tmp_path, monkeypatch, obj, source)
    census.record(linked(obj), [])
    assert accepted == [True]
    rows = census.HISTORY.read_text().splitlines()
    assert rows[0].split(",") == census.HISTORY_FIELDS
    assert rows[-1].endswith(f",{census.RULES},{census.RULES_NO_WRONG_SELECTED}")


def test_census_of_another_head_publishes_nothing(tmp_path, monkeypatch):
    # The objects and tools are unchanged, but HEAD is not the commit the
    # census (and the previous rules) linked.
    obj, source = tmp_path / "f.obj", tmp_path / "f.cpp"
    obj.write_bytes(b"object")
    accepted = _record_harness(tmp_path, monkeypatch, obj, source)
    for stale in (linked(obj, commit="stale"), {k: v for k, v in linked(obj).items() if k != "commit"}):
        with pytest.raises(SystemExit, match="but HEAD is abc"):
            census.record(stale, [])
    old = {"rules": census.LEGACY_RULES, "commit": "stale", "objects_digest": census.objects_digest([obj]),
           "game_code": 10, "files_linked": 1, "linked_bytes": 1, "linked_authored": 1}
    monkeypatch.setattr(census, "read_history", lambda: [{"date": "2026-10-01 00:00", "commit": "x"}])
    with pytest.raises(SystemExit, match="not for this commit"):
        census.record(linked(obj), [], rebaseline=old)
    assert not accepted and not census.HISTORY.exists()


def test_missing_provenance_refuses(tmp_path, monkeypatch):
    obj, source = tmp_path / "f.obj", tmp_path / "f.cpp"
    obj.write_bytes(b"object")
    accepted = _record_harness(tmp_path, monkeypatch, obj, source)
    for key in ("tools", "objects_digest"):
        with pytest.raises(SystemExit, match="changed since this census linked"):
            census.record({k: v for k, v in linked(obj).items() if k != key}, [])
    assert not accepted and not census.HISTORY.exists()


def test_rebaseline_game_code_mismatch_publishes_nothing(tmp_path, monkeypatch):
    # The denominators are compared before the status, index or history is
    # written, so a refusal leaves the re-baseline retryable.
    obj, source = tmp_path / "f.obj", tmp_path / "f.cpp"
    obj.write_bytes(b"object")
    accepted = _record_harness(tmp_path, monkeypatch, obj, source)
    monkeypatch.setattr(census, "read_history", lambda: [{"date": "2026-10-01 00:00", "commit": "x"}])
    old = {"rules": census.LEGACY_RULES, "commit": "abc", "objects_digest": census.objects_digest([obj]),
           "game_code": 11, "files_linked": 1, "linked_bytes": 1, "linked_authored": 1}
    with pytest.raises(SystemExit, match="game code 11, these 10"):
        census.record(linked(obj), [], rebaseline=old)
    assert not accepted and not census.HISTORY.exists()
    figure = census.record(linked(obj), [], rebaseline={**old, "game_code": 10})
    assert accepted == [True] and figure["prev_rules"] == census.LEGACY_RULES
    assert census.HISTORY.read_text().splitlines()[-1].endswith(f",{census.RULES},{census.LEGACY_RULES}")


def test_census_build_names_every_unprovable_tu_then_refuses(tmp_path, monkeypatch):
    # One re-baseline stopped at the first TU without proof; the census now
    # compiles on, names every such TU, and still links nothing.
    from test_census_receipts import fixture
    import census_receipts
    source, header, obj, _, _, run = fixture(tmp_path, monkeypatch)

    def changed(cmd, **kwargs):
        result = run(cmd, **kwargs)
        if '-E' not in cmd:
            header.write_text(header.read_text() + "// edited mid-compile\n")
        return result
    monkeypatch.setattr(census.build.subprocess, "run", changed)
    receipts = census_receipts.Receipts(tmp_path / "proof.json", collect=True)
    for _ in range(2):
        assert census.build.try_compile_source(source, obj, input_proof=receipts)[0]
    assert len(receipts.failures) == 2 and not receipts.entries
    assert all("inputs changed during compile" in failure for failure in receipts.failures)

    _main_harness(tmp_path, monkeypatch, obj, source)
    monkeypatch.setattr(census.build, "ensure_case_shims", lambda: None)

    def compile_rows(rows, sources, input_proof, strict):
        input_proof.failures += ["census input proof unavailable: a.cpp", "census input proof unavailable: b.cpp"]
    monkeypatch.setattr(census.build, "compile_rows", compile_rows)
    monkeypatch.setattr(census, "link", lambda *a, **k: pytest.fail("linked without proof"))
    with pytest.raises(SystemExit, match=r"2 compiled objects have no census proof[\s\S]*a\.cpp[\s\S]*b\.cpp"):
        census.main(["--build"])
