### LINK-274: Bridge constructor layout and remaining merge views
Status: Open. Updated: 2026-11-04; inspected revision: 96e492564922.
Completed: destination padding now exposes the existing verified constructor members; native dry merge changes from no donor to W3DBridgeCtor.cpp accepted, preserving 34 rows and passing its linked-unit guard.
Remaining / next check: apply the native constructor merge; GetModelVerticesFixed still needs Vector3 declaration ordering and Load needs RefCountPtr/model-view reconciliation. Canonical W3DBridge adoption remains separate.
Evidence: [Layout repair and bounded verification](../../reverse/attempt_support/bridge-ctor-layout-20261104.md).
Clearance: constructor composition only; full-image linking and runtime unverified.
Census confirmation: awaiting; no headline linking change claimed.
