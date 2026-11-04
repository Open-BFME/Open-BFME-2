# W3DMouse shard-0 consolidation blockers

Inspected revision: `d70d1218ef`; allocated shard: `0/5`.

Checks:

- `consolidation_queue.py --check-tu Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouse.cpp` — passed.
- Scoped consolidation planner under `Code/GameEngineDevice/Source/W3DDevice/GameClient` and `--check build/consolidation` — completed with no missing inputs; currency check passed.
- `tu_skeleton.py --plan .../W3DMouse.cpp` — 54 approved rows, 4 mixed files, no refused files.
- Merge dry run accepted no donors. `W3DMouseCtor.cpp` cannot include `d3d9.h`; `W3DMouse_releaseD3DCursorTextures.cpp` and `W3DMouse_freeD3DAssets.cpp` fail with missing-brace syntax errors. LinkGuard names the census-linked seed providers `W3DMouseCtor.cpp`, `W3DMouse_freeD3DAssets.cpp`, and `W3DMouse_releaseD3DCursorTextures.cpp`.
- Mixed-file split dry runs: `FamilyDeletingDtors3.cpp` cannot spell row `0x99203`; `W3DMouseCursorDirection.cpp` would leave matched row `0x422CD` out of its residual; `W3DMouseInitW3DAssets.cpp` would grow the hatch count through a copied helper or datum; `W3DMouse_loadD3DCursorTextures.cpp` compiles its carved rows alone but combined composition fails on duplicate `StringBase` definitions and LinkGuard.

No source or ledger changes were applied. These are mechanical blockers for this allocated composition; resolve the missing include/syntax, mixed residual/hatch constraints and selected `StringBase` provider context before retrying. The earlier AsciiString provider obstacle remains separately open under LINK-213.
