// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ??0GiveUpgradeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0049C3AC, 74 bytes.
// GiveUpgradeUpdate behavior ctor over the pinned Rva0044EF5E intermediate
// base (0x44EF5E, thing plus data): re-stores the primary vtable slot and
// the +0x0C/+0x10/+0x20 secondary slots (address-of TU-local dummies,
// DIR32-masked), then clears two flags at +0x88/+0x89 and zeroes a float at
// +0x8C (xorps plus movss, needs /arch:SSE). The rowed name getter at
// 0x49C471 and ModuleData factory 0x24E800 prove the class; the rowed
// instance factory 0x24E7C5 is the sole raw caller. Row supersedes the ctor
// pin. BFME1 donor GiveUpgradeUpdate.cpp has the same two-flag plus trailing
// member shape (bool m_e8/m_e9 plus m_ec).

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary20;

// Opaque intermediate base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x20 - 0x14];
};

class GiveUpgradeUpdate : public Rva0044EF5E
{
public:
	GiveUpgradeUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_p20;
	unsigned char m_pad24[0x88 - 0x24];
	bool m_firstFlag;
	bool m_secondFlag;
	unsigned char m_pad8A[2];
	float m_value;
};

// ??0GiveUpgradeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x49C3AC
GiveUpgradeUpdate::GiveUpgradeUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p20 = &s_secondary20;
	m_firstFlag = false;
	m_secondFlag = false;
	m_value = 0.0f;
}
