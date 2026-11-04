### LINK-212: Image TU merge loses the census-linked STL erase COMDAT provider
Status: Blocked. Updated: 2026-11-04; inspected revision: 51fe3f09f8.
Evidence / affected units: `Code/GameEngine/Source/GameClient/System/Image.cpp` and `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva002D9186.cpp`; [scoped dry-run evidence](../../reverse/attempt_support/image-tu-linkguard-refusal-20261104-codex.md).
Completed: allocation and current-input planner checks passed; LinkGuard refused the donor because it links at census but the merged object would not provide the `_M_erase` COMDAT for `Rva002D9186Element`.
Remaining / next check: trace the provider and consumers for that COMDAT and verify the binding before attempting a new merge.
Clearance: pending; the donor was not merged.
Census confirmation: not claimed.
