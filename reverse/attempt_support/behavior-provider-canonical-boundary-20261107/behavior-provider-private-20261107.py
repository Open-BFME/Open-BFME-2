import csv,json,sys,re
from pathlib import Path
sys.path.insert(0,'tools')
import tu_skeleton as T,link_census as C,build
lab=Path('build/behavior-provider-private-20261107');lab.mkdir(exist_ok=True)
common='Code/GameEngine/Source/Common/Rva0049B47CDerived.cpp'
upgrade='Code/GameEngine/Source/GameLogic/Object/Upgrade/UpgradeModuleCtor.cpp'
with Path('reverse/functions.csv').open(newline='',encoding='utf-8') as f:
 rows={s:[] for s in [common,upgrade]}
 for r in csv.DictReader(f):
  if r['source'] in rows: rows[r['source']].append(r)
text=Path(common).read_text()
assert text.count('class MiBase1')==1
c=text[:text.index('class MiBase1')]
c+='#include "../../Include/GameLogic/Module/BehaviorModule.h"\nBehaviorModule::~BehaviorModule() {}\n'
u=Path(upgrade).read_text()
a=u.index('// Retail\'s unwind of the BehaviorModule base')
b=u.index('class UpgradeMux',a)
u=u[:a]+'#include "../../../../Include/GameLogic/Module/BehaviorModule.h"\n\n'+u[b:]
report={}
for source,proposal in [(common,c),(upgrade,u)]:
 v=T.Verifier(source)
 v.sm.update({'??1BehaviorModule@@MAE@XZ':[0x4607E1],
              '??_GBehaviorModule@@MAEPAXI@Z':[0x25335A],
              '??_GBehaviorModule@@UAEPAXI@Z':[0x25335A],
              '??_7BehaviorModule@@6BObjectModule@@@':[0x7EEA7C],
              '??_7BehaviorModule@@6BBehaviorModuleInterface@@@':[0x7EE9C0]})
 wanted=[]
 for row in rows[source]:
  row=dict(row)
  if row['name']=='??1Rva004607E1@@UAE@XZ':row['name']='??1BehaviorModule@@MAE@XZ'
  if row['name']=='??_GRva004607E1@@UAEPAXI@Z':row['name']='??_GBehaviorModule@@MAEPAXI@Z'
  wanted.append(row)
 got=v.matched(proposal,wanted)
 rec={'rows':len(wanted),'matched':len(got or []),'missing':[r['name'] for r in wanted if r['target_rva'] not in (got or set())], 'errors':v.all_errors}
 if v.obj:
  defs,und,weak,alts,inc=C.object_symbols(v.obj)
  rec['behavior_definitions']=sorted(n for n in defs if 'BehaviorModule@@' in n)
  rec['undefined_behavior']=sorted(n for n in und if 'BehaviorModule@@' in n)
  rec['obj']=str(v.obj)
 (lab/Path(source).name).write_text(proposal,encoding='utf-8',newline='\n')
 report[source]=rec
 print(source,json.dumps(rec),flush=True)
(lab/'report.json').write_text(json.dumps(report,indent=2))
