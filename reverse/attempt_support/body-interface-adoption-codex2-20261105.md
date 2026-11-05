# Body-interface caller adoption, 2026-11-05 (codex2)

Inspected source: `945f800ce67c`. Link preview index: `f44cbcf5b0`, 2026-11-05 15:19.

Each removed private `BodyModule` view describes the interface stored at Object +0x254, not the complete module with its primary and behavior-interface bases. The units now include the unchanged registered `BodyModuleClass.h` and use its canonical `BodyModuleInterface` subobject type. Existing virtual-call offsets prove the correspondence; exact byte verification confirms the complete callers. No donor-path or new source-name claim is made.

| Unit | Interface calls (zero-based slots) |
| --- | --- |
| OldSchoolHelpBoxContentSource | getHealthRatio (5) |
| AutoAbilityBehaviorRva0045A447 | getHealthRatio (5) |
| PropagandaTowerBehavior | getMaxHealth (6) |
| EvacuateDamageRva004BAF55 | getMaxHealth (6), formerly mislabeled getHealth |
| ObjectShockRva00296065 | getLastDamageInfo (15), retaining the existing +8 source-ID view |
| ScriptActionsTeamHealthPercent | setInitialHealth (21), rva004BDB37 (23) |
| HordeContainIface20Slots | clearArmorSetFlag (13), same argument 5 |
| GarrisonContain | getDamageState (8) |

## Verification

- Normal `./build.sh` checks: 62/62 matched functions in the initial six units, 5/5 in HordeContainIface20Slots, and 42/42 in GarrisonContain: 109/109 total. The PropagandaTowerBehavior data row passes. String, float and import references pass; renamed EH labels are verified through parent EH data.
- `find_declared_unmatched.py` passes for every changed unit.
- One final `header_adopt_lane.py accept --class BodyModule` cohort covers all eight sources below. Every unit passes byte and link-preservation judgment. The owning tool retired eight queue rows (six in the initial acceptance and two when the cohort was extended).
- External-definition/directive comparison against pre-change compiled objects: seven units lose no definitions; OldSchoolHelpBoxContentSource replaces only `?getBodyModule@Object@@QBEPAVBodyModule@@XZ` with the canonical-interface return spelling. No alternatename or weak binding is removed. No vtable definition is added or removed.
- Searched all 39,415 `.obj` files under `build/` for the removed accessor spelling, then parsed matching COFF symbols/directives. No object imports it or uses it through a weak binding, alternatename or INCLUDE. Other build/match definitions remain in ControlBarPopupDescription, PassiveAreaEffectBehavior and PassiveAreaEffectBehaviorPulse. Thus this adoption does not remove its only provider or strand a compiled consumer.
- `git diff --check` passes. No source paths, shared headers, pins, ledger rows or escape hatches change.

The complete-module/base-layout adoption failures remain queued and their sources are restored. This is caller/header-debt cleanup, not a real-link, census or runtime result. No smoke runner was started.

Final acceptance scope:

```text
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/OldSchoolHelpBoxContentSource.cpp
Code/GameEngine/Source/GameLogic/Object/Behavior/AutoAbilityBehaviorRva0045A447.cpp
Code/GameEngine/Source/GameLogic/Object/Behavior/PropagandaTowerBehavior.cpp
Code/GameEngine/Source/GameLogic/Object/Damage/EvacuateDamageRva004BAF55.cpp
Code/GameEngine/Source/GameLogic/Object/ObjectShockRva00296065.cpp
Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsTeamHealthPercent.cpp
Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface20Slots.cpp
Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp
```
