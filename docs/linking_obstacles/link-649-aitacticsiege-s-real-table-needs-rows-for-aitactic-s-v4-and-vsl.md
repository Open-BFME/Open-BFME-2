### LINK-649: AITacticSiege's real table needs rows for AITactic's v4 and vslot08 before its TU can merge
Status: Open. Updated: 2026-11-08; inspected revision: `142b6e389c`.
Evidence / affected units: `Code/GameEngine/Source/Common/AITacticSiege.cpp`, `Rva005DC87BXfer.cpp`, `Rva005DC73CDerived.cpp`, `Code/GameEngine/Include/Common/AITactic.h`.

*Target facts.* Retail's table at 0x00876808 has 11 slots: 0 ??_G 0x005DC886; 1, 2, 6, 7, 9 `__purecall`; 3
initializeTeamTemplate 0x004ECE61; 4 0x000910FB (`xor eax,eax; inc eax; ret`); 5 xfer 0x005DC903; 8 0x004EDDAA; 10
0x0050B5C6 (`mov al,1; ret`).

*Tree facts.* AITacticSiege.cpp's private AITacticOffensive is a copy of a registered class and emits a 1-slot table.
Replacing it with the canonical header emits all 11 slots, 4/4 rows exact, and slots 1-3, 5, 6, 7 and 9 line up by
ledger address. `tools/tu_skeleton.py --merge` then refuses the TU: "links at the census; the merged object would not:
unresolved ?v4@AITactic@@UAEIXZ; unresolved ?vslot08@AITactic@@UAEXXZ; comdat ??_7AITacticSiege@@6B@ (first)".

- AITactic.h declares both as virtual and out of line. No row has either name: 0x004EDDAA is rowed as the non-virtual
  `?rva004EDDAA@AITactic@@QAEXXZ`, and 0x000910FB is a shared fold rowed under other names.
- The canonical AITacticOffensive::slot10 returns false; retail's slot 10 in this table returns true. AITacticSiege
  needs its own override.
- Rva005DC73CDerived.cpp owns ~AITacticSiege and declares the class too; the `comdat (first)` finding names the table.

*Inference, not proven.* v4 and vslot08 are the same two names any tactic unit's real table would need, so fixing them
in AITactic.h (16 sources include it or AITacticOffensive.h) should clear more than this TU.

Completed: both units adopt object.h (`AITacticSiege.cpp` in the nine-unit batch; `Rva005DC87BXfer.cpp` on its own, also
dropping /O1 /G7 /arch:SSE, which it did not need). The TU's move to the canonical header was reverted: it would lose a
unit that links today.
Remaining / next check: give v4 and vslot08 real rows or rename them onto the owners, settle the table's COMDAT with
Rva005DC73CDerived.cpp, then rerun `tu_skeleton.py --merge Code/GameEngine/Source/Common/AITacticSiege.cpp --dry-run`.
Clearance: none. Census confirmation: not applicable; nothing here changed a link result.
