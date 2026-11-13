// cl: /MD
//
// Opaque DirtySock destructors tail-calling the shared base at 0x00666BA0.
// The base is only declared here (defined in Rva00666BA0Dtor.cpp) so the
// calls resolve at the ledger address instead of capturing locally.
// Vtable values are DIR32 auto-patches. Owner identities are unproven
// (opaque Rva names). One ledger row per destructor.

#include "Rva00666BA0.h"
// ??0Rva00666BA0@@QAE@XZ @0x00661320 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE2BD8) and returning this.
Rva00666BA0::Rva00666BA0()
{
}

class Rva00661350 : public Rva00666BA0
{
public:
	Rva00661350();
	virtual ~Rva00661350();
	// Retail table 0x00CE2BE8: the base's three __purecall entries, then three more.
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
};
// ??0Rva00661350@@QAE@XZ @0x006613A0 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE2BE8) and returning this.
Rva00661350::Rva00661350()
{
}

Rva00661350::~Rva00661350()
{
}
