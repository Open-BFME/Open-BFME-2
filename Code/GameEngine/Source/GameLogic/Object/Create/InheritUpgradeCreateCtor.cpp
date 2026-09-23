// cl: /O1 /DNDEBUG /MD
//
// ??0InheritUpgradeCreate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B9428, 42 bytes.
// InheritUpgradeCreate behavior ctor over the rowed CreateModule base
// (0x4B8CF7): re-stores the primary vtable slot and the +0x0C/+0x10
// secondary slots (address-of TU-local dummies, DIR32-masked). The rowed
// name getter at 0x4B9471 and ModuleData pair (proc 0x4B94B6 plus factory
// 0x250CC3) prove the class; the rowed instance factory 0x250C8B is the sole
// raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Rowed CreateModule base; ctor resolves to its row. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class CreateModule
{
public:
	CreateModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
};

class InheritUpgradeCreate : public CreateModule
{
public:
	InheritUpgradeCreate(Thing *thing, const ModuleData *moduleData);
};

// ??0InheritUpgradeCreate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B9428
InheritUpgradeCreate::InheritUpgradeCreate(Thing *thing, const ModuleData *moduleData)
	: CreateModule(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
