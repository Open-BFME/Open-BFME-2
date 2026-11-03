### WinMain Microsoft-header migration (2026-10-28)

Status: scoped cleanup verified; external consumer/census confirmation pending.
Inspected base: `46f3656491`; preview index: `41c28839bf`.
WinMain now uses the Platform SDK and CRT headers, removing all 140 flagged
local Microsoft declarations. All 13 rows and its EH graph remain exact; all
35 external COMDAT digests and external definition/reference sets are unchanged.
Strict preparation passes and ordinary preview retains LINKS for 3,224 authored
bytes. The batch audit is INCONCLUSIVE: the index predates the base and affected
consumer Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Carry this
scope into the next census; no linking gain is claimed.
[Evidence and checks](../../reverse/attempt_support/winmain-ms-headers-20261028-codexb.md).
