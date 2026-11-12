# W3DTreeBuffer table at RVA 0x007CEEA4

The real-link queue at `12b12c9ec3` reports short copies of the retail
24-byte table under `Rva000EDA94` and `W3DTreeBuffer`. The constructor
at `0x000EDE35` and destructor at `0x000EDA94` both install it.
Slot 2 returns the literal W3DTreeBuffer. The consolidated source has
separate class declarations for the constructor and destructor.

The supported class-fold dry run refused because the existing
`W3DTreeBuffer` is registered. Its shared header only declares the
eight methods external callers use. The constructor view owns the
record array at +0x5C0, the object list at +0x44548 and the type array at
+0x44558. The destructor view models its list teardown through a
different wrapper. Reconcile the list destructor and its unwind calls
before putting both lifetimes under one shared definition. Then prove
the six table targets and rebuild the header consumers.
