// cl: /DNDEBUG /MD /EHsc
//
// ?rva00454472@GettingBuiltBehaviorSecondary@@QAEXH@Z, retail 0x00454472,
// 29 bytes. Secondary-this wrapper in the GettingBuilt file-unit (prev poolkey
// rowed at 0x004543EB, next dtor rowed at 0x0045448F in GettingBuiltBehaviorDtor).
// Retail: lea ecx [esi-0x10] plus indirect slot-0 call plus push arg plus lea
// ecx [esi-0x20] plus push m_object (this-0x18) plus rowed setWakeFrame
// 0x0044DF71. Layout follows rowed ctor 0x004542FA (UpdateModule base 0x20
// with BehaviorModuleOther at +0x0C and UpdateModuleInterface at +0x10 plus
// secondary at +0x20 with m_object at primary+0x08). No EH frame; no STL.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void iface00();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	friend class GettingBuiltBehaviorSecondary;
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime frame);
};

class GettingBuiltBehaviorSecondary
{
public:
	void rva00454472(int arg);
};

void GettingBuiltBehaviorSecondary::rva00454472(int arg)
{
	UpdateModuleInterface *iface = (UpdateModuleInterface *)((char *)this - 0x10);
	iface->iface00();
	Object *obj = *(Object **)((char *)this - 0x18);
	UpdateModule *mod = (UpdateModule *)((char *)this - 0x20);
	mod->setWakeFrame(obj, (UpdateSleepTime)arg);
}
