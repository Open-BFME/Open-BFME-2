// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0GiantBirdSlowDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00461E58, 72 bytes.
// GiantBirdSlowDeathBehavior behavior ctor over the pinned SlowDeathBehavior
// intermediate base (0x45D4B4, thing plus data): forwards both args to the
// base, clears the int at +0x50, re-stores the primary vtable slot and the
// +0x0C/+0x10/+0x20/+0x24 secondary slots (address-of TU-local dummies,
// DIR32-masked), then zeroes the float at +0x60 (plain float member,
// /arch:SSE emits retail movss) and the byte at +0x64. The rowed name getter
// and ModuleData factory prove the class; the rowed instance factory
// 0x24B599 (news 0x68) is the sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary20;
static int s_secondary24;

// Opaque intermediate base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class SlowDeathBehavior
{
public:
	SlowDeathBehavior(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad14[0x20 - 0x14];
	const void *m_p20;
	const void *m_p24;
	unsigned char m_pad28[0x50 - 0x28];
};

class GiantBirdSlowDeathBehavior : public SlowDeathBehavior
{
public:
	GiantBirdSlowDeathBehavior(Thing *thing, const ModuleData *moduleData);

private:
	int m_50;
	unsigned char m_pad54[0x60 - 0x54];
	float m_60;
	unsigned char m_64;
	unsigned char m_pad65[0x68 - 0x65];
};

// ??0GiantBirdSlowDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x461E58
GiantBirdSlowDeathBehavior::GiantBirdSlowDeathBehavior(Thing *thing, const ModuleData *moduleData)
	: SlowDeathBehavior(thing, moduleData)
{
	m_50 = 0;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p20 = &s_secondary20;
	m_p24 = &s_secondary24;
	m_60 = 0.0f;
	m_64 = 0;
}
