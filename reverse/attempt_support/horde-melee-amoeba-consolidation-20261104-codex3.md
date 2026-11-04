# HordeMeleeAmoeba consolidation prerequisites

Inspected revision: `132c321fb8e08b1e2c5414a3cae34048ccacc957`, 2026-11-04.
Scope: the provisional approved TU
`Code/Libraries/Source/WWVegas/WWLib/HordeMeleeAmoeba.cpp` and the six donors
selected by `next_work.py --claim`. No source path or ledger row moved.

## Retained repair

`HordeMeleeAmoeba_setUnitNeedsNewAttackPos.cpp` now includes the existing
`Code/GameEngine/Include/GameLogic/HordeMeleeAmoeba.h`. Removed its private
HordeMeleeAmoeba/base declarations and the local BfmePod60S12 record. The
canonical vector's 60-byte stride and needsPosition/index fields produce the
same bounds checks and stores at offsets 0x0C/0x10. No symbol identity changed.

The original and adopted sources each pass `./build.sh` (1/1, 52 bytes).
`find_declared_unmatched.py` passes. `header_adopt_lane.py accept --class
HordeMeleeAmoeba` passes and retires exactly the setter's header-queue row.
Before and after, `link_check.py` reports LINKS, 52 -> 52 bytes, against the
2026-11-03 20:03 census at `8661f15284`. This is a preview, not a new census.
`check_csv.py` and `git diff --check` pass.

## Merge and reconciliation verdicts

The supported consolidation planner ran under WWLib. Its file packets report
unresolved placement evidence, pragma/include context on the seed, an
unledgered emission anchor in the deleting-dtor donor, and internal linkage in
the overflow donor. These packets approve no routing. `tu_skeleton` uses the
current approved map and independently checks composition.

`tu_views.py` ran its merge dry-run and retained no edits, accepting 0/6 donors:

| Donor (WWLib unless otherwise shown) | Refusal / prerequisite |
| --- | --- |
| HordeMeleeAmoeba_setUnitNeedsNewAttackPos.cpp | Link guard: the merged object breaks another unit's `??_7HordeMeleeAmoeba@@6B@` copy. Reconcile the seed's emitted table and its provider closure before merging the setter. |
| FamilyDeletingDtors_Rva00587F69.cpp | C2511: the seed does not declare its EmitVtableTag constructor. The existing canonical-header handoff already proves adding the complete table exposes unresolved opaque slots; that failed experiment was not repeated. |
| stlport_sort_rva00588195.cpp | Link guard rejects the changed `copy_backward<Rva00588195Elem*>` COMDAT. Preserve its current linking status until selected-copy identity is reconciled. |
| stlport_pod60_vector_resize_default.cpp | C2953: duplicate allocator definition. |
| stlport_vector_rva00587375_overflow.cpp | C2118: negative extent assertion after incompatible Rva00587375 views compose. |
| Code/GameEngine/Source/GameLogic/Object/HordeMeleeAmoebaXfer.cpp | C3190: incompatible vector specialization/resize declarations. |

The view reconciler leaves Rva005D6FCC shared, defers registered
HordeMeleeAmoeba to the header lane, and refuses Rva00587375 because its ledger
names use both class and struct mangling. Its BfmePod60 superset trial adds an
EH frame to the seed's 73-byte by-value resize at 0x0058814C, failing 1/11 rows;
the tool restored the originals. The subsequent canonical-adoption probe
refuses the seed's vector<BfmeE16> and the setter's vector<BfmePod60S12> field
types. Only the setter was then manually reconciled and accepted as above.

The next seed repair needs native element/helper identity and lifetime
contracts; padding agreement alone does not justify vector<BfmeE16> becoming
vector<BfmePod60>. The overflow family remains covered by LINK-002. The existing
[canonical ABI evidence](hordeamoeba-canonical-qc10-20261031/README.md) separates
retail table facts from the unresolved method signatures.

## Register and binding audit

No merge was applied. The seed's two alternatename hatches and data-ledger key
remain untouched. Searches of the selected paths in code identity, data debt,
gate debt, hatch and MS-header registers found no donor key to transfer for
the retained source-only adoption. Other HordeMeleeAmoeba header-queue rows
remain. There are no outgoing source-path changes requiring consumer repoints.
The setter's before/after byte and link verdicts cover its changed field types;
there is no claim that the seed, other donors, whole family or game now links.
