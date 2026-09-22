// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ShipSlowDeathBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B2F0, 56 bytes. Dedicated TU: retail news 0x5C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x45E9AA. Class identity is the
// "ShipSlowDeathBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ShipSlowDeathBehavior
{
public:
	ShipSlowDeathBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x5C];
};

// ?friend_newModuleInstance@ShipSlowDeathBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ShipSlowDeathBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ShipSlowDeathBehavior(thing, moduleData));
}
