// cl: /O1 /DNDEBUG /MD /GX- /arch:SSE
//
// ??0SiegeDeploySpecialPowerModuleData@@QAE@XZ, retail 0x004C5815 (70 bytes).
// Frameless ModuleData ctor over the rowed AIUpdateModuleData base
// (0x0058925D, size 0x18): installs vtable 0x00C5DAB0 explicitly (novtable),
// clears two int slots and two byte slots, loads two float slots from
// compiler literals (500.0/200.0, DIR32-masked like the retail globals),
// sets the +0x20 flag, and zeroes the trailing float slot. /GX- keeps the
// body frameless (declared virtual dtor plus calls would otherwise emit an
// __EH_prolog frame); /arch:SSE selects the retail movss/xorps float idiom.
// Donor: BFME1 SpecialPower files (BFME2 appends its own int/float tail past
// the 0x18 base).

class __declspec(novtable) AIUpdateModuleData
{
public:
	AIUpdateModuleData();
	virtual ~AIUpdateModuleData();

private:
	unsigned char m_opaque[0x18 - 4];
};

class __declspec(novtable) SiegeDeploySpecialPowerModuleData : public AIUpdateModuleData
{
public:
	SiegeDeploySpecialPowerModuleData();

private:
	int m_int18;	// +0x18
	int m_int1C;	// +0x1C
	bool m_flag20;	// +0x20
	bool m_byte21;	// +0x21
	bool m_byte22;	// +0x22
	float m_float24;	// +0x24
	float m_float28;	// +0x28
	float m_float2C;	// +0x2C
};

SiegeDeploySpecialPowerModuleData::SiegeDeploySpecialPowerModuleData()
{
	*(unsigned int *)this = 0x00C5DAB0;
	m_int18 = 0;
	m_int1C = 0;
	m_byte21 = false;
	m_byte22 = false;
	m_float24 = 500.0f;
	m_float28 = 200.0f;
	m_flag20 = true;
	m_float2C = 0.0f;
}
