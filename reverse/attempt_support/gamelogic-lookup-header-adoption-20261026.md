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

The result is one fewer queued header adoption. Other GameLogic consumers and
the full class layout remain separate work; no new matched or linked bytes
are claimed.
