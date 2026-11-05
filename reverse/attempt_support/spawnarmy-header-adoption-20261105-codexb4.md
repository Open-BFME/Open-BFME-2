# SpawnArmy canonical-header adoption, seven more consumers

Base: `51ba895b7cd7e696961ca7fe3be428c2d13e67d0`, 2026-11-05.
Scope claimed through the header picker: `class:SpawnArmy`.

Replace seven private SpawnArmy declarations with the existing canonical header.
Select the supported STLport profile for QueueUnitButton. In the three consumers
that already include LivingWorldRegion, retain its Snapshot slot-3 spelling by
mapping `xfer` to `DoXfer` locally while including SpawnArmy. This keeps the
canonical class concrete without changing the shared headers or vtable slots.
The two placement copies use the existing two-float record view at canonical
`m_20`/`m_24`; the aggregate assignment preserves retail's integer word copies.
Use canonical `m_4c` and `m_2c` for the other two accessed fields. These are target
layout and code-generation facts, not donor-name or original-TU claims.

## Verification

`find_declared_unmatched.py` passes before and after for all seven sources.
`./build.sh` passes all **92/92 function rows**, including the parent-validated
funclets, six string literals and one float literal. One batch invocation of
`header_adopt_lane.py accept --class SpawnArmy` passes all seven and retires
exactly seven rows through the supported header-queue path.

Compare each before/after COFF object's complete external-definition set: all
seven sets are identical. No inline member, alias, data or other external
provider is removed. No shared header, pin, symbol mapping or source path changes.

`link_check.py` passes **7/7 LINKS**, **6,428 -> 6,428 bytes**, using its fetched
2026-11-05 15:19 index at `f44cbcf5b0`. This scoped prediction preserves the
preview's linking coverage; no real-link or census headline gain is claimed.

| Consumer | External definitions retained | Preview bytes before/after |
| --- | ---: | ---: |
| `Code/GameEngine/Source/Common/Rva005E8C54Ctor.cpp` | 43 | 889 / 889 |
| `Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldAIOrders.cpp` | 18 | 967 / 967 |
| `Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldAISupport/LivingWorldAIBuildingTypes.cpp` | 138 | 1420 / 1420 |
| `Code/GameEngine/Source/GameClient/LivingWorld/InGameUI/StrategicInGameUIQueueUnitButton.cpp` | 15 | 925 / 925 |
| `Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildingNuggetSpawnArmy.cpp` | 11 | 844 / 844 |
| `Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldScenarioOwnershipSet.cpp` | 6 | 585 / 585 |
| `Code/GameEngine/Source/GameLogic/System/LivingWorld/Rva0059DA34.cpp` | 50 | 798 / 798 |

Six queue entries remain: StrategicInGameUIBuildQueueIconSelect, LivingWorldArmy,
LivingWorldCampaignAct, LivingWorldCampaignObjects, LivingWorldLogic, and WWLib's
SpawnArmy. Their source-specific prerequisites remain as recorded in the prior
[cohort evidence](spawnarmy-header-adoption-20261105-codex3.md); these six files
were not changed in this batch.
