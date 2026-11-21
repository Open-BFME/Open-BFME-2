# 0x00814E5C `??_7Rva00355D66@@6B@` in ProgressIndicator.cpp (blocked on naming)

Target facts (retail):
- 0x00814E5C (VA 0xC14E5C) is a 6-slot table: [0x355FDD ??_G, 0x355FF9, 0x3B810
  __purecall x3, 0x50B5C6 (mov al,1; ret)].
- Ctor 0x355D4E (ProgressIndicator.cpp) and dtor 0x355D66 (Rva00355D66Dtor.cpp) install
  it. The dtor destroys +8 through TheWindowManager slot 0x8C (winDestroy) when non-null,
  then clears +8.
- Slot 1 (0x355FF9) is already rowed `?update@LoadScreen@@UAEXH@Z` in
  `Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp`. That unit's `ShellGameLoadScreen`
  calls it non-virtually. ShellGameLoadScreen's table 0x00814E74 is the table that
  `Rva00355DC5` (a subclass of Rva00355D66) installs.
- AptLoadScreen (`AptLoadScreen.h`) derives from Rva00355D66.

Donor fact: BFME 1 `LoadScreen::~LoadScreen` has the same body as 0x355D66
(reference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/LoadScreen.cpp:162). That
donor body is present-unmatched in BFME 1, so `bfme1_sweep.py` has no placement for it.

Inference (not a name yet): Rva00355D66 is LoadScreen. LoadScreen.cpp's private
`class LoadScreen` view is a twin of it.

Blockers:
- Table slot 1 can only name 0x355FF9's row if the emitting units spell the class
  `LoadScreen`.
- Rowing `?update@Rva00355D66@@...` would rename a readable row to a placeholder. An ICF
  row would claim a fold that does not exist.
- `rename.py class --name Rva00355D66 --new LoadScreen --basis canonical:bfme1` is refused:
  name_evidence has no bfme1-body candidate.
- `--fold` is refused: T names no `LoadScreen`.

Next: get an inferred approval for Rva00355D66 -> LoadScreen through name_lane, then
`rename.py class`. Once renamed, both emitting units take the canonical header plus
`virtual void update(int)` (slot 1). Slot 5 is an ICF fold at 0x50B5C6
(fold-proof=Code/GameEngine/Source/Common/VtableConstantPredicates.cpp). Slots 2-4 stay
pure.
