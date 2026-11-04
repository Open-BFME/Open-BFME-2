### LINK-204: FXShaderSetup vector-view consolidation prerequisites
Status: Open. Updated: 2026-11-04; inspected revision: `9ebc31c72f`.
Completed: reconciled the erase and resize vector views across the shader TU and their providers; all 58 rows in three sources still byte-match. Merged 12 donors into the TU (71/71 rows match); 6 donors remain.
Remaining / next check: adopt canonical FXShaderSetup.h in the seed (UpdateDynamicParameterSet, Rva00152D1C donors), then rewrite the hand-rolled `_STL`/StringBase donors against real STLport; the ambiguous `BfmeAssignRecord36::bytes` binding stays open.
Evidence: [scope, tool verdicts and remaining prerequisites](../../reverse/attempt_support/fxshadersetup-vector-views-20261104-codexb5.md).
Merge evidence: [merged and rejected donors](../../reverse/attempt_support/fxshadersetup-merge-20261104-claudeb.md).
Clearance: declaration repair only; outgoing link audit inconclusive (stale index and missing current object receipts); whole-TU merge/link clearance pending. Census confirmation: not claimed.
