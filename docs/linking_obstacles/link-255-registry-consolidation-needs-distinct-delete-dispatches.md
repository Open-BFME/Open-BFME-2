### LINK-255: registry consolidation needs distinct delete dispatches
Status: Blocked. Updated: 2026-11-04; inspected revision: c6adee4abf.
Evidence / affected units: registry.cpp and RegistryDeleteValues.cpp; [scoped trials and restored verification](../../reverse/attempt_support/registry-allocation-dispatch-20261104-codexb.md).
Completed: isolated the donor mismatch to array delete instead of retail scalar delete; removing the forced include fixes the donor but changes the separately rowed StringClass deleting destructor. All trial edits restored; 43/43 rows and both restored link previews pass.
Remaining / next check: recover a common source context preserving scalar delete at 0x006103D0 and array delete at 0x0011F6D8 before retrying the approved TU merge; NATIVE_COPY_ASSIGN alone does not resolve this boundary.
Clearance: pending; no source or ownership change.
Census confirmation: no new measurement claimed.
