# GroupOrder post-composition link audit, 2026-11-04

Follow-up to [the two-donor merge](grouporder-tu-merge-20261104.md).
The runner accepted the reconciliation and merge commits for fleet publication;
the fleet rebased them while these checks ran. No published commit was amended.

The normal commit hook passes 28/28 source rows, one data row, all six EH rows
EXACT, zero new code/data identity findings and no new COMDAT variants. Local
link previews remain as recorded in the merge evidence; they are not a census.

The wider `link_batch_audit.py --base HEAD^ --tip HEAD` initially lacks current
receipts for six direct constructor/counter consumers. Use the supported
`link_check.py --prepare-current --paths-from` to refresh exactly these seven
existing sources (including already-current peers), with no source edits:

- AttackObjectGroupOrderCtor.cpp
- ChangeStanceGroupOrder.cpp
- GarrisonObjectGroupOrderCtor.cpp
- GroupOrderHolderCtor.cpp
- MoveToGroupOrderCtor.cpp
- SynchronizeGroupOrder.cpp
- System/AiOrdersManager.cpp

Result: 56/56 rows and one data row exact, eight funclet pins verified, no
literal/import findings; strict reusable receipts written. Following the fleet
rebase, prepare the destination the same way: 13/13 rows and its data row exact.
These are normal byte checks, not an independent link closure result.

Final batch audit (exit 2):

```
link batch audit: INCONCLUSIVE baseline: index at f12552d0a7, outgoing base HEAD^; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```

This is a broader shared-COMDAT consumer reached after the direct identities
were refreshed. The audit stops before provider-selection and consumer-loss
comparison completes; do not call the batch globally link-clean. The old census
baseline also prevents a definitive before/after verdict. Carry this merge and
its constructor/counter consumers into the next scheduled census, then compare
selected providers and affected consumers against that current baseline. No
nightly, link-cycle or smoke runner was started. Wider census confirmation stays
open rather than expanding this small merge into a whole-tree rebuild.
