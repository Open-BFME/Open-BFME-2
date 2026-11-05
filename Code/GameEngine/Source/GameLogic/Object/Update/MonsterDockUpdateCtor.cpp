// cl: /DNDEBUG /MD
//
// ??0MonsterDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004A139A, 70 bytes.
// MonsterDockUpdate behavior ctor over the rowed DockUpdate base (0x58A290,
// thing plus data): zeroes +0x8C, re-stores the primary vtable slot and the
// +0x0C/+0x10/+0x20 secondary slots, then sets the bytes at +0x88/+0x89 to
// 1/0 (the class's own tables, by their retail store immediates). The rowed name getter at
// 0x4A1414 proves the class; the rowed instance factory 0x24EAF1 is the sole
// raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" const void *const __identifier("??_7MonsterDockUpdate@@6BRva0058A0F4_Root@@@")[];  // vftable 0x00C51D74
extern "C" const void *const __identifier("??_7MonsterDockUpdate@@6BRva0058A0F4_M1@@@")[];  // vftable 0x00C51B20
extern "C" const void *const __identifier("??_7MonsterDockUpdate@@6BRva0058A0F4_B2@@@")[];  // vftable 0x00C51D68
extern "C" const void *const __identifier("??_7MonsterDockUpdate@@6BRva0058A0F4_E1@@@")[];  // vftable 0x00C51D18

// Rowed DockUpdate base; ctor resolves to its row. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class DockUpdate
{
public:
	DockUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x20 - 0x14];
	const void *m_p20;
	unsigned char m_pad24[0x88 - 0x24];
	unsigned char m_88;
	unsigned char m_89;
	int m_8C;
};

class MonsterDockUpdate : public DockUpdate
{
public:
	MonsterDockUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0MonsterDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4A139A
MonsterDockUpdate::MonsterDockUpdate(Thing *thing, const ModuleData *moduleData)
	: DockUpdate(thing, moduleData)
{
	m_8C = 0;
	_ReadWriteBarrier();
	m_vtable = __identifier("??_7MonsterDockUpdate@@6BRva0058A0F4_Root@@@");
	m_p0C = __identifier("??_7MonsterDockUpdate@@6BRva0058A0F4_M1@@@");
	m_p10 = __identifier("??_7MonsterDockUpdate@@6BRva0058A0F4_B2@@@");
	m_p20 = __identifier("??_7MonsterDockUpdate@@6BRva0058A0F4_E1@@@");
	m_88 = 1;
	m_89 = 0;
}
