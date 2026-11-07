import csv,json,sys
from pathlib import Path
sys.path.insert(0,'tools')
import tu_skeleton as T,link_census as C
source='Code/GameEngine/Source/GameLogic/Object/Upgrade/UpgradeModuleCtor.cpp'
lab=Path('build/behavior-provider-private-20261107')
text=(lab/'UpgradeModuleCtor.cpp').read_text()
assert text.count('class UpgradeModule :')==1
text=text.replace('class UpgradeModule :','class __declspec(novtable) UpgradeModule :')
with Path('reverse/functions.csv').open(newline='',encoding='utf-8') as f:rows=[r for r in csv.DictReader(f) if r['source']==source]
v=T.Verifier(source)
v.sm['??1BehaviorModule@@MAE@XZ']=[0x4607E1]
got=v.matched(text,rows)
rec={'rows':len(rows),'matched':len(got or []),'missing':[r['name'] for r in rows if r['target_rva'] not in (got or set())],'errors':v.all_errors}
if v.obj:rec['obj']=str(v.obj)
(lab/'UpgradeModuleCtor-novtable.cpp').write_text(text,encoding='utf-8',newline='\n')
(lab/'upgrade-novtable-report.json').write_text(json.dumps(rec,indent=2))
print(json.dumps(rec))
