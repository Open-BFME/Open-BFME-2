# UnitRevivalEntry header retirement after census refresh

Inspected base: `adfa7b591af94e9bd708ff7fb3c7a4e7790b1e4e`.
Source: `Code/GameEngine/Source/Common/UnitRevivalEntry.cpp`.
Claims: `class:AsciiString`, plus the source's file scope.

The canonical AsciiString adoption already landed; this change retires its
restored header-queue entry through the owning tool. The previous publisher
refusal and source reconstruction remain documented in
[the original handoff](unit-revival-ascii-header-20261028-codex3.md).
No source, header, function row, pin or compilation option changes here.

The new evidence is the published census index at `85f6b7f40c`, dated
2026-10-29 15:08, fetched with `tools/link_check.py --fetch-index`.
The ordinary current-object preview now produces a usable per-unit verdict:
`LINKS  LINKED 134 -> 134 bytes`. It preserves the existing scoped result;
these authored bytes are not a new census gain.

Verification:

- `tools/find_declared_unmatched.py` reports all definitions already matched.
- `./build.sh` verifies the complete 135-byte constructor at `0x0037E352`
  and its one float literal, with no string/import failures.
- `tools/link_check.py --prepare-current` supplies a strict reusable receipt
  for this source without changing census or index measurements.
- `tools/header_adopt_lane.py accept --class AsciiString` passes its byte,
  include, private-body and ordinary-preview checks and retires exactly one
  entry from `reverse/header_queue.tsv`.

Publication must independently repeat the owning verdict. The broader
consumer scope in LINK-100 remains pending; this does not assert class-wide
link closure or image ownership. The other AsciiString queue rows remain.
The default pick's 20-byte vector helper still has the documented raw pointer
assignment versus owning string-assignment identity blocker; no unchanged
source trial was repeated and its queue entry is retained.

BFME 1 upstream was fetched at `fbfea42889700c5141ff601c2d2134b50ec84448`.
The reference-update scope remains claimed by `yasinschroeder-codexb`.
The committed `e42b9782fd4cce1f79832a6ed591b0b8fdbbc2fc` input pin is
preserved and no freshness success stamp is written.

## Preparation recovery publication boundary (2026-10-29)

The preserved 14-commit batch was rebased without dropping any commit. The
local full-gate dry run passed all 99,003 function rows at `908831e6a4`.
After the fleet publisher rebased the batch onto `e584f5892953`, its owning
header-debt check refused this retirement: `link_check produced no usable
per-unit verdict`. Restore the exact upstream header-queue entry in a new
commit; retain the canonical source and the earlier local evidence above.
The queue's FAIL text is historical. No header-debt retirement is claimed.
Obtain a usable verdict in the publisher checkout before accepting it again.

The local batch link audit was INCONCLUSIVE: index `85f6b7f40c` predates
base `0780fe436f`, and 36 affected source objects lacked current receipts.
Its first reported source was `Common/RTS/PlayerInitFromDict.cpp`. These
consumers remain unverified for the next scheduled census; this records
neither a proven linking loss nor a census gain. No source, provider, pin,
function row or compiler option is changed by this recovery correction.
The preparation backup remains at
`refs/runner/preparation/1793304764628675868`; no stash was recorded.

## Recovery against the later upstream retirement

Upstream c89bb4eb64 already records the independent owning-tool retry and
usable LINKS verdict. Keep its retired queue state; the older restoration
proposal above is superseded. This rebase adds no queue entry and performs
no new debt retirement. Preserve the original obstacle follow-up here because
the shared obstacle document is currently claimed by another worker:

**2026-10-29 preparation recovery publication follow-up:** the recovered
retirement passed its local full-gate dry run, but the fleet publisher at
base `e584f5892953` again reports `link_check produced no usable per-unit
verdict`. Restore the exact upstream queue entry and defer retirement;
retain the canonical source and the prior evidence. No header-debt gain
is claimed. The local batch link audit is INCONCLUSIVE: 36 affected source
objects lack current receipts against index `85f6b7f40c`, which predates
base `0780fe436f`. Carry this scope into the next scheduled census; no
linking loss is proven. [Recovery boundary](unit-revival-header-retirement-20261029-codexb4.md).
