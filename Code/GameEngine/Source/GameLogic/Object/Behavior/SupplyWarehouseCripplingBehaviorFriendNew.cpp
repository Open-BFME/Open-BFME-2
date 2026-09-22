// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SupplyWarehouseCripplingBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C484, 56 bytes. Dedicated TU: retail news 0x2C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x483A8B. Class identity is the
// "SupplyWarehouseCripplingBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SupplyWarehouseCripplingBehavior
{
public:
	SupplyWarehouseCripplingBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x2C];
};

// ?friend_newModuleInstance@SupplyWarehouseCripplingBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SupplyWarehouseCripplingBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SupplyWarehouseCripplingBehavior(thing, moduleData));
}
