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
def weaks():
    """{object: {name: default}} the batch fixture's weak reader returns."""
    return {}


@pytest.fixture
def batch(monkeypatch, tmp_path, weaks):
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
    monkeypatch.setattr(A, "weak_reader", lambda index, replacements: lambda obj: weaks.get(obj, {}))
    monkeypatch.setattr(A, "bridged_names", lambda: set())
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
    # the audit runs as one of the hook's concurrent jobs, beside the scoped audits
    jobs = hook[hook.index('_job_pids=()'):hook.index('# fast_forward_or_fail')]
    audits = hook[hook.index('# link_audit LIST'):hook.index('protected_paths_check() {')]
    block = hook[hook.index('    link_scope=$(mktemp)'):
                 hook.index('    stage "scoped DIR32 + eh + data audits, link_batch_audit')]
    setup = (f'set -euo pipefail\nverify=(); scope_units=(); scoped_list=""; base=a; local_sha=b\n'
             f'fail() {{ exit 1; }}\nshadow_cap() {{ return {status}; }}\nstage() {{ :; }}\n')
    done = subprocess.run([bash, "-c", setup + jobs + audits + block], capture_output=True, text=True)
    assert (done.returncode != 0) == blocked, done.stderr
    if status in (2, 124):
        assert "UNVERIFIED" in done.stderr


def test_omitted_references_names_a_changed_object_reaching_an_omitted_row(monkeypatch, tmp_path):
    omitted, kept = tmp_path / "thunks.obj", tmp_path / "kept.obj"
    kept.write_bytes(b"")
    monkeypatch.setattr(A.exit_link, "placement_objects", lambda rows: {omitted: "thunks.cpp"})
    monkeypatch.setattr(A.exit_link, "placement_rows", lambda rows: [{"name": "?j_0052b7b3@@YAXXZ"}])
    monkeypatch.setattr(A.build, "ledger_object_symbol", lambda row: row["name"])
    monkeypatch.setattr(A.exit_link, "coff_view", lambda path: ([], {}, b""))
    monkeypatch.setattr(A.exit_link, "coff_references",
                        lambda path, data: {"?j_0052b7b3@@YAXXZ", "?real@@YAXXZ"})
    assert A.omitted_references([], [kept]) == [("kept.obj", "?j_0052b7b3@@YAXXZ")]
    assert A.omitted_references([], [omitted]) == []


def test_omitted_reference_is_refused_even_when_receipts_are_stale(monkeypatch, tmp_path):
    saved = index()
    marker = tmp_path / "index.pkl"
    marker.touch()
    current = tmp_path / "ini.obj"
    current.touch()
    monkeypatch.setattr(A.link_check, "INDEX", marker)
    monkeypatch.setattr(A.link_check, "load_index", lambda: saved)
    monkeypatch.setattr(A, "changed_sources", lambda base, tip: {"Code/INI.cpp"})
    monkeypatch.setattr(A.link_census, "ledger", lambda: [{"source": "Code/INI.cpp"}])
    monkeypatch.setattr(A.link_census, "data_ledger", lambda: [])
    monkeypatch.setattr(A.link_census, "RetailTruth", lambda rows: None)
    monkeypatch.setattr(A.build, "obj_path", lambda source: current)
    monkeypatch.setattr(A.link_census, "object_current", lambda source, obj: False)
    monkeypatch.setattr(A, "omitted_references", lambda rows, objects: [("ini.obj", "?j_0052b7b3@@YAXXZ")] if objects else [])
    assert A.audit("a" * 40, "b" * 40, ["Code/INI.cpp"]) == 1


def test_a_stale_consumer_outside_the_verified_set_is_not_judged_for_omitted_references(monkeypatch, tmp_path, capsys):
    saved = index()
    marker = tmp_path / "index.pkl"
    marker.touch()
    current = tmp_path / "ini.obj"
    current.touch()
    monkeypatch.setattr(A.link_check, "INDEX", marker)
    monkeypatch.setattr(A.link_check, "load_index", lambda: saved)
    monkeypatch.setattr(A, "changed_sources", lambda base, tip: {"Code/INI.cpp"})
    monkeypatch.setattr(A.link_census, "ledger", lambda: [{"source": "Code/INI.cpp"}])
    monkeypatch.setattr(A.link_census, "data_ledger", lambda: [])
    monkeypatch.setattr(A.link_census, "RetailTruth", lambda rows: None)
    monkeypatch.setattr(A.build, "obj_path", lambda source: current)
    monkeypatch.setattr(A.link_census, "object_current", lambda source, obj: False)
    monkeypatch.setattr(A, "omitted_references", lambda rows, objects: [("ini.obj", "?j_0052b7b3@@YAXXZ")] if objects else [])
    assert A.audit("a" * 40, "b" * 40, []) == 2      # in scope by the change alone, stale, not verified: unverified
    assert "OMITTED" not in capsys.readouterr().out



# The real-link loss check (LINK-626): a name a batch leaves with no definition, still referenced.
def test_removing_a_wrong_but_present_definition_is_a_real_link_loss(batch, capsys):
    saved, facts, _, _ = batch
    # The census judged the provider's copy wrong and the consumer unlinked, so the existing
    # checks skip both; the real link still resolved `api` through that copy.
    saved["comdat"]["api"] = [(0, "bad", "wrong")]
    saved["blockers"]["Code/caller.cpp"]["linked"] = False
    saved["blockers"]["Code/provider.cpp"]["linked"] = False
    facts["provider.obj"] = ([], [], [], [])
    assert A.audit("a" * 40, "b" * 40, []) == 0                 # report mode: the exit is unchanged
    out = capsys.readouterr().out
    assert "REAL-LINK LOSS api: defined before this batch by provider.obj, by no kept object after; " \
           "still referenced by caller.obj" in out
    assert "(report mode: not refused)" in out


def test_the_refuse_mode_fails_the_push(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    saved["blockers"]["Code/caller.cpp"]["linked"] = False
    facts["provider.obj"] = ([], [], [], [])
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "refuse mode: refused" in capsys.readouterr().out


def test_an_unreferenced_removal_is_no_real_link_loss(batch, capsys):
    saved, facts, _, _ = batch
    saved["touches"]["caller.obj"] = {"caller"}
    facts["provider.obj"] = ([], [], [], [])
    facts["caller.obj"] = ([], ["caller"], [], [])
    A.audit("a" * 40, "b" * 40, [])
    assert "REAL-LINK LOSS" not in capsys.readouterr().out


def test_a_name_the_toolchain_resolves_is_no_real_link_loss(batch, capsys):
    saved, facts, _, _ = batch
    saved["blockers"]["Code/caller.cpp"]["linked"] = False
    saved["excuses"]["runtime"] = {"api"}
    facts["provider.obj"] = ([], [], [], [])
    A.audit("a" * 40, "b" * 40, [])
    assert "REAL-LINK LOSS" not in capsys.readouterr().out


def test_a_moved_definition_is_no_real_link_loss(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    saved["blockers"]["Code/caller.cpp"]["linked"] = False
    facts["provider.obj"] = ([], [], [], [])
    facts["caller.obj"] = ([("api", "good", 10, "retail")], ["caller"], [], [])
    monkeypatch.setattr(A, "changed_sources", lambda base, tip: {"Code/provider.cpp", "Code/caller.cpp"})
    A.audit("a" * 40, "b" * 40, [])
    assert "REAL-LINK LOSS" not in capsys.readouterr().out


def test_real_link_losses_ignore_census_verdicts_and_pins():
    saved = index()
    saved.update(excuses={"runtime": set(), "imported": {}, "stubs": {}},
                 touches={"retail.obj": {"insert_unique"}, "ini.obj": {"insert_unique"}})
    updated = A.overlay(saved, [], {"retail.obj"}, None)
    updated["comdat"] = {}
    losses = A.real_link_losses(saved, updated, {"insert_unique"}, {"retail.obj": 0, "ini.obj": 1}, {"ini.obj": 0})
    assert losses == [("insert_unique", ["ini.obj", "retail.obj"], ["ini.obj"], "loss")]


# Review of bfc63dc096: counterexamples to the first real-link loss rule.
def tables(objects, **kw):
    found = {"objects": list(objects), "strong": {}, "comdat": {}, "common": {}, "alternates": {},
             "touches": {}, "forgotten": set(), "excuses": {"runtime": set(), "imported": {}, "stubs": {}}}
    found.update(kw)
    return found


def rank(*objects):
    return {obj: i for i, obj in enumerate(objects)}


def test_a_placement_only_definer_hides_no_loss(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    # gthunks.obj also defines `api`, but exit_link.py leaves placement objects out of the link.
    saved["objects"].append("gthunks.obj")
    saved["strong"] = {**saved["strong"], "api": [2]}
    saved["touches"]["gthunks.obj"] = {"api"}
    saved["blockers"]["Code/caller.cpp"]["linked"] = False
    facts["provider.obj"] = ([], [], [], [])
    monkeypatch.setattr(A.link_check, "link_rank", lambda rows: rank("provider.obj", "caller.obj", "gthunks.obj"))
    monkeypatch.setattr(A.exit_link, "placement_objects", lambda rows: {
        Path("gthunks.obj"): "Code/gen_small/gthunks_1_admitted.cpp"})
    A.audit("a" * 40, "b" * 40, [])
    out = capsys.readouterr().out
    assert "REAL-LINK LOSS api: defined before this batch by provider.obj, by no kept object after; " \
           "still referenced by caller.obj" in out


def test_a_name_only_a_placement_object_defined_was_never_in_the_real_link():
    before = tables(["thunks.obj", "caller.obj"], strong={"api": [0]},
                    touches={"caller.obj": {"api"}, "thunks.obj": {"api"}})
    after = tables(["caller.obj"], touches={"caller.obj": {"api"}})
    assert A.real_link_losses(before, after, {"api"}, rank("thunks.obj", "caller.obj"),
                              rank("caller.obj"), omitted={"thunks.obj"}) == []


def test_an_alternate_to_an_undefined_target_resolves_nothing():
    before = tables(["provider.obj", "caller.obj"], strong={"api": [0]}, touches={"caller.obj": {"api"}})
    after = tables(["caller.obj"], alternates={"api": [(0, "missing")]}, touches={"caller.obj": {"api"}})
    losses = A.real_link_losses(before, after, {"api"}, rank("provider.obj", "caller.obj"), rank("caller.obj"))
    assert losses == [("api", ["provider.obj"], ["caller.obj"], "loss")]


def test_an_alternate_chain_to_a_definition_resolves_and_a_cycle_does_not():
    before = tables(["provider.obj", "caller.obj"], strong={"api": [0]}, touches={"caller.obj": {"api"}})
    chain = tables(["caller.obj"], strong={"real": [0]},
                   alternates={"api": [(0, "mid")], "mid": [(0, "real")]}, touches={"caller.obj": {"api"}})
    cycle = tables(["caller.obj"], alternates={"api": [(0, "mid")], "mid": [(0, "api")]},
                   touches={"caller.obj": {"api"}})
    ranks = rank("provider.obj", "caller.obj"), rank("caller.obj")
    assert A.real_link_losses(before, chain, {"api"}, *ranks) == []
    assert A.real_link_losses(before, cycle, {"api"}, *ranks) == [("api", ["provider.obj"], ["caller.obj"], "loss")]


def test_an_alternate_in_an_omitted_object_resolves_nothing():
    before = tables(["provider.obj", "caller.obj"], strong={"api": [0]}, touches={"caller.obj": {"api"}})
    after = tables(["caller.obj", "thunks.obj"], strong={"real": [0]}, alternates={"api": [(1, "real")]},
                   touches={"caller.obj": {"api"}})
    losses = A.real_link_losses(before, after, {"api"}, rank("provider.obj", "caller.obj"),
                                rank("caller.obj", "thunks.obj"), omitted={"thunks.obj"})
    assert [entry[0] for entry in losses] == ["api"]


def test_a_weak_fallback_that_resolves_is_no_loss_and_one_that_does_not_is(batch, weaks, capsys):
    saved, facts, _, _ = batch
    saved["blockers"]["Code/caller.cpp"]["linked"] = False
    saved["strong"] = {**saved["strong"], "fallback": [1]}
    facts["provider.obj"] = ([], [], [], [])
    weaks["caller.obj"] = {"api": "fallback"}
    A.audit("a" * 40, "b" * 40, [])
    assert "REAL-LINK LOSS" not in capsys.readouterr().out
    weaks["caller.obj"] = {"api": "nowhere"}
    A.audit("a" * 40, "b" * 40, [])
    assert "REAL-LINK LOSS api:" in capsys.readouterr().out


def test_a_name_the_vtable_bridge_may_generate_is_a_candidate(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    saved["blockers"]["Code/caller.cpp"]["linked"] = False
    facts["provider.obj"] = ([], [], [], [])
    monkeypatch.setattr(A, "bridged_names", lambda: {"api"})
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 0
    out = capsys.readouterr().out
    assert "REAL-LINK LOSS CANDIDATE api:" in out and "the vtable bridge" in out
    assert "0 name(s) the real link would no longer resolve, 1 candidate(s) " \
           "(refuse mode: candidates only, not refused)" in out


def test_an_unreadable_weak_table_makes_a_candidate(batch, weaks, monkeypatch, capsys):
    saved, facts, _, _ = batch
    saved["blockers"]["Code/caller.cpp"]["linked"] = False
    facts["provider.obj"] = ([], [], [], [])
    weaks["caller.obj"] = None
    A.audit("a" * 40, "b" * 40, [])
    assert "REAL-LINK LOSS CANDIDATE api:" in capsys.readouterr().out


@pytest.mark.parametrize("broken", ["real_link_losses", "bridged_names", "weak_reader", "report_real_link_losses"])
def test_report_mode_never_lets_the_check_change_the_exit(batch, monkeypatch, capsys, broken):
    saved, facts, _, _ = batch
    saved["blockers"]["Code/caller.cpp"]["linked"] = False
    facts["provider.obj"] = ([], [], [], [])

    def boom(*args, **kwargs):
        raise RuntimeError("injected")
    monkeypatch.setattr(A, broken, boom)
    assert A.audit("a" * 40, "b" * 40, []) == 0
    assert "real-link loss check failed: RuntimeError: injected (report mode: unverified)" in capsys.readouterr().out


def test_a_failing_check_in_refuse_mode_is_inconclusive(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    saved["blockers"]["Code/caller.cpp"]["linked"] = False
    facts["provider.obj"] = ([], [], [], [])
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    monkeypatch.setattr(A, "bridged_names", lambda: 1 / 0)
    assert A.audit("a" * 40, "b" * 40, []) == 2


def test_refuse_mode_on_a_provisional_baseline_does_not_say_refused(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    saved["blockers"]["Code/caller.cpp"]["linked"] = False
    facts["provider.obj"] = ([], [], [], [])
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("c" * 40, "b" * 40, []) == 2
    out = capsys.readouterr().out
    assert "(refuse mode: provisional baseline, not refused)" in out
    assert "refuse mode: refused" not in out


def vtable_object(path, default_defined):
    """A COFF object whose .rdata vftable slot relocates to the weak `??_Eapi` (default `??_Gapi`),
    the shape MSVC emits for a deleting destructor slot."""
    import struct
    rdata = b"\0" * 4
    offset = 20 + 40
    reloc = offset + len(rdata)
    table = reloc + 10
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, table, 5, 0, 0)
    section = b".rdata\0\0" + struct.pack("<IIIIIIHHI", 0, 0, 4, offset, reloc, 0, 1, 0, 0x40300040)
    relocation = struct.pack("<IIH", 0, 2, 6)                        # DIR32 to symbol 2, ??_Eapi
    strings = bytearray(4)

    def symbol(name, section_number, storage, aux=0):
        raw = name.encode()
        field = raw.ljust(8, b"\0") if len(raw) <= 8 else struct.pack("<II", 0, len(strings))
        if len(raw) > 8:
            strings.extend(raw + b"\0")
        return field + struct.pack("<IhHBB", 0, section_number, 0, storage, aux)
    records = symbol("??_7api@@6B@", 1, A.link_census.EXTERNAL)
    records += symbol("??_Gapi@@UAEPAXI@Z", 0, A.link_census.EXTERNAL)        # symbol 1: the default
    records += symbol("??_Eapi@@UAEPAXI@Z", 0, A.link_census.WEAK_EXTERNAL, 1)
    records += struct.pack("<II", 1, 3) + b"\0" * 10                 # aux: tag symbol 1, SEARCH_ALIAS
    records += symbol("_unrelated", 0, A.link_census.EXTERNAL)
    strings[:4] = struct.pack("<I", len(strings))
    path.write_bytes(header + section + rdata + relocation + records + bytes(strings))
    return path


@pytest.mark.parametrize("lost, loses", [("??_Eapi@@UAEPAXI@Z", False), ("??_Gapi@@UAEPAXI@Z", True)])
def test_a_reference_from_a_vtable_section_is_judged_through_its_weak_default(tmp_path, lost, loses):
    obj = vtable_object(tmp_path / "vtable.obj", True)
    fact = A.link_census.object_facts(obj, object())
    touches = A.link_census.touched_names(fact)
    assert {"??_Eapi@@UAEPAXI@Z", "??_Gapi@@UAEPAXI@Z"} <= touches
    names = {"??_Eapi@@UAEPAXI@Z", "??_Gapi@@UAEPAXI@Z"}
    kept = names - {lost}
    before = tables(["dtor.obj", "vtable.obj"], strong={name: [0] for name in names},
                    touches={"vtable.obj": touches})
    after = tables(["dtor.obj", "vtable.obj"], strong={name: [0] for name in kept},
                   touches={"vtable.obj": touches})
    index = {"blockers": {}}
    losses = A.real_link_losses(before, after, {lost}, rank("dtor.obj", "vtable.obj"),
                                rank("dtor.obj", "vtable.obj"), weak_defaults=A.weak_reader(index, [obj]))
    assert [entry[0] for entry in losses] == ([lost] if loses else [])
    assert all(entry[2] == ["vtable.obj"] and entry[3] == "loss" for entry in losses)
