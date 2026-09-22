// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FreeLifeBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251676, 59 bytes. Dedicated TU: retail news 0x114 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4C18CA. Class identity is the
// "FreeLifeBody" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class FreeLifeBody
{
public:
	FreeLifeBody(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x114];
};

// ?friend_newModuleInstance@FreeLifeBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FreeLifeBody::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FreeLifeBody(thing, moduleData));
}
