# TBuff unsigned buffer consolidation (2026-11-04)

Base: `f43643c13732b5cab239f7356095152168ca6cab` (the independently
verified constructor-specialization prerequisite). Scope: absorb
`Code/Libraries/Source/WWVegas/WW3D2/ShareBufferClassUnsignedCtor.cpp` into
`Code/GameEngine/Source/Common/System/TBuff.cpp` through `tu_skeleton.py`.
One source removed; five rows moved; all 25 destination rows retained (903 B).
The approved destination is provisional: this does not establish retail's
original filename or strengthen the TU map's placement evidence.

The original trial refused duplicate generic constructor definitions. Unsigned
uses explicit raw allocation, whereas Vector2's generic constructor runs array
element construction. The prerequisite specializes unsigned and reconciles its
declaration to the existing destination view, preserving both implementations.
The inherited destructor remains virtual. Its five rows passed independently.

Verification after the supported merge:

- `./build.sh Code/GameEngine/Source/Common/System/TBuff.cpp`: 25/25 exact;
  all five renumbered funclets resolved through their parent EH graphs;
  four compiler float literals verified, no string/import findings.
- `find_declared_unmatched.py`: all definitions matched, before and after.
- `eh_verify.py`: four EXACT graphs, no missing objects or baseline findings.
- `check_csv.py`, `check_case_collisions.py`, and staged `tu_ownership.py
  --shadow`: passed. The map diff only repoints five source cells; no rebuilt
  assignments or evidence are committed.
- `data_check.py` and `data_check.py --converged`: zero findings; 11 converged
  addresses, no second names and no unjudged rows.
- The merge's census-linked guard accepted both inputs without a provider or
  selected-COMDAT loss. A separate `link_check.py` preview against the census
  at `8c757ea0db` (2026-11-04 17:56) reports LINKS for TBuff and the five
  inspected consumer units: W3DFloorBuffer, DX8RendererAddMesh, part_buf,
  meshmatdesc and OpaqueScalarDeletingDtorsB01. TBuff's 729 -> 903 B is the
  absorbed donor's 174 B, not an increase in census-linked coverage.

Path/queue/debt audit covers this single deletion and destination. Searches of
tools, hooks, workflows, Code includes, build/configuration inputs, registries
and documentation found no executable old-path consumer requiring an update.
Remaining old-path references are explanatory comments, the merge's provenance
comment, historical attempt receipts/log entries, and census-owned link status.
The destination is already in the doxygen source list. No alias is removed.
There are no donor data/identity/gate/header keys to retire or transfer.
The destination's two optimization hatches and three canonical-header queue
rows remain unchanged. The merge refreshed the Microsoft-header queue, adding
its unverified `free` finding rather than concealing it. Header adoption and
that Microsoft-header finding remain separate work; no debt retirement or
new census measurement is claimed. The outgoing push hook supplies the final
batch consumer audit.

Post-commit freshness check: the shadow identity gate initially reported four
duplicate definitions against cached TerrainLogicCtor, GapBodiesSeat2B and
VtableVirtualForwarders objects. Current sources already declare/reference those
names instead of defining them; all four TBuff bodies also predate this merge.
Rebuilding those three units through `./build.sh` passed 50/50 rows, and a fresh
scoped `code_identity_gate.check` for TBuff returned zero findings in shadow
mode. No source or baseline change was needed. The scoped naming picker could
not inventory the two explicit unsigned template-specialization functions;
their inspected `count`, `msg`, and `alignment` parameters retain their existing
names. This is not a claim of complete template-binding inventory coverage.
