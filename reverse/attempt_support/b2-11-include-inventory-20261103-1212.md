# Repair include inventory in PathfinderIsValidHordeMemberRegularMovement

Source `Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderIsValidHordeMemberRegularMovement.cpp`. Remove only the redundant whole-checkout `/I.` search
root and anchor existing root-spelled includes relative to this source. Every
resolved dependency path and digest is unchanged. Optimization, ABI switches,
headers, hatches, aliases, native pins, ledgers and baselines are unchanged.

Native normal/frozen/EH checks pass for 1 existing function/EH rows.
All 4 retained external code bodies and relocations, named
TU-local code and every non-debug section including linker directives remain
exact. No external code is added or removed. This is compiler-input receipt
maintenance, not new native coverage or a runtime/RAM/crash/FPS improvement.

Header mappings:

- `Code/GameEngine/Source/GameLogic/AI/PathfinderPositionValue.h` -> `../AI/PathfinderPositionValue.h` (same resolved file).
- `Code/Libraries/Include/Lib/ICoord2D.h` -> `../../../../Libraries/Include/Lib/ICoord2D.h` (same resolved file).

Final native receipt stability and bounded link-preview results are in the batch evidence.
