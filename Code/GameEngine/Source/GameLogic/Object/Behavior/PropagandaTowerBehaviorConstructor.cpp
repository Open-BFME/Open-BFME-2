// cl: /DNDEBUG /MD /EHsc
// readable body of ??0PropagandaTowerBehavior@@: Code/GameEngine/Source/GameLogic/Object/Behavior/PropagandaTowerBehavior.cpp

// The retail BFME UpdateModule prefix has three interface vptrs before the
// PropagandaTowerBehavior interface.  Keep that verified view local to this
// constructor; the shared ZH declaration has a different base layout.
class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
    UPDATE_SLEEP_NONE = 1
};

class PB_Iface1 { public: virtual void slot(); };
class PB_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class PropagandaTowerBehaviorIface
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PropagandaTowerBehavior.h
class PropagandaTowerBehavior : public UpdateModule,
    public PropagandaTowerBehaviorIface
{
public:
    PropagandaTowerBehavior(Thing *, const ModuleData *);

private:
    unsigned int m_lastScanFrame;
    void *m_insideList;
    const void *m_upgradeRequired;
public:
	// retail slot 4: the rowed ?getModuleNameKey@PropagandaTowerBehavior@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
public:
	// retail vftable slot: the rowed override
	virtual UpdateSleepTime update();
};

// ??0PropagandaTowerBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
PropagandaTowerBehavior::PropagandaTowerBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData),
      m_lastScanFrame(0),
      m_insideList(0),
      m_upgradeRequired(0)
{
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot@PB_Iface1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot@PB_Iface2@@UAEXXZ=?update@PropagandaTowerBehavior@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?slot@PropagandaTowerBehaviorIface@@UAEXXZ=?rva00481837@Rva00481837@@UAEXH@Z")
