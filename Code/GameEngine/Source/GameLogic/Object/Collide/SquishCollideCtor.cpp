// cl: /O1 /DNDEBUG /MD
//
// ??0SquishCollide@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004BB9CF, 42 bytes. SquishCollide behavior ctor over the pinned
// CollideModule intermediate base (0x4BB702, thing plus data): forwards both
// args to the base, then re-stores the primary vtable slot (the behavior
// vtable 0x00C5A204, whose slot2 is the name getter 0x004BB962 pushing
// SquishCollide) and the +0x0C/+0x10 secondary slots (address-of TU-local
// dummies, DIR32-masked).
//
// The class declares no virtuals of its own: the stores land from explicit
// members in body order. The base ctor spelling resolves to its pin at
// 0x004BB702. Recipe: the opaque-base behavior-ctor pattern
// (SalvageCrateCollideCtor.cpp). Donor: BFME1 SquishCollideConstructor.cpp
// inits CollideModule directly. Class identity is the Squish retail cluster
// (vtable slot2 getter, the instance factory at 0x00250FE6 is the sole raw
// caller).

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

class SquishCollide : public CollideModule
{
public:
	SquishCollide(Thing *thing, const ModuleData *moduleData);
};

// ??0SquishCollide@@QAE@PAVThing@@PBVModuleData@@@Z
SquishCollide::SquishCollide(Thing *thing, const ModuleData *moduleData)
	: CollideModule(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
