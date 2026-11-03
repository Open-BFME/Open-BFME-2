### ThingTemplate FX-map identity prerequisites (2026-10-28)

Status: Blocked on coherent tree-provider typing and a clean identity verdict.
Inspected `b986237bff16`; ordinary-preview index `41c28839bf`.
The selected callback's insert_unique binds 0x0033D28A, currently owned by
the NoCaseTreeValue4/BfmeStringNoCaseLess family. Its insertion comparator
inlines ordinary AsciiString operator<, while the placeholder identity also
spans the copy/assignment family. A callback-only type replacement would
not establish that whole family's original types.
Normal verification preserves 22/22 rows; ordinary preview remains blocked
for all 882 authored bytes. The owning retirement refuses missing/stale
provider receipts and six additional identity findings; all three registered
keys remain. No source edit retained.
[Owner chain, checks and next steps](../../reverse/attempt_support/thing-template-fx-identity-20261028-codex3.md).
Reconcile insertion/allocation owners and their consumers, then resolve the
independent sparse-finder and additional identity findings before retirement.
No census or linking gain is claimed.
