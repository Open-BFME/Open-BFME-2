### BaseHeightMap bit-vector optimization cleanup (2026-10-28)

Status: cleanup verified; placement and census consumer confirmation pending.
Inspected base `c58504c47d`, preview index `41c28839bf`. Removing redundant
`/Oy-` and two optimization pragmas from Rva000677CAHostRva0006DC8E.cpp preserves
both rows and its LINKS preview (249 authored bytes). Strict preparation passes;
all nine external COMDAT names and definition/reference sets remain, while four
unused iterator copies lose their frame overhead and preview diagnostics.
The batch audit is INCONCLUSIVE: the older index lacks a current receipt for
Common/0CreateAHeroManager21FE49.cpp. Carry the changed copies and consumers into
the next normal census. The served 15 BaseHeightMap code rows still need naming
witnesses for three placeholder bracket owners; no TU approval or link gain is
claimed. [Evidence and prerequisites](../../reverse/attempt_support/baseheightmap-approval-cleanup-20261028-codexb.md).
