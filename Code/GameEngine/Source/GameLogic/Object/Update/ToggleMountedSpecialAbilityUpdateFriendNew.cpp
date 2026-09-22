// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ToggleMountedSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024F68A, 59 bytes. Dedicated TU: retail news 0x90 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4ADAB5. Class identity is the
// "ToggleMountedSpecialAbilityUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ToggleMountedSpecialAbilityUpdate
{
public:
	ToggleMountedSpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x90];
};

// ?friend_newModuleInstance@ToggleMountedSpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ToggleMountedSpecialAbilityUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ToggleMountedSpecialAbilityUpdate(thing, moduleData));
}
