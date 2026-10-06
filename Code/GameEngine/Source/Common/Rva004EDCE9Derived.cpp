// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva004EDCE9::~
// Rva004EDCE9 at 0x004EDCE9 (pinned opaque SEH base dtor; identity
// unproven). Each class below stores its own vtable and tail-calls the base
// destructor; the base itself is only declared here (defined nowhere -- it
// resolves via the pin), because a same-TU definition would capture the call
// locally instead of at the ledger address. Owner identities are unproven
// (opaque Rva names). One ledger row per destructor, landed one commit at
// a time.

class Rva004EDCE9
{
public:
	virtual ~Rva004EDCE9();
};

class Rva005DC73C : public Rva004EDCE9
{
public:
	virtual ~Rva005DC73C();
};

Rva005DC73C::~Rva005DC73C()
{
}

class Rva005DCB27 : public Rva004EDCE9
{
public:
	virtual ~Rva005DCB27();
};

Rva005DCB27::~Rva005DCB27()
{
}

class Rva005DCBE3 : public Rva004EDCE9
{
public:
	virtual ~Rva005DCBE3();
};

Rva005DCBE3::~Rva005DCBE3()
{
}

class Rva005DCC24 : public Rva004EDCE9
{
public:
	virtual ~Rva005DCC24();
};

Rva005DCC24::~Rva005DCC24()
{
}
