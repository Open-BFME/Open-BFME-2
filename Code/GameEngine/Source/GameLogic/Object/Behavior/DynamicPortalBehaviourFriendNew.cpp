// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DynamicPortalBehaviour@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B47B, 56 bytes. Dedicated TU: retail news 0x40 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x460B6C. Class identity is the
// "DynamicPortalBehaviour" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DynamicPortalBehaviour
{
public:
	DynamicPortalBehaviour(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x40];
};

// ?friend_newModuleInstance@DynamicPortalBehaviour@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DynamicPortalBehaviour::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DynamicPortalBehaviour(thing, moduleData));
}
