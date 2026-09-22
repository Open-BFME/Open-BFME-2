// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@BezierProjectileBehavior@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x0024B183, 84 bytes. Named for the "BezierProjectileBehavior" literal
// ModuleFactory registers with this stub; ZH's module macro defines it on the
// module class. It news 0xC4, runs the no-arg data ctor at 0x45B4F1
// and hands the data plus the parse proc at 0x45B5E3 to
// INI::initFromINIMultiProc when ini is non-null. BezierProjectileBehaviorModuleData is ZH's
// naming convention, not a retail fact. Recipe: CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class MultiIniFieldParse;

void BezierProjectileBehaviorParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class BezierProjectileBehaviorModuleData
{
public:
	BezierProjectileBehaviorModuleData();

private:
	char m_pad[0xC4];
};

class BezierProjectileBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@BezierProjectileBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BezierProjectileBehavior::friend_newModuleData(INI *ini)
{
	BezierProjectileBehaviorModuleData *data = new BezierProjectileBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, BezierProjectileBehaviorParse);
	return reinterpret_cast<ModuleData *>(data);
}
