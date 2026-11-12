// cl: /MD /Ireference/shims/bfme2_ascii
//
// Opaque special-power destructors tail-call native 0x00493DEF and restore
// tables at +0, +0x0C and +0x10. The canonical BehaviorModule supplies the
// twelve-byte ObjectModule core and the four-byte +0x0C interface, including
// its zero-return defaults. The +0x10 interface remains an incomplete view.
// No complete SpecialPowerModule or derived-class identity is asserted here.

#include "../../Include/GameLogic/Module/BehaviorModule.h"

class Rva00493DEF : public BehaviorModule
{
public:
	virtual ~Rva00493DEF();

};





class Rva004C29BB_B2
{
public:
	virtual void f2();
};

class Rva004C29BB : public Rva00493DEF, public Rva004C29BB_B2
{
public:
	virtual ~Rva004C29BB();
};

Rva004C29BB::~Rva004C29BB()
{
}



















class Rva004C67A0_B2
{
public:
	virtual void f2();
};

class Rva004C67A0 : public Rva00493DEF, public Rva004C67A0_B2
{
public:
	virtual ~Rva004C67A0();
};

Rva004C67A0::~Rva004C67A0()
{
}















class Rva004C8A16_B2
{
public:
	virtual void f2();
};

class Rva004C8A16 : public Rva00493DEF, public Rva004C8A16_B2
{
public:
	virtual ~Rva004C8A16();
};

Rva004C8A16::~Rva004C8A16()
{
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?f2@Rva004C2656_B2@@UAEXXZ=?eq@Rva002687D0@@QBE_NH@Z")
#pragma comment(linker, "/alternatename:?f2@Rva004C29BB_B2@@UAEXXZ=?eq@Rva002687D0@@QBE_NH@Z")
#pragma comment(linker, "/alternatename:?f2@Rva004C67A0_B2@@UAEXXZ=?eq@Rva002687D0@@QBE_NH@Z")
#pragma comment(linker, "/alternatename:?f2@Rva004C8A16_B2@@UAEXXZ=?eq@Rva002687D0@@QBE_NH@Z")
