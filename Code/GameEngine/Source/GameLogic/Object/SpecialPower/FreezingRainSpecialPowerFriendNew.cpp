// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FreezingRainSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251F38, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C4BA1. Class identity is the
// "FreezingRainSpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class FreezingRainSpecialPower
{
public:
	FreezingRainSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@FreezingRainSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FreezingRainSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FreezingRainSpecialPower(thing, moduleData));
}
