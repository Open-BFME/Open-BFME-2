import ast,csv,json,hashlib
from pathlib import Path
import build,eh_verify as E,link_census as C
lab=Path('build/fade-full-view-proof-20261106')
p=Path('build/sole-private-proof-20261103/build/gamewindowmanager-readonly-20261103/gadget-anchor-probe.py')
fn=next(n for n in ast.parse(p.read_text()).body if isinstance(n,ast.FunctionDef) and n.name=='facts');exec(compile(ast.Module(body=[fn],type_ignores=[]),str(p),'exec'))
proof=json.loads((lab/'proof.json').read_text());im=E.Image();out=[]
wanted=set()
for row in proof:
 weak=dict(row['after_facts'][2]['weak'])
 for name in ('??_7FadeInTextRender@@6B@','??_7Rva0059675ABase@@6B@'):
  if name in row['after_facts'][0]:wanted.update(weak.get(n,n) for _,_,n in row['after_facts'][0][name]['relocations'])
owners={n:set() for n in wanted};rows_by={r['source']:[] for r in proof}
with Path('reverse/functions.csv').open(newline='',encoding='utf-8') as f:
 for r in csv.DictReader(f):
  if r['status']!='matched':continue
  if r['name'] in owners:owners[r['name']].add(int(r['target_rva'],16))
  if r['source'] in rows_by:rows_by[r['source']].append(r)
for row in proof:
 source=row['source'];obj=build.obj_path(source);got=json.loads(json.dumps(facts(obj)));assert got==row['after_facts'],source
 result={'source':source,'source_sha256':hashlib.sha256(Path(source).read_bytes()).hexdigest(),'object_sha256':hashlib.sha256(obj.read_bytes()).hexdigest(),'rows':len(rows_by[source]),'normal_equals_private':True,'tables':{},'eh':{}}
 weak=dict(got[2]['weak'])
 for name,rva in (('??_7FadeInTextRender@@6B@',0x870A70),('??_7Rva0059675ABase@@6B@',0x870A5C)):
  table=got[0].get(name)
  if not table:continue
  assert len(bytes.fromhex(table['bytes']))==20 and len(table['relocations'])==5
  slots=[]
  for i,(offset,kind,n) in enumerate(table['relocations']):
   resolved=weak.get(n,n);target=im.dword(rva+offset)-im.base;assert offset==4*i and kind==6
   if resolved=='__purecall':assert target==0x3B810
   else:assert owners[resolved]=={target},(source,name,i,resolved,owners[resolved],hex(target))
   slots.append({'slot':i,'symbol':n,'resolved_symbol':resolved,'target_rva':hex(target)})
  result['tables'][name]=slots
 o=E.Obj(obj)
 for r in rows_by[source]:
  n=build.ledger_object_symbol(r)
  if build.is_funclet_row(r,n):continue
  e=E.verify_row(im,o,n,int(r['target_rva'],16))
  if e is not None:result['eh'][n]=e
 assert all(e[0]=='EXACT' for e in result['eh'].values());out.append(result)
(lab/'normal-closure.json').write_text(json.dumps(out,indent=2)+'\n',newline='\n');print(json.dumps([{'source':r['source'],'rows':r['rows'],'tables':list(r['tables']),'eh_exact':len(r['eh'])} for r in out],indent=2))
