// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0AnimalAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0047ECA8
// (121 bytes). Behavior ctor over the pinned opaque Transport base (0x26E9BD,
// thing plus data): installs the six behavior vtable slots (+0x00/+0x0C/+0x10/
// +0x20/+0x24 via explicit members with TU-local dummy statics, DIR32-masked;
// +0x3E4 double-stored C1C780-then-C47B84) plus zeros at +0x3E8/+0x3F8/+0x3F9
// plus float zeros at +0x3EC/+0x3F0/+0x3F4. The class declares no virtuals of
// its own: the stores land from explicit members in body order (AssaultTransport
// precedent with volatile-first-store for the redundant +0x3E4 pair). Row
// supersedes the sole-caller pin; the instance factory at 0x24BE95 is the
// single raw caller; vtable 0x847B98 slot4 holds the rowed AnimalAIUpdate
// poolkey 0x47EC1A.

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
	int m_3E8;				// +0x3E8
	float m_3EC;				// +0x3EC
	float m_3F0;				// +0x3F0
	float m_3F4;				// +0x3F4
	unsigned char m_3F8;			// +0x3F8
	unsigned char m_3F9;			// +0x3F9
};

class AnimalAIUpdate : public Rva0026E9BDBase
{
public:
	AnimalAIUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0AnimalAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x47ECA8
AnimalAIUpdate::AnimalAIUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva0026E9BDBase(thing, moduleData)
{
	*(const void * volatile *)&m_p3E4 = &s_slot3E4first;
	m_p3E4 = &s_slot3E4second;
	m_3E8 = 0;
	m_3F8 = 0;
	m_3F9 = 0;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p20 = &s_secondary20;
	m_p24 = &s_secondary24;
	m_3F4 = 0.0f;
	m_3F0 = 0.0f;
	m_3EC = 0.0f;
}
