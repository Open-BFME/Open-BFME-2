// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0SpecialDisguiseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B0292, 85 bytes.
// SpecialDisguiseUpdate behavior ctor over the pinned Rva0044EF5E
// intermediate base (0x44EF5E, thing plus data): sets the +0x88 slot from its
// base form to its final form through a pointer-to-volatile local (address-of
// TU-local dummies, DIR32-masked; the volatile target keeps both stores so
// retail keeps the lea plus double through-eax shape, and with no barrier
// the float-zero xorps hoists above the lea), then re-stores the primary vtable slot and the +0x0C/+0x10/
// +0x20 secondary slots (address-of TU-local dummies, DIR32-masked), then
// zeroes the float at +0x8C (/arch:SSE emits retail movss) and the byte at
// +0x90. The rowed name getter at 0x4B01D3 and ModuleData factory 0x24F9D8
// prove the class; the rowed instance factory 0x24F99D (news 0x94) is the
// sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_slotBase;
static int s_slotFinal;
static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary20;

// Opaque intermediate base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x20 - 0x14];
};

class SpecialDisguiseUpdate : public Rva0044EF5E
{
public:
	SpecialDisguiseUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_p20;
	unsigned char m_pad24[0x88 - 0x24];
	const void *m_88;
	float m_8C;
	unsigned char m_90;
	unsigned char m_pad91[0x94 - 0x91];
};

// ??0SpecialDisguiseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B0292
SpecialDisguiseUpdate::SpecialDisguiseUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
	const void * volatile *slot = (const void * volatile *)((char *)this + 0x88);
	*slot = &s_slotBase;
	*slot = &s_slotFinal;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p20 = &s_secondary20;
	m_8C = 0.0f;
	m_90 = 0;
}
