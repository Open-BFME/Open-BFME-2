### Anim2D lookup alias cleanup (2026-10-28)

Status: bounded cleanup verified; full consumer and census confirmation pending.
Inspected base `2d245982a2`, preview index `41c28839bf`. AutoHealBehavior's
lookup now calls the existing 0x002D752D owner directly, allowing the parser's
linker alias to be retired. All 15 affected rows, both EH graphs and all
46 external COMDAT bodies remain exact after resolving the former alias.
Strict preparation passes the caller, parser and lookup provider; ordinary
previews preserve LINKS for 1,872 authored bytes. The batch audit is
INCONCLUSIVE on the older index and an affected CreateAHeroManager receipt.
Carry this alias removal into the next normal census. Anim2D TU approval
remains blocked by the interleaved parser's donor-path anchor; no placement
or census gain is claimed.
[Checks and prerequisites](../../reverse/attempt_support/anim2d-alias-cleanup-20261028-codex.md).
