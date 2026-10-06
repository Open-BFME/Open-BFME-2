// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva0055B0CC::~
// Rva0055B0CC at 0x0055B0CC (pinned opaque base dtor; identity unproven).
// Each class below stores its own vtable and tail-calls the base destructor;
// the base itself is only declared here (defined nowhere -- it resolves via
// the pin), because a same-TU definition would capture the call locally
// instead of at the ledger address. Owner identities are unproven (opaque
// Rva names). One ledger row per destructor, landed one commit at a time.

class Rva0055B0CC
{
public:
	virtual ~Rva0055B0CC();
};

class Rva00596B05 : public Rva0055B0CC
{
public:
	virtual ~Rva00596B05();
};

Rva00596B05::~Rva00596B05()
{
}

class Rva0059734B : public Rva0055B0CC
{
public:
	virtual ~Rva0059734B();
};

Rva0059734B::~Rva0059734B()
{
}

class Rva005DAAB6 : public Rva0055B0CC
{
public:
	virtual ~Rva005DAAB6();
};

Rva005DAAB6::~Rva005DAAB6()
{
}
