// cl: /DNDEBUG /MD
//
// ??0SpecialDisguiseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B0292, 85 bytes.
// SpecialDisguiseUpdate behavior ctor over the pinned Rva0044EF5E
// intermediate base (0x44EF5E, thing plus data): sets the +0x88 slot from its
// base form to its final form through a pointer-to-volatile local (the base
// slot still uses a dummy; the final slot uses the recovered shared table).
// The volatile target keeps both stores so
// retail keeps the lea plus double through-eax shape, and with no barrier
// the float-zero xorps hoists above the lea. Then it re-stores the primary
// vtable slot and the +0x0C/+0x10/+0x20 secondary slots (using shared tables
// where recovered), then
// zeroes the float at +0x8C (/arch:SSE emits retail movss) and the byte at
// +0x90. The rowed name getter at 0x4B01D3 and ModuleData factory 0x24F9D8
// prove the class; the rowed instance factory 0x24F99D (news 0x94) is the
// sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" const void *const __identifier("??_7GhostObject@@6BRva001B3E60SecondBaseCore@@@")[];
extern "C" const void *const s_dummy62C8[4];
extern "C" const void *const __identifier("??_7Rva004B0164@@6B@")[];
extern "C" const void *const s_dummy62D8[47];
extern "C" const void *const __identifier("??_7ArrowStormUpdate@@6BUpdateModule@@@")[];
extern "C" const void *const __identifier("??_7SpecialAbilityUpdate@@6BSpecialPowerUpdateInterface@@@")[9];

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
	*slot = __identifier("??_7GhostObject@@6BRva001B3E60SecondBaseCore@@@");
	*slot = s_dummy62C8;
	m_vtable = __identifier("??_7Rva004B0164@@6B@");
	m_p0C = s_dummy62D8;
	m_p10 = __identifier("??_7ArrowStormUpdate@@6BUpdateModule@@@");
	m_p20 = __identifier("??_7SpecialAbilityUpdate@@6BSpecialPowerUpdateInterface@@@");
	m_8C = 0.0f;
	m_90 = 0;
}
