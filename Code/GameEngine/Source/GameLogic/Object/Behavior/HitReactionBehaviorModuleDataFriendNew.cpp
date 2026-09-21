// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@HitReactionBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024AE4A, 81 bytes. Dedicated TU: the factory news 0x24, runs the
// pinned nullary ctor (0x4591EA, sole raw caller is this factory at 0x24AE6B),
// then feeds the new data plus the rowed parse proc (0x459217, pushed
// immediate 0x859217) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x20 pad). Recipe:
// SlaveWatcherBehaviorModuleDataFriendNew.cpp. Class identity is the rowed
// HitReactionBehaviorModuleData::buildFieldParse proc (table 0xC410F0:
// HitReactionLifeTimer1@8/2@C/3@10/Threshold1@14/2@18/3@1C/FastHitsReset@20/
// HitsParalyze@21) pushed as the factory's proc immediate; the rowed
// HitReactionBehavior pool key 0x4591A5 sits in the same cluster; the ctor
// fits the 0x24 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class HitReactionBehaviorModuleData
{
public:
	HitReactionBehaviorModuleData();
	virtual ~HitReactionBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x24 - 4];
};

// ?friend_newModuleData@HitReactionBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HitReactionBehaviorModuleData::friend_newModuleData(INI *ini)
{
	HitReactionBehaviorModuleData *data = new HitReactionBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, HitReactionBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
