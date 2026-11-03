from pathlib import Path
import ast,csv,hashlib,json,shutil,sys
main=Path.cwd();root=main/'build/sole-private-proof-20261103';sys.path.insert(0,str(root/'tools'));import build,tu_skeleton as T,eh_verify as E,link_census as C
lab=root/'build/owned-pointer-native-proof-20261103';lab.mkdir(exist_ok=True);s='Code/GameEngine/Source/Common/Rva0057702EClear.cpp';raw=(main/s).read_bytes();control=raw.decode('utf-8-sig');assert control.count('\tvoid rva0057702E();')==1
candidate=control.replace('\tvoid rva0057702E();','\tvoid rva0057702E();\n\t~Rva0057702E();')+'''\n// Native constructor unwind0x0079B6CB destroys this four-byte holder at+0x14.\n// The lifetime body shares retail0x0057702E with the existing clear operation.\nRva0057702E::~Rva0057702E()\n{\n    Rva0057702EBase *p = m_ptr;\n    m_ptr = 0;\n    ::operator delete(p ? p->f4(0) : 0);\n}\n'''
rows=[]
with (main/'reverse/functions.csv').open(encoding='utf-8',newline='') as f:
 for r in csv.DictReader(f):
  if r['source']==s and r['status']=='matched':rows.append(r)
extra={'name':'??1Rva0057702E@@QAE@XZ','target_rva':'0x0057702E','target_size':'30','source':s,'status':'matched','notes':'private native lifetime fold proof'}
f=ast.parse((root/'build/gamewindowmanager-readonly-20261103/gadget-anchor-probe.py').read_text());exec(compile(ast.Module(body=[n for n in f.body if isinstance(n,ast.FunctionDef) and n.name=='facts'],type_ignores=[]),'facts','exec'))
out={'source':s,'control_sha256':hashlib.sha256(raw).hexdigest(),'variants':{}}
for label,text,rs in [('control',control,rows),('candidate',candidate,rows+[extra])]:
 v=T.Verifier(s);got=v.matched(text,rs);rec={'matched':sorted(got or []),'missing':sorted({r['target_rva'] for r in rs}-(got or set())),'errors':v.all_errors};out['variants'][label]=rec;(lab/(label+'.cpp')).write_text(text,encoding='utf-8',newline='\n')
 if v.obj:p=lab/(label+'.obj');shutil.copyfile(v.obj,p);rec['facts']=facts(p)
 print(label,{k:v for k,v in rec.items() if k!='facts'},flush=True)
a,ap,ar=out['variants']['control']['facts'];b,bp,br=out['variants']['candidate']['facts'];out['delta']={'old_count':len(a),'new_count':len(b),'removed':sorted(a.keys()-b.keys()),'added':sorted(b.keys()-a.keys()),'changed':sorted(n for n in a.keys()&b.keys() if a[n]!=b[n]),'properties_changed':sorted(n for n in ap.keys()&bp.keys() if ap[n]!=bp[n]),'dependencies_unchanged':ar['undefined']==br['undefined'] and ar['weak']==br['weak'] and ar['alternates']==br['alternates'] and ar['includes']==br['includes']};print(out['delta']);(lab/'proof.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8',newline='\n')
