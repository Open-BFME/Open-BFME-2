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

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

// Expose the canonical protected helper for this secondary-this wrapper.
// No object of this access class is constructed; its base starts at offset zero.
class GettingBuiltWakeAccess : public UpdateModule
{
public:
	using UpdateModule::setWakeFrame;
};

class GettingBuiltBehaviorSecondary
{
public:
	void rva00454472(int arg);
};

void GettingBuiltBehaviorSecondary::rva00454472(int arg)
{
	UpdateModuleInterface *iface = (UpdateModuleInterface *)((char *)this - 0x10);
	iface->update();
	Object *obj = *(Object **)((char *)this - 0x18);
	GettingBuiltWakeAccess *mod = (GettingBuiltWakeAccess *)((char *)this - 0x20);
	mod->setWakeFrame(obj, (UpdateSleepTime)arg);
}
