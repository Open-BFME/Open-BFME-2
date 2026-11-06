# Reconciliation plans for the 18 high-confidence identity candidates (2026-11-06)

The identity pass in `reverse/attempt_support/class-identity-reviews-20261106/` ended
with 18 high-confidence `same` verdicts on live sources: a private stand-in judged to be
the same type as an existing canonical class. This is the next question for each -
whether the replacement can actually be made, and what it costs. Read-only throughout:
no source, contract, header or ledger row was changed, and no unit was built.

**4 ready, 12 blocked, 2 needing more evidence.**

The headline is that identity was never the bottleneck. Of the 17 distinct types
proposed, only 10 have both a registered header and a contract; the other 7 - CameraPath,
GameResultsInterface, IDirect3DVertexBuffer8, LaserUpdate, PathfindCellInfo, TurretInfo
and W3DModelDrawModuleData - are themselves file-local declarations in some `.cpp`, with
no row in `reverse/canonical_classes.csv` and no contract. There is nothing to include,
so the stand-in cannot adopt them however certain the identity is. Those need a canonical
header established first, which is the header lane's own establish step, not this one.

Of the 10 that are registered, several carry a contract that cannot support a size check:
ThingTemplate records size 1 with no fields, Team records 60 against its own evidence of
0x13C, MeshModelClass records 192 against a retail extent of 193. That defect is measured
across all 568 contracts in `reverse/attempt_support/class-contract-size-vote-20261106/`.

## Ready

Each still owes the lane's verification: byte gate and the affected-consumer link check.
None has been applied.

### PathfindCell - `Code/GameEngine/Source/GameLogic/AI/PathfinderCellQueryPredicates.cpp`

- highest offset used: 0x0C; contract: {"size": 16, "size_by": "majority", "key": "class", "bases": []}
- include: `#include "../../../Include/GameLogic/PathfindCell.h"`
- class key: stand-in `struct`, mismatch True (no ledger row names the stand-in, so source spelling only)
- risk: low - size 16 and the +0x0C uint match the contract exactly, the change touches only the view type, no mangled ledger rows name the stand-in, and the 47 VPathfindCell rows are unaffected.
- plan: 1. Confirm the name ledger state for nl-b359a142c7c7 (naming guard only) and record the rename there. 2. Confirm the 9 Pathfinder predicate rows in this file are still matched (functions.csv lines 44686-44695: IsWaterCell 47B, IsCliffCell 36B, IsImpassableCell 38B, GetCellType 60B, GetGroundLayer 38B, IsPointOnWall 51B, isBlockedGateObstacleCell 47B, IsNonPinchedCliffCell 47B, IsBuildRestrictedCell 79B). 3. Declaration commit: add `#include "../../../Include/GameLogic/PathfindCell.h"` after the existing AIPathfind.h include; delete `struct Rva001E3647Result { char m_pad[0x0C]; unsigned int m_flags; };`; replace the 9 `(Rva001E3647Result *)` casts of rva001E3647Pos with `(PathfindCell *)`; replace the 11 `->m_flags` reads with `->m_0C`. Keep the raw bit expressions ((flags>>4)&0x3F, flags&0x0F) rather than getLayer()/getType() so the emitted code stays the same. Do not touch rva001E3647Pos (AIPathfind.h line 209 returns void*). 4. Byte verification by the lead on one build for the 9 rows above and the Rva002E9ACC ctor row at functions.csv line 41698 (101B), which is in the same file. 5. Affected-consumer link check on the callers of the 9 predicates (the Pathfinder methods are exported, and their names and signatures do not change). Include cycle check: PathfindCell.h has no #include lines, so the include cannot cycle.

### PlayerTemplate - `Code/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorPrimarySlots.cpp`

- highest offset used: 0x1BC (bool m_isEvil, 1 byte; ends 0x1BD). Contract size 476 (0x1DC) fits.; contract: {"size": 476, "size_by": "majority", "key": "class", "bases": []}
- include: `#include "../../../../Include/Common/PlayerTemplate.h"`
- class key: stand-in `struct`, mismatch True (no ledger row names the stand-in, so source spelling only)
- risk: low - one member retyped and one include added; the stand-in's Player view remains a private competing view, which is out of scope here
- plan: 1. Add the include line above next to the unit's existing include block.
2. Delete struct Rva004534F5PlayerPart (lines 67-71) and retype the private Player view member to const PlayerTemplate *m_34; // +0x34 (match Player.h's const).
3. Leave the body at line 114 (player->m_34->m_isEvil) unchanged; m_isEvil is at +0x1BC in PlayerTemplate.h, which is the same offset.
4. Make this declaration-only change as its own commit; do not touch the Player private view beyond the member type.
5. Dave's build runs the byte check for row 0x004534F5 (194 bytes) and the link check for PlayerTemplate consumers (layout 3d80ccf86f and cd12039382 units first). Expect byte-identical output.
6. Record the keyword struct->class change as a no-op for mangling: the unit's only row (?onObjectCreated@GettingBuiltBehavior@@) does not spell the stand-in type, so no ledger rename is needed.

### SpecialAbilityUpdateModuleData - `Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdateSlot8.cpp`

- highest offset used: 0x38 (m_specialPowerTemplate, 4-byte pointer, bytes 0x38-0x3B); the stand-in's m_pad00[0x38] is never read; contract: {"size": 200, "size_by": "majority", "key": "class", "bases": []}
- include: `#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"`
- class key: stand-in `struct`, mismatch True (no ledger row names the stand-in, so source spelling only)
- risk: low - the stand-in is a pad plus one pointer, and only one cast changes. The main risk is the contract's stale type name for +0x38, which tools may read; the 7 existing consumers must still link.
- plan: 1. Re-run tools/find_declared_unmatched.py on the file before editing (it reports frozen=false today). 2. Declarations commit only: reconcile the contract's m_specialPowerTemplate type (Overridable * -> const SpecialPowerTemplate *) in reverse/class_contracts/SpecialAbilityUpdateModuleData.json, or record it as the reason for the later header-type change. 3. Source commit: delete the forward decl 'class Rva0044EDA6ModuleData;' (line 15) and 'struct Rva0044EDA6Outer' (lines 52-56); add the include line after line 18. 4. Change line 64 to 'const SpecialAbilityUpdateModuleData *data=(const SpecialAbilityUpdateModuleData *)m_moduleData;'. Line 66 (data->m_specialPowerTemplate->getFO()->m_type) stays unchanged because the field sits at +0x38 in both views. 5. Lead runs the build; byte-verify SpecialAbilityUpdate::vslot08 (0x0044EDA6, 97 bytes) is identical. 6. Affected-consumer link check on the 7 units/7 layouts that use SpecialAbilityUpdateModuleData per tools/class_views.py: DockUpdate.cpp, SpecialAbilityUpdate.cpp, GiveOrRestoreUpgradeSpecialPowerModuleDataCtor.cpp, WeaponFireSpecialAbilityUpdateModuleDataCtor.cpp, DominateEnemySpecialPower.cpp, SpecialAbilityUpdateModuleData.cpp, SpecialAbilityUpdateTriggerAbilityEffect.cpp.

### AIUpdateInterface - `Code/GameEngine/Source/GameLogic/Object/WeaponRva002CB2D1Range.cpp`

- highest offset used: 0x1F0 (void *m_1F0, bytes 0x1F0-0x1F3). Contract size 0x3E4 covers it.; contract: {"size": 996, "size_by": "retail-new", "key": "class", "bases": ["UpdateModule", "AICommandInterface", "AIUpdateInterface24"]}
- include: `#include "../../../Include/GameLogic/Module/AIUpdate.h"`
- class key: stand-in `struct`, mismatch True (no ledger row names the stand-in, so source spelling only)
- risk: medium - the AIUpdateInterface header touches 208 units. This file's change is small, but the include can reorder definitions in a TU that also defines its own 'class Object'; a compile must confirm no collision. Include-cycle check: AIUpdate.h's include closure (11 files) does not reach AI.h, Weapon.h or any of this unit's headers.
- plan: 1. Re-run tools/find_declared_unmatched.py before editing (frozen=false today). 2. Declarations commit: add '#include "../../../Include/GameLogic/Module/AIUpdate.h"' before the 'class Object' definition (line 56), after the Coord3D include at line 15, so AIUpdateInterface is complete before getCurLocomotor is called. Check include order against line 44 (Module.h) with a compile. 3. Delete 'struct Rva002CB35CAI' (lines 38-42). Change the Object member at line 70 to 'AIUpdateInterface *m_258;'. 4. In Weapon::isWithinAttackRange (line 145), change '!ai->m_1F0' to '!ai->getCurLocomotor()'. 5. Lead runs the build and checks that Weapon::isSourceObjectWithGoalPositionWithinAttackRange (0x002CB2D1, 139 bytes) and Weapon::isWithinAttackRange (0x002CB35C, 568 bytes) stay byte-identical. 6. Affected-consumer link check across the 208 AIUpdateInterface units (198 layouts) the lead already tracks with tools/class_views.py --class AIUpdateInterface, with extra attention to units that include AI.h and Weapon.h.

## Blocked and needs-evidence

Grouped by the reason that actually stops them, with the details in `plans.json`.

- **ThingTemplate** (blocked) - `Code/GameEngine/Source/GameClient/DrawableRva0027B18C.cpp`
  - contract size is 1 (size_by majority), so no size check can pass against it; retail evidence in the contract and header (new 0x640, ctor end +0x63C) says the real size is about 1600; contract bases [] conflicts with header line 37 (class ThingTemplate : public Overridable) and the header's note that the ctor writes the base prefix at +4, +8, +0xC; contract fields list is empty, so the field compar
- **MeshModelClass** (needs-evidence) - `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBufferRva000E8365.cpp`
  - pointee layout is unproven: the stand-in reads m_array at +0x0C of its buffer struct, but the ShareBufferClass shim puts Array at +0x08 (RefCountClass is 8 bytes per class_contracts/RefCountClass.json). Retail rva000E8365 (753 bytes) decides which is right; no evidence found in the repo for +0x0C; contract size 192 is below the retail extent lower bound 193 (byte written at +0xC0 by the ctor at 0x
- **W3DModelDrawModuleData** (blocked) - `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawDistanceOpacity.cpp`
  - no registered canonical header: canonical_classes.csv has no W3DModelDrawModuleData row, class_views.py reports header '-', and the class body is in Code/Libraries/Source/WWVegas/WWLib/W3DModelDrawModuleData.cpp (line 150), which cannot be included as a header; no class contract exists, so bases (Snapshot per the .cpp), size and key cannot be checked against a registered contract; key mismatch wit
- **WeaponTemplate** (blocked) - `Code/GameEngine/Source/GameLogic/Object/Made002CC5E1Rva005084FC.cpp`
  - Size conflict: contract size is 364 (0x16C) but the canonical header declares m_field17C (void*, +0x17C, ends 0x180 = 384). Contract view_sizes show 384 in 4 views and 364 in 7. The stand-in itself only reaches 0x142, so the conflict is between the header and the contract, not the stand-in.; Base clause conflict: canonical WeaponTemplate.h declares `class WeaponTemplate : public MemoryPoolObject` 
- **CameraPath** (blocked) - `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCameraModLookTowardBfme.cpp`
  - No canonical header: class CameraPath is defined inside W3DViewCameraModFinalLookTowardBfme.cpp (not in any Include header) and is not registered in reverse/canonical_classes.csv. Adoption would mean creating a new canonical declaration, which is not a replacement.; No class contract: reverse/class_contracts/CameraPath.json does not exist, so size, key and bases cannot be checked against a registe
- **TurretInfo** (blocked) - `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DScriptedModelDrawTurretInfo.cpp`
  - No registered canonical header: reverse/canonical_classes.csv has no TurretInfo row (header column is '-'), and class_views.py lists only one unit, W3DModelDrawConditionParsers.cpp:30, as a file-local struct.; Scope conflict: the canonical struct is at namespace scope in W3DModelDrawConditionParsers.cpp:30, but the ledger names the class ModelConditionInfo::TurretInfo (reverse/functions.csv row ?c
- **LaserUpdate** (blocked) - `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLaserDrawBfmeDoDraw.cpp`
  - No registered canonical header: reverse/canonical_classes.csv has no LaserUpdate row and the header column is '-'. The class is defined in Code/GameEngine/Source/GameLogic/Object/Update/LaserUpdate.cpp, a .cpp TU, so there is no header to include.; No class contract: reverse/class_contracts/LaserUpdate.json does not exist.; Base mismatch: the canonical class derives from Rva0049B47C (polymorphic, 
- **IDirect3DVertexBuffer8** (needs-evidence) - `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DAptRendererBeginTriangleList.cpp`
  - No class contract: reverse/class_contracts/IDirect3DVertexBuffer8.json does not exist, and canonical_classes.csv has no row. The only authority is the vendored shim, reference/shims/d3d8_shim_validated.h:219.; Call-site type mismatch inside a matched function: BeginTriangleList (0x00111224, 238B, matched) passes &memory (void**) to Lock, which takes BYTE**. Fixing it means either a reinterpret_cas
- **DisplayString** (blocked) - `Code/GameEngine/Source/Common/Rva00262045Unlink.cpp`
  - size: reverse/class_contracts/DisplayString.json size 4 (size_by majority, 46 views at 4 vs 5 at 20) under-reports the layout. m_prev at 0x10 ends at 0x14, which DisplayString.h:2 and the W3D ctor bound at 0x14. The contract must be corrected before adoption.; access: DisplayString.h:56-57 declares m_next and m_prev protected, and the only friend is class DisplayStringManager (DisplayString.h:21).
- **PathfindCellInfo** (blocked) - `Code/GameEngine/Source/Common/System/Rva002F1BD5Finish.cpp`
  - no registered canonical header: PathfindCellInfo has no canonical_classes.csv row, no class contract and no header under Code/GameEngine/Include. Its only definition is a private struct PathfindCellInfo inside Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp (line 187), so there is no include line to adopt.; class versus struct conflict: PathfindCell.h:10 forward-declares class PathfindCellInfo,
- **GameResultsInterface** (blocked) - `Code/GameEngine/Source/Common/GameEngineDeletingBaseDerived.cpp`
  - stale candidate: already folded. Commit b85670a7fb0 'Fold class Rva00419CD4 into GameResultsInterface' is an ancestor of HEAD. GameEngineDeletingBaseDerived.cpp now declares class GameResultsInterface (line 129), and rg finds no Rva00419CD4 in that file or in GameResultsQueueStartup_Unresolved.cpp. This entry has nothing left to reconcile.; ledger residue (not a source blocker): reverse/name_agree
- **ThingTemplate** (blocked) - `Code/GameEngine/Source/GameLogic/AI/PathfinderCellQueryPredicates.cpp`
  - registered contract class_contracts/ThingTemplate.json records size 1 (size_by majority), but its own retail evidence gives 0x640 (allocation_observed; extent_lower_bound 1600 at 0x33E1B8). The size gate cannot pass against a size of 1; the contract must be repaired first; ThingTemplate contract has an empty fields list (0 entries), so the field comparison above relies on ThingTemplate.h's offset 
- **StructureCollapseUpdate** (blocked) - `Code/GameEngine/Source/Common/Rva0024A797Grandchildren.cpp`
  - dtor-holder with live link bindings: the stand-in's destructor rows are ??1Rva004A4214@@UAE@XZ (0x004A4214, 32 B) and ??_GRva004A4214@@UAEPAXI@Z (0x004A436F, 28 B) in Rva0024A797Grandchildren.cpp, and the registered contract's vtable slot 0 is named ??_GRva004A4214@@UAEPAXI@Z. Renaming the stand-in touches all of them; link-level alias: Rva0024A797Grandchildren.cpp:455 binds /alternatename:?fe@Rva
- **Team** (blocked) - `Code/GameEngine/Source/Common/TeamInQueue.cpp`
  - Contract size is wrong: reverse/class_contracts/Team.json says size 60 (majority), but +0x5E needs at least 0x5F bytes. Its own evidence shows allocation 0x13c (3 sites) and an extent lower bound of 297, and TeamBFME2.h:227-228 asserts sizeof(Team)==0x13C. Fix the contract before any adoption.; The contract's fields list records only __vfptr, so +0x5D/+0x5E are not checked against it. The canonica

## Two cautions about this data

The `frozen` field in `plans.json` is not a verified frozen-file check. It was inferred
from `find_declared_unmatched.py` reporting all defined functions matched; that tool has
no frozen flag. Anyone acting on a plan must run the project's own frozen check first,
as `AGENTS.md` requires before planning an edit.

One candidate is stale rather than blocked: `Rva00419CD4` -> GameResultsInterface was
already folded in b85670a7fb0, an ancestor of this commit, and only ledger residue
remains in the name and data ledgers. It needs retiring, not reconciling.
