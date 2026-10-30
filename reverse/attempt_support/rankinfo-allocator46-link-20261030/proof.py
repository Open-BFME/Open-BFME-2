import csv, json, struct, sys
from pathlib import Path
sys.path.insert(0, 'tools')
import build
import link_check

source = 'Code/GameEngine/Source/GameLogic/System/RankInfoCtor.cpp'
before = Path('build/rankinfo-allocator46-link-20261030/before.obj')
after = build.obj_path(Path(source))
old_allocator = '?allocate@?$allocator@H@_STL@@QBEPAHIPBX@Z'
new_allocator = '?allocate@?$allocator@H@_STL@@QAEPAHIPBX@Z'
with Path('reverse/functions.csv').open(newline='') as f:
    rows = [r for r in csv.DictReader(f) if r['source'] == source]
assert len(rows) == 4
proof = {'source': source, 'rows': {}, 'changed_relocations': []}
for row in rows:
    name = row['name']
    old_body, old_relocs = build.read_object_symbol_bytes(before, name, code_only=True)
    new_body, new_relocs = build.read_object_symbol_bytes(after, name, code_only=True)
    assert old_body == new_body
    expected = [(offset, kind, new_allocator if symbol == old_allocator else symbol)
                for offset, kind, symbol in old_relocs]
    assert new_relocs == expected
    for old, new in zip(old_relocs, new_relocs):
        if old != new:
            offset = new[0]
            rva = int(row['target_rva'], 16)
            native = build.read_target_bytes(rva, int(row['target_size']))
            assert new[1] == 20 and native[offset - 1] == 0xE8
            target = rva + offset + 4 + struct.unpack_from('<i', native, offset)[0]
            assert target == 0x68E15
            proof['changed_relocations'].append({'caller': name, 'offset': offset, 'old': old[2], 'new': new[2], 'native_target': hex(target)})
    proof['rows'][name] = {'rva': row['target_rva'], 'size': row['target_size'],
                           'raw_code_identical': True, 'relocations': new_relocs}
assert len(proof['changed_relocations']) == 1
def symbols(path, defined):
    return sorted(s['name'] for s in build.read_object_symbols(path.read_bytes())
                  if s.get('storage') == 2 and (s['section'] > 0 if defined else s['section'] == 0))
old_def, new_def = set(symbols(before, True)), set(symbols(after, True))
removed_helpers = {
    '??$__stl_alloc_rebind@HH@_STL@@YAAAV?$allocator@H@0@AAV10@PBH@Z',
    '?allocate@?$_STLP_alloc_proxy@PAHHV?$allocator@H@_STL@@@_STL@@QAEPAHI@Z',
}
assert old_def - new_def == removed_helpers and not new_def - old_def
for name in sorted(new_def):
    old_body, old_relocs = build.read_object_symbol_bytes(before, name)
    new_body, new_relocs = build.read_object_symbol_bytes(after, name)
    assert old_body == new_body
    assert new_relocs == [(o, k, new_allocator if n == old_allocator else n) for o, k, n in old_relocs]
old_ref, new_ref = set(symbols(before, False)), set(symbols(after, False))
assert old_ref - new_ref == {old_allocator}
assert new_ref - old_ref == {new_allocator}
proof['external_definitions_preserved'] = sorted(new_def)
proof['removed_definitions'] = sorted(removed_helpers)
proof['removed_externals'] = sorted(old_ref - new_ref)
proof['added_externals'] = sorted(new_ref - old_ref)
index = link_check.load_index()
proof['index'] = index['meta']
proof['removed_helper_index_evidence'] = {}
for name in sorted(removed_helpers):
    other = [index['objects'][i] for i, _, _ in index['comdat'].get(name, ()) if index['objects'][i] != after.name]
    assert other and not link_check.is_referenced(index, name)
    proof['removed_helper_index_evidence'][name] = {
        'other_provider_count': len(other), 'example_objects': other[:3],
        'referenced_in_index': False, 'scope': 'published index; not a current whole-tree receipt'}
out = Path('build/rankinfo-allocator46-link-20261030/proof.json')
out.write_text(json.dumps(proof, indent=2) + '\n')
print('All four raw code bodies and every retained definition preserved; two obsolete proxy helpers removed; the sole external/row-relocation change binds the 4.6 allocator to native 00068E15.')
