// cl: /MD
//
// Opaque DirtySock destructors tail-calling the shared base at 0x00666BA0.
// The base is only declared here (defined in Rva00666BA0Dtor.cpp) so the
// calls resolve at the ledger address instead of capturing locally.
// Vtable values are DIR32 auto-patches. Owner identities are unproven
// (opaque Rva names). One ledger row per destructor.

class Rva00666BA0
{
public:
	virtual ~Rva00666BA0();
};

class Rva00661350 : public Rva00666BA0
{
public:
	virtual ~Rva00661350();
};

Rva00661350::~Rva00661350()
{
}
