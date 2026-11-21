# 0x007C8298 `??_7Rva0098477@@6B@` in SubsystemDerivedDtors.cpp (blocked)

Target facts (retail):
- 0x007C8298 (VA 0xBC8298) is a 15-slot table: SubsystemInterface's 14 slots and one
  more. It holds [0x984B2 ??_G, 0xB3FD0 init, 0x1B5384 loadIniFilesFromLegend, 0xB3FD0,
  0x5CB9FF, 0x47A699, 0xD43D0, 0x47A69C, 0xB3FD0, 0x318A95 (slot 9 = reset), 0xB3FD0
  (update), 0x5CB9FF, 0xB3FD0, 0x47A69C, 0x318A87 (slot 14)].
- Ctor 0x318AA5 (Rva0098477Ctor.cpp) stores it. Derived ctor 0x984CE (Rva00984EF,
  OpaqueSingleInheritanceDtors.cpp) calls 0x318AA5, then stores 0xBC82D4. That table
  0x007C82D4 holds the same slots 1-14 (reset 0x318A95, slot 14 0x318A87).
- 0x4C662 is slot 48 (+0xC0) of table 0x007C4738. Slot 46 of that table is the named
  `W3DGameClient::createSnowManager` 0x4C5F8. 0x4C662 news 0x1C bytes and calls
  0x984CE.
- `parseCloudBreakEffectDefinition` 0x318ABB tail-calls slot 14 of
  `TheCloudBreakEffectManager` (0xA01CEC). 0x318A87 copies the sunbeam global 0xA01CF4
  into +0x0C, the AsciiString that dtor 0x98477 tears down.

Inference (not yet a name): GameClient's +0xC0 is `createCloudBreakEffectManager`
(GameClientDrawableTOC.cpp:396), so Rva0098477 is CloudBreakEffectManager and Rva00984EF is
its W3D subclass. Slot 14 is the `loadSunbeamObject`-style hook that the parser calls.

Sibling tables in the same unit have the same shape. Each overrides reset and adds a
slot 14:
- Rva00985E4 0x007C8318: init 0x30ADE8, reset 0x30AEA6, slot 14 0x30AE42.
- Rva009519B 0x007C81A8: reset 0x2150BE, slot 14 0x214F14.

Blocker: defining `BFME_SUBSYSTEM_SLOTS` (as in 4495e84e6c) only gives the base slots.
Slot 9 must be spelled `reset` and slot 14 needs a name. The rows 0x318A95
`?rva00318A95@Rva00318A95@@QAEXXZ` and 0x318A87 `?loadSunbeamObject@Rva00318A87@@QAEXXZ`
(Rva00318ABBFieldParse.cpp) are under placeholder classes. `rename.py function --to-class
Rva0098477` keeps a placeholder identifier only, and `reset` or any other name needs a
name_lane slot approval on a class registered in canonical_classes.csv. Rva0098477 is not
registered. It has four private views (SubsystemDerivedDtors, Rva0098477Ctor with an
`/alternatename` hatch, OpaqueSingleInheritanceDtors, Rva0004C662Factory).

Next:
1. Register a canonical header for Rva0098477 (and Rva00984EF) with the 14
   SubsystemInterface slots plus slot 14, and adopt it in the four views.
2. Vote the slot names (reset; slot 14) and move 0x318A95 and 0x318A87 with
   `--to-class Rva0098477 --also`.
3. Drop the `/alternatename` in Rva0098477Ctor.cpp once the header's table is emitted.
