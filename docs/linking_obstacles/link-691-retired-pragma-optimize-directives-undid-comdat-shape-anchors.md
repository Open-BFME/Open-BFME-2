### LINK-691: retired `#pragma optimize` directives undid COMDAT-shape anchors in first-in-order providers
Status: Repair landed / awaiting verification (animobj.cpp); Open for the other providers below. Updated: 2026-11-18; inspected revision: `d72acd01df`.

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

Remaining / next check: LadderDefs.cpp (`9317f5872f` retired a `"t",on` / `"",on` pair) and
dx8renderer.cpp (`793701890c` retired `"s",on`, `ab706d5c75` a `"",on`) by the same test: disassemble
the unit's copy against the owner's (`string_base_inline.cpp`, `multilist.cpp`) and restore the state
without raising a hatch line. The other units those four commits and their siblings touched
(`git log --grep "pragma optimize" --since 2026-11-13`) emit no first-in-order wrong copy today, but
a later row that moves one of them ahead in link order would expose the same loss: compare an
anchor unit's COMDAT digests before and after retiring a directive, not only its rows.
Clearance: animobj.cpp scope cleared by the current-object preview above; the rest pending.
Census confirmation: awaiting; the preview does not change the headline.
