# AssetReference: four canonical-header consumers

Inspected source base: c6130c141bebcf1ab4c219ebd562d5de8f55a828.
Date: 2026-11-05. Model: gpt-6.1-sol.

Adopted the unchanged `Code/GameEngine/Include/Common/AssetReference.h` in:

- `Code/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMapTileTexture.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapDrawAuxiliary.cpp`
- `Code/Libraries/Source/WWVegas/WW3D2/RenderAssetParseBFME2.cpp`
- `Code/Libraries/Source/WWVegas/WW3D2/Rva0007B93BApply.cpp`

WorldHeightMap's converting handle reads canonical `field00`. The other
three units retain their existing inline destructor definitions outside the
class, including their original release referents. Rva0007B93BApply expresses
its temporary null test and opaque holder view at the call sites. The second
temporary still lasts through the same full expression; VC7.1's address-of-
temporary extension preserves its native return buffer and cleanup.

The frozen-source check exposed the previously unrowed canonical destructor
name after moving those definitions outside the private classes. Existing
`reverse/symbols.csv` already pins it to 0x0017098D. `add_match.py --icf-owner
'??1?$RefCountPtr@VTextureClass@@@@QAE@XZ'` verified the emitted 12-byte
`??1AssetReference@@QAE@XZ` in Rva0007B93BApply against the existing
streakRender.cpp owner. This adds an identity row with `gen-alias` and
`fold-proof`, no physical bytes or pin. It makes no donor-name recovery claim.

Provider audit: saved current original objects after a passing baseline build,
then compared external definitions and destructor bytes/relocations. All three
destructors are byte-and-relocation identical before and after. WorldHeightMap
has no AssetReference destructor definition. Only two external definitions
disappear: `?IsNull@AssetReference@@QBE_NXZ` and
`?View@AssetReference@@QAEPAVRva001514D0@@XZ`. A scan of all 25,021 `.obj`
files under `build/match/` found zero remaining definitions, imports or
`/alternatename:<name>=` directives for either helper. The destructor retains
20 defining objects and six importing objects. No alias, data definition or
other external provider is removed from these four objects.

Validation:

- Baseline `./build.sh` over the four sources: 37/37 matched.
- Edited `./build.sh`: the same 37/37 matched; `add_match.py` separately
  verified the fourth row in Rva0007B93BApply.
- Final `./build.sh --strict` over all four: 38/38 matched; 16 literals,
  13 empty-string references, two float literals and two named imports pass.
- `find_declared_unmatched.py --fail` over all four: all defined functions
  already matched. `check_csv.py`: OK, 99,495 function rows.
- One cohort `header_adopt_lane.py accept --class AssetReference` over all
  four retired exactly four queue rows. Repeated against the final destructor
  row: all four PASS. No hand retirement.
- `link_check.py` on the final cohort: all four LINKS, preserving
  2,895 -> 2,895 census-linked bytes (299, 379, 2,028 and 189 respectively).
  Published index: f44cbcf5b0, 2026-11-05 15:19 UTC. The unreferenced
  ShaderClass copy-constructor diagnostic in BaseHeightMap is unchanged.

This is a scoped source/header cleanup result. It provides no new real-link,
image, boot or census measurement. The remaining AssetReference queue rows
retain their existing prerequisites; the shared header was not edited.
