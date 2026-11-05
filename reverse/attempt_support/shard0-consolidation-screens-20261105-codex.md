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
