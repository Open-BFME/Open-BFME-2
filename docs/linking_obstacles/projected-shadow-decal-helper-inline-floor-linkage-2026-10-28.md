### Projected shadow decal helper inline floor linkage (2026-10-28)

Status: consumer repair verified in preview; census confirmation pending.
Inspected base: `f3c74a9e4f`; index: `41c28839bf`.
`W3DProjectedShadowDecalHelpers.cpp` now gives the math-header `_floorf`
inline copy internal linkage. The scoped build verifies all 17 rows and the
EH verifier reports both graphs EXACT. The same-index ordinary preview changes
from blocked solely on `_floorf` to LINKS for 10,338 authored bytes. The
frozen-file check passes. Carry this consumer into the next normal census;
LINK-132/LINK-133 remain open globally and no census gain is claimed.
