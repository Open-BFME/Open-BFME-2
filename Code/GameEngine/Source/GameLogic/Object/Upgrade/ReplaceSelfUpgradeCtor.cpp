// cl: /O1 /DNDEBUG /MD
//
// ??0ReplaceSelfUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B7045, 63 bytes.
// ReplaceSelfUpgrade behavior ctor over the pinned UpgradeModule base
// (0x460AEC, thing plus data): double-stores +0x1C (first volatile) around
// the primary vtable slot and the +0x0C/+0x10/+0x18 secondary slots
// (address-of TU-local dummies, DIR32-masked). The rowed name getter at
// 0x4B708A proves the class; the rowed instance factory 0x250696 is the sole
// raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_first1C;
static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary18;
static int s_second1C;

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
	const void *m_p18;
};

class ReplaceSelfUpgrade : public UpgradeModule
{
public:
	ReplaceSelfUpgrade(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_p1C;
};

// ??0ReplaceSelfUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B7045
ReplaceSelfUpgrade::ReplaceSelfUpgrade(Thing *thing, const ModuleData *moduleData)
	: UpgradeModule(thing, moduleData)
{
	*(const void * volatile *)&m_p1C = &s_first1C;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p18 = &s_secondary18;
	m_p1C = &s_second1C;
}
