import csv
import json
import os
import re
import sys
import subprocess
from pathlib import Path

sys.path.insert(0, 'tools')
import tu_skeleton as T

lab = Path('build/state-transition-canonical-20261107')
lab.mkdir(exist_ok=True)
header = Path('Code/GameEngine/Include/Common/StateMachine.h')
raw = subprocess.check_output(['git', 'show', '1bba2f618a:' + header.as_posix()]).decode('utf-8')
raw = raw.replace('class Object;\n', 'class Object;\nstruct StateConditionInfo;\n', 1)
raw = raw.replace(' void *m_transitionsFirst; //10\n void *m_transitionsLast; //14',
                  ' const StateConditionInfo *m_transitionsFirst; //10\n'
                  ' int m_transitionsLast; //14: native transition count, legacy spelling')
assert 'int m_transitionsLast;' in raw
raw = raw.replace(' int m_id; //4',
                  ' void rva004D7127(const StateConditionInfo *conditions);\n'
                  ' StateReturnType friend_checkForTransitions(StateReturnType status);\n'
                  ' StateReturnType friend_checkForSleepTransitions(StateReturnType status);\n'
                  ' int m_id; //4', 1)
(lab / 'candidate-StateMachine.h').write_text(raw, encoding='utf-8', newline='\n')

def route_include(match):
    target = header.parent / match.group(1)
    return '#include "' + Path(os.path.relpath(target, lab)).as_posix() + '"' if target.is_file() else match.group(0)

raw = re.sub(r'^#include "([^"]+)"', route_include, raw, flags=re.M)
(lab / 'state-transition-proof.h').write_text(raw, encoding='utf-8', newline='\n')
seed = 'Code/GameEngine/Source/Common/StateMachine.cpp'
ctor = 'Code/GameEngine/Source/Common/StateCtor.cpp'
text = subprocess.check_output(['git', 'show', '1bba2f618a:' + seed]).decode('utf-8')
text, n = re.subn(r'enum StateReturnType\s*\{[^}]*\};', '', text, count=1)
assert n == 1
text, n = re.subn(r'class __declspec\(novtable\) State\s*\{.*?\n\};', '', text, count=1, flags=re.S)
assert n == 1
text = text.replace('#include "Common/Snapshot.h"', '#include "Common/Snapshot.h"\n#include "state-transition-proof.h"', 1)
text = text.replace('m_transitionsCount', 'm_transitionsLast')
candidate_texts = {seed: text, ctor: subprocess.check_output(['git', 'show', '1bba2f618a:' + ctor]).decode('utf-8').replace(
    '#include "../../Include/Common/StateMachine.h"', '#include "state-transition-proof.h"', 1)}
rows = {seed: [], ctor: []}
with Path(__file__).with_name('rows.csv').open(newline='', encoding='utf-8') as handle:
    for row in csv.DictReader(handle):
        if row['source'] in rows:
            rows[row['source']].append(row)
report = {}
for source, text in candidate_texts.items():
    lines = text.splitlines(keepends=True)
    lines[0] = lines[0].rstrip() + ' /I' + lab.as_posix() + '\n'
    candidate = ''.join(lines)
    (lab / (Path(source).name + '.txt')).write_text(candidate, encoding='utf-8', newline='\n')
    verifier = T.Verifier(source)
    matched = verifier.matched(candidate, rows[source]) or set()
    report[source] = dict(rows=len(rows[source]), matched=len(matched),
                          missing=[row['name'] for row in rows[source] if row['target_rva'] not in matched],
                          errors=verifier.all_errors,
                          object=str(verifier.obj) if verifier.obj else None)
    print(json.dumps({source: report[source]}), flush=True)
(lab / 'report.json').write_text(json.dumps(report, indent=2), encoding='utf-8')
sys.exit(0 if all(item['rows'] == item['matched'] for item in report.values()) else 1)
