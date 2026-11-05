// cl: /DNDEBUG /MD
//
// ??0DoCommandUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B4C2E, 49 bytes.
// DoCommandUpgrade behavior ctor over the pinned UpgradeModule base
// (0x460AEC, thing plus data): re-stores the primary vtable slot and the
// +0x0C/+0x10/+0x18 secondary slots (the class's own tables, by
// their retail store immediates). The rowed name getter at 0x4B4BC7 and ModuleData pair
// (proc 0x4B4C0C plus factory 0x2557B5) prove the class; the rowed instance
// factory 0x2500AE is the sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" const void *const __identifier("??_7DoCommandUpgrade@@6BObjectModule@@@")[];  // vftable 0x00C57B58
extern "C" const void *const __identifier("??_7DoCommandUpgrade@@6BBehaviorModuleInterface@@@")[];  // vftable 0x00C57328
extern "C" const void *const __identifier("??_7DoCommandUpgrade@@6BUpgradeMux@@@")[];  // vftable 0x00C57B10
extern "C" const void *const __identifier("??_7DoCommandUpgrade@@6BModuleInterface@@@")[];  // vftable 0x00C58790

// Opaque UpgradeModule base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class UpgradeModule
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x18 - 0x14];
};

class DoCommandUpgrade : public UpgradeModule
{
public:
	DoCommandUpgrade(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_p18;
};

// ??0DoCommandUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B4C2E
DoCommandUpgrade::DoCommandUpgrade(Thing *thing, const ModuleData *moduleData)
	: UpgradeModule(thing, moduleData)
{
	m_vtable = __identifier("??_7DoCommandUpgrade@@6BObjectModule@@@");
	m_p0C = __identifier("??_7DoCommandUpgrade@@6BBehaviorModuleInterface@@@");
	m_p10 = __identifier("??_7DoCommandUpgrade@@6BUpgradeMux@@@");
	m_p18 = __identifier("??_7DoCommandUpgrade@@6BModuleInterface@@@");
}
