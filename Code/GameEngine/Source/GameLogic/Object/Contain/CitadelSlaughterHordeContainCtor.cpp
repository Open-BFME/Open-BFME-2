// cl: /O1 /DNDEBUG /MD
//
// ??0CitadelSlaughterHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0048059F, 91 bytes.
// CitadelSlaughterHordeContain behavior ctor over the rowed
// SlaughterHordeContain intermediate base (0x48034E, thing plus data):
// forwards both args to the base, clears the int at +0x9EC, then re-stores
// the primary vtable slot and eight secondary slots at +0x0C/+0x10/+0x20/
// +0x24/+0x28/+0x2C/+0x30/+0x34 (address-of TU-local dummies, DIR32-masked).
// The and-first uses the ThreatFinder barrier recipe. The rowed pool key at
// 0x480600 and ModuleData factory 0x24C100 prove the class; the rowed
// instance factory 0x24C0C5 (news 0x9F0) is the sole raw caller. Row
// supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary20;
static int s_secondary24;
static int s_secondary28;
static int s_secondary2C;
static int s_secondary30;
static int s_secondary34;

// Rowed SlaughterHordeContain base; ctor resolves to its row. The explicit
// m_vtable member stands in for the inherited vptr so body order is source
// order.
class SlaughterHordeContain
{
public:
	SlaughterHordeContain(Thing *thing, const ModuleData *moduleData);

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
	unsigned char m_pad38[0x9EC - 0x38];
};

class CitadelSlaughterHordeContain : public SlaughterHordeContain
{
public:
	CitadelSlaughterHordeContain(Thing *thing, const ModuleData *moduleData);

private:
	int m_9EC;
	unsigned char m_pad9F0[0x9F0 - 0x9EC - 4];
};

// ??0CitadelSlaughterHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x48059F
CitadelSlaughterHordeContain::CitadelSlaughterHordeContain(Thing *thing, const ModuleData *moduleData)
	: SlaughterHordeContain(thing, moduleData)
{
	m_9EC = 0;
	_ReadWriteBarrier();
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
