# Carryover helper handoff — 2026-11-02

Read-only survey; no new compilation, Code/tool/ledger edits, network or claims.
The real assignment is available, typed Construct45 is committed as
028f21b0c2, and the shared CarryoverUnit header is established. Keep all existing
synthetic providers while adding independently verified typed twins.

## Smallest next step

Add only `fill<CarryoverUnit *, CarryoverUnit>` beside the existing fill owner
in `Code/Libraries/Source/WWVegas/WWLib/stlport_asciistring_record_bodies.cpp`.
Native RVA **1EB84E, 32 bytes** calls assignment **1EB20E** at **1EB85B**.
The live source object is a CarryoverUnit: fill-insert constructs its stack
temporary through copy1EB79E, passes that exact temporary to fill at1EBF3F and
1EBF8B, then destroys it through37DEE4. This is target typeflow, beyond stride
similarity. Existing code performs no field access itself.

The minimal private candidate is the canonical header include plus an explicit
instantiation of the existing STLport `fill` template. Preserve the existing
`fill<BfmeAssignRecord172 *, BfmeAssignRecord172>` row and its other callers.
Do not rename the class or replace its owner. If exact, admit via
`add_match.py --icf-owner` against that existing32B row. The expected relocation
change is from BfmeAssignRecord172::operator= to the already verified
CarryoverUnit::operator= twin at the same native1EB20E; prove address-resolved
equivalence rather than claiming the two raw mangled relocation names equal.

There are43 existing rows in this provider: private baseline/candidate proof
must preserve every row and every retained complete definition before normal
verification and publication.

## Native dependency chain

| Native RVA / bytes | Operation and current owner | Required relation |
| --- | --- | --- |
| 1EB20E /84 | real CarryoverUnit assignment in Common/CarryoverUnit.cpp; old BfmeAssignRecord172Assign.cpp retained | Already available. |
| 1EB84E /32 | fill<BfmeAssignRecord172> in WWLib/stlport_asciistring_record_bodies.cpp | Best next typed twin; calls1EB20E. |
| 1EB262 /54 | __copy_backward<BfmeAssignRecord172*,…> in the same43-row provider | Calls1EB20E at1EB289; next inner backward-loop twin. |
| 1EB831 /29 | __copy_backward_ptrs<Rva001EB831Element*,…> in WWLib/StlSweepW5Rva001EB831.cpp | Calls1EB262 at1EB844. Retain the old wrapper; its historical9B declaration is not a real class layout. LinearCampaignCarryoverInsert.cpp already supplies a separate172B view and verified visible loop. |
| 1EB9E6 /45 | _Construct<BfmePod172> plus new _Construct<CarryoverUnit> in WWLib/stlport_construct_pod172.cpp | Typed provider now committed. Calls real copy1EB79E. |
| 1EBA30 /47 | __uninitialized_copy<const BfmePod172*,BfmePod172*> in WWLib/stlport_pod_vector_bodies.cpp | Calls Construct at1EBA48. Fill and overflow need the **nonconst** CarryoverUnit* input variant; preserve/prove both real ICF spellings. |
| 1EBA5F /40 | __uninitialized_fill_n<BfmePod172*,unsigned,BfmePod172> in the same157-row provider | Calls Construct at1EBA72. |
| 1EBAB4 /27 | uninitialized_fill_n<BfmePod172*,unsigned,BfmePod172> in that provider | Calls1EBA5F at1EBAC5. |
| 1EBD3B /191 | vector<BfmePod172>::_M_insert_overflow in WWLib/Rva001EBD3BFinish.cpp | Calls allocation1EAEBD, copy1EBA30, Construct1EB9E6, uninitialized fill1EBA5F and clear1EB9C8. Later connected typed operation. |

Direct native1EBEAB calls are recorded in `native-helper-calls.json`:
copy1EB79E; uninitialized copy1EBA30 twice; backward wrapper1EB831;
fill1EB84E twice; uninitialized-fill wrapper1EBAB4; dtor37DEE4;
overflow1EBD3B. Ordinary forward `copy`1EBACF/27B is used by the adjacent
range-insert family, not directly by this fill-insert. Its owners are
WWLib/StlportCopyWrapperPairsFamily.cpp and Rva001EBACFRangeForward.cpp;
avoid expanding this step into that separate caller migration.

## Include context, placement and reservations

The43-row assignment-helper source already includes the same canonical
`ascii_string.h` after `<vector>/<map>`. It declares neither Snapshot nor
CarryoverUnit and defines no Snapshot profile selector. CarryoverUnit.h itself
adds no STL include. Thus source inspection found **no known Snapshot/STL
collision** for a canonical include placed after the existing includes. This
is an uncompiled next hypothesis, not a verified adoption result. No local
real-class copy, new pragma, alias or pin is needed.

Fresh in-memory mapping in `fresh-tu-map.json` deliberately leaves the generic
fill/backward/uninitialized/Construct addresses unassigned; `tu_map.homeless`
recognizes their template identities. That is template-emission eligibility,
not explicit approval to a named retail TU. Adding an ICF twin beside its
current owner moves no row; `tu_skeleton.fold_alias` makes such twins follow
their actual emission. The parent fill1EBEAB and overflow1EBD3B are explicitly
approved to GameLogic/System/LinearCampaignManager.cpp; parent funclets76A5CC
and76A5D7 inherit that approved home. Do not move those parent rows into a new
helper file or infer helper approval from neighboring addresses.

Local cached claim-mirror inspection found no relevant helper/file entries,
but this **is not a current reservation grant**. Root must acquire the32B RVA
and provider-file scope before editing. No network claim query was performed.
See `cached-relevant-claims.json`.

The43-row provider has seven existing alternatename hatch entries, all
unrelated to this typed fill. Preserve them. Narrow register checks found no
source entry in gate baseline, identity baseline, data debt/convergence,
header queue, flag overrides or pin-consistency baseline. The157-row
uninitialized-helper provider has a separate CreateAHeroManager header-queue
item; retain it.

## Later boundary

Do not mechanically transfer the old BfmePod172 Construct declaration's
`__declspec(nothrow)` to the typed helper. The157-row source suppresses cleanup
through that historical declaration, while generic uninitialized algorithms
contain `_STLP_TRY/_STLP_UNWIND` destruction. The typed Construct now has a
verified complete EH graph. Achieving47/40B typed uninitialized bodies needs
an independently supported exception contract or existing evidenced template
configuration; absence of native caller EH does not establish no-throw.
This is why the32B assignment-only fill is the cheaper next step.
