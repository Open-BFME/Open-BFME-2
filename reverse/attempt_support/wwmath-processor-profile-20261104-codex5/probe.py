import csv, io, subprocess, sys
from pathlib import Path
sys.path.insert(0, 'tools')
import tu_skeleton as T
header=subprocess.check_output(['head','-1','reverse/functions.csv'],text=True)
lines=subprocess.check_output(['rg','WW(?:Math|Lib)/wwmath.cpp,','reverse/functions.csv'],text=True)
rows=list(csv.DictReader(io.StringIO(header+lines)))
seed=Path('Code/Libraries/Source/WWVegas/WWMath/wwmath.cpp').read_text()
source=seed+'\n#include <stdlib.h>\nclass WWMath { public: static float Random_Float(); };\nfloat WWMath::Random_Float() { return ((float)(rand() & 0xFFF)) / (float)(0xFFF); }\n'
for flags in ['-O2 -G5 -arch:SSE -MD', '-O2 -G6 -arch:SSE -MD', '-O1 -G5 -arch:SSE -MD -Ot']:
 v=T.Verifier('Code/Libraries/Source/WWVegas/WWMath/wwmath.cpp',flags=flags)
 got=v.matched(source,rows)
 print(flags, sorted(got or []), flush=True)
