// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RespawnBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025155B, 59 bytes. Dedicated TU: retail news 0x100 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4C12EB. Class identity is the
// "RespawnBody" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RespawnBody
{
public:
	RespawnBody(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x100];
};

// ?friend_newModuleInstance@RespawnBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RespawnBody::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RespawnBody(thing, moduleData));
}
