"""Native-only audit of changed non-VP6 donors; never reads donor source text.

This is a scoped refresh, not bfme1_sweep.scan or a global control-floor result.
Placements are byte evidence, not BFME 2 identity or source-transfer approval.
"""
from pathlib import Path
import csv
import hashlib
import io
import json
import subprocess
import sys

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / 'tools'))
import bfme1_sweep as sweep

OUT = ROOT / 'build/bfme1-refresh-f64f0f32'
OUT.mkdir(parents=True, exist_ok=True)
audit = json.loads(Path(__file__).with_name('input-audit.json').read_text())
revision = audit['new']
sources = [s for s in audit['changed'] if s.startswith('game/')
           and s.endswith(('.cpp', '.c'))
           and not any(x in s.lower() for x in ('vp6', 'winamp', 'ffdshow', 'mfnode', 'on2'))]
assert sources
assert all('vp6' not in source.lower() for source in sources)
reference = ROOT / 'reference/open-bfme-1'
ledger = 'targets/game/reverse/functions.csv'
with (reference / ledger).open() as handle:
    header = handle.readline()
command = ['git', '-C', str(reference), 'show', revision + ':' + ledger]
producer = subprocess.Popen(command, stdout=subprocess.PIPE)
select = ['rg', '-F']
for source in sources:
    select += ['-e', source]
selected = subprocess.run(select, stdin=producer.stdout, capture_output=True, text=True)
producer.stdout.close()
assert producer.wait() == 0
assert selected.returncode in (0, 1), selected.stderr
rows = list(csv.DictReader(io.StringIO(header + selected.stdout)))
rows = [row for row in rows if row.get('source') in sources]
donor_image = sweep.Image(sweep.BFME1_EXE)
target_image = sweep.Image(sweep.build.EXE)
records = []
for row in rows:
    notes = row.get('notes', '')
    size = int(row['target_size'])
    if size < sweep.MIN_FUNC or 'gen-' in notes or 'vendored=' in notes:
        continue
    donor_rva = int(row['target_rva'], 16)
    donor = donor_image.body(donor_rva, size)
    record = dict(donor_name=row['name'], donor_source=row['source'],
                  donor_rva=hex(donor_rva), size=size, placements=[])
    records.append(record)
    if donor is None or len(donor) != size:
        record['verdict'] = 'unreadable-retail-extent'
        continue
    fields = sweep.volatile_fields(donor, donor_image, donor_rva)
    runs = sweep.clear_runs(sweep.mask_from(fields, size))
    if not runs or runs[0][1] < sweep.MIN_NEEDLE:
        record['verdict'] = 'no-discriminating-needle'
        continue
    offset, length = runs[0]
    candidates = sweep.occurrences(target_image.text, donor[offset:offset + length],
                                   cap=sweep.PLACEMENT_CAP)
    if len(candidates) >= sweep.PLACEMENT_CAP:
        record['verdict'] = 'candidate-cap-reached'
        continue
    for candidate in candidates:
        start = candidate - offset
        if start < 0 or start + size > len(target_image.text):
            continue
        target_rva = target_image.text_rva + start
        window = target_image.text[start:start + size]
        unexplained, _, _ = sweep.explain(donor, fields, runs, window, donor_rva,
                                         target_rva, donor_image, target_image)
        if unexplained == 0:
            record['placements'].append(hex(target_rva))
            if len(record['placements']) > sweep.AMBIGUOUS_CAP:
                break
    count = len(record['placements'])
    record['verdict'] = ('no-exact-placement' if count == 0 else
                         'unique-native-placement' if count == 1 else
                         'ambiguous-native-placement')
result = dict(scope='changed non-VP6 donor metadata and retail bytes only',
              donor_revision=revision, source_paths=sources,
              donor_source_text_read=False, full_sweep_run=False,
              global_control_floor_claimed=False,
              source_transfer_or_identity_claimed=False,
              target_head=subprocess.check_output(['git', 'rev-parse', 'HEAD'], text=True).strip(),
              donor_retail_sha256=hashlib.sha256(sweep.BFME1_EXE.read_bytes()).hexdigest(),
              target_retail_sha256=hashlib.sha256(sweep.build.EXE.read_bytes()).hexdigest(),
              selected_ledger_rows=len(rows), inspected_native_bodies=len(records),
              records=records)
(OUT / 'affected-donors.json').write_text(json.dumps(result, indent=2) + '\n')
from collections import Counter
print(json.dumps(dict(selected_rows=len(rows), native_bodies=len(records),
                      verdicts=dict(Counter(r['verdict'] for r in records))), indent=2))
