import ast, csv, hashlib, json, re, shutil, sys
from pathlib import Path
sys.path.insert(0, str(Path.cwd() / 'tools'))
import build, tu_skeleton as T, eh_verify as E, link_census as C, header_adopt_lane as H, class_contract
source = 'Code/GameEngine/Source/Common/System/Snapshot.cpp'
lab = Path('build/coord3d-class-key-proof-20261107')
lab.mkdir(exist_ok=True)
raw = Path(source).read_bytes()
text = raw.decode('utf-8-sig')
canonical = Path('Code/Libraries/Include/Lib/Coord3D.h').read_text()
assert canonical.count('struct Coord3D {') == 1
headers = {'struct': canonical, 'class': canonical.replace('struct Coord3D {', 'class Coord3D {\npublic:')}
with Path('reverse/functions.csv').open(newline='', encoding='utf-8') as f:
    rows = [r for r in csv.DictReader(f) if r['source'] == source and r['status'] == 'matched']
def facts(path):
 o=E.Obj(path);selections=C._comdat_selections(path.read_bytes());ds={};props={}
 for s in o.symbols.values():
  if s.get('storage')!=2 or s.get('section',0)<=0:continue
  sec=o.sections[s['section']-1];start=s['value'];ds[s['name']]={'bytes':sec['data'][start:].hex(),'relocations':[[a-start,t,o.symbols[i]['name']] for a,i,t in sec['relocs'] if a>=start]};props[s['name']]={'symbol_storage':s['storage'],'section':sec['name'],'comdat_selection':selections.get(s['section'])}
 defined,undefined,weaks,alts,includes=C.object_symbols(path);return ds,props,{'defined':sorted(defined),'undefined':sorted(undefined),'weak':weaks,'alternates':alts,'includes':sorted(includes)}

def rekey(value):
    if isinstance(value, str):
        return value.replace('UCoord3D@@', 'VCoord3D@@')
    if isinstance(value, list):
        return [rekey(x) for x in value]
    if isinstance(value, tuple):
        return [rekey(x) for x in value]
    if isinstance(value, dict):
        return {rekey(k): rekey(v) for k, v in value.items()}
    return value
out = {'source': source, 'source_sha256': hashlib.sha256(raw).hexdigest(), 'export_key': dict(class_contract.export_key('Coord3D')), 'scope': 'Private compiler evidence only. Temporary header copies stay in ignored build; no canonical header, source or ledger is changed.', 'variants': {}}
maps = {}
for key, header in headers.items():
    name = 'Coord3D-' + key + '-proof.h'
    (lab / name).write_text(header, encoding='utf-8', newline='\n')
    lines = text.splitlines(keepends=True)
    pos = next(i for i, line in enumerate(lines) if line.startswith('// cl:'))
    lines[pos] = lines[pos].rstrip('\r\n') + ' /I' + lab.as_posix() + '\n'
    lines.insert(pos + 1, '#include "' + name + '"\n')
    proposal = ''.join(lines)
    wanted = [rekey(r) if key == 'class' else dict(r) for r in rows]
    v = T.Verifier(source)
    if key == 'class':
        v.sm = rekey(v.sm)
    got = v.matched(proposal, wanted)
    rec = {'rows': len(wanted), 'matched_addresses': len(got or []), 'missing': [r['name'] for r in wanted if r['target_rva'] not in (got or set())], 'errors': v.all_errors}
    if v.obj:
        obj = lab / ('snapshot-' + key + '.obj')
        shutil.copyfile(v.obj, obj)
        maps[key] = facts(obj)
    out['variants'][key] = rec
    print(key, json.dumps(rec), flush=True)
if len(maps) == 2:
    out['normalized_snapshot_facts_equal'] = rekey(maps['struct']) == json.loads(json.dumps(maps['class']))
    print('normalized snapshot facts equal', out['normalized_snapshot_facts_equal'], flush=True)
out['fixtures'] = {}
base_flags = text.splitlines()[0] + ' /I' + lab.as_posix() + '\n'
for key in headers:
    fixture = base_flags + '#include "Coord3D-' + key + '-proof.h"\nCoord3D *CoordKeyProbe(Coord3D *point) { return point; }\nbool Coord3D::operator==(const Coord3D &other) { return x == other.x && y == other.y && z == other.z; }\n'
    v = T.Verifier(source)
    v.matched(fixture, [])
    rec = {'errors': v.all_errors}
    if v.obj:
        obj = lab / ('fixture-' + key + '.obj')
        shutil.copyfile(v.obj, obj)
        defs, _, _, _, _ = C.object_symbols(obj)
        rec['symbols'] = sorted(n for n in defs if 'CoordKeyProbe' in n or '??8Coord3D' in n)
    out['fixtures'][key] = rec
    print('fixture', key, json.dumps(rec), flush=True)
old = out['fixtures']['struct'].get('symbols', [])
out['current_lane_backref_refusals'] = H.key_backref_names([{'name': n} for n in old], 'Coord3D', 'U')
(lab / 'proof.json').write_text(json.dumps(out, indent=2) + '\n', encoding='utf-8', newline='\n')
