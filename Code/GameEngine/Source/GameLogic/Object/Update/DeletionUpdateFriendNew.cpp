// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DeletionUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "DeletionUpdate"
// (addModule pairs the name with it). news 0x24 and runs the declared-only
// module ctor, pinned at 0x004883D0.

class Thing;
class ModuleData;
class Module;

class DeletionUpdate
{
public:
	DeletionUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@DeletionUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DeletionUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DeletionUpdate(thing, moduleData));
}
