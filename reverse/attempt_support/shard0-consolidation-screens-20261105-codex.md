# Shard 0/5 consolidation screens (2026-11-05)

These were allocated TUs checked with `consolidation_queue.py --check-tu`, a
fresh `name_lane.py consolidate` snapshot under each target parent, and the
current snapshot check. Each guarded `tu_skeleton.py --merge ... --dry-run`
reported `accepted: []`; none was applied and no claims were acquired.

## `Code/GameEngine/Source/Common/PickupStuffUpdate.cpp`

The plan has 23 approved rows, three donor files, and three mixed files. Dry run
exited 2: `FamilyDeletingDtors_muse-p7z-f52d.cpp` fails because the
`PickupStuffUpdateModuleData(EmitVtableTag *)` overload is undeclared;
`PickupStuffUpdateModuleDataCtor.cpp` fails with C2600 because its constructor
is a compiler-generated special member not declared by the class. The tool
requests reconciliation of `PickupStuffUpdateModuleData` views. LinkGuard lists
the seed and both donor objects as census-linked.

## `Code/GameEngine/Source/GameLogic/Object/SpecialPower/PlayerHealSpecialPower.cpp`

The plan has 18 approved rows, two donor files, and three mixed files. Dry run
exited 2: `PlayerHealSpecialPowerCtor.cpp` fails C2511 because the constructor
signature `(Thing *, const ModuleData *)` is absent from the destination class
view. The tool requests reconciliation of `PlayerHealSpecialPower` and
`SpecialPowerModule`. LinkGuard lists the seed and constructor donor as
census-linked.

## `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMainMenu.cpp`

The plan has 134 approved rows, five donor files, and four mixed files. Dry run
exited 2 with no merge: the seed itself fails byte verification under every
merged flag set. `AptMainMenuCallbacks_ExitGame.cpp` also has missing type/member
declarations (`TheDisplay`), and `AptMainMenuFirewallPrompts.cpp` lacks the
`Rva0057BC63FunctorHolder` declaration. The tool requests class-view work across
Apt menu, callback, audio, window, and functor types. LinkGuard lists the seed,
both callback donors, firewall prompts, and the functor-holder object as
census-linked. The seed byte mismatch must be resolved before a merge can be
considered.

## `Code/GameEngine/Source/GameLogic/Object/Update/HeroModeSpecialAbilityUpdate.cpp`

The plan has 16 approved rows, two donor files, and three mixed files. Dry run
exited 2 because `HeroModeSpecialAbilityUpdateModuleDataDtor.cpp` fails byte
verification. The seed's first adoption list includes `AICommandInterface` and
`SpecialAbilityUpdate`; LinkGuard lists the seed and dtor donor as census-linked.

No source, ledger, map, or claim changes were made. These screens establish no
accepted mechanical merge. Header/class-view repairs and any source byte repair
belong to other contributors; this seat should continue with another allocated
TU instead of retrying these unchanged trials.


All 20 entries from `python3 /opt/runner/consolidation_queue.py --limit 20`
passed `--check-tu`, were planned after a parent-scoped
`name_lane.py consolidate` run and passing `--check build/consolidation`, and
were run through `tu_skeleton.py --merge TU --dry-run`. Every dry run accepted
zero donors. No merge was applied, no claims were acquired, and no source or
ledger rows changed. LinkGuard reported census-linked composition for the
listed TUs and their donors; do not bypass its results.

Manual repairs and evidence needed before retry:

- `GameLogic/Object/Update/DelayedDeathBody.cpp`: `DelayedDeathBodyApply.cpp`
  rejects with C2511 for the constructor; `DelayedDeathBodyXfer.cpp` reports
  `xfer` absent. Tool suggests `tu_views.py` for `DelayedDeathBody` and
  `RespawnBody`.
- `GameLogic/Object/Update/SlavedUpdate.cpp`: ctor uses undeclared
  `m_secondary20`/`m_24`; another donor references absent
  `Object::m_modelConditionWords`; Xfer and Coord3D declarations conflict.
  Tool suggests `tu_views.py` for `SlavedUpdate`.
- `GameLogic/Object/Upgrade/DelayedUpgrade.cpp`:
  `upgradeImplementation` absent from `DelayedUpgrade`; tool suggests its view
  and `UpgradeModule` reconciliation.
- `GameLogic/Object/Create/EvaAnnounceClientCreate.cpp`: ctor overload and
  `rva004C9A51` are undeclared; xfer is absent from the view. Tool suggests
  `tu_views.py` for `EvaAnnounceClientCreate`.
- `Common/System/MemoryReadFile.cpp`: LinkGuard rejects
  `File_createMemoryReadFile.cpp`; merged object loses unresolved
  `convertToRAMFile`, `nextLine`, and `open` providers.
- `Libraries/Source/Fesl/gamebrowser/gamebrowserpinger.cpp`: `initPool` and
  `clear` are absent from `Rva00803080`; another donor has a conflicting
  `Gen008030A0` vftable. Tool suggests class-view reconciliation for
  `Rva007EAServiceHub`, `Rva007EAServiceList`, `Rva00803080`, and
  `Rva00803080Request`.
- `GameLogic/Object/Create/GrantUpgradeCreate.cpp`: onCreate/onBuildComplete
  include duplicate `Module`/`ObjectModule`; module-data ctor has duplicate
  `StringBase`; module-data dtor fails bytes. Tool suggests
  `GrantUpgradeCreate`/`Object` view work.
- `Libraries/Source/WWVegas/WW3D2/matpass.cpp`: destructor and install donors
  lose two rows under carried flags; two donors have no baseline match; ctor
  has `RefCountClass` redefinition. No accepted donor.
- `GameLogic/Object/SpecialPower/DevastateSpecialPower.cpp`:
  `doSpecialPower` and `doSpecialPowerAtLocation` are undeclared, module-data
  dtor fails bytes. Tool suggests `tu_views.py` for `DevastateSpecialPower`.
- `GameLogic/Object/Body/OathbreakerBody.cpp`: `attemptDamage` is undeclared;
  tool suggests reconciling `OathbreakerBody`.
- `GameLogic/Object/Update/ToggleDeploySpecialAbilityUpdate.cpp`: ctor and
  slot methods are undeclared; tool suggests view reconciliation for the
  update and related argument/data classes.
- `Libraries/Source/Fesl/ariesudp.cpp`: `Rva00661650AriesUdp.cpp` fails bytes.
- `GameLogic/Object/Update/StrafeAreaUpdate.cpp`: method declarations and
  special members are missing; `Thing` is undefined in the update donor. Tool
  suggests views for `Object`, `StrafeAreaUpdate`, module data, and direction.
- `GameEngineDevice/.../GameClient/W3DGameClient.cpp`: duplicate STL templates,
  duplicate `createSnowManager`, missing `Rva004C743` methods, and duplicate
  Coord3D/Thing declarations. Tool suggests W3D client and related view work.
- `GameLogic/Object/Behavior/BridgeTowerBehavior.cpp`: Xfer/Version conflict
  and `GameLogic` redefinitions in both damage donors. Tool suggests views for
  `BridgeBehaviorInterface`, `BridgeTowerBehavior`, and its interface.
- `GameLogic/Object/Behavior/ModelConditionAudioLoopClientBehavior.cpp`: ctor
  overload and slot methods are undeclared; tool suggests view work for the
  behavior and `Rva004CBF9A`.
- `GameEngineDevice/.../Drawable/Draw/W3DQuadrupedDraw.cpp`: ctor overload is
  undeclared; Coord3D vector allocator/specialization conflicts reject the
  other donors. Tool suggests class views for the draw class and module data.
- `GameLogic/Object/Die/CallHelpOnDamage.cpp`: ctor and xfer are absent from
  the class view; two module-data/destructor donors fail bytes. Tool suggests
  views for `CallHelpOnDamage`, its module data, and `Rva003623E5Filter`.
- `Common/MessageStream.cpp`: duplicate GameMessage/SubsystemInterface and
  Coord3D declarations, translator pointer type mismatch, and one bytes
  failure. Tool suggests GameMessage/MessageStream/CommandList class views.
- `GameLogic/Object/Behavior/SiegeDockingBehavior.cpp`: STL allocator
  specialization conflicts, Coord3D versus `Rva004598F2Point` mismatch,
  missing behavior method, and destructor bytes failure. Tool suggests views
  for Object, SiegeDockingBehavior, and its related records.

The remaining first-batch task is to screen mixed-source split plans for
eligible destinations; if the first 20 are exhausted, inspect the full shard
with `consolidation_queue.py --limit 100000` before declaring no work. Do not
repeat any unchanged dry run above until its prerequisite changes.
