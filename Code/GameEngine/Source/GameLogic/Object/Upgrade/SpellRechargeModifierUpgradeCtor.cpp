// cl: /DNDEBUG /MD
//
// ??0SpellRechargeModifierUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B5D7D, 67 bytes.
// SpellRechargeModifierUpgrade behavior ctor over the pinned UpgradeModule
// base (0x460AEC, thing plus data): double-stores +0x1C (first volatile),
// re-stores the primary vtable slot and the +0x0C/+0x10/+0x18 secondary
// slots, then sets the byte at +0x20 to 1 (address-of TU-local dummies,
// DIR32-masked). The rowed name getter at 0x4B5D38 proves the class; the
// rowed instance factory 0x25036A is the sole raw caller. Row supersedes the
// ctor pin.

class Thing;
class ModuleData;

extern "C" char __identifier("??_7GhostObject@@6BRva001B3E60SecondBaseCore@@@");
extern "C" char __identifier("??_7Rva004B5D0B@@6BObjectModule@@@");
extern "C" char __identifier("??_7CostModifierUpgrade@@6BBehaviorModuleInterface@@@");
extern "C" char __identifier("??_7Rva004B5D0B@@6BUpgradeMux@@@");
extern "C" char __identifier("??_7AODHordeContain@@6BIface2C@@@");
extern "C" char __identifier("??_7Rva004B5D0B@@6B@");

// Opaque UpgradeModule base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class UpgradeModule
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x18 - 0x14];
	const void *m_p18;
};

class SpellRechargeModifierUpgrade : public UpgradeModule
{
public:
	SpellRechargeModifierUpgrade(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_p1C;
	unsigned char m_20;
};

// ??0SpellRechargeModifierUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B5D7D
SpellRechargeModifierUpgrade::SpellRechargeModifierUpgrade(Thing *thing, const ModuleData *moduleData)
	: UpgradeModule(thing, moduleData)
{
	*(const void * volatile *)&m_p1C = &__identifier("??_7GhostObject@@6BRva001B3E60SecondBaseCore@@@");
	m_vtable = &__identifier("??_7Rva004B5D0B@@6BObjectModule@@@");
	m_p0C = &__identifier("??_7CostModifierUpgrade@@6BBehaviorModuleInterface@@@");
	m_p10 = &__identifier("??_7Rva004B5D0B@@6BUpgradeMux@@@");
	m_p18 = &__identifier("??_7AODHordeContain@@6BIface2C@@@");
	m_p1C = &__identifier("??_7Rva004B5D0B@@6B@");
	m_20 = 1;
}
