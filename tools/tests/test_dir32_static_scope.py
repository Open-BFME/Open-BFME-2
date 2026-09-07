"""Same-named static data in two COFF objects has independent identity."""
import importlib
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))


@pytest.mark.parametrize('storage,same_source,valid', [(3, False, True),
                                                     (3, True, False),
                                                     (2, False, False)])
def test_static_scope_preserves_real_conflict_detection(monkeypatch, tmp_path,
                                                       storage, same_source, valid):
    build = importlib.import_module('build')
    (tmp_path / 'reverse').mkdir()
    (tmp_path / 'reverse/dir32_consistency_whitelist.txt').write_text('')
    objects = [tmp_path / 'a.obj', tmp_path / ('a.obj' if same_source else 'b.obj')]
    for obj in objects:
        obj.write_bytes(b'fixture')
    rows = [{'name':f'function{i}', 'target_rva':hex(0x1000+i*0x10),
             'target_size':'7', 'source':f'Code/{obj.stem}.cpp', 'notes':''}
            for i, obj in enumerate(objects)]
    monkeypatch.setattr(build, 'ROOT', tmp_path)
    monkeypatch.setattr(build, 'require_row_object', lambda row:
                        objects[int(row['name'][-1])])
    monkeypatch.setattr(build, 'read_target_bytes', lambda rva,size:
                        b'\xd9\x05' + struct.pack('<I', 0x402000+(rva-0x1000)*0x10) + b'\xc3')
    monkeypatch.setattr(build, 'read_object_symbol_bytes', lambda *args:
                        (b'\xd9\x05\x00\x00\x00\x00\xc3', [(2,6,'_constant')]))
    monkeypatch.setattr(build, '_object_layout', lambda *args:
                        (b'', [], [{'name':'_constant','storage':storage,'section':1}]))
    if valid:
        build.verify_dir32_consistency(rows)
    else:
        with pytest.raises(SystemExit):
            build.verify_dir32_consistency(rows)
