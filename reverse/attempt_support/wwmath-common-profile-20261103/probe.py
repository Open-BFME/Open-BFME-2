import csv,io,subprocess,sys,json
from pathlib import Path
sys.path.insert(0,'tools')
import tu_skeleton as T
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
names=['Code/Libraries/Source/WWVegas/WWMath/wwmath.cpp','Code/Libraries/Source/WWVegas/WWLib/wwmath.cpp']
header=subprocess.check_output(['head','-1','reverse/functions.csv'],text=True)
lines=subprocess.check_output(['rg','WW(?:Math|Lib)/wwmath.cpp,','reverse/functions.csv'],text=True)
rows=list(csv.DictReader(io.StringIO(header+lines)))
seed=Path(names[0]).read_text()
source=seed+'\n#include <stdlib.h>\nclass WWMath { public: static float Random_Float(); };\nfloat WWMath::Random_Float() { return ((float)(rand() & 0xFFF)) / (float)(0xFFF); }\n'
v=T.Verifier(names[0],flags='-O1 -G7 -arch:SSE -MD')
match=v.matched(source,rows)
print('base',match,v.obj,flush=True)
md=Cs(CS_ARCH_X86,CS_MODE_32)
for r in rows:
 if 'Random_Float' not in r['name']: continue
 p=v.B.compile_function(r,v.sm,v.obj)
 for title,data in [('retail',p['target']),('O1',p['bytes'])]:
  print(title,flush=True)
  for i in md.disasm(data,0):print(i.mnemonic,i.op_str)
variants={
 'integer-local':'int randomBits = rand() & 0xFFF; return randomBits / 4095.0f;',
 'unsigned-local':'unsigned randomBits = rand() & 0xFFF; return randomBits / 4095.0f;',
 'volatile-int':'volatile int randomBits = rand() & 0xFFF; return randomBits / 4095.0f;',
 'double-conversion':'return (float)((double)(rand() & 0xFFF) / 4095.0);',
 'double-denominator':'return ((float)(rand() & 0xFFF)) / 4095.0;',
 'multiply-reciprocal':'return (float)(rand() & 0xFFF) * (1.0f / 4095.0f);',
}
old='return ((float)(rand() & 0xFFF)) / (float)(0xFFF);'
for tag,body in variants.items():
 trial=source.replace(old,body)
 got=v.matched(trial,rows)
 print(tag,sorted(got or []),flush=True)
 if len(got or [])==len(rows): Path('build/wwmath-profile-20261103/winner.cpp').write_text(trial)
