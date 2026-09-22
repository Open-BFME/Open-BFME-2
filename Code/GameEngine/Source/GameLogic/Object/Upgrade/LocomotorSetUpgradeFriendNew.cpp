// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@LocomotorSetUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024FF33, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B3F0B. Class identity is the
// "LocomotorSetUpgrade" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class LocomotorSetUpgrade
{
public:
	LocomotorSetUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@LocomotorSetUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *LocomotorSetUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new LocomotorSetUpgrade(thing, moduleData));
}
