// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva005EEDAA::~
// Rva005EEDAA at 0x005EEDAA (row in Rva005EE30CChain.cpp). Each class below
// stores its own vtable and tail-calls the base destructor; the base itself
// is only declared here (defined once in Rva005EE30CChain.cpp), because a
// same-TU definition would capture the call locally instead of at the ledger
// address. Owner identities are unproven (opaque Rva names). One ledger row
// per destructor, landed one commit at a time.

#include "../../Include/Common/Rva0058AD7A.h"

class Rva005EEDAA : public Rva0058AD7A
{
public:
	Rva005EEDAA();
	virtual ~Rva005EEDAA();
private:
	int m_1C; // Native base ctor005EED92 initializes this member after Rva0058AD7A(3).
};

class Rva005D8723 : public Rva005EEDAA
{
public:
	Rva005D8723();
	virtual ~Rva005D8723();
};

Rva005D8723::Rva005D8723()
{
}

Rva005D8723::~Rva005D8723()
{
}

class Rva005D9DC1 : public Rva005EEDAA
{
public:
	virtual ~Rva005D9DC1();
};

Rva005D9DC1::~Rva005D9DC1()
{
}

class Rva005DA0E2 : public Rva005EEDAA
{
public:
	Rva005DA0E2();
	virtual ~Rva005DA0E2();
};

// ??0Rva005DA0E2@@QAE@XZ @0x005DA0D0 18B: default ctor calls base 0x005EED92 then stores vtable 0x008764BC.
// Evidence: call to rowed base ctor plus vtable store; sits immediately before its dtor 0x005DA0E2; caller 0x0058A707.
Rva005DA0E2::Rva005DA0E2()
{
}

Rva005DA0E2::~Rva005DA0E2()
{
}
