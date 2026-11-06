import ast,csv,json,shutil
from pathlib import Path
import build,tu_skeleton as T,eh_verify as E,link_census as C,header_adopt_lane as H
lab=Path('build/aidock-table-overrides-proof-20261106');lab.mkdir(exist_ok=True)
p=Path('build/sole-private-proof-20261103/build/gamewindowmanager-readonly-20261103/gadget-anchor-probe.py')
fn=next(n for n in ast.parse(p.read_text()).body if isinstance(n,ast.FunctionDef) and n.name=='facts');exec(compile(ast.Module(body=[fn],type_ignores=[]),str(p),'exec'))
sources=['Code/GameEngine/Source/GameLogic/AI/AIStateHashCtors0033F2FD.cpp','Code/GameEngine/Source/Common/Rva0034159ADtor.cpp']
rows_by={s:[] for s in sources}
with Path('reverse/functions.csv').open(newline='',encoding='utf-8') as f:
 for row in csv.DictReader(f):
  if row['source'] in rows_by and row['status']=='matched':rows_by[row['source']].append(row)
out=[]
for source in sources:
 text=Path(source).read_text();span=H.body_span(text,'AIDockState');assert span
 block=text[span[0]:span[1]]
 at=block.index('private:')
 block=block[:at]+'''public:
    virtual StateReturnType onEnter();
    virtual void onExit(StateExitType status);
    virtual StateReturnType update();
protected:
    virtual void xfer(Xfer *xfer);
'''+block[at:]
 if source==sources[1]:block=block.replace('Rva0034159AMember *m_20;','Rva0034159AMember *m_20;\n    bool m_24; // native constructor33F540 and transfer3415F5 establish +24')
 candidate=text[:span[0]]+block+text[span[1]:]
 target=lab/(Path(source).stem+'.cpp.txt');target.write_text(candidate,newline='\n')
 v=T.Verifier(source);got=v.matched(candidate,rows_by[source]);r={'source':source,'candidate':target.as_posix(),'row_count':len(rows_by[source]),'matched':sorted(got or []),'missing':sorted({x['target_rva'] for x in rows_by[source]}-(got or set())),'errors':v.all_errors}
 if v.obj:
  obj=lab/(Path(source).stem+'.obj');shutil.copyfile(v.obj,obj);a=facts(build.obj_path(source));b=facts(obj)
  r.update(before_facts=a,after_facts=b,added=sorted(b[0].keys()-a[0].keys()),removed=sorted(a[0].keys()-b[0].keys()),changed=sorted(n for n in a[0].keys()&b[0].keys() if a[0][n]!=b[0][n]))
 out.append(r);print(json.dumps({k:v for k,v in r.items() if not k.endswith('_facts')},indent=2))
(lab/'proof.json').write_text(json.dumps(out,indent=2)+'\n',newline='\n')
