### LINK-214: RespawnBody header acceptance awaits a census destination object
Status: Blocked. Updated: 2026-11-04; inspected revision: 10b67cc307d6.
Evidence / affected units: `Code/GameEngine/Source/GameLogic/Object/Update/RespawnBody.cpp`; [verification and consolidation handoff](../../reverse/attempt_support/respawn-body-damageinfo-20261104-codex5.md).
Completed: canonical DamageInfo include replaces its private view; six rows byte-match, both EH parents are EXACT, and the complete runtime object is identical. The header queue row is retained.
Remaining / next check: fetched index a62ac1c10b (census 5a13f2cd61) lacks this destination, so ordinary preview and header acceptance have no usable verdict. After a scheduled census includes it, rerun link_check and header_adopt_lane.py accept --class DamageInfo for this unit. A separate merge prerequisite is canonical ActiveBody inheritance reconciliation.
Clearance: pending; no consumer-link improvement claimed.
Census confirmation: awaiting the scheduled census; no new measurement run requested.
