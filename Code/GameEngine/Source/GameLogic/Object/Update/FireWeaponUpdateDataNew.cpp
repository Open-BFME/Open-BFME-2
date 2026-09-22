// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@FireWeaponUpdate@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x0024CF56, 81 bytes. Named for the "FireWeaponUpdate" literal
// ModuleFactory registers with this stub; ZH's module macro defines it on the
// module class. It news 0x10, runs the no-arg data ctor at 0x48BC03
// and hands the data plus the parse proc at 0x48C0B4 to
// INI::initFromINIMultiProc when ini is non-null. FireWeaponUpdateModuleData is ZH's
// naming convention, not a retail fact. Recipe: CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class MultiIniFieldParse;

void FireWeaponUpdateParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class FireWeaponUpdateModuleData
{
public:
	FireWeaponUpdateModuleData();

private:
	char m_pad[0x10];
};

class FireWeaponUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FireWeaponUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FireWeaponUpdate::friend_newModuleData(INI *ini)
{
	FireWeaponUpdateModuleData *data = new FireWeaponUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, FireWeaponUpdateParse);
	return reinterpret_cast<ModuleData *>(data);
}
