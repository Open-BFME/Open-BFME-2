### LINK-175: name-level sweep of the 18:30 census's non-linking units: five definers exist only under other spellings (2026-11-01, seat halilkkaya-lk13)

Status: Open (no repair landed). Base `c9f1a00d82`; census 2026-11-01 18:30 (`dae306bc9d`).
Scope: `link_rank.py` lists 163 non-linking units (45,970 matched B). Current objects
(`link_check` after a full `./build.sh`) link 24 of the 162 surviving ones; 138 still fail
(37,601 own B). Names that block several units: the six-unit canonical BehaviorModule tables
(LINK-168, held class); `AudioEventRTS` lifetimes `??0/??1/??4` (6 units, no rows anywhere;
each unit has 14-57 other blockers); `?set@UnicodeString@@QAEXABV1@@Z` (5 GUI menus, 12-47
blockers each); `?scanIndexList@INI@@SAHPBDPBQBD@Z` (4); `?crc@UpdateModule@@MAEXPAVXfer@@@Z`
(3, held class). None of these is a unit's last blocker, so this pass traced the units with
one or two blockers to their definers instead. Retail facts below come from the image and
the ledger; nothing was landed.

| Unit (own B) | Missing / losing name | Retail definer | Blocker |
|---|---|---|---|
| `RTS/PlayerCtorBFME2.cpp` (593) | `??1UnitRevivalTracker@@UAE@XZ` | Player ctor funclet `mov ecx,[ebp-10h]; add ecx,738h; jmp` reaches 0x002B0B8E, rowed `??1Rva002B0B8E@@QAE@XZ` (PlayerDestructor.cpp, `add ecx,4; jmp` vector dtor). Retail table 0x00818DF0 (ctor 0x0037F27B) has one slot, `xfer@UnitRevivalTracker`: the dtor is non-virtual | placeholder-into-existing-class rename (LINK-063 decision); `class --fold` needs a vftable install, which this dtor lacks |
| same | `Rva002B0F3CEnergy` slots | Player ctor stores 0x007FDC48 = Energy's table: 0x004A10FD folded `??_G`, 0x000B3FD0 empty, 0x002AA3AF `mov eax,"Energy"; ret` (rowed `?name@Rva002AA3AFNamed@@QBEPBDXZ`), 0x004DF290 `?xfer@Energy@@MAEXPAVXfer@@@Z` | spelling the view `Energy` makes it emit `??_7Energy@@6B@`, which `EnergyConstructorThunk.cpp` (0x00674870) also emits, but that body stores 0x008E0F20, not Energy's table: its BFME 1 donor identity is wrong and has to be resolved first |
| `RTS/Player.cpp` (112) | `?withdraw/deposit@Money@@...` | only caller is the unrowed one-argument Zero Hour `transferAssetsFromThat` (index: Player.obj alone touches it; retail's body is the two-argument row 0x002AEA9F) | dropping it links the unit (0 -> 112 B) but stops emitting row `?getDefaultTeam@Player@@QAEPAVTeam@@XZ` 0x0046F7E4 (`mov eax,[ecx+160h]; ret`, doubted in PlayerBFME2.h), a lost matched row. Reverted |
| `System/GlobalWeatherSystemCtorDeferred.cpp` (143) | `??1GlobalWeatherSystem@@UAE@XZ` | rowed as `??1Rva00318637@@UAE@XZ` 0x00318637 / `??_G` 0x0031861B / `??_E...WM@` 0x00318613 (Rva00318637Dtor.cpp); the rowed ctor 0x00318588 stores both tables | `rename.py class --fold Rva00318637 --into GlobalWeatherSystem`: refused first on the stale `data_ledger.csv` (regenerating names table 0x00C0C734 `??_7GlobalWeatherSystem@@6BSubsystemInterface@@@`; generator diff is 19k lines, not committed), then on the `??_E` adjustor thunk sitting on the Snapshot table 0x00C0C724 rather than on T. Recorded as a false reject (re_attempts) |
| same | `??1WeatherData@@QAE@XZ` | ctor's `eh vector constructor iterator` pushes dtor 0x0010F149, the shared 12-byte release dtor with about 40 `fold-proof=` twins | an inline view dtor plus an `add_match --icf-owner` twin; worth doing only with the row above |
| `STLport/Rva008312E0StringReplace.cpp` (1,351) | `?replaceBase@Rva008312E0String@@...` (L+S) | pinned to 0x0002A610, rowed `?bfmeReplaceV24@BfmeStrV24@@QAEPAV1@PAD000H@Z` (BfmeS1155.cpp, frame 0xd4) | the unit's own copy (frame 0x44) is kept and judged wrong. A declaration-only member shrinks the caller 0x0002AE50 frame 0x9c -> 0x5c (byte failure). Member template plus `extern template` is VC7.1 C1001. Both reverted; the 2026-10-28 link-order handoff still holds |
| `WWMath/tcbspline.cpp` (340) | `?Resize@?$VectorClass@VTCBClass...` (L+S) | pinned to 0x000F0BF1 (`VectorClass<Vector3>::Resize`, EH frame, `new T[n]` through the eh vector ctor iterator with the folded empty ctor 0x0047A6A9). The unit's POD `TCBClass` copy (156 B, no EH) occurs nowhere in retail (masked search) | retail's TCBClass is evidently non-POD, folded with Vector3's copy. A BFME 2 `tcbspline.h` with an empty `TCBClass()` would make the copies agree; no evidence for that header yet |

Also checked and left alone: `LivingWorldBuilding.cpp` (LINK-024; `Rva004E0D67Dtor.cpp` held by
StarkillerHDX), `WeaponStore.cpp` (dtor rowed as `Rva002CCD56`; file held), `RtcStack.cpp`
(`@_RTC_CheckStackVars@8` is strongly defined by both it and the vendored msvcrt `stack.obj`,
same retail digest: a modelling question), `DebugDestructorThunk.cpp` (re_attempts 83418/83695).
Remaining / next check: maintainer decisions on placeholder-into-existing-class renames (they
would clear UnitRevivalTracker, GlobalWeatherSystem and WeaponStore), an `rename.py --fold`
that accepts an MI class's adjustor thunk on its secondary table, and the identity of
0x0046F7E4 and 0x00674870.
Clearance: none. Census confirmation: not claimed.
