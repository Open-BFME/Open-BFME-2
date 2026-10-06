// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ScaleWallSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024DD8D, 59 bytes. Dedicated TU: retail news 0x88 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x494DCA. Class identity is the
// "ScaleWallSpecialAbilityUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

// The matched ctor at 0x494DCA calls the SpecialAbilityUpdate base at 0x44EF5E;
// the adjacent pool-key body at 0x494E83 independently names this module.
#pragma comment(linker, "/alternatename:??0ScaleWallSpecialAbilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z=??0Rva00494DCA@@QAE@PAVThing@@PBVModuleData@@@Z")

class Thing;
class ModuleData;
class Module;

class ScaleWallSpecialAbilityUpdate
{
public:
	ScaleWallSpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x88];
};

// ?friend_newModuleInstance@ScaleWallSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ScaleWallSpecialAbilityUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ScaleWallSpecialAbilityUpdate(thing, moduleData));
}
