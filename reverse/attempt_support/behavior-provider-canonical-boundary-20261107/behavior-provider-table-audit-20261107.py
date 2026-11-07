import json,sys,struct
from pathlib import Path
sys.path.insert(0,'tools')
import build
lab=Path('build/behavior-provider-private-20261107')
r=json.loads((lab/'report.json').read_text())
obj=Path(r['Code/GameEngine/Source/Common/Rva0049B47CDerived.cpp']['obj'])
sm=build.load_symbol_map()
for name,va,count in [('??_7BehaviorModule@@6BObjectModule@@@',0xBEEA7C,12),('??_7BehaviorModule@@6BBehaviorModuleInterface@@@',0xBEE9C0,47)]:
 data,rels=build.read_object_symbol_bytes(obj,name)
 targets=struct.unpack('<'+'I'*count,build.read_target_bytes(va-0x400000,count*4))
 out=[]
 for off,typ,sym in rels:
  if off//4<count:out.append({'slot':off//4,'symbol':sym,'expected_rva':hex(targets[off//4]-0x400000),'known_rvas':[hex(x) for x in sm.get(sym,[])]})
 print(name, 'slots',len(data)//4)
 print(json.dumps(out if count==12 else out[:5],indent=2))
 (lab/('primary-slots.json' if count==12 else 'interface-slots.json')).write_text(json.dumps(out,indent=2))
