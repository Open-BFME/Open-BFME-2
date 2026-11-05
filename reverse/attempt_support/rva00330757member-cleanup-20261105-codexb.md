# Rva00330757Member cleanup reconciliation, 2026-11-05

Inspected revision: `5bfe6bc044` (upstream `742bc117a2`). The header and
eleven queued consumers were claimed through the header picker. This pass
changes three consumers; the other eight retain their queue rows.

The unchanged canonical header records target-proven scalar storage and a
16-byte extent, with unknown original class and element identities. Each
retained unit includes it and defines its existing nullable-free destructor
inline outside the class, preserving the unit's allocator and compiler flags.

- Rva0053947DDtor.cpp no longer invents inheritance from its forEach call
  view. Its canonical base owns the storage and teardown. The callback uses
  the existing call view cast from the canonical base address.
- Rva005D4C61Dtor.cpp lets the canonical member destroy its buffer instead
  of freeing it explicitly in the containing list's destructor.
- Common/System/Rva005A71B1Dtor.cpp likewise lets its canonical member
  perform cleanup instead of an explicit free in the containing base.

No shared header, source path, row, pin, alias or hatch changes. No donor name
or recovered element type is claimed. The first build diagnosed a missing
include search directory; relative includes to the canonical header fix it.

Verification of the final sources:

- `find_declared_unmatched.py` passes before and after editing.
- `./build.sh Rva0053947DDtor.cpp Rva005D4C61Dtor.cpp
  Rva005A71B1Dtor.cpp`: 33/33 function rows and one data row pass;
  nine funclet rows verify through parent EH data. String, float and
  import-reference checks pass.
- `header_adopt_lane.py accept --class Rva00330757Member` for the three
  full paths passes and retires exactly their three header-queue rows.
- Ordinary joint `link_check.py` against index `112a456a2c`,
  2026-11-05 15:52, reports all three LINKS, preserving 1,195 bytes:
  237 for Rva0053947DDtor, 247 for Rva005D4C61Dtor and 711 for
  Common/System/Rva005A71B1Dtor. These are preview results, not a new
  census or real-link measurement.
- `check_csv.py` and `git diff --check` pass.

LINK-214 remains open for eight consumers. Constructor-emitting vector/Header
views and SecondaryBase's release helper still need reconciliation. Other
consumers have scope-sensitive field names; this pass does not retry them.
