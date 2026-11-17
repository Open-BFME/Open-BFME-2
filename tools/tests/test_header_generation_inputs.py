"""Current input population cannot omit established shared-header consumers."""
import csv
from dataclasses import replace
import hashlib
import json
from pathlib import Path
import subprocess
import sys
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import header_generation_inputs as G


HEADER = "Code/Inc/Target.h"


def git(root, *args):
    return subprocess.run(["git", *args], cwd=root, capture_output=True, check=True)


def put(root, path, text, tracked=True):
    target = root / path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(text.encode("utf-8") if isinstance(text, str) else text)
    if tracked:
        git(root, "add", "--", path)
    return target


def rows(root, functions=(), data=()):
    for path, sources in zip(G.LEDGERS, (functions, data)):
        target = root / path
        target.parent.mkdir(parents=True, exist_ok=True)
        with target.open("w", encoding="utf-8", newline="") as stream:
            writer = csv.writer(stream, lineterminator="\n")
            writer.writerow(["source"])
            writer.writerows((s,) for s in sources)
        git(root, "add", "--", path)


def receipt(root, unit, includes=(), **changes):
    path = G._receipt_path(root, unit)
    path.parent.mkdir(parents=True, exist_ok=True)
    output = path.with_name(path.name[:-len(".deps.json")] + ".obj")
    output.write_bytes(b"fixture object " + unit.encode())
    md5 = lambda p: hashlib.md5(Path(p).read_bytes()).hexdigest()
    meta = {"path": unit, "source": md5(root / unit), "object": md5(output),
            "deps": {p: md5(root / p) for p in includes}}
    meta.update(changes)
    path.write_text(json.dumps(meta), encoding="utf-8")
    return path


@pytest.fixture
def repo(tmp_path, monkeypatch):
    git(tmp_path, "init", "-q")
    put(tmp_path, HEADER, "struct Target { int value; };\n")
    monkeypatch.setattr(G, "_compiler_inputs", lambda root, source, output, cache=None:
                        G.CompilerInputs("command", "inventory", (), True))
    return tmp_path


def source(root, path, text="void f() {}\n", deps=()):
    put(root, path, text)
    receipt(root, path, deps)
    return path


def test_effective_working_bytes_instead_of_index(repo):
    a = source(repo, "Code/A.cpp")
    b = source(repo, "Code/B.cpp")
    rows(repo, (a, b))
    put(repo, a, '#include "Inc/Target.h"\n', tracked=False)
    receipt(repo, a)
    got = G.discover(HEADER, repo)
    assert got.sources == (a, b)
    assert got.mandatory == (a,)
    assert got.uncertainty == ()
    assert git(repo, "show", ":" + a).stdout == b"void f() {}\n"


def test_current_function_and_data_rows_are_both_in_population(repo):
    a = source(repo, "Code/A.cpp")
    b = source(repo, "Code/Data.c", '#include "Inc/Target.h"\n', (HEADER,))
    rows(repo, (a,))
    put(repo, G.LEDGERS[1], "source\n" + b + "\n", tracked=False)
    got = G.discover(HEADER, repo)
    assert got.sources == (a, b)
    assert got.mandatory == (b,)
    assert HEADER in got.files and G.LEDGERS[1] in got.files


def test_transitive_included_cpp_and_nonstandard_table_fixed_point(repo):
    put(repo, "Code/Inner.cpp", '#include "Inc/Target.h"\n')
    put(repo, "Code/middle.tbl", '#include "Inner.cpp"\n')
    put(repo, "Code/Outer.h", '#include "middle.tbl"\n')
    a = source(repo, "Code/A.cpp", '#include "Outer.h"\n')
    b = source(repo, "Code/B.cpp")
    rows(repo, (a, b))
    assert G.discover(HEADER, repo).mandatory == (a,)


@pytest.mark.parametrize("forced", ["Forced.h", "Forced.tbl"])
def test_actual_compiler_forced_input_and_its_transitive_closure(repo, monkeypatch, forced):
    put(repo, "Code/" + forced, '#include "Inc/Target.h"\n')
    a = source(repo, "Code/A.cpp")
    b = source(repo, "Code/B.cpp")
    rows(repo, (a, b))
    monkeypatch.setattr(G, "_compiler_inputs", lambda root, source, output, cache=None:
                        G.CompilerInputs("command", "inventory", (forced,) if source == a else (), True))
    got = G.discover(HEADER, repo)
    assert got.mandatory == (a,)
    assert got.uncertainty == ()


def test_command_adapter_uses_real_builder_forced_operands(tmp_path, monkeypatch):
    calls = []
    def command(src, out):
        calls.append((src, out))
        return ["cl", "-FI", "One.h", "/FITwo.h", "-c", str(src)], {"INCLUDE": "roots"}
    fake = SimpleNamespace(ROOT=tmp_path, compiler_command=command,
                           search_inventory=lambda *a, **k: "inventory",
                           compile_is_current=lambda *a, **k: k["strict"],
                           _cmd_fingerprint=lambda *a: "fingerprint")
    monkeypatch.setitem(sys.modules, "build", fake)
    got = G._compiler_inputs(tmp_path.resolve(), "Code/A.cpp", tmp_path / "A.obj")
    assert got == G.CompilerInputs("fingerprint", "inventory", ("One.h", "Two.h"), True)
    assert calls == [(tmp_path / "Code/A.cpp", tmp_path / "A.obj")]


def test_receipt_actual_include_union_covers_files_outside_graph_roots(repo):
    put(repo, "vendor/Bridge.h", '#include "Target.h"\n')
    a = source(repo, "Code/A.cpp", '#include "../vendor/Bridge.h"\n', ("vendor/Bridge.h", HEADER))
    b = source(repo, "Code/B.cpp")
    rows(repo, (a, b))
    assert G.discover(HEADER, repo).mandatory == (a,)


def test_macro_include_widens_through_its_includers(repo):
    put(repo, "Code/Indirect.tbl", "#include SELECTED\n")
    a = source(repo, "Code/A.cpp", '#include "Indirect.tbl"\n')
    b = source(repo, "Code/B.cpp")
    rows(repo, (a, b))
    assert G.discover(HEADER, repo).mandatory == (a,)


@pytest.mark.parametrize("definition", [
    "#define _STLP_NATIVE_HEADER(X) selected\n",
    "#define _STLP_NATIVE_HEA\\\nDER(X) selected\n",
    "#define /*comment*/ _STLP_NATIVE_HEADER(X) selected\n",
])
def test_stlp_override_prepass_cannot_keep_fixed_literal_shortcut(repo, definition):
    put(repo, "Code/Override.h", definition)
    a = source(repo, "Code/A.cpp", "#include _STLP_NATIVE_HEADER(other.h)\n")
    b = source(repo, "Code/B.cpp")
    rows(repo, (a, b))
    assert G.discover(HEADER, repo).mandatory == (a,)


def test_spliced_commented_trigraph_include_is_not_lost(repo):
    a = source(repo, "Code/A.cpp", '??=inc\\\nlude /* comment */ "Inc/Target.h"\n')
    rows(repo, (a,))
    assert G.discover(HEADER, repo).mandatory == (a,)


@pytest.mark.parametrize("text", ["#include @bad\n", "%:include <Inc/Target.h>\n",
                                 "/* prefix */ %:include <Inc/Target.h>\n",
                                 "%\\\n:include <Inc/Target.h>\n",
                                 "#pragma include_alias(\"x\", \"y\")\n"])
def test_unbounded_directive_cannot_shrink_population(repo, text):
    put(repo, "Code/Doubt.h", text)
    a = source(repo, "Code/A.cpp")
    b = source(repo, "Code/B.cpp")
    rows(repo, (a, b))
    got = G.discover(HEADER, repo)
    assert got.mandatory == (a, b)
    assert got.uncertainty


@pytest.mark.parametrize("failure", ["missing", "malformed", "wrong_source", "wrong_object", "wrong_digest", "stale", "unavailable", "missing_dep"])
def test_missing_stale_or_unbound_receipt_is_unknown_and_mandatory(repo, monkeypatch, failure):
    a = source(repo, "Code/A.cpp")
    b = source(repo, "Code/B.cpp")
    rows(repo, (a, b))
    path = G._receipt_path(repo, a)
    if failure == "missing":
        path.unlink()
    elif failure == "malformed":
        path.write_text("not json")
    elif failure == "wrong_source":
        receipt(repo, a, path=b)
    elif failure == "wrong_object":
        receipt(repo, a, object="0" * 32)
    elif failure == "wrong_digest":
        receipt(repo, a, source="0" * 32)
    elif failure == "missing_dep":
        receipt(repo, a, deps={"Code/missing.h": "0" * 32})
    else:
        def compiler(root, name, output, cache=None):
            if name == a and failure == "unavailable":
                raise OSError("no compiler input proof")
            return G.CompilerInputs("command", "inventory", (), name != a)
        monkeypatch.setattr(G, "_compiler_inputs", compiler)
    got = G.discover(HEADER, repo)
    assert got.mandatory == (a,)
    assert any(a in why for why in got.uncertainty)


@pytest.mark.parametrize("change", ["header", "source", "ledger", "table", "receipt", "object", "dependency", "tracked"])
def test_snapshot_revalidation_refuses_changed_observed_inputs(repo, change):
    dep = "vendor/Used.h"
    put(repo, dep, "int used;\n")
    table = "Code/Used.tbl"
    put(repo, table, "int table;\n")
    a = source(repo, "Code/A.cpp", '#include "Used.tbl"\n', (dep,))
    rows(repo, (a,))
    got = G.discover(HEADER, repo)
    paths = {"header": repo / HEADER, "source": repo / a, "ledger": repo / G.LEDGERS[0],
             "table": repo / table, "receipt": G._receipt_path(repo, a), "dependency": repo / dep}
    if change == "tracked":
        put(repo, "Code/New.h", "int new_input;\n")
    elif change == "object":
        p = G._receipt_path(repo, a)
        p.with_name(p.name[:-len(".deps.json")] + ".obj").write_bytes(b"changed object")
    else:
        with paths[change].open("ab") as stream:
            stream.write(b"\nchanged\n")
    with pytest.raises(G.InputRefused):
        got.revalidate()


@pytest.mark.parametrize("changes", [{"fingerprint": "changed"}, {"inventory": "changed"},
                                    {"forced": ("Other.h",)}, {"reusable": False}])
def test_snapshot_refuses_command_or_search_inventory_drift(repo, monkeypatch, changes):
    a = source(repo, "Code/A.cpp")
    rows(repo, (a,))
    got = G.discover(HEADER, repo)
    changed = replace(G.CompilerInputs("command", "inventory", (), True), **changes)
    monkeypatch.setattr(G, "_compiler_inputs", lambda *a, **k: changed)
    with pytest.raises(G.InputRefused, match="compiler/search inputs changed"):
        got.revalidate()


def test_missing_or_untracked_ledger_source_is_refused(repo):
    put(repo, "Code/Missing.cpp", "void f() {}\n", tracked=False)
    rows(repo, ("Code/Missing.cpp",))
    with pytest.raises(G.InputRefused, match="ledger source"):
        G.discover(HEADER, repo)


def test_result_cannot_have_its_snapshot_silently_mutated(repo):
    a = source(repo, "Code/A.cpp")
    rows(repo, (a,))
    got = G.discover(HEADER, repo)
    with pytest.raises(TypeError):
        got.files[HEADER] = "forged"
    assert got.revalidate() is True
