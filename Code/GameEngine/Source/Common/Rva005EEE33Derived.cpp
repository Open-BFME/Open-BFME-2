// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva005EEE33::~
// Rva005EEE33 at 0x005EEE33 (matched opaque chain dtor in
// Rva005EE30CChain.cpp; only declared here so each tail-call resolves to the
// ledger address instead of a same-TU definition). Each class below stores
// its own vtable (DIR32 auto-patches) and tail-calls the base destructor.
// Owner identities are unproven (opaque Rva names). One ledger row per
// destructor, landed one commit at a time.

class Rva005EEE33
{
public:
	virtual ~Rva005EEE33();
};

class Rva005D9A1E : public Rva005EEE33
{
public:
	virtual ~Rva005D9A1E();
};

Rva005D9A1E::~Rva005D9A1E()
{
}

class Rva005D9F70 : public Rva005EEE33
{
public:
	virtual ~Rva005D9F70();
};

Rva005D9F70::~Rva005D9F70()
{
}
