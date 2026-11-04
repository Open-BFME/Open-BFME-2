# PartitionManagerImpl string-header prerequisite, 2026-11-04

Inspected revision: `11dd6c6970`. Scope: the selected WorldBuilder path lead
`Code/Libraries/Source/partitionmanager/partitionmanager_impl.cpp` and its
approved provisional TU `Code/Libraries/Source/partitionmanager/PartitionManagerImpl.cpp`.

## Evidence and limits

- Target: the selected row at 0x00626AA0 already has its real method name and
  a matched 72-byte body. The current-map dry run approves 67 rows for the
  provisional PartitionManagerImpl TU. This is existing coverage, not a lost row.
- Donor: `wb_show.py 0x00626AA0 --gd` pairs WB 0x0167FEC0 with the retail
  recursion. The editor body pushes the original partitionmanager_impl.cpp
  path and line 180. The ten path-paired game bodies already have approved
  grouping; the TU path remains provisional. No independent game F anchor
  for this spelling was found by the planner or path triage.
- Inference: the editor filename remains a useful lead. It does not satisfy
  tu_map's W route on its own: W only corroborates a matching independent
  naming hint and excludes names derived from the same lead. No map was
  regenerated or path asserted, and this filename-evidence task remains blocked.

## Verified prerequisite cleanup

`Code/GameEngine/Source/Common/PartitionManagerImpl.cpp` replaces its private
_STL::basic_string/allocator/char_traits declaration with STLport `<string>`.
The source opts into the existing static-library and bfmealloc configurations,
also used by the destination TU. The stock allocator configuration byte-matched
but introduced a conflicting __node_alloc::deallocate COMDAT; the existing
bfmealloc shim restores link compatibility. No shared header was edited.

The destructor's previous comment inferred string elements solely from the
ICF-equivalent destructor at 0x00142D70. That does not establish element type;
the comment now distinguishes the existing callee from the tree-vector storage
seen in the recovered operations. Established names and callee identities stay.

Verification of the final source:

- `./build.sh Code/GameEngine/Source/Common/PartitionManagerImpl.cpp`: all
  3/3 rows exact (84-byte destructor, 22-byte unwind funclet, 10-byte handler).
  The funclet label renumbered; parent EH data verifies retail placement.
- `find_declared_unmatched.py`: all defined functions already matched.
- `link_check.py` current-object preview: LINKS, 84 -> 84 authored bytes,
  index 2026-11-04 17:56 at 8c757ea0db. The follow-up declares the existing
  basic_string destructor specialization without defining it, avoiding extra
  allocator implementations and their diagnostic. This is preserved preview
  coverage, not a census result or a real-link/boot measurement.

## Remaining consolidation prerequisites

The original merge dry run rejected the destructor donor on duplicate private
basic_string templates (C2953/C2955). With the header cleanup, that collision
is gone; the next error is C2600: the seed class lacks a destructor declaration.
`tu_views.py --dry-run` separately refuses to reconcile the class: the seed's
m_buckets at +0 overlaps the destructor donor's vfptr. Next: inspect the retail
constructor/vftable and member accesses, establish the actual manager ABI, and
reconcile the views without moving any accessed field or changing row identities.
Do not merely add a virtual member and shift the seed's fields.

Other donors remain unchanged: GetObjectsInRange has an incompatible -O2 -G6
override; BfmeResultSourceA has incompatible result/manager declarations;
FlightDeckInfoVectorInsertOverflow fails merged bytes. The lowercase source
also holds mixed rows. No donor was absorbed. Its 13/13 rows were verified
before the trials.

Local transcripts: build/partition-tu-views-codexb.log and
build/partition-string-merge-check-codexb.log. No source paths, ledger owners,
protected debt keys, aliases, pins or hatch counts changed. No debt is retired.

## Shadow identity comparison

The commit hook reports two shadow binding findings for the parent/funclet's
Gen_uw_009f5690 destructor adapter at 0x00142D70. Restoring the original source
from 11dd6c6970, rebuilding it, and running the scoped staged identity gate
reproduces exactly the same two findings. Restoring the header-based source
with the declaration-only specialization keeps the same findings: these are
pre-existing adapter-identity debt, not findings introduced by the header
cleanup. No baseline entry was added or retired. The specialization keeps the
header adoption from emitting another copy of the already-rowed string destructor.
