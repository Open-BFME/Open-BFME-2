// cl: /O1 /DNDEBUG /MD
//
// ??0CaveContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00466630, 125 bytes.
// CaveContain behavior ctor over the pinned OpenContain base (0x4649F8,
// thing plus data): volatile-first double-store at +0xFC around two
// and-zeros at +0x104/+0x108, the primary vtable slot and eight secondary
// slots at +0x0C/+0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34, then the second
// +0xFC store and a trailing one byte at +0x100 (address-of TU-local
// dummies, DIR32-masked). The rowed pool key at 0x4663FF and the rowed
// instance factory 0x24B797 (sole caller, news 0x10C) prove the class. Row
// supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_firstFC;
static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary20;
static int s_secondary24;
static int s_secondary28;
static int s_secondary2C;
static int s_secondary30;
static int s_secondary34;
static int s_secondFC;

// Opaque OpenContain base (0xFC); ctor resolves to its pin.
class OpenContain
{
public:
	OpenContain(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_pad[0xFC];
};

class CaveContain : public OpenContain
{
public:
	CaveContain(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_FC;
	unsigned char m_100;
	unsigned char m_pad101[3];
	int m_104;
	int m_108;
};

// ??0CaveContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x466630
CaveContain::CaveContain(Thing *thing, const ModuleData *moduleData)
	: OpenContain(thing, moduleData)
{
	*(const void * volatile *)&m_FC = &s_firstFC;
	_ReadWriteBarrier();
	m_104 = 0;
	m_108 = 0;
	*(const void **)this = &s_vtable;
	*(const void **)((char *)this + 0xC) = &s_secondary0C;
	*(const void **)((char *)this + 0x10) = &s_secondary10;
	*(const void **)((char *)this + 0x20) = &s_secondary20;
	*(const void **)((char *)this + 0x24) = &s_secondary24;
	*(const void **)((char *)this + 0x28) = &s_secondary28;
	*(const void **)((char *)this + 0x2C) = &s_secondary2C;
	*(const void **)((char *)this + 0x30) = &s_secondary30;
	*(const void **)((char *)this + 0x34) = &s_secondary34;
	m_FC = &s_secondFC;
	m_100 = 1;
}
