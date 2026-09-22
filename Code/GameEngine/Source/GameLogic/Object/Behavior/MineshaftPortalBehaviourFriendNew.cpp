// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@MineshaftPortalBehaviour@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B625, 56 bytes. Dedicated TU: retail news 0x3C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x373096. Class identity is the
// "MineshaftPortalBehaviour" literal ModuleFactory registers alongside this stub and the
// MineshaftPortalBehaviourModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class MineshaftPortalBehaviour
{
public:
	MineshaftPortalBehaviour(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x3C];
};

// ?friend_newModuleInstance@MineshaftPortalBehaviour@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *MineshaftPortalBehaviour::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new MineshaftPortalBehaviour(thing, moduleData));
}
