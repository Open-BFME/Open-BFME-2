// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SupplyTruckAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024EED6, 59 bytes. Dedicated TU: retail news 0x408 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4A71A1. Class identity is the
// "SupplyTruckAIUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SupplyTruckAIUpdate
{
public:
	SupplyTruckAIUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x408];
};

// ?friend_newModuleInstance@SupplyTruckAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SupplyTruckAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SupplyTruckAIUpdate(thing, moduleData));
}
