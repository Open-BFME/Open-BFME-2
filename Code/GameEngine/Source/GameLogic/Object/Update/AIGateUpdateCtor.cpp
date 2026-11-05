// cl: /DNDEBUG /MD
//
// ??0AIGateUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B08E8, 60
// bytes. AIGateUpdate ctor over the rowed UpdateModule base (0x253390):
// zeroed state at +0x20/+0x24/+0x28/+0x2C/+0x30/+0x31 plus the vtable and the
// two secondary installs. Base-class layout mirrors UpdateModuleCtor.cpp
// exactly (MI chain plus wake/index members) so the derived stores land;
// the secondary installs at +0xC/+0x10 come from that chain. The members
// use the seed TU's field view. Recipe:
// DestroyEnvironmentUpdateCtor.cpp minus the GameLogic tail.

class Thing;
class ModuleData;
class GateOpener;

class BehaviorModuleBase
{
	virtual void unused();

protected:
	const ModuleData *m_moduleData;
	int m_object;
};

class BehaviorModuleOther
{
	virtual void unused();
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class AIGateUpdate : public UpdateModule
{
public:
	AIGateUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~AIGateUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update(); // UpdateModuleInterface slot 0, the rowed override

private:
	GateOpener *m_opener;
	unsigned m_24;
	int count28;
	int count2C;
	bool loaded;
	unsigned char enabled;
};

// ??0AIGateUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
AIGateUpdate::AIGateUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData),
	  m_opener(0),
	  m_24(0),
	  count28(0),
	  count2C(0),
	  loaded(false),
	  enabled(0)
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleOther@@EAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleBase@@EAEXXZ=??_GAIGateUpdate@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?update@UpdateModule@@UAEXXZ=?update@AIGateUpdate@@UAE?AW4UpdateSleepTime@@XZ")
