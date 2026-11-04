# Campaign forwarder identity correction refused

Inspected revision: e2cf205c0e; 2026-11-04; worker yasinschroeder-codex5.

Target facts: the existing 13-byte row at 0x001EC981 is named
`?removeAllBibs@W3DTerrainVisual@@UAEXXZ` in W3DTerrainVisual.cpp.
The native `mov ecx,[ecx+0x10]; test ecx,ecx; je return; jmp 0x001EC3B5`
forwards to the existing LinearCampaign::onCurrentMissionWon row. Both
ScriptGlueRva003BD598.cpp and ScriptGlueRva003C3B4A.cpp use
TheLinearCampaignManager as the receiver through a W3DTerrainVisual cast.
The current campaign manager view stores its current campaign at +0x10.
These corroborate LINK-181's campaign-manager identity; they do not prove
an original method name for the forwarder.

Verification: ./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp
passed 2/2 rows and its data row from current cached objects.
The current link_check.py preview remains 0 -> 0 linked bytes, with sole
unresolved name ?removeAllTerrainBibs@BaseHeightMapRenderObjClass@@QAEXXZ.
No census or real-link improvement is claimed.

The documented correction path (docs/naming.md, Disputes) was attempted:

```
python3 tools/add_match.py '?rva001EC981@LinearCampaignManager@@QAEXXZ' 0x001EC981 13 Code/GameEngine/Source/GameLogic/System/LinearCampaignManager.cpp --replace-rva 0x001EC981 --notes 'Identity correction: campaign-manager +0x10 null-checked forwarder to LinearCampaign::onCurrentMissionWon; native callers use TheLinearCampaignManager.'
```

It exited 1 before changing any source or ledger:

```
add_match: --replace-rva 0x001EC981 is ?removeAllBibs@W3DTerrainVisual@@UAEXXZ (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp), not a gen-dump, gen-alias, generated unwind, verified gap-thunk or gen-import scaffold row
add_match: only scaffolding may be taken over by name; retract a real claim in its own commit so the retraction is reviewable
```

This contradicts the documented identity-correction path for a real row.
No retraction, gate workaround, replacement, source move or pin removal was
performed. Next: a separate tooling repair should support an evidence-backed,
atomic identity correction without temporarily losing matched coverage.
Then verify the wrapper and both callers together, recompute TU approval
(the committed map currently marks 0x001EC981 displaced), audit all references
to the old terrain pin, and retire that pin only with the identity repair.
