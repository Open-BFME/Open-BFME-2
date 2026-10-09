#!/usr/bin/env python3
"""Conservatively select outgoing sources affected by compiler flag decisions.

Only committed inputs are read. No compiler or historical Python is executed.
Prints one source per line; failed Git or malformed snapshots refuse.
"""
import argparse
import csv
import hashlib
import io
import subprocess
import sys
from collections import defaultdict
from pathlib import Path, PurePosixPath

ROOT = Path(__file__).resolve().parents[1]
LEDGER = 'reverse/functions.csv'
REGIONS = 'reverse/retail_inventory/flag_regions.csv'
OVERRIDES = 'reverse/flag_overrides.csv'
DATA_ROWS = 'reverse/data_rows.csv'
LEDGER_HEADER = ('name', 'export_rva', 'target_rva', 'target_size', 'source', 'status', 'notes')
DATA_HEADER = ('name', 'address', 'address_kind', 'size', 'section', 'source', 'status', 'evidence', 'model')
SUPPORTED = {'.cpp', '.c', '.asm', '.lib'}

class SnapshotError(ValueError):
    pass

def git(*args):
    got = subprocess.run(['git', '-C', str(ROOT), *args], capture_output=True)
    if got.returncode:
        raise SnapshotError('Git failed: ' + got.stderr.decode('utf-8', errors='replace').strip())
    return got.stdout

def blob(rev, path, required=False):
    entry = git('ls-tree', rev, '--', path).strip()
    if not entry:
        if required:
            raise SnapshotError(f'{rev}: missing {path}')
        return None
    if not entry.startswith((b'100644 blob ', b'100755 blob ')) or b'\n' in entry:
        raise SnapshotError(f'{rev}: {path} is not one regular file')
    return git('show', f'{rev}:{path}')

def rows(data, required, label):
    if data is None:
        return []
    try:
        reader = csv.DictReader(io.StringIO(data.decode('utf-8-sig')), strict=True)
        if not reader.fieldnames or not set(required) <= set(reader.fieldnames):
            raise SnapshotError(f'{label}: malformed CSV header')
        result = []
        for row in reader:
            if None in row or any(row.get(field) is None for field in required):
                raise SnapshotError(f'{label}: malformed CSV row')
            result.append(row)
        return result
    except (UnicodeError, csv.Error) as exc:
        raise SnapshotError(f'{label}: {exc}') from exc

def managed(source):
    return source.startswith('Code/') and PurePosixPath(source).suffix.lower() in {'.c', '.cpp'}

def valid_source(source):
    path = PurePosixPath(source)
    if not source or '\0' in source or '\n' in source or '\r' in source or '\\' in source or path.is_absolute() or '..' in path.parts:
        raise SnapshotError(f'unsafe source path: {source!r}')

def ledger(data, label):
    matched, votes = set(), defaultdict(list)
    # Retain only source set and vote hashes, not the full ledger in memory.
    try:
        reader = csv.DictReader(io.StringIO(data.decode('utf-8-sig')))
        required = {'source', 'status', 'target_rva', 'target_size'}
        if tuple(reader.fieldnames or ()) != LEDGER_HEADER:
            raise SnapshotError(f'{label}: malformed ledger header')
        for row in reader:
            if None in row or any(value is None for value in row.values()):
                raise SnapshotError(f'{label}: malformed ledger row')
            if tuple(row.values()) == LEDGER_HEADER:
                raise SnapshotError(f'{label}: repeated ledger header')
            if row['status'] != 'matched':
                continue
            source = row['source']; valid_source(source)
            rva, size = int(row['target_rva'], 16), int(row['target_size'])
            if not 0 <= rva <= 0xffffffff or size <= 0:
                raise SnapshotError(f'{label}: invalid row range')
            if row['status'] == 'matched':
                if PurePosixPath(source).suffix.lower() in SUPPORTED:
                    matched.add(source)
                if managed(source):
                    votes[source].append((rva, size))
        votes = {s: hashlib.sha256(repr(sorted(values)).encode()).digest() for s, values in votes.items()}
        return matched, votes
    except (UnicodeError, csv.Error, ValueError) as exc:
        if isinstance(exc, SnapshotError):
            raise
        raise SnapshotError(f'{label}: {exc}') from exc

def data_sources(data, label):
    """Data-only units are compiled by the same driver and flag resolver."""
    if data is None:
        return set()
    try:
        reader = csv.DictReader(io.StringIO(data.decode('utf-8-sig')))
        if tuple(reader.fieldnames or ()) != DATA_HEADER:
            raise SnapshotError(f'{label}: malformed data ledger header')
        matched = set()
        for row in reader:
            if None in row or any(value is None for value in row.values()):
                raise SnapshotError(f'{label}: malformed data ledger row')
            if tuple(row.values()) == DATA_HEADER:
                raise SnapshotError(f'{label}: repeated data ledger header')
            if row['status'] == 'matched':
                valid_source(row['source'])
                if PurePosixPath(row['source']).suffix.lower() in SUPPORTED:
                    matched.add(row['source'])
        return matched
    except (UnicodeError, csv.Error) as exc:
        raise SnapshotError(f'{label}: {exc}') from exc


def regions(data, label):
    parsed = rows(data, ('rva_start', 'rva_end', 'opt', 'arch', 'tune', 'n_funcs', 'n_opt_evidence'), label)
    for r in parsed:
        try:
            low, high = int(r['rva_start'], 16), int(r['rva_end'], 16)
            if low < 0 or high < low or r['opt'] not in {'O1', 'O2', 'Od', 'Ox'} or r['arch'] not in {'?', 'SSE', 'SSE2', 'x87'} or r['tune'] not in {'?', 'G6', 'G7'}:
                raise ValueError('invalid region values')
            if int(r['n_funcs']) <= 0 or int(r['n_opt_evidence']) < 0:
                raise ValueError('invalid evidence count')
        except ValueError as exc:
            raise SnapshotError(f'{label}: {exc}') from exc
    # The resolver stable-sorts by numeric start and bisect_right picks the
    # LAST equal-start entry. Preserve ties: sorting complete row tuples loses
    # compiler-significant input order.
    return [tuple(sorted(r.items())) for r in
            sorted(parsed, key=lambda r: int(r['rva_start'], 16))]

def overrides(data, label):
    parsed = rows(data, ('source', 'flags', 'rows', 'default_lost', 'reason'), label)
    result = {}
    for r in parsed:
        valid_source(r['source'])
        if r['source'] in result or not managed(r['source']):
            raise SnapshotError(f'{label}: duplicate or unmanaged override')
        try:
            if int(r['rows']) < 0 or int(r['default_lost']) < 0:
                raise ValueError('negative override count')
        except ValueError as exc:
            raise SnapshotError(f'{label}: {exc}') from exc
        result[r['source']] = tuple(sorted(r.items()))
    return result

def select(base, tip):
    for rev in (base, tip):
        git('rev-parse', '--verify', '--end-of-options', rev + '^{commit}')
    old_matched, old_votes = ledger(blob(base, LEDGER, True), base)
    tip_matched, tip_votes = ledger(blob(tip, LEDGER, True), tip)
    # Missing historical data_rows.csv is legitimate; blob() fails on Git errors.
    tip_matched |= data_sources(blob(tip, DATA_ROWS), tip)
    data_sources(blob(base, DATA_ROWS), base)  # refuse malformed old inputs too
    old_regions, new_regions = [regions(blob(rev, REGIONS), rev) for rev in (base, tip)]
    old_overrides, new_overrides = [overrides(blob(rev, OVERRIDES), rev) for rev in (base, tip)]
    changed_driver = any(blob(base, p) != blob(tip, p) for p in ('tools/build.py', 'build.sh', 'build.cmd'))
    changed_resolver = blob(base, 'tools/flag_defaults.py') != blob(tip, 'tools/flag_defaults.py')
    if changed_driver:
        return sorted(tip_matched)
    selected = {s for s in tip_matched if managed(s)} if changed_resolver or old_regions != new_regions else set()
    selected |= {s for s in tip_matched if managed(s) and old_votes.get(s) != tip_votes.get(s)}
    selected |= {s for s in set(old_overrides) | set(new_overrides)
                 if s in tip_matched and old_overrides.get(s) != new_overrides.get(s)}
    return sorted(selected)

def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    parser.add_argument('--range', nargs=2, required=True, metavar=('BASE', 'TIP'))
    args = parser.parse_args(argv)
    if hasattr(sys.stdout, 'reconfigure'):
        sys.stdout.reconfigure(newline='\n')
    try:
        for source in select(*args.range):
            print(source)
    except SnapshotError as exc:
        print('flag_delta_sources: ' + str(exc), file=sys.stderr)
        return 1
    return 0

if __name__ == '__main__':
    sys.exit(main())
