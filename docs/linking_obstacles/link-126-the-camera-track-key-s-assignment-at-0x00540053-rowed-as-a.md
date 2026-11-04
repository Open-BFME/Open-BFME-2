### LINK-126: the camera-track key's assignment at 0x00540053 rowed as a pair copy constructor

**Status: Repair landed / awaiting verification. Updated: 2026-10-27; inspected revision: 472c3b46dc.**

- **Evidence / scope:** `StlSweepW4Rva00540053.cpp` rowed 0x00540053 (29 B) as
  `pair<const int, Rva00540053Element>`'s copy constructor and was unresolved on
  the element copy constructor, pinned onto 0x0053FFCE. That callee is the 9-dword
  frame assignment (`Rva0053FDE6::operator=`, folded with
  `SentenceDataStruct::operator=`). The copy constructor 0x00540036 calls
  0x0053FF5F instead. The callers are the stride-0x28 `__copy` (0x00540082),
  `__copy_backward` (0x005400FF) and `vector<Rva0054000B>::insert` (0x00540731).
  All three bound the body through `/alternatename`. The body is
  `Rva0054000B::operator=`.
- **Completed:** the row was re-identified as `??4Rva0054000B@@QAEAAV0@ABV0@@Z`
  in the same file. It calls the frame assignment through the
  `Render2DSentenceClass::SentenceDataStruct` forwarder that
  `Rva00540B48Append.cpp` already uses. The insert unit's alternatename is
  gone; the other two units' aliases now name the new row. The orphaned
  `??0Rva00540053Element` pin was removed. `./build.sh`: 46/46 exact over the
  four sources. `link_check.py` (index 73061d9452): StlSweepW4Rva00540053.cpp
  0 -> 29 B; StlSweepW5Rva00540082.cpp, stlport_asciistring_record_bodies.cpp,
  stlport_vector_rva0054000b_insert.cpp and Rva00540B48Append.cpp keep LINKS.
- **Completed (follow-up):** `__copy` 0x00540082, `__copy_backward` 0x005400FF
  and the `__copy_backward_ptrs` forwarder 0x00540197 were respelled over
  `Rva0054000B` in place (tombstones in `deleted_rows.csv`). Retail confirms
  each element call: 0x00540082 and 0x005400FF call 0x00540053, and 0x00540197
  calls 0x005400FF. The `BfmeAssignRecord40` and `Rva00540082Element`
  alternatenames are gone. Five pins went with them: the two retired element
  assignments, plus three `Rva0054000B` pins that only repeated their rows'
  names. The `BfmePod40` `__copy_ptrs` forwarder 0x0054014D now names
  `__copy<Rva0054000B *>`. `./build.sh`: the four edited sources are exact.
  `link_check.py` (index 73061d9452): all seven units keep LINKS.
- **Remaining / next check:** `vector<BfmePod40>` rows in this range
  (`_Vector_base` 0x0053FF92, `__copy_ptrs` 0x0054014D, `erase` 0x005401B4 and
  0x00540324, `__lower_bound` 0x00540253, `clear` 0x00540672, `reserve`
  0x0054067D) still use the size-only `BfmePod40` view. Check each one's callers
  before respelling it, because `BfmePod40` rows elsewhere fold other 40-byte
  types. The insert unit emits its own `__copy_backward` and
  `__copy_backward_ptrs<Rva0054000B *>` COMDATs. Declaring them only (so the
  rows serve them) makes its 0x00540731 body materialise the `__false_type` tag
  temp, so it no longer matches.
- **Clearance:** preview scope (the seven units above, including StlSweepW5Rva00540197.cpp and stlport_pod_vector_malloc_bodies.cpp).
- **Census confirmation:** awaiting the next census.

**2026-10-27 motchan AdaptiveDelta resolved:** d232da8fd4c adds `reference/shims/bfmemotchan/motchan.h` (project shim scoped by motchan.cpp's `// cl:` line; vendored header untouched) naming +0x10 `DataByteCount` in retail's 0x1C prefix; 871817034c0 swaps AdaptiveDeltaLoadW3D.cpp's `#include <new>` for plain `operator new[]`/`delete[]` declarations (still 1/1); ccdd57dcda0 merges both donors into motchan.cpp (21/21, link_check LINKS 984 -> 1,535 B). The shim keeps BFME1's `CacheFrame`/`CacheData` after +0x1C only for the present-unmatched getframe/decompress bodies. Pattern for other C2084 `<new>` collisions: declare the array operators instead of including `<new>`. Remaining merge-queue rejections (private STL/StringBase redefinitions, `Rva*` placeholder classes, udp names, matpass flags) are unchanged.
**2026-10-27 evening template-collision triage (no commit possible):** RayEffect's donor Rva002CEE1BDtor.cpp is a placeholder class (`Rva002CEE1B`) built against the `bfme2_ascii` StringBase shim while RayEffect.cpp sees the vendored `string_base.h`; using the real templates needs the donor recast as RayEffect's class (a rename to an existing class name, not approved). AIUnitUpgrader_shutdown.cpp depends on `/GX- /Oy- /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS` and dllimport force-inlined `vector<void*>` specialisations; AIUnitUpgrader.cpp is `/EHs` without those defines, so the bodies cannot share a TU without per-function optimisation pragmas. The picker's AptMyHero merge fails before any donor: the seed's private `cosf`/`sinf` inline wrappers collide under every merged flag set, and its donors span `/MD`-only, `/O1 /G7 /arch:SSE` and `/arch:SSE2` flag sets. `next_work --tier anchored`: byte matching complete; the link tier's top item (Rva005189CFText.cpp) already LINKS (279 B) pending the next census; link_rank's sole blockers are all registered above.

**2026-11-04 AptMyHero prerequisite update:** shared the complete `Rva005B1830` helper/record layout with its destructor caller (16/16 exact; LINKS 1,067 -> 1,067 B); merge still accepts 0/8 donors, with canonical-header and compile-environment prerequisites detailed in [the handoff](../../reverse/attempt_support/aptmyhero-helper-view-20261104.md).
