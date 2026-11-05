### LINK-484: AISkirmishPlayer lifetime merge exposes incomplete AIPlayer slots
Status: Blocked. Updated: 2026-11-05; inspected revision: 8578d8fd3e.
Evidence / completed / next check: [destructor declarations reconciled and stale forwarding thunk recovered; byte-exact destructor composition still fails its link guard on AIPlayer slot01/isSkirmishAI/doTeamBuilding; reconcile canonical slots/providers and constructor Player/field views before retrying](../../reverse/attempt_support/aiskirmish-consolidation-20261105-codexb4.md).
Clearance: Main TU's ordinary preview remains clean; no source merge retained. Census confirmation: awaiting; no new measurement claimed.

2026-11-05: Four non-lifetime AIPlayer consumers adopt the canonical header (4 header keys retired; preview 4,129/4,129 B); the byte-exact destructor trial is restored because its canonical table additionally needs eight virtual-name providers and table reconciliation before lifetime adoption. [Exact names and receipts](../../reverse/attempt_support/aiplayer-header-20261105-codexb4.md).
