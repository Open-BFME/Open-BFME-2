# Native-provider repair for the 36-byte fill-insert

Source base: `c647a75e55`. Claimed parent `0x001524F9`, wrapper
`0x00152659`, unwind `0x00766C94`, handler `0x00766C9C`, and source
`Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva001524F9.cpp`.
This is LINK-002 cleanup of four existing matched rows; no coverage is added.

Target facts:

| Call RVA | Native destination | Existing provider spelling |
| --- | --- | --- |
| 0x00152530 | 0x001513AD | Rva0007BB16Record copy constructor |
| 0x0015255F, 0x001525AB | 0x0010E5DE | __uninitialized_copy of Rva0007BB16Record pointers |
| 0x00152573 | 0x00151FE7 | __copy_backward_ptrs of BfmeAssignRecord36 pointers |
| 0x00152580, 0x001525C0 | 0x00151DF8 | fill of BfmeAssignRecord36 |
| 0x00152592 | 0x00151E15 | uninitialized_fill_n of Rva0007BB16Record |
| 0x001525CF | 0x0007BB16 | Rva0007BB16Record destructor |
| 0x001525E6 | 0x0007D8FE | vector<Rva0007BB16Record>::_M_insert_overflow |

The native stride is 36 bytes. These destinations establish ABI boundaries,
not an original application class name or a donor field layout. Both existing
record spellings remain structural views. Other uses of either spelling are
not thereby identified as this application type.

The source specializes STLport 4.5.3 count insertion in clean C++, binding
copy/destruction/uninitialized/overflow operations to the first view and
assignment operations to the second. A derived access-only view exposes the
protected overflow method without an emitted wrapper. Parent and wrapper
symbols stay unchanged, so the resize caller needs no edit. The four overflow
dependencies (allocation, deallocation, __destroy_aux and __destroy) and two
untagged fill helpers are declared as specializations. Tagged copy, backward
and overflow bodies remain visible to the compiler.

Compiler evidence:

- Declaration-only tagged helpers zero-initialize empty tag temporaries and
  enlarge the frame. Keeping the template form alone does not fix this.
- Named uninitialized tags restore the 258-byte extent but leave seven stack
  offsets wrong: old_finish uses +0x0C instead of +0x10 and three tag references
  use +0x13 instead of +0x0B. Changing scopes, const, inline or local names
  does not fix the complete body.
- Letting cl see the tagged helpers' ordinary bodies restores all bytes.
  An explicit member specialization also matches; no replacement of the
  generic vector template or shared-header edit is retained.

Seven obsolete Rva001524F9Element helper pins are removed. Current objects have
no references to those names; the parent and wrapper keep their opaque element
spelling. The hatch tool lowers pins 9405 -> 9398; unrelated address-global
tightening was reverted. External COMDATs fall 25 -> 14 and the old element's
unresolved constructor, destructor and assignment references disappear.

Verification:

- Frozen-file checks pass before and after. Ordinary builds verify 4/4 source
  rows and 8/8 with Rva00152BDBValueVectorResize.cpp. Parent EH is EXACT; its
  unwind label renumbers from $L4705 to $L4968, bound by the exact parent graph.
- Strict preparation verifies 132/132 rows across StlportVectorGrowthFootprints.cpp,
  stlport_asciistring_record_bodies.cpp, StlSweepW5Rva00151FE7.cpp and
  stlport_vector_rva0007bb16_destroy.cpp, plus 8/8 in the consumer pair.
- All six units preview LINKS against index 2026-10-30 10:11 at 12b9e7a7c0.
  The repaired source changes 0 -> 273 authored bytes; resize retains 152,
  and the providers retain 6470, 1396, 29 and 142. Total: 8189 -> 8462.
  This is a prediction, not a census gain.
- CSV, pin consistency and shadow data checks pass (zero data findings).
- Staged-tree consumer audit exits 2, INCONCLUSIVE: the index predates base
  c647a75e55 and an affected consumer lacks a current strict receipt, first
  Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp. This is not a
  clean full-consumer verdict. Carry that consumer and this repair into the
  next scheduled census. No nightly or census run was started.

LINK-002 is cleared only for this fill-insert's ordinary preview and verified
six-unit scope. Broader type unification, consumer verification and census
confirmation remain pending. Scratch trials and object snapshots are under
build/fill-insert-native-1524f9-codex3/.
