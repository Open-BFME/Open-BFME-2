// ??0SpecialDisguiseUpdateModuleData@@QAE@XZ
// partial score=0.98 date=2026-09-23
// cl: /O1 /MD /DNDEBUG /arch:SSE
//
// ??0SpecialDisguiseUpdateModuleData@@QAE@XZ, retail 0x004B0255 (61 bytes).
// Frameless derived ctor over the pinned Rva0044EB54 intermediate base
// (0x0044EB54, size 0xC8): the base call builds the base, int and float
// zeros share xor-eax/xorps, the derived installs vtable 0x00C563F8
// explicitly (Defector law; the classes carry no virtuals so the compiler
// emits no store of its own), then the int/byte tail and the zero float
// slot store. No EH (the lone base call precedes any construction).
// Identity is the ModuleFactory registration under "SpecialDisguiseUpdate"
// (sole-caller data factory per the superseded ctor pin).

class Rva0044EB54
{
public:
	Rva0044EB54();

private:
	// No virtuals are declared (Defector law), so the pad spans the full
	// 0xC8 base ahead of the derived tail.
	unsigned char m_opaque[0xC8];
};

class SpecialDisguiseUpdateModuleData : public Rva0044EB54
{
public:
	SpecialDisguiseUpdateModuleData();

private:
	bool m_flagC8;	// +0xC8
	float m_floatCC;	// +0xCC
	int m_intD0;	// +0xD0
	int m_intD4;	// +0xD4
	int m_intD8;	// +0xD8
	bool m_flagDC;	// +0xDC
};

SpecialDisguiseUpdateModuleData::SpecialDisguiseUpdateModuleData()
	: Rva0044EB54()
	, m_intD0(0)
	, m_intD4(0)
{
	*(unsigned int *)this = 0x00C563F8;
	m_flagC8 = false;
	m_floatCC = 0.0f;
	m_intD8 = 0;
	m_flagDC = false;
}
