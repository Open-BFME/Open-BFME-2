# AODCrushCollide consolidation prerequisite

Inspected revision: `7e66c0c0fb`, 2026-11-04. Scope:
`Code/GameEngine/Source/GameLogic/Object/Collide/AODCrushCollide.cpp`
and its claimed destructor donors.

The supported consolidation planner surveyed the Collide directory (47 sources,
8 investigation groups); its committed-map view was stale. The merge tool
rebuilt approval from current inputs. Its initial dry run accepted no donors:

- `AODCrushCollideDtor.cpp`: the merged object omitted
  `??_7AODCrushCollide@@6BCollideDtorB2@@@`, referenced by the census object.
- `FamilyDeletingDtors_muse-95ab.cpp`: byte verification failed. Its other
  deleting destructor belongs to DominateEnemySpecialPowerModuleData; no row
  or queue key has been removed from that file.

`tu_views.py` confirmed differing AODCrushCollide base clauses and differing
`novtable` spelling for AODCrushCollideModuleData. It applied no changes.

## Verified prerequisite repair

Replaced the destructor donor's four synthetic CollideDtor bases with the
existing shared UpdateModule hierarchy and the main TU's CrushCollide/interface
layout. CrushCollide remains novtable and has an empty inline destructor so
the derived destructor reaches the out-of-line UpdateModule destructor.
The constructor's existing layout supports the interface at +0x20 and the
fields at +0x24/+0x28/+0x2C; no external donor layout was substituted.

- `./build.sh .../AODCrushCollideDtor.cpp`: both rows exact, 32 + 28 bytes;
  source, string, float and import checks pass.
- `find_declared_unmatched.py .../AODCrushCollideDtor.cpp`: all bodies matched.
- `header_adopt_lane.py accept --class UpdateModule .../AODCrushCollideDtor.cpp`:
  PASS, retired its one queue row through the owning tool.
- `link_check.py .../AODCrushCollideDtor.cpp`: LINKS, 60 -> 60 bytes against
  census 2026-11-04 13:15 at `f6d845ecd4`; no census gain claimed.
- `check_csv.py` and `git diff --check`: pass.

Next: retry the guarded merge with current donor bindings. The family deleting
destructor's byte mismatch and mixed ownership remain separate prerequisites.
