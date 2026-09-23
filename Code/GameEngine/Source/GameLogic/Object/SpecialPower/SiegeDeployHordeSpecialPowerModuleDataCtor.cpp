// cl: /O1 /MD /DNDEBUG
//
// ??0SiegeDeployHordeSpecialPowerModuleData@@QAE@XZ, retail 0x004C64D3
// (22 bytes). Frameless derived ctor over the rowed AIUpdateModuleData base
// (0x0058925D, size 0x18): the base call builds the base, then the derived
// installs vtable 0x00C5DAB0 explicitly (Defector law; the classes carry no
// virtuals so the compiler emits no store of its own) and clears the +0x18
// flag. No EH (the lone base call precedes any construction). Shares its
// vtable with SiegeDeploySpecialPowerModuleData (a Horde variant adding no
// virtuals). Identity is the ModuleFactory registration under
// "SiegeDeployHordeSpecialPower" (sole-caller data factory per the
// superseded ctor pin).

class AIUpdateModuleData
{
public:
	AIUpdateModuleData();

private:
	// No virtuals are declared (Defector law), so the pad spans the full
	// 0x18 base: the rowed base carries its own vtable plus members to
	// +0x14, and the derived flag sits at +0x18.
	unsigned char m_opaque[0x18];
};

class SiegeDeployHordeSpecialPowerModuleData : public AIUpdateModuleData
{
public:
	SiegeDeployHordeSpecialPowerModuleData();

private:
	bool m_flag18;	// +0x18
};

SiegeDeployHordeSpecialPowerModuleData::SiegeDeployHordeSpecialPowerModuleData()
	: AIUpdateModuleData()
{
	*(unsigned int *)this = 0x00C5DAB0;
	m_flag18 = false;
}
