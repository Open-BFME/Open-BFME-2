# SpecialPowerModuleInterface caller adoption (2026-11-05, codexb2)

The existing canonical header is unchanged. Eight callers replace private
interface declarations with `GameLogic/Module/SpecialPowerModule.h`.

The old declarations and canonical header establish these dispatch slots:

| Old caller spelling | Slot | Canonical spelling |
| --- | --- | --- |
| AISpecialPowerUpdate `s1` | 1 | `isReady` |
| ControlBar `isPaused` | 3 | `slot03` |
| ToggleHidden `rva004AE2D0Slot9` | 9 | `pauseCountdown` |
| ActivateModule `atLocation` | 12 | `doSpecialPowerAtLocation` |
| TriggerAbilityEffect `resetRecharge`, WeaponFire `rva15` | 15 | `startPowerRecharge` |
| Store `rva_slot18`, ControlBar `isUsable` | 18 | `rva0049466D` |
| SpecialAbilityUpdate `s19` | 19 | `slot19` |

Both slot-18 callers pass zero; the canonical pointer argument preserves that
call. Slot 3 retains its neutral canonical name: this change makes no new name
or role claim. No derived interface implementations or ledger symbols change.

## Verification

- `./build.sh` on the eight sources: 94/94 rows byte-match, including parent-EH
  verification of renumbered funclet labels; literal/reference checks pass.
- `find_declared_unmatched.py` passes for every changed source.
- `header_adopt_lane.py accept --class SpecialPowerModuleInterface` passes for
  every changed source, including its explicit per-unit link-loss prediction;
  it retires exactly eight `reverse/header_queue.tsv` rows.
- This is header debt retirement, not a new link census or game smoke result.

## Scope

- `Code/GameEngine/Source/Common/RTS/SpecialPowerStoreCanUseSpecialPower.cpp`
- `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarRappellerCount.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/AISpecialPowerUpdate.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/ActivateModuleSpecialPowerVslot.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdateTriggerAbilityEffect.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/ToggleHiddenSpecialAbilityUpdate.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/WeaponFireSpecialAbilityUpdate.cpp`

## Remaining queue

The initial automatic adoption trial passed no units and restored its trials.
The thirteen remaining queue entries need separate work: several derived
implementations use different virtual signatures; loadPostProcess places
implementation fields in its private interface; other callers use incompatible
arguments or return types. Their queue entries remain unchanged. No nonmatching
trial remains in Code/.
