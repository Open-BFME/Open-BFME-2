// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SupplyWarehouseCreate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250AD1, 56 bytes. Dedicated TU: retail news 0x18 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B8E78. Class identity is the
// "SupplyWarehouseCreate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SupplyWarehouseCreate
{
public:
	SupplyWarehouseCreate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x18];
};

// ?friend_newModuleInstance@SupplyWarehouseCreate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SupplyWarehouseCreate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SupplyWarehouseCreate(thing, moduleData));
}
