import ast,csv,json,shutil
from pathlib import Path
import build,tu_skeleton as T,eh_verify as E,link_census as C,header_adopt_lane as H
lab=Path('build/fade-full-view-proof-20261106');lab.mkdir(exist_ok=True)
p=Path('build/sole-private-proof-20261103/build/gamewindowmanager-readonly-20261103/gadget-anchor-probe.py')
fn=next(n for n in ast.parse(p.read_text()).body if isinstance(n,ast.FunctionDef) and n.name=='facts');exec(compile(ast.Module(body=[fn],type_ignores=[]),str(p),'exec'))
sources=['Code/GameEngine/Source/Common/FadeInTextRender.cpp','Code/GameEngine/Source/Common/Rva0059675ADtor.cpp','Code/GameEngine/Source/GameLogic/SkirmishAI/AIEconomyBuilder/rva00596908Rva00596908Farm.cpp']
base='''class Rva0059675ABase
{
public:
    virtual ~Rva0059675ABase();
    virtual void LoadAssets() = 0;
    virtual void rva00596908(Text004721F0 *text, const ICoord2D *pos, unsigned frame) = 0;
    virtual int rva002A98A7() const = 0;
    virtual int rva005C4ACD() const = 0;
};'''
derived='''struct FadeInTextRender : Rva0059675ABase
{
    FadeInTextRender();
    virtual ~FadeInTextRender();
    virtual void LoadAssets();
    virtual void rva00596908(Text004721F0 *text, const ICoord2D *pos, unsigned frame);
    virtual int rva002A98A7() const { return width; }
    virtual int rva005C4ACD() const { return delay; }
    void bfmeExtend(int left, int top, int right, int bottom);
    GameFont *font;
    int m_bfmeLeft, m_bfmeTop, m_bfmeRight, m_bfmeBottom;
    unsigned effectColor;
    Anim2D *anim;
    float scale;
    AsciiString fontName;
    unsigned color;
    int delay;
    unsigned fontSize;
    unsigned starts[3], ends[3];
    int width, height;
};'''
forward='class Text004721F0;\nstruct ICoord2D;\nclass GameFont;\nclass Anim2D;\n'
newrows=[('?rva002A98A7@FadeInTextRender@@UBEHXZ',0x2A98A7,4),('?rva005C4ACD@FadeInTextRender@@UBEHXZ',0x5C4ACD,4)]
rows_by={s:[] for s in sources}
with Path('reverse/functions.csv').open(newline='',encoding='utf-8') as f:
 for row in csv.DictReader(f):
  if row['source'] in rows_by and row['status']=='matched':rows_by[row['source']].append(row)
rows_by[sources[0]] += [dict(name=n,target_rva=hex(r),target_size=str(z),source=sources[0],status='matched',notes='') for n,r,z in newrows]
out=[]
for source in sources:
 text=Path(source).read_text()
 span=H.body_span(text,'FadeInTextRender');assert span;text=text[:span[0]]+derived+text[span[1]:]
 span=H.body_span(text,'Rva0059675ABase');assert span;text=text[:span[0]]+forward+base+text[span[1]:]
 if source==sources[1]:
  text=text.replace('#include "string_base.h"','#include "string_base.h"\n#include "ascii_string.h"')
  text=text.replace('m_1c ? m_1c->slot0(0) : 0','anim ? reinterpret_cast<Rva0059675AInner *>(anim)->slot0(0) : 0').replace('m_1c = 0','anim = 0')
 target=lab/(Path(source).stem+'.cpp.txt');target.write_text(text,newline='\n')
 v=T.Verifier(source);got=v.matched(text,rows_by[source]);r={'source':source,'candidate':target.as_posix(),'row_count':len(rows_by[source]),'matched':sorted(got or []),'missing':sorted({x['target_rva'] for x in rows_by[source]}-(got or set())),'errors':v.all_errors}
 if v.obj:
  obj=lab/(Path(source).stem+'.obj');shutil.copyfile(v.obj,obj);a=facts(build.obj_path(source));b=facts(obj)
  r.update(before_facts=a,after_facts=b,added=sorted(b[0].keys()-a[0].keys()),removed=sorted(a[0].keys()-b[0].keys()),changed=sorted(n for n in a[0].keys()&b[0].keys() if a[0][n]!=b[0][n]))
 out.append(r);print(json.dumps({k:v for k,v in r.items() if not k.endswith('_facts')},indent=2))
(lab/'proof.json').write_text(json.dumps(out,indent=2)+'\n',newline='\n')
