// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@BridgeScaffoldBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024AC90, 56 bytes. Dedicated TU: retail news 0x60 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x45831C. Class identity is the
// "BridgeScaffoldBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class BridgeScaffoldBehavior
{
public:
	BridgeScaffoldBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x60];
};

// ?friend_newModuleInstance@BridgeScaffoldBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BridgeScaffoldBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new BridgeScaffoldBehavior(thing, moduleData));
}
