// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@PickupStuffUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D923, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x491E98. Class identity is the
// "PickupStuffUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class PickupStuffUpdate
{
public:
	PickupStuffUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@PickupStuffUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *PickupStuffUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new PickupStuffUpdate(thing, moduleData));
}
