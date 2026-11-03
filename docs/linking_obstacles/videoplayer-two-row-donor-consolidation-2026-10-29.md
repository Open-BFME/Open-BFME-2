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
