# HCompressedAnim visibility name: inherited-virtual ABI boundary

2026-11-01, GPT-6, lane R, budget30m, t=8min. No Code, shared header,
function row, pin or naming approval changes were applied by this attempt.

The fresh name_evidence wb lane grades Get_VisibilityF canonical at1903C0:
WorldBuilder A2FF90 explicitly asserts HCompressedAnimClass::Get_VisibilityF,
with score8 and its own hcanim.cpp path. The body and self-assert were reviewed
with wb_show. The normal function rename dry-run succeeds and proposes only
the implementation word and reference/shims/bfmehcanim/hcanim.h declaration.

The existing declaration lacks an explicit virtual keyword: it inherits that
property through BFME1 HAnimClass::_bfme_hanim_fade. BFME1's declaration has
the old spelling. In a private header copy, the exact normal rename therefore
loses that override. Official Scorer compiles the plan with the actual source
flags and the private header prepended to the include path. It emits
?Get_VisibilityF@HCompressedAnimClass@@QAEMHM@Z; its588-byte body remains exact,
but the required UAE virtual symbol is absent. The requested-symbol score is
-1, not a near-match score. The compiler cache under build/match was untouched.

This is an admission/ABI boundary, not missing name evidence. Do not land the
QAE spelling, add a pin/alias, edit the committed BFME1 reference or add a new
virtual slot merely to satisfy the row. LINK-023 already proves the shared
HAnim views disagree with native23-slot tables. A native-compatible BFME2 base
view and the override must be reconciled together. The current naming plan's
successful dry-run is not verification; its normal byte gate would reject the
missing UAE symbol. The unchanged two production sources pass80/80 rows,
3 string literals,30 compiler floats and2 named imports. All files remain at
their original content and the confirmed animation scopes are released after
banking. No measured linking or unique matched-byte gain.
