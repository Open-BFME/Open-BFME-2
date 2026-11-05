// cl: /DNDEBUG /MD /GX
//
// ??0FoundationAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004551B3,
// 107 bytes. Behavior-side ctor (rowed instance factory 0x24AA26 news
// 0x30 with this pinned 2-arg ctor as a raw caller at 0x24AA4D; poolkey
// rowed at 0x455167 pushes the FoundationAIUpdate literal; a derived
// behavior ctor at 0x3983D4 shares the base call).
//
// Shape follows the SlaveWatcherBehavior precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, a two-phase +0x20 slot via sourced-before address-take, an
// and-zero at +0x28, a one-homed local (xor-plus-inc) feeding the
// setWakeFrame frame plus +0x24/+0x2C, the three derived vtable installs,
// and the setWakeFrame tail (protected IAEX Object-uint spelling resolves
// via the existing pin at 0x44DF71). Row supersedes the ctor pin.

extern "C" const void *const __identifier("??_7Rva005EEF2FBase0@@6B@")[];  // vftable 0x00BFBC9C

extern "C" const void *const __identifier("??_7CastleBehavior@@6BFoundationAIUpdateInterface@@@")[];  // vftable 0x00C1A690
extern "C" const void *const __identifier("??_7Rva00455050@@6BUpdateModule@@@")[];  // vftable 0x00C40538
extern "C" const void *const __identifier("??_7Rva00455050@@6BBehaviorModuleInterface@@@")[];  // vftable 0x00C40548
extern "C" const void *const __identifier("??_7Rva00455050@@6BObjectModule@@@")[];  // vftable 0x00C40608

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class FoundationAIUpdate : public UpdateModule
{
public:
	FoundationAIUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned char m_2C;
};

// ??0FoundationAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004551B3
FoundationAIUpdate::FoundationAIUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int *slot20 = (int *)&m_20;
	*slot20 = (int)((unsigned int)__identifier("??_7Rva005EEF2FBase0@@6B@"));
	m_28 &= 0;
	int one = 1;
	*(const void **)this = (const void *)((unsigned int)__identifier("??_7Rva00455050@@6BObjectModule@@@"));
	*(const void **)((char *)this + 0x0C) = (const void *)((unsigned int)__identifier("??_7Rva00455050@@6BBehaviorModuleInterface@@@"));
	*(const void **)((char *)this + 0x10) = (const void *)((unsigned int)__identifier("??_7Rva00455050@@6BUpdateModule@@@"));
	m_20 = (const void *)((unsigned int)__identifier("??_7CastleBehavior@@6BFoundationAIUpdateInterface@@@"));
	m_24 = one;
	m_2C = (unsigned char)one;
	setWakeFrame(m_object, (UpdateSleepTime)one);
}
