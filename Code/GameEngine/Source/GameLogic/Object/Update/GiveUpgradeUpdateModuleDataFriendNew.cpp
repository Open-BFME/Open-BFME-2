// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@GiveUpgradeUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024E800, 84 bytes. Same recipe as
// AIUpdate/ChinookAIUpdateModuleDataFriendNew.cpp: new 0xE4, run the
// declared-only nullary ctor (pinned at 0x0049C4D2; it installs vtable
// 0x00C51280), then pass the data and the class parse proc (pinned at
// 0x0049C391, pushed immediate) to INI::initFromINIMultiProc when ini is
// non-null.
//
// Identity: ModuleFactory registration at 0x00259B45 pushes the module name
// "GiveUpgradeUpdate", then this data factory (0x0064E800) and its instance
// factory (0x0064E7C5), then calls addModule (0x002573EE). This address was
// previously rowed as ChinookAIUpdate's factory from a masked placement of
// ModuleFactory.cpp's Chinook factory, which compiles to the same bytes once
// relocations are masked; ChinookAIUpdateModuleData's real factory is the
// row at 0x00251740 (0x180 bytes, vtable 0x00BF4028).

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class GiveUpgradeUpdateModuleData
{
public:
	GiveUpgradeUpdateModuleData();
	virtual ~GiveUpgradeUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xE4 - 4];
};

// ?friend_newModuleData@GiveUpgradeUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GiveUpgradeUpdateModuleData::friend_newModuleData(INI *ini)
{
	GiveUpgradeUpdateModuleData *data = new GiveUpgradeUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, GiveUpgradeUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
