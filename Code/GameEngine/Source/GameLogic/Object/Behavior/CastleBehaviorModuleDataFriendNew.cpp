// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@CastleBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z.
// Identity: ModuleFactory registers this data factory under "CastleBehavior"
// (addModule pairs the name with it). news 0x78, runs the declared-only
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

class CastleBehaviorModuleData
{
public:
	CastleBehaviorModuleData();
	virtual ~CastleBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x78 - 4];
};

// ?friend_newModuleData@CastleBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CastleBehaviorModuleData::friend_newModuleData(INI *ini)
{
	CastleBehaviorModuleData *data = new CastleBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CastleBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
