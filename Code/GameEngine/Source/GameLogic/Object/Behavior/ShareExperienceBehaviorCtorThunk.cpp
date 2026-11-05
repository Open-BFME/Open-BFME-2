// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
    UPDATE_SLEEP_DUMMY
};

class ShareExperienceBehaviorIface1
{
public:
    virtual void slot();
};

class ShareExperienceBehaviorIface2
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class ShareExperienceBehaviorInterface
{
public:
    virtual void slot();
};

class ShareExperienceBehavior : public UpdateModule,
    public ShareExperienceBehaviorInterface
{
public:
    ShareExperienceBehavior(Thing *, const ModuleData *);
public:
	// retail slot 4: the rowed ?getModuleNameKey@ShareExperienceBehavior@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
public:
	// retail vftable slot: the rowed override
	virtual UpdateSleepTime update();
};

// ??0ShareExperienceBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
ShareExperienceBehavior::ShareExperienceBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    setWakeFrame(getObject(), (UpdateSleepTime)0x3fffffff);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot@ShareExperienceBehaviorIface1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot@ShareExperienceBehaviorIface2@@UAEXXZ=?update@ShareExperienceBehavior@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?slot@ShareExperienceBehaviorInterface@@UAEXXZ=?rva00480093@ShareExperienceBehavior@@UAEXM@Z")
