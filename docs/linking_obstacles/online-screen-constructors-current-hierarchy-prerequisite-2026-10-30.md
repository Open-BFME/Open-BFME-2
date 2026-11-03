### Online screen constructors: current hierarchy prerequisite (2026-10-30, codex3)

The source-wide recheck of `Rva005BA1FDCtor.cpp` retains 2/2 exact rows
and U7 against index `12b9e7a7c0`; no source change or census gain. Native
constructor/destructor table stores and singleton accesses pair 0x005BA1FD
with the already-rowed opaque destructor 0x005BA23A, and 0x005BA28E with
0x005BA2CB. Both secondary deleting-thunk families already have rows. The
constructor's polymorphic-member placeholders and the two destructor emitters
need one complete inherited hierarchy; a shared BaseVirt pin cannot represent
the distinct deleting targets. The earlier assigned virtual-table audit remains
open. Both constructor boundaries now carry deferred attempt records.
[Target facts, owner scope and checks](../../reverse/attempt_support/online-screen-constructor-hierarchy-20261030-codex3.md).
