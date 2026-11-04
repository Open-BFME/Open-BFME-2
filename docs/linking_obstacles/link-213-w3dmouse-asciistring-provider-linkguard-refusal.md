### LINK-213: W3DMouse merge loses the AsciiString provider required by its seed
Status: Blocked. Updated: 2026-11-04; inspected revision: a0bb7d5b8e.
Evidence / affected units: `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouse.cpp`; [scoped dry-run evidence](../../reverse/attempt_support/w3d-mouse-linkguard-provider-refusal-20261104-codex.md).
2026-11-04 consolidation follow-up: a fresh shard-0 dry run still accepted no donors. Three donor compositions fail compilation (`d3d9.h` is unavailable for `W3DMouseCtor.cpp`; `releaseD3DCursorTextures.cpp` and `freeD3DAssets.cpp` fail with missing-brace syntax errors), while LinkGuard identifies `W3DMouseCtor.cpp`, `W3DMouse_freeD3DAssets.cpp` and `W3DMouse_releaseD3DCursorTextures.cpp` as census-linked providers. The `W3DMouse_loadD3DCursorTextures.cpp` split is also blocked by duplicate `StringBase` definitions and LinkGuard; other mixed-file split trials fail on residual row loss, an unspelled definition, or hatch growth. [Full trial evidence](../../reverse/attempt_support/w3d-mouse-consolidation-blockers-20261104-codex.md).
Completed: allocated-TU and planner checks passed; LinkGuard rejected the trial because the seed links at census but the merged object leaves `AsciiString::freeBytes` unresolved and selects a non-retail `AsciiString::set` COMDAT.
Remaining / next check: reconcile the seed's AsciiString provider and selected COMDAT before attempting another merge; retain the separate W3DMouse omitted-funclet obstacle.
Clearance: pending; no donor was merged.
Census confirmation: not claimed.
