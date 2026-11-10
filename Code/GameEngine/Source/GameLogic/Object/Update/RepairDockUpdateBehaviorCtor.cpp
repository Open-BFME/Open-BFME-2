// cl: /DNDEBUG /MD
//
// ??0RepairDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004A118B, 67 bytes.
// RepairDockUpdate behavior ctor over the rowed DockUpdate base (0x58A290,
// thing plus data): zeroes +0x88, re-stores the primary vtable slot and the
// +0x0C/+0x10/+0x20 secondary slots, then zeroes the float at +0x8C
// (address-of TU-local dummies, DIR32-masked). The leading xorps hoists
// freely above the stores while the movss stays last, so no barrier is used
// (a barrier traps the xorps below the and). The rowed name getter at 0x4A11F4 proves
// the class; the rowed instance factory 0x24EA65 is the sole raw caller. Row
// supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" const void *const __identifier("??_7Rva004A11D4@@6BRva0058A0F4_Root@@@")[];
extern "C" const void *const __identifier("??_7MonsterDockUpdate@@6BRva0058A0F4_M1@@@")[];
static int s_secondary10;
extern "C" const void *const __identifier("??_7Rva004A11D4@@6BRva0058A0F4_E1@@@")[];

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
	int m_88;
	float m_8C;
};

class RepairDockUpdate : public DockUpdate
{
public:
	RepairDockUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0RepairDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4A118B
RepairDockUpdate::RepairDockUpdate(Thing *thing, const ModuleData *moduleData)
	: DockUpdate(thing, moduleData)
{
	m_88 = 0;
	m_vtable = __identifier("??_7Rva004A11D4@@6BRva0058A0F4_Root@@@");
	m_p0C = __identifier("??_7MonsterDockUpdate@@6BRva0058A0F4_M1@@@");
	m_p10 = &s_secondary10;
	m_p20 = __identifier("??_7Rva004A11D4@@6BRva0058A0F4_E1@@@");
	m_8C = 0.0f;
}
