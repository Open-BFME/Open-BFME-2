# Team canonical NameKeyGenerator adoption, 2026-11-04

Base: `fc30b41159`. Scope: `Code/GameEngine/Source/Common/RTS/Team.cpp`.

The seed included the short canonical SubsystemInterface before its private
NameKeyGenerator declaration. Include the canonical NameKeyGenerator header at
that earlier include site and remove the private declaration. The header enables
the full subsystem slots before SubsystemInterface is defined. No function,
member, global or ledger identity changes.

Verification:

- `./build.sh Code/GameEngine/Source/Common/RTS/Team.cpp`: 156/156 functions
  exact, one data row verified; string, float, import and funclet checks pass.
- `find_declared_unmatched.py` before and after: all defined functions matched;
  the existing one-unclaimed-definition note remains (157 ledger rows).
- `header_adopt_lane.py accept --class NameKeyGenerator` for the seed: PASS;
  retired its one row from `reverse/header_queue.tsv` through the owning lane.
- `link_check.py` for the seed: LINKS, 7,862 -> 7,862 bytes against census
  2026-11-03 20:03 (`8661f15284`). This is a local prediction, not a new census.

## Consolidation trial and remaining prerequisites

The required `name_lane.py consolidate --under Code/GameEngine/Source/Common/RTS/`
planner ran and its snapshot check passed before the trial. The current TU map
was rebuilt in memory; no regenerated map is committed.

Before this adoption, `tu_skeleton.py --merge .../Team.cpp --dry-run` accepted
the seed and TeamMemberKindCounts.cpp, Team_hasAnyUnits.cpp,
Team_hasAnyBuildings.cpp, TeamHasAnyObjects.cpp and Team_hasAnyBuildFacility.cpp:
160 rows preserved, with its census-linked provider/consumer guard passing.
Applying that plan wrote no files: the tool's wider merge scope needed four
shared addresses held by other workers (0x0007FAB3, 0x0014F3C4, 0x00417B55,
0x0049C38A). No source paths, hatch counts or protected-register keys moved.
The active-path audit found no hard-coded tooling consumers of those five
donors; three ThingTemplate header-queue rows would need carrying in a merge.

Retry the merge only when its required claims are available, with a fresh
planner snapshot and merge plan after this header change. NameKeyGenerator's
include-order obstacle in the seed is cleared. Other rejected donors still
need Object/Team/TeamPrototype view reconciliation, STLport specialization
composition, or the existing Coord3D class-key prerequisite. This change claims
no donor merge, source-file reduction or census improvement.
