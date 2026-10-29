"""Wave isolation belongs to commits, including commits inside a push range."""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import conversion_gate as gate

HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"
REAL_ROW = "?old@@YAHXZ,,0x00001000,16,Code/Old.cpp,matched,\n"
DUMP_ROW = ("?d_00002000@@YAXXZ,,0x00002000,1,"
            "Code/gen_asm/d_00002000.asm,matched,gen-dump\n")
DUMP = (".386\n.model flat\n_TEXT SEGMENT\n"
        "public ?d_00002000@@YAXXZ\n?d_00002000@@YAXXZ PROC\n"
        "    db 0C3h\n?d_00002000@@YAXXZ ENDP\n_TEXT ENDS\nEND\n")


@pytest.fixture(autouse=True)
def scratch_cache(tmp_path, monkeypatch):
    """Results reused by tree pair live with the test, not in this clone's cache."""
    import ledger_cache
    monkeypatch.setattr(ledger_cache, "folder", lambda: tmp_path / "ledger-cache")


@pytest.fixture
def repo(tmp_path, monkeypatch):
    monkeypatch.chdir(tmp_path)

    def git(*args):
        return subprocess.run(["git", *args], check=True, capture_output=True,
                              text=True).stdout.strip()

    def write(path, content):
        destination = tmp_path / path
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_text(content, encoding="utf-8")

    def commit():
        git("add", "Code", "reverse/functions.csv")
        git("commit", "-qm", "test change")
        return git("rev-parse", "HEAD")

    git("init", "-q")
    git("config", "user.name", "Gate test")
    git("config", "user.email", "gate@example.invalid")
    git("config", "core.hooksPath", str(tmp_path / "no-hooks"))
    write("Code/Old.cpp", "int old() { return 1; }\n")
    write("reverse/functions.csv", HEADER + REAL_ROW)
    base = commit()
    return git, write, commit, base


def wave(write, row=DUMP_ROW, dump=DUMP):
    write("Code/gen_asm/d_00002000.asm", dump)
    write("reverse/functions.csv", HEADER + REAL_ROW + row)


def check_main(monkeypatch, base, tip):
    monkeypatch.setattr(sys, "argv", ["conversion_gate.py", base, tip])
    return gate.main()


@pytest.mark.parametrize("replace_dump", [False, True])
def test_separate_wave_and_recovery_commits_can_publish_together(repo, monkeypatch,
                                                               replace_dump):
    _, write, commit, base = repo
    wave(write)
    wave_tip = commit()
    write("Code/Recovered.cpp", "void recovered() {}\n")
    recovered_rva = "0x00002000" if replace_dump else "0x00003000"
    recovered = ("?recovered@@YAXXZ,,%s,1,"
                 "Code/Recovered.cpp,matched,converted\n") % recovered_rva
    write("reverse/functions.csv", HEADER + REAL_ROW +
          ("" if replace_dump else DUMP_ROW) + recovered)
    tip = commit()
    assert gate.gen_asm_offences(base, wave_tip) == []
    assert gate.gen_asm_offences(wave_tip, tip) == []
    assert gate.gen_asm_offences(base, tip) == []
    assert check_main(monkeypatch, base, tip) == 0


def test_mixed_wave_is_refused_even_after_code_edit_is_reverted(repo):
    _, write, commit, base = repo
    wave(write)
    write("Code/Old.cpp", "int old() { return 2; }\n")
    mixed = commit()
    write("Code/Old.cpp", "int old() { return 1; }\n")
    tip = commit()
    offences = gate.gen_asm_offences(base, tip)
    assert any(offence.startswith("C3 ") and mixed in offence for offence in offences)


def test_staged_mixed_wave_is_still_refused(repo):
    git, write, _, base = repo
    wave(write)
    write("Code/Old.cpp", "int old() { return 2; }\n")
    git("add", "Code", "reverse/functions.csv")
    assert any(offence.startswith("C3 ") for offence in gate.gen_asm_offences(base, ":"))


def test_staged_dump_only_wave_is_allowed(repo):
    git, write, _, base = repo
    wave(write)
    git("add", "Code/gen_asm/d_00002000.asm", "reverse/functions.csv")
    assert gate.gen_asm_offences(base, ":") == []


def test_wave_cannot_delete_a_cpp_source(repo):
    git, write, commit, base = repo
    wave(write)
    git("rm", "Code/Old.cpp")
    tip = commit()
    assert any(offence.startswith("C3 ") and "Code/Old.cpp" in offence
               for offence in gate.gen_asm_offences(base, tip))


@pytest.mark.parametrize("rule,row,dump", [
    ("C1", DUMP_ROW, DUMP + "named_function PROC\n"),
    ("C2", DUMP_ROW.replace("?d_00002000@@YAXXZ", "?named@@YAXXZ"), DUMP),
    ("C2", DUMP_ROW.replace("gen-dump", "recovered"), DUMP),
])
def test_invalid_dump_cannot_be_hidden_by_a_later_revert(repo, rule, row, dump):
    git, write, commit, base = repo
    wave(write, row, dump)
    commit()
    git("restore", "--source", base, "reverse/functions.csv")
    git("rm", "Code/gen_asm/d_00002000.asm")
    tip = commit()
    assert any(offence.startswith(rule + " ") for offence in gate.gen_asm_offences(base, tip))


def test_mixed_commit_on_merged_branch_is_checked(repo):
    git, write, commit, base = repo
    git("checkout", "-qb", "side")
    wave(write)
    write("Code/Old.cpp", "int old() { return 2; }\n")
    mixed = commit()
    git("checkout", "--detach", base)
    write("Code/Main.cpp", "void main_path() {}\n")
    commit()
    git("merge", "--no-ff", "-m", "merge test", "side")
    tip = git("rev-parse", "HEAD")
    assert any(offence.startswith("C3 ") and mixed in offence
               for offence in gate.gen_asm_offences(base, tip))


def test_root_commit_on_merged_branch_is_checked(repo):
    git, write, commit, base = repo
    git("checkout", "--orphan", "side")
    wave(write)
    root = commit()
    git("checkout", "--detach", base)
    git("merge", "--allow-unrelated-histories", "--no-ff", "-s", "ours",
        "-m", "merge root", "side")
    tip = git("rev-parse", "HEAD")
    assert any(offence.startswith("C3 ") and root in offence
               for offence in gate.gen_asm_offences(base, tip))


def test_naked_lifts_remain_refused(repo, monkeypatch):
    _, write, commit, base = repo
    write("Code/Lift.cpp", "__declspec(naked) void lift() { __emit(0xc3); }\n")
    tip = commit()
    assert check_main(monkeypatch, base, tip) == 1


def test_clean_cpp_repointed_to_dump_remains_refused(repo, monkeypatch):
    _, write, commit, base = repo
    wave(write, DUMP_ROW.replace("00002000", "00001000"))
    write("reverse/functions.csv", HEADER + DUMP_ROW.replace("0x00002000", "0x00001000"))
    tip = commit()
    assert gate.clean_coverage_lost(base, tip)
    assert check_main(monkeypatch, base, tip) == 1


@pytest.mark.parametrize("staged", [False, True])
@pytest.mark.parametrize("suffix", [".lib", ".LIB"])
def test_prebuilt_archive_may_yield_to_assembly(repo, monkeypatch, staged, suffix):
    git, write, commit, _ = repo
    archive = "vendor/crt/runtime" + suffix
    write(archive, "prebuilt archive fixture\n")
    git("add", archive)
    write("reverse/functions.csv", HEADER + REAL_ROW.replace("Code/Old.cpp", archive))
    before = commit()
    assembly = "Code/masm_dumps/CompilerHelper.asm"
    write(assembly, ".386\n.model flat\nEND\n")
    write("reverse/functions.csv", HEADER + REAL_ROW.replace("Code/Old.cpp", assembly))
    if staged:
        git("add", "Code", "reverse/functions.csv")
        tip = ":"
    else:
        tip = commit()
    assert gate.clean_coverage_lost(before, tip) == []
    assert check_main(monkeypatch, before, tip) == 0


@pytest.mark.parametrize("staged", [False, True])
@pytest.mark.parametrize("suffix", [".lib", ".LIB", ".s"])
def test_non_cpp_source_cannot_replace_clean_cpp(repo, monkeypatch, staged, suffix):
    git, write, commit, before = repo
    replacement = "Code/Replacement" + suffix
    write(replacement, "non-C++ fixture\n")
    write("reverse/functions.csv", HEADER + REAL_ROW.replace("Code/Old.cpp", replacement))
    if staged:
        git("add", "Code", "reverse/functions.csv")
        tip = ":"
    else:
        tip = commit()
    assert gate.clean_coverage_lost(before, tip)
    assert check_main(monkeypatch, before, tip) == 1


@pytest.fixture
def imports(monkeypatch, tmp_path):
    import build
    from test_pe_imports import fixture_pe, scaffold_row, scaffold_source, thunk
    data, slots = fixture_pe([("d3dx9_27.dll", "D3DXMatrixMultiply")])
    exe = tmp_path / "fixture.exe"
    exe.write_bytes(data)
    monkeypatch.setattr(build, "EXE", exe)
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: thunk(slots[0]))
    row = scaffold_row(slots[0])
    def csv_row(row):
        return ",".join(row.get(key, "") for key in HEADER.strip().split(",")) + "\n"
    return row, scaffold_source(), csv_row


def test_exact_generated_import_may_yield_to_real_abi_assembly(repo, imports, monkeypatch):
    _, write, commit, _ = repo
    row, source, csv_row = imports
    write(row["source"], source)
    write("reverse/functions.csv", HEADER + csv_row(row))
    before = commit()
    write("Code/masm_dumps/Import.asm", ".386\n.model flat\nEND\n")
    write("reverse/functions.csv", HEADER + csv_row({**row, "name": "_D3DXMatrixMultiply@12",
          "source": "Code/masm_dumps/Import.asm", "notes": "compiler import glue"}))
    tip = commit()
    assert gate.clean_coverage_lost(before, tip) == []
    assert check_main(monkeypatch, before, tip) == 0


@pytest.mark.parametrize("forge", ["authored-path", "actual-name", "body", "wrong-slot"])
def test_gen_import_tag_cannot_hide_authored_cpp_loss(repo, imports, monkeypatch, forge):
    _, write, commit, _ = repo
    row, source, csv_row = imports
    if forge == "authored-path":
        row["source"] = "Code/Handwritten.cpp"
    elif forge == "actual-name":
        row["name"] = "?actual@@YAXXZ"
    elif forge == "body":
        source = source.replace("D3DXMatrixMultiply(); }", "D3DXMatrixMultiply(); side_effect(); }")
    else:
        row["notes"] = row["notes"].replace("slot=0x00401480", "slot=0x00401490")
    write(row["source"], source)
    write("reverse/functions.csv", HEADER + csv_row(row))
    before = commit()
    write("Code/masm_dumps/Import.asm", ".386\n.model flat\nEND\n")
    write("reverse/functions.csv", HEADER + csv_row({**row, "source": "Code/masm_dumps/Import.asm"}))
    tip = commit()
    assert gate.clean_coverage_lost(before, tip)
    assert check_main(monkeypatch, before, tip) == 1


def test_import_proof_reads_old_revision_not_current_worktree(repo, imports, monkeypatch):
    _, write, commit, _ = repo
    row, source, csv_row = imports
    write(row["source"], source.replace("D3DXMatrixMultiply(); }", "D3DXMatrixMultiply(); side_effect(); }"))
    write("reverse/functions.csv", HEADER + csv_row(row))
    before = commit()
    # A now-canonical working-tree body must not erase OLD's authored semantics.
    write(row["source"], source)
    write("Code/masm_dumps/Import.asm", ".386\n.model flat\nEND\n")
    write("reverse/functions.csv", HEADER + csv_row({**row, "source": "Code/masm_dumps/Import.asm"}))
    tip = commit()
    assert gate.clean_coverage_lost(before, tip)
    assert check_main(monkeypatch, before, tip) == 1


def test_other_cpp_owner_at_import_address_keeps_rule_b_coverage(repo, imports, monkeypatch):
    _, write, commit, _ = repo
    row, source, csv_row = imports
    write(row["source"], source)
    authored = {**row, "name": "?actual@@YAXXZ", "source": "Code/Old.cpp", "notes": ""}
    write("reverse/functions.csv", HEADER + csv_row(row) + csv_row(authored))
    before = commit()
    write("Code/masm_dumps/Import.asm", ".386\n.model flat\nEND\n")
    write("reverse/functions.csv", HEADER + csv_row({**row, "source": "Code/masm_dumps/Import.asm"}))
    tip = commit()
    assert gate.clean_coverage_lost(before, tip)
    assert check_main(monkeypatch, before, tip) == 1


def test_rule_b_uses_old_scaffold_blob_even_when_worktree_is_modified(repo, imports, monkeypatch):
    _, write, commit, _ = repo
    row, source, csv_row = imports
    write(row["source"], source)
    write("reverse/functions.csv", HEADER + csv_row(row))
    before = commit()
    write("Code/masm_dumps/Import.asm", ".386\n.model flat\nEND\n")
    write("reverse/functions.csv", HEADER + csv_row({**row, "source": "Code/masm_dumps/Import.asm"}))
    tip = commit()
    write(row["source"], "handwritten body in the worktree\n")
    assert gate.clean_coverage_lost(before, tip) == []
    assert check_main(monkeypatch, before, tip) == 0


@pytest.mark.parametrize("which", ["old", "new"])
def test_invalid_revision_is_not_an_import_exemption(repo, imports, which):
    _, _, _, base = repo
    with pytest.raises(SystemExit, match="failed"):
        gate.clean_coverage_lost("not-a-real-ref" if which == "old" else base,
                                "not-a-real-ref" if which == "new" else base)


@pytest.mark.parametrize("staged", [False, True])
def test_existing_dump_reorder_with_cpp_edit_is_not_a_wave(repo, staged):
    git, write, commit, _ = repo
    wave(write)
    # Several retained rows make Git report the moved dump as delete/add,
    # as it does when dedup_csv sorts a real ledger.
    retained = REAL_ROW + "".join(
        REAL_ROW.replace("?old@@", "?kept%d@@" % i)
        .replace("0x00001000", "0x%08X" % (0x4000 + i * 0x10))
        for i in range(5))
    write("reverse/functions.csv", HEADER + retained + DUMP_ROW)
    base = commit()
    write("reverse/functions.csv", HEADER + DUMP_ROW + retained)
    write("Code/Old.cpp", "int old() { return 2; }\n")
    if staged:
        git("add", "Code/Old.cpp", "reverse/functions.csv")
        tip = ":"
    else:
        tip = commit()
    assert gate.gen_asm_offences(base, tip) == []


@pytest.mark.parametrize("extra", [
    DUMP_ROW,
    DUMP_ROW.replace("00002000", "00003000"),
    DUMP_ROW.replace("gen-dump", "gen-dump changed extent evidence"),
])
def test_reorder_does_not_hide_added_or_changed_dump_row(repo, extra):
    git, write, commit, _ = repo
    wave(write)
    base = commit()
    write("reverse/functions.csv", HEADER + DUMP_ROW + REAL_ROW + extra)
    write("Code/Old.cpp", "int old() { return 2; }\n")
    git("add", "Code/Old.cpp", "reverse/functions.csv")
    assert any(offence.startswith("C3 ")
               for offence in gate.gen_asm_offences(base, ":"))


def test_changed_existing_dump_row_is_still_a_wave(repo):
    git, write, commit, _ = repo
    wave(write)
    base = commit()
    changed = DUMP_ROW.replace("gen-dump", "gen-dump changed extent evidence")
    write("reverse/functions.csv", HEADER + changed + REAL_ROW)
    write("Code/Old.cpp", "int old() { return 2; }\n")
    git("add", "Code/Old.cpp", "reverse/functions.csv")
    assert any(offence.startswith("C3 ")
               for offence in gate.gen_asm_offences(base, ":"))


def test_show_reads_utf8_sources_regardless_of_locale(repo):
    """A committed source holding a UTF-8 right quote (bytes e2 80 9d; 0x9D is
    undefined in cp1252) must read back as text, not None."""
    _git, write, commit, _base = repo
    write("Code/Old.cpp", "// ”quoted”\nint old() { return 1; }\n")
    commit()
    text = gate.show("HEAD", "Code/Old.cpp")
    assert text is not None and "quoted" in text


# --- results reused by tree pair -----------------------------------------------

def counted(monkeypatch):
    """Count each rule's evaluations from here on."""
    calls = []
    for name in ("_gen_asm_diff_offences", "added_lift_lines", "clean_coverage_lost"):
        real = getattr(gate, name)
        monkeypatch.setattr(gate, name, lambda *a, real=real, name=name: calls.append(name) or real(*a))
    return calls


def test_the_staged_index_and_its_tree_are_refused_alike(repo, monkeypatch):
    git, write, commit, base = repo
    wave(write)
    write("Code/Other.cpp", "int other() { return 2; }\n")
    git("add", "Code", "reverse/functions.csv")
    write("Code/Other.cpp", "int other() { return 3; }\n")        # worktree differs from the index
    tree = git("write-tree")
    staged = gate.gen_asm_offences("HEAD", ":")
    assert staged and any(o.startswith("C3 ") for o in staged)
    assert gate._gen_asm_diff_offences("HEAD", tree) == staged
    assert gate.added_lift_lines("HEAD", tree) == gate.added_lift_lines("HEAD", ":")


def test_a_lift_is_refused_whatever_the_worktree_attributes(repo):
    # passing results are reused by tree: nothing outside the two trees may hide added lines
    git, write, commit, base = repo
    write(".gitattributes", "Code/*.cpp -diff\n")          # untracked: not in either tree
    write("Code/Lift.cpp", "void lift() { __asm { __emit 0x90 } }\n")
    git("add", "Code/Lift.cpp")
    assert gate.added_lift_lines("HEAD", ":")
    assert gate.added_lift_lines(base, commit())


def test_a_refusal_is_never_kept(repo, monkeypatch):
    git, write, commit, base = repo
    wave(write)
    write("Code/Other.cpp", "int other() { return 2; }\n")
    tip = commit()
    calls = counted(monkeypatch)
    for _ in range(2):
        assert check_main(monkeypatch, base, tip) == 1
    assert calls.count("_gen_asm_diff_offences") >= 4                # judged again each time


def test_a_one_commit_push_reuses_pre_commits_results(repo, monkeypatch):
    git, write, commit, base = repo
    write("Code/New.cpp", "int fresh() { return 4; }\n")
    git("add", "Code")
    monkeypatch.setattr(sys, "argv", ["conversion_gate.py", "HEAD", ":"])
    assert gate.main() == 0                                         # pre-commit
    tip = commit()
    calls = counted(monkeypatch)
    assert check_main(monkeypatch, base, tip) == 0                  # the push of that commit
    assert calls == []
    write("Code/New.cpp", "int fresh() { return 5; }\n")
    tip2 = commit()
    assert check_main(monkeypatch, base, tip2) == 0                 # another pair: judged
    assert "added_lift_lines" in calls and "_gen_asm_diff_offences" in calls
