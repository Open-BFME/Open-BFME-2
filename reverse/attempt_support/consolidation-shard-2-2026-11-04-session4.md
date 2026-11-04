# Shard 2 consolidation handoff (2026-11-04, session 4)

Allocated TU trials completed in this session. Every destination passed
`consolidation_queue.py --check-tu`; each planner snapshot was freshly generated
under a narrow parent and passed `name_lane.py consolidate --check`. These are
dry-run results only: no TU was applied, no file/RVA claim was taken, and no
source or ledger change was made.

- `Common/System/Geometry.cpp`: 45 approved rows, 21 donors, 12 mixed files.
  Accepted none. Donors were refused for flag conflicts, region-default compile
  failures, byte mismatches, and LinkGuard's census-linked set; no approved
  merge was verified. See dry-run for per-donor verdicts.
- `WWVegas/WW3D2/RenderAsset.cpp`: 75 approved rows, 8 donors, 10 mixed, 5
  refused. Accepted none. The seed fails on `renderAbs` missing/redefinition;
  donors fail on duplicate `_STL::allocator<char>` and `_STL::_Rb_tree` symbols.
  LinkGuard includes census-linked sources.
- `WWLib/BfmePod248.cpp`: 34 approved rows, 2 donors, 8 mixed. The sole donor
  `StlportPod248ElementDtor.cpp` fails C2908/C2766 because the `_STL::vector`
  specialization is already instantiated; class reconciliation for
  `BfmePod248` is reported. LinkGuard sees both units as census-linked.
- `Object/Contain/ProductionQueueHordeContain.cpp`: 41 approved rows, 7 donors,
  4 mixed. LinkGuard rejects the destination seed itself: census-linked object
  becomes non-linking with duplicate `?rva00481279@Rva00481279@@QAE_NHHHHHH@Z`.
  Other donors have missing class declarations, malformed slots, no default
  constructor, or byte failures. Do not retry until prerequisites change.
- `Object/Update/DockUpdate/SupplyCenterDockUpdate.cpp`: 16 approved rows, 2
  donors, 4 mixed. Its constructor donor fails C2039 because
  `BehaviorModule::behaviorModuleAnchor` is absent; class reconciliation for
  `DockUpdate` and `SupplyCenterDockUpdate` is reported.
- `GameClient/GUI/GUICallbacks/Apt/AptPlayerStatus.cpp`: 42 approved rows, 4
  donors, 1 mixed. Donors fail on missing `GameWindow` base declaration, a
  duplicate C-linkage `_mbscpy` overload (C2733), or byte mismatch; class-view
  reconciliation is reported.
- `GameClient/GUI/GUICallbacks/Apt/AptMpGameRules.cpp`: 62 approved rows, 4
  donors, 3 mixed. Common donors hit duplicate `_STL::allocator` definitions;
  GameClient donor hits conflicting `HMODULE`/`HINSTANCE` shim types. LinkGuard
  blocks the census-linked set; no verified merge.
- `Object/Upgrade/RemoveUpgradeUpgrade.cpp`: 18 approved rows, 3 donors, 2
  mixed. `RemoveUpgradeUpgradeImplementation.cpp` fails C2883 on `_STL::free`
  conflicting with the `free` using-declaration. The module-data constructor
  donor fails C2600 because the compiler-generated constructor is undeclared;
  reconcile `RemoveUpgradeUpgradeModuleData` before retrying. LinkGuard names
  all three census-linked units.
- `Common/AIGameTeam.cpp`: dry run accepted the seed and
  `SkirmishAITeamOwnedDtor.cpp` (16 rows, no rejected donors), but application
  was deferred because active source comments in `AIGameTeam.cpp` still name the
  donor path as unmerged (lines 359, 385, 387, 391 at audit time). A path-consumer
  repair is outside this lane; update those comments and audit the
  `reverse/stlport_trial.csv` consumer before a later apply.

The already documented blockers in session 3 and earlier were skipped without
repeating their trials. No hidden `.*.tu_skeleton.cpp` trial artifacts were
created by these dry runs (confirm before publication). Net source-file change,
TUs merged, and matched rows preserved this session: 0, 0, 0.

Next: continue the still-allocated shard-2 listing with fresh destination
checks; do not retry the above donors until the recorded declarations, compile
prerequisites, path consumer, or LinkGuard evidence changes.
