# Adopt canonical ICoord2D in Rva002ECE6AInfoCtor

Base `c55cddf26377555521449e646a4cc1efb04db6f9`. Source `Code/GameEngine/Source/GameLogic/Pathfinder/Rva002ECE6AInfoCtor.cpp`; scope claimed before editing.

Replace the private scalar-only POD view with the registered data header. The existing explicit Int typedef is int where used. Preserve every native body, external binding and non-debug section.

The normal byte gate preserves 2 matched row(s), with existing
extents 263, 436 bytes. Actual COFF comparison
preserves 8 external code bodies and relocation lists.
Added external code definitions: none. Removed definitions:
none.

All 11 non-debug sections preserve their bytes and relocation target positions. Defined compiler-local $T/$L labels are resolved by section/value; external names are never normalized.

Normal/frozen and owning header acceptance pass. No shared header, native-address pin, alias, data row, source path or baseline changes. No compiler flag changes. Fresh strict provider preparation and EH checks pass. The owning accept tool retires this source/class queue key.

Bounded preview, distinct from census/full-image/runtime proof:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/Pathfinder/Rva002ECE6AInfoCtor.cpp: LINKS  LINKED 699 -> 699 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 699)
link_check: 1 of 1 link cleanly; LINKED 699 -> 699 bytes (2.8s)
```

Controls: ignored `build/up-to-eighteen-each-20261103-0008/b2-02-*` and matching diagnostic package. Local inference not needed for this scope; build pool14 per repository, aggregate28 logical CPUs available; no local model needed.
