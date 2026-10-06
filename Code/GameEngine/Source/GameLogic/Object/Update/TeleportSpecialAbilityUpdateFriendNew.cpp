// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@TeleportSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024DBC5, 59 bytes. Dedicated TU: retail news 0x88 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x492C59. Class identity is the
// "TeleportSpecialAbilityUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

// The matched ctor at 0x492C59 calls the SpecialAbilityUpdate base at 0x44EF5E;
// the adjacent pool-key body at 0x492CB0 independently names this module.
#pragma comment(linker, "/alternatename:??0TeleportSpecialAbilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z=??0Rva00492C59@@QAE@PAVThing@@PBVModuleData@@@Z")

class Thing;
class ModuleData;
class Module;

class TeleportSpecialAbilityUpdate
{
public:
	TeleportSpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x88];
};

// ?friend_newModuleInstance@TeleportSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *TeleportSpecialAbilityUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new TeleportSpecialAbilityUpdate(thing, moduleData));
}
