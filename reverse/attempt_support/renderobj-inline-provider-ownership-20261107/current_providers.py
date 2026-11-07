import collections
import csv
import hashlib
import json
import sys
from pathlib import Path

sys.path.insert(0, 'tools')
import build
import image_report
import link_check as L
import link_cycle as C
import vtable_bridge as V

names = [
    '?Get_Bounding_Box@RenderObjClass@@UBEABVAABoxClass@@XZ',
    '?Get_Bounding_Sphere@RenderObjClass@@UBEABVSphereClass@@XZ',
    '?Get_Current_LOD@RenderObjClass@@UAEPAV1@XZ',
    '?Set_ObjectScale@RenderObjClass@@UAEXM@Z',
    '?_bfme_ro_flag111@RenderObjClass@@UBEHXZ',
    '?_bfme_ro_flag113@RenderObjClass@@UBEHXZ',
    '?_bfme_ro_flag115@RenderObjClass@@UBEHXZ',
]
index = L.load_index()
positions = set()
for name in names:
    positions.update(index['strong'].get(name, []))
    positions.update(entry[0] for entry in index['comdat'].get(name, []))
paths = [Path('build/match') / index['objects'][p] for p in sorted(positions)]
objects = C.Objects(paths)
by_name = {name: [] for name in names}
for path in paths:
    obj = objects.get(path)
    if obj is None:
        raise ValueError(f'missing previous provider: {path}')
    defined = objects.defined(obj)[0]
    for name in names:
        if name in defined:
            by_name[name].append(path)
owners = {}
with Path('reverse/functions.csv').open(newline='', encoding='utf-8') as handle:
    for row in csv.DictReader(handle):
        if row['name'] in names:
            if row['name'] in owners:
                raise ValueError(f'duplicate ledger name: {row["name"]}')
            owners[row['name']] = row
report = {'index': index['meta'], 'scope': 'previous indexed providers, current objects; not a real link',
          'objects_inspected': len(paths), 'providers': []}
for name in names:
    row = owners[name]
    owner = build.row_object(row)
    copies = by_name[name]
    owner_body = V.comdat_body(objects, owner, name)
    first = copies[0] if copies else None
    report['providers'].append({
        'name': name, 'rva': row['target_rva'], 'owner_source': row['source'],
        'current_definitions': [p.name for p in copies],
        'first_is_owner': first is not None and first.resolve() == owner.resolve(),
        'first_exact_bridge_twin': owner_body is not None and first is not None
            and owner_body == V.comdat_body(objects, first, name),
        'owner_flags': hex(owner_body[0]) if owner_body else None,
        'owner_bytes': owner_body[1].hex() if owner_body else None,
        'owner_relocations': owner_body[2] if owner_body else None,
    })
mesh_source = 'Code/Libraries/Source/WWVegas/WW3D2/MeshClassLifetime.cpp'
mesh = build.obj_path(Path(mesh_source))
table_name = '??_7MeshClass@@6BRefCountClass@@@'
mesh_objects = C.Objects([mesh])
table = V.definitions(mesh_objects, {table_name})[table_name]
assert len(table) == 1
table = table[0]
with Path('reverse/data_ledger.csv').open(newline='', encoding='utf-8') as handle:
    table_rows = [row for row in csv.DictReader(handle) if row['address'].lower() == '0x007d35a8']
assert len(table_rows) == 1
slots, reason = V.retail_slots(image_report.Retail(build.EXE.read_bytes()), table_rows[0])
assert reason is None
pointer_names = {entry[0] for entry in table['pointers'].values()}
addresses = collections.defaultdict(set)
with Path('reverse/functions.csv').open(newline='', encoding='utf-8') as handle:
    for row in csv.DictReader(handle):
        name = build.ledger_object_symbol(row) or row['name']
        if name in pointer_names:
            addresses[name].add(int(row['target_rva'], 16))
report['mesh_table'] = {
    'name': table_name, 'rva': table_rows[0]['address'],
    'compiled_extent': table['extent'], 'retail_slots': len(slots),
    'mismatches': V.source_slot_mismatches(table, slots, addresses),
    'affected_slots': [dict(slot=i, name=table['pointers'][i*4][0],
                            target_rva=hex(slots[i])) for i in range(len(slots))
                       if table['pointers'].get(i*4, ('',))[0] in names],
}
report['header_sha256'] = hashlib.sha256(Path('Code/Libraries/Source/WWVegas/WW3D2/rendobj.h').read_bytes()).hexdigest()
out = Path('build/mesh-four-provider-private-20261107/current-providers.json')
out.write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
print(json.dumps({
    'objects': report['objects_inspected'],
    'providers': [{k: p[k] for k in ('name', 'first_is_owner', 'first_exact_bridge_twin')}
                  | {'definitions': len(p['current_definitions'])} for p in report['providers']],
    'mesh_slots': len(slots), 'mesh_mismatches': len(report['mesh_table']['mismatches']),
    'report': str(out),
}, indent=2))
