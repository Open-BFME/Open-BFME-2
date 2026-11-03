### Living-world scorekeeper CRT time declarations (2026-10-30)

At base `f3871e5718`, LivingWorldScoreKeeper.cpp replaces two handwritten
`time` declarations with `<time.h>` under its supported scoped `_CRTIMP`
configuration. The owning Microsoft-header scanner retires one local queue
row; included-shim findings remain separate. All 23 rows and the EXACT
parent EH graph verify. All 70 external COMDAT fingerprints, external
bindings and reference graphs remain unchanged. Strict preparation passes;
ordinary preview retains LINKS and 1,982 authored bytes against index
`12b9e7a7c0` (2026-10-30 10:11).

The scoped staged audit is INCONCLUSIVE on that older index and the missing
current `Common/0CreateAHeroManager21FE49.cpp` consumer receipt. Full
affected-consumer selection and loss checks remain pending; carry this
provider and wider consumers into the next scheduled census. No census
gain is claimed. [Verification](../../reverse/attempt_support/scorekeeper-crt-header-20261030-codexb.md).
