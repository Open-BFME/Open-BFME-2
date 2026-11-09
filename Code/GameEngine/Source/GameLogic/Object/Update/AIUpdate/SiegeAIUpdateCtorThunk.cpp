// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SiegeAIUpdate module ctor.
// Out-of-line base MI, then five most-derived vtbls at
// +0/+0xC/+0x10/+0x20/+0x24.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../../Include/GameLogic/Module/BehaviorModule.h"
// The +0x10 update interface and the +0x14..+0x1F fields are UpdateModule's.
#include "../../../../../Include/GameLogic/Module/UpdateModule.h"


class SiegeAIUpdateIface3
{
public:
	virtual void siegeAIUpdateIface3Anchor();
};

class SiegeAIUpdateIface4
{
public:
	virtual void siegeAIUpdateIface4Anchor();
};

class AIUpdateInterface : public UpdateModule, public SiegeAIUpdateIface3, public SiegeAIUpdateIface4
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
	// BehaviorModuleInterface slots 1 and 19 (retail VA 0x00BFA3C0): AIUpdateInterface's
	// overrides, rowed at 0x003730FC and 0x004FA5F4 (header-inline in AIUpdate.h;
	// SupplyTruckAIUpdateCtor.cpp).
	virtual CollideModuleInterface *getCollide();
	virtual AIUpdateInterface *getAIUpdateInterface();
	// UpdateModuleInterface slots (retail +0x10 tables, e.g. VA 0x00C53A98): AIUpdateInterface's
	// update (0x0026E267) and getDisabledTypesToProcess (0x004A2D67), both rowed.
	virtual UpdateSleepTime update();
	virtual DisabledMaskType getDisabledTypesToProcess() const;
protected:
	virtual ~AIUpdateInterface();
};

class SiegeAIUpdate : public AIUpdateInterface
{
public:
	SiegeAIUpdate(Thing *thing, const ModuleData *moduleData);
public:
	virtual ~SiegeAIUpdate();
public:
	// retail slot 4: the rowed ?getModuleNameKey@SiegeAIUpdate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

// ??0SiegeAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SiegeAIUpdate::SiegeAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AIUpdateInterface(thing, moduleData)
{
}

