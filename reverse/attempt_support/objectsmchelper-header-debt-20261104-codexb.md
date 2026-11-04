# ObjectSMCHelper canonical header debt retirement

Date: 2026-11-04; inspected source revision: `aca9a34025`;
worker: `yasinschroeder-codexb`.

Scope: `Code/GameEngine/Source/GameLogic/Object/Helper/ObjectSMCHelper.cpp`.
The TU already included canonical Drawable.h, which transitively supplied Thing.
Added a direct include of `Common/Thing/thing.h` so the Thing adoption lane can
verify its canonical include explicitly. No class declaration or body changed.

Both owning commands passed and each removed its own header-queue row:

```
python3 tools/header_adopt_lane.py accept --class Drawable Code/GameEngine/Source/GameLogic/Object/Helper/ObjectSMCHelper.cpp
python3 tools/header_adopt_lane.py accept --class Thing Code/GameEngine/Source/GameLogic/Object/Helper/ObjectSMCHelper.cpp
```

Verification after the include change:

- `find_declared_unmatched.py` passed; `./build.sh` retained all five byte matches.
- Comparing pre-change and post-change objects with `class_cleanup.runtime_graph`
  and `same_runtime` returned true: 42 runtime sections and 36 external
  definitions on each side. This includes non-debug bytes, relocations,
  providers, weak defaults and COMDAT policies.
- `link_check.py` used current dependency-cached inputs and reported one of one
  units link cleanly, with LINKED 622 -> 622 bytes. Its census reference was
  2026-11-04 20:47 at `f12552d0a7`. This is a preview, not a new census gain.
- `check_csv.py` passed: 99,452 functions, 9,328 symbols and 2,268 data rows.

ModelConditionFlags header debt remains. The separate destructor consolidation
still requires the reconciliation recorded in
[the earlier attempt](objectsmchelper-consolidation-20261104-codexb.md);
no source was moved and no merge or linked-byte increase is claimed.
