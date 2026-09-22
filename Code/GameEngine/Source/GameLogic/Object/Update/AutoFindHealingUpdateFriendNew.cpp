// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AutoFindHealingUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024DEC6, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x495139. Class identity is the
// "AutoFindHealingUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AutoFindHealingUpdate
{
public:
	AutoFindHealingUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@AutoFindHealingUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AutoFindHealingUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AutoFindHealingUpdate(thing, moduleData));
}
