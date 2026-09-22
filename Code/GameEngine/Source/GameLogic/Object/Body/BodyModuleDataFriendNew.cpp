// cl: /O1 /GX /DNDEBUG /MD
//
// friend_newModuleData data factories for Body modules. Each one's identity is
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

class StructureBodyModuleData
{
public:
	StructureBodyModuleData();
	virtual ~StructureBodyModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x64 - 4];
};

// ?friend_newModuleData@StructureBodyModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StructureBodyModuleData::friend_newModuleData(INI *ini)
{
	StructureBodyModuleData *data = new StructureBodyModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, StructureBodyModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class SymbioticStructuresBodyModuleData
{
public:
	SymbioticStructuresBodyModuleData();
	virtual ~SymbioticStructuresBodyModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x68 - 4];
};

// ?friend_newModuleData@SymbioticStructuresBodyModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SymbioticStructuresBodyModuleData::friend_newModuleData(INI *ini)
{
	SymbioticStructuresBodyModuleData *data = new SymbioticStructuresBodyModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SymbioticStructuresBodyModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
