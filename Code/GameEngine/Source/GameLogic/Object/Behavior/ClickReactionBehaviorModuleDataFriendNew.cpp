// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ClickReactionBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024AED3, 81 bytes. Dedicated TU: the factory news 0x20, runs the
// pinned nullary ctor (0x4595F0, sole raw caller is this factory at 0x24AEF4),
// then feeds the new data plus the rowed parse proc (0x45960C, pushed
// immediate 0x85960C) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x1C pad). Recipe:
// SlaveWatcherBehaviorModuleDataFriendNew.cpp. Class identity is the rowed
// ClickReactionBehaviorModuleData::buildFieldParse proc (table 0xC412F8:
// ClickReactionTimer@8/ReactionFrames1@C/2@10/3@14/4@18/5@1C) pushed as the
// factory's proc immediate; the rowed ClickReactionBehavior pool key 0x4595AB
// sits in the same cluster; the ctor fits the 0x20 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ClickReactionBehaviorModuleData
{
public:
	ClickReactionBehaviorModuleData();
	virtual ~ClickReactionBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x20 - 4];
};

// ?friend_newModuleData@ClickReactionBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ClickReactionBehaviorModuleData::friend_newModuleData(INI *ini)
{
	ClickReactionBehaviorModuleData *data = new ClickReactionBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ClickReactionBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
