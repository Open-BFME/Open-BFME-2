// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@RemoveUpgradeUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025082A, 84 bytes. Dedicated TU: the factory news 0x134, runs
// the pinned ctor (0x4B7FF1, EBP-frame body), then feeds the new data plus
// the class parse proc (pinned chained link at 0x4B7F82, pushed immediate)
// to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x130 pad). Recipe:
// ReplaceObjectUpdateModuleDataFriendNew.cpp. Class identity is the pinned
// RemoveUpgradeUpgradeModuleData::buildFieldParse proc (base proc plus table
// 0x00C58EA0 holding UpgradeToRemove at +0x118 plus UpgradeGroupsToRemove at
// +0x124 plus SuppressEvaEventForRemoval at +0x130 plus
// RemoveFromAllPlayerObjects at +0x131) pushed as the factory's proc
// immediate; the RemoveUpgradeUpgrade pool key at 0x4B7F67 sits in the same
// retail cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class RemoveUpgradeUpgradeModuleData
{
public:
	RemoveUpgradeUpgradeModuleData();
	virtual ~RemoveUpgradeUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x134 - 4];
};

// ?friend_newModuleData@RemoveUpgradeUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RemoveUpgradeUpgradeModuleData::friend_newModuleData(INI *ini)
{
	RemoveUpgradeUpgradeModuleData *data = new RemoveUpgradeUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RemoveUpgradeUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
