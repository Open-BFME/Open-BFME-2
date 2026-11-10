# The CAT_WIND default particle module (tables 0x00C1B5E0 / 0x00C1B5D0), 2026-11-10

Served as `??_7Rva003A59C3@@6B@` (0x0081B5D0, link-cycle repair,
unbounded-retail-row). Nothing in `Code/` changed: the one source trial that
byte-matched loses the unit's link, so it is banked here instead.

## Trial 1: retail's slot shape in the constructor unit (byte-exact, not landed)

[class-shape-trial.cpp.txt](class-shape-trial.cpp.txt) is
`Rva003A59C3Ctor.cpp` with retail's slot shape: a four-slot abstract module
base, a one-slot +8 base, and the info as the shim `Snapshot` with the
capitalized slots (no private class with a hand-written vptr restore). Its
object emits four-slot tables for +0 and +0x0C and a one-slot table for +8
(today: three, two and three), with both adjustor thunks. `./build.sh`: 4/4
rows match (constructor, EH handler, funclet, folded info destructor), EH
EXACT.

Not landed: `link_check` on it reads `0 of 1 link cleanly; LINKED 143 -> 0
bytes`, with seven unresolved names (`??1Rva003A59C3@@UAE@XZ`,
`?update@`, `?DoXfer@`, `?GetSnapshotName@Rva003A59C3@@...`, and the info's
`?LoadPostProcess@`, `?GetSnapshotName@`, `?DoXfer@Rva003A59C3B3@@...`).
Today's unit links because its three-slot tables hold inline empty bodies.
The shape can land only together with the slot rows below.

## Target facts (retail bytes)

- Constructor 0x003A59C3 calls the base constructor 0x0055EFE1, inlines the
  info constructor (transient table VA 0x00C1B568, Real at +0x10), then
  stores VA 0x00C1B5E0 (+0), 0x00C1C780 (+8), 0x00C1B5D0 (+0x0C).
- 0x00C1B5E0: 0x003AE270 (deleting destructor), 0x003A5A58 (708 bytes),
  `__purecall`, 0x003A57A9 (DoXfer).
- 0x00C1B5D0: 0x003A5A48 (`sub ecx,0Ch; jmp 0x003AE270`), 0x000B3FD0 (one
  `ret`), 0x003A5A42 (returns the literal `DefaultParticleModule<CAT_WIND>`),
  0x003A5A50 (`sub ecx,0Ch; jmp 0x003A57A9`).
- 0x00C1B568 (the info's own table): 0x004A10FD, 0x000B3FD0, 0x003A5784
  (returns `ParticleWindModuleInfo`), 0x003A578A.
- 0x00C1C780 is one `__purecall` word. 0x00C1D2C0 (the base constructor's
  table) is 0x003AE16E and three `__purecall` words. 0x00C1B320 is
  0x003A53A7 and one `__purecall` word.
- The factory 0x003AD03B runs 0x003A59C3 and then stores VA 0x00C1CED8,
  0x00C1BFB4 and 0x00C1CEC8. 0x00C1CED8 is 0x003AE270, 0x003A5A58,
  0x003ADFFA (clone), 0x003A57A9.
- The constructor has two unwind funclets. 0x00781C16 is
  `mov ecx,[ebp-10h]; jmp 0x003A583E`; 0x00781C1E is
  `mov ecx,[ebp-10h]; add ecx,0Ch; jmp 0x0049B47C`.
- 0x003A583E (24 bytes) stores 0x00C1C780 at +8 and 0x00C1B320 at +0.
  0x003ADFB2 (41 bytes) stores 0x00BBB554 at +0x0C, then the same two.
- The assert path in the constructor is `...\FXParticleSystem\fxpswindmodule.cpp`,
  line 404.

## Structural inferences (not proven names)

- 0x003A59C3 constructs an abstract class: its slot 2 is pure and only the
  factory's derived class fills it (clone). So the class at 0x00C1B5E0 is the
  base of the class at 0x00C1CED8.
- 0x003A5A42, 0x003A5A48, 0x003A5A50 and 0x003A5A58 follow the constructor
  directly, so the name getter, both adjustors and the 708-byte body are this
  class's own members. 0x003AE270 and 0x003ADFB2 sit in the shared region and
  are folds with same-layout classes.
- The primary base chain is root (table 0x00C1B320, two slots: destructor and
  one pure) then a class adding two pure slots (table 0x00C1D2C0). The base's
  destructor is the out-of-line 0x003A583E; funclet 0x00781C16 calls it. That
  funclet is still rowed as `uw_00781c16` in `Code/gen_small/uw_gen_011.cpp`
  with no parent.
- The getter's literal reads as `DefaultParticleModule<CAT_WIND>`; the ledger
  already uses `FXParticleSystem::DefaultParticleModule<N>` as a template
  argument of exported `ModuleTag` names, and category 6's template writes
  through `WindModuleTemplateWriteINI.cpp`. A lead for the real name, not
  evidence graded by `name_evidence.py`.

## What still keeps the tables bridged

The compiled slots name this unit's class; the rows at retail's addresses are
spelled under other placeholders:

| slot target | compiled name | row today |
| --- | --- | --- |
| 0x003AE270 | `??_GRva003A59C3@@UAEPAXI@Z` | `??_GRva003ADFB2@@UAEPAXI@Z` (fold) |
| 0x003A5A48 | `??_ERva003A59C3@@WM@AEPAXI@Z` | `??_ERva003ADFB2@@WM@AEPAXI@Z` |
| 0x003A5A58 | `?update@Rva003A59C3@@UAEXXZ` | `?rva003A5A58@Rva003A5A58@@UAEXXZ` |
| 0x003A57A9 | `?DoXfer@Rva003A59C3@@UAEXAAVXfer@@@Z` | `?DoXfer@Rva003A57A9@@UAEXAAVXfer@@@Z` |
| 0x003A5A50 | `?DoXfer@Rva003A59C3@@WM@AEXAAVXfer@@@Z` | `?DoXfer@Rva003A57A9@@WM@AEXAAVXfer@@@Z` |
| 0x003A5A42 | `?GetSnapshotName@Rva003A59C3@@UAEPBDXZ` | `?Rva003A5A42Get@@YAHXZ` |
| 0x000B3FD0 | `?LoadPostProcess@Rva003A59C3B3@@UAEXXZ` | no row under this name |

Trial 2 and 3, not landed:

- Pointing `data_rows.csv`'s two one-byte stand-ins (`_Rva003AE03D_v0C`,
  `_Rva003AE03D_v0`, owner `Rva003AE03DCopyCtor.cpp`) at the compiler tables
  and storing those tables in the copy constructor: the copy constructor still
  matches, and `Data rows` then refuses both tables at slot 0 (`... has no
  retail address in the ledgers`). So the stand-ins go only after the slot
  rows exist. The data-row check is a local proxy for the pass test.
- `rename.py function --rva 0x003A5A58 --to-class Rva003A59C3 --new update
  --dry-run` refuses: 0x003A5A58 is also slot 1 of 0x00C1CED8, which the
  ledger gives to `Rva003AE017`, a class no view derives from `Rva003A59C3`.

## Next step

One header for the family, adopted by every unit that names it: the root,
the four-slot module base (today `Rva00563FE1`, `Rva0055EFE1`,
`Rva003AE13C`, `Rva003ADEBF` views), the info (`Rva003AE07D`,
`Rva003A578A`, `Rva003A5784Named`), this class (`Rva003A59C3`,
`Rva003AE03D`, `Rva003A57A9`, `Rva003A5A58`) and the factory's derived class
(`Rva003AE017`, `Rva003AD03BModule`). With the derived class declared on this
one, `rename.py --to-class ... --also 0x003A57A9=DoXfer` can move the slots
together; the two fold rows and the base destructor's funclet follow, then
the stand-ins in `Rva003AE03DCopyCtor.cpp` and `Rva003AE017CopyCtor.cpp`.
`FXModuleTemplateBase.h` (LINK-636) is the model on the template side.
