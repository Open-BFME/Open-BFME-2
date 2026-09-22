// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RebuildHoleBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C3FB, 56 bytes. Dedicated TU: retail news 0x48 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x483271. Class identity is the
// "RebuildHoleBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RebuildHoleBehavior
{
public:
	RebuildHoleBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x48];
};

// ?friend_newModuleInstance@RebuildHoleBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RebuildHoleBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RebuildHoleBehavior(thing, moduleData));
}
