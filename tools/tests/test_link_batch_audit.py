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


@pytest.fixture(autouse=True)
def no_real_verdict_log(monkeypatch, tmp_path_factory):
    # main() logs every run to the clone's git common dir; outside a repository it writes nothing.
    monkeypatch.setattr(A.link_check, "ROOT", tmp_path_factory.mktemp("not-a-repo"))


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
def includes():
    """{object: {name}} the batch fixture's /INCLUDE reader returns."""
    return {}


@pytest.fixture
def references():
    """{object: {name}} the batch fixture's reader returns for an object the index never read."""
    return {}


@pytest.fixture
def bridge():
    """{name: [vtable_bridge.definitions copy]} the batch fixture's bridge reader returns."""
    return {}


def select_any(obj, selection=2, **extra):
    return dict(object=obj, comdat=True, selection=selection, offset=0, other_publics=[], executable=False,
                archive=False, extent=4, pointers={}, **extra)


def bridged(at, rva=0x100):
    return {name: {"rva": rva, "names": set(at), "addresses": {other: {rva} for other in at}} for name in at}


@pytest.fixture
def batch(monkeypatch, tmp_path, weaks, includes, references, bridge):
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
    monkeypatch.setattr(A, "weak_reader", lambda *args: lambda obj: weaks.get(obj, {}))
    monkeypatch.setattr(A, "bridged_names", lambda: {})
    monkeypatch.setattr(A, "include_reader", lambda *args: lambda obj: includes.get(obj, set()))
    monkeypatch.setattr(A, "reference_reader", lambda paths: lambda obj: references.get(obj, set()))
    monkeypatch.setattr(A, "bridge_copy_reader", lambda paths: lambda names, holders: {
        name: copies for name, copies in bridge.items() if name in names})
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
    for obj in objects:                                          # every listed object was read
        found["touches"].setdefault(obj, set())
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


def test_a_name_the_vtable_bridge_may_generate_is_a_candidate(batch, bridge, monkeypatch, capsys):
    saved, facts, _, _ = batch
    saved["blockers"]["Code/caller.cpp"]["linked"] = False
    saved["comdat"]["twin"] = [(1, "t", "retail")]                    # caller keeps a COMDAT copy of `twin`
    facts["caller.obj"] = ([("twin", "t", 4, "retail")], ["caller"], ["api"], [])
    facts["provider.obj"] = ([], [], [], [])
    bridge["twin"] = [select_any("caller.obj")]
    monkeypatch.setattr(A, "bridged_names", lambda: bridged({"api", "twin"}))
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 2                     # unproven: inconclusive, never clean
    out = capsys.readouterr().out
    assert "REAL-LINK LOSS CANDIDATE api:" in out and "the vtable bridge" in out
    assert "0 name(s) the real link would no longer resolve, 1 candidate(s) " \
           "(refuse mode: candidates only, unverified)" in out
    assert "no linking regression found" not in out


@pytest.mark.parametrize("copy, why", [
    (dict(selection=3), "unsupported-selection"),
    (dict(offset=8), "shared-or-prefixed-comdat"),
    (dict(other_publics=["_other"]), "shared-or-prefixed-comdat"),
    (dict(executable=True), "shared-or-prefixed-comdat"),
    (dict(comdat=False), "strong neighbour: no copy left"),
])
def test_a_neighbour_the_bridge_refuses_leaves_a_loss(batch, bridge, monkeypatch, capsys, copy, why):
    saved, facts, _, _ = batch
    unlinked(saved)
    saved["comdat"]["twin"] = [(1, "t", "retail")]
    facts["caller.obj"] = ([("twin", "t", 4, "retail")], ["caller"], ["api"], [])
    facts["provider.obj"] = ([], [], [], [])
    bridge["twin"] = [{**select_any("caller.obj"), **copy}]
    monkeypatch.setattr(A, "bridged_names", lambda: bridged({"api", "twin"}))
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1, why
    out = capsys.readouterr().out
    assert "REAL-LINK LOSS api:" in out and "CANDIDATE" not in out


def test_a_name_bound_at_a_second_address_is_never_bridged(batch, bridge, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    saved["comdat"]["twin"] = [(1, "t", "retail")]
    facts["caller.obj"] = ([("twin", "t", 4, "retail")], ["caller"], ["api"], [])
    facts["provider.obj"] = ([], [], [], [])
    bridge["twin"] = [select_any("caller.obj")]
    table = bridged({"api", "twin"})
    table["api"]["addresses"]["twin"] = {0x100, 0x200}            # `twin` is also bound elsewhere
    monkeypatch.setattr(A, "bridged_names", lambda: table)
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1


def test_unreadable_bridge_copies_make_a_candidate(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    saved["comdat"]["twin"] = [(1, "t", "retail")]
    facts["caller.obj"] = ([("twin", "t", 4, "retail")], ["caller"], ["api"], [])
    facts["provider.obj"] = ([], [], [], [])
    monkeypatch.setattr(A, "bridged_names", lambda: bridged({"api", "twin"}))
    monkeypatch.setattr(A, "bridge_copy_reader", lambda paths: lambda names, holders: None)
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 2
    assert "REAL-LINK LOSS CANDIDATE api:" in capsys.readouterr().out


def test_the_bridge_copy_reader_reads_the_holders_with_the_bridge_s_own_reader(tmp_path):
    import link_cycle
    obj = link_cycle.write_coff(tmp_path / "t.obj", [(".rdata", 0x40301040, bytes(4), 2)],
                                [("??_7twin@@6B@", 1, 0, link_cycle.EXTERNAL)])
    found = A.bridge_copy_reader({"t.obj": obj})({"??_7twin@@6B@"}, {"t.obj"})
    assert [(c["comdat"], c["selection"]) for c in found["??_7twin@@6B@"]] == [(True, 2)]
    assert A.bridge_copy_reader({"gone.obj": tmp_path / "gone.obj"})({"x"}, {"gone.obj"}) is None
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


# Re-check of efda9b5a5b: referrers through an alias spelling and through /INCLUDE.
def test_a_caller_reaching_the_lost_name_through_an_alias_is_a_referrer(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    saved["blockers"]["Code/caller.cpp"]["linked"] = False
    saved["touches"]["caller.obj"] = {"caller", "public"}          # caller spells `public` ...
    saved["alternates"] = {"public": [(1, "api")]}                   # ... and redirects it to `api`
    facts["caller.obj"] = ([], ["caller"], ["public"], [])
    monkeypatch.setattr(A.link_check, "alternate_names",
                        lambda obj: {"public": "api"} if obj.name == "caller.obj" else {})
    facts["provider.obj"] = ([], [], [], [])
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "REAL-LINK LOSS public: defined before this batch through /alternatename, by no kept object after; " \
           "still referenced by caller.obj" in capsys.readouterr().out


def test_an_alias_chain_reaches_the_lost_name_and_a_defined_alias_does_not():
    chain = {"public": [(1, "mid")], "mid": [(1, "api")]}
    before = tables(["provider.obj", "caller.obj"], strong={"api": [0]}, alternates=chain,
                    touches={"caller.obj": {"public"}})
    after = tables(["caller.obj"], alternates={"public": [(0, "mid")], "mid": [(0, "api")]},
                   touches={"caller.obj": {"public"}})
    defined = tables(["caller.obj", "own.obj"], strong={"public": [1]}, alternates={"public": [(0, "mid")]},
                     touches={"caller.obj": {"public"}})
    cycle_before = tables(["provider.obj", "caller.obj"], strong={"api": [0]},
                          alternates={"public": [(1, "mid")], "mid": [(1, "public")], "x": [(1, "api")]},
                          touches={"caller.obj": {"mid"}})
    cycle = tables(["caller.obj"], alternates={"public": [(0, "mid")], "mid": [(0, "public")], "x": [(0, "api")]},
                   touches={"caller.obj": {"mid"}})
    old = rank("provider.obj", "caller.obj")
    assert A.real_link_losses(before, after, {"api"}, old, rank("caller.obj")) == [
        ("public", ["/alternatename"], ["caller.obj"], "loss")]
    assert A.real_link_losses(before, defined, {"api"}, old, rank("caller.obj", "own.obj")) == []
    # terminates; `mid` never resolved, before or after, so nothing was lost
    assert A.real_link_losses(cycle_before, cycle, {"api"}, old, rank("caller.obj")) == []


def test_a_weak_default_satisfies_an_alias_spelling_only_when_it_resolves():
    before = tables(["provider.obj", "caller.obj"], strong={"api": [0]}, alternates={"public": [(1, "api")]},
                    touches={"caller.obj": {"public"}})
    after = tables(["caller.obj"], strong={"fallback": [0]}, alternates={"public": [(0, "api")]},
                   touches={"caller.obj": {"public"}})
    old, new = rank("provider.obj", "caller.obj"), rank("caller.obj")
    assert A.real_link_losses(before, after, {"api"}, old, new,
                              weak_defaults=lambda obj: {"public": "fallback"}) == []
    assert [entry[0] for entry in A.real_link_losses(before, after, {"api"}, old, new,
                                                     weak_defaults=lambda obj: {"public": "nowhere"})] == ["public"]


def include_object(path, text):
    import struct
    body = text.encode("latin-1")
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 20 + 40 + len(body), 0, 0, 0)
    section = b".drectve" + struct.pack("<IIIIIIHHI", 0, 0, len(body), 60, 0, 0, 0, 0, 0x100A00)
    path.write_bytes(header + section + body + struct.pack("<I", 4))
    return path


@pytest.mark.parametrize("directive", [" /INCLUDE:api ", ' /include:"api" ', " /INCLUDE:public "])
def test_an_include_directive_is_a_referrer(tmp_path, directive):
    obj = include_object(tmp_path / "include.obj", directive)
    fact = A.link_census.object_facts(obj, object())
    assert "api" not in A.link_census.touched_names(fact)          # the symbol table alone misses it
    before = tables(["provider.obj", "include.obj"], strong={"api": [0]}, alternates={"public": [(1, "api")]},
                    touches={"include.obj": set()})
    after = tables(["include.obj"], alternates={"public": [(0, "api")]}, touches={"include.obj": set()})
    losses = A.real_link_losses(before, after, {"api"}, rank("provider.obj", "include.obj"), rank("include.obj"),
                                includes=A.include_reader({"blockers": {}}, [obj]))
    spelled = "public" if "public" in directive else "api"
    assert [(name, referrers, kind) for name, _before, referrers, kind in losses] == [
        (spelled, ["include.obj"], "loss")]


def test_includes_are_read_only_for_a_name_the_reference_graph_holds_or_from_changed_objects():
    before = tables(["provider.obj", "include.obj"], strong={"api": [0]}, touches={"include.obj": set()})
    after = tables(["include.obj"], touches={"include.obj": set()})
    old, new = rank("provider.obj", "include.obj"), rank("include.obj")
    read = []

    def includes(obj):
        read.append(obj)
        return {"api"}
    assert A.real_link_losses(before, after, {"api"}, old, new, includes=includes, referenced={"other"}) == []
    assert read == []
    assert [e[0] for e in A.real_link_losses(before, after, {"api"}, old, new, includes=includes,
                                             referenced={"other"}, changed={"include.obj"})] == ["api"]
    assert [e[0] for e in A.real_link_losses(before, after, {"api"}, old, new, includes=includes,
                                             referenced={"api"})] == ["api"]
    assert [e[0] for e in A.real_link_losses(before, after, {"api"}, old, new, includes=includes)] == ["api"]


def test_an_unreadable_directive_table_makes_a_candidate_only_without_other_referrers():
    before = tables(["provider.obj", "include.obj"], strong={"api": [0]}, touches={"include.obj": set()})
    after = tables(["include.obj"], touches={"include.obj": set()})
    losses = A.real_link_losses(before, after, {"api"}, rank("provider.obj", "include.obj"), rank("include.obj"),
                                includes=lambda obj: None, referenced={"api"})
    assert losses == [("api", ["provider.obj"], ["(an unread object)"], "candidate")]


def test_an_include_in_a_batch_is_reported_by_the_audit(batch, includes, capsys):
    saved, facts, _, _ = batch
    saved["blockers"]["Code/caller.cpp"]["linked"] = False
    saved["touches"]["caller.obj"] = {"caller"}
    facts["caller.obj"] = ([], ["caller"], [], [])
    facts["provider.obj"] = ([], [], [], [])
    includes["caller.obj"] = {"api"}
    A.audit("a" * 40, "b" * 40, [])
    assert "REAL-LINK LOSS api: defined before this batch by provider.obj, by no kept object after; " \
           "still referenced by caller.obj" in capsys.readouterr().out


def test_an_alias_only_an_omitted_object_declares_reaches_nothing():
    before = tables(["provider.obj", "caller.obj"], strong={"api": [0]}, touches={"caller.obj": {"public"}})
    after = tables(["caller.obj", "thunks.obj"], alternates={"public": [(1, "api")]},
                   touches={"caller.obj": {"public"}})
    assert A.real_link_losses(before, after, {"api"}, rank("provider.obj", "caller.obj"),
                              rank("caller.obj", "thunks.obj"), omitted={"thunks.obj"},
                              referenced=set()) == []


def test_a_weak_default_for_one_spelling_does_not_cover_another():
    before = tables(["provider.obj", "caller.obj"], strong={"api": [0]}, touches={"caller.obj": {"api", "public"}})
    after = tables(["caller.obj"], strong={"fallback": [0]}, alternates={"public": [(0, "api")]},
                   touches={"caller.obj": {"api", "public"}})
    losses = A.real_link_losses(before, after, {"api"}, rank("provider.obj", "caller.obj"), rank("caller.obj"),
                                weak_defaults=lambda obj: {"public": "fallback"})
    assert losses == [("api", ["provider.obj"], ["caller.obj"], "loss")]


# Re-check of 3448a035de: aliases from the before-state, and one proof outweighs any doubt.
def unlinked(saved):
    for entry in saved["blockers"].values():
        entry["linked"] = False


def test_a_changed_object_dropping_its_alias_and_definition_strands_the_caller(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    saved["alternates"] = {"public": [(0, "api")]}                   # provider.obj: /alternatename:public=api
    saved["touches"]["caller.obj"] = {"caller", "public"}
    facts["caller.obj"] = ([], ["caller"], ["public"], [])
    facts["provider.obj"] = ([], [], [], [])                          # both the definition and the directive go
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "REAL-LINK LOSS public: defined before this batch through /alternatename, by no kept object after; " \
           "still referenced by caller.obj" in capsys.readouterr().out


def test_a_deleted_object_holding_the_alias_strands_the_caller(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    saved["alternates"] = {"public": [(0, "api")]}
    saved["touches"]["caller.obj"] = {"caller", "public"}
    facts["caller.obj"] = ([], ["caller"], ["public"], [])
    monkeypatch.setattr(A.link_census, "ledger", lambda: [{"source": "Code/caller.cpp"}])
    monkeypatch.setattr(A.link_check, "link_rank", lambda rows: {"caller.obj": 0})
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "REAL-LINK LOSS public:" in capsys.readouterr().out


def test_an_old_alias_the_kept_inputs_resolve_another_way_is_no_spelling():
    before = tables(["provider.obj", "caller.obj"], strong={"api": [0]},
                    alternates={"public": [(0, "api")]}, touches={"caller.obj": {"public"}})
    after = tables(["caller.obj", "new.obj"], strong={"public": [1]}, touches={"caller.obj": {"public"}})
    assert A.real_link_losses(before, after, {"api"}, rank("provider.obj", "caller.obj"),
                              rank("caller.obj", "new.obj"), referenced=set()) == []


def test_an_old_alias_held_only_by_an_omitted_object_is_no_spelling():
    before = tables(["provider.obj", "caller.obj", "thunks.obj"], strong={"api": [0]},
                    alternates={"public": [(2, "api")]}, touches={"caller.obj": {"public"}})
    after = tables(["caller.obj", "thunks.obj"], touches={"caller.obj": {"public"}})
    assert A.real_link_losses(before, after, {"api"}, rank("provider.obj", "caller.obj", "thunks.obj"),
                              rank("caller.obj", "thunks.obj"), omitted={"thunks.obj"}, referenced=set()) == []


def test_an_unreadable_referrer_does_not_downgrade_a_proven_one(batch, weaks, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    facts["provider.obj"] = ([], [], ["api"], [])                    # loses `api`, still calls it
    weaks["caller.obj"] = None                                       # caller's weak table unreadable
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1
    out = capsys.readouterr().out
    assert "REAL-LINK LOSS api: defined before this batch by provider.obj, by no kept object after; " \
           "still referenced by caller.obj, provider.obj" in out
    assert "CANDIDATE" not in out


def test_an_include_proof_outweighs_an_unreadable_symbol_referrer(batch, weaks, includes, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    facts["provider.obj"] = ([], [], ["api"], [])
    weaks["provider.obj"] = None
    saved["touches"]["caller.obj"] = {"caller"}
    facts["caller.obj"] = ([], ["caller"], [], [])
    includes["caller.obj"] = {"api"}
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1
    out = capsys.readouterr().out
    assert "REAL-LINK LOSS api:" in out and "CANDIDATE" not in out


def test_only_unreadable_referrers_make_a_candidate():
    before = tables(["provider.obj", "caller.obj"], strong={"api": [0]}, touches={"caller.obj": {"api"}})
    after = tables(["caller.obj"], touches={"caller.obj": {"api"}})
    assert A.real_link_losses(before, after, {"api"}, rank("provider.obj", "caller.obj"), rank("caller.obj"),
                              weak_defaults=lambda obj: None) == [
        ("api", ["provider.obj"], ["caller.obj"], "candidate")]


def test_the_reference_graph_shortcut_passes_a_clean_batch_without_reading_unchanged_objects(
        batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    saved["references"]["referenced"] = {"caller"}                   # nothing the link keeps reaches `api`
    saved["touches"]["caller.obj"] = {"caller"}
    facts["caller.obj"] = ([], ["caller"], [], [])
    facts["provider.obj"] = ([], [], [], [])
    read = []

    def reader(*args):
        def includes(obj):
            read.append(obj)
            return set()
        return includes
    monkeypatch.setattr(A, "include_reader", reader)
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 0
    out = capsys.readouterr().out
    assert "REAL-LINK LOSS" not in out and "no linking regression found" in out
    assert read == ["provider.obj"]                                  # the changed object only


# Round 3 (cff58099ab): the vtable bridge's own eligibility, split and alias-only chains, and an
# index --update-index moved past its census.
def test_a_lost_vtable_name_with_no_kept_copy_beside_it_is_a_loss(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    facts["provider.obj"] = ([], [], [], [])
    # The ledger lists `api` as a vtable with a neighbour, but no kept object has a COMDAT copy of
    # either: the bridge would refuse no-kept-definition, so nothing emits `api`.
    monkeypatch.setattr(A, "bridged_names", lambda: bridged({"api", "twin"}))
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1
    out = capsys.readouterr().out
    assert "REAL-LINK LOSS api:" in out and "CANDIDATE" not in out
def test_bridged_names_keep_only_names_with_one_retail_address(monkeypatch):
    import vtable_bridge
    rows = [{"address": "0x10", "name": "a", "names": "b"}, {"address": "0x20", "name": "c", "names": "b"}]
    monkeypatch.setattr(vtable_bridge, "table_rows", lambda root: rows)
    assert A.bridged_names() == {
        "a": {"rva": 0x10, "names": {"a", "b"}, "addresses": {"a": {0x10}, "b": {0x10, 0x20}}},
        "c": {"rva": 0x20, "names": {"b", "c"}, "addresses": {"b": {0x10, 0x20}, "c": {0x20}}}}
def test_resolving_an_inner_alias_leaves_the_outer_one_unresolved(batch, monkeypatch, capsys):
    saved, facts, changes, _ = batch
    unlinked(saved)
    saved["alternates"] = {"public": [(0, "mid")], "mid": [(1, "api")]}   # provider: public=mid; caller: mid=api
    saved["touches"]["caller.obj"] = {"caller", "public"}
    facts["provider.obj"] = ([], [], [], [])
    facts["caller.obj"] = ([], ["caller", "mid"], ["public"], [])      # caller now defines a real `mid`
    changes.add("Code/caller.cpp")
    monkeypatch.setattr(A.link_check, "alternate_names",
                        lambda obj: {"mid": "api"} if obj.name == "caller.obj" else {})
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "REAL-LINK LOSS public: defined before this batch through /alternatename" in capsys.readouterr().out


def test_removing_only_an_alias_strands_its_callers(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    saved["alternates"] = {"public": [(0, "api")]}                   # provider keeps `api`, drops public=api
    saved["touches"]["caller.obj"] = {"caller", "public"}
    facts["caller.obj"] = ([], ["caller"], ["public"], [])
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "REAL-LINK LOSS public:" in capsys.readouterr().out


def test_a_kept_alias_whose_target_survives_is_no_loss(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    saved["alternates"] = {"public": [(0, "api")]}
    saved["touches"]["caller.obj"] = {"caller", "public"}
    facts["caller.obj"] = ([], ["caller"], ["public"], [])
    monkeypatch.setattr(A.link_check, "alternate_names",
                        lambda obj: {"public": "api"} if obj.name == "provider.obj" else {})
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 0
    assert "REAL-LINK LOSS" not in capsys.readouterr().out


def test_an_include_whose_weak_default_resolves_is_no_loss(batch, weaks, includes, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    saved["strong"]["fallback"] = [1]
    saved["touches"]["caller.obj"].add("fallback")
    facts["provider.obj"] = ([], [], [], [])
    facts["caller.obj"] = ([], ["caller", "fallback"], ["api"], [("api", "fallback")])
    weaks["caller.obj"] = {"api": "fallback"}
    includes["caller.obj"] = {"api"}
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 0


def updated_index_batch(saved, facts, paths, monkeypatch):
    """An index --update-index moved past its census: a unit added since is in the ledger and the
    link order but in no index table and not in the reference graph."""
    unlinked(saved)
    saved["meta"]["census_commit"] = "d" * 40
    saved["references"]["referenced"] = {"caller"}
    saved["touches"]["caller.obj"] = {"caller"}
    facts["caller.obj"] = ([], ["caller"], [], [])
    facts["provider.obj"] = ([], [], [], [])
    monkeypatch.setattr(A.link_census, "ledger", lambda: [{"source": "Code/provider.cpp"}, {"source": "Code/caller.cpp"},
                                                          {"source": "Code/new_unit.cpp"}])
    paths["new_unit.obj"] = paths["caller.obj"].parent / "new_unit.obj"
    paths["new_unit.obj"].touch()
    monkeypatch.setattr(A.link_check, "link_rank", lambda rows: rank("provider.obj", "caller.obj", "new_unit.obj"))
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")


def unit(defined=(), refs=(), weaks=None, alternates=None, forced=()):
    return {"defined": set(defined), "references": set(refs), "weaks": dict(weaks or {}),
            "alternates": dict(alternates or {}), "includes": set(forced)}


def test_an_include_in_a_unit_the_updated_index_never_read_is_found(batch, references, monkeypatch, capsys):
    saved, facts, _, paths = batch
    updated_index_batch(saved, facts, paths, monkeypatch)
    references["new_unit.obj"] = unit(forced={"api"})
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "REAL-LINK LOSS api:" in capsys.readouterr().out
def test_a_symbol_reference_in_a_unit_the_index_never_read_is_found(batch, references, monkeypatch, capsys):
    saved, facts, _, paths = batch
    updated_index_batch(saved, facts, paths, monkeypatch)
    references["new_unit.obj"] = {"api"}
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "REAL-LINK LOSS api: defined before this batch by provider.obj, by no kept object after; " \
           "still referenced by new_unit.obj" in capsys.readouterr().out


def test_an_unreadable_unit_the_index_never_read_makes_a_candidate(batch, references, monkeypatch, capsys):
    saved, facts, _, paths = batch
    updated_index_batch(saved, facts, paths, monkeypatch)
    references["new_unit.obj"] = None
    assert A.audit("a" * 40, "b" * 40, []) == 2
    out = capsys.readouterr().out
    assert "REAL-LINK LOSS CANDIDATE api:" in out and "no linking regression found" not in out


def test_a_definition_in_a_unit_the_index_never_read_keeps_the_name(batch, references, monkeypatch, capsys):
    saved, facts, _, paths = batch
    updated_index_batch(saved, facts, paths, monkeypatch)
    saved["touches"]["caller.obj"] = {"caller", "api"}
    facts["caller.obj"] = ([], ["caller"], ["api"], [])
    references["new_unit.obj"] = unit(defined={"api"})
    assert A.audit("a" * 40, "b" * 40, []) == 0
    assert "REAL-LINK LOSS" not in capsys.readouterr().out


def test_an_alias_in_a_unit_the_index_never_read_strands_its_callers(batch, references, monkeypatch, capsys):
    saved, facts, _, paths = batch
    updated_index_batch(saved, facts, paths, monkeypatch)
    saved["touches"]["caller.obj"] = {"caller", "public"}
    facts["caller.obj"] = ([], ["caller"], ["public"], [])
    references["new_unit.obj"] = unit(alternates={"public": "api"})
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "REAL-LINK LOSS public: defined before this batch through /alternatename" in capsys.readouterr().out


def test_report_mode_keeps_its_exit_but_does_not_claim_a_clean_pass(batch, references, monkeypatch, capsys):
    saved, facts, _, paths = batch
    updated_index_batch(saved, facts, paths, monkeypatch)
    references["new_unit.obj"] = None
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "report")
    assert A.audit("a" * 40, "b" * 40, []) == 0
    out = capsys.readouterr().out
    assert "no linking regression found in the checked scope" not in out
    assert "the real-link findings above are reported only" in out
def test_an_updated_index_reads_every_kept_object_s_directives():
    before = tables(["provider.obj", "old.obj"], strong={"api": [0]}, touches={"old.obj": set()})
    after = tables(["old.obj"], touches={"old.obj": set()})
    read = []

    def includes(obj):
        read.append(obj)
        return {"api"}
    args = (before, after, {"api"}, rank("provider.obj", "old.obj"), rank("old.obj"))
    assert A.real_link_losses(*args, includes=includes, referenced={"other"}) == []
    assert [e[0] for e in A.real_link_losses(*args, includes=includes, referenced={"other"},
                                             graph_trusted=False)] == ["api"]
    assert read == ["old.obj"]


def test_reference_reader_reads_a_unit_whole(tmp_path):
    import link_cycle
    obj = link_cycle.write_coff(tmp_path / "u.obj", [(".text", 0x60500020, b"\xc3", 0),
                                                     (".drectve", 0x100A00, b" /alternatename:public=api /INCLUDE:root ", 0)],
                                [("own", 1, 0, link_cycle.EXTERNAL), ("used", 0, 0, link_cycle.EXTERNAL)])
    assert A.reference_reader({"u.obj": obj})("u.obj") == {
        "defined": {"own"}, "references": {"used"}, "weaks": {}, "alternates": {"public": "api"}, "includes": {"root"}}
    assert A.reference_reader({"gone.obj": tmp_path / "gone.obj"})("gone.obj") is None
def test_dropping_an_alias_to_a_name_the_batch_never_defined_strands_its_callers():
    # provider.obj (changed) drops /alternatename:public=lib; `lib` lives in an unchanged object,
    # so it is not among the names the batch's objects define.
    before = tables(["provider.obj", "lib.obj", "caller.obj"], strong={"lib": [1]},
                    alternates={"public": [(0, "lib")]}, touches={"caller.obj": {"public"}})
    after = tables(["provider.obj", "lib.obj", "caller.obj"], strong={"lib": [1]}, touches={"caller.obj": {"public"}})
    order = rank("provider.obj", "lib.obj", "caller.obj")
    assert A.real_link_losses(before, after, set(), order, order, changed={"provider.obj"}) == [
        ("public", ["/alternatename"], ["caller.obj"], "loss")]
    assert A.real_link_losses(before, after, set(), order, order) == []        # nothing changed: nothing judged


def test_a_trusted_graph_still_reads_a_unit_the_index_never_read():
    before = tables(["provider.obj", "old.obj"], strong={"api": [0]})
    after = tables(["old.obj"])
    after["touches"].pop("old.obj")                              # a unit the census never indexed
    found = A.real_link_losses(before, after, {"api"}, rank("provider.obj", "old.obj"), rank("old.obj"),
                               references=lambda obj: unit(forced={"api"}), referenced={"other"})
    assert [(e[0], e[2], e[3]) for e in found] == [("api", ["old.obj"], "loss")]
def test_an_updated_index_does_not_trust_its_graph_for_an_indexed_unit(batch, includes, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    saved["meta"]["census_commit"] = "d" * 40                    # --update-index reread caller.obj ...
    saved["references"]["referenced"] = {"caller"}               # ... without regrowing the graph
    saved["touches"]["caller.obj"] = {"caller"}
    facts["caller.obj"] = ([], ["caller"], [], [])
    facts["provider.obj"] = ([], [], [], [])
    includes["caller.obj"] = {"api"}                             # its new /INCLUDE:api
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "REAL-LINK LOSS api:" in capsys.readouterr().out


# Round 4 (98ce5bd575): the real link's own import requests.
IMPORTS = {"runtime": {"_strcpy"}, "imported": {"socket": {"wsock32.dll"}, "GetTickCount": {"kernel32.dll"},
                                               "strlen": {"msvcr71.dll"}},
           "stubs": {"_socket@12": {("wsock32.dll", "socket")}, "_htons@4": {("wsock32.dll", "htons")}}}


@pytest.mark.parametrize("refs, defined, supplied", [
    ({"_socket@12"}, set(), {"_socket@12", "__imp__socket@12"}),          # a direct call: CODE member
    ({"__imp__socket@12"}, set(), {"_socket@12", "__imp__socket@12"}),    # dllimport: the same member
    ({"__imp__socket@12"}, {"_socket@12"}, {"__imp__socket@12"}),         # tree defines _X: DATA member
    ({"public"}, set(), set()),                                           # an alias's target alone
    ({"__imp__GetTickCount@0"}, set(), {"_GetTickCount@0", "__imp__GetTickCount@0"}),
    ({"_htons@4"}, set(), set()),                                         # a stub retail does not import
    ({"_free_name"}, set(), set()),
    ({"_socket@12"}, {"_socket@12"}, set()),                              # the tree defines it: no request
    ({"_strlen"}, set(), set()),                                          # msvcr71 stays with msvcrt.lib
])
def test_import_supplies_every_symbol_of_the_generated_members(refs, defined, supplied):
    direct, plain = A.requests_from_names(refs, IMPORTS["imported"])
    assert A.import_supplies(direct, plain, IMPORTS["imported"], lambda name: name in defined) == supplied


def test_an_alias_to_an_import_the_real_link_never_requests_strands_its_callers(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    name = "_socket@12"
    saved["comdat"] = {name: [(0, "good", "retail")]}
    saved["touches"] = {"provider.obj": {name}, "caller.obj": {"caller", "public"}}
    saved["alternates"] = {"public": [(1, name)]}
    saved["excuses"] = IMPORTS
    facts["provider.obj"] = ([], [], [], [])
    facts["caller.obj"] = ([], ["caller"], ["public"], [])
    monkeypatch.setattr(A.link_check, "alternate_names",
                        lambda obj: {"public": name} if obj.name == "caller.obj" else {})
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "REAL-LINK LOSS public:" in capsys.readouterr().out


def test_a_direct_call_of_an_import_still_resolves_after_its_tree_copy_goes(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    name = "_socket@12"
    saved["comdat"] = {name: [(0, "good", "retail")]}
    saved["touches"] = {"provider.obj": {name}, "caller.obj": {"caller", name}}
    saved["excuses"] = IMPORTS
    facts["provider.obj"] = ([], [], [], [])
    facts["caller.obj"] = ([], ["caller"], [name], [])
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 0
    assert "REAL-LINK LOSS" not in capsys.readouterr().out


def test_an_include_reader_hit_counts_for_a_unit_the_index_never_read(batch, includes, monkeypatch, capsys):
    saved, facts, _, paths = batch
    updated_index_batch(saved, facts, paths, monkeypatch)
    includes["new_unit.obj"] = {"api"}                            # the directive reader's view of the unit
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "REAL-LINK LOSS api:" in capsys.readouterr().out


def test_an_alias_to_an_import_another_reference_requests_still_resolves(batch, monkeypatch, capsys):
    # Round 5: `public=_socket@12` alone requests nothing, but the caller's own `__imp__socket@12`
    # makes exit_link.py generate socket@12, whose CODE member also defines the `_socket@12` thunk.
    saved, facts, _, _ = batch
    unlinked(saved)
    name = "_socket@12"
    saved["comdat"] = {name: [(0, "good", "retail")]}
    saved["touches"] = {"provider.obj": {name}, "caller.obj": {"caller", "public", "__imp__socket@12"}}
    saved["alternates"] = {"public": [(1, name)]}
    saved["excuses"] = IMPORTS
    facts["provider.obj"] = ([], [], [], [])
    facts["caller.obj"] = ([], ["caller"], ["public", "__imp__socket@12"], [])
    monkeypatch.setattr(A.link_check, "alternate_names",
                        lambda obj: {"public": name} if obj.name == "caller.obj" else {})
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 0
    assert "REAL-LINK LOSS" not in capsys.readouterr().out


# Re-check of f2d31641f5: a definition is no import request.
def test_a_defined_imp_name_requests_no_import(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    name = "_socket@12"
    saved["comdat"] = {name: [(0, "good", "retail")]}
    saved["strong"] = {"caller": [1], "__imp__socket@12": [1]}        # caller DEFINES __imp__socket@12
    saved["touches"] = {"provider.obj": {name}, "caller.obj": {"caller", "public", "__imp__socket@12"}}
    saved["alternates"] = {"public": [(1, name)]}
    saved["excuses"] = IMPORTS
    facts["provider.obj"] = ([], [], [], [])
    facts["caller.obj"] = ([], ["caller", "__imp__socket@12"], ["public"], [])
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "REAL-LINK LOSS public:" in capsys.readouterr().out


def test_the_import_request_reader_runs_link_cycle_s_helpers_on_the_file(tmp_path):
    import link_cycle
    defines = link_cycle.write_coff(tmp_path / "defines.obj", [(".data", 0xC0300040, bytes(4), 0)],
                                    [("__imp__socket@12", 1, 0, link_cycle.EXTERNAL), ("public", 0, 0, link_cycle.EXTERNAL)])
    calls = link_cycle.write_coff(tmp_path / "calls.obj", [(".text", 0x60500020, b"\xc3", 0)],
                                  [("__imp__GetTickCount@0", 0, 0, link_cycle.EXTERNAL),
                                   ("_socket@12", 0, 0, link_cycle.EXTERNAL), ("_own", 1, 0, link_cycle.EXTERNAL)])
    read = A.import_request_reader({"defines.obj": defines, "calls.obj": calls, "gone.obj": tmp_path / "gone.obj"},
                                   IMPORTS["imported"])
    assert read("defines.obj") == (set(), set())
    assert read("calls.obj") == ({"__imp__GetTickCount@0"}, {"__imp__socket@12"})
    assert read("gone.obj") is None


def test_the_file_s_requests_win_over_the_index_s_names(batch, monkeypatch, capsys):
    # The index lists `__imp__socket@12` for caller.obj without saying it is defined there; the
    # caller's own file shows no request, so nothing supplies the `_socket@12` thunk.
    saved, facts, _, _ = batch
    unlinked(saved)
    name = "_socket@12"
    saved["comdat"] = {name: [(0, "good", "retail")]}
    saved["touches"] = {"provider.obj": {name}, "caller.obj": {"caller", "public", "__imp__socket@12"}}
    saved["alternates"] = {"public": [(1, name)]}
    saved["excuses"] = IMPORTS
    facts["provider.obj"] = ([], [], [], [])
    facts["caller.obj"] = ([], ["caller"], ["public", "__imp__socket@12"], [])
    monkeypatch.setattr(A, "import_request_reader", lambda paths, imported: lambda obj: (set(), set()))
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "REAL-LINK LOSS public:" in capsys.readouterr().out


def test_a_changed_object_s_earlier_requests_come_from_the_index():
    # Before: changed.obj called `_socket@12` directly (so its import was requested and `public`
    # resolved through the alias); its old file is gone. After: it no longer calls it.
    before = tables(["changed.obj", "caller.obj"], alternates={"public": [(1, "_socket@12")]},
                    touches={"changed.obj": {"_socket@12"}, "caller.obj": {"public"}}, excuses=IMPORTS)
    after = tables(["changed.obj", "caller.obj"], alternates={"public": [(1, "_socket@12")]},
                   touches={"changed.obj": set(), "caller.obj": {"public"}}, excuses=IMPORTS)
    order = rank("changed.obj", "caller.obj")
    found = A.real_link_losses(before, after, {"_socket@12"}, order, order, changed={"changed.obj"},
                               import_requests=lambda obj: (set(), set()))   # every kept file: no request now
    assert [(e[0], e[3]) for e in found] == [("public", "loss")]


def test_an_unindexed_unit_s_direct_call_requests_the_import_an_alias_reaches(batch, references, monkeypatch, capsys):
    saved, facts, _, paths = batch
    updated_index_batch(saved, facts, paths, monkeypatch)
    name = "_socket@12"
    saved["comdat"] = {name: [(0, "good", "retail")]}
    saved["touches"] = {"provider.obj": {name}, "caller.obj": {"caller", "public"}}
    saved["alternates"] = {"public": [(1, name)]}
    saved["excuses"] = IMPORTS
    facts["caller.obj"] = ([], ["caller"], ["public"], [])
    monkeypatch.setattr(A.link_check, "alternate_names",
                        lambda obj: {"public": name} if obj.name == "caller.obj" else {})
    references["new_unit.obj"] = unit(refs={name})            # calls socket directly: the import is requested
    assert A.audit("a" * 40, "b" * 40, []) == 0
    assert "REAL-LINK LOSS public" not in capsys.readouterr().out


# Re-check of 7eff814c7f: a COMMON record is a section-0 external, so link_cycle requests it.
def test_removing_a_common_imp_record_drops_the_import_an_alias_reached(batch, monkeypatch, capsys):
    saved, facts, _, _ = batch
    unlinked(saved)
    saved["comdat"] = {}
    saved["common"] = {"__imp__socket@12": [(0, 4)]}               # provider: COMMON __imp__socket@12 ...
    saved["strong"] = {"caller": [1]}
    saved["touches"] = {"provider.obj": {"__imp__socket@12"}, "caller.obj": {"caller", "public"}}
    saved["alternates"] = {"public": [(0, "_socket@12")]}          # ... and public=_socket@12
    saved["excuses"] = IMPORTS
    facts["provider.obj"] = ([], [], [], [])                       # the batch drops the COMMON, keeps the alias
    facts["caller.obj"] = ([], ["caller"], ["public"], [])
    monkeypatch.setattr(A.link_check, "alternate_names",
                        lambda obj: {"public": "_socket@12"} if obj.name == "provider.obj" else {})
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 1
    assert "REAL-LINK LOSS public:" in capsys.readouterr().out


def test_link_cycle_reads_a_common_record_as_a_request(tmp_path):
    import link_cycle
    obj = link_cycle.write_coff(tmp_path / "common.obj", [], [("__imp__socket@12", 0, 4, link_cycle.EXTERNAL)])
    assert A.import_request_reader({"common.obj": obj}, IMPORTS["imported"])("common.obj") == (
        {"__imp__socket@12"}, set())


def test_a_common_definition_keeps_the_thunk_of_a_requested_import():
    # make_import_libs marks an export DATA only for a symbol defined in a section; a COMMON
    # `_socket@12` does not stop the CODE member's thunk.
    assert A.import_supplies({"__imp__socket@12"}, set(), IMPORTS["imported"], lambda name: False) == {
        "__imp__socket@12", "_socket@12"}


def test_a_common_definition_does_not_stop_a_plain_import_request(batch, monkeypatch, capsys):
    # provider.obj (changed) loses its `__imp__socket@12`; caller.obj reaches it only through
    # public=__imp__socket@12. other.obj COMMON-defines `_socket@12` and calls it plainly: section 0,
    # so undefined_plain_imports still requests `__imp__socket@12`, and `public` still resolves.
    saved, facts, _, _ = batch
    unlinked(saved)
    saved["objects"].append("other.obj")
    saved["comdat"] = {}
    saved["strong"] = {"caller": [1], "__imp__socket@12": [0]}
    saved["common"] = {"_socket@12": [(2, 4)]}
    saved["touches"] = {"provider.obj": {"__imp__socket@12"}, "caller.obj": {"caller", "public"},
                        "other.obj": {"_socket@12"}}
    saved["alternates"] = {"public": [(1, "__imp__socket@12")]}
    saved["excuses"] = IMPORTS
    facts["provider.obj"] = ([], [], [], [])
    facts["caller.obj"] = ([], ["caller"], ["public"], [])
    monkeypatch.setattr(A.link_check, "alternate_names",
                        lambda obj: {"public": "__imp__socket@12"} if obj.name == "caller.obj" else {})
    monkeypatch.setattr(A.link_check, "link_rank", lambda rows: rank("provider.obj", "caller.obj", "other.obj"))
    monkeypatch.setattr(A, "import_request_reader", lambda paths, imported: lambda obj: None)   # index names
    monkeypatch.setattr(A, "REAL_LINK_LOSS_MODE", "refuse")
    assert A.audit("a" * 40, "b" * 40, []) == 0
    assert "REAL-LINK LOSS public" not in capsys.readouterr().out


# ------------------------------------------------- the verdict log (strict receipts design, step 0)
def _run_main(monkeypatch, tmp_path, audit):
    sources = tmp_path / "sources"
    sources.write_bytes(b"Code/a.cpp\0Code/b.cpp\0")
    logged = []
    monkeypatch.setattr(A, "audit", audit)
    monkeypatch.setattr(A, "log_verdict", logged.append)
    monkeypatch.setattr(sys, "argv", ["link_batch_audit.py", "--base", "b" * 40, "--tip", "t" * 40,
                                      "--sources-from", str(sources)])
    return A.main(), logged


@pytest.mark.parametrize("printed, code, verdict, reason", [
    (["link batch audit: no linking regression found in the checked scope"], 0, "clean", None),
    (["link batch audit: FAILED: 2 reference(s) to omitted objects; x"], 1, "failed", None),
    (["link batch audit: INCONCLUSIVE: 3 source object(s) lack current receipts; first: Code/a.cpp"], 2,
     "inconclusive", "missing-receipts"),
    (["link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/c.cpp"], 2,
     "inconclusive", "consumer-receipt"),
    (["link batch audit: INCONCLUSIVE: census index missing; fetch with link_check.py --fetch-index"], 2,
     "inconclusive", "no-index"),
    (["link batch audit: INCONCLUSIVE baseline: index at abc, outgoing base def; provisional",
      "link batch audit: INCONCLUSIVE: no provisional finding from the older index"], 2,
     "inconclusive", "non-exact-base"),
])
def test_each_run_logs_its_verdict_and_changes_no_output_or_exit(monkeypatch, tmp_path, capsys,
                                                                 printed, code, verdict, reason):
    def audit(base, tip, verified):
        assert verified == ["Code/a.cpp", "Code/b.cpp"]
        print("  some detail line")
        for line in printed:
            print(line)
        return code
    got, logged = _run_main(monkeypatch, tmp_path, audit)
    assert got == code
    assert capsys.readouterr().out == "  some detail line\n" + "".join(line + "\n" for line in printed)
    assert len(logged) == 1
    record = logged[0]
    assert (record["verdict"], record["reason"], record["exit"], record["sources"]) == (verdict, reason, code, 2)
    assert record["lines"] == printed and record["base"] == "b" * 40 and record["tip"] == "t" * 40
    assert record["exact_base"] is not any("baseline" in line for line in printed)


def test_a_crashing_audit_is_logged_and_still_crashes(monkeypatch, tmp_path):
    def audit(base, tip, verified):
        print("link batch audit: 1 current object(s), 0 retired")
        raise RuntimeError("boom")
    stdout = sys.stdout
    with pytest.raises(RuntimeError):
        _run_main(monkeypatch, tmp_path, audit)
    assert sys.stdout is stdout


def test_crash_record_names_the_crash(monkeypatch, tmp_path):
    logged = []
    monkeypatch.setattr(A, "log_verdict", logged.append)

    def audit(base, tip, verified):
        raise RuntimeError("boom")
    sources = tmp_path / "sources"
    sources.write_bytes(b"")
    monkeypatch.setattr(A, "audit", audit)
    monkeypatch.setattr(sys, "argv", ["link_batch_audit.py", "--base", "b", "--tip", "t", "--sources-from",
                                      str(sources)])
    with pytest.raises(RuntimeError):
        A.main()
    assert [record["verdict"] for record in logged] == ["crashed"]


def test_the_log_is_appended_in_the_git_common_dir_and_a_failing_write_is_silent(monkeypatch, tmp_path):
    import json
    subprocess.run(["git", "init", "-q", str(tmp_path / "clone")], check=True)
    monkeypatch.setattr(A.link_check, "ROOT", tmp_path / "clone")
    A.log_verdict({"verdict": "clean"})
    A.log_verdict({"verdict": "failed"})
    log = tmp_path / "clone/.git" / A.VERDICT_LOG
    assert [json.loads(line)["verdict"] for line in log.read_text().splitlines()] == ["clean", "failed"]
    (tmp_path / "not-a-repo").mkdir()
    monkeypatch.setattr(A.link_check, "ROOT", tmp_path / "not-a-repo")
    A.log_verdict({"verdict": "clean"})          # no git dir: nothing raised, nothing written


@pytest.mark.parametrize("locked", [True, False])
def test_concurrent_writers_never_interleave_a_line(tmp_path, locked):
    # Review of e30cdbb710: 16 concurrent writers on Windows corrupted 274 of 4,800 lines. Linux
    # writes a whole line atomically anyway, so each writer here splits os.write into 512-byte
    # pieces, as Windows may; without the lock (the negative control) lines then interleave.
    import json
    clone = tmp_path / "clone"
    subprocess.run(["git", "init", "-q", str(clone)], check=True)
    writer = (
        "import os, sys, time; sys.path.insert(0, sys.argv[1]); import link_batch_audit as A\n"
        "import portable_lock\n"
        "from pathlib import Path\n"
        "real = os.write\n"
        "def chunked(fd, data):\n"
        "    time.sleep(0.0002)\n"
        "    return real(fd, bytes(data[:512]))\n"
        "os.write = chunked\n"
        "if sys.argv[4] == 'unlocked':\n"
        "    portable_lock.lock = lambda handle, **k: None\n"
        "    portable_lock.unlock = lambda handle: None\n"
        "A.link_check.ROOT = Path(sys.argv[2])\n"
        "for n in range(40):\n"
        "    A.log_verdict({'writer': int(sys.argv[3]), 'n': n, 'pad': 'x' * 4000})\n")
    tools = str(Path(A.__file__).resolve().parent)
    procs = [subprocess.Popen([sys.executable, "-c", writer, tools, str(clone), str(w),
                               "locked" if locked else "unlocked"]) for w in range(16)]
    assert all(proc.wait() == 0 for proc in procs)
    lines = (clone / ".git" / A.VERDICT_LOG).read_bytes().split(b"\n")
    whole = []
    for line in lines[:-1]:
        try:
            whole.append(json.loads(line))
        except ValueError:
            pass
    expected = [(w, n) for w in range(16) for n in range(40)]
    if locked:
        assert lines[-1] == b"" and len(whole) == len(lines) - 1          # every line whole
        assert sorted((r["writer"], r["n"]) for r in whole) == expected
    else:
        assert len(whole) < len(expected)                                 # the control does interleave
