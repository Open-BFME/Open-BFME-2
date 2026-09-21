// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "WeaponChangeSpecialPowerModule" (addModule
// pairs the name with this factory); formerly misnamed ScavengerSpecialPowerModuleData.
//
// ?friend_newModuleData@WeaponChangeSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x00251D40, 81 bytes. Dedicated TU: the factory news 0x9C, runs
// the pinned ctor (0x4C4257, 117B EH body over the SpecialPower base with
// the toggle bitset plus sleep-frame stores plus string members), then feeds
// the new data plus the class parse proc (rowed base-call link at 0x4C3FDD,
// pushed immediate, SpecialPower base proc plus table 0x00C5D0F0 holding
// FlagsUsedForToggle at +0x7C plus ToggleOnSleepFrames at +0x8C plus
// ToggleOffSleepFrames at +0x90 plus ToggleOnAttributeModifier at +0x94 plus
// ToggleOffAttributeModifier at +0x98) to INI::initFromINIMultiProc (rowed
// at 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. The TU-local class keeps only size and virtuality (vptr plus
// 0x98 pad). Recipe: ElvenWoodSpecialPowerModuleDataFriendNew.cpp. Class
// identity is the rowed WeaponChangeSpecialPowerModuleData::buildFieldParse
// proc pushed as the factory's proc immediate (unique image-wide); the
// ScavengerSpecialPower pool key at 0x4C4387 plus the name getter at
// 0x4C4381 sit in the same cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class WeaponChangeSpecialPowerModuleData
{
public:
	WeaponChangeSpecialPowerModuleData();
	virtual ~WeaponChangeSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x9C - 4];
};

// ?friend_newModuleData@WeaponChangeSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WeaponChangeSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	WeaponChangeSpecialPowerModuleData *data = new WeaponChangeSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, WeaponChangeSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
