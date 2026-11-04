### TileData RGBA mip fragment class views (2026-11-04)
Status: Cleared for the RGBA mip fragment and existing TileData destination only.
Completed: canonical TileData/RefCountClass adoption removes the private-view composition blocker; supported merge removes one fragment with 10/10 byte matches and preserves the pair's 719 preview-linked bytes.
Evidence / remaining scope: [repair, verification and path audit](../../reverse/attempt_support/tiledata-mip-consolidation-20261104-codex5.md); mixed TileDataGetRGBDataForWidth.cpp remains outside this merge, and no new census or whole-game link is claimed.
