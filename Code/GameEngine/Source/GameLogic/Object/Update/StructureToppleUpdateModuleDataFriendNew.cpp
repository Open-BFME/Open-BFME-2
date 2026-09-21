// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@StructureToppleUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z.
// Identity: ModuleFactory registers this data factory under "StructureToppleUpdate"
// (addModule pairs the name with it). news 0xBC, runs the declared-only
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

class StructureToppleUpdateModuleData
{
public:
	StructureToppleUpdateModuleData();
	virtual ~StructureToppleUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xBC - 4];
};

// ?friend_newModuleData@StructureToppleUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StructureToppleUpdateModuleData::friend_newModuleData(INI *ini)
{
	StructureToppleUpdateModuleData *data = new StructureToppleUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, StructureToppleUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
