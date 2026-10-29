"""A passed full gate carries to a later push only from a commit of this
clone, while the verifier is unchanged and header_dependents can bound the
change between them (tools/full_gate_receipt.py)."""
import os
import subprocess
import sys
import time
from pathlib import Path

import pytest
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import full_gate_receipt as R


def git(root, *args):
    return subprocess.run(["git", *args], cwd=root, capture_output=True, text=True, check=True).stdout.strip()


def commit(root, path, text):
    (root / path).parent.mkdir(parents=True, exist_ok=True)
    (root / path).write_text(text)
    git(root, "add", path)
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", path)
    return git(root, "rev-parse", "HEAD")


@pytest.fixture
def repo(tmp_path, monkeypatch):
    root = tmp_path / "repo"
    root.mkdir()
    git(root, "init", "-q")
    monkeypatch.setattr(R, "ROOT", root)
    monkeypatch.setattr(R, "bounded", lambda old, new: True)
    return root


def test_a_rebased_push_carries_the_full_gate_it_passed(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0, base=c0)
    assert R.find(c0) == c0
    c1 = commit(repo, "Code/b.cpp", "2")  # master moved: the rebased push
    assert R.find(c1) == c0


def test_no_carry_across_a_verifier_change(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0, base=c0)
    assert R.find(commit(repo, "tools/build.py", "changed")) is None
    c2 = commit(repo, "Code/c.cpp", "3")
    R.record(c2, base=c2)
    assert R.find(commit(repo, ".githooks/pre-push", "changed")) is None


def test_no_carry_when_the_change_is_unbounded(repo, monkeypatch):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0, base=c0)
    c1 = commit(repo, "vendor/stlport/x.h", "2")
    monkeypatch.setattr(R, "bounded", lambda old, new: False)
    assert R.find(c1) is None


def test_expired_or_foreign_receipts_carry_nothing(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0, base=c0)
    stale = time.time() - (R.KEEP_HOURS + 1) * 3600
    os.utime(R.receipts_dir() / c0, (stale, stale))
    assert R.find(commit(repo, "Code/b.cpp", "2")) is None
    (R.receipts_dir() / ("f" * 40)).write_text("0\n")  # not a commit of this clone
    assert R.recorded() == []


def test_the_nearest_receipt_is_tried_first(repo, monkeypatch):
    far = commit(repo, "Code/a.cpp", "1")
    R.record(far, base=far)
    commit(repo, "Code/b.cpp", "2")
    near = commit(repo, "Code/c.cpp", "3")
    R.record(near, base=near)
    os.utime(R.receipts_dir() / near, (time.time() - 60, time.time() - 60))  # older record, nearer tree
    tried = []
    monkeypatch.setattr(R, "bounded", lambda old, new: tried.append(old) or True)
    assert R.find(commit(repo, "Code/d.cpp", "4")) == near and tried == [near]


def test_no_carry_across_a_tree_wide_baseline_change(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0, base=c0)
    assert R.find(commit(repo, "reverse/gate_baseline.txt", "one debt line fewer")) is None
    c2 = commit(repo, "Code/b.cpp", "2")
    R.record(c2, base=c2)
    # the exception-data and converged lists are re-audited by the hook instead
    assert R.find(commit(repo, "reverse/eh_baseline.csv", "shrunk")) == c2


def _loads(tmp_path, *entries):
    folder = tmp_path / "loads"
    folder.mkdir(exist_ok=True)
    (folder / "123").write_text("".join(f"{e}\n" for e in entries))
    return folder


def test_a_tool_the_gate_never_loaded_does_not_void_its_receipt(repo, tmp_path):
    commit(repo, "tools/build.py", "b")
    commit(repo, "tools/tu_skeleton.py", "1")
    commit(repo, "tools/tests/test_tu_skeleton.py", "1")
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0, base=c0, loads=_loads(tmp_path, "tools/build.py", "tools/ledger_io.py", "tools/"))
    commit(repo, "tools/tu_skeleton.py", "2")  # another seat's tool and its test landed
    assert R.find(commit(repo, "tools/tests/test_tu_skeleton.py", "2")) == c0


def test_a_loaded_tool_or_hook_change_voids_the_receipt(repo, tmp_path):
    commit(repo, "tools/build.py", "b")
    c0 = commit(repo, "tools/ledger_io.py", "1")
    loads = _loads(tmp_path, "tools/build.py", "tools/ledger_io.py", "tools/")
    R.record(c0, base=c0, loads=loads)
    assert R.find(commit(repo, "tools/ledger_io.py", "2")) is None
    c2 = commit(repo, "Code/b.cpp", "2")
    R.record(c2, base=c2, loads=loads)
    assert R.find(commit(repo, ".githooks/pre-push", "changed")) is None


def test_an_added_or_removed_entry_of_a_listed_directory_voids_the_receipt(repo, tmp_path):
    commit(repo, "tools/build.py", "b")
    commit(repo, "tools/tests/test_a.py", "1")
    c0 = commit(repo, "tools/old_tool.py", "1")
    loads = _loads(tmp_path, "tools/build.py", "tools/")
    R.record(c0, base=c0, loads=loads)
    assert R.find(commit(repo, "tools/json.py", "shadows an import")) is None
    c2 = commit(repo, "Code/b.cpp", "2")
    R.record(c2, base=c2, loads=loads)
    assert R.find(commit(repo, "tools/tests/test_b.py", "1")) == c2  # tools/tests/ was not listed
    c4 = commit(repo, "Code/c.cpp", "3")
    R.record(c4, base=c4, loads=loads)
    assert R.find(commit(repo, "tools/newpkg/__init__.py", "")) is None  # a new subdirectory
    c6 = commit(repo, "Code/d.cpp", "4")
    R.record(c6, base=c6, loads=loads)
    git(repo, "rm", "-q", "tools/old_tool.py")
    git(repo, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "rm")
    assert R.find(git(repo, "rev-parse", "HEAD")) is None


def test_a_carried_push_keeps_the_tool_list_of_the_receipt_it_carried_from(repo, tmp_path):
    commit(repo, "tools/build.py", "b")
    commit(repo, "tools/tu_skeleton.py", "0")
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0, base=c0, loads=_loads(tmp_path, "tools/build.py", "tools/"))
    c1 = commit(repo, "Code/b.cpp", "2")
    R.record(c1, base=c1, loads="", loads_from=c0)          # the pre-push hook's carried-push record
    assert R.receipt_loads(c1) == R.receipt_loads(c0)
    commit(repo, "tools/tu_skeleton.py", "1")       # a tool neither gate loaded changed: both carry
    assert R.find(commit(repo, "Code/c.cpp", "3")) in (c0, c1)
    c4 = commit(repo, "Code/d.cpp", "4")
    R.record(c4, base=c4, loads_from="0" * 40)               # an unknown receipt: all of tools/ counts
    assert R.receipt_loads(c4) is None


def test_a_receipt_without_a_usable_load_list_counts_all_of_tools(repo, tmp_path):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0, base=c0)
    assert R.find(commit(repo, "tools/tu_skeleton.py", "1")) is None
    c2 = commit(repo, "Code/b.cpp", "2")
    R.record(c2, base=c2, loads=_loads(tmp_path, "tools/ledger_io.py"))  # no build.py: an incomplete log
    assert R.receipt_loads(c2) is None
    assert R.find(commit(repo, "tools/tu_skeleton.py", "2")) is None
    assert R.gate_loads(tmp_path / "missing") is None


def test_build_logs_the_tools_it_loads(tmp_path):
    tools = Path(__file__).resolve().parents[1]
    folder = tmp_path / "loads"
    folder.mkdir()
    env = dict(os.environ, BFME_GATE_LOADS=str(folder))
    code = "import build, eh_verify; open(build.ROOT / 'tools' / 'judges.json').close()"
    subprocess.run([sys.executable, "-c", code], cwd=tools, env=env, check=True)
    entries = R.gate_loads(folder)
    assert {"tools/build.py", "tools/ledger_io.py", "tools/eh_verify.py", "tools/judges.json", "tools/"} <= entries
    assert not any("__pycache__" in e for e in entries)
    assert "tools/tu_skeleton.py" not in entries


def test_cross_checks_byte_verify_what_they_had_to_rebuild(monkeypatch):
    import build
    import check_module_registry
    a, b = build.ROOT / "Code" / "a.cpp", build.ROOT / "Code" / "b.cpp"
    rows = [{"source": "Code/a.cpp"}, {"source": "Code/b.cpp"}]
    stale = {"calls": 0}

    def stale_sources(sources, outputs, workers=1, **kw):
        stale["calls"] += 1
        return [a] if stale["calls"] == 1 else []   # a was not current; the compile fixed it
    verified = []
    monkeypatch.setattr(build, "ensure_case_shims", lambda: None)
    monkeypatch.setattr(build, "ensure_reference_current", lambda: None)
    monkeypatch.setattr(build, "load_function_rows", lambda: rows)
    monkeypatch.setattr(build, "stale_sources", stale_sources)
    monkeypatch.setattr(build, "compile_rows", lambda rows, sources, **kw: None)
    monkeypatch.setattr(build, "main", lambda only=None, **kw: verified.append(kw["exact_sources"]))
    monkeypatch.setattr(build, "verify_dir32_consistency", lambda rows, **kw: None)
    monkeypatch.setattr(check_module_registry, "verify", lambda: None)
    assert build.cross_source_checks() == 0
    assert verified == [{"Code/a.cpp"}]

    def mismatch(only=None, **kw):
        raise SystemExit(1)
    stale["calls"] = 0
    monkeypatch.setattr(build, "main", mismatch)
    assert build.cross_source_checks() == 1


@pytest.mark.parametrize("failure", [None, "bytes", "restore", "moved", "compile-race", "dir32", "module"])
def test_large_restored_scope_stays_exact_and_fail_closed(monkeypatch, failure):
    import build
    import check_module_registry
    # Crossing the former 1,024 threshold must not request a full gate. One
    # unchanged source still participates in the global checks and final currency.
    rows = [{"source": f"Code/part{i}.cpp"} for i in range(1026)]
    sources = [build.ROOT / row["source"] for row in rows]
    rebuilt = sources[:-1]
    calls = []
    moved_during_compile = []
    def compile_rows(rows, scope, **kw):
        assert scope == rebuilt
        if failure == "compile-race":
            # Inputs of the initially current TU moved after the snapshot. It
            # must not be silently restored outside the captured byte scope.
            moved_during_compile.append(sources[-1])
    def stale_sources(scope, outputs, workers=1, **kw):
        calls.append(list(scope))
        if len(calls) == 1:
            return rebuilt
        if failure == "restore" and len(calls) == 2:
            return [rebuilt[0]]
        if failure == "moved" and len(calls) == 3:
            return [sources[-1]]
        if moved_during_compile and sources[-1] in scope:
            return moved_during_compile
        return []
    verified, global_rows, modules = [], [], []
    def verify(only=None, *, exact_sources=None):
        assert only is None and exact_sources is not None
        verified.append(exact_sources)
        if failure == "bytes":
            raise SystemExit(1)
    def dir32(scope, **kw):
        global_rows.append(scope)
        if failure == "dir32":
            raise SystemExit(1)
    def module():
        modules.append(True)
        if failure == "module":
            raise SystemExit(1)
    monkeypatch.setattr(build, "ensure_case_shims", lambda: None)
    monkeypatch.setattr(build, "ensure_reference_current", lambda: None)
    monkeypatch.setattr(build, "load_function_rows", lambda: rows)
    monkeypatch.setattr(build, "stale_sources", stale_sources)
    monkeypatch.setattr(build, "compile_rows", compile_rows)
    monkeypatch.setattr(build, "main", verify)
    monkeypatch.setattr(build, "verify_dir32_consistency", dir32)
    monkeypatch.setattr(check_module_registry, "verify", module)
    assert build.cross_source_checks() == (0 if failure is None else 1)
    if failure == "restore":
        assert verified == []
    else:
        assert verified == [{row["source"] for row in rows[:-1]}]
    if failure not in ("restore", "bytes"):
        assert global_rows == [rows] and modules == [True]
        assert calls[-1] == sources


def test_exact_scope_runs_every_scoped_reference_gate(monkeypatch):
    import build
    import data_rows
    rows = [{"source": "Code/a.cpp", "name": "a"},
            {"source": "Code/nested/Code/a.cpp", "name": "b"},
            {"source": "Code/other.cpp", "name": "Code/a.cpp"}]
    scope = {"Code/a.cpp"}
    calls = []
    monkeypatch.setattr(build, "ensure_case_shims", lambda: None)
    monkeypatch.setattr(build, "ensure_reference_current", lambda: None)
    monkeypatch.setattr(build, "load_function_rows", lambda: rows)
    monkeypatch.setattr(build, "verify_source_claims", lambda only, **kw: calls.append(("claims", kw["exact_sources"])))
    monkeypatch.setattr(build, "verify_functions", lambda only, **kw: calls.append(("functions", kw["exact_sources"])))
    monkeypatch.setattr(data_rows, "load", lambda: rows)
    monkeypatch.setattr(data_rows, "verify", lambda **kw: calls.append(("data", kw["sources"])))
    for label in ("string", "float", "import"):
        monkeypatch.setattr(build, f"verify_{label}_refs", lambda scope, label=label: calls.append((label, scope)))
    build.main(exact_sources=scope)
    assert calls == [("claims", scope), ("data", ["Code/a.cpp"]), ("functions", scope),
                     ("string", rows[:1]), ("float", rows[:1]), ("import", rows[:1])]
    with pytest.raises(SystemExit, match="empty exact source scope"):
        build.main(exact_sources=set())


def test_exact_function_scope_checks_bytes_without_rewriting_full_derived_file(tmp_path, monkeypatch):
    import build
    source = tmp_path / "Code/a.cpp"
    source.parent.mkdir()
    source.write_text("// fixture\n")
    rows = [{"source": "Code/a.cpp", "name": "a", "target_rva": "0x1000"},
            {"source": "Code/else.cpp", "name": "Code/a.cpp", "target_rva": "0x2000"}]
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "load_function_rows", lambda: rows)
    monkeypatch.setattr(build, "load_all_function_rows", lambda: rows)
    monkeypatch.setattr(build, "load_symbol_map", lambda: {})
    monkeypatch.setattr(build, "compile_rows", lambda rows, sources: {})
    monkeypatch.setattr(build, "row_object", lambda row: None)
    monkeypatch.setattr(build, "body_extent_problems", lambda *a, **kw: [])
    def no_derived_write(patches):
        pytest.fail("exact source scope must not overwrite the full derived index")
    monkeypatch.setattr(build, "write_reloc_names", no_derived_write)
    patch = {"target": b"\xc3", "bytes": b"\xc3", "masked": False,
             "note": "", "verified_folds": set(), "unresolved": []}
    visited = []
    def compile_function(row, symbols, obj):
        visited.append(row["source"])
        return patch
    monkeypatch.setattr(build, "compile_function", compile_function)
    assert build.verify_functions(exact_sources={"Code/a.cpp"}) == [patch]
    assert set(visited) == {"Code/a.cpp"}
    patch["bytes"] = b"\xcc"
    with pytest.raises(SystemExit):
        build.verify_functions(exact_sources={"Code/a.cpp"})


@pytest.mark.parametrize("unchanged_funclet", [False, True])
def test_cross_source_global_proof_still_checks_unchanged_owners(tmp_path, monkeypatch, capsys, unchanged_funclet):
    import build
    import check_module_registry
    import struct
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/dir32_consistency_whitelist.txt").write_text("")
    objects = [tmp_path / "a.obj", tmp_path / "b.obj"]
    for obj in objects:
        obj.write_bytes(b"fixture")
    rows = [{"source": f"Code/{letter}.cpp", "name": f"function{i}",
             "target_rva": hex(0x1000 + i * 0x10), "target_size": "7", "notes": ""}
            for i, letter in enumerate("ab")]
    if unchanged_funclet:
        rows[1]["notes"] = "gen-funclet;object-symbol=$L123;parent=parent"
    sources = [tmp_path / row["source"] for row in rows]
    currency_calls = []
    def stale(scope, outputs, workers=1, **kw):
        currency_calls.append(list(scope))
        return sources[:1] if len(currency_calls) == 1 else []
    def bounded(only=None, *, exact_sources):
        assert only is None and exact_sources == {"Code/a.cpp"}
    visited = []
    def object_for(row):
        visited.append(row["source"])
        return objects[0 if row["source"] == "Code/a.cpp" else 1]
    collisions = []
    def unchanged_owner_collision(row, symbol, obj, retail):
        assert row is rows[1]
        collisions.append(symbol)
        raise SystemExit(1)
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "ensure_case_shims", lambda: None)
    monkeypatch.setattr(build, "ensure_reference_current", lambda: None)
    monkeypatch.setattr(build, "load_function_rows", lambda: rows)
    monkeypatch.setattr(build, "stale_sources", stale)
    monkeypatch.setattr(build, "compile_rows", lambda rows, sources, **kw: None)
    monkeypatch.setattr(build, "main", bounded)
    monkeypatch.setattr(build, "require_row_object", object_for)
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size:
                        b"\xd9\x05" + struct.pack("<I", 0x402000 + (rva - 0x1000) * 0x10) + b"\xc3")
    monkeypatch.setattr(build, "read_object_symbol_bytes", lambda *args:
                        (b"\xd9\x05\x00\x00\x00\x00\xc3", [(2, 6, "_shared_global")]))
    monkeypatch.setattr(build, "_object_layout", lambda *args: (b"", [], []))
    monkeypatch.setattr(build, "read_funclet", unchanged_owner_collision)
    monkeypatch.setattr(check_module_registry, "verify", lambda: None)
    assert build.cross_source_checks() == 1
    assert {"Code/a.cpp", "Code/b.cpp"} <= set(visited)
    assert collisions == (["$L123"] if unchanged_funclet else [])
    if not unchanged_funclet:
        assert "NEW inconsistent symbol" in capsys.readouterr().out



# --- carried cross-checks: the DIR32 index ------------------------------------

def dir32_fixture(tmp_path, monkeypatch, bases=None):
    """Rows a and b each address `_shared_global`; their retail bytes put it at
    `bases[source]` (one address: consistent). Returns (rows, objects, visited, stale)."""
    import build
    import check_module_registry
    import struct
    bases = bases if bases is not None else {"Code/a.cpp": 0x402000, "Code/b.cpp": 0x402000}
    (tmp_path / "reverse").mkdir(exist_ok=True)
    (tmp_path / "reverse/dir32_consistency_whitelist.txt").write_text("")
    match = tmp_path / "build" / "match"
    match.mkdir(parents=True, exist_ok=True)
    rows = [{"source": f"Code/{letter}.cpp", "name": f"function{i}",
             "target_rva": hex(0x1000 + i * 0x10), "target_size": "7", "notes": ""}
            for i, letter in enumerate("ab")]
    objects = {row["source"]: match / build._ledger_object_name(row) for row in rows}
    for obj in objects.values():
        obj.write_bytes(b"fixture")
    by_rva = {int(row["target_rva"], 16): row["source"] for row in rows}
    visited, stale = [], []
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "BUILD_DIR", match)
    monkeypatch.setattr(build, "ensure_case_shims", lambda: None)
    monkeypatch.setattr(build, "ensure_reference_current", lambda: None)
    monkeypatch.setattr(build, "load_function_rows", lambda: rows)
    monkeypatch.setattr(build, "stale_sources", lambda scope, outputs, workers=1, **kw:
                        [s for s in scope if s.relative_to(tmp_path).as_posix() in stale])
    monkeypatch.setattr(build, "compile_rows", lambda rows, sources, **kw: None)
    monkeypatch.setattr(build, "main", lambda only=None, **kw: None)
    monkeypatch.setattr(build, "row_object", lambda row: objects[row["source"]])

    def require(row):
        visited.append(row["source"])
        return objects[row["source"]]
    monkeypatch.setattr(build, "require_row_object", require)
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size:
                        b"\xd9\x05" + struct.pack("<I", bases[by_rva[rva]]) + b"\xc3")
    monkeypatch.setattr(build, "read_object_symbol_bytes", lambda *args:
                        (b"\xd9\x05\x00\x00\x00\x00\xc3", [(2, 6, "_shared_global")]))
    monkeypatch.setattr(build, "_object_layout", lambda *args: (b"", [], []))
    monkeypatch.setattr(check_module_registry, "verify", lambda: None)
    return rows, objects, visited, stale, bases


def passed_index(tmp_path, monkeypatch):
    """A full cross-check pass that writes its index, as a full gate does."""
    import build
    fixture = dir32_fixture(tmp_path, monkeypatch)
    index = tmp_path / "passed.dir32.gz"
    assert build.cross_source_checks(index_out=str(index)) == 0
    assert index.is_file()
    fixture[2].clear()
    return fixture, index


def test_carried_cross_checks_read_only_the_verified_objects(tmp_path, monkeypatch, capsys):
    import build
    (rows, objects, visited, stale, bases), index = passed_index(tmp_path, monkeypatch)
    out = tmp_path / "next.dir32.gz"
    assert build.cross_source_checks(carried_index=index, verified={"Code/a.cpp"}, index_out=str(out)) == 0
    assert set(visited) == {"Code/a.cpp"}
    assert "1 row(s) carried" in capsys.readouterr().out
    # the carried push's own index carries the next retry the same way
    visited.clear()
    assert build.cross_source_checks(carried_index=out, verified=set()) == 0
    assert visited == []


def test_carried_cross_checks_refuse_a_collision_with_an_unread_row(tmp_path, monkeypatch, capsys):
    # What the full pass refuses: a verified row now puts the global elsewhere than
    # an unchanged row the carried index answers for.
    import build
    (rows, objects, visited, stale, bases), index = passed_index(tmp_path, monkeypatch)
    bases["Code/a.cpp"] = 0x403000
    assert build.cross_source_checks(carried_index=index, verified={"Code/a.cpp"}) == 1
    assert set(visited) == {"Code/a.cpp"}
    assert "NEW inconsistent symbol" in capsys.readouterr().out
    visited.clear()
    assert build.cross_source_checks() == 1     # the full pass agrees


def test_a_rebuilt_unverified_object_checks_every_row(tmp_path, monkeypatch, capsys):
    import build
    import os
    (rows, objects, visited, stale, bases), index = passed_index(tmp_path, monkeypatch)
    stat = objects["Code/b.cpp"].stat()
    os.utime(objects["Code/b.cpp"], ns=(stat.st_atime_ns, stat.st_mtime_ns + 10**9))
    assert build.cross_source_checks(carried_index=index, verified={"Code/a.cpp"}) == 0
    assert "rebuilt since the carried check" in capsys.readouterr().out
    assert set(visited) == {"Code/a.cpp", "Code/b.cpp"}


def test_a_changed_unverified_row_checks_every_row(tmp_path, monkeypatch, capsys):
    import build
    (rows, objects, visited, stale, bases), index = passed_index(tmp_path, monkeypatch)
    rows[1]["notes"] = "object-symbol=other"
    build.cross_source_checks(carried_index=index, verified={"Code/a.cpp"})
    assert "not in the carried index" in capsys.readouterr().out
    assert "Code/b.cpp" in visited


@pytest.mark.parametrize("damage", ["missing", "corrupt", "version"])
def test_an_unusable_index_checks_every_row(tmp_path, monkeypatch, capsys, damage):
    import build
    import gzip
    (rows, objects, visited, stale, bases), index = passed_index(tmp_path, monkeypatch)
    if damage == "missing":
        index.unlink()
    elif damage == "corrupt":
        index.write_bytes(b"not gzip")
    else:
        with gzip.open(index, "wt") as handle:
            handle.write('{"version": 0, "rows": {}, "objects": {}}')
    assert build.cross_source_checks(carried_index=index, verified={"Code/a.cpp"}) == 0
    assert "no carried DIR32 index" in capsys.readouterr().out
    assert set(visited) == {"Code/a.cpp", "Code/b.cpp"}


def test_a_verified_object_that_is_not_current_fails(tmp_path, monkeypatch, capsys):
    import build
    (rows, objects, visited, stale, bases), index = passed_index(tmp_path, monkeypatch)
    stale.append("Code/a.cpp")
    assert build.cross_source_checks(carried_index=index, verified={"Code/a.cpp"}) == 1
    assert "verified object(s) not current" in capsys.readouterr().out


def test_a_receipt_keeps_its_index_and_cross_checks_find_it(repo, monkeypatch, tmp_path):
    import build
    sha = commit(repo, "Code/a.cpp", "a")
    index = tmp_path / "index.gz"
    index.write_bytes(b"index")
    R.record(sha, base=sha, now=time.time(), dir32_index=str(index))
    assert R.index_path(sha).read_bytes() == b"index"
    assert R.recorded() == [sha]               # the index is not a receipt
    seen = {}
    monkeypatch.setattr(build, "cross_source_checks", lambda **kw: seen.update(kw) or 0)
    listing = tmp_path / "verified"
    listing.write_bytes(b"Code/a.cpp\0")
    assert R.main(["cross-checks", "--since", sha, "--verified-from", str(listing)]) == 0
    assert seen["carried_index"] == R.index_path(sha) and seen["verified"] == {"Code/a.cpp"}
    R.record(sha, base=sha, now=time.time())             # a receipt without an index drops the old one
    assert not R.index_path(sha).exists()
    assert R.main(["cross-checks", "--since", sha, "--verified-from", str(listing)]) == 0
    assert seen["carried_index"] is None


def test_the_ledger_object_name_is_obj_paths():
    import build
    for row in ({"source": "Code/GameEngine/Source/GameClient/Eva.cpp", "notes": ""},
                {"source": "Code/stlport/LocaleTimeDestroy.c", "notes": ""},
                {"source": "Code/a.b/Unit.Name.cpp", "notes": ""},
                {"source": "vendor/msvc71crt/msvcrt.lib", "notes": r"member=obj\i386\stack.obj"}):
        assert build._ledger_object_name(row) == build.row_object(row).name


def test_a_gzip_file_beside_the_tool_logs_is_not_a_log(repo, tmp_path):
    # a136856afb: the hook wrote the DIR32 index into the BFME_GATE_LOADS folder and
    # record died reading it as UTF-8, so the passed full gate left no receipt
    import gzip
    c0 = commit(repo, "Code/a.cpp", "1")
    loads = _loads(tmp_path, "tools/build.py", "tools/ledger_io.py")
    with gzip.open(loads / "dir32-index.gz", "wt") as handle:
        handle.write("{}")
    R.record(c0, base=c0, loads=loads)
    assert R.receipt_loads(c0) == {"tools/build.py", "tools/ledger_io.py"}


# --- catch-up: the receipt's base and verifier identity ------------------------

def test_a_receipt_records_its_base_and_verifier(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0, base=c0)
    base, identity = R.receipt_meta(c0)
    assert base == c0 and identity == R.verifier_identity(c0, None)


def test_catch_up_needs_the_same_verifier_blobs(repo, tmp_path):
    c0 = commit(repo, "tools/build.py", "gate")
    commit(repo, "tools/other.py", "unloaded")
    c1 = commit(repo, "Code/a.cpp", "1")
    R.record(c1, base=c0, loads=_loads(tmp_path, "tools/build.py"))
    assert R.find(commit(repo, "tools/other.py", "unloaded, changed")) == c1    # not the verifier
    assert R.find(commit(repo, "tools/build.py", "gate, changed")) is None      # the verifier moved


def test_an_incoming_hook_change_forces_the_full_gate(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0, base=c0)
    assert R.find(commit(repo, ".githooks/pre-push", "incoming")) is None


def test_a_receipt_without_base_or_identity_forces_the_full_gate(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0, base=c0)
    path = R.receipts_dir() / c0
    lines = path.read_text().splitlines()
    path.write_text("\n".join([lines[0]] + lines[2:]) + "\n")     # a receipt from before this change
    assert R.receipt_meta(c0) is None
    assert R.find(commit(repo, "Code/b.cpp", "2")) is None


def test_a_receipt_whose_base_the_push_does_not_descend_from_forces_the_full_gate(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    empty = "4b825dc642cb6eb9a060e54bf8d69288fbee4904"    # git's empty tree: an unrelated history
    foreign = git(repo, "-c", "user.name=t", "-c", "user.email=t@t", "commit-tree", empty, "-m", "foreign")
    R.record(c0, base=foreign)
    assert R.find(commit(repo, "Code/b.cpp", "2")) is None


def test_record_refuses_a_receipt_without_a_base(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    with pytest.raises(SystemExit):
        R.record(c0)


# --- scoped pushes: DIR32 over the verified sources and witnesses ---------------

def test_a_scoped_push_refuses_a_conflict_within_its_sources(tmp_path, monkeypatch, capsys):
    import build
    rows, objects, visited, stale, bases = dir32_fixture(
        tmp_path, monkeypatch, {"Code/a.cpp": 0x402000, "Code/b.cpp": 0x403000})
    assert build.scoped_dir32({"Code/a.cpp", "Code/b.cpp"}) == 1      # no index needed
    assert "NEW inconsistent symbol" in capsys.readouterr().out


def test_a_scoped_push_refuses_a_conflict_with_a_witness(tmp_path, monkeypatch, capsys):
    import build
    (rows, objects, visited, stale, bases), index = passed_index(tmp_path, monkeypatch)
    bases["Code/a.cpp"] = 0x403000
    assert build.scoped_dir32({"Code/a.cpp"}, index=build.load_dir32_index(index)) == 1
    assert set(visited) == {"Code/a.cpp", "Code/b.cpp"}               # the witness was read again
    assert "1 witness row(s)" in capsys.readouterr().out


def test_a_consistent_scoped_push_passes(tmp_path, monkeypatch):
    import build
    (rows, objects, visited, stale, bases), index = passed_index(tmp_path, monkeypatch)
    assert build.scoped_dir32({"Code/a.cpp"}, index=build.load_dir32_index(index)) == 0


@pytest.mark.parametrize("unusable", ["stale", "dirty"])
def test_a_witness_that_is_not_current_is_not_read(tmp_path, monkeypatch, capsys, unusable):
    import build
    (rows, objects, visited, stale, bases), index = passed_index(tmp_path, monkeypatch)
    bases["Code/a.cpp"] = 0x403000
    dirty = frozenset()
    if unusable == "stale":
        stale.append("Code/b.cpp")
    else:
        dirty = frozenset({"code/b.cpp"})
    # b's object no longer shows the pushed tree: it proves nothing either way
    assert build.scoped_dir32({"Code/a.cpp"}, index=build.load_dir32_index(index), dirty=dirty) == 0
    assert set(visited) == {"Code/a.cpp"}
    assert "0 witness row(s)" in capsys.readouterr().out


def test_a_scoped_push_with_a_stale_verified_object_fails(tmp_path, monkeypatch):
    import build
    rows, objects, visited, stale, bases = dir32_fixture(tmp_path, monkeypatch)
    stale.append("Code/a.cpp")
    assert build.scoped_dir32({"Code/a.cpp"}) == 1
