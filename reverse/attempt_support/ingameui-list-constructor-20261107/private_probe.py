import csv
import json
import posixpath
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, 'tools')
import tu_skeleton as T

source = 'Code/GameEngine/Source/GameClient/InGameUI.cpp'
donor = 'Code/Libraries/Source/WWVegas/WWLib/Rva002A1B07Ctor.cpp'
flags = '-O1 -Ot -G7 -arch:SSE'
original = subprocess.check_output(['git', 'show', '5d3b84e454:' + source]).decode('utf-8')
donor_text = subprocess.check_output(['git', 'show', '5d3b84e454:' + donor]).decode('utf-8')
donor_text = T.relocate_includes(donor_text, posixpath.dirname(donor), posixpath.dirname(source))
anchor = 'namespace _STL { template <> _List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &); }'
inline = '''namespace _STL {
template <> inline list<Drawable *, allocator<Drawable *> >::list(const allocator<Drawable *> &__a)
    : _List_base<Drawable *, allocator<Drawable *> >(__a) {}
}'''
assert original.count(anchor) == 1
candidate = original.replace(anchor, anchor + '\n\n' + inline)
candidate = candidate.replace('namespace _STL { template <> list<Drawable *,allocator<Drawable *> >::list(allocator<Drawable *> const &); }', '')
with Path(__file__).with_name('rows.csv').open(newline='', encoding='utf-8') as handle:
    rows = list(csv.DictReader(handle))
sk = [(dict(rva=row['target_rva'], size=row['target_size']), row)
      for row in sorted(rows, key=lambda row: int(row['target_rva'], 16))]
report = {}
for label, host in [('before', original), ('after', candidate)]:
    verifier = T.Verifier(source, flags=flags)
    texts = {source: host, donor: donor_text}
    for strategy, _ in T.distinct_strategies(
            lambda strategy: T.compose(source, sk, [source, donor], texts, T.flags_of(host), strategy)):
        drop, drop_all = set(), set()
        for _ in range(16):
            text = T.compose(source, sk, [source, donor], texts, T.flags_of(host), strategy,
                             frozenset(drop), frozenset(drop_all))
            got = verifier.matched(text, rows)
            again = T.redefined(verifier.all_errors) if got is None else set()
            if not again - drop_all:
                break
            drop_all |= again & drop
            drop |= again
        if got is not None:
            report[label] = dict(matched=len(got), rows=len(rows),
                                 missing=[row['name'] for row in rows if row['target_rva'] not in got])
            break
    assert label in report, verifier.all_errors
    print(label, json.dumps(report[label]), flush=True)
assert report['before']['matched'] == 8
assert report['after']['matched'] == 9
