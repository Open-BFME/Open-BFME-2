// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva004E3CD0::~
// Rva004E3CD0 at 0x004E3CD0 (pinned opaque SEH base dtor; identity unproven).
// Each class below stores its own vtable (DIR32 auto-patches) and tail-calls
// the base destructor; the base itself is only declared here (defined
// nowhere -- it resolves via the pin), because a same-TU definition would
// capture the call locally instead of at the ledger address. Owner
// identities are unproven (opaque Rva names). One ledger row per destructor,
// landed one commit at a time.

class Rva004E3CD0
{
public:
	virtual ~Rva004E3CD0();
};

class Rva004E3D2A : public Rva004E3CD0
{
public:
	virtual ~Rva004E3D2A();
};

Rva004E3D2A::~Rva004E3D2A()
{
}

class Rva004E3D47 : public Rva004E3CD0
{
public:
	virtual ~Rva004E3D47();
};

Rva004E3D47::~Rva004E3D47()
{
}
