# InGameUI installer views at full vtable width (banked, 2026-11-04, seat halilkkaya-rl-o3)

Base: `4da444c38e`. Patch: `ingameui-installer-full-views.patch` (InGameUICtor.cpp and
InGameUIDtor.cpp).

## Why

`rename.py function --to-class InGameUI` reads the vftable that InGameUI's installer units compile:
the constructor 0x002A61A9 (InGameUICtor.cpp) and the destructor 0x002A5B30 (InGameUIDtor.cpp). Both
private views declared six virtuals, so `??_7InGameUI@@6BSubsystemInterface@@@` had 7 slots against
retail's 120. The image report records the same 7 against 120. That made `--to-class` refuse every
InGameUI slot, and a linked image would carry a 7-slot InGameUI vtable.

## What the patch does

The same change goes into both files:
- `BFME_SNAPSHOT_NAME_SLOT` and `BFME_SUBSYSTEM_SLOTS` are defined before the Snapshot and
  SubsystemInterface includes, as the canonical InGameUI.h selects them.
- The +0x10 interface declares the canonical slot signatures: slot10_00, slot10_01, rva0029B56E,
  slot10_03(AnimateWindow *) and slot10_04.
- The six-virtual list becomes canonical InGameUI.h's full virtual list, in its order and with its
  access.
- The canonical header's inline slot bodies are declarations only. W3DInGameUI's unit emits those
  COMDATs. The views' field names differ from the header's, so the bodies cannot be repeated.

## Result

- `./build.sh`: InGameUICtor.cpp 84/84 and InGameUIDtor.cpp 46/46 exact, funclets included. The
  `$L` labels renumber, and the builder places them from the verified parent EH data.
- Compiled tables against retail:

  | Table | Slots | Agree | Clash |
  |---|---|---|---|
  | 0x00BFD410 | 120 | 76 | 0 |
  | +0xC 0x00BFD400 | 4 | 2 | 0 |
  | +0x10 0x00BC7A64 | 5 | 1 | 0 |

  Every other slot names an inline COMDAT or a name that no row spells yet.
- `rename.py function --to-class InGameUI --dry-run` now passes the installer check for slot10_00,
  slot89, slot65 and getMousedOverDrawableID. It stops at the next stage: the source of each row
  must be given as prepared C++.

## Why it is not landed

With the full table, both units reference W3DInGameUI's 15 still-unresolved slots:
- slot10_00, slot10_01, slot10_03, slot10_04;
- getScrollAmount, slot49, slot50, getPendingPlaceSourceObjectID, getMousedOverDrawableID;
- slot65, slot77, slot87, slot89, slot92, slot96.

A joint link_check with Rva0008EF3FProductCtor_Unresolved.cpp and the respelled units takes
InGameUICtor (2,686 B) and InGameUIDtor (956 B) from LINKS to not linking. Land this patch in one
batch with the last of those 15 names, never before.

## Remaining per slot (see LINK-181)

- **Prepared C++ under InGameUI** in each row's unit: slot10_00/01/04 and slot89 (GapBodiesS3B.cpp),
  slot10_03 (GapBodiesSeat1A.cpp), slot65 (DispByteOneSetters.cpp), getMousedOverDrawableID
  (DispDwordFieldGetters.cpp) and slot77 (VslotSmallBodiesC.cpp, full mangled `UBE` name).
- **slot49/slot50** (Rva0029AA3F.cpp): `--to-class` refuses ("its parameters name a type by
  back-reference"). `to_class_symbol` treats any digit in the tail as a back-reference, and
  `PBUCoord3D@@` contains a 3. False reject, recorded in re_attempts.log.
- **getScrollAmount** (`Rva00SlotFloat2Copy` return) and **getPendingPlaceSourceObjectID**
  (`int` return): the return types need respelling first.
- **slot87**: the row is the free stdcall `?bfmeGoBLD@@YGXPAX@Z`.
- **slot92 and slot96**: see LINK-181.
