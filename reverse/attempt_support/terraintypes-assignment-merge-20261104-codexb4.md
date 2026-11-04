# TerrainTypes assignment consolidation, 2026-11-04

Prerequisite commit: `a13bf42fda` (the publisher rebased the initially reported
`0c85a26d86`). The Common planner was regenerated after the repair, and
`name_lane.py consolidate --check build/consolidation` passed before applying
the supported merge. Current TU approval was rebuilt in memory; only the moved
row's source column changes in the committed TU map.

`tu_skeleton.py --merge Code/GameEngine/Source/Common/TerrainTypes.cpp`
absorbs `WWLib/stlport_vector_nocasepair_assign.cpp`, removing one source file.
The assignment at `0x00317EBB` moves into its approved retail TU. All 31 matched
rows remain. The merger still rejects `Common/TerrainType.cpp` because its
private `_Vector_base` destructor redefines the seed's specialization (C2995).
The three mixed donors remain intact, and LINK-095 remains open.

## Verification and ownership

- `./build.sh TerrainTypes.cpp`: 31/31 rows, three literals and one empty-string
  reference pass. Renumbered funclet labels resolve through parent EH data.
- Declared-unmatched validation and staged whitespace checks pass.
- The merger's census-linked guard preserves the seed, assignment and rejected
  destructor unit's existing provider/consumer bindings. The final-path local
  preview predicts LINKS, 1051 -> 1231 authored bytes, against census
  `40fe1783d7` (2026-11-04 12:23). The 180 bytes are transferred ownership,
  not a measured linking gain.
- The supported merge refreshes header and Microsoft-header queues; neither
  queue changes for this donor. No protected identity/data key names the removed
  donor, before or after composition. No debt is retired. The hatch update
  keeps the existing allocator alias and changes no registered count.
- The prerequisite commit's hook reports shadow code-identity findings for
  TerrainTypes: the existing AsciiString clear binding and divergent ScienceType
  allocator/push_back definitions. These remain follow-up work; byte equality
  and a local link preview do not clear identity findings.

## Complete pending path audit

The pending batch through prerequisite `a13bf42fda` plus this staged merge has
one source-path removal: the assignment donor above. A repository search for
its full path and basename finds no active tool, hook, workflow, include,
build/configuration or source-registry consumer. Remaining references are the
historical attempt notes/log, the TU's origin comment, this evidence and
`reverse/link_status.csv` (a census snapshot, not hand-rewritten).

`functions.csv` and `tu_map.csv` now resolve the assignment to TerrainTypes;
targeted searches of code/data debt, header queues, hatch/flag registers,
data ledger and body owners leave no removed-path key. Relative includes and
existing shim flags compile at the final path. No directory is removed. The
ordinary outgoing hook retains responsibility for its batch-wide link audit;
the next scheduled census must carry any inconclusive consumers forward.
