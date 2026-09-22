// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@BattlePlanUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "BattlePlanUpdate"
// (addModule pairs the name with it). news 0x8C and runs the declared-only
// module ctor, pinned at 0x00497ED0.

class Thing;
class ModuleData;
class Module;

class BattlePlanUpdate
{
public:
	BattlePlanUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x8C];
};

// ?friend_newModuleInstance@BattlePlanUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BattlePlanUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new BattlePlanUpdate(thing, moduleData));
}
