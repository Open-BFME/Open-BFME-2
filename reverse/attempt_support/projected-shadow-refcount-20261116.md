# Projected-shadow RefCount provider reconciliation

The destination previously reached the donor RefCountClass before the canonical
RenderObjClass header. The reader emits the canonical non-const Release_Ref;
the destination instead emitted the donor const overload. The composer refused
the missing reader provider.

Including RefCountData.h alone preserved 64/64 rows but removed the seven-byte
destructor and changed the deleting wrapper from the retail 29 bytes to a
non-retail 28 bytes. That trial was reverted. Supplying the real empty inline
destructor, already identified by the ledger at RVA 0x00072892, preserves both
destructor providers. This is a TU-local definition, not a shared-header change.

The final provider comparison adds only canonical Release_Ref (10 bytes) and
changes Delete_This to the retail 20-byte body. Both are judged retail; the
29-byte deleting destructor remains retail. The donor const Release_Ref is
removed. Official build passes 64/64, EH verification is EXACT 9/9, canonical
header acceptance passes, and scoped preview remains 3,466 bytes. The preview
uses the cached census at 061d53ad84 and is not whole-image verification.

Logs: build/decal-diagnostic/seed-refcount-inline-*.

Before this change, the official writer merge passed 74/74 rows and ten EH
graphs but its commit hook correctly refused private DX8Wrapper and WW3D copies
in the destination. The entire uncommitted merge was saved as
build/decal-diagnostic/writer-merge-blocked.patch and reverted. Those classes
were held by another worker then; their claims have since become available and
were acquired for the next adoption. No hook was bypassed. The reader still
requires a separate investigation of the disappearing std::max<float> COMDAT.
Neither the merge nor selection rendering has been verified in a game image.

## Follow-up after render-state header adoption

The writer now uses canonical WW3D, StringClass and DX8Wrapper declarations.
Its ten rows, EH graph and every external provider fingerprint are unchanged;
all three official header acceptances passed. The next official dry run
(canonical-statics-merge-dry.log) still accepts no donor. The seed's transitive
reference headers already define StringClass, so including StringClassData.h
in the composed file reports C2011 and a duplicate inline destructor. Also,
the reference d3d8_shim_validated.h typedefs D3DTRANSFORMSTATETYPE to
_D3DTRANSFORMSTATETYPE but does not define the SDK's _D3D8TYPES_H_ guard;
DX8WrapperClass.h consequently forward-declares a different enum (C2371).
These conflicts require reconciling the actual header dependencies, not
manually merging or suppressing compiler diagnostics.

The reader now has only the missing std::max<float> provider refusal. Its byte
comparison succeeds. The old census has no reference to that name, but a
complete ProviderGuard proof covering the current replacement objects is still
needed before classifying this as a false rejection or changing the gate.
No verifier changes were made in this round. No actual merge was applied.

## Direct dependencies and complete reference proof

The destination now includes hash.h and StringClassData.h instead of unused
assetmgr.h, and windows.h instead of d3d8.h. Its only direct D3D dependencies
are four buffer pointers; spell their existing struct-pointer types directly.
The first trial exposed the missing LP typedefs and was completed by spelling
those same types, without defining SDK guards. Remove unused SHADOW_DECAL_FVF.
All 64 rows, nine EH graphs and external provider fingerprints are preserved.
The official composer accepts the writer after these changes.

The reader's std::max<float> refusal was observed without altering the official
guard's return value. Initially its reference proof was unavailable because
MappedImageCache.obj was missing. Building that unchanged source with build.sh
passes 5/5 and completes the proof. The guard now establishes that no reference
names the removed ANY COMDAT (digest 3d03d1a05786), but its unconditional missing
definition clause still rejects it. This is the bounded false rejection to fix
separately with a regression test; no exemption has been applied to source.
