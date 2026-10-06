// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@AISpecialPowerUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024FD76, 81 bytes. Dedicated TU: the factory news 0x1C, runs the
// rowed nullary ctor (0x4B2FCD, frameless stores), then feeds the new data
// plus the class parse proc (rowed at 0x4B2F19, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x18 pad). Recipe:
// ToppleUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// AISpecialPowerUpdateModuleData::buildFieldParse proc (CommandButtonName
// plus SpecialPowerAIType plus radius plus range plus flags, linked to the
// AISpecialPowerUpdate behavior by pool-key adjacency) pushed as the
// factory's proc immediate; the ctor installs vtable 0x00C56F48 and fits the
// 0x1C news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AISpecialPowerUpdateModuleData
{
public:
	AISpecialPowerUpdateModuleData();
	virtual ~AISpecialPowerUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1C - 4];
};

// ?friend_newModuleData@AISpecialPowerUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AISpecialPowerUpdateModuleData::friend_newModuleData(INI *ini)
{
	AISpecialPowerUpdateModuleData *data = new AISpecialPowerUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AISpecialPowerUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
