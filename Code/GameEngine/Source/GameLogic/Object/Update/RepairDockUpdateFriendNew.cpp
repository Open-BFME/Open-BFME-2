// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "ModelConditionAudioLoopClientBehavior" (addModule
// pairs the name with this factory); formerly misnamed RepairDockUpdate/RepairDockUpdateModuleData.
//
// ?friend_newModuleData@ModelConditionAudioLoopClientBehavior@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x00252D9A, 81 bytes. Dedicated TU: the rowed no-arg ctor TU
// RepairDockUpdateCtor.cpp proves a 0x14-byte root class (vtable plus a
// trailing E16 vector); the factory news 0x14, runs the declared-only ctor
// (rowed at 0x4CC20A), then feeds the new data plus the class parse proc at
// 0x4CC583 (pushed immediate, no pin) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. Recipe: CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class INI;
class MultiIniFieldParse;

void RepairDockUpdateParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ModelConditionAudioLoopClientBehavior
{
public:
	ModelConditionAudioLoopClientBehavior();
	virtual ~ModelConditionAudioLoopClientBehavior();
	static ModuleData *friend_newModuleData(INI *ini);

private:
	int m_unused04;
	unsigned char m_vec08[12];
};

// ?friend_newModuleData@ModelConditionAudioLoopClientBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ModelConditionAudioLoopClientBehavior::friend_newModuleData(INI *ini)
{
	ModelConditionAudioLoopClientBehavior *data = new ModelConditionAudioLoopClientBehavior;
	if (ini)
		ini->initFromINIMultiProc(data, RepairDockUpdateParse);
	return reinterpret_cast<ModuleData *>(data);
}
