### LINK-090: the terrain bib wrapper calls a row identified as LinearCampaign

Status: Blocked on wrapper identity. Updated: 2026-10-26; inspected revision: `2a45addda1806342ac5c52757f63be902dcd428e`.
Evidence / affected unit: `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp`, the existing 13-byte `removeAllBibs` row at RVA `0x001EC981`. Its REL32 at offset `+0x8` targets RVA `0x001EC3B5`, which is already the 648-byte `LinearCampaign::onCurrentMissionWon` row in `Code/GameEngine/Source/GameLogic/System/LinearCampaign/LinearCampaignOnMissionWon.cpp`. That row's evidence identifies the WorldBuilder campaign twin, carry-over units and player upgrades. Raw native relocation and row evidence: `build/link-worker-w5-c136/native-refs.log` and `native-target-owners.json`.
Completed: inspected the current wrapper object and native destination without editing either unit. The unresolved `BaseHeightMapRenderObjClass::removeAllTerrainBibs` spelling is not evidence of an unimplemented body at this target.
Remaining / next check: establish the wrapper's actual campaign receiver and purpose before any row/name correction. Do not bind this terrain method to the existing campaign spelling merely because the call bytes agree. The separate water-transform row and the unit's unrowed terrain ports do not settle that identity.
Clearance: pending. Census confirmation: not claimed.

**Path refresh and duplicate-forwarder connection (2026-11-03, inspected `c475665b306`):**
The unit path above is stale: `Code/GameEngine/Source/GameLogic/System/LinearCampaign/LinearCampaignOnMissionWon.cpp`
no longer exists, and the 648-byte `?onCurrentMissionWon@LinearCampaign@@QAEXXZ` row at
`0x001EC3B5` is now owned by `Code/GameEngine/Source/GameLogic/System/LinearCampaignManager.cpp`.
The double naming this entry describes is unchanged and still present: `symbols.csv:5979`
carries `?removeAllTerrainBibs@BaseHeightMapRenderObjClass@@QAEXXZ` at that same address.
That file also owns the two 17-byte address-derived forwarders immediately after the
wrapper, `?rva001EC99B@Rva001EC99B@@QAEPAXHH@Z` and `?rva001EC9AC@Rva001EC9AC@@QAE_NHHH@Z`
(`functions.csv:46946-46947`, both noted "identity remains address-derived"), and those two
plus `?thru@Rva0023D6D5Callee@@QAEXXZ` are exactly the duplicates that stop the unit linking
when it adopts a canonical W3D header (LINK-184). Structural inference, not proven: the
terrain spelling at `0x001EC3B5` and the W3D-side duplicates suggest this forwarder cluster's
real owner is terrain/heightmap code rather than the campaign manager, so rehoming the
cluster may settle both entries. No row, name, pin or source was changed, and no identity
is asserted. No linking, debt or census gain is claimed.
