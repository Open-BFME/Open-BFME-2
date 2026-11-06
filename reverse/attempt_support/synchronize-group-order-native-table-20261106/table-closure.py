import ast,csv,json,hashlib
from pathlib import Path
import build,eh_verify as E,link_census as C
lab=Path('build/sync-order-full-view-proof-20261106')
p=Path('build/sole-private-proof-20261103/build/gamewindowmanager-readonly-20261103/gadget-anchor-probe.py')
fn=next(n for n in ast.parse(p.read_text()).body if isinstance(n,ast.FunctionDef) and n.name=='facts')
exec(compile(ast.Module(body=[fn],type_ignores=[]),str(p),'exec'))
proof=json.loads((lab/'proof.json').read_text());im=E.Image();out=[]
wanted=set()
for row in proof:
 table=row['after_facts'][0].get('??_7SynchronizeGroupOrder@@6B@')
 if table:
  weak=dict(row['after_facts'][2]['weak'])
  wanted.update(weak.get(n,n) for _,_,n in table['relocations'])
symbol_map={n:set() for n in wanted}
with Path('reverse/functions.csv').open(newline='',encoding='utf-8') as f:
 for row in csv.DictReader(f):
  if row['name'] in wanted and row['status']=='matched':symbol_map[row['name']].add(int(row['target_rva'],16))
for row in proof:
 source=row['source'];obj=build.obj_path(source);got=json.loads(json.dumps(facts(obj)));assert got==row['after_facts'],source
 result={'source':source,'source_sha256':hashlib.sha256(Path(source).read_bytes()).hexdigest(),'object_sha256':hashlib.sha256(obj.read_bytes()).hexdigest(),'normal_equals_private':True,'eh':{}}
 table=got[0].get('??_7SynchronizeGroupOrder@@6B@')
 if table:
  assert len(bytes.fromhex(table['bytes']))==56
  weak=dict(got[2]['weak']);slots=[]
  for i,(offset,kind,name) in enumerate(table['relocations']):
   assert offset==4*i and kind==6
   resolved=weak.get(name,name);rv=sorted(symbol_map.get(resolved,[]));target=im.dword(0x86A314+offset)-im.base
   assert rv==[target],(source,i,name,rv,hex(target));slots.append({'slot':i,'symbol':name,'resolved_symbol':resolved,'target_rva':hex(target)})
  assert len(slots)==14;result['native_table']=slots
 o=E.Obj(obj)
 with Path('reverse/functions.csv').open(newline='',encoding='utf-8') as f:
  for r in csv.DictReader(f):
   if r['source']!=source or r['status']!='matched':continue
   n=build.ledger_object_symbol(r)
   if build.is_funclet_row(r,n):continue
   e=E.verify_row(im,o,n,int(r['target_rva'],16))
   if e is not None:result['eh'][n]=e
 assert all(e[0]=='EXACT' for e in result['eh'].values());out.append(result)
(lab/'normal-closure.json').write_text(json.dumps(out,indent=2)+'\n',newline='\n')
print(json.dumps([{'source':x['source'],'native_slots':len(x.get('native_table',[])),'eh_exact':len(x['eh']),'normal_equals_private':x['normal_equals_private']} for x in out],indent=2))
