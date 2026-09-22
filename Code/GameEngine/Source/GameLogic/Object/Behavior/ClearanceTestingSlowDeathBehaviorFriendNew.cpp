// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ClearanceTestingSlowDeathBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C50D, 56 bytes. Dedicated TU: retail news 0x54 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x483D39. Class identity is the
// "ClearanceTestingSlowDeathBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ClearanceTestingSlowDeathBehavior
{
public:
	ClearanceTestingSlowDeathBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x54];
};

// ?friend_newModuleInstance@ClearanceTestingSlowDeathBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ClearanceTestingSlowDeathBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ClearanceTestingSlowDeathBehavior(thing, moduleData));
}
