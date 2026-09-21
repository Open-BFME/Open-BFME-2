// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@WeaponSetUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z.
// Identity: ModuleFactory registers this data factory under "WeaponSetUpgrade"
// (addModule pairs the name with it). news 0x128, runs the declared-only
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

class WeaponSetUpgradeModuleData
{
public:
	WeaponSetUpgradeModuleData();
	virtual ~WeaponSetUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x128 - 4];
};

// ?friend_newModuleData@WeaponSetUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WeaponSetUpgradeModuleData::friend_newModuleData(INI *ini)
{
	WeaponSetUpgradeModuleData *data = new WeaponSetUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, WeaponSetUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
