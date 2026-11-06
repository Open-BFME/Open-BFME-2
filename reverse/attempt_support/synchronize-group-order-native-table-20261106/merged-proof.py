import ast,csv,json,hashlib,shutil
from pathlib import Path
import build,tu_skeleton as T,eh_verify as E,link_census as C
source='Code/GameEngine/Source/GameLogic/AI/SynchronizeGroupOrder.cpp';lab=Path('build/sync-order-merged-proof-20261106');lab.mkdir(exist_ok=True)
p=Path('build/sole-private-proof-20261103/build/gamewindowmanager-readonly-20261103/gadget-anchor-probe.py')
fn=next(n for n in ast.parse(p.read_text()).body if isinstance(n,ast.FunctionDef) and n.name=='facts');exec(compile(ast.Module(body=[fn],type_ignores=[]),str(p),'exec'))
rows=[]
with Path('reverse/functions.csv').open(newline='',encoding='utf-8') as f:
 for r in csv.DictReader(f):
  if r['source']==source and r['status']=='matched':rows.append(r)
assert len(rows)==20
text=Path(source).read_text();v=T.Verifier(source);got=v.matched(text,rows);assert got=={r['target_rva'] for r in rows},(got,v.all_errors)
shutil.copyfile(v.obj,lab/'private.obj');normal=json.loads(json.dumps(facts(build.obj_path(source))));private=json.loads(json.dumps(facts(lab/'private.obj')));assert normal==private
table=normal[0]['??_7SynchronizeGroupOrder@@6B@'];assert len(bytes.fromhex(table['bytes']))==56 and len(table['relocations'])==14
weak=dict(normal[2]['weak']);names={weak.get(n,n) for _,_,n in table['relocations']};owners={n:set() for n in names}
with Path('reverse/functions.csv').open(newline='',encoding='utf-8') as f:
 for r in csv.DictReader(f):
  if r['name'] in owners and r['status']=='matched':owners[r['name']].add(int(r['target_rva'],16))
im=E.Image();slots=[]
for i,(offset,kind,name) in enumerate(table['relocations']):
 resolved=weak.get(name,name);rva=im.dword(0x86A314+offset)-im.base;assert offset==4*i and kind==6 and owners[resolved]=={rva};slots.append({'slot':i,'symbol':name,'resolved_symbol':resolved,'rva':hex(rva)})
eh={};obj=E.Obj(build.obj_path(source))
for r in rows:
 n=build.ledger_object_symbol(r)
 if build.is_funclet_row(r,n):continue
 e=E.verify_row(im,obj,n,int(r['target_rva'],16))
 if e is not None:eh[n]=e
assert len(eh)==5 and all(e[0]=='EXACT' for e in eh.values())
out={'source':source,'source_sha256':hashlib.sha256(Path(source).read_bytes()).hexdigest(),'object_sha256':hashlib.sha256(build.obj_path(source).read_bytes()).hexdigest(),'rows':len(rows),'normal_equals_private':True,'native_table':slots,'eh':eh,'after_facts':normal}
(lab/'proof.json').write_text(json.dumps(out,indent=2)+'\n',newline='\n');print(json.dumps({k:v for k,v in out.items() if k not in ('after_facts','native_table')},indent=2))
