// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0PassiveAreaEffectBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x00484A67, 110 bytes. Behavior-side ctor in the PassiveAreaEffect
// file-unit: the rowed UpdateModule base ctor (0x253390, thing plus data)
// runs first, then the +0x20 word zeroes (RMW-and hoists to the front),
// the list setup hoists above the compiler-emitted MI vptr re-stores at
// +0/+0x0C/+0x10 (values are TU-local vtables, DIR32-masked), and the
// +0x24 list-base row (0x4EC36C) runs last of init. The body clears the
// list through the rowed clear (0x23DAA5, second EH state) then keeps
// itself awake with setWakeFrame(obj, 1) through the pin at 0x44DF71.
// Hierarchy mirrors the rowed UpdateModuleCtor TU (MI with three vptrs);
// the derived override re-stores all three vptrs, which is the identity
// proof alongside the rowed pool key at 0x484ADD (begins where this ctor
// ends). The ModuleData proc 0x48490E, ModuleData ctor 0x484DF4, ModuleData
// factory 0x24C724 and instance factory 0x24C6EC complete the unit.

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

// ??0PassiveAreaEffectBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x484A67
PassiveAreaEffectBehavior::PassiveAreaEffectBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
	, m_20(0)
{
	m_trackedIds.clear();
	setWakeFrame(*(Object **)((char *)this + 8), 1);
}
