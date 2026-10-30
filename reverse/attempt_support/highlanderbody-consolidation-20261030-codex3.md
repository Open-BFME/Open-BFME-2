# HighlanderBody composition prerequisite (2026-10-30)

Base: `6ac652269ad5dcb1adc7e0576d9561119a428262`.
Scope: `Code/GameEngine/Source/GameLogic/Object/Body/HighlanderBody.cpp`,
`HighlanderBodyPoolKey.cpp` and `HighlanderBodyAttemptDamage.cpp`.

The default picker first served ImmortalBody. Its current in-memory plan still
approves only 33 cleanup rows while their parent placements remain proposed;
the earlier false-approval entry in re_attempts.log still applies. No source
trial or merge was made there, and all 15 scope claims were released.

The supported Body naming planner catalogued the Highlander fragments and
their conflicting private views. The current in-memory TU map approves the
constructor, destructor, deleting destructor, name-key getter, damage method
and two getter EH rows for HighlanderBody.cpp. The six-byte name getter in
the mixed Common/ConstIntGetters2.cpp is also approved, but stays outside this
whole-file merge. ZH method definitions and the target name-key literal anchor
the main rows; no WorldBuilder path alone is treated as target placement.

The initial supported merge rejects both donors: the seed lacks
getModuleNameKey, and the damage donor has incompatible base/interface views.
tu_views reports those hierarchy and virtual-slot conflicts explicitly.

## Target facts and bounded repair

Native constructor 004C0781 and destructor 004C07B1 install primary table
00C5B440 and secondary tables 00C5AD78 at +0C and 00C5B390 at +10. Primary
slot 4 contains 008C07CA, the already rowed name-key method; slot 8 contains
008BDCAC, the already rowed ActiveBody::onDelete. The registered Module and
ObjectModule headers establish the common +4 ModuleData and +8 object fields.

Replace BehaviorModule's flattened eight-byte storage and artificial primary
anchor with the canonical ObjectModule base. Retain the seed's existing
secondary interfaces and ActiveBody relationship. Declare the existing
HighlanderBody::getModuleNameKey override and ActiveBody::onDelete. No provider,
pin, alias, recovered function body or class name is invented.

This is a partial view: Snapshot overrides, the rest of the primary table,
and both secondary-interface contracts still need recovery. The new primary
table is ten slots, not a claim that the whole native table is recovered.

## Prerequisite checks

- Before editing, strict preparation passes all seven rows across the three
  files, the pool-name literal and one floating literal. Ordinary preview
  retains three LINKS verdicts, 95 + 79 + 67 authored bytes, against index
  `6fe1089c24` (2026-10-30 04:25).
- The final seed builds 3/3 rows; all frozen-file checks pass. Strict preparation
  again passes 7/7 across the three files. Ordinary preview again retains all
  three LINKS verdicts and 241 authored bytes.
- Relocation-aware object facts preserve all six original COMDATs except the
  primary vtable, which grows from 8 to 40 bytes. Strong definitions, weak
  binding and both secondary tables are unchanged. Four inline canonical
  providers appear: Module::onObjectCreated, onDrawableBoundToObject,
  preloadAssets and ObjectModule::onCapture. Undefined names replace
  BehaviorModule::behaviorModuleAnchor with getModuleNameKey,
  ActiveBody::onDelete and __purecall. Constructor/destructor code and their
  relocations retain their fingerprints.
- The scoped Microsoft-header scan is clean. Neither source has code-identity,
  data-check, header-queue, Microsoft-header-queue or hatch debt to retire.
- A fresh supported merge dry run accepts the seed and pool-key donor for six
  rows and passes its census-linked input guard. The damage donor still fails
  C2504/C2039; its interface/base reconciliation remains separate work.
- The staged prerequisite audit exits 2, INCONCLUSIVE: the index predates this
  base and affected consumer Common/AIBuildable.cpp lacks a current strict
  receipt. Full affected-consumer selection/loss checks and census confirmation
  remain open. Carry the expanded primary table, canonical inline providers,
  existing onDelete provider and their consumers into the next scheduled census.

No source paths move in this prerequisite. No debt retirement, census gain or
image-ownership improvement is claimed. The whole-file merge must independently
verify the pool-key parent, cleanup graph, data ownership and provider bindings.

## Applied composition

After prerequisite `3410c04f98`, the supported naming planner was refreshed and
its currency check passed. `tu_skeleton.py --merge` accepts the seed and pool-key
donor, retaining all six rows in the approved HighlanderBody.cpp. The damage
donor still fails C2504/C2039, and the mixed ConstIntGetters2.cpp remains intact.
One source file is removed. The merger changes three source cells each in
functions.csv and tu_map.csv; the committed map is not regenerated. Two
data-ledger source cells move the getter's cached key and guard to their actual
provider, preserving names, addresses, sizes and ownership status.

The final normal build verifies 6/6 rows and the pool-name literal. The parent
EH graph is EXACT, including placement of the renumbered cleanup label. Frozen
file checks pass. Relocation-aware object facts show that all 12 external
COMDATs equal the input union, with identical strong definitions and weak/COMMON
bindings. No external dependency is added; the getter reference resolves inside
the destination. The composition does not change the prerequisite's expanded
primary table or canonical inline providers.

Both ordinary and converged data checks pass, as does staged TU ownership.
The supported merger refreshes the header and Microsoft-header queues through
their owning APIs, with no queue changes. A separate scoped Microsoft-header
scan is clean. Neither moved source owns debt-baseline or hatch keys; no debt
retirement is claimed. Active code/data owners and fold proofs resolve to the
surviving source.

The complete pending path batch, fetched against origin/master `8822408da0`,
contains two absorbed sources: AISpecialPowerRva004B327F.cpp into
AISpecialPowerUpdate.cpp (already handed to the fleet publisher), and
HighlanderBodyPoolKey.cpp into HighlanderBody.cpp. Combined old-path/basename
and directory-consumer searches cover tools, hooks, workflows, includes,
build/configuration inputs, registries and documentation. No active consumer
needs repair. Remaining old-path references are destination provenance, old
census/deleted-row records and historical attempt/comparison evidence. Keep
those references. No directory or derived-path convention changes.

Strict preparation passes 7/7 rows across the destination and damage residual,
one pool-name literal and one floating literal. Ordinary preview retains both
LINKS verdicts: destination 95 -> 174 authored bytes, damage 67 -> 67. The
apparent 79-byte destination increase is entirely the absorbed donor; the
three original inputs' total remains 241. This is not a census gain.

The scoped audit from prerequisite `3410c04f98` to staged composition tree
`beef5d67d3e38764a364af932c2d3e0e44a46892` exits 2, INCONCLUSIVE. The index
still predates the base, and Common/AIBuildable.cpp lacks a current strict
receipt. Full affected-consumer selection/loss checks and census confirmation
remain open. Carry both outgoing consolidations, the prerequisite's primary
table and canonical inline providers, the existing onDelete provider and
their consumers into the next scheduled census. No runtime or image-ownership
result is claimed.
