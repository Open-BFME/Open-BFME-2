// cl: /DNDEBUG /MD
//
// ??0SlaughterHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0048034E, 98 bytes.
// SlaughterHordeContain behavior ctor over the pinned HordeGarrisonContain
// intermediate base (0x47A040, thing plus data): forwards both args to the
// base, clears the int at +0x9E4, re-stores the primary vtable slot and eight
// secondary slots at +0x0C/+0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34
// (the class's own tables, by their retail store immediates), then clears the int at
// +0x9E8. The and-first/and-last pair uses the AudioLoop two-barrier shape.
// The rowed pool key at 0x4803B6 and ModuleData factory 0x24C071 prove the
// class; the rowed instance factory 0x24C036 (news 0x9EC) is the sole raw
// caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" const void *const __identifier("??_7SlaughterHordeContain@@6BB0@@@")[];  // vftable 0x00C48AA0
extern "C" const void *const __identifier("??_7SlaughterHordeContain@@6BB1@@@")[];  // vftable 0x00C43528
extern "C" const void *const __identifier("??_7SlaughterHordeContain@@6BB2@@@")[];  // vftable 0x00C48A90
extern "C" const void *const __identifier("??_7SlaughterHordeContain@@6BB3@@@")[];  // vftable 0x00C48918
extern "C" const void *const __identifier("??_7SlaughterHordeContain@@6BB4@@@")[];  // vftable 0x00C46064
extern "C" const void *const __identifier("??_7SlaughterHordeContain@@6BB5@@@")[];  // vftable 0x00C48910
extern "C" const void *const __identifier("??_7SlaughterHordeContain@@6BB6@@@")[];  // vftable 0x00C463D8
extern "C" const void *const __identifier("??_7SlaughterHordeContain@@6BB7@@@")[];  // vftable 0x00C488E0
extern "C" const void *const __identifier("??_7SlaughterHordeContain@@6BB8@@@")[];  // vftable 0x00C48B28

// Opaque intermediate base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class HordeGarrisonContain
{
public:
	HordeGarrisonContain(Thing *thing, const ModuleData *moduleData);

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
	unsigned char m_pad38[0x9E4 - 0x38];
};

class SlaughterHordeContain : public HordeGarrisonContain
{
public:
	SlaughterHordeContain(Thing *thing, const ModuleData *moduleData);

private:
	int m_9E4;
	int m_9E8;
};

// ??0SlaughterHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x48034E
SlaughterHordeContain::SlaughterHordeContain(Thing *thing, const ModuleData *moduleData)
	: HordeGarrisonContain(thing, moduleData)
{
	m_9E4 = 0;
	_ReadWriteBarrier();
	m_vtable = __identifier("??_7SlaughterHordeContain@@6BB0@@@");
	m_p0C = __identifier("??_7SlaughterHordeContain@@6BB1@@@");
	m_p10 = __identifier("??_7SlaughterHordeContain@@6BB2@@@");
	m_p20 = __identifier("??_7SlaughterHordeContain@@6BB3@@@");
	m_p24 = __identifier("??_7SlaughterHordeContain@@6BB4@@@");
	m_p28 = __identifier("??_7SlaughterHordeContain@@6BB5@@@");
	m_p2C = __identifier("??_7SlaughterHordeContain@@6BB6@@@");
	m_p30 = __identifier("??_7SlaughterHordeContain@@6BB7@@@");
	m_p34 = __identifier("??_7SlaughterHordeContain@@6BB8@@@");
	_ReadWriteBarrier();
	m_9E8 = 0;
}
