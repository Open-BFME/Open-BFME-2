"""pre-push with receipts (tools/push_receipts.py): a scoped push byte-verifies
exactly the units no receipt proves, the audits still judge the whole scope, and
a passing push records its own receipt. The receipt logic itself is
test_push_receipts.py; here push_receipts.py is a stub whose answers the tests set."""
import json

import pytest

import test_hook_fail_closed as hooks
from test_pre_push_chunks import calls, medium_receipt_fixture, repo, run_hook  # noqa: F401

STUB = """import json, os, sys
args = sys.argv[1:]
with open('receipts-calls.jsonl', 'a', encoding='utf-8') as out:
    out.write(json.dumps(args[:1]) + '\\n')


def emit(name):
    items = [i for i in os.environ.get(name, '').split(',') if i]
    sys.stdout.buffer.write(b''.join(i.encode() + b'\\0' for i in items))


if args[0] == 'cover':
    emit('RECEIPT_COVER')
elif args[0] == 'previous':
    if os.environ.get('RECEIPT_PREV'):
        print(os.environ['RECEIPT_PREV'])
elif args[0] == 'units':
    emit('RECEIPT_UNITS')
elif args[0] == 'stale':
    emit('RECEIPT_STALE')
elif args[0] == 'record-push':
    listing = open(args[args.index('--units-from') + 1], 'rb').read()
    with open('receipt-records.jsonl', 'a', encoding='utf-8') as out:
        out.write(json.dumps({'from': args[args.index('--from') + 1] if '--from' in args else None,
                              'units': sorted(p.decode() for p in listing.split(b'\\0') if p)}) + '\\n')
"""


@pytest.fixture
def receipted(repo):  # noqa: F811
    fixture = medium_receipt_fixture(repo)
    path = fixture[0]
    hooks.write(path, 'tools/push_receipts.py', STUB)
    hooks.git(path, 'add', '--', 'tools/push_receipts.py')
    hooks.git(path, 'commit', '-qm', 'receipt stub')
    return path, fixture[1], fixture[2], hooks.git(path, 'rev-parse', 'HEAD')


def built(path):
    return sorted(source for chunk in calls(path) for source in chunk)


def eh_scope(path):
    return [sorted(c) for c in calls(path, 'eh-calls.jsonl') if c and not c[0].startswith('--')]


def test_without_receipts_every_unit_is_verified(receipted):
    path, sources = receipted[0], receipted[1]
    selected = sources[:3]
    done = run_hook(receipted, selected)
    assert done.returncode == 0, done.stderr
    assert built(path) == sorted(selected)
    assert json.loads((path / 'receipt-records.jsonl').read_text())['units'] == sorted(selected)


def test_units_the_commit_receipts_prove_are_not_built_again(receipted):
    path, sources = receipted[0], receipted[1]
    selected = sources[:3]
    done = run_hook(receipted, selected, RECEIPT_COVER=','.join(selected[:2]))
    assert done.returncode == 0, done.stderr
    assert built(path) == [selected[2]]
    assert eh_scope(path) == [sorted(selected)]                # the audits judge the whole scope
    assert '2 of 3 source(s) proven by receipts' in done.stdout


def test_an_intersection_with_masters_changes_reverifies_exactly_those_units(receipted):
    # A lost race: the previous push of `prev` proved all three; master's commits
    # since then (scope_from prev: delta-retry.txt) reach only the first.
    path, sources = receipted[0], receipted[1]
    selected = sources[:3]
    prev = receipted[2]
    hooks.write(path, 'delta-retry.txt', selected[0] + '\n')
    done = run_hook(receipted, selected, RECEIPT_PREV=prev, RECEIPT_UNITS=','.join(selected), CARRY_FROM=prev)
    assert done.returncode == 0, done.stderr
    assert built(path) == [selected[0]]
    assert json.loads((path / 'receipt-records.jsonl').read_text())['from'] == prev


def test_a_proven_unit_whose_object_is_not_current_is_built(receipted):
    path, sources = receipted[0], receipted[1]
    selected = sources[:3]
    done = run_hook(receipted, selected, RECEIPT_COVER=','.join(selected), RECEIPT_STALE=selected[1])
    assert done.returncode == 0, done.stderr
    assert built(path) == [selected[1]]


def test_a_refused_build_still_fails_the_push(receipted):
    path, sources = receipted[0], receipted[1]
    selected = sources[:3]
    done = run_hook(receipted, selected, RECEIPT_COVER=','.join(selected[:2]), FAIL_EXTRA=selected[2])
    assert done.returncode == 1
    assert not (path / 'receipt-records.jsonl').exists()        # a failed push records nothing


def test_a_large_scope_uses_no_push_receipts(receipted):
    path = receipted[0]
    done = run_hook(receipted)
    assert done.returncode == 0, done.stderr
    assert calls(path) == [[]]                                  # the full gate, as before
    assert not (path / 'receipts-calls.jsonl').exists()
