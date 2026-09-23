// cl: /O1 /DNDEBUG /MD
//
// ??0WargBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00460804, 35 bytes.
// WargBehavior ctor over the rowed BehaviorModule base (0x253330): re-stores
// the primary vtable slot and the +0x0C secondary slot (address-of TU-local
// dummies, DIR32-masked). The rowed pool key at 0x46082D and the rowed
// instance factory 0x24B443 (sole caller, ModuleFactory registration
// literal) prove the class. Row supersedes the ctor pin.

class ModuleData;
class Thing;

static int s_vtable;
static int s_secondary0C;

// Opaque BehaviorModule base; ctor resolves to its row. The explicit
// m_vtable member stands in for the inherited vptr so body order is source
// order.
class BehaviorModule
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
};

class WargBehavior : public BehaviorModule
{
public:
	WargBehavior(Thing *thing, const ModuleData *moduleData);
};

// ??0WargBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x460804
WargBehavior::WargBehavior(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
}
