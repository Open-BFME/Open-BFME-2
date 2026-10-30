# DelayedWeaponSetUpgradeUpdate composition prerequisite (2026-10-30)

Base: `d41945e85ec30033bcfa16059a985fad478ca744`.
Scope: `Code/GameEngine/Source/GameLogic/Object/Update/DelayedWeaponSetUpgradeUpdate.cpp`
and its `DelayedWeaponSetUpgradeUpdatePoolKey.cpp` donor.

The default picker claimed both files for consolidation. The supported naming
planner (`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/`)
reported private-view, pragma-context and path-keyed-register prerequisites.
Those packets provide investigation evidence only. `tu_skeleton.py --plan`
rebuilt the stale TU map in memory and approved eight rows for the destination:
four existing rows, the pool-key method and its two compiler EH rows, and the
six-byte name getter still in the mixed `Common/ModuleNameGetters3.cpp`.
That mixed source has 116 other rows and remains outside this whole-file merge.
No regenerated TU map is committed.

The first supported merge dry run rejected the pool-key donor: the seed class
lacked `getModuleNameKey`. `tu_views.py --dry-run` separately exposed the donor's
baseless class versus the seed's UpdateModule/interface bases. The seed's
private Module flattened both canonical Module's +4 ModuleData and ObjectModule's
+8 Object pointer into two storage words. Adopt the registered Module and
ObjectModule headers, derive BehaviorModule from ObjectModule, and declare the
existing pool-key method as the slot-4 override. The headers' retail base-chain
and slot evidence is documented in the shared obstacle register. This does not
establish canonical BehaviorModule or UpdateModule interfaces; their existing
placeholder slots and aliases remain. No name is newly inferred from a donor.

## Prerequisite verification

- Before editing, `find_declared_unmatched.py` passes both files, and the ordinary
  build passes all seven rows and the pool-name string. The baseline preview
  retains LINKS for 133 seed bytes and 78 donor bytes against the 2026-10-29
  15:08 index at `85f6b7f40c`.
- The changed seed passes all four rows, totaling 133 bytes. The owning
  `header_adopt_lane.py accept --class Module` passes its byte and per-unit
  link guards and retires exactly one row from `reverse/header_queue.tsv`.
  An initial acceptance refused the transitive Module include; the source now
  includes both registered headers directly.
- Both providers pass `link_check.py --prepare-current`: seven rows, the string
  reference, and strict reusable compiler receipts. Frozen-file checks pass.
- Before/after `link_census.object_facts` comparison preserves all three strong
  definitions and the weak alias. Ten COMDATs become fifteen: the old four-byte
  Module primary table becomes the canonical forty-byte ObjectModule primary
  table, and five inline providers appear (Module onObjectCreated,
  onDrawableBoundToObject, preloadAssets, onDelete; ObjectModule onCapture).
  The constructor/destructor relocation-aware fingerprints change with the
  primary-table symbol; ordinary byte verification still passes. Undefined names
  gain the separately rowed getModuleNameKey and __purecall. No unchanged-facts
  or complete consumer-closure claim is made.

- The post-edit ordinary preview retains both LINKS verdicts and 211 authored
  bytes (133 + 78). The staged-tree batch audit exits 2, INCONCLUSIVE: its index
  predates the outgoing base and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. The new providers and their affected consumers need confirmation in
  the next scheduled census; this is not a complete consumer verdict.

This prerequisite retires one header-debt entry. No source path changes and no
census linking or image-ownership gain is claimed. The subsequent supported
merge must independently preserve all seven rows and the local-static EH graph.
