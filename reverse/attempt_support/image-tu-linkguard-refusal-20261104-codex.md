# Image TU consolidation LinkGuard refusal

Inspected source revision: `51fe3f09f8`; allocated shard: `0/5`.

Commands and results:

- `python3 /opt/runner/consolidation_queue.py --check-tu Code/GameEngine/Source/GameClient/System/Image.cpp` — passed.
- `python3 tools/name_lane.py consolidate --under Code/GameEngine/Source/GameClient/System/` — completed with no missing inputs.
- `python3 tools/name_lane.py consolidate --check build/consolidation` — passed.
- `python3 tools/tu_skeleton.py --plan Code/GameEngine/Source/GameClient/System/Image.cpp` — 33 approved rows, 5 donor files, 1 mixed file, 0 refused.
- `python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/GameClient/System/Image.cpp --dry-run` — no accepted donors. LinkGuard rejected `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva002D9186.cpp`: it links in the census, but its merged object would not, due to the `_M_erase` COMDAT for `Rva002D9186Element`.

Other unchanged donor blockers in the same dry-run: `StlSweepW5Rva002D8FB7.cpp` failed bytes; `ImageCollectionDtor.cpp` and `ImageCollectionFindImage.cpp` hit duplicate declarations. No merge was applied, no claim was taken, and no source or ledger changed. Next check: investigate the `_M_erase` provider/consumer binding before reconsidering this donor; leave it untouched meanwhile.
