// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@CommandPointsUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x002548D2, 84 bytes. Dedicated TU: the factory news 0x120, runs
// the pinned ctor (0x254891, EH body), then feeds the new data plus the class
// parse proc (pinned chained link at 0x4B863F, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x11C pad). Recipe:
// RespawnUpdateModuleDataFriendNew.cpp. Class identity is the pinned
// CommandPointsUpgradeModuleData::buildFieldParse proc (base proc plus table
// 0x00C590E8 holding CommandPoints at +0x118 plus RequiredObject at +0x11C)
// pushed as the factory's proc immediate; the CommandPointsUpgrade pool key
// ends where the proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class CommandPointsUpgradeModuleData
{
public:
	CommandPointsUpgradeModuleData();
	virtual ~CommandPointsUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x120 - 4];
};

// ?friend_newModuleData@CommandPointsUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CommandPointsUpgradeModuleData::friend_newModuleData(INI *ini)
{
	CommandPointsUpgradeModuleData *data = new CommandPointsUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CommandPointsUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
