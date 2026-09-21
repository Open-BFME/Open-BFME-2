// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@CivilianSpawnCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z.
// Identity: ModuleFactory registers this data factory under "CivilianSpawnCollide"
// (addModule pairs the name with it). news 0xC, runs the declared-only
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

class CivilianSpawnCollideModuleData
{
public:
	CivilianSpawnCollideModuleData();
	virtual ~CivilianSpawnCollideModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xC - 4];
};

// ?friend_newModuleData@CivilianSpawnCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CivilianSpawnCollideModuleData::friend_newModuleData(INI *ini)
{
	CivilianSpawnCollideModuleData *data = new CivilianSpawnCollideModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CivilianSpawnCollideModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
