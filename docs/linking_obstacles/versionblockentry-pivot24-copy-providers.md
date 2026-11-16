### VersionBlockEntry and Pivot24 copy providers

Status: VersionBlockEntry and Pivot24 repaired locally; full-link and
runtime confirmation pending.

The diagnostic image at a06b14bb6a7d stops at the VersionBlockEntry copy stub
02921280 before menu. The latest inspected real link at 1ffed447 still lists
both copy names as unresolved from VersionBlockParser.cpp. Both existing pins
identify the native 61-byte two-string copy at RVA 00427F75, whose rowed owner
is NarrowStringRecordCopyBFME2.cpp. No new pin, alias or row is introduced.

VersionBlockEntry now owns its two 12-byte strings instead of inheriting a
declaration-only footprint view. Its complete memberwise copy, defined after
the callers, is a byte/relocation twin of native 00427F75 with an EXACT EH
graph. The existing vector footprint remains explicit at its two push_back
boundaries. All 50 parser rows and nine existing EH graphs remain exact.
Provider comparison adds only this constructor; every retained definition
is unchanged. Scoped link_check removes its unresolved name and still refuses
the file for Pivot24. No full-link gain or menu success is claimed.

Pivot24 now also owns two strings and emits the native 61-byte copy. Its
destructor is the complete native 65-byte body instead of the previous
five-byte forwarding thunk. Official pin_admission accepted its fold-proof
at 00238580, including relocation bindings and EH, and updated the pin counter
from one to two through its admission path. All 50 rows and nine existing EH
graphs pass; direct EH checks for both copies and the destructor are EXACT.
Scoped link_check now reports no unresolved constructors (2965 own bytes),
against the same stale census. A fresh full link and Windows run remain required.

Evidence and rejected trials: [handoff](../../reverse/attempt_support/versionblockentry-pivot24-copy-providers.md).
