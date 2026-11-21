// cl: /MD /Ireference/shims/bfme2_ascii
//
// Special-power destructors that tail-call SpecialPowerModule's 0x00493DEF
// and restore the class's tables at +0, +0x0C and +0x10. The canonical
// SpecialPowerModule (SpecialPowerModuleClass.h) supplies the base: the
// BehaviorModule core, the +0x10 SpecialPowerModuleInterface and the slots
// rowed under SpecialPowerModule's name. No derived-class identity is
// asserted here.
#include "../../Include/GameLogic/Module/SpecialPowerModuleClass.h"
class Rva004C29BB : public SpecialPowerModule
{
public:
	virtual ~Rva004C29BB();
};
Rva004C29BB::~Rva004C29BB()
{
}

class Rva004C67A0 : public SpecialPowerModule
{
public:
	virtual ~Rva004C67A0();
};

Rva004C67A0::~Rva004C67A0()
{
}

class Rva004C8A16 : public SpecialPowerModule
{
public:
	virtual ~Rva004C8A16();
};

Rva004C8A16::~Rva004C8A16()
{
}

// CashHackSpecialPower.cpp's Rva004C2656_B2 placeholder still links through
// this directive (its +0x10 table's slot 0 is retail's 0x0049323D).
#pragma comment(linker, "/alternatename:?f2@Rva004C2656_B2@@UAEXXZ=?eq@Rva002687D0@@QBE_NH@Z")
