### LINK-691: retired `#pragma optimize` directives undid COMDAT-shape anchors in first-in-order providers
Status: Repair landed / awaiting verification (animobj.cpp, dx8renderer.cpp, LadderDefs.cpp); Blocked for rawfile.cpp (hatch re-admission or a TU approval). Updated: 2026-11-18; inspected revision: `d72acd01df`.

Evidence / affected units: the 2026-11-18 10:35 census (`147fd3e52b`) holds 143 units out, and
`link_check.py --paths-from` over all 160 census-blocked sources at `d72acd01df` links none. Three
providers that come first in the census's link order each emit a compiler-generated or header-inline
COMDAT in the wrong optimisation shape, so every unit touching that name fails `selected`:

| First definer (link position) | Name | Units held out (own bytes) |
|---|---|---|
| `WW3D2/animobj.cpp` (768) | `??_EWeightInfoStruct@NamedPivotMapClass@@QAEPAXI@Z` | 29 (56,102) |
| `WW3D2/animobj.cpp` (768) | `??_GHTreeClass@@QAEPAXI@Z` | 3 (4,863) |
| `GameSpy/LadderDefs.cpp` (529) | `?getCharAt@?$StringBase@D@@QBEDH@Z` | 8 (27,122) |
| `WW3D2/dx8renderer.cpp` (1157) | `??_GMultiListObjectClass@@UAEPAXI@Z` | 10 (19,924) |
| `WW3D2/dx8renderer.cpp` (1157) | `??_GGenericMultiListClass@@UAEPAXI@Z` | 19 (16,816) |

Cause, proven for animobj.cpp: its two unemitted anchors (`bfmeWeightInfoVddAnchor`,
`bfmeHTreeDeleteAnchor`) give `??_E`/`??_G` the state of the first function that needs them and each
sat under its own `#pragma optimize("gsy", on)`. Commits `8669caffb1` and `ab706d5c75` (2026-11-16)
retired those two directives as duplicates of the one at the top of the file. They were not
duplicates: `WW3D2/rendobj.h`, included in between, ends its size-optimised class with
`#pragma optimize("", on)` (since `033a79d879`, 2026-10-31), so the anchors compiled in the
command-line state and emitted the `/O2` shapes (`add esp,4`, two epilogues; 92 bytes against
retail's 81 for `??_E`). Those commits verified rows only; an unrowed COMDAT's shape is invisible to
the byte gate, and the hatch register cannot tell a pragma a header overrides from a redundant one.

Completed: animobj.cpp (this commit). The two anchors, with the `hanim.h` and `htree.h` includes
they need, moved into the existing size-optimised block ahead of `rendobj.h`. No directive was
added: the unit keeps one `"gsy",on` and one `"",on`. `./build.sh` 55/55 matched.
`link_check.py animobj.cpp` LINKS 0 -> 4,454; with its 31 consumers 30 of 31 link, 0 -> 56,313
bytes (index `147fd3e52b`). The one left, `W3DModelDraw.cpp` (198 bytes), fails on
`??$__copy@PAV?$BitFlags@$0HF@@@PAV1@H@_STL@@...`, an unrelated copy.

dx8renderer.cpp (its own commit): `793701890c` retired the `#pragma optimize("s", on)` ahead of
`#include "multilist.h"` as "overwritten" by the reset after the include, and `ab706d5c75` then
retired that reset as a duplicate, so multilist.h's classes compiled in the command-line state and
`??_GMultiListObjectClass` / `??_GGenericMultiListClass` came out 30 bytes (`add esp,4`) against
retail's 28 (`pop ecx`). `multilist.h` now sits in the `bfmeVciAnchor` block, between the unit's one
`"gsy",on` and its one `"",on`, with `mutex.h` moved ahead of that block so
`FastCriticalSectionClass::LockClass` keeps its `/O2` destructor. `./build.sh` 91/91 matched;
`link_check.py` dx8renderer.cpp with its 24 consumers: 25 of 25 link, 0 -> 26,146 bytes (index
`147fd3e52b`). The unit's unreferenced `??0MultiListObjectClass` copy is 13 bytes against a majority
16: a diagnostic, as it was under the retired `"s",on`.

LadderDefs.cpp (its own commit): the unit builds `/O1` (its region's default; the `// cl:` line
names no `/O`), so the `#pragma optimize("t", on)` / `("", on)` pair around its inline
`StringBase<char>::getCharAt` specialization was what made the emitted copy retail's 23-byte
two-RET body. `9317f5872f` retired the pair as redundant under `/O2`; the copy became the 22-byte
tail-merged one, first in link order. VC7.1 emits an inline explicit specialization once the unit
uses it, even when every use is expanded and only `.debug$F` still names it (tried: defined ahead of AsciiString's forwarder, as a member-template
definition, and `__forceinline`; each still emitted the size-shaped body), so no reordering gives a
speed-built copy without a directive. The specialization now takes AptOnlineHomeTimeZone.cpp's form
for the same function, `__declspec(dllimport) __forceinline`: the rows expand it as before and the
object defines no `?getCharAt@?$StringBase@D@@QBEDH@Z`. `./build.sh` 67/67 matched; `link_check.py`
LadderDefs.cpp with its 7 other consumers and string_base_inline.cpp: 9 of 9 link, 1,021 -> 28,143
bytes (index `147fd3e52b`). Its unreferenced `?getCharAt@AsciiString@@QBEDH@Z` forwarder copy is now
the expanded 22-byte body where four later units carry the 5-byte jump: a diagnostic; the name has no
retail address and those four link.

Blocked, rawfile.cpp (3,305 B; `??_GFileClass@@UAEPAXI@Z`, "unproven and differs from the kept
copy"): `793701890c` retired the `#pragma optimize("gsy", on)` ahead of its `WWFILE.H` include as
overwritten and `7facb77827` the reset after it. The unit's copy is the 31-byte `/O2` shape; the row
(0x00078257, W3DFileSystem.cpp) is the 29-byte `/O1` one. No reordering helps: the unit builds `/O2`,
has no size-optimised block left to share, and must keep emitting FileClass's table because it rows
`??1FileClass@@UAE@XZ` 0x00078246 and `?Tell@FileClass@@UAEHXZ` 0x0007824D. Those two rows are also
why it precedes W3DFileSystem.cpp (first row 0x00078257) in the census's order: they are the inline
members retail's W3DFileSystem object emitted beside its `??_G`. Two routes, neither open to a
matching seat: re-admit the retired pair (the register holds no `pragma_optimize` line for the unit;
`cfbcc23bab` is the precedent, `Verifier-Change: hatch-admit`), or a `tu_map.csv` approval that sends
0x00078246 and 0x0007824D to W3DFileSystem.cpp, after which rawfile.cpp sorts behind the owner and
its unproven copy no longer decides.
The `"t",on` pair `16ad168ccf` retired from `Rva001DBBAD.cpp` must NOT come back: LINK-692 shows the
size-optimised body is retail's, under another class.

Remaining / next check: `SidesList.cpp` and `AptMessengerOnlineResponse.cpp` still emit the
size-shaped `StringBase<char>::getCharAt`; they come after string_base_inline.cpp in the census's
order, so they lose nothing there, but path order (the real link) may keep either: read
`kept_copies.tsv` for 0x00035720 on the next image. `W3DModelDraw.cpp` (198 bytes) is left on its
`__copy<BitFlags<117>*>` copy. The other units the retirement commits touched
(`git log --grep "pragma optimize" --since 2026-11-13`) emit no first-in-order wrong copy today, but
a later row that moves one of them ahead in link order would expose the same loss: compare an
anchor unit's COMDAT digests before and after retiring a directive, not only its rows, and read the
unit's built flags (`retail_body.build_flags`), not its `// cl:` line.
Clearance: the three providers' scopes cleared by current-object previews at index `147fd3e52b`: `link_check.py --paths-from` over the 160 census-blocked sources links 63 with the three repairs, 0 -> 109,581 of the census's 163,608 unlinked bytes (none linked before them).
Census confirmation: awaiting; the preview does not change the headline.
