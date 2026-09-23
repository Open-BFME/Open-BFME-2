// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0HeightDieUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0048FCB2, 77 bytes.
// HeightDieUpdate behavior ctor over the rowed UpdateModule base (0x253390):
// sets +0x30 to -1, re-stores the primary vtable slot and the +0x0C/+0x10
// secondary slots, zeroes the bytes at +0x20/+0x21, then stores -1.0f into
// +0x24/+0x28/+0x2C (address-of TU-local dummies plus -1.0f literals that
// pool-merge to retail 0xBBB9AC, DIR32-masked). The rowed name getter at
// 0x48FC30 proves the class; the rowed instance factory 0x24D37E is the sole
// raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

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

class HeightDieUpdate : public UpdateModule
{
public:
	HeightDieUpdate(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_20;
	unsigned char m_21;
	unsigned char m_pad22[2];
	float m_24;
	float m_28;
	float m_2C;
	int m_30;
};

// ??0HeightDieUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x48FCB2
HeightDieUpdate::HeightDieUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_30 |= -1;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_20 = 0;
	m_21 = 0;
	m_24 = -1.0f;
	m_28 = -1.0f;
	m_2C = -1.0f;
}
