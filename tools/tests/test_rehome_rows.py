"""Rehoming requires exact bodies, successful admission, and source removal."""
import csv
import subprocess
import sys
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import rehome_rows


class RehomeVerificationTests(unittest.TestCase):
    def verify(self, *, returncode=0, stdout="Functions: OK 1/1 matched", emitted=b"retail", unresolved=()):
        def native_run(command, **kwargs):
            # A Windows process cannot execute the Bash build.sh entry point.
            if command[0].endswith(".sh") or command[0] == "python3":
                raise OSError("not a native executable")
            self.assertEqual(command[0], sys.executable)
            self.assertEqual(Path(command[1]).name, "build.py")
            return SimpleNamespace(returncode=returncode, stdout=stdout)

        with (patch.object(rehome_rows.sys, "platform", "win32"),
              patch.object(rehome_rows.subprocess, "run", side_effect=native_run),
              patch.object(rehome_rows, "_SYMBOLS", {}),
              patch.object(rehome_rows.build, "obj_path", return_value=Path("home.obj")),
              patch.object(rehome_rows.build, "compile_function", return_value={
                  "bytes": emitted, "target": b"retail", "unresolved": unresolved
              }) as compile_body):
            accepted = rehome_rows.all_exact([{"name": "body"}], "Code/Home.cpp")
            return accepted, compile_body.call_count

    def test_native_windows_gate_accepts_only_exact_body(self):
        self.assertEqual(self.verify(), (True, 1))
        self.assertEqual(self.verify(emitted=b"different"), (False, 1))
        self.assertEqual(self.verify(unresolved=("missing",)), (False, 1))

    def test_failed_gate_never_checks_or_rehomes_old_object(self):
        self.assertEqual(self.verify(returncode=1), (False, 0))

    def test_empty_success_output_is_not_gate_proof(self):
        self.assertEqual(self.verify(stdout=""), (False, 0))


def git(root, *args):
    return subprocess.run(["git", *args], cwd=root, capture_output=True,
                          text=True, check=True).stdout.strip()


def write_rows(root, rows):
    with (root / "reverse/functions.csv").open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=rows[0].keys())
        writer.writeheader()
        writer.writerows(rows)


def read_rows(root):
    with (root / "reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
        return list(csv.DictReader(handle))


@pytest.fixture
def project(tmp_path, monkeypatch):
    # A hook can export its own Git paths. Keep all fixture Git operations in
    # this disposable repository, including the real git rm in main().
    for name in (
        "GIT_DIR", "GIT_WORK_TREE", "GIT_COMMON_DIR", "GIT_INDEX_FILE",
        "GIT_OBJECT_DIRECTORY", "GIT_ALTERNATE_OBJECT_DIRECTORIES",
        "GIT_GRAFT_FILE", "GIT_SHALLOW_FILE", "GIT_PREFIX",
        "GIT_INTERNAL_SUPER_PREFIX", "GIT_IMPLICIT_WORK_TREE",
        "GIT_CEILING_DIRECTORIES",
    ):
        monkeypatch.delenv(name, raising=False)
    root = tmp_path / "project with spaces"
    (root / "Code").mkdir(parents=True)
    (root / "reverse").mkdir()
    split, home = "Code/Split.cpp", "Code/Home.cpp"
    other_split, other_home = "Code/OtherSplit.cpp", "Code/OtherHome.cpp"
    rows = [
        {"name": name, "target_rva": hex(4096 + index * 16), "target_size": "16",
         "source": source, "notes": ""}
        for index, (name, source) in enumerate((
            ("first", split), ("second", split), ("independent", other_split)))
    ]
    for source in (split, home, other_split, other_home):
        (root / source).write_text(f"// original {source}\n", encoding="utf-8")
    write_rows(root, rows)
    git(root, "init", "-q")
    git(root, "add", "--", split, home, other_split, other_home, "reverse/functions.csv")
    git(root, "-c", "user.name=Rehome fixture", "-c", "user.email=fixture@example.invalid",
        "commit", "-qm", "rehome fixture")

    def admit(command):
        # Simulate only add_match's expensive verified-admission boundary and
        # its persistent ledger/source effects. Source removal uses real Git.
        name, destination = command[2], command[5]
        current = read_rows(root)
        for row in current:
            if row["name"] == name:
                row["source"] = destination
        write_rows(root, current)
        with (root / destination).open("a", encoding="utf-8") as handle:
            handle.write(f"// admitted {name}\n")
        return subprocess.CompletedProcess(command, 0, "add_match: verified OK\n", "")

    return SimpleNamespace(
        root=root, split=split, home=home, other_split=other_split, other_home=other_home,
        candidates=[(split, home, rows[:2]), (other_split, other_home, rows[2:])], admit=admit,
    )


def run_main(project, monkeypatch, *, admit=None, candidates=None, argv=None, exact=True):
    actual_run = subprocess.run
    admitted, removals = [], []

    def run(command, **kwargs):
        assert kwargs["cwd"] == project.root
        if command[:2] == [sys.executable, "tools/add_match.py"]:
            assert "--replace-existing" in command
            admitted.append(command[2])
            return (admit or project.admit)(command)
        assert command[:2] == ["git", "rm"]
        assert "-f" not in command and "--force" not in command
        removals.append(command)
        return actual_run(command, **kwargs)

    with monkeypatch.context() as context:
        context.setattr(rehome_rows, "ROOT", project.root)
        context.setattr(rehome_rows.claims, "owner", lambda: "fixture")
        context.setattr(rehome_rows.claims, "active", lambda: {})
        context.setattr(rehome_rows, "candidates", lambda: (
            project.candidates[:1] if candidates is None else candidates))
        context.setattr(rehome_rows, "all_exact", lambda rows, home: exact)
        context.setattr(rehome_rows.subprocess, "run", run)
        code = rehome_rows.main(["--apply"] if argv is None else argv)
    return code, admitted, removals


def test_git_refuses_local_edits_without_reporting_a_move(project, monkeypatch, capfd):
    split = project.root / project.split
    local_edits = split.read_text(encoding="utf-8") + "// unrelated local work\n"
    split.write_text(local_edits, encoding="utf-8")

    code, admitted, removals = run_main(project, monkeypatch)
    out, err = capfd.readouterr()

    assert code == 1, (out, err)
    assert admitted == ["first", "second"] and len(removals) == 1
    assert split.read_text(encoding="utf-8") == local_edits
    assert git(project.root, "ls-files", "--", project.split) == project.split
    assert [row["source"] for row in read_rows(project.root)[:2]] == [project.home] * 2
    assert "// admitted second" in (project.root / project.home).read_text(encoding="utf-8")
    assert "git rm failed (exit 1)" in err
    assert "local modifications" in err
    assert "review" in err.lower() and "ledger" in err.lower()
    assert "MOVED" not in out
    assert "0 unit(s) moved; 1 failed" in out


def test_successful_removal_is_counted(project, monkeypatch, capfd):
    code, admitted, removals = run_main(project, monkeypatch)
    out, err = capfd.readouterr()

    assert code == 0 and not err
    assert admitted == ["first", "second"] and len(removals) == 1
    assert not (project.root / project.split).exists()
    assert git(project.root, "diff", "--cached", "--name-status", "--", project.split) == (
        "D\t" + project.split)
    assert "MOVED   " + project.split in out
    assert "1 unit(s) moved" in out


@pytest.mark.skipif(sys.platform != "win32", reason="Windows index replacement sharing semantics")
def test_failed_index_replacement_can_leave_source_removed(project, monkeypatch, capfd):
    import ctypes
    from ctypes import wintypes

    kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)
    create_file = kernel32.CreateFileW
    create_file.argtypes = [wintypes.LPCWSTR, wintypes.DWORD, wintypes.DWORD,
                           wintypes.LPVOID, wintypes.DWORD, wintypes.DWORD, wintypes.HANDLE]
    create_file.restype = wintypes.HANDLE
    close_handle = kernel32.CloseHandle
    close_handle.argtypes = [wintypes.HANDLE]
    close_handle.restype = wintypes.BOOL
    # Allow index reads/writes but deny replacement until the handle closes.
    # Git can remove the clean source before failing to replace this index.
    handle = create_file(str(project.root / ".git/index"), 0x80000000,
                         0x1 | 0x2, None, 3, 0x80, None)
    assert handle != wintypes.HANDLE(-1).value, ctypes.get_last_error()
    actual_run = subprocess.run

    def bounded_run(command, **kwargs):
        # Some Git for Windows versions ask whether to retry index replacement.
        return actual_run(command, input="n\n" * 20, timeout=20, **kwargs)

    monkeypatch.setattr(subprocess, "run", bounded_run)
    try:
        code, admitted, removals = run_main(project, monkeypatch)
    finally:
        assert close_handle(handle)
    out, err = capfd.readouterr()

    assert code == 1 and admitted == ["first", "second"] and len(removals) == 1
    assert not (project.root / project.split).exists()
    assert git(project.root, "ls-files", "--", project.split) == project.split
    assert [row["source"] for row in read_rows(project.root)[:2]] == [project.home] * 2
    assert "// admitted second" in (project.root / project.home).read_text(encoding="utf-8")
    assert "git rm failed (exit 128)" in err
    assert "unit kept" not in err
    assert "worktree" in err and "index" in err
    assert "MOVED" not in out
    assert "0 unit(s) moved; 1 failed" in out


def test_failed_removal_does_not_block_independent_unit(project, monkeypatch, capfd):
    split = project.root / project.split
    local_edits = split.read_text(encoding="utf-8") + "// unrelated local work\n"
    split.write_text(local_edits, encoding="utf-8")

    code, admitted, removals = run_main(
        project, monkeypatch, candidates=project.candidates, argv=["--apply", "--limit", "1"])
    out, err = capfd.readouterr()

    assert code == 1
    assert admitted == ["first", "second", "independent"] and len(removals) == 2
    assert split.read_text(encoding="utf-8") == local_edits
    assert not (project.root / project.other_split).exists()
    assert "git rm failed (exit 1)" in err
    assert "MOVED   " + project.split not in out
    assert "MOVED   " + project.other_split in out
    assert "1 unit(s) moved; 1 failed" in out


def test_nonzero_admission_after_success_marker_keeps_partial_edits(project, monkeypatch, capfd):
    def failed_after_verification(command):
        result = project.admit(command)
        result.returncode = 1
        result.stderr = "could not record landing\n"
        return result

    code, admitted, removals = run_main(project, monkeypatch, admit=failed_after_verification)
    out, err = capfd.readouterr()

    assert code == 1
    assert admitted == ["first"] and not removals
    assert (project.root / project.split).exists()
    assert [row["source"] for row in read_rows(project.root)[:2]] == [project.home, project.split]
    assert "// admitted first" in (project.root / project.home).read_text(encoding="utf-8")
    assert "could not record landing" in err and "exit 1" in err
    assert "review" in err.lower() and "ledger" in err.lower()
    assert "MOVED" not in out
    assert "0 unit(s) moved; 1 failed" in out


def test_later_admission_failure_preserves_rows_and_continues_independent_unit(
        project, monkeypatch, capfd):
    def fail_second(command):
        if command[2] == "second":
            return subprocess.CompletedProcess(command, 1, "", "verification failed\n")
        return project.admit(command)

    code, admitted, removals = run_main(
        project, monkeypatch, admit=fail_second, candidates=project.candidates,
        argv=["--apply", "--limit", "1"])
    out, err = capfd.readouterr()

    assert code == 1
    assert admitted == ["first", "second", "independent"] and len(removals) == 1
    assert (project.root / project.split).exists()
    assert not (project.root / project.other_split).exists()
    assert [row["source"] for row in read_rows(project.root)] == [
        project.home, project.split, project.other_home]
    assert "verification failed" in err
    assert "MOVED   " + project.split not in out
    assert "MOVED   " + project.other_split in out
    assert "1 unit(s) moved; 1 failed" in out


def test_remaining_ledger_row_reports_incomplete_move(project, monkeypatch, capfd):
    def leave_second_row(command):
        if command[2] == "second":
            return subprocess.CompletedProcess(command, 0, "verified OK\n", "")
        return project.admit(command)

    code, admitted, removals = run_main(project, monkeypatch, admit=leave_second_row)
    out, err = capfd.readouterr()

    assert code == 1 and not removals
    assert admitted == ["first", "second"]
    assert (project.root / project.split).exists()
    assert [row["source"] for row in read_rows(project.root)[:2]] == [project.home, project.split]
    assert "PARTIAL" in err and "1 row(s)" in err
    assert "review" in err.lower() and "ledger" in err.lower()
    assert "MOVED" not in out
    assert "0 unit(s) moved; 1 failed" in out


def test_zero_exit_without_admission_marker_is_not_success(project, monkeypatch, capfd):
    def unverified(command):
        return subprocess.CompletedProcess(command, 0, "no verification performed\n", "")

    code, admitted, removals = run_main(project, monkeypatch, admit=unverified)
    out, err = capfd.readouterr()

    assert code == 1 and admitted == ["first"] and not removals
    assert not git(project.root, "status", "--porcelain")
    assert "no verification performed" in err
    assert "0 unit(s) moved; 1 failed" in out


@pytest.mark.parametrize("exact, expected", [(True, "1 unit(s) movable"), (False, "0 unit(s) movable")])
def test_dry_run_never_admits_or_removes(project, monkeypatch, capfd, exact, expected):
    code, admitted, removals = run_main(project, monkeypatch, argv=[], exact=exact)
    out, err = capfd.readouterr()

    assert code == 0 and not admitted and not removals and not err
    assert not git(project.root, "status", "--porcelain")
    assert expected in out


if __name__ == "__main__":
    unittest.main()
