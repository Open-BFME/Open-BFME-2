// cl: /MD
// Native warehouse table 00853790 slot 5 overrides the canonical
// Module::onObjectCreated contract. Body 004A7E43 uses module data +10,
// object +8 and boxes +88, then the existing drawable broadcast 0027164E.
#include "../GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdateNative.h"
#include "Thing/thing.h"

struct Rva002716Holder { void Rva0027164EBroadcast(int a, int b); };

void SupplyWarehouseDockUpdate::onObjectCreated()
{
    Rva002716Holder *holder =
        (Rva002716Holder *)((Thing *)m_object)->getDrawable();
    if (!holder)
        return;
    holder->Rva0027164EBroadcast(
        ((const SupplyWarehouseDockUpdateModuleData *)m_moduleData)->m_startingBoxesData,
        m_boxesStored);
}
