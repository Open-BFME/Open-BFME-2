// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva005DC73C::~
// Rva005DC73C at 0x005DC73C (pinned opaque base dtor; identity unproven).
// Each class below stores its own vtable and tail-calls the base destructor;
// the base itself is only declared here (defined nowhere -- it resolves via
// the pin), because a same-TU definition would capture the call locally
// instead of at the ledger address. Owner identities are unproven (opaque
// Rva names). One ledger row per destructor, landed one commit at a time.

class Rva005DC73C
{
public:
	virtual ~Rva005DC73C();
};

class Rva005A990B : public Rva005DC73C
{
public:
	virtual ~Rva005A990B();
};

Rva005A990B::~Rva005A990B()
{
}

class Rva005AA647 : public Rva005DC73C
{
public:
	virtual ~Rva005AA647();
};

Rva005AA647::~Rva005AA647()
{
}

class Rva005DC87B : public Rva005DC73C
{
public:
	virtual ~Rva005DC87B();
};

Rva005DC87B::~Rva005DC87B()
{
}
