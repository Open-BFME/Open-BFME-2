### Game-logic random CRT declaration cleanup (2026-10-28)

Status: scoped cleanup verified; full consumer/census confirmation pending.
Inspected base `6d7a215d6b`, preview index `d92e7e6635`. The integer and real
GameLogicRandomValue units use the real string header for imported strrchr
and remove their misleading FILE aliases. Their game-side `_fprintf` call
remains bound to RVA 0x002CEC42, not the CRT stream operation. Both rows
remain exact, all external object facts are unchanged, and both ordinary
previews retain LINKS (213 authored bytes). Four local header declarations
are removed; the two logger-name findings remain.
[Evidence and remaining prerequisites](../../reverse/attempt_support/random-value-ms-headers-20261028-codexb.md).
The outgoing batch audit is INCONCLUSIVE: the index predates the base and
Common/0CreateAHeroManager21FE49.cpp lacks a current consumer receipt. Carry
that scope into the next scheduled census. No census-linked gain is claimed.
