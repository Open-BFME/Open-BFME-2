### Formation selection parser direct deque call (2026-10-28)

Status: alias cleanup verified; TU placement and census confirmation pending.
Inspected base: `1d3867f364`; preview index: `41c28839bf`.
The parser now declares and calls the existing 0x00423BFD deque push_back
provider directly, retiring one linker alias. Its five rows and EH graph
remain exact; all 29 external COMDAT bodies and relocation targets are
unchanged after resolving the old alias. Parser and provider preserve LINKS
for 1,910 authored preview bytes. No new census-linked coverage is claimed.

The batch audit is INCONCLUSIVE because the index predates the base and
`Common/0CreateAHeroManager21FE49.cpp` lacks a current consumer receipt.
Carry the removed alias into the next normal census. The served
0x00423D0D..0x00424709 run still lacks a TU anchor; WorldBuilder's path and
parser vocabulary do not approve a merge.
[Evidence and next placement prerequisite](../../reverse/attempt_support/formation-selection-cleanup-20261028-codex.md).
