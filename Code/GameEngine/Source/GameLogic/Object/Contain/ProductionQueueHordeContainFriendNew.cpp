// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ProductionQueueHordeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C154, 59 bytes. Dedicated TU: retail news 0x9E4 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x481343. Class identity is the
// "ProductionQueueHordeContain" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ProductionQueueHordeContain
{
public:
	ProductionQueueHordeContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x9E4];
};

// ?friend_newModuleInstance@ProductionQueueHordeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ProductionQueueHordeContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ProductionQueueHordeContain(thing, moduleData));
}
