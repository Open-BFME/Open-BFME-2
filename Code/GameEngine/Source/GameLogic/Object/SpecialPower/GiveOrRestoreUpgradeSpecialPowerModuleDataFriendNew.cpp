// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@GiveOrRestoreUpgradeSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00253003, 84 bytes. Dedicated TU: the factory news 0xE0, runs
// the rowed ctor (0x4CD0B1, frameless body over the Rva0044EB54 base with
// the CommandButton plus UpgradeToGive zeros and the FlagsUsedForToggle
// bitset reset), then feeds the new data plus the class parse proc (rowed
// chained link at 0x4CD061, pushed immediate) to INI::initFromINIMultiProc
// (rowed at 0x2DEB5) when ini is non-null. Operator new and __EH_prolog
// resolve via their rows. The TU-local class keeps only size and virtuality
// (vptr plus 0xDC pad). Recipe:
// ElvenWoodSpecialPowerModuleDataFriendNew.cpp. Class identity is the rowed
// GiveOrRestoreUpgradeSpecialPowerModuleData::buildFieldParse proc (Rva
// base proc plus table 0x0085F8C0 holding CommandButton at +0xC8 plus
// UpgradeToGive at +0xCC plus FlagsUsedForToggle at +0xD0) pushed as the
// factory's proc immediate; the GiveOrRestoreUpgradeSpecialPower pool key
// at 0x4CD14B sits in the same cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class GiveOrRestoreUpgradeSpecialPowerModuleData
{
public:
	GiveOrRestoreUpgradeSpecialPowerModuleData();
	virtual ~GiveOrRestoreUpgradeSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xE0 - 4];
};

// ?friend_newModuleData@GiveOrRestoreUpgradeSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GiveOrRestoreUpgradeSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	GiveOrRestoreUpgradeSpecialPowerModuleData *data = new GiveOrRestoreUpgradeSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, GiveOrRestoreUpgradeSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
