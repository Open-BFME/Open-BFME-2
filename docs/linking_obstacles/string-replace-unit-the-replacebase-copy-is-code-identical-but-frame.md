### String replace unit: the replaceBase copy is code-identical but frame-different (2026-10-29)

`Code/Libraries/Source/STLport/Rva008312E0StringReplace.cpp` (rows 0x0002AE50 and
0x000284D0, 1,351 bytes) still does not link against index `85f6b7f40c`. Its only
finding is the COMDAT copy `?replaceBase@Rva008312E0String@@QAEAAV1@PAD000ABURva008312E0Tag@@@Z`:
`comdat ... (retail: not retail's body)` and `selected ... (the definition the
link keeps is not retail's)`. `reverse/symbols.csv` pins that name at 0x0002A610,
whose row is `?bfmeReplaceV24@BfmeStrV24@@QAEPAV1@PAD000H@Z` in `BfmeS1155.cpp`
(279 B, matched).

Target facts: retail 0x0002A610 (279 B) and the object's 249-byte copy disassemble
to the same 92 instructions in the same order. The only differences are the
prologue reservation (`sub esp, 0xd4` with `this` at `[ebp-0xd4]` in retail,
`0x44`/`[ebp-0x44]` here) and the call displacements to this unit's own copies.
The copy is not dead: `bfmeReplaceAliasedRange`'s grow path calls it out of line,
and retail's call at the same site targets 0x0002A610.

Trials, all reverted: removing the pin makes `link_check` LINKS (0 -> 1,351 B) but
the byte gate refuses, because the call then has no target (`e8 00 00 00 00`); the
pin is load-bearing for row 0x0002AE50. Spelling the helper as STLport's member
template (`??$replaceBase@PAD@...`) links but fails the byte gate: /Ob1 then
declines the inline and emits an unresolved call, and the caller's frame moves.
`__forceinline` removes the copy but changes the caller's frame 0x9c -> 0xa4, so
row 0x0002AE50 fails.

Remaining prerequisite: one name, one owner. Retail's body at 0x0002A610 is
already defined by `BfmeS1155.cpp`; this unit should declare `replaceBase` and
bind the call to that shared definition, which also retires the pin. The retract
must land in its own commit first: `tools/add_match.py --replace-rva 0x0002A610`
refuses because the existing row is a real claim, not scaffolding. A second commit
then adds `?replaceBase@Rva008312E0String@@...` at 0x0002A610 (the asm body there
already calls `Rva008312E0String::insertRange`, so the class view exists), drops
the pin and the local body, and keeps `call BfmeStrV24::bfmeEraseV24` in the asm
(pinned 0x00012150). Next check: that retract/re-add pair, then `build.sh` on both
units and `link_check` on the replace unit. No clearance or census gain is
claimed.
