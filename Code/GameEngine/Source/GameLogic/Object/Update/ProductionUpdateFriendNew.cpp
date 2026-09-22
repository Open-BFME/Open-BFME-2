// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ProductionUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E854, 59 bytes. Dedicated TU: retail news 0x140 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x49E03A. Class identity is the
// "ProductionUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ProductionUpdate
{
public:
	ProductionUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x140];
};

// ?friend_newModuleInstance@ProductionUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ProductionUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ProductionUpdate(thing, moduleData));
}
