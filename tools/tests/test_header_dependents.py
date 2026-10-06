"""header_dependents: a header change reaches exactly the sources that can include it, and
every doubt widens the set or falls back to the full gate."""
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


def test_toolchain_or_vendor_change_needs_the_full_gate(repo, capsys):
    base(repo)
    put(repo, "vendor/stlport/stl/_vector.h", "x\n")
    assert run(repo, capsys, "--staged")[0] == 2


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


def test_an_included_vendored_file_needs_the_full_gate(repo, capsys):
    included_base(repo)
    put(repo, "Code/Alloc.cpp", "#include <stl/_alloc.c>\n")
    git(repo, "commit", "-qm", "alloc")
    put(repo, "vendor/stlport/stl/_alloc.c", "x\n")
    assert run(repo, capsys, "--staged")[0] == 2


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


