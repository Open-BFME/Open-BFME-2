// cl: /O1 /DNDEBUG /MD
//
// ??0VeterancyCrateCollide@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004BCE32, 42 bytes. VeterancyCrateCollide behavior ctor over the pinned
// CrateCollide intermediate base (0x4BC523, thing plus data): forwards both
// args to the base, then re-stores the primary vtable slot (the behavior
// vtable 0x00C5A954, whose slot2 is the name getter 0x004BCE5C pushing
// VeterancyCrateCollide) and the +0x0C/+0x10 secondary slots (address-of
// TU-local dummies, DIR32-masked).
//
// The class declares no virtuals of its own: the stores land from explicit
// members in body order. The base ctor spelling resolves to its pin at
// 0x004BC523. Recipe: the opaque-base behavior-ctor pattern
// (SalvageCrateCollideCtor.cpp). Class identity is the VeterancyCrate retail
// cluster (pool key rowed at 0x004BCE7B, name getter at 0x004BCE5C, the
// instance factory at 0x00251261 is the sole raw caller).

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

class VeterancyCrateCollide : public CrateCollide
{
public:
	VeterancyCrateCollide(Thing *thing, const ModuleData *moduleData);
};

// ??0VeterancyCrateCollide@@QAE@PAVThing@@PBVModuleData@@@Z
VeterancyCrateCollide::VeterancyCrateCollide(Thing *thing, const ModuleData *moduleData)
	: CrateCollide(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
