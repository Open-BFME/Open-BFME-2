# Shard 2 consolidation handoff (2026-11-04, session 5)

The supported dry run accepted `DetachableRiderBodyCtor.cpp` and
`ChinookAIUpdateBuildFieldParse.cpp`; other donors remained unchanged. The
applied trial's `./build.sh` verified 4/4 rows, the funclet pin check passed,
and `find_declared_unmatched.py` found no unmatched declarations. LinkGuard
retained all listed census-linked units. However, `tu_ownership.py --staged`
refused the trial: EH rows 0x0078FC8F and 0x0078FC87 route to
`Code/GameEngine/Source/GameLogic/Object/Body/ImmortalBody.cpp` (P), and the
merged file introduces private `ActiveBody` and `UpgradeMux` bodies despite
their registered canonical headers. The trial was restored and all three file
claims and four RVA claims were released. Net source-file change, TU merges and
matched rows preserved: 0, 0, 0. The path-consumer search found only
provenance comments and repointed ledger/queue owners; code-identity and
data-check baselines had no entries for the donor paths. No source-path history
or identity debt was retired.

Fresh allocated trials with no accepted donors:

- `Common/System/Geometry.cpp`: rejected for flag/profile conflicts and byte
  mismatches; LinkGuard listed the census-linked seed and donors.
- `Object/Made002CCB67.cpp`: ctor unresolved three `Rva00507823` vslot symbols;
  LinkGuard listed both census-linked units.
- `Common/GameEngine.cpp`: private declarations for `ClientFrameSubsystem`,
  `NetworkInterface`, `SubsystemInterfaceList` and `GameEngine` state prevent
  compilation; seed and donors were census-linked.
- `Object/Update/HeightDieUpdate.cpp`: ctor and module-data constructor
  declarations are absent from the merged class views; all three units were
  census-linked.
- `Object/Made002CCB04.cpp`: ctor donor fails byte verification; both units
  were census-linked.
- `GameClient/BfmeHub982.cpp`: missing `DX8Wrapper::bfmeRva00120650` declaration;
  private `RenderStateStruct` and `W3DAptRenderer` views remain prerequisites.
- `Object/Damage/HordeTransportContainDamage.cpp`: ctor and callback donors
  require class declarations absent from the seed view; all three units were
  census-linked.
- `Object/Collide/CrateCollide/HealCrateCollide.cpp` and
  `Object/Behavior/WargBehavior.cpp`: constructors and execute method require
  class declarations absent from the seed views; affected units were
  census-linked.
- `Common/AptObject.cpp`: donor compile fails because `DestroyGCPointers` is
  absent from `AptObject`; `AptValueWithHash::DestroyGCPointers` also fails as
  an illegal non-static call. Reconcile the private `AptObject` view.
- `Object/Update/AssistedTargetingUpdate.cpp`: pool-key and feedback donors
  redefine `SubsystemInterface`, `Coord3D` and `Thing`; the ctor donor also
  references undeclared `m_vtable` and `m_secondary0C`. Reconcile the private
  `AssistedTargetingUpdate` view and include prerequisites.

No other source, ledger, body or path-consumer repairs were made. The report
records dry-run blockers for follow-up; retry only after the named declaration,
flag/profile or byte prerequisites change.
