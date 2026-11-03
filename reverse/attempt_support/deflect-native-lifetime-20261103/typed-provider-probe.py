from pathlib import Path
import ast,csv,json,shutil,sys
main=Path.cwd();root=main/'build/sole-private-proof-20261103';sys.path.insert(0,str(root/'tools'));import build,tu_skeleton as T,eh_verify as E,link_census as C
lab=root/'build/deflect-native-proof-20261103';s='Code/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeployHordeSpecialPower.cpp';text=(lab/'function-pointer.cpp').read_text().replace('class DeflectSpecialPowerModuleData :','class __declspec(novtable) DeflectSpecialPowerModuleData :');rows=[]
with (main/'reverse/functions.csv').open(encoding='utf-8',newline='') as f:
 for r in csv.DictReader(f):
  if r['source']==s and r['status']=='matched':rows.append(r)
rows.append({'name':'??1DeflectSpecialPowerModuleData@@UAE@XZ','target_rva':'0x004C64E9','target_size':'5','source':s,'status':'matched','notes':'private folded provider proof'})
v=T.Verifier(s);got=v.matched(text,rows);out={'matched':sorted(got or []),'missing':sorted({r['target_rva'] for r in rows}-(got or set())),'errors':v.all_errors};(lab/'function-pointer-novtable.cpp').write_text(text,encoding='utf-8',newline='\n')
if v.obj:
 p=lab/'function-pointer-novtable.obj';shutil.copyfile(v.obj,p);f=ast.parse((root/'build/gamewindowmanager-readonly-20261103/gadget-anchor-probe.py').read_text());exec(compile(ast.Module(body=[n for n in f.body if isinstance(n,ast.FunctionDef) and n.name=='facts'],type_ignores=[]),'facts','exec'));out['facts']=facts(p);a,ap,ar=json.loads((lab/'proof.json').read_text())['variants']['control']['facts'];b,bp,br=out['facts'];out['delta']={'old_count':len(a),'new_count':len(b),'removed':sorted(a.keys()-b.keys()),'added':sorted(b.keys()-a.keys()),'changed':sorted(n for n in a.keys()&b.keys() if a[n]!=b[n]),'properties_changed':sorted(n for n in ap.keys()&bp.keys() if ap[n]!=bp[n]),'added_undefined':sorted(set(br['undefined'])-set(ar['undefined']))}
print({k:v for k,v in out.items() if k!='facts'});(lab/'function-pointer-novtable.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8',newline='\n')
