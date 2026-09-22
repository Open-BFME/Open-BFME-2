// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@BridgeBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024AC00, 59 bytes. Dedicated TU: retail news 0x108 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x457472. Class identity is the
// "BridgeBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class BridgeBehavior
{
public:
	BridgeBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x108];
};

// ?friend_newModuleInstance@BridgeBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BridgeBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new BridgeBehavior(thing, moduleData));
}
