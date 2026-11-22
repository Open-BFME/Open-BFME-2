// cl: /MD
// Existing six native destructor rows keep their original identities and
// bodies. Adopt the shared four-vptr DockUpdate hierarchy instead of the
// one-slot secondary stand-ins. Native store offsets are0/+0C/+10/+20.
// SupplyWarehouseDockUpdate is already declared by this existing header.
#include "../GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdateNative.h"

class SupplyCenterDockUpdate : public DockUpdate
{
public:
    virtual ~SupplyCenterDockUpdate();
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
