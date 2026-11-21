// cl: /MD
//
// Destructors of three DockUpdate subclasses: each restores the four vptrs
// of its complete object (+0x00 primary, +0x0C BehaviorModuleInterface table
// 0x00851B20, +0x10 UpdateModuleInterface, +0x20 DockUpdateInterface) and
// tail-jumps to ~DockUpdate (0x0058A0F4). DockUpdate is the view
// SupplyWarehouseDockUpdate.cpp compiles against
// (SupplyWarehouseDockUpdateNative.h), as MonsterDockUpdateDtor.cpp does; each
// class here declares only its destructor. Rva004A11D4's identity is
// unproven. One ledger row per destructor.

#include "../GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdateNative.h"

// Overrides rowed in SupplyCenterDockUpdate.cpp, declared so its tables name
// them: getModuleNameKey (0x004A0E4C, primary slot 4), xfer (0x004A0E2C,
// slot 3) and update (0x004A1119, +0x10 slot 0).
class SupplyCenterDockUpdate : public DockUpdate
{
public:
	virtual ~SupplyCenterDockUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
protected:
	virtual void xfer(Xfer *);
};

SupplyCenterDockUpdate::~SupplyCenterDockUpdate()
{
}

class Rva004A11D4 : public DockUpdate
{
public:
	virtual ~Rva004A11D4();
};

Rva004A11D4::~Rva004A11D4()
{
}

SupplyWarehouseDockUpdate::~SupplyWarehouseDockUpdate()
{
}
