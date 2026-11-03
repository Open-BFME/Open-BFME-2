from pathlib import Path
import csv,json,shutil,sys
main=Path.cwd();root=main/'build/sole-private-proof-20261103';sys.path.insert(0,str(root/'tools'));import tu_skeleton as T
lab=root/'build/deflect-native-proof-20261103';s='Code/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeployHordeSpecialPower.cpp';base=(lab/'plain.cpp').read_text();old='extern "C" const void *const __identifier("??_7DeflectSpecialPowerModuleData@@6B@")[];';assert base.count(old)==1;rows=[]
with (main/'reverse/functions.csv').open(encoding='utf-8',newline='') as f:
 for r in csv.DictReader(f):
  if r['source']==s and r['status']=='matched':rows.append(r)
rows.append({'name':'??1DeflectSpecialPowerModuleData@@UAE@XZ','target_rva':'0x004C64E9','target_size':'5','source':s,'status':'matched','notes':'private folded provider proof'})
forms={'const-void':'extern "C" const void *__identifier("??_7DeflectSpecialPowerModuleData@@6B@")[];','plain-void':'extern "C" void *__identifier("??_7DeflectSpecialPowerModuleData@@6B@")[];','function-pointer':'extern "C" void (__cdecl *const __identifier("??_7DeflectSpecialPowerModuleData@@6B@")[])();'};out={}
for label,decl in forms.items():
 text=base.replace(old,decl);v=T.Verifier(s);got=v.matched(text,rows);rec={'matched':sorted(got or []),'missing':sorted({r['target_rva'] for r in rows}-(got or set())),'errors':v.all_errors};out[label]=rec;print(label,rec,flush=True);(lab/(label+'.cpp')).write_text(text,encoding='utf-8',newline='\n')
 if v.obj:shutil.copyfile(v.obj,lab/(label+'.obj'))
(lab/'declaration-probes.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8',newline='\n')
