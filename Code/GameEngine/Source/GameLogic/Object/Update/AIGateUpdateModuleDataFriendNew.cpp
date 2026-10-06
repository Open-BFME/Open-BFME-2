// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@AIGateUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024FA64, 81 bytes. Dedicated TU: the factory news 0x10, runs the
// pinned nullary ctor (0x4B08C1, 21-byte inline installing vtable 0x00C4ED70
// plus float zeros at +8/+0xC), then feeds the new data plus the class parse
// proc (rowed at 0x4B08D7, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0xC pad). Recipe:
// ExperienceLevelCreateModuleDataFriendNew.cpp. Class identity is the rowed
// AIGateUpdateModuleData::buildFieldParse proc (table 0x00C564D4 holds
// TriggerWidthX at +8 plus TriggerWidthY at +0xC, matching the ctor stores)
// pushed as the factory's proc immediate; the AIGateUpdate pool key (rowed
// at 0x4B087C) ends where the MD ctor begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AIGateUpdateModuleData
{
public:
	AIGateUpdateModuleData();
	virtual ~AIGateUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x10 - 4];
};

// ?friend_newModuleData@AIGateUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AIGateUpdateModuleData::friend_newModuleData(INI *ini)
{
	AIGateUpdateModuleData *data = new AIGateUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AIGateUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
