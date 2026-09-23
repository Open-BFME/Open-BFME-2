// cl: /O1 /DNDEBUG /MD
//
// ??0TunnelContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0047DBF7, 98 bytes.
// TunnelContain behavior ctor over the pinned HordeGarrisonContain
// intermediate base (0x47A040, thing plus data): forwards both args to the
// base, then re-stores the primary vtable slot and eight secondary slots at
// +0x0C/+0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34 (address-of TU-local
// dummies, DIR32-masked), then stores the bytes at +0x9E4/+0x9E5. The rowed
// name getter at 0x47DB88 and ModuleData factory 0x257A0A prove the class;
// the rowed instance factory 0x24BCED (news 0x9E8) is the sole raw caller.
// Row supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary20;
static int s_secondary24;
static int s_secondary28;
static int s_secondary2C;
static int s_secondary30;
static int s_secondary34;

// Opaque intermediate base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class HordeGarrisonContain
{
public:
	HordeGarrisonContain(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad14[0x20 - 0x14];
	const void *m_p20;
	const void *m_p24;
	const void *m_p28;
	const void *m_p2C;
	const void *m_p30;
	const void *m_p34;
	unsigned char m_pad38[0x9E4 - 0x38];
};

class TunnelContain : public HordeGarrisonContain
{
public:
	TunnelContain(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_9E4;
	unsigned char m_9E5;
	unsigned char m_pad9E6[0x9E8 - 0x9E6];
};

// ??0TunnelContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x47DBF7
TunnelContain::TunnelContain(Thing *thing, const ModuleData *moduleData)
	: HordeGarrisonContain(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p20 = &s_secondary20;
	m_p24 = &s_secondary24;
	m_p28 = &s_secondary28;
	m_p2C = &s_secondary2C;
	m_p30 = &s_secondary30;
	m_p34 = &s_secondary34;
	m_9E4 = 1;
	m_9E5 = 0;
}
