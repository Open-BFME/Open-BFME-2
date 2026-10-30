# dd-23 consolidation (split lane) handoff, 2026-10-29

Base: the verdicts below were measured in two sessions, on origin/master
`444c1da86f` (sandbox `bx_uamateky`) and `bcf2930e2d` (sandbox `bx_6v4q2rqp`,
which carries the two landed commits), both from snapshot
`bfme2-toolchain-20261029b`. Priority: split mixed files per
`build/fleet/merge_map/REPORT.md`, high-yield carves first.

Two splits landed (below). Every other attempt was refused by
`tools/tu_skeleton.py --split FILE --for TU --dry-run --no-claim` after the carve
itself succeeded (rows match beside the TU). The refusal causes are grouped so the
next seat does not repeat them.

## Landed

Both are the getter-sweep shape: a donor of independent leaf bodies, a few rows
approved for a class TU, and a large residual.

| commit | split | rows |
|---|---|---|
| `de8043c376` | `Common/Disp8ByteFieldGetters.cpp` -> `GameLogic/Object/Behavior/GettingBuiltBehavior.cpp` | 5 carved (`0x4543B6 0x4543BE 0x4543C2 0x4543C6 0x4543DF`), residual keeps 100; 125/125 rows across both sources byte-verify; link guard clean |
| `719290fce7` | `Common/Disp8PtrChaseDwordGetters.cpp` -> `Common/StdioStreambufBase.cpp` | 4 carved (`0x01CD60 0x01CD70 0x01CD90 0x01CDA0`), residual keeps 77; 87/87 rows byte-verify; two EH funclets renumbered and verified through their parent's EH data |

## Refused, with the tool's own verdict

| donor -> TU | rows | verdict |
|---|---|---|
| `Common/FamilyTailDtors1DBAC3.cpp` -> `GameClient/GUI/GameWindowTransitionsStyles.cpp` | 15 carved (residual 2) | `an escape-hatch count would grow (hatch_counters rule 3)`: the donor's 11 `alternatename` pins (`?slot1/?slot3..?slot7@Rva0035E00F`, `?slot4..?slot7@MainMenuMediumScaleUpTransition`) are copied with the carved bodies. Retire those pins first, or carve only the rows that do not carry them. |
| `GameClient/GUI/TransitionStyleSlotsBfme2.cpp` -> `GameWindowTransitionsStyles.cpp` | 8 carved (residual 3), 8/8 match beside TU | merge rejected `C2084: function 'Color GameMakeColor(UnsignedByte,...)' already has a body`; the TU defines `inline Int GameMakeColor(unsigned char,...)` at line 668. The donor's private helper (line 68) is copied. Reconcile the helper (use the TU's spelling or drop the donor's definition) before the split; `drawFillRect`/`drawOpenRect`/`drawImage` are donor-only and do not collide. |
| `Common/Rva00308AA4Notifiers.cpp` -> `GameLogic/Map/StandingWaterArea.cpp` | 6 carved (residual 19) | `the residual loses matched rows`: `0x005CB274` (shared helper). Four further rows refuse `2 definitions spell its name`. |
| `Common/Rva0036E346Count.cpp` -> `GameLogic/AI/AIGroup.cpp` | 5 carved (residual 1), 5/5 match beside TU | merge rejected `C2039: 'rva0036E2E2' is not a member of 'AIGroup'` and `C2065: 'm_head'`: the donor declares its own `class AIGroup` (line 69). Needs `tu_views` reconciliation of the donor's AIGroup view first. |
| `GameLogic/Object/Behavior/Rva00087A93DeletingDtor.cpp` -> `W3DDevice/GameClient/W3DView.cpp` | 2 carved (residual 2), 2/2 match | `TU path exists and holds rows the map does not place there (split it first): (unplaced) 1`. `W3DView.cpp` carries `0x0008553B ?setZoomToPos@ScreenMotionBlurFilter@@SAXPBUCoord3D@@@Z`, which `tu_map.csv` records as `displaced` (natural home `ScreenMotionBlurFilter.cpp`, no approved TU). Every split into `W3DView.cpp` refuses until that row is rehomed or its unit approved. |
| `W3DDevice/GameClient/W3DViewCameraModFinalZoomBfme.cpp` -> `W3DView.cpp` | 9 carved | `a namespace/extern "C" block defines something: carve not supported` — the file's named `namespace _STL` block (line 153) defines templates. |
| `W3DDevice/GameClient/W3DViewRotateCamera.cpp` -> `W3DView.cpp` | 6 carved, 6/6 match | `the residual loses matched rows`: `0x000854EC`, `0x000855D1` (the file-static `normAngle` used on both sides). |
| `WWVegas/WW3D2/meshmdl_sidehash.cpp` -> `meshmdl.cpp` | 2 carved, 13 `no definition spells its name` | `an escape-hatch count would grow (hatch_counters rule 3)`. The 13 refused rows are template/macro-emitted, so this donor is near-zero yield. |
| `Common/DispDwordFieldGetters.cpp` -> `GameClient/GUI/GameWindow.cpp` | 6 carved | `hatch_counters rule 3`: row `0x003140C8` carries three `/alternatename` pragmas (`?bfmeFindDEA/DEB/DEC@BfmeThingDE*)` that are copied into the TU. |
| `WWVegas/WW3D2/SurfaceByteSize.cpp` -> `surfaceclass.cpp` | 8 carved, residual 0 | `the residual loses matched rows`: `0x00116560`. |
| `WWVegas/WW3D2/HTreeClassFirstCapturedBone.cpp` -> `htree.cpp` | 5 carved, residual 1 | `the residual loses matched rows`: `0x00162BB0`, `0x00163A80` (`2 definitions spell its name`). |
| `Common/Rva0025BFE3Derived.cpp` -> `Common/AIStatBase.cpp` | 6 carved, 7/7 match beside TU, residual 3 | merge rejected with an EMPTY compiler message (`'compile: '`), reproduced twice on two sandbox sessions. Worth a look: either the compiler dies silently or the report loses the reason. |
| `GameLogic/Object/SpecialPower/SpecialPowerModuleDataBuildFieldParse.cpp` -> `ElvenWoodSpecialPower.cpp` | 7 carved, residual 16 | link guard: `moved selected COMDAT ?buildFieldParse@<X>ModuleData@@SAXAAVMultiIniFieldParse@@@Z lacks matching private/weak-free context`. |
| `Common/ConstIntGetters4.cpp` -> `ElvenWoodSpecialPower.cpp` | 7 carved, residual 256 | link guard: `moved selected COMDAT ??_C@...@TaintSpecialPower?$AA@ lacks matching private/weak-free context` (string literals). |
| `GameLogic/ScriptEngine/ScriptListDestructor.cpp` -> `Scripts.cpp` | 4 carved, residual 1 | `the residual loses matched rows`: `0x003B241A`. |
| `Common/System/Rva005A71B1Dtor.cpp` -> `GameNetwork/NAT.cpp` | 3 carved, residual 6, 9/9 match | merge rejected `bytes` (the destination's own bytes change). |
| `Common/GapBodiesGE51.cpp` -> `Common/RTS/PlayerTemplate.cpp` | 5 carved, residual 17, 5/5 match | merge rejected `C2953: 'StringBase' template class has already been defined` and `C2600`. |

## The shape that lands

A sweep donor of independent leaf bodies (`Disp8ByteFieldGetters`,
`Disp8PtrChaseDwordGetters`) whose rows are `mov`/`lea`+`ret` getters: no
private class view of the TU, no `alternatename` pragma, no shared file-static
helper, no string literal, and a residual that keeps dozens of rows. Everything
else in this pass failed on one of those five properties.

## Shared causes worth one fleet-level fix

1. `W3DView.cpp` (queue rank 1: 53 files, 128 rows) is blocked for every split by
   one displaced row, `0x0008553B`. Rehoming/approving it unlocks the top TU.
2. Private-view donors (`class <TUClass>` defined in the donor) refuse with C2039
   on every split; they need the `tu_views` reconciliation before carving.
3. Files whose named `namespace _STL` block defines templates cannot be carved at
   all; a sweep-file carve has to come from a donor without that block.
4. `alternatename` pins on placeholder virtual slots are copied with carved
   bodies and trip `hatch_counters` rule 3; retiring the pins is a prerequisite.

## Claims

All claims taken for these items were released (donor files and both destination
TUs).
