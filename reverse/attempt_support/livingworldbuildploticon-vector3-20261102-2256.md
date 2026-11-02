# Adopt canonical Vector3 in LivingWorldBuildPlotIcon

Base `d41f899c6523ea356ddc9f90779eda2a8170094c`. Source `Code/GameEngine/Source/GameClient/LivingWorld/LivingWorldBuildPlotIcon.cpp`; scope claimed before editing.

Use the existing registered storage header and preserve native layout, ABI, retained bytes and relocation targets. Local helpers retain the original inline operation order where required.

The normal byte gate preserves 3 matched row(s), with existing
extents 307, 10, 10 bytes. Actual COFF comparison
preserves 34 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
none.

All 39 non-debug sections preserve their bytes and relocation target positions. Defined compiler-local $T/$L labels are resolved by section/value; external names are never normalized.

Normal/frozen and owning header acceptance pass. No shared header, compiler flag, native-address pin, alias, data row, source path or baseline changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameClient/LivingWorld/LivingWorldBuildPlotIcon.cpp: LINKS  LINKED 316 -> 316 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 316)
link_check: 1 of 1 link cleanly; LINKED 316 -> 316 bytes (3.1s)
```

Controls: ignored `build/up-to-eighteen-each-20261102-2256/b2-02-*` and matching diagnostic package. Local inference not needed for this scope; build pool14 per repository, aggregate28 logical CPUs available; no local model needed.
