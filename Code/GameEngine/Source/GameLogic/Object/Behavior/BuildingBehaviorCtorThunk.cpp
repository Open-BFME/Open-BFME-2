// cl: /DNDEBUG /MD /EHsc
// The named ModuleFactory entry reaches this constructor through its unique
// 0x24-byte allocation, fixing the two bytes of derived state.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class BB_Iface1 { public: virtual void slot(); };
class BB_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class BuildingBehavior : public UpdateModule
{
public:
    BuildingBehavior(Thing *, const ModuleData *);

private:
    bool m_field20;
    bool m_field21;
};

// ??0BuildingBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
BuildingBehavior::BuildingBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_field20 = false;
    m_field21 = true;
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot@BB_Iface1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot@BB_Iface2@@UAEXXZ=?update@BuildingBehavior@@UAE?AW4UpdateSleepTime@@XZ")
