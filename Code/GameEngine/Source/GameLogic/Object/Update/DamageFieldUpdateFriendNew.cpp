// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DamageFieldUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "DamageFieldUpdate"
// (addModule pairs the name with it). news 0x30 and runs the declared-only
// module ctor, pinned at 0x004912A9.

class Thing;
class ModuleData;
class Module;

class DamageFieldUpdate
{
public:
	DamageFieldUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x30];
};

// ?friend_newModuleInstance@DamageFieldUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DamageFieldUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DamageFieldUpdate(thing, moduleData));
}
