### Rows that do not need their class: two repairs for the real link's blockers (2026-11-04, seat ancalgonn-ops-srv1)

**Status: Open as a method. Applied to the units below; the next real link measures them.**

Most of the real link's unresolved names come from a compiler vtable: a rowed constructor or
destructor makes the unit emit its class's table, and the table names members no unit defines.
Two repairs remove those references without new row names, and both keep the row byte-exact.

**1. The unit is a Zero Hour port of a class retail does not have.** Test it first: game.dat has no
string naming the class, and no other unit uses it. Keep the file and its rows and delete the
class's bodies. A row can stay without the class:

- a non-inline row stays an ordinary definition;
- a non-virtual inline stays by explicit instantiation or a pointer anchor;
- a virtual inline or a constructor stays through a file-local function nothing runs that calls it
  directly (`object->Class::slot()`, or a local of the type), with an extern pointer holding that
  function. `#pragma inline_depth(0)` around the function, or `/Ob0` on the unit, keeps the call out
  of line. Use neither when the row's own body needs an inline: `Matrix3D(bool)` needs its inlined
  `Make_Identity`, so `JetAIUpdate.cpp` relies on `/O1`, which keeps the constructor out of line.

This answers "cannot be anchored", recorded in LINK-072. Examples: `DumbProjectileBehavior.cpp`,
`JetAIUpdate.cpp`, `RailedTransportDockUpdate.cpp`, `WW3D2/collect.cpp`, `WWSaveLoad/twiddler.cpp`.

**2. The class is real but its virtuals are not all named yet.** The constructor stores retail's
tables itself, and each table is filled from retail's words with the ledger row at each slot's
address (`extern "C" { void __identifier("<row>")(); }`, then `(const void *)&__identifier("<row>")`).
Either give the class no virtuals of its own (`Rva005BA1FDCtor.cpp`) or, when a real base needs the
derived class to stay derived, mark it `__declspec(novtable)` so the constructor emits no table
(`Rva0008EF3FProductCtor_Unresolved.cpp`). Name the tables plainly: the compiler reserves a class's
`??_7` names as soon as the class is defined. This also makes the table retail's length.

**Limits.** Neither repair helps when the missing names are base destructors an EH unwind calls by name
(`Rva0057621ACtor.cpp`), or with real virtual inheritance (`Rva005F422CDtor.cpp`). A hand table is a
step toward linking, not the final source: when the class's members get real names, go back to the
compiler's table. Repair 1 removes retained COMDATs, so read the push hook's `link_batch_audit` and the
next real link for any provider a consumer loses.

**Evidence.** Each unit's rows byte-verified by `./build.sh` at the time of its commit. Unresolved at
`fe50b7af7a`, before these landed: 271. Not yet measured after them.
