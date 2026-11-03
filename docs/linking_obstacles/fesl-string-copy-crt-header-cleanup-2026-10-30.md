### FESL string-copy CRT header cleanup (2026-10-30)

At base `e969e5b869`, Y2FeslSafeStrCopy.cpp removes its local strncpy
declaration and uses string.h with `/D_CRTIMP=` to retain retail's direct
CRT thunk call. All 13 rows verify; all 17 COMDAT fingerprints and 19 external
records are unchanged. The header auditor retires one queue finding. Strict
preparation passes and preview retains LINKS for 468 authored bytes against
`85f6b7f40c`. The batch audit is INCONCLUSIVE on the older index and missing
current receipt for affected consumer Common/0CreateAHeroManager21FE49.cpp.
Carry this provider and consumer into the next scheduled census; full consumer
closure remains unverified and no census gain is claimed.
[Evidence](../../reverse/attempt_support/fesl-string-crt-header-20261030-codexb.md).
