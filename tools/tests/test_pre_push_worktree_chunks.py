"""Run the tracked push hook against real Git worktrees with bounded path checks.

The old source loop spawned one Git per path: 2,000 checks took 146 seconds,
and an actual 21,913-source push crashed in MSYS fork after about 7,521 paths.
Only checker/build results are stubbed here; equality checks use real Git.
"""

import json
import os
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

import test_hook_fail_closed as hooks
from test_hook_argmax import _definition


ROOT = Path(__file__).resolve().parents[2]
HOOK = ROOT / ".githooks" / "pre-push"
COUNT = 350


@pytest.fixture
def worktree(tmp_path):
    repo = hooks.repo.__wrapped__(tmp_path)
    sources = [f"Code/GameEngine/Source/Common/Chunks/SelectedUnit{i:04d}.cpp"
               for i in range(COUNT)]
    for source in sources:
        hooks.write(repo, source, "// unchanged selected source\n")
    ledger = "name,export_rva,target_rva,target_size,source,status,notes\n"
    ledger += "".join(f"?f{i}@@YAXXZ,,0x{0x1000 + i * 16:08X},16,{source},matched,\n"
                      for i, source in enumerate(sources))
    hooks.write(repo, "reverse/functions.csv", ledger)
    hooks.git(repo, "add", "Code", "reverse/functions.csv")
    hooks.git(repo, "commit", "-qm", "selected source controls")
    base = hooks.git(repo, "rev-parse", "HEAD")
    hooks.write(repo, "reverse/functions.csv", ledger.replace(",matched,\n", ",matched,selected\n"))
    hooks.git(repo, "add", "reverse/functions.csv")
    hooks.git(repo, "commit", "-qm", "ledger-only outgoing change")
    pushed = hooks.git(repo, "rev-parse", "HEAD")
    # Repeat entries and an empty entry must not expand the established verify list.
    hooks.write(repo, "delta.txt", "\n".join(sources + [sources[0], "", sources[-1]]) + "\n")
    hooks.write(repo, ".gitignore", (repo / ".gitignore").read_text() + "spy/\ngit-calls.jsonl\n")
    # Record Bash's calls, forwarding to native Git with unchanged arguments and
    # stdout/stderr/status. A shell function avoids Git Bash's PATH rewriting.
    real_git = str(Path(shutil.which("git")).resolve())
    spy = repo / "spy"
    spy.mkdir()
    hooks.write(repo, "spy/record_git.py", f"""import json, os, pathlib, subprocess, sys
args = sys.argv[1:]
paths = set({sources!r})
selected = (len(args) > 4 and args[:2] == ['diff', '--quiet'] and args[3] == '--'
            and all(p in paths for p in args[4:]))
log = pathlib.Path('git-calls.jsonl')
if selected:
    prior = log.read_text().splitlines() if log.exists() else []
    with log.open('a', encoding='utf-8') as out:
        out.write(json.dumps(args) + '\\n')
    if len(prior) + 1 == int(os.environ.get('FAIL_EQUALITY_CHUNK', '0')):
        print('forced Git equality error', file=sys.stderr)
        sys.exit(2)
sys.exit(subprocess.call([{real_git!r}, *args]))
""")
    env = dict(os.environ)
    return repo, sources, base, pushed, env


def run_hook(worktree, **extra_env):
    repo, sources, base, pushed, env = worktree
    refs = f"refs/heads/master {pushed} refs/heads/master {base}\n"
    harness = 'git() { python3 spy/record_git.py "$@"; }\nsource "$1"'
    return subprocess.run([hooks._bash(), "--noprofile", "--norc", "-c", harness,
                           "fixture", HOOK.as_posix()], cwd=repo, input=refs,
                          capture_output=True, text=True, encoding="utf-8", errors="replace",
                          env=dict(env, **extra_env), timeout=600)


def equality_calls(repo):
    path = repo / "git-calls.jsonl"
    return [json.loads(line) for line in path.read_text().splitlines()] if path.exists() else []


def test_real_hook_checks_every_deduplicated_source_in_bounded_chunks(worktree):
    repo, sources, _, pushed, _ = worktree
    done = run_hook(worktree)
    assert done.returncode == 0, done.stderr
    calls = equality_calls(repo)
    assert len(calls) > 1
    assert [p for call in calls for p in call[4:]] == sources
    assert all(call[:4] == ["diff", "--quiet", pushed, "--"] for call in calls)
    assert all(sum(2 * len(p.encode()) + 3 for p in call[4:]) <= 24000 for call in calls)
    assert hooks.built(repo) == set(sources)
    assert f"PRE-PUSH OK ({COUNT} outgoing source(s) byte-verified)" in done.stdout


@pytest.mark.parametrize("staged", [False, True], ids=["unstaged", "staged"])
def test_real_hook_refuses_dirty_source_in_a_later_chunk(worktree, staged):
    repo, sources, _, _, _ = worktree
    hooks.write(repo, sources[-1], "// differs from the pushed source\n")
    if staged:
        hooks.git(repo, "add", "--", sources[-1])
    done = run_hook(worktree)
    assert done.returncode == 1
    assert "differs from the pushed commit" in done.stderr
    assert len(equality_calls(repo)) > 1
    assert sources[-1] in equality_calls(repo)[-1][4:]
    assert not hooks.built(repo)


@pytest.mark.parametrize("restore_worktree", [False, True], ids=["newer-body", "pushed-body"])
def test_real_hook_uses_pushed_revision_instead_of_head_or_index(worktree, restore_worktree):
    repo, sources, _, pushed, _ = worktree
    source = sources[-1]
    hooks.write(repo, source, "// newer HEAD and index body\n")
    hooks.git(repo, "add", "--", source)
    hooks.git(repo, "commit", "-qm", "newer body not being pushed")
    assert hooks.git(repo, "rev-parse", "HEAD") != pushed
    if restore_worktree:
        # Leave the index and HEAD newer, but build the actual pushed body on disk.
        hooks.write(repo, source, "// unchanged selected source\n")
    done = run_hook(worktree)
    if restore_worktree:
        assert done.returncode == 0, done.stderr
        assert hooks.built(repo) == set(sources)
    else:
        assert done.returncode == 1 and "differs from the pushed commit" in done.stderr
        assert not hooks.built(repo)
    assert all(call[2] == pushed for call in equality_calls(repo))


def test_real_hook_still_refuses_a_missing_selected_source(worktree):
    repo, sources, _, _, _ = worktree
    (repo / sources[-1]).unlink()
    done = run_hook(worktree)
    assert done.returncode == 1
    assert f"outgoing rows reference missing source {sources[-1]}" in done.stderr
    assert not hooks.built(repo)


def test_real_hook_fails_closed_on_git_error_in_a_later_chunk(worktree):
    repo, _, _, _, _ = worktree
    done = run_hook(worktree, FAIL_EQUALITY_CHUNK="2")
    assert done.returncode == 1
    assert "forced Git equality error" in done.stderr
    assert "git diff failed" in done.stderr
    assert len(equality_calls(repo)) == 2
    assert not hooks.built(repo)


def chunk_harness(tmp_path, sources, fail_at=0):
    (tmp_path / "selectors").write_bytes(b"".join(s.encode() + b"\0" for s in sources))
    revision = "1234567890abcdef" * 2 + "12345678"
    harness = f"""set -euo pipefail
fail() {{ echo "FAILED: $*" >&2; exit 1; }}
n=0
git() {{
    n=$((n + 1))
    printf '%s\\0' "$@" > "calls.$n"
    if [ "$n" -eq {fail_at} ]; then echo 'git failure stderr retained' >&2; return 2; fi
}}
{_definition(HOOK, 'measure_argument')}
{_definition(HOOK, 'check_worktree_chunks')}
mapfile -d '' -t selectors < selectors
check_worktree_chunks {revision} "${{selectors[@]}}"
echo DONE
"""
    done = subprocess.run([hooks._bash(), "--noprofile", "--norc"], cwd=tmp_path,
                          input=harness, text=True, capture_output=True)
    calls = sorted(tmp_path.glob("calls.*"), key=lambda p: int(p.suffix[1:]))
    chunks = [[v.decode() for v in p.read_bytes().split(b"\0")[:-1]] for p in calls]
    return done, chunks, revision


@pytest.mark.parametrize("fail_at", [0, 2])
def test_tracked_chunk_function_preserves_argv_and_stops_on_failure(tmp_path, fail_at):
    sources = [f"Code/{'Deep/' * 20}Unit {i:04d}.cpp" for i in range(1000)]
    sources += ["-leading-option.cpp", "Code/a b.cpp", "Code/[abc]?.cpp", "Code/*.cpp",
                "Code/quote'\".cpp", "Code/semicolon;dollar$.cpp"]
    done, chunks, revision = chunk_harness(tmp_path, sources, fail_at)
    assert all(c[:4] == ["diff", "--quiet", revision, "--"] for c in chunks)
    for chunk in chunks:
        command = subprocess.list2cmdline(["g" * 1000, *chunk])
        assert len(command.encode("utf-16-le")) // 2 < 32767
    if fail_at:
        assert done.returncode == 1 and len(chunks) == fail_at
        assert "git failure stderr retained" in done.stderr
        assert "DONE" not in done.stdout
    else:
        assert done.returncode == 0, done.stderr
        assert len(chunks) > 1
        assert [p for c in chunks for p in c[4:]] == sources


def test_empty_chunk_list_runs_no_git(tmp_path):
    done, chunks, _ = chunk_harness(tmp_path, [])
    assert done.returncode == 0 and not chunks


def test_oversized_single_path_refuses_without_git(tmp_path):
    done, chunks, _ = chunk_harness(tmp_path, ["x" * 12000])
    assert done.returncode == 1
    assert "worktree source exceeds argument limit" in done.stderr
    assert not chunks
