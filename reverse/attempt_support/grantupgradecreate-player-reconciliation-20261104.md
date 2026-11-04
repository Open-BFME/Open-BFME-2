# GrantUpgradeCreate Player declarations

Base: `15c42cb052`. Scope: the approved GrantUpgradeCreate TU and its five
unmerged donors. The Create-subsystem consolidation planner was regenerated
for this pass. No source path, ledger owner, pin, alias or hatch changed.

The seed included Zero Hour's `Common/Player.h`, while onCreate already included
the canonical BFME2 Player header. The supported merge dry run accepted no
donors and diagnosed a Player redefinition for onCreate. The seed now includes
the same canonical header explicitly. This uses the existing target declaration;
it does not infer Player's target layout from the donor header.

Verification after the include change:

- `./build.sh GrantUpgradeCreate.cpp`: 2/2 code rows and one data row exact;
  string, float and import checks pass.
- `./build.sh GrantUpgradeCreate_onCreate.cpp`: 1/1 code row exact; string,
  float and import checks pass.
- `find_declared_unmatched.py` passes for both files, before and after the edit.
  The seed retains its existing present-unmatched markers.
- `header_adopt_lane.py accept --class Player` passes for both files. It retires
  the one outstanding onCreate row from `reverse/header_queue.tsv`; the seed
  had no queue row. No register line was removed by hand.
- `link_check.py` preserves seed 59 -> 59 and onCreate 118 -> 118 bytes against
  census `a62ac1c10b` (2026-11-04 07:28). These are previews, not census gains.
- `link_check.py --new-variants` for the seed exits 0 with no findings.

The pre-edit merge dry run also rejected PoolKey (SubsystemInterface
redefinition), onBuildComplete (Module/ObjectModule redefinitions), ModuleDataCtor
(StringBase redefinition) and ModuleDataDtor (bytes). No merge was applied.
After the Player edit, `tu_views.py --dry-run` still reports that no one
GrantUpgradeCreate view declares every virtual slot, and that ModuleDataCtor's
ordinary declaration conflicts with ModuleDataDtor's `novtable` declaration.
Its Object plan covers the two identical private donor views, not the Object
header included by the seed. Next work must reconcile the seed's module and
Object headers with the donor views and prove the ModuleData lifetime shapes;
this pass does not claim the whole TU is ready to merge.
