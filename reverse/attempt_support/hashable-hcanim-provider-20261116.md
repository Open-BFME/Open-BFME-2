# Restore the hcanim Hashable provider

Base: `46a8a48d9e`. Local repair only. Claims cover HashableClass, its constructor
at RVA `0x000EF9C2`, hcanim.cpp and the affected records. The user previously
explicitly authorized official admission of these two restored optimization
directives for local work; this is the same bounded historical restoration.

Commits `32d5ed6157` and `c7bf2ea72a` removed the optimization scope around
hash.h, the existing vector-constructor anchor and refcount.h. Matched hcanim
rows still pass, but its emitted inline providers differ from retail. Restore
the historical `#pragma optimize("gsy", on)` / `#pragma optimize("", on)` pair;
do not change the canonical class, add a caller or move a row. The official
`hatch_counters.py --admit` records the exact two tokens. These two restored
directives increase registered pragma debt; they are not debt retirement.
The file's CRLF endings are normalized to LF because Git's whitespace check
rejects the CR characters on the two added lines; the non-whitespace source
delta remains just those two directives. Normalization exposes legacy trailing
spaces to the staged whitespace check, so these are trimmed as well. Admissions
are re-stamped by the tool.

Native constructor row: 13 bytes, including RET (earlier modern-branch prose
incorrectly called it 12). Current-master copy before repair is 16 bytes:
`8bc1c70000000000c7400400000000c3`, vtable relocation at +4. Repaired copy is
`8bc183600400c70000000000c3`, vtable relocation at +8. Both bind
`??_7HashableClass@@6B@`; the latter is judged retail by RetailTruth.

Exactly four COMDAT fingerprints change, all from wrong to retail:

| Provider | Before | After |
| --- | ---: | ---: |
| HashableClass constructor | 16 | 13 |
| HashableClass scalar deleting destructor | 31 | 29 |
| compiler vector constructor iterator (`??_H`) | 50 | 34 |
| RefCountClass scalar deleting destructor | 31 | 29 |

No COMDAT is added or removed. Official `./build.sh hcanim.cpp` passes 62/62
rows, three strings, 15 float literals and two imports, before and after.
`eh_verify.py` reports all six EH graphs EXACT. The paired ordinary preview
reports LINKS for hcanim and W3DProjectedShadow, retaining 11,931 bytes
(8,465 + 3,466) against the existing index at `aa505f34c8`. That is a preview,
not proof of a full link, merge or working selections.

Evidence is in `build/decal-diagnostic/hashable-master-before-build.log`,
`hashable-master-after-build.log`, `hashable-master-provider-diff.json` and
`hashable-master-paired-link.log`. The before object is retained for comparison.
After committing the code, `link_check.py --update-index` refreshed the index
to `061d53ad84` (699 objects reread, 135 removed, one new unit not in the census).
The official focused `tu_skeleton.py --merge --dry-run` now gets past the seed:
the Hashable selected-provider rejection is gone and both donors are tried.
No donor is accepted yet. The reader fails on floorf linkage and duplicate
Coord3D/PartitionManager/Thing/ICoord2D views; the writer fails on duplicate
Coord3D/RenderInfoClass, TheDX8MeshRenderer pointer/object disagreement and
drawStartX/Y storage declarations. Thus the constructor prerequisite is cleared,
but canonical-header/view reconciliation is still needed. No merge was applied.
Logs: `hashable-master-index.log`, `hashable-master-merge-dry.log`.
