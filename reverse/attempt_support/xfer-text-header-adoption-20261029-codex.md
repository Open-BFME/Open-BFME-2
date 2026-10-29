# XferSaveAsText canonical base-header adoption

Inspected `eb384b72a19073f986ee9ae431ebb3766d45562c` on 2026-10-29 under `class:Xfer` and
`file:Code/GameEngine/Include/Common/BfmeXfer.h`. This clears the text saver's
constructor-emission prerequisite from the
[previous handoff](xfer-header-blockers-20261028-codex.md).

## Change and evidence boundary

The private Xfer in BfmeRva00C7B388Xfer.cpp already had an imported,
force-inlined empty constructor. The previous out-of-class definition
could preserve the rows but emitted a second external constructor, while
an imported out-of-class definition disagreed with the canonical declaration.
The header now offers that existing declaration/body under the explicit
`BFME_XFER_INLINE_CTOR` option. Its ordinary declaration remains the default.
The text saver selects it alongside the existing inline-destructor option,
retains its original inline-depth control and defines the inline destructor
locally. This removes the private Xfer definition without creating another
constructor provider or changing the class layout.

This is a compiler-emission/header reconciliation of existing source.
No new donor identity, original TU placement, generated-body recovery or
new retail coverage is inferred. The function ledger, pins, data ownership,
source paths and other five Xfer header-queue entries are unchanged.

## Verification

- Normal paired build: 79/79 function rows (36 text-saver, 43 constructor-owner),
  one data row, 42 literals plus three empty-string references and one named
  import pass. The text saver's renumbered EH label is verified from the parent
  EH data at 0x007A6D72.
- The before/after object comparison preserves all 88 text-saver and 63 owner
  external COMDAT byte-and-relocation fingerprints. Neither object adds,
  removes or changes a fingerprint; external definitions, undefined symbols
  and weak bindings are equal. [Comparison](xfer-text-header-adoption-20261029-codex.json).
- `header_adopt_lane.py accept --class Xfer` passes and retires exactly the
  text saver's queue row through the owning tool. Frozen-file checks pass for
  the source and header.
- `link_check.py --prepare-current` prepares both sources with strict current
  receipts. The paired ordinary preview retains LINKS for 2,447 + 2,015 =
  4,462 authored bytes against index `85f6b7f40c` (2026-10-29 15:08).
  These are unchanged preview bytes, not a new census result.

## Remaining work

The FamilyDeletingDtors tag-constructor emitter needs its own emission or
approved-placement solution; selecting an imported inline constructor does
not itself emit its scalar deleting destructor. The concrete reader/block
provider identities in GameStateAutoSave and xfer_load, the stream identity
in XferSaveOpen, and PersistentStorageThread's concrete reader interface
remain separate prerequisites. This adoption does not clear those entries.

Local raw build inputs and comparison objects are in
`build/xfer-header-20261029-codex/`; the result above does not depend on their
continued availability.

## Dependent gate and outgoing audit

`header_adopt_lane.py gate-cost` verifies all 641 pre-existing header
dependents in two chunks: 441 seconds, BUILD_POOL=13, zero red chunks.
Together with the separately verified adopting source, the staged header
scope contains 642 ledger sources. The normal commit hook checks that
staged scope again as required.

The staged-tree outgoing audit is INCONCLUSIVE (exit 2). Its index
`85f6b7f40c` predates base `eb384b72a1`, and 640 dependent objects lack
current census receipts (first: Common/AIGuardState_xfer.cpp). Passing the
normal byte gate does not supply those strict link receipts. Carry the
642-source header scope and its affected consumers into the next scheduled
census; this change claims neither complete consumer closure nor a measured
linking/ownership gain.
