// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ModelConditionSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D670, 59 bytes. Dedicated TU: retail news 0x88 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x490D3F. Class identity is the
// "ModelConditionSpecialAbilityUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

// The matched ctor at 0x490D3F calls the SpecialAbilityUpdate base at 0x44EF5E;
// the adjacent pool-key body at 0x490D96 independently names this module.
#pragma comment(linker, "/alternatename:??0ModelConditionSpecialAbilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z=??0Rva00490D3F@@QAE@PAVThing@@PBVModuleData@@@Z")

class Thing;
class ModuleData;
class Module;

class ModelConditionSpecialAbilityUpdate
{
public:
	ModelConditionSpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x88];
};

// ?friend_newModuleInstance@ModelConditionSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ModelConditionSpecialAbilityUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ModelConditionSpecialAbilityUpdate(thing, moduleData));
}
