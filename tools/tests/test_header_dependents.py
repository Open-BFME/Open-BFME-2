"""header_dependents: a header change reaches exactly the sources that can include it, and
every doubt widens the set or falls back to the full gate."""
import hashlib
import json
import re
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import header_dependents as H  # noqa: E402


def git(root, *args):
    subprocess.run(["git", *args], cwd=root, check=True, capture_output=True)


@pytest.fixture
def repo(tmp_path, monkeypatch):
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "user.name", "Fixture")
    git(tmp_path, "config", "user.email", "fixture@example.invalid")
    monkeypatch.setattr(H, "ROOT", tmp_path)
    return tmp_path


def put(root, path, text):
    target = root / path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(text)
    git(root, "add", "--", path)


def ledger(root, *sources):
    put(root, "reverse/functions.csv",
        "name,export_rva,target_rva,target_size,source,status,notes\n"
        + "".join(f"?f{i}@@YAXXZ,,0x{0x1000 + i:08X},4,{s},matched,x\n" for i, s in enumerate(sources)))


def head(repo):
    return subprocess.run(["git", "rev-parse", "HEAD"], cwd=repo, capture_output=True,
                          text=True, check=True).stdout.strip()


def run(root, capsys, *args):
    code = H.main(list(args))
    out = capsys.readouterr()
    return code, [line for line in out.out.splitlines() if line]


def base(repo):
    put(repo, "Code/Inc/Low.h", "int low;\n")
    put(repo, "Code/Inc/Mid.h", '#include "../Inc/LOW.H"\n')
    put(repo, "Code/A.cpp", '#include "Inc/Mid.h"\nvoid a() {}\n')
    put(repo, "Code/B.cpp", "void b() {}\n")
    put(repo, "Code/C.cpp", "// cl: /FIForced.h\nvoid c() {}\n")
    put(repo, "Code/Forced.h", "int forced;\n")
    ledger(repo, "Code/A.cpp", "Code/B.cpp", "Code/C.cpp")
    git(repo, "commit", "-qm", "base")


def test_transitive_case_insensitive_include(repo, capsys):
    base(repo)
    put(repo, "Code/Inc/Low.h", "int low2;\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/A.cpp"])


def test_forced_include_counts(repo, capsys):
    base(repo)
    put(repo, "Code/Forced.h", "int forced2;\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/C.cpp"])


def test_deleted_header_still_finds_its_includers(repo, capsys):
    base(repo)
    git(repo, "rm", "-q", "Code/Inc/Low.h")
    assert run(repo, capsys, "--staged") == (0, ["Code/A.cpp"])


def test_new_unincluded_header_reaches_nothing(repo, capsys):
    base(repo)
    put(repo, "Code/Inc/Unused.h", "int unused;\n")
    assert run(repo, capsys, "--staged") == (0, [])


def test_macro_include_counts_as_including_everything(repo, capsys):
    base(repo)
    put(repo, "Code/D.cpp", "#define H \"x.h\"\n#include H\nvoid d() {}\n")
    ledger(repo, "Code/A.cpp", "Code/B.cpp", "Code/C.cpp", "Code/D.cpp")
    git(repo, "commit", "-qm", "macro")
    put(repo, "Code/Inc/Low.h", "int low3;\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/A.cpp", "Code/D.cpp"])


@pytest.mark.parametrize("path", ["build/toolchains/vc71/include/stdio.h", "reference/open-bfme-1"])
def test_toolchain_or_bfme1_pointer_change_needs_the_full_gate(repo, capsys, path):
    base(repo)
    put(repo, path, "x\n")
    assert run(repo, capsys, "--staged")[0] == 2


def test_a_vendored_change_without_receipts_reaches_every_compiled_unit(repo, capsys):
    base(repo)
    put(repo, "vendor/stlport/stl/_vector.h", "x\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/A.cpp", "Code/B.cpp", "Code/C.cpp"])


MACRO_INCLUDER = '#define H "x.h"\n#include H\nvoid d() {}\n'


def test_a_game_unit_named_stlport_is_not_vendored(repo, capsys):
    # A macro include anywhere makes every changed unit a root; a game unit that
    # merely carries STLport in its NAME must still get the bounded scope.
    base(repo)
    put(repo, "Code/Lib/StlportVectorThing.cpp", "void s() {}\n")
    put(repo, "Code/D.cpp", MACRO_INCLUDER)
    ledger(repo, "Code/A.cpp", "Code/B.cpp", "Code/C.cpp", "Code/D.cpp", "Code/Lib/StlportVectorThing.cpp")
    git(repo, "commit", "-qm", "named")
    put(repo, "Code/Lib/StlportVectorThing.cpp", "void s2() {}\n")
    assert run(repo, capsys, "--staged")[0] == 0


@pytest.mark.parametrize("path", ["Code/stlport/NarrowFilebufInputError.cpp",
                                  "Code/Libraries/Source/STLport/IosBase.cpp",
                                  "Code/Libraries/Source/STLport/LocaleUnshiftStrwcmp.c"])
def test_a_game_unit_in_an_stlport_directory_is_bounded(repo, capsys, path):
    # 694c36df81 edited Code/stlport/NarrowFilebufInputError.cpp, an ordinary unit:
    # its includers (here only the macro includer) are the scope, not the full gate.
    base(repo)
    put(repo, "Code/D.cpp", MACRO_INCLUDER)
    put(repo, path, "void i() {}\n")
    ledger(repo, "Code/A.cpp", "Code/B.cpp", "Code/C.cpp", "Code/D.cpp", path)
    git(repo, "commit", "-qm", "lib")
    old = head(repo)
    put(repo, path, "void i2() {}\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/D.cpp"])
    git(repo, "commit", "-qm", "edit")
    assert run(repo, capsys, "--range", old, head(repo)) == (0, ["Code/D.cpp"])


def test_an_stlport_directory_under_code_is_bounded_by_the_graph(repo, capsys):
    # Code/stlport/ and Code/Libraries/Source/STLport/ hold game units on no
    # include path: their includers (here only the macro includer) are the scope.
    base(repo)
    put(repo, "Code/D.cpp", MACRO_INCLUDER)
    put(repo, "Code/Libraries/Source/STLport/IosBase.cpp", "void i() {}\n")
    ledger(repo, "Code/A.cpp", "Code/B.cpp", "Code/C.cpp", "Code/D.cpp",
           "Code/Libraries/Source/STLport/IosBase.cpp")
    git(repo, "commit", "-qm", "lib")
    put(repo, "Code/Libraries/Source/STLport/IosBase.cpp", "void i2() {}\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/D.cpp"])


def test_limit_falls_back_to_the_full_gate(repo, capsys):
    base(repo)
    put(repo, "Code/Inc/Low.h", "int low4;\n")
    assert run(repo, capsys, "--staged", "--limit", "0")[0] == 2


def test_mod_headers_are_not_game_dependencies(repo, capsys):
    base(repo)
    put(repo, "mods/features/x/feature.h", "int mod;\n")
    assert run(repo, capsys, "--staged") == (0, [])


def included_base(repo):
    put(repo, "Code/Net/Inc.cpp", "void inc() {}\n")
    put(repo, "Code/Net/Host.cpp", '#include "Inc.cpp"\nvoid host() {}\n')
    put(repo, "Code/Lib/Outer.cpp", '#include "../Net/Host.cpp"\n')
    put(repo, "Code/Lib/henc.tbl", "1, 2, 3,\n")
    put(repo, "Code/Lib/Huff.inl", '#include "henc.tbl"\n')
    put(repo, "Code/Lib/Huff.cpp", '#include "Huff.inl"\nvoid huff() {}\n')
    ledger(repo, "Code/Net/Inc.cpp", "Code/Net/Host.cpp", "Code/Lib/Outer.cpp", "Code/Lib/Huff.cpp")
    git(repo, "commit", "-qm", "base")


def test_an_included_source_reaches_its_includers_through_sources(repo, capsys):
    included_base(repo)
    put(repo, "Code/Net/Inc.cpp", "void inc2() {}\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/Lib/Outer.cpp", "Code/Net/Host.cpp"])


def test_an_included_table_reaches_through_a_header(repo, capsys):
    included_base(repo)
    put(repo, "Code/Lib/henc.tbl", "4, 5, 6,\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/Lib/Huff.cpp"])


def test_a_renamed_included_source_still_reaches_the_old_includers(repo, capsys):
    included_base(repo)
    git(repo, "mv", "Code/Net/Inc.cpp", "Code/Net/Moved.cpp")
    assert run(repo, capsys, "--staged") == (0, ["Code/Lib/Outer.cpp", "Code/Net/Host.cpp"])


def test_a_source_nothing_includes_skips_the_graph(repo, capsys, monkeypatch):
    included_base(repo)
    monkeypatch.setattr(H, "graph", lambda: pytest.fail("graph built for an unincluded source"))
    put(repo, "Code/Lib/Huff.cpp", '#include "Huff.inl"\nvoid huff2() {}\n')
    assert run(repo, capsys, "--staged") == (0, [])


def test_an_included_vendored_file_without_receipts_reaches_every_unit(repo, capsys):
    included_base(repo)
    put(repo, "Code/Alloc.cpp", "#include <stl/_alloc.c>\n")
    ledger(repo, "Code/Net/Inc.cpp", "Code/Net/Host.cpp", "Code/Lib/Outer.cpp", "Code/Lib/Huff.cpp",
           "Code/Alloc.cpp")
    git(repo, "commit", "-qm", "alloc")
    put(repo, "vendor/stlport/stl/_alloc.c", "x\n")
    assert "Code/Alloc.cpp" in run(repo, capsys, "--staged")[1]


def one_includer(repo, includer, text, extra=None):
    put(repo, "Code/shared.h", "#define VALUE 1\n")
    put(repo, includer, text)
    for path, body in (extra or {}).items():
        put(repo, path, body)
    ledger(repo, includer)
    git(repo, "commit", "-qm", "base")


@pytest.mark.parametrize("suffix", ["cc", "cxx"])
def test_other_cxx_suffixes_are_selected(repo, capsys, suffix):
    one_includer(repo, f"Code/a.{suffix}", '#include "shared.h"\n')
    put(repo, "Code/shared.h", "#define VALUE 2\n")
    assert run(repo, capsys, "--staged") == (0, [f"Code/a.{suffix}"])


def test_a_chain_through_an_included_non_header_is_followed(repo, capsys):
    one_includer(repo, "Code/a.cpp", '#include "bridge.def"\n', {"Code/bridge.def": '#include "shared.h"\n'})
    put(repo, "Code/shared.h", "#define VALUE 2\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/a.cpp"])


@pytest.mark.parametrize("text", ['#include \\\n"shared.h"\n', '#inc\\\nlude "shared.h"\n',
                                  '#\\\ninclude "shared.h"\n', '/* x */ #include "shared.h"\n',
                                  '#include /* x */ "shared.h"\n', '﻿#include "shared.h"\n',
                                  '??=include "shared.h"\n', '#include \\\r\n"shared.h"\r\n'])
def test_spliced_commented_or_bom_includes_are_seen(repo, capsys, text):
    put(repo, "Code/shared.h", "#define VALUE 1\n")
    (repo / "Code/a.cpp").write_bytes(text.encode("utf-8"))
    git(repo, "add", "Code/a.cpp")
    ledger(repo, "Code/a.cpp")
    git(repo, "commit", "-qm", "base")
    put(repo, "Code/shared.h", "#define VALUE 2\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/a.cpp"])


@pytest.mark.parametrize("text", ['#include "shared.h"\n', '#inc\\\nlude "shared.h"\n', '#\\\ninclude "shared.h"\n'])
def test_git_without_pcre_falls_back_to_the_same_selection(repo, capsys, monkeypatch, text):
    monkeypatch.setattr(H, "GREP_PCRE", "(")  # git grep -P fails as it does without PCRE
    one_includer(repo, "Code/a.cpp", text)
    put(repo, "Code/shared.h", "#define VALUE 2\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/a.cpp"])


def test_a_binary_looking_source_is_still_scanned(repo, capsys):
    one_includer(repo, "Code/a.cpp", '#include "shared.h"\nchar z = 0;\0\n')
    put(repo, "Code/shared.h", "#define VALUE 2\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/a.cpp"])


def test_an_unparseable_include_needs_the_full_gate(repo, capsys):
    one_includer(repo, "Code/a.cpp", '#include "shared.h\n')
    put(repo, "Code/shared.h", "#define VALUE 2\n")
    assert run(repo, capsys, "--staged")[0] == 2


def test_a_utf16_source_needs_the_full_gate(repo, capsys):
    put(repo, "Code/shared.h", "#define VALUE 1\n")
    (repo / "Code/a.cpp").write_bytes('#include "shared.h"\n'.encode("utf-16"))
    git(repo, "add", "Code/a.cpp")
    ledger(repo, "Code/a.cpp")
    git(repo, "commit", "-qm", "base")
    put(repo, "Code/shared.h", "#define VALUE 2\n")
    assert run(repo, capsys, "--staged")[0] == 2


def test_a_macro_include_reaches_a_changed_non_header(repo, capsys):
    one_includer(repo, "Code/a.cpp", '#define BODY "part.data"\nint f(){return\n#include BODY\n;}\n',
                 {"Code/part.data": "1\n"})
    put(repo, "Code/part.data", "2\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/a.cpp"])


def test_staged_selection_reads_the_index_not_the_worktree(repo, capsys):
    one_includer(repo, "Code/a.cpp", '#include "shared.h"\n')
    put(repo, "Code/shared.h", "#define VALUE 2\n")
    (repo / "Code/a.cpp").write_text("int f() { return 1; }\n")
    (repo / "reverse/functions.csv").write_text("name,export_rva,target_rva\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/a.cpp"])


def test_range_selection_reads_the_commits_not_the_worktree(repo, capsys):
    one_includer(repo, "Code/a.cpp", '#include "shared.h"\n')
    old = head(repo)
    put(repo, "Code/shared.h", "#define VALUE 2\n")
    git(repo, "commit", "-qm", "header")
    (repo / "Code/a.cpp").write_text("int f() { return 1; }\n")
    (repo / "reverse/functions.csv").write_text("name,export_rva,target_rva\n")
    assert run(repo, capsys, "--range", old, head(repo)) == (0, ["Code/a.cpp"])


def test_range_sees_the_old_name_of_a_renamed_header(repo, capsys):
    base(repo)
    old = head(repo)
    git(repo, "mv", "Code/Inc/Low.h", "Code/Inc/Lower.h")
    git(repo, "commit", "-qm", "rename")
    git(repo, "config", "diff.renames", "true")
    assert run(repo, capsys, "--range", old, head(repo)) == (0, ["Code/A.cpp"])




def test_a_data_only_unit_is_a_dependent(repo, capsys):
    """A unit owning only data rows (reverse/data_rows.csv) is byte-verified too;
    a header it includes must select it (GPT-6.1-Sol, converged gate round 4)."""
    put(repo, "Code/Init.h", "#define INIT 1\n")
    put(repo, "Code/DataOnly.cpp", '#include "Init.h"\nint g = INIT;\n')
    put(repo, "Code/Other.cpp", "void o() {}\n")
    ledger(repo, "Code/Other.cpp")                       # no function row names DataOnly.cpp
    put(repo, "reverse/data_rows.csv", "name,address,address_kind,size,section,source,status,evidence,model\n"
        "?g@@3HA,0x009E0000,rva,4,.data,Code/DataOnly.cpp,matched,e,m\n")
    git(repo, "commit", "-qm", "base")
    old = head(repo)
    put(repo, "Code/Init.h", "#define INIT 2\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/DataOnly.cpp"])
    git(repo, "commit", "-qm", "header")
    assert run(repo, capsys, "--range", old, head(repo)) == (0, ["Code/DataOnly.cpp"])


def _drop_blob(repo, spec):
    """Delete the loose object `spec` names: the path stays listed, its blob unreadable."""
    sha = subprocess.run(["git", "rev-parse", spec], cwd=repo, capture_output=True, text=True,
                         check=True).stdout.strip()
    loose = repo / ".git" / "objects" / sha[:2] / sha[2:]
    loose.chmod(0o644)                                   # git writes objects read-only
    loose.unlink()


@pytest.mark.parametrize("staged", [True, False])
def test_an_unreadable_data_ledger_is_not_taken_for_a_missing_one(repo, capsys, staged):
    """A data_rows.csv the snapshot lists but cannot read must fail the selection
    (the hooks then widen to every source), never select as if it were absent
    (GPT-6.1-Sol, converged gate round 5). Absence itself is fine (control)."""
    put(repo, "Code/Init.h", "#define INIT 1\n")
    put(repo, "Code/DataOnly.cpp", '#include "Init.h"\nint g = INIT;\n')
    put(repo, "Code/Other.cpp", "void o() {}\n")
    ledger(repo, "Code/Other.cpp")
    git(repo, "commit", "-qm", "base, no data ledger")
    old = head(repo)
    put(repo, "Code/Init.h", "#define INIT 2\n")
    assert run(repo, capsys, "--staged") == (0, [])               # control: no data_rows.csv at all
    put(repo, "reverse/data_rows.csv", "name,address,address_kind,size,section,source,status,evidence,model\n"
        "?g@@3HA,0x009E0000,rva,4,.data,Code/DataOnly.cpp,matched,e,m\n")
    if staged:
        _drop_blob(repo, ":reverse/data_rows.csv")
        with pytest.raises(SystemExit):
            H.main(["--staged"])
    else:
        git(repo, "commit", "-qm", "header and data ledger")
        _drop_blob(repo, "HEAD:reverse/data_rows.csv")
        with pytest.raises(SystemExit):
            H.main(["--range", old, head(repo)])


def test_a_data_ledger_tracked_under_another_case_is_refused(repo, capsys):
    """Windows builds read reverse/Data_Rows.csv as the data ledger; git's exact
    lookup would miss it and its units would go unselected (review round 6)."""
    put(repo, "Code/Init.h", "#define INIT 1\n")
    put(repo, "Code/DataOnly.cpp", '#include "Init.h"\nint g = INIT;\n')
    put(repo, "Code/Other.cpp", "void o() {}\n")
    ledger(repo, "Code/Other.cpp")
    put(repo, "reverse/Data_Rows.csv", "name,address,address_kind,size,section,source,status,evidence,model\n"
        "?g@@3HA,0x009E0000,rva,4,.data,Code/DataOnly.cpp,matched,e,m\n")
    git(repo, "commit", "-qm", "base")
    put(repo, "Code/Init.h", "#define INIT 2\n")
    with pytest.raises(SystemExit):
        H.main(["--staged"])


def test_a_data_ledger_under_a_miscased_directory_is_refused(repo, capsys):
    """Reverse/data_rows.csv: the variant is the parent, which a listing of reverse/
    never shows (review round 7)."""
    put(repo, "Code/Init.h", "#define INIT 1\n")
    put(repo, "Code/DataOnly.cpp", '#include "Init.h"\nint g = INIT;\n')
    put(repo, "Code/Other.cpp", "void o() {}\n")
    ledger(repo, "Code/Other.cpp")
    blob = repo / "blob.tmp"
    blob.write_text("name,address,address_kind,size,section,source,status,evidence,model\n"
                    "?g@@3HA,0x009E0000,rva,4,.data,Code/DataOnly.cpp,matched,e,m\n")
    sha = subprocess.run(["git", "hash-object", "-w", str(blob)], cwd=repo, capture_output=True, text=True,
                         check=True).stdout.strip()
    git(repo, "update-index", "--add", "--cacheinfo", f"100644,{sha},Reverse/data_rows.csv")
    git(repo, "commit", "-qm", "base")
    old = head(repo)
    put(repo, "Code/Init.h", "#define INIT 2\n")
    with pytest.raises(SystemExit):
        H.main(["--staged"])
    git(repo, "commit", "-qm", "header")
    with pytest.raises(SystemExit):
        H.main(["--range", old, head(repo)])



# --- vendored changes: bounded by compile receipts and opt-ins -------------------

def receipt(repo, source, deps, path=None):
    """The build/match/*.deps.json build.py writes for `source` after compiling it
    (tools/build.py _write_deps_sidecar), hashing the working tree now."""
    def md5(rel):
        return hashlib.md5((repo / rel).read_bytes()).hexdigest()
    target = H.receipt_path(source)
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(json.dumps({"cmd": "x", "source": md5(source), "path": path or source,
                                  "deps": {dep.replace("/", "\\"): md5(dep) for dep in deps}}))


def vendored_base(repo, extra=None):
    """A, B, C units with current receipts; A includes vendor/lib/a.h."""
    put(repo, "vendor/lib/a.h", "int a;\n")
    put(repo, "vendor/lib/b.h", "int b;\n")
    put(repo, "Code/A.cpp", "#include <a.h>\nvoid a() {}\n")
    put(repo, "Code/B.cpp", "#include <b.h>\nvoid b() {}\n")
    put(repo, "Code/C.cpp", "void c() {}\n")
    for path, text in (extra or {}).items():
        put(repo, path, text)
    ledger(repo, "Code/A.cpp", "Code/B.cpp", "Code/C.cpp", *[p for p in (extra or {}) if p.endswith(".cpp")])
    git(repo, "commit", "-qm", "base")
    receipt(repo, "Code/A.cpp", ["vendor/lib/a.h"])
    receipt(repo, "Code/B.cpp", ["vendor/lib/b.h"])
    receipt(repo, "Code/C.cpp", [])
    for path in extra or {}:
        if path.endswith(".cpp"):
            receipt(repo, path, [])


def test_a_modified_vendored_header_reaches_only_the_units_recording_it(repo, capsys):
    vendored_base(repo)
    put(repo, "vendor/lib/a.h", "int a2;\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/A.cpp"])


def test_a_new_vendored_package_nothing_opts_into_reaches_no_unit(repo, capsys):
    vendored_base(repo)
    old = head(repo)
    put(repo, "vendor/stlport-4.6/stlport/vector", "#include <stl/_vector.h>\n")
    put(repo, "vendor/stlport-4.6/stlport/stl/_vector.h", "x\n")
    assert run(repo, capsys, "--staged") == (0, [])
    git(repo, "commit", "-qm", "import")
    assert run(repo, capsys, "--range", old, head(repo)) == (0, [])


@pytest.mark.parametrize("text", ["// stlport46\nvoid o() {}\n", "// cl: /Ivendor/STLPORT-4.6/stlport\nvoid o() {}\n"])
def test_a_unit_opting_into_a_new_package_is_reached(repo, capsys, text):
    vendored_base(repo, {"Code/Opt.cpp": text})
    put(repo, "vendor/stlport-4.6/stlport/vector", "x\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/Opt.cpp"])


def test_a_header_opting_in_reaches_its_includers(repo, capsys):
    vendored_base(repo, {"Code/Uses.cpp": '#include "uses.h"\n', "Code/uses.h": '#include "../vendor/newlib/x.h"\n'})
    put(repo, "vendor/newlib/x.h", "x\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/Uses.cpp"])


def test_a_macro_includer_opts_into_every_package(repo, capsys):
    vendored_base(repo, {"Code/D.cpp": MACRO_INCLUDER})
    put(repo, "vendor/newlib/x.h", "x\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/D.cpp"])


def test_an_added_file_reaches_every_unit_recording_its_package(repo, capsys):
    # a new header can shadow one a unit resolves later on its search path
    vendored_base(repo)
    put(repo, "vendor/lib/c.h", "int c;\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/A.cpp", "Code/B.cpp"])


def test_a_deleted_file_reaches_every_unit_recording_its_package(repo, capsys):
    vendored_base(repo)
    git(repo, "rm", "-q", "vendor/lib/b.h")
    assert run(repo, capsys, "--staged") == (0, ["Code/A.cpp", "Code/B.cpp"])


def test_an_unrecorded_tool_input_reaches_the_opted_in_units(repo, capsys):
    # PROVENANCE.txt is read by build.py, never #included: no receipt bounds it
    vendored_base(repo, {"Code/Dx.cpp": "// dxsdk\nvoid d() {}\n",
                         "vendor/dxsdk-aug2005/PROVENANCE.txt": "a\n"})
    put(repo, "vendor/dxsdk-aug2005/PROVENANCE.txt", "b\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/Dx.cpp"])


def test_vendored_stlport_reaches_reference_units_by_path(repo, capsys):
    vendored_base(repo, {"reference/open-bfme-1/x/Unit.cpp": "void u() {}\n"})
    put(repo, "vendor/stlport/new_header", "x\n")
    assert run(repo, capsys, "--staged") == (0, ["reference/open-bfme-1/x/Unit.cpp"])


def test_a_stale_receipt_counts_as_missing(repo, capsys):
    vendored_base(repo)
    put(repo, "Code/C.cpp", '#include <a.h>\nvoid c() {}\n')
    git(repo, "commit", "-qm", "c includes a.h now; C's receipt predates it")
    put(repo, "vendor/lib/a.h", "int a2;\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/A.cpp", "Code/C.cpp"])


def test_a_receipt_with_a_changed_recorded_header_counts_as_missing(repo, capsys):
    vendored_base(repo, {"Code/inc.h": "int i;\n"})
    receipt(repo, "Code/C.cpp", ["Code/inc.h"])
    put(repo, "Code/inc.h", "int i2;\n")
    git(repo, "commit", "-qm", "header moved on since C compiled")
    put(repo, "vendor/lib/a.h", "int a2;\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/A.cpp", "Code/C.cpp"])


def test_a_dirty_unit_counts_as_missing(repo, capsys):
    vendored_base(repo)
    (repo / "Code/B.cpp").write_text("#include <a.h>\n")
    receipt(repo, "Code/B.cpp", [])     # hashed from the dirty file
    put(repo, "vendor/lib/a.h", "int a2;\n")
    git(repo, "commit", "-qm", "vendor")
    old = subprocess.run(["git", "rev-parse", "HEAD~1"], cwd=repo, capture_output=True, text=True).stdout.strip()
    assert run(repo, capsys, "--range", old, head(repo)) == (0, ["Code/A.cpp", "Code/B.cpp"])


def test_a_receipt_for_another_source_counts_as_missing(repo, capsys):
    # Code/a_b.cpp and Code/a/b.cpp share one object name
    vendored_base(repo)
    receipt(repo, "Code/B.cpp", [], path="Code/b.cpp")
    put(repo, "vendor/lib/a.h", "int a2;\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/A.cpp", "Code/B.cpp"])


@pytest.mark.parametrize("path", ["vendor/msvc71crt/msvcrt.lib", "vendor/lib/tool.exe",
                                  "vendor/vc71-sp1/provenance.txt"])
def test_binaries_and_compiler_profiles_need_the_full_gate(repo, capsys, path):
    vendored_base(repo, {"vendor/vc71-sp1/bin/cl.exe": "exe"})
    put(repo, path, "changed\n")
    assert run(repo, capsys, "--staged")[0] == 2


def test_the_vendored_limit_falls_back_to_the_full_gate(repo, capsys):
    vendored_base(repo)
    put(repo, "vendor/lib/a.h", "int a2;\n")
    assert run(repo, capsys, "--staged", "--limit", "0")[0] == 2


def test_every_vendored_package_the_build_names_has_an_opt_in():
    """A package build.py (or a module it loads) puts on an include path must be
    in OPT_IN, or the evidence scope could miss its marker units."""
    text = "".join((TOOLS / name).read_text(encoding="utf-8") for name in
                   ("build.py", "compiler_profiles.py", "stlport_overlay.py") if (TOOLS / name).exists())
    named = set(re.findall(r'"vendor"\s*/\s*"([\w.+-]+)"', text)) | {n.rstrip(".") for n in re.findall(r'vendor/([A-Za-z0-9][\w.+-]*)', text)}
    profiles = {p.parent.parent.name for p in (TOOLS.parent / "vendor").glob("*/bin/*")} | \
        {p.parent.name for p in (TOOLS.parent / "vendor").glob("*/compiler.zip")}
    missing = sorted(n for n in named if n not in H.OPT_IN and n not in profiles)
    assert not missing, f"vendored packages build.py names without an OPT_IN entry: {missing}"


def test_an_unrecorded_document_no_tool_reads_reaches_no_unit(repo, capsys):
    vendored_base(repo, {"Code/S.cpp": "// stlport\nvoid s() {}\n", "vendor/lib/README.md": "a\n"})
    put(repo, "vendor/lib/README.md", "b\n")
    assert run(repo, capsys, "--staged") == (0, [])


def test_an_unrecorded_file_a_tool_names_reaches_the_package(repo, capsys):
    # build.py tests vendor/stlport/list for existence
    vendored_base(repo, {"Code/S.cpp": "// stlport\nvoid s() {}\n", "vendor/stlport/list": "a\n",
                         "tools/build.py": 'if (path / "list").exists(): pass\n'})
    put(repo, "vendor/stlport/list", "b\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/S.cpp"])


def test_stlport_overlay_code_forces_the_full_gate(repo, capsys):
    # stlport_overlay.selected runs for every unit in build.compiler_environment
    base(repo)
    put(repo, "tools/stlport_overlay.py", "input\n")
    assert run(repo, capsys, "--staged")[0] == 2
    git(repo, "commit", "-qm", "overlay")
    before = head(repo)
    git(repo, "rm", "-q", "tools/stlport_overlay.py")
    git(repo, "commit", "-qm", "remove overlay")
    assert run(repo, capsys, "--range", before, head(repo))[0] == 2


@pytest.mark.parametrize("path", ["vendor/stlport-4.6-bfme/_tree.c.patch", "vendor/stlport-4.6/stlport/vector"])
def test_stlport46_inputs_reach_the_opted_in_units(repo, capsys, path):
    # the overlay patches vendor/stlport-4.6 into build/stlport46/<digest>/, which only
    # `// stlport46` units search: no receipt names the input, the marker does
    vendored_base(repo, {"Code/S46.cpp": "// stlport46\nvoid s() {}\n", "Code/S.cpp": "// stlport\nvoid t() {}\n",
                         path: "input\n"})
    put(repo, path, "changed\n")
    assert run(repo, capsys, "--staged") == (0, ["Code/S46.cpp"])
    git(repo, "commit", "-qm", "input")
    before = head(repo)
    git(repo, "rm", "-q", path)
    git(repo, "commit", "-qm", "remove input")
    assert run(repo, capsys, "--range", before, head(repo)) == (0, ["Code/S46.cpp"])
