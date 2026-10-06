// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva006D63C0::~
// Rva006D63C0 at 0x006D63C0 (pinned opaque SEH base dtor; identity unproven).
// Each class below stores its own vtable (DIR32 auto-patches) and tail-calls
// the base destructor; the base itself is only declared here (defined
// nowhere -- it resolves via the pin), because a same-TU definition would
// capture the call locally instead of at the ledger address. Owner
// identities are unproven (opaque Rva names). One ledger row per destructor,
// landed one commit at a time.

class Rva006D63C0
{
public:
	virtual ~Rva006D63C0();
};

class Rva006DE2B0 : public Rva006D63C0
{
public:
	virtual ~Rva006DE2B0();
};

Rva006DE2B0::~Rva006DE2B0()
{
}

class Rva006DE6C0 : public Rva006D63C0
{
public:
	virtual ~Rva006DE6C0();
};

Rva006DE6C0::~Rva006DE6C0()
{
}
