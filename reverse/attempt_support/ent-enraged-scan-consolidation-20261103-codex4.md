# EntEnragedUpdate scan declaration prerequisite

Inspected base: `bfec8f1807` (2026-11-03). Scope: Common/EntEnragedUpdate.cpp
and GameLogic/Object/Update/EntEnragedUpdateScan.cpp.

The first supported merge trial accepted no donors. The scan declared a flat
EntEnragedUpdate with module data at +4 and Object at +8, while the constructor
TU already used the canonical UpdateModule hierarchy (own fields start at
+0x20). Its module-data struct also used separate range/filter spellings.

The scan now uses the constructor TU's existing declarations and field names.
An explicit cast reads its derived module-data view; filter arguments take the
addresses of the existing four-byte handle members. Friendship permits the
scan methods to read those fields without exposing them publicly. This is
declaration reconciliation, not new evidence for original names or a complete
module-data lifetime recovery.

Verification before the prerequisite commit:

- `./build.sh` on both sources: 26/26 rows matched; strings, floats, imports
  and ten renumbered funclet labels verified.
- `find_declared_unmatched.py` on each source: all defined functions matched.
- `link_check.py --fetch-index`: retained census 2026-11-03 20:03 at
  `8661f15284`, imported 17,785 current-input-reusable object candidates.
- Current-object link previews: constructor LINKS 524 -> 524 bytes; scan LINKS
  342 -> 342 bytes. These predictions do not change census totals.
- Supported merge dry run now accepts the constructor and scan, 25 rows.
  No aliases or pins were removed or added.

Remaining donors: FamilyDeletingDtors_muse-x7q-eb73.cpp needs a compatible
EmitVtableTag constructor/lifetime view; EntEnragedUpdateModuleDataDtor.cpp
still fails merged bytes; EntEnragedUpdateUpdate.cpp needs the combined Object
fields/methods and compatible derived fields. Three mixed donors stay outside
the merge. Next step: commit this prerequisite, then use tu_skeleton --merge
for the accepted scan fragment and audit its new source ownership.
