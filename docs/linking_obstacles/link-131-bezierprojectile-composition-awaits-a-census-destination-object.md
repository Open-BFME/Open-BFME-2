### LINK-131: BezierProjectile composition awaits a census destination object

2026-10-30 follow-up (`6bfd053837`, index `12b9e7a7c0`): the current census now
contains the destination and all nine remaining whole-file donors as linked;
the cost accessor is already in the destination. The old missing-destination
prerequisite above no longer blocks this scope. The cached-key donor at
0x0045BFD9 needs its existing virtual/const declaration in the destination.
That declaration preserves all 23 destination external COMDATs and the
external definition/dependency/reference sets; paired builds pass 12/12 rows
and two EXACT EH graphs. The supported merge preview now accepts the cached-key
donor (12 rows total). Eight other whole-file donors still fail on private
views or missing declarations, and all five mixed sources remain untouched.
Ordinary preview preserves LINKS for both units (673 authored bytes). The
outgoing consumer audit remains INCONCLUSIVE: the index predates the base and
`Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Carry that
consumer into the next normal census; no census or runtime gain is claimed.
[Current evidence](../../reverse/attempt_support/bezier-cached-key-consolidation-20261030-codexb.md).

Composition after prerequisite `5910301b5f`: the supported merge absorbs the
cached-key donor, removes one source and repoints its three code rows and two
static-local data records. All 12 rows and both EH graphs pass; all 25 external
definitions and the union of symbol/reference bindings are unchanged. The
surviving unit's ordinary LINKS preview is 673 authored bytes, preserving the
prior pair's total. Header/MS-header refresh, data and path-consumer checks
pass. Eight donors and five mixed sources remain outside this merge. The
broader consumer limitation above remains; no census, runtime, debt or ownership
gain is claimed.

Status: Blocked; verified declaration prerequisite published. Updated: 2026-10-28; inspected revision: `f37de6bb3b`; latest fetched index: `54b83e4f69`.

Evidence / affected units: BezierProjectileBehavior.cpp and its existing cost accessor in Common/Bfme5FortyThree.cpp. The current supported merge plan has 47 approved rows and ten whole-file donors. [Scoped evidence and remaining private views](../../reverse/attempt_support/bezier-projectile-consolidation-20261028-codexb4.md).

Completed: expose the cost donor's existing twelve-byte element pointers at +0x44/+0x48 and size helper in the destination. Paired build passes 9/9 rows and one EXACT EH graph; all 21 destination external COMDAT digests and the external definition/dependency sets are unchanged. Frozen-file, class and strict receipt checks pass.

Remaining / next check: the cost donor now passes the supported merge's compile/byte checks, but its census-linked body cannot move into a destination with no census object: the guard cannot verify the resulting link order. A fresh index fetch still leaves that destination absent from census `54b83e4f69`. Await the normal census/index, then retry the supported merge. Nine other whole-file donors require separate private-view/declaration repairs; all five mixed sources remain untouched. No applying merge or source-path move was performed.

Outgoing audit: INCONCLUSIVE against parent `f7755f211c`; index `54b83e4f69` predates that base and affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Both scoped providers have refreshed strict receipts (9/9 exact). Carry this consumer and scope into the next normal census.

Clearance: unchanged prerequisite bytes/bindings only. Composition and selected-consumer coverage remain unverified; no linked-byte, source-file, debt, runtime or ownership gain is claimed.
