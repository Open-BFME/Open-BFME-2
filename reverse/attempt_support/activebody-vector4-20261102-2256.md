# Adopt canonical Vector4 in ActiveBody

Base `d41f899c6523ea356ddc9f90779eda2a8170094c`. Source `Code/GameEngine/Source/GameLogic/Object/Body/ActiveBody.cpp`; scope claimed before editing.

Use the existing registered storage header and preserve native layout, ABI, retained bytes and relocation targets. Local helpers retain the original inline operation order where required.

The normal byte gate preserves 73 matched row(s), with existing
extents 13, 13, 7, 7, 7, 92, 11, 115, 10, 11, 28, 69, 18, 28, 95, 25, 78, 88, 484, 191, 421, 385, 113, 134, 315, 551, 62, 1189, 36, 54, 513, 83, 33, 7, 23, 21, 28, 31, 10, 10, 10, 10, 22, 8, 10, 32, 140, 126, 440, 319, 17, 10, 2107, 8, 8, 8, 8, 8, 8, 11, 8, 8, 8, 10, 8, 8, 11, 8, 11, 8, 11, 13, 13 bytes. Actual COFF comparison
preserves 164 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
none.

All 219 non-debug sections preserve their bytes and relocation target positions. Defined compiler-local $T/$L labels are resolved by section/value; external names are never normalized.

Normal/frozen and owning header acceptance pass. No shared header, native-address pin, alias, data row, source path or baseline changes. No compiler flag changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/Object/Body/ActiveBody.cpp: LINKS  LINKED 8,323 -> 8,323 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 8,323)
link_check: 1 of 1 link cleanly; LINKED 8,323 -> 8,323 bytes (3.3s)
```

Controls: ignored `build/up-to-eighteen-each-20261102-2256/b2-16-*` and matching diagnostic package. Local inference not needed for this scope; build pool14 per repository, aggregate28 logical CPUs available; no local model needed.
