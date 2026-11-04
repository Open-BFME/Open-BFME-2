# TerrainResourceBehavior UpdateModule reconciliation, 2026-11-04

Base: `a1ad5f0db7`. Scope: `TerrainResourceBehavior.cpp` and
`TerrainResourceBehaviorCtor.cpp` in `Code/GameEngine/Source/GameLogic/Object/Behavior/`.
The default picker claimed the TU and its two clean donors.

The fresh-map merge dry run initially rejected the constructor (`m_20`/`m_24`
were raw pointer fields only in its private view) and the module-data destructor
(bytes). `tu_views.py --dry-run` confirmed incompatible base clauses for both.
The module-data destructor is unchanged in this commit.

Both behavior views now include canonical `UpdateModule.h` and describe the
existing +0x20/+0x24 interface subobjects. The TU-local inline accessors move
from the removed private base to the derived class. `novtable` retains the
constructor's existing explicit table installations and existing named providers;
no table identity or alias is added or removed. The +0x28/+0x29/+0x2C fields use
the main TU's existing names. Taking the interface addresses by native offsets
avoids VC7.1's nullable derived-to-base adjustment and preserves the retail
constructor's exact instruction sequence.

Verification:

- `./build.sh` on both sources: 18/18 code rows and the 52-byte vtable data row
  pass; string, float and import checks pass.
- `find_declared_unmatched.py` on both: all defined functions matched.
- `eh_verify.py` on both: EXACT 4/4, no baseline entries.
- `header_adopt_lane.py accept --class UpdateModule` on both: PASS, two queue
  entries retired through the owning tool. The corresponding
  `UpdateModuleInterface` acceptance on the main TU passes and retires one entry.
- `link_check.py` on the TU, constructor and unchanged module-data destructor:
  LINKS 1,188 + 135 + 48 = 1,371 bytes, unchanged from the 2026-11-04 05:53
  census index at `5a13f2cd61`. This is a current-object prediction, not a census.
- A new merge dry run accepts the TU and constructor. The module-data destructor
  still fails bytes and remains a separate donor; the two mixed sources remain.

No source path moves in this reconciliation commit. Merge application, path
consumer audit and final combined verification belong to the following commit.
