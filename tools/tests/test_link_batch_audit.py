"""Outgoing link regressions: identity, provider removal and class declarations."""
import sys
import copy
import shutil
import subprocess
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_batch_audit as A

REAL_DEFINITION_GUARD = A.removed_definition_guard


@pytest.fixture(autouse=True)
def no_real_git(monkeypatch):
    monkeypatch.setattr(A, "removed_definition_guard", lambda *args: 0)
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


@pytest.mark.parametrize("status,blocked", [(0, False), (1, True), (2, False), (124, False), (137, False), (3, True)])
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
    if status in (2, 124, 137):
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




def symbols(defined=(), refs=(), aliases=None, weak=(), includes=()):
    return set(defined), set(refs), list(weak), aliases or {}, set(includes)


def test_removed_private_drawable_inline_is_refused_without_census_credit():
    name = '?getID@Drawable@@QBE?AW4DrawableID@@XZ'
    before = {'DrawableHealthBarGate.cpp': symbols([name])}
    after = {'DrawableHealthBarGate.cpp': symbols(),
             **{f'caller{i}.cpp': symbols(refs=[name]) for i in range(11)}}
    assert len(A.definition_losses(before, after)) == 11
    after['real_owner.cpp'] = symbols([name])
    assert A.definition_losses(before, after) == []


def test_removed_import_alternatename_target_is_refused():
    target = '?ji_006291ae@@YAXXZ'
    alias = '?ji_006291ae@@YAPAXPAXHI@Z'
    before = {'imports_001.cpp': symbols([target])}
    after = {'imports_001.cpp': symbols(),
             'Rva00219B9EAccessor.cpp': symbols(refs=[alias], aliases={alias: target})}
    assert A.definition_losses(before, after) == [('Rva00219B9EAccessor.cpp', alias, target)]
    # A new provider or a real definition overriding the alias makes it safe.
    after['typed.cpp'] = symbols([target])
    assert A.definition_losses(before, after) == []
    after['typed.cpp'] = symbols([alias])
    assert A.definition_losses(before, after) == []


def test_transitive_cross_object_directive_and_weak_default():
    before = {'old': symbols(['target'])}
    after = {'consumer': symbols(weak=[('weak', 'alias')]),
             'directive': symbols(aliases={'alias': 'target'})}
    assert A.definition_losses(before, after) == [('consumer', 'weak', 'target')]


def test_unused_removal_and_alias_cycle_terminate():
    before = {'old': symbols(['unused'])}
    assert A.definition_losses(before, {'new': symbols()}) == []
    assert A.definition_losses(before, {'new': symbols(refs=['a'], aliases={'a': 'b', 'b': 'a'})}) == []


def test_include_and_local_import_binding():
    before = {'old': symbols(['target'])}
    after = {'caller': symbols(includes=['__imp_target'])}
    assert A.definition_losses(before, after) == [('caller', '__imp_target', 'target')]


def test_guard_refusal_precedes_missing_census(monkeypatch, tmp_path):
    monkeypatch.setattr(A, 'changed_sources', lambda *a: {'Code/provider.cpp'})
    monkeypatch.setattr(A, 'removed_definition_guard', lambda *a: 1)
    monkeypatch.setattr(A.link_check, 'INDEX', tmp_path / 'missing')
    assert A.audit('base', 'tip', []) == 1



@pytest.mark.parametrize('alternate', [False, True])
def test_real_coff_removed_definition(alternate, tmp_path):
    """Use actual COFF symbol and directive parsing, not mocked symbol facts."""
    import struct
    target = '?ji_006291ae@@YAXXZ' if alternate else '?getID@Drawable@@QBE?AW4DrawableID@@XZ'
    root = '?ji_006291ae@@YAPAXPAXHI@Z' if alternate else target

    def write(name, entries, directive=b''):
        strings = bytearray(b'\0' * 4)
        symbols = bytearray()
        for symbol, section in entries:
            offset = len(strings); strings.extend(symbol.encode() + b'\0')
            symbols.extend(struct.pack('<II', 0, offset) + struct.pack('<IhHBB', 0, section, 0x20, 2, 0))
        struct.pack_into('<I', strings, 0, len(strings))
        # .text plus .drectve; all external definitions in .text.
        payload = b'\xc3' + directive
        headers = (b'.text\0\0\0' + struct.pack('<IIIIIIHHI', 0, 0, 1, 100, 0, 0, 0, 0, 0x60000020)
                   + b'.drectve' + struct.pack('<IIIIIIHHI', 0, 0, len(directive), 101, 0, 0, 0, 0, 0x100A00))
        header = struct.pack('<HHIIIHH', 0x14c, 2, 0, 100 + len(payload), len(entries), 0, 0)
        path = tmp_path / name
        path.write_bytes(header + headers + payload + symbols + strings)
        return A.link_census.object_symbols(path)

    before = {'provider': write('base.obj', [(target, 1)])}
    after = {'provider': write('tip.obj', []),
             'caller': write('caller.obj', [(root, 0)],
                             (' /alternatename:' + root + '=' + target).encode() if alternate else b'')}
    assert A.definition_losses(before, after) == [('caller', root, target)]
    after['replacement'] = write('replacement.obj', [(target, 1)])
    assert A.definition_losses(before, after) == []




def test_guard_missing_evidence_warns(monkeypatch, tmp_path, capsys):
    def refuse(*a):
        raise ValueError('manifest unavailable')
    monkeypatch.setattr(A, 'changed_sources', lambda *a: {'Code/provider.cpp'})
    monkeypatch.setattr(A, 'removed_definition_guard', refuse)
    monkeypatch.setattr(A.link_check, 'INDEX', tmp_path / 'missing')
    assert A.audit('base', 'tip', []) == 2
    assert 'definition guard: UNCHECKED: manifest unavailable' in capsys.readouterr().out


@pytest.fixture
def manifest_repo(monkeypatch, tmp_path):
    import json
    repo = tmp_path
    (repo / 'Code').mkdir()
    for name in ('provider', 'caller'):
        (repo / 'Code' / (name + '.cpp')).write_text('// original\n')
    subprocess.run(['git', 'init', '-q', str(repo)], check=True)
    subprocess.run(['git', '-C', str(repo), 'config', 'user.name', 'test'], check=True)
    subprocess.run(['git', '-C', str(repo), 'config', 'user.email', 'test@example.com'], check=True)
    def commit():
        subprocess.run(['git', '-C', str(repo), 'add', 'Code'], check=True)
        subprocess.run(['git', '-C', str(repo), 'commit', '-qm', 'fixture'], check=True)
        return subprocess.check_output(['git', '-C', str(repo), 'rev-parse', 'HEAD'], text=True).strip()
    base = commit()
    monkeypatch.setattr(A.link_check, 'ROOT', repo)
    monkeypatch.setattr(A, 'git', lambda *args: subprocess.check_output(['git', '-C', str(repo), *args], text=True).strip())
    monkeypatch.setattr(A, 'library_definitions', lambda names: set())
    monkeypatch.setattr(A.build, 'obj_path', lambda path: repo / (path.stem + '.obj'))
    monkeypatch.setattr(A.link_census, 'object_symbols', lambda path, raw=None: A.unpack_facts(json.loads(path.read_text())))
    def object_(source, facts):
        (repo / (Path(source).stem + '.obj')).write_text(json.dumps(A.pack_facts(facts)))
    def manifest(facts):
        result = {'commit': base, 'objects': [dict(source=s, provider=Path(s).stem + '.obj',
                                                   facts=A.pack_facts(f)) for s, f in facts.items()]}
        monkeypatch.setattr(A, 'load_real_manifest', lambda: result)
        return result
    return repo, base, commit, object_, manifest


@pytest.mark.parametrize('alternate', [False, True])
def test_manifest_reproduces_both_removed_providers(manifest_repo, alternate, capsys):
    repo, base, commit, object_, manifest = manifest_repo
    target = '?ji_006291ae@@YAXXZ' if alternate else '?getID@Drawable@@QBE?AW4DrawableID@@XZ'
    root = '?ji_006291ae@@YAPAXPAXHI@Z' if alternate else target
    manifest({'Code/provider.cpp': symbols([target]),
              'Code/caller.cpp': symbols(refs=[root], aliases={root: target} if alternate else {})})
    (repo / 'Code/provider.cpp').write_text('// inline or import thunk removed\n')
    tip = commit(); object_('Code/provider.cpp', symbols())
    assert REAL_DEFINITION_GUARD(base, tip, ['Code/provider.cpp']) == 1
    assert 'LOST EXTERNAL ' + target in capsys.readouterr().out


def test_library_supplies_removed_definition(manifest_repo, monkeypatch):
    repo, base, commit, object_, manifest = manifest_repo
    manifest({'Code/provider.cpp': symbols(['_memset']), 'Code/caller.cpp': symbols(refs=['_memset'])})
    (repo / 'Code/provider.cpp').write_text('// use /MD provider\n')
    tip = commit(); object_('Code/provider.cpp', symbols())
    monkeypatch.setattr(A, 'library_definitions', lambda names: {'_memset'})
    assert REAL_DEFINITION_GUARD(base, tip, ['Code/provider.cpp']) == 0


@pytest.mark.parametrize('merge', [False, True])
def test_rename_and_merge_preserve_provider(manifest_repo, merge):
    repo, base, commit, object_, manifest = manifest_repo
    manifest({'Code/provider.cpp': symbols(['target']), 'Code/caller.cpp': symbols(refs=['target'])})
    (repo / 'Code/provider.cpp').unlink()
    dest = 'Code/caller.cpp' if merge else 'Code/renamed.cpp'
    (repo / dest).write_text('// moved definition\n')
    tip = commit(); object_(dest, symbols(['target'], refs=[]))
    assert A.changed_sources(base, tip) >= {'Code/provider.cpp', dest}
    assert REAL_DEFINITION_GUARD(base, tip, [dest]) == 0


def test_rebased_unbuilt_consumer_is_unchecked_not_stale_local_evidence(manifest_repo, capsys):
    repo, base, commit, object_, manifest = manifest_repo
    manifest({'Code/provider.cpp': symbols(['target']), 'Code/caller.cpp': symbols()})
    (repo / 'Code/caller.cpp').write_text('// new reference since manifest\n')
    (repo / 'Code/provider.cpp').write_text('// removed provider\n')
    tip = commit(); object_('Code/provider.cpp', symbols())
    object_('Code/caller.cpp', symbols())  # stale local object deliberately has no import
    assert REAL_DEFINITION_GUARD(base, tip, ['Code/provider.cpp']) == 0
    assert 'UNCHECKED tip object: Code/caller.cpp' in capsys.readouterr().out


def test_source_grep_finds_alternate_without_local_consumer_object(manifest_repo, capsys):
    repo, base, commit, object_, manifest = manifest_repo
    (repo / 'Code/caller.cpp').write_text('#pragma comment(linker, "/alternatename:alias=target")\n')
    measured = commit()
    record = manifest({'Code/provider.cpp': symbols(['target']), 'Code/caller.cpp': symbols()})
    record['commit'] = measured
    (repo / 'Code/provider.cpp').write_text('// removed\n')
    tip = commit(); object_('Code/provider.cpp', symbols())
    assert not (repo / 'caller.obj').exists()
    assert REAL_DEFINITION_GUARD(measured, tip, ['Code/provider.cpp']) == 1
    assert 'source directive Code/caller.cpp:' in capsys.readouterr().out


def test_docs_only_push_preserves_dirty_unrelated_file(manifest_repo, monkeypatch):
    import time
    repo, base, commit, object_, manifest = manifest_repo
    (repo / 'notes.md').write_text('documentation')
    subprocess.run(['git', '-C', str(repo), 'add', 'notes.md'], check=True)
    subprocess.run(['git', '-C', str(repo), 'commit', '-qm', 'docs'], check=True)
    tip = A.git('rev-parse', 'HEAD')
    (repo / 'Code/caller.cpp').write_text('// unrelated dirty work\n')
    monkeypatch.setattr(A, 'removed_definition_guard', lambda *a: pytest.fail('guard should not run'))
    started = time.monotonic()
    assert A.audit(base, tip, []) == 0
    assert time.monotonic() - started < 1
    assert (repo / 'Code/caller.cpp').read_text() == '// unrelated dirty work\n'


def test_missing_tip_object_warns_without_refusing(manifest_repo, capsys):
    repo, base, commit, object_, manifest = manifest_repo
    manifest({'Code/provider.cpp': symbols(['target']), 'Code/caller.cpp': symbols(refs=['target'])})
    (repo / 'Code/provider.cpp').write_text('// changed\n'); tip = commit()
    assert REAL_DEFINITION_GUARD(base, tip, ['Code/provider.cpp']) == 0
    assert 'UNCHECKED tip object: Code/provider.cpp' in capsys.readouterr().out



def test_exact_runtime_and_generated_import_providers(monkeypatch):
    import link_cycle
    original = A.library_definitions
    monkeypatch.setattr(link_cycle, 'runtime_libraries', lambda: [Path('runtime.lib')])
    monkeypatch.setattr(A.link_census, 'library_symbols', lambda path: {'_memset'})
    monkeypatch.setattr(A.link_census, 'retail_imports', lambda: {'Sleep': {'kernel32.dll'}})
    found = original({'_memset', '_Sleep@4', '__imp__Sleep@4', '?getID@Drawable@@QBE?AW4DrawableID@@XZ'})
    assert {'_memset', '_Sleep@4', '__imp__Sleep@4'} <= found
    assert '?getID@Drawable@@QBE?AW4DrawableID@@XZ' not in found


def test_absent_artifact_manifest_is_warning(monkeypatch, capsys):
    monkeypatch.setattr(A, 'changed_sources', lambda *a: {'Code/provider.cpp'})
    monkeypatch.setattr(A, 'load_real_manifest', lambda: {'commit': 'a' * 40, 'objects': [], 'warning': 'no image_objects.json'})
    assert REAL_DEFINITION_GUARD('base', 'tip', []) == 0
    assert 'UNCHECKED: no image_objects.json' in capsys.readouterr().out


def test_manifest_loader_verifies_hashes_without_extracting(monkeypatch, tmp_path):
    import io, json, hashlib, zipfile, struct
    name = 'target'
    symbol = name.encode().ljust(8, b'\0') + struct.pack('<IhHBB', 0, 1, 0x20, 2, 0)
    raw = struct.pack('<HHIIIHH', 0x14c, 1, 0, 61, 1, 0, 0)
    raw += b'.text\0\0\0' + struct.pack('<IIIIIIHHI', 0, 0, 1, 60, 0, 0, 0, 0, 0x60000020)
    raw += b'\xc3' + symbol + struct.pack('<I', 4)
    def archive(digest):
        stream = io.BytesIO()
        with zipfile.ZipFile(stream, 'w') as z:
            z.writestr('image/image_objects.json', json.dumps([{'path': 'image_objects-objects/a.obj',
                'sha256': digest, 'source': 'Code/provider.cpp', 'provider': 'provider.obj'}]))
            z.writestr('image/image_objects.json.receipt.json', json.dumps({'map_sha256': 'fixture'}))
            z.writestr('image/image_objects-objects/a.obj', raw)
        return stream.getvalue()
    monkeypatch.setattr(A, 'source_object_names', lambda c: {})
    parsed = A.parse_manifest_archive(archive(hashlib.sha256(raw).hexdigest()), 'commit')
    assert A.unpack_facts(parsed['objects'][0]['facts'])[0] == {'target'}
    with pytest.raises(ValueError, match='digest mismatch'):
        A.parse_manifest_archive(archive('bad'), 'commit')
    assert list(tmp_path.iterdir()) == []


def test_shared_cache_has_size_cap(monkeypatch, tmp_path):
    monkeypatch.setattr(A, 'CACHE_LIMIT', 120)
    for i in range(6):
        A.save_cache(tmp_path / f'{i}.json', {'data': 'x' * 60})
    assert sum(p.stat().st_size for p in tmp_path.iterdir()) <= 120


def test_manifest_cache_avoids_repeat_downloads(monkeypatch, tmp_path):
    monkeypatch.setattr(A, 'cache_root', lambda: tmp_path)
    monkeypatch.setattr(A, 'manifest_candidates', lambda: [dict(kind='real', commit='a' * 40, artifact=2)])
    calls = []
    def api(endpoint):
        calls.append(endpoint)
        return b'zip fixture'
    monkeypatch.setattr(A, 'gh_api', api)
    monkeypatch.setattr(A, 'parse_manifest_archive', lambda raw, c, kind: {'schema': A.CACHE_SCHEMA,
                        'commit': c, 'kind': kind, 'objects': [], 'warning': 'manifest absent'})
    first = A.load_real_manifest()
    assert len(calls) == 1
    assert A.load_real_manifest() == first
    assert len(calls) == 1


def test_diagnostic_stub_definitions_never_count_as_base_providers(monkeypatch, tmp_path):
    import io, json, hashlib, zipfile
    commit = 'a' * 40
    objects = []
    contents = {}
    for provider, symbols_ in [('provider.obj', {'real_target'}), ('diagnostic_stubs.obj', {'already_missing'})]:
        path = tmp_path / provider
        A.exit_link.diagnostic_stubs(symbols_, path)  # COFF fixture writer, no compiler
        raw = path.read_bytes()
        stored = 'image_objects-objects/' + provider
        objects.append(dict(provider=provider, source='Code/provider.cpp' if provider == 'provider.obj' else '',
                            path=stored.replace('/', '\\'), sha256=hashlib.sha256(raw).hexdigest()))
        contents['image/' + stored] = raw
    stream = io.BytesIO()
    with zipfile.ZipFile(stream, 'w') as z:
        z.writestr('image/image_objects.json', json.dumps(objects))
        z.writestr('image/image_objects.json.receipt.json', json.dumps({'map_sha256': 'map'}))
        z.writestr('image/image_receipt.json', json.dumps({'kind': 'diagnostic', 'commit': commit,
                    'map_sha256': 'map', 'stubbed': ['already_missing']}))
        z.writestr('stubbed.tsv', 'name\ttrap_symbol\nalready_missing\talready_missing\n')
        for name, raw in contents.items(): z.writestr(name, raw)
    monkeypatch.setattr(A, 'source_object_names', lambda c: {})
    manifest = A.parse_manifest_archive(stream.getvalue(), commit, 'diagnostic')
    assert manifest['kind'] == 'diagnostic'
    assert manifest['excluded_stub_objects'] == ['diagnostic_stubs.obj']
    before = {e['provider']: A.unpack_facts(e['facts']) for e in manifest['objects']}
    assert 'already_missing' not in set().union(*(f[0] for f in before.values()))
    assert A.definition_losses(before, {'caller': symbols(refs=['already_missing'])}) == []
    assert A.definition_losses(before, {'caller': symbols(refs=['real_target'])}) == [('caller', 'real_target', 'real_target')]


def test_missing_real_manifest_falls_back_to_diagnostic_and_caches(monkeypatch, tmp_path):
    monkeypatch.setattr(A, 'cache_root', lambda: tmp_path)
    candidates = [dict(kind='real', commit='a' * 40, artifact=1),
                  dict(kind='diagnostic', commit='b' * 40, artifact=2)]
    monkeypatch.setattr(A, 'manifest_candidates', lambda: candidates)
    calls = []
    monkeypatch.setattr(A, 'gh_api', lambda endpoint: calls.append(endpoint) or b'fixture')
    def parse(raw, commit, kind):
        return dict(schema=A.CACHE_SCHEMA, kind=kind, commit=commit,
                    objects=[{'provider': 'p'}] if kind == 'diagnostic' else [],
                    **({'warning': 'no manifest'} if kind == 'real' else {}))
    monkeypatch.setattr(A, 'parse_manifest_archive', parse)
    result = A.load_real_manifest()
    assert result['kind'] == 'diagnostic' and result['commit'] == 'b' * 40
    assert result['fallback_warnings'] == ['real-link ' + 'a' * 40 + ': no manifest']
    assert A.load_real_manifest() == result
    assert len(calls) == 2


def test_diagnostic_workflow_uses_artifact_source_commit_not_run_head(monkeypatch):
    import json
    def api(endpoint):
        if 'workflows/real-link.yml' in endpoint:
            return json.dumps({'workflow_runs': [{'id': 1, 'head_sha': 'a' * 40}]}).encode()
        if 'workflows/diagnostic-link.yml' in endpoint:
            return json.dumps({'workflow_runs': [{'id': 2, 'head_sha': 'c' * 40}]}).encode()
        def artifact(kind, commit, ident, created):
            return dict(id=ident, name=kind + '-link-' + commit, expired=False,
                        size_in_bytes=1, created_at=created)
        artifacts = ([artifact('real', 'a' * 40, 1, '2026-11-05T01:00:00Z'),
                      artifact('diagnostic', 'a' * 40, 3, '2026-11-05T01:00:00Z')]
                     if '/runs/1/' in endpoint else
                     [artifact('diagnostic', 'b' * 40, 2, '2026-11-05T02:00:00Z')])
        return json.dumps({'artifacts': artifacts}).encode()
    monkeypatch.setattr(A, 'gh_api', api)
    candidates = A.manifest_candidates()
    assert [(c['kind'], c['commit']) for c in candidates] == [
        ('real', 'a' * 40), ('diagnostic', 'b' * 40), ('diagnostic', 'a' * 40)]


def test_diagnostic_evidence_kind_and_commit_appear_in_refusal(manifest_repo, capsys):
    repo, base, commit, object_, manifest = manifest_repo
    record = manifest({'Code/provider.cpp': symbols(['target']), 'Code/caller.cpp': symbols(refs=['target'])})
    record['kind'] = 'diagnostic'
    (repo / 'Code/provider.cpp').write_text('// removed\n'); tip = commit(); object_('Code/provider.cpp', symbols())
    assert REAL_DEFINITION_GUARD(base, tip, ['Code/provider.cpp']) == 1
    output = capsys.readouterr().out
    assert 'LOST EXTERNAL target:' in output
    assert '[diagnostic-link ' + base + ']' in output



def test_unrelated_alias_conflicts_do_not_hide_a_proven_loss():
    before = {'provider': symbols(['target'])}
    after = {'caller': symbols(refs=['target']),
             'directives1': symbols(aliases={'unrelated': 'a'}),
             'directives2': symbols(aliases={'unrelated': 'b'})}
    unchecked = set()
    assert A.definition_losses(before, after, unchecked) == [('caller', 'target', 'target')]
    assert not unchecked
    after['ambiguous consumer'] = symbols(refs=['unrelated'])
    assert A.definition_losses(before, after, unchecked) == [('caller', 'target', 'target')]
    assert unchecked == {'conflicting weak/alternate targets: unrelated'}
