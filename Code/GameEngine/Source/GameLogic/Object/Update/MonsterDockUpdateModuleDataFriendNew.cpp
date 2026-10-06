// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@MonsterDockUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024EB2C, 81 bytes. Dedicated TU: the factory news 0x18, runs the
// pinned ctor (0x4A1517, EH body over the pinned DockUpdateModuleData base),
// then feeds the new data plus the class parse proc (pinned chained link at
// 0x4A137F, pushed immediate) to INI::initFromINIMultiProc (rowed at 0x2DEB5)
// when ini is non-null. Operator new and __EH_prolog resolve via their rows.
// The TU-local class keeps only size and virtuality (vptr plus 0x14 pad).
// Recipe: MissileUpdateModuleDataFriendNew.cpp. Class identity is the pinned
// MonsterDockUpdateModuleData::buildFieldParse proc (rowed DockUpdate base
// proc plus table 0x00C51CE4 holding DockableObjectFilter plus
// DockedAnimationTime) pushed as the factory's proc immediate; the
// MonsterDockUpdate pool key, Update ctor and dtor sit in the same retail
// cluster at 0x4A139A, and the BFME1 RepairDockUpdate donor proves the
// DockUpdateModuleData-subclass pattern.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class MonsterDockUpdateModuleData
{
public:
	MonsterDockUpdateModuleData();
	virtual ~MonsterDockUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x18 - 4];
};

// ?friend_newModuleData@MonsterDockUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *MonsterDockUpdateModuleData::friend_newModuleData(INI *ini)
{
	MonsterDockUpdateModuleData *data = new MonsterDockUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, MonsterDockUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
