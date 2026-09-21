// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@InvisibilitySpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z.
// Identity: ModuleFactory registers this data factory under "InvisibilitySpecialPower"
// (addModule pairs the name with it). news 0x140, runs the declared-only
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

class InvisibilitySpecialPowerModuleData
{
public:
	InvisibilitySpecialPowerModuleData();
	virtual ~InvisibilitySpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x140 - 4];
};

// ?friend_newModuleData@InvisibilitySpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *InvisibilitySpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	InvisibilitySpecialPowerModuleData *data = new InvisibilitySpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, InvisibilitySpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
