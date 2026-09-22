// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@HordeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B8F0, 59 bytes. Dedicated TU: retail news 0x30C (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x46F543. Class identity is the
// "HordeContain" literal ModuleFactory registers alongside this stub and the
// HordeContainModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class HordeContain
{
public:
	HordeContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x30C];
};

// ?friend_newModuleInstance@HordeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HordeContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new HordeContain(thing, moduleData));
}
