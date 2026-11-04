# BFME 2 consolidation shard 2 session 3 (2026-11-04)

Scope: mechanical TU consolidation only. The allocated queue remained shard 2/5. Fresh scoped name-lane reports passed `--check build/consolidation` for each candidate. No merge or split was applied; no claims were acquired; code and ledgers remain unchanged. Net source files removed: 0; TUs merged: 0; matched rows preserved by verified merge: 0.

## Additional dry-run blockers

- `WWVegas/WW3D2/RenderAsset.cpp`: no donor accepted. The seed fails merged compilation (`renderAbs` undefined/redefinition); other donors collide on STL allocator/tree definitions or the unapproved seed rows. LinkGuard reports no verified merge.
- `GameLogic/Object/Update/MonitorConditionUpdate.cpp`: constructor donor is a compiler-generated special member absent from its class declaration (C2600); update donor fails byte verification; class views need reconciliation.
- `GameLogic/Object/Update/FloodUpdate.cpp`: no donors accepted. Constructor/module-data donors require missing fields, duplicate STL declarations, or fail bytes; `FloodUpdate`/module-data views need reconciliation.
- `W3DDevice/GameClient/Water/W3DWaterTracks.cpp`: no donors accepted. Render donor redefines Zero Hour `RealRange`; flush donor lacks `TextureClass`; class views need reconciliation.
- `Common/StateMachine.cpp`: no donors accepted. Multiple donors fail because `StateMachine::StateReturnType`/fields and `State::rva004D7127` are absent; another donor fails bytes; `Object` views need reconciliation.
- `GameClient/GUI/AptSpellStore.cpp`: constructor donor is a compiler-generated special member absent from the class declaration (C2600); seed fails LinkGuard due to unresolved `Rva0043D16F` vslots and a changed provider. Reconcile `Rva0043D16F` before retry.
- `GameLogic/Object/Update/CivilianSpawnUpdate.cpp`: ctor thunk fails to convert `int` to `UpdateSleepTime`; module-data dtor fails bytes; class view needs reconciliation.
- `GameLogic/Object/Contain/CaveContain.cpp`: ctor donor lacks `m_FC`/`m_104`; dtor donor loses an `OpenContain::getApparentControllingPlayer` provider under LinkGuard; class views need reconciliation.
- `GameLogic/Object/Upgrade/BaseUpgrade.cpp`: sole donor fails because `StringBase` is defined twice under the merged include set.

All candidates passed `consolidation_queue.py --check-tu`; each was freshly planned and dry-run, with no accepted unchanged donors. The earlier shard handoffs record additional candidates and blockers. Further destinations remain in this shard; their manual class/header repairs and blocked compositions are prerequisites for other contributors. No source reduction or identity-debt retirement is claimed.
