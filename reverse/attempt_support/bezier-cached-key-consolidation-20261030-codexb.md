# BezierProjectile cached-key consolidation, 2026-10-30

Base: `6bfd053837`; owner: `yasinschroeder-codexb`.
Destination: `Code/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior.cpp`.
Donor: the adjacent `BezierProjectileBehaviorPoolKey.cpp`.

## Evidence and prerequisite

The supported picker claimed the destination and nine remaining whole-file
donors. The Behavior naming planner's packet records competing private class
views and mixed sources; it does not approve a merge. `tu_skeleton.py` rebuilds
the stale TU map in memory and approves 47 rows for this destination. Its first
merge preview rejects every donor. In particular, the seed omits the cached-key
member that the donor defines at 0x0045BFD9.

Expose the donor's existing `virtual NameKeyType getModuleNameKey() const`
declaration and identical enum. Remove the seed's explicit vtable pointer:
the compiler supplies the vptr at the same offset. This partial class view is
never constructed here and no virtual slot is called. This establishes the
member's ABI, not the full retail vtable or layout. No donor source, new name,
pin, hatch, header or shared class declaration is added.

Validation: before/after paired builds pass all 12 rows (9 destination, 3
donor), and `eh_verify.py` passes two EXACT parent graphs. All 23 destination
external COMDAT fingerprints and sizes, external definition/dependency/weak
sets, and object reference roots/edges are identical before and after.
Frozen-file and class checks pass. The second supported merge preview accepts
the seed plus cached-key donor with 12 rows; eight whole-file donors still fail
on private views or missing methods. Five mixed sources remain untouched.

The fetched index is `12b9e7a7c0` (2026-10-30 10:11 UTC). It includes the seed
and all nine whole-file donors as linked; the old LINK-131 missing-destination
blocker has cleared. The cost donor from the October 28 handoff has already
been absorbed. Ordinary preview preserves LINKS for both current units:
594 + 79 = 673 authored bytes. This is not a census measurement.

The scoped batch audit is INCONCLUSIVE against `6bfd053837`: the index predates
the base and affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a
current receipt. Carry that consumer into the next normal census. No full
consumer clearance, linked-byte gain, debt retirement, runtime result or image
ownership gain is claimed.

Two strict receipt preparation attempts overlapped merge-preview scratch
files and correctly refused changed input snapshots. Retrying after the merge
preview finishes checks stable inputs; the failed attempts are not receipts.
The stable retry passes 12/12 rows and writes strict reusable receipts for both
explicit providers without changing census/index/status.

## Remaining work

Apply only the supported cached-key merge after committing the prerequisite;
repoint the donor's two owned static-local data records with the merge tool.
Reconcile the other eight donors separately before attempting further moves.
Do not split the five mixed files as part of this merge.
