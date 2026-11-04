### LINK-203: FXShaderSetup vector-view consolidation prerequisites
Status: Open. Updated: 2026-11-04; inspected revision: `9caf2e13f3`.
Completed: reconciled the erase and resize vector views across the shader TU and their providers; all 58 rows in three sources still byte-match.
Remaining / next check: canonical shader/record header adoption and the other private views, including the ambiguous `BfmeAssignRecord36::bytes` binding, precede another bounded merge trial.
Evidence: [scope, tool verdicts and remaining prerequisites](../../reverse/attempt_support/fxshadersetup-vector-views-20261104-codexb5.md).
Clearance: declaration repair only; outgoing link audit inconclusive (stale index and missing current object receipts); whole-TU merge/link clearance pending. Census confirmation: not claimed.
