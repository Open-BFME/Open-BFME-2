// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@DestroyDie@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x00254E7D, 81 bytes. Named for the "DestroyDie" literal
// ModuleFactory registers with this stub; ZH's module macro defines it on the
// module class. It news 0x38, runs the no-arg data ctor at 0x253510
// and hands the data plus the parse proc at 0x2534FE to
// INI::initFromINIMultiProc when ini is non-null. DestroyDieModuleData is ZH's
// naming convention, not a retail fact. Recipe: CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class MultiIniFieldParse;

void DestroyDieParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DestroyDieModuleData
{
public:
	DestroyDieModuleData();

private:
	char m_pad[0x38];
};

class DestroyDie
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DestroyDie@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DestroyDie::friend_newModuleData(INI *ini)
{
	DestroyDieModuleData *data = new DestroyDieModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DestroyDieParse);
	return reinterpret_cast<ModuleData *>(data);
}
