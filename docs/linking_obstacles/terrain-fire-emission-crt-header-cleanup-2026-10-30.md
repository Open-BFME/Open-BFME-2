### Terrain fire emission CRT header cleanup (2026-10-30)

At base `7f540888a6`, Rva0055E6D4Write.cpp replaces its local free declaration
with stdlib.h and `/D_CRTIMP=`, preserving the retail direct call that blocked
the earlier header trial. All four rows and the exact EH graph verify; all
553 COMDAT fingerprints and 570 external records are unchanged. The header
auditor retires one queue finding. Strict preparation passes and preview
retains LINKS for 322 authored bytes against `85f6b7f40c`. The batch audit
is INCONCLUSIVE on the older index and missing current receipt for affected
consumer Common/0CreateAHeroManager21FE49.cpp. Carry that consumer and this
provider into the next scheduled census; full consumer closure remains
unverified and no census gain is claimed.
[Evidence](../../reverse/attempt_support/terrain-fire-crt-header-20261030-codexb.md).
