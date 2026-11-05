// cl: /DNDEBUG /MD
//
// ??0ObjectCreationUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B40A6, 68 bytes.
// ObjectCreationUpgrade behavior ctor: UpgradeMux 0-arg base at +0 (pinned
// 0x4CE2A3) then UpdateModule base at +8 (rowed 0x253390, thing plus data),
// then the derived stores in source order: int zero at +0x28 (and-RMW),
// UpdateModule-subobject vtable, primary vtable, +0x14/+0x18 secondaries
// (the class's own tables, by their retail store immediates), byte zero at +0x2C. The
// ModuleFactory registration pairs this class literal ("ObjectCreationUpgrade")
// with the module factory 0x24FF6B (news 0x30, matching this layout) and the
// rowed ModuleData factory 0x24FFAC; the module factory is the sole raw
// caller. The adjacent buildFieldParse at 0x4B4084 and ModuleData ctor at
// 0x4B425B prove the cluster. Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" const void *const __identifier("??_7ObjectCreationUpgrade@@6BUpgradeMux@@@")[];  // vftable 0x00C57660
extern "C" const void *const __identifier("??_7ObjectCreationUpgrade@@6BObjectModule@@@")[];  // vftable 0x00C5762C
extern "C" const void *const __identifier("??_7ObjectCreationUpgrade@@6BBehaviorModuleInterface@@@")[];  // vftable 0x00C57570
extern "C" const void *const __identifier("??_7ObjectCreationUpgrade@@6BUpdateModule@@@")[];  // vftable 0x00C57560

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
	m_updateVtable = __identifier("??_7ObjectCreationUpgrade@@6BObjectModule@@@");
	m_muxVtable = __identifier("??_7ObjectCreationUpgrade@@6BUpgradeMux@@@");
	m_p14 = __identifier("??_7ObjectCreationUpgrade@@6BBehaviorModuleInterface@@@");
	m_p18 = __identifier("??_7ObjectCreationUpgrade@@6BUpdateModule@@@");
	m_flag = false;
}
