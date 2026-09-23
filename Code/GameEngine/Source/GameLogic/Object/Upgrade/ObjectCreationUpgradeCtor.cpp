// cl: /O1 /DNDEBUG /MD
//
// ??0ObjectCreationUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B40A6, 68 bytes.
// ObjectCreationUpgrade behavior ctor: UpgradeMux 0-arg base at +0 (pinned
// 0x4CE2A3) then UpdateModule base at +8 (rowed 0x253390, thing plus data),
// then the derived stores in source order: int zero at +0x28 (and-RMW),
// UpdateModule-subobject vtable, primary vtable, +0x14/+0x18 secondaries
// (address-of TU-local dummies, DIR32-masked), byte zero at +0x2C. The
// ModuleFactory registration pairs this class literal ("ObjectCreationUpgrade")
// with the module factory 0x24FF6B (news 0x30, matching this layout) and the
// rowed ModuleData factory 0x24FFAC; the module factory is the sole raw
// caller. The adjacent buildFieldParse at 0x4B4084 and ModuleData ctor at
// 0x4B425B prove the cluster. Row supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_vtable;
static int s_midVtable;
static int s_secondary14;
static int s_secondary18;

// Opaque UpgradeMux base at +0; 0-arg ctor resolves to its pin.
class UpgradeMux
{
public:
	UpgradeMux();

protected:
	const void *m_muxVtable;
	bool m_executed;
	unsigned char m_muxPad[3];
};

// Opaque UpdateModule base at +8 (0x20 bytes); 2-arg ctor resolves to its
// row. The explicit members stand in for the inherited slots so body order
// is source order.
class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_updateVtable;
	unsigned char m_pad0C[0x14 - 0x0C];
	const void *m_p14;
	const void *m_p18;
	unsigned char m_tail[0x28 - 0x1C];
};

class ObjectCreationUpgrade : public UpgradeMux, public UpdateModule
{
public:
	ObjectCreationUpgrade(Thing *thing, const ModuleData *moduleData);

private:
	int m_status;
	bool m_flag;
};

// ??0ObjectCreationUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B40A6
ObjectCreationUpgrade::ObjectCreationUpgrade(Thing *thing, const ModuleData *moduleData)
	: UpgradeMux(), UpdateModule(thing, moduleData)
{
	m_status = 0;
	m_updateVtable = &s_midVtable;
	m_muxVtable = &s_vtable;
	m_p14 = &s_secondary14;
	m_p18 = &s_secondary18;
	m_flag = false;
}
