// cl: /O1 /DNDEBUG /MD
//
// ??0AssaultTransportAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x0048F5A3 (89 bytes). Behavior ctor over the pinned opaque Transport
// base (0x26E9BD, thing plus data): installs the six behavior vtable slots
// (+0x00/+0x0C/+0x10/+0x20/+0x24 via explicit members with TU-local dummy
// statics, DIR32-masked; +0x3E4 double-stored C1C780-then-C4CC88) plus 0xA
// at +0x43C, then runs the pinned class helper (0x48F365). The class
// declares no virtuals of its own: the stores land from explicit members in
// body order (PlayerHeal precedent). Row supersedes the sole-caller pin;
// the instance factory at 0x24D263 is the single raw caller.

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary20;
static int s_secondary24;
static int s_slot3E4first;
static int s_slot3E4second;

class Rva0026E9BDBase
{
public:
	Rva0026E9BDBase(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;			// +0x00
	unsigned char m_pad04[0x0C - 4];
	const void *m_p0C;			// +0x0C
	const void *m_p10;			// +0x10
	unsigned char m_pad14[0x20 - 0x14];
	const void *m_p20;			// +0x20
	const void *m_p24;			// +0x24
	unsigned char m_pad28[0x3E4 - 0x28];
	const void *m_p3E4;			// +0x3E4
	unsigned char m_pad3E8[0x43C - 0x3E8];
	int m_count43C;			// +0x43C
};

class AssaultTransportAIUpdate : public Rva0026E9BDBase
{
public:
	AssaultTransportAIUpdate(Thing *thing, const ModuleData *moduleData);
	void Rva0048F365Helper();
};

// ??0AssaultTransportAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x48F5A3
AssaultTransportAIUpdate::AssaultTransportAIUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva0026E9BDBase(thing, moduleData)
{
	*(const void * volatile *)&m_p3E4 = &s_slot3E4first;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p20 = &s_secondary20;
	m_p24 = &s_secondary24;
	m_p3E4 = &s_slot3E4second;
	m_count43C = 0xA;
	Rva0048F365Helper();
}
