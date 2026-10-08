// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva0049B47C::~
// Rva0049B47C at 0x0049B47C (pinned opaque fold-point dtor: 25 destructors
// fold there including FX infos, Snapshot and ObjectModule; identity
// unproven). Each class below stores its own vtable and tail-calls the base
// destructor; the base itself is only declared here (defined nowhere -- it
// resolves via the pin), because a same-TU definition would capture the call
// locally instead of at the ledger address. Owner identities are unproven
// (opaque Rva names). One ledger row per destructor, landed one commit at
// a time.

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

class Rva000CEB6F : public Rva0049B47C
{
public:
	virtual ~Rva000CEB6F();
};

Rva000CEB6F::~Rva000CEB6F()
{
}

class Rva00254C4B : public Rva0049B47C
{
public:
	virtual ~Rva00254C4B();
};

Rva00254C4B::~Rva00254C4B()
{
}

class Rva00341E22 : public Rva0049B47C
{
public:
	virtual ~Rva00341E22();
};

Rva00341E22::~Rva00341E22()
{
}

class Rva00362EE3 : public Rva0049B47C
{
public:
	virtual ~Rva00362EE3();
};

Rva00362EE3::~Rva00362EE3()
{
}

class MiBase1
{
public:
	virtual void f1();
};

class Rva004607E1 : public Rva0049B47C, public MiBase1
{
public:
	virtual ~Rva004607E1();
};

Rva004607E1::~Rva004607E1()
{
}
