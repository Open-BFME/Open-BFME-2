// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@RandomSoundSelectorClientBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025792A, 84 bytes. Dedicated TU: the factory news 0x1E0, runs the
// pinned nullary ctor (0x25785C, sole raw caller is this factory), then feeds
// the new data plus the rowed parse proc (0x4CBC09, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x1DC pad). Recipe:
// AutoAbilityBehaviorModuleDataFriendNew.cpp. Class identity is the rowed
// RandomSoundSelectorClientBehaviorModuleData::buildFieldParse proc (34B
// table-first double-add graft over the rowed voice getter at 0x33A495)
// pushed as the factory's proc immediate; the ctor fits the 0x1E0 news size; the rowed poolkey
// (RandomSoundSelectorClientBehavior at 0x4CBCAD) closes this vein beside
// the parked behavior side.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class RandomSoundSelectorClientBehaviorModuleData
{
public:
	RandomSoundSelectorClientBehaviorModuleData();
	virtual ~RandomSoundSelectorClientBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1E0 - 4];
};

// ?friend_newModuleData@RandomSoundSelectorClientBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RandomSoundSelectorClientBehaviorModuleData::friend_newModuleData(INI *ini)
{
	RandomSoundSelectorClientBehaviorModuleData *data = new RandomSoundSelectorClientBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RandomSoundSelectorClientBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
