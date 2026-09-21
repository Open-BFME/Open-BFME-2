// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@OCLSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z.
// Identity: ModuleFactory registers this data factory under "OCLSpecialPower"
// (addModule pairs the name with it). news 0xA0, runs the declared-only
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

class OCLSpecialPowerModuleData
{
public:
	OCLSpecialPowerModuleData();
	virtual ~OCLSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xA0 - 4];
};

// ?friend_newModuleData@OCLSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *OCLSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	OCLSpecialPowerModuleData *data = new OCLSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, OCLSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
