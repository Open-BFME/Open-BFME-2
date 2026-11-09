### LINK-444: MaterialPassClass consumer header adoption
Status: Open. Updated: 2026-11-05; inspected revision: `5f6ed5eb3e`.
Completed: RTS3DSceneCtor, rinfo and both DX8 material-pass append consumers adopt the existing canonical header; the owning accept tool retires four header-queue rows.
Evidence: [cohort checks and remaining diagnostics](../../reverse/attempt_support/materialpass-header-20261105-codexb4/readme.md).
Remaining / next check: four consumers remain: the constructor/destructor providers need typed owning stage lifetimes, W3DGlowOutlineMaterialPassClass needs reference-base reconciliation, and MeshClassRender needs its Render floating-point code generation preserved after the base-slot correction; matpass merge flag obstacles remain separate.
Clearance: all four edited consumers byte-match (55 rows); acceptance and combined preview retain 2,962 census-linked bytes. Wider class adoption remains open.
Census confirmation: awaiting; no headline change claimed.

2026-11-05: five more consumers adopt MaterialPassClass with corrected embedded/base extents; 219 rows byte-match and their combined preview retains 8,675 linked bytes. The owning lane retires five MaterialPassClass queue rows; [consumer checks and provider-removal audit](../../reverse/attempt_support/materialpass-consumers-20261105-codex.md).

2026-11-09: `W3DGlowOutlineMaterialPassClass.cpp` is out of the census on `??_7Rva0073F96A@@6B@`, and choosing between the two copies cannot fix it.
Retail's table at VA 0x00CF1544 (ledger 0x008F1544) has four slots: Delete_This 0x0006CE57, `??_G` 0x0073F9F4, 0x0073FA10 and 0x0073F9D1. This unit's local
`MaterialPassClass` stand-in gives one slot (`??_E`). `Rva0073F96ACtor.cpp`'s canonical header gives four, but slots 2 and 3 are the base's
`Install_Materials`/`UnInstall_Materials`. The fix is one class on the canonical base with both overrides; 0x0073FA10 is rowed as
`W3DGlowOutlineMaterialPassClass::rva0073FA10` and 0x0073F9D1 as the free function `bfmeGoTDB`, so both rows' identities move with it.
