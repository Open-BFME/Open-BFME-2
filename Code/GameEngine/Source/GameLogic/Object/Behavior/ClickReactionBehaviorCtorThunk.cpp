// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
    UPDATE_SLEEP_NONE = 1
};

class PB_Iface1
{
public:
    virtual void slot();
};

class PB_Iface2
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class ClickReactionBehaviorIface
{
public:
    virtual void slot();
};

class ClickReactionBehavior : public UpdateModule,
    public ClickReactionBehaviorIface
{
public:
    ClickReactionBehavior(Thing *, const ModuleData *);

private:
    int m_clicks; // +0x24, shared reaction/xfer view
    int m_cooldown; // +0x28, shared reaction/xfer view
public:
	// retail slot 4: the rowed ?getModuleNameKey@ClickReactionBehavior@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

// ??0ClickReactionBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
ClickReactionBehavior::ClickReactionBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_clicks(0), m_cooldown(0)
{
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot@ClickReactionBehaviorIface@@UAEXXZ=?get@Rva004543A9LeaNegSbbField@@WBE@BEHXZ")
#pragma comment(linker, "/alternatename:?slot@PB_Iface1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot@PB_Iface2@@UAEXXZ=?update@Rva0045969F@@UAEHXZ")
