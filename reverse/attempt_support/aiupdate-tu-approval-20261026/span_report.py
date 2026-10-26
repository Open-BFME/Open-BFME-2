import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path('tools').resolve()))
import tu_map

captured = {}
def capture(frame, event, result):
    if event == 'return' and frame.f_code is tu_map.build.__code__:
        captured['roots'] = set(frame.f_locals['roots'])
        captured['rows'] = frame.f_locals['rows']

# Observe the ordinary read-only build; never change its inputs or verdicts.
sys.setprofile(capture)
try:
    tu_map.build(tu_map.Layout(Path.cwd()))
finally:
    sys.setprofile(None)

target = 'Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp'
own = [r for r in captured['rows'] if r['A'] == target]
core = [r for r in own if 0x00260000 <= r['rva'] <= 0x00270000]
narrow = [r for r in core if r['rva'] != 0x0026FF1E]
lo, hi = min(r['rva'] for r in narrow), max(r['rva'] for r in narrow)
foreign = [r for r in captured['rows'] if lo <= r['rva'] <= hi and r['A'] and r['A'] != target]
print('COUNTERFACTUAL BOUNDS ONLY: no admission or modified map', hex(lo), hex(hi))
for r in foreign:
    blocker = r['A'].lower() in captured['roots'] and r['by'] in tu_map.SPAN_BREAKERS
    print(json.dumps({k: r[k] for k in ('rva', 'size', 'name', 'source', 'A', 'by')}
                     | {'anchored_root': r['A'].lower() in captured['roots'], 'span_breaker': blocker}))
