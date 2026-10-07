// cl: /DNDEBUG /MD
//
// ??0PlayerHealSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004C7E7E, 39 bytes. PlayerHealSpecialPower behavior ctor over the pinned
// SpecialPowerModule intermediate base (0x493C5A, thing plus data): re-stores the
// primary vtable slot (the behavior vtable 0x00C5E36C, distinct from the
// ModuleData vtable 0x00C5E7A8) and the +0x0C/+0x10 secondary slots
// (address-of TU-local dummies, DIR32-masked).
//
// The class declares no virtuals of its own: the vtable store at +0 lands
// from the explicit m_vtable member in body order, so a virtual TU spelling
// cannot reproduce the order. The base call now names its verified provider.
// Recipe: InvisibilityUpdateCtor.cpp opaque-base pattern with the PlayerHeal
// file-unit (pool key at 0x004C7EFB plus ModuleData proc 0x004C7E63 ending
// exactly where this ctor begins plus ModuleData factory 0x002525C7; the
// instance factory at 0x0025258F is the sole raw caller).

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Constructor-only view of the verified SpecialPowerModule base at RVA
// 0x00493C5A (SpecialPowerModuleCtor.cpp). Retail calls pass this unchanged,
// followed by Thing* and ModuleData*. Keep the already verified field view;
// the explicit vptr member preserves the native store order.
class SpecialPowerModule
{
public:
	SpecialPowerModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	unsigned char m_pad04[0x0C - 4];
	const void *m_p0C;
	const void *m_p10;
};

class PlayerHealSpecialPower : public SpecialPowerModule
{
public:
	PlayerHealSpecialPower(Thing *thing, const ModuleData *moduleData);
};

// ??0PlayerHealSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x4C7E7E
PlayerHealSpecialPower::PlayerHealSpecialPower(Thing *thing, const ModuleData *moduleData)
	: SpecialPowerModule(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
