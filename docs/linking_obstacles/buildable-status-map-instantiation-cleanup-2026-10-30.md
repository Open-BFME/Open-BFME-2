### Buildable-status map instantiation cleanup (2026-10-30)

At base `43231d14ed`, VAsciiStringRva002460C3.cpp replaces its synthetic
GameLogic instantiation caller with an explicit member-template instantiation.
All four matched rows and all five retained external COMDAT fingerprints stay
exact; only the unrowed caller disappears. The fetched index records no other
source touching that name. Strict preparation passes and preview retains LINKS,
131 -> 131 authored bytes against `6fe1089c24` (2026-10-30 04:25). The owning
tools retire one Microsoft-header finding and one class-gate exemption.

The GameLogic header queue row remains: acceptance requires the canonical
include even after the class is removed. False reject recorded; no unused
include or verifier workaround. The staged batch audit is INCONCLUSIVE on its
older index and missing current `Common/0CreateAHeroManager21FE49.cpp` consumer
receipt. Full affected-consumer selection and loss checks remain unverified;
carry this provider and its wider consumers into the next scheduled census.
No census gain is claimed.
[Evidence and checks](../../reverse/attempt_support/buildable-map-instantiation-20261030-codexb5.md).
