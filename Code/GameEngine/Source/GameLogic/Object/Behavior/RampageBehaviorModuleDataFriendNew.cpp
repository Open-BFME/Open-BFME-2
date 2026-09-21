// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@RampageBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024AD38, 81 bytes. Dedicated TU: the factory news 0x2C, runs the
// pinned nullary ctor (0x458C0F, sole raw caller is this factory at 0x24AD59),
// then feeds the new data plus the rowed parse proc (0x458B4F, pushed
// immediate 0x858B4F) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x28 pad). Recipe:
// SlaveWatcherBehaviorModuleDataFriendNew.cpp. Class identity is the rowed
// RampageBehaviorModuleData::buildFieldParse proc (table 0xC40E78:
// RampageHealthThreshold@14/RampageLifeTimer@18/RampageAngryLifeTimer@1C/
// RampageResetTimer@20/RampageEnemyCheckRange@24/RampageEnemyThreshold@28/
// RequiredUpgrade@8) pushed as the factory's proc immediate; the rowed
// RampageBehavior pool key 0x458B0A (69B) ends where the proc begins; the
// ctor installs vtable 0xC40EF8 and fits the 0x2C news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class RampageBehaviorModuleData
{
public:
	RampageBehaviorModuleData();
	virtual ~RampageBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x2C - 4];
};

// ?friend_newModuleData@RampageBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RampageBehaviorModuleData::friend_newModuleData(INI *ini)
{
	RampageBehaviorModuleData *data = new RampageBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RampageBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
