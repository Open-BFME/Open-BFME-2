// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva005D9DC1::~
// Rva005D9DC1 at 0x005D9DC1 (row in Rva004D759CDerived.cpp). Each class below
// stores its own vtable and tail-calls the base destructor; the base itself
// is only declared here (defined once in Rva004D759CDerived.cpp), because a
// same-TU definition would capture the call locally instead of at the ledger
// address. Owner identities are unproven (opaque Rva names). One ledger row
// per destructor, landed one commit at a time.

class Rva005D9DC1
{
public:
	virtual ~Rva005D9DC1();
};

class Rva005D99BD : public Rva005D9DC1
{
public:
	virtual ~Rva005D99BD();
};

Rva005D99BD::~Rva005D99BD()
{
}

class Rva005D9D5A : public Rva005D9DC1
{
public:
	virtual ~Rva005D9D5A();
};

Rva005D9D5A::~Rva005D9D5A()
{
}
