// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@SlaveWatcherBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024C660, 81 bytes. Dedicated TU: the factory news 0x14, runs the
// rowed nullary ctor (0x4846C7, sole caller is this factory), then feeds the
// new data plus the rowed parse proc (0x4845BA, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x10 pad). Recipe:
// ToppleUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// SlaveWatcherBehaviorModuleData::buildFieldParse proc (GrantUpgrade@8/
// RemoveUpgrade@C/ShareUpgrades@10/LetSlaveLive@11 table 0xC4A208) pushed
// as the factory's proc immediate; the ctor installs unique vtable
// 0x00C4A298 and fits the 0x14 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class SlaveWatcherBehaviorModuleData
{
public:
	SlaveWatcherBehaviorModuleData();
	virtual ~SlaveWatcherBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x14 - 4];
};

// ?friend_newModuleData@SlaveWatcherBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SlaveWatcherBehaviorModuleData::friend_newModuleData(INI *ini)
{
	SlaveWatcherBehaviorModuleData *data = new SlaveWatcherBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SlaveWatcherBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
