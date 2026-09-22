// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RubbleRiseUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "RubbleRiseUpdate"
// (addModule pairs the name with it). news 0x48 and runs the declared-only
// module ctor, pinned at 0x004A4CC7.

class Thing;
class ModuleData;
class Module;

class RubbleRiseUpdate
{
public:
	RubbleRiseUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x48];
};

// ?friend_newModuleInstance@RubbleRiseUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RubbleRiseUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RubbleRiseUpdate(thing, moduleData));
}
