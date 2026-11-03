### LINK-185: AptSkirmish profile unwind wrapper conflicts with its existing provider

Status: Blocked. Updated: 2026-11-03; inspected revision: f24e6ea67b.
Scope: AptSkirmishDestructor.cpp funclet at 0x00796303 and TailJumpWrappers5B.cpp wrapper at 0x0052163E.
Completed: an empty derived view corrects the unwind binding and preserves 12/12 matched rows, but creates a duplicate provider and loses the caller's 351 census-linked bytes in preview; the trial was reverted.
Remaining / next check: establish an approved TU for the wrapper and reconcile its provider ownership before changing the caller; preserve the normal base-dtor call at 0x003148E6 and unwind wrapper call at 0x0052163E.
Evidence: [banked trial, identity targets and link-preview boundary](../../reverse/attempt_support/apt-skirmish-profile-wrapper-20261103/README.md).
Clearance: pending. Census confirmation: none claimed.
