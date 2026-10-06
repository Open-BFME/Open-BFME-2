// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ExperienceLevelCreateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00250BCA, 81 bytes. Dedicated TU: the factory news 0x10, runs the
// pinned nullary ctor (0x4B9220, 17-byte inline installing vtable 0x00C595E8
// plus -1 at +8 plus false at +0xC), then feeds the new data plus the class
// parse proc (rowed at 0x4B91F0, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0xC pad). Recipe:
// SlotToLockUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// ExperienceLevelCreateModuleData::buildFieldParse proc (table 0x00C595B4
// holds LevelToGrant at +8 plus MPOnly at +0xC, matching the ctor stores)
// pushed as the factory's proc immediate; the ExperienceLevelCreate pool key
// (rowed at 0x4B91AB) ends where the proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ExperienceLevelCreateModuleData
{
public:
	ExperienceLevelCreateModuleData();
	virtual ~ExperienceLevelCreateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x10 - 4];
};

// ?friend_newModuleData@ExperienceLevelCreateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ExperienceLevelCreateModuleData::friend_newModuleData(INI *ini)
{
	ExperienceLevelCreateModuleData *data = new ExperienceLevelCreateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ExperienceLevelCreateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
