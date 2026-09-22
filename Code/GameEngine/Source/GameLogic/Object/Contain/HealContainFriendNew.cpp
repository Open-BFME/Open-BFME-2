// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@HealContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B7D2, 59 bytes. Dedicated TU: retail news 0xFC (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x466AEB. Class identity is the
// "HealContain" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class HealContain
{
public:
	HealContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0xFC];
};

// ?friend_newModuleInstance@HealContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HealContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new HealContain(thing, moduleData));
}
