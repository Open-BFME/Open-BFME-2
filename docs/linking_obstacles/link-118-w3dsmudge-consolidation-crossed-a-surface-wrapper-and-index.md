### LINK-118: W3DSmudge consolidation crossed a surface-wrapper and index-buffer view boundary

Status: ReAcquireResources subset merged and verified; copyRect remains open. Updated: 2026-10-27; prerequisite revision: c8ebfe4c97.

The current-map W3DSmudge.cpp merge rejected ReAcquireResources: its temporary
wrapper inherited the seed's engine SurfaceClass, and the seed selected the
Zero Hour unsigned-short index-buffer constructor. The wrapper now owns its
single pointer independently and the seed explicitly selects the existing
BFME indexbuffercount shim. Its established void unlock interface resolves
through the existing BfmeDX8ThreadLock alternate name. All 15 standalone rows
and three EH graphs verify; emitted definitions and undefined bindings are
unchanged after only that alias normalization. The supported dry run accepts
the pair. Current-object previews with BfmeDX8ThreadLock/Check give 5/5 LINKS
for those providers and all three Smudge units, confirming LINK-106's existing
repair rather than recording a census improvement.

Clearance: the supported merge removes ReAcquireResources's donor and retains
all 15 rows in W3DSmudge.cpp, with 554 external definitions unchanged from the
prerequisite-object union and no new undefined name. The two owned Smudge
sources pass bounded strict preparation (16/16 rows including copyRect). A
read-only current-object overlay that omits the retired census donor previews
4/4 LINKS with current thread providers; their ordinary receipts do not prove
full strict closure. A plain old-index preview retains the retired strong
definition and reports a stale duplicate. No census or headline gain follows.

Remaining: copyRect still fails
at IDirect3DSurface9 because the seed's D3D8 headers suppress the D3D9 SDK
interface; the previously recorded 0x0900 trial instead duplicates SDK enums.
Keep that donor and the four mixed files intact. Full evidence and follow-up:
[Smudge consolidation](../../reverse/attempt_support/smudge-reacquire-consolidation-20261027-codex5.md).
Census confirmation remains pending.
