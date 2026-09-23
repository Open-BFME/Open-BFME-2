// cl: /O1 /DNDEBUG /MD
//
// ??0ScavengerSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C4353, 46 bytes.
// ScavengerSpecialPower behavior ctor over the pinned Rva00493C5A
// intermediate base (0x493C5A, thing plus data): re-stores the primary
// vtable slot and the +0x0C/+0x10 secondary slots, then zeroes the byte at
// +0x34 (address-of TU-local dummies, DIR32-masked). The rowed name getter
// at 0x4C43BC proves the class; the rowed instance factory 0x251D94 is the
// sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Opaque intermediate base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class Rva00493C5A
{
public:
	Rva00493C5A(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	unsigned char m_pad04[0x0C - 4];
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad14[0x34 - 0x14];
};

class ScavengerSpecialPower : public Rva00493C5A
{
public:
	ScavengerSpecialPower(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_34;
};

// ??0ScavengerSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x4C4353
ScavengerSpecialPower::ScavengerSpecialPower(Thing *thing, const ModuleData *moduleData)
	: Rva00493C5A(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_34 = 0;
}
