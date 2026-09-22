// cl: /O1 /GX /DNDEBUG /MD
// Target: ModuleFactory registers this factory as "PhysicsBehavior"; it calls
// the ctor at 0x00390119 and pushes the parser at 0x003901C9.
// Donor: the BFME1 DumbProjectileBehavior data header informed the 0x5C layout;
// its class name is not the target identity.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class PhysicsBehaviorModuleData
{
public:
	PhysicsBehaviorModuleData();
	virtual ~PhysicsBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x5C - 4];
};

// ?friend_newModuleData@PhysicsBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PhysicsBehaviorModuleData::friend_newModuleData(INI *ini)
{
	PhysicsBehaviorModuleData *data = new PhysicsBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, PhysicsBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
