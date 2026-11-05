### LINK-559: TerrainLogic composition needs STL copy-header reconciliation
Status: Blocked. Updated: 2026-11-05; inspected revision: `e06b0b97c9`.
Evidence / affected units: TerrainLogic.cpp and its clean donors, especially Rva002821CFErase.cpp; [trial and verification evidence](../../reverse/attempt_support/terrainlogic-consolidation-20261105-codexb4.md).
Completed: retained-record view reconciled with identical object identities; separate units pass 153/153 byte checks and paired link preview passes 2/2. Current index reaches compilation, beyond the earlier stale-residual blocker.
Remaining / next check: reconcile by-value shim versus const-reference STLport 4.6 copy dispatch and effective overload declarations; isolated pair matches 151/153. Other donors still require header/view and flag reconciliation.
Clearance: pending; both merge trials accept no donor, no file removed.
Census confirmation: not claimed.
