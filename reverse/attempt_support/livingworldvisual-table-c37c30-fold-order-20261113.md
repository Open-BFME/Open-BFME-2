# Bridged table 0x00C37C30 (LivingWorldVisual): what its retirement needs, in order (2026-11-13)

Base ed8d9b80d2. Served as vtable-bridge `??_7Rva003FD14DBase@@6B@` in
Code/GameEngine/Source/Common/System/ParticleControlCtorFamily.cpp. No source changed.

## Target facts (game.dat words, names from functions.csv)

Table VA 0x00C37C30, 14 slots; the next table 0x00C37C68 starts at word 14.

| slot | RVA | current row |
|---|---|---|
| 0 | 0x003FD173 | `??_GRva003FCE38@@UAEPAXI@Z` |
| 1, 2 | 0x0047A69C | shared 3-byte `ret 4` (many names) |
| 3 | 0x003FB7DB | `?rva003FB7DB@Rva003FDCEB@@QAEXXZ` |
| 4 | 0x003FBB99 | `?rva003FBB99@Rva003FBA58@@QAEXXZ` |
| 5 | 0x003FBD9F | `?rva003FBD9F@Rva003FD14DBase@@QAEXXZ` |
| 6 | 0x003FCA58 | `?rva003FCA58@Rva003FD14DBase@@QAEXXZ` |
| 7 | 0x003FB6C5 | `?rva003FB6C5@Rva003FD14DBase@@QAEXABVVector3@@@Z` |
| 8 | 0x003FB602 | `?setHouseColor@LivingWorldVisual@@UAEXABH@Z` |
| 9 | 0x000B3FD0 | shared 1-byte `ret` |
| 10 | 0x003FBA58 | `?rva003FBA58@Rva003FBA58@@QAEXXZ` |
| 11 | 0x003FBAE4 | `?rva003FBAE4@Rva003FBA58@@QAEX_N@Z` |
| 12 | 0x003FCCC9 | `?rva003FCCC9@LivingWorldVisual@@QAEX_N@Z` (non-virtual spelling) |
| 13 | 0x0050B5C6 | shared 3-byte `mov al,1; ret` |

Constructor 0x003FC58C is rowed `??0Rva003FD14DBase@@QAE@H@Z`, destructor 0x003FCE38
`??1Rva003FCE38@@UAE@XZ`. The registered LivingWorldVisual.h already states both install this
table and declares the 14 slots (`vslot01`..`vslot13`, `setHouseColor`), so the class has three
names: Rva003FD14DBase (ctor, slots 5-7), Rva003FCE38 (destructor family, registered with an
8-byte generated header) and LivingWorldVisual (slots 8, 12 and the non-virtual members).
Derived table 0x00C37C68: constructor `??0Rva003FD14D@@QAE@H@Z` 0x003FD14D, slot 0
`??_GRva003FDC41` 0x003FDC25, slot 12 `?rva003FCD58@Rva003FDC41@@QAEXE@Z` 0x003FCD58.

## Tool verdicts (dry runs, nothing written)

- `rename.py class --fold Rva003FD14DBase --into LivingWorldVisual`: refused, the table is named
  only `??_7Rva003FCE38` / `??_7Rva003FD14DBase`; nothing ties LivingWorldVisual to it by name.
- `rename.py class --fold Rva003FD14DBase --into Rva003FCE38`: refused, Rva003FD14DBase scopes a
  frozen key in reverse/hatch_baseline.tsv: the `/alternatename:?vbfunc@Rva003FD14DBase@@UAEXXZ=
  ??_GRva003FDC41@@UAEPAXI@Z` in Code/GameEngine/Source/Common/Rva003FD14D.cpp.
- That alternatename also serves ParticleControlCtorFamily.cpp: its base view declares the same
  `virtual void vbfunc()` and defines the constructor, so its one-slot table resolves through the
  other unit's directive. Removing it in Rva003FD14D.cpp alone would unresolve this unit.
- `rename.py class --fold Rva003FDC41 --into Rva003FD14D`: refused (no own table); Rva003FDC41 is
  not destructor-only because of the method row 0x003FCD58. The other direction is refused because
  0x00C37C68 is named only `??_7Rva003FD14D`.

## Order that follows

1. One prepared transaction over every unit spelling Rva003FD14DBase (16 files spell it or
   Rva003FCE38): base views take a virtual destructor in place of `vbfunc`, which removes the
   alternatename and its hatch line; then fold Rva003FD14DBase into Rva003FCE38 (registered, so each
   unit comes `--prepared` on its header, whose contract must first grow from 8 bytes to the
   0xAC-byte layout the constructor needs).
2. Tie LivingWorldVisual to the table: `class --name Rva003FCE38 --new LivingWorldVisual
   --merge-existing` looks like the mode (registered placeholder, NEW already spelled); not tried.
3. Slot moves: `function --to-class` for 3, 4, 10, 11 (placeholder classes Rva003FDCEB and
   Rva003FBA58), `--virtual` for 5, 6, 7 and 12 (12 also needs the header's `vslot12`/`rva003FCCC9`
   pair reduced to one declaration), ICF twin rows with `fold-proof=` for 1, 2, 9, 13.
4. Derived classes after the base: move 0x003FCD58 into Rva003FD14D, then fold Rva003FDC41.

Not checked: the 16 units' builds under any of these edits; whether `--merge-existing` accepts
step 2; tables 0x00C37DA0 / 0x00C37DD8 / 0x00C744E8 of the other derived classes.
