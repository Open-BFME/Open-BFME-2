# WanderAIUpdate destructor source split prerequisite

Inspected base: `c083ef052d`, 2026-10-30, codexb4.

The default picker served `Common/Rva0026E836Derived.cpp` on the historical
WanderAIUpdate destructor duplicate. LINK-149 already records its repair:
WanderAIUpdate.cpp now declares that destructor out of line. No source trial
or new linking repair was needed.

Current checks:

- `./build.sh` verifies all 12 rows of Rva0026E836Derived.cpp and all 12 rows
  of WanderAIUpdate.cpp, including the latter's renumbered EH labels.
- A preview of the destructor unit alone still reports the duplicate from
  the saved `85f6b7f40c` index (2026-10-29 15:08). Overlaying both current
  objects gives 2/2 LINKS, 428 and 646 authored bytes. This is bounded preview
  confirmation of the existing repair, not a census gain.
- The supported source-layout planner was run under
  `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/`. Its report marks
  the committed map stale and keeps donor/name evidence at hint strength.
- `tu_skeleton.py --split Common/Rva0026E836Derived.cpp` rebuilds the current
  map in memory and lists two WanderAIUpdate rows. Its dry run with the full
  approved WanderAIUpdate.cpp destination identifies the destructor body at
  `0x004A935D` (the deleting destructor is its companion), then refuses before
  writing: `an escape-hatch count would grow (hatch_counters rule 3)`.

The mixed file's retained preprocessor lines include the linker alias from
`?f1@Rva0026E836_M1@@UAEXXZ` to the folded ControlBarInput stub. Carving keeps
that alias in both outputs. Removing or reconciling this interface binding is
a prerequisite to retrying the split; no alias, pin or baseline was added.
No source or ledger path moved, and declaration scans report both files clean.

Next check: recover the secondary interface contract and remove the alias in
its own verified change, then retry the supported split. Carry both units and
their consumers into the next scheduled census; broader consumer closure and
census confirmation remain pending.
