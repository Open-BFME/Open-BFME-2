// cl: /MD
//
// Create-module destructors tail-calling ~CreateModule at 0x004B8CDE: each stores
// its three tables (+0x00/+0x0C/+0x10) and jumps to the base. The +0x0C table is
// shared across the family (0xBEF9C0). Some owners are still unproven (Rva names).

class Thing;
class ModuleData;
class Xfer;
#include "../../Include/GameLogic/Module/CreateModuleClass.h"

class LockWeaponCreate : public CreateModule
{
public:
	virtual ~LockWeaponCreate();
};

LockWeaponCreate::~LockWeaponCreate()
{
}

class Rva004B8DB1 : public CreateModule
{
public:
	virtual ~Rva004B8DB1();
};

Rva004B8DB1::~Rva004B8DB1()
{
}

class Rva004B8EA8 : public CreateModule
{
public:
	virtual ~Rva004B8EA8();
};

Rva004B8EA8::~Rva004B8EA8()
{
}

class Rva004B8F92 : public CreateModule
{
public:
	virtual ~Rva004B8F92();
};

Rva004B8F92::~Rva004B8F92()
{
}

class Rva004B9287 : public CreateModule
{
public:
	virtual ~Rva004B9287();
};

Rva004B9287::~Rva004B9287()
{
}

class Rva004B9375 : public CreateModule
{
public:
	virtual ~Rva004B9375();
};

Rva004B9375::~Rva004B9375()
{
}

class InheritUpgradeCreate : public CreateModule
{
public:
	virtual ~InheritUpgradeCreate();
};

InheritUpgradeCreate::~InheritUpgradeCreate()
{
}
