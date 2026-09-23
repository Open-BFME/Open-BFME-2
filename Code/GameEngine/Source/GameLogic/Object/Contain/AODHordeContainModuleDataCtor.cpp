// cl: /O1 /MD /DNDEBUG /arch:SSE
//
// ??0AODHordeContainModuleData@@QAE@XZ, retail 0x0047A2E1 (207 bytes).
// Frameless derived ctor over the pinned HordeContainModuleData base
// (0x00475C9A, size 0x274): the base call builds the base, eleven float
// slots zero through a shared xorps, the derived installs vtable 0x00C465F8
// explicitly (Defector law; the classes carry no virtuals so the compiler
// emits no store of its own), then six float slots load from compiler
// literals (1.0/0.45/999999.0/0.3/0.4, DIR32-masked like the retail globals)
// plus a 2-valued int slot. No EH (the lone base call precedes any
// construction). Identity is the ModuleFactory registration under
// "AODHordeContain" (sole-caller data factory per the superseded ctor pin).

class HordeContainModuleData
{
public:
	HordeContainModuleData();

private:
	// No virtuals are declared (Defector law), so the pad spans the full
	// 0x274 base ahead of the derived tail.
	unsigned char m_opaque[0x274];
};

class AODHordeContainModuleData : public HordeContainModuleData
{
public:
	AODHordeContainModuleData();

private:
	float m_f274;	// +0x274
	float m_f278;	// +0x278
	float m_f27C;	// +0x27C
	float m_f280;	// +0x280
	float m_f284;	// +0x284
	float m_f288;	// +0x288
	float m_f28C;	// +0x28C
	float m_f290;	// +0x290
	float m_f294;	// +0x294
	float m_f298;	// +0x298
	float m_f29C;	// +0x29C
	float m_f2A0;	// +0x2A0
	float m_f2A4;	// +0x2A4
	float m_f2A8;	// +0x2A8
	int m_i2AC;	// +0x2AC
	float m_f2B0;	// +0x2B0
	float m_f2B4;	// +0x2B4
	float m_f2B8;	// +0x2B8
};

AODHordeContainModuleData::AODHordeContainModuleData()
	: HordeContainModuleData()
{
	*(unsigned int *)this = 0x00C465F8;
	m_f274 = 0.0f;
	m_f278 = 0.0f;
	m_f27C = 0.0f;
	m_f280 = 0.0f;
	m_f284 = 0.0f;
	m_f288 = 0.0f;
	m_f28C = 0.0f;
	m_f290 = 0.0f;
	m_f294 = 0.0f;
	m_f298 = 0.0f;
	m_f29C = 1.0f;
	m_f2A0 = 0.45f;
	m_f2A4 = 0.0f;
	m_f2A8 = 999999.0f;
	m_i2AC = 2;
	m_f2B0 = 1.0f;
	m_f2B4 = 0.3f;
	m_f2B8 = 0.4f;
}
