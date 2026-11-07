# BehaviorModule canonical-provider boundary, 2026-11-07

Investigated after `50a776d8b4`. All candidates were private Verifier inputs;
no tracked game source, header, symbol binding or row identity was changed.
The actual destructor is still rowed under Rva004607E1. This is a blocked
linking handoff, not provider or runtime clearance.

## New compiler evidence

Replacing the Rva004607E1 view in Common/Rva0049B47CDerived.cpp with the
canonical BehaviorModule header and its empty destructor preserves all ten
rows. The protected `??1BehaviorModule@@MAE@XZ` is exact for retail's 18-byte
0x004607E1; its emitted protected scalar deleting destructor is exact for
0x0025335A/28. Private row names and symbol-map bindings model the proposed
rename only. Both rows stay in their existing source: no unapproved TU move.

UpgradeModuleCtor.cpp is the other explicit Rva004607E1 consumer. Merely
adopting the canonical BehaviorModule base changes its constructor (1/2 rows
remain exact). Marking its existing abstract UpgradeModule view novtable
suppresses the extra compiler vptr stores while retaining the explicit retail
stores, restoring 2/2. This is compiler evidence only; the constructor still
contains its pre-existing dummy primary vptr and needs its own table recovery.

The existing prepared class-fold planner still refuses the table's five other
view names: BehaviorModuleView, PrimaryP, PrimaryP24A797, PrimaryP4B8CDE and
UpgradeBehaviorBaseView. `rename-refusal.txt` preserves the actual verdict.
Their declarations occur across thirteen sources; do not clear the refusal
merely from the byte match of two destructor bodies.

## Data boundary found before application

The newly emitted canonical BehaviorModule primary table has twelve slots,
but slots 1, 2 and 3 are **__purecall**. Retail table VA 0x00BEEA7C instead
requires 0x000B3FD0, 0x0024A791 and 0x004C9C7D respectively: the existing
loadPostProcess, GetSnapshotName and xfer providers. The current header keeps
the base overrides optional to avoid silently changing unmeasured leaf
tables. A provider migration must reconcile this surface and the affected
derived tables; emitting a longer table does not prove it correct.

The primary slot 0 relocation uses compiler-generated `??_EBehaviorModule`,
with the scalar deleting body available as `??_GBehaviorModule`; its compiler
alias/weak relationship also needs preserving. The JSON object-symbol reader
can list a name as both defined and undefined, so its raw undefined list is
not an unresolved-link verdict. The secondary table contains 47 slots; the
recorded slot names/addresses are inventory, not a full data-proof receipt.

## Reproduce and continue

Run the four retained Python probes from the repository root in their listed
order: base/compiler probes, novtable caller probe, prepared fold plan, then
table audit. They write only ignored build/ artifacts and use
tu_skeleton.Verifier; they never call build.compile_source. Compiler object
paths in the reports identify this private run and are not portable receipts.

Continue with the registered BehaviorModule/ObjectModule/Snapshot contract,
the helper-view cohort and native table slots. Then repeat the supported
prepared fold, normal byte/EH/data checks, affected-consumer audit and real
link. LockWeaponCreate's CreateModule fold, DamageModule's provider and the
Zero Hour crc table consumers remain separate downstream prerequisites.
