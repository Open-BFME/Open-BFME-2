### LINK-444: MaterialPassClass consumer header adoption
Status: Open. Updated: 2026-11-05; inspected revision: `5f6ed5eb3e`.
Completed: RTS3DSceneCtor, rinfo and both DX8 material-pass append consumers adopt the existing canonical header; the owning accept tool retires four header-queue rows.
Evidence: [cohort checks and remaining diagnostics](../../reverse/attempt_support/materialpass-header-20261105-codexb4/readme.md).
Remaining / next check: four consumers remain: the constructor/destructor providers need typed owning stage lifetimes, W3DGlowOutlineMaterialPassClass needs reference-base reconciliation, and MeshClassRender needs its Render floating-point code generation preserved after the base-slot correction; matpass merge flag obstacles remain separate.
Clearance: all four edited consumers byte-match (55 rows); acceptance and combined preview retain 2,962 census-linked bytes. Wider class adoption remains open.
Census confirmation: awaiting; no headline change claimed.

2026-11-05: five more consumers adopt MaterialPassClass with corrected embedded/base extents; 219 rows byte-match and their combined preview retains 8,675 linked bytes. The owning lane retires five MaterialPassClass queue rows; [consumer checks and provider-removal audit](../../reverse/attempt_support/materialpass-consumers-20261105-codex.md).
