# Update-module canonical Xfer adoption

Inspected upstream `9e1ca7f93f`, BFME 1 reference `f633d0e97a`.
The default queue served the complete `StealthUpdateXfer.cpp` source and
claimed the Xfer class scope. Its historical header trial failed because
`Snapshot` was undeclared.

## Stealth update

Replace the private Xfer declaration with the registered `BfmeXfer.h`.
The local `UpdateXferTypes.h` supplies only operand forward declarations,
before the canonical include, including when TU composition hoists includes.
The shared header and function ledger remain unchanged.

The existing four-byte version storage and its `(1, 4)` initialization are
kept, passed as the opaque `Xfer::Version &` operand at slot `0x28`.
Unsigned-int, int, bool and AsciiString overloads retain slots `0x78`,
`0x7c`, `0x90` and `0x6c`; loading and light-CRC dispatch remain `0x04`
and `0x10`. Field order, version gates, native callees, string lifetime,
throw path and existing linker alias are unchanged. This does not recover
a new Version layout or resolve the existing alias debt.

- Read the complete source; frozen-file checks pass before and after.
- Normal byte/reference gates pass both rows before and after: the 422-byte
  parent at `0x00374942` and its ten-byte handler at `0x0077E906`.
- The current parent's EH graph is EXACT, with no baseline exception.
- Ordinary before/after previews keep the already-linked unit clean,
  **429 -> 429 authored nonpadding bytes**, against index `f995f30157`
  (2026-10-25 21:36 UTC).
- `header_adopt_lane.py accept --class Xfer` passes and retires one queue row.

## Deletion update

Read the complete `DeletionUpdateXfer.cpp` sibling and its earlier boundary
handoff: the verified row is 39 bytes, not the superseded 27-byte deferral.
The private Xfer table is replaced by the same two includes. `Version1()`
and `UpdateModule::xfer()` are unchanged; the unsigned-int overload takes
the existing `m_dieFrame` reference at slot `0x78`.

Before/after frozen-file and normal byte/reference checks pass the complete
39-byte row at `0x00488483`. There is no parent EH graph. Ordinary previews
retain **39 -> 39 authored bytes** against the same index. The owning header
acceptance command passes and retires this source's single queue row.

This is retirement of two header-debt rows, not new matched, C++ exact or census-linked
bytes. Other Xfer consumers and class-wide or executable closure remain open.
