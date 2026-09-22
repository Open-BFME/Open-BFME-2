// cl: /O1 /DNDEBUG /MD
//
// ??0CreateObjectDie@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x00485A96, 42 bytes. CreateObjectDie behavior ctor over the
// pinned Rva0045CEBDUpdate intermediate base (0x45CEBD, thing plus data):
// re-stores the primary vtable slot (the behavior vtable 0x00C4A7E0) and the
// +0x0C/+0x10 secondary slots (address-of TU-local dummies, DIR32-masked).
//
// The class declares no virtuals of its own: the vtable store at +0 lands
// from the explicit m_vtable member in body order, so a virtual TU spelling
// cannot reproduce the order. The base ctor spelling resolves to its pin.
// Recipe: PlayerHealSpecialPowerCtor.cpp opaque-base pattern. Identity: the
// sole raw caller is the instance factory 0x0024C889, which ModuleFactory
// registers under "CreateObjectDie"; formerly misnamed
// CreateObjectDieIfEldestKindof (its factory 0x0024C912 calls 0x00485B4B).

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Opaque intermediate base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class Rva0045CEBDUpdate
{
public:
	Rva0045CEBDUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	unsigned char m_pad04[0x0C - 4];
	const void *m_p0C;
	const void *m_p10;
};

class CreateObjectDie : public Rva0045CEBDUpdate
{
public:
	CreateObjectDie(Thing *thing, const ModuleData *moduleData);
};

// ??0CreateObjectDie@@QAE@PAVThing@@PBVModuleData@@@Z @0x485A96
CreateObjectDie::CreateObjectDie(Thing *thing, const ModuleData *moduleData)
	: Rva0045CEBDUpdate(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
