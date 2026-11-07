import csv
import json
import re
import sys
import subprocess
from pathlib import Path

sys.path.insert(0, 'tools')
import tu_skeleton as T

source = 'Code/GameEngine/Source/GameClient/InGameUI.cpp'
lab = Path('build/ingameui-host-private-20261107')
lab.mkdir(exist_ok=True)
original = subprocess.check_output(['git', 'show', 'd4b1d294df:' + source]).decode('utf-8')
candidate = original
for name in ['isScrolling', 'setSelecting', 'isSelecting', 'setScrollAmount']:
    marker = '// ?InGameUI::' + name + ' present-unmatched'
    start = candidate.index(marker)
    signature = re.search(r'\bInGameUI::' + name + r'\s*\(', candidate[start:])
    assert signature, name
    opening = candidate.index('{', start + signature.end())
    end, depth = opening + 1, 1
    while depth:
        depth += (candidate[end] == '{') - (candidate[end] == '}')
        end += 1
    candidate = candidate[:start] + candidate[end:].lstrip('\n')
(lab / 'candidate.cpp.txt').write_text(candidate, encoding='utf-8', newline='\n')
with Path(__file__).with_name('rows.csv').open(newline='', encoding='utf-8') as handle:
    rows = [r for r in csv.DictReader(handle) if r['source'] == source]
report = {}
for label, text, region in [('original-current', original, False),
                            ('original-region', original, True),
                            ('pruned-current', candidate, False)]:
    verifier = T.Verifier(source, region=region)
    got = verifier.matched(text, rows) or set()
    report[label] = dict(rows=len(rows), matched=len(got),
                         missing=[dict(name=r['name'], rva=r['target_rva'], size=r['target_size'])
                                  for r in rows if r['target_rva'] not in got],
                         errors=verifier.all_errors,
                         object=str(verifier.obj) if verifier.obj else None)
    print(label, json.dumps(report[label]), flush=True)
(lab / 'report.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
