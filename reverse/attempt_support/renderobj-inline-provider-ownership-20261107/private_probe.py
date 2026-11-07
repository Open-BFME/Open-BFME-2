import csv,json,re,os,sys,subprocess
from pathlib import Path
sys.path.insert(0,'tools')
import tu_skeleton as T,link_census as C
lab=Path('build/mesh-four-provider-private-20261107');lab.mkdir(exist_ok=True)
header=Path('Code/Libraries/Source/WWVegas/WW3D2/rendobj.h')
raw=subprocess.check_output(['git','show','fdf8f1b9fe:'+header.as_posix()]).decode('utf-8')
for name in ['Get_Current_LOD','_bfme_ro_flag111','_bfme_ro_flag113','_bfme_ro_flag115']:
 m=re.search(r'\b'+re.escape(name)+r'\([^;{}]*\)[^;{}]*\{',raw);assert m,name
 start=m.end()-1;end=start+1;depth=1
 while depth:depth+=(raw[end]=='{')-(raw[end]=='}');end+=1
 raw=raw[:start]+';'+raw[end:]
# Save the exact proposed live header before making scratch include routes explicit.
(lab/'candidate-rendobj.h').write_text(raw,encoding='utf-8',newline='\n')
def include(m):
 target=header.parent/m.group(1)
 return '#include "'+Path(os.path.relpath(target,lab)).as_posix()+'"' if target.is_file() else m.group(0)
raw=re.sub(r'^#include "([^"]+)"',include,raw,flags=re.M)
(lab/'rendobj-four-proof.h').write_text(raw,encoding='utf-8',newline='\n')
sources=['Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapConstructor.cpp','Code/Libraries/Source/WWVegas/WW3D2/MeshClassLifetime.cpp']
rows={s:[] for s in sources}
with Path('reverse/functions.csv').open(newline='',encoding='utf-8') as f:
 for r in csv.DictReader(f):
  if r['source'] in rows:rows[r['source']].append(r)
report={}
for source in sources:
 text=Path(source).read_text();assert text.count('#include "rendobj.h"')==1
 text=text.replace('#include "rendobj.h"','#include "rendobj-four-proof.h"',1)
 lines=text.splitlines(keepends=True);lines[0]=lines[0].rstrip()+' /I'+lab.as_posix()+'\n';text=''.join(lines)
 v=T.Verifier(source);got=v.matched(text,rows[source])
 r={'rows':len(rows[source]),'matched':len(got or []),'missing':[r['name'] for r in rows[source] if r['target_rva'] not in (got or set())],'errors':v.all_errors}
 if v.obj:r['obj']=str(v.obj)
 report[source]=r;print(source,json.dumps(r),flush=True)
(lab/'report.json').write_text(json.dumps(report,indent=2))
