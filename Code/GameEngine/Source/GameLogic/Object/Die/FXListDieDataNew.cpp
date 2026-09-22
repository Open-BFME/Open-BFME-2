// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@FXListDie@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x00253AB4, 81 bytes. Named for the "FXListDie" literal
// ModuleFactory registers with this stub; ZH's module macro defines it on the
// module class. It news 0x40, runs the no-arg data ctor at 0x253A78
// and hands the data plus the parse proc at 0x253A92 to
// INI::initFromINIMultiProc when ini is non-null. FXListDieModuleData is ZH's
// naming convention, not a retail fact. Recipe: CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class MultiIniFieldParse;

void FXListDieParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class FXListDieModuleData
{
public:
	FXListDieModuleData();

private:
	char m_pad[0x40];
};

class FXListDie
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FXListDie@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FXListDie::friend_newModuleData(INI *ini)
{
	FXListDieModuleData *data = new FXListDieModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, FXListDieParse);
	return reinterpret_cast<ModuleData *>(data);
}
