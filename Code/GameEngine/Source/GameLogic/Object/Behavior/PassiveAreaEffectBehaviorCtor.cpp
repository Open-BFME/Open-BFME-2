// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/Libraries/Include /ICode/GameEngine/Source /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmelist
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

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}

class Thing;
class ModuleData;
class Object;
class Xfer;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

#include "../../../../Include/Common/ObjectModule.h"

// Slot 0 of each module's primary vftable is its deleting destructor
// (0x00484C3C in 0x00C4A448), so the base's first virtual is the destructor.
struct AreaData;
class BehaviorModuleBase
{
private:
	virtual ~BehaviorModuleBase();
public:
	const AreaData *m_moduleData; // +0x04
	Object *m_object; // +0x08
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

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};


class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime frame);
};

class PassiveAreaEffectBehavior : public UpdateModule
{
public:
	PassiveAreaEffectBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~PassiveAreaEffectBehavior();
	virtual void slot01() = 0;
	virtual void slot02() = 0;

protected:
	virtual void xfer(Xfer *xfer);

public:
	virtual NameKeyType getModuleNameKey() const;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void rva00484C8B();
	virtual void rva004848E6(Object *obj);
	virtual void rva0048491F(Object *obj);
	virtual void rva00484A08(Object *obj);
	virtual UpdateSleepTime update();

private:
	unsigned int m_20; // +0x20
	_STL::list<int> m_trackedIds; // +0x24, runtime watch list
};

// ??0PassiveAreaEffectBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x484A67
PassiveAreaEffectBehavior::PassiveAreaEffectBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
	, m_20(0)
{
	m_trackedIds.clear();
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleOther@@EAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
