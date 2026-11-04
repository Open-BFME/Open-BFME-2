# hcanim consolidation, 2026-11-04

Scope: `Code/Libraries/Source/WWVegas/WW3D2/hcanim.cpp` and its sampler donor.
Prerequisites published through the runner: "Adopt canonical BFME2MotionChannel
in hcanim" adopts the canonical header and retires one header-queue row through
`header_adopt_lane.py accept`; "Specialize the four-component adaptive-delta
sampler" makes the sampler definitions explicit specializations without changing
their symbols or bytes. Commit subjects identify these prerequisites across
the runner publisher's rebases.

The supported `tu_skeleton.py --merge` absorbs `hcanimGetFrame4.cpp`, repointing
its two rows (0x0018F9C0, 222 B; 0x0018FCC0, 194 B) and their TU-map source
columns. Source files decrease by one. Current in-memory TU-map approval is
by C brackets 0x0018F8C0..0x0018FB10 and 0x0018FB70..0x0018FE30 respectively.
The committed map was not regenerated. The naming planner's WorldBuilder
original-path evidence establishes that hcanim.cpp existed in that build;
approval comes from the TU map, not from the path string alone.

Verification after composition:

- `./build.sh .../hcanim.cpp`: 57/57 matched rows; three string literals,
  15 float literals and two named imports verified. Four renumbered funclet
  labels verified through their parent EH graphs; `eh_verify.py`: EXACT 6/6.
- `find_declared_unmatched.py`: all defined functions already matched.
  Microsoft-header check clean. Shadow data check: zero findings; converged
  data check: 11 addresses, zero second names or unjudged rows.
- `link_check.py` against census index `a62ac1c10b` (2026-11-04 07:28):
  hcanim LINKS, own bytes 8,046 before / 8,461 after; the absorbed donor
  previously provided 415 own bytes. The unchanged memory donor remains
  LINKS with 166 own bytes. These are previews, not new census measurements.
- `check_csv.py` and working/index diff whitespace checks pass. The merge
  tool's link guard accepted the composition. No alias pragma was removed.

Path-consumer audit covers this session's three-commit batch: only the sampler
path is removed. Combined basename/path searches across tools, hooks, workflows,
Code, shim headers, docs and reverse registers found no active consumer of that
path after the two ledger repoints. The surviving source provenance comment is
intentional history. The absorbed donor owns no data/identity/header/MS-header
debt; `tu_skeleton` refreshed the two header queues without further changes.
The destination's existing pragma-optimize hatch keys remain unchanged. The
tool also globally deleted eight unrelated stale W3DVideoBuffer hatch keys;
that entire unrelated baseline diff was restored, so no hatch retirement is
claimed or included.

Remaining: the supported merge rejects `HCompressedAnimMemory.cpp` because
`reference/shims/bfmehcanim/hcanim.h` does not declare its existing virtual
`HCompressedAnimClass::rva0018FB70`. Reconcile that method with the owning
HAnim/HCompressed views and reverify affected virtual calls before retrying.
The exact memory donor and both mixed files (`VslotSmallBodiesX.cpp` and
`HCompressedAnimTransform.cpp`) are unchanged. This does not resolve LINK-023's
shared HAnim vtable-layout disagreement.
