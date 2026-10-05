// cl: /O2 /MD
//
// ?rva0070DFE0@BfmeAptValue006DCD20@@QAEXXZ, retail 0x0070DFE0, 5 bytes.
// 5B jmp thunk to rowed ?rva006DE150@Rva006DE150@@QAEXXZ at 0x006DE150.
// Evidence: vtable slot 11 (offset 0x2C) of 18 vtables (e.g. 0x008EA264);
// callers at 0x006D93D3 plus jmp thunks at 0x006F2C69 and 0x00709E3F;
// LINK BONUS 2 files wait only for this body.

class Rva006DE150
{
public:
	void rva006DE150();
};

class BfmeAptValue006DCD20
{
public:
	void rva0070DFE0();
};

void BfmeAptValue006DCD20::rva0070DFE0()
{
	((Rva006DE150 *)this)->rva006DE150();
}
