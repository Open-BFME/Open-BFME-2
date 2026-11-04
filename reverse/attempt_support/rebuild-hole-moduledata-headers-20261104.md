# RebuildHoleExposeDie module-data header adoption

Inspected 2026-11-04 at `1e2125afaae297db81897cd518dffcc3689124da`.
Scope: `Code/GameEngine/Source/GameLogic/Object/Die/RebuildHoleExposeDie.cpp`.

The StoreObjectsSpecialPowerModuleData picker served four consumers. The
straight header swap failed in RebuildHole's data-row compilation because its
`Common/BfmeModuleData.h` shim and canonical `Common/ModuleData.h` both define
ModuleData. A separate class-layout compilation confirmed C2011; the normal
data verifier's shortened diagnostic had hidden that first error. The original
RebuildHole and Dock units passed their combined 33 function rows and two data
rows before repair.

## Repair and target evidence

RebuildHole now includes canonical ModuleData and DestroyDieModuleData rather
than the shim and its local padded DestroyDieModuleData. The canonical headers
record retail's eight-byte module-tag prefix and the DieMuxData member at +8,
ending at +0x38. The source's RebuildHole data constructor and parse table keep
their existing offsets. This is adoption of existing target-backed headers,
not a newly inferred layout or recovered donor identity.

The same prerequisite repair lets the adoption tool replace eight static-only
local declarations with their canonical headers: SpecialAbilityUpdate,
StoreObjectsSpecialPower, CurseSpecialPower, DelayedDeathBody,
DominateEnemySpecialPower, GiveUpgradeUpdate, TeleportToCasterSpecialPower,
and WeaponSetUpgrade module data. The already included canonical Player header
also passes its queued acceptance. All ten queue rows are retired only through
`header_adopt_lane.py accept`.

Compiler layout evidence from `class_layouts.compile_layouts` (its separate
layout cache, not the match cache):

| Class | Size | Relevant members |
| --- | --- | --- |
| ModuleData | 0x08 | module tag +4 |
| DestroyDieModuleData | 0x38 | DieMuxData +8, size 0x30 |
| RebuildHoleExposeDieModuleData | 0x48 | hole name +0x38, max health +0x3C, fade time +0x40, transfer flag +0x44 |

Verification: `./build.sh` passes 11/11 functions, one data row, one string
literal and one float literal; the frozen-file check reports all definitions
matched. Every acceptance passes the byte and link gates. The final link
preview uses the published 2026-11-04 17:56 index at `8c757ea0db` and preserves
the unit's census-linked scope. This is a prediction, not a new linking census
or a measured headline increase.

## Remaining consumers and prerequisites

- ModuleFactoryInit and DockUpdate: the straight StoreObjects header swap
  still encounters the conflicting legacy ModuleData definition. Reconcile
  each owning unit's base and derived layout before retrying; neither source
  was changed here.
- MissileLauncherBuildingUpdate: the adoption scanner now stops at the
  unchanged continued-comment input in `vendor/stlport/config/stl_dec_vms.h:50`.
  No scanner bypass, field-renaming workaround, or byte/link acceptance is
  claimed. Its source was restored unchanged. The scanner prerequisite is
  already registered in the guarded include-cycle verifier entry.
- RebuildHole's DieModule adoption remains blocked by the separate primary
  vtable ownership issue in LINK-167. Its private AI and PlayerList views also
  remain queued. These existing blockers were not retried without new evidence.

No headers, pins, aliases, source paths, function rows or data identities were
changed. No alternate-name provider was removed.
