// cl: /O1 /DNDEBUG /MD
//
// ??0UntamedAllegianceSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C7B06, 42 bytes.
// UntamedAllegianceSpecialPower behavior ctor over the pinned Rva00493C5A
// intermediate base (0x493C5A, thing plus data): re-stores the primary
// vtable slot and the +0x0C/+0x10 secondary slots (address-of TU-local
// dummies, DIR32-masked). The rowed name getter at 0x4C7B4F proves the
// class; the rowed instance factory 0x25247A is the sole raw caller. Row
// supersedes the ctor pin.

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
};

class UntamedAllegianceSpecialPower : public Rva00493C5A
{
public:
	UntamedAllegianceSpecialPower(Thing *thing, const ModuleData *moduleData);
};

// ??0UntamedAllegianceSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x4C7B06
UntamedAllegianceSpecialPower::UntamedAllegianceSpecialPower(Thing *thing, const ModuleData *moduleData)
	: Rva00493C5A(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
