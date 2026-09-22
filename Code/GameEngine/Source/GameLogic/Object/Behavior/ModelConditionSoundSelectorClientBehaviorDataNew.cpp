// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ModelConditionSoundSelectorClientBehavior@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x00252C13, 81 bytes. Named for the "ModelConditionSoundSelectorClientBehavior" literal
// ModuleFactory registers with this stub; ZH's module macro defines it on the
// module class. It news 0x14, runs the no-arg data ctor at 0x4CAEE6
// and hands the data plus the parse proc at 0x4CB0F3 to
// INI::initFromINIMultiProc when ini is non-null. ModelConditionSoundSelectorClientBehaviorModuleData is ZH's
// naming convention, not a retail fact. Recipe: CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class MultiIniFieldParse;

void ModelConditionSoundSelectorClientBehaviorParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ModelConditionSoundSelectorClientBehaviorModuleData
{
public:
	ModelConditionSoundSelectorClientBehaviorModuleData();

private:
	char m_pad[0x14];
};

class ModelConditionSoundSelectorClientBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ModelConditionSoundSelectorClientBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ModelConditionSoundSelectorClientBehavior::friend_newModuleData(INI *ini)
{
	ModelConditionSoundSelectorClientBehaviorModuleData *data = new ModelConditionSoundSelectorClientBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ModelConditionSoundSelectorClientBehaviorParse);
	return reinterpret_cast<ModuleData *>(data);
}
