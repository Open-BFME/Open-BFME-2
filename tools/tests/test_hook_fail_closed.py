"""A lister that fails must stop the hook, not shrink what it verifies.

Both hooks read their lists through `< <(cmd)` or `mapfile < <(cmd)`, which drop the
producer's exit status: a delta_sources.py that crashed, or a `git diff` that could not
read the index, looked exactly like "nothing to verify" and the commit or push went
through. Each case runs the real hook in a throwaway repository with stub checkers;
tools/build.py records what it was asked to verify.
"""

import json
import os
import shutil
import stat
import subprocess
from pathlib import Path

import pytest


ROOT = Path(__file__).resolve().parents[2]
SOURCE = "Code/GameEngine/Source/Common/Unit.cpp"
STUBS = ("check_case_collisions", "conversion_gate", "link_debt", "class_gate", "tu_ownership",
         "hatch_counters", "code_identity_gate", "data_check", "ledger_guard", "check_csv",
         "flag_defaults", "flag_delta_sources", "pin_consistency", "pin_admission", "header_dependents")
# These read their list on stdin; drain it as the real tools do.
READERS = ("eh_verify", "find_declared_unmatched", "link_check")
RECORD_BUILD = """import json, sys
with open("build-calls.jsonl", "a", encoding="utf-8") as out:
    out.write(json.dumps(sys.argv[1:]) + "\\n")
"""
# Prints delta.txt like the real tool (LF only), then exits with delta-exit's code.
DELTA = """import os, sys
sys.stdout.reconfigure(newline="\\n")
if os.path.exists("delta.txt"):
    sys.stdout.write(open("delta.txt", encoding="utf-8").read())
sys.stdout.flush()
sys.exit(int(open("delta-exit").read()) if os.path.exists("delta-exit") else 0)
"""
# name_dependents.py, the same way: prints name-deps.txt, exits with name-deps-exit's code.
NAME_DEPS = DELTA.replace("delta", "name-deps")
LEDGER = ("name,export_rva,target_rva,target_size,source,status,notes\n"
          f"?f@Unit@@QAEXXZ,,0x00001000,16,{SOURCE},matched,{{note}}\n")


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
    pytest.skip("Bash is required to exercise the tracked hooks")


def git(repo, *args):
    return subprocess.run(["git", *args], cwd=repo, check=True, capture_output=True,
                          text=True).stdout.strip()


def write(repo, path, text):
    target = repo / path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(text.encode("utf-8"))


@pytest.fixture
def repo(tmp_path):
    if os.name == "nt" and not shutil.which("py"):
        pytest.skip("the hooks build through the py launcher on Windows")
    repo = tmp_path / "repo"
    repo.mkdir()
    git(repo, "init", "-q")
    git(repo, "config", "user.name", "Fixture")
    git(repo, "config", "user.email", "fixture@example.invalid")
    git(repo, "config", "core.autocrlf", "false")
    for tool in STUBS:
        write(repo, f"tools/{tool}.py", "raise SystemExit(0)\n")
    for tool in READERS:
        write(repo, f"tools/{tool}.py", "import sys\nsys.stdin.buffer.read()\n")
    # data_check --converged reads its source list on stdin: drain it, as the tool does,
    # or the hook's printf takes SIGPIPE and pipefail fails the step.
    write(repo, "tools/data_check.py", "import sys\nif '-' in sys.argv:\n    sys.stdin.buffer.read()\n")
    write(repo, "tools/delta_sources.py", DELTA)
    write(repo, "tools/name_dependents.py", NAME_DEPS)
    write(repo, "tools/build.py", RECORD_BUILD)
    write(repo, "build.sh", '#!/usr/bin/env bash\nexec python3 tools/build.py "$@"\n')
    build_sh = repo / "build.sh"
    build_sh.chmod(build_sh.stat().st_mode | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)
    write(repo, "reverse/functions.csv", LEDGER.format(note=""))
    write(repo, SOURCE, "struct Unit { void f(); };\nvoid Unit::f() {}\n")
    write(repo, ".gitignore", "*.jsonl\ndelta.txt\ndelta-exit\nname-deps.txt\nname-deps-exit\nbad-index\n")
    git(repo, "add", "-A")
    git(repo, "commit", "-qm", "base")
    return repo


def run(repo, hook, refs="", env=None):
    return subprocess.run([_bash(), str(ROOT / ".githooks" / hook)], cwd=repo, input=refs,
                          capture_output=True, text=True, encoding="utf-8", errors="replace",
                          env=dict(os.environ, **(env or {})), timeout=600)


def built(repo):
    path = repo / "build-calls.jsonl"
    if not path.exists():
        return set()
    return {s for line in path.read_text(encoding="utf-8").splitlines() for s in json.loads(line)}


def ledger_only_commit(repo):
    """A row edit with no source change: only delta_sources names the TU to verify."""
    write(repo, "reverse/functions.csv", LEDGER.format(note="re-anchored"))
    git(repo, "add", "reverse/functions.csv")


# ---------------------------------------------------------------- pre-commit

def test_pre_commit_verifies_what_delta_sources_names(repo):
    ledger_only_commit(repo)
    write(repo, "delta.txt", SOURCE + "\n")
    result = run(repo, "pre-commit")
    assert result.returncode == 0, result.stderr
    assert built(repo) == {SOURCE}


def test_pre_commit_refuses_when_delta_sources_crashes(repo):
    # Positive control: before, the crash read as an empty delta and the commit passed
    # with nothing byte-verified.
    ledger_only_commit(repo)
    write(repo, "delta.txt", SOURCE + "\n")
    write(repo, "delta-exit", "3")
    result = run(repo, "pre-commit")
    assert result.returncode == 1
    assert "PRE-COMMIT FAILED: delta_sources (see above)" in result.stderr
    assert not built(repo)


def test_pre_commit_refuses_when_git_cannot_list_the_index(repo):
    # Before, every `git diff --cached` listing came back empty and the hook took
    # its early exit: a commit with sources passed with nothing checked.
    write(repo, SOURCE, "struct Unit { void f(); };\nvoid Unit::f() { int x = 0; }\n")
    git(repo, "add", SOURCE)
    write(repo, "bad-index", "not an index\n")
    result = run(repo, "pre-commit", env={"GIT_INDEX_FILE": str(repo / "bad-index")})
    assert result.returncode == 1
    # the lessons ban's listing is the first: through a pipe its failure read as "no
    # lessons.md" and the hook went on to the next listing
    assert "PRE-COMMIT FAILED: listing staged files (see above)" in result.stderr
    assert not built(repo)


# ---------------------------------------------------------------- pre-push

def push_refs(repo, base):
    return f"refs/heads/main {git(repo, 'rev-parse', 'HEAD')} refs/heads/main {base}\n"


def test_pre_push_verifies_delta_and_edited_sources(repo):
    base = git(repo, "rev-parse", "HEAD")
    write(repo, SOURCE, "struct Unit { void f(); };\nvoid Unit::f() { int x = 0; }\n")
    git(repo, "commit", "-qam", "edit")
    result = run(repo, "pre-push", push_refs(repo, base))
    assert result.returncode == 0, result.stderr
    assert "PRE-PUSH OK (1 outgoing source(s) byte-verified)" in result.stdout
    assert built(repo) == {SOURCE}


def test_pre_push_refuses_when_delta_sources_crashes(repo):
    # Positive control: before, mapfile read the crash as "nothing to verify" and the
    # ledger-only push went out with 0 sources byte-verified.
    base = git(repo, "rev-parse", "HEAD")
    ledger_only_commit(repo)
    git(repo, "commit", "-qm", "row")
    write(repo, "delta-exit", "3")
    result = run(repo, "pre-push", push_refs(repo, base))
    assert result.returncode == 1
    assert "PRE-PUSH FAILED: delta_sources (see above)" in result.stderr
    assert not built(repo)


def test_pre_push_refuses_when_the_edited_source_list_cannot_be_built(repo):
    # The pushed commit's ledger is unreadable, so the edited-source lister dies;
    # before, that read as "no edited sources" and the edit went out unverified.
    base = git(repo, "rev-parse", "HEAD")
    write(repo, SOURCE, "struct Unit { void f(); };\nvoid Unit::f() { int x = 0; }\n")
    git(repo, "rm", "-q", "--cached", "reverse/functions.csv")
    git(repo, "commit", "-qam", "edit without a ledger")
    result = run(repo, "pre-push", push_refs(repo, base))
    assert result.returncode == 1
    assert "PRE-PUSH FAILED: listing the edited claimed sources (see above)" in result.stderr
    assert not built(repo)


# ---------------------------------------------------------------- name_dependents

def test_pre_commit_refuses_when_name_dependents_crashes(repo):
    # The units calling a renamed name are listed by tools/name_dependents.py; a crash
    # there must not read as "no unit calls it".
    ledger_only_commit(repo)
    write(repo, "name-deps.txt", SOURCE + "\n")
    write(repo, "name-deps-exit", "3")
    result = run(repo, "pre-commit")
    assert result.returncode == 1
    assert ("PRE-COMMIT FAILED: listing the units that call a renamed or removed name "
            "(see above)") in result.stderr
    assert not built(repo)


def test_pre_push_refuses_when_name_dependents_crashes(repo):
    base = git(repo, "rev-parse", "HEAD")
    ledger_only_commit(repo)
    git(repo, "commit", "-qm", "row")
    write(repo, "name-deps.txt", SOURCE + "\n")
    write(repo, "name-deps-exit", "3")
    result = run(repo, "pre-push", push_refs(repo, base))
    assert result.returncode == 1
    assert ("PRE-PUSH FAILED: listing the units that call a renamed or removed name "
            "(see above)") in result.stderr
    assert not built(repo)


# ---------------------------------------------------------------- pre-push: converged data check
# The judged objects are built from the working tree, so it must be the pushed
# commit; and a source a pushed header reaches is byte-verified before its
# relocations are read (GPT-6.1-Sol, converged gate review round 2).
RECORD_CONVERGED = """import csv, json, sys
srcs = [p.decode() for p in sys.stdin.buffer.read().split(b"\\0") if p] if "-" in sys.argv else []
if "--print-claimed" in sys.argv:          # as data_check.claimed_sources: matched rows own a source
    claimed = {r["source"] for r in csv.DictReader(open("reverse/functions.csv")) if r["status"] == "matched"}
    try:
        claimed |= {r["source"] for r in csv.DictReader(open("reverse/data_rows.csv")) if r["status"] == "matched"}
    except FileNotFoundError:
        pass
    sys.stdout.buffer.write(b"".join(s.encode() + b"\\0" for s in srcs if s in claimed))
    sys.exit(0)
with open("conv-calls.jsonl", "a", encoding="utf-8") as out:
    out.write(json.dumps({"argv": sys.argv[1:], "sources": srcs}) + "\\n")
"""
PARKED = "Code/GameEngine/Source/Common/Parked.cpp"   # a draft with no row
HEADER_DEPS = """import sys
sys.stdout.reconfigure(newline="\\n")
if "--range" in sys.argv:
    print(%r)
    print(%r)
""" % (SOURCE, PARKED)


def header_push(repo):
    """A pushed header change that reaches SOURCE (header_dependents --range)."""
    write(repo, "tools/data_check.py", RECORD_CONVERGED)
    write(repo, "tools/header_dependents.py", HEADER_DEPS)
    write(repo, "Code/GameEngine/Include/Shared.h", "struct Shared {};\n")
    write(repo, PARKED, "// a parked draft: no row\n")
    git(repo, "add", "-A")
    git(repo, "commit", "-qm", "stubs and header")
    base = git(repo, "rev-parse", "HEAD")
    write(repo, "Code/GameEngine/Include/Shared.h", "struct Shared { int m; };\n")
    git(repo, "commit", "-qam", "header")
    return base


def test_pre_push_byte_verifies_and_judges_what_a_header_reaches(repo):
    base = header_push(repo)
    result = run(repo, "pre-push", push_refs(repo, base))
    assert result.returncode == 0, result.stderr
    assert SOURCE in built(repo)                                      # byte-verified first
    assert PARKED not in built(repo)                                  # review round 3: no row, not built
    calls = [json.loads(line) for line in (repo / "conv-calls.jsonl").read_text(encoding="utf-8").splitlines()]
    judged = [c for c in calls if "--converged" in c["argv"]]
    assert judged and SOURCE in judged[-1]["sources"] and "--converged-base" in judged[-1]["argv"]
    assert PARKED not in judged[-1]["sources"]


def test_pre_push_builds_the_pushed_commit_not_head(repo):
    """Review round 3: sources were bound to HEAD, so pushing an older commit
    built and judged the newer body."""
    base = git(repo, "rev-parse", "HEAD")
    write(repo, SOURCE, "struct Unit { void f(); };\nvoid Unit::f() { int pushed = 1; }\n")
    git(repo, "commit", "-qam", "pushed")
    pushed = git(repo, "rev-parse", "HEAD")
    write(repo, SOURCE, "struct Unit { void f(); };\nvoid Unit::f() { int later = 2; }\n")
    git(repo, "commit", "-qam", "later, not pushed")
    refs = f"refs/heads/main {pushed} refs/heads/main {base}\n"
    result = run(repo, "pre-push", refs)
    assert result.returncode == 1 and "differs from" in result.stderr and not built(repo)
    git(repo, "checkout", pushed, "--", SOURCE)                       # the pushed body on disk: control
    result = run(repo, "pre-push", refs)
    assert result.returncode == 0, result.stderr
    assert built(repo) == {SOURCE}


def test_pre_push_refuses_a_header_on_disk_unlike_the_pushed_commit(repo):
    base = header_push(repo)
    write(repo, "Code/GameEngine/Include/Shared.h", "struct Shared {};\n")    # restored on disk only
    result = run(repo, "pre-push", push_refs(repo, base))
    assert result.returncode == 1
    assert "differs from" in result.stderr and not built(repo)


# A unit owning only a data row: header_dependents (the real selector) must name it,
# and both hooks byte-verify and judge it (GPT-6.1-Sol, converged gate round 4).
DATA_ONLY = "Code/GameEngine/Source/Common/DataOnly.cpp"
INIT_H = "Code/GameEngine/Source/Common/Init.h"


def data_only_setup(repo):
    shutil.copyfile(ROOT / "tools" / "header_dependents.py", repo / "tools" / "header_dependents.py")
    write(repo, "tools/data_check.py", RECORD_CONVERGED)
    write(repo, INIT_H, "#define INIT 1\n")
    write(repo, DATA_ONLY, '#include "Init.h"\nint g_init = INIT;\n')
    write(repo, "reverse/data_rows.csv", "name,address,address_kind,size,section,source,status,evidence,model\n"
          f"?g_init@@3HA,0x009E0000,rva,4,.data,{DATA_ONLY},matched,e,m\n")
    git(repo, "add", "-A")
    git(repo, "commit", "-qm", "a data-only unit")


def judged_sources(repo):
    path = repo / "conv-calls.jsonl"
    calls = [json.loads(line) for line in path.read_text(encoding="utf-8").splitlines()] if path.exists() else []
    return {s for c in calls if "--converged" in c["argv"] for s in c["sources"]}


def test_pre_commit_verifies_a_data_only_unit_a_header_reaches(repo):
    data_only_setup(repo)
    write(repo, INIT_H, "#define INIT 2\n")
    git(repo, "add", INIT_H)
    result = run(repo, "pre-commit")
    assert result.returncode == 0, result.stderr
    assert DATA_ONLY in built(repo) and DATA_ONLY in judged_sources(repo)


def test_pre_push_verifies_a_data_only_unit_a_header_reaches(repo):
    data_only_setup(repo)
    base = git(repo, "rev-parse", "HEAD")
    write(repo, INIT_H, "#define INIT 2\n")
    git(repo, "commit", "-qam", "header")
    result = run(repo, "pre-push", push_refs(repo, base))
    assert result.returncode == 0, result.stderr
    assert DATA_ONLY in built(repo) and DATA_ONLY in judged_sources(repo)


def test_hooks_refuse_a_ledger_tracked_under_another_case(repo):
    """reverse/Data_Rows.csv: a case-insensitive file system serves it to the build as
    the data ledger while every exact lookup in the hooks misses it, so a ledger-only
    or source-only change verified nothing (GPT-6.1-Sol, converged gate round 7)."""
    shutil.copyfile(ROOT / "tools" / "check_case_collisions.py", repo / "tools" / "check_case_collisions.py")
    git(repo, "add", "tools/check_case_collisions.py")
    git(repo, "commit", "-qm", "the real case checker")
    base = git(repo, "rev-parse", "HEAD")
    blob = repo / "blob.tmp"
    blob.write_text("name,address,address_kind,size,section,source,status,evidence,model\n"
                    f"?g@@3HA,0x009E0000,rva,4,.data,{SOURCE},matched,e,m\n", encoding="utf-8")
    sha = git(repo, "hash-object", "-w", str(blob))
    git(repo, "update-index", "--add", "--cacheinfo", f"100644,{sha},reverse/Data_Rows.csv")
    result = run(repo, "pre-commit")
    assert result.returncode == 1 and "rename to reverse/data_rows.csv" in result.stderr and not built(repo)
    git(repo, "commit", "-qm", "variant ledger")                     # as made with the hook bypassed
    result = run(repo, "pre-push", push_refs(repo, base))
    assert result.returncode == 1 and "rename to reverse/data_rows.csv" in result.stderr and not built(repo)


@pytest.mark.parametrize("in_base", [True, False])
@pytest.mark.parametrize("variant", ["reverse/Gate_Baseline.txt", "Reverse/gate_baseline.txt"])
def test_hooks_refuse_a_register_renamed_by_case(repo, variant, in_base):
    """A gate baseline renamed by case escaped its shrink-only check, and the build
    still read it on Windows (GPT-6.1-Sol, converged gate round 8) -- also when no
    base holds the register at all (round 9)."""
    shutil.copyfile(ROOT / "tools" / "check_case_collisions.py", repo / "tools" / "check_case_collisions.py")
    git(repo, "add", "tools/check_case_collisions.py")
    if in_base:
        write(repo, "reverse/gate_baseline.txt", "# baseline\n")
        git(repo, "add", "reverse/gate_baseline.txt")
    git(repo, "commit", "-qm", "the real case checker" + (" and a register" if in_base else ""))
    base = git(repo, "rev-parse", "HEAD")
    blob = repo / "blob.tmp"
    blob.write_text("# baseline\nstrnul 0x00001000 _f\n", encoding="utf-8")
    sha = git(repo, "hash-object", "-w", str(blob))
    if in_base:
        git(repo, "update-index", "--force-remove", "reverse/gate_baseline.txt")
    git(repo, "update-index", "--add", "--cacheinfo", f"100644,{sha},{variant}")
    result = run(repo, "pre-commit")
    assert result.returncode == 1 and "rename to reverse/gate_baseline.txt" in result.stderr and not built(repo)
    git(repo, "commit", "-qm", "register renamed by case")            # as made with the hook bypassed
    result = run(repo, "pre-push", push_refs(repo, base))
    assert result.returncode == 1 and "rename to reverse/gate_baseline.txt" in result.stderr and not built(repo)


def test_pre_push_refuses_a_register_recreated_in_another_case_within_the_range(repo):
    """Round 9: create the canonical register, delete it, recreate it under another
    case with an exemption, all in one push: the pushed tip is refused."""
    shutil.copyfile(ROOT / "tools" / "check_case_collisions.py", repo / "tools" / "check_case_collisions.py")
    git(repo, "add", "tools/check_case_collisions.py")
    git(repo, "commit", "-qm", "the real case checker")
    base = git(repo, "rev-parse", "HEAD")
    write(repo, "reverse/gate_baseline.txt", "# baseline\n")
    git(repo, "add", "reverse/gate_baseline.txt")
    git(repo, "commit", "-qm", "create")
    git(repo, "rm", "-q", "reverse/gate_baseline.txt")
    git(repo, "commit", "-qm", "delete")
    blob = repo / "blob.tmp"
    blob.write_text("# baseline\nstrnul 0x00001000 _f\n", encoding="utf-8")
    sha = git(repo, "hash-object", "-w", str(blob))
    git(repo, "update-index", "--add", "--cacheinfo", f"100644,{sha},Reverse/Gate_Baseline.txt")
    git(repo, "commit", "-qm", "recreate in another case")
    result = run(repo, "pre-push", push_refs(repo, base))
    assert result.returncode == 1 and "rename to reverse/gate_baseline.txt" in result.stderr and not built(repo)


@pytest.mark.parametrize("variant", ["Reverse/attempts/0x00001000.cpp", "reverse/Attempts/0x00001000.cpp"])
def test_pre_commit_refuses_a_stash_under_a_case_renamed_attempts_tree(repo, variant):
    """check_csv and the hook select reverse/attempts/ by exact spelling: a stash
    under a case-renamed tree escaped both (GPT-6.1-Sol, converged gate round 10)."""
    shutil.copyfile(ROOT / "tools" / "check_case_collisions.py", repo / "tools" / "check_case_collisions.py")
    git(repo, "add", "tools/check_case_collisions.py")
    git(repo, "commit", "-qm", "the real case checker")
    blob = repo / "blob.tmp"
    blob.write_text("// score: not-a-number\n", encoding="utf-8")
    sha = git(repo, "hash-object", "-w", str(blob))
    git(repo, "update-index", "--add", "--cacheinfo", f"100644,{sha},{variant}")
    result = run(repo, "pre-commit")
    assert result.returncode == 1 and f"rename to {variant.lower()}" in result.stderr and not built(repo)


@pytest.mark.parametrize("name", ["docs/lessons.md", "Docs/Lessons-2026.md"])
def test_the_lessons_ban_fires_however_long_the_staged_list(repo, name):
    """`git diff | grep -q` under pipefail: grep exited at its match, a listing past
    the 64 KiB pipe buffer died of SIGPIPE, the pipeline failed and the ban did not
    run (found in Open-BFME-1's copy of the same line, 2026-10-10)."""
    for i in range(4000):           # sorted after docs/: ~70 bytes a line, ~280 KB
        write(repo, f"zz/a_long_directory_name_for_the_pipe_buffer/file_{i:05d}.txt", "x\n")
    write(repo, name, "# lessons\n")
    git(repo, "add", "-A")
    result = run(repo, "pre-commit")
    assert result.returncode == 1 and "lessons.md is banned" in result.stderr and not built(repo)


@pytest.mark.parametrize("operation", ["delete", "rename"])
def test_pre_commit_checks_the_ledger_when_data_rows_is_deleted_or_renamed(repo, operation):
    """The ACMRT listing omits a deletion and names only a rename's destination, so
    either took the early exit and check_csv never saw the orphaned data-only unit
    (GPT-6.1-Sol, Open-BFME-1 hook port round 1)."""
    data_only_setup(repo)
    write(repo, "tools/check_csv.py", "open('check-csv-ran', 'w').close()\n")
    git(repo, "add", "tools/check_csv.py")
    git(repo, "commit", "-qm", "a recording ledger check")
    if operation == "delete":
        git(repo, "rm", "-q", "reverse/data_rows.csv")
    else:
        git(repo, "mv", "reverse/data_rows.csv", "reverse/data_rows_saved.csv")
    run(repo, "pre-commit")
    assert (repo / "check-csv-ran").exists()


PIN_BASELINE = "reverse/pin_consistency_baseline.csv"
# pin_consistency's answer when its baseline is gone (read_baseline refuses)
PIN_STUB = """import pathlib, sys
if not pathlib.Path("reverse/pin_consistency_baseline.csv").exists():
    print("pin_consistency: baseline is missing", file=sys.stderr)
    raise SystemExit(1)
"""


def pin_setup(repo):
    write(repo, "tools/pin_consistency.py", PIN_STUB)
    write(repo, PIN_BASELINE, "symbol,bodies\n?p@@YAXXZ,1000\n?q@@YAXXZ,2000\n")
    git(repo, "add", "-A")
    git(repo, "commit", "-qm", "a pin baseline")


@pytest.mark.parametrize("operation", ["delete", "rename"])
def test_pre_commit_refuses_deleting_or_renaming_the_pin_baseline(repo, operation):
    """The deleted side set no flag, so the commit took the early exit and a required
    baseline went missing for every later gate (GPT-6.1-Sol, hook port round 2)."""
    pin_setup(repo)
    if operation == "delete":
        git(repo, "rm", "-q", PIN_BASELINE)
    else:
        git(repo, "mv", PIN_BASELINE, PIN_BASELINE.replace(".csv", "_saved.csv"))
    result = run(repo, "pre-commit")
    assert result.returncode == 1 and "baseline is missing" in result.stderr


def test_pre_commit_passes_a_pin_baseline_shrink(repo):
    pin_setup(repo)
    write(repo, PIN_BASELINE, "symbol,bodies\n?p@@YAXXZ,1000\n")
    git(repo, "add", PIN_BASELINE)
    result = run(repo, "pre-commit")
    assert result.returncode == 0, result.stderr


FLAG_OVERRIDES = "reverse/flag_overrides.csv"
# the full gate's answer when an override the unchanged source needs is gone
FLAG_BUILD = """import json, pathlib, sys
with open("build-calls.jsonl", "a", encoding="utf-8") as out:
    out.write(json.dumps(sys.argv[1:]) + "\\n")
if not pathlib.Path("reverse/flag_overrides.csv").exists():
    print("byte mismatch: Unit::f lost its /Oy- override", file=sys.stderr)
    raise SystemExit(1)
"""


@pytest.mark.parametrize("operation", ["delete", "rename"])
def test_pre_commit_runs_the_full_gate_when_flag_overrides_go(repo, operation):
    """flags_changed came only from the ACMRT listing: deleting or renaming the
    overrides skipped the full gate (GPT-6.1-Sol, hook port round 2)."""
    write(repo, "tools/build.py", FLAG_BUILD)
    write(repo, FLAG_OVERRIDES, f"source,flags\n{SOURCE},/Oy-\n")
    git(repo, "add", "-A")
    git(repo, "commit", "-qm", "an override the unit needs")
    if operation == "delete":
        git(repo, "rm", "-q", FLAG_OVERRIDES)
    else:
        git(repo, "mv", FLAG_OVERRIDES, FLAG_OVERRIDES.replace(".csv", "_saved.csv"))
    result = run(repo, "pre-commit")
    assert result.returncode == 1 and "lost its /Oy- override" in result.stderr
