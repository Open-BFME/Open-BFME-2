# LivingWorldPlayer staged header adoption, 2026-11-05

Inspected source revision: `ce150e37e9` (rebased on `7d450ddcaf`).
Scope: the 13 LivingWorldPlayer header-queue consumers. No canonical header,
provider identity, pin, function row or hatch was changed.

## Retained adoptions

- `Code/GameEngine/Source/GameClient/LivingWorld/InGameUI/StrategicInGameUIBattlePromptDialog.cpp`:
  replace the private player class with the canonical header; use existing
  canonical name +0x1C, faction pointer +0x40 and color +0x184 storage.
  The faction remains a local view reached by a cast from the canonical void pointer.
- `Code/GameEngine/Source/GameLogic/System/LivingWorld/Rva0020EE29Rva0020F483.cpp`:
  replace the private player class with the canonical header; retain the
  existing local bonus-block view by casting canonical +0x258 storage, and
  access the existing canonical +0x14 ID field.

Target facts are the offsets already embodied by the matched source and
canonical header provenance. These edits establish shared class identity;
they make no claim about original donor field spellings.

Verification:

- `./build.sh` on the two retained and four restored trial sources:
  **38/38 matched**, string references 1/1, float/import references pass.
- `find_declared_unmatched.py` on both retained sources: all definitions matched.
- `header_adopt_lane.py accept --class LivingWorldPlayer --header
  Code/GameEngine/Include/GameLogic/LivingWorldPlayer.h <both sources>`:
  PASS for both; tool retired exactly two header-queue rows.
- Current-input `link_check.py <both sources>`: 2/2 link cleanly,
  773 -> 773 and 230 -> 230 bytes, total 1003 -> 1003.
  Index metadata: provider commit `c95fcfcfcd`, date 2026-11-05 05:17;
  underlying census commit `c2a9f8e0d7`, date 2026-11-05 03:49.
  This is a link preview, not a new census or headline gain.

## Restored manual trials and prerequisites

All four failed trials were restored before the successful 38-row verification.
No nonmatching trial remains under Code/.

- `StrategicInGameUILocalPlayerData.cpp`, parent 0x005E9A5E (236 bytes):
  the same field substitutions as BattlePromptDialog reach a compile-time
  Snapshot contract conflict. LivingWorldPlayer requires the native name slot
  and rejects capitalized/reference-transfer profiles; this source already
  includes canonical LivingWorldBattle, which requires both. Compiler C1189
  at LivingWorldBattle.h:28. Reordering alone cannot satisfy both contracts.
  Next: reconcile the shared Snapshot interface contracts with independent
  target vtable/transfer evidence before retrying dual adoption. This pass
  deliberately made no shared-header change.
- `LivingWorldPlayer_CheckForRemovedMultiRegionBonuses.cpp`, 0x002E1FC2
  (139 bytes): references to typed maps in canonical +0x29C/+0x2A8 storage
  and the +4 listener list compile but change register allocation (this from
  EDI to ESI); bytes fail. Next: preserve native aggregate access/codegen
  while retaining the canonical player definition.
- `LivingWorldPlayerRegionMembership.cpp`, 0x002E0B76 (74 bytes): a typed
  vector reference over canonical +0x1B8 storage compiles but changes size
  calculation load order and registers; bytes fail. Same aggregate-codegen
  prerequisite as above.
- `LivingWorldLogicRemovePlayer.cpp`, 0x002B7DE6 (563 bytes): canonical
  ID/lost accesses and a const vector reference at +0x1B8 compile, but change
  register allocation and the lost-byte test instruction shape. Next: retain
  the original forceinline predicate shape and resolve aggregate access
  codegen before retrying. The original source verifies after restoration.

## Automated refusals left unchanged

The supported adoption trial across all 13 sources retained no edits. Besides
scope-sensitive token renames in the two now manually repaired consumers,
its refusals were typed/opaque storage mismatches (+4 list, +0x1A8 records,
+0x1B8 vector, +0x258 bonus), score data not explicitly represented by the
canonical field divisions (+0x2C8, +0x2F0), opaque prefix mismatches,
AptTimeLineStats layout rejection, and AptQuitMenuCallbacks data-row failure.
Their queue rows remain. Eleven LivingWorldPlayer consumers still need work.
