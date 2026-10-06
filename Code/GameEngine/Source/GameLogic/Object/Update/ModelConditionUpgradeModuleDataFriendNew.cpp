// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ModelConditionUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00250546, 84 bytes. Dedicated TU: the factory news 0x1B8, runs
// the pinned ctor (0x4B6428, EH body), then feeds the new data plus the class
// parse proc (pinned chained link at 0x4B6691, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x1B4 pad). Recipe:
// AudioLoopUpgradeModuleDataFriendNew.cpp. Class identity is the pinned
// ModelConditionUpgradeModuleData::buildFieldParse proc (base proc plus
// table 0x00C58730 holding AddConditionFlags plus RemoveConditionFlags plus
// RemoveConditionFlagsInRange plus AddTempConditionFlag plus TempConditionTime)
// pushed as the factory's proc immediate; the ModelConditionUpgrade pool key
// ends where the MD ctor begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ModelConditionUpgradeModuleData
{
public:
	ModelConditionUpgradeModuleData();
	virtual ~ModelConditionUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1B8 - 4];
};

// ?friend_newModuleData@ModelConditionUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ModelConditionUpgradeModuleData::friend_newModuleData(INI *ini)
{
	ModelConditionUpgradeModuleData *data = new ModelConditionUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ModelConditionUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
