# Shard 0 mechanical consolidation dry-run handoff

Inspected revision: `f33821b80212ed02ccb66d18b3eebe50df5f1e44` (BFME 2, 2026-11-04).
The read-only allocator reported shard `0/5`; `--check-tu` exited 0 for each
attempted destination. Each destination's scoped `name_lane.py consolidate`
snapshot was current before its plan/dry-run. No source or ledger was changed,
no claim was acquired, and no dry run accepted two or more donors. LinkGuard
reported the listed source units census-linked and rejected no candidate on
link loss except the explicit `XferMD5CRC` donor noted below.

| Destination | Dry-run blocker |
|---|---|
| `Common/MessageStream.cpp` | `GameMessage` / `SubsystemInterface` and `Coord3D` / `ICoord2D` redefinitions; `MessageTranslatorNode*` assignment mismatch; command-name donor `bytes`. |
| `Common/XferMD5CRC.cpp` | `XferSave::Open` is absent from the destination view; the GUI dtor donor loses its selected `Rva0052B497` vftable COMDAT under LinkGuard. |
| `Fesl/gamebrowser/gamebrowserpinger.cpp` | `Rva00803080` lacks `initPool`, `clear`, and `m_0c`; generated `Gen008030A0` vftable redefinition. |
| `GameLogic/Object/Upgrade/DelayedUpgrade.cpp` | `DelayedUpgrade` view lacks `upgradeImplementation` and referenced fields. |
| `GameLogic/Object/Create/EvaAnnounceClientCreate.cpp` | Destination class view lacks constructor, slot, and `xfer` declarations. |
| `Fesl/ariesudp.cpp` | GameNetwork donor fails byte verification. |
| `Common/LivingWorldBuildingNuggetSpawnArmy.cpp` | Destination class view lacks `rva004FA659`. |
| `GameLogic/Object/Update/ToggleDeploySpecialAbilityUpdate.cpp` | Destination class view lacks constructor and slot declarations (`rva004AE5B8`, `rva004AE6D7`, `getModuleNameKey`). |
| `W3DDevice/GameClient/Drawable/Draw/W3DQuadrupedDraw.cpp` | Destination class view lacks constructor; STLport `allocator` redefinition and `vector::resize` specialization conflict. |
| `Common/BfmeOwnVVD.cpp` | Donor needs `TheGameClient`, whose declaration is absent from the composed TU. |
| `GameLogic/AI/GroupOrder.cpp` | Donors redefine `GroupOrder` vftable; constructor compiler-generated-member conflict; STLport vector declaration conflict. |
| `GameClient/Snow.cpp` | `SubsystemInterface` redefinition; `WeatherSetting` special-member and constructor declaration conflicts; INI donor compile produced no diagnostic. |
| `W3DDevice/GameClient/GUI/W3DAptComponentColorPicker.cpp` | Donors require undefined base `Rva005248D0`. |
| `Apt/AptDate.cpp` | Donor's `objectMemberLookup` is absent from the destination class view. |
| `GameLogic/Object/Update/FreelistPool.cpp` | donor `Rva001EAFFEElementAt.cpp` fails byte verification. |
| `WW3D2/streak.cpp` | destructor donor explicitly specializes `SimpleVecClass<T>::~SimpleVecClass` after it has already been instantiated. |
| `W3DDevice/GameClient/camerashakesystem.cpp` | donor's `GenericMultiListClass` view lacks `m_headNext08` / `m_headPrev04`. |
| `WW3D2/agg_def.cpp` | donor `AggregateDefRva001A3930.cpp` defines `rva001A3930`, absent from the destination class view. |
| `GameLogic/Object/Upgrade/SpellRechargeModifierUpgrade.cpp` | constructor donor signature is absent from the destination class view. |
| `GameLogic/Object/Update/ModelConditionSoundSelectorClientBehavior.cpp` | module-data dtor and STLport vector donors both failed compilation without diagnostics; LinkGuard retained all three linked objects. |
| `GameLogic/Object/Create/SupplyWarehouseCreate.cpp` | `SupplyWarehouseCreatePoolKey.cpp` donor has duplicate `SubsystemInterface` declarations; LinkGuard retained both census-linked objects. |
| `GameLogic/Object/Behavior/BridgeTowerBehavior.cpp` | Pool-key donor has `SubsystemInterface` redefinition; Xfer donor has `Xfer` redefinition and missing `Version1`; OnDamage/OnHealing donors have `GameLogic` redefinition. LinkGuard retained all five census-linked objects; canonical header adoption/class reconciliation remain registered prerequisites. |

Also not retried because the obstacle register already records an unchanged
prerequisite: `MemoryReadFile.cpp` (missing current consumer/index receipt),
`DevastateSpecialPower.cpp`, `SpecialPowerCreate.cpp`, and `ProcessAnimateWindow.cpp`.
The previously handed-off shard entries for W3DMouse, Command, matpass,
GrabPassengerSpecialPower, ToggleHiddenSpecialAbilityUpdate,
BfmeResourceEnumerator, LinearCampaignManager and AptLoadScreen were not retried.
DelayedDeathBody was not rerun because LINK-211 already records its missing
census-index prerequisite. BridgeTowerBehavior's canonical header and class
prerequisites are already recorded in LINK-168 and the canonical-module header
handoff.

Next useful check: have the responsible code/header owners reconcile the stated
declarations, class layouts, STLport or byte prerequisites, then recheck the
destination's allocation and rerun the supported dry run. Do not apply any of
these candidates until it accepts unchanged donors and LinkGuard passes.
