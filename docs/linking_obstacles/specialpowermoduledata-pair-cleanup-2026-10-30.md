### SpecialPowerModuleData pair cleanup (2026-10-30)

At base `23bfc966db`, the destructor's EH cleanup used a standalone reference
at `+14`, while retail destroys the pair at `+10` through `004C9F38`.
Reusing the constructor's existing pair view preserves both destructor rows
and makes its EH graph EXACT, retiring one EH baseline entry. Strict paired
preparation passes 13/13 rows and one data row; paired EH is EXACT 2. Both
sources preview LINKS against `85f6b7f40c`, retaining 508 authored bytes.
Full affected-consumer selection and census confirmation remain unverified;
carry this pair and its reference-holder consumers into the next scheduled
census. No linked-byte gain is claimed.

The seven proposed cleanup/handler rows remain blocked on the parent's
displaced TU assignment. No source path or generated row was changed.
[Native layout proof and TU boundary](../../reverse/attempt_support/specialpower-data-eh-20261030-codex3.md).
