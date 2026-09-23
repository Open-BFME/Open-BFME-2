// cl: /O1 /DNDEBUG /MD
//
// ??0CommandPointsUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B8661, 49 bytes.
// CommandPointsUpgrade behavior ctor over the pinned UpgradeModule base
// (0x460AEC, thing plus data): re-stores the primary vtable slot and the
// +0x0C/+0x10/+0x18 secondary slots (address-of TU-local dummies,
// DIR32-masked). The rowed name getter at 0x4B85FA and ModuleData triple
// (proc 0x4B863F plus ctor 0x254891 plus factory 0x2548D2) prove the class;
// the rowed instance factory 0x2508EE is the sole raw caller. Row supersedes
// the ctor pin.

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary18;

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

class CommandPointsUpgrade : public UpgradeModule
{
public:
	CommandPointsUpgrade(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_p18;
};

// ??0CommandPointsUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B8661
CommandPointsUpgrade::CommandPointsUpgrade(Thing *thing, const ModuleData *moduleData)
	: UpgradeModule(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p18 = &s_secondary18;
}
