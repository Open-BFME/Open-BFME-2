# UnitRevivalEntry shared-header adoption, 2026-11-04

Inspected base: `ac936f239c62fadd8d4f3c516ef4cbf4f9b0086c`.
Claim owner: `yasinschroeder-codex5`; class scope acquired by `next_work.py --claim`.

## Applied and verified

- `Code/GameEngine/Source/Common/RTS/UnitRevivalTrackerRva0037F2C0Finish.cpp`: replace the private entry and its unused helper views with `GameLogic/UnitRevivalEntry.h`; use that header's existing +0x94 member spelling. Constructor, destructor, copy and vector calls remain unchanged.
- `Code/GameEngine/Source/GameLogic/System/ArmySummaryRevivalSpawn.cpp`: replace the opaque 0xD8 entry view with the same header. No entry fields are accessed here.
- Existing header evidence supplies the target size/offset facts. This change asserts no recovered original member names and uses no donor source.
- `find_declared_unmatched.py` passes before and after both edits.
- Normal `./build.sh` passes all five rows: one tracker row and four spawn/EH rows. Renumbered EH labels are resolved by parent EH data.
- `header_adopt_lane.py accept --class UnitRevivalEntry` passes each consumer and removes exactly its own queue row (two total).
- No source paths, aliases, pins, baseline exemptions or shared headers changed. Other debt stays registered.

Ordinary combined preview, published census index `a62ac1c10b` (2026-11-04 07:28):

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/RTS/UnitRevivalTrackerRva0037F2C0Finish.cpp: LINKS  LINKED 111 -> 111 bytes (census 2026-11-04 07:28 at a62ac1c10b; file's own bytes 111)
Code/GameEngine/Source/GameLogic/System/ArmySummaryRevivalSpawn.cpp: LINKS  LINKED 312 -> 312 bytes (census 2026-11-04 07:28 at a62ac1c10b; file's own bytes 312)
link_check: 2 of 2 link cleanly; LINKED 423 -> 423 bytes (5.4s)
```

These are preservation previews, not a new census or a real-link measurement.

## Remaining eight consumers

The supported bulk adoption trial changed no source and reported:

```text
  FAIL Code/GameEngine/Source/Common/RTS/UnitRevivalEntry.cpp: field renames: UnitRevivalEntry::m_14 (+0x14) is Rva001EAE6FHelper; the canonical UnitRevivalEntry::m_field14 is BfmeFixedStorage128
  FAIL Code/GameEngine/Source/Common/RTS/UnitRevivalTracker.cpp: field renames: the header's layout: Code/GameEngine/Source/Common/RTS/UnitRevivalTracker.cpp: compile failed: C2011
  FAIL Code/GameEngine/Source/Common/RTS/UnitRevivalTrackerRva0037F2C0Finish.cpp: field renames: UnitRevivalEntry::m_14 (+0x14) is Rva001EAE6FHelper; the canonical UnitRevivalEntry::m_field14 is BfmeFixedStorage128
  FAIL Code/GameEngine/Source/GameClient/GUI/GUICallbacks/OldSchoolHelpBoxContentSource.cpp: field renames: /work5/Open-BFME-2/vendor/stlport/config/stl_dec_vms.h:50: trigraph or continued line comment in include input
  FAIL Code/GameEngine/Source/GameLogic/Object/Update/FreelistPool.cpp: field renames: UnitRevivalEntry::m_B0 (+0xB0, 32 bytes) has no canonical field of that offset and size
  FAIL Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_livingWorldRegion.cpp: field renames: /work5/Open-BFME-2/vendor/stlport/config/stl_dec_vms.h:50: trigraph or continued line comment in include input
  FAIL Code/GameEngine/Source/GameLogic/System/ArmySummaryRevivalSpawn.cpp: field renames: UnitRevivalEntry::opaque (+0x0, 216 bytes) has no canonical field of that offset and size
  FAIL Code/GameEngine/Source/GameLogic/System/LinearCampaignManager.cpp: field renames: /work5/Open-BFME-2/vendor/stlport-4.6/stlport/config/stl_dec_vms.h:50: trigraph or continued line comment in include input
  FAIL Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldPlayer.cpp: field renames: the header's layout: Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldPlayer.cpp: compile failed: C2011
  FAIL Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldPlayerCreateRevival.cpp: field renames: UnitRevivalEntry::unknown00 (+0x0, 8 bytes) has no canonical field of that offset and size
```

The two consumers above were then manually adapted and accepted through the owning lane. For the remaining eight, no source attempt is retained and no queue row is retired. Next check: reconcile the private +0x14 helper and +0xB0 record identities/lifetimes in the constructor/destructor providers before retrying those providers; inspect the C2011 diagnostic for UnitRevivalTracker/LivingWorldPlayer. Other consumers need binding-aware member mapping or replacement of opaque views. The trigraph/continued-comment diagnostic is an include-input scanning refusal, not a byte mismatch; inspect it separately rather than weakening the scanner in this change.
