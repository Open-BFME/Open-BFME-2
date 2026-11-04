# GrantUpgradeCreate onBuildComplete canonical base

Base: `42ac56fd5f`. Scope: the existing matched 78-byte body at RVA
`0x004B9093`, in
`Code/GameEngine/Source/GameLogic/Object/Create/GrantUpgradeCreate_onBuildComplete.cpp`.
No ledger owner, source path, pin, alias or hatch changes.

The Create-subsystem consolidation planner and `tu_views.py` found incompatible
GrantUpgradeCreate definitions. The onCreate donor already derives from
CreateModule; onBuildComplete instead used three private bases and a thirteen-slot
interface approximation. The canonical CreateModule header records the target
constructor's interfaces at +0x0C/+0x10, its flag at +0x14, and the four-slot
CreateModuleInterface table. The function's existing ledger evidence identifies
interface slot 1 and the slot-3 gate. These target facts support adopting that
header; the Zero Hour names documented there are donor evidence, not a claim
that its source path is BFME 2's.

The donor now derives from CreateModule, calls shouldDoOnBuildComplete,
getModuleData, CreateModule::onBuildComplete and getObject, and removes the three
private base approximations. It retains the same upgrade-grant behavior.

Verification:

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Create/GrantUpgradeCreate_onBuildComplete.cpp`:
  1/1 matched, 78 bytes; string, float and import checks pass.
- `find_declared_unmatched.py` before and after: all definitions matched.
- `header_adopt_lane.py accept --class CreateModule` for this source: PASS;
  there was no header-queue row to retire.
- `link_check.py` for this source: clean, LINKED 78 -> 78 bytes against census
  `8661f15284` (2026-11-03 20:03). This is a preview, not a new census result.
- `link_check.py --new-variants` for this source: exit 0, no findings.
- COFF external comparison against the saved pre-edit normal build object:
  all six old definition/reference pairs retained; no removals. Added inline
  definitions are Module::getModuleData, ObjectModule::getObject and
  CreateModule::onBuildComplete. No alternatename pragma was removed.

The initial merge dry-run accepted no donors. Remaining diagnostics were a
StringBase redefinition in ModuleDataCtor, ModuleDataDtor byte differences,
UpgradeStatusType redefinition for onBuildComplete, Player redefinition for
onCreate, and SubsystemInterface redefinition for PoolKey. The seed and donors
still need declaration reconciliation before a tool-driven merge. This repair
only resolves onBuildComplete's incompatible base hierarchy; no merge or source
file reduction is claimed, and the merge dry-run was not repeated afterward.
