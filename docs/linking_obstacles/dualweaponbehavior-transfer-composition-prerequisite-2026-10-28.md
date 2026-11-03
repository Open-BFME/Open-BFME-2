### DualWeaponBehavior transfer composition prerequisite (2026-10-28)

Status: declaration prerequisite byte-verified at `c424759b95`; supported merge
blocked on absent destination census object. Base `4a0da02819`, preview index
`d92e7e6635`.
The seed now declares the existing nonvirtual UpdateModule::xfer method.
All seven seed rows, its constructor EH graph and all 25 external COMDAT
fingerprints and symbol/dependency sets are unchanged. All three original
inputs have strict current receipts and preserve eleven rows. The seed is
absent from the preview census; no ordinary linking verdict is claimed.
Both donors preview LINKS against that index (75 and 68 linked bytes).
The post-prerequisite dry run clears transfer composition's compile/byte checks,
then LinkGuard refuses the resulting earlier link order because the seed has
no census object. No applying merge or path move occurred. Retry after the
normal census/index includes the destination; external consumer selection
and census confirmation remain pending. The pool-key donor still needs
virtual-interface reconciliation and two mixed sources remain.
[Evidence](../../reverse/attempt_support/dualweapon-consolidation-20261028-codexb4.md).
