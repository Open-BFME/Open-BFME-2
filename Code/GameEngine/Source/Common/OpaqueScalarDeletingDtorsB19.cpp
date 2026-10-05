// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B19: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner (vtable bounds taken from the constructor vptr stores
// in .text; slots shared by three or more vtables are not counted as owners).
// Each destructor is declared, not defined, so the call resolves to its pin
// in reverse/symbols.csv; the dummy tag constructors (no retail counterpart)
// only make this TU emit each vtable and with it the deleting destructor.
// Owner identities are not recovered, and these declarations model no layout
// (docs/reconstruction/deleting-destructor-identity-audit.md).
//
//   wrapper     dtor        vtable#slot
//   0x007410D0  0x0074104C  0x00CF1648#0

struct EmitVtableTag;

class Rva0074104C
{
public:
	Rva0074104C(EmitVtableTag *);
public:
	virtual ~Rva0074104C();
};

// ?<Rva0074104C::Rva0074104C> absent-from-retail
Rva0074104C::Rva0074104C(EmitVtableTag *)
{
}
