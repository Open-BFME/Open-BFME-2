// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1PassiveAreaEffectBehavior@@UAE@XZ, retail 0x00484B22,
// 73 bytes. Behavior-side dtor restoring the three MI vptrs (+0 0xC4A448
// plus +0x0C 0x7EFF90 plus +0x10 0xC4A438) then destroying the +0x24
// tracked-ids list through the rowed 0x4EC395 List_base dtor and calling
// the UpdateModule base dtor through the pinned 0x24A797. Layout follows
// the ctor TU 0x484A67 (UpdateModule base size 0x20 plus m_20 plus list)
// over the rowed UpdateModuleCtor TU. Identity is the own vtable 0xC4A448
// plus slot 0 deleting dtor 0x484C3C calling this body plus poolkey
// 0x484ADD. BFME1 donor PassiveAreaEffectBehaviorDestructors.cpp proves
// virtual public UAE spelling plus list at +0x24.

#include <list>

class Thing;
class ModuleData;
class Object;

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

protected:
	void setWakeFrame(Object *obj, unsigned int frame);
};

class PassiveAreaEffectBehavior : public UpdateModule
{
public:
	PassiveAreaEffectBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~PassiveAreaEffectBehavior();

private:
	int m_20; // +0x20
	_STL::list<int> m_trackedIds; // +0x24, runtime watch list
};

// ??1PassiveAreaEffectBehavior@@UAE@XZ @0x00484B22
PassiveAreaEffectBehavior::~PassiveAreaEffectBehavior()
{
}
