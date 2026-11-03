from pathlib import Path
import ast,csv,hashlib,json,shutil,sys
main=Path.cwd();root=main/'build/sole-private-proof-20261103';sys.path.insert(0,str(root/'tools'));import build,tu_skeleton as T,eh_verify as E,link_census as C
lab=root/'build/deflect-native-proof-20261103';s='Code/GameEngine/Source/GameLogic/Object/SpecialPower/DeflectSpecialPowerModuleDataConstructor.cpp';raw=(main/s).read_bytes();control=raw.decode('utf-8-sig');candidate='''// cl: /DNDEBUG /MD /EHsc
// Native0x004C5671/18B: constructs the0x18-byte base then installs Deflect's table.
// The existing AIUpdateModuleData owner supplies the witnessed base lifetime;
// this view does not establish the original intermediate class ancestry.
class AIUpdateModuleData
{
public:
    AIUpdateModuleData();
    virtual ~AIUpdateModuleData();
private:
    unsigned char m_opaque[0x14];
};

class DeflectSpecialPowerModuleData : public AIUpdateModuleData
{
public:
    DeflectSpecialPowerModuleData();
    virtual ~DeflectSpecialPowerModuleData();
};

DeflectSpecialPowerModuleData::DeflectSpecialPowerModuleData()
{
}
''';rows=[]
with (main/'reverse/functions.csv').open(encoding='utf-8',newline='') as f:
 for r in csv.DictReader(f):
  if r['source']==s and r['status']=='matched':rows.append(r)
f=ast.parse((root/'build/gamewindowmanager-readonly-20261103/gadget-anchor-probe.py').read_text());exec(compile(ast.Module(body=[n for n in f.body if isinstance(n,ast.FunctionDef) and n.name=='facts'],type_ignores=[]),'facts','exec'))
out={'source':s,'control_sha256':hashlib.sha256(raw).hexdigest(),'variants':{}}
for label,text in [('control',control),('candidate',candidate)]:
 v=T.Verifier(s);got=v.matched(text,rows);rec={'matched':sorted(got or []),'missing':sorted({r['target_rva'] for r in rows}-(got or set())),'errors':v.all_errors};out['variants'][label]=rec;(lab/('constructor-'+label+'.cpp')).write_text(text,encoding='utf-8',newline='\n')
 if v.obj:
  p=lab/('constructor-'+label+'.obj');shutil.copyfile(v.obj,p);rec['facts']=facts(p)
 print(label,{k:v for k,v in rec.items() if k!='facts'},flush=True)
a,ap,ar=out['variants']['control']['facts'];b,bp,br=out['variants']['candidate']['facts'];out['delta']={'old_count':len(a),'new_count':len(b),'removed':sorted(a.keys()-b.keys()),'added':sorted(b.keys()-a.keys()),'changed':sorted(n for n in a.keys()&b.keys() if a[n]!=b[n]),'properties_changed':sorted(n for n in ap.keys()&bp.keys() if ap[n]!=bp[n]),'removed_undefined':sorted(set(ar['undefined'])-set(br['undefined'])),'added_undefined':sorted(set(br['undefined'])-set(ar['undefined']))};print(out['delta']);(lab/'constructor-proof.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8',newline='\n')
