// cl: /MD
//
// Opaque destructor chain tail-calling through Rva0058AD7A at 0x0058AD7A
// (pinned opaque empty base dtor: vtable store plus ret). Rva005EE30C is a
// single-inheritance derived destructor (vtable store, tail jump, no member
// of its own); the 22 bodies after it derive from it in turn, same shape.
// Owner identities are unproven (opaque Rva names). One ledger row per
// destructor, landed one commit at a time.

class Rva0058AD7A
{
public:
	virtual ~Rva0058AD7A();
};

class Rva005EE30C : public Rva0058AD7A
{
public:
	virtual ~Rva005EE30C();
};

Rva005EE30C::~Rva005EE30C()
{
}

class Rva005EE2A0 : public Rva0058AD7A
{
public:
	virtual ~Rva005EE2A0();
};

Rva005EE2A0::~Rva005EE2A0()
{
}

class Rva005EEDAA : public Rva0058AD7A
{
public:
	virtual ~Rva005EEDAA();
};

Rva005EEDAA::~Rva005EEDAA()
{
}

class Rva005EEE33 : public Rva0058AD7A
{
public:
	virtual ~Rva005EEE33();
};

Rva005EEE33::~Rva005EEE33()
{
}
