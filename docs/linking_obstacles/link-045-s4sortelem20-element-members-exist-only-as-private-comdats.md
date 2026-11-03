### LINK-045: S4SortElem20 element members exist only as private COMDATs under a placeholder name
Status: Open. Updated: 2026-10-26; inspected revision: 25f8ba858f (index d1f046749a).
Evidence / affected units: the 20-byte S4 sort element is rowed under two
placeholder class names: copy ctor `??0Rva003371B1@@QAE@ABV0@@Z` 0x003371B1
(Rva003371B1Copy.cpp), dtor `??1Rva003371B1@@QAE@XZ` 0x003372B7
(Rva003371B1Dtor.cpp), assignment `??0Rva002E9E70@@QAE@ABV0@@Z` 0x003372EC
(Rva002E9E70Copy.cpp, named as a copy ctor but called as the assignment by
swap 0x003373D9); its unguarded linear insert 0x00337424 is rowed as
`?Rva00337424Insert@@...` (Rva00337424Insert.cpp). The STLport sort units name
the element `S4SortElem20` and reach those bodies through symbols.csv pins,
which the link does not use: `??0`/`??1S4SortElem20` resolve only through the
implicit COMDAT copies in stlport_unguarded_insertion_sort_s4sortelem20.cpp
(census provenance `unknown`), whose bodies still call the undefined
placeholder `BfmeSortElem20Tail` ctor/dtor. That unit itself fails on those
two names and on `__unguarded_linear_insert<S4SortElem20 *...>` (kept copy is
S4StlSortHelpers.cpp's, not retail's).
Completed: 797d6cd0f5 linked stlport_introsort_loop_s4sortelem20.cpp (+90 B,
link_check vs d1f046749a; all 8 S4SortElem20 units checked, none drops): its
tail assignment now calls the rowed vector<Rva00332217Record>::operator=
(0x332217) and the element ctor/dtor are declared out of line.
Remaining / next check: one element type and name for 0x3371B1 / 0x3372B7 /
0x3372EC / 0x337424 (rename the Rva003371B1 / Rva002E9E70 rows, or respell
the S4SortElem20 users onto them) so one unit defines each member; then drop
the insertion-sort unit's implicit copies and recheck it with
S4StlSortHelpers.cpp, partition and introsort units together.
Clearance: pending.
Census confirmation: awaiting.

**2026-10-26 current-provider follow-up, inspected `896af216804e`:** the assigned insertion-sort unit remains U2/S1 when checked alongside current `S4StlSortHelpers.cpp`; the helper unit still selects its nonretail linear-insert copy. Retail 0x00337555 calls the 67-byte record copy 0x003371B1 and 85-byte linear insert 0x00337424, both already rowed under the placeholder names recorded above. Its unresolved `BfmeSortElem20Tail` members come from the implicit local element copies, not separate calls in the matched 46-byte loop. Dropping those copies without reconciling the existing S4 users would remove their provider. No source edit or additional pin was attempted. Evidence: `build/link-worker-w5/retail-probe-final.log`, `index-probe.log`, `before-extra-providers.log` and `after-cohort.log`. Next: the existing cross-unit element/member identity reconciliation, preserving all consumers. No clearance or census confirmation claimed.

**Final-insertion helper repaired (2026-10-26, inspected `2a45addda1806342ac5c52757f63be902dcd428e`; ordinary-preview index `d1f046749a`, retail-truth-4):** `S4StlSortHelpers.cpp` now instantiates only its rowed final-insertion dispatcher, keeps its original `-GX-` flag and declares insertion sort without a body. Existing `stlport_introsort_loop_s4sortelem20.cpp` explicitly instantiates insertion sort using its unchanged EH-enabled flags, correct element lifetime and const-reference comparator. The consumer view uses canonical AsciiString storage, a byte flag and opaque three-pointer tail, with copy construction/destruction and nonthrowing assignment declared out of line. This removes unrelated wrappers and replaces the three selected-wrong insertion helpers with retail copies from the existing provider. `build/link-worker-w6/s4-verdicts.log` proves the final dispatcher, insertion sort, linear insert, unguarded sort, unguarded linear insert and comparator retail across the two objects. An intermediate flag-omission trial was rejected; `flag-directives.log` verifies that both retained sources preserve every original code-generation flag. All assigned and changed-provider rows byte-verify; declaration, EH, shadow data, CSV and pin checks pass. Paired current-object previews in `paired-before.log` / `paired-after.log` include every assigned unit, named provider and S4 consumer; `cohort-comparison.json` verifies completeness, no new named blocker and no lost linking unit. The helper unit is cleared in ordinary-preview scope; census confirmation pending. The insertion-loop provider still has the two BfmeSortElem20Tail lifetime references, so the broader element-name reconciliation remains open. Next check: reconcile that tail's actual vector copy/destructor owners without reviving the now-correct helper copies. Full receipts: `build/link-report.md`.

**2026-10-27 tail-owner check (claudeb, census index 2026-10-27 14:34 at `73061d9452`):** the insertion unit is still U2 (`??0`/`??1BfmeSortElem20Tail`). Retail callers show who owns the tail. 0x003321D8 has exactly one caller, element dtor 0x003372B7, so it is the +8 tail's destructor; its row is `??1Rva003321D8@@QAE@XZ` in RvaVectorDtorFamily.cpp. Tail copy 0x0033629E has exactly one caller, element copy 0x003371B1; its row is `vector<BfmeStringRecord000331962>`'s copy ctor. The only `??1?$vector@UBfmeStringRecord000331962...` in the index is a non-retail COMDAT in Rva003371B1Copy.obj. Index edges show every `??0`/`??1S4SortElem20` consumer is an STLport S4 instantiation: swap, `__linear_insert`, `__insertion_sort`, `__unguarded_insertion_sort_aux`, `__unguarded_partition` and `__unguarded_linear_insert`. The only providers are this unit's `unknown` COMDATs; the retail bodies are rowed as `Rva003371B1`. The remaining step is a class-identity decision: `S4SortElem20` is an unrecorded label and `Rva003371B1` a placeholder. Settle it through the name lane (`name_lane.py`) rather than a hand rename. Then one class name owns 0x3371B1/0x3372B7, and this unit can declare both out of line. Gluing the tail to two different names in this unit (copy via the vector, dtor via `Rva003321D8`) was considered and not attempted. No source edit.
