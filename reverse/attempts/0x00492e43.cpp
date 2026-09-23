// ??0TeleportSpecialAbilityUpdateModuleData@@QAE@XZ
// partial score=0.98 date=2026-09-23
// cl: /O1 /MD /DNDEBUG /arch:SSE
//
// ??0TeleportSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x00492E43
// (54 bytes). Frameless derived ctor over the pinned Rva0044EB54
// intermediate base (0x0044EB54, size 0xC8): the base call builds the base,
// a -1.0 literal loads (DIR32-masked like the retail global 0xBBB9AC), two
// int slots clear through a shared xor-eax, the derived installs vtable
// 0x00C4E208 explicitly (Defector law; the classes carry no virtuals so the
// compiler emits no store of its own), then the int tail and the -1.0 float
// slot store. No EH (the lone base call precedes any construction).
// Identity is the ModuleFactory registration under
// "TeleportSpecialAbilityUpdate" (sole-caller data factory per the
// superseded ctor pin).

class Rva0044EB54
{
public:
	Rva0044EB54();

private:
	// No virtuals are declared (Defector law), so the pad spans the full
	// 0xC8 base ahead of the derived tail.
	unsigned char m_opaque[0xC8];
};

class TeleportSpecialAbilityUpdateModuleData : public Rva0044EB54
{
public:
	TeleportSpecialAbilityUpdateModuleData();

private:
	int m_intC8;	// +0xC8
	int m_intCC;	// +0xCC
	int m_intD0;	// +0xD0
	float m_floatD4;	// +0xD4
};

TeleportSpecialAbilityUpdateModuleData::TeleportSpecialAbilityUpdateModuleData()
	: Rva0044EB54()
{
	m_intC8 = 0;
	*(unsigned int *)this = 0x00C4E208;
	m_intCC = 0;
	m_intD0 = 0;
	m_floatD4 = -1.0f;
}
