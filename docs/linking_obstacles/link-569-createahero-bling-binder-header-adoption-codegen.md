### LINK-569: CreateAHeroManager bling-binder canonical storage changes register allocation
Status: Open. Updated: 2026-11-05; inspected revision: `72234bf59f`.
Evidence / affected units: `CreateAHeroManager_GetBlingBinder.cpp`, `0x0021A106`; [trials and retained accessor adoptions](../../reverse/attempt_support/createahero-accessor-header-20261105-codex2.md).
Completed: two sibling accessor units adopt the canonical header and pass owning acceptance, retiring two queue rows while preserving 112 preview-linked bytes; the bling-binder trial is discarded and its original source restored and byte-verified.
Remaining / next check: preserve native member reloads and register lifetimes when accessing canonical `field168`; the typed overlay hoists LEA and the scalar-pointer trial caches start in ESI (44B versus native 46B).
Clearance: pending exact reconstruction and header acceptance for the bling-binder unit; no current link regression claimed.
Census confirmation: not claimed.
