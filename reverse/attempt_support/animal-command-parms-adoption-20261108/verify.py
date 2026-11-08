from pathlib import Path
import csv, hashlib, json
import build as B
import link_census as C
import link_check as K
import reloc_ledger as R

lab = Path('build/animal-command-parms-adoption-20261108')
source = 'Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AnimalAIUpdate.cpp'
providers = ['Code/GameEngine/Source/Common/Rva00336B23AICommand.cpp',
             'Code/GameEngine/Source/Common/AICommandInterface_aiMoveToObject.cpp']
coords_dtor = '??1RvaCoords@@QAE@XZ'
parms_dtor = '??1AICommandParms@@QAE@XZ'

def facts(raw):
    sections, syms = R.parse_coff(raw)
    policies = C._comdat_selections(raw)
    names = {s['name']: s for s in syms.values() if s['storage'] == 2 and s['section'] > 0}
    code = {s['name']: (body, [(o, k, target['name']) for o, k, target in relocs],
                       sections[s['section']-1]['flags'], policies.get(s['section']))
            for s, body, relocs, digest, size in C._comdat_sections(raw)}
    data = {}
    for name, sym in names.items():
        sec = sections[sym['section']-1]
        if sec['flags'] & 0x20000000 or sec['name'].startswith('.debug') or sec['name'] in ('.drectve', '.sxdata'):
            continue
        start = sym['value']
        end = min((s['value'] for s in syms.values() if s['section'] == sym['section'] and s['value'] > start), default=sec['size'])
        data[name] = (sec['flags'], end-start, sec['body'][start:end] if sec['body'] is not None else None,
                      [(o-start, k, syms[t]['name']) for o, t, k in sec['relocs'] if start <= o < end])
    undefined = {s['name'] for s in syms.values() if s['storage'] == 2 and s['section'] == 0}
    return code, data, undefined, set(names)

objects = {}
for item in [source, *providers]:
    path = Path(item).resolve()
    obj = B.obj_path(path)
    assert B.compile_is_current(path, obj, strict=True), item
    objects[item] = obj
old, od, ou, on = facts(lab.joinpath('original.obj').read_bytes())
raw = objects[source].read_bytes()
new, nd, nu, nn = facts(raw)
assert set(old)-set(new) == {coords_dtor} and not set(new)-set(old)
assert all(new[n] == old[n] for n in new)
assert od == nd and ou == nu and on-nn == {coords_dtor} and not nn-on
provider_reports = []
for item in providers:
    code = facts(objects[item].read_bytes())[0]
    assert code[coords_dtor] == old[coords_dtor], item
    provider_reports.append(dict(source=item, strict_current=True, same_body_relocations_flags_policy=True,
                                 sha256=hashlib.sha256(objects[item].read_bytes()).hexdigest()))

with open('reverse/functions.csv', newline='', encoding='utf-8') as handle:
    rows = [r for r in csv.DictReader(handle) if r['name'] == parms_dtor or r['source'] in [source, *providers]]
dtor_rows = [r for r in rows if r['name'] == parms_dtor]
assert len(dtor_rows) == 1
assert int(dtor_rows[0]['target_rva'], 16) == 0x1e7e9f and int(dtor_rows[0]['target_size']) == 15
result = B.compile_function(dtor_rows[0], B.load_symbol_map(), objects[source])
assert result['bytes'] == result['target']
minimum = {item: min(int(r['target_rva'],16) for r in rows if r['source'] == item) for item in [source, *providers]}
assert minimum[source] < minimum[providers[0]] < minimum[providers[1]]
assert sorted([source, *providers])[0] == providers[1]
index = K.load_index()
copies = index['comdat'][coords_dtor]
object_sources = {entry['object']: item for item, entry in index['blockers'].items() if 'object' in entry}
cached_order = [object_sources.get(index['objects'][i], index['objects'][i]) for i, digest, verdict in copies]
report = dict(source=source, retained_code_comdats=len(new), retained_code_facts_relocations_flags_policies_equal=True,
              named_data_count=len(nd), named_data_equal=True, undefined_references_equal=True,
              removed_definitions=[coords_dtor], added_definitions=[],
              parameter_destructor_native_rva='0x001E7E9F', parameter_destructor_native_bytes_verified=15,
              coords_destructor_body_hex=old[coords_dtor][0].hex(), coords_destructor_relocations=old[coords_dtor][1],
              coords_destructor_flags=hex(old[coords_dtor][2]), coords_destructor_policy=old[coords_dtor][3],
              providers=provider_reports, minimum_code_rvas={p:hex(rva) for p,rva in minimum.items()},
              census_replacement_provider=providers[0], default_real_link_path_provider=providers[1],
              cached_census_provider_order=cached_order, index_meta=index.get('meta'),
              original_object_sha256=hashlib.sha256(lab.joinpath('original.obj').read_bytes()).hexdigest(),
              current_object_sha256=hashlib.sha256(raw).hexdigest(),
              current_source_sha256=hashlib.sha256(Path(source).read_bytes()).hexdigest())
lab.joinpath('final-proof.json').write_bytes((json.dumps(report, indent=2)+'\n').encode())
print(json.dumps(report, indent=2))
