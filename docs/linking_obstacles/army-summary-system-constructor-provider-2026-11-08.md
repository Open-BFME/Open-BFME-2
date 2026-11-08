# ArmySummarySystem constructor provider

Status: blocked on constructor/helper identity and complete virtual surface.

Rva0040DB52Ctor.cpp's 98-byte constructor passes normally. The table at
0x008394CC is named ArmySummarySystem by native getter 0x0040DBA3; this is
not the canonical ArmySummary class. As LINK-619 records, its /Oy- context
emits a 31-byte deleting destructor that precedes the 28-byte native owner
in Rva0040DB52Dtor.cpp. The constructor view also retains two pure slots
where native has the empty post-load callback and name getter.

A whole-file typed-vector trial is reverted: both byte and private link
checks reject it. The native 29-byte empty-base helper conflicts with the
known pointer-vector 15-byte helper, and new member typing changes scheduling.
Empty-vector construction/clear cannot establish element domain or stride.
Recover that evidence and reconcile helper identities before another type
trial; preserve the constructor's exact bytes and fix virtual/provider scope
together. No new flag hatch or abstract-destructor declaration is justified.

[Native boundary, retained row and rejected whole-file trial](../../reverse/attempt_support/army-summary-system-constructor-20261108/README.md).
