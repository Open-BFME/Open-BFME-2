### LINK-209: W3DMouse merge loses the AsciiString provider required by its seed
Status: Blocked. Updated: 2026-11-04; inspected revision: a0bb7d5b8e.
Evidence / affected units: `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouse.cpp`; [scoped dry-run evidence](../../reverse/attempt_support/w3d-mouse-linkguard-provider-refusal-20261104-codex.md).
Completed: allocated-TU and planner checks passed; LinkGuard rejected the trial because the seed links at census but the merged object leaves `AsciiString::freeBytes` unresolved and selects a non-retail `AsciiString::set` COMDAT.
Remaining / next check: reconcile the seed's AsciiString provider and selected COMDAT before attempting another merge; retain the separate W3DMouse omitted-funclet obstacle.
Clearance: pending; no donor was merged.
Census confirmation: not claimed.
