// cl: /O1 /DNDEBUG /MD
//
// ??0FellBeastSwoopPower@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C6C1E, 56 bytes.
// FellBeastSwoopPower behavior ctor over the pinned Rva0044EF5E intermediate
// base (0x44EF5E, thing plus data): re-stores the primary vtable slot and
// the +0x0C/+0x10/+0x20 secondary slots, then zeroes the byte at +0x88
// (address-of TU-local dummies, DIR32-masked). The rowed name getter at
// 0x4C6C7C proves the class; the rowed instance factory 0x2523B3 is the sole
// raw caller. Row supersedes the ctor pin.

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

class FellBeastSwoopPower : public Rva0044EF5E
{
public:
	FellBeastSwoopPower(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_p20;
	unsigned char m_pad24[0x88 - 0x24];
	unsigned char m_88;
};

// ??0FellBeastSwoopPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x4C6C1E
FellBeastSwoopPower::FellBeastSwoopPower(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p20 = &s_secondary20;
	m_88 = 0;
}
