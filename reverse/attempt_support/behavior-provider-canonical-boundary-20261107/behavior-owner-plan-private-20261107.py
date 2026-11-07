import sys,json
from pathlib import Path
sys.path.insert(0,'tools')
import rename as R
lab=Path('build/behavior-provider-private-20261107')
common='Code/GameEngine/Source/Common/Rva0049B47CDerived.cpp'
upgrade='Code/GameEngine/Source/GameLogic/Object/Upgrade/UpgradeModuleCtor.cpp'
edits={common:(lab/'Rva0049B47CDerived.cpp').read_bytes(),upgrade:(lab/'UpgradeModuleCtor-novtable.cpp').read_bytes()}
class View(R.Context):
 def read(self,rel):return edits[rel] if rel in edits else super().read(rel)
ctx=View()
try:
 p=R.plan_class(ctx,'Rva004607E1','BehaviorModule',fold=True,prepared=list(edits),access='protected',max_files=30)
 (lab/'rename-plan.txt').write_text(p.report(),encoding='utf-8')
 print(p.report())
except R.Refusal as exc:
 (lab/'rename-refusal.txt').write_text(str(exc),encoding='utf-8')
 print('REFUSED',exc)
