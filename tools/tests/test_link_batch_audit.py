"""Outgoing link regressions: identity, provider removal and class declarations."""
import sys
import copy
import shutil
import subprocess
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_batch_audit as A


@pytest.fixture(autouse=True)
def no_real_git(monkeypatch):
    monkeypatch.setattr(A, "git", lambda *args: "Code/intervening.cpp" if "c" * 40 in args else "")


def index():
    return {
        "objects": ["retail.obj", "ini.obj"],
        "comdat": {"insert_unique": [(0, "good", "retail"), (1, "bad", "wrong")]},
        "strong": {}, "common": {}, "alternates": {}, "digests": {},
        "blockers": {"Code/retail.cpp": {"object": "retail.obj", "linked": True},
                     "Code/INI.cpp": {"object": "ini.obj", "linked": True}},
        "bytes": {"Code/retail.cpp": 120, "Code/INI.cpp": 80},
        "selection": {"exceptions": {}, "owners": {}},
        "touches": {"retail.obj": {"insert_unique"}, "ini.obj": {"insert_unique"}},
        "common_schema": A.link_check.COMMON_SCHEMA,
        "meta": {"commit": "a" * 40, "date": "today", "clean_tree": True},
    }


def test_existing_wrong_copy_can_become_first():
    saved = index()
    before = A.selected(saved, "insert_unique", {"retail.obj": 0, "ini.obj": 1})
    after = A.selected(saved, "insert_unique", {"ini.obj": 0, "retail.obj": 1})
    assert before == ("retail.obj", "ok")
    assert after == ("ini.obj", "wrong")


def test_retired_donor_removes_its_provider():
    saved = index()
    updated = A.overlay(saved, [], {"retail.obj"}, None)
    assert A.selected(saved, "insert_unique", {"retail.obj": 0, "ini.obj": 1}) == ("retail.obj", "ok")
    assert A.selected(updated, "insert_unique", {"ini.obj": 0}) == ("ini.obj", "wrong")
    assert "Code/retail.cpp" not in updated["blockers"]


def test_batch_reports_selection_loss_and_stale_baseline(monkeypatch, tmp_path, capsys):
    saved = index()
    marker = tmp_path / "index.pkl"
    marker.touch()
    current = tmp_path / "ini.obj"
    current.touch()
    monkeypatch.setattr(A.link_check, "INDEX", marker)
    monkeypatch.setattr(A.link_check, "load_index", lambda: saved)
    monkeypatch.setattr(A.link_check, "link_rank", lambda rows: {"ini.obj": 0, "retail.obj": 1})
    monkeypatch.setattr(A, "changed_sources", lambda base, tip: {"Code/INI.cpp"})
    monkeypatch.setattr(A.link_census, "ledger", lambda: [{"source": "Code/INI.cpp"}])
    monkeypatch.setattr(A.link_census, "data_ledger", lambda: [])
    monkeypatch.setattr(A.link_census, "RetailTruth", lambda rows: None)
    monkeypatch.setattr(A.link_census, "ledger_owners", lambda rows: {})
    monkeypatch.setattr(A.build, "obj_path", lambda source: current)
    monkeypatch.setattr(A.link_census, "object_current", lambda source, obj: True)
    monkeypatch.setattr(A.link_census, "object_facts", lambda obj, truth: ([
        ("insert_unique", "bad", 10, "wrong")], [], [], []))
    monkeypatch.setattr(A.link_census, "common_definitions", lambda obj: {})
    monkeypatch.setattr(A, "overlay", lambda ix, objects, removed, truth: copy.deepcopy(ix))
    monkeypatch.setattr(A.link_check, "check_object", lambda obj, ix, truth, source: {"unresolved": []})

    A.audit("a" * 40, "b" * 40, ["Code/INI.cpp"])
    output = capsys.readouterr().out
    assert "REVIEW wrong selected provider: insert_unique; selected retail.obj -> ini.obj" in output
    assert "INCONCLUSIVE baseline" not in output

    A.audit("c" * 40, "b" * 40, ["Code/INI.cpp"])
    output = capsys.readouterr().out
    assert "INCONCLUSIVE baseline" in output
    assert "REVIEW wrong selected provider" in output


def test_changed_unit_unresolved_reports_prior_bytes(monkeypatch, tmp_path, capsys):
    saved = index()
    marker = tmp_path / "index.pkl"
    marker.touch()
    current = tmp_path / "ini.obj"
    current.touch()
    monkeypatch.setattr(A.link_check, "INDEX", marker)
    monkeypatch.setattr(A.link_check, "load_index", lambda: saved)
    monkeypatch.setattr(A.link_check, "link_rank", lambda rows: {"retail.obj": 0, "ini.obj": 1})
    monkeypatch.setattr(A, "changed_sources", lambda base, tip: {"Code/INI.cpp"})
    monkeypatch.setattr(A.link_census, "ledger", lambda: [{"source": "Code/INI.cpp"}])
    monkeypatch.setattr(A.link_census, "data_ledger", lambda: [])
    monkeypatch.setattr(A.link_census, "RetailTruth", lambda rows: None)
    monkeypatch.setattr(A.link_census, "ledger_owners", lambda rows: {})
    monkeypatch.setattr(A.build, "obj_path", lambda source: current)
    monkeypatch.setattr(A.link_census, "object_current", lambda source, obj: True)
    monkeypatch.setattr(A.link_census, "object_facts", lambda obj, truth: ([], [], ["__assert"], []))
    monkeypatch.setattr(A.link_census, "common_definitions", lambda obj: {})
    monkeypatch.setattr(A, "overlay", lambda ix, objects, removed, truth: ix)
    monkeypatch.setattr(A.link_check, "check_object", lambda obj, ix, truth, source: {"unresolved": ["__assert"]})
    A.audit("a" * 40, "b" * 40, ["Code/INI.cpp"])
    assert "LOST 80 previously linked source bytes: unresolved in Code/INI.cpp: __assert" in capsys.readouterr().out


def test_no_index_is_inconclusive(monkeypatch, tmp_path, capsys):
    monkeypatch.setattr(A, "changed_sources", lambda base, tip: {"Code/INI.cpp"})
    monkeypatch.setattr(A.link_check, "INDEX", tmp_path / "missing.pkl")
    assert A.audit("a", "b", []) == 2
    assert "INCONCLUSIVE: census index missing" in capsys.readouterr().out


def test_missing_source_list_is_inconclusive(monkeypatch, tmp_path):
    monkeypatch.setattr(sys, "argv", ["audit", "--base", "a", "--tip", "b",
                                    "--sources-from", str(tmp_path / "missing")])
    assert A.main() == 2


@pytest.fixture
def batch(monkeypatch, tmp_path):
    """Use the real overlay and link resolver; supply small object fact sets."""
    saved = index()
    saved.update(objects=["provider.obj", "caller.obj"],
                 comdat={"api": [(0, "good", "retail")]}, strong={"caller": [1]},
                 blockers={"Code/provider.cpp": {"object": "provider.obj", "linked": True},
                           "Code/caller.cpp": {"object": "caller.obj", "linked": True}},
                 touches={"provider.obj": {"api"}, "caller.obj": {"caller", "api"}},
                 bytes={"Code/provider.cpp": 10, "Code/caller.cpp": 20},
                 references={"schema": A.link_check.REFERENCES_SCHEMA, "edges": {},
                             "referenced": {"api", "caller"}},
                 excuses={"runtime": set(), "imported": {}, "stubs": {}})
    facts = {"provider.obj": ([("api", "good", 10, "retail")], [], [], []),
             "caller.obj": ([], ["caller"], ["api"], [])}
    paths = {name: tmp_path / name for name in facts}
    for path in paths.values():
        path.touch()
    marker = tmp_path / "index.pkl"
    marker.touch()
    changes = {"Code/provider.cpp"}
    rows = [{"source": "Code/provider.cpp"}, {"source": "Code/caller.cpp"}]
    monkeypatch.setattr(A.link_check, "ROOT", tmp_path)
    monkeypatch.setattr(A.link_check, "INDEX", marker)
    monkeypatch.setattr(A.link_check, "load_index", lambda: saved)
    monkeypatch.setattr(A.link_check, "link_rank", lambda rows: {"provider.obj": 0, "caller.obj": 1})
    monkeypatch.setattr(A, "changed_sources", lambda base, tip: changes)
    monkeypatch.setattr(A.link_census, "ledger", lambda: rows)
    monkeypatch.setattr(A.link_census, "data_ledger", lambda: [])
    monkeypatch.setattr(A.link_census, "RetailTruth", lambda rows: object())
    monkeypatch.setattr(A.link_census, "ledger_owners", lambda rows: {})
    monkeypatch.setattr(A.build, "obj_path", lambda source: paths[source.stem + ".obj"])
    monkeypatch.setattr(A.link_census, "object_current", lambda source, obj: True)
    monkeypatch.setattr(A.link_census, "object_facts", lambda obj, truth: facts[obj.name])
    monkeypatch.setattr(A.link_census, "common_definitions", lambda obj: {})
    monkeypatch.setattr(A.link_check, "alternate_names", lambda obj: {})
    monkeypatch.setattr(A.link_census, "object_references", lambda obj: (
        set(facts[obj.name][1]) | set(facts[obj.name][2]), {}))
    return saved, facts, changes, paths


def test_ledger_only_identity_change_rejudges_same_provider(batch, monkeypatch, capsys):
    saved, facts, changes, _ = batch
    changes.clear()
    monkeypatch.setattr(A, "changed_identities", lambda base, tip: {"api"})
    # The object bytes/digest and holder do not move; only identity changes.
    facts["provider.obj"] = ([("api", "good", 10, "wrong")], [], [], [])
    assert A.audit("a" * 40, "b" * 40, []) == 1
    output = capsys.readouterr().out
    assert "wrong selected provider: api; selected provider.obj -> provider.obj" in output
    assert "selected in Code/caller.cpp" in output
    assert saved["comdat"]["api"] == [(0, "good", "retail")]


def test_removed_provider_breaks_unchanged_consumer(batch, capsys):
    _, facts, _, _ = batch
    facts["provider.obj"] = ([], [], [], [])
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "unresolved in Code/caller.cpp: api" in capsys.readouterr().out


def test_unused_provider_removal_is_not_a_regression(batch, capsys):
    saved, facts, _, _ = batch
    saved["touches"]["caller.obj"] = {"caller"}
    facts["provider.obj"] = ([], [], [], [])
    facts["caller.obj"] = ([], ["caller"], [], [])
    assert A.audit("a" * 40, "b" * 40, []) == 0
    assert "FAILED" not in capsys.readouterr().out


@pytest.mark.parametrize("layout,expected", [("same", 0), ("different", 1)])
def test_class_declaration_change_checks_vtable_copies(batch, layout, expected, capsys):
    saved, facts, changes, _ = batch
    saved["comdat"]["vtable"] = [(0, "same", None), (1, "same", None)]
    saved["touches"]["provider.obj"].add("vtable")
    saved["touches"]["caller.obj"].add("vtable")
    saved["references"]["referenced"].add("vtable")
    facts["provider.obj"][0].append(("vtable", "same", 16, None))
    facts["caller.obj"][0].append(("vtable", layout, 20, None))
    changes.clear()
    changes.add("Code/caller.cpp")
    assert A.audit("a" * 40, "b" * 40, []) == expected
    if expected:
        assert "comdat in Code/caller.cpp: vtable" in capsys.readouterr().out


def test_new_exclusive_definition_breaks_previous_linking_units(batch, capsys):
    _, facts, changes, _ = batch
    facts["caller.obj"] = ([], ["caller", "api"], [], [])
    changes.clear()
    changes.add("Code/caller.cpp")
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "duplicates in Code/caller.cpp: api" in capsys.readouterr().out


def test_new_merge_destination_preserves_linked_donors(batch, monkeypatch, capsys):
    saved, facts, changes, _ = batch
    saved["selection"]["owners"] = {"api": {"provider.obj"}}
    facts["caller.obj"] = ([], ["caller", "api"], ["missing_base_dtor"], [])
    changes.update({"Code/caller.cpp"})
    # caller.cpp was blocked before; the clean provider is now absorbed into it.
    saved["blockers"]["Code/caller.cpp"]["linked"] = False
    monkeypatch.setattr(A.link_census, "ledger", lambda: [{"source": "Code/caller.cpp", "name": "api"}])
    monkeypatch.setattr(A.link_check, "link_rank", lambda rows: {"caller.obj": 0})
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "unresolved in Code/caller.cpp: missing_base_dtor" in capsys.readouterr().out


def test_safe_replacement_passes_and_stale_baseline_is_unverified(batch):
    _, facts, _, _ = batch
    facts["provider.obj"] = ([("api", "new", 10, "retail")], [], [], [])
    assert A.audit("a" * 40, "b" * 40, []) == 0
    assert A.audit("d" * 40, "b" * 40, []) == 0  # census publication, identical inputs
    assert A.audit("c" * 40, "b" * 40, []) == 2


def test_stale_consumer_cannot_prove_a_loss(batch, monkeypatch):
    _, facts, _, _ = batch
    facts["provider.obj"] = ([], [], [], [])
    monkeypatch.setattr(A.link_census, "object_current", lambda source, obj: obj.name != "caller.obj")
    assert A.audit("a" * 40, "b" * 40, []) == 2


def test_old_index_without_consumer_names_is_unverified(batch):
    saved, _, _, _ = batch
    del saved["touches"]
    with pytest.raises(ValueError, match="per-object consumer names"):
        A.audit("a" * 40, "b" * 40, [])


def test_identity_diff_includes_removed_names_and_object_symbols(monkeypatch):
    monkeypatch.setattr(A, "git", lambda *args: '\n'.join([
        '--- a/reverse/functions.csv', '+++ b/reverse/functions.csv',
        '-old,,0x10,2,Code/old.cpp,matched,object-symbol=body',
        '+new,,0x20,2,Code/new.cpp,matched,', '+pin,0x30,reason']))
    assert A.changed_identities("a", "b") == {"old", "new", "body", "pin"}


def test_reordering_keeps_selection_and_numeric_tables_consistent():
    saved = index()
    saved["selection"]["exceptions"] = {"kept": 0}
    A.reorder(saved, {"ini.obj": 0, "retail.obj": 1})
    assert saved["objects"] == ["ini.obj", "retail.obj"]
    assert saved["comdat"]["insert_unique"] == [(0, "bad", "wrong"), (1, "good", "retail")]
    assert saved["selection"]["exceptions"]["kept"] == 1


def test_consumer_names_are_written_refreshed_and_retired(batch):
    saved, facts, _, paths = batch
    tables = A.link_check.index_tables(list(paths.values()), list(facts.values()), saved["selection"])
    assert tables["touches"]["caller.obj"] == {"caller", "api"}
    facts["caller.obj"] = ([], ["caller"], ["new_api"], [])
    A.link_check.refresh(saved, [paths["caller.obj"]], object())
    assert saved["touches"]["caller.obj"] == {"caller", "new_api"}
    A.link_check.forget(saved, {"caller.obj"})
    assert "caller.obj" not in saved["touches"]


@pytest.mark.parametrize("status,blocked", [(0, False), (1, True), (2, False), (124, False), (3, True)])
def test_push_hook_honors_audit_exit_status(status, blocked):
    bash = shutil.which("bash")
    if not bash:
        pytest.skip("bash unavailable")
    hook = (Path(__file__).resolve().parents[2] / ".githooks/pre-push").read_text()
    block = hook[hook.index('    link_scope=$(mktemp)'):hook.index('    # Replayed commits')]
    setup = (f'set -euo pipefail\nverify=(); scope_units=(); base=a; local_sha=b\n'
             f'fail() {{ exit 1; }}\nshadow_cap() {{ return {status}; }}\nstage() {{ :; }}\n')
    done = subprocess.run([bash, "-c", setup + block], capture_output=True, text=True)
    assert (done.returncode != 0) == blocked, done.stderr
    if status in (2, 124):
        assert "UNVERIFIED" in done.stderr
