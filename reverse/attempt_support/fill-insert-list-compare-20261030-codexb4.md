# String-record fill-insert iterator comparison cleanup

Inspected source base: `a3dcf853f0`. Claimed RVA `0x005DE651` and source
`Code/Libraries/Source/WWVegas/WWLib/stlport_vector_stringrecord_5de651_fill_insert.cpp`.

The picker served one selected-provider blocker. Before the edit, the ordinary
preview reports `does not link`, with the selected
`??9_List_iterator_base@_STL@@QBE_NABU01@@Z` definition failing retail identity.
The source already byte-verifies all three rows; this is linking cleanup,
not new matched coverage.

Apply the TU-local free iterator comparison already used by the separate
`StlSweepW5Rva005DE4BA.cpp` overflow provider. Comparing the iterator node
pointers directly prevents this TU from emitting the generic base-class
comparison. No compiler flag, row, pin, source path or recovered type name
changes.

Target facts and inference boundary:

- The parent row at RVA `0x005DE651` has extent 260 bytes, with existing
  8-byte unwind and 10-byte handler rows. All three match before and after.
- The existing overflow call at parent offset `+0xF0` reaches the separate
  RVA `0x005DE4BA` owner. The element view remains an address-derived ABI
  inference; this repair establishes no donor name or additional layout.
- The published index (updated 2026-10-30 04:25 at `6fe1089c24`, census
  02:53 at `8716fcf38f`) lists five copies of the base iterator comparison.
  The copy in `stlport_list_int.cpp` is retail; this source and three other
  copies are marked wrong. Removing this source's copy leaves providers.

A declaration-only overflow specialization was tested first and removed:
it changed the parent to 267 bytes and altered call/stack code generation.
That failed trial is not retained in `Code/`.

Verification:

- Before/after frozen-file checks pass. The final ordinary build passes
  3/3 rows and all reference gates. The existing unwind label renumbers to
  `$L7053`; its parent EH data still binds it to RVA `0x007A2E03`.
- Comparing the baseline and repaired normal objects with
  `link_census._comdat_sections` finds 68 -> 67 external COMDATs. All 67
  retained names have identical sizes and byte/relocation fingerprints.
  `link_census._coff_symbols` finds exactly one removed external definition,
  the base iterator comparison, no added definitions, and no change in the
  undefined external set. The replacement emits a 12-byte TU-local comparison
  (storage class 3, outside the external COMDAT set); the removed external
  comparison was 18 bytes. Scratch snapshots, comparison code and results
  are under `build/fill-insert-link-codexb4/`.
- Supported strict preparation passes 4/4 rows across this source and the
  unchanged overflow provider, with reusable receipts and ordinary reference
  gates. Final paired preview predicts LINKS, 0 -> 270 authored bytes for
  this source and 178 -> 178 for the overflow provider, against that index.
- The source-only staged-tree consumer audit exits 2, INCONCLUSIVE: the index
  predates source base `a3dcf853f0`, and an affected consumer lacks a current
  strict receipt, first `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`.
  This is not a clean full-consumer verdict.
- The outgoing staged-tree audit, including the earlier runner-held batch,
  also exits 2, INCONCLUSIVE: index `6fe1089c24` predates outgoing merge base
  `198e16293c2f34021efe015bf77e39fc7a951ed1`; three source objects lack current
  strict receipts, first `GameClient/GUI/GUICallbacks/Apt/AptPlayerStatusDtor.cpp`.
  The repaired source and its overflow provider have their strict receipts.

The index refresh installed the index successfully. Its optional bulk object
cache import was interrupted after sustained processing; it was writing only
the object store, not the byte-check build cache. The explicit preparation
and previews above completed normally.

Census confirmation and broader consumer verification remain pending. Carry
the repaired source, its overflow provider and the missing consumer receipts
into the next scheduled census. No census-linking or image-ownership gain is
claimed. The other three conflicting iterator copies remain separate work.
