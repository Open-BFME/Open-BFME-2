# Texture share-buffer callback identity, 2026-10-28

Inspected checkout: `af996f496c`. Prediction index: `d92e7e6635`, fetched through
`tools/link_check.py --fetch-index`; this is not a new census.

Source: `Code/Libraries/Source/WWVegas/WW3D2/ShareBufferClassTextureCopyCtor.cpp`.
Claimed parent: `0x0015AE10`, 284 bytes.

## Target facts and scope

The copy constructor's vector-new callbacks reach `0x00326BE6` (zero a pointer)
and `0x0017098D` (conditionally release the texture). Existing ledger providers
name these `RefCountPtr<TextureClass>` construction and destruction:

- `fxshadernamespacesas.cpp`: `??0?$RefCountPtr@VTextureClass@@@@QAE@XZ`, 6 bytes.
- `streakRender.cpp`: `??1?$RefCountPtr@VTextureClass@@@@QAE@XZ`, 12 bytes.

The former unit's existing template stores one texture pointer, initializes it
to zero and conditionally calls `TextureBaseClass::Release_Ref` on destruction.
The private `TextureSlot` view had the same operations but a different symbol
identity. Its constructor generated the registered wrong binding at
`0x00326BE6`. This repair uses that established template identity for the array
allocation and its callback pair. It adds no pin, alias, ledger row or hatch.

All ten emitted COMDATs have identical raw bytes before and after the change.
Their relocation fingerprints also agree after translating only the
`TextureSlot` constructor, destructor and vector-deleting-destructor names to
their `RefCountPtr<TextureClass>` counterparts. The parent and vector-delete
helper otherwise differ in fingerprints only because their callback names
changed; the other eight fingerprints are unchanged after mapping definitions.

The BFME 1 `sharebuf.h` copy skeleton and `meshmatdesc.cpp` texture ownership
operations are donor leads already documented in the source. They do not prove
BFME 2's outer template spelling or full source layout. This change resolves
the local callback identity only; it does not claim complete source recovery
for the share-buffer family.

## Verification and retirement

- `find_declared_unmatched.py SOURCE`, before and after: all definitions matched.
- `./build.sh SOURCE`, before and after: all four rows match; both renumbered
  unwind labels are verified by the parent's exact EH graph.
- `eh_verify.py SOURCE`: EXACT 1, no failures.
- `allowed_symbols.py --source SOURCE`: wrong bindings 1 -> 0; final reference
  counts are owner 8, EH 1, alias 1.
- `data_check.py --enforce SOURCE`: no findings.
- `link_check.py --prepare-current SOURCE`: strict current-input receipt passes.
- Ordinary `link_check.py SOURCE`, before and after: LINKS, 294 -> 294 authored
  bytes. This is a prediction, not an increase in census LINKED coverage.

The first identity-retirement check correctly refused missing objects for 42
ledger sources and stale objects for `dx8indexbuffer.cpp` and `texture.cpp`.
Building this bounded prerequisite set through `./build.sh` verified all
413 rows across 44 sources, including six complete constructor folds. No
prerequisite source was edited. The second
`repair_queue.py retire identity SOURCE` passed, removing exactly one key from
`reverse/code_identity_baseline.tsv` with zero remaining findings.

Remaining: other share-buffer and container identities are outside this repair;
LINK-002 remains open. Census confirmation belongs to the scheduled measurement.

Revalidated at `2be96b3c93` before publication: ledger integrity, frozen-source,
four-row byte verification, exact parent EH graph, zero wrong identity bindings,
zero enforced data findings and strict current-input preparation all pass.
The ordinary preview still reports LINKS for 294 authored bytes.
