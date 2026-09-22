// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@SiegeDockingBehavior@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x0024AF5C, 81 bytes. Named for the "SiegeDockingBehavior" literal
// ModuleFactory registers with this stub; ZH's module macro defines it on the
// module class. It news 0xC, runs the no-arg data ctor at 0x254C8E
// and hands the data plus the parse proc at 0x4598E1 to
// INI::initFromINIMultiProc when ini is non-null. SiegeDockingBehaviorModuleData is ZH's
// naming convention, not a retail fact. Recipe: CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class MultiIniFieldParse;

void SiegeDockingBehaviorParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class SiegeDockingBehaviorModuleData
{
public:
	SiegeDockingBehaviorModuleData();

private:
	char m_pad[0xC];
};

class SiegeDockingBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SiegeDockingBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SiegeDockingBehavior::friend_newModuleData(INI *ini)
{
	SiegeDockingBehaviorModuleData *data = new SiegeDockingBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SiegeDockingBehaviorParse);
	return reinterpret_cast<ModuleData *>(data);
}
