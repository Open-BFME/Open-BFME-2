# Chat-window class family (tables 0x00C6FFFC .. 0x00C75B5C): state and next steps (2026-11-13)

First served as vtable-bridge `??_7Rva005AFE3FBase@@6B@` in
Code/GameEngine/Source/GameClient/GUI/ChatWindowsInGame.cpp.

## Classes as the tree now spells them

| Retail table | Slots | Class | Installers | Compiled table vs retail |
|---|---|---|---|---|
| 0x00C6FFFC | 2 | `Rva005AFE3FBase` (listener, two pure slots) | inline dtor, twin at 0x0057C03B | agrees |
| 0x00C728B8 | 6 | `Rva005AFE3F` (base, 0x24 bytes) | ctor 0x005AFE86, dtor 0x005AFE3F | agrees |
| 0x00C7287C | 6 | `Rva005AFA03` (in-game) | ctor 0x005AF9EF, dtor 0x005AFA03 | slots 3, 4 differ |
| 0x00C75AC4 | 7 | `Rva005D50D8` (LAN) | ctor 0x005D5095, dtor 0x005D50D8 | agrees |
| 0x00C75AE0 | 7 | `Rva005D50C4` (LAN leaf) | ctor 0x005D50C4 | slot 3 differs |
| 0x00C75AFC | 7 | `Rva005D50E3` (LAN leaf) | ctor 0x005D50E3 | slot 3 differs |
| 0x00C75B2C | 6 | `Rva005D583C` (online) | ctor 0x005D57D3, dtor 0x005D583C | agrees |
| 0x00C75B44 | 6 | `Rva005D5802` (online room leaf) | ctor 0x005D5802 | hand-written array, matched data row |
| 0x00C75B5C | 6 | `Rva005D5828` (online buddy leaf) | ctor 0x005D5828 | hand-written array, matched data row |

"Agrees" is every slot of the compiled `??_7` naming the row at retail's word, with the compiled
`??_E` standing where retail holds the class's own `??_G`. Measured per object with a scratch
script over `reloc_ledger.parse_coff` and game.dat's words; not a repository tool.

The class text (listener base, base, and each derived class) is repeated privately in
SingleBaseCtors.cpp, Rva005AFE3FDerived.cpp, Rva005AFE86Ctor.cpp, VslotSmallBodiesAE.cpp,
ChatWindowsInGame.cpp, StrategicInGameUIHeroComparator.cpp and Rva005D5F86ChatPlayerTooltip.cpp.
Rva005D583CCtor.cpp still uses data-only views and stores its three tables by hand.

## Landed

- 56940e1d57 and before: the base (one layout in four units, fold of `Rva005AFE86`, slot 1's
  0x005AFCEC, twins at 0x0047A69C and 0x0057C03B).
- LAN: fold `Rva005D5095Base` into `Rva005D50D8`; 0x005D50AD is `vslot04`; the leaves declare
  slot 6 inline (twins at 0x0047A699 and 0x0050B5C6).
- Online: fold `Rva005D57D3` into `Rva005D583C`; 0x005D57EB is `vslot04`, 0x005D5F86 is `vslot05`.
- In-game: fold `Rva005AF9EF` into `Rva005AFA03`.

`tools/link_check.py` over the fourteen units that spell the family: 14 of 14 link,
LINKED 10,558 -> 10,574 bytes.

## What is left, and what refuses it

1. **LAN leaves, slot 3.** 0x005D56D0 and 0x005D574C are rowed
   `?rva005D56D0@ChatWindowsLan@@QAE_NXZ` and `?rva005D574C@ChatWindowsLan@@QAE_NXZ`, but they
   are the two leaves' overrides of the base's pure `PopulatePlayerList` (0x00C75AE0 and
   0x00C75AFC slot 3). `rename.py function --to-class Rva005D50C4 --new PopulatePlayerList`
   refuses: "class ChatWindowsLan is a readable name: --to-class moves only a placeholder class's
   member". It is a naming-lane respell. A prepared ChatWindowsLan.cpp built in this session
   declared the hierarchy there and called the helpers (`GetLobbyPlayers`,
   `PopulatePlayerList(vector *)`, `rva005D5648`) through a `ChatWindowsLan *` cast; it was never
   byte-gated because the plan was refused first. Inference: `ChatWindowsLan` is the middle class
   `Rva005D50D8` (both leaves call its helpers on the same receiver).
2. **LAN leaves, slot 2.** Retail holds the middle class's `??_G` 0x005D5103 in both leaf tables.
   Compiled, the leaf `??_G` calls an out-of-line `??1<leaf>` and fails the twin check
   (`add_match --icf-owner`: unresolved call `??1Rva005D50C4@@UAE@XZ`). Inference: retail's
   middle destructor 0x005D50D8 is an inline function's out-of-line copy, so the leaves' implicit
   destructors fold onto it. Making it inline here moves its row out of Rva005AFE3FDerived.cpp,
   and `tu_map.csv` has no approved unit for 0x005D5095..0x005D5103. The same holds for the
   online leaves (0x005D58A8 in all three online tables).
3. **Online leaves.** `class --fold Rva005D5802 --into ChatWindowsOnlineRoom` refuses: nothing
   names `??_7ChatWindowsOnlineRoom@@6B@` at 0x00C75B44 (the unit stores a hand-written array).
   Compiled tables for the two leaves need the leaf classes to carry the names their slot-3 rows
   already have (`?PopulatePlayerList@ChatWindowsOnlineRoom@@UAE_NXZ`, `...OnlineBuddy...`); until
   then the hand-written arrays are the correct ones and should stay.
4. **In-game class.** Slot 3 is `?PopulatePlayerList@ChatWindowsInGame@@UAE_NXZ` and
   `class --fold Rva005AFA03 --into ChatWindowsInGame` refuses for the same reason as 3. Slot 4,
   0x005AFA0E, is rowed `?rva005AFA0E@Rva005AFA0E@@QAEXHH@Z`; the base's slot 4 is
   `bool (const UnicodeString &, GameWindow *)` as the LAN and online bodies have it, and
   `--to-class` keeps parameters and return type, so that row needs a new spelling first.
5. **Names.** The canonical header ChatWindowsInGame.h declares 0x005AFCB4, 0x005AFDC5,
   0x005B000C and 0x005B00C8, which lie in the base's address range, and ChatWindowsOnlineRoom.cpp
   derives `ChatWindowsOnline` from `ChatWindowsInGame`: other units use that name for the class
   this file calls `Rva005AFE3F`. Slot 5 carries the agreed name `showPlayerTooltip`
   (agree:nl-293eeb80802e) only as a comment at its definition; the base declares `vslot05`, and
   renaming the base's twin row at 0x0047A69C by the inferred route refuses (a pin already names
   the address).
6. Funclet `uw_0079edb2` (0x0079EDB2) can be repointed to the base constructor's `$L` label.

Not checked: the real link; whether the bridge queue drops 0x00C6FFFC, 0x00C728B8, 0x00C75AC4 and
0x00C75B2C at the next published real link.
