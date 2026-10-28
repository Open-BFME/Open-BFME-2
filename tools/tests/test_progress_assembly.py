"""Reviewed assembly counts as rebuilt, while dumps and C++ stay distinct."""
import sys
import xml.etree.ElementTree as ET
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import progress
import progress_site
import readme_progress


def test_reviewed_assembly_union_padding_and_cpp_precedence(monkeypatch):
    source = "Code/Libraries/Source/VP6/MmxIDct.asm"
    image = b'\x90' * 7 + b'\xcc' + b'\x90' * 24
    monkeypatch.setattr(progress, '_text_image', lambda: (0x1000, image))
    matched = {('asm', '0x1000'): (16, source),
               ('cpp', '0x1000'): (4, 'Code/f.cpp'),
               ('overlap', '0x1008'): (8, source),
               ('dump', '0x1010'): (8, 'Code/gen_asm/f.asm'),
               ('unknown-asm', '0x1018'): (8, 'Code/unknown.asm')}
    notes = {key: '' for key in matched}
    split = progress.real_split(matched, notes, 0x1000, 32)
    assert (split['authored'], split['assembly'], split['dump']) == (4, 11, 16)
    assert progress.rebuildable(split) == 15
    assert progress.decompiled(split) == 4
    assert readme_progress.measures(dict(split, total=31))['authored'] == (4, 31)  # assembly is not hand-written
    assert readme_progress.measures(dict(split, total=31))['matched'] == (15, 31)
    owners = progress_site.per_source(matched, notes, 0x1000, 32, ())
    for lane in progress.SOURCE_LANES:
        assert sum(counts[lane] for counts in owners.values()) == split[lane]
    assert progress.source_lane('Code/gen_asm/MmxIDct.asm', '', False) == 'dump'
    assert progress.source_lane('Code/f.cpp', '', True) == 'dump'
    assert progress.source_lane(source, 'gen-dump;', False) == 'dump'


def test_accounting_change_is_not_reported_as_new_recovery():
    old = dict(total=100, authored=40, vendored=5, generated=10, library=5)
    new = dict(old, assembly=10)
    assert readme_progress.delta_since(old, 'matched', 70, 100, new) is None
    svg = readme_progress.render(new, old)
    post = readme_progress.announcement(new, old)['embeds'][0]['description']
    rendered_text = ' '.join(' '.join(ET.fromstring(svg).itertext()).split())
    assert 'accounting changed' in svg and 'not new recovery' in rendered_text
    assert 'accounting changed' in post and 'not new recovery' in post
    assert readme_progress.delta_since(new, 'matched', 71, 100, dict(new, assembly=11)) > 0


def test_only_documented_assembly_exceptions_are_admitted():
    for source in progress.REBUILT_ASM_SOURCES:
        assert progress.source_lane(source, '', False) == 'assembly'
        assert progress.source_lane(source, 'gen-dump;', False) == 'dump'
    assert progress.source_lane('Code/masm_dumps/Other.asm', '', False) == 'dump'
