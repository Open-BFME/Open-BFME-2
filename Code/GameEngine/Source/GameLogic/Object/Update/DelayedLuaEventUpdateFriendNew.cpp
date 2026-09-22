// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DelayedLuaEventUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "DelayedLuaEventUpdate"
// (addModule pairs the name with it). news 0x78 and runs the declared-only
// module ctor, pinned at 0x004A8E7B.

class Thing;
class ModuleData;
class Module;

class DelayedLuaEventUpdate
{
public:
	DelayedLuaEventUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x78];
};

// ?friend_newModuleInstance@DelayedLuaEventUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DelayedLuaEventUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DelayedLuaEventUpdate(thing, moduleData));
}
