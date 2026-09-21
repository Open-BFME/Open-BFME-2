// cl: /O1 /DNDEBUG /MD
//
// ??0InvisibilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004A382D,
// 67 bytes. InvisibilityUpdate behavior ctor over the rowed UpdateModule
// base (0x253390, thing plus data): re-stores the primary vtable slot and
// the +0x0C/+0x10 secondary slots (address-of TU-local dummies,
// DIR32-masked), points +0x20 at the dispatch table, then copies the
// owner's stealth flag byte (+0x1D0) into +0x24.
//
// The class declares no virtuals of its own: the vtable store at +0 lands
// from the explicit m_vtable member in body order (retail keeps the +0x20
// store ahead of it), so a virtual TU spelling cannot reproduce the order.
// The base ctor spelling is the rowed one; the call resolves to its row.
// Recipe: BoredUpdateCtor.cpp opaque-base pattern with the Invisibility
// file-unit (pool key at 0x004A393C plus ModuleData proc 0x004A381C).

class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Thing
{
public:
	unsigned char m_reserved[0x1D0];
	unsigned char m_stealthFlag;
};

static int s_first20;
static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_second20;

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

class InvisibilityUpdate : public UpdateModule
{
public:
	InvisibilityUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_dispatch20;
	unsigned char m_stealth24;
};

// ??0InvisibilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
InvisibilityUpdate::InvisibilityUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_dispatch20 = &s_first20;
	_ReadWriteBarrier();
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_dispatch20 = &s_second20;
	m_stealth24 = m_owner->m_stealthFlag;
}
