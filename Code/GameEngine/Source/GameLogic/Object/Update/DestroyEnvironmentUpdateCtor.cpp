// cl: /DNDEBUG /MD
//
// ??0DestroyEnvironmentUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004AC63A, 68 bytes. DestroyEnvironmentUpdate ctor over the rowed
// UpdateModule base (0x253390): next-call frame defaults to 0x3FFFFFFF with
// the object ID cleared, then refreshes from TheGameLogic frame when module data is
// present. Base-class layout mirrors UpdateModuleCtor.cpp exactly (MI chain
// plus wake/index members) so the derived stores land at +0x20/+0x24; the
// secondary vtable installs at +0xC/+0x10 come from that chain. TheGameLogic
// frame read at +0x40 inlines the BFME1 donor GetFrame path. Recipe: the
// BFME1 DestroyEnvironmentUpdateCtorThunk donor verbatim.

class Thing;
class ModuleData;

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


#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class DestroyEnvironmentUpdate : public UpdateModule
{
public:
	DestroyEnvironmentUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~DestroyEnvironmentUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	void rva004AC722();

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrame;
	ObjectID m_objectID;
};

// ??0DestroyEnvironmentUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DestroyEnvironmentUpdate::DestroyEnvironmentUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData),
	  m_nextCallFrame(0x3FFFFFFF),
	  m_objectID(INVALID_OBJECT_ID)
{
	if (getModuleData() != 0)
		m_nextCallFrame = TheGameLogic->getFrame();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleOther@@EAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleBase@@EAEXXZ=??_GDestroyEnvironmentUpdate@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?update@UpdateModule@@UAEXXZ=?update@DestroyEnvironmentUpdate@@UAE?AW4UpdateSleepTime@@XZ")
