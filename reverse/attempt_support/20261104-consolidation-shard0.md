# Consolidation shard 0/5 handoff — 2026-11-04

Mechanical TU trials found no verified merge in this session. The allocator
listed 86 destinations in shard 0/5; all were unheld. The first 20 were
examined, then the full listing was inspected and additional destinations were
selected across Code/. No trial was applied, so net source files removed: 0;
TUs merged: 0; matched rows moved: 0. No source or ledger changes were made.

## Dry-run targets

The 29 merge dry runs accepted no donors:

- `Code/GameEngine/Source/GameLogic/Object/Update/DelayedDeathBody.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Upgrade/DelayedUpgrade.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Create/GrantUpgradeCreate.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Create/EvaAnnounceClientCreate.cpp`
- `Code/GameEngine/Source/Common/System/MemoryReadFile.cpp`
- `Code/Libraries/Source/Fesl/gamebrowser/gamebrowserpinger.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehavior.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DGameClient.cpp`
- `Code/Libraries/Source/WWVegas/WW3D2/matpass.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLightDraw.cpp`
- `Code/GameEngine/Source/GameLogic/Object/SpecialPower/DevastateSpecialPower.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Behavior/ModelConditionAudioLoopClientBehavior.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Body/OathbreakerBody.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/ToggleDeploySpecialAbilityUpdate.cpp`
- `Code/Libraries/Source/Fesl/ariesudp.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Behavior/SiegeDockingBehavior.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DQuadrupedDraw.cpp`
- `Code/GameEngine/Source/Common/XferMD5CRC.cpp`
- `Code/GameEngine/Source/Common/MessageStream.cpp`
- `Code/GameEngine/Source/Common/LivingWorldBuildingNuggetSpawnArmy.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Create/SpecialPowerCreate.cpp`
- `Code/GameEngine/Source/GameLogic/AI/GroupOrder.cpp`
- `Code/GameEngine/Source/GameClient/Snow.cpp`
- `Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp`
- `Code/Libraries/Source/WWVegas/WWMath/wwmath.cpp`
- `Code/GameEngine/Source/GameClient/System/Image.cpp`
- `Code/GameEngine/Source/GameNetwork/Connection.cpp`
- `Code/GameEngine/Source/Common/BfmeOwnVVD.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DAptComponentColorPicker.cpp`

Most rejections require manual work outside this seat: missing class members or
constructors, duplicate private class/header views, STL or coordinate type
conflicts, donor byte mismatches, or changed flag regions. The link guard also
rejected merges that would remove existing census link providers. In
particular, ProcessAnimateWindow.cpp's seed would lose the linked
`AnimateWindow::getVel` provider; Image.cpp donors would break census links;
ConnectionRva0058BD4F.cpp changes a flag region covering 17 rows; and
WWMath's donor failed byte verification. Do not retry these donors unchanged.

Mixed-plan probe: splitting
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DGameClientFactories.cpp`
for `W3DGameClient.cpp` carved three matching rows in the tool's trial, but the
tool rejected the split because of a `GameClient` class redefinition. No split
was applied. Remaining action for other contributors is the relevant header,
class-view, compiler-flag, byte-recovery or link-provider repair; this seat
must then take a fresh allocator and planner report before retrying.

The scoped consolidation planner and its currency check passed for each
additional selected TU. No claims remain from these trials. Existing five
commits already ahead of origin/master were preserved.

## Follow-up session

`Code/GameEngine/Source/GameLogic/AI/AITNGuard.cpp` had a fresh, allocated
trial. The dry run accepted the seed plus three unchanged donor files and 12
rows, but applying it is blocked: the destination `file:` claim was held by
another worker (`claims.py claim file:Code/GameEngine/Source/GameLogic/AI/AITNGuard.cpp`
reported `not claimed: file:8b01a57c95fad0da (held by someone else)`). This seat
released its 47 body and file claims. Do not apply until the destination can be
claimed and the trial inputs are still current. The other four donor files
were rejected for missing `AITNGuardMachine`/`TheAI` declarations.

Four more allocated dry runs accepted no donors:

- `Code/GameEngine/Source/GameLogic/Object/Create/InheritUpgradeCreate.cpp`:
  constructor, `xfer`, `onBuildComplete` and module-data constructors are not
  declared in the seed views; the tool calls for class-view reconciliation.
- `Code/GameEngine/Source/GameLogic/Object/Die/CallHelpOnDamage.cpp`: missing
  constructor and virtual/member declarations, plus two donor byte mismatches;
  class-view reconciliation is required.
- `Code/GameEngine/Source/GameLogic/Object/Behavior/ShipSlowDeathBehavior.cpp`:
  its constructor donor is missing the destination constructor declaration.
- `Code/GameEngine/Source/GameLogic/Object/Upgrade/ModelConditionUpgrade.cpp`:
  its constructor donor is missing the destination constructor declaration.

All four were dry runs only; no source or ledger changes. The next allocated
candidate checked for continuation is
`Code/GameEngine/Source/GameLogic/Object/Upgrade/SpellRechargeModifierUpgrade.cpp`
(allocation check exit 0). Refresh allocator and scoped planner evidence before
working it.

## Follow-up session, continued

`Code/GameEngine/Source/GameLogic/Object/Upgrade/SpellRechargeModifierUpgrade.cpp`
passed its allocation check and the refreshed scoped planner check. Its merge
dry run accepted no donors: the constructor donor fails because the destination
view lacks `SpellRechargeModifierUpgrade(Thing *, const ModuleData *)`. The
`FireWeaponWhenDeadBehaviorDerived.cpp` mixed-file split for this TU was refused
because no row is approved for the destination. The
`UpgradeModuleDataGetterBuildFieldParse.cpp` split carved `0x004B60FA`, but the
link guard refused it: the moved `buildFieldParse` selected COMDAT lacks
matching private/weak-free context. Nothing was applied.

A fresh allocated `Code/GameEngine/Source/GameLogic/Object/Create/SupplyWarehouseCreate.cpp`
trial also accepted no donors. `SupplyWarehouseCreatePoolKey.cpp` fails to
compile together because `SubsystemInterface` is redefined. The split of
`ConstIntGetters4.cpp` for this TU carved `0x004B8EA2` but compilation was
refused for `Coord3D` and `Thing` redefinitions. The split of
`Rva004B8CDEDerived.cpp` carved `0x004B8EA8`; the link guard refused its
constructor and selected vtable COMDAT contexts. No merge or split was applied.
These blockers need source/header or link-context repair outside this seat.

A fresh allocated `Code/GameEngine/Source/GameLogic/Object/Made002CCC90.cpp`
trial accepted no donors. Its constructor donor fails because the class view
lacks the compiler-generated special-member declaration. The mixed
`VslotSmallBodiesAM.cpp` split carved `0x0050BD7C` but was blocked because a
copied helper or datum would grow the escape-hatch count. No source changes
were applied.
