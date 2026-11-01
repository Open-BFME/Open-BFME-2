// cl: /MD
// Native 004A7FC5 (43B) and 004A7F78 (77B) use object +8,
// module-data +4/starting-boxes +10 and boxes +88.
#include <math.h>
#include "../GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdateNative.h"
#include "Thing/thing.h"

class Rva002716Holder
{
public:
    void Rva0027164EBroadcast(int a, int b);
};

class GlobalData
{
public:
    unsigned char m_pad00[0xA5C];
    int m_valuePerSupplyBox;
};
extern GlobalData *TheWritableGlobalData;

void SupplyWarehouseDockUpdate::loadPostProcess()
{
    DockUpdate::loadPostProcess();
    Thing *thing = (Thing *)m_object;
    const SupplyWarehouseDockUpdateModuleData *aux =
        (const SupplyWarehouseDockUpdateModuleData *)m_moduleData;
    Drawable *drawable = thing->getDrawable();
    if (drawable == 0)
        return;
    ((Rva002716Holder *)drawable)->Rva0027164EBroadcast(aux->m_startingBoxesData, m_boxesStored);
}

void SupplyWarehouseDockUpdate::rva004A7F78(int val)
{
    m_boxesStored = (int)ceil((double)val / TheWritableGlobalData->m_valuePerSupplyBox);
    Drawable *drawable = ((Thing *)m_object)->getDrawable();
    if (drawable == 0)
        return;
    ((Rva002716Holder *)drawable)->Rva0027164EBroadcast(
        ((const SupplyWarehouseDockUpdateModuleData *)m_moduleData)->m_startingBoxesData,
        m_boxesStored);
}
