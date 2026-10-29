# Connection ack alias cleanup and consolidation prerequisites

Inspected base: `01bdf8d61808d0a52059a18cbff3cf484379c769`.
Preview index: `85f6b7f40c`, 2026-10-29 15:08.

## Retained cleanup

`ConnectionProcessAck.cpp` now calls its existing `rva0058BD4F(void *)`
owner directly in the stage-1 branch. Remove that branch's linker alias and
its unused `symbols.csv` pin, lowering both hatch allowances by one. The
both-stage overload/alias remains: calling the same owner in both branches
coalesces their call sites to 29 bytes instead of retail's 37. A typed
pointer-to-member cast trial also coalesces the calls; neither trial remains.
No owner, layout, canonical name, row, extent or compiler flag changes.

The pin/alias referred to the already-rowed owner at 0x0058BD4F; this is
binding cleanup, not new identity evidence for either folded overload.
The 37-byte dispatch body at 0x0058BD7B retains its two calls. The first REL32
at +0x0E now names the owner directly; the second at +0x1A still names the
both-stage overload, whose unchanged alias reaches the same owner. Comparing
the saved pre-edit object with the final one using link_census's COFF reader
preserves both COMDATs' complete bytes, sizes and relocation records after
normalizing the retired alias to its existing destination. Source searches
find no other callers of the retired symbol; the saved index's touches map
also names only ConnectionProcessAck.cpp for it.

Checks:

- `./build.sh` on all eight claimed files: 19/19 function rows, three float
  references and four named imports pass; the renamed doSend funclet is
  verified through its parent's EH data.
- Frozen-source checks: all definitions already matched across the scope.
- Dispatcher/provider strict-current preparation: both rows pass; ordinary
  preview retains LINKS for 37 + 44 = 81 authored bytes.
- Pin consistency: passes, no new or stale findings. Ledger check and diff
  whitespace check pass. No protected identity/data/header key is retired.

## Consolidation remains blocked

The supported GameNetwork evidence planner was run against the current inputs.
It catalogues the ZH same-name definitions and stale-map placement hints;
these are distinct from current target approval. tu_skeleton rebuilds the map
in memory and approves 20 rows: 19 in the eight claimed whole-file sources,
one in the mixed clearCommandsExceptFrom file. No regenerated map is committed.

The supported dry run stops before composition: carrying the
ConnectionRva0058BD4F `-O2 -arch:SSE` override loses two destination rows.
This reproduces the existing compiler-profile prerequisite, not a new loss.
The supported class-view tool retains no edits and reports:

- NetCommandList seed +0x00 data overlaps other views' vfptr.
- Connection m_addrA +0x0C..0x10 overlaps m_address +0x0C..0x14.
- NetCommandMsg getNetCommandType returns int versus NetCommandType.
- NetCommandRef m_relay +0x0C..0x0D overlaps m_retryCount +0x0C..0x10.
- NetPacket m_packet +0x04..0x1E0 overlaps m_data +0x04..0x204.

Resolve the compiler profile and evidence-backed class views before retrying
composition. No files move, no mixed file is split, and no source-file or
census gain is claimed. The path-consumer audit for moves does not apply.
The ordinary preview establishes the two-unit scope, not consumer-wide closure.

## Reference freshness

Official BFME 1 master was fetched at
`fbfea42889700c5141ff601c2d2134b50ec84448`. The update file scope is held by
`yasinschroeder-codexb`; retain the verified
`e42b9782fd4cce1f79832a6ed591b0b8fdbbc2fc` pin. No freshness success stamp
was written and the reference checkout was not changed.

## Outgoing audit

The staged-tree batch audit is INCONCLUSIVE: index `85f6b7f40c` predates the
outgoing base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry that consumer and the dispatcher/provider scope into the next
scheduled census. This does not establish consumer-wide link closure. The
staged hatch gate credits alternatename 2897 -> 2896 and pin 9412 -> 9411.
