// cl: /DNDEBUG /MD
//
// ??0StructureBody@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C0951, 49 bytes.
// StructureBody behavior ctor over the pinned ActiveBody base (0x4BF6A1,
// thing plus data): zeroes +0x100, then re-stores the primary vtable slot
// and the +0x0C/+0x10 secondary slots. All three name the tables that
// StructureBody.cpp emits for this class (placeholder Rva004C0988), mapped by
// retail's store immediates: 0x00C5AD78 (+0x0C, BehaviorModuleInterface)
// and 0x00C5B5B0 (+0x10, body interface). The rowed name getter at 0x4C09B5 proves the class; the
// rowed instance factory 0x2514CA is the sole raw caller. Row supersedes the
// ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" const void *const __identifier("??_7Rva004C0988@@6BRva004BF951@@@")[];
extern "C" const void *const __identifier("??_7Rva004C0988@@6BMiBase1@@@")[];
extern "C" const void *const __identifier("??_7Rva004C0988@@6BRva004C0988_B2@@@")[];

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
	m_vtable = __identifier("??_7Rva004C0988@@6BRva004BF951@@@");
	m_p0C = __identifier("??_7Rva004C0988@@6BMiBase1@@@");
	m_p10 = __identifier("??_7Rva004C0988@@6BRva004C0988_B2@@@");
}
