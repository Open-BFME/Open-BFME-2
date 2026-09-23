// cl: /O1 /DNDEBUG /MD
//
// ??0W3DFloorDraw@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x000CF10B,
// 68 bytes. Draw-side ctor completing the W3DFloorDraw file-unit (name getter
// rowed at 0xCF14F returning the W3DFloorDraw literal; pool key rowed at
// 0xCF161; ModuleData factory rowed at 0x64DA6; behavior instance factory
// rowed at 0x64D6E with this ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the rowed W3DPropDraw base 0xCEEC0
// with a two-phase +0x10 word (sourced-before address-take slot commits the
// initial constant above the owner-load hoist), the derived vtable plus the
// +0x10 reinstall stored explicitly via pointer casts, four flag zeros
// sharing one xor, and a conditional flag set from the owner byte at +0x1E
// (FakePathfindPortalBehaviour two-phase precedent; no virtuals are declared
// anywhere so no vtable is emitted here; the immediates are DIR32-masked in
// comparison). Zero new pins (base resolves to its row). Row supersedes the
// ctor pin.

class ModuleData;

class Thing
{
public:
	unsigned char m_pad[0x1E];
	bool m_flag1E;
};

class W3DPropDraw
{
public:
	W3DPropDraw(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	int m_pad0C;
};

class W3DFloorDraw : public W3DPropDraw
{
public:
	W3DFloorDraw(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_10;
	bool m_flag14;
	bool m_flag15;
	bool m_flag16;
	bool m_flag17;
};

// ??0W3DFloorDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0xCF10B
W3DFloorDraw::W3DFloorDraw(Thing *thing, const ModuleData *moduleData) :
	W3DPropDraw(thing, moduleData)
{
	int *slot10 = (int *)&m_10;
	*slot10 = (int)0x00C1C780;
	*(unsigned int *)this = 0x00BCD4E0;
	m_10 = (const void *)0x00BCD4D8;
	m_flag14 = false;
	m_flag15 = false;
	m_flag16 = false;
	m_flag17 = false;
	if (m_owner->m_flag1E != 0)
		m_flag14 = true;
}
