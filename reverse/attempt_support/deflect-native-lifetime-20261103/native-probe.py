from pathlib import Path
import ast,csv,hashlib,json,shutil,sys
main=Path.cwd();root=main/'build/sole-private-proof-20261103';sys.path.insert(0,str(root/'tools'));import build,tu_skeleton as T,eh_verify as E,link_census as C
lab=root/'build/deflect-native-proof-20261103';lab.mkdir(exist_ok=True)
f=ast.parse((root/'build/gamewindowmanager-readonly-20261103/gadget-anchor-probe.py').read_text());exec(compile(ast.Module(body=[n for n in f.body if isinstance(n,ast.FunctionDef) and n.name=='facts'],type_ignores=[]),'facts','exec'))
s='Code/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeployHordeSpecialPower.cpp';raw=(main/s).read_bytes();control=raw.decode('utf-8-sig');rs=[]
with (main/'reverse/functions.csv').open(encoding='utf-8',newline='') as f:
 for r in csv.DictReader(f):
  if r['source']==s and r['status']=='matched':rs.append(r)
extra={'name':'??1DeflectSpecialPowerModuleData@@UAE@XZ','target_rva':'0x004C64E9','target_size':'5','source':s,'status':'matched','notes':'private typed fold-provider proof only'}
addition='''\n// Native Deflect deleting call4C5686 reaches the same5B lifetime thunk.\n// The18B Deflect constructor and0x18-byte factory allocation bound its base view.\nclass ATTRIBUTE DeflectSpecialPowerModuleData : public AIUpdateModuleData\n{\npublic:\n    virtual ~DeflectSpecialPowerModuleData();\n};\n\nDeflectSpecialPowerModuleData::~DeflectSpecialPowerModuleData()\n{\n}\n'''
out={'source':s,'control_sha256':hashlib.sha256(raw).hexdigest(),'variants':{}}
for label,text,rows in [('control',control,rs),('plain',control+addition.replace('ATTRIBUTE ',''),rs+[extra]),('novtable',control+addition.replace('ATTRIBUTE','__declspec(novtable)'),rs+[extra])]:
 v=T.Verifier(s);got=v.matched(text,rows);rec={'matched':sorted(got or []),'missing':sorted({r['target_rva'] for r in rows}-(got or set())),'errors':v.all_errors};out['variants'][label]=rec;(lab/(label+'.cpp')).write_text(text,encoding='utf-8',newline='\n')
 if v.obj:
  p=lab/(label+'.obj');shutil.copyfile(v.obj,p);rec['facts']=facts(p);o=E.Obj(p);im=E.Image();rec['EH']={}
  for r in rows:
   if build.is_funclet_row(r,build.ledger_object_symbol(r)):continue
   eh=E.verify_row(im,o,build.ledger_object_symbol(r),int(r['target_rva'],16))
   if eh is not None:rec['EH'][r['name']]=eh
 print(label,{k:v for k,v in rec.items() if k!='facts'},flush=True)
a,ap,ar=out['variants']['control']['facts']
for label in ['plain','novtable']:
 rec=out['variants'][label]
 if 'facts' not in rec:continue
 b,bp,br=rec['facts'];rec['delta']={'old_count':len(a),'new_count':len(b),'removed':sorted(a.keys()-b.keys()),'added':sorted(b.keys()-a.keys()),'changed':sorted(n for n in a.keys()&b.keys() if a[n]!=b[n]),'properties_changed':sorted(n for n in ap.keys()&bp.keys() if ap[n]!=bp[n]),'added_undefined':sorted(set(br['undefined'])-set(ar['undefined']))};print(label,rec['delta'],flush=True)
(lab/'proof.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8',newline='\n')
