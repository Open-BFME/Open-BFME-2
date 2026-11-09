# rename.py --to-class chain walker: banked, not landed

Branch `chain-proof`, head 936df17ced, on srv1's seat6-r1; `walker.diff` is its whole change. It tried to relate a table
to a class by a same-`this` walk from the table's destructor or constructor to the class's vptr store. Codex refused both
rounds, with false accepts on synthetic bytes through the real planner and no unrelated retail table found.

Round 1: linear decoding read `this` across a jump, a return, a tail jump and a call inside the row. An unreadable receiver
counted as another receiver, which lifted a canonical header's veto. The deleting-destructor test was a shape with wildcards.

Round 2: backward edges can make a `this` receiver (`mov esi,ecx; mov ecx,[ecx+4]; dec eax; jne back; mov ecx,esi; store`).
Skipping operator new still cleared the veto. `__EH_prolog` (0x00629188) overwrites eax and ebp, so treating it as harmless
aliased registers. The classifier still admitted an ordinary method. The allocation rule excused FormationTranslator
(0x00C3C97C) and AptLoadScreen (0x00C3D490) as well as W3DShroud (0x00BC6568).

The principle: a helper storing a vptr through ecx proves a vptr install at that address, not C++ derivation. A general
proof inside a rename gate is the wrong shape. The landed form is one reviewed entry per class in
`tools/retail_identity.py` (`SHARED_SLOTS`), which a reader can check by hand and which accepts nothing unlisted.

Useful as evidence: the same 24 tables and paths the entry states came from this walk, under its strictest round. The
walker's verdict on them is not what proves them; the entry's facts and its review are.
