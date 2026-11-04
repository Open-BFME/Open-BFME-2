### LINK-300: Mineshaft TU composition needs frame and manager-vtable reconciliation
Status: Blocked. Updated: 2026-11-04; inspected revision: `0ebd1b81e8`.
Completed: link-step declarations reconciled; its 115-byte row remains exact and LINKS in the 17:56 `8c757ea0db` index preview. No TU merge landed.
Remaining / next check: preserve the link-step's `/Oy-` frame in composition, reconcile the constructor's duplicate allocator specialization and destructor's subsystem header, and prove the manager's native virtual slots before its selected-vtable guard can pass.
Evidence: [trial scope, byte discrepancy and verification](../../reverse/attempt_support/mineshaft-tu-consolidation-20261104.md).
Clearance: pending; no census gain claimed.
