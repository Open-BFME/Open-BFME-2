// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@DetachableRiderUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z.
// Identity: ModuleFactory registers this data factory under "DetachableRiderUpdate"
// (addModule pairs the name with it). news 0x28, runs the declared-only
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

class DetachableRiderUpdateModuleData
{
public:
	DetachableRiderUpdateModuleData();
	virtual ~DetachableRiderUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x28 - 4];
};

// ?friend_newModuleData@DetachableRiderUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DetachableRiderUpdateModuleData::friend_newModuleData(INI *ini)
{
	DetachableRiderUpdateModuleData *data = new DetachableRiderUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DetachableRiderUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
