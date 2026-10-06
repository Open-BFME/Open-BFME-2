// cl: /O1 /MD
#include "../../Include/Common/Rva00041004Lock.h"
//
// Opaque single-inheritance destructors tail-calling SEH bases pinned
// elsewhere. Each class below stores its own vtable and tail-calls its base
// destructor; every base is only declared here (defined nowhere -- it
// resolves via its pin), because a same-TU definition would capture the call
// locally instead of at the ledger address. Vtable values are DIR32
// auto-patches. Owner identities are unproven (opaque Rva names). One ledger
// row per destructor, landed one commit at a time.

class Rva0098477
{
public:
	Rva0098477();
	virtual ~Rva0098477();
};

class Rva00984EF : public Rva0098477
{
public:
	Rva00984EF();
	virtual ~Rva00984EF();

private:
	unsigned char m_pad04[0xC];
	int m_10;
	int m_14;
	int m_18;
};

Rva00984EF::Rva00984EF()
{
	m_10 = 0;
	m_14 = 0;
	m_18 = 0xFF;
}

Rva00984EF::~Rva00984EF()
{
}

inline Rva00514E6B::~Rva00514E6B()
{
}

class Rva002D0588
{
public:
	virtual ~Rva002D0588();
};

class Rva004CA13 : public Rva002D0588
{
public:
	virtual ~Rva004CA13();
};

inline Rva004CA13::~Rva004CA13()
{
}

class Rva00224A90
{
public:
	virtual ~Rva00224A90();
};

class Rva00628FD : public Rva00224A90
{
public:
	virtual ~Rva00628FD();
};

inline Rva00628FD::~Rva00628FD()
{
}

class Rva002C5398
{
public:
	virtual ~Rva002C5398();
};

class Rva008FCA3 : public Rva002C5398
{
public:
	virtual ~Rva008FCA3();
};

inline Rva008FCA3::~Rva008FCA3()
{
}

class Rva0023AE08
{
public:
	Rva0023AE08();
	virtual ~Rva0023AE08();

private:
	char m_pad04[8];
};

class __declspec(novtable) MiBase1_4C743
{
public:
	virtual void f1();
};

class Rva004C743 : public Rva0023AE08, public MiBase1_4C743
{
public:
	Rva004C743();
	virtual ~Rva004C743();
};

// ??0Rva004C743@@QAE@XZ @0x0004C43E (25B): derived ctor beside the rowed
// 2-vptr dtor; pinned primary-base ctor then both vptrs (compiler-emitted).
inline Rva004C743::Rva004C743() : Rva0023AE08()
{
}

inline Rva004C743::~Rva004C743()
{
}

class Rva0028418A
{
public:
	virtual ~Rva0028418A();
};

class MiBase1_62AF7
{
public:
	virtual void f1();

private:
	char m_pad04[8];
};

class MiBase2_62AF7
{
public:
	virtual void f2();
};

class MiBase3_62AF7
{
public:
	virtual void f3();
};

class Rva0062AF7 : public Rva0028418A, public MiBase1_62AF7, public MiBase2_62AF7, public MiBase3_62AF7
{
public:
	virtual ~Rva0062AF7();
};

inline Rva0062AF7::~Rva0062AF7()
{
}

class Rva00605CA7
{
public:
	virtual ~Rva00605CA7();
};

class Rva00605C6A : public Rva00605CA7
{
public:
	virtual ~Rva00605C6A();
};

Rva00605C6A::~Rva00605C6A()
{
}

class Rva003B00D6
{
public:
	virtual ~Rva003B00D6();
};

class Rva003B0152 : public Rva003B00D6
{
public:
	virtual ~Rva003B0152();
};

Rva003B0152::~Rva003B0152()
{
}

class Rva003B0344
{
public:
	virtual ~Rva003B0344();
};

class Rva003B0401 : public Rva003B0344
{
public:
	virtual ~Rva003B0401();
};

Rva003B0401::~Rva003B0401()
{
}

class Rva003FCE38
{
public:
	virtual ~Rva003FCE38();
};

class Rva005C4B1B : public Rva003FCE38
{
public:
	virtual ~Rva005C4B1B();
};

Rva005C4B1B::~Rva005C4B1B()
{
}

class Rva001E3624
{
public:
	virtual ~Rva001E3624();
};

class Rva003FA776 : public Rva001E3624
{
public:
	virtual ~Rva003FA776();
};

Rva003FA776::~Rva003FA776()
{
}

class Rva0061ED80
{
public:
	virtual ~Rva0061ED80();
};

class Rva00180EA0 : public Rva0061ED80
{
public:
	virtual ~Rva00180EA0();
};

Rva00180EA0::~Rva00180EA0()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f3@MiBase3_62AF7@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:?f2@MiBase2_62AF7@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")

// These six destructors are header inlines in copier units; the anchor retains
// this unit's matched row bodies, but the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeOpaqueSingleInheritanceDtorInlineAnchor@@YAXPAX@Z absent-from-retail
void _bfmeOpaqueSingleInheritanceDtorInlineAnchor(void *storage)
{
	Rva004C743 *rva004C743 = (Rva004C743 *)storage;
	rva004C743->Rva004C743::Rva004C743();
	Rva004CA13 *rva004CA13 = (Rva004CA13 *)storage;
	rva004CA13->Rva004CA13::~Rva004CA13();
	Rva00514E6B *rva00514E6B = (Rva00514E6B *)storage;
	rva00514E6B->Rva00514E6B::~Rva00514E6B();
	Rva00628FD *rva00628FD = (Rva00628FD *)storage;
	rva00628FD->Rva00628FD::~Rva00628FD();
	Rva0062AF7 *rva0062AF7 = (Rva0062AF7 *)storage;
	rva0062AF7->Rva0062AF7::~Rva0062AF7();
	Rva008FCA3 *rva008FCA3 = (Rva008FCA3 *)storage;
	rva008FCA3->Rva008FCA3::~Rva008FCA3();
}
#pragma inline_depth()
