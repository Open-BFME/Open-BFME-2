### LINK-673: GameClient.cpp's second TheTerrainVisual has no live reader
Status: Open (record; no runtime effect found). Updated: 2026-11-13 (seat halilkkaya-bt3); inspected revision:
`d605b7a1a05` (source) and the CI diagnostic image at `c3cee37c76d` (linked image).

Evidence / affected units:
- Target fact: retail's terrain visual singleton is the one word at 0x00DFF080. Its ledger owner is
  `?TheTerrainVisual@@3PAVG00DFF080Obj@@A` (`reverse/data_rows.csv`, `Code/GameEngine/Source/Common/Rva0029A94FClear.cpp`,
  48 DIR32 sites). Every other unit that names it, including `GameClientDrawableTOC.cpp` (`GameClient::init` stores
  the created visual there) and `W3DRadarTerrainTexture.cpp`, declares `extern G00DFF080Obj *TheTerrainVisual`.
- `Code/GameEngine/Source/GameClient/GameClient.cpp` line 143 also defines `TerrainVisual *TheTerrainVisual = 0;`
  ("placement unverified: no rowed DIR32 site yet"), so the image holds a second word,
  `?TheTerrainVisual@@3PAVTerrainVisual@@A` (0x02BF88A4 in the `c3cee37c76d` image, in `gameclient.obj`), that nothing
  writes.
- Its only reader in that image is `?destroyPlacementIcons@InGameUI@@IAEXXZ` (`InGameUI.cpp`, a Zero Hour body marked
  `present-unmatched`, no ledger row), through `GameClient/TerrainVisual.h`'s declaration, at +0x22 and +0x61. That
  body has no caller in the image: no E8 call and no dword holding its address.

Consequence: none today. If a matched row ever calls this body, `TheTerrainVisual->removeFactionBibDrawable` and
`->removeAllBibs()` dereference the null second word.

Remaining / next check: when `destroyPlacementIcons` is rowed or its body replaced, bind it to the owner symbol (view
cast through `G00DFF080Obj`, as the other units do) and drop `GameClient.cpp`'s definition in the same change. Then
check with `link_check` that no unit loses its provider.

Clearance: when the image holds one `TheTerrainVisual` word.
Census confirmation: not claimed.
