"""pre-commit step 4: a commit's new units go through link_check --new-variants.

A new unit that adds a second body for a COMDAT every linked object shares, or
a wrong copy of a ledger-owned name, where link.exe would keep it over the copy
the others link against, re-blocks every unit that links against it (three
donor ports re-blocked 56 units this way). The step runs in shadow mode: it
reports and never refuses until its false-refusal rate is measured. Each case
runs the real hook in a throwaway repository (test_hook_fail_closed's fixture)
with link_check.py replaced by a recorder: what it was asked to judge, how,
and whether the byte verify had already built the objects it reads.
"""
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/tests"))
from test_hook_fail_closed import repo, git, write, run, built, SOURCE  # noqa: E402,F401

RECORD_LINK = """import json, os, sys
paths = [os.fsdecode(p) for p in sys.stdin.buffer.read().split(b"\\0") if p]
with open("link-calls.jsonl", "a", encoding="utf-8") as out:
    out.write(json.dumps({"argv": sys.argv[1:], "paths": paths,
                          "after_build": os.path.exists("build-calls.jsonl")}) + "\\n")
for path in paths:
    print("link_check [shadow] %s: its copy of f would replace the one other units link against" % path,
          file=sys.stderr)
sys.exit(int(open("link-exit").read()) if os.path.exists("link-exit") else 0)
"""
# A space in the name: the list travels NUL-separated on stdin, never as words.
NEW = "Code/GameEngine/Source/Common/New Unit.cpp"
NEW_C = "Code/GameEngine/Source/Common/Helper.c"
GENERATED = ("Code/gen_small/uw_gen_fixture.cpp", "Code/gen_asm/gen_fixture.cpp")
EDITED = "struct Unit { void f(); };\nvoid Unit::f() { int x = 0; }\n"
ARGV = ["--new-variants", "--staged-peers", "--shadow", "--paths-from", "-"]


def linked(repo):
    path = repo / "link-calls.jsonl"
    if not path.exists():
        return []
    return [json.loads(line) for line in path.read_text(encoding="utf-8").splitlines()]


def recorded(repo):
    write(repo, "tools/link_check.py", RECORD_LINK)
    return repo


def stage(repo, *paths):
    for path in paths:
        write(repo, path, EDITED if path == SOURCE else "void fixture() {}\n")
    git(repo, "add", *paths)


def test_new_units_reach_link_check_on_stdin_after_the_byte_verify(repo):
    repo = recorded(repo)
    stage(repo, SOURCE, NEW, NEW_C, *GENERATED)
    result = run(repo, "pre-commit")
    assert result.returncode == 0, result.stderr
    assert built(repo) == {SOURCE}
    calls = linked(repo)
    assert len(calls) == 1
    # Only added hand-written units: the edited unit is a peer the tool reads
    # itself (--staged-peers), and generated units are never judged here.
    assert calls[0]["argv"] == ARGV
    assert sorted(calls[0]["paths"]) == sorted([NEW, NEW_C])
    assert calls[0]["after_build"]


def test_a_reported_new_unit_still_commits_in_shadow_mode(repo):
    repo = recorded(repo)
    stage(repo, NEW)
    result = run(repo, "pre-commit")
    assert result.returncode == 0, result.stderr
    assert f"link_check [shadow] {NEW}: its copy of f" in result.stderr
    assert "PRE-COMMIT OK" in result.stdout
    assert [call["paths"] for call in linked(repo)] == [[NEW]]


def test_a_shadow_check_that_cannot_run_is_reported_and_ignored(repo):
    repo = recorded(repo)
    write(repo, "link-exit", "1")
    stage(repo, NEW)
    result = run(repo, "pre-commit")
    assert result.returncode == 0, result.stderr
    assert "pre-commit: link admission shadow check failed to run (ignored)" in result.stderr
    assert "PRE-COMMIT OK" in result.stdout


def test_a_commit_adding_no_hand_written_unit_runs_no_link_check(repo):
    repo = recorded(repo)
    stage(repo, SOURCE, *GENERATED)
    result = run(repo, "pre-commit")
    assert result.returncode == 0, result.stderr
    assert not linked(repo)
