### LINK-401: XferMD5CRC destructor merge changes the kept vtable
Status: Blocked. Updated: 2026-11-05; inspected revision: 2620447df6.
Evidence / affected units: `XferMD5CRC.cpp`, `Rva0052B497Dtor.cpp`, `OpaqueScalarDeletingDtorsB12.cpp`; [consolidation audit](../../reverse/attempt_support/xfermd5crc-consolidation-20261105.md).
Completed: declared `XferSave::Open` and merged the 73-byte open-method donor; all eight destination rows byte-match and its current-object link preview is clean.
Remaining / next check: reconcile the one-slot `Rva0052B497` vtable emitter with the derived destructor's inherited `XferEnum` slot, then verify providers and consumers together before retrying the destructor merge.
Clearance: pending for the destructor merge; its existing source is retained.
Census confirmation: none claimed; the accepted source move preserves already-linked coverage.
