// cl: /DNDEBUG /MD
//
// ??0DestroyEnvironmentUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004AC63A, 68 bytes. DestroyEnvironmentUpdate ctor over the rowed
// UpdateModule base (0x253390): next-call frame defaults to 0x3FFFFFFF with
// flags zeroed, then refreshes from TheGameLogic frame when module data is
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

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
	const ModuleData *getModuleData() const { return m_moduleData; }
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual void update();
};

class GameLogic
{
public:
	unsigned getFrame() const { return m_frame; }

private:
	unsigned char m_reserved[0x40];
	unsigned m_frame;
};

extern GameLogic *TheGameLogic;

class DestroyEnvironmentUpdate : public UpdateModule
{
public:
	DestroyEnvironmentUpdate(Thing *thing, const ModuleData *moduleData);

private:
	unsigned int m_nextCallFrame;
	unsigned int m_flags;
};

// ??0DestroyEnvironmentUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DestroyEnvironmentUpdate::DestroyEnvironmentUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData),
	  m_nextCallFrame(0x3FFFFFFF),
	  m_flags(0)
{
	if (getModuleData() != 0)
		m_nextCallFrame = TheGameLogic->getFrame();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleOther@@EAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
