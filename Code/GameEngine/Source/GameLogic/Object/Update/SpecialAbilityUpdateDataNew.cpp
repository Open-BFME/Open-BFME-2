// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@SpecialAbilityUpdate@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x0024A882, 84 bytes. Named for the "SpecialAbilityUpdate" literal
// ModuleFactory registers with this stub; ZH's module macro defines it on the
// module class. It news 0xC8, runs the no-arg data ctor at 0x44EB54
// and hands the data plus the parse proc at 0x44ED95 to
// INI::initFromINIMultiProc when ini is non-null. SpecialAbilityUpdateModuleData is ZH's
// naming convention, not a retail fact. Recipe: CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class MultiIniFieldParse;

void SpecialAbilityUpdateParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class SpecialAbilityUpdateModuleData
{
public:
	SpecialAbilityUpdateModuleData();

private:
	char m_pad[0xC8];
};

class SpecialAbilityUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SpecialAbilityUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpecialAbilityUpdate::friend_newModuleData(INI *ini)
{
	SpecialAbilityUpdateModuleData *data = new SpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SpecialAbilityUpdateParse);
	return reinterpret_cast<ModuleData *>(data);
}
