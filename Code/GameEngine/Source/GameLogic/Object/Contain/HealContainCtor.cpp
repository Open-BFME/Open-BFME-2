// cl: /O1 /DNDEBUG /MD
//
// ??0HealContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00466AEB, 84 bytes.
// HealContain behavior ctor over the pinned OpenContain base (0x4649F8,
// thing plus data): re-stores the primary vtable slot and eight secondary
// slots at +0x0C/+0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34 (address-of
// TU-local dummies, DIR32-masked). The rowed name getter at 0x466B88 proves
// the class; the rowed instance factory 0x24B7D2 is the sole raw caller. Row
// supersedes the ctor pin.

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

// Opaque OpenContain base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class OpenContain
{
public:
	OpenContain(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x20 - 0x14];
};

class HealContain : public OpenContain
{
public:
	HealContain(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_p20;
	const void *m_p24;
	const void *m_p28;
	const void *m_p2C;
	const void *m_p30;
	const void *m_p34;
};

// ??0HealContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x466AEB
HealContain::HealContain(Thing *thing, const ModuleData *moduleData)
	: OpenContain(thing, moduleData)
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
}
