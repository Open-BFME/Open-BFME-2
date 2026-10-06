// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@SpecialEnemySenseUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025409C, 81 bytes. Dedicated TU: the factory news 0x14, runs the
// pinned ctor (0x25404A, EH body with filter at +8 plus zero float at +0xC
// plus one at +0x10), then feeds the new data plus the class parse proc
// (rowed at 0x25408B, pushed immediate, no pin) to INI::initFromINIMultiProc
// (rowed at 0x2DEB5) when ini is non-null. Operator new and __EH_prolog
// resolve via their rows. The TU-local class keeps only size and virtuality
// (vptr plus 0x10 pad). Recipe:
// AIGateUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// SpecialEnemySenseUpdateModuleData::buildFieldParse proc (table 0x00BF1B88
// holds SpecialEnemyFilter at +8 plus ScanRange at +0xC plus ScanInterval at
// +0x10, matching the ctor stores) pushed as the factory's proc immediate;
// ctor, proc and factory are triple-contiguous at 0x25404A, and the
// SpecialEnemySenseUpdate pool key is rowed at 0x499F64.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class SpecialEnemySenseUpdateModuleData
{
public:
	SpecialEnemySenseUpdateModuleData();
	virtual ~SpecialEnemySenseUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x14 - 4];
};

// ?friend_newModuleData@SpecialEnemySenseUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpecialEnemySenseUpdateModuleData::friend_newModuleData(INI *ini)
{
	SpecialEnemySenseUpdateModuleData *data = new SpecialEnemySenseUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SpecialEnemySenseUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
