// cl: /O1 /DNDEBUG /MD
//
// ??0PickupStuffUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00491E98, 50 bytes.
// PickupStuffUpdate behavior ctor over the rowed UpdateModule base
// (0x253390): zeroes +0x24, re-stores the primary vtable slot and the
// +0x0C/+0x10 secondary slots, then zeroes the byte at +0x20 (address-of
// TU-local dummies, DIR32-masked). The rowed pool key at 0x491DF2 and
// ModuleData triple (proc 0x491E87 plus ctor 0x491E37 plus factory 0x24D95B)
// prove the class; the rowed instance factory 0x24D923 is the sole caller.
// Row supersedes the ctor pin.

class ModuleData;
class Thing;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

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

class PickupStuffUpdate : public UpdateModule
{
public:
	PickupStuffUpdate(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_20;
	unsigned char m_pad21[3];
	int m_24;
};

// ??0PickupStuffUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x491E98
PickupStuffUpdate::PickupStuffUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_24 = 0;
	_ReadWriteBarrier();
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_20 = 0;
}
