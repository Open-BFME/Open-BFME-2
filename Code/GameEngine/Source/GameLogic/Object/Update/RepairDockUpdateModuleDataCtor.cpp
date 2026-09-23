// cl: /O1 /MD /DNDEBUG /arch:SSE
//
// ??0RepairDockUpdateModuleData@@QAE@XZ, retail 0x004A1297 (31 bytes).
// Frameless derived ctor over the rowed DockUpdateModuleData base
// (0x005896B0): the base call builds the base, a 1.0 literal loads
// (DIR32-masked like the retail global 0xBBB8D8), the derived installs
// vtable 0x00C4ED70 explicitly (Defector law; the classes carry no virtuals
// so the compiler emits no store of its own), and the +0x10 float slot
// stores. No EH (the lone base call precedes any construction). Identity is
// the ModuleFactory registration under "RepairDockUpdate" (sole-caller data
// factory per the superseded ctor pin).

class DockUpdateModuleData
{
public:
	DockUpdateModuleData();

private:
	// Base writes through +0x0C per its rowed ctor; pad so the derived
	// float lands at +0x10.
	unsigned char m_opaque[0x10];
};

class RepairDockUpdateModuleData : public DockUpdateModuleData
{
public:
	RepairDockUpdateModuleData();

private:
	float m_float10;	// +0x10
};

RepairDockUpdateModuleData::RepairDockUpdateModuleData()
	: DockUpdateModuleData()
{
	*(unsigned int *)this = 0x00C4ED70;
	m_float10 = 1.0f;
}
