"""Real Git commit-msg/range regression for new flag/EH protected paths.

Exercise the tracked checker through the actual commit-msg hook and range CLI.
"""
import os
import subprocess
import sys
from pathlib import Path
import pytest

CHECKER = Path(__file__).resolve().parents[1] / 'protected_paths.py'
HOOK = Path(__file__).resolve().parents[2] / '.githooks' / 'commit-msg'
PATHS = ('tools/flag_defaults.py', 'reverse/flag_overrides.csv', 'tools/eh_verify.py',
         'tools/compiler_profiles.py', 'vendor/clang23-x86/compiler.zip',
         # the STLport pin rename.py's identity respell trusts
         'reverse/stlport_manifest.txt')

def run(root, *args, input=None):
    env = dict(os.environ, GIT_CONFIG_NOSYSTEM='1', GIT_CONFIG_GLOBAL=os.devnull,
               GIT_AUTHOR_NAME='Fixture', GIT_AUTHOR_EMAIL='fixture@example.invalid',
               GIT_COMMITTER_NAME='Fixture', GIT_COMMITTER_EMAIL='fixture@example.invalid')
    for name in list(env):
        if name == 'GIT_CONFIG_COUNT' or name.startswith(('GIT_CONFIG_KEY_', 'GIT_CONFIG_VALUE_')):
            env.pop(name)
    return subprocess.run(args, cwd=root, env=env, input=input,
                          text=True, capture_output=True)

def git(root, *args, input=None):
    got = run(root, 'git', *args, input=input)
    assert got.returncode == 0, got.stderr
    return got.stdout.strip()

@pytest.mark.parametrize('path', PATHS)
@pytest.mark.parametrize('operation', ['edit', 'delete', 'rename'])
@pytest.mark.parametrize('valid', [False, True])
@pytest.mark.parametrize('mode', ['commit-msg', 'range'])
def test_new_lane_protection_actual_commit_msg_and_range(tmp_path, path, operation, valid, mode):
    git(tmp_path, 'init', '-q')
    checker = tmp_path / 'tools/protected_paths.py'
    checker.parent.mkdir(parents=True)
    checker.write_bytes(CHECKER.read_bytes())
    target = tmp_path / path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text('original fixture\n')
    git(tmp_path, 'add', 'tools/protected_paths.py', path)
    git(tmp_path, 'commit', '-qm', 'Seed protected checker\n\nVerifier-Change: Seed isolated integration fixture checker')
    base = git(tmp_path, 'rev-parse', 'HEAD')
    if operation == 'edit':
        target.write_text('changed fixture\n')
    elif operation == 'delete':
        target.unlink()
    else:
        # Rename into an unprotected destination must still protect the old name.
        target.rename(tmp_path / 'moved-unprotected.txt')
    git(tmp_path, 'add', '-A')
    message = 'Fixture change\n'
    if valid:
        message += '\nVerifier-Change: Strengthen isolated flag and EH verifier coverage\n'
    msg = tmp_path / 'message.txt'
    msg.write_text(message)
    # Actual commit-msg hook reads the checker from committed HEAD via git show.
    # Use the tracked bytes through a relative path: Windows Bash cannot use
    # every native drive-path spelling as its script argument.
    hook = tmp_path / 'actual-commit-msg'
    hook.write_bytes(HOOK.read_bytes())
    if mode == 'commit-msg':
        staged = run(tmp_path, 'bash', hook.name, msg.name)
        assert staged.returncode == (0 if valid else 1), staged.stderr
        if not valid:
            assert path in staged.stderr and 'Verifier-Change: MISSING' in staged.stderr
        return
    # Manufacture an adversarial commit object without changing HEAD or disabling
    # any hook. Range validation must independently reject its missing trailer.
    tree = git(tmp_path, 'write-tree')
    tip = git(tmp_path, 'commit-tree', tree, '-p', base, input=message)
    checked = run(tmp_path, sys.executable, str(CHECKER), '--range', base, tip)
    assert checked.returncode == (0 if valid else 1), checked.stderr
    if not valid:
        assert path in checked.stderr and 'without a Verifier-Change trailer' in checked.stderr


# --- the glob's reach ---------------------------------------------------------
#
# `*` stays inside one path segment and `**` spans them. fnmatch's `*` crossed
# `/`, so `reverse/*baseline*` -- written for the debt registers sitting directly
# in reverse/ -- also claimed 48 tracked handoff files under
# reverse/attempt_support/ (re_attempts.log:103352). Both halves matter: narrowing
# every `*` would have unprotected nested files under the subtree entries, which
# is why those say `**`.

sys.path.insert(0, str(CHECKER.parent))
import protected_paths as pp  # noqa: E402


@pytest.mark.parametrize("path", [
    "reverse/gate_baseline.txt",                        # a real debt register
    "reverse/eh_baseline.csv",
    "reverse/dir32_consistency_whitelist.txt",
    ".githooks/pre-commit",                             # subtree entries, one level
    ".github/workflows/real-link.yml",
    "tools/audit/anything.py",
    "vendor/clang23-x86/compiler.zip",
    "vendor/clang23-x86/notices/copying.txt",           # ... and nested
    "tools/publisher_fixtures/bfme2/cases.json",
    "reverse/retail_inventory/deep/er.tsv",
])
def test_protected_paths_stay_protected(path):
    assert pp.protected([path]) == [path]


@pytest.mark.parametrize("path", [
    "reverse/attempt_support/bridge-native-contract-seat2-20261023/baseline-byte.log",
    "reverse/attempt_support/ai-countmap-recheck-20261023/restored-baseline.txt",
    "reverse/attempt_support/notes/whitelist-draft.md",
    "reverse/attempt_support/baseline.txt",             # one level down is still not reverse/
])
def test_handoff_evidence_is_not_a_debt_register(path):
    assert pp.protected([path]) == []


def test_the_real_tree_keeps_every_register_and_drops_only_evidence():
    """Guards the swap itself: 48 files leave, none of them a register."""
    tracked = subprocess.run(["git", "ls-files"], cwd=CHECKER.parents[1],
                             capture_output=True, text=True, check=True).stdout.split()
    hits = pp.protected(tracked)
    assert [p for p in hits if p.startswith("reverse/attempt_support/")] == []
    # only the two filename globs; `baselines/.../manifest.json` is listed in full
    # and is not one of them.
    globs = [g for g in pp.PROTECTED if g.startswith("reverse/*")]
    assert globs, pp.PROTECTED
    registers = [p for p in hits if any(pp._pattern(g).match(p) for g in globs)]
    assert all(p.count("/") == 1 for p in registers), registers
    assert len(registers) >= 10
