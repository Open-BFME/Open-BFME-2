"""Exercise the actual candidate pre-push and real Git per-commit EH debt API."""
import ast
import json
import sys
from pathlib import Path
import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools/tests'))
from test_hook_fail_closed import repo, git, write, SOURCE

CANDIDATE_EH = ROOT / 'tools/eh_verify.py'
CANDIDATE_HOOK = ROOT / '.githooks/pre-push'
EH_TEXT = CANDIDATE_EH.read_text()
# Use the real proposed range implementation without importing actual compiler
# dependencies or reading the main ledger; only verification itself is stubbed.
node = ast.parse(EH_TEXT)
FUNCTIONS = '\n\n'.join(ast.get_source_segment(EH_TEXT, n) for n in node.body
                         if isinstance(n, ast.FunctionDef) and n.name in ('load_baseline', 'assert_shrink_range'))
EH = '''import csv, json, subprocess, sys
from pathlib import Path
ROOT = Path.cwd()
BASELINE = ROOT / "reverse/eh_baseline.csv"
''' + FUNCTIONS + '''
with open("eh-calls.jsonl", "a") as out:
    out.write(json.dumps(sys.argv[1:]) + "\\n")
if "--assert-shrink-range" in sys.argv:
    raise SystemExit(assert_shrink_range(*sys.argv[2:]))
entries = sys.stdin.buffer.read().split(b"\\0")
with open("eh-sources.json", "w") as out:
    json.dump([x.decode() for x in entries if x], out)
if Path("fail-eh").exists():
    raise SystemExit(7)
'''
HEADER = 'name,target_rva,verdict\n'
ROW = '?f@@YAXXZ,0x00001000,bytes_differ\n'

@pytest.fixture
def hooked(repo):
    write(repo, 'tools/eh_verify.py', EH)
    write(repo, 'reverse/eh_baseline.csv', HEADER)
    git(repo, 'add', 'tools/eh_verify.py', 'reverse/eh_baseline.csv')
    git(repo, 'commit', '-qm', 'Seed real range verifier')
    return repo

def push(repo, base, tip):
    import subprocess
    return subprocess.run(['bash', str(CANDIDATE_HOOK)], cwd=repo,
        input=f'refs/heads/master {tip} refs/heads/master {base}\n',
        text=True, capture_output=True, timeout=60)

def tip(repo):
    git(repo, 'add', SOURCE)
    git(repo, 'commit', '-qm', 'Source change')
    return git(repo, 'rev-parse', 'HEAD')

@pytest.mark.parametrize('bad', [False, True])
def test_selected_outgoing_sources_receive_eh_verification_after_build(hooked, bad):
    base = git(hooked, 'rev-parse', 'HEAD')
    write(hooked, SOURCE, 'struct Unit { void f(); };\nvoid Unit::f() { }\n// change\n')
    rev = tip(hooked)
    if bad:
        write(hooked, 'fail-eh', '1')
    got = push(hooked, base, rev)
    assert got.returncode == (1 if bad else 0), got.stderr
    assert json.loads((hooked / 'eh-sources.json').read_text()) == [SOURCE]
    assert (hooked / 'build-calls.jsonl').exists()
    assert '--all' not in (hooked / 'eh-calls.jsonl').read_text()
    if bad:
        assert 'exception data differs' in got.stderr

@pytest.mark.parametrize('temporary', [False, True])
def test_baseline_growth_is_refused_even_if_later_removed(hooked, temporary):
    base = git(hooked, 'rev-parse', 'HEAD')
    write(hooked, 'reverse/eh_baseline.csv', HEADER + ROW)
    git(hooked, 'add', 'reverse/eh_baseline.csv')
    git(hooked, 'commit', '-qm', 'Add wrong debt\n\nVerifier-Change: Fixture cannot excuse debt growth')
    if temporary:
        write(hooked, 'reverse/eh_baseline.csv', HEADER)
        git(hooked, 'add', 'reverse/eh_baseline.csv')
        git(hooked, 'commit', '-qm', 'Remove temporary debt')
    got = push(hooked, base, git(hooked, 'rev-parse', 'HEAD'))
    assert got.returncode == 1 and 'eh_baseline.csv grew' in got.stderr
    assert not (hooked / 'build-calls.jsonl').exists()


def test_empty_source_delta_does_not_run_unbounded_eh_verification(hooked):
    base = git(hooked, 'rev-parse', 'HEAD')
    write(hooked, 'notes.txt', 'Evidence only\n')
    git(hooked, 'add', 'notes.txt')
    git(hooked, 'commit', '-qm', 'Evidence only')
    got = push(hooked, base, git(hooked, 'rev-parse', 'HEAD'))
    assert got.returncode == 0, got.stderr
    assert not (hooked / 'eh-sources.json').exists()
    assert not (hooked / 'build-calls.jsonl').exists()


def test_delta_producer_failure_still_refuses(hooked):
    base = git(hooked, 'rev-parse', 'HEAD')
    write(hooked, SOURCE, '// changed\n')
    rev = tip(hooked)
    write(hooked, 'delta-exit', '3')
    got = push(hooked, base, rev)
    assert got.returncode == 1 and 'delta_sources' in got.stderr
    assert not (hooked / 'build-calls.jsonl').exists()


def test_missing_baseline_at_base_is_empty_debt_not_growth_permission(hooked):
    git(hooked, 'rm', 'reverse/eh_baseline.csv')
    git(hooked, 'commit', '-qm', 'Remove empty baseline')
    base = git(hooked, 'rev-parse', 'HEAD')
    write(hooked, 'reverse/eh_baseline.csv', HEADER + ROW)
    git(hooked, 'add', 'reverse/eh_baseline.csv')
    git(hooked, 'commit', '-qm', 'Create baseline debt')
    got = push(hooked, base, git(hooked, 'rev-parse', 'HEAD'))
    assert got.returncode == 1 and 'eh_baseline.csv grew' in got.stderr


def test_range_invalid_revision_fails_closed(hooked):
    import subprocess
    got = subprocess.run([sys.executable, 'tools/eh_verify.py', '--assert-shrink-range',
                          'nonexistent-review-ref', 'HEAD'], cwd=hooked,
                         capture_output=True, text=True)
    assert got.returncode != 0 and 'Git failed' in got.stderr


def test_baseline_removal_positive_control(hooked):
    write(hooked, 'reverse/eh_baseline.csv', HEADER + ROW)
    git(hooked, 'add', 'reverse/eh_baseline.csv')
    git(hooked, 'commit', '-qm', 'Seed existing debt')
    base = git(hooked, 'rev-parse', 'HEAD')
    write(hooked, 'reverse/eh_baseline.csv', HEADER)
    git(hooked, 'add', 'reverse/eh_baseline.csv')
    git(hooked, 'commit', '-qm', 'Pay existing debt')
    got = push(hooked, base, git(hooked, 'rev-parse', 'HEAD'))
    assert got.returncode == 0, got.stderr


@pytest.mark.parametrize('case', ['valid', 'invalid', 'exclusive'])
def test_full_eh_module_cli_main_over_real_git(hooked, monkeypatch, case):
    import importlib.util
    sys.path.insert(0, str(ROOT / 'tools'))
    spec = importlib.util.spec_from_file_location('eh_review_full_cli', CANDIDATE_EH)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    monkeypatch.setattr(module, 'ROOT', hooked)
    monkeypatch.setattr(module, 'BASELINE', hooked / 'reverse/eh_baseline.csv')
    base = git(hooked, 'rev-parse', 'HEAD')
    args = ['--assert-shrink-range', base, 'HEAD']
    if case == 'invalid':
        args[1] = 'nonexistent-review-ref'
        with pytest.raises(SystemExit, match='Git failed'):
            module.main(args)
    elif case == 'exclusive':
        with pytest.raises(SystemExit) as rejected:
            module.main(args + ['--all'])
        assert rejected.value.code == 2
    else:
        assert module.main(args) == 0
