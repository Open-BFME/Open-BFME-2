// cl: /DNDEBUG /MD
//
// ??0ShipSlowDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0045E9AA, 74 bytes.
// ShipSlowDeathBehavior behavior ctor over the pinned SlowDeathBehavior
// intermediate base (0x45D4B4, thing plus data): forwards both args to the
// base, then re-stores the primary vtable slot and the +0x0C/+0x10/+0x20/
// +0x24 secondary slots (the class's own tables, by their retail store
// immediates), then
// zeroes the floats at +0x50/+0x54/+0x58 (plain float members, /arch:SSE
// emits retail movss triple). The rowed name getter and ModuleData factory
// prove the class; the rowed instance factory 0x24B2F0 (news 0x5C) is the
// sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" const void *const __identifier("??_7ShipSlowDeathBehavior@@6BRva0045D39E_Root@@@")[];  // vftable 0x00C423FC
extern "C" const void *const __identifier("??_7ShipSlowDeathBehavior@@6BRva0045D39E_Mid@@@")[];  // vftable 0x00C42DA8
extern "C" const void *const __identifier("??_7ShipSlowDeathBehavior@@6BRva0045D39E_B2@@@")[];  // vftable 0x00C423F0
extern "C" const void *const __identifier("??_7ShipSlowDeathBehavior@@6BRva0045D39E_E1@@@")[];  // vftable 0x00C42030
extern "C" const void *const __identifier("??_7ShipSlowDeathBehavior@@6BRva0045D39E_E2@@@")[];  // vftable 0x00C423E0

// Opaque intermediate base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class SlowDeathBehavior
{
public:
	SlowDeathBehavior(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad14[0x20 - 0x14];
	const void *m_p20;
	const void *m_p24;
	unsigned char m_pad28[0x50 - 0x28];
};

class ShipSlowDeathBehavior : public SlowDeathBehavior
{
public:
	ShipSlowDeathBehavior(Thing *thing, const ModuleData *moduleData);

private:
	float m_50;
	float m_54;
	float m_58;
};

// ??0ShipSlowDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x45E9AA
ShipSlowDeathBehavior::ShipSlowDeathBehavior(Thing *thing, const ModuleData *moduleData)
	: SlowDeathBehavior(thing, moduleData)
{
	m_vtable = __identifier("??_7ShipSlowDeathBehavior@@6BRva0045D39E_Root@@@");
	m_p0C = __identifier("??_7ShipSlowDeathBehavior@@6BRva0045D39E_Mid@@@");
	m_p10 = __identifier("??_7ShipSlowDeathBehavior@@6BRva0045D39E_B2@@@");
	m_p20 = __identifier("??_7ShipSlowDeathBehavior@@6BRva0045D39E_E1@@@");
	m_p24 = __identifier("??_7ShipSlowDeathBehavior@@6BRva0045D39E_E2@@@");
	m_50 = 0.0f;
	m_54 = 0.0f;
	m_58 = 0.0f;
}
