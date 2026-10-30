# Persistent-storage reader Xfer header adoption

Inspected `1ef43074a3` on 2026-10-30 under `class:Xfer`. The prior
network/library adoption handoff recorded an abstract concrete reader and an
incompatible implicit conversion to the existing stats-transfer view. This
change resolves those two declaration prerequisites locally in
`Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PersistentStorageThread.cpp`.

## Change and evidence boundary

The private `Xfer : XferStub` definition becomes an include of the registered
`BfmeXfer.h`, preceded by operand forward declarations. The existing
`Rva0060C5FA` reader declares the five inherited pure-virtual overrides so its
already external constructor can still be used on the stack. No override
body or additional provider is emitted. Its existing 0x20-byte storage and
constructor/destructor call routes are retained. The six reader-to-stats
calls explicitly use the existing `XferStub` view; that view and all rowed
stats-transfer signatures remain unchanged.

This is header/declaration cleanup. The neutral reader identity, original
member names, full reader interface and source-TU placement are not recovered
by matching bytes. In particular, the override declarations do not assign a
second name or pin to any block-operation provider. The shared header,
function/symbol ledgers, globals, source paths and compiler flags are unchanged.

## Verification

- Normal source builds preserve 306/306 function rows, three complete STLport
  constructor folds, three data rows, 52 literals plus 13 empty-string
  references, 23 compiler float literals and 14 named imports.
- Before/after normalized COFF comparison preserves all 347 external COMDAT
  byte-and-relocation fingerprints and the complete strong-definition,
  undefined-symbol and weak-binding sets. No fingerprint is added, removed
  or changed. [Comparison](persistent-storage-xfer-header-20261030-codex.json).
- Frozen-source checks pass (309 matched ledger rows; the existing one
  unclaimed definition remains accepted).
- EH verification reports EXACT 46/46 graphs.
- `header_adopt_lane.py accept --class Xfer` passes and retires exactly the
  persistent-storage queue row through the owning tool.
- Strict current preparation passes for the source with a reusable receipt.
- Ordinary before/after previews retain LINKS for 21,853 authored bytes
  against index `85f6b7f40c` (2026-10-29 15:08). The two existing unreferenced
  allocator-relocation diagnostics remain; no new blocker is reported.
- The staged outgoing audit is INCONCLUSIVE: index `85f6b7f40c` predates
  base `1ef43074a3`, and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a
  current receipt. Carry this provider/consumer scope into the next scheduled
  census; the audit does not establish consumer-wide closure.

Local input backups, compiled comparison objects and raw logs are under
`build/xfer-persistent-20261030-codex/`; the tracked comparison records the
result without depending on their continued availability.

## Remaining scope

The other Xfer queue entries retain their separate constructor-emission,
concrete reader/block-provider and stream-identity prerequisites. The
`XferStub` stats operand interface remains a partial view. Consumer-wide
verification and a scheduled census are still required; this change claims
no new census-linked bytes or image-ownership result.
