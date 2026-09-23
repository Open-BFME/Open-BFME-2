// cl: /O1 /DNDEBUG /MD
//
// ??0EvaAnnounceClientCreate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C99D4, 50 bytes.
// EvaAnnounceClientCreate behavior ctor over the rowed Rva00362EC7 base
// (0x362EC7, thing plus data): double-stores +0x0C (first volatile) around
// an and-zero at +0x10, the primary vtable slot and a trailing zero byte at
// +0x14 (address-of TU-local dummies, DIR32-masked). The rowed name getter
// at 0x4C9A0C proves the class; the rowed instance factory 0x252A50 is the
// sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_first0C;
static int s_vtable;
static int s_secondary0C;

// Rowed Rva00362EC7 base; ctor resolves to its row. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class Rva00362EC7
{
public:
	Rva00362EC7(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	int m_10;
};

class EvaAnnounceClientCreate : public Rva00362EC7
{
public:
	EvaAnnounceClientCreate(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_14;
};

// ??0EvaAnnounceClientCreate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4C99D4
EvaAnnounceClientCreate::EvaAnnounceClientCreate(Thing *thing, const ModuleData *moduleData)
	: Rva00362EC7(thing, moduleData)
{
	*(const void * volatile *)&m_p0C = &s_first0C;
	_ReadWriteBarrier();
	m_10 = 0;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_14 = 0;
}
