import csv,json,sys,collections
from pathlib import Path
sys.path.insert(0,'tools')
import header_adopt_lane as H,pin_admission as P
oldpins=list(csv.DictReader(Path('reverse/symbols.csv').open(newline='',encoding='utf-8')))
rows=[]
for r in csv.DictReader(Path('reverse/functions.csv').open(newline='',encoding='utf-8')):
 if 'Coord3D@' in r['name']:
  try:r={**r,'name':H.rekey_symbol(r['name'],'Coord3D','U')}
  except ValueError:pass
 rows.append(r)
retained=[];added=[]
for p in oldpins:
 try:new=H.rekey_symbol(p['name'],'Coord3D','U')
 except ValueError:new=p['name']
 if new==p['name']:retained.append(p)
 else:added.append({**p,'name':new})
names=P.names_by_address(rows,retained)
results=[]
for p in added:
 reason=P.pin_problems(p,names,prove=lambda *args:['unverified: existing note requests a proof, not executed by this read-only preflight'])
 results.append({'name':p['name'],'address':p['address'],'notes':p.get('notes'),'static_reason':reason})
 names.setdefault(int(p['address'],16),set()).add(p['name'])
Path('build/coord3d-pin-static-admission-20261107.json').write_text(json.dumps(results,indent=2))
print(json.dumps({'pins':len(results),'no_second_name_refusal':sum(not p['static_reason'] for p in results),'second_name_or_proof_needed':sum(bool(p['static_reason']) for p in results)},indent=2))
