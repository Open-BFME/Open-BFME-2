# LargeGroupAudio key-list erase binding

Inspected upstream `e5c5a1787c`, BFME 1 reference `f633d0e97a`.
The default link queue served the complete `LargeGroupAudioKeyList.cpp`.
Its sole row is `bfmeClearMembers`, `0x003ED7A2..0x003ED861`, 191 bytes.
The old solved/converted attempt and the separate key-map-layout bank were
read before changing it.

## Current-input repair

The normal before-build is exact. Against published index `f995f30157`
(2026-10-25 21:36 UTC), ordinary preview reproduces one unresolved datum,
one nonretail erase COMDAT and one wrong selected erase copy. Current code
identity reports three owner references and one wrong/extent reference:
the parent call at offset 108 (instruction `0x003ED80E`) targets `0x00056BC3`.

The existing row at that address is the 59-byte AsciiString-set erase in
`stlport_asciistring_set_base.cpp`. Its normal whole-file gate passes all
15 rows. The caller instead instantiated a different allocator-specialized
record-tree erase under an existing fold pin.

A declaration-only record-tree specialization removes the wrong local copy
but leaves an unresolved alias in the ordinary preview. The final repair
calls the existing row's actual specialization through a receiver/node-prefix
view and declares that specialization without emitting a second definition.
The proven tree header and first AsciiString member are the call ABI; this
does not identify the complete record payload as an AsciiString or recover
an application class name. The bit traversal, signed counter, iterator order
and next-key rebuild are unchanged.

- Normal before/after byte/reference checks preserve all 191 bytes.
- Frozen-file checks pass; the caller has no parent EH graph.
- Final code identity reports **four owner references, zero wrong bindings**.
- Final ordinary preview has **one unresolved datum, zero COMDAT and zero
  selected-copy blockers**. Four unreferenced codegen diagnostics are separate.
- Linked-byte preview remains **0 -> 0** because the datum is still unresolved.
- No pin, alias directive, ledger row, baseline or tool is added or changed.
  The caller no longer references its old fold pin; the pin is not retired
  by this repair.

## Remaining storage prerequisite

`g_lgaKeyRecords` is still only an extern in this source and
`LargeGroupAudioKeyMapBfmeAddKey.cpp`. The data ledger records the address
`0x00A02E50` as unowned, with three competing spellings. Source inspection finds
a pointer-sized definition `g_00A02E50` in `Rva003ED498Count.cpp` and a separate
unsigned-int definition `g_Va00E02E50` in `Rva007B6880Thunks.cpp`.

Initializer `0x007AF8CD` in `Rva007ACDE1StlGlobalInits.cpp` constructs the
container at the latter symbol through `0x0024613C`, then registers cleanup
`0x007B80F1`; that cleanup reaches the tree destructor at `0x003ED94A`.
The pointer spelling is also used by `Rva003ED9B1Merge.cpp`. Merely redirecting
the full tree view to either four-byte definition would not establish enough
storage or a shared lifetime. Reconcile these consumers, the complete storage
extent and the existing initializer/cleanup before claiming unit closure.

The separate 2026-10-19 key-map-layout bank concerns bitmap owners and a
135/136-byte static accessor mismatch. It was not applied and is not evidence
that this global tree's storage is repaired.

This commit repairs one call binding while preserving coverage. It does not
claim new matched, C++ exact, census-linked or complete-image bytes.
