import json
import sys
from pathlib import Path
sys.path.insert(0, 'tools')
import build
import link_census as census
old = '?getID@Drawable@@QBE?AW4DrawableID@@XZ'
new = '?get@Rva0055A88BDwordField@@QBEHXZ'
source = 'Code/GameEngine/Source/GameClient/GameClient.cpp'
before = Path('build/gc_getid/before.obj').read_bytes()
after = build.obj_path(source).read_bytes()
def externals(data, defined):
    return {s['name'] for s in census._coff_symbols(data) if s['storage'] == census.EXTERNAL and (s['section'] > 0 if defined else s['section'] == 0 and s['value'] == 0)}
assert externals(before, True) == externals(after, True)
assert externals(before, False) - externals(after, False) == {old}
assert externals(after, False) - externals(before, False) == {new}
def normalized(data):
    out = {}
    for symbol, body, relocs, digest, size in census._comdat_sections(data):
        refs = []
        for offset, kind, target in relocs:
            name = target['name']
            name = new if name == old else name
            label = census._normal(name) if target['storage'] in (census.EXTERNAL, census.WEAK_EXTERNAL) else 'local'
            refs.append((offset, kind, label))
        out[symbol['name']] = (body, size, refs)
    return out
assert normalized(before) == normalized(after)
before_digests = {symbol['name']: digest for symbol, _, _, digest, _ in census._comdat_sections(before)}
changed = sorted(symbol['name'] for symbol, _, _, digest, _ in census._comdat_sections(after) if before_digests[symbol['name']] != digest)
provider = build.obj_path('Code/GameEngine/Source/Common/DispDwordFieldGetters.cpp')
assert new in externals(provider.read_bytes(), True)
out = {'source': source, 'provider_defines_replacement': True,
       'external_definitions_preserved': len(externals(after, True)),
       'external_comdats_preserved': len(normalized(after)), 'changed_comdats': changed,
       'removed_undefined': old, 'added_undefined': new,
       'normalized_comdat_bytes_sizes_relocations_equal': True}
print(json.dumps(out, indent=2))
