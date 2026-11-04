# BFME 2 consolidation shard 2/5, session 8

No mechanical merge was accepted. The full allocator listing (`--limit 100000`)
showed the shard-2 TU candidates; session 5/6/7 handoffs already cover most
unchanged refusals. Five additional allocated destinations were inspected with
fresh scoped planner snapshots, allocation checks, `tu_skeleton.py --plan` and
`--merge --dry-run`. No claims or source edits were made.

- `HordeTransportContain.cpp`: 48 approved rows, 6 donors. None accepted.
  Constructor/interface donors need `TransportContain` declarations; other
  donors fail on missing `isValidContainerFor`, `x3C`, or a conflicting
  `Matrix3D::Get_X_Vector` declaration. LinkGuard reports the seed and all five
  donors census-linked. Reconcile declarations/signatures before retry.
- `BaseTemplateLibrary.cpp`: 32 approved rows, 4 donors; one unrelated source
  refused because its rows are not approved here. None accepted. The donors
  fail on `_STL::free`, duplicate `_STL::vector::end`, and duplicate
  `SubsystemInterface`; LinkGuard reports the seed and all three donors
  census-linked. Reconcile the private template/interface views first.
- `AIWall.cpp`: 50 approved rows, 2 donors. The scalar-deleting-dtor donor
  fails byte verification; the STLport donor is refused because its flag
  override costs a seed row. LinkGuard reports the seed and byte-refused donor
  census-linked. No accepted donor to pair with a split.
- `AIUnitBuilder.cpp`: 62 approved rows, 2 donors; one unrelated source
  refused because its rows are not approved here. No donor accepted. The build
  donor is refused by LinkGuard because the census-linked unit would lose its
  selected list-insert COMDAT. Reconcile the selected COMDAT context first.
- `LivingWorldBuilding.cpp`: 53 approved rows, 2 donors. The destructor donor
  fails on missing `NativeBuildingObserverCallback` declarations; LinkGuard
  reports the seed and donor census-linked. Reconcile declarations first.

Fresh scoped planner checks passed for each parent directory; reports were
reused only after `name_lane.py consolidate --check build/consolidation` passed.
No build, source-path audit, identity/provider comparison or declaration scan
was applicable because no merge or split was accepted. The inherited session-7
blocker note is also being published with this handoff. Net source-file change,
TUs merged and matched rows moved/lost: 0, 0, 0. Claims taken by this session: 0.
