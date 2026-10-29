# Army hero constructor link preview

Inspected revision `9df8832b7d` on 2026-10-29. The default picker claimed
0x005E3C6F and `ArmyHeroIconCtor.cpp`. The file's frozen-file check passes
with six matched rows. The published index fetch retained the local index at
`840db2d676` (2026-10-28 20:44).

`python3 tools/link_check.py Code/GameEngine/Source/GameClient/LivingWorld/InGameUI/ArmyHeroIconCtor.cpp`
returns exit 1: zero of 130 authored bytes link. Ten unresolved references
are the `StrategicInGameUI::ArmyHeroIcon` destructor, the anonymous
`HeroDetailsPortion` destructor and its `slot1`, `slot5`, `rva005F3FF4` and
`rva005F3F6B` methods, and `Rva005F4179`'s `DoUpdate`, `rva005F4254`,
`rva005F3FF4` and `rva005F3F6B` methods.

The lifetime owner `Common/Rva005F422CDtor.cpp` still uses `Rva005F422C`
for the hero and a distinct details class, while this constructor uses the
real hero name and an anonymous details emitter. The existing LINK-086
handoff identifies the native eight-slot tables and rowed providers. A
bounded declaration change would leave the class identities and hidden-result
signatures inconsistent, so no previous failed trial was repeated and no
source changes were made. Reconcile the lifetime and constructor views and
verify all emitted tables and thunks together before rechecking the units.
This preview does not establish census clearance.
