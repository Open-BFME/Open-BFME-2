// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0SiegeDeploySpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004C56BA, 124 bytes. Behavior-side ctor (rowed instance factory
// 0x25216B news 0x74 with this pinned 2-arg ctor as its sole raw caller
// at 0x252192).
//
// Shape is straight-line stores over the pinned WeaponModeSpecialPowerUpdate
// base (0x58959A, thing plus data): the vtable group reinstalls the primary
// slot, the +0x0C/+0x10 secondaries and +0x20/+0x24, then an int-zero run
// clears +0x38 through +0x44, float zeros land at +0x48 through +0x5C,
// a zero byte at +0x60, float zeros at +0x64 through +0x6C and a zero byte
// at +0x70. No virtuals are declared anywhere so no vtable is emitted here.
// Every store goes through a sourced-before address-take pointer (RebuildHole
// idiom): plain assignments let /O1 cluster the eax-stores above the vtable
// immediates and lift the zero bytes above the float runs, while the pointer
// indirection pins each group in program order. The immediates are the retail
// vtable slots. Row supersedes the ctor pin.

class Thing;
class ModuleData;

class WeaponModeSpecialPowerUpdateBase
{
public:
	WeaponModeSpecialPowerUpdateBase(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	const ModuleData *m_moduleData;
	void *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned char m_pad14[0x0C];
	const void *m_slot20;
	const void *m_slot24;
	unsigned char m_pad28[0x10];
};

class SiegeDeploySpecialPower : public WeaponModeSpecialPowerUpdateBase
{
public:
	SiegeDeploySpecialPower(Thing *thing, const ModuleData *moduleData);

private:
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	float m_48;
	float m_4C;
	float m_50;
	float m_54;
	float m_58;
	float m_5C;
	unsigned char m_60;
	float m_64;
	float m_68;
	float m_6C;
	unsigned char m_70;
	unsigned char m_pad71[0x03];
};

// ??0SiegeDeploySpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x004C56BA
SiegeDeploySpecialPower::SiegeDeploySpecialPower(Thing *thing, const ModuleData *moduleData)
	: WeaponModeSpecialPowerUpdateBase(thing, moduleData)
{
	int *slot00 = (int *)&m_vtable;
	*slot00 = (int)0x00C5DCFC;
	int *slot0C = (int *)&m_secondary0C;
	*slot0C = (int)0x00C4E998;
	int *slot10 = (int *)&m_secondary10;
	*slot10 = (int)0x00C5DCF0;
	int *slot20 = (int *)&m_slot20;
	*slot20 = (int)0x00C5DCCC;
	int *slot24 = (int *)&m_slot24;
	*slot24 = (int)0x00C5DC68;
	m_38 = 0;
	m_3C = 0;
	m_40 = 0;
	m_44 = 0;
	float *cell48 = &m_48;
	*cell48 = 0.0f;
	float *cell4C = &m_4C;
	*cell4C = 0.0f;
	float *cell50 = &m_50;
	*cell50 = 0.0f;
	float *cell54 = &m_54;
	*cell54 = 0.0f;
	float *cell58 = &m_58;
	*cell58 = 0.0f;
	float *cell5C = &m_5C;
	*cell5C = 0.0f;
	unsigned char *cell60 = &m_60;
	*cell60 = 0;
	float *cell64 = &m_64;
	*cell64 = 0.0f;
	float *cell68 = &m_68;
	*cell68 = 0.0f;
	float *cell6C = &m_6C;
	*cell6C = 0.0f;
	unsigned char *cell70 = &m_70;
	*cell70 = 0;
}
