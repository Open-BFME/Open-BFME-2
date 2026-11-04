# DamageNugget.cpp consolidation: no donor accepted (2026-11-04, claude seat)

`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/DamageNugget.cpp --dry-run`
(at origin c8b988aae8) accepted none of the 4 donors; `tu_views.py` reports:

- `Rva00507823`: canonical header `GameLogic/Module/Rva00507823.h`; the donors'
  header-queue rows still fail (`header_queue.tsv`), so this is header-lane work first.
- `DamageNugget`: conflicting views in all 5 files. The seed (ctor 0x00507C2D,
  `doEffectPosition`) declares no virtuals; `Made002CC5E1Rva00507991.cpp` declares
  15 slots with placeholder names (`v1`, `v6`, `pad07`..`pad13`, `v14`), only some
  rowed (`rva00507943`, `rva0050797D`, `v4`, `rva00507991`); `Made002CC5E1Rva005084FC.cpp`
  rows `rva005086CE` as a non-virtual (`QAE`) although its notes put it at slot 1 of
  0x00864048. One shared declaration therefore renames rows (virtual mangling) and
  makes the merged ctor's vftable reference undefined slot names: identity work
  (name slots 1, 6..14 of 0x00864048, settle `rva005086CE`'s virtualness), then merge.
- `Object`: `DamageNugget_generateDamageInfo.cpp` puts `module04` at +0x4 under
  the Thing base (own data starts at +0x60); needs the canonical Object view.
