### PlayerTemplate fragment inline-constructor cleanup (2026-10-28)

Status: scoped cleanup verified; TU placement and census consumer confirmation
pending. Base `34926aa896`; preview index `d92e7e6635`. Suppressing the unused
S3Money default-constructor copy in BfmeObject476Copy.cpp retires one unmatched
hatch. All 147 rows and seven EH graphs remain exact; all 178 retained external
COMDAT fingerprints and bindings are unchanged. Strict preparation passes, and
ordinary preview retains LINKS for 2,519 authored bytes. No census gain is claimed.
The proposed BfmeObject476 TU has no approved rows. Three container-wrapper
trials were reverted because they change STL constructor emission; reconcile
that context and establish target naming evidence before further recovery.
[Checks and prerequisites](../../reverse/attempt_support/bfmeobject476-cleanup-20261028-codexb.md).
Carry the removed-copy scope and its consumers into the next scheduled census.

The outgoing staged-tree audit is INCONCLUSIVE (exit 2): index `d92e7e6635`
predates the base and affected consumer
`Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Carry this
consumer and the removed-copy scope into the next scheduled census.
