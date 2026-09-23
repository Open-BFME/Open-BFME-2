// cl: /O1 /DNDEBUG /MD
//
// ??0StructureBody@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C0951, 49 bytes.
// StructureBody behavior ctor over the pinned ActiveBody base (0x4BF6A1,
// thing plus data): zeroes +0x100, then re-stores the primary vtable slot
// and the +0x0C/+0x10 secondary slots (address-of TU-local dummies,
// DIR32-masked). The rowed name getter at 0x4C09B5 proves the class; the
// rowed instance factory 0x2514CA is the sole raw caller. Row supersedes the
// ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Opaque ActiveBody base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class ActiveBody
{
public:
	ActiveBody(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x100 - 0x14];
	int m_100;
};

class StructureBody : public ActiveBody
{
public:
	StructureBody(Thing *thing, const ModuleData *moduleData);
};

// ??0StructureBody@@QAE@PAVThing@@PBVModuleData@@@Z @0x4C0951
StructureBody::StructureBody(Thing *thing, const ModuleData *moduleData)
	: ActiveBody(thing, moduleData)
{
	m_100 = 0;
	_ReadWriteBarrier();
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
