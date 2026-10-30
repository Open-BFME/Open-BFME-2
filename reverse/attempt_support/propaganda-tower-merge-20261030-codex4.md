# PropagandaTowerBehavior scan merge

Prerequisite: `739c96a7e8` (local SHA before fleet publication),
`propaganda-tower-views-20261030-codex4.md`.

`tools/tu_skeleton.py --merge
Code/GameEngine/Source/GameLogic/Object/Behavior/PropagandaTowerBehavior.cpp`
absorbed only PropagandaTowerBehaviorDoScan.cpp. This removes one source file
and puts its seven code rows in their approved TU. All 23 scoped rows remain;
17 now live in the seed, with constructor, module-data constructor, Update and
Xfer still separate. Seven mixed sources remain outside this whole-file merge.

## Composition and checks

- The merge rebuilt current TU assignments in memory. Its only committed
  `tu_map.csv` changes are seven `source` repoints, retaining approval and
  evidence columns; no regenerated assignments are committed.
- Normal `./build.sh` verifies all 17 seed rows, its data row and literal.
  Strict preparation verifies 23/23 rows across the five surviving providers.
  `find_declared_unmatched.py` and `check_csv.py` pass.
- All four parent EH graphs are EXACT, including the scan's reassigned local
  labels. Funclet identity and retail parent binding are retained.
- The composed object contains exactly the union of the previous two objects'
  44 COMDAT names, digest/size pairs, strong definitions, undefined names, weak
  directives and relocation roots/edges. No code/data provider variant or
  external binding changed in the composition.
- All five bounded link previews report LINKS. The seed owns 957 bytes
  (previous seed 480 plus scan 477); scoped own-byte total remains 1,674.
  This is a source move, not a census linking increase.
- The complete outgoing staged-tree audit, from `origin/master` to the tree
  produced by `git write-tree`, remains INCONCLUSIVE on index `12b9e7a7c0`
  and missing current `Common/0CreateAHeroManager21FE49.cpp` consumer receipt.
  Include the composed seed and affected consumers in the next scheduled
  census. No wider consumer selection/loss clearance is claimed.

## Queue, debt and tooling compatibility audit

Audited the only pending source-path move, DoScan.cpp -> the approved seed,
after composition and before publication. The planner was regenerated after
the publication rebase/merge changed the source directory snapshot.

No moved source holds a gate, code-identity, data-check, header-queue or hatch
baseline key. The existing constructor hatches remain in their original files.
The seed retains the FieldParse data provider; no data-ledger owner changes.
The merge engine refreshed the header queue and rescanned the composed TU for
the Microsoft-header queue through their owning tools; neither queue changed.

Searched the old path and basename throughout active tools, hooks, workflows,
source/includes, configuration, registries and docs. Functions and TU-map
owners are repointed by the merge engine. No pin, body-owner, fold-proof,
doxygen or active tooling consumer requires a path update. Remaining old-path
mentions are the seed's provenance marker, an example comment in
AutoAbilityBehaviorUpdate.cpp, append-only attempt history and the historical
census link_status.csv. These are intentionally retained. No fallback path
or shared tooling edit is needed.

Remaining class-layout prerequisites and the reference freshness limitation
are retained in the prerequisite evidence. No nightly or game run was started.
