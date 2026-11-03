### LINK-019: `Rva0039B893` vtable mismatch across copy-ctor and default-ctor units blocks `ScoreKeeperPerFrameStatsDefaultResizeDeferred.cpp` linking

**Status: Cleared. Updated: 2026-10-26; inspected revision: d831bc24031.**

- **Evidence / scope:** `Code/GameEngine/Source/Common/RTS/ScoreKeeperPerFrameStatsDefaultResizeDeferred.cpp`
  failed link_check with unresolved virtual symbols `loadPostProcess`, `crc`, `xfer` and COMDAT
  vtable divergence for `??_7Rva0039B893@@6B@`. The class declared virtual methods from Snapshot without
  bodies, differing from the single virtual destructor emitted by earlier link-order unit `V3PolyCopyCtors.cpp`.
- **Completed:** Reconciled `Rva0039B893` declaration in `ScoreKeeperPerFrameStatsDefaultResizeDeferred.cpp`
  to match `V3PolyCopyCtors.cpp` with `virtual ~Rva0039B893()`, eliminating pure virtual unresolved references
  and COMDAT vtable conflict.
- **Clearance:** `tools/link_check.py Code/GameEngine/Source/Common/RTS/ScoreKeeperPerFrameStatsDefaultResizeDeferred.cpp`
  reports: LINKS (0 -> 66 bytes). Full 2/2 matched rows preserved.
- **Census confirmation:** awaiting the next census.
