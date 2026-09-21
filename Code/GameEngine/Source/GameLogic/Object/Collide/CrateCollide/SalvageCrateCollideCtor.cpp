// cl: /O1 /DNDEBUG /MD
//
// ??0SalvageCrateCollide@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004BD1D7, 42 bytes. SalvageCrateCollide behavior ctor over the pinned
// CrateCollide intermediate base (0x4BC523, thing plus data): forwards both
// args to the base, then re-stores the primary vtable slot (the behavior
// vtable 0x00C5A9C0, whose slot2 is the name getter 0x004BD201 and whose
// slot4 is the pool key 0x004BD220) and the +0x0C/+0x10 secondary slots
// (address-of TU-local dummies, DIR32-masked).
//
// The class declares no virtuals of its own: the stores land from explicit
// members in body order, so a virtual TU spelling cannot reproduce the
// order. The base ctor spelling resolves to its pin at 0x004BC523 (six raw
// callers, all CrateCollide-family behavior ctors; chains into 0x004BB702
// and the rowed BehaviorModule ctor 0x00253330). Recipe: the opaque-base
// behavior-ctor pattern (PlayerHealSpecialPowerCtor.cpp) with the
// SalvageCrateCollide file-unit (pool key at 0x004BD220 plus name getter at
// 0x004BD201 plus ctor-thunk at 0x004BD207 plus scalar-deleting-dtor at
// 0x004BD265; the instance factory at 0x002512B4 is the sole raw caller).

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Opaque intermediate base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class CrateCollide
{
public:
	CrateCollide(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	unsigned char m_pad04[0x0C - 4];
	const void *m_p0C;
	const void *m_p10;
};

class SalvageCrateCollide : public CrateCollide
{
public:
	SalvageCrateCollide(Thing *thing, const ModuleData *moduleData);
};

// ??0SalvageCrateCollide@@QAE@PAVThing@@PBVModuleData@@@Z
SalvageCrateCollide::SalvageCrateCollide(Thing *thing, const ModuleData *moduleData)
	: CrateCollide(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
