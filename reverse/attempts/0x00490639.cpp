// ??0ArrowStormUpdateModuleData@@QAE@XZ
// partial score=0.97 date=2026-09-23
// cl: /O1 /MD /DNDEBUG /arch:SSE
//
// ??0ArrowStormUpdateModuleData@@QAE@XZ, retail 0x00490639 (64 bytes).
// Frameless derived ctor over the pinned Rva0044EB54 intermediate base
// (0x0044EB54, size 0xC8): the base call builds the base, int and float
// zeros share xor-eax/xorps with a single inc for the three one-valued int
// slots, the derived installs vtable 0x00C4D5A0 explicitly (Defector law;
// the classes carry no virtuals so the compiler emits no store of its own),
// the +0xC8 word clears, and the float/flag tail stores. No EH (the lone
// base call precedes any construction). Identity is the ModuleFactory
// registration under "ArrowStormUpdate" (sole-caller data factory per the
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

class ArrowStormUpdateModuleData : public Rva0044EB54
{
public:
	ArrowStormUpdateModuleData();

private:
	int m_intC8;	// +0xC8
	float m_floatCC;	// +0xCC
	int m_intD0;	// +0xD0
	int m_intD4;	// +0xD4
	int m_intD8;	// +0xD8
	bool m_flagDC;	// +0xDC
};

ArrowStormUpdateModuleData::ArrowStormUpdateModuleData()
	: Rva0044EB54()
{
	*(unsigned int *)this = 0x00C4D5A0;
	m_intC8 = 0;
	m_intD0 = 1;
	m_intD4 = 1;
	m_intD8 = 1;
	m_floatCC = 0.0f;
	m_flagDC = false;
}
