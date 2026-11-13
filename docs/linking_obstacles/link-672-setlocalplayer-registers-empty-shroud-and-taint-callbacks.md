### LINK-672: setLocalPlayer registers empty shroud and taint callbacks
Status: Repair landed / awaiting verification (one unit). Updated: 2026-11-13 (seat halilkkaya-bt3); inspected revision:
`d605b7a1a05` (source) and the CI diagnostic image at `c3cee37c76d` (linked image).

Evidence / affected units:
- `Code/GameEngine/Source/Common/RTS/PlayerList.cpp`, `?setLocalPlayer@PlayerList@@QAEXPAVPlayer@@@Z` (0x002A7B34,
  93 bytes). Target facts: retail pushes 0x006D7AE0 at 0x002A7B6B and 0x006D7B18 at 0x002A7B84, the addresses of
  `?rva002D7AE0@@YAXHHH@Z` and `?rva002D7B18@@YAXHHH@Z` (both rowed in `Code/GameEngine/Source/Common/System/Radar.cpp`),
  and hands them to TheShroudManager's thunk 0x00739730 (which stores the player index at +0x64 and the callback at
  +0x6C through 0x0073B280) and to TheTaintManager's 0x006C0800. 0x002D7AE0 forwards a cell to
  `TheDisplay` slot +0x130 (`W3DDisplay::rva00044FF2`, the only caller of `W3DShroud::setShroudLevel` 0x000731F4
  besides `interpolateFogLevels`) and `TheRadar` slot +0x24 (`W3DRadar::setShroudLevel`). The other registration,
  `?rva002A8306@PlayerList@@QAEX_N@Z` (observer switching, `PlayerList_getNthPlayer.cpp`), pushes the same two
  functions. No other retail dword holds 0x006D7AE0 or 0x006D7B18, and a byte search of retail's `.text` for
  `call [reg+0x130]` within 40 bytes of a `TheDisplay` (0x00DFE9D8) load finds only 0x002D7AE0.
- The unit pushed the addresses of two empty file-level functions it defined itself,
  `?Rva002D7AE0LocalPlayerShroudCallback@@YAXXZ` and `?Rva002D7B18LocalPlayerTaintCallback@@YAXXZ`. A `push imm32`
  is the same bytes whatever its DIR32 names, so the row byte-matched. In the linked image at `c3cee37c76d` these are
  one `ret` each (0x0214E0E6 and 0x0214E0E7), and `setLocalPlayer` registers them. The callee-binding scan
  (`reverse/attempt_support/callee-binding-scan-20261108/`, order 3881, `other-body`) already listed both pairs.
- Consequence (inferred from the code path): the shroud manager's cell callback for the local player does nothing, so `W3DShroud::setShroudLevel`
  and `W3DRadar::setShroudLevel` are never called after `setLocalPlayer`; the terrain shroud stays fully shrouded
  (black terrain under every object) and the radar's shroud layer is never cleared (no terrain lines, no icons). The
  taint cell callback is dead the same way.

Completed: "PlayerList::setLocalPlayer: register Radar.cpp's shroud and taint callbacks, not empty stubs" (this
commit). The unit now declares `rva002D7AE0` / `rva002D7B18` (as `PlayerList_getNthPlayer.cpp` does) and pushes
their addresses; the two empty functions are gone. `./build.sh` of the file 19/19 exact; the object names
`?rva002D7AE0@@YAXHHH@Z` and `?rva002D7B18@@YAXHHH@Z` and no longer defines the stubs; `link_check` LINKS,
PlayerList.cpp 718 -> 718 and Radar.cpp 5,415 -> 5,415 bytes.

Remaining / next check: in the next diagnostic image from a revision with this commit, `setLocalPlayer`'s two pushes
should resolve to `?rva002D7AE0@@YAXHHH@Z` / `?rva002D7B18@@YAXHHH@Z` in `radar.obj`. Other `other-body` rows of the
same scan are unrelated to this unit and still need their own checks.

Clearance: pending the next image built from a revision with this commit.
Census confirmation: not claimed (the census links under `/FORCE` and never loads an image).
