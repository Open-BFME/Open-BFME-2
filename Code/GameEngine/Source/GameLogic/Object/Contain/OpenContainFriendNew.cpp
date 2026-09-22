// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@OpenContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B6E9, 59 bytes. Dedicated TU: retail news 0xFC (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4649F8. Class identity is the
// "OpenContain" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class OpenContain
{
public:
	OpenContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0xFC];
};

// ?friend_newModuleInstance@OpenContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *OpenContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new OpenContain(thing, moduleData));
}
