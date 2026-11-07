import csv
import json
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, 'tools')
import tu_skeleton as T

source = 'Code/GameEngine/Source/GameClient/InGameUI.cpp'
text = subprocess.check_output(['git', 'show', '5d3b84e454:' + source]).decode('utf-8')
with Path(__file__).with_name('rows.csv').open(newline='', encoding='utf-8') as handle:
    rows = list(csv.DictReader(handle))
report = {}
for label, flags, region in [('old', None, False), ('regional', None, True),
                              ('optimized', '-O1 -Ot -G7 -arch:SSE', False)]:
    verifier = T.Verifier(source, flags=flags, region=region)
    got = verifier.matched(text, rows) or set()
    guard = T.LinkGuard(source)
    preparation = guard.prepare([source]) if label == 'optimized' else None
    verdict = guard.judge(verifier.obj, [source], verifier.effective(text, rows)) \
        if label == 'optimized' and preparation is None and len(got) == len(rows) else None
    report[label] = dict(rows=len(rows), matched=len(got),
                         missing=[row['name'] for row in rows if row['target_rva'] not in got],
                         errors=verifier.all_errors, preparation=preparation, guard=verdict)
    print(label, json.dumps(report[label]), flush=True)
out = Path('build/ingameui-optimized-host-20261107')
out.mkdir(exist_ok=True)
(out / 'report.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
