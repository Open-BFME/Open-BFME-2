// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@StoreObjectsSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "StoreObjectsSpecialPower"
// (addModule pairs the name with it). news 0x94 and runs the declared-only
// module ctor, pinned at 0x004CD933.

class Thing;
class ModuleData;
class Module;

class StoreObjectsSpecialPower
{
public:
	StoreObjectsSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x94];
};

// ?friend_newModuleInstance@StoreObjectsSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *StoreObjectsSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new StoreObjectsSpecialPower(thing, moduleData));
}
