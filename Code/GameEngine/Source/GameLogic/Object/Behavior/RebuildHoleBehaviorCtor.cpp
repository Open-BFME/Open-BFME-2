// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0RebuildHoleBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00483271,
// 102 bytes. RebuildHoleBehavior ctor over the rowed UpdateModule base
// (0x253390, thing plus data). FakePathfindPortalBehaviour two-phase idiom:
// sourced-before address-take slots commit the initial +0x20/+0x24 constants
// first; a shared-zero run clears +0x28 through +0x3C; the vtable group
// reinstalls the primary slot, the +0x0C/+0x10 secondaries and +0x20/+0x24;
// a float zero lands at +0x40 and a set flag at +0x44 (address-of TU-local
// dummies, DIR32-masked; no virtuals are declared anywhere so no vtable is
// emitted here).
//
// The rowed name getter at 0x48331C (RebuildHoleBehavior literal), the pool
// key at 0x4832D7, the ModuleData pair (ctor 0x48323E plus factory 0x24C433)
// and the rowed instance factory 0x24C3FB (sole caller, ModuleFactory
// registration literal) prove the class. Row supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary20;
static int s_secondary24;

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

class RebuildHoleBehavior : public UpdateModule
{
public:
	RebuildHoleBehavior(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_secondary20;
	const void *m_secondary24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	float m_40;
	bool m_44;
};

// ??0RebuildHoleBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x483271
RebuildHoleBehavior::RebuildHoleBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int *slot20 = (int *)&m_secondary20;
	*slot20 = (int)0x00C1C780;
	int *slot24 = (int *)&m_secondary24;
	*slot24 = (int)0x00C078DC;
	m_28 = 0;
	m_2C = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 0;
	m_3C = 0;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_secondary20 = &s_secondary20;
	m_secondary24 = &s_secondary24;
	m_40 = 0.0f;
	m_44 = true;
}
