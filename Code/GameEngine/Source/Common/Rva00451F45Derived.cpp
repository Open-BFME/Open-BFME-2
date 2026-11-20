// cl: /O1 /MD
//
// Destructors of six SpecialAbilityUpdate modules, each storing its four
// vftables at +0x00, +0x0C, +0x10 and +0x20 and tail-jumping to
// SpecialAbilityUpdate::~SpecialAbilityUpdate at 0x00451F45.
//
// Target facts: 0x00451F45 is rowed as ??1SpecialAbilityUpdate (its deleting
// destructor 0x004522F0 calls it); its four vptrs are UpdateModule's three
// (+0x00, +0x0C, +0x10) and SpecialPowerUpdateInterface's (+0x20), the shape
// of the canonical SpecialAbilityUpdate.h. So each class derives from that
// class. The constructor units that store these tables by name
// (Rva00492C59Ctor.cpp, ScaleWallSpecialAbilityUpdate.cpp,
// GiveUpgradeUpdateCtor.cpp, ToggleHiddenSpecialAbilityUpdateCtor.cpp,
// WoundArrowUpdateCtor.cpp, FellBeastSwoopPowerCtor.cpp) name the tables this
// view emits. Owner identities of the address-named classes stay unproven, so
// no override is declared under their names.

#include "../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class Rva00492C90 : public SpecialAbilityUpdate
{
public:
	virtual ~Rva00492C90();
};

Rva00492C90::~Rva00492C90()
{
}

class Rva00494E01 : public SpecialAbilityUpdate
{
public:
	virtual ~Rva00494E01();
};

Rva00494E01::~Rva00494E01()
{
}

class Rva0049C3FC : public SpecialAbilityUpdate
{
public:
	virtual ~Rva0049C3FC();
};

Rva0049C3FC::~Rva0049C3FC()
{
}

class Rva004AE1AC : public SpecialAbilityUpdate
{
public:
	virtual ~Rva004AE1AC();
};

Rva004AE1AC::~Rva004AE1AC()
{
}

class Rva004C6943 : public SpecialAbilityUpdate
{
public:
	virtual ~Rva004C6943();
};

Rva004C6943::~Rva004C6943()
{
}

class Rva004C6C5C : public SpecialAbilityUpdate
{
public:
	virtual ~Rva004C6C5C();
};

Rva004C6C5C::~Rva004C6C5C()
{
}
