# TU evidence: 0x005CC4B3..0x005CCACA (blocked)

Date 2026-11-04, seat claudec, model claude-opus-5-5. Served by
`next_work.py --claim` as tier tu-evidence, check `no-signal`: 20 rows in 16
sources, below `0x005CC49A` (icoord.cpp, ICoord3D.cpp proposed by N), above
`0x005CCB37` (font3d.cpp, approved by S), 0x69D bytes apart.

## Target facts

- `tools/tu_evidence.py --source Code/GameEngine/Source/Common/Rva005CC4B3Permuted.cpp`
  prints only its header: no E/P/T/R/V/I signal reaches the run.
- game.dat carries no `__FILE__` path for these files:
  `reverse/worldbuilder_source_paths.csv` marks
  `LivingWorld/InGameUI/StrategicInGameUI*.cpp` `present_in_game_dat=no`.
- The run's callers and WorldBuilder pairings are Strategic (Living World) UI:
  region details panel (`0x005CC543`, `0x005CC698`, `0x005CC81F`) and checklist
  item (`0x005CCA0B`, `0x005CCA57`); the checklist continues past the upper
  bracket (`0x005CCCB4..0x005CCD3E`, `0x005CCE1B`, `0x005CD049` carry W leads to
  StrategicInGameUIChecklist.cpp).
- `tu_map.py --validate`: W anchors are on (170/170).

## Why no current signal can place the run

- Z/S: Zero Hour has no StrategicInGameUI classes.
- W anchors only where it names the path of a row's own hint, and never on a
  row named from the lead. The named rows (`0x005CC81F` CreatePage,
  `0x005CCA0B`/`0x005CCA57` ChecklistItem::Impl) cite WorldBuilder in their
  notes (Wself). Independently, `tu_map.demangle` returns no class for nested
  scopes (`?CreatePage@Impl@RegionDetailsPanel@StrategicInGameUI@@...` gives
  `(None, ...)`), so such rows get no N hint at all. The other rows are
  address-named placeholders (no N either).
- T needs approved F/Z/L brackets within GAP; there are none.

## Upper bracket is a mis-named row (donor name unsupported by target)

`0x005CCB37` (7 B) is rowed as `?Peek_Texture@Font3DInstanceClass@@QAEPAVTextureClass@@XZ`
in `Code/Libraries/Source/WWVegas/WW3D2/render2d.cpp`, placed by "masked
whole-.text search - single hit"; its S anchor approves it into font3d.cpp.
Target facts against that name:

- Body `mov eax,[ecx+8]; mov eax,[eax+0xC]; ret`. Its neighbours
  `0x005CCB30` (`mov eax,[ecx+8]; add eax,8; ret`) and `0x005CCB3E`
  (`mov eax,[ecx+8]; mov al,[eax+0x21]; ret`) read the same `+8` pointer:
  one accessor family of one class.
- Its only image callers (`tools/callers_of.py 0x005CCB37`) are `0x005CD737`,
  `0x005CD762`, `0x005CD78B`, each of which first calls `0x005CCB3E` on the same
  object and then compares this getter's result with `1` (a type or state
  code, not a texture pointer).
- No render2d/font caller reaches it.

So the byte shape matches ZH's inline `FontData->Peek_Texture()` but the name is
not supported; the font3d.cpp approval of `0x005CCB37` is a false S anchor.
Next step for the naming lane: give `0x005CCB37` an address-derived name in the
`0x005CCB30`/`0x005CCB3E` family (and update the three callers' local
`Font3DInstanceClass` views). That alone gives the run no TU.

## What would unblock it

An independent anchor for StrategicInGameUIRegionDetailsPanel.cpp /
StrategicInGameUIChecklist.cpp: a promoted structural signal reaching these
rows, or a tu_map hint for nested-scope names (outer scope + class, e.g.
`StrategicInGameUI::RegionDetailsPanel` -> `StrategicInGameUIRegionDetailsPanel.cpp`)
validated at the W/N gates in a Verifier-Change commit. Never assert the TU by
hand.
