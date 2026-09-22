// cl: /O1 /GX /DNDEBUG /MD
//
// friend_newModuleData data factories for Collide modules. Each one's identity is
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

class SalvageCrateCollideModuleData
{
public:
	SalvageCrateCollideModuleData();
	virtual ~SalvageCrateCollideModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x80 - 4];
};

// ?friend_newModuleData@SalvageCrateCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SalvageCrateCollideModuleData::friend_newModuleData(INI *ini)
{
	SalvageCrateCollideModuleData *data = new SalvageCrateCollideModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SalvageCrateCollideModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
