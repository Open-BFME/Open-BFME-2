# Sorting renderer private list ownership

Status: blocked on complete native storage/visibility or TU recovery.

2026-11-06 current check atbaa896fe56: SortingRendererBFME1.cpp26/26 passes.
Its five registered DX8-global names are already corrected. Data retirement
properly refuses two newer local-list findings; no baseline key is removed.

Current COFF/native evidence shows three separate private list views among
SortingRendererBFME1.cpp, sortingrenderer.cpp and SortingNodeStructDtor.cpp,
plus four-byte pointer owners in Rva007B6880Thunks.cpp. Retail has one pair of
twelve-byte objects atDB6200/DB620C. Clean+4 is a field, not another global.
The7B7090/7B70A0 vptr restorers are atexit cleanups registered by7ACD90/7ACDA0.
[Current evidence and supported prerequisites](../../reverse/attempt_support/sorting-list-ownership-20261106/README.md).

Both obvious sharing trials are already rejected in prior evidence: full extern
lists change five bodies; owner casts add null checks in Deinit151B and still
lack full storage. No unchanged retry or new alias was attempted here. Reconcile
native layout, visibility, vtable/lifetime and all readers together. Approved
renderer rows permit partial TU recovery; mixed/proposed Get_Sorting_Struct/
Insert and other ownership must be resolved before complete reunification.

The proposed/cached-map observations in the audit grant no move approval; use
the fresh owning-tool map. This entry records an actual data-state problem,
not a missing-body regression, gate false reject or measured runtime failure.

## 2026-11-20 Retirement recheck

The selected `0x009EDA98` reference already uses the existing `number_of_DX8_calls` declaration. At `2e03601b5dc`, the ordinary build passes 26/26 rows and the parent EH graph is exact. The owning retirement command reports `duplicate-def` and `wrong-name` for each of `_sorted_list` (`0x009B6200`) and `_clean_list` (`0x009B620C`). Both current renderer objects still contain private 12-byte list prefixes for both addresses. The source and all five registered DX8 keys stay unchanged. The existing storage and TU ownership prerequisites still apply.
