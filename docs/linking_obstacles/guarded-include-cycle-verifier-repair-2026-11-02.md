### Guarded include-cycle verifier repair (2026-11-02)

The cycle check now uses the complete literal include graph and stable-guard
residual cycles, fixing the recorded guarded-intermediate false rejection.
Guard resets and alternate unguarded cycles remain refused.229 header tests
and61 exploit cases pass, with one existing exploit skip. No game source or
header queue is changed by this separate verifier fix. The original strict
STLport walk now stops at its unchanged continued-comment refusal in
config/stl_dec_vms.h:50; Carryover parent adoption is still unaccepted.
Evidence: reverse/attempt_support/header-cycle-verifier-20261102/.
