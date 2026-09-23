// cl: /O1 /DNDEBUG /MD
//
// ??0TerrainResourceClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00252DEB, 32 bytes.
// TerrainResourceClientBehavior behavior ctor over the rowed Rva00252B68
// base (0x252B68, thing plus data): re-stores the primary vtable slot, then
// zeroes the byte at +0x0C (address-of TU-local dummy, DIR32-masked). The
// rowed pool key at 0x252E0B proves the class; the rowed instance factory
// 0x254C56 is the sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_vtable;

// Rowed Rva00252B68 base; ctor resolves to its row. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class Rva00252B68
{
public:
	Rva00252B68(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	unsigned char m_pad04[0x0C - 4];
};

class TerrainResourceClientBehavior : public Rva00252B68
{
public:
	TerrainResourceClientBehavior(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_0C;
};

// ??0TerrainResourceClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x252DEB
TerrainResourceClientBehavior::TerrainResourceClientBehavior(Thing *thing, const ModuleData *moduleData)
	: Rva00252B68(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_0C = 0;
}
