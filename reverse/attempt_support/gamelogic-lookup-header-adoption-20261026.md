# GameLogic lookup header adoption

Inspected upstream `8da4ac24ce`, with verified BFME 1 reference `f633d0e97a`.
This pass replaces private pointer-only GameLogic declarations with the
registered `Code/GameEngine/Source/Common/GameLogicObjectLookupView.h`.
The shared header, ABI names, pins and function/data rows are unchanged.

## AITarget owner: Rva002C589BDtor.cpp

The default queue served the complete source at
`Code/GameEngine/Source/Common/Rva002C589BDtor.cpp`. Its historical adoption
failure was `Data rows: FAIL 1 of 1`; current baseline verification already
passes that data row, so this change does not claim a separate data repair.

Include the canonical header, remove the local GameLogic and ObjectID bodies,
and use its zero-valued `INVALID_OBJECT_ID` in reset and construction. The unit
only calls GameLogic through `TheGameLogic`; it neither constructs that class
nor relies on its size. The complete source was read before editing.

- Before and after normal byte/reference checks: 9/9 function rows, 434 bytes;
  the existing four-byte `g_AITargetThreatFinderSerial` data row and one string
  literal also pass. Frozen-file checks pass before and after.
- Before and after EH verification: one EXACT graph, no baseline exceptions.
- Ordinary link previews against census index `f995f30157` (2026-10-25
  21:36 UTC) keep this already-linked unit at 406 authored nonpadding bytes.
  The preview does not establish global closure or a new census result.
- `header_adopt_lane.py accept --class GameLogic` passes and retires this
  source's single queue row through the normal owning-tool path.

## Indexed object getter: Rva0025BFF8ObjectGetter.cpp

The complete 24-byte getter consumes ObjectID values from its existing array
and calls the same `findObjectByID` provider. Replace its local GameLogic and
ObjectID declarations with the same canonical header. The removed
`OBJECTID_INVALID = -1` enumerator was unused; no value test or stored value
changes. Current normal builds and frozen-file checks pass before and after
(1/1 row); the ordinary link preview remains 24 -> 24 bytes. The owning header
acceptance command retires this source's one queue row. No function row or
pin changes.

## Audio owner position: BfmeAudioEventOwnerPosition.cpp

The complete 332-byte owner-position worker uses GameLogic only in its
object-ID branch. Include the canonical header and remove the local GameLogic
and ObjectID declarations; both removed enumerators were unused. The worker,
its five cases, existing native offsets and global bindings are unchanged.
Normal builds and frozen-file checks pass before and after (1/1 row), and
the header acceptance command retires this source's queue row.

The final ordinary preview checks all three current objects together against
the same published index: 3/3 link cleanly, 762 -> 762 authored nonpadding
bytes. All 11 matched rows preserve 790 bytes, plus the existing four-byte
data row; the cohort's one EH graph remains EXACT.

The result is three fewer queued header adoptions. Other GameLogic consumers and
the full class layout remain separate work; no new matched or linked bytes
are claimed.
