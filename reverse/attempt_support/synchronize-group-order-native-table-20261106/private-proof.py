import ast,csv,json,shutil
from pathlib import Path
import build,tu_skeleton as T,eh_verify as E,link_census as C
source='Code/GameEngine/Source/GameLogic/AI/SynchronizeGroupOrder.cpp'
lab=Path('build/sync-order-slot-proof-20261106');lab.mkdir(exist_ok=True)
p=Path('build/sole-private-proof-20261103/build/gamewindowmanager-readonly-20261103/gadget-anchor-probe.py')
fn=next(n for n in ast.parse(p.read_text()).body if isinstance(n,ast.FunctionDef) and n.name=='facts')
exec(compile(ast.Module(body=[fn],type_ignores=[]),str(p),'exec'))
control=Path(source).read_text()
candidate=control.replace('class Rva0036E346;','class Rva0036E346;\nstruct Coord3D;\nstruct GroupOrderCommand;')
old='\tvirtual ~GroupOrder();'
new=old+'''\n\tvirtual void loadPostProcess() {}\n\tvirtual void slot07Set(int unused) {}\n\tvirtual bool isNearDestination(const Coord3D *position) { return false; }\n\tvirtual int slot10() { return -1; }'''
assert candidate.count(old)==1;candidate=candidate.replace(old,new)
old='\tSynchronizeGroupOrder *rva005469FD();'
new=old+'''\n\tvirtual Coord3D *getDestination(int position) { return reinterpret_cast<Coord3D *>(position); }\n\tvirtual bool slot11Command(int *outType, GroupOrderCommand *command) { return false; }'''
assert candidate.count(old)==1;candidate=candidate.replace(old,new)
newrows=[
('?loadPostProcess@GroupOrder@@UAEXXZ',0xB3FD0,1),
('?slot07Set@GroupOrder@@UAEXH@Z',0x47A69C,3),
('?isNearDestination@GroupOrder@@UAE_NPBUCoord3D@@@Z',0x5CB9FF,5),
('?slot10@GroupOrder@@UAEHXZ',0x36CC7A,4),
('?getDestination@SynchronizeGroupOrder@@UAEPAUCoord3D@@H@Z',0x21983A,7),
('?slot11Command@SynchronizeGroupOrder@@UAE_NPAHPAUGroupOrderCommand@@@Z',0x50B5F1,5),
]
rows=[]
with Path('reverse/functions.csv').open(newline='',encoding='utf-8') as f:
 for r in csv.DictReader(f):
  if r['source']==source and r['status']=='matched':rows.append(r)
base_count=len(rows)
rows += [dict(name=n,target_rva=hex(r),target_size=str(z),source=source,status='matched',notes='') for n,r,z in newrows]
(lab/'candidate.cpp.txt').write_text(candidate,newline='\n')
v=T.Verifier(source);got=v.matched(candidate,rows)
out={'source':source,'base_rows':base_count,'rows':len(rows),'new_rows':newrows,'matched':sorted(got or []),'missing':sorted({r['target_rva'] for r in rows}-(got or set())),'errors':v.all_errors}
if v.obj:
 shutil.copyfile(v.obj,lab/'candidate.obj');a=facts(build.obj_path(source));b=facts(lab/'candidate.obj');out.update(before_facts=a,after_facts=b,added=sorted(b[0].keys()-a[0].keys()),removed=sorted(a[0].keys()-b[0].keys()),changed=sorted(n for n in a[0].keys()&b[0].keys() if a[0][n]!=b[0][n]))
(lab/'proof.json').write_text(json.dumps(out,indent=2)+'\n',newline='\n')
print(json.dumps({k:v for k,v in out.items() if not k.endswith('_facts')},indent=2))
