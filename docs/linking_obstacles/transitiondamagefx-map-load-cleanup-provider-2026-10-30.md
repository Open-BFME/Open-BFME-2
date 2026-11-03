### TransitionDamageFX map-load cleanup provider (2026-10-30)

At base `080799847f`, the map-load unit still emits a conflicting
`_Vector_base<AsciiString>` destructor. Declaring its string-vector destructor
specialization uses the existing native `0x0002CC70` provider and suppresses
13 local cleanup copies. All 13 retained external COMDAT fingerprints and all
five source rows remain unchanged; the parent EH graph is EXACT. Strict
three-source preparation passes 36/36 rows. Ordinary paired-scope preview
reports 3/3 LINKS for 1,546 authored bytes against `6fe1089c24`; the repaired
caller's isolated preview changes from failure to LINKS for its 339 bytes.

The staged batch audit is INCONCLUSIVE on the older index and missing current
`Common/AIBuildable.cpp` consumer receipt. Full affected-consumer selection
and loss checks remain unverified; carry this caller, the string-vector
destructor provider and affected consumers into the next scheduled census.
No census gain or debt retirement is claimed. The existing LINK-135
copy-constructor repair is separate and remains valid in this preview.
[Native binding and object comparison](../../reverse/attempt_support/transitiondamagefx-map-link-20261030-codex3.md).
