# AutoHeal PlayerScan header debt

Inspected revision: `70d173d45a`. Scope:
`Code/GameEngine/Source/GameLogic/Object/Behavior/AutoHealBehaviorPlayerScan.cpp`.

The unit already obtained canonical BehaviorModule and UpdateModule declarations
through AIUpdate.h. Replace its direct ObjectModule include with explicit
BehaviorModule.h and UpdateModule.h includes, making the base-class dependencies
visible to the owning header-acceptance check. No class layout or body changes.

Verification:

- `./build.sh <source>` before and after: 12/12 rows byte-match, including the
  update parent and its six EH-related rows. String, float and import checks pass.
- `find_declared_unmatched.py <source>`: all defined functions already matched.
- `header_adopt_lane.py accept --class CLASS <source>` passes separately for
  BehaviorModule, BehaviorModuleInterface, UpdateModule and UpdateModuleInterface.
  Each verdict retires exactly its own queue row and includes the tool's per-unit
  census-link preservation check. No queue rows were removed manually.
- A comparison using `link_census.comdat_bodies` finds the same 45 external
  COMDAT definitions before/after: no added, removed or changed body/relocation
  digest. External undefined-symbol sets are identical too.
- The source has no code-identity, data-check or hatch baseline keys to retire.
  The remaining PlayerScan header queue entries are ContainModuleInterface,
  GeometryInfo and ThingTemplate; they remain queued.

Consolidation was investigated first, using the supported planner and a fresh
`tu_skeleton.py --merge .../AutoHealBehavior.cpp --dry-run`. The planner's target
packet separates original-path leads from approved placement, flags compiler
settings and duplicate views, and does not approve moves. The merge rebuilt the
stale TU map in memory. Its 30 approved rows span the seed, six clean donors and
four mixed sources; no remaining donor was accepted. In particular:

- PoolKey introduces a second SubsystemInterface through its canonical
  NameKeyGenerator include; it also needs a matching seed method declaration.
- Xfer and Rva004523CC introduce canonical Module/ObjectModule declarations
  beside the seed's imported header chain.
- PlayerScan and pulseHealObject introduce a second GameLogic view; PlayerScan
  additionally conflicts on coordinate declarations.
- Ctor conflicts with compiler-owned DamageModuleInterface vftable storage.

The previously accepted Rva004523F5 constructor is already in the seed, from
`bb0c2735b9`. The old scope-contention prerequisite is therefore spent.
`tu_views.py` stops with `AutoHealBehaviorModuleData is defined inside a
preprocessor conditional`; no view rewrite was retained. Next work is coherent
seed/donor header and inheritance reconciliation, not another unchanged merge
retry. This commit removes four stale header debt rows; it claims no source-file
reduction, census gain or runtime result.
