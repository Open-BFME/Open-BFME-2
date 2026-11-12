# AptValue base table in the six built-in constructors

Tested on `572185fc5d` for the queue entry at RVA `0x008EAED0`.
Its recorded slot-14 refusal predates `fbfc9a8e06`, which addressed
the deleting-destructor provider. This attempt tested the source of
the vptr writes in the six constructors from `0x006DE480` to
`0x006DE790` in `Code/Libraries/Source/Apt/AptValue.cpp`.

Using the existing declaration of AptValue for the base constructor and
initializing its flag word preserved all 31 matched rows. Keeping the
private intermediate classes still left the two Rva006D6470Owner conflicts
and introduced a selected, non-retail AptValue constructor.

Replacing the intermediate classes with AptValueGC, AptValueWithHash and
AptObject from AptScriptFunction.h also matched 31/31 rows, 14 string
literals and 10/10 exception graphs. This version initialized the hash
member and the three AptObject bitfields through their constructors.
The scoped link prediction still rejected the selected AptValue constructor
and conflicting COMDATs for AptValueGC and AptValueWithHash. The frozen-file
check also reported four constructor definitions without rows in this unit.

Control after reverting the trial: 31/31 rows match. The same link index
at `c31795c94c` reports only the Rva006D6470Owner constructor and table
conflicts in the original unit. Both control and trial predict zero linked
bytes for the unit. No trial source or ledger change was retained.

Next investigate the out-of-line constructor owner at `0x006DCCC0` in
`AptValue/AptValueConstructorBFME2.cpp`. Its call to the type initializer
at `0x006DBBC0` is a boundary to verify alongside the inlined flag writes
in the six constructors. Compare both emitted copies and confirm the
selected body before moving the constructor's identity. The queue's pass
test requires a published real link that uses the source tables.
