// cl: /DNDEBUG /MD
//
// ??0DamageFilteredCreateObjectDie@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00485F87, 64 bytes.
// DamageFilteredCreateObjectDie behavior ctor over the pinned DieModule base
// (0x45CEBD, thing plus data): stores +0x14, zeroes +0x18, sets +0x1C to -1,
// then re-stores the primary vtable slot and the +0x0C/+0x10 secondary slots
// and stores +0x14 a second time (the class's own tables by their retail
// store immediates; the transient first +0x14 value, overwritten before any
// call, stays a TU-local dummy).
// The rowed name getter at 0x485EFD proves the class; the
// rowed instance factory 0x24C99B is the sole raw caller. Row supersedes the
// ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_first14;
extern "C" const void *const __identifier("??_7DamageFilteredCreateObjectDie@@6BObjectModule@@@")[];  // vftable 0x00C4AB54
extern "C" const void *const __identifier("??_7DamageFilteredCreateObjectDie@@6BBehaviorModuleInterface@@@")[];  // vftable 0x00C4AA98
extern "C" const void *const __identifier("??_7DamageFilteredCreateObjectDie@@6BDieModule@@@")[];  // vftable 0x00C4AA90
extern "C" const void *const __identifier("??_7DamageFilteredCreateObjectDie@@6BRva00C4AA84Iface@@@")[];  // vftable 0x00C4AA84

// Opaque DieModule base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class DieModule
{
public:
	DieModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	const void *m_p14;
	int m_18;
	int m_1C;
};

class DamageFilteredCreateObjectDie : public DieModule
{
public:
	DamageFilteredCreateObjectDie(Thing *thing, const ModuleData *moduleData);
};

// ??0DamageFilteredCreateObjectDie@@QAE@PAVThing@@PBVModuleData@@@Z @0x485F87
DamageFilteredCreateObjectDie::DamageFilteredCreateObjectDie(Thing *thing, const ModuleData *moduleData)
	: DieModule(thing, moduleData)
{
	*(const void * volatile *)&m_p14 = &s_first14;
	_ReadWriteBarrier();
	m_18 = 0;
	m_1C |= -1;
	m_vtable = __identifier("??_7DamageFilteredCreateObjectDie@@6BObjectModule@@@");
	m_p0C = __identifier("??_7DamageFilteredCreateObjectDie@@6BBehaviorModuleInterface@@@");
	m_p10 = __identifier("??_7DamageFilteredCreateObjectDie@@6BDieModule@@@");
	m_p14 = __identifier("??_7DamageFilteredCreateObjectDie@@6BRva00C4AA84Iface@@@");
}
