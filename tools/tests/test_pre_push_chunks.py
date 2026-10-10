"""Large push scopes run one ordinary full gate, with no lost selectors.

The hook and revision/equality checks are real; build/checker outcomes are
recorded fixture controls. A partial scope must keep the existing chunk path.
"""

import json
import os
import subprocess
from pathlib import Path

import pytest

import test_hook_fail_closed as hooks
from test_hook_argmax import RECORD_EH, _definition


ROOT = Path(__file__).resolve().parents[2]
HOOK = ROOT / ".githooks/pre-push"
COUNT = 1040
DATA = "Code/OnlyData.c"
ASM = "Code/Provider.asm"
EXTRA = "Code/extra selector.cpp"
LIB = "reference/library.lib(member.obj)"
RECORD_FULL = """import json, os, sys
with open('build-calls.jsonl', 'a', encoding='utf-8') as out:
    out.write(json.dumps(sys.argv[1:]) + '\\n')
if not sys.argv[1:] and os.environ.get('FAIL_FULL'):
    raise SystemExit(3)
if os.environ.get('FAIL_EXTRA') in sys.argv[1:]:
    raise SystemExit(4)
"""


@pytest.fixture
def repo(tmp_path, monkeypatch):
    # Isolate fixture commits from the real checkout's native hook configuration.
    for key in list(os.environ):
        if key.startswith('GIT_CONFIG_'):
            monkeypatch.delenv(key, raising=False)
    repo = hooks.repo.__wrapped__(tmp_path)
    sources = [f"Code/GameEngine/Source/FullScope/Unit{i:04d}.cpp" for i in range(COUNT)]
    for source in sources + [DATA, ASM, EXTRA]:
        hooks.write(repo, source, "// fixture provider\n")
    rows = "name,export_rva,target_rva,target_size,source,status,notes\n"
    rows += "".join(f"?f{i},,0x{0x2000 + i * 16:08X},16,{s},matched,\n"
                    for i, s in enumerate(sources + [ASM]))
    rows += f"?library,,0x00008000,16,{LIB},matched,\n"
    hooks.write(repo, "reverse/functions.csv", rows)
    hooks.write(repo, "reverse/data_rows.csv",
                "name,target_rva,target_size,source,status\n"
                f"?data,0x00009000,4,{DATA},matched\n")
    hooks.write(repo, "tools/build.py", RECORD_FULL)
    hooks.write(repo, "tools/eh_verify.py", RECORD_EH)
    hooks.write(repo, "tools/data_check.py", hooks.RECORD_CONVERGED)
    hooks.git(repo, "add", "--", "Code", "reverse", "tools")
    hooks.git(repo, "commit", "-qm", "all providers")
    base = hooks.git(repo, "rev-parse", "HEAD")
    hooks.write(repo, "tools/build.py", RECORD_FULL + "# outgoing driver change\n")
    hooks.git(repo, "commit", "-qam", "driver change")
    pushed = hooks.git(repo, "rev-parse", "HEAD")
    return repo, sources + [ASM, DATA], base, pushed


def calls(repo, path="build-calls.jsonl"):
    listing = repo / path
    return [json.loads(line) for line in listing.read_text().splitlines()] if listing.exists() else []


def run_hook(fixture, selected=None, **env):
    repo, sources, base, pushed = fixture
    hooks.write(repo, "delta.txt", "\n".join(sources if selected is None else selected) + "\n")
    refs = f"refs/heads/master {pushed} refs/heads/master {base}\n"
    return hooks.run(repo, "pre-push", refs, env)


def classify(fixture, selected, rev=None, listing_bytes=None):
    repo, _, _, pushed = fixture
    listing = repo / "scope-list"
    listing.write_bytes(listing_bytes if listing_bytes is not None else
                        b"".join(path.encode() + b"\0" for path in selected))
    harness = _definition(HOOK, 'classify_full_scope') + f"\nclassify_full_scope {rev or pushed} scope-list\n"
    done = subprocess.run([hooks._bash(), "--noprofile", "--norc"], cwd=repo,
                          input=harness.encode(), capture_output=True)
    return done, [p.decode() for p in done.stdout.split(b"\0") if p]


def test_complete_function_and_data_scope_runs_one_full_gate(repo):
    done = run_hook(repo)
    assert done.returncode == 0, done.stderr
    assert calls(repo[0]) == [[]]
    assert 'ordinary full gate once' in done.stdout
    assert calls(repo[0], 'eh-calls.jsonl') == [
        ['--assert-shrink-range', repo[2], repo[3]], repo[1]]
    converged = calls(repo[0], 'conv-calls.jsonl')
    assert len(converged) == 1 and converged[0]['sources'] == repo[1]


@pytest.mark.parametrize('missing', [0, -1], ids=['function-provider', 'data-provider'])
def test_partial_scope_keeps_every_selector_in_bounded_builds(repo, missing):
    selected = list(repo[1])
    selected.pop(missing)
    done = run_hook(repo, selected)
    assert done.returncode == 0, done.stderr
    chunks = calls(repo[0])
    assert len(chunks) > 1 and all(chunks)
    assert [path for chunk in chunks for path in chunk] == selected


@pytest.mark.parametrize('failure', ['', EXTRA], ids=['extra-kept', 'extra-refused'])
def test_full_gate_keeps_additional_rowless_selectors_explicit(repo, failure):
    done = run_hook(repo, repo[1] + [EXTRA], FAIL_EXTRA=failure)
    assert calls(repo[0]) == [[], [EXTRA]]
    assert done.returncode == (1 if failure else 0), done.stderr
    if failure:
        assert 'additional outgoing sources' in done.stderr


def test_full_gate_failure_stops_before_eh_and_data(repo):
    done = run_hook(repo, FAIL_FULL='1')
    assert done.returncode == 1 and 'full byte-verify' in done.stderr
    assert calls(repo[0]) == [[]]
    assert calls(repo[0], 'eh-calls.jsonl') == [
        ['--assert-shrink-range', repo[2], repo[3]]]
    assert not calls(repo[0], 'conv-calls.jsonl')


def test_full_scope_still_binds_sources_outside_the_selected_provider_set(repo):
    # The full gate reads more than the selected rows: bind all tracked Code.
    hooks.write(repo[0], EXTRA, '// dirty additional source\n')
    done = run_hook(repo)
    assert done.returncode == 1 and 'tracked source differs' in done.stderr
    assert not calls(repo[0])


def test_missing_selected_source_is_refused_before_the_full_gate(repo):
    (repo[0] / repo[1][-1]).unlink()
    done = run_hook(repo)
    assert done.returncode == 1 and 'outgoing rows reference missing source' in done.stderr
    assert not calls(repo[0])


def test_classifier_uses_pushed_ledgers_instead_of_newer_head(repo):
    path, selected, _, pushed = repo
    ledger = (path / 'reverse/functions.csv').read_text()
    hooks.write(path, 'reverse/functions.csv', ledger + f'?extra,,0x0000A000,16,{EXTRA},matched,\n')
    hooks.git(path, 'commit', '-qam', 'newer ledger')
    done, scope = classify(repo, selected, pushed)
    assert done.returncode == 0 and scope == ['full'], done.stderr
    done, scope = classify(repo, selected, 'HEAD')
    assert done.returncode == 0 and scope == ['chunks'], done.stderr


def test_classifier_preserves_extra_path_bytes_and_order(repo):
    extras = ['Code/space and quote\'.cpp', 'Code/semicolon;dollar$.c', 'Code/\u00e9.asm']
    done, scope = classify(repo, repo[1] + extras)
    assert done.returncode == 0 and scope == ['full', *extras], done.stderr


def test_absent_data_ledger_is_proven_by_git(repo):
    hooks.git(repo[0], 'rm', '-q', 'reverse/data_rows.csv')
    hooks.git(repo[0], 'commit', '-qm', 'no data providers')
    done, scope = classify(repo, repo[1][:-1], 'HEAD')
    assert done.returncode == 0 and scope == ['full'], done.stderr


@pytest.mark.parametrize('broken', ['missing-columns', 'missing-functions', 'short-row',
                                    'long-row', 'empty-source', 'unterminated-list'])
def test_classifier_errors_never_become_an_empty_successful_scope(repo, broken):
    path = repo[0]
    if broken == 'missing-columns':
        hooks.write(path, 'reverse/functions.csv', 'name\n?f\n')
        hooks.git(path, 'commit', '-qam', 'malformed ledger')
    elif broken == 'missing-functions':
        hooks.git(path, 'rm', '-q', 'reverse/functions.csv')
        hooks.git(path, 'commit', '-qm', 'missing ledger')
    elif broken in ('short-row', 'long-row', 'empty-source'):
        ledger = (path / 'reverse/functions.csv').read_text()
        bad = {'short-row': '?bad,', 'long-row': '?bad,,0x2000,16,Code/Bad.cpp,matched,,extra',
               'empty-source': '?bad,,0x2000,16,,matched,'}[broken]
        hooks.write(path, 'reverse/functions.csv', ledger + bad + '\n')
        hooks.git(path, 'commit', '-qam', 'malformed row')
    raw = b'Code/unterminated.cpp' if broken == 'unterminated-list' else None
    done, scope = classify(repo, repo[1], 'HEAD', listing_bytes=raw)
    assert done.returncode != 0 and not scope


def test_classifier_git_failure_propagates(repo):
    done, scope = classify(repo, repo[1], 'invalid-revision')
    assert done.returncode != 0 and not scope


def test_full_scope_classifier_failure_stops_the_real_hook(repo):
    path = repo[0]
    hooks.write(path, 'reverse/data_rows.csv', 'name\n?missing-source-and-status\n')
    # Earlier filters pass in this fixture; the real scope proof must refuse.
    hooks.write(path, 'tools/data_check.py', "import sys\nif '-' in sys.argv:\n    sys.stdin.buffer.read()\n")
    hooks.git(path, 'commit', '-qam', 'malformed data ledger')
    updated = (*repo[:3], hooks.git(path, 'rev-parse', 'HEAD'))
    done = run_hook(updated)
    assert done.returncode == 1 and 'proving full build scope' in done.stderr
    assert not calls(path)
