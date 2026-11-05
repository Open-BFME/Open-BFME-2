# W3DLightDraw consolidation dry-run handoff

Inspected source revision: `463674729a`; allocator shard: `0/5`.

Commands and results:

- `python3 /opt/runner/consolidation_queue.py --check-tu Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLightDraw.cpp` — passed.
- `python3 tools/name_lane.py consolidate --under Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/` — completed with no missing inputs; `tools/name_lane.py consolidate --check build/consolidation` passed.
- `python3 tools/tu_skeleton.py --plan Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLightDraw.cpp` — 19 approved rows, 6 pull donors, 1 mixed file, 0 refused.
- `python3 tools/tu_skeleton.py --merge Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLightDraw.cpp --dry-run` — 0 accepted donors. Xfer and DoDrawModule failed C2504 because `DrawModule` is undefined; PoolKey failed C2065 for missing `m_radius`; the module-data constructor failed C2373 for a vftable redefinition; ReactToTransformChange failed a syntax error before `*`. `adopt_first` recommends DrawModule, LightClass, RTS3DScene, W3DDynamicLight and W3DLightDraw for the seed, DrawModule/Matrix3D/W3DLightDraw for DoDrawModule and W3DLightDraw for ReactToTransformChange. LinkGuard lists the destination and five affected donors as census-linked; no merged composition passed it.

No source, ledger or claim changed. Class declarations and header prerequisites need owner-side reconciliation before another merge trial.
