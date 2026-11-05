### VideoPlayer two-row donor consolidation (2026-10-29)

Status: bounded composition verified; remaining donors and census confirmation
pending. Inspected base d2cd76f18672; index 840db2d676 (2026-10-28 20:44).
The existing fuller SubsystemInterface header preserves the approved
Rva006892F0 donor's 56-byte vtable, allowing the supported merge to absorb its
11-byte destructor and 30-byte deleting wrapper into VideoPlayer.cpp.
One source file is removed; all 24 rows, 32 bindings, external object facts and
the EH graph remain exact/unchanged. Ordinary preview preserves the combined
1,113 authored bytes. A donor-only canonical-header trial truncated the table
to four bytes despite exact function bodies and was reverted. The canonical
header's full virtual interface, differing VideoPlayer base views, record
class-key/ownership views and compiler contexts remain prerequisites for the
other donors. No canonical-header adoption or census gain is claimed.
The outgoing audit is INCONCLUSIVE: the index predates the base and
Common/0CreateAHeroManager21FE49.cpp lacks a current consumer receipt. Carry
that consumer and the moved provider scope into the next scheduled census.
[Verification, trials and complete path audit](../../reverse/attempt_support/video-player-consolidation-20261029-bce2/README.md).

2026-11-04: the other donors include VideoPlayerClass.h, so the seed must adopt
it first. That adoption byte-matches 34/34 once row 0x00689180 is spelled
`?reset@VideoPlayer@@UAEXXZ`; next step is an agreed name for that row.
[Seed adoption trial](../../reverse/attempt_support/video-player-canonical-adoption-20261104-c3/README.md).

Follow-up (2026-11-04): after `VideoPlayer.cpp` changed, the current merge dry
run rejects all donors on `SubsystemInterface` redefinition, missing
`Rva00689180`, and an element-destructor pointer conversion. Reconcile these
views and rerun the provider/consumer audit before applying; [current trial
evidence](../../reverse/attempt_support/consolidation-queue-20261104-seat.md).

2026-11-04: vector destructor donor absorbed after compiler-context reconciliation; one fewer source, 37/37 rows and four EH graphs exact, bounded link guard/preview passed. Remaining next steps are flag overrides and base/element-view reconciliation; census confirmation remains pending. [Evidence and path audit](../../reverse/attempt_support/videoplayer-vector-consolidation-20261104.md).

2026-11-05: element pointer conversion reconciled, six donor rows/EH exact and link facts unchanged; composition now stops on the 0x00689740 `_Destroy` class/struct key identity. Reconcile its ledger/provider bindings before merging; other donor prerequisites remain. [Evidence](../../reverse/attempt_support/videoplayer-element-view-20261105-codex3.md).
