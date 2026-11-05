import json
import sys
from pathlib import Path
sys.path.insert(0, 'tools')
import build
import link_census as census
old = '?get@Rva0055A88BDwordField@@QBEHXZ'
new = '?getID@Drawable@@QBE?AW4DrawableID@@XZ'
base = Path('build/drawable-selection-real-getter')
report = []
for source in ['Code/GameEngine/Source/GameClient/InGameUISelectDrawable.cpp', 'Code/GameEngine/Source/GameClient/InGameUI.cpp', 'Code/GameEngine/Source/GameClient/InGameUIXfer.cpp']:
    before = (base/(Path(source).stem+'.before.obj')).read_bytes()
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
    changed = [symbol['name'] for symbol, _, _, digest, _ in census._comdat_sections(after) if before_digests[symbol['name']] != digest]
    assert len(changed) == 1
    report.append({'source': source, 'external_definitions_preserved': len(externals(after, True)), 'external_comdats_preserved': len(normalized(after)), 'changed_comdat': changed[0], 'removed_undefined': old, 'added_undefined': new, 'normalized_comdat_bytes_sizes_relocations_equal': True})
provider = build.obj_path('Code/GameEngine/Source/GameClient/Drawable.cpp')
assert new in externals(provider.read_bytes(), True)
(base/'object-audit.json').write_text(json.dumps({'provider_defines_replacement': True, 'consumers': report}, indent=2)+'\n')
print((base/'object-audit.json').read_text())
