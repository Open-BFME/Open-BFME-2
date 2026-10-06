// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva005DCC24::~
// Rva005DCC24 at 0x005DCC24 (row in Rva004D759CDerived.cpp). Each class below
// stores its own vtable and tail-calls the base destructor; the base itself
// is only declared here (defined once in Rva004D759CDerived.cpp), because a
// same-TU definition would capture the call locally instead of at the ledger
// address. Owner identities are unproven (opaque Rva names). One ledger row
// per destructor, landed one commit at a time.

class Rva005DCC24
{
public:
	virtual ~Rva005DCC24();
};

class Rva005AAB91 : public Rva005DCC24
{
public:
	virtual ~Rva005AAB91();
};

Rva005AAB91::~Rva005AAB91()
{
}

class Rva005AB125 : public Rva005DCC24
{
public:
	virtual ~Rva005AB125();
};

Rva005AB125::~Rva005AB125()
{
}

class Rva005AB309 : public Rva005DCC24
{
public:
	virtual ~Rva005AB309();
};

Rva005AB309::~Rva005AB309()
{
}

class Rva005AC7E1 : public Rva005DCC24
{
public:
	virtual ~Rva005AC7E1();
};

Rva005AC7E1::~Rva005AC7E1()
{
}

class Rva005ACCE4 : public Rva005DCC24
{
public:
	virtual ~Rva005ACCE4();
};

Rva005ACCE4::~Rva005ACCE4()
{
}
