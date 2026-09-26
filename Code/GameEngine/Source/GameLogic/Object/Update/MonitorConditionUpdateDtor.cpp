// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1MonitorConditionUpdate@@UAE@XZ, retail 0x004916AC, 73 bytes.
// MonitorConditionUpdate behavior dtor: compiler MI machinery restores the
// primary vtable 0x0084DAD8 plus the +0x0C/+0x10 secondary slots
// (0x007EFF90/0x0084DACC, DIR32-masked), then tears down the
// StringBase<char> at +0x20 through the pinned 0x36410 body, then the
// UpdateModule base through the rowed 0x24A797 body (twin pin for
// ??1UpdateModule). Layout from the rowed ctor 0x00491633 (same three
// stores plus and-[+0x20]-0) joined to UpdateModuleCtor.cpp MI hierarchy.
// Caller is the slot-0 ??_G at 0x00491750.

class Thing;
class ModuleData;

template <typename T> class StringBase
{
public:
	~StringBase();

private:
	void *m_data;
};

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

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
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
	virtual ~UpdateModule();
};

class MonitorConditionUpdate : public UpdateModule
{
public:
	MonitorConditionUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~MonitorConditionUpdate();

private:
	StringBase<char> m_str; // +0x20
};

MonitorConditionUpdate::~MonitorConditionUpdate()
{
}
