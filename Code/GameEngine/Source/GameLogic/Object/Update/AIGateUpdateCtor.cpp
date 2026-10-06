// cl: /DNDEBUG /MD
//
// ??0AIGateUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B08E8, 60
// bytes. AIGateUpdate ctor over the rowed UpdateModule base (0x253390):
// zeroed state at +0x20/+0x24/+0x28/+0x2C/+0x30/+0x31 plus the vtable and the
// two secondary installs. Base-class layout mirrors UpdateModuleCtor.cpp
// exactly (MI chain plus wake/index members) so the derived stores land;
// the secondary installs at +0xC/+0x10 come from that chain. The members
// have no identified purpose yet, hence reserved names. Recipe:
// DestroyEnvironmentUpdateCtor.cpp minus the GameLogic tail.

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

class AIGateUpdate : public UpdateModule
{
public:
	AIGateUpdate(Thing *thing, const ModuleData *moduleData);

private:
	unsigned int m_reserved20;
	unsigned int m_reserved24;
	unsigned int m_reserved28;
	unsigned int m_reserved2C;
	unsigned char m_reserved30;
	unsigned char m_reserved31;
};

// ??0AIGateUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
AIGateUpdate::AIGateUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData),
	  m_reserved20(0),
	  m_reserved24(0),
	  m_reserved28(0),
	  m_reserved2C(0),
	  m_reserved30(0),
	  m_reserved31(0)
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleOther@@EAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
