# BFME 2 consolidation shard 2 follow-up (2026-11-04)

Scope: mechanical TU consolidation only. Starting from the clean checkout after the earlier shard-2 handoff, the allocated queue still reported shard 2/5 and all selected destinations passed `--check-tu`. Each attempted destination had a current scoped `name_lane.py consolidate` report and `--check build/consolidation` pass before its plan/dry-run. No merge or split was applied; no claims were acquired; source and ledger files remain unchanged. Net source files removed: 0; TUs merged: 0; matched rows preserved by merge: 0.

## Additional dry-run blockers

- `GameLogic/Object/Made002CCB67.cpp`: `Made002CCB67Ctor.cpp` rejected by LinkGuard. Moving it makes the census-linked TU lose providers for `Rva00507823` vslots 1–3.
- `GameLogic/Object/Collide/CrateCollide/HealCrateCollide.cpp`: ctor has no matching `HealCrateCollide(Thing *, const ModuleData *)` declaration; execute donor's method is absent from the class view. Reconcile `CrateCollide`/`HealCrateCollide` views before retry.
- `GameEngineDevice/Source/W3DDevice/GameClient/BfmeHub982.cpp`: `W3DAptRendererBeginTriangleList.cpp` fails because `DX8Wrapper::bfmeRva00120650` is absent; class reconciliation required.
- `GameLogic/Object/Damage/HordeTransportContainDamage.cpp`: ctor and callback donors fail because their constructor/method are absent from `HordeTransportContainDamage`; class reconciliation required.
- `Common/GameEngine.cpp`: all seven donors rejected on missing `GameEngine` fields/methods, `SubsystemInterfaceList::rva001B5140`, or a `NetworkInterface` declaration. `ClientFrameSubsystem` view reconciliation is also reported.
- `Common/AptObject.cpp`: destructor donor fails because `AptObject::DestroyGCPointers` is absent from the class view.
- `Common/GameLOD.cpp`: `GameLODApplyPreset.cpp` fails on conflicting `TheTerrainVisual` declarations and `SubsystemInterface` redefinition; `GameLOD`/`OptionPreferences` reconciliation is needed.
- `Libraries/Source/debug/debug_except.cpp`: `Rva0088D8E0RecordInitialize.cpp` rejected for bytes.
- `Common/LightPointSystem.cpp`: `Rva00421520Find.cpp` fails with duplicate `_STL::allocator`/`vector` definitions; `ModuleData`/`Overridable` reconciliation is reported.
- `Libraries/Source/WWVegas/WW3D2/animobj.cpp`: transform donor has a return-type-only overload conflict; class donor lacks `Rva001A5460`/`_slave` declarations. Reconcile `Animatable3DObjClass`/`BfmeVciAnchorElem` before retry.
- `Libraries/Source/collisionmanager/CollisionManagerImpl.cpp`: Common donor needs missing `m_flag`/`m_listHead`; ScoreKeeper donor has `Coord3D` redefinition and placement-new conflicts. Class-view reconciliation required.
- `Libraries/Source/COM/_com_error.cpp`: plan stopped at `cl flags: unterminated quoted /I include path`; no dry-run composition was produced.

The earlier handoff `consolidation-shard-2-2026-11-04.md` records the other sampled shard-2 blockers and the reverted ownership refusal. The current full allocated listing contains 66 destinations; this session made no progress claim from dry runs. Remaining untried candidates must get a fresh planner/eligibility check and should be selected only after the listed prerequisites are resolved or another mechanical composition is identified.
