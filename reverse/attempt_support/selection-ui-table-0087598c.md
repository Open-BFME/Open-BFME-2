# Selection UI table at RVA 0x0087598C

On master 4671394f63 the eleven little-endian pointers in the 1.06 PE
agree with the table in Rva005D3C2BDtor.cpp. Slots 3, 4, 8, 9 and 10
already target named nonvirtual SelectionUIImpl methods. Six slots have
other owners. Of the six, only slot 0 (0x0030D377) currently has multiple
function rows. A single ledger row for each of the other five establishes
neither a distinct class nor an ICF fold.

The virtual respell dry run for ShowCommandPoints refuses: the installer
names Rva005D3C2B. The class fold into StrategicHUD::SelectionUIImpl refuses:
none of its named methods are rowed virtual and its scoped name cannot
supply initializer proof. Moving slots 1 and 6 into Rva005D3C2B together
also refuses: the destructor object emits no compiler table for that class.

The checked-in base and derived declarations both have virtual destructors.
None of the eleven retail entries is a deleting destructor, and the adjacent
base table at 0x00875908 contains eleven pure calls. The owner setter at
0x0057873E directly calls the complete destructor and then operator delete.
A direct call does not independently prove destructor virtuality. Resolve
the destructor decoration and its existing unwind rows before trying a shared
eleven-slot declaration in the two installer units. No rows changed.
