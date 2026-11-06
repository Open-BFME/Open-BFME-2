import ast,csv,json,hashlib
from pathlib import Path
import build,eh_verify as E,link_census as C
lab=Path('build/aidock-table-overrides-proof-20261106')
p=Path('build/sole-private-proof-20261103/build/gamewindowmanager-readonly-20261103/gadget-anchor-probe.py')
fn=next(n for n in ast.parse(p.read_text()).body if isinstance(n,ast.FunctionDef) and n.name=='facts');exec(compile(ast.Module(body=[fn],type_ignores=[]),str(p),'exec'))
proof=json.loads((lab/'proof.json').read_text());names={'?xfer@AIDockState@@MAEXPAVXfer@@@Z':0x3415F5,'?onEnter@AIDockState@@UAE?AW4StateReturnType@@XZ':0x341695,'?onExit@AIDockState@@UAEXW4StateExitType@@@Z':0x341723,'?update@AIDockState@@UAE?AW4StateReturnType@@XZ':0x341770}
sources=[r['source'] for r in proof]+['Code/GameEngine/Source/GameLogic/AI/AIDockStateOnExit.cpp'];rows_by={s:[] for s in sources};owners={n:set() for n in names}
with Path('reverse/functions.csv').open(newline='',encoding='utf-8') as f:
 for row in csv.DictReader(f):
  if row['status']!='matched':continue
  if row['source'] in rows_by:rows_by[row['source']].append(row)
  if row['name'] in owners:owners[row['name']].add(int(row['target_rva'],16))
assert all(owners[n]=={rva} for n,rva in names.items())
im=E.Image();out=[];normal_by={}
for source in sources:
 obj=build.obj_path(source);normal=json.loads(json.dumps(facts(obj)));normal_by[source]=normal
 private=next((r['after_facts'] for r in proof if r['source']==source),None)
 if private is not None:assert normal==private
 result={'source':source,'rows':len(rows_by[source]),'source_sha256':hashlib.sha256(Path(source).read_bytes()).hexdigest(),'object_sha256':hashlib.sha256(obj.read_bytes()).hexdigest(),'normal_equals_private':private is not None,'eh':{}}
 table=normal[0].get('??_7AIDockState@@6B@')
 if table:
  assert len(bytes.fromhex(table['bytes']))==68
  slots={offset//4:n for offset,kind,n in table['relocations'] if kind==6}
  assert len(slots)==17 and slots[2]=='__purecall'
  result['verified_lifecycle_slots']=[]
  for slot in range(3,7):
   n=slots[slot];native=im.dword(0x811368+4*slot)-im.base;assert names[n]==native
   result['verified_lifecycle_slots'].append({'slot':slot,'symbol':n,'rva':hex(native)})
  result['getter_slot_2_still_pending']=True
 o=E.Obj(obj)
 for row in rows_by[source]:
  n=build.ledger_object_symbol(row)
  if build.is_funclet_row(row,n):continue
  e=E.verify_row(im,o,n,int(row['target_rva'],16))
  if e is not None:result['eh'][n]=e
 assert all(e[0]=='EXACT' for e in result['eh'].values());out.append(result)
removed='?onEnter@State@@UAE?AW4StateReturnType@@XZ'
assert removed in normal_by[sources[0]][0]
out.append({'removed_redundant_header_copy':removed,'retained_current_provider':sources[0],'body':normal_by[sources[0]][0][removed]})
(lab/'normal-closure.json').write_text(json.dumps(out,indent=2)+'\n',newline='\n');print(json.dumps([{k:v for k,v in r.items() if k not in ('eh','body')} for r in out],indent=2));print('exact EH graphs:',sum(len(r.get('eh',{})) for r in out))
