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

## Composition after prerequisite 5910301b5f

The runner handed the prerequisite and earlier pending work to the fleet
publisher. Its rebase changed unrelated upstream inputs but neither scoped
source. `check_csv.py` passes after that rebase. The supported applying merge
rebuilds approval in memory and accepts only the seed and cached-key donor;
eight rejected whole-file donors and five mixed files remain unchanged.
It removes one source, repoints three function rows and three TU-map source
columns, and carries the two owned data records at 0x00A034C0/0x00A034C4.
No TU-map assignment, approval or generated map is committed.

- `./build.sh` and strict receipt preparation pass 12/12 rows, including
  five renumbered funclet labels placed by exact parent EH data. Both EH
  graphs are EXACT. Frozen-file and staged TU-ownership checks pass.
- COFF comparison against the two pre-merge objects retains all 25 external
  definitions with identical COMDAT fingerprints and sizes; the strong,
  undefined and weak bindings and reference roots/edges equal their union.
  The two static-local data records change only source ownership.
- Ordinary preview: the surviving unit LINKS for 673 authored bytes, combining
  the former 594-byte seed and 79-byte donor. No census gain is claimed.
- Data checks have zero findings, including zero second names and unjudged
  rows for converged data. CSV integrity passes (99,013 functions, 9,391 pins,
  2,246 data rows). The changed counts since the prerequisite are upstream
  changes brought in by the runner, not progress from this merge.
- The merge tool refreshes header and Microsoft-header queues; neither changes.
  Neither scoped source has a data/identity debt or flag-override key. The
  seed's three existing address-global hatches remain unchanged. Its global
  hatch refresh also removed an unrelated stale marker entry for
  `Common/RTS/Rva0073DFD0Finish.cpp`; that out-of-scope register-only deletion
  is restored to HEAD and excluded. No hatch or debt gain is claimed.
- The Behavior evidence planner is regenerated after composition and its
  currency check passes. Its surveyed source count falls 493 -> 492. Private
  views and placement hints remain investigation leads, not new TU approvals.

### Pending path-consumer audit

Audited origin/master `be3a127ff1` through prerequisite `5910301b5f` plus this
staged merge, including the already handed-over INIMultiplayerSettings.cpp
absorption and StlSweepR3Rva001FDEBC.cpp deletion. Combined basename/full-path
searches cover tools, hooks, workflows, source/header includes, root build and
configuration files, active ledgers/registers/queues and documentation.
No active consumer requires a path change. Remaining mentions are generated
source provenance, historical census status, tombstone prose and prior evidence.
Active ownership columns, data owners and fold proofs contain none of the
removed paths. Both absorptions stay in their seed directories, so relative
includes keep resolving. No `.cpp` include consumes a removed source; source
discovery retains its existing directory traversal.

The protected-register trailer records the two data-owner transfers. It does
not retire debt. Full selected-consumer closure still requires the next normal
census, especially `Common/0CreateAHeroManager21FE49.cpp`.

The final scoped `link_batch_audit.py` also returns INCONCLUSIVE against
pre-merge HEAD: index `12b9e7a7c0` predates that base and the same affected
consumer lacks a current receipt. This is not full outgoing consumer clearance.
