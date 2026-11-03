# Repair include inventory in FormationPreviewPoolLookup

Source `Code/GameEngine/Source/GameClient/FormationPreviewPoolLookup.cpp`. Remove only the redundant whole-checkout `/I.` search
root and anchor existing root-spelled includes relative to this source. Every
resolved dependency path and digest is unchanged. Optimization, ABI switches,
headers, hatches, aliases, native pins, ledgers and baselines are unchanged.

Native normal/frozen/EH checks pass for 4 existing function/EH rows.
All 40 retained external code bodies and relocations, named
TU-local code and every non-debug section including linker directives remain
exact. No external code is added or removed. This is compiler-input receipt
maintenance, not new native coverage or a runtime/RAM/crash/FPS improvement.

Header mappings:

- `reference/shims/bfme2_ascii/ascii_string.h` -> `../../../../reference/shims/bfme2_ascii/ascii_string.h` (same resolved file).

Final native receipt stability and bounded link-preview results are in the batch evidence.
