# Collision plane provider reconciliation

Inputs: BFME 2 `222bc9bf5ba245815f7222005485a881f38c129a`; committed and checked-out BFME 1 `34f59164f6d1efd413c5fd37f4894ec834c3c0fe`. The relevant donor math headers are unchanged from `6583` through `c1f3` to `34f`. No shared headers, compiler settings, symbol pins or function identities are changed. This repairs existing matches: +0 new C++ exact bytes.

## Reference pass

Reviewed BFME 1 `b307a865be972` (QueueProductionExit/Vector3 provider repair): rehoming an existing exact row to a natural emitter applies here; its callback change is unrelated. `29a91c09531b` (Test_Aligned_Box) and `fd416e8919c5` (_CIpow binding) are already inherited in CollisionMathLineBox.cpp and imports_000.cpp. No direct get_far_extent repair was found in those donor repairs. The committed lift_lane.py pass returned 150 servable lifts/93,785 bytes but no PlaneClass/Vector3/CollisionMath lead for this scope.

## Target and donor evidence

Existing native rows establish get_far_extent at 0x0007B5C8/112 and Plane/Point Overlap_Test at 0x0007B638/86. The point provider reads normal components at offsets 0/4/8 and distance 12. The existing 94-byte caller at 0x0007B68E supplies the normal at offset 0, then compares the point-test result with 1. PlaneClass's complete declaration and enum meanings come from donor plane.h/colmath.h. The second argument remains address-named: these bytes do not independently establish its full identity/layout.

The earlier census at fb21f507c7 selected the wrong aabtreecull get_far_extent copy (digest 5def687a518b), ahead of the exact split provider (9cdec647b215). Remove that surplus copy and the same wrong copies from colmathplane/colmathfrustum. Preserve the donor expressions as private forced-inline helpers where the matched native consumers already inline them; external calls use the existing exact provider. The split provider is a normal definition, replacing its artificial emission wrapper. No new emission anchor is introduced.

Rehome the unchanged native sign predicate 0x0007B29D/15 from aabtreecull to its natural emitter colmathplane with add_match. All 15 bytes verify. The three consumer units also emitted wrong 91-byte Plane/Point copies; their matched rows already inline the calculation. Keep this math source-local, passing the real private CollisionMath epsilon from the member callers, and let the existing 86-byte provider own the external symbol.

Rva0007BA09Bodies now uses existing bfme2_vector3 and donor PlaneClass/CollisionMath declarations instead of a private Vector3, opaque 96-byte PlaneClass and partial enum. colmathplane also adopts bfme2_vector3. Its genuine returned-value negation helper default-constructs, Set's the negated components and returns the vector, preserving the 600-byte OBBox body without emitting the wrong three-float constructor. Broad adoption in aabtreecull/frustum changed native bytes, so those views are retained rather than changing a shared header.

The existing Frustum/Sphere row 0x00719A20/77 already names the real source method. Its whole body verifies directly, with the rowed Plane/Sphere callee 0x007151F0/85. Retire redundant gen-alias/object-symbol metadata with add_match; this adds no coverage. Remove five obsolete present-unmatched occurrences and that one object-symbol hatch from the shrink-only register.

## Verification and remaining link debt

Normal build: all 38 existing rows across the five changed sources pass whole-byte, extent, float, string and import checks. The declared-unmatched guard passes. A normal census with all 20,004 objects present completed successfully at 2026-10-08 17:30 UTC, rules retail-truth-1, compile receipt run 99367d2dd6c14d39a99dbcc2a6e5fb81. Objects digest: 7a3b33b57ff4607890e1c4e55b86b13291ed66e5ad23c410da8469c4a43d43ac. A private immutable snapshot preserves its index, exact initial patch, source hashes and receipts.

The fresh census plus final peer-aware link_check predicts colmathplane becomes LINKS 2,198 bytes (previously 0). Rva0007BA09Bodies links 167 bytes. Frustum retains its incompatible Vector3 three-float constructor; aabtreecull retains separate RefCount/AABox/locking/pool blockers. The 112-byte exact provider still conflicts with wrong surplus inline copies from unchanged MeshClassRender and Rva0092CC40BoxOutsideFrustum. Those two callers have no out-of-line helper calls in their matched bodies. A bounded trial keeping donor math local and substituting target-proven immutable epsilon 0x358637BD at .rdata 0x008EFC94 changed scheduling/registers in their 1,126/208-byte bodies; both trials were reverted completely and their scope claims released. No nonmatching code, extra alias or debt allowance remains. These are separate follow-up repairs, not new recovered bodies.

The final link preview is measured against the successful census's index with all five changed providers/consumers replaced together. The index is preserved for other seats to refresh normally. No census history row or rule rebaseline is edited.
