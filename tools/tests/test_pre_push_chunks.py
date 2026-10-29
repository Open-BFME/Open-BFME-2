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


def classify(fixture, selected, rev=None, listing_bytes=None, full_required=0):
    repo, _, _, pushed = fixture
    listing = repo / "scope-list"
    listing.write_bytes(listing_bytes if listing_bytes is not None else
                        b"".join(path.encode() + b"\0" for path in selected))
    harness = _definition(HOOK, 'classify_full_scope') + f"\nclassify_full_scope {rev or pushed} scope-list {full_required}\n"
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


# Logs the subcommand and its commit (cross-checks: the receipt it carries and the
# sources it was told were verified); temporary paths and empty options are not logged.
RECORD_RECEIPT = """import json, os, sys
args = sys.argv[1:]
if args[:1] == ['scoped-dir32']:
    with open(args[args.index('--verified-from') + 1], 'rb') as listing:
        scope = sorted(p.decode() for p in listing.read().split(b'\\0') if p)
    with open('scoped-calls.jsonl', 'a', encoding='utf-8') as out:
        out.write(json.dumps(scope) + '\\n')
    raise SystemExit(int(os.environ.get('FAIL_SCOPED') or 0))
entry = args[:2]
if args[:1] == ['cross-checks']:
    entry = ['cross-checks', args[args.index('--since') + 1]]
    with open(args[args.index('--verified-from') + 1], 'rb') as listing:
        entry.append(sorted(p.decode() for p in listing.read().split(b'\\0') if p))
with open('receipt-calls.jsonl', 'a', encoding='utf-8') as out:
    out.write(json.dumps(entry) + '\\n')
if sys.argv[1:2] == ['find'] and os.environ.get('CARRY_FROM'):
    print(os.environ['CARRY_FROM'])
"""


def receipt_log(fixture):
    path, sources, base, _ = fixture
    hooks.write(path, 'tools/full_gate_receipt.py', RECORD_RECEIPT)
    hooks.git(path, 'add', '--', 'tools/full_gate_receipt.py')
    hooks.git(path, 'commit', '-qm', 'receipt log fixture')
    return path, sources, base, hooks.git(path, 'rev-parse', 'HEAD')


def test_large_bounded_chunk_scope_records_a_receipt(repo):
    # A bounded scope of 1,000+ sources (a widely included header) stays in chunks
    # but takes as long as the full gate; its rebased retry must be able to carry it.
    fixture = receipt_log(repo)
    selected = list(repo[1])
    selected.pop(0)
    done = run_hook(fixture, selected)
    assert done.returncode == 0, done.stderr
    assert len(calls(repo[0])) > 1 and all(calls(repo[0]))
    assert calls(repo[0], 'receipt-calls.jsonl') == [['find', fixture[3]], ['record', fixture[3]]]


def test_full_scope_still_records_a_receipt(repo):
    fixture = receipt_log(repo)
    done = run_hook(fixture)
    assert done.returncode == 0, done.stderr
    assert calls(repo[0]) == [[]]
    assert calls(repo[0], 'receipt-calls.jsonl') == [['find', fixture[3]], ['record', fixture[3]]]


def test_the_full_gate_keeps_its_dir32_index_out_of_the_tool_logs(repo):
    # a136856afb's receipt failed: the index sat in BFME_GATE_LOADS, whose every
    # file full_gate_receipt.py reads as one of build.py's UTF-8 tool logs
    fixture = receipt_log(repo)
    hooks.write(repo[0], 'tools/build.py', RECORD_FULL + """
if not sys.argv[1:]:
    with open('gate-env.json', 'w', encoding='utf-8') as out:
        json.dump({k: os.environ.get(k) for k in ('BFME_GATE_LOADS', 'BFME_DIR32_INDEX')}, out)
""")
    hooks.git(repo[0], 'commit', '-qam', 'record the gate environment')
    done = run_hook((repo[0], repo[1], repo[2], hooks.git(repo[0], 'rev-parse', 'HEAD')))
    assert done.returncode == 0, done.stderr
    env = json.loads((repo[0] / 'gate-env.json').read_text(encoding='utf-8'))
    assert env['BFME_GATE_LOADS'] and env['BFME_DIR32_INDEX']
    loads = os.path.normcase(os.path.abspath(env['BFME_GATE_LOADS']))
    index = os.path.normcase(os.path.abspath(env['BFME_DIR32_INDEX']))
    assert os.path.commonpath([loads, index]) != loads


def test_small_scope_neither_asks_for_nor_records_a_receipt(repo):
    fixture = receipt_log(repo)
    done = run_hook(fixture, [repo[1][0]])
    assert done.returncode == 0, done.stderr
    assert not calls(repo[0], 'receipt-calls.jsonl')


@pytest.mark.parametrize('count,receipted', [(511, False), (512, True), (550, True)])
def test_medium_bounded_scope_carries_only_after_every_selector_passes(repo, count, receipted):
    fixture = receipt_log(repo)
    selected = fixture[1][:count]
    done = run_hook(fixture, selected)
    assert done.returncode == 0, done.stderr
    chunks = calls(fixture[0])
    assert all(chunks) and [source for chunk in chunks for source in chunk] == selected
    expected = [['find', fixture[3]], ['record', fixture[3]]] if receipted else []
    assert calls(fixture[0], 'receipt-calls.jsonl') == expected


def medium_receipt_fixture(repo):
    path, sources, base, _ = repo
    # Checker outcomes are fixture controls. The real hook must preserve scope,
    # failure propagation and receipt ordering; real receipt eligibility is
    # separately covered by test_full_gate_receipt.py.
    hooks.write(path, 'tools/full_gate_receipt.py', RECORD_RECEIPT + """
if sys.argv[1:2] == ['cross-checks'] and os.environ.get('FAIL_RETRY') == 'cross':
    raise SystemExit(5)
""")
    hooks.write(path, 'tools/delta_sources.py', """import os, sys
sys.stdout.reconfigure(newline='\\n')
listing = 'delta-retry.txt' if sys.argv[2] == os.environ.get('CARRY_FROM') else 'delta.txt'
sys.stdout.write(open(listing, encoding='utf-8').read())
""")
    hooks.write(path, 'tools/eh_verify.py', RECORD_EH + """
import os
if '--assert-shrink-range' not in sys.argv and os.environ.get('FAIL_RETRY') == 'eh':
    raise SystemExit(6)
""")
    hooks.write(path, 'tools/data_check.py', hooks.RECORD_CONVERGED + """
import os
if os.environ.get('FAIL_RETRY') == 'data':
    raise SystemExit(7)
""")
    hooks.git(path, 'add', '--', 'tools/full_gate_receipt.py', 'tools/delta_sources.py',
              'tools/eh_verify.py', 'tools/data_check.py')
    hooks.git(path, 'commit', '-qm', 'medium carry checker controls')
    return path, sources, base, hooks.git(path, 'rev-parse', 'HEAD')


@pytest.mark.parametrize('failure', ['build', 'eh', 'data'])
def test_medium_bounded_failure_never_records_a_receipt(repo, failure):
    fixture = medium_receipt_fixture(repo)
    selected = fixture[1][:550]
    env = {'FAIL_EXTRA': selected[-1]} if failure == 'build' else {'FAIL_RETRY': failure}
    done = run_hook(fixture, selected, **env)
    assert done.returncode == 1, done.stderr
    assert calls(fixture[0], 'receipt-calls.jsonl') == [['find', fixture[3]]]
    assert [source for chunk in calls(fixture[0]) for source in chunk] == selected


@pytest.mark.parametrize('failure', [None, 'build', 'cross', 'eh', 'data'])
def test_medium_carried_retry_checks_new_delta_and_preserves_failures(repo, failure):
    fixture = medium_receipt_fixture(repo)
    path, sources, base, verified = fixture
    selected = sources[:550]
    first = run_hook(fixture, selected)
    assert first.returncode == 0, first.stderr
    assert calls(path, 'receipt-calls.jsonl') == [['find', verified], ['record', verified]]
    prior_builds = len(calls(path))
    source = selected[0]
    hooks.write(path, source, '// changed after the verified medium gate\n')
    hooks.git(path, 'add', '--', source)
    hooks.git(path, 'commit', '-qm', 'incoming source change')
    pushed = hooks.git(path, 'rev-parse', 'HEAD')
    hooks.write(path, 'delta-retry.txt', source + '\n')
    env = {'CARRY_FROM': verified}
    if failure == 'build':
        env['FAIL_EXTRA'] = source
    elif failure:
        env['FAIL_RETRY'] = failure
    done = run_hook((path, sources, base, pushed), selected, **env)
    assert done.returncode == (1 if failure else 0), done.stderr
    assert calls(path)[prior_builds:] == [[source]]
    expected = [['find', pushed]]
    if failure != 'build':
        # every row is judged; only the source this retry verified is read again
        expected += [['cross-checks', verified, [source]]]
    if failure is None:
        # A passed carried retry becomes the nearest receipt for the next retry.
        expected += [['record', pushed]]
    assert calls(path, 'receipt-calls.jsonl')[2:] == expected


def unbounded_headers(fixture):
    path, sources, base, _ = fixture
    hooks.write(path, 'tools/header_dependents.py', 'raise SystemExit(2)\n')
    hooks.git(path, 'commit', '-qam', 'unbounded reference dependency fixture')
    return path, sources, base, hooks.git(path, 'rev-parse', 'HEAD')


@pytest.mark.parametrize('selected', [[], [EXTRA]], ids=['no-body-delta', 'rowless-extra'])
def test_unbounded_headers_build_full_tree_before_all_data(repo, selected):
    fixture = unbounded_headers(repo)
    done = run_hook(fixture, selected)
    assert done.returncode == 0, done.stderr
    assert calls(repo[0]) == ([[], selected] if selected else [[]])
    converged = calls(repo[0], 'conv-calls.jsonl')
    assert len(converged) == 1 and '--all' in converged[0]['argv']


def test_unbounded_header_full_failure_stops_before_eh_and_data(repo):
    fixture = unbounded_headers(repo)
    done = run_hook(fixture, [repo[1][0]], FAIL_FULL='1')
    assert done.returncode == 1 and 'full byte-verify' in done.stderr
    assert calls(repo[0]) == [[]]
    assert calls(repo[0], 'eh-calls.jsonl') == [
        ['--assert-shrink-range', fixture[2], fixture[3]]]
    assert not calls(repo[0], 'conv-calls.jsonl')


def test_unbounded_headers_bind_unselected_sources_before_build(repo):
    fixture = unbounded_headers(repo)
    hooks.write(repo[0], EXTRA, '// dirty unselected source\n')
    done = run_hook(fixture, [repo[1][0]])
    assert done.returncode == 1 and 'tracked source differs' in done.stderr
    assert not calls(repo[0])


def test_unbounded_headers_keep_rowless_refusal_after_full_build(repo):
    fixture = unbounded_headers(repo)
    done = run_hook(fixture, [EXTRA], FAIL_EXTRA=EXTRA)
    assert done.returncode == 1 and 'additional outgoing sources' in done.stderr
    assert calls(repo[0]) == [[], [EXTRA]]
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


@pytest.mark.parametrize('selected_kind', ['complete', 'subset', 'data-and-asm'])
def test_unbounded_headers_do_not_repeat_covered_providers(repo, selected_kind):
    fixture = unbounded_headers(repo)
    selected = {'complete': repo[1], 'subset': repo[1][:3],
                'data-and-asm': [ASM, DATA]}[selected_kind]
    done = run_hook(fixture, selected)
    assert done.returncode == 0, done.stderr
    assert calls(repo[0]) == [[]]
    assert calls(repo[0], 'eh-calls.jsonl') == [
        ['--assert-shrink-range', fixture[2], fixture[3]], selected]
    converged = calls(repo[0], 'conv-calls.jsonl')
    assert len(converged) == 1 and '--all' in converged[0]['argv']


@pytest.mark.parametrize('failure', ['', EXTRA], ids=['extra-kept', 'extra-refused'])
def test_unbounded_headers_filter_providers_but_keep_rowless_extras(repo, failure):
    fixture = unbounded_headers(repo)
    done = run_hook(fixture, repo[1] + [EXTRA], FAIL_EXTRA=failure)
    assert calls(repo[0]) == [[], [EXTRA]]
    assert done.returncode == (1 if failure else 0), done.stderr
    if failure:
        assert not calls(repo[0], 'conv-calls.jsonl')


def test_required_full_scope_uses_pushed_data_and_function_ledgers(repo):
    done, scope = classify(repo, [repo[1][0], ASM, DATA, EXTRA], full_required=1)
    assert done.returncode == 0 and scope == ['full', EXTRA], done.stderr
    done, scope = classify(repo, [repo[1][0], EXTRA], full_required=0)
    assert done.returncode == 0 and scope == ['chunks'], done.stderr


def test_required_full_scope_keeps_library_selectors_explicit(repo):
    done, scope = classify(repo, [repo[1][0], LIB], full_required=1)
    assert done.returncode == 0 and scope == ['full', LIB], done.stderr


def test_required_full_scope_refuses_malformed_provider_ledger(repo):
    hooks.write(repo[0], 'reverse/data_rows.csv', 'name\n?bad\n')
    hooks.git(repo[0], 'commit', '-qam', 'malformed data ledger')
    done, scope = classify(repo, [], 'HEAD', full_required=1)
    assert done.returncode != 0 and not scope


def test_unbounded_header_classifier_failure_stops_real_hook(repo):
    fixture = unbounded_headers(repo)
    hooks.write(repo[0], 'reverse/data_rows.csv', 'name\n?bad\n')
    hooks.git(repo[0], 'commit', '-qam', 'malformed data ledger')
    fixture = (*fixture[:3], hooks.git(repo[0], 'rev-parse', 'HEAD'))
    done = run_hook(fixture, [])
    assert done.returncode == 1 and 'proving full build scope' in done.stderr
    assert not calls(repo[0])


@pytest.mark.parametrize('failure', ['', '1'], ids=['consistent', 'two-addresses'])
def test_a_scoped_push_checks_dir32_over_its_sources(repo, failure):
    # 86dd4a6165 landed through a scoped push: its rows stayed exact while two of
    # them put one template static at two addresses, which only the full gate saw.
    fixture = receipt_log(repo)
    selected = fixture[1][:3]
    done = run_hook(fixture, selected, FAIL_SCOPED=failure)
    assert calls(fixture[0], 'scoped-calls.jsonl') == [sorted(selected)]
    assert done.returncode == (1 if failure else 0), done.stderr
    if failure:
        assert 'DIR32 consistency over the outgoing sources failed' in done.stderr


def test_a_full_gate_push_runs_no_scoped_dir32(repo):
    fixture = receipt_log(repo)
    done = run_hook(fixture)
    assert done.returncode == 0, done.stderr
    assert not calls(fixture[0], 'scoped-calls.jsonl')
