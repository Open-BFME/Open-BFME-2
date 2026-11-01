// cl: /DNDEBUG /MD /EHsc
// Retail 004A7DA5 is primary slot 4 of the warehouse module table
// 00853790. Module.h and Object::findModule establish getModuleNameKey's
// virtual const signature; its cached literal identifies this module.
// The earlier static placeholder represented the body but lost that slot.
#include "../../../../Include/Common/NameKeyGenerator.h"
#include "DockUpdate/SupplyWarehouseDockUpdateNative.h"

NameKeyType SupplyWarehouseDockUpdate::getModuleNameKey() const
{
    static NameKeyType TheSupplyWarehouseDockUpdatePoolKey =
        TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
    return TheSupplyWarehouseDockUpdatePoolKey;
}
