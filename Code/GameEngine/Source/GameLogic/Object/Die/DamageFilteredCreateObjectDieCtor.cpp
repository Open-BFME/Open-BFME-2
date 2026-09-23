// cl: /O1 /DNDEBUG /MD
//
// ??0DamageFilteredCreateObjectDie@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00485F87, 64 bytes.
// DamageFilteredCreateObjectDie behavior ctor over the pinned DieModule base
// (0x45CEBD, thing plus data): stores +0x14, zeroes +0x18, sets +0x1C to -1,
// then re-stores the primary vtable slot and the +0x0C/+0x10 secondary slots
// and stores +0x14 a second time (address-of TU-local dummies,
// DIR32-masked). The rowed name getter at 0x485EFD proves the class; the
// rowed instance factory 0x24C99B is the sole raw caller. Row supersedes the
// ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_first14;
static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_second14;

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
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p14 = &s_second14;
}
