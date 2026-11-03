# AptSaveLoad TU approval: blocked by a split naming hint (2026-11-03)

Picker item: TU approval, `Code/GameEngine/Source/Common/AptSaveLoad.cpp` (18 proposed rows).
Inspected at master `dac9fa4d1e`. No source or ledger edit was made.

## Target facts

- `reverse/tu_map.csv` 0x00433D71..0x00437053: every row of class `AptSaveLoad` is `proposed`
  (0 approved). Two unanchored naming hints interleave in one address span:
  `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptSaveLoad.cpp` (most rows) and
  `Code/GameEngine/Source/Common/AptSaveLoad.cpp` (N hints from the files listed below).
  The GameClient span is wider than `tu_map.UNION_SPAN` (0x2000), so the two are not unioned,
  and each one's N rows break the other's provisional span (`tu_map.provisional`).
- `reverse/wb_name_leads.csv` names `C:\Projects\bfme2\Code\GameEngine\Source\GameClient\Gui\GUICallbacks\Apt\AptSaveLoad.cpp`
  for 0x00433FF3 (`AptSaveLoad::GetOpponentSlotData`), 0x00434160 (`AptSaveLoad::OpenScreen`),
  0x00435107, 0x004354F3, 0x0043566A, 0x00435DE7 and 0x00436259. Every one of those rows took
  its name from the lead (`tu_map.wb_self`), so W anchors none of them.

## The Common/ sources that carry the second hint

    Common/Rva00433FDDSet.cpp                   0x00433D96, 0x00433FDD
    Common/AptSaveLoad_GetOpponentSlotData.cpp  0x00433FF3
    Common/Rva004340ACMethod.cpp                0x004340AC
    Common/AptSaveLoad_OpenScreen.cpp           0x00434160
    Common/OpaqueScalarDeletingDtorsB10.cpp     0x004360A8, 0x00436197 (mixed file, ??_GAptSaveLoad)

## Structural measurement (in-memory, not committed)

`tu_map.build()` on a ledger copy with the first four sources re-keyed under
`GameClient/GUI/GUICallbacks/Apt/`: 102 code rows in 0x00433D71..0x00437053 become
`approved ... provisional` under the GameClient path (baseline 0); the two
OpaqueScalarDeletingDtorsB10.cpp rows become `displaced`.

## Why this was not applied

A cross-directory move is a TU-placement judgement (`tools/rename.py` file kind refuses it),
and AGENTS.md moves rows only into the address's approved unit, which none of these rows has.
The W leads are self-confirming here. Next step for a seat with authority over placement:
an F/Z/S anchor for any GameClient AptSaveLoad row, or a supported cross-directory move
for the four Common/ files the WB leads place in AptSaveLoad.cpp.
