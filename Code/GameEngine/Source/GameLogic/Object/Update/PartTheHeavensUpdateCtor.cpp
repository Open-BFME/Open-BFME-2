// cl: /DNDEBUG /MD
//
// ??0PartTheHeavensUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004AC998,
// 70 bytes. PartTheHeavensUpdate behavior ctor over the rowed UpdateModule
// base (0x253390, thing plus data): zero +0x24 (and-RMW, barrier-pinned),
// re-store the primary vtable slot and the +0x0C/+0x10 secondary slots
// with the class's own tables (retail 0x00C54DA4, 0x00BEFF90, 0x00C54D98,
// the three PartTheHeavensUpdate.cpp emits and its destructor installs),
// default +0x20 to 0x3FFFFFFF, then overwrite it from TheGameLogic+0x40
// unless the owner is null.
//
// The rowed name getter at 0x4AC93C (PartTheHeavensUpdate literal), the pool
// key at 0x4AC942 and the ModuleData pair (proc 0x4AC987 plus factory
// 0x24F4FD) prove the class; the rowed instance factory 0x24F4C5 is the sole
// raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" const void *const __identifier("??_7PartTheHeavensUpdate@@6BObjectModule@@@")[];  // vftable 0x00C54DA4
extern "C" const void *const __identifier("??_7PartTheHeavensUpdate@@6BBehaviorModuleInterface@@@")[];  // vftable 0x00BEFF90 (shared)
extern "C" const void *const __identifier("??_7PartTheHeavensUpdate@@6B@")[];  // vftable 0x00C54D98

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

// Opaque UpdateModule base; ctor resolves to its row. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x20 - 0x14];
};

class PartTheHeavensUpdate : public UpdateModule
{
public:
	PartTheHeavensUpdate(Thing *thing, const ModuleData *moduleData);

private:
	int m_20;
	int m_24;
};

// ??0PartTheHeavensUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4AC998
PartTheHeavensUpdate::PartTheHeavensUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_24 = 0;
	_ReadWriteBarrier();
	m_vtable = __identifier("??_7PartTheHeavensUpdate@@6BObjectModule@@@");
	m_p0C = __identifier("??_7PartTheHeavensUpdate@@6BBehaviorModuleInterface@@@");
	m_p10 = __identifier("??_7PartTheHeavensUpdate@@6B@");
	m_20 = 0x3FFFFFFF;
	if (m_owner != 0)
		m_20 = TheGameLogic->getFrame();
}
