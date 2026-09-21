// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@FlammableUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z.
// Identity: ModuleFactory registers this data factory under "FlammableUpdate"
// (addModule pairs the name with it). news 0x58, runs the declared-only
// ctor, then hands the data and the class parse proc to
// INI::initFromINIMultiProc when ini is non-null; both callees are pinned.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class FlammableUpdateModuleData
{
public:
	FlammableUpdateModuleData();
	virtual ~FlammableUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x58 - 4];
};

// ?friend_newModuleData@FlammableUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FlammableUpdateModuleData::friend_newModuleData(INI *ini)
{
	FlammableUpdateModuleData *data = new FlammableUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, FlammableUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
