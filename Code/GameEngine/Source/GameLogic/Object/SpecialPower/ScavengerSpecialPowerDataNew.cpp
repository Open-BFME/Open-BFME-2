// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ScavengerSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x00251DCC, 84 bytes. Named for the "ScavengerSpecialPower" literal
// ModuleFactory registers with this stub; ZH's module macro defines it on the
// module class. It news 0x80, runs the no-arg data ctor at 0x4C2A6A
// and hands the data plus the parse proc at 0x4C4338 to
// INI::initFromINIMultiProc when ini is non-null. ScavengerSpecialPowerModuleData is ZH's
// naming convention, not a retail fact. Recipe: CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class MultiIniFieldParse;

void ScavengerSpecialPowerParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ScavengerSpecialPowerModuleData
{
public:
	ScavengerSpecialPowerModuleData();

private:
	char m_pad[0x80];
};

class ScavengerSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ScavengerSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ScavengerSpecialPower::friend_newModuleData(INI *ini)
{
	ScavengerSpecialPowerModuleData *data = new ScavengerSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ScavengerSpecialPowerParse);
	return reinterpret_cast<ModuleData *>(data);
}
