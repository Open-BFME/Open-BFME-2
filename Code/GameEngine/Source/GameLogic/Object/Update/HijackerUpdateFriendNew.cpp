// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@HijackerUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024ED27, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4A4055. Class identity is the
// "HijackerUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class HijackerUpdate
{
public:
	HijackerUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@HijackerUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HijackerUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new HijackerUpdate(thing, moduleData));
}
