// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ProductionSpeedBonus@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251AC6, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C2EF5. Class identity is the
// "ProductionSpeedBonus" literal ModuleFactory registers alongside this stub and the
// ProductionSpeedBonusModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ProductionSpeedBonus
{
public:
	ProductionSpeedBonus(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@ProductionSpeedBonus@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ProductionSpeedBonus::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ProductionSpeedBonus(thing, moduleData));
}
