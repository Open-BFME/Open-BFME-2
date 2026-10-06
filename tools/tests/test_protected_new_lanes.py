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
PATHS = ('tools/flag_defaults.py', 'reverse/flag_overrides.csv', 'tools/eh_verify.py')

def run(root, *args, input=None):
    env = dict(os.environ, GIT_CONFIG_NOSYSTEM='1', GIT_CONFIG_GLOBAL=os.devnull,
               GIT_AUTHOR_NAME='Fixture', GIT_AUTHOR_EMAIL='fixture@example.invalid',
               GIT_COMMITTER_NAME='Fixture', GIT_COMMITTER_EMAIL='fixture@example.invalid')
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
    # Avoid relying on this ignored review directory's location for the hook.
    hook = HOOK
    if mode == 'commit-msg':
        staged = run(tmp_path, 'bash', str(hook), str(msg))
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
