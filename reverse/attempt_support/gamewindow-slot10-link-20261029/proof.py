import json, struct, sys
from pathlib import Path
sys.path.insert(0, 'tools')
import build
w = Path('build/gamewindow-slot10-link-20261029')
image = build.EXE.read_bytes()
sections = build.pe_sections(image)
native = build.read_pe_bytes(image, sections, 0x80BBCC, 44)
assert struct.unpack_from('<I', native, 40)[0] == 0x90B5C6
body = build.read_pe_bytes(image, sections, 0x50B5C6, 3)
assert body == bytes.fromhex('b001c3')
source = 'Code/GameEngine/Source/Common/VtableConstantPredicates.cpp'
proof = {'native_table_rva': '0x0080BBCC', 'native_table_bytes': native.hex(),
         'native_body_rva': '0x0050B5C6', 'native_body_bytes': body.hex(),
         'unique_coverage_gain': 0, 'copies': {}}
for symbol in ['?rva0050B5C6@Rva0050B5C6@@QAE_NXZ', '?vslot10@GameWindow@@UAE_NXZ']:
    compiled, relocs = build.read_object_symbol_bytes(build.obj_path(source), symbol, code_only=True)
    assert compiled == body and not relocs
proof['byte_and_relocation_twins'] = True
old = json.loads(Path('reverse/attempt_support/gamewindow-predicate-slots-link-20261028/table-proof.json').read_text())
for source in ['Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp',
               'Code/GameEngine/Source/GameClient/GUI/GameWindowDtor.cpp']:
    data = build.obj_path(source).read_bytes()
    symbols = build.read_object_symbols(data)
    table = next(s for s in symbols if s['name'] == '??_7GameWindow@@6B@' and s['section'] > 0)
    section = 20 + (table['section'] - 1) * 40
    size = struct.unpack_from('<I', data, section + 16)[0]
    pos = struct.unpack_from('<I', data, section + 24)[0]
    count = struct.unpack_from('<H', data, section + 32)[0]
    relocs = []
    for n in range(count):
        offset, index, kind = struct.unpack_from('<IIH', data, pos + n * 10)
        relocs.append([offset, kind, symbols[index]['name']])
    assert size == 44
    expected = old['table_copies'][source]['relocations']
    expected[-1] = [40, 6, '?vslot10@GameWindow@@UAE_NXZ']
    assert relocs == expected
    proof['copies'][source] = {'size': size, 'relocations': relocs}
(w/'table-proof.json').write_text(json.dumps(proof, indent=2) + '\n')
print('Both eleven-slot tables preserve slots0..9 and bind slot10 to the exact relocation-free native constant.')
