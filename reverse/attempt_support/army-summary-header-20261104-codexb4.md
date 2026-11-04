# ArmySummary scalar consumers: canonical header adoption

Inspected base: `4642058575`; date: 2026-11-04; model: gpt-6.1-sol.

## Retained changes

Three pointer consumers replace their private ArmySummary declarations with
`Code/GameEngine/Include/GameLogic/ArmySummary.h`. The header is unchanged.
Target member accesses stay at +0x14 (byte), +0x1C (int), and +0x2C (int),
using its existing field14/field1C/field2C members. Existing nonvirtual method
signatures, calls, flags, rows, pins and source paths are unchanged.

| Source (under Code/GameEngine/Source/) | Matched rows | Ordinary preview bytes |
| --- | ---: | ---: |
| GameLogic/System/ArmySummarySystemWalkOn.cpp | 2 | 122 -> 122 |
| GameLogic/System/ArmySummarySystemLoad.cpp | 1 | 637 -> 637 |
| GameLogic/System/LivingWorld/AutoResolve/LivingWorldAutoResolveApplyResults.cpp | 7 | 577 -> 577 |

Verification:

- Before editing, find_declared_unmatched.py reports every defined function
  already matched; the post-edit checks report the same for all three sources.
- `./build.sh` over all three passes 10/10 rows and all reference checks.
  The applyResults compiler-local labels renumber; its parent EH graph still
  places the three rowed funclets at their original retail addresses.
- `tools/eh_verify.py` on applyResults reports one EXACT graph, zero failures.
- `tools/link_check.py --fetch-index` fetches the published 2026-11-04 12:23
  index at `40fe1783d7` and imports 18,321 compiled objects. Ordinary preview
  of the three current objects reports 3/3 LINKS and 1,336 -> 1,336 bytes.
- `tools/header_adopt_lane.py accept --class ArmySummary` passes all three
  before and after fetching that index. Only that tool removes their three
  rows from reverse/header_queue.tsv. Seventeen ArmySummary rows remain.

This preserves the stated ordinary-preview scope; it is neither a new census
nor a whole-image/runtime closure result. No data/identity debt is retired.

## Reverted fourth trial and remaining prerequisite

Rva002B2AFDSelect.cpp's visitor at RVA 0x002B31DB (23 bytes) uses a private
ArmySummary state word at +0x2C. Replacing that declaration with the canonical
header and changing the access to field2C fails compilation: the existing
LivingWorldBattle.h emits C1189, requiring its registered Snapshot name,
capitalized method and reference-transfer surface. ArmySummary.h includes
Snapshot earlier with its lowercase pointer-transfer surface. This is a
shared-base declaration prerequisite, not a missing body or new regression.
The source is restored exactly; its queue row remains and file claim is released.

Next: reconcile the canonical ArmySummary/Snapshot override surface with the
LivingWorldBattle consumer under the shared-header owner's dependent scope,
then verify both families before retrying adoption. No flag, shim, virtual-slot,
header or alias workaround is retained. The other unattempted queue rows retain
their existing representation/API prerequisites.
