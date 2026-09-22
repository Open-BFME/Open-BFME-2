// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FakePathfindPortalBehaviour@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B50D, 56 bytes. Dedicated TU: retail news 0x38 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x461944. Class identity is the
// "FakePathfindPortalBehaviour" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class FakePathfindPortalBehaviour
{
public:
	FakePathfindPortalBehaviour(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x38];
};

// ?friend_newModuleInstance@FakePathfindPortalBehaviour@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FakePathfindPortalBehaviour::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FakePathfindPortalBehaviour(thing, moduleData));
}
