# Matrix3D setter: canonical Vector4 without an extra provider

Base `c38e282bad`. Claimed file and Vector4 scopes; reviewed the existing
Vector4 contract/header and the native row layout before editing. The normal
baseline passes both rows: Matrix3D::Set at `00711E70` (118 bytes) and its
Vector3 subscript provider at `004047D9` (10 bytes).

Replace the private Vector4 with the existing `Vector4Data.h`. A direct use
of its Set method keeps both rows exact but emits an extra shared
`Vector4::Set` code definition. A static inline setter avoids that shared
definition but still emits a separate internal code copy. Both controls are
preserved; neither is the final implementation.

The final setter captures each row's four inputs in local floats before
writing X/Y/Z/W, in the original right-to-left argument-evaluation order.
This preserves the original read-before-write behavior if an input aliases
the destination. It emits exactly the original two code functions: all
118/10 bytes and every relocation are identical, with no added, removed or
changed code definition and no standalone helper. The canonical 16-byte row
storage is used directly; no shared header, flag, import, pin, alias, class
ABI, source path or data row changes.

The complete source passes its normal and frozen-definition gates, strict
preparation and owning Vector4 acceptance. Exactly one queue key is retired.
The final acceptance is rerun after eliminating the transient static helper;
the already-retired key is not re-added or hand-edited. Bounded prediction at
`3c7a254a38` (2026-10-31 13:43) retains LINKS/128 authored bytes. This is
header-debt retirement, not new matched bytes or a census/runtime gain.

Together with the separately committed physics adoption, this batch retires
two Vector4 keys while preserving three rows and 1,003 authored preview
bytes. The separate Matrix3D/Vector3 private-view work is not claimed complete.
The outgoing audit's currency/consumer scope remains separate.

Controls, including the intermediate static-helper source/object, final
actual-object comparison, strict receipts and both acceptance runs, are in
ignored `build/two-each-no-qwen-20261031-1559` and the matching create-only
diagnostic package. No local model is used; the shared ten-worker cap remains.

## Consumer audit before publication

The first outgoing audit found the physics strict receipt stale after its
newline-only cleanup. Fresh strict preparation of that owned source resolves
that prerequisite. The repeated audit at base `c38e282bad`, tip `d83fe6ae8`,
with the NUL-delimited two-source list is INCONCLUSIVE, exit 2: index
`3c7a254a38` predates the base and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. No complete consumer-loss clearance follows. Carry that scope into
the scheduled census; the publisher hook audits the final rebased range again.
