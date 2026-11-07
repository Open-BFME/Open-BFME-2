import csv,json,sys,hashlib,subprocess
from pathlib import Path
sys.path.insert(0,'tools')
import tu_skeleton as T,link_census as C,build
source='Code/Libraries/Source/WWVegas/WW3D2/collect.cpp'
lab=Path('build/collect-5ad93a-recovery-20261107');lab.mkdir(exist_ok=True)
raw=subprocess.check_output(['git','show','009791f6a9:'+source]);text=raw.decode('utf-8')
call='\tobject->RenderObjClass::Set_ObjectScale(0.0f);\n'
assert text.count(call)==1
text=text.replace(call,'')
text+='''\n// Native 0x005AD93A stores one float at receiver+0x4C and returns with ret4.\n// No callers or table entries identify its original owner. Keep an address\n// placeholder rather than attributing this different field offset to RenderObjClass.\nclass Rva005AD93AOwner\n{\npublic:\n    void rva005AD93A(float value);\nprivate:\n    unsigned char m_unknown[0x4C];\n    float m_value;\n};\n\nvoid Rva005AD93AOwner::rva005AD93A(float value)\n{\n    m_value = value;\n}\n'''
with Path('reverse/functions.csv').open(newline='',encoding='utf-8') as f:rows=[r for r in csv.DictReader(f) if r['source']==source]
name='?rva005AD93A@Rva005AD93AOwner@@QAEXM@Z'
wanted=[{**r,'name':name,'notes':'Native unreferenced float setter at receiver+0x4C; original owner unknown; replaces incorrect RenderObjClass alias.'} if r['target_rva'].lower()=='0x005ad93a' else r for r in rows]
v=T.Verifier(source);v.sm[name]=[0x5AD93A]
got=v.matched(text,wanted)
report={'source':source,'before_sha256':hashlib.sha256(raw).hexdigest(),'rows':len(wanted),'matched':len(got or []),'missing':[r['name'] for r in wanted if r['target_rva'] not in (got or set())],'errors':v.all_errors}
if v.obj:
 defs,und,_,_,_=C.object_symbols(v.obj)
 report.update(obj=str(v.obj),old_set_scale_defined='?Set_ObjectScale@RenderObjClass@@UAEXM@Z' in defs,new_setter_defined=name in defs)
 (lab/'candidate.cpp').write_text(text,encoding='utf-8',newline='\n')
(lab/'report.json').write_text(json.dumps(report,indent=2))
print(json.dumps(report))
