### EmotionTrackerUpdate constructor canonical base (2026-10-29)

Status: scoped repair verified; consumer-wide and census confirmation pending.
Base `f143cd5169`, index `85f6b7f40c` (2026-10-29 15:08). The constructor's
private one-slot ObjectModule emitted a four-byte primary vtable conflicting
with the destructor's canonical forty-byte copy. Adopting ObjectModule.h and
casting the canonical Object* through the existing local ID view preserves
11/11 constructor/destructor rows and the exact constructor EH graph. Both
units preview LINKS (constructor 0 -> 430 authored bytes, destructor 159 -> 159).
The owning header tool retires one ObjectModule queue row; the separate Thing
view and complete derived virtual-interface reconciliation remain open.
The outgoing audit is INCONCLUSIVE on the older index and a missing current
receipt for Common/0CreateAHeroManager21FE49.cpp. Carry that consumer and this
provider scope into the next scheduled census; no census gain is claimed.
[Evidence](../../reverse/attempt_support/emotion-tracker-base-header-20261029-codex.md).
Commit-hook follow-up: two shadow identity findings remain for the existing
Rva004DD489 vector push_back (0x004DFCB0) and Rva002EE9B7 cleanup (0x002F0F02).
The saved pre-edit object proves these named bindings unchanged. Their real
container/owner reconciliation is separate from the cleared COMDAT conflict.

Consolidation follow-up from base `6825bf755c`: the selector seed now declares
the existing nugget deactivation and module-name getter; the clear helper uses
the same partial nugget view. The two revised objects preserve all 15 matched
rows and their COMDAT fingerprints and external bindings. After rebasing onto
`e584f58929`, the supported merge absorbs the clear and name-key satellites:
two fewer sources, 18/18 matched rows, EXACT 2/2 EH graphs, and the same 28
COMDAT fingerprints and external bindings as the combined original objects.
The final TU previews LINKS with all 1,044 authored bytes retained. Refreshing
four stale outgoing/affected receipts verifies another 30/30 rows; the batch
audit remains INCONCLUSIVE on the older index and the same missing
Common/0CreateAHeroManager21FE49.cpp receipt. Carry the merged provider and
consumer scope into the next scheduled census. The constructor, other derived
interfaces and mixed files still need separate reconciliation. No census gain
or consumer-wide closure is claimed.
[Consolidation evidence](../../reverse/attempt_support/emotion-tracker-consolidation-20261029-codex.md).

2026-11-05: the nested-filter constructor adopts canonical EmotionTrackerUpdate and reads inherited ObjectModule::m_object; 5/5 rows and the 240-byte clean preview are preserved, and owning acceptance retires one header row. The five other selected consumers retain their module-base/vector-lifetime prerequisites. [Evidence and next checks](../../reverse/attempt_support/emotion-filter-header-20261105.md).

2026-11-05: repair `439048516f` is published; its outgoing audit remains INCONCLUSIVE on the older census index and missing filter-object receipt. Carry this consumer and its canonical header dependencies into the next scheduled census. [Outgoing audit evidence](../../reverse/attempt_support/emotion-filter-outgoing-audit-20261105.md).
