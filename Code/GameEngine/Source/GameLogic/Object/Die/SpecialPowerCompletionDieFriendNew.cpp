// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SpecialPowerCompletionDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024CB69, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x486A74. Class identity is the
// "SpecialPowerCompletionDie" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SpecialPowerCompletionDie
{
public:
	SpecialPowerCompletionDie(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@SpecialPowerCompletionDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SpecialPowerCompletionDie::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SpecialPowerCompletionDie(thing, moduleData));
}
