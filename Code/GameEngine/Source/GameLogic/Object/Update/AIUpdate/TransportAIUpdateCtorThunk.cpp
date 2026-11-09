// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: TransportAIUpdate module ctor.
// Out-of-line base MI, then five most-derived vtbls at
// +0/+0xC/+0x10/+0x20/+0x24.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../../Include/GameLogic/Module/BehaviorModule.h"
// The +0x10 update interface and the +0x14..+0x1F fields are UpdateModule's.
#include "../../../../../Include/GameLogic/Module/UpdateModule.h"


class TransportAIUpdateIface3
{
public:
	virtual void transportAIUpdateIface3Anchor();
};

class TransportAIUpdateIface4
{
public:
	virtual void transportAIUpdateIface4Anchor();
};

class AIUpdateInterface : public UpdateModule, public TransportAIUpdateIface3, public TransportAIUpdateIface4
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransportAIUpdate.h
class TransportAIUpdate : public AIUpdateInterface
{
public:
	TransportAIUpdate(Thing *thing, const ModuleData *moduleData);
public:
	virtual ~TransportAIUpdate();
protected:
	// retail slot 3: the rowed ?xfer@TransportAIUpdate@@MAEXPAVXfer@@@Z
	virtual void xfer(Xfer *xfer);
public:
	// retail slot 4: the rowed ?getModuleNameKey@TransportAIUpdate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

// ??0TransportAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
TransportAIUpdate::TransportAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AIUpdateInterface(thing, moduleData)
{
}

