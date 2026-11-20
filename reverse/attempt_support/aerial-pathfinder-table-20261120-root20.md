# AerialPathfinder table and shared declarations

Both SaveGame lifetime units now use the established four-byte
BitFlags<11> specialization. Their five function rows, both EH
graphs, COMDAT fingerprints and reference graphs remain exact.
Together they retain 172 scoped linked bytes.

The map query now uses the registered AerialPathfinder declaration.
The list view binds to the proven storage at +0x10. Each operation
reads that storage directly, preserving the two head loads in the
131-byte height query. An intermediate cached reference collapsed
one of those loads and changed register allocation. The final 131-
and 133-byte functions, COMDATs and reference graph are exact.
The owning adoption tool retired the map query's header queue entry.

## Table at 0x007E74F0

Retail has 56 bytes and 14 slots. The current constructor and
destructor objects each emit four bytes. Native scratch trials with
the full subsystem slot profile emit the same 56-byte table in both
objects while preserving all five current function rows. The nine
inherited virtual names already have exact matched owners.
The deleting slot uses the compiler weak default to 0x0022C9DA.

Leaf slots 1 and 10 can emit the exact one-byte return at 0x000B3FD0.
The bridge verifier needs a named fold row for each, using the same
admission pattern as ActionManager. Slot 9 is the existing eight-byte
body at 0x0022C9D2. It adjusts the receiver by 0x10 and jumps to the
matched list clear at 0x0023DAA5. The owning transfer to
AerialPathfinder::reset requires the missing approved slot key
`Code/GameEngine/Include/GameLogic/AerialPathfinder.h|slot|AerialPathfinder@0x00BE74F0|9`.

Both lifetimes and the map query now share the existing eight-byte
polygon/height payload declaration. The owning fold admissions
established the 11-, 39-, 41- and 23-byte helper names at 0x0014F3C4,
0x0023DAA5, 0x0035C9A6 and 0x004EC395. Their original providers
retain their rows. The typed constructor and destructor match all
existing lifetime rows and bind the admitted list helpers. The
six-source build verified 81 function rows and six exact EH graphs.
The scoped preview kept 2,735 linked bytes.
