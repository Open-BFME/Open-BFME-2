### LINK-550: InvisibilitySpecialPower constructor vtable declaration blocks composition
Status: Blocked. Updated: 2026-11-05; inspected revision: `2690b78ff205`.
Evidence / affected units: InvisibilitySpecialPower.cpp and InvisibilitySpecialPowerCtor.cpp; [trial and verification evidence](../../reverse/attempt_support/invisibility-consolidation-20261105-codexb4.md).
Completed: current-index merge reaches compilation; automatic view reconciliation reverts safely; restored sources pass 12/12 byte checks.
Remaining / next check: reconcile the complete constructor hierarchy and retail vtable bindings; its explicit compiler-vtable declaration conflicts with the home TU's actual interface base.
Clearance: pending; no source file removed or link gain claimed.
Census confirmation: not claimed.
