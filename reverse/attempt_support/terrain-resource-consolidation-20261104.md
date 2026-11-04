# TerrainResourceBehavior constructor consolidation, 2026-11-04

Base: `3d43977b70`, following the canonical UpdateModule reconciliation in
`terrain-resource-update-adoption-20261104.md`. The consolidation planner was
regenerated for `Code/GameEngine/Source/GameLogic/Object/Behavior/` after that
change. `tu_skeleton.py --merge` rebuilt approval inputs in memory, accepted the
main TU and `TerrainResourceBehaviorCtor.cpp`, and deleted the constructor donor.
No TU assignment or confidence was changed in the committed map.

The tool repointed two function rows (constructor 0x0048209B and its handler
0x0078BB80), the 52-byte table at 0x00849408, and their source columns in the TU
map. The merged TU retains all 18 matched code rows (1,323 bytes). Source files
decrease by one and two code rows move into their approved TU.

Verification and batch audit:

- `./build.sh` on the destination: 18/18 code rows and its data row pass;
  string (2), float (6), and import (2) checks pass.
- `find_declared_unmatched.py`: all defined functions matched.
- `eh_verify.py`: EXACT 4/4, no baseline entries or missing objects.
- `check_csv.py`: 99,434 functions, 9,338 symbols and 2,269 data rows pass;
  `git diff --cached --check` passes.
- The merge's link guard compared the combined object against the census
  providers, selected COMDATs, placement and outside consumers; no regression
  was reported. All three input units were census-linked.
- `link_check.py`: destination LINKS 1,323 bytes; unchanged module-data
  destructor LINKS 48 bytes. Combined 1,371 bytes is unchanged from the main TU
  plus both donors. Index: 2026-11-04 05:53 at `5a13f2cd61`. These checks predict
  compatibility; they do not record a new census or real-link result.
- No donor keys existed in gate, data, code-identity or hatch debt registers.
  The three header adoptions were retired by their owning tool in the preceding
  commit. The merge refreshed header and Microsoft-header queues; five existing
  destination header entries survive and no Microsoft-header entry changed.
- Audited the outgoing reconciliation commit and staged merge, the only source
  move in this batch. Searches for the old path/basename across tools, hooks,
  workflows, Code, configuration, docs and active reverse registers found no
  active consumer needing an update. Remaining mentions are the merge's source
  breadcrumb, attempt evidence/logs, the published census status snapshot and
  LINK-168's historical repair. Historical measurements and attempts stay intact.
  No alias or named table provider was removed. Core ledger repointing is the
  merge tool's output; no deleted-row coverage or debt retirement is needed.

The module-data destructor still fails combined byte verification and remains
separate. Its private ModuleData/base and member views need reconciliation
before another merge trial. Mixed `Rva00589079Derived.cpp` and
`ModuleDataBuildFieldParse.cpp`, and the generated unwind donor, remain outside
this merge. LINK-168's earlier table-binding repair is preserved; its cause and
next step are unchanged, so its entry is not edited.

Two initial merge applications stopped before editing on an unconfirmed claim
refresh. The next normal merge claimed the complete scope and succeeded; no
claim or verification bypass was used.
