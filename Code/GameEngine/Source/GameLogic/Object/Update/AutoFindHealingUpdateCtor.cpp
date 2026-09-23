// cl: /O1 /DNDEBUG /MD
//
// ??0AutoFindHealingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00495139, 46 bytes.
// AutoFindHealingUpdate behavior ctor over the rowed UpdateModule base
// (0x253390): zeroes +0x20, then re-stores the primary vtable slot and the
// +0x0C/+0x10 secondary slots (address-of TU-local dummies, DIR32-masked).
// The rowed pool key at 0x4950B4 and ModuleData triple (proc 0x495128 plus
// ctor 0x4950F9 plus factory 0x24DEFE) prove the class; the rowed instance
// factory 0x24DEC6 is the sole caller. Row supersedes the ctor pin.

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

class AutoFindHealingUpdate : public UpdateModule
{
public:
	AutoFindHealingUpdate(Thing *thing, const ModuleData *moduleData);

private:
	int m_20;
};

// ??0AutoFindHealingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x495139
AutoFindHealingUpdate::AutoFindHealingUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_20 = 0;
	_ReadWriteBarrier();
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
