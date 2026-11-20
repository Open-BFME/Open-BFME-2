# Render-object copy constructor bridge prerequisites

Inspected `579a7e91d2` on 2026-11-20. The picker served the three tables
emitted by `Rva003AE6A9CopyCtor.cpp`. The unchanged complete source passes
3/3 function rows and the declared-body check; that does not validate its
tables.

Native `game.dat` words, expressed as RVAs:

| Table | Slot targets |
| --- | --- |
| 0x0081D4E4 | 003AE718, 000B3FD0, 003ABB7D, 003ABB8B |
| 0x0081D4F4 | 003AE720, 000B3FD0, 0003B810, 00562945, 00562DDB, 00562BF7, 004BD9CB, 003F3FCE, 000910FB, 000910FB, 004647D1 |
| 0x0081D520 | 003AE73C followed by ten 0003B810 pure calls |

The secondary table inherits RenderObjectDrawModuleInfo's name and transfer
methods, but retail overrides both. The name getter is currently rowed as
the free integer-returning `Rva003ABB7DGet` in ConstIntGetters4.cpp.
The transfer thunk is rowed under `Rva00562945` in GapForwardersSeat8.cpp;
it adjusts the receiver by -0x18 before the primary transfer at 0x00562945.
Simply declaring overrides in Rva003AE6A9 would introduce unresolved names,
not connect these existing providers.

The primary class view still declares slots 1-10 pure, whereas retail has
concrete providers in nine of those slots. The intermediate table's
destructor also needs its real owning class identified. Existing attempts
already identify the Rva003AB9FF/Rva003AE6A9 and Rva003ACED6/Rva003AE683
class-identity problem; the current novtable lifetime views solve constructor
code shape, not virtual provider identity.

Next work is a coordinated class/provider reconciliation across those
owners, retaining the 0x18 secondary-base adjustment and constructor/EH
behavior, before rebuilding the tables. The explicit table consumer
Rva005634F7Ctor.cpp must be included. No aliases, extra providers, bridge
queue edits, or speculative class renames were made. All three bridges
remain pending the maintainer's next real-link measurement.
