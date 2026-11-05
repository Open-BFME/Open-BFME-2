# SpawnArmy canonical-header adoption, 2026-11-05

Base: `feeb8a9454baf2c8b7c7f0b7d410b7be76270ffe`.
Scope claimed through the header picker: `class:SpawnArmy`, canonical header
and its 21 queued consumers. No shared header, symbol, pin or source path changed.

## Repair

The canonical class contains `_STL::vector<AsciiString>`. The eight consumers
below lacked the supported `// stlport` compile-profile marker, so including it
failed before adoption could be checked. Select that profile and replace each
private SpawnArmy declaration with the existing canonical header.

Six consumers pass automatic `header_adopt_lane.py adopt` after that profile
change. The probe's private `RvaVecAscii` and the check's opaque prefix are not
field-for-field matches for the adoption parser. Replace those two declarations
manually, preserving the complete function bodies, and verify normally. The
probe uses canonical `m_48`; the check uses canonical `m_2c`. The unused private
`RvaVecAscii` declaration disappears with the probe's private SpawnArmy view.

These are compile/layout facts from existing target evidence and verification;
no external donor identity or original TU attribution is inferred.

## Verification

`find_declared_unmatched.py` passes before and after the edits for all eight.
`header_adopt_lane.py accept --class SpawnArmy` passes all eight and retires
exactly eight rows from `reverse/header_queue.tsv` through its supported path.

Final `./build.sh` over all eight: exit 0, functions **21/21** exact, one data
row verified, 12 string literals and two compiler float literals verified.
The probe's `$L1217` label renumbers to `$L5425`; parent EH data still places it
at RVA `0x0079A36F`, and funclet verification passes. No hatch is added or removed.

Final `link_check.py` over all eight: exit 0, **8/8 LINKS**, **832 -> 832 bytes**.
This is a scoped prediction using current compiled inputs, not a real-link or
census headline change. Index metadata: provider commit `c95fcfcfcd`, date
`2026-11-05 05:17`; census_commit `c2a9f8e0d7`, census_date `2026-11-05 03:49`.
Index SHA-256: `fc8fb85e6cb11b8514bf608e38196a7ec85c5a49e1d1d2ed6b096b11557093f1`.

| Consumer | Link-preview bytes before/after |
| --- | --- |
| `Code/GameEngine/Source/Common/GapBodiesS3E.cpp` | 238 / 238 |
| `Code/GameEngine/Source/Common/GapBodiesS3E_Rva003F9CD2.cpp` | 393 / 393 |
| `Code/GameEngine/Source/Common/Rva002E074EAccum.cpp` | 22 / 22 |
| `Code/GameEngine/Source/Common/Rva002E0764Sub.cpp` | 27 / 27 |
| `Code/GameEngine/Source/Common/Rva002E112A.cpp` | 43 / 43 |
| `Code/GameEngine/Source/Common/Rva004FF2F4Dtor.cpp` | 8 / 8 |
| `Code/GameEngine/Source/Common/Rva0056AA54Probe.cpp` | 82 / 82 |
| `Code/Libraries/Source/WWVegas/WWLib/Rva00319CEDCheck.cpp` | 19 / 19 |

## Remaining cohort

Thirteen queue rows remain. The initial supported adoption trial reverted each
failed candidate. Their diagnostics below are prerequisites, not claims that a
manual recovery is impossible. Continue one source at a time: reconcile opaque
arrays/coordinates, distinguish same-spelled fields by class, or select a
compatible STLport/Snapshot profile, then rerun byte and link acceptance. Do not
change vendored input or bypass the parser to accept a row.

```text
Code/GameEngine/Source/Common/Rva005E8C54Ctor.cpp: field renames: SpawnArmy::m_data (+0x4, 84 bytes) has no canonical field of that offset and size
Code/GameEngine/Source/GameClient/LivingWorld/InGameUI/StrategicInGameUIBuildQueueIconSelect.cpp: field renames: vendor/stlport/config/stl_dec_vms.h:50: trigraph or continued line comment in include input
Code/GameEngine/Source/GameClient/LivingWorld/InGameUI/StrategicInGameUIQueueUnitButton.cpp: field renames: the header's layout: Code/GameEngine/Source/GameClient/LivingWorld/InGameUI/StrategicInGameUIQueueUnitButton.cpp: compile failed: C2653; C2143; C2501
Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldAIOrders.cpp: field renames: SpawnArmy::bytes (+0x4, 84 bytes) has no canonical field of that offset and size
Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldAISupport/LivingWorldAIBuildingTypes.cpp: field renames: SpawnArmy::data (+0x4, 84 bytes) has no canonical field of that offset and size
Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldArmy.cpp: field renames: Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldArmy.cpp: renaming a04 -> m_04 collides with an existing `m_04` there
Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildingNuggetSpawnArmy.cpp: field renames: SpawnArmy::m_pos (+0x20, 8 bytes) has no canonical field of that offset and size
Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldCampaignAct.cpp: field renames: the header's layout: Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldCampaignAct.cpp: compile failed: C2953; C2953; C2955
Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldCampaignObjects.cpp: field renames: Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldCampaignObjects.cpp: m_buildTime is also a member of ThingTemplate; a token rename would reach it
Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogic.cpp: field renames: SpawnArmy::m_name (+0x4) is StringBase<char>; the canonical SpawnArmy::m_04 is AsciiString
Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldScenarioOwnershipSet.cpp: field renames: SpawnArmy::pos (+0x20, 8 bytes) has no canonical field of that offset and size
Code/GameEngine/Source/GameLogic/System/LivingWorld/Rva0059DA34.cpp: field renames: Code/GameEngine/Source/GameLogic/System/LivingWorld/Rva0059DA34.cpp: m_name is also a member of SubsystemInterface; a token rename would reach it
Code/Libraries/Source/WWVegas/WWLib/SpawnArmy.cpp: field renames: the header's layout: Code/Libraries/Source/WWVegas/WWLib/SpawnArmy.cpp: compile failed: C1189
```
