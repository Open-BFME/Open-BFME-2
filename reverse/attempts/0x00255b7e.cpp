// ??0SalvageCrateCollideModuleData@@QAE@XZ
// partial score=0.99 date=2026-09-23
// cl: /O1 /DNDEBUG /MD /GX- /arch:SSE
//
// ??0SalvageCrateCollideModuleData@@QAE@XZ, retail 0x00255B7E (84 bytes).
// Frameless ModuleData ctor over the rowed CrateCollideModuleData base
// (0x004BC657, size 0x5C): installs vtable 0x00BF3A40 explicitly (novtable),
// zeroes two float slots, loads 100.0/0.5 from compiler literals
// (DIR32-masked like the retail globals), stores the float tail, then the
// int tail (100/5000/zero) and the flag byte. /GX- keeps the body frameless
// (declared virtual dtor plus calls would otherwise emit an __EH_prolog
// frame); /arch:SSE selects the retail movss/xorps float idiom. Donor:
// BFME1 CrateCollide files plus the Zero Hour CrateCollide header (BFME2
// appends its own float/int tail past the 0x5C base).

class __declspec(novtable) CrateCollideModuleData
{
public:
	CrateCollideModuleData();
	virtual ~CrateCollideModuleData();

private:
	unsigned char m_opaque[0x5C - 4];
};

class __declspec(novtable) SalvageCrateCollideModuleData : public CrateCollideModuleData
{
public:
	SalvageCrateCollideModuleData();

private:
	float m_float5C;	// +0x5C
	float m_float60;	// +0x60
	float m_float64;	// +0x64
	float m_float68;	// +0x68
	float m_float6C;	// +0x6C
	int m_int70;	// +0x70
	int m_int74;	// +0x74
	int m_int78;	// +0x78
	bool m_flag7C;	// +0x7C
};

SalvageCrateCollideModuleData::SalvageCrateCollideModuleData()
{
	*(unsigned int *)this = 0x00BF3A40;
	m_float5C = 0.0f;
	m_float60 = 0.0f;
	m_float64 = 0.5f;
	m_float68 = 100.0f;
	m_float6C = 0.5f;
	m_int70 = 100;
	m_int74 = 5000;
	m_int78 = 0;
	m_flag7C = false;
}
