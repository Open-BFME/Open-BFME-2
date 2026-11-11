"""header_adopt_lane: source surgery, header generation, failure taxonomy and the closure check."""
import csv
import os
import sys
import time
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import header_adopt_lane as lane  # noqa: E402

UNIT = """// cl: /O2
typedef float Real;
// struct Coord3D { int fake; };
struct Coord3D
{
    Real x, y, z;
    void zero() { x = y = z = 0.0f; }
};
template <class T>
class StringBase { T *p; };
class AsciiString : public StringBase<char> { char *m_data; };
void use(Coord3D *c) { c->zero(); }
"""


def test_batch_byte_gate_shares_one_successful_process(monkeypatch):
    calls = []
    monkeypatch.setattr(lane, "BFME2", True)
    monkeypatch.setattr(lane.subprocess, "run", lambda command, **kwargs:
                        calls.append(command) or SimpleNamespace(returncode=0, stdout="Functions: OK 2/2", stderr=""))
    assert lane.gate_many(["a.cpp", "b.cpp", "a.cpp"]) == {"a.cpp": None, "b.cpp": None}
    assert calls == [[sys.executable, "tools/build.py", "a.cpp", "b.cpp"]]


def test_batch_byte_failure_is_isolated_without_trusting_diagnostic_names(monkeypatch):
    calls = []
    monkeypatch.setattr(lane, "BFME2", True)
    def run(command, **kwargs):
        files = command[2:]
        calls.append(files)
        failed = "bad.cpp" in files
        return SimpleNamespace(returncode=int(failed), stdout="Functions: OK" if not failed else "a.cpp mentioned here", stderr="")
    monkeypatch.setattr(lane.subprocess, "run", run)
    monkeypatch.setattr(lane, "gate_one", lambda source: "real failure" if source == "bad.cpp" else None)
    sources = ["a.cpp", "b.cpp", "c.cpp", "d.cpp", "e.cpp", "f.cpp", "g.cpp", "bad.cpp"]
    assert lane.gate_many(sources) == {s: "real failure" if s == "bad.cpp" else None for s in sources}
    assert calls == [sources, sources[:4], sources[4:]]


def test_batch_gate_rejects_exit_zero_without_explicit_success(monkeypatch):
    monkeypatch.setattr(lane, "BFME2", True)
    monkeypatch.setattr(lane.subprocess, "run", lambda *a, **kw: SimpleNamespace(returncode=0, stdout="", stderr=""))
    assert lane.gate_many(["a.cpp", "b.cpp"]) == {"a.cpp": "gate exited 0", "b.cpp": "gate exited 0"}


def test_batch_gate_bounds_windows_command_size(monkeypatch):
    monkeypatch.setattr(lane, "BFME2", True)
    calls = []
    monkeypatch.setattr(lane.subprocess, "run", lambda command, **kw:
                        calls.append(command) or SimpleNamespace(returncode=0, stdout="Functions: OK", stderr=""))
    sources = [f"Code/{'x' * 180}/{i}.cpp" for i in range(80)]
    assert lane.gate_many(sources) == dict.fromkeys(sources)
    assert len(calls) > 1
    assert all(sum(len(s) + 3 for s in command[2:]) <= 6000 for command in calls)


def test_wholly_failing_variant_has_bounded_bisection_overhead(monkeypatch):
    monkeypatch.setattr(lane, "BFME2", True)
    calls = []
    monkeypatch.setattr(lane.subprocess, "run", lambda command, **kw:
                        calls.append(command) or SimpleNamespace(returncode=1, stdout="FAIL", stderr=""))
    sources = [f"Code/Unit{i}.cpp" for i in range(25)]
    assert all(lane.gate_many(sources).values())
    assert len(calls) == len(sources) + 7


@pytest.mark.parametrize("raise_gate", [False, True])
def test_trial_batch_shares_ledger_and_restores_sources_even_on_exception(tmp_path, monkeypatch, raise_gate):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    ledger = tmp_path / "functions.csv"
    ledger.write_bytes(b"old,row\r\n")
    monkeypatch.setattr(lane, "LEDGER", ledger)
    monkeypatch.setattr(lane, "adoption_dependencies", lambda items: {})
    originals = {s: f"original {s}\r\n".encode() for s in ["a.cpp", "b.cpp", "blocked.cpp"]}
    for s, content in originals.items():
        (tmp_path / s).write_bytes(content)
    monkeypatch.setattr(lane, "prepare_unit", lambda s, *args:
                        (s, "preparation error", None, []) if s == "blocked.cpp" else
                        (s, None, f"candidate {s}", [("old", "new")] if s == "a.cpp" else []))
    def gate(sources):
        assert sources == ["a.cpp", "b.cpp"]
        assert ledger.read_text() == "new,row\n"
        assert (tmp_path / "a.cpp").read_text() == "candidate a.cpp"
        assert (tmp_path / "b.cpp").read_text() == "candidate b.cpp"
        assert (tmp_path / "blocked.cpp").read_bytes() == originals["blocked.cpp"]
        if raise_gate:
            raise RuntimeError("interrupted")
        return {"a.cpp": None, "b.cpp": "byte mismatch"}
    monkeypatch.setattr(lane, "gate_many", gate)
    if raise_gate:
        with pytest.raises(RuntimeError, match="interrupted"):
            lane.try_units(list(originals), ["C"], "C.h", "class")
    else:
        got = lane.try_units(list(originals), ["C"], "C.h", "class")
        assert [g[1] for g in got] == [None, "byte mismatch", "preparation error"]
    assert ledger.read_bytes() == b"old,row\r\n"
    assert {s: (tmp_path / s).read_bytes() for s in originals} == originals


def test_batch_acceptance_shares_setup_and_requires_individual_link_results(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "C.h").write_text("class C {};\n")
    sources = ["ok.cpp", "byte.cpp", "unknown.cpp", "loss.cpp", "private.cpp"]
    for s in sources:
        (tmp_path / s).write_text('#include "C.h"\n' + ("class C {};" if s == "private.cpp" else ""))
    calls = []
    monkeypatch.setattr(lane, "gate_many", lambda ss: calls.append(("build", list(ss))) or
                        {s: "byte mismatch" if s == "byte.cpp" else None for s in ss})
    monkeypatch.setattr(lane, "link_ok", lambda ss: calls.append(("link", list(ss))) or
                        {"ok.cpp": True, "loss.cpp": False, "private.cpp": True})
    retired = []
    monkeypatch.setattr(lane, "retire_rows", lambda done: retired.append(done) or 0)
    assert lane.accept("C", sources, "C.h") == 1
    assert calls == [("build", sources), ("link", [s for s in sources if s != "byte.cpp"])]
    assert retired == [{("C", "ok.cpp")}]


@pytest.mark.parametrize("existing", [False, True])
def test_variant_failure_restores_the_trial_header(tmp_path, monkeypatch, existing):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(lane, "registered", lambda: {})
    monkeypatch.setattr(lane, "view_methods", lambda *args: {})
    monkeypatch.setattr(lane, "generate", lambda *args: "candidate header\n")
    header = tmp_path / "C.h"
    original = b"original\r\n"
    if existing:
        header.write_bytes(original)
    def fail(*args, **kwargs):
        assert header.read_text() == "candidate header\n"
        raise RuntimeError("interrupted")
    monkeypatch.setattr(lane, "try_units", fail)
    with pytest.raises(RuntimeError, match="interrupted"):
        lane.tournament("C", {"fields": [], "key": "class"}, ["a.cpp", "b.cpp"], "C.h", ["data"], 1)
    assert header.read_bytes() == original if existing else not header.exists()

CONTRACT = {"class": "Coord3D", "key": "struct", "key_by": "bytes", "size": 12, "size_by": "zh", "bases": [],
            "fields": [{"offset": o, "size": 4, "kind": "f4", "type": "float", "name": n}
                       for o, n in ((0, "x"), (4, "y"), (8, "z"))]}


@pytest.fixture
def dependency_tree(tmp_path, monkeypatch):
    import name_dependents as nd
    from test_name_dependents import compiled
    old = "?getVel@Owner@@QAE?AUPoint@@XZ"
    new = "?getVel@Owner@@QAE?AVPoint@@XZ"
    provider, caller, data = "Code/provider.cpp", "Code/caller.cpp", "Code/data.cpp"
    texts = {provider: "struct Point { int x; }; // getVel owner\n",
             caller: "void caller() { getVel(); }\n", data: "void *table = getVel;\n"}
    objects = {s: compiled(tmp_path, s, [old], text) for s, text in texts.items()}
    rev = tmp_path / "reverse"
    rev.mkdir()
    ledger = rev / "functions.csv"
    rows = [dict(name=old, target_rva="0x1000", target_size="18", source=provider, status="matched", notes=""),
            dict(name="?caller@@YAXXZ", target_rva="0x2000", target_size="8", source=caller, status="matched", notes="")]
    def write_rows(path, rows, fields):
        with path.open("w", newline="", encoding="utf-8") as handle:
            writer = csv.DictWriter(handle, fields)
            writer.writeheader()
            writer.writerows(rows)
    write_rows(ledger, rows, list(rows[0]))
    write_rows(rev / "symbols.csv", [], ["name", "address"])
    data_rows = [dict(name="_table", address="0x00403000", address_kind="va", size="4", source=data, status="matched")]
    write_rows(rev / "data_rows.csv", data_rows, list(data_rows[0]))
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(lane, "LEDGER", ledger)
    monkeypatch.setattr(nd, "_row_objects", lambda rows: {s: [objects[s]] for s in {r["source"] for r in rows}})
    monkeypatch.setattr(nd, "_data_row_objects", lambda rows: {s: [objects[s]] for s in {r["source"] for r in rows}})
    return SimpleNamespace(root=tmp_path, ledger=ledger, rows=rows, old=old, new=new, provider=provider,
                           caller=caller, data=data, texts=texts, objects=objects, write_rows=write_rows)


def prepared_dependency_items(tree, sources):
    return [(s, None, "// adopted " + s, [(tree.old, tree.new)] if s == tree.provider else []) for s in sources]


def test_rename_discovery_shares_one_scan_and_includes_data_only_consumers(dependency_tree, monkeypatch):
    import name_dependents as nd
    t = dependency_tree
    calls = []
    scan = nd.dependents_by_name
    monkeypatch.setattr(nd, "dependents_by_name", lambda names, objects, root:
                        calls.append((set(names), set(objects))) or scan(names, objects, root))
    plan = lane.adoption_dependencies(prepared_dependency_items(t, [t.provider]))
    assert plan == {t.provider: {t.old: [t.caller, t.data]}}
    assert calls == [({t.old}, {t.provider, t.caller, t.data})]


def test_provider_loss_still_checks_callers_when_an_address_pin_remains(dependency_tree):
    t = dependency_tree
    t.write_rows(t.root / "reverse/symbols.csv", [dict(name=t.old, address="0x1000")], ["name", "address"])
    assert lane.adoption_dependencies(prepared_dependency_items(t, [t.provider])) == {
        t.provider: {t.old: [t.caller, t.data]}}


def test_no_name_change_skips_all_dependency_io(monkeypatch):
    monkeypatch.setattr(lane, "LEDGER", None)
    assert lane.adoption_dependencies([("a.cpp", None, "candidate", [])]) == {}


def test_stale_objects_use_the_hook_scanners_conservative_text_check(dependency_tree):
    t = dependency_tree
    t.objects[t.caller].unlink()
    assert t.caller in lane.adoption_dependencies(prepared_dependency_items(t, [t.provider]))[t.provider][t.old]


def test_external_dependencies_block_before_any_write_or_byte_gate(dependency_tree, monkeypatch):
    t = dependency_tree
    items = prepared_dependency_items(t, [t.provider])
    monkeypatch.setattr(lane, "prepare_unit", lambda *args: items[0])
    monkeypatch.setattr(lane, "gate_many", lambda *args: pytest.fail("blocked candidate reached byte gate"))
    monkeypatch.setattr(lane, "rewrite_ledger", lambda *args: pytest.fail("blocked candidate wrote ledger"))
    original = t.ledger.read_bytes()
    got = lane.try_units([t.provider], ["Point"], "Point.h", "class")
    assert "symbol dependencies" in got[0][1]
    assert t.caller in got[0][1] and t.data in got[0][1]
    assert (t.root / t.provider).read_text() == t.texts[t.provider]
    assert t.ledger.read_bytes() == original


def test_complete_coordinated_batch_passes_and_restores_its_trial(dependency_tree, monkeypatch):
    t = dependency_tree
    sources = [t.provider, t.caller, t.data]
    prepared = {i[0]: i for i in prepared_dependency_items(t, sources)}
    monkeypatch.setattr(lane, "prepare_unit", lambda s, *args: prepared[s])
    calls = []
    def gate(ss):
        calls.append(list(ss))
        assert t.new in t.ledger.read_text() and t.old not in t.ledger.read_text()
        assert all((t.root / s).read_text() == prepared[s][2] for s in ss)
        return dict.fromkeys(ss)
    monkeypatch.setattr(lane, "gate_many", gate)
    original = t.ledger.read_bytes()
    plan = {}
    got = lane.try_units(sources, ["Point"], "Point.h", "class", dependency_plan=plan)
    assert all(why is None for _, why, _, _ in got)
    assert plan == {t.provider: {t.old: [t.caller, t.data]}}
    assert calls == [sources]
    assert t.ledger.read_bytes() == original
    assert all((t.root / s).read_text() == t.texts[s] for s in sources)


def test_failed_caller_prevents_partial_provider_application(dependency_tree, monkeypatch):
    t = dependency_tree
    sources = [t.provider, t.caller, t.data]
    prepared = {i[0]: i for i in prepared_dependency_items(t, sources)}
    monkeypatch.setattr(lane, "prepare_unit", lambda s, *args: prepared[s])
    monkeypatch.setattr(lane, "gate_many", lambda ss: {s: "caller mismatch" if s == t.caller else None for s in ss})
    original = t.ledger.read_bytes()
    got = {s: why for s, why, _, _ in lane.try_units(sources, ["Point"], "Point.h", "class")}
    assert got[t.caller] == "caller mismatch"
    assert "symbol dependencies" in got[t.provider] and "symbol dependencies" in got[t.data]
    assert t.ledger.read_bytes() == original
    assert all((t.root / s).read_text() == t.texts[s] for s in sources)


def test_failed_rename_rechecks_survivors_against_the_restored_resolver(dependency_tree, monkeypatch):
    t = dependency_tree
    sources = [t.provider, t.caller]
    prepared = {i[0]: i for i in prepared_dependency_items(t, sources)}
    monkeypatch.setattr(lane, "prepare_unit", lambda s, *args: prepared[s])
    monkeypatch.setattr(lane, "adoption_dependencies", lambda items: {})
    calls = []
    def gate(ss):
        calls.append(list(ss))
        if len(calls) == 1:
            assert t.new in t.ledger.read_text()
            return {t.provider: "provider mismatch", t.caller: None}
        assert ss == [t.caller] and t.old in t.ledger.read_text()
        assert (t.root / t.provider).read_text() == t.texts[t.provider]
        return {t.caller: "new provider is unavailable"}
    monkeypatch.setattr(lane, "gate_many", gate)
    got = lane.try_units(sources, ["Point"], "Point.h", "class")
    assert [why for _, why, _, _ in got] == ["provider mismatch", "new provider is unavailable"]
    assert calls == [sources, [t.caller]]


def test_dependency_scan_failure_cannot_approve_ungated_survivors(dependency_tree, monkeypatch):
    t = dependency_tree
    prepared = {i[0]: i for i in prepared_dependency_items(t, [t.provider, t.caller])}
    monkeypatch.setattr(lane, "prepare_unit", lambda s, *args: prepared[s])
    def fail(items):
        raise OSError("unreadable object")
    monkeypatch.setattr(lane, "adoption_dependencies", fail)
    monkeypatch.setattr(lane, "gate_many", lambda *args: pytest.fail("discovery failure reached gate"))
    got = lane.try_units(list(prepared), ["Point"], "Point.h", "class")
    assert all("discovery unavailable" in why for _, why, _, _ in got)


def test_already_applied_rename_cannot_retire_debt_with_outside_callers(dependency_tree, monkeypatch):
    t = dependency_tree
    import name_dependents as nd
    baseline = t.ledger.read_bytes()
    monkeypatch.setattr(nd, "git_bytes", lambda *args: baseline)
    lane.rewrite_ledger([(t.old, t.new)])
    monkeypatch.setattr(lane, "gate_one", lambda *args: pytest.fail("blocked acceptance reached byte gate"))
    monkeypatch.setattr(lane, "retire_rows", lambda *args: pytest.fail("blocked acceptance retired debt"))
    assert lane.accept("Point", [t.provider]) == 1


def test_unchanged_ledger_acceptance_skips_csv_parsing_and_dependency_scans(dependency_tree, monkeypatch):
    t = dependency_tree
    import name_dependents as nd
    baseline = t.ledger.read_bytes()
    monkeypatch.setattr(nd, "git_bytes", lambda *args: baseline)
    monkeypatch.setattr(nd, "csv_dicts", lambda *args: pytest.fail("unchanged ledger was parsed"))
    assert lane.acceptance_dependencies([t.provider]) == {}


@pytest.mark.parametrize("failure", ["none", "byte", "link", "unknown"])
def test_acceptance_retires_only_complete_dependency_groups(dependency_tree, monkeypatch, failure):
    t = dependency_tree
    import name_dependents as nd
    baseline = t.ledger.read_bytes()
    monkeypatch.setattr(nd, "git_bytes", lambda *args: baseline)
    lane.rewrite_ledger([(t.old, t.new)])
    sources = [t.provider, t.caller, t.data]
    monkeypatch.setattr(lane, "gate_many", lambda ss:
                        {s: "byte mismatch" if s == t.caller and failure == "byte" else None for s in ss})
    monkeypatch.setattr(lane, "adoption_problems", lambda name, s, header, gate: [gate(s)] if gate(s) else [])
    monkeypatch.setattr(lane, "link_ok", lambda ss:
                        {s: (False if failure == "link" else None) if s == t.caller and failure in ("link", "unknown")
                         else True for s in ss})
    retired = []
    monkeypatch.setattr(lane, "retire_rows", lambda done: retired.append(done) or 0)
    assert lane.accept("Point", sources) == (failure != "none")
    assert retired == ([{("Point", s) for s in sources}] if failure == "none" else [set()])


def test_multiple_renames_of_one_provider_keep_all_dependencies(dependency_tree, monkeypatch):
    t = dependency_tree
    import name_dependents as nd
    other = "?other@Owner@@QAE?AUPoint@@XZ"
    rows = t.rows + [{**t.rows[0], "name": other, "target_rva": "0x1100"}]
    changed = [{**r, "name": t.new if r["name"] == t.old else other + "New" if r["name"] == other else r["name"]}
               for r in rows]
    monkeypatch.setattr(nd, "dependents_by_name", lambda *args: {t.old: {t.caller}, other: {t.data}})
    items = [(t.provider, None, None, [(t.old, t.new)]), (t.provider, None, None, [(other, other + "New")])]
    assert lane.adoption_dependencies(items, rows, changed) == {t.provider: {t.old: [t.caller], other: [t.data]}}


def test_acceptance_checks_each_name_at_a_folded_row_address(dependency_tree, monkeypatch):
    t = dependency_tree
    import name_dependents as nd
    rows = t.rows + [{**t.rows[0], "name": "?folded@@YAXXZ"}]
    t.write_rows(t.ledger, rows, list(rows[0]))
    baseline = t.ledger.read_bytes()
    monkeypatch.setattr(nd, "git_bytes", lambda *args: baseline)
    lane.rewrite_ledger([(t.old, t.new)])
    assert lane.acceptance_dependencies([t.provider]) == {t.provider: {t.old: [t.caller, t.data]}}


def test_dependency_blockers_propagate_transitively_but_preserve_unrelated_work():
    plan = {"provider.cpp": {"old": ["middle.cpp"]}, "middle.cpp": {"other": ["outside.cpp"]}}
    blocked = lane.dependency_blockers(plan, ["provider.cpp", "middle.cpp", "unrelated.cpp"])
    assert set(blocked) == {"provider.cpp", "middle.cpp"}
    assert all("outside.cpp" in why for why in blocked.values())


def test_bulk_link_refusal_cannot_publish_only_half_a_dependency_group(dependency_tree, monkeypatch):
    t = dependency_tree
    unrelated = "Code/unrelated.cpp"
    (t.root / unrelated).write_text("// unrelated original\n")
    sources = [t.provider, t.caller, unrelated]
    originals = {s: (t.root / s).read_bytes() for s in sources}
    best = dict(verdicts=dict.fromkeys(sources), texts=dict.fromkeys(sources, "// adopted\n"),
                renames={t.provider: [(t.old, t.new)]}, header="class Point {};\n",
                dependencies={t.provider: {t.old: [t.caller]}})
    prepared = dict(results={"data": best}, winner="data", header="Point.h", sources=sources,
                    contract={"class": "Point", "fields": []}, evidence={})
    monkeypatch.setattr(lane, "REGISTRY", t.root / "reverse/canonical_classes.csv")
    monkeypatch.setattr(lane, "QUEUE", t.root / "reverse/header_queue.tsv")
    monkeypatch.setattr(lane.class_contract, "CONTRACTS", t.root / "reverse/class_contracts")
    monkeypatch.setattr(lane, "claim_rewrites", lambda *args: [])
    monkeypatch.setattr(lane, "register", lambda *args: None)
    queued, renamed, committed = {}, [], []
    monkeypatch.setattr(lane, "write_queue", lambda name, header, failures: queued.update(failures))
    monkeypatch.setattr(lane, "rewrite_ledger", lambda names: renamed.extend(names))
    ctx = dict(link_check=lambda ss: {s: s != t.caller for s in ss}, trailers=[],
               commit=lambda paths, message: committed.append(paths) or (True, "commit", ""))
    status, _, _ = lane.bulk_land("Point", prepared, ctx)
    assert status == "adopted"
    assert unrelated in committed[0] and not {t.provider, t.caller} & set(committed[0])
    assert "symbol dependencies" in queued[t.provider]
    assert queued[t.caller].startswith("link regression")
    assert not renamed
    assert (t.root / t.provider).read_bytes() == originals[t.provider]
    assert (t.root / t.caller).read_bytes() == originals[t.caller]


@pytest.fixture
def ambiguous_include_tree(tmp_path, monkeypatch):
    import build
    source = "Code/Body.cpp"
    header = "Code/GameEngine/Include/GameLogic/Module/UpdateModule.h"
    shim = "reference/shims/other/GameLogic/Module/UpdateModule.h"
    for relative in (header, shim):
        path = tmp_path / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text("class UpdateModule {};\n")
    body = tmp_path / source
    body.write_text('#include "GameLogic/Module/UpdateModule.h"\n')
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(lane, "tracked_headers", lambda: [header, shim])
    monkeypatch.setattr(build, "compile_source", lambda *a, **kw: pytest.fail("include proof compiled a source"))
    command, env = ["cl.exe", "-ICode/GameEngine/Include"], {}
    monkeypatch.setattr(build, "compiler_command", lambda *a: (command, env))
    return SimpleNamespace(root=tmp_path, source=source, header=header, body=body,
                           command=command, env=env)


@pytest.mark.parametrize("flags", [
    ["-ICode/GameEngine/Include"], ["/ICode/GameEngine/Include"],
    ["-I", "Code/GameEngine/Include"], ["/I", "Code/GameEngine/Include"],
    ["-ICode/GameEngine/Include", "-Ireference/shims/other"],
])
def test_header_acceptance_resolves_duplicate_suffix_by_compiler_order(ambiguous_include_tree, flags):
    t = ambiguous_include_tree
    t.command[:] = ["cl.exe", *flags]
    assert lane.includes_header(t.source, t.header)


@pytest.mark.parametrize("case", ["earlier-shim", "adjacent-shim", "unsearched", "CL", "_CL_", "X"])
def test_duplicate_header_cannot_bypass_search_order(ambiguous_include_tree, case):
    t = ambiguous_include_tree
    if case == "earlier-shim":
        t.command.insert(1, "-Ireference/shims/other")
    elif case == "adjacent-shim":
        shadow = t.body.parent / "GameLogic/Module/UpdateModule.h"
        shadow.parent.mkdir(parents=True)
        shadow.write_text("class WrongUpdateModule {};\n")
    elif case == "unsearched":
        t.command[:] = ["cl.exe", "-Ireference/shims/other"]
    elif case in ("CL", "_CL_"):
        t.env[case] = "/Ireference/shims/other"
    elif case == "X":
        t.command[:] = ["cl.exe", "-X"]
        t.env["INCLUDE"] = str(t.root / "Code/GameEngine/Include")
    assert not lane.includes_header(t.source, t.header)


def test_duplicate_header_uses_include_environment_after_explicit_roots(ambiguous_include_tree):
    t = ambiguous_include_tree
    t.command[:] = ["cl.exe"]
    t.env["INCLUDE"] = str(t.root / "Code/GameEngine/Include")
    assert lane.includes_header(t.source, t.header)
    t.command.append("-Ireference/shims/other")
    assert not lane.includes_header(t.source, t.header)


def test_duplicate_header_angle_include_does_not_use_source_directory(ambiguous_include_tree):
    t = ambiguous_include_tree
    t.body.write_text("#include <GameLogic/Module/UpdateModule.h>\n")
    shadow = t.body.parent / "GameLogic/Module/UpdateModule.h"
    shadow.parent.mkdir(parents=True)
    shadow.write_text("class WrongUpdateModule {};\n")
    assert lane.includes_header(t.source, t.header)


@pytest.mark.parametrize("wrapper", ["/*\n{}*/\n", "#if 0\n{}#endif\n"])
def test_duplicate_header_still_requires_an_active_directive(ambiguous_include_tree, wrapper):
    t = ambiguous_include_tree
    t.body.write_text(wrapper.format(t.body.read_text()))
    assert not lane.includes_header(t.source, t.header)


def test_duplicate_header_refuses_unavailable_compiler_proof(ambiguous_include_tree, monkeypatch):
    import build
    t = ambiguous_include_tree
    def unavailable(*args):
        raise RuntimeError("compiler profile unavailable")
    monkeypatch.setattr(build, "compiler_command", unavailable)
    assert not lane.includes_header(t.source, t.header)


@pytest.fixture(params=[("Coord2D", "Coord2DCtorView"),
                        ("Coord3D", "Coord3DCtorView"),
                        ("Coord3D", "Coord3DDerivedView"),
                        ("Coord3D", "Coord3DInline")])
def constructor_companion(tmp_path, monkeypatch, request):
    name, companion_name = request.param
    directory = "Code/Libraries/Include/Lib"
    header = f"{directory}/{name}.h"
    companion = f"{directory}/{companion_name}.h"
    for path in (header, companion):
        full = tmp_path / path
        full.parent.mkdir(parents=True, exist_ok=True)
        full.write_text(f"class {name} {{}};\n")
    source = "Code/Body.cpp"
    body = tmp_path / source
    body.write_text(f'#include "Libraries/Include/Lib/{companion_name}.h"\n')
    queue = tmp_path / "header_queue.tsv"
    queue.write_text("class\tsource\theader\n" + f"{name}\t{source}\t{header}\n")
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(lane, "QUEUE", queue)
    monkeypatch.setattr(lane, "registered", lambda: {name: header})
    monkeypatch.setattr(lane, "tracked_headers", lambda: [header, companion])
    calls = []
    monkeypatch.setattr(lane, "gate_one", lambda source: calls.append(source))
    monkeypatch.setattr(lane, "link_ok", lambda sources: dict.fromkeys(sources, True))
    return name, source, header, companion, body, queue, calls


def test_constructor_companion_uses_the_same_default_and_explicit_verdict(constructor_companion):
    name, source, header, companion, body, queue, calls = constructor_companion
    # The CLI and repair_queue's trusted-base verdict must agree without --header.
    assert lane.verdict(name, source) == []
    assert lane.verdict(name, source, header=header) == []
    assert lane.accept(name, [source]) == 0
    assert queue.read_text() == "class\tsource\theader\n"
    assert calls == [source, source, source]


def test_constructor_companion_cannot_retire_a_byte_mismatch(constructor_companion, monkeypatch):
    name, source, header, companion, body, queue, calls = constructor_companion
    before = queue.read_bytes()
    monkeypatch.setattr(lane, "gate_one", lambda source: "byte mismatch")
    assert lane.verdict(name, source) == ["byte mismatch"]
    assert lane.accept(name, [source]) == 1
    assert queue.read_bytes() == before


@pytest.mark.parametrize("case", ["comment", "disabled", "private", "missing", "ambiguous",
                                  "unapproved", "other-class", "other-header"])
def test_constructor_companion_does_not_bypass_adoption_checks(constructor_companion, monkeypatch, case):
    name, source, header, companion, body, queue, calls = constructor_companion
    text = body.read_text()
    explicit = None
    if case == "comment":
        body.write_text("/*\n" + text + "*/\n")
    elif case == "disabled":
        body.write_text("#if 0\n" + text + "#endif\n")
    elif case == "private":
        body.write_text(f"class {name} {{ float x, y; }};\n" + text)
    elif case == "missing":
        (lane.ROOT / companion).unlink()
    elif case == "ambiguous":
        basename = Path(companion).name
        body.write_text(f'#include "{basename}"\n')
        monkeypatch.setattr(lane, "tracked_headers", lambda: [header, companion, f"Code/Other/{basename}"])
    elif case in ("unapproved", "other-class"):
        fake = (f"Code/Other/{Path(companion).name}" if case == "unapproved" else
                "Code/Libraries/Include/Lib/" + ("Coord3D" if name == "Coord2D" else "Coord2D") + "CtorView.h")
        (lane.ROOT / fake).parent.mkdir(parents=True, exist_ok=True)
        (lane.ROOT / fake).write_text(f"#define CANONICAL_{name.upper()}_H\nclass {name} {{}};\n")
        body.write_text(f'#include "{fake.removeprefix("Code/")}"\n')
    elif case == "other-header":
        explicit = f"Code/Other/{name}.h"
        (lane.ROOT / explicit).parent.mkdir(parents=True)
        (lane.ROOT / explicit).write_text(f"class {name} {{}};\n")
    problems = lane.verdict(name, source, header=explicit)
    assert problems, case
    assert any(("private body" if case == "private" else "does not #include") in p for p in problems)
    assert calls == [source]  # Even rejected includes still run the byte gate.


def test_consolidation_transfers_all_debt_and_only_acceptance_retires_it(tmp_path, monkeypatch):
    queue = tmp_path / "header_queue.tsv"
    cols = ["class", "source", "retail_rvas", "header", "failure", "retry_budget", "acceptance"]
    rows = [dict(zip(cols, ["Coord3D", source, rva, "Coord3D.h", "original failure", "3",
                           lane.acceptance_command("Coord3D", source)]))
            for source, rva in [("Code/A.cpp", "0x10"), ("Code/B.cpp", "0x20"),
                                ("Code/Other.cpp", "0x30")]]
    with queue.open("w", newline="") as handle:
        writer = csv.DictWriter(handle, cols, delimiter="\t", lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)
    assert lane.transfer_sources(["Code/A.cpp", "Code/B.cpp"], "Code/T.cpp", queue) == 2
    with queue.open(newline="") as handle:
        moved = list(csv.DictReader(handle, delimiter="\t"))
    assert len(moved) == len(rows)
    for before, after in zip(rows[:2], moved[:2]):
        assert after == dict(before, source="Code/T.cpp",
                             acceptance=lane.acceptance_command("Coord3D", "Code/T.cpp"))
    assert moved[2] == rows[2]
    monkeypatch.setattr(lane, "QUEUE", queue)
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(lane, "verdict", lambda *args: ["not adopted"])
    assert lane.accept("Coord3D", ["Code/T.cpp"]) == 1
    assert len(list(csv.DictReader(queue.open(), delimiter="\t"))) == 3
    monkeypatch.setattr(lane, "verdict", lambda *args: [])
    assert lane.accept("Coord3D", ["Code/T.cpp"]) == 0
    assert list(csv.DictReader(queue.open(), delimiter="\t")) == rows[2:]


def test_swap_strips_the_view_and_includes_the_header_where_it_stood():
    out = lane.swap(UNIT, ["Coord3D"], "../Lib/Coord3D.h")
    assert "Real x, y, z;" not in out
    assert out.index('#include "../Lib/Coord3D.h"') < out.index("void use")
    assert "// struct Coord3D { int fake; };" in out          # a commented-out head is not a view
    assert lane.swap("void f();\n", ["Coord3D"], "x.h") is None


@pytest.mark.parametrize("separator", ["\n", "\r\n", "\n\t\n", "\v\f", "\n/* end of view */\n"])
def test_swap_accepts_whitespace_before_the_class_semicolon(separator):
    prefix = "void before();\n"
    view = "class Pair { public: Pair() {} const char *ptr; int len; }" + separator + ";\n"
    suffix = "struct Holder { Pair value; };\nvoid after(Pair *);\n"
    out = lane.swap(prefix + view + suffix, ["Pair"], "Pair.h")
    assert out == prefix + '#include "Pair.h"\n' + suffix


@pytest.mark.parametrize("tail", ["\nPair value;\n", "\nvalue;\n", "\n*value;\n", "\n#define END ;\n"])
def test_swap_still_requires_a_standalone_complete_class_definition(tail):
    text = "class Pair { int len; }" + tail
    assert lane.swap(text, ["Pair"], "Pair.h") is None


def test_dependency_views_go_with_the_class():
    out = lane.swap(UNIT, ["AsciiString", "StringBase"], "ascii_string.h")
    assert "StringBase" not in out.split("void use")[0].split('#include "ascii_string.h"')[1]
    assert "template <class T>" not in out
    assert out.count('#include "ascii_string.h"') == 1


@pytest.mark.parametrize("indent", ["", "    ", "\t"])
def test_swap_preserves_nested_snapshot_and_only_replaces_global_view(indent):
    allocator = ("namespace EA { namespace Allocator {\n"
                 "class GeneralAllocator {\npublic:\n"
                 + indent + "struct Snapshot { unsigned m_magic; };\n"
                 "};\n}}\n")
    assert lane.body_span(allocator, "Snapshot") is None
    assert lane.swap(allocator, ["Snapshot"], "Snapshot.h") is None
    text = allocator + "    class Snapshot { int game; };\n"
    out = lane.swap(text, ["Snapshot"], "Snapshot.h")
    assert out == allocator + '#include "Snapshot.h"\n'


def test_nested_record_does_not_bypass_header_acceptance(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Snapshot.h").write_text("class Snapshot {};\n")
    (tmp_path / "unit.cpp").write_text("class Allocator {\nstruct Snapshot { int magic; };\n};\n")
    assert lane.verdict("Snapshot", "unit.cpp", "Snapshot.h", gate=lambda _: None) == [
        "does not #include Snapshot.h"]


def test_indented_global_private_view_still_fails_acceptance(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Snapshot.h").write_text("class Snapshot {};\n")
    (tmp_path / "unit.cpp").write_text('#include "Snapshot.h"\n    class Snapshot { int game; };\n')
    assert lane.verdict("Snapshot", "unit.cpp", "Snapshot.h", gate=lambda _: None) == [
        "still declares a private body"]


NESTED_ONLY = "class Allocator {\nstruct Snapshot { int magic; };\n};\n"


@pytest.fixture
def misqueued(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Snapshot.h").write_text("class Snapshot {};\n")
    (tmp_path / "unit.cpp").write_text(NESTED_ONLY)
    monkeypatch.setattr(lane, "link_ok", lambda sources: dict.fromkeys(sources, True))
    monkeypatch.setattr(lane, "queued_text", lambda name, source: NESTED_ONLY)
    monkeypatch.setattr(lane.class_layouts, "compile_layouts",
                        lambda source: {"Allocator::Snapshot": {"fwd": False}})
    return tmp_path


def test_misclassified_row_needs_no_include(misqueued):
    assert lane.verdict("Snapshot", "unit.cpp", "Snapshot.h", gate=lambda _: None) == []


@pytest.mark.parametrize("case", ["view-when-queued", "uses-class", "forward-ref", "no-history", "no-compile",
                                  "byte-mismatch", "private-view-now"])
def test_misclassified_row_still_needs_every_other_proof(misqueued, monkeypatch, case):
    gate = lambda _: None
    if case == "view-when-queued":                              # a view renamed since it was queued
        monkeypatch.setattr(lane, "queued_text", lambda name, source: "class Snapshot { int game; };\n")
    elif case in ("uses-class", "forward-ref"):
        monkeypatch.setattr(lane.class_layouts, "compile_layouts",
                            lambda source: {"Snapshot": {"fwd": case == "forward-ref"}})
    elif case == "no-history":
        monkeypatch.setattr(lane, "queued_text", lambda name, source: None)
    elif case == "no-compile":
        def broken(source):
            raise RuntimeError("compile failed")
        monkeypatch.setattr(lane.class_layouts, "compile_layouts", broken)
    elif case == "byte-mismatch":
        gate = lambda _: "byte mismatch"
    else:
        (misqueued / "unit.cpp").write_text(NESTED_ONLY + "class Snapshot { int game; };\n")
    assert lane.verdict("Snapshot", "unit.cpp", "Snapshot.h", gate=gate)


def test_queued_text_reads_the_commit_that_queued_the_row(tmp_path, monkeypatch):
    import subprocess

    def git(*args):
        subprocess.run(["git", *args], cwd=tmp_path, capture_output=True, check=True)

    def commit(source, rows):
        (tmp_path / "unit.cpp").write_text(source)
        (tmp_path / "reverse/header_queue.tsv").write_text("class\tsource\tnote\n" + rows)
        git("add", "-A")
        git("commit", "-q", "-m", "step")

    (tmp_path / "reverse").mkdir()
    git("init", "-q")
    git("config", "user.email", "t@example.com")
    git("config", "user.name", "t")
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(lane, "QUEUE", tmp_path / "reverse/header_queue.tsv")
    commit("// before\n", "")
    assert lane.queued_text("Snapshot", "unit.cpp") is None
    commit("// queued\n", "Snapshot\tunit.cpp\tC2259\n")
    commit("// edited\n", "Snapshot\tunit.cpp\tC2039\n")    # a refreshed note does not requeue
    commit("// retired\n", "")
    assert lane.queued_text("Snapshot", "unit.cpp") == "// queued\n"
    assert lane.queued_text("Snapshot", "other.cpp") is None


def test_generated_header_spells_the_contract():
    text = lane.generate(CONTRACT, "data", {})
    assert "struct Coord3D {" in text and "float x;" in text and "float z;" in text
    assert "Coord3D() {}" not in text
    assert "Coord3D() {}" in lane.generate(CONTRACT, "data+ctor", {})


def test_failure_taxonomy():
    assert lane.failure_class("x.cpp(3) : error C2039: 'zero' : is not a member") == "C2039 missing member"
    assert lane.failure_class("x.cpp(3) : error C2371: 'Bool' : redefinition") == "C2371"
    assert lane.failure_class("Functions: FAIL ?f@@YAXXZ") == "bytes/callee identity"


def test_closure_diff_flags_lost_rows(tmp_path):
    head = "name,retail_rva,closed_strict\n"
    before, same, lost = tmp_path / "a.csv", tmp_path / "b.csv", tmp_path / "c.csv"
    before.write_text(head + "?f@@YAXXZ,0x00401000,1\n?g@@YAXXZ,0x00401010,0\n")
    same.write_text(head + "?f@@YAXXZ,0x00401000,1\n?g@@YAXXZ,0x00401010,1\n")
    lost.write_text(head + "?f@@YAXXZ,0x00401000,0\n?g@@YAXXZ,0x00401010,1\n")
    assert lane.closure_diff(before, same) == 0      # negative control: closure only grew
    assert lane.closure_diff(before, lost) == 1      # positive control: a closed row was lost


def test_view_methods_merge_void_spelling_and_skip_declspec_special_members(tmp_path, monkeypatch):
    # Region3D views spell width() and width(void), and declare
    # `__declspec(nothrow) Region3D(const Region3D&);`: both once made every
    # generated methods header C2535.
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "a.cpp").write_text("struct Region3D {\n    float lo, hi;\n"
                                    "    float width() const { return hi - lo; }\n"
                                    "    bool in(const Coord3D *p) const;\n"
                                    "    __declspec(nothrow) Region3D(const Region3D&);\n};\n")
    (tmp_path / "b.cpp").write_text("struct Region3D {\n    float lo, hi;\n"
                                    "    float width(void) const { return hi - lo; }\n"
                                    "    bool in(const Coord3D *query) const { return query != 0; }\n};\n")
    assert len(lane.view_methods("Region3D", ["a.cpp", "b.cpp"])) == 1   # in() names a class not included
    methods = lane.view_methods("Region3D", ["a.cpp", "b.cpp"], {"Coord3D"})
    assert len(methods) == 2                    # one width, one in(): pointer parameter names do not count
    assert "{" in methods[lane.signature("bool in(const Coord3D *p) const;", "Region3D")]   # the body wins


def test_view_methods_keeps_hump_underscore_identifiers(tmp_path, monkeypatch):
    # WWLib method names are hump-underscore identifiers (Delete_This,
    # Add_Ref); the old all-uppercase-sounds-like-a-type filter dropped every
    # such method, so generated headers shipped vtables whose slot 0 was the
    # delete-dtor instead of the base class's Delete_This.
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "rc.cpp").write_text(
        "class RefCountClass {\n"
        "public:\n"
        "    void Release_Ref(void);\n"
        "    virtual void Delete_This(void);\n"
        "    virtual ~RefCountClass(void);\n"
        "private:\n"
        "    int NumRefs;\n};\n")
    methods = lane.view_methods("RefCountClass", ["rc.cpp"])
    assert "virtual void Delete_This(void);" in " ".join(methods.values())


def test_generated_header_orders_destructor_last():
    # A leading destructor would put the delete-dtor in the class vtable's
    # first slot; the donor order keeps member virtuals before it.
    methods = {"void Delete_This();": "virtual void Delete_This();",
               "~dtor": "virtual ~RefCountClass(void) {}"}
    contract = {"class": "RefCountClass", "key": "class", "key_by": "bytes", "size": 8, "size_by": "zh",
                "bases": [], "fields": []}
    text = lane.generate(contract, "data+methods", methods, None)
    assert text.index("Delete_This") < text.rindex("~RefCountClass")


# The three views 2a5da69f56 adopted, read at its parent. The generated header
# dropped their out-of-line destructor, so DestroyInstances.cpp emitted ??1 as a
# COMDAT ANY copy beside retail's out-of-line one: P137's LNK2005.
P137_VIEWS = {
    "DestroyInstances.cpp": "class Rva0022304A\n{\npublic:\n\t~Rva0022304A();\n};\n"
                            "class Rva0022CFE6\n{\npublic:\n\t~Rva0022CFE6();\n};\n",
    "FamilyDeletingDtors_Rva0022CFE6.cpp": "class Rva0022CFE6 { public: ~Rva0022CFE6(); };\n"
                                           "void famgenDelete(Rva0022CFE6 *p) { delete p; }\n",
    "Rva0022D9B7Delete.cpp": "class Rva0022CFE6\n{\npublic:\n\t~Rva0022CFE6();\n};\n",
}
P137_CONTRACT = {"class": "Rva0022CFE6", "key": "class", "key_by": "bytes", "size": 8, "size_by": "majority",
                 "bases": [], "vslots": {}, "queue": [],
                 "fields": [{"kind": "S:AsciiString", "name": "m_head", "offset": 0, "size": 4,
                             "type": "AsciiString"}]}


def special(name, views, index=None, **kwargs):
    return lane.special_declarations(name, sorted(views), read=views.__getitem__, index=index or {}, **kwargs)


def test_rva0022cfe6_views_keep_their_out_of_line_destructor(monkeypatch):
    monkeypatch.setattr(lane, "registered", lambda: {})
    carried, problems = special("Rva0022CFE6", P137_VIEWS)
    assert problems == []
    assert carried == [{"role": "dtor", "access": "public", "sig": "~", "text": "~Rva0022CFE6();"}]
    methods = {"void clear()": "void clear() {}"}
    for variant in ("data", "data+ctor", "data+methods", "data+includes", "data+ctor+copy"):
        text = lane.generate(P137_CONTRACT, variant, methods, None, None, carried)
        body = text[text.index("class Rva0022CFE6"):text.index("};")]
        assert body.count("~Rva0022CFE6();") == 1
        assert body.rstrip().endswith("~Rva0022CFE6();")       # the destructor stays last


def test_special_members_keep_spelling_access_and_skip_what_another_part_declares(monkeypatch):
    monkeypatch.setattr(lane, "registered", lambda: {})
    view = ("class Pod {\npublic:\n    explicit Pod(Real r);\n    Pod();\n    Pod(const Pod &other);\n"
            "    Pod(const Coord3D &where);\n    Pod &operator = (const Pod &);\n    void setMode(int m = MODE_ON);\n"
            "    ~Pod() {}\nprivate:\n    Pod(int a, int b);\n    float m_r;\n};\n")
    other = ("class Pod {\npublic:\n    Pod(void);\n    Pod(Pod const &);\n    Pod& operator=(const Pod &that);\n"
             "    ~Pod() {}\n    float m_r;\n};\n")
    carried, problems = special("Pod", {"a.cpp": view, "b.cpp": other})
    # Pod(const Coord3D &) names a type the header lacks; left out, a call to it could fall
    # to another constructor, so the class is held
    assert problems == ["special Pod(const Coord3D &where): names a type or default argument the header "
                        "does not declare, and Pod(float) could take its calls"]
    assert sorted((c["role"], c["access"], c["text"]) for c in carried) == [
        ("assign", "public", "Pod &operator = (const Pod &);"), ("copy", "public", "Pod(const Pod &other);"),
        ("ctor", "private", "Pod(int a, int b);"), ("ctor", "public", "explicit Pod(float r);"),
        ("default", "public", "Pod();"), ("dtor", "public", "~Pod() {}")]
    contract = {"class": "Pod", "key": "class", "key_by": "bytes", "size": 4, "size_by": "zh", "bases": [],
                "fields": [{"kind": "f4", "type": "float", "name": "m_r"}]}
    methods = {"Pod&operator=(const Pod&)": "Pod& operator=(const Pod &that);"}
    text = lane.generate(contract, "data+ctor+copy+methods", methods, None, None, carried)
    body = text[text.index("class Pod"):text.index("};")]
    assert "\n    Pod() {}" not in body and "Pod(const Pod &that);" not in body   # the views' own spellings win
    assert body.count("operator") == 1
    assert body.index("~Pod() {}") < body.index("private:") < body.index("Pod(int a, int b);")
    assert "explicit Pod(float r);" in body.split("private:")[0]


def test_inline_special_members_the_views_agree_on_are_carried_in_every_variant(monkeypatch):
    # The implicit destructor would not call release(): beside the views' inline one
    # (COMDAT ANY both) the linker may keep either body.
    monkeypatch.setattr(lane, "registered", lambda: {})
    view = "class C {\npublic:\n    ~C() {\n        release();\n    }\n    void release();\n    int x;\n};\n"
    carried, problems = special("C", {"a.cpp": view, "b.cpp": view})
    assert problems == [] and [c["text"] for c in carried] == ["~C() {\n        release();\n    }"]
    contract = {"class": "C", "key": "class", "key_by": "bytes", "size": 4, "size_by": "zh", "bases": [],
                "fields": [{"kind": "i4", "type": "int", "name": "x"}]}
    for variant in ("data", "data+ctor", "data+methods", "data+includes"):
        assert "release();" in lane.generate(contract, variant, {}, None, None, carried)
    other = "class C {\npublic:\n    ~C() { x = 0; }\n    int x;\n};\n"
    carried, problems = special("C", {"a.cpp": view, "b.cpp": other})
    assert problems == ["special ~C(): inline bodies differ (a.cpp, b.cpp)"] and carried == []


def test_special_member_keys_keep_qualifiers_and_drop_names():
    # C(C&) and C(const C&) are two constructors (two mangled names); a parameter's
    # name, even inside a function-pointer declarator, is no part of the key.
    view = "class C { public: C(C&); C(const C&); C& operator=(C&); C& operator=(const C&); int x; };\n"
    carried, problems = special("C", {"a.cpp": view})
    assert problems == [] and len(carried) == 4
    carried, problems = special("C", {"a.cpp": "class C { public: C(void (*f)(int x)); int x; };\n",
                                      "b.cpp": "class C { public: C(void (*g)(int y)); int x; };\n"})
    assert problems == [] and len(carried) == 1
    assert lane.param_key("void (C::*pm)(int x, const char *s) const") == "void(C::*)(int,const char*)const"


@pytest.mark.parametrize("a,b", [
    ("C(int *p) : m(p) {}", "C(int *q) : m(0) {}"),      # Rva005F4096: two inline bodies
    ("C(int *p);", "C(int *q) : m(0) {}"),                # out of line against inline
    ("C(int *p);", "private: C(int *p); public:"),        # other access
    ("C &operator=(int v);", "C &operator=(int v) { m = 0; return *this; }"),
])
def test_a_disputed_member_without_an_implicit_counterpart_is_left_out_not_held(a, b):
    # Dropping such a member is safe when no other overload could take its calls: a unit
    # that calls it no longer compiles and is queued.
    carried, problems = special("C", {"a.cpp": "class C { public: %s ~C(); int *m; };\n" % a,
                                      "b.cpp": "class C { public: %s ~C(); int *m; };\n" % b})
    assert problems == [] and [c["text"] for c in carried] == ["~C();"]


def test_a_disputed_member_another_overload_could_absorb_holds_the_class():
    # C t(1) would fall to C(long) silently if C(int) were left out.
    carried, problems = special("C", {"a.cpp": "class C { public: C(long); C(int); int m; };\n",
                                      "b.cpp": "class C { public: C(long); C(int) {} int m; };\n"})
    assert problems == ["special C(int): the views disagree on it, and C(long) could take its calls"]
    # c = 1 would fall to the copy assignment through the converting constructor
    carried, problems = special("C", {"a.cpp": "class C { public: C(int); C &operator=(int); int m; };\n",
                                      "b.cpp": "class C { public: C(int); C &operator=(int) { return *this; } "
                                               "int m; };\n"})
    assert problems == ["special C &operator=(int): the views disagree on it, and C(int) could take its calls"]
    # only a carried overload takes calls: ICoord2D's converting constructor and assignment
    # from a type the header lacks are both left out; the default and copy members take no
    # one-argument call of their own (GroupOrder's holder constructor beside them)
    carried, problems = special("C", {"a.cpp": "class C { public: C(); C(const C &); C(const Wire &w); "
                                               "C &operator=(const Wire &w); int m; };\n"})
    assert problems == [] and sorted(c["role"] for c in carried) == ["copy", "default"]


def test_copy_assignment_by_value_is_a_copy_assignment():
    views = {"a.cpp": "class C { public: C &operator=(C other); int m; };\n", "b.cpp": "class C { public: int m; };\n"}
    carried, problems = special("C", views)
    assert problems == ["special C &operator=(C other): declared in a.cpp, omitted by b.cpp and no matched row "
                        "defines it"]
    carried, problems = special("C", views, {"??4C@@": ["??4C@@QAEAAV0@V0@@Z"]})
    assert problems == [] and [c["role"] for c in carried] == ["assign"]


def test_defaulted_parameters_make_default_and_copy_constructors(monkeypatch):
    monkeypatch.setattr(lane, "registered", lambda: {})
    view = "class C { public: C(int n = 0); C(const C &o, int flags = 0); int x; };\n"
    carried, problems = special("C", {"a.cpp": view}, {"??0C@@": []})
    assert problems == [] and sorted(c["role"] for c in carried) == ["copy", "default"]
    contract = {"class": "C", "key": "class", "key_by": "bytes", "size": 4, "size_by": "zh", "bases": [],
                "fields": [{"kind": "i4", "type": "int", "name": "x"}]}
    body = lane.generate(contract, "data+ctor+copy", {}, None, None, carried)
    assert "C() {}" not in body and "C(const C &that);" not in body     # no ambiguous second default


def test_a_carried_declaration_keeps_its_string_literals():
    carried, problems = special("C", {"a.cpp": 'class C { public: C(const char *s = "a  b"); int x; };\n'})
    assert problems == [] and carried[0]["text"] == 'C(const char *s = "a  b");'
    # comment markers and braces inside a literal are text, not comments or members
    view = 'class C {\npublic:\n    ~C() { log("a/*  b  */c}"); } // gone\n    void log(const char *);\n};\n'
    carried, problems = special("C", {"a.cpp": view, "b.cpp": view})
    assert problems == [] and [c["text"] for c in carried] == ['~C() { log("a/*  b  */c}"); }']


def test_ledger_proof_reads_nested_scope_back_references():
    index = {"??0ModuleTemplate@FXParticleSystem@@": ["??0ModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z"],
             "??4ModuleTemplate@FXParticleSystem@@": [
                 "??4ModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z"]}
    for role in ("copy", "assign"):
        assert lane.ledger_defines("FXParticleSystem::ModuleTemplate", role, index=index)
        assert not lane.ledger_defines("ModuleTemplate", role, index={"??0ModuleTemplate@@": ["??0ModuleTemplate@@QAE@ABV1@@Z"]})
    assert lane.ledger_defines("C", "copy", index={"??0C@@": ["??0C@@QAE@ABU0@@Z"]})


@pytest.mark.parametrize("views,index,slotted,why", [
    ({"a.cpp": "class C { public: ~C(); int x; };\n", "b.cpp": "class C { public: ~C() {} int x; };\n"},
     {}, (), "special ~C(): out of line in a.cpp, inline in b.cpp"),
    ({"a.cpp": "class C { public: ~C(); int x; };\n", "b.cpp": "class C { public: virtual ~C(); int x; };\n"},
     {}, (), "special ~C(): virtual in b.cpp only, not in a.cpp"),
    ({"a.cpp": "class C { public: C(const C &); int x; };\n", "b.cpp": "class C { C(C const &); int x; };\n"},
     {}, (), "special C(const C &): access disagrees (private, public)"),
    ({"a.cpp": "class C { public: ~C(); int x; };\n", "b.cpp": "class C { public: int x; };\n"},
     {}, (), "special ~C(): declared in a.cpp, omitted by b.cpp and no matched row defines it"),
    ({"a.cpp": "class C { public: ~C() { Holder::release(m); } int m; };\n"},
     {}, (), "special ~C(): names a type or default argument the header does not declare"),
])
def test_views_that_disagree_on_a_special_member_hold_the_class(views, index, slotted, why):
    carried, problems = special("C", views, index, slotted=slotted)
    assert problems == [why] and carried == []


def test_an_omitted_special_member_is_carried_when_the_ledger_defines_it():
    views = {"a.cpp": "class C { public: ~C(); C(); int x; };\n", "b.cpp": "class C { public: int x; };\n"}
    index = {"??1C@@": ["??1C@@QAE@XZ"], "??0C@@": ["??0C@@QAE@XZ"]}
    carried, problems = special("C", views, index)
    assert problems == [] and sorted(c["text"] for c in carried) == ["C();", "~C();"]
    # a copy constructor row proves no default constructor
    carried, problems = special("C", views, {"??1C@@": ["??1C@@QAE@XZ"], "??0C@@": ["??0C@@QAE@ABV0@@Z"]})
    assert problems == ["special C(): declared in a.cpp, omitted by b.cpp and no matched row defines it"]
    # a destructor the slot declarations emit (virtual through a base) is theirs
    carried, problems = special("C", {"a.cpp": "class C : public B { public: ~C(); };\n",
                                      "b.cpp": "class C : public B { public: virtual ~C(); };\n"}, {}, slotted={"~"})
    assert problems == [] and carried == []


def test_run_refuses_views_that_disagree_on_a_special_member(tmp_path, monkeypatch):
    import json
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(lane.class_contract, "ROOT", tmp_path)
    monkeypatch.setattr(lane.class_contract, "CONTRACTS", tmp_path / "contracts")
    monkeypatch.setattr(lane.class_contract, "census", lambda name: ["a.cpp", "b.cpp"])
    monkeypatch.setattr(lane, "registered", lambda: {})
    monkeypatch.setattr(lane, "_matched_index", lambda: {})
    (tmp_path / "a.cpp").write_text("class C { public: ~C(); int x; };\n", encoding="utf-8")
    (tmp_path / "b.cpp").write_text("class C { public: int x; };\n", encoding="utf-8")
    path = lane.class_contract.contract_path("C")
    path.parent.mkdir()
    path.write_text(json.dumps({"class": "C", "key": "class", "key_by": "bytes", "size": 4, "size_by": "zh",
                                "bases": [], "fields": [], "vslots": {}, "queue": []}), encoding="utf-8")
    args = SimpleNamespace(name="C", header="C.h", generate=True, sample=None, seed=1, jobs=1, variants="data",
                           apply=False)
    monkeypatch.setattr(lane, "tournament", lambda *a, **k: pytest.fail("generated despite a disagreement"))
    assert lane.run(args) == 2
    assert "special-undeclarable" in lane.DECIDABLE         # repair_queue serves the held class


def preview(source, before, after, clean=True):
    return (f"{source}: {'LINKS' if clean else 'does not link'}  "
            f"LINKED {before:,} -> {after:,} bytes (census 2026-10-27 at bf3dd31211; "
            f"file's own bytes {max(before, after):,})\n")


@pytest.mark.parametrize("output,code,expected", [
    (preview("Code/FX.cpp", 5649, 5649), 0, True),
    (preview("Code/FX.cpp", 5649, 0, False), 1, False),
    (preview("Code/FX.cpp", 0, 42), 0, True),
    (preview("Code/FX.cpp", 0, 0, False), 1, True),
    ("Code/FX.cpp(3): error C2259: cannot instantiate abstract class\n", 1, None),
    ("Code/FX.cpp: UNKNOWN (missing object)\n", 1, None),
    (preview("Code/Other.cpp", 5649, 5649), 0, None),
    (preview("Code/FX.cpp", 5649, 5649) * 2, 0, None),
    (preview("Code/FX.cpp", 5649, 5649), 2, None),
])
def test_link_guard_requires_explicit_per_unit_coverage(output, code, expected, tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "tools").mkdir()
    (tmp_path / "tools/link_check.py").touch()

    def run(command, **kwargs):
        assert command == [sys.executable, "tools/link_check.py", "./Code/FX.cpp"]
        assert kwargs["cwd"] == tmp_path
        return SimpleNamespace(stdout=output, stderr="", returncode=code)

    monkeypatch.setattr(lane.subprocess, "run", run)
    assert lane.link_ok(["./Code/FX.cpp"]) == {"./Code/FX.cpp": expected}


def test_link_guard_judges_the_rest_without_an_out_of_census_unit(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "tools").mkdir()
    (tmp_path / "tools/link_check.py").touch()
    calls = []

    def run(command, **kwargs):
        calls.append(command[2:])
        if "Code/New.cpp" in command:
            return SimpleNamespace(stdout="", returncode=1, stderr=(
                "link_check: not in census 5a13f2cd61, so not previewable "
                "(the next census measures it): Code/New.cpp\n"))
        return SimpleNamespace(stdout=preview("Code/FX.cpp", 5649, 5649) + preview("Code/Lost.cpp", 90, 0, False),
                               stderr="", returncode=1)

    monkeypatch.setattr(lane.subprocess, "run", run)
    assert lane.link_ok(["Code/FX.cpp", "Code/New.cpp", "Code/Lost.cpp"]) == {
        "Code/FX.cpp": True, "Code/New.cpp": None, "Code/Lost.cpp": False}
    assert calls == [["Code/FX.cpp", "Code/New.cpp", "Code/Lost.cpp"], ["Code/FX.cpp", "Code/Lost.cpp"]]
    calls.clear()
    assert lane.link_ok(["Code/New.cpp"]) == {"Code/New.cpp": None}
    assert calls == [["Code/New.cpp"]]


@pytest.mark.parametrize("output,code,passes", [
    (preview("Code/FX.cpp", 5649, 0, False), 1, False),
    ("Code/FX.cpp: UNKNOWN (missing object)\n", 1, False),
    (preview("Code/FX.cpp", 5649, 5649), 0, True),
    (preview("Code/FX.cpp", 0, 0, False), 1, True),
])
def test_header_acceptance_keeps_debt_unless_linked_bytes_are_preserved(output, code, passes, tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Code").mkdir()
    (tmp_path / "Code/FX.cpp").write_text('#include "../Snapshot.h"\n')
    (tmp_path / "Snapshot.h").write_text("class Snapshot {};\n")
    (tmp_path / "tools").mkdir()
    (tmp_path / "tools/link_check.py").touch()
    queue = tmp_path / "header_queue.tsv"
    original = "class\tsource\nSnapshot\tCode/FX.cpp\n"
    queue.write_text(original)
    monkeypatch.setattr(lane, "QUEUE", queue)
    monkeypatch.setattr(lane.subprocess, "run", lambda *args, **kwargs: SimpleNamespace(
        stdout=output, stderr="", returncode=code))

    assert lane.accept("Snapshot", ["Code/FX.cpp"], "Snapshot.h", gate=lambda source: None) == (not passes)
    assert queue.read_text() == ("class\tsource\n" if passes else original)


def test_link_guard_has_no_verdict_without_checker(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    assert lane.link_ok(["Code/FX.cpp"]) == {"Code/FX.cpp": None}


def test_bad_byte_gate_does_not_run_link_preview(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "FX.cpp").write_text('#include "Snapshot.h"\n')
    (tmp_path / "Snapshot.h").touch()

    def unexpected(sources):
        raise AssertionError("link preview ran after byte failure")

    monkeypatch.setattr(lane, "link_ok", unexpected)
    assert lane.verdict("Snapshot", "FX.cpp", "Snapshot.h", gate=lambda source: "bytes differ") == ["bytes differ"]


# ---- merge blockers: the classes whose header unblocks the most merge donors rank first

CTOR_VIEW = """class Module { public: virtual ~Module(); };
class UpdateModule : public Module
{
public:
    UpdateModule();
    int m_phase;
};
"""
XFER_VIEW = """class UpdateModule
{
public:
    virtual int getModuleNameKey() const;   // slot 0 of its own
    int m_phase;
};
"""
FAKE_VIEW = """struct UpdateModule
{
    void *m_vtable;
    int m_phase;
};
"""
SAME_VIEW = """class Helper { int a; };
"""


def test_view_signatures_read_head_bases_and_vtable_shape():
    sigs = lane.view_signatures(CTOR_VIEW + "// class Ghost : public X { };\n")
    assert sigs["UpdateModule"] == ("class", "", "public Module", False, False, "")
    assert lane.view_signatures(XFER_VIEW)["UpdateModule"][5] == "getModuleNameKey"
    assert sigs["Module"][4] is True and "Ghost" not in sigs
    assert lane.view_signatures(FAKE_VIEW)["UpdateModule"][3] is True
    assert lane.base_names("public BehaviorModule, public virtual UpdateModuleInterface, Pair<int, int>") == [
        "BehaviorModule", "UpdateModuleInterface", "Pair"]


def test_disagreement_names_the_first_blocking_kind():
    ctor, xfer, fake = (lane.view_signatures(t)["UpdateModule"] for t in (CTOR_VIEW, XFER_VIEW, FAKE_VIEW))
    assert lane.disagreement([ctor, xfer], False) == "base"
    assert lane.disagreement([xfer, fake], False) == "fake-vtable"
    assert lane.disagreement([xfer, ("class", "", "", False, False, "")], False) == "vfptr"
    assert lane.disagreement([xfer, ("class", "", "", False, True, "~UpdateModule")], False) == "vslot"
    assert lane.disagreement([("class", "", "public M", False, True, "a"), ("class", "", "public M", False, True, "b")],
                             False) is None                            # an override introduces no slot
    assert lane.disagreement([xfer, ("struct", "", "", False, True, "getModuleNameKey")], False) == "key/declspec"
    assert lane.disagreement([xfer, xfer], False) is None              # tu_views reconciles these
    assert lane.disagreement([xfer, xfer], True) == "canonical-copy"   # a registered class: the lane's work


def _queue(files):
    tus = {"Code/A.cpp": {"Code/A.cpp": [1], "Code/A_xfer.cpp": [1, 2]},
           "Code/B.cpp": {"Code/B.cpp": [1], "Code/B2.cpp": [1], "Code/B3.cpp": [1]}}
    return ([{"tu": t} for t in sorted(tus)], lambda tu: tus[tu], lambda f: files[f])


def test_compute_merge_blockers_counts_donors_rows_tus_and_bases():
    files = {"Code/A.cpp": CTOR_VIEW + SAME_VIEW, "Code/A_xfer.cpp": XFER_VIEW + SAME_VIEW,
             "Code/B.cpp": CTOR_VIEW + "class Coord3D { float x; };\n",
             "Code/B2.cpp": FAKE_VIEW + "class Coord3D { float x; };\n", "Code/B3.cpp": "int x;\n"}
    queue, donors_of, read = _queue(files)
    got = lane.compute_merge_blockers(queue, donors_of, read, canon={"Coord3D": "Coord3D.h"})
    assert sorted(got) == ["Coord3D", "UpdateModule"]                  # Helper agrees; Module is in one file per TU
    um = got["UpdateModule"]
    assert (um["donors"], um["rows"], um["tus"]) == (4, 5, ["Code/A.cpp", "Code/B.cpp"])
    assert um["kinds"] == {"base": 2} and um["bases"] == ["Module"]
    assert um["virtual"] is True and got["Coord3D"]["virtual"] is False    # XFER_VIEW declares a virtual
    assert got["Coord3D"]["kinds"] == {"canonical-copy": 1}


def test_merge_rank_lifts_prerequisites_and_drops_invented_bases():
    blockers = {"UpdateModule": {"donors": 50, "bases": ["BehaviorModule", "InventedBase"]},
                "BehaviorModule": {"donors": 5, "bases": ["Module"]},
                "Module": {"donors": 1, "bases": []},
                "Object": {"donors": 70, "bases": ["Thing"]},
                "Coord3D": {"donors": 2, "bases": []},
                "Lonely": {"donors": 3, "bases": []}}
    order = [("value types", ["Coord3D"]), ("object", ["Object"])]
    ranked = lane.merge_rank(blockers, {}, order)
    assert ranked == [("Coord3D", 70, 2), ("Object", 70, 70), ("Module", 50, 1),
                      ("BehaviorModule", 50, 5), ("UpdateModule", 50, 50), ("Lonely", 3, 3)]
    assert lane.merge_rank(blockers, {}, order) == ranked              # deterministic


@pytest.fixture
def merge_cache(tmp_path, monkeypatch):
    """The lane's merge cache in tmp_path, a fake tree state, and a counting compute."""
    directory = tmp_path / "cache" / "merge_blockers"
    monkeypatch.setattr(lane, "merge_cache_dir", lambda: directory)
    state = {"inputs": ("headA", ""), "ancestor": True, "calls": 0}
    monkeypatch.setattr(lane, "merge_inputs", lambda: state["inputs"])

    def git(*args, strip=True):
        if args[:2] == ("merge-base", "--is-ancestor"):
            return "" if state["ancestor"] else None
        return None
    monkeypatch.setattr(lane, "_git", git)

    def compute():
        state["calls"] += 1
        return {"classes": {"X": {"donors": state["calls"]}}, "destinations": {}}
    monkeypatch.setattr(lane, "compute_merge_payload", compute)
    return directory, state


def test_merge_cache_is_keyed_by_head_and_dirty_fingerprint_and_refreshable(merge_cache):
    _, state = merge_cache
    assert lane.merge_blockers() == {"X": {"donors": 1}}
    assert lane.merge_blockers() == {"X": {"donors": 1}} and state["calls"] == 1
    assert lane.merge_blockers(refresh=True) == {"X": {"donors": 2}}
    state["inputs"] = ("headA", "f00d")                                # same HEAD, Code/ edited: a miss
    assert lane.merge_blockers() == {"X": {"donors": 3}}


def test_merge_cache_reuses_an_ancestor_only_with_the_same_fingerprint(merge_cache):
    _, state = merge_cache
    lane.merge_blockers()                                              # clean headA
    state["inputs"] = ("headB", "beef")                                # headA is an ancestor, but dirty
    assert lane.merge_blockers() == {"X": {"donors": 2}} and state["calls"] == 2
    state["inputs"] = ("headC", "")                                    # clean reuses clean headA
    assert lane.merge_blockers() == {"X": {"donors": 1}} and state["calls"] == 2
    state["inputs"] = ("headD", "beef")                                # dirty reuses the same dirt only
    assert lane.merge_blockers() == {"X": {"donors": 2}} and state["calls"] == 2
    state["ancestor"] = False
    state["inputs"] = ("headE", "")
    assert lane.merge_blockers() == {"X": {"donors": 3}}


def test_merge_cache_ignores_an_entry_of_another_payload_version(merge_cache, monkeypatch):
    _, state = merge_cache
    lane.merge_blockers()
    monkeypatch.setattr(lane, "MERGE_PAYLOAD_VERSION", lane.MERGE_PAYLOAD_VERSION + 1)
    state["inputs"] = ("headB", "")                                    # neither exact nor ancestor reuse
    assert lane.cached_merge_payload(("headA", "")) is None and lane.cached_merge_payload(state["inputs"]) is None
    assert lane.merge_blockers() == {"X": {"donors": 2}}


def test_porcelain_z_keeps_the_first_path_whole_and_both_rename_paths():
    status = " M Code/x.cpp\0R  Code/new.cpp\0Code/old.cpp\0?? reverse/n.csv\0"
    assert lane.porcelain_paths(status) == [(" M", "Code/x.cpp"), ("R ", "Code/new.cpp"), ("R ", "Code/old.cpp"),
                                            ("??", "reverse/n.csv")]


def test_merge_inputs_fingerprint_follows_the_first_dirty_file(tmp_path, monkeypatch):
    (tmp_path / "Code").mkdir()
    edited = tmp_path / "Code/x.cpp"
    edited.write_text("int a;\n")
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    answers = {("rev-parse", "HEAD"): "head", ("config", "-f", ".gitmodules", "--get-regexp", r"\.path$"): ""}

    def git(*args, strip=True):
        if args[0] == "status":
            assert strip is False and "-z" in args
            return " M Code/x.cpp\0"
        return answers.get(args)
    monkeypatch.setattr(lane, "_git", git)
    before = lane.merge_inputs()
    edited.write_text("int b;\n")
    after = lane.merge_inputs()
    assert before[0] == after[0] == "head" and before[1] and before[1] != after[1]


def _apply_run(tmp_path, monkeypatch, claim_result, released, skip_held=False, generate=False):
    """run --apply of a fixed header over two census units whose tournament passes both."""
    import json
    import claims
    import class_contract
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(lane, "SCRATCH", tmp_path / "build/header_lane")
    monkeypatch.setattr(lane, "QUEUE", tmp_path / "header_queue.tsv")
    monkeypatch.setattr(class_contract, "CONTRACTS", tmp_path / "contracts")
    units = ["Code/A.cpp", "Code/Elsewhere/NoRows.cpp"]
    for unit in units:
        (tmp_path / unit).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / unit).write_text("struct Coord3D { float x, y, z; };\n")
    monkeypatch.setattr(class_contract, "census", lambda name: list(units))
    path = class_contract.contract_path("Coord3D")
    path.parent.mkdir()
    path.write_text(json.dumps({**CONTRACT, "queue": []}), encoding="utf-8")
    monkeypatch.setattr(lane, "tournament", lambda *a, **k: {("data" if generate else "registered"): {
        "verdicts": dict.fromkeys(units), "seconds": 0.0, "header": "", "renames": {},
        "texts": {u: '#include "Coord3D.h"\n' for u in units}}})
    registered = []
    monkeypatch.setattr(lane, "register", lambda *a: registered.append(a))
    monkeypatch.setattr(lane, "write_queue", lambda *a: None)
    asked = []

    def claim(keys, **kwargs):
        asked.append((list(keys), kwargs.get("atomic_only")))
        return claim_result(keys)
    monkeypatch.setattr(claims, "claim", claim)
    monkeypatch.setattr(claims, "release", lambda keys, **k: released.extend(keys) or list(keys))
    monkeypatch.setattr(claims, "_blocking_records", lambda root=None: [
        {claims.key_of("file:Code/Elsewhere/NoRows.cpp"): {"owner": "seat-7"}}])
    args = type("A", (), {"name": "Coord3D", "header": "Coord3D.h", "generate": generate, "sample": None, "seed": 1,
                          "jobs": 1, "variants": "data", "apply": True, "skip_held": skip_held})()
    queued = {}
    monkeypatch.setattr(lane, "write_queue", lambda name, header, failed: queued.update(failed))
    code = lane.run(args)
    _apply_run.queued = queued
    return code, units, asked, registered


def test_apply_refuses_when_a_census_unit_is_held_by_another_seat(tmp_path, monkeypatch, capsys):
    import claims
    held = claims.key_of("file:Code/Elsewhere/NoRows.cpp")
    released = []
    code, units, asked, registered = _apply_run(
        tmp_path, monkeypatch, lambda keys: claims.ClaimResult([], [held]), released)
    assert code == 3 and not registered
    assert asked == [(["file:Code/A.cpp", "file:Code/Elsewhere/NoRows.cpp"], True)]   # all or nothing
    assert all((tmp_path / u).read_text().startswith("struct Coord3D") for u in units)  # nothing rewritten
    out = capsys.readouterr().out
    assert "refusing to apply" in out and "Code/Elsewhere/NoRows.cpp (seat-7)" in out
    assert not (tmp_path / "build/header_lane/Coord3D.claims").exists()


def test_skip_held_queues_the_held_unit_and_applies_the_rest(tmp_path, monkeypatch, capsys):
    import claims
    held = claims.key_of("file:Code/Elsewhere/NoRows.cpp")

    def claim(keys):
        if "file:Code/Elsewhere/NoRows.cpp" in keys:
            return claims.ClaimResult([], [held])
        return claims.ClaimResult([claims.key_of(k) for k in keys], [])
    released = []
    code, units, asked, registered = _apply_run(tmp_path, monkeypatch, claim, released, skip_held=True)
    assert code == 0 and registered
    assert asked[-1][0] == ["file:Code/A.cpp"]                                   # reduced set claimed
    assert (tmp_path / units[0]).read_text().startswith("#include")
    assert (tmp_path / units[1]).read_text().startswith("struct Coord3D")        # held unit untouched
    assert _apply_run.queued == {"Code/Elsewhere/NoRows.cpp": "held by seat-7 during run; retry when released"}


def test_skip_held_still_refuses_when_the_header_is_held(tmp_path, monkeypatch, capsys):
    import claims
    held = claims.key_of("file:Coord3D.h")

    def claim(keys):
        return claims.ClaimResult([], [held])
    monkeypatch.setattr(lane, "registered", lambda: {})
    released = []
    import class_contract
    monkeypatch.setattr(class_contract, "decide", lambda *a, **k: {"queue": []})
    code, units, asked, registered = _apply_run(tmp_path, monkeypatch, claim, released, skip_held=True, generate=True)
    assert code == 3 and not registered
    assert all((tmp_path / u).read_text().startswith("struct Coord3D") for u in units)


def test_apply_claims_the_units_it_rewrites_and_release_gives_them_back(tmp_path, monkeypatch, capsys):
    import claims
    released = []
    code, units, asked, registered = _apply_run(
        tmp_path, monkeypatch, lambda keys: claims.ClaimResult([claims.key_of(k) for k in keys], []), released)
    assert code == 0 and registered
    assert all((tmp_path / u).read_text().startswith("#include") for u in units)
    assert "header_adopt_lane.py release --class Coord3D" in capsys.readouterr().out
    assert lane.main(["release", "--class", "Coord3D"]) == 0
    assert released == ["file:Code/A.cpp", "file:Code/Elsewhere/NoRows.cpp"]
    assert not (tmp_path / "build/header_lane/Coord3D.claims").exists()


def test_header_destination_takes_one_official_path_and_never_guesses(tmp_path):
    bfme1, zh = (tmp_path / tree for _, tree in lane.REFERENCE_HEADER_TREES)
    for base, rel, text in ((bfme1, "GameEngine/Include/GameLogic/Module/UpgradeModule.h", "class UpgradeModule { };\n"),
                            (zh, "GameEngine/Include/GameLogic/Module/UpgradeModule.h", "class UpgradeModule { };\n"),
                            (zh, "GameEngine/Include/Common/Team.h", "class Team { };\nclass TeamA { };\n"),
                            (zh, "GameEngine/Include/Common/Team2.h", "class TeamA { };\n"),
                            (zh, "GameEngine/Include/Common/Fwd.h", "class Absent;\n")):
        (base / rel).parent.mkdir(parents=True, exist_ok=True)
        (base / rel).write_text(text)
    index = lane.reference_header_index(root=tmp_path)
    none = lambda p: False                                             # noqa: E731
    got = lane.header_destination("UpgradeModule", index, none)
    assert got["header"] == "Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h"
    assert got["evidence"].startswith("bfme1: ")                       # BFME 1 before ZH
    assert lane.header_destination("Team", index, none)["header"] == "Code/GameEngine/Include/Common/Team.h"
    assert lane.header_destination("TeamA", index, none)["header"] is None    # two headers: ambiguous
    assert lane.header_destination("Absent", index, none)["header"] is None   # a declaration is no definition
    occupied = lane.header_destination("Team", index, lambda p: True)
    assert occupied["header"] is None and "overwrite" in occupied["why"]


def test_header_destination_prefers_the_header_named_for_the_class(tmp_path):
    bfme1 = tmp_path / lane.REFERENCE_HEADER_TREES[0][1]
    for rel, text in (("GameEngine/Source/GameLogic/Object/object.h", "class Object : public Thing { int a; };\n"),
                      ("GameEngine/Source/GameLogic/Object/ObjectStatusBits.h", "class Object { char pad[4]; };\n"),
                      ("A/Twice.h", "class Pair { };\n"), ("B/Twice.h", "class Pair { };\n"),
                      ("C/pair.h", "class Pair2 { };\n"), ("D/pair2.h", "class Pair2 { };\n"),
                      ("E/pair2.h", "class Pair2 { };\n")):
        (bfme1 / rel).parent.mkdir(parents=True, exist_ok=True)
        (bfme1 / rel).write_text(text)
    index = lane.reference_header_index(root=tmp_path)
    got = lane.header_destination("Object", index, lambda p: False)
    assert got["header"] == "Code/GameEngine/Source/GameLogic/Object/object.h"
    assert "named for the class" in got["evidence"] and "ObjectStatusBits.h" in got["evidence"]
    assert lane.header_destination("Pair", index, lambda p: False)["header"] is None    # no header named Pair
    assert lane.header_destination("Pair2", index, lambda p: False)["header"] is None   # two named pair2.h


def test_picker_never_computes_and_starts_one_refresh(merge_cache, monkeypatch):
    directory, state = merge_cache
    monkeypatch.setattr(lane, "compute_merge_payload", lambda: pytest.fail("the picker computed the ranking"))
    monkeypatch.setattr(lane, "refresh_allowed", lambda: True)
    spawned = []
    monkeypatch.setattr(lane, "_spawn_detached", spawned.append)
    payload, note = lane.merge_payload_nonblocking()
    assert payload is None and "DEPENDENCY_ORDER only" in note and "refresh started" in note
    assert len(spawned) == 1 and "refresh-merges" in spawned[0] and (directory / "refresh.lock").exists()
    payload, note = lane.merge_payload_nonblocking()                   # the lock holds: no duplicate
    assert payload is None and "already running" in note and len(spawned) == 1
    old = time.time() - lane.MERGE_LOCK_SECONDS - 60                   # a dead refresh's lock is taken over
    os.utime(directory / "refresh.lock", (old, old))
    lane.merge_payload_nonblocking()
    assert len(spawned) == 2
    lane.store_merge_payload(state["inputs"], {"classes": {"X": {"donors": 9}}})
    assert lane.merge_payload_nonblocking() == ({"classes": {"X": {"donors": 9}}}, "")


def test_no_background_refresh_under_pytest_or_ci(tmp_path, monkeypatch):
    assert not lane.refresh_allowed()                                  # PYTEST_CURRENT_TEST is set here
    monkeypatch.delenv("PYTEST_CURRENT_TEST", raising=False)
    monkeypatch.setenv("CI", "true")
    assert not lane.refresh_allowed()
    assert "no background refresh" in lane.start_refresh(tmp_path, spawn=lambda c: pytest.fail("spawned"))
    assert not (tmp_path / "refresh.lock").exists()


def test_header_classes_follow_local_includes(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Inc" / "Mod").mkdir(parents=True)
    (tmp_path / "Inc" / "Base.h").write_text("class Base { int b; };\n")
    (tmp_path / "Inc" / "Mod" / "Mid.h").write_text('#include "../Base.h"\n#include <string.h>\nclass Mid : public Base { };\n')
    (tmp_path / "Inc" / "Mod" / "Leaf.h").write_text('#include "Mid.h"\n// #include "Gone.h"\nclass LeafIface { };\nclass Leaf : public Mid { };\n')
    assert lane.header_classes("Inc/Mod/Leaf.h") == ["LeafIface", "Leaf", "Mid", "Base"]
    assert lane.header_classes("Inc/Missing.h") == []


def test_tournament_strips_every_class_the_header_brings(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Leaf.h").write_text("class Base { };\nclass Leaf : public Base { };\n")
    seen = []
    monkeypatch.setattr(lane, "try_units", lambda sources, strip, header, key, jobs, **kw:
                        seen.append(list(strip)) or [(s, None, "", []) for s in sources])
    monkeypatch.setattr(lane, "registered", lambda: {})
    lane.tournament("Leaf", {"fields": [], "key": "class"}, ["u.cpp"], "Leaf.h", ["registered"], 1, fixed_header=True)
    assert seen == [["Leaf", "Base"]]


def test_reference_headers_does_not_cache_an_empty_tree(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "merge_cache_dir", lambda: tmp_path)
    monkeypatch.setattr(lane, "_git", lambda *args, strip=True: "pin")
    indexes = [{"bfme1": {}, "zh": {}}, {"bfme1": {"Object": "a.h"}, "zh": {"Object": "b.h"}}]
    monkeypatch.setattr(lane, "reference_header_index", lambda: indexes.pop(0))
    assert lane.reference_headers() == {"bfme1": {}, "zh": {}}
    assert not (tmp_path / "reference_headers_pin.json").exists()
    assert lane.reference_headers()["bfme1"] == {"Object": "a.h"}
    assert lane.reference_headers()["bfme1"] == {"Object": "a.h"}       # now read from the cache
