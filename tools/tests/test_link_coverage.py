"""Inclusive linking counts verified executable providers, one census at a time."""
import sys
import xml.etree.ElementTree as ET
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import progress as p
import readme_progress as daily
import progress_site


def test_global_partition_overlap_padding_data_and_unassessed_assembly(monkeypatch):
    image = bytearray(b'\x90' * 64)
    image[5] = 0xCC
    monkeypatch.setattr(p, '_text_image', lambda: (0x1000, bytes(image)))
    monkeypatch.setattr(p, 'real_code_denominator', lambda *a: (1, 63))
    asm = 'Code/Libraries/Source/VP6/MmxIDct.asm'
    rows = {('a', '0x1000'): (8, 'Code/a.cpp'),
            ('g', '0x1004'): (12, 'Code/gen_small/g.cpp'),
            ('v', '0x1010'): (4, 'vendor/v.cpp'),
            ('l', '0x1014'): (4, 'vendor/v.lib'),
            ('s', '0x1018'): (4, asm),
            ('d', '0x101c'): (4, 'Code/gen_asm/d.asm')}
    notes = {key: '' for key in rows}
    data = [(0x1020, 0x1024, 'Code/data.cpp')]
    clean = {'Code/a.cpp', 'Code/gen_small/g.cpp', 'vendor/v.cpp',
             'vendor/v.lib', 'Code/gen_asm/d.asm', 'Code/data.cpp'}
    result = p.linked_game_coverage(rows, notes, set(), clean, 0x1000, 64, data)
    assert result['linked_game_executable'] == 15  # union, minus one CC
    assert result['game_executable'] == 51  # retains unclaimed executable bytes
    assert p.linked_game_coverage(rows, notes, set(), clean | {asm}, 0x1000, 64, data)['linked_game_executable'] == 19


def test_inclusive_snapshot_and_accounting_transition():
    old = dict(total=100, authored=60, generated=10, assembly=5, vendored=5,
               library=5, data=5, linked_authored=50, linked_game_code=90)
    new = dict(old, linked_game_executable=65, game_executable=85,
               link_coverage_rules=p.LINK_COVERAGE_RULES)
    assert daily.measures(new)['linked'] == (65, 85)
    assert daily.measures(old)['linked'] == (50, 90)
    text = daily.announcement(new, old)['embeds'][0]['description']
    assert 'accounting changed' in text and daily.UP not in text
    assert 'Generated linked code now counted' in text
    svg = ET.fromstring(daily.render(new, old))
    assert max(float(node.attrib['y']) for node in svg.iter() if node.tag.endswith('text')) < float(svg.attrib['height'])
    del new['game_executable']
    with pytest.raises(ValueError, match='Incomplete linking'):
        daily.measures(new)


def test_recalculation_refuses_status_not_reproducing_recorded_bytes(monkeypatch):
    monkeypatch.setattr(p, 'census_at', lambda ref: dict(commit='tree', date='date', rules='r',
                        linked_authored='999', linked_bytes='999', game_code='10'))
    monkeypatch.setattr(p.subprocess, 'run', lambda *a, **k: SimpleNamespace(returncode=0, stdout='report'))
    monkeypatch.setattr(p, '_text_at', lambda *a: 'source,linked\nCode/a.cpp,yes\n')
    monkeypatch.setattr(p, 'matched_at', lambda ref: {})
    monkeypatch.setattr(p, 'notes_at', lambda ref: {})
    monkeypatch.setattr(p, 'naked_cpp_rows_at', lambda *a: set())
    monkeypatch.setattr(p, 'retail_text', lambda: (0, 10))
    monkeypatch.setattr(p, 'real_split', lambda *a, **k: dict(authored=1, vendored=0, library=0))
    monkeypatch.setattr(p, 'real_code_denominator', lambda *a: (0, 10))
    p.linking_coverage_at.cache_clear()
    assert p.linking_coverage_at('inconsistent-status-test') is None


def test_chart_separates_legacy_and_inclusive_accounting():
    history = [dict(date='2026-10-01', byte_matched='80', total='100'),
               dict(date='2026-10-02', byte_matched='90', total='100')]
    old = dict(date='2026-10-01', linked_authored='60', game_code='100', rules='retail-truth-4')
    new = dict(old, date='2026-10-02', linked_game_executable='85',
               game_executable='90', link_coverage_rules=p.LINK_COVERAGE_RULES)
    chart = progress_site._chart(history, [old, new])
    assert 'linking 94.44%' in chart
    assert 'accounting changed' in chart and 'not progress' in chart
