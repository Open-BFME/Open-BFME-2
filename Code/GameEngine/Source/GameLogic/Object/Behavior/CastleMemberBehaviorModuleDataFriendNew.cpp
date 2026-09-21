// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@CastleMemberBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024AB26, 81 bytes. Dedicated TU: the factory news 0x1C, runs the
// pinned nullary ctor (0x395B03, sole raw caller is this factory at 0x24AB47),
// then feeds the new data plus the rowed parse proc (0x395AF2, pushed
// immediate 0x795AF2) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x18 pad). Recipe:
// SlaveWatcherBehaviorModuleDataFriendNew.cpp. Class identity is the rowed
// CastleMemberBehaviorModuleData::buildFieldParse proc (table 0xC1A310:
// CampDestroyedOwnerEvaEvent@8/Ally@C/Attacker@10/BeingBuiltSound@14/
// StoreUpgradePrice@18/CountsForEvaCastleBreached@19) pushed as the factory's
// proc immediate; the rowed CastleMemberBehavior pool key 0x3959B5 sits in
// the same cluster; the ctor installs vtable 0xC1A380 and fits the 0x1C news
// size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class CastleMemberBehaviorModuleData
{
public:
	CastleMemberBehaviorModuleData();
	virtual ~CastleMemberBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1C - 4];
};

// ?friend_newModuleData@CastleMemberBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CastleMemberBehaviorModuleData::friend_newModuleData(INI *ini)
{
	CastleMemberBehaviorModuleData *data = new CastleMemberBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CastleMemberBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
