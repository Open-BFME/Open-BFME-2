// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@UnpauseSpecialPowerUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025018E, 84 bytes. Dedicated TU: the factory news 0x120, runs
// the rowed ctor (0x4B544A, frameless body over the OpenContain base with
// the SpecialPowerTemplate zero and the ObeyRechageOnTrigger flag), then
// feeds the new data plus the class parse proc (rowed double-add link at
// 0x4B546A, pushed immediate) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. The TU-local class keeps only size and virtuality (vptr plus
// 0x11C pad). Recipe:
// ElvenWoodSpecialPowerModuleDataFriendNew.cpp. Class identity is the rowed
// UnpauseSpecialPowerUpgradeModuleData::buildFieldParse proc (getter table
// plus table 0x00857EF0 holding SpecialPowerTemplate at +0x118 plus
// ObeyRechageOnTrigger at +0x11C) pushed as the factory's proc immediate;
// the UnpauseSpecialPowerUpgrade pool-key function at 0x4B5405 ends where
// the ctor begins in the same cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class UnpauseSpecialPowerUpgradeModuleData
{
public:
	UnpauseSpecialPowerUpgradeModuleData();
	virtual ~UnpauseSpecialPowerUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x120 - 4];
};

// ?friend_newModuleData@UnpauseSpecialPowerUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *UnpauseSpecialPowerUpgradeModuleData::friend_newModuleData(INI *ini)
{
	UnpauseSpecialPowerUpgradeModuleData *data = new UnpauseSpecialPowerUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, UnpauseSpecialPowerUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
