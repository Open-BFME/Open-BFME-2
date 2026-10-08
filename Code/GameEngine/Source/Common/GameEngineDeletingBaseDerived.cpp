// cl: /O1 /MD /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
//
// Opaque derived destructors that tail-call the verified SubsystemInterface
// destructor at 0x001B4E74. Its vtable and name member at +0x08 establish
// the base identity; derived owner names remain unknown. Use the existing
// native header, including its full base layout and virtual interface.

typedef bool Bool;
#include "subsystem_interface.h"

class Rva00221027 : public SubsystemInterface
{
public:
	virtual ~Rva00221027();
};

Rva00221027::~Rva00221027()
{
}

class Rva00225ACA : public SubsystemInterface
{
public:
	virtual ~Rva00225ACA();
};

Rva00225ACA::~Rva00225ACA()
{
}

class Rva0025DB46 : public SubsystemInterface
{
public:
	virtual ~Rva0025DB46();
};

Rva0025DB46::~Rva0025DB46()
{
}

class Rva0026201C : public SubsystemInterface
{
public:
	virtual ~Rva0026201C();
};

Rva0026201C::~Rva0026201C()
{
}

class Rva002D22CA : public SubsystemInterface
{
public:
	virtual ~Rva002D22CA();
};

Rva002D22CA::~Rva002D22CA()
{
}

class Rva002E55D8 : public SubsystemInterface
{
public:
	virtual ~Rva002E55D8();
};

Rva002E55D8::~Rva002E55D8()
{
}

class Rva003BA6A9 : public SubsystemInterface
{
public:
	virtual ~Rva003BA6A9();
};

Rva003BA6A9::~Rva003BA6A9()
{
}

class Rva003E3BD4 : public SubsystemInterface
{
public:
	virtual ~Rva003E3BD4();
};

Rva003E3BD4::~Rva003E3BD4()
{
}

class Rva00419CD4 : public SubsystemInterface
{
public:
	virtual ~Rva00419CD4();
};

Rva00419CD4::~Rva00419CD4()
{
}

class Rva0041B8C7 : public SubsystemInterface
{
public:
	virtual ~Rva0041B8C7();
};

Rva0041B8C7::~Rva0041B8C7()
{
}

class Rva0041FE0E : public SubsystemInterface
{
public:
	virtual ~Rva0041FE0E();
};

inline Rva0041FE0E::~Rva0041FE0E()
{
}

class Rva0044954D : public SubsystemInterface
{
public:
	virtual ~Rva0044954D();
};

Rva0044954D::~Rva0044954D()
{
}

// ??1Rva0041FE0E is a header inline elsewhere: other units emit select-any
// copies of it, so a strong definition here was a duplicate symbol in the
// linked build. This anchor only makes this unit emit its copy for the ledger
// row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRva0041FE0EDtor@@YAXPAVRva0041FE0E@@@Z present-unmatched
void bfmeEmitRva0041FE0EDtor(Rva0041FE0E *p)
{
	p->Rva0041FE0E::~Rva0041FE0E();
}
#pragma inline_depth()
