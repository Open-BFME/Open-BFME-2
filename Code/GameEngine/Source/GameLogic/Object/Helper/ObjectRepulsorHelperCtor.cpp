// cl: /O1 /DNDEBUG /MD
//
// ??0ObjectRepulsorHelper@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0028CAB4, 42 bytes.
// ObjectRepulsorHelper behavior ctor over the rowed ObjectHelper base
// (0x28C8DF, thing plus data): re-stores the three most-derived vtable slots
// only (address-of TU-local dummies, DIR32-masked). BFME1 donor is
// ObjectRepulsorHelper.cpp; BFME2 keeps the empty-body shape. The rowed
// factory 0x299613 (news 0x20, no new members) is the sole raw caller, and
// the ObjectRepulsorHelper pool key at 0x28CADE immediately follows. Row
// supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Opaque ObjectHelper base (0x20 bytes); 2-arg ctor resolves to its row.
class ObjectHelper
{
public:
	ObjectHelper(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_baseVtable;
	unsigned char m_midPad[0x0C - 0x04];
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_tailPad[0x20 - 0x14];
};

class ObjectRepulsorHelper : public ObjectHelper
{
public:
	ObjectRepulsorHelper(Thing *thing, const ModuleData *moduleData);
};

// ??0ObjectRepulsorHelper@@QAE@PAVThing@@PBVModuleData@@@Z @0x28CAB4
ObjectRepulsorHelper::ObjectRepulsorHelper(Thing *thing, const ModuleData *moduleData)
	: ObjectHelper(thing, moduleData)
{
	m_baseVtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
