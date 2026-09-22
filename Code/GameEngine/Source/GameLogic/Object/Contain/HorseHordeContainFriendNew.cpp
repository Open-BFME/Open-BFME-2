// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@HorseHordeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B97F, 59 bytes. Dedicated TU: retail news 0x30C (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4765E5. Class identity is the
// "HorseHordeContain" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class HorseHordeContain
{
public:
	HorseHordeContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x30C];
};

// ?friend_newModuleInstance@HorseHordeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HorseHordeContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new HorseHordeContain(thing, moduleData));
}
