// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ReplenishUnitsBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C599, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x484227. Class identity is the
// "ReplenishUnitsBehavior" literal ModuleFactory registers alongside this stub and the
// ReplenishUnitsBehaviorModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ReplenishUnitsBehavior
{
public:
	ReplenishUnitsBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@ReplenishUnitsBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ReplenishUnitsBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ReplenishUnitsBehavior(thing, moduleData));
}
