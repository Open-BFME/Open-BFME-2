// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling Rva0056AC26::~
// Rva0056AC26 at 0x0056AC26 (pinned opaque MI base dtor: SEH, vptrs at
// +0x00/+0x08; identity unproven). Each class below derives from the
// canonical Rva0056AC26 (registered Rva0007DF07 at +0, registered
// Rva0056AC26Base2 at +8), so the compiler emits both vptrs and the
// tail-call to the base destructor. Owner identities are unproven (opaque
// Rva names). Non-default secondary slots come from each retail destructor's
// installed tables (reverse/attempt_support/registry-acff-slot-contract.md).

#include "../../Include/Common/Rva0056AC26.h"

class Rva0056AC82 : public Rva0056AC26
{
public:
	virtual ~Rva0056AC82();
	virtual bool ac26Slot1() { return true; } // 0x0086D0A8 slot 1: 0x0050B5C6
};

Rva0056AC82::~Rva0056AC82()
{
}

class Rva0056ACC5 : public Rva0056AC26
{
public:
	virtual ~Rva0056ACC5();
	virtual bool ac26Slot1();
	virtual void rva0056AB35(int id);
	virtual bool slot12(int);
};

Rva0056ACC5::~Rva0056ACC5()
{
}

class Rva0056ACDF : public Rva0056AC26
{
public:
	virtual ~Rva0056ACDF();
	virtual bool ac26Slot1();
	virtual int slot14(int);
};

Rva0056ACDF::~Rva0056ACDF()
{
}

class Rva0056ACFF : public Rva0056AC26
{
public:
	virtual ~Rva0056ACFF();
	virtual bool ac26Slot1();
	virtual bool slot1(Rva002B4BC9Arg *arg);	// Base2-view slot 1
	virtual bool slot4(LivingWorldArmy *army, Rva00318C32Ret *target);
};

Rva0056ACFF::~Rva0056ACFF()
{
}

class Rva0056AE4A : public Rva0056AC26
{
public:
	virtual ~Rva0056AE4A();
	virtual bool ac26Slot1();
};

Rva0056AE4A::~Rva0056AE4A()
{
}

// Slot 1 of each of Rva0056ACFF's two tables forwards to a rowed query on
// the living-world logic singleton (ecx = TheLivingWorldLogic, then a tail
// jump): 0x0056ABC0 in the Rva0007DF07 table (0x0086D19C) to 0x002B32CE,
// 0x0056ABCB in the Rva0056AC26Base2 table (0x0086D160) to 0x002B4BC9 with
// its one argument. The Base2-view member spells the contract's slot1:
// spelled b1Slot1 the compiler saw no override of Base2::slot1 and appended
// it as a new virtual at primary slot 5 (a 24-byte primary table against
// retail's 20) while slot 1 of 0x0086D160 kept the Base2 fold.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva002B32CE
{
public:
	bool rva002B32CE();
};

class Rva002B4BC9
{
public:
	bool rva002B4BC9(Rva002B4BC9Arg *arg);
};

bool Rva0056ACFF::ac26Slot1()
{
	return ((Rva002B32CE *)TheLivingWorldLogic)->rva002B32CE();
}

bool Rva0056ACFF::slot1(Rva002B4BC9Arg *arg)
{
	return ((Rva002B4BC9 *)TheLivingWorldLogic)->rva002B4BC9(arg);
}
