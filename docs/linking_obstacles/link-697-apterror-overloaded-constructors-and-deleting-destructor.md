### LINK-697 AptError table needs one lifetime identity across two constructors

**Status** Blocked. Inspected 2026-11-21 at `47e47e02607`.

The published real link at `c7c6a6fcab5` still bridges three emitters at RVA `0x008EC85C`. The canonical `AptError` emitter currently binds 13 of 15 retail slots. Its setter is rowed with placeholder parameters in `AptMiscObjects.cpp`. Its scalar deleting destructor is rowed under an opaque wrapper in `Rva006CBF40Deferred.cpp`. The complete destructor and zero-argument constructor still emit shorter tables under different class names. Either ordinary class fold refuses the other's third table name.

The scope build matched all 61 function rows and one data row. The factory object emits a byte-equal 35-byte canonical deleting destructor with the three retail relocations. The scoped destructor-member trial also matches with actual `EAStringC` fields at `+0x20` and `+0x24`.

The next check is a prepared setter respell and a coordinated lifetime change covering both constructor signatures, the retained complete destructor, and the approved `AptMiscObjects.cpp` placement of the deleting destructor. Verify each compiled installer against the 15 retail slots and check the following authoritative queue. [Native evidence and dry-run results](../../reverse/attempt_support/apt-error-table-20261121.md)
