# Consolidation shard 1 follow-up (2026-11-04)

- `Code/Libraries/Source/Lua/lapi.c`: the allocated check, scoped planner,
  destination plan and guarded dry run completed. Neither proposed record-lookup
  donor was accepted: both had no baseline match. LinkGuard reports all three
  objects census-linked. No source edits or claims.
- `Code/GameEngine/Source/GameLogic/System/RankInfo.cpp`: the allocated check,
  scoped planner, destination plan and guarded dry run completed. No donor was
  accepted. LinkGuard refused the destination composition because it creates a
  duplicate selected `?theRankBlockParse@@3UBlockParse@@A`; `RankInfoParse.cpp`
  also failed bytes, and the planner requires `Overridable` adoption first.
  Census-linked units are listed in the tool report. No source edits or claims.

The `W3DFloorDraw.cpp` accepted-donor trial was restored after staged identity
and data shadow checks reproduced the existing blocker recorded in
`w3dfloordraw-merge-identity-audit-blocker-20261104.md`; all 32 owned claims
were released. Do not retry without resolving that prerequisite.
