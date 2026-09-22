// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AIUpdateInterface@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024BDB7, 59 bytes. Dedicated TU: retail news 0x3E4 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x26E9BD. Class identity is the
// "AIUpdateInterface" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AIUpdateInterface
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x3E4];
};

// ?friend_newModuleInstance@AIUpdateInterface@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AIUpdateInterface::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AIUpdateInterface(thing, moduleData));
}
