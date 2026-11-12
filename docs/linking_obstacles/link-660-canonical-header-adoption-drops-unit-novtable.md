### LINK-660: canonical header adoption drops a unit's `__declspec(novtable)`, so the unit emits its own base table and deleting destructor
Status: Open (one instance repaired). Updated: 2026-11-12; seat halilkkaya-lk96, base `af29ac558c5`.

**Problem.** Several units declared an abstract base privately as `class __declspec(novtable) X { virtual ~X(); }`
so that they never emit `??_7X@@6B@` or `??_GX@@UAEPAXI@Z` (Rva006CBF40Siblings.cpp said so in a comment). The
headers `tools/header_adopt_lane.py` generates from `reverse/class_contracts/X.json` carry no novtable. When a unit
adopts one, its inline `X` constructor stores the base vptr again, so the unit emits the base table and a COMDAT
deleting destructor that calls the out-of-line `~X`. Two failure shapes follow:
- the destructor has no definition, and the unit stops linking (an unresolved `??1X@@UAE@XZ` in the real link);
- the destructor exists, but the unit's `??_G` is not retail's body and comes first in path order, so
  `vtable_bridge` refuses every table whose slot names that `??_G` (target-not-winning-provider) and the image keeps
  a short copy.

**Instances.**
- Rva006DE350 ("Register canonical Rva006DE350, adopt it in 10 units"): Rva006CBF40Siblings.cpp and the five
  Rva006D8510/D86F0/D88B0/FB9B0/FBA10 deleting-destructor units each emitted a 30-byte `??_GRva006DE350`; retail's
  is AptValue.cpp's 75-byte body at 0x006DE820, slot 14 of AptValue's 15-slot table 0x008EAED0. An offline bridge
  plan refused the four names there (AptValue, BfmeAptValue006DCD20, Rva006DE350, RvaAptValueBase). **Repaired**
  ("Keep novtable on Rva006DE350 in six units so AptValue's tables bridge again"): refused 36 -> 35, the four names
  bridged at 15 slots again, nothing else changed; the six units LINKS unchanged.
- Rva0056AC26A and Rva0056AC26B ("Register canonical Rva0056AC26A, adopt it in 4 units" and its B twin): only
  OpaqueScalarDeletingDtorsB12.cpp constructs them (its `Rva0056AD19(EmitVtableTag *)` scaffold). It now emits
  both base tables, whose `??_G` call `??1Rva0056AC26A@@UAE@XZ` and `??1Rva0056AC26B@@UAE@XZ`, which nothing
  defines: the two unresolved symbols in the newest real link. link_check at `af29ac558c5`: B12 "does not link",
  699 -> 0 B. **Open**: the file is claimed by nleigh. The same two-line fix applies (forward declarations
  `class __declspec(novtable) Rva0056AC26A;` and `class __declspec(novtable) Rva0056AC26B;` ahead of the two
  includes); LINK-627 also lists that scaffold's two derived tables as stale spellings no retail code installs.

**Recipe.** Keep the unit's novtable property on a forward declaration ahead of the canonical include
(GpuDrawModuleInfoDtor.cpp precedent). The header still supplies the class and its layout; class_gate accepts it.
Compare the unit's object before and after: only the unwanted `??_7X`/`??_GX` and the dead base vptr store in the
inline `??0X` go away.

**Scan.** Commits of the last 48 hours that removed a private novtable class definition: the two above, plus
GameStateMap (before the newest real link; no refusal or blocker follows from it) and three deliberate module-data
adoptions (CrateCollide, DestroyDie, ModuleData). Tooling lead: `header_adopt_lane.py apply` could keep a novtable
forward declaration when it replaces a novtable view, or refuse an adoption after which the unit's object gains a
`??_7`/`??_G` for the adopted class.
