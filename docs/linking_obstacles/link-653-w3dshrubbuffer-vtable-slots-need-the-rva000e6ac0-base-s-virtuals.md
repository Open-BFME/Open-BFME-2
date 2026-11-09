### LINK-653: W3DShrubBuffer vtable slots need the Rva000E6AC0 base's real virtuals

Status: open (2026-11-09).

Target facts: retail table RVA 0x007CECB8 (24 B, six slots) is bound in
`reverse/data_ledger.csv` as `??_7Rva000E9BAC@@6B@;??_7W3DShrubBuffer@@6B@`; the
real link bridges both names (`reverse/vtable_bridge_queue.tsv`, missing-source-slot
1-5). Slot 0 is the `??_E` of dtor 0x000E9BAC; slot 1 is 0x000E7529 (rowed
`?rva000E7529@Rva000E7529@@QAEXXZ`, `Code/GameEngine/Source/Common/VtableSlotBodiesR3.cpp`);
slot 2 is 0x000E9C0F (`?name@Rva000E9C0FNamed@@QBEPBDXZ`, returns "W3DShrubBuffer");
slot 3 is 0x000E96B4 (`?DoXfer@W3DShrubBuffer@@QAEXPAVXfer@@@Z`, non-virtual spelling,
`W3DShrubBufferDoXfer.cpp`); slot 4 is the shared ICF constant-true 0x0050B5C6; slot 5 is
0x000E9C15 (`?enable@Rva000E9C15ByteOneSetter@@QAEXXZ`). The base table
`??_7Rva000E6AC0@@6B@` (0x007CEAB4, six slots) is itself bridged: its slots 2-5
have no source virtuals either.

Structural inference: `Rva000E9BAC` and the `W3DShrubBuffer` view in
`W3DShrubBuffer.cpp` are one class over the `Rva000E6AC0` base; slots 1-5 are
overrides of base virtuals (name / xfer shape suggests a snapshot-style interface).
Not proven.

Prerequisite: declare `Rva000E6AC0`'s five virtuals with real names first (retire its
own bridge), unify `Rva000E9BAC` with `W3DShrubBuffer`, then respell the five rows above
as `W3DShrubBuffer` virtual overrides across their three files
(`rename.py function --virtual` cannot change the class). Not attempted: no source
change landed.
