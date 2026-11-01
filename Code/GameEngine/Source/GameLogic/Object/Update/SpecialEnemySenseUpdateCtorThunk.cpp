// cl: /DNDEBUG /MD /EHsc
// The named ModuleFactory entry reaches this constructor through its unique
// 0x20-byte allocation, leaving no derived state beyond UpdateModule.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class SESU_DeepBase
{
public:
    SESU_DeepBase(Thing *, const ModuleData *);
    virtual ~SESU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class SESU_Iface1 { public: virtual void slot(); };
class SESU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class SpecialEnemySenseUpdate : public UpdateModule
{
public:
    SpecialEnemySenseUpdate(Thing *, const ModuleData *);
};

// ??0SpecialEnemySenseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SpecialEnemySenseUpdate::SpecialEnemySenseUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot@SESU_Iface1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot@SESU_Iface2@@UAEXXZ=?update@SpecialEnemySenseUpdate@@UAE?AW4UpdateSleepTime@@XZ")
