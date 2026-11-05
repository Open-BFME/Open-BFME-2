### LINK-412: W3DTornadoDraw consolidation needs canonical base and lifetimes
Status: Open. Updated: 2026-11-05; inspected revision: `643786484e`.
Completed: transfer TU adopts canonical DrawModule, replacing its padded opaque intermediate; 68B exact, link preview 68 -> 68B, one header queue row retired by acceptance.
Remaining / next check: adopt the seed's DrawModule view while reconciling all W3DTornadoDraw vtable emitters; separately reconcile module-data ctor/dtor novtable and lifetime models before another merge.
Evidence: [scoped verification and prerequisites](../../reverse/attempt_support/w3dtornado-drawmodule-adoption-20261105.md).
Clearance: transfer header adoption only; full consolidation remains open. Census confirmation: not claimed.
Update-radius cohort: canonical RadiusDecalTemplate adoption retires one header row (3/3 exact, link preview 239 -> 239B); its provisional Update TU still needs allocator-wrapper and class-view reconciliation: [evidence and next step](../../reverse/attempt_support/tornado-radius-header-adoption-20261105.md).
