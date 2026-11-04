# BFME 2 consolidation shard 2/5, session 10

Fresh allocated trials were run with passing `--check-tu`, scoped consolidation snapshots and `--check`, then upstream `--plan` and `--merge --dry-run`. No merge/split was applied and no claims remain.

- `HeightDieUpdate.cpp`: no donor accepted. `HeightDieUpdateModuleDataCtor.cpp` fails C2600 (compiler-generated constructor not declared); `HeightDieUpdateCtor.cpp` fails C2511 (constructor absent from class view). LinkGuard sees the seed and both donors as census-linked.
- `LivingWorldBuilding.cpp`: destructor donor fails because `NativeBuildingObserverCallback` is undeclared (`C2146`/`C2501`); LinkGuard sees seed and donor census-linked.
- `LivingWorldScoreKeeper.cpp`: no donor accepted. `Rva004EEE38CollectTurnStats.cpp` needs absent `m_lastTurn`; STL donor files redefine `_STL` templates; `Rva004EE15BFwd.cpp` needs undeclared `Xfer::vf10`/`vf33`; `Rva004EE9E9XferVector.cpp` fails bytes. LinkGuard reports seed and six donors census-linked.
- `FXShaderRenderer.cpp`: no donor accepted. `Rva00174753GapFillerDtor.cpp` lacks `BfmeAssignRecord32`; two STL donors fail bytes; another STL donor has no compile diagnostic. LinkGuard reports the seed and four donors census-linked. `BfmeAssignRecord32` view reconciliation is required.
- `TurretAI.cpp`: no donor accepted. Failures require missing/colliding class declarations and fields (`TurretAIAttackInterface`, `xfer`, `INIException`, `m_modelConditionFlags`, `TheAudio`); LinkGuard reports seed and all five donors census-linked.
- `LargeGroupAudioUpdate.cpp`: ctor and dtor fail on duplicate vftables/classes; update donor has incompatible `BitFlags<N>`/`Block19` view. LinkGuard reports seed and all three donors census-linked.
- `RainOfFireUpdate.cpp`: ctor/dtor fail on duplicate class/vftable declarations; class view reconciliation required. LinkGuard reports seed and both donors census-linked.
- `W3DBuffBuffer.cpp`: `Rva000D3A8ACtor.cpp` has incompatible `Rva000D3A8AElemB[10]`/`Rva000D3A17SetSlot*` types. LinkGuard sees seed and donor census-linked; another source was correctly refused because its row is not approved for this TU.
- `SymbioticStructuresBody.cpp`: both donor dry runs were blocked because the current census index is missing the census-linked seed TU. No index was built in-session.

The existing shard handoffs document the other sampled candidates, including Geometry, AptObject, GameEngine, WargBehavior, AIWall, and prior LinkGuard/class-view refusals. These are compile, declaration, byte or census prerequisites for other contributors; this pass made no source-file or matched-row changes and claims no identity/link improvement.
