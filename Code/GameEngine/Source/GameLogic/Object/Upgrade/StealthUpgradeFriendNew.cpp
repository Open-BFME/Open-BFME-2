// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@StealthUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025011E, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B5378. Class identity is the
// "StealthUpgrade" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class StealthUpgrade
{
public:
	StealthUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@StealthUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *StealthUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new StealthUpgrade(thing, moduleData));
}
