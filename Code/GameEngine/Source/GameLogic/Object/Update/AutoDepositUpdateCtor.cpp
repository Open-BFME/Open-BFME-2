// cl: /O1 /DNDEBUG /MD
//
// ??0AutoDepositUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0049A20F,
// 68 bytes. AutoDepositUpdate behavior ctor over the rowed UpdateModule base
// (0x253390, thing plus data): materialize the owner into a named local (pins
// the early +0x04 load above the vtable stores), re-store the primary vtable
// slot and the +0x0C/+0x10 secondary slots (address-of TU-local dummies,
// DIR32-masked), clear two flags, then accumulate +0x20 from the owner word
// at +0x08 plus TheGameLogic+0x40.
//
// The rowed ModuleData pair (ctor 0x2540ED plus factory 0x254152) and the
// rowed instance factory 0x24E4ED (sole caller, ModuleFactory registration
// literal) prove the class. Row supersedes the ctor pin.

class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

class Thing
{
public:
	int m_pad[2];
	int m_08;
};

class GameLogic
{
public:
	int m_pad[0x40 / 4];
	int m_40;
};

extern GameLogic *TheGameLogic;

// Opaque UpdateModule base; ctor resolves to its row. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x20 - 0x14];
};

class AutoDepositUpdate : public UpdateModule
{
public:
	AutoDepositUpdate(Thing *thing, const ModuleData *moduleData);

private:
	int m_20;
	bool m_flag24;
	bool m_flag25;
};

// ??0AutoDepositUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x49A20F
AutoDepositUpdate::AutoDepositUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	Thing *owner = m_owner;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_flag24 = false;
	m_flag25 = false;
	m_20 = owner->m_08 + TheGameLogic->m_40;
}
