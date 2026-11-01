# Browser COM GUID ownership, 2026-11-01

Control `821bd9d380`; published index `0d24c60eef`.

The browser initialization unit and the 141-byte CreateInstance provider used
different spellings of the same native GUIDs. The existing C-linkage
IID_IUnknown definition is at RVA 7D4E4C; the existing g_bfmeIidTSA owner is at
7D4E3C. No new global, pin, alias or code row is added.

The initialization unit has a TU-local inline specialization of the bundled
VS2003 comip.h operation. It preserves release/create/OleRun/query/release,
direct creation and failure-null behavior, using the existing IUnknown GUID.
The provider uses that same IUnknown owner and the existing browser GetIID
specialization. The UUID template argument remains unchanged, preserving the
toolchain's type and function names. Pristine SDK files are untouched.

The earlier one-sided attempt lost the initialization unit. Changing only
IUnknown on both sides also leaves a 141-byte COMDAT conflict: the browser IID
relocation names still differ. The final repair aligns both GUID references
in both implementations. Their complete 141 raw bytes AND symbolic relocation
tuples are identical. No conflicting copy is suppressed or hidden.

## Verification

- Normal and strict controls pass all 8 rows, one existing data row, two string
  literals and nine named imports across both units.
- The initialization parent's EH graph is EXACT; all four existing cleanup
  labels are verified through their native parent graph after renumbering.
- Frozen scans pass for both complete source files.
- The original/current private comparison retains all 27 external code
  definitions (23 + 4), adding/removing none. All raw code bytes are identical;
  five definitions change only their GUID relocation names.
- The existing IID_IUnknown definition's 16 bytes equal retail, without data
  relocations. This is bounded object evidence, not a new image-ownership
  receipt or data-ledger admission.
- Before and after paired previews are 2/2 LINKS, 912 -> 912 authored bytes
  (771 initialization, 141 provider). The prior unreferenced GetIID diagnostics
  disappear in the final pair.
- `repair_queue.py retire data` removes the initialization unit's sole GUID
  wrong-name key, with zero remaining source findings. The register only shrinks.

This retires one data-identity debt entry. It claims no new matched bytes,
source-file reduction, census-linked gain or runtime result. Wider affected
consumer verification follows the publication audit and scheduled census.
