# Partition STL helper consolidation, 2026-11-04

Scope: `Code/Libraries/Source/partitionmanager/PartitionManagerImpl.cpp`, after
prerequisite d344d123ad1d3f210da8eb3a1bf79f8bd1756939. The current TU map approves
this grouping; its destination spelling remains provisional, not a proven retail
source filename. `name_lane.py consolidate --under
Code/Libraries/Source/partitionmanager/` supplied the plan.

`tu_skeleton.py --merge` absorbed `StlSweepW5Rva00626EF0.cpp` (96 bytes) and
`StlSweepR3Rva00627B10.cpp` (28 bytes) from WWVegas/WWLib. Two source files are
removed; the destination holds 30 rows / 3,278 bytes. Only these two source
columns changed in functions.csv and tu_map.csv; no map regeneration was committed.
The prerequisite removed the copy helper's unused algorithm include and supplied
only the public push_heap wrapper, avoiding duplicate heap template definitions.
Both helper rows byte-matched independently before the merge.

## Verification and limits

- Before: ordinary link_check previews LINKS for destination (3,154 bytes),
  push_heap (28) and copy (96), total 3,278. After: destination LINKS, 3,278 bytes.
  Index: 2026-11-04 16:16 at 2f0cb97f52. This is preserved preview coverage, not
  new census linking or a real-link result.
- After: `./build.sh` destination passes 30/30 rows; two funclet labels renumbered
  but parent EH data verified their pinned addresses. Six compiler float literals
  and two imports verified. `find_declared_unmatched.py` passes.
- `link_check.py --prepare-current` destination passes all 30 rows with strict
  reusable receipts. It does not check LINK closure. The outgoing hook performs
  the full batch audit; no full-current-census claim is made here.
- Merge link guard identifies all seven candidate scopes as census-linked.
  `git diff --cached --check` passes.

## Debt and path audit

- Scoped searches found no identity/data debt keys or header queue rows for the
  two donors. The merge tool refreshed header/MS-header queue transfers without
  a queue diff. No debt key was retired.
- flag_overrides.csv transfers the absorbed copy helper's record to the existing
  destination record (rows/default_lost 7 to 8); destination flags remain unchanged.
  All aliases remain, hatch totals unchanged; no link-wide alias was removed.
- Post-merge search of tools/, .githooks/, .github/, Code/ and docs/ found no
  active tooling, include or workflow consumer of the removed paths. The active
  linking_targets.md row is repointed. Historical LINK-083 descriptions and
  generated provenance comments retain the old names. Old link_status.csv rows
  are dated census evidence and were not rewritten.
- Remaining candidates are unchanged: GetObjectsInRange needs reconciliation of
  its -O2 -G6 flag override; Common/PartitionManagerImpl has duplicate private
  basic_string declarations; BfmeResultSourceA has incompatible private result/
  manager views; FlightDeckInfoVectorInsertOverflow fails merged bytes. Seven
  mixed-source donors were left intact. These are consolidation prerequisites,
  not new linking regressions.

Local transcripts: build/partition-merge-apply.log,
build/partition-links-before.log, build/partition-strict-prepare.log,
build/partition-path-consumers.log. These scratch logs are not committed.
