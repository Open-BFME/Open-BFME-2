# ArmySummarySystem constructor provider boundary

The served Rva0040DB52 constructor's 98-byte body is still exact. Its native
table 0x008394CC has a name getter at 0x0040DBA3 returning
"ArmySummarySystem"; it is distinct from the registered ArmySummary class.
No class is renamed or assigned a donor path from this literal.

As LINK-619 already records, this constructor unit's /Oy- context emits a
31-byte framed scalar deleting destructor, while the native owner in
Rva0040DB52Dtor.cpp is 28 bytes. That is a real provider mismatch, not the
alignment-only getter boundary. Slots 1/2 also remain pure in the constructor
view instead of the native empty callback/name getter. No flag exception,
new pragma, import pin or artificial abstract destructor is introduced.

A private whole-file storage-view trial replaces the two BfmeE16 vectors
with the scalar/pointer operation views already used for clearing them.
It does not preserve the constructor: the known void-pointer vector-base
name binds to the native 15-byte helper at 0x00025100, while this constructor
calls the 29-byte helper at 0x00211E58. The new emitted scalar/proxy bodies
also change provider selection, and typed member access reschedules finish
pointer loads across the two float stores. Both caller bytes and LinkGuard
reject the trial. The unlanded candidate is evidence only.

Default construction and clearing an empty container do not establish its
stored element domain or stride. Recover those from per-element users and
reconcile the real helper identities before attempting the type cleanup.
Keep the framed-deleting-destructor and full Snapshot-slot prerequisites
with that work. No Code or ledger change is retained; normal build still
passes the one constructor row. The table's real-link pass test remains open.
