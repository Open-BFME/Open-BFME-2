### LINK-312: StructureBody merge selects a duplicate provider
Status: Blocked. Updated: 2026-11-04; inspected revision: `293fbba275`.
Evidence / affected units: `StructureBody.cpp` and `StructureBodyCtor.cpp` were census-linked by the guarded dry run; the merged composition would select duplicate `?rva004C09A1@Rva004C09A1@@QAEXPBURva004C09A1Object@@@Z`. The same definition spelling occurs in `Common/GapBodiesGE24.cpp` while the matched row is owned by `StructureBody.cpp`.
Completed: current allocation, scoped planner and TU plan passed; guarded `--merge ... --dry-run` refused both the seed composition (LinkGuard duplicate provider) and ctor donor (`bytes`). No source or ledger changes were applied.
Remaining / next check: resolve the duplicate provider's ownership and verify the affected object composition before retrying the merge.
Clearance: pending. Census confirmation: no new census claimed.
Evidence and other shard 1 dry-run prerequisites: [mechanical consolidation handoff](../../reverse/attempt_support/consolidation-mechanical-shard1-20261104.md).
