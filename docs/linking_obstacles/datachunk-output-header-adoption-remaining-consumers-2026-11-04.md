### DataChunkOutput header adoption in the remaining consumers (2026-11-04)

Status: Cleared for six header-debt rows in `Common/System/DataChunk.cpp`, `GameLogic/Map/SidesListDataChunks.cpp` and `SidesList_validateSides.cpp`; inspected revision `abef5f93e3`. These units now use canonical DataChunkOutput, and both SidesList units use canonical DataChunkInput. The owning acceptance commands retired four output and two input queue rows. Other input consumers remain queued; census confirmation is not claimed.

Verification: 168/168 matched functions, two data rows and three clean ordinary link previews preserving 11,012 bytes; [scope, acceptance results and preview receipt](../../reverse/attempt_support/datachunk-headers-20261104-codexb4/README.md).
