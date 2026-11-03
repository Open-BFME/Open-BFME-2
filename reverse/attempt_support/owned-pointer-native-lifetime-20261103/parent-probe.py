from pathlib import Path
import ast,csv,hashlib,json,shutil,sys
main=Path.cwd();root=main/'build/sole-private-proof-20261103';sys.path.insert(0,str(root/'tools'));import build,tu_skeleton as T,eh_verify as E,link_census as C
lab=root/'build/owned-pointer-native-proof-20261103';s='Code/GameEngine/Source/Common/Rva005770F7Dtor.cpp';raw=(main/s).read_bytes();control=raw.decode('utf-8-sig');old='''struct Wrap1005770F7
{
	~Wrap1005770F7() { m_m.rva0057702E(); }
	Rva0057702E m_m;
};
''';assert control.count(old)==1
one=control.replace(old,'').replace('\tvoid rva0057702E();','\t~Rva0057702E();').replace('\tWrap1005770F7 m_14;','\tRva0057702E m_14;')
a=one.index('class Rva005CD7DA\n');b=one.index('class Rva005CD651\n',a);both=one[:a]+'''// The existing native39B record destructor owns the16-byte member cleanup.
class Wrap2000576C4B
{
public:
    ~Wrap2000576C4B();
private:
    int m_data[4];
};
'''+one[b:];both=both.replace('\tWrap2005770F7 m_18;','\tWrap2000576C4B m_18;');rows=[]
with (main/'reverse/functions.csv').open(encoding='utf-8',newline='') as f:
 for r in csv.DictReader(f):
  if r['source']==s and r['status']=='matched':rows.append(r)
f=ast.parse((root/'build/gamewindowmanager-readonly-20261103/gadget-anchor-probe.py').read_text());exec(compile(ast.Module(body=[n for n in f.body if isinstance(n,ast.FunctionDef) and n.name=='facts'],type_ignores=[]),'facts','exec'))
out={'source':s,'control_sha256':hashlib.sha256(raw).hexdigest(),'variants':{}}
for label,text in [('control',control),('direct-holder',one),('direct-both',both)]:
 v=T.Verifier(s);got=v.matched(text,rows);rec={'matched':sorted(got or []),'missing':sorted({r['target_rva'] for r in rows}-(got or set())),'errors':v.all_errors};out['variants'][label]=rec;(lab/('parent-'+label+'.cpp')).write_text(text,encoding='utf-8',newline='\n')
 if v.obj:
  p=lab/('parent-'+label+'.obj');shutil.copyfile(v.obj,p);rec['facts']=facts(p);rec['EH']=E.verify_row(E.Image(),E.Obj(p),'??1Rva005770F7@@UAE@XZ',0x5770f7)
 print(label,{k:v for k,v in rec.items() if k!='facts'},flush=True)
a,ap,ar=out['variants']['control']['facts']
for label in ['direct-holder','direct-both']:
 b,bp,br=out['variants'][label]['facts'];z={'old_count':len(a),'new_count':len(b),'removed':sorted(a.keys()-b.keys()),'added':sorted(b.keys()-a.keys()),'changed':sorted(n for n in a.keys()&b.keys() if a[n]!=b[n]),'properties_changed':sorted(n for n in ap.keys()&bp.keys() if ap[n]!=bp[n]),'removed_undefined':sorted(set(ar['undefined'])-set(br['undefined'])),'added_undefined':sorted(set(br['undefined'])-set(ar['undefined']))};out['variants'][label]['delta']=z;print(label,z,flush=True)
(lab/'parent-proof.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8',newline='\n')
