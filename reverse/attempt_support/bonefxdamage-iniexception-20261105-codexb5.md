# BoneFXDamage shared INIException adoption

Inspected source revision: `5eb11e1e87`; 2026-11-05, seat codexb5.

The picker served the stale exit-link BoneFXDamage entry. Prior repair
`a0e226ee89` already removed the Zero Hour crc slot and supplied the BFME2
snapshot overrides. This pass replaces only the remaining private INIException
declaration with `Common/INI/FieldParse.h`; the shared declaration describes
the same eight-byte exception. No new names, pins, rows or hatches are needed.

Verification:

- `header_adopt_lane.py adopt --class INIException --header
  Code/GameEngine/Include/Common/INI/FieldParse.h
  Code/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp --apply`: PASS.
- `./build.sh Code/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp`:
  9/9 functions exact, both renumbered funclets verified through parent EH
  data, all three string references verified.
- `find_declared_unmatched.py` on the unit: all defined functions matched.
- `header_adopt_lane.py accept --class INIException` on the unit: PASS,
  retired its one header-queue row through the supported acceptance path.
- Published index fetched: census 2026-11-05 05:17, `c95fcfcfcd` (same as local).
  Ordinary preview of BoneFXDamage alone initially misses three providers
  added after that census: its destructor, DamageModule::loadPostProcess and
  DamageModule::xfer. Checking their current source units together resolves
  all three; this is provider freshness, not a fresh source regression.
- `link_check.py Code/GameEngine/Source/Common/Rva004B96CCDerived.cpp
  Code/GameEngine/Source/GameLogic/Object/Damage/DamageModule.cpp
  Code/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp`: 3/3 LINKS,
  respectively 159 -> 159, 6 -> 38 and 0 -> 322 bytes; 165 -> 519 total.

LINK-113 is cleared for this three-unit current-object preview. These preview
figures verify the earlier repair and this adoption; they are not a census
gain or a new real-link run. The next scheduled census/real link must confirm
the stale blocker entry disappears.
