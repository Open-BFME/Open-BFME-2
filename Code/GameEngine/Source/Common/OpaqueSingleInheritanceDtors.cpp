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

class W3DThingFactory : public Rva002D0588
{
public:
	virtual ~W3DThingFactory();
};

inline W3DThingFactory::~W3DThingFactory()
{
}

// The base is AptPlayer (its rowed constructor 0x00224E10 and destructor
// 0x00224A90); Rva00628FD is the Win32GameEngine slot-37 factory's 0x32C
// product (Win32GameEngineFactories.cpp), which adds only its own table.
class AptPlayer
{
public:
	AptPlayer();
	virtual ~AptPlayer();
private:
	char m_unmodelled_04[0x32C - 0x04];
};

class Rva00628FD : public AptPlayer
{
public:
	Rva00628FD();
	virtual ~Rva00628FD();
};

// ??0Rva00628FD@@QAE@XZ, retail 0x000628EB (18 bytes): the base constructor,
// then the 0x00BC57E0 table.
Rva00628FD::Rva00628FD()
{
}

inline Rva00628FD::~Rva00628FD()
{
}

class Rva002C5398
{
public:
	Rva002C5398();
	virtual ~Rva002C5398();
};

class Rva008FCA3 : public Rva002C5398
{
public:
	Rva008FCA3();
	virtual ~Rva008FCA3();
};

inline Rva008FCA3::~Rva008FCA3()
{
}

// ??0Rva008FCA3@@QAE@XZ retail 0x0008FC51 18B: base ctor 0x002C5334 then own
// vptr BC7C90; built by game client vtable 0x00BC4738 factory 0x0004C4C7 (new 0x40).
Rva008FCA3::Rva008FCA3()
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

class W3DTerrainLogic : public Rva0028418A, public MiBase1_62AF7, public MiBase2_62AF7, public MiBase3_62AF7
{
public:
	virtual ~W3DTerrainLogic();
};

inline W3DTerrainLogic::~W3DTerrainLogic()
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
	// Pure in every copy of the 0x003B00D6 family's vtables (Rva003BCtors0083.cpp).
	virtual void bfmeVtSlot1() = 0;
	virtual void bfmeVtSlot2() = 0;
	virtual void bfmeVtSlot3() = 0;
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

#include "../../Include/Common/Overridable.h"

class Rva003FA776 : public Overridable
{
public:
	virtual ~Rva003FA776();
};

Rva003FA776::~Rva003FA776()
{
}

// Rva00180EA0::~Rva00180EA0 (0x00180EA0) moved to WWLib/FamilyDeletingDtorsO2.cpp
// beside its /O2 deleting dtor.

class Rva000A8903AudioDevice;
class Rva0073EE55
{
public:
	virtual ~Rva0073EE55();
};
class Rva000A8856
{
public:
	void rva000A8856(Rva000A8903AudioDevice *device);
private:
	void *object;
};
#include <new>

void Rva000A8856::rva000A8856(Rva000A8903AudioDevice *device)
{
	void *old = object;
	if (device == old)
		return;
	object = device;
	if (old) {
		((Rva0073EE55 *)old)->Rva0073EE55::~Rva0073EE55();
		::operator delete(old);
	}
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
	W3DThingFactory *rva004CA13 = (W3DThingFactory *)storage;
	rva004CA13->W3DThingFactory::~W3DThingFactory();
	Rva00514E6B *rva00514E6B = (Rva00514E6B *)storage;
	rva00514E6B->Rva00514E6B::~Rva00514E6B();
	Rva00628FD *rva00628FD = (Rva00628FD *)storage;
	rva00628FD->Rva00628FD::~Rva00628FD();
	W3DTerrainLogic *rva0062AF7 = (W3DTerrainLogic *)storage;
	rva0062AF7->W3DTerrainLogic::~W3DTerrainLogic();
	Rva008FCA3 *rva008FCA3 = (Rva008FCA3 *)storage;
	rva008FCA3->Rva008FCA3::~Rva008FCA3();
}
#pragma inline_depth()

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:??0Rva0023AE08@@QAE@XZ=??0GameClient@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva0023AE08@@UAE@XZ=??1GameClient@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva0028418A@@UAE@XZ=??1TerrainLogic@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva002D0588@@UAE@XZ=??1ThingFactory@@UAE@XZ")
#pragma comment(linker, "/alternatename:?f1@MiBase1_4C743@@UAEXXZ=??_ERva004C743@@WM@AEPAXI@Z")
#pragma comment(linker, "/alternatename:?f1@MiBase1_62AF7@@UAEXXZ=??_EW3DTerrainLogic@@W3AEPAXI@Z")
