### LINK-422: InstantDeathBehavior parser merge refuses the existing OCL ICF owner transfer
Status: Blocked. Updated: 2026-11-05; inspected revision: b68a6b7959.
Evidence / affected units: InstantDeathBehavior seed and its two parser donors; existing `_M_insert_overflow<vector<const ObjectCreationList *> >` fold at 0x002DFCF6. [Scoped receipts and audit boundary](../../reverse/attempt_support/instantdeath-parser-merge-20261105-codexb4.md).
Completed: vector reconciliation published through runner handoff; supported two-donor merge passes 19/19 rows, three exact EH graphs, zero new code/data identity findings, and scoped link preview; merge fully restored after A2 refusal.
Remaining / next check: reproduce the recorded ownership false reject for a proven compiler-emitted fold whose shared address is assigned to LivingWorldBuildingTemplate.cpp; independently verify the rule before retrying the source move. OnDie and destructor prerequisites remain separate.
Clearance: pending; batch provider audit was inconclusive with unrelated working-tree compiler inputs, and no source-file reduction is claimed.
Census confirmation: not claimed.
