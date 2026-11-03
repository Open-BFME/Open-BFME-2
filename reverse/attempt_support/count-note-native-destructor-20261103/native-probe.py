from pathlib import Path
import ast,csv,hashlib,json,shutil,sys
main=Path.cwd();root=main/'build/sole-private-proof-20261103';sys.path.insert(0,str(root/'tools'))
import build,tu_skeleton as T,eh_verify as E,link_census as C
lab=root/'build/count-note-native-proof-20261103';lab.mkdir(exist_ok=True)
fns=ast.parse((root/'build/gamewindowmanager-readonly-20261103/gadget-anchor-probe.py').read_text())
exec(compile(ast.Module(body=[n for n in fns.body if isinstance(n,ast.FunctionDef) and n.name=='facts'],type_ignores=[]),'facts','exec'))
sources=['Code/GameEngine/Source/GameClient/Rva000427195Dtor.cpp','Code/GameEngine/Source/Common/RvaCountNoteRunFamily.cpp']
texts={s:(main/s).read_text(encoding='utf-8-sig') for s in sources};rows={s:[] for s in sources}
with (main/'reverse/functions.csv').open(encoding='utf-8',newline='') as f:
 for r in csv.DictReader(f):
  if r['source'] in rows and r['status']=='matched':rows[r['source']].append(r)
s=sources[0];candidate=texts[s]+'''\n// Native 0x0052B6FE: clears the local registration table and frees its buckets.\n// The original table specialization remains unidentified.\nstruct Rva0052B6FE\n{\n    ~Rva0052B6FE();\n    void *m_unused00;\n    Rva000427195BucketHandle m_buckets;\n    unsigned int m_numElements;\n};\n\nRva0052B6FE::~Rva0052B6FE()\n{\n    ((Rva000427195 *)this)->rva003A2A41();\n}\n'''
newrows=[dict(r) for r in rows[s]]
for r in newrows:
 if int(r['target_rva'],16)==0x52b6fe:r['name']='??1Rva0052B6FE@@QAE@XZ';r['notes']='Native registration-table destructor; original specialization unidentified'
results={};objects={}
for source,variants in [(s,[('control',texts[s],rows[s]),('candidate',candidate,newrows)])]:
 for label,text,rs in variants:
  v=T.Verifier(source)
  if label=='candidate':v.sm['??1Rva0052B6FE@@QAE@XZ']=0x52b6fe
  got=v.matched(text,rs);key='dtor-'+label;rec={'matched':sorted(got or []),'missing':sorted({r['target_rva'] for r in rs}-(got or set())),'errors':v.all_errors};results[key]=rec
  (lab/(key+'.cpp')).write_text(text,encoding='utf-8',newline='\n')
  if v.obj:
   path=lab/(key+'.obj');shutil.copyfile(v.obj,path);objects[key]=path;rec['facts']=facts(path);rec['EH']={};o=E.Obj(path);im=E.Image()
   for r in rs:
    if build.is_funclet_row(r,build.ledger_object_symbol(r)):continue
    eh=E.verify_row(im,o,build.ledger_object_symbol(r),int(r['target_rva'],16))
    if eh is not None:rec['EH'][r['name']]=eh
  print(key,{k:v for k,v in rec.items() if k!='facts'},flush=True)
s=sources[1];old='class Rva0052B7B3Dtor\n{\npublic:\n    ~Rva0052B7B3Dtor();\n};';assert texts[s].count(old)==1
replacement='''class Rva0052B6FE\n{\npublic:\n    ~Rva0052B6FE();\n};\n\nclass Rva0052B7B3Dtor\n{\npublic:\n    ~Rva0052B7B3Dtor()\n    {\n        reinterpret_cast<Rva0052B6FE *>(this)->~Rva0052B6FE();\n    }\n};'''
text=texts[s].replace(old,replacement);pragma='#pragma comment(linker, "/alternatename:??1Rva0052B7B3Dtor@@QAE@XZ=?j_0052b7b3@@YAXXZ")\n';assert text.count(pragma)==2;text=text.replace(pragma,'')
extra={'name':'??1Rva0052B7B3Dtor@@QAE@XZ','target_rva':'0x0052B7B3','target_size':'5','source':s,'status':'matched','notes':'private native inline-provider proof only'}
for label,text,rs in [('control',texts[s],rows[s]),('candidate',text,rows[s]+[extra])]:
 v=T.Verifier(s);v.sm['??1Rva0052B6FE@@QAE@XZ']=0x52b6fe;got=v.matched(text,rs);key='count-'+label;rec={'matched':sorted(got or []),'missing':sorted({r['target_rva'] for r in rs}-(got or set())),'errors':v.all_errors};results[key]=rec
 (lab/(key+'.cpp')).write_text(text,encoding='utf-8',newline='\n')
 if v.obj:
  path=lab/(key+'.obj');shutil.copyfile(v.obj,path);objects[key]=path;rec['facts']=facts(path);rec['EH']={};o=E.Obj(path);im=E.Image()
  for r in rs:
   if build.is_funclet_row(r,build.ledger_object_symbol(r)):continue
   eh=E.verify_row(im,o,build.ledger_object_symbol(r),int(r['target_rva'],16))
   if eh is not None:rec['EH'][r['name']]=eh
 print(key,{k:v for k,v in rec.items() if k!='facts'},flush=True)
results['control_sha256']={s:hashlib.sha256((main/s).read_bytes()).hexdigest() for s in sources}
(lab/'proof.json').write_text(json.dumps(results,indent=2)+'\n',encoding='utf-8',newline='\n')
