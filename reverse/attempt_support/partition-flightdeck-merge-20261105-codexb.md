# PartitionManager FlightDeck consolidation, 2026-11-05

Prerequisite: `3a4a2ed32b`; see the [environment experiments](partition-flightdeck-environment-20261105-codexb.md).
Applied `tu_skeleton.py --merge Code/Libraries/Source/partitionmanager/PartitionManagerImpl.cpp`.
It rebuilds the stale TU map in memory and accepts the seed plus
FlightDeckInfoVectorInsertOverflow.cpp, preserving 34 rows and deleting one
source file. Only the four moved rows' source columns change in the committed
TU map; no regenerated approval map is included.

## Verification and compatibility audit

- Final `./build.sh`: 34/34 exact; string, float and import checks pass.
  `find_declared_unmatched.py`: all defined functions matched (two pre-existing
  unclaimed inline definitions reported as informational).
- `eh_verify.py`: EXACT 2, no missing objects or non-exact EH rows. Funclet
  labels are verified through their parent EH records.
- `check_csv.py` passes; the four moved addresses still each have one ledger
  row: 0x006200D0, 0x00626E90, 0x00627BC0 and 0x00627F50.
- Strict `link_check.py --prepare-current` verifies the merged provider and
  writes reusable receipts. Current preview LINKS at 3,719 bytes; compared
  with the seed plus donor's previous 3,278 + 441 bytes, coverage is preserved.
  The merge engine's paired link guard also accepts removal of the donor
  object and replacement with the composed object. This is preview evidence,
  using census index 2026-11-05 05:17 at c95fcfcfcd, not a new census or real link.
- Audited the complete pending source-path batch (origin/master through the
  prerequisite commits plus this staged merge). Its only path removal is
  Code/GameEngine/Source/GameLogic/Object/Behavior/FlightDeckInfoVectorInsertOverflow.cpp
  into Code/Libraries/Source/partitionmanager/PartitionManagerImpl.cpp.
  Combined basename/path search across tools, hooks, workflows, build.sh,
  Code, docs and reverse found no active tooling or include consumer to update.
  Surviving old-path mentions are the TU provenance comment, LINK-151's prior
  history, attempt evidence and the historical census link_status.csv row.
- The merge tool repoints functions.csv and the four TU-map source cells and
  transfers the donor's blank flag override to the destination (counts 8+4=12).
  Neither source has keys in code_identity_baseline.tsv, data_check_baseline.txt,
  header_queue.tsv or ms_header_queue.tsv. Its owned header-queue refresh leaves
  both queues unchanged. No debt is retired; hatch counts remain unchanged,
  including every existing link-wide alternatename binding.
- Selected FlightDeck reserve/allocate-and-copy providers remain declared
  external specializations; no new aliases or pins are introduced. Existing
  shadow identity findings remain outside this consolidation's scope.

## Remaining scope

The destructor donor still fails specialization placement and has an incompatible
manager view beneath the vfptr. BfmeResultSourceA still fails result declaration
order and incompatible declarations. GetObjectsInRange keeps its incompatible
`-O2 -G6` override. Seven mixed sources are not split or absorbed. These are
prerequisites for a later pass, not lost rows or completed recovery.
