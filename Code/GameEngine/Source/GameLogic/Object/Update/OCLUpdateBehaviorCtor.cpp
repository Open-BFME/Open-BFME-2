// cl: /O1 /DNDEBUG /MD
//
// ??0OCLUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0049B381, 53 bytes.
// OCLUpdate behavior ctor over the rowed UpdateModule base (0x253390):
// zeroes +0x20/+0x24/+0x28, then re-stores the primary vtable slot and the
// +0x0C/+0x10 secondary slots (address-of TU-local dummies, DIR32-masked).
// The rowed pool key at 0x49B310 and ModuleData triple (proc 0x49B370 plus
// ctor 0x49B355 plus factory 0x24E5D3) prove the class; the rowed instance
// factory 0x24E59B is the sole caller. Row supersedes the ctor pin.

class ModuleData;
class Thing;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

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

class OCLUpdate : public UpdateModule
{
public:
	OCLUpdate(Thing *thing, const ModuleData *moduleData);

private:
	int m_20;
	int m_24;
	int m_28;
};

// ??0OCLUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x49B381
OCLUpdate::OCLUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
