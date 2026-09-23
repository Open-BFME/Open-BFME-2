// cl: /O1 /DNDEBUG /MD
//
// ??0SpecialPowerCompletionDie@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00486A74, 50 bytes.
// SpecialPowerCompletionDie behavior ctor over the pinned DieModule base
// (0x45CEBD, thing plus data): zeroes +0x14, re-stores the primary vtable
// slot and the +0x0C/+0x10 secondary slots, then zeroes the byte at +0x18
// (address-of TU-local dummies, DIR32-masked). The rowed name getter at
// 0x486A2F proves the class; the rowed instance factory 0x24CB69 is the sole
// raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Opaque DieModule base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class DieModule
{
public:
	DieModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	int m_14;
};

class SpecialPowerCompletionDie : public DieModule
{
public:
	SpecialPowerCompletionDie(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_18;
};

// ??0SpecialPowerCompletionDie@@QAE@PAVThing@@PBVModuleData@@@Z @0x486A74
SpecialPowerCompletionDie::SpecialPowerCompletionDie(Thing *thing, const ModuleData *moduleData)
	: DieModule(thing, moduleData)
{
	m_14 = 0;
	_ReadWriteBarrier();
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_18 = 0;
}
