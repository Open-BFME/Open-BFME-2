### LINK-244: W3DMouse's split flag blocks data-debt retirement
Status: Blocked. Updated: 2026-11-04; inspected revision: 4ee23edebd.
Evidence / affected units: `W3DMouse.cpp`, `W3DMouseInitW3DAssets.cpp`, `Rva007B6880Thunks.cpp`; [repair and codegen evidence](../../reverse/attempt_support/w3dmouse-data-identity-20261104-codex4.md).
Completed: shared real eight-byte mutex objects replace the separate four-byte cleanup providers; 923/923 functions and 18 data rows verify. W3DMouse's 776 bytes pass a current-object link preview against index f6d845ecd4.
Remaining / next check: remove the duplicated `isThread` without changing init's instruction order, or reconcile it in an approved TU merge after LINK-213; then rerun data retirement. The cleanup unit separately retains two unresolved array-name globals in this index.
Clearance: mutex wrong-name findings are absent; flag identity and debt retirement remain blocked, and no baseline key was retired.
Census confirmation: not claimed.


**2026-11-07 owner-placement trial.** Giving W3DMouse.cpp the external definition and moving the one-byte data row passes all six scoped data rows. It still changes the order of the clear in the 58-byte init body. A volatile mode comparison puts the compare back first but moves the thread-address load, so the source and data changes were reverted. [Trial evidence](../../reverse/attempt_support/w3dmouse-thread-flag-owner-20261107.md).
