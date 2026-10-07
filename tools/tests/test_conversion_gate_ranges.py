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
