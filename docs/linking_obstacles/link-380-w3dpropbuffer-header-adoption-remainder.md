### LINK-380: W3DPropBuffer header adoption still needs Snapshot and nested-view reconciliation
Status: Open. Updated: 2026-11-05; inspected revision: b0c72d51e394.
Completed: canonical W3DPropBuffer adopted in six consumers; six header-queue rows retired through `header_adopt_lane.py accept`, preserving matched rows and the preview's census-linked bytes.
Remaining / next check: nine consumers remain queued; reconcile W3DFloorBuffer's Snapshot selection, then the padding-based prop views; constructor/destructor storage and EH identities remain separate prerequisites.
Evidence: [accepted scope, verification and per-unit blockers](../../reverse/attempt_support/w3dpropbuffer-header-adoption-20261105.md).
Clearance: only the six listed consumers' W3DPropBuffer header debt is cleared; no whole-unit or class-family link clearance claimed. Census confirmation: awaiting, no new measurement claimed.
