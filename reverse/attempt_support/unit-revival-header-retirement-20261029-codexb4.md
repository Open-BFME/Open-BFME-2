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
