// cl: /O1 /DNDEBUG /MD
//
// ??0CivilianSpawnCollide@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004BD694, 42 bytes. CivilianSpawnCollide behavior ctor over the pinned
// CollideModule intermediate base (0x4BB702, thing plus data): forwards both
// args to the base, then re-stores the primary vtable slot (the behavior
// vtable 0x00C5AA88, whose slot2 is the name getter 0x004BD606 pushing
// CivilianSpawnCollide) and the +0x0C/+0x10 secondary slots (address-of
// TU-local dummies, DIR32-masked).
//
// The class declares no virtuals of its own: the stores land from explicit
// members in body order. The base ctor spelling resolves to its pin at
// 0x004BB702. Recipe: the opaque-base behavior-ctor pattern
// (SquishCollideCtor.cpp). Donor: BFME1 CivilianSpawnCollideCtorThunk.cpp
// declares the (Thing, ModuleData) ctor. Class identity is the
// CivilianSpawn retail cluster (vtable slot2 getter, the instance factory
// at 0x002512EC is the sole raw caller).

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Opaque intermediate base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class CollideModule
{
public:
	CollideModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	unsigned char m_pad04[0x0C - 4];
	const void *m_p0C;
	const void *m_p10;
};

class CivilianSpawnCollide : public CollideModule
{
public:
	CivilianSpawnCollide(Thing *thing, const ModuleData *moduleData);
};

// ??0CivilianSpawnCollide@@QAE@PAVThing@@PBVModuleData@@@Z
CivilianSpawnCollide::CivilianSpawnCollide(Thing *thing, const ModuleData *moduleData)
	: CollideModule(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
