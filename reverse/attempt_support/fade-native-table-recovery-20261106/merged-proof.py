import ast,csv,json,hashlib,shutil,struct
from pathlib import Path
import build,tu_skeleton as T,eh_verify as E,link_census as C
source='Code/GameEngine/Source/Common/FadeInTextRender.cpp';lab=Path('build/fade-merged-proof-20261106');lab.mkdir(exist_ok=True)
p=Path('build/sole-private-proof-20261103/build/gamewindowmanager-readonly-20261103/gadget-anchor-probe.py')
fn=next(n for n in ast.parse(p.read_text()).body if isinstance(n,ast.FunctionDef) and n.name=='facts');exec(compile(ast.Module(body=[fn],type_ignores=[]),str(p),'exec'))
rows=[]
with Path('reverse/functions.csv').open(newline='',encoding='utf-8') as f:
 for r in csv.DictReader(f):
  if r['source']==source and r['status']=='matched':rows.append(r)
assert len(rows)==20
text=Path(source).read_text();v=T.Verifier(source);got=v.matched(text,rows);assert got=={r['target_rva'] for r in rows},(got,v.all_errors)
shutil.copyfile(v.obj,lab/'private.obj');normal=json.loads(json.dumps(facts(build.obj_path(source))));private=json.loads(json.dumps(facts(lab/'private.obj')));assert normal==private
im=E.Image();weak=dict(normal[2]['weak']);tables={};wanted=set()
for name in ('??_7FadeInTextRender@@6B@','??_7Rva0059675ABase@@6B@'):
 table=normal[0][name];assert len(bytes.fromhex(table['bytes']))==20 and len(table['relocations'])==5;wanted.update(weak.get(n,n) for _,_,n in table['relocations'])
owners={n:set() for n in wanted}
with Path('reverse/functions.csv').open(newline='',encoding='utf-8') as f:
 for r in csv.DictReader(f):
  if r['name'] in owners and r['status']=='matched':owners[r['name']].add(int(r['target_rva'],16))
for name,rva in (('??_7FadeInTextRender@@6B@',0x870A70),('??_7Rva0059675ABase@@6B@',0x870A5C)):
 table=normal[0][name];slots=[]
 for i,(offset,kind,n) in enumerate(table['relocations']):
  resolved=weak.get(n,n);target=im.dword(rva+offset)-im.base;assert offset==4*i and kind==6
  if resolved=='__purecall':assert target==0x3B810
  else:assert owners[resolved]=={target},(name,i,resolved,owners[resolved],hex(target))
  slots.append({'slot':i,'symbol':n,'resolved_symbol':resolved,'rva':hex(target)})
 tables[name]=slots
body=normal[0]['??_GRva0059675ABase@@UAEPAXI@Z'];exact=bytearray.fromhex(body['bytes']);assert len(exact)==29
assert body['relocations']==[[10,6,'??_7Rva0059675ABase@@6B@'],[18,20,'??3@YAXPAX@Z']]
struct.pack_into('<I',exact,10,im.base+0x870A5C);struct.pack_into('<I',exact,18,(0x2FD60-(0x5966C0+18+4))&0xffffffff)
assert bytes(exact)==im.bytes[0x5966C0:0x5966DD]
eh={};obj=E.Obj(build.obj_path(source))
for r in rows:
 n=build.ledger_object_symbol(r)
 if build.is_funclet_row(r,n):continue
 e=E.verify_row(im,obj,n,int(r['target_rva'],16))
 if e is not None:eh[n]=e
assert len(eh)==4 and all(e[0]=='EXACT' for e in eh.values())
out={'source':source,'source_sha256':hashlib.sha256(Path(source).read_bytes()).hexdigest(),'object_sha256':hashlib.sha256(build.obj_path(source).read_bytes()).hexdigest(),'rows':len(rows),'normal_equals_private':True,'native_tables':tables,'base_deleting_destructor_unmasked_native_29B':True,'eh':eh,'after_facts':normal}
(lab/'proof.json').write_text(json.dumps(out,indent=2)+'\n',newline='\n');print(json.dumps({k:v for k,v in out.items() if k not in ('after_facts','native_tables')},indent=2))
