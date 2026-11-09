// cl: /O1 /DNDEBUG /MD
//
// UpdateModule::UpdateModule, retail 0x00253390, 61 bytes. Dedicated TU so
// CreateModule.cpp cannot see this body. BehaviorModule ctor stays at 0x253330.

class Thing;
class ModuleData;

class BehaviorModuleBase
{
	virtual void unused();
	int a;
	int b;
};

class BehaviorModuleOther
{
	virtual void unused();
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

template <int N> class BitFlags;

// The interface table as the other UpdateModule views (first in link order:
// DumbProjectileBehavior.cpp) spell it: update stays pure in UpdateModule and the
// second slot is UpdateModule's getDisabledTypesToProcess.
class UpdateModuleInterface
{
public:
	virtual void update() = 0;
	virtual BitFlags<11> getDisabledTypesToProcess() const = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	// BehaviorModuleInterface slot 9 (retail VA 0x00BEFF90): UpdateModule's override,
	// rowed at 0x002533D3 (header-inline in UpdateModule.h; SupplyTruckAIUpdateCtor.cpp).
	virtual UpdateModuleInterface *getUpdate();
	virtual BitFlags<11> getDisabledTypesToProcess() const;
};

UpdateModule::UpdateModule(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData),
	  m_nextCallFrameAndPhase(0),
	  m_indexInLogic(-1),
	  m_bfmeReserved(-1)
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleOther@@EAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
