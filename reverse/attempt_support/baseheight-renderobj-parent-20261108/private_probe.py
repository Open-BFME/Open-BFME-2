import csv
import json
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, 'tools')
import tu_skeleton as T

source = 'Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva0006D0D7Dtor.cpp'
flags_source = 'Code/Libraries/Source/WWVegas/WW3D2/Rva001684D6Copy.cpp'
base = '102f753792'
before = subprocess.check_output(['git', 'show', base + ':' + source]).decode('utf-8')
flags = subprocess.check_output(['git', 'show', base + ':' + flags_source]).decode('utf-8').splitlines()[0]
candidate = flags + ' /Ireference/shims/bfme2_ascii\n' + before.split('\n', 1)[1]
start = candidate.index('class RO0 ')
end = candidate.index('class SnapC8', start)
candidate = candidate[:start] + '''#define BFME_RO_DTOR_DECL_ONLY
#include "../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"
class DX8_CleanupHook {
public:
    virtual void ReleaseResources() = 0;
    virtual void ReAcquireResources() = 0;
};
''' + candidate[end:]
candidate = candidate.replace('public RenderObjClass, public SnapC8',
                              'public RenderObjClass, public DX8_CleanupHook, public SnapC8')
candidate = candidate.replace('virtual ~BaseHeightMapRenderObjClass();',
                              'virtual ~BaseHeightMapRenderObjClass();\n'
                              'virtual void ReleaseResources();\nvirtual void ReAcquireResources();')
with Path(__file__).with_name('rows.csv').open(newline='', encoding='utf-8') as handle:
    rows = list(csv.DictReader(handle))
for label, text in [('before', before), ('after', candidate)]:
    verifier = T.Verifier(source)
    got = verifier.matched(text, rows) or set()
    print(label, json.dumps(dict(matched=len(got), rows=len(rows), errors=verifier.all_errors)), flush=True)
    assert len(got) == len(rows)
