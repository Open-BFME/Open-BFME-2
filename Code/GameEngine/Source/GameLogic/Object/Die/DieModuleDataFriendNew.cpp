// cl: /O1 /GX /DNDEBUG /MD
//
// friend_newModuleData data factories for Die modules. Each one's identity is
// ModuleFactory's addModule registration, which pushes the module name with
// this factory. Every factory news its data class, runs the declared-only ctor
// and passes the class parse proc to INI::initFromINIMultiProc; both callees
// are pinned at the addresses the retail factory calls and pushes.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class CreateCrateDieModuleData
{
public:
	CreateCrateDieModuleData();
	virtual ~CreateCrateDieModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x3C - 4];
};

// ?friend_newModuleData@CreateCrateDieModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CreateCrateDieModuleData::friend_newModuleData(INI *ini)
{
	CreateCrateDieModuleData *data = new CreateCrateDieModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CreateCrateDieModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class CreateObjectDieModuleData
{
public:
	CreateObjectDieModuleData();
	virtual ~CreateObjectDieModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x4C - 4];
};

// ?friend_newModuleData@CreateObjectDieModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CreateObjectDieModuleData::friend_newModuleData(INI *ini)
{
	CreateObjectDieModuleData *data = new CreateObjectDieModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CreateObjectDieModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
