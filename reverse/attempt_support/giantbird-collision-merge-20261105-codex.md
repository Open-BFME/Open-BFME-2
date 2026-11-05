# GiantBird collision TU merge

`tu_skeleton.py --merge .../GiantBirdAIUpdate.cpp --dry-run` accepted the
seed and `GiantBirdAIUpdateOnCollide.cpp` after the separately verified
[declaration repair](giantbird-collision-prep-20261105-codex.md). Application
reused that plan (`plan_reused: True`), checked the bytes and link guard again,
and moved RVA 0x003698CD into its currently approved retail TU. Source files
decrease by one; no new body or new linking coverage is claimed.

Verification:

- Applied TU: `./build.sh` 19/19 matched; all three unwind labels verified
  through parent EH data, one STLport constructor fold verified, 16 compiler
  float literals verified, no unverified string/import references.
- `find_declared_unmatched.py`: all definitions rowed.
- `check_csv.py`: functions 99,458; symbols 9,319; data rows 2,268; all valid.
- The guarded composition preserves the census-linked units and their affected
  consumers. Standalone `link_check.py` predicts LINKS for the merged object,
  2,487 bytes, against the 2026-11-05 05:17 census at c95fcfcfcd. Before the
  merge the seed and collision donor predicted 2,249 + 238 = 2,487 bytes;
  the apparent per-file increase is transferred ownership, not new linking.
- `git diff --cached --check`: clean.

## Register and tooling audit

Audited the complete pending range from origin/master 4c1c2f261c through
04bb2553e9 plus the staged merge. This contains one source-path removal:
`Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdAIUpdateOnCollide.cpp`
is absorbed into the adjacent `GiantBirdAIUpdate.cpp`.

- The merge tool repointed the single functions.csv row and the corresponding
  tu_map.csv source cell. The TU map assignments were rebuilt in memory for
  approval; no regenerated map is committed.
- Neither source owns code-identity or data-check baseline entries. The donor
  owns no header/ms-header queue entries or hatches. The seed's five remaining
  header entries, data-ledger owner and two counted address-global occurrences
  remain unchanged; nothing is retired by the merge. The hatch owner tool ran
  and produced no register diff.
- The existing canonical AI/base/state declarations survive composition.
  The byte checks cover the collision calls, compiler literals and existing
  COMDAT folds; the merge's link guard checks the combined provider and
  consumer bindings with the absorbed donor removed from the index.
- Searched the old basename across tools, hooks, workflows, Code, docs and
  reverse registers. No active tooling, include, build/configuration or source
  registry requires an update. Remaining mentions are the generated provenance
  comment, historical evidence/obstacle history and reverse/link_status.csv.
  rename.py explicitly leaves that census output for the next census to re-key.
- No aliases or pins were removed or added. No other source paths moved.

## Remaining donors

The fresh trial still rejects the factory, constructor and path-append donors
at AICommandType declaration order; DoLocomotor at the Thing/Object view;
the guard-machine donor at Object::isAbleToAttack; Xfer at the missing xfer
declaration; and waypoints at privateFollowWaypointPath. The Swoop donor is
mixed (six approved rows here plus rows assigned elsewhere), so it remains
untouched. Reconcile each prerequisite in its own verified commit before
trying another guarded merge.
