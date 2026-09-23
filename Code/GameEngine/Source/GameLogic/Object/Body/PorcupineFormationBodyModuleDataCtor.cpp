// cl: /O1 /MD /DNDEBUG
//
// ??0PorcupineFormationBodyModuleData@@QAE@XZ, retail 0x004C225D (29 bytes).
// Frameless derived ctor over the rowed ActiveBodyModuleData base
// (0x004BF59F, size 0x64): the base call builds the base, two int slots and
// a byte slot clear through a shared xor-eax, then the derived installs
// vtable 0x00BF4028 explicitly at the end (Defector law; the classes carry
// no virtuals so the compiler emits no store of its own). No EH (the lone
// base call precedes any construction). Identity is the ModuleFactory
// registration under "PorcupineFormationBody" (sole-caller data factory per
// the superseded ctor pin).

class ActiveBodyModuleData
{
public:
	ActiveBodyModuleData();

private:
	// No virtuals are declared (Defector law), so the pad spans the full
	// 0x64 base: the rowed base carries its own vtable plus members, and
	// the derived tail sits at +0x64.
	unsigned char m_opaque[0x64];
};

class PorcupineFormationBodyModuleData : public ActiveBodyModuleData
{
public:
	PorcupineFormationBodyModuleData();

private:
	int m_int64;	// +0x64
	int m_int68;	// +0x68
	bool m_flag6C;	// +0x6C
};

PorcupineFormationBodyModuleData::PorcupineFormationBodyModuleData()
	: ActiveBodyModuleData()
{
	m_int64 = 0;
	m_int68 = 0;
	m_flag6C = false;
	*(unsigned int *)this = 0x00BF4028;
}
