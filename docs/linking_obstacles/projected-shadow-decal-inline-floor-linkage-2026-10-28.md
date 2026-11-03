### Projected-shadow decal inline floor linkage (2026-10-28)

Status: bounded cleanup verified; full consumer and census confirmation pending.
Inspected base: `e6588f7665`; preview index: `41c28839bf`.
W3DProjectedShadowDecalHelpers.cpp now keeps its unused math-header `floorf`
wrapper local. All 17 rows, both EH graphs, all 82 retained external COMDAT
fingerprints and external dependencies are unchanged. Same-index ordinary
preview changes this unit from blocked to LINKS for 10,338 authored bytes.
LINK-132 / LINK-133 already record a separate selected-provider repair;
this old-index result is not a new census or incremental master-wide gain.

The outgoing batch audit is INCONCLUSIVE: the index predates the base and
Common/0CreateAHeroManager21FE49.cpp lacks a current consumer receipt. Carry
this removed-copy scope into the next normal census; full external consumer
selection remains unverified.
[Evidence and object comparison](../../reverse/attempt_support/decal-floor-link-20261028-codex.md).
