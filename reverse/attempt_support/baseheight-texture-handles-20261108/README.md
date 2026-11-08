# Terrain texture handles use their canonical owning template

Rva0006D0D7Dtor.cpp replaces its private RefTex helper with the canonical
WWLib RefCountPtr<TextureClass> header. Five one-pointer members keep their
offsets and teardown order. The local TextureClass surface declares only the
already-rowed Release_Ref operation; it makes no complete layout claim.
Target placement and ownership come from the native destructor, not a donor
source-path claim.

All 25 retained rows pass the normal byte gate; the parent remains 735 bytes,
and its EH graph is EXACT. All 18 cleanup rows retain parent-proven locations.
The redundant 12-byte RefTex alias is retired through ledger_io.rewrite with a
deleted_rows tombstone. Its canonical RefCountPtr destructor owner at
0x0017098D remains rowed in streakRender.cpp, so no retail range loses coverage.
No source path, pin, shared header or verifier is changed.

The current index's complete touches inventory names only this source for
RefTex. The merge-oriented private LinkGuard still flags its old census row
ownership as a reference; this is recorded, not described as a clean guard.
The normal current-object preview reports LINKS, 817 -> 805 authored bytes:
the 12-byte change removes the redundant claim, not an implementation of a
distinct native function. Broader publication/selection verification remains
subject to the normal outgoing audit and the next census/image.

## Full-header investigation retained for the next pass

The unlanded full-header candidate includes canonical BaseHeightMap.h. Its
first trial used CRT free and shortened the destructor by eight bytes. The
existing TBuff/XferSaveAsText pattern, scoped to preloading vector, binds
allocator deallocation to the already-pinned _STL::free at 0x00030830. This
restores all 735 parent bytes and the exact EH graph. It verifies 21 of the old
26 rows. Three old helper aliases stop emitting; two vector cleanup rows
resolve their tail jump to the existing vector<bool> pin 0x00142D70, while
retail uses 0x0007FAB3. Both complete 14-byte native bodies call 0x00030830 and
are relocation twins. Neither address calls a different free routine.

This observation alone does not authorize changing a pin or masking a call.
No such change is landed. The full-header LinkGuard also exposes twelve
unresolved virtual names, two table-selection findings and four removed helper
providers. The attached candidate and reports are investigation evidence,
not a verified reconstruction in Code. Its bounded TextureClass inheritance
view is experimental and is not claimed as a recovered complete class.

The primary table still has 129 of retail's 148 slots, and the Snapshot view
still has one of four. This pass claims only canonical texture-handle lifetime
cleanup. It does not establish a new linked image or runtime progress.

Published as e45a923881 on the first push attempt (34.7 seconds). Required
gates pass all 25 rows, scoped DIR32 for seven symbols, the exact parent EH
graph and converged data. name_dependents finds zero outside users of the
retired helper. The outgoing audit remains INCONCLUSIVE: index f4727bbd09
versus base eba83a23bec9a0ccf16e8e8bbf244379acf77da4, one source without a
current audit receipt (this destructor). The code-identity shadow report also
retains the array helper Rva001F3574Vec's two bindings to Snapshot's folded
destructor; this pass does not repair that independent helper identity.
