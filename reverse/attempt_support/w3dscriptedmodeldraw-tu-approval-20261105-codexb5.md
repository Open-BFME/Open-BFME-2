# W3DScriptedModelDraw TU approval, 2026-11-05

Inspected revision: `4bfef7ad91a6cda07765b3297a326a88121ba8e8`.
Scope: `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DScriptedModelDraw.cpp`.

## Current target facts

- `tu_skeleton.py --plan` rebuilt the stale map in memory: 90 ordinary code rows remain proposed; 76 EH companion rows are approved. The plan has no absorbable external donor (one pull source is the destination itself), four mixed files and five refused files.
- The ordinary proposed cluster spans RVA `0x000B3A80..0x000C8914`. It overlaps the following independently Z/S-anchored W3DModelDraw rows; naming and brackets alone cannot approve this cluster.

| RVA | Signal | Current source |
|---|---|---|
| `0x000B3D39` | S | `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawRva000B3D39.cpp` |
| `0x000B4E43` | Z | `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawClientTurret.cpp` |
| `0x000B51DA` | S | `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawGetCurrentBonePositions.cpp` |
| `0x000B52CD` | Z | `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawGetCurrentBonePositions.cpp` |
| `0x000B6EDE` | Z | `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawParticles.cpp` |
| `0x000B6F6D` | Z | `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw_setHidden.cpp` |
| `0x000B6FFE` | Z | `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp` |
| `0x000B77B2` | Z | `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawClientTurret.cpp` |
| `0x000B7C24` | S | `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawAttachableSubModels.cpp` |
| `0x000B7FE8` | Z | `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawReactToTransformChange.cpp` |
| `0x000B9CE8` | Z | `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw_setTerrainDecal.cpp` |
| `0x000BAF7B` | Z | `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawUpdateSubObjects.cpp` |

## Donor facts and limits

- WorldBuilder leads in the current map name `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/W3DScriptedModelDraw.cpp`, whereas the served naming hint includes the additional `Draw/` directory. A WorldBuilder pairing is a placement hint, not proof that a differently named game body belongs there.
- Zero Hour Z/S evidence places the interleavers in `Draw/W3DModelDraw.cpp`. Neither spelling agreement nor the address span proves that BFME 2 retained that donor organization.
- The consolidation evidence packet surveyed 168 sources in the Draw directory, found zero verified retail path operands in those selected rows, and records declaration, routing and compiler prerequisites. It grants no merge approval.

## Verification and attempted cleanup

- `find_declared_unmatched.py` passes for the claimed destination; baseline `./build.sh` verifies 19/19 function rows and 22 data rows, plus 11 literals and five empty-string references.
- Replacing `AsciiString name(g_Rva0107301CEmptyString)` in RVA `0x000BF7E8` with `AsciiString name("")` changes register allocation and the stack frame (`sub esp,0x10` becomes `sub esp,0x14`), so the 363-byte parent and its EH dependents fail. The attempt was reverted; the hatch/register entries remain intact.
- `class_views.py --unused --files <destination>` finds no removable class candidate.
- No source, TU-map, name, debt or coverage change is claimed.

## Next useful work

Establish BFME 2 class identities and original placement for the interleaved W3DModelDraw/ScriptedModelDraw bodies, then use the supported naming evidence workflow. Alternatively, validate an appropriate retail structural routing rule separately. Do not move the 90 proposed bodies or force a provisional TU on the strength of this span. Rebuild the map in memory and rerun the plan after that prerequisite changes.
