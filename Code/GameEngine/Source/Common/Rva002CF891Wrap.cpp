// cl: /MD
// ?Rva002CF891Wrap@@YAXPAURva002CF571Item@@0@Z @0x002CF891 24B.
// EBP-frame cdecl wrapper over the rowed 0x002CF571 range loop: reserves one
// dword local, passes the address of its low byte plus the two through args
// (begin, end), cleans 0xc, leave/ret. Retail never reads the third arg in
// the callee; the byte local is modeled as an unused unsigned char whose
// address is taken. Callers at 0x002CFB98 0x002D0FE5 0x0033C40D.
struct Rva002CF571Item;
void __cdecl Rva002CF571Loop(Rva002CF571Item *first, Rva002CF571Item *last, void *unused);

void __cdecl Rva002CF891Wrap(Rva002CF571Item *first, Rva002CF571Item *last)
{
	unsigned char unused;
	Rva002CF571Loop(first, last, &unused);
}
