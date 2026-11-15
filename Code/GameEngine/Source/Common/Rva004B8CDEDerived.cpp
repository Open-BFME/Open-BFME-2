// cl: /MD
//
// Create-module destructors tail-calling ~CreateModule at 0x004B8CDE: each stores
// its three tables (+0x00/+0x0C/+0x10) and jumps to the base. The +0x0C table is
// shared across the family (0xBEF9C0). Some owners are still unproven (Rva names).

class Thing;
class ModuleData;
class Xfer;
#include "../../Include/GameLogic/Module/CreateModuleClass.h"
#include "../../Include/GameLogic/Module/LockWeaponCreate.h"



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


// The class's own overrides, as InheritUpgradeCreate.cpp (the owner of every other
// row of the class) declares them, so both units emit the same two tables: retail's
// 0x008596E4 holds onCreate (the folded empty body 0x000B3FD0), onBuildComplete
// 0x004B96A9 and slot02 0x004B96C4; 0x008596F4 holds xfer 0x004B94E3 and
// getModuleNameKey 0x004B9471.
enum NameKeyType;
class InheritUpgradeCreate : public CreateModule
{
public:
	virtual ~InheritUpgradeCreate();
	virtual NameKeyType getModuleNameKey() const;
	virtual void onCreate() { }
	virtual void onBuildComplete();
	virtual void slot02();

protected:
	virtual void xfer(Xfer *xfer);
};

InheritUpgradeCreate::~InheritUpgradeCreate()
{
}
