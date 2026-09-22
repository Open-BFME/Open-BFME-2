// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RespawnUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024F8F6, 56 bytes. Dedicated TU: retail news 0x44 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4AF096. Class identity is the
// "RespawnUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RespawnUpdate
{
public:
	RespawnUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x44];
};

// ?friend_newModuleInstance@RespawnUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RespawnUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RespawnUpdate(thing, moduleData));
}
