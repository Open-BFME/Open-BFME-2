# Retire 3 verified AIUpdateInterface header queue entries

Base: `1bd4745e4fc91c2c53227b37fb54dca45925fdc1`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 28 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/Object/Update/BloodthirstyUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 14 |
| `Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderSidewaysAttack.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 5 |
| `Code/GameEngine/Source/GameLogic/Object/WeaponPrivateFireWeapon.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 9 |
