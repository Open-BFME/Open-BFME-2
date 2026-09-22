// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@BridgeTowerBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024ACC8, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x458704. Class identity is the
// "BridgeTowerBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class BridgeTowerBehavior
{
public:
	BridgeTowerBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@BridgeTowerBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BridgeTowerBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new BridgeTowerBehavior(thing, moduleData));
}
