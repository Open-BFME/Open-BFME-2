### LINK-130: renderer category-list callbacks use the donor template identity

Status: Repair landed / awaiting verification; constructor identity retirement blocked. Updated: 2026-10-28; inspected parent: `5ca3063071`; ordinary-preview index: `14dc3d2467`.

Evidence / affected units: `WW3D2/dx8renderer.cpp`'s FVF array callbacks and unwind rows name the donor's list template rather than the existing `TextureCategoryList` destructor owner. [Scoped evidence and remaining prerequisites](../../reverse/attempt_support/fvf-category-list-identity-20261028-codexb5.md).

Completed: use that existing class identity through a local declaration. Renderer bytes remain 86/86 exact, all five EH graphs EXACT; seven destructor bindings become owner references. The 39-byte constructor and its one-slot vtable recursively prove retail, and the vtable/deleting thunk agree with the existing destructor provider. No row, pin, shared header or source-path change.

Remaining / next check: identity retirement refuses missing/stale provider receipts and two constructor bindings whose local vtable definition the identity checker does not carry. All three registered keys remain. The paired preview retains the pre-existing inherited-render-data accessor dependency; its provider in `rendobj.cpp` is outside the preview's underlying census. Carry removed template-provider consumers and current accessor closure into the next census; do not infer a newly lost link from the unchanged preview.

Post-rebase verification (`b3739a6dfd`): both outgoing edited providers have strict receipts, 96/96 function rows and two data rows exact, six EH graphs EXACT. The outgoing audit remains INCONCLUSIVE because the index predates its base and lacks per-object consumer names. The hook's shadow Matrix3D subscript divergence has an unchanged 12-byte COMDAT fingerprint; retain it as an inherited class-view prerequisite, not a new list-repair regression.

Clearance: byte/EH verification and seven destructor bindings only; full renderer linking and registered retirement remain open. Census confirmation: not claimed.
