// cl: /O1 /DNDEBUG /MD
//
// ??0CreateObjectDieIfEldestKindof@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00485B4B, 53 bytes.
// CreateObjectDieIfEldestKindof behavior ctor over the rowed CreateObjectDie
// behavior base (0x485A96): loads +0x14 from TheGameLogic+0x40, then
// re-stores the primary vtable slot and the +0x0C/+0x10 secondary slots
// (address-of TU-local dummies, DIR32-masked). The rowed name getter at
// 0x485A2F proves the class; the rowed instance factory 0x24C912 is the sole
// raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

class GameLogic
{
public:
	int m_pad[0x40 / 4];
	int m_40;
};

extern GameLogic *TheGameLogic;

// Rowed CreateObjectDie base; ctor resolves to its row. The explicit
// m_vtable member stands in for the inherited vptr so body order is source
// order.
class CreateObjectDie
{
public:
	CreateObjectDie(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
};

class CreateObjectDieIfEldestKindof : public CreateObjectDie
{
public:
	CreateObjectDieIfEldestKindof(Thing *thing, const ModuleData *moduleData);

private:
	int m_14;
};

// ??0CreateObjectDieIfEldestKindof@@QAE@PAVThing@@PBVModuleData@@@Z @0x485B4B
CreateObjectDieIfEldestKindof::CreateObjectDieIfEldestKindof(Thing *thing, const ModuleData *moduleData)
	: CreateObjectDie(thing, moduleData)
{
	m_14 = TheGameLogic->m_40;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
