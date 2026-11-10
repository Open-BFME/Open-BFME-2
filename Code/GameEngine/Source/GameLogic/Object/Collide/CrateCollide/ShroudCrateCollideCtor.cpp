// cl: /DNDEBUG /MD
//
// ??0ShroudCrateCollide@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004BCADD, 42 bytes. ShroudCrateCollide behavior ctor over the pinned
// CrateCollide intermediate base (0x4BC523, thing plus data): forwards both
// args to the base, then re-stores the primary vtable slot (the behavior
// vtable 0x00C5A8D8, whose slot2 is the name getter 0x004BCB07 pushing
// ShroudCrateCollide) and the +0x0C/+0x10 secondary slots. Its destructor
// at 0x004BCB0D stores the same collision interface table at +0x10.
//
// The class declares no virtuals of its own: the stores land from explicit
// members in body order. The base ctor spelling resolves to its pin at
// 0x004BC523. Recipe: the opaque-base behavior-ctor pattern
// (SalvageCrateCollideCtor.cpp). Class identity is the ShroudCrate retail
// cluster (pool key rowed at 0x004BCBB2 pushing the same string, name getter
// at 0x004BCB07, the instance factory at 0x002511BB is the sole raw caller).

class Thing;
class ModuleData;

extern "C" const void *const __identifier("??_7Rva004BCB0D@@6BRva004BC4FC_Root@@@")[];
extern "C" const void *const __identifier("??_7FireWeaponCollide@@6BBehaviorModuleInterface@@@")[];
extern "C" const void *const __identifier("??_7Rva004BCB0D@@6BRva004BC4FC_B2@@@")[];

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

class ShroudCrateCollide : public CrateCollide
{
public:
	ShroudCrateCollide(Thing *thing, const ModuleData *moduleData);
};

// ??0ShroudCrateCollide@@QAE@PAVThing@@PBVModuleData@@@Z
ShroudCrateCollide::ShroudCrateCollide(Thing *thing, const ModuleData *moduleData)
	: CrateCollide(thing, moduleData)
{
	m_vtable = __identifier("??_7Rva004BCB0D@@6BRva004BC4FC_Root@@@");
	m_p0C = __identifier("??_7FireWeaponCollide@@6BBehaviorModuleInterface@@@");
	m_p10 = __identifier("??_7Rva004BCB0D@@6BRva004BC4FC_B2@@@");
}
