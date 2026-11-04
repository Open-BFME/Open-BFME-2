# GrantUpgradeCreate lifecycle declarations

Inspected revision: `1f9f32d5c5`, 2026-11-04. All six consolidation file
scopes were claimed before investigation. This is a prerequisite repair;
no source is merged, no ledger owner moves and no debt key retires.

`GrantUpgradeCreate_onCreate.cpp` now includes the canonical CreateModule
header already used by onBuildComplete. The two leaf views declare the same
onCreate/onBuildComplete overrides. The unused constructor and Snapshot-era
crc/xfer/loadPostProcess/destructor declarations are removed from onCreate's
partial view; no function definition or external symbol is removed.

Target evidence is the canonical header's constructor/vtable analysis and
the existing matched leaf constructor at 0x004B8F62: the create interface is
at +0x10 and its first two slots are these two lifecycle bodies. This adopts
the existing target layout, without claiming a complete recovered leaf class
or importing a Zero Hour layout.

Verification:

- Before and after, normal `./build.sh` verifies both rows: onCreate
  0x004B901D, 118 bytes; onBuildComplete 0x004B9093, 78 bytes. String,
  float and import checks pass. Declared-unmatched checking passes.
- `header_adopt_lane.py accept --class CreateModule` passes for both files;
  neither had an outstanding queue key to remove.
- Saved original objects versus final objects: all five onCreate and four
  onBuildComplete code sections have identical raw bytes and symbolic
  relocation tuples. External definition/reference sets are identical.
- `link_check.py` preserves 118 -> 118 and 78 -> 78 bytes against census
  2026-11-04 17:56 at `8c757ea0db`. Both new-variant checks exit zero.
  These are previews, with no census or image-ownership gain claimed.
- The scoped naming child proposed all nine recognized bindings. Parent
  review retained all nine after the planner protected three proposals.
  The directly initialized `BfmeObject872Header tmp(...)` was inspected but
  is absent from the regex inventory and remains unchanged.

## Consolidation boundary

The pre-edit supported dry merge accepts no donors; its current census link
guard passes for all six sources. Rejections are PoolKey's SubsystemInterface
redefinition, onCreate's missing Object::rva00293077 in the seed header,
onBuildComplete's Module/ObjectModule redefinitions, ModuleDataCtor's
StringBase/leaf declaration conflicts, and ModuleDataDtor's byte difference.
The earlier Player conflict is already resolved by another repair.

After this repair, `tu_views.py --dry-run` still refuses the overall leaf
reconciliation because no view supplies all virtual slots. The two lifecycle
views now agree, but the seed still includes legacy module/leaf/Object headers.
ModuleDataCtor and ModuleDataDtor also disagree on novtable and lifetime shape.
The next step remains a verified seed/header and module-data reconciliation,
including its missing destructor/snapshot-name providers, before another merge.
No second full merge search repeats these unresolved prerequisite failures.

No alias, pin, hatch, source path or shared header changes. The ordinary
pre-push batch audit retains responsibility for wider consumer verification.
