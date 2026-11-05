# Team query consolidation, 2026-11-05

Base: `66cc14dc43`. Owner: `yasinschroeder-codexb`.
Result: five source files absorbed into the approved retail TU
`Code/GameEngine/Source/Common/RTS/Team.cpp`; six code rows repointed, no
matched rows lost. No new source-name or layout claim is made.

The evidence planner (`name_lane.py consolidate --under
Code/GameEngine/Source/Common/RTS/`) identified the Team group and its private
view prerequisites. `tu_skeleton.py --merge ... --dry-run` rebuilt the stale
TU map in memory and accepted the seed plus TeamMemberKindCounts,
Team_hasAnyUnits, Team_hasAnyBuildings, TeamHasAnyObjects and
Team_hasAnyBuildFacility. Their six code rows already have approved Team.cpp
assignments (Z/S evidence); only source columns change in the committed map.
The applying merge reused the saved verified composition. Source recovery
reduces the Code source-file count by five; this is not new matched coverage.

Verification:

- Seed before merge: 156/156 functions exact. Combined TU: 162/162 functions,
  one data row, four string literals and five floating literals verified.
  Parent EH data verifies the 42 funclet pins after compiler-label renumbering.
- `find_declared_unmatched.py`: all defined functions already matched, before
  and after the merge. `check_csv.py` passes with 99,481 function rows.
- Read-only COFF inventory before composition: 274 unique external definitions
  across the six objects (285 definition occurrences). After composition, all
  274 remain, with every occurrence's bytes and relocation tuples identical.
  This includes data and inline providers; no provider or alias is removed.
- The merge's link guard passes its 50 census-linked candidate units and
  composition/provider checks. Local index: `112a456a2c`, census timestamp
  2026-11-05 15:52. Before: all six objects preview-link, 8,471 bytes total.
  After: Team.cpp preview-links at 8,471 bytes. Its displayed 7,862 -> 8,471
  change is ownership aggregation, not a headline linking gain.
- Staged TU ownership passes. Data check: one source, zero findings. Code
  identity remains in shadow with four binding findings in the seed's
  hashtable/Rb-tree helpers; the identical external bytes and relocation
  fingerprints show these were preserved, not introduced or retired.

The batch path-consumer audit covers all five absorbed paths and basenames,
active tooling/hooks/workflows, Code includes, root build/configuration files,
source registries and documentation. No active hard-coded tooling consumer
requires a repair. Functions, TU-map source columns and naming-basis owners
are repointed by the merge tool. Header queue has no donor keys; the MS-header
queue refresh retains Team.cpp's unchanged debt. Data/identity/protected
registers and fold proofs have no references to deleted donors. The tool's
hatch update preserves totals and produces no baseline diff.

Intentional old-path mentions: reverse/link_status.csv is the historical
census; name_basis old/new fields, name_votes/name_agreed/name_bindings are
historical naming evidence (binding digests must not be re-keyed into fresh
proof); prior attempt receipts and the TeamRva0039E0D0 neighbour comment
remain historical context. The Team.cpp comment names the former donor as
provenance. The planner report becomes stale after applying the merge and is
not reused for further work.

The remaining 44 rejected Team donors still need private-view/header and
container reconciliation; ten mixed donors also remain outside this merge.
The broad obstacle remains open. This receipt claims no new census, real-link,
image-ownership or game-smoke result; the next scheduled census must confirm
current linked-unit coverage.
