# FlammableUpdate: canonical TreeKey changes cleanup code

Inspected `8b681de717`, 2026-11-05. The supported consolidation planner ran
under `Code/GameEngine/Source/GameLogic/Object/Update/`; its current queue
identifies the destructor donor and two camera helpers. No merge was applied.
Read the preceding frame-prerequisite handoff before testing this new hypothesis.

Target facts: the original `FlammableUpdateDtor.cpp` passes all 18 code rows,
eight funclets, three string literals and three floats. Its ordinary link preview
preserves 2,817 census-linked bytes against index `f44cbcf5b0` (2026-11-05
15:19); this is a preview, not a new census measurement.

Trial: replace the private TreeKey body with the existing canonical header,
use `field04` for the string, and cast `field00` to `const FXList *` at the two
FXList calls. This avoids the automated adoption's file-scope `fx` token rename
collision without changing the shared header or declaring another canonical
class body.

`./build.sh Code/GameEngine/Source/GameLogic/Object/Update/FlammableUpdateDtor.cpp`
rejects `tryToIgnite` (17/18 ordinary rows pass). The normal loop cleanup changes
from `lea ecx,[ebp-14h]` followed by StringBase<char>::releaseBuffer (0x00036410)
to `lea ecx,[ebp-18h]` followed by TreeKey's declared destructor (0x0029D7C2).
Two EH cleanup bodies also change. The canonical header expressly declares an
out-of-line destructor; the private view had an implicit destructor which
allowed the string-member cleanup directly. Equal record layouts and matching
field accesses therefore do not establish interchangeable cleanup codegen.

Restored the original file immediately and reran the normal build: 18/18,
funclets and literals pass. The source diff is empty; no source paths, ledger
rows, headers, pins or debt keys changed. All claims were released.

Next: reconcile this record's lifetime/cleanup codegen with the canonical
out-of-line destructor contract before retrying the field-only adoption or the
merge. The earlier `/Oy-` rejection and camera-helper byte mismatches still
stand; they were not retried. No donor-name, census, runtime or debt-retirement
claim follows from this attempt.
