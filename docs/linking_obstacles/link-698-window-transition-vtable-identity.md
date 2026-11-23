### LINK-698 GameWindowTransitionsStyles vtable references and class identities

**Status** The medium-scale reference is repaired and awaits a published real-link result. The other three entries for this source remain open. Inspected on 2026-11-23 at `158cf2387c7`.

The 80-byte `MainMenuMediumScaleUpTransition` constructor at `0x0035DE55` now references the compiler's vtable symbol for `0x00816574` directly. Native constructor emission moved the vtable store ahead of the end-frame store. Declaring the decorated vtable as an external array failed under MSVC with C2373. An expression referring to the compiler's existing symbol preserves the store order and emits a local table, so the class declaration supplies all eight virtuals. The emitted 32-byte table and all eight COFF relocations agree with the existing provider in `FamilyTailDtors1DBAC3.cpp`. The constructor's masked bytes and all other bindings agree with the parent object.

All 144 function rows, one data row, and 18 unwind graphs passed across the constructor, destructor, and slot-provider units. The three-source preview links all three units and reports 9,883 linked bytes against index `76a04dbe10`. Check the next published queue for removal of `_vtbl_00C16574`.

The entries at `0x00816530`, `0x00816594`, and `0x008166BC` still need their installer and slot owners reconciled. The existing class-fold route refuses the transition identities split across those slots. A direct explicit reference can emit the local class view's table, so it requires an independently verified complete slot layout. [Previous transition-family work](../../reverse/attempt_support/00816530-transition-family-vtables-20261121.md)
