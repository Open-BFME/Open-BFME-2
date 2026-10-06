// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@SpawnUnitBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x002559F1, 81 bytes. Dedicated TU: the factory news 0x20, runs the
// declared-only nullary ctor (pinned at 0x25598C, sole raw E8 caller is this
// factory), then feeds the new data plus the class parse proc (rowed at
// 0x4B8840, pushed immediate) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new resolves via its row. The
// TU-local class keeps only size and virtuality (vptr plus 0x1C pad).
// Recipe: SupplyTruckAIUpdateModuleDataFriendNew.cpp. Class identity is the
// rowed SpawnUnitBehaviorModuleData::buildFieldParse proc (UnitName plus
// UnitCommand plus SpawnOnce with SpawnOnce at 0x1C per BFME1
// SpawnUnitBehavior) pushed as the factory's proc immediate; the ctor
// installs vtable 0x00BF36C0 and fits the 0x20 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class SpawnUnitBehaviorModuleData
{
public:
	SpawnUnitBehaviorModuleData();
	virtual ~SpawnUnitBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x20 - 4];
};

// ?friend_newModuleData@SpawnUnitBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpawnUnitBehaviorModuleData::friend_newModuleData(INI *ini)
{
	SpawnUnitBehaviorModuleData *data = new SpawnUnitBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SpawnUnitBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
