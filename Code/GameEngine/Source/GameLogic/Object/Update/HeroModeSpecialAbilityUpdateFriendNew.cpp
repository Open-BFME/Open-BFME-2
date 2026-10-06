// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@HeroModeSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D9C7, 59 bytes. Dedicated TU: retail news 0x88 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x492179. Class identity is the
// "HeroModeSpecialAbilityUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

// The matched ctor at 0x492179 calls the SpecialAbilityUpdate base at 0x44EF5E;
// the adjacent pool-key body at 0x4921D0 independently names HeroModeSpecialAbilityUpdate.
#pragma comment(linker, "/alternatename:??0HeroModeSpecialAbilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z=??0Rva00492179@@QAE@PAVThing@@PBVModuleData@@@Z")

class Thing;
class ModuleData;
class Module;

class HeroModeSpecialAbilityUpdate
{
public:
	HeroModeSpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x88];
};

// ?friend_newModuleInstance@HeroModeSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HeroModeSpecialAbilityUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new HeroModeSpecialAbilityUpdate(thing, moduleData));
}
