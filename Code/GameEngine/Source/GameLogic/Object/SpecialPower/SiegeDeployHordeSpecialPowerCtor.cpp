// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0SiegeDeployHordeSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x004C6386, 82 bytes. Frameless behavior ctor over the pinned
// WeaponModeSpecialPowerUpdateBase base (0x58959A): re-stores the primary
// vtable slot and the +0x0C/+0x10/+0x20/+0x24 secondary slots (address-of
// TU-local dummies, DIR32-masked), zeroes +0x38, three float zeros at
// +0x3C/+0x40/+0x44, zeroes +0x48. The rowed instance factory 0x2521F4 is
// the sole caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary20;
static int s_secondary24;

class WeaponModeSpecialPowerUpdateBase
{
public:
	WeaponModeSpecialPowerUpdateBase(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	char m_pad04[0x0C - 0x04];
	const void *m_p0C;
	const void *m_p10;
	char m_pad14[0x20 - 0x14];
	const void *m_p20;
	const void *m_p24;
	char m_pad28[0x38 - 0x28];
};

class SiegeDeployHordeSpecialPower : public WeaponModeSpecialPowerUpdateBase
{
public:
	SiegeDeployHordeSpecialPower(Thing *thing, const ModuleData *moduleData);

private:
	int m_38;
	float m_3C;
	float m_40;
	float m_44;
	int m_48;
};

// ??0SiegeDeployHordeSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x4C6386
SiegeDeployHordeSpecialPower::SiegeDeployHordeSpecialPower(Thing *thing, const ModuleData *moduleData)
	: WeaponModeSpecialPowerUpdateBase(thing, moduleData)
{
	m_38 = 0;
	_ReadWriteBarrier();
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p20 = &s_secondary20;
	m_p24 = &s_secondary24;
	m_3C = 0.0f;
	m_40 = 0.0f;
	m_44 = 0.0f;
	_ReadWriteBarrier();
	m_48 = 0;
}
