# W3DMouse LinkGuard provider refusal

Inspected source revision: `a0bb7d5b8e`; allocated shard: `0/5`.

Commands and results:

- `python3 /opt/runner/consolidation_queue.py --check-tu Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouse.cpp` — passed.
- `python3 tools/name_lane.py consolidate --under Code/GameEngineDevice/Source/W3DDevice/GameClient/` and `--check build/consolidation` — planner completed with no missing inputs; snapshot check passed.
- `python3 tools/tu_skeleton.py --plan Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouse.cpp` — 54 approved rows, 4 donor files, 4 mixed files, 0 refused.
- `python3 tools/tu_skeleton.py --merge Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouse.cpp --dry-run` — no accepted donors. The seed itself fails LinkGuard under every merged flag set: it links at census, but the merged object leaves `?freeBytes@AsciiString@@AAEXXZ` unresolved and selects a non-retail `?set@AsciiString@@QAEXABV1@@Z` COMDAT.

The ctor donor fails on private `DX8Wrapper`/`Mouse` declarations; two other donors redeclare `MAX_2D_CURSOR_ANIM_FRAMES` (C2365). No merge was applied, no claim was taken, and no source or ledger changed. This is separate from the existing W3DMouse omitted-funclet obstacle. Next check: resolve the AsciiString provider/selection for the seed before retrying any donor.
