// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@BaseUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024FE37, 84 bytes. Dedicated TU: the factory news 0x124, runs
// the pinned ctor (0x4B3698, EH body), then feeds the new data plus the class
// parse proc (pinned chained link at 0x4B36FA, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x120 pad). Recipe:
// RemoveUpgradeUpgradeModuleDataFriendNew.cpp. Class identity is the pinned
// BaseUpgradeModuleData::buildFieldParse proc (base proc plus table
// 0x00C57208 holding BuildingTemplateName at +0x118 plus PlacementPrefix at
// +0x11C plus PlacementIndex at +0x120, matching the ctor stores) pushed as
// the factory's proc immediate; the BaseUpgrade pool key ends where the MD
// ctor begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class BaseUpgradeModuleData
{
public:
	BaseUpgradeModuleData();
	virtual ~BaseUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x124 - 4];
};

// ?friend_newModuleData@BaseUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BaseUpgradeModuleData::friend_newModuleData(INI *ini)
{
	BaseUpgradeModuleData *data = new BaseUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, BaseUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
