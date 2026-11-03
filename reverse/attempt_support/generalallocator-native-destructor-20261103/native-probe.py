from pathlib import Path
import ast,csv,hashlib,json,shutil,sys
main=Path.cwd();root=main/'build/sole-private-proof-20261103';sys.path.insert(0,str(root/'tools'));import build,tu_skeleton as T,eh_verify as E,link_census as C
lab=root/'build/generalallocator-native-proof-20261103';lab.mkdir(exist_ok=True)
a=ast.parse((root/'build/gamewindowmanager-readonly-20261103/gadget-anchor-probe.py').read_text());exec(compile(ast.Module(body=[n for n in a.body if isinstance(n,ast.FunctionDef) and n.name=='facts'],type_ignores=[]),'facts','exec'))
sources=['Code/GameEngine/Source/Common/VslotSmallBodiesAJ_Rva00034D00.cpp','Code/GameEngine/Source/Common/Rva006C3CC0Cluster.cpp'];rows={s:[] for s in sources}
with (main/'reverse/functions.csv').open(encoding='utf-8',newline='') as f:
 for r in csv.DictReader(f):
  if r['source'] in rows and r['status']=='matched':rows[r['source']].append(r)
texts={s:(main/s).read_text(encoding='utf-8-sig') for s in sources};candidates={}
s=sources[0];old='''// 0x00034D00: tail jump to Rva006C1F60::rva00033D50.
class Rva00034D00 : public EA::Allocator::GeneralAllocator
{
public:
	bool rva00034D00();
};
bool Rva00034D00::rva00034D00()
{
	return EA::Allocator::GeneralAllocator::rva00033D50();
}''';assert texts[s].count(old)==1
candidates[s]=texts[s].replace(old,'''// Native 0x00034D00: the nonvirtual GeneralAllocator destructor.
// Derived destruction and its unwind action call this thunk, which runs
// the independently rowed teardown at 0x00033D50.
EA::Allocator::GeneralAllocator::~GeneralAllocator()
{
    rva00033D50();
}''')
s=sources[1];start=texts[s].index('namespace EA\n');end=texts[s].index('\nclass Rva006C17B0',start);candidates[s]=texts[s][:start]+'#include "../../Include/Common/GeneralAllocator.h"\n'+texts[s][end:];candidates[s]=candidates[s].replace('unsigned char m_pad0[0x684];','unsigned char m_pad0[0x174];');assert candidates[s]!=texts[s]
out={'sources':sources,'control_sha256':{s:hashlib.sha256((main/s).read_bytes()).hexdigest() for s in sources},'variants':{}}
for s in sources:
 for label,text in [('control',texts[s]),('candidate',candidates[s])]:
  rs=[dict(r) for r in rows[s]]
  if label=='candidate':
   for r in rs:
    if int(r['target_rva'],16)==0x34d00:r['name']='??1GeneralAllocator@Allocator@EA@@QAE@XZ';r['notes']='Canonical nonvirtual GeneralAllocator destructor; actual34D00 thunk'
  v=T.Verifier(s)
  if label=='candidate':v.sm['??1GeneralAllocator@Allocator@EA@@QAE@XZ']=[0x34d00]
  got=v.matched(text,rs);key=Path(s).stem+'-'+label;rec={'matched':sorted(got or []),'missing':sorted({r['target_rva'] for r in rs}-(got or set())),'errors':v.all_errors};out['variants'][key]=rec
  (lab/(key+'.cpp')).write_text(text,encoding='utf-8',newline='\n')
  if v.obj:
   p=lab/(key+'.obj');shutil.copyfile(v.obj,p);rec['facts']=facts(p);rec['EH']={};o=E.Obj(p);im=E.Image()
   for r in rs:
    if build.is_funclet_row(r,build.ledger_object_symbol(r)):continue
    eh=E.verify_row(im,o,build.ledger_object_symbol(r),int(r['target_rva'],16))
    if eh is not None:rec['EH'][r['name']]=eh
  print(key,{k:v for k,v in rec.items() if k!='facts'},flush=True)
(lab/'proof.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8',newline='\n')
