"""Coverage of gate-verified data embedded in the executable code section."""
import csv
import io
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import data_rows
import progress
import progress_site
import readme_progress


def ledger(*rows):
    out = io.StringIO()
    writer = csv.writer(out)
    writer.writerow(data_rows.FIELDS)
    for address, kind, section, status in rows:
        writer.writerow(['_table', address, kind, '16', section,
                         'Code/table.cpp', status, 'verified initializer', 'test'])
    return out.getvalue()


def test_data_ledger_is_read_at_each_requested_revision(monkeypatch):
    states = {
        'old': None,
        'new': ledger(('0x00401000', 'va', '.text', 'matched')),
        None: ledger(('0x1010', 'rva', '.text', 'matched'),
                     ('0x2000', 'rva', '.rdata', 'matched'),
                     ('0x1030', 'rva', '.text', 'blocked')),
    }
    monkeypatch.setattr(progress, '_text_at', lambda ref, path: states[ref])
    assert progress.text_data_at('old') == []
    assert progress.text_data_at('new') == [(0x1000, 0x1010, 'Code/table.cpp')]
    assert progress.text_data_at(None) == [(0x1010, 0x1020, 'Code/table.cpp')]


@pytest.mark.parametrize('raw', ['bad header', ledger(('0x1000', 'guess', '.text', 'matched'))])
def test_malformed_data_claim_fails_instead_of_inflating_progress(monkeypatch, raw):
    monkeypatch.setattr(progress, '_text_at', lambda *a: raw)
    with pytest.raises(SystemExit, match='invalid data_rows.csv'):
        progress.text_data_at(None)


def test_data_union_clipping_padding_and_function_totals(monkeypatch):
    # Two functions overlap the table. Data must gain only unique bytes, while
    # a former dump inside the table yields to the stronger typed-data claim.
    image = b'\x90' * 4 + b'\xcc' + b'\x90' * 27
    monkeypatch.setattr(progress, '_text_image', lambda: (0x1000, image))
    matched = {('f', '0x1000'): (4, 'Code/f.cpp'),
               ('dump', '0x1008'): (8, 'Code/dump.asm')}
    notes = {key: '' for key in matched}
    data = [(0x0FF8, 0x1010, 'Code/table.cpp'),
            (0x1004, 0x1010, 'Code/table.cpp'),
            (0x101E, 0x1040, 'Code/end.cpp')]
    before = progress.real_split(matched, notes, 0x1000, 32)
    after = progress.real_split(matched, notes, 0x1000, 32, text_data=data)
    assert after['authored'] == before['authored'] == 4
    assert after['data'] == 13  # 12 new table bytes - one CC + two end bytes
    assert after['dump'] == 0
    assert progress.rebuildable(after) == 17
    assert progress.decompiled(after) == progress.decompiled(before) == 4
    assert progress.game_code(after, 31) == progress.game_code(before, 31)
    # Data is never executable code: the Game code in C++* denominator drops
    # by it, the game's own code (the census's stored game_code) does not.
    assert progress.game_executable(after, 31) == progress.game_code(after, 31) - 13
    assert progress.game_executable(before, 31) == progress.game_code(before, 31)
    filtered = progress.real_split(matched, notes, 0x1000, 32,
                                   keep=lambda *a: True, text_data=data)
    assert filtered['data'] == 0  # function-name filters cannot credit data
    stats = progress.coverage(matched, 0x1000, 32, text_data=data)
    assert (stats['cpp'], stats['asm_only'], stats['data_only'], stats['exact']) == (4, 8, 6, 18)
    owners = progress_site.per_source(matched, notes, 0x1000, 32, (), data)
    for lane in progress.SOURCE_LANES:
        assert sum(counts[lane] for counts in owners.values()) == after[lane]


def test_keyboard_table_counts_4094_without_becoming_function_code(monkeypatch):
    image = bytearray(b'\x00' * 4096)
    image[204 * 16 + 4] = image[204 * 16 + 9] = 0xCC
    monkeypatch.setattr(progress, '_text_image', lambda: (0x629F20, bytes(image)))
    split = progress.real_split({}, {}, 0x629F20, 4096,
                                text_data=[(0x629F20, 0x62AF20, 'Code/keyboard.cpp')])
    assert split['data'] == progress.rebuildable(split) == 4094
    assert progress.decompiled(split) == split['authored'] == 0
    current = dict(split, total=4094, linked_authored=None, linked_game_code=None)
    assert readme_progress.measures(current)['matched'] == (4094, 4094)
    assert readme_progress.measures(current)['authored'] == (0, 0)  # data is never code C++ could cover
    assert readme_progress.blocks(0, 0, readme_progress.BLOCK['authored']) == readme_progress.REST_BLOCK * 10
