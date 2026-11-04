# Consolidation shard 1 repeated trial evidence (2026-11-04)

`Code/GameEngine/Source/Common/AIReturnTheRingTactic.cpp` remains allocated
(`--check-tu` exited 0); the current narrow Common planner passed its currency
check. The plan has 21 approved rows, two donor files, four mixed files, and no
refused files. The dry run again accepts no donors: `AIReturnTheRingTactic_run.cpp`
fails because the destination view lacks `AIReturnTheRingTactic::run` and
`m_owner`. LinkGuard marks both units census-linked. This matches the existing
obstacle and the prior handoff; no source, ledger, or claim changed. Required
class/view reconciliation is outside this mechanical seat. No retry is warranted
until that prerequisite changes.

## Additional allocated dry runs

The following targets passed `consolidation_queue.py --check-tu`; each used a
current narrow planner snapshot (`name_lane.py consolidate --check` passed)
before `--plan` and `--merge --dry-run`. No merge or source edits were made.

| TU | Dry-run result |
|---|---|
| `Code/GameEngine/Source/GameClient/Drawable/Update/SwayClientUpdate.cpp` | No accepted donors. `Rva004C908BCtor.cpp` fails because the target view lacks `SwayClientUpdate(Thing *, const ModuleData *)`; both objects are census-linked. |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/ScreenHilightFilter.cpp` | No accepted donors. `ScreenHilightFilterPreRender.cpp` has DirectX declaration conflicts; `ScreenFilterRva007D85C0Slot6.cpp` has a target type/declaration error. The donors and target are census-linked; class view reconciliation is required. |
| `Code/GameEngine/Source/Common/HordeAIUpdate.cpp` | No accepted donors. `HordeAIUpdateCtor.cpp` fails because the seed view's `AIUpdateInterface` has no suitable default constructor/member layout; seed and donor are census-linked. |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/FlatHeightMap.cpp` | No accepted donors. `FlatHeightMapDoPartialUpdate.cpp` produces compiler internal error C1001; target and donor are census-linked. |
| `Code/Libraries/Source/Apt/AptMiscObjects.cpp` | No accepted donors. `AptLoadVarsLookup.cpp` lacks the `AptActionInterpreter::AptBasePtrStack` declaration in the seed view; `Rva006e9730Cluster.cpp` redefines `AptValue` and expects absent members. Both donors and seed are census-linked; class view reconciliation is required. |
| `Code/Libraries/Source/WWVegas/WW3D2/camera.cpp` | No accepted donors. `CameraAdditionalTransformSetter.cpp` expects `Set_Reflected_Projection_Matrix` and `m_38C` absent from the seed `CameraClass` view. Both units are census-linked. |
| `Code/GameEngine/Source/Common/RTS/ActionManager.cpp` | No accepted donors. `Rva0041C9C4.cpp` lacks the `Overridable` base and `friend_getFinalOverride`; `ActionManagerCanDoSpecialPowerAtLocation.cpp` lacks `SHROUDED` and `SpecialPowerModuleInterface::ready`. The affected units are census-linked; class/header repair is outside this seat. |
| `Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdate.cpp` | No accepted donors. Coord3D/Xfer redefinitions, BitFlags template mismatch, and missing constructor/view members block the donors; affected units are census-linked. |
| `Code/GameEngine/Source/Common/OathbreakersFadeAwayBehavior.cpp` | No accepted donors. Constructor overload and `getModuleNameKey` are absent from the seed view; reconciliation is outside this seat. |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/RampageBehavior.cpp` | No accepted donors. UpdateModule, `getModuleNameKey`, constructor/member declarations are absent; `tu_views` reconciliation is required. |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp` | No accepted donors. Two otherwise-linked donors lose `BaseHeightMapRenderObjClass::removeAllTerrainBibs` at the combined link position; remaining class/type errors need upstream view/header repair. The two link failures match the area of existing obstacle `link-090`; no obstacle status changed. |
| `Code/GameEngine/Source/GameLogic/Object/Collide/VeterancyCrateCollide.cpp` | No accepted donors. The constructor donor lacks the target constructor declaration; target and donor are census-linked. |
| `Code/GameNetwork/GameSpy/GSConfig.cpp` | No accepted donors. STL allocator and set-member declarations are missing; another candidate fails bytes; affected units are census-linked. |
| `Code/Libraries/Source/Lua/lapi.c` | No accepted donors. Both routed record-lookup donors fail the baseline match; the three units are census-linked. |
| `Code/Libraries/Source/WWVegas/WW3D2/dx8webbrowser.cpp` | The plan has two donors and mixed files; dry run stops at `cl flags: unterminated quoted /I include path`. This is a flag prerequisite outside the mechanical lane. |
| `Code/GameEngine/Source/Common/BfmeB1137.cpp` | No accepted donors. Constructor donor expects `UnInstall_Materials` absent from the target class view; destructor donor defines an undeclared special member. The target and donors are census-linked; class view reconciliation is required. |
| `Code/GameEngine/Source/GameLogic/Object/PartitionManager.cpp` | No accepted donors across 17 planned donors. Compile failures include missing `Gen_008F7CD0` members, duplicate `AsciiString`/`PartitionData` views, private-member access, and undeclared `CDEArraySlot`; one donor fails bytes. All affected units are census-linked; class-view and declaration work is outside this seat. |

No accepted two-donor composition was found in these allocated trials. Each
rejected donor needs a prerequisite outside mechanical consolidation; do not
retry until those declarations, views, or compile conditions change. Full
allocated shard listing was inspected (91 TUs); previously logged failures
were skipped rather than rerun.
