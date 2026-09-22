// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DeployStyleAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D1E6, 59 bytes. Dedicated TU: retail news 0x4D8 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x48E983. Class identity is the
// "DeployStyleAIUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DeployStyleAIUpdate
{
public:
	DeployStyleAIUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x4D8];
};

// ?friend_newModuleInstance@DeployStyleAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DeployStyleAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DeployStyleAIUpdate(thing, moduleData));
}
