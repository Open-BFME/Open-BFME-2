### DX8 color clamp Vector4 adoption (2026-10-31)

The clamp unit includes the existing Vector4 storage header. A TU-local
component accessor preserves native SSE store order after direct-pointer
and local-reference trials failed. All three rows and five retained external
code bodies/relocations remain exact. The removed shared mutable accessor
and new internal helper copy each have only debug incoming edges; runtime
calls are unchanged. Strict preparation and owning acceptance retire one
Vector4 key, retaining bounded LINKS/654. With comparisons, two keys are
retired and bounded cohort 785 -> 785 is preserved.
[Controls and limits](../../reverse/attempt_support/color-clamp-vector4-adoption-20261031.md).

The comparison unit's unchanged Matrix3D row accessor is still reported
divergent by the shadow identity check; its separate class/provider work
remains open. Scoped LINKS is not a full selection or census verdict.

The outgoing two-source audit with fresh owned-provider receipts is
INCONCLUSIVE: `3c7a254a38` predates explicit base `9a6314fbcd`, and affected
consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt.
Carry this provider/consumer scope into the next scheduled census; the
two accepted keys do not establish complete consumer-loss clearance.
