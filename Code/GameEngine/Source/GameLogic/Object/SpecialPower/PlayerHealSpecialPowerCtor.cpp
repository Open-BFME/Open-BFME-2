// cl: /O1 /DNDEBUG /MD
//
// ??0PlayerHealSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004C7E7E, 39 bytes. PlayerHealSpecialPower behavior ctor over the pinned
// Rva00493C5A intermediate base (0x493C5A, thing plus data): re-stores the
// primary vtable slot (the behavior vtable 0x00C5E36C, distinct from the
// ModuleData vtable 0x00C5E7A8) and the +0x0C/+0x10 secondary slots
// (address-of TU-local dummies, DIR32-masked).
//
// The class declares no virtuals of its own: the vtable store at +0 lands
// from the explicit m_vtable member in body order, so a virtual TU spelling
// cannot reproduce the order. The base ctor spelling resolves to its pin.
// Recipe: InvisibilityUpdateCtor.cpp opaque-base pattern with the PlayerHeal
// file-unit (pool key at 0x004C7EFB plus ModuleData proc 0x004C7E63 ending
// exactly where this ctor begins plus ModuleData factory 0x002525C7; the
// instance factory at 0x0025258F is the sole raw caller).

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

class PlayerHealSpecialPower : public Rva00493C5A
{
public:
	PlayerHealSpecialPower(Thing *thing, const ModuleData *moduleData);
};

// ??0PlayerHealSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x4C7E7E
PlayerHealSpecialPower::PlayerHealSpecialPower(Thing *thing, const ModuleData *moduleData)
	: Rva00493C5A(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
