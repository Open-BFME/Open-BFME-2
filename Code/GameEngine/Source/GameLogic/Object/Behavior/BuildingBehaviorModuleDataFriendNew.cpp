// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@BuildingBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024ABAF, 81 bytes. Dedicated TU: the factory news 0x38, runs the
// pinned nullary ctor (0x456489, sole raw caller is this factory; vtable
// 0xC40798 plus 4-element window-name member at plus-0x8 via the 0x629512
// helper), then feeds the new data plus the rowed parse proc (0x456206,
// pushed immediate) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x34 pad).
// Recipe: SlaveWatcherBehaviorModuleDataFriendNew.cpp. Class identity is
// the rowed BuildingBehaviorModuleData::buildFieldParse proc
// (NightWindowName plus FireWindowName plus GlowWindowName plus FireName,
// table 0xC40748) pushed as the factory's proc immediate; the rowed
// BuildingBehavior pool key at 0x4561C1 ends where the proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class BuildingBehaviorModuleData
{
public:
	BuildingBehaviorModuleData();
	virtual ~BuildingBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x38 - 4];
};

// ?friend_newModuleData@BuildingBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BuildingBehaviorModuleData::friend_newModuleData(INI *ini)
{
	BuildingBehaviorModuleData *data = new BuildingBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, BuildingBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
