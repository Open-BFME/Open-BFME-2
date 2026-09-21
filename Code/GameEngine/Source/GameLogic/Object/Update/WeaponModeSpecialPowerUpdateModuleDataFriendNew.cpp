// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@WeaponModeSpecialPowerUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z.
// Identity: ModuleFactory registers this data factory under "WeaponModeSpecialPowerUpdate"
// (addModule pairs the name with it). news 0x34, runs the declared-only
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

class WeaponModeSpecialPowerUpdateModuleData
{
public:
	WeaponModeSpecialPowerUpdateModuleData();
	virtual ~WeaponModeSpecialPowerUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x34 - 4];
};

// ?friend_newModuleData@WeaponModeSpecialPowerUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WeaponModeSpecialPowerUpdateModuleData::friend_newModuleData(INI *ini)
{
	WeaponModeSpecialPowerUpdateModuleData *data = new WeaponModeSpecialPowerUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, WeaponModeSpecialPowerUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
