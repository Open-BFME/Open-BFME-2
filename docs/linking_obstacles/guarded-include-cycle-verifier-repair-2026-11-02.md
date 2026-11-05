### Guarded include-cycle verifier repair (2026-11-02)

The cycle check now uses the complete literal include graph and stable-guard
residual cycles, fixing the recorded guarded-intermediate false rejection.
Guard resets and alternate unguarded cycles remain refused.229 header tests
and61 exploit cases pass, with one existing exploit skip. No game source or
header queue is changed by this separate verifier fix. The original strict
STLport walk now stops at its unchanged continued-comment refusal in
config/stl_dec_vms.h:50; Carryover parent adoption is still unaccepted.
Evidence: reverse/attempt_support/header-cycle-verifier-20261102/.

The unchanged STLport continued-comment refusal also blocks four Thing adoption trials before compilation. [Sources and recorded refusals](../../reverse/attempt_support/thing-header-adoption-20261104.md#scanner-handoff).

2026-11-04: The same `stl_dec_vms.h:50` refusal blocks StoreObjectsSpecialPowerModuleData adoption in MissileLauncherBuildingUpdate; the source remains unchanged. [Scoped evidence](../../reverse/attempt_support/rebuild-hole-moduledata-headers-20261104.md#remaining-consumers-and-prerequisites).

2026-11-05: Fixed the `stl_dec_vms.h:50` refusal for independently commented continuation lines; 149 header/exploit tests pass (one existing skip). OneRing's Object adoption now reaches a separate comma-expression refusal; other adoption prerequisites remain. [Verifier evidence](../../reverse/attempt_support/header-comment-splice-verifier-20261105-codex.md).
