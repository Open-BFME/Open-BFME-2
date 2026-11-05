// cl: /DNDEBUG /MD
//
// ??0HorseHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004765E5, 104 bytes.
// HorseHordeContain behavior ctor over the pinned HordeContain intermediate
// base (0x46F543, thing plus data): forwards both args to the base, then
// re-stores the primary vtable slot and ten secondary slots at +0x0C/+0x10/
// +0x20/+0x24/+0x28/+0x2C/+0x30/+0x34/+0xFC/+0x11C (the class's own tables,
// by their retail store immediates). The class adds no size (factory news 0x30C equals
// the base size). The rowed pool key and ModuleData factory prove the class;
// the rowed instance factory 0x24B97F (news 0x30C) is the sole raw caller.
// Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" const void *const __identifier("??_7HorseHordeContain@@6BB0@@@")[];  // vftable 0x00C45C38
extern "C" const void *const __identifier("??_7HorseHordeContain@@6BB1@@@")[];  // vftable 0x00C441B8
extern "C" const void *const __identifier("??_7HorseHordeContain@@6BB2@@@")[];  // vftable 0x00C45040
extern "C" const void *const __identifier("??_7HorseHordeContain@@6BB3@@@")[];  // vftable 0x00C45AC0
extern "C" const void *const __identifier("??_7HorseHordeContain@@6BB4@@@")[];  // vftable 0x00C45AA4
extern "C" const void *const __identifier("??_7HorseHordeContain@@6BB5@@@")[];  // vftable 0x00C46F78
extern "C" const void *const __identifier("??_7HorseHordeContain@@6BB6@@@")[];  // vftable 0x00C58790
extern "C" const void *const __identifier("??_7HorseHordeContain@@6BB7@@@")[];  // vftable 0x00C43FFC
extern "C" const void *const __identifier("??_7HorseHordeContain@@6BB8@@@")[];  // vftable 0x00C46B9C
extern "C" const void *const __identifier("??_7HorseHordeContain@@6BHFC@@@")[];  // vftable 0x00C47834
extern "C" const void *const __identifier("??_7HorseHordeContain@@6BHLC@@@")[];  // vftable 0x00C45838

// Opaque intermediate base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class HordeContain
{
public:
	HordeContain(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad14[0x20 - 0x14];
	const void *m_p20;
	const void *m_p24;
	const void *m_p28;
	const void *m_p2C;
	const void *m_p30;
	const void *m_p34;
	unsigned char m_pad38[0xFC - 0x38];
	const void *m_pFC;
	unsigned char m_pad100[0x11C - 0x100];
	const void *m_p11C;
	unsigned char m_pad120[0x30C - 0x120];
};

class HorseHordeContain : public HordeContain
{
public:
	HorseHordeContain(Thing *thing, const ModuleData *moduleData);
};

// ??0HorseHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x4765E5
HorseHordeContain::HorseHordeContain(Thing *thing, const ModuleData *moduleData)
	: HordeContain(thing, moduleData)
{
	m_vtable = __identifier("??_7HorseHordeContain@@6BB0@@@");
	m_p0C = __identifier("??_7HorseHordeContain@@6BB1@@@");
	m_p10 = __identifier("??_7HorseHordeContain@@6BB2@@@");
	m_p20 = __identifier("??_7HorseHordeContain@@6BB3@@@");
	m_p24 = __identifier("??_7HorseHordeContain@@6BB4@@@");
	m_p28 = __identifier("??_7HorseHordeContain@@6BB5@@@");
	m_p2C = __identifier("??_7HorseHordeContain@@6BB6@@@");
	m_p30 = __identifier("??_7HorseHordeContain@@6BB7@@@");
	m_p34 = __identifier("??_7HorseHordeContain@@6BB8@@@");
	m_pFC = __identifier("??_7HorseHordeContain@@6BHFC@@@");
	m_p11C = __identifier("??_7HorseHordeContain@@6BHLC@@@");
}
