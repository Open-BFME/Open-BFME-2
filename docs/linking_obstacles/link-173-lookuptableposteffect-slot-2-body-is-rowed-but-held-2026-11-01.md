### LINK-173: LookupTablePostEffect slot 2 body is rowed but held (2026-11-01, halilkkaya-codex)

Status: Open / skipped held body. Native 007CFAC8 slot 2 targets matched
00111DB6, currently Rva00111DB6::rva00111DB6 (QAEXXZ); ctor/dtor copies
instead emit __purecall. Its body file remains held by StarkillerHDX, so
owner/virtual reconciliation was not attempted. Base 007CFB24 slots 0/2-4
really are pure and stay so. Eight unchanged class/reference units preview
LINKS 2,350 B. [All slots, exact existing name and next identity step](../../reverse/attempt_support/purecall-slot-audit-20261101/lookup.md).


**2026-11-14 consolidation follow-up (merge-climb).** The slot-2 owner repair
was already present before this change (LINK-102's 2026-11-12 follow-up).
The current supported merge absorbs `Rva00111DB6PostFXLookupTable.cpp` into
`LookupTablePostEffect.cpp`: 20/20 rows preserved, zero lost, one source file
removed. The registered `Rva0007BB16Record` private body moves unchanged,
with one copy before and after; its header-adoption debt remains queued.
ProviderGuard and LinkGuard pass on the fresh 09:53 census index
`a5dce5d8f1f697c358276325b8b5237fa360d962837eaf82bcc083acdaf79c0e`.
All 50 external definitions, COMDATs, weak defaults and the five-slot derived
table are conserved; no new undefined symbols, identity/data findings or
hatches. The ordinary preview reports LINKS (598 -> 940 authored bytes for
the destination); this is consolidation, not a census or real-link gain.
The old held-body condition is superseded for this verified cohort.
Broader post-effect/module-data contracts and real-link confirmation remain
open. Evidence: `sweeps/merge-climb/gate-freed-landings/lookuptableposteffect/`.
