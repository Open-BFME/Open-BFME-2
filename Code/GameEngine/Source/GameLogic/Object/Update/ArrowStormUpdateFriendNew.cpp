// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ArrowStormUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "ArrowStormUpdate"
// (addModule pairs the name with it). news 0x9C and runs the declared-only
// module ctor, pinned at 0x004909D7.

class Thing;
class ModuleData;
class Module;

class ArrowStormUpdate
{
public:
	ArrowStormUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x9C];
};

// ?friend_newModuleInstance@ArrowStormUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ArrowStormUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ArrowStormUpdate(thing, moduleData));
}
