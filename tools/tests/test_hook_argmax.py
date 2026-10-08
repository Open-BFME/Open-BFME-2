"""pre-commit with more staged sources than one Windows command line can hold.

Windows caps a native command line at 32,767 characters. Past roughly 300 staged
sources, `find_declared_unmatched.py --fail --staged <every source>` died with
"Argument list too long" before it had checked anything, and so did the build and
eh_verify calls after it. The hook now hands lists to Python on stdin and runs the
build in bounded chunks. Each case runs the real hook in a throwaway repository:
find_declared_unmatched.py is the real tool, the other checkers are stubs, and
tools/build.py and tools/eh_verify.py record what they were asked to verify.
"""

import json
import os
import re
import shutil
import stat
import subprocess
import sys
from pathlib import Path

import pytest


ROOT = Path(__file__).resolve().parents[2]
HOOK = ROOT / ".githooks" / "pre-commit"
COUNT = 1500
# Everything else pre-commit runs; each passes.
STUBS = ("check_case_collisions", "conversion_gate", "link_debt", "class_gate", "tu_ownership",
         "hatch_counters", "code_identity_gate", "data_check", "ledger_guard", "check_csv",
         "flag_defaults", "pin_consistency", "pin_admission", "header_dependents",
         "name_dependents")
RECORD_BUILD = """import json, sys
with open("build-calls.jsonl", "a", encoding="utf-8") as out:
    out.write(json.dumps(sys.argv[1:]) + "\\n")
"""
RECORD_EH = """import json, sys
sources = list(sys.argv[1:])
if "--sources-from" in sources:
    at = sources.index("--sources-from")
    assert sources[at + 1] == "-", sources
    del sources[at:at + 2]
    sources += [p.decode("utf-8") for p in sys.stdin.buffer.read().split(b"\\0") if p]
with open("eh-calls.jsonl", "a", encoding="utf-8") as out:
    out.write(json.dumps(sources) + "\\n")
"""
# delta_sources.py prints LF-only lines, like the real tool.
DELTA = """import os, sys
sys.stdout.reconfigure(newline="\\n")
if os.path.exists("delta.txt"):
    sys.stdout.write(open("delta.txt", encoding="utf-8").read())
"""


def _bash() -> str:
    """Git-for-Windows Bash, not the WindowsApps WSL shim (as in test_hook_build_dispatch)."""
    candidates = []
    if os.name == "nt":
        git = shutil.which("git")
        if git:
            git_root = Path(git).resolve().parent.parent
            candidates.extend((git_root / "bin/bash.exe", git_root / "usr/bin/bash.exe"))
        program_files = Path(os.environ.get("ProgramFiles", r"C:\Program Files"))
        candidates.extend(
            (program_files / "Git/bin/bash.exe", program_files / "Git/usr/bin/bash.exe")
        )
    discovered = shutil.which("bash")
    if discovered:
        candidates.append(Path(discovered))
    for candidate in candidates:
        if Path(candidate).is_file():
            return str(candidate)
    pytest.skip("Bash is required to exercise the tracked hook")


def git(repo, *args, **kwargs):
    return subprocess.run(["git", *args], cwd=repo, check=True, capture_output=True, **kwargs)


def source(i):
    # Real BFME2 paths run 60-120 characters; 1,500 of these are ~130,000.
    return f"Code/GameEngine/Source/GameLogic/Object/Update/SyntheticUpdateModule{i:04d}.cpp"


def write(repo, path, text):
    target = repo / path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(text.encode("utf-8"))


@pytest.fixture
def repo(tmp_path):
    return make_repo(tmp_path, COUNT)


@pytest.fixture
def small_repo(tmp_path):
    return make_repo(tmp_path, 40)


def make_repo(tmp_path, count):
    if os.name == "nt" and not shutil.which("py"):
        pytest.skip("the hook builds through the py launcher on Windows")
    repo = tmp_path / "repo"
    repo.mkdir()
    git(repo, "init", "-q")
    git(repo, "config", "user.name", "Fixture")
    git(repo, "config", "user.email", "fixture@example.invalid")
    git(repo, "config", "core.autocrlf", "false")
    for tool in STUBS:
        write(repo, f"tools/{tool}.py", "raise SystemExit(0)\n")
    write(repo, "tools/delta_sources.py", DELTA)
    write(repo, "tools/build.py", RECORD_BUILD)
    write(repo, "tools/eh_verify.py", RECORD_EH)
    shutil.copyfile(ROOT / "tools" / "find_declared_unmatched.py",
                    repo / "tools" / "find_declared_unmatched.py")
    write(repo, "build.sh", '#!/usr/bin/env bash\nexec python3 tools/build.py "$@"\n')
    build_sh = repo / "build.sh"
    build_sh.chmod(build_sh.stat().st_mode | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)
    write(repo, "reverse/functions.csv",
          "name,export_rva,target_rva,target_size,source,status,notes\n"
          + "".join(f"?f@C{i:04d}@@QAEXXZ,,0x{0x1000 + 16 * i:08X},16,{source(i)},matched,\n"
                    for i in range(count)))
    write(repo, ".gitignore", "*.jsonl\ndelta.txt\n")
    git(repo, "add", "-A")
    git(repo, "commit", "-qm", "base")
    for i in range(count):
        write(repo, source(i), f"struct C{i:04d} {{ void f(); }};\nvoid C{i:04d}::f() {{}}\n")
    return repo


def stage_and_run(repo):
    git(repo, "add", "Code")
    return subprocess.run([_bash(), str(HOOK)], cwd=repo, capture_output=True, text=True,
                          encoding="utf-8", errors="replace", timeout=900)


def calls(repo, name):
    path = repo / name
    if not path.exists():
        return []
    return [json.loads(line) for line in path.read_text(encoding="utf-8").splitlines()]




def test_clean_commit_of_1500_sources_verifies_every_one_in_bounded_chunks(repo):
    # A delta source with no matched row is dropped before the build. That filter
    # read print()ed lines, whose CR LF on Windows left a CR on every key, so it
    # never removed anything there.
    parked = "Code/GameEngine/Source/Parked.cpp"
    write(repo, "delta.txt", f"{parked}\n{source(0)}\n")
    result = stage_and_run(repo)
    assert result.returncode == 0, result.stderr[-3000:]
    assert "Argument list too long" not in result.stderr
    assert f"PRE-COMMIT OK (ledger integrity + {COUNT} source(s) byte-verified)" in result.stdout
    builds = calls(repo, "build-calls.jsonl")
    assert len(builds) > 1
    assert sorted(s for chunk in builds for s in chunk) == sorted(map(source, range(COUNT)))
    for chunk in builds:
        command = subprocess.list2cmdline(["p" * 1000, "s" * 1000] + chunk)
        assert len(command.encode("utf-16-le")) // 2 < 32767
    # eh_verify aggregates over every row, so it still sees the whole set in one call.
    eh = calls(repo, "eh-calls.jsonl")
    assert len(eh) == 1 and sorted(eh[0]) == sorted(map(source, range(COUNT)))


def test_undeclared_and_unclaimed_definitions_among_1500_are_still_refused(repo):
    bad = source(750)
    write(repo, bad, "struct C0750 { void f(); void g(); };\n"
                     "void C0750::f() {}\nvoid C0750::g() {}\n")
    unclaimed = "Code/GameEngine/Source/GameLogic/Object/Update/UnclaimedDraft.cpp"
    write(repo, unclaimed, "struct Draft { void run(); };\nvoid Draft::run() {}\n")
    result = stage_and_run(repo)
    assert result.returncode == 1
    assert "Argument list too long" not in result.stderr
    assert "staged sources define functions the ledger does not declare" in result.stderr
    report = result.stdout.replace("\\", "/")  # the tool prints native paths
    assert f"{bad}: C0750::g" in report
    assert f"{unclaimed}: ZERO matched functions.csv rows" in report
    assert f"{unclaimed}: Draft::run" in report
    assert "C0749::f" not in report
    assert not calls(repo, "build-calls.jsonl")


def test_a_staged_source_with_unstaged_edits_is_refused(small_repo):
    git(small_repo, "add", "Code")
    (small_repo / source(7)).write_text("// not what was staged\n")
    result = subprocess.run([_bash(), str(HOOK)], cwd=small_repo, capture_output=True,
                            text=True, encoding="utf-8", errors="replace", timeout=900)
    assert result.returncode == 1
    assert f"unstaged edits in: {source(7)}" in result.stderr
    assert source(8) not in result.stderr
    assert not calls(small_repo, "build-calls.jsonl")


def run_tool(repo, args, stdin=None):
    return subprocess.run([sys.executable, "tools/find_declared_unmatched.py", *args], cwd=repo,
                          input=stdin, capture_output=True)


@pytest.mark.parametrize("separator", [b"\0", b"\n", b"\r\n"])
def test_paths_from_stdin_reports_exactly_what_arguments_do(small_repo, separator):
    write(small_repo, source(3), "struct C0003 { void f(); void g(); };\n"
                                 "void C0003::f() {}\nvoid C0003::g() {}\n")
    orphan = "Code/GameEngine/Source/Orphan.cpp"
    write(small_repo, orphan, "struct O { void o(); };\nvoid O::o() {}\n")
    paths = [source(i) for i in range(40)] + [orphan]
    git(small_repo, "add", "Code")
    by_argv = run_tool(small_repo, ["--fail", "--staged", *paths])
    by_stdin = run_tool(small_repo, ["--fail", "--staged", "--paths-from", "-"],
                        stdin=separator.join(p.encode() for p in paths) + separator)
    assert by_argv.returncode == by_stdin.returncode == 1
    assert by_stdin.stdout == by_argv.stdout
    assert b"Orphan.cpp: ZERO matched" in by_stdin.stdout and b"C0003::g" in by_stdin.stdout


def test_an_empty_paths_from_list_inspects_nothing(small_repo):
    done = run_tool(small_repo, ["--fail", "--staged", "--paths-from", "-"], stdin=b"")
    assert done.returncode == 0
    assert done.stdout.strip() == b"All defined functions are already matched."


def test_eh_verify_reads_a_source_list_as_it_reads_arguments(tmp_path, monkeypatch):
    sys.path.insert(0, str(ROOT / "tools"))
    import eh_verify
    seen = []
    monkeypatch.setattr(eh_verify, "row_rows", lambda sources: seen.append(sources) or [])
    monkeypatch.setattr(eh_verify, "verify", lambda rows, objdir=None: ({}, 0))
    sources = ["Code/a b.cpp", "Code/c.cpp"]
    listing = tmp_path / "sources"
    listing.write_bytes(b"\0".join(s.encode() for s in sources) + b"\0")
    assert eh_verify.main(sources) == eh_verify.main(["--sources-from", str(listing)]) == 0
    assert seen[0] == seen[1] == set(sources)


def _definition(hook, name):
    match = re.search(rf"(?ms)^{name}\(\) \{{\n.*?^\}}\n", hook.read_text(encoding="utf-8"))
    assert match, f"{hook.name} has no {name} function"
    return match.group(0)


@pytest.mark.parametrize("hook", [HOOK, ROOT / ".githooks" / "pre-push"], ids=lambda p: p.name)
@pytest.mark.parametrize("fail_at", [0, 2])
def test_build_chunks_passes_every_selector_once_and_stops_at_a_failure(tmp_path, hook, fail_at):
    # pre-push split at a fixed 200 sources, which overflows once paths average ~160
    # characters; both hooks now bound each build's arguments by size.
    selectors = [f"Code/GameEngine/Source/{'Deep/' * 20}Unit {i:04d}.cpp" for i in range(3000)]
    (tmp_path / "selectors").write_bytes(b"\0".join(s.encode() for s in selectors) + b"\0")
    harness = f"""set -euo pipefail
fail() {{ echo "FAILED: $*" >&2; exit 1; }}
n=0
run_build() {{
    n=$((n + 1))
    printf '%s\\0' "$@" > "calls.$n"
    printf '%s\\n' "$BUILD_POOL" > "pool.$n"
    [ "$n" -ne {fail_at} ]
}}
{_definition(hook, "measure_argument")}
{_definition(hook, "build_chunks")}
mapfile -d '' -t selectors < selectors
build_chunks "byte-verify (see above)" "${{selectors[@]}}"
echo DONE
"""
    done = subprocess.run([_bash(), "--noprofile", "--norc"], cwd=tmp_path, input=harness,
                          text=True, capture_output=True)
    calls = sorted(tmp_path.glob("calls.*"), key=lambda p: int(p.suffix[1:]))
    chunks = [p.read_bytes().split(b"\0")[:-1] for p in calls]
    for chunk in chunks:
        command = subprocess.list2cmdline(["p" * 1000, "s" * 1000] + [c.decode() for c in chunk])
        assert len(command.encode("utf-16-le")) // 2 < 32767
    assert all(p.read_text().strip() == "4" for p in tmp_path.glob("pool.*"))
    if fail_at:
        assert done.returncode == 1 and "FAILED: byte-verify (see above)" in done.stderr
        assert len(chunks) == fail_at and "DONE" not in done.stdout
    else:
        assert done.returncode == 0, done.stderr
        assert len(chunks) > 1
        assert [c.decode() for chunk in chunks for c in chunk] == selectors


def test_a_staged_tool_with_a_syntax_error_is_refused(small_repo):
    # The staged-tool syntax check reads its list on stdin now too.
    write(small_repo, "tools/ok_tool.py", "x = 1\n")
    write(small_repo, "tools/broken tool.py", "def f(:\n")
    git(small_repo, "add", "tools")
    result = subprocess.run([_bash(), str(HOOK)], cwd=small_repo, capture_output=True,
                            text=True, encoding="utf-8", errors="replace", timeout=900)
    assert result.returncode == 1
    assert "python syntax error in a staged tool" in result.stderr
    assert "tools/broken tool.py:1:" in result.stderr
    assert "ok_tool" not in result.stderr
