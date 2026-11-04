# DataChunk header adoption, 2026-11-04

Inspected revision: `abef5f93e3`. Scope: `class:DataChunkOutput`, claimed by
`yasinschroeder-codexb4` before edits.

The remaining output-header consumers were `Common/System/DataChunk.cpp`,
`GameLogic/Map/SidesListDataChunks.cpp` and `SidesList_validateSides.cpp`.
The automatic adoption trial stopped conservatively: `file` also names CRT
parameters in the first unit, and the two SidesList input views express their
entire 40-byte storage as an opaque array.

The retained edit replaces the output declarations with the existing canonical
header. Only output-method member references change from `file` to the existing
canonical `m_tmp_file`; CRT parameter names remain intact. The two SidesList
units also include canonical `DataChunk.h` instead of their opaque input views,
which would otherwise conflict with the output header's dependency. No new
layout or donor identity is inferred; the existing headers document their target
offset/signature evidence and donor naming basis. The local `writeAsciiString`
definition retains its `throw()` specification.

Verification:

- `./build.sh` on all three sources: **168/168 functions matched**, two data
  rows verified, 76 funclet rows verified, string/float/import checks passed.
- `find_declared_unmatched.py` before and after: all defined functions already
  matched (the DataChunk unit retains its informational unclaimed-definition
  count, with no frozen-file refusal).
- `header_adopt_lane.py accept --class DataChunkOutput` on all three: **3 PASS**,
  **4 queue rows retired** (DataChunk.cpp had two rows).
- `header_adopt_lane.py accept --class DataChunkInput` on the two SidesList
  units: **2 PASS**, **2 queue rows retired**.
- [Ordinary link preview](link-preview.txt): all three units link, preserving
  **11,012 -> 11,012** census-linked bytes against index `a62ac1c10b`, census
  2026-11-04 07:28. The listed unreferenced diagnostics are not blockers.

This clears these six header-queue entries only. Other DataChunkInput consumers
remain queued. No new census, real-link result or image-ownership gain is claimed.
